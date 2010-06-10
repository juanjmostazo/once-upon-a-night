#include "OUAN_Precompiled.h"

#include "PhysicsComponentCharacterOny.h"
#include "../../RayCasting/RayCasting.h"

using namespace OUAN;

PhysicsComponentCharacterOny::PhysicsComponentCharacterOny(const std::string& type)
:PhysicsComponentCharacter(type)
{
	mPointRenderable=NULL;
	reset();
}

PhysicsComponentCharacterOny::~PhysicsComponentCharacterOny()
{
	mPointRenderable=NULL;//NxOgre will handle the destruction of these objects.
}

TPhysicsComponentCharacterOnyParameters::TPhysicsComponentCharacterOnyParameters() : TPhysicsComponentCharacterParameters()
{

}

TPhysicsComponentCharacterOnyParameters::~TPhysicsComponentCharacterOnyParameters()
{

}