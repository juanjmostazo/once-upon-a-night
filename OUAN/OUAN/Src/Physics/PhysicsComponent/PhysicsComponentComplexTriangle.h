#ifndef PhysicsComponentComplexTriangleH_H
#define PhysicsComponentComplexTriangleH_H

#include "PhysicsComponentComplex.h"
namespace OUAN
{
	// Complex elements which have physics but can NOT be moved, shape will be TriangleMesh
	class PhysicsComponentComplexTriangle: public PhysicsComponentComplex
	{
	public:
		PhysicsComponentComplexTriangle(const std::string& name="");
		~PhysicsComponentComplexTriangle();

		void setNxOgreTriangleGeometry(NxOgre::TriangleGeometry* pNxOgreTriangleGeometry);
		NxOgre::TriangleGeometry* getNxOgreTriangleGeometry();

	protected:
		NxOgre::TriangleGeometry* mNxOgreTriangleGeometry;
	};

	class TPhysicsComponentComplexTriangleParameters: public TPhysicsComponentComplexParameters
	{
	public:
		TPhysicsComponentComplexTriangleParameters();
		~TPhysicsComponentComplexTriangleParameters();
	};
}

#endif