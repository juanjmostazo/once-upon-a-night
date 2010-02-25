#include "GameObjectTripollo.h"

using namespace OUAN;

GameObjectTripollo::GameObjectTripollo(const std::string& name)
:GameObject(name)
{

}

GameObjectTripollo::~GameObjectTripollo()
{

}

void GameObjectTripollo::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectTripollo::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectTripollo::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}


RenderComponentEntityPtr GameObjectTripollo::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectTripollo::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectTripollo::getPhysicsComponentCharacter()
{
	return mPhysicsComponentCharacter;
}

TGameObjectTripolloParameters::TGameObjectTripolloParameters() : TGameObjectParameters()
{
}

TGameObjectTripolloParameters::~TGameObjectTripolloParameters()
{
}