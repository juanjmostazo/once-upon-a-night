#include "GameObjectViewport.h"
#include "../GameWorldManager.h"
#include "../../Application.h"
#include "../../Graphics/RenderSubsystem.h"

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

void GameObjectViewport::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:

		if (Application::getInstance()->getRenderSubsystem()->BLOOM_ACTIVATED_ALWAYS_DREAMS)
		{
			setEffect(Application::getInstance()->getRenderSubsystem()->BLOOM, true);
		}
		else
		{
			setEffect(Application::getInstance()->getRenderSubsystem()->BLOOM, false);
		}

		if (Application::getInstance()->getRenderSubsystem()->HDR_ACTIVATED_ALWAYS_DREAMS)
		{
			setEffect(Application::getInstance()->getRenderSubsystem()->HDR, true);
		}
		else
		{
			setEffect(Application::getInstance()->getRenderSubsystem()->HDR, false);
		}

		if (Application::getInstance()->getRenderSubsystem()->RADIAL_BLUR_ACTIVATED_ALWAYS_DREAMS)
		{
			setEffect(Application::getInstance()->getRenderSubsystem()->RADIAL_BLUR, true);
		}
		else
		{
			setEffect(Application::getInstance()->getRenderSubsystem()->RADIAL_BLUR, false);
		}

		break;
	case NIGHTMARES:

		if (Application::getInstance()->getRenderSubsystem()->BLOOM_ACTIVATED_ALWAYS_NIGHTMARES)
		{
			setEffect(Application::getInstance()->getRenderSubsystem()->BLOOM, true);
		}
		else
		{
			setEffect(Application::getInstance()->getRenderSubsystem()->BLOOM, false);
		}

		if (Application::getInstance()->getRenderSubsystem()->HDR_ACTIVATED_ALWAYS_NIGHTMARES)
		{
			setEffect(Application::getInstance()->getRenderSubsystem()->HDR, true);
		}
		else
		{
			setEffect(Application::getInstance()->getRenderSubsystem()->HDR, false);
		}

		if (Application::getInstance()->getRenderSubsystem()->RADIAL_BLUR_ACTIVATED_ALWAYS_NIGHTMARES)
		{
			setEffect(Application::getInstance()->getRenderSubsystem()->RADIAL_BLUR, true);
		}
		else
		{
			setEffect(Application::getInstance()->getRenderSubsystem()->RADIAL_BLUR, false);
		}

		break;
	default:
		break;
	}
}

void GameObjectViewport::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectViewport::changeToWorld(int newWorld, double perc)
{
	if (!isEnabled()) return;

	switch(newWorld)
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