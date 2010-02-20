#include "PhysicsComponentTerrain.h"
using namespace OUAN;

PhysicsComponentTerrain::PhysicsComponentTerrain(const std::string& name)
:PhysicsComponentNonMovable(name.empty()?COMPONENT_NAME_OGRE:name)
{
}

PhysicsComponentTerrain::~PhysicsComponentTerrain()
{
}

TPhysicsComponentTerrainParameters::TPhysicsComponentTerrainParameters() : TPhysicsComponentNonMovableParameters()
{
}

TPhysicsComponentTerrainParameters::~TPhysicsComponentTerrainParameters()
{
}