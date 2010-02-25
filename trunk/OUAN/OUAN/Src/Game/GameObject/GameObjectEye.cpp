#include "GameObjectEye.h"

using namespace OUAN;

GameObjectEye::GameObjectEye(const std::string& name)
:GameObject(name)
{

}

GameObjectEye::~GameObjectEye()
{

}

RenderComponentEntityPtr GameObjectEye::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectEye::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectEye::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectEye::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectEye::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectEye::getPhysicsComponentCharacter()
{
	return mPhysicsComponentCharacter;
}

TGameObjectEyeParameters::TGameObjectEyeParameters() : TGameObjectParameters()
{
}

TGameObjectEyeParameters::~TGameObjectEyeParameters()
{
}