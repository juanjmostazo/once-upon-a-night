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

void WalkabilityMap::init(TWalkabilityMapParameters tWalkabilityMapParameters)
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

		//add graph edges
		for(i=0;i<tWalkabilityMapParameters.walkabilityNodes.size();i++)
		{
			for(j=0;j<tWalkabilityMapParameters.walkabilityNodes[i].neighbors.size();j++)
			{
				add_edge(getNodeNumber(tWalkabilityMapParameters.walkabilityNodes[i].nodeName.c_str()),
					getNodeNumber(tWalkabilityMapParameters.walkabilityNodes[i].neighbors[j].c_str()),
					mGraph);
				Ogre::LogManager::getSingleton().logMessage("Adding edge "+tWalkabilityMapParameters.walkabilityNodes[i].nodeName+" "
					+tWalkabilityMapParameters.walkabilityNodes[i].neighbors[j]);
			}
		}

		graph_traits < adjacency_list <> >::vertex_iterator it, end;
		graph_traits < adjacency_list <> >::adjacency_iterator ai, a_end;
		property_map < adjacency_list <>, vertex_index_t >::type
		index_map = get(vertex_index, mGraph);

		Ogre::LogManager::getSingleton().logMessage("PRINT GRAPH");

		for (tie(it, end) = vertices(mGraph); it != end; ++it) {
			Ogre::LogManager::getSingleton().logMessage( "NODE "+getNodeName(get(index_map, *it)));
			tie(ai, a_end) = adjacent_vertices(*it, mGraph);
			if (ai == a_end)
				Ogre::LogManager::getSingleton().logMessage( " has no children");
			else
				Ogre::LogManager::getSingleton().logMessage( " adjacent with: ");
			for (; ai != a_end; ++ai) {
			  Ogre::LogManager::getSingleton().logMessage( getNodeName(get(index_map, *ai)));
			}
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