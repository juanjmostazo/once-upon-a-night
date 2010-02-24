#ifndef PhysicsComponentComplexNonMovableH_H
#define PhysicsComponentComplexNonMovableH_H

#include "PhysicsComponentComplex.h"
namespace OUAN
{
	// Complex elements which have physics but can NOT be moved, shape will be TriangleMesh
	// Examples: Terrain, rocks, walls, etc.
	class PhysicsComponentComplexNonMovable: public PhysicsComponentComplex
	{
	public:
		PhysicsComponentComplexNonMovable(const std::string& name="");
		~PhysicsComponentComplexNonMovable();

		void setNxOgreTriangleGeometry(NxOgre::TriangleGeometry* pNxOgreTriangleGeometry);
		NxOgre::TriangleGeometry* getNxOgreTriangleGeometry();

	protected:
		NxOgre::TriangleGeometry* mNxOgreTriangleGeometry;
	};

	class TPhysicsComponentComplexNonMovableParameters: public TPhysicsComponentComplexParameters
	{
	public:
		TPhysicsComponentComplexNonMovableParameters();
		~TPhysicsComponentComplexNonMovableParameters();
	};
}

#endif