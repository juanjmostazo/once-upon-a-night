#include "GameObjectOny.h"

using namespace OUAN;

GameObjectOny::GameObjectOny(const std::string& name, const std::string& id)
:GameObject(name,id)
{

}

GameObjectOny::~GameObjectOny()
{

}
void GameObjectOny::setRenderComponentPositional(RenderComponentPositionalPtr pPositionalEntity)
{
	mRenderComponentPositional=pPositionalEntity;
}

RenderComponentPositionalPtr GameObjectOny::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectOny::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}


RenderComponentEntityPtr GameObjectOny::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

TGameObjectOnyParameters::TGameObjectOnyParameters() : TGameObjectParameters()
{
}
TGameObjectOnyParameters::~TGameObjectOnyParameters()
{
}