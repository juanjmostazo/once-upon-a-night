#ifndef PhysicsComponentVolumeTriangleH_H
#define PhysicsComponentVolumeTriangleH_H

#include "PhysicsComponentVolume.h"
namespace OUAN
{
	// Physics volumes having the shape of a Triangle
	class PhysicsComponentVolumeTriangle: public PhysicsComponentVolume
	{
	public:
		PhysicsComponentVolumeTriangle(const std::string& type="");
		~PhysicsComponentVolumeTriangle();

		virtual void create();
		virtual void destroy();

		NxOgre::Vec2 getNxOgreSize();
		void setNxOgreSize(NxOgre::Vec2 pNxOgreSize);

		NxOgre::TriangleGeometry* getNxOgreTriangleGeometry();
		void setNxOgreTriangleGeometry(NxOgre::TriangleGeometry* pNxOgreTriangleMesh);

		//void setQueryFlags(QueryFlags queryFlags);

		void setPosition(Vector3 position);
		void setOrientation(Quaternion orientation);

	protected:
		NxOgre::TriangleGeometry* mTriangleMesh;

	};

	class TPhysicsComponentVolumeTriangleParameters: public TPhysicsComponentVolumeParameters
	{
	public:
		TPhysicsComponentVolumeTriangleParameters();
		~TPhysicsComponentVolumeTriangleParameters();

		// Name of the physics nxs file related to the given object mesh
		std::string nxsFile;
	};
}

#endif