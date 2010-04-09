#include "WalkabilityMap.h"

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
	TNodeNumbersIterator it;

	for(it = mNodeNumbers.begin(); it != mNodeNumbers.end(); it++) 
	{
		if(it->second == nodeNumber)
		{
			return it->first;
		}
	}

	Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Walkability Map Node "+
		Ogre::StringConverter::toString(nodeNumber)+" does not exist");
	return "";
}

void WalkabilityMap::init(TWalkabilityMapParameters tWalkabilityMapParameters,Ogre::SceneManager * pSceneManager)
{
		unsigned int i,j;

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
		

		//add graph edges and create graph nodes
		for(i=0;i<tWalkabilityMapParameters.walkabilityNodes.size();i++)
		{
			pSceneNode=pSceneManager->getRootSceneNode()->createChildSceneNode(tWalkabilityMapParameters.walkabilityNodes[i].nodeName);
			pSceneNode->setPosition(tWalkabilityMapParameters.walkabilityNodes[i].position);
			pSceneNode->setOrientation(tWalkabilityMapParameters.walkabilityNodes[i].orientation);

			//add_vertex(getNodeNumber(tWalkabilityMapParameters.walkabilityNodes[i].nodeName),mGraph);

			mGraph[getNodeNumber(tWalkabilityMapParameters.walkabilityNodes[i].nodeName)].name=tWalkabilityMapParameters.walkabilityNodes[i].nodeName;

			for(j=0;j<tWalkabilityMapParameters.walkabilityNodes[i].neighbors.size();j++)
			{
				Ogre::LogManager::getSingleton().logMessage("Adding edge "+tWalkabilityMapParameters.walkabilityNodes[i].nodeName+"-"
					+tWalkabilityMapParameters.walkabilityNodes[i].neighbors[j]);

				add_edge(getNodeNumber(tWalkabilityMapParameters.walkabilityNodes[i].nodeName.c_str()),
					getNodeNumber(tWalkabilityMapParameters.walkabilityNodes[i].neighbors[j].c_str()),
					mGraph);
			}
		}


		Graph::vertex_descriptor v1,v2;
		Ogre::SceneNode * pSceneNode1;
		Ogre::SceneNode * pSceneNode2;
		Graph::edge_descriptor e = *edges(mGraph).first;

		boost::graph_traits<Graph>::edge_iterator eit,eend;
		for (tie(eit, eend) = edges(mGraph); eit != eend; ++eit) 
		{
			Graph::edge_descriptor e = *eit;

			v1=source(e, mGraph);
			v2=target(e, mGraph);
			pSceneNode1=pSceneManager->getSceneNode(mGraph[v1].name);
			pSceneNode2=pSceneManager->getSceneNode(mGraph[v2].name);

			mGraph[e].distance=pSceneNode1->getPosition().distance(pSceneNode2->getPosition());

		}

		Ogre::LogManager::getSingleton().logMessage("PRINT GRAPH VERTICES");
		boost::graph_traits<Graph>::vertex_iterator vit,vend;
		for (tie(vit, vend) = vertices(mGraph); vit != vend; ++vit) 
		{
			Ogre::LogManager::getSingleton().logMessage(mGraph[*vit].name);
		}

		Ogre::LogManager::getSingleton().logMessage("PRINT GRAPH EDGES");
		for (tie(eit, eend) = edges(mGraph); eit != eend; ++eit) 
		{
			v1=source(*eit, mGraph);
			v2=target(*eit, mGraph);

			Ogre::LogManager::getSingleton().logMessage("Edge "+mGraph[v1].name+"-"+mGraph[v2].name+
				" distance:"+Ogre::StringConverter::toString(Ogre::Real(mGraph[*eit].distance)));
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