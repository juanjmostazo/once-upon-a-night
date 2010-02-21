#include "PhysicsComponentSimpleCube.h"
using namespace OUAN;

PhysicsComponentSimpleCube::PhysicsComponentSimpleCube(const std::string& name)
:PhysicsComponentSimple(name.empty()?COMPONENT_NAME_OGRE:name)
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