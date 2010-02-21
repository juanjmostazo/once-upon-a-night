#include "PhysicsComponentSimpleCube.h"
using namespace OUAN;

PhysicsComponentSimpleCube::PhysicsComponentSimpleCube(const std::string& name)
:PhysicsComponentSimple(COMPONENT_NAME_PHYSICS_SIMPLE_CUBE)
{
}

PhysicsComponentSimpleCube::~PhysicsComponentSimpleCube()
{
}

TPhysicsComponentSimpleCubeParameters::TPhysicsComponentSimpleCubeParameters() : TPhysicsComponentSimpleParameters()
{
}

TPhysicsComponentSimpleCubeParameters::~TPhysicsComponentSimpleCubeParameters()
{
}