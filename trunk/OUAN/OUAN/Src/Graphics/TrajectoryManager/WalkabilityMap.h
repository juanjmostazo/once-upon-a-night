#ifndef WalkabilityMapH_H
#define WalkabilityMapH_H

#include "../../OUAN.h"
//#include <iostream> // std::cout
//#include <utility> // std::pair
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/astar_search.hpp>
//#include <boost/graph/topological_sort.hpp>
//#include <boost/graph/graph_utility.hpp>

using namespace boost;

namespace OUAN
{
	class WalkabilityMap
	{
	public:

		WalkabilityMap();
		~WalkabilityMap();

		void init(TWalkabilityMapParameters tWalkabilityMapParameters,Ogre::SceneManager * pSceneManager,Ogre::SceneNode * pDebugObjects);

		std::vector<Ogre::SceneNode *> pathFinding(Ogre::SceneNode * sourceNode,Ogre::SceneNode * targetNode);

		bool hasNode(std::string nodeName);

		void setVisible(bool visible);

	private:

		struct VertexProperties
		{
			Ogre::SceneNode * mSceneNode;
		};

		struct EdgeProperties
		{
			double edge_weight_t;
		};

		struct cost
		{
			double c;
		};

		//boost Graph definitions
		typedef adjacency_list<    
			boost::listS, boost::vecS, boost::undirectedS,
			VertexProperties,
			property<edge_weight_t, float>
		> Graph;

		typedef Graph::vertex_descriptor Vertex;
		typedef Graph::edge_descriptor Edge;
		//typedef graph_traits<Graph> GraphTraits;
		//typedef GraphTraits::vertex_descriptor Vertex;
		//typedef std::pair<int, int> Edge;

		//Stuff for A* pathfinding

			//A* heuristic function

			template <class Graph, class CostType, class LocMap>
			class MinDistanceAStarHeuristic : public astar_heuristic<Graph, CostType>
			{
				public:
					typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
					MinDistanceAStarHeuristic(LocMap l, Vertex goal)
					: m_location(l), m_goal(goal) {}
					CostType operator()(Vertex u)
					{	//TODO FIX THIS:!!
						CostType dx = m_location[m_goal].c;
						return 0;
					}
				private:
					LocMap m_location;
					Vertex m_goal;
			};

			struct FoundGoal 
			{
				std::string info;
			}; // exception for termination

			//A* goal visitor function
			template <class Vertex>
			class MinDistanceAStarGoalVisitor : public boost::default_astar_visitor
			{
				public:
				  MinDistanceAStarGoalVisitor(Vertex goal) : m_goal(goal) {}
				  template <class Graph>
				  void examine_vertex(Vertex u, Graph& g) 
				  {
					if(u == m_goal)
					  throw FoundGoal();
				  }
				private:
				  Vertex m_goal;
			};


		//graph used to represent the walkability map
		Graph mGraph;

		std::string mName;

		bool mVisible;

		Ogre::SceneNode * mDebugObjects;

		std::map<std::string,int> mNodeNumbers;
		typedef std::map<std::string,int>::iterator TNodeNumbersIterator;

		int getNodeNumber(std::string nodeName);
		std::string getNodeName(int nodeNumber);

		int getNearestNode(Ogre::Vector3 position);



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
		Vector3 position;
		Quaternion orientation;
		std::vector<String> neighbors;
	};


}

#endif