#include "WalkabilityMap.h"
#include "../Line3D/Line3D.h"

using namespace OUAN;
using namespace boost;

WalkabilityMap::WalkabilityMap()
{

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

		mDebugObjects->createChildSceneNode("walkability#"+tWalkabilityMapParameters.name);

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
		//add graph edges and create graph nodes
		for(i=0;i<tWalkabilityMapParameters.walkabilityNodes.size();i++)
		{
			pSceneNode=pSceneManager->getRootSceneNode()->createChildSceneNode(tWalkabilityMapParameters.walkabilityNodes[i].nodeName);
			pSceneNode->setPosition(tWalkabilityMapParameters.walkabilityNodes[i].position);
			pSceneNode->setOrientation(tWalkabilityMapParameters.walkabilityNodes[i].orientation);

			mGraph[getNodeNumber(tWalkabilityMapParameters.walkabilityNodes[i].nodeName)].mSceneNode=pSceneNode;

			for(j=0;j<tWalkabilityMapParameters.walkabilityNodes[i].neighbors.size();j++)
			{
				/*Ogre::LogManager::getSingleton().logMessage("Adding edge "+tWalkabilityMapParameters.walkabilityNodes[i].nodeName+"-"
					+tWalkabilityMapParameters.walkabilityNodes[i].neighbors[j]);*/

				add_edge(getNodeNumber(tWalkabilityMapParameters.walkabilityNodes[i].nodeName.c_str()),
					getNodeNumber(tWalkabilityMapParameters.walkabilityNodes[i].neighbors[j].c_str()),
					mGraph);
			}

			//create graphics debug objects
			std::string debugName="walkability#"+tWalkabilityMapParameters.name+"#"+tWalkabilityMapParameters.walkabilityNodes[i].nodeName;
			pEntityDebugNode=mDebugObjects->createChildSceneNode(debugName);
			pEntityDebugNode->setVisible(false);
			pEntityDebugNode->setPosition(pSceneNode->getPosition());
			pEntity=pSceneManager->createEntity(debugName,"node.mesh");
			pEntity->setMaterialName("red");
			pEntity->setVisible(false);
			pEntityDebugNode->attachObject(pEntity);

		}

		//set graph edges properties
		Graph::vertex_descriptor v1,v2;
		Ogre::SceneNode * pSceneNode1;
		Ogre::SceneNode * pSceneNode2;
		Graph::edge_descriptor e = *edges(mGraph).first;

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
			myLine->setVisible(false);
			mDebugObjects->attachObject(myLine);
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

	Ogre::LogManager::getSingleton().logMessage("PATHFINDING "+sourceNode->getName()+" to "+targetNode->getName());

	//add source and target nodes to graph
	source=num_vertices(mGraph);
	target=num_vertices(mGraph)+1;

	//add edge from source to source's nearest node and add edge from target to target's nearest node
	sourceNearestNode=getNearestNode(sourceNode->getPosition());
	targetNearestNode=getNearestNode(targetNode->getPosition());
	sourceEdge=add_edge(source,sourceNearestNode,mGraph).first;
	targetEdge=add_edge(target,targetNearestNode,mGraph).first;

	//set vertex properties
	mGraph[source].mSceneNode=sourceNode;
	mGraph[target].mSceneNode=targetNode;

	//set edge properties
	boost::property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, mGraph);
	weightmap[sourceEdge]=mGraph[sourceNearestNode].mSceneNode->getPosition().distance(mGraph[source].mSceneNode->getPosition());
	weightmap[targetEdge]=mGraph[targetNearestNode].mSceneNode->getPosition().distance(mGraph[target].mSceneNode->getPosition());

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
		Ogre::LogManager::getSingleton().logMessage(mGraph[source].mSceneNode->getName());
		path.push_back(mGraph[source].mSceneNode);

		std::list<Vertex>::iterator spi = shortest_path.begin();
		for(++spi; spi != shortest_path.end(); ++spi)
		{
			path.push_back(mGraph[*spi].mSceneNode);
			Ogre::LogManager::getSingleton().logMessage(mGraph[*spi].mSceneNode->getName());
		}

		fg.info="";
		
		clear_vertex(target,mGraph);
		remove_vertex(target,mGraph);
		clear_vertex(source,mGraph);
		remove_vertex(source,mGraph);

		return path;
  }

  Ogre::LogManager::getSingleton().logMessage("FAIL");

	clear_vertex(target,mGraph);
	remove_vertex(target,mGraph);
	clear_vertex(source,mGraph);
	remove_vertex(source,mGraph);

	return path;
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