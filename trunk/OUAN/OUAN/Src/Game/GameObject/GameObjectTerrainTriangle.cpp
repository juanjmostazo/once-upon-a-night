#include "GameObjectTerrainTriangle.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectTerrainTriangle::GameObjectTerrainTriangle(const std::string& name)
:GameObject(name)
{

}

GameObjectTerrainTriangle::~GameObjectTerrainTriangle()
{

}

void GameObjectTerrainTriangle::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectTerrainTriangle::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

void GameObjectTerrainTriangle::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares)
{
	mRenderComponentEntityNightmares=pRenderComponentEntityNightmares;
}

RenderComponentEntityPtr GameObjectTerrainTriangle::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectTerrainTriangle::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectTerrainTriangle::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectTerrainTriangle::setPhysicsComponentComplexTriangle(PhysicsComponentComplexTrianglePtr pPhysicsComponentComplexTriangle)
{
	mPhysicsComponentComplexTriangle=pPhysicsComponentComplexTriangle;
	mPhysicsComponentComplexTriangle->create();
}

PhysicsComponentComplexTrianglePtr GameObjectTerrainTriangle::getPhysicsComponentComplexTriangle()
{
	return mPhysicsComponentComplexTriangle;
}

void GameObjectTerrainTriangle::changeWorld(int world)
{
	switch(world)
	{
	case DREAMS:
		mRenderComponentEntityDreams->setVisible(true);
		mRenderComponentEntityNightmares->setVisible(false);
		break;
	case NIGHTMARES:
		mRenderComponentEntityDreams->setVisible(false);
		mRenderComponentEntityNightmares->setVisible(true);
		break;
	default:break;
	}
}
TGameObjectTerrainTriangleParameters::TGameObjectTerrainTriangleParameters() : TGameObjectParameters()
{

}

TGameObjectTerrainTriangleParameters::~TGameObjectTerrainTriangleParameters()
{

}
