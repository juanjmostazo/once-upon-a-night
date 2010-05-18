#include "GameObjectViewport.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectViewport::GameObjectViewport(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_VIEWPORT)
{

}

GameObjectViewport::~GameObjectViewport()
{

}

void GameObjectViewport::setRenderComponentViewport(RenderComponentViewportPtr pRenderComponentViewport)
{
	mRenderComponentViewport=pRenderComponentViewport;
}

RenderComponentViewportPtr GameObjectViewport::getRenderComponentViewport() const
{
	return mRenderComponentViewport;
}

void GameObjectViewport::changeWorldFinished(int world)
{
	if (!isEnabled()) return;

	switch(world)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectViewport::changeWorldStarted(int world)
{
	if (!isEnabled()) return;

	switch(world)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectViewport::changeToWorld(int world, double perc)
{
	if (!isEnabled()) return;

	switch(world)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectViewport::setEffect(std::string effectName, bool activated)
{
	mRenderComponentViewport->setEffect(effectName,activated);
}

//-------------------------------------------------------------------------------------------
TGameObjectViewportParameters::TGameObjectViewportParameters() : TGameObjectParameters()
{

}

TGameObjectViewportParameters::~TGameObjectViewportParameters()
{

}