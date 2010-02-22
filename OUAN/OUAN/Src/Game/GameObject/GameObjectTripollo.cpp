#include "GameObjectTripollo.h"

using namespace OUAN;

GameObjectTripollo::GameObjectTripollo(const std::string& name, const std::string& id)
:GameObject(name,id)
{

}

GameObjectTripollo::~GameObjectTripollo()
{

}

void GameObjectTripollo::setRenderComponentPositional(RenderComponentPositionalPtr pPositionalEntity)
{
	mRenderComponentPositional=pPositionalEntity;
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

TGameObjectTripolloParameters::TGameObjectTripolloParameters() : TGameObjectParameters()
{
}
TGameObjectTripolloParameters::~TGameObjectTripolloParameters()
{
}