#ifndef WalkabilityMapH_H
#define WalkabilityMapH_H

#include "../../OUAN.h"
//#include <iostream> // std::cout
#include <utility> // std::pair
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/graph_utility.hpp>

using namespace boost;

namespace OUAN
{
	class WalkabilityMap
	{
	private:

		//boost Graph definitions
		typedef adjacency_list<> Graph;

		typedef graph_traits<Graph> GraphTraits;

		typedef GraphTraits::vertex_descriptor Vertex;

		typedef std::pair<int, int> Edge;

		//graph used to represent the walkability map
		Graph mGraph;

		std::map<std::string,int> mNodeNumbers;
		typedef std::map<std::string,int>::iterator TNodeNumbersIterator;

		int getNodeNumber(std::string nodeName);
		std::string getNodeName(int nodeNumber);

	public:

		WalkabilityMap();
		~WalkabilityMap();

		void init(TWalkabilityMapParameters tWalkabilityMapParameters);

	};

	class TWalkabilityMapParameters
	{
	public:
		TWalkabilityMapParameters();
		~TWalkabilityMapParameters();

		String name;
		std::vector<TWalkabilityMapNodeParameters> walkabilityNodes;
	};

	class TWalkabilityMapNodeParameters
	{
	public:
		TWalkabilityMapNodeParameters();
		~TWalkabilityMapNodeParameters();

		String nodeName;
		std::vector<String> neighbors;
	};


}

#endif