#ifndef PhysicsComponentVolumeConvexH_H
#define PhysicsComponentVolumeConvexH_H

#include "PhysicsComponentVolume.h"
namespace OUAN
{
	// Physics volumes having the shape of a Convex
	class PhysicsComponentVolumeConvex: public PhysicsComponentVolume
	{
	public:
		PhysicsComponentVolumeConvex(const std::string& type="");
		~PhysicsComponentVolumeConvex();

		virtual void create();
		virtual void destroy();

		NxOgre::Vec2 getNxOgreSize();
		void setNxOgreSize(NxOgre::Vec2 pNxOgreSize);

		NxOgre::Mesh* getNxOgreConvexMesh();
		void setNxOgreConvexMesh(NxOgre::Mesh* pNxOgreConvexMesh);

		//void setQueryFlags(QueryFlags queryFlags);

		void setPosition(Vector3 position);
		void setOrientation(Quaternion orientation);

	protected:
		NxOgre::Mesh* mConvexMesh;

	};

	class TPhysicsComponentVolumeConvexParameters: public TPhysicsComponentVolumeParameters
	{
	public:
		TPhysicsComponentVolumeConvexParameters();
		~TPhysicsComponentVolumeConvexParameters();

		// Name of the physics nxs file related to the given object mesh
		std::string nxsFile;
	};
}

#endif