#include "WalkabilityMap.h"
#include "../Line3D/Line3D.h"

using namespace OUAN;
using namespace boost;

WalkabilityMap::WalkabilityMap()
{
	mVisible=false;
	mDebugObjects=0;
	mSceneManager=0;
}

WalkabilityMap::~WalkabilityMap()
{

}

int WalkabilityMap::getNodeNumber(std::string nodeName)
{
	TNodeNumbersIterator it;

	it=mNodeNumbers.find(nodeName);

	if(it==mNodeNumbers.end())
	{
		Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Walkability Map Node "+
			nodeName+" does not exist");
		return -1;
	}
	else
	{
		return mNodeNumbers[nodeName];
	}
}

std::string WalkabilityMap::getNodeName(int nodeNumber)
{
	return mGraph[vertex(nodeNumber,mGraph)].mSceneNode->getName();
}

void WalkabilityMap::init(TWalkabilityMapParameters tWalkabilityMapParameters,Ogre::SceneManager * pSceneManager,Ogre::SceneNode * pDebugObjects)
{
		unsigned int i,j;

		mDebugObjects=pDebugObjects;
		mSceneManager=pSceneManager;

		mName=tWalkabilityMapParameters.name;

		mDebugObjects->createChildSceneNode("walkability#"+tWalkabilityMapParameters.name);

		myLines.clear();
		myNodes.clear();

		//init node numbers
		mNodeNumbers.clear();
		for(i=0;i<tWalkabilityMapParameters.walkabilityNodes.size();i++)
		{
			mNodeNumbers[tWalkabilityMapParameters.walkabilityNodes[i].nodeName]=i;
		}

		//init graph
		mGraph.clear();
		mGraph = Graph(mNodeNumbers.size());

		Ogre::SceneNode * pSceneNode;
		Ogre::Entity * pEntity;
		Ogre::SceneNode * pEntityDebugNode;
		//create graph nodes
		for(i=0;i<tWalkabilityMapParameters.walkabilityNodes.size();i++)
		{
			//Ogre::LogManager::getSingleton().logMessage("Adding node "+tWalkabilityMapParameters.walkabilityNodes[i].nodeName);

			if(pSceneManager->hasSceneNode(tWalkabilityMapParameters.walkabilityNodes[i].nodeName))
			{
				pSceneNode=pSceneManager->getSceneNode(tWalkabilityMapParameters.walkabilityNodes[i].nodeName);
			}
			else
			{
				pSceneNode=pSceneManager->getRootSceneNode()->createChildSceneNode(tWalkabilityMapParameters.walkabilityNodes[i].nodeName);
				pSceneNode->setPosition(tWalkabilityMapParameters.walkabilityNodes[i].position);
				pSceneNode->setOrientation(tWalkabilityMapParameters.walkabilityNodes[i].orientation);
			}

			mGraph[getNodeNumber(tWalkabilityMapParameters.walkabilityNodes[i].nodeName)].mSceneNode=pSceneNode;

			//create graphics debug objects
			std::string debugName="walkability#"+tWalkabilityMapParameters.name+"#"+tWalkabilityMapParameters.walkabilityNodes[i].nodeName;
			pEntityDebugNode=mDebugObjects->createChildSceneNode(debugName);
			pEntityDebugNode->setPosition(pSceneNode->getPosition());
			pEntityDebugNode->setVisible(mVisible);
			pEntity=pSceneManager->createEntity(debugName,"node.mesh");
			pEntity->setMaterialName("red");
			pEntity->setVisible(mVisible);
			pEntity->setQueryFlags(OUAN::QUERYFLAGS_NONE);
			pEntityDebugNode->attachObject(pEntity);

			myNodes.push_back(pEntity);
		}

		//add graph edges
		for(i=0;i<tWalkabilityMapParameters.walkabilityNodes.size();i++)
		{
			for(j=0;j<tWalkabilityMapParameters.walkabilityNodes[i].neighbors.size();j++)
			{
				//Ogre::LogManager::getSingleton().logMessage("Adding edge "+tWalkabilityMapParameters.walkabilityNodes[i].nodeName+"-"
				//	+tWalkabilityMapParameters.walkabilityNodes[i].neighbors[j]);

				if(hasNode(tWalkabilityMapParameters.walkabilityNodes[i].neighbors[j]))
				{
					add_edge(getNodeNumber(tWalkabilityMapParameters.walkabilityNodes[i].nodeName.c_str()),
						getNodeNumber(tWalkabilityMapParameters.walkabilityNodes[i].neighbors[j].c_str()),
						mGraph);
				}
			}
		}

		//set graph edges properties
		Graph::vertex_descriptor v1,v2;
		Ogre::SceneNode * pSceneNode1;
		Ogre::SceneNode * pSceneNode2;

		Graph::edge_descriptor e;

		boost::graph_traits<Graph>::edge_iterator eit,eend;

		boost::property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, mGraph);
		i=0;

		Line3D *myLine; 

		for (tie(eit, eend) = edges(mGraph); eit != eend; ++eit) 
		{
			Graph::edge_descriptor e = *eit;

			v1=source(e, mGraph);
			v2=target(e, mGraph);
			pSceneNode1=mGraph[v1].mSceneNode;
			pSceneNode2=mGraph[v2].mSceneNode;

			weightmap[e]=pSceneNode1->getPosition().distance(pSceneNode2->getPosition());

			//create graphics debug objects
			myLine = new Line3D();
			myLine->addPoint(pSceneNode1->getPosition());
			myLine->addPoint(pSceneNode2->getPosition());
			myLine->setMaterial("black");
			myLine->drawLines();
			mDebugObjects->attachObject(myLine);
			mDebugObjects->setVisible(mVisible);

			myLines.push_back(myLine);
		}

		//print graph information
		Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Walkability map vertices");
		boost::graph_traits<Graph>::vertex_iterator vit,vend;
		for (tie(vit, vend) = vertices(mGraph); vit != vend; ++vit) 
		{
			Ogre::LogManager::getSingleton().logMessage("Vertex "+mGraph[*vit].mSceneNode->getName());
		}

		Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Walkability map edges");
		for (tie(eit, eend) = edges(mGraph); eit != eend; ++eit) 
		{
			v1=source(*eit, mGraph);
			v2=target(*eit, mGraph);

			Ogre::LogManager::getSingleton().logMessage("Edge "+mGraph[v1].mSceneNode->getName()+"-"+mGraph[v2].mSceneNode->getName()+
				" distance:"+Ogre::StringConverter::toString(Ogre::Real(weightmap[*eit])));
		}
}

