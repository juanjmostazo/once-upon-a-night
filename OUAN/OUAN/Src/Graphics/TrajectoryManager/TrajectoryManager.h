#ifndef TrajectoryManagerH_H
#define TrajectoryManagerH_H

#include "../../OUAN.h"

//#include <iostream> // std::cout
//#include <utility> // std::pair
//#include <boost/graph/graph_traits.hpp>
//#include <boost/graph/adjacency_list.hpp>
//#include <boost/graph/topological_sort.hpp>

namespace OUAN
{
	class TrajectoryManager
	{
	private:
		std::map<std::string,Trajectory *> trajectoryContainer;
		typedef std::map<std::string,Trajectory *>::iterator TTrajectoryIterator;

		std::map<std::string,WalkabilityMap *> walkabilityMapContainer;
		typedef std::map<std::string,WalkabilityMap *>::iterator TWalkabilityMapIterator;

		Ogre::SceneManager * mSceneManager;

	 // using namespace boost;
	 // typedef adjacency_list<vecS, vecS, bidirectionalS, 
		//  property<vertex_color_t, default_color_type>
		//> Graph;
	 // Graph g(used_by, used_by + sizeof(used_by) / sizeof(Edge), N);
	 // typedef graph_traits<Graph>::vertex_descriptor Vertex;

	public:

		TrajectoryManager();
		~TrajectoryManager();
		
		void init(RenderSubsystemPtr pRenderSubsystem);
		void clear();

		void createTrajectory(TTrajectoryParameters tTrajectoryParameters);
		void createWalkabilityMap(TWalkabilityMapParameters tWalkabilityMapParameters);

		Trajectory * getTrajectoryInstance(std::string name);

		bool hasTrajectory(std::string name);
		bool hasWalkabilityMap(std::string name);
	};
}

#endif