int WalkabilityMap::getNearestNode(Ogre::Vector3 position)
{
	int nearestNode=-1;
	double minDistance=-1;
	double currentDistance;

	boost::graph_traits<Graph>::vertex_iterator vit,vend;
	for (tie(vit, vend) = vertices(mGraph); vit != vend; ++vit) 
	{
		currentDistance=position.distance(mGraph[*vit].mSceneNode->getPosition());
		if(minDistance==-1 || minDistance>currentDistance)
		{
			minDistance=currentDistance;
			nearestNode=*vit;
		}
	}

	return nearestNode;
}

std::vector<Ogre::SceneNode *> WalkabilityMap::pathFinding(Ogre::SceneNode * sourceNode,Ogre::SceneNode * targetNode)
{

	std::vector<Ogre::SceneNode *> path;

	int sourceNearestNode;
	int targetNearestNode;
	int source;
	int target;
	Edge targetEdge;
	Edge sourceEdge;

	bool createdSource=false;
	bool createdTarget=false;


	//Ogre::LogManager::getSingleton().logMessage("PATHFINDING "+sourceNode->getName()+" to "+targetNode->getName());

	//add source and target nodes to graph
	if(!hasNode(sourceNode->getName()))
	{
		source=num_vertices(mGraph);
		sourceNearestNode=getNearestNode(sourceNode->getPosition());

		if(num_vertices(mGraph)==0 || mGraph[sourceNearestNode].mSceneNode->getPosition().distance(sourceNode->getPosition())>=sourceNode->getPosition().distance(targetNode->getPosition()))
		{
			//we do not need walkability map since we're closer to the target than nearest node
			path.push_back(sourceNode);
			path.push_back(targetNode);
			return path;
		}

		sourceEdge=add_edge(source,sourceNearestNode,mGraph).first;

		//set vertex properties
		mGraph[source].mSceneNode=sourceNode;

		//set edge properties
		boost::property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, mGraph);
		weightmap[sourceEdge]=mGraph[sourceNearestNode].mSceneNode->getPosition().distance(mGraph[source].mSceneNode->getPosition());

		createdSource=true;
	}
	else
	{
		source=getNodeNumber(sourceNode->getName());
	}

	if(!hasNode(targetNode->getName()))
	{
		target=num_vertices(mGraph);
		targetNearestNode=getNearestNode(targetNode->getPosition());

		targetEdge=add_edge(target,targetNearestNode,mGraph).first;

		//set vertex properties
		mGraph[target].mSceneNode=targetNode;

		//set edge properties
		boost::property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, mGraph);
		weightmap[targetEdge]=mGraph[targetNearestNode].mSceneNode->getPosition().distance(mGraph[target].mSceneNode->getPosition());

		createdTarget=true;
	}
	else
	{
		target=getNodeNumber(targetNode->getName());
	}

	std::vector<Graph::vertex_descriptor> p(num_vertices(mGraph));
	std::vector<double> d(num_vertices(mGraph));

	Vertex goal = vertex(target,mGraph);

	//TODO FIX THIS:!!
	cost costs[] = { 
		{0}, {0}, {0},
		{0}, {0}, {0}
	};

	try {

		astar_search
			(mGraph, source,
			MinDistanceAStarHeuristic<Graph,double,cost*>(costs,goal),
			predecessor_map(&p[0]).distance_map(&d[0]).visitor(MinDistanceAStarGoalVisitor<Vertex>(goal))
			);
	} 
	catch(FoundGoal fg) 
	{ 
		Vertex v;
		// found a path to the goal
		std::list<Vertex> shortest_path;
		for(v = goal;; v = p[v]) 
		{
		  shortest_path.push_front(v);
		  if(p[v] == v)
		  {
			break;
		  }
		}
		//Ogre::LogManager::getSingleton().logMessage(mGraph[source].mSceneNode->getName());
		path.push_back(mGraph[source].mSceneNode);

		std::list<Vertex>::iterator spi = shortest_path.begin();
		for(++spi; spi != shortest_path.end(); ++spi)
		{
			path.push_back(mGraph[*spi].mSceneNode);
			//Ogre::LogManager::getSingleton().logMessage(mGraph[*spi].mSceneNode->getName());
		}

		fg.info="";
		
		if(createdTarget)
		{
			clear_vertex(target,mGraph);
			remove_vertex(target,mGraph);
		}
		if(createdSource)
		{
			clear_vertex(source,mGraph);
			remove_vertex(source,mGraph);
		}

		return path;
  }

  Ogre::LogManager::getSingleton().logMessage("Path not found");

	if(createdTarget)
	{
		clear_vertex(target,mGraph);
		remove_vertex(target,mGraph);
	}
	if(createdSource)
	{
		clear_vertex(source,mGraph);
		remove_vertex(source,mGraph);
	}

	return path;
}

bool WalkabilityMap::hasNode(std::string nodeName)
{
	TNodeNumbersIterator it;
	it=mNodeNumbers.find(nodeName);

	return it!=mNodeNumbers.end();
}

void WalkabilityMap::setVisible(bool visible)
{
	unsigned int i;

	mVisible=visible;

	for(i=0;i<myLines.size();i++)
	{
		myLines[i]->setVisible(mVisible);
	}

	for(i=0;i<myNodes.size();i++)
	{
		myNodes[i]->setVisible(mVisible);
	}

}

TWalkabilityMapParameters::TWalkabilityMapParameters()
{

}

TWalkabilityMapParameters::~TWalkabilityMapParameters()
{

}


TWalkabilityMapNodeParameters::TWalkabilityMapNodeParameters()
{

}

TWalkabilityMapNodeParameters::~TWalkabilityMapNodeParameters()
{

}