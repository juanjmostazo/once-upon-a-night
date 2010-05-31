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

		//mRenderComponentViewport->setBloomAmount(0.0f);
		setEffect(Application::getInstance()->getRenderSubsystem()->BLOOM, Application::getInstance()->getRenderSubsystem()->BLOOM_ACTIVATED_ALWAYS_DREAMS);
		setEffect(Application::getInstance()->getRenderSubsystem()->HDR, Application::getInstance()->getRenderSubsystem()->HDR_ACTIVATED_ALWAYS_DREAMS);
		setEffect(Application::getInstance()->getRenderSubsystem()->RADIAL_BLUR, Application::getInstance()->getRenderSubsystem()->RADIAL_BLUR_ACTIVATED_ALWAYS_DREAMS);
		setEffect(Application::getInstance()->getRenderSubsystem()->MOTION_BLUR, Application::getInstance()->getRenderSubsystem()->MOTION_BLUR_ACTIVATED_ALWAYS_DREAMS);


		break;
	case NIGHTMARES:

		//mRenderComponentViewport->setBloomAmount(1.0f);
		setEffect(Application::getInstance()->getRenderSubsystem()->BLOOM, Application::getInstance()->getRenderSubsystem()->BLOOM_ACTIVATED_ALWAYS_NIGHTMARES);
		setEffect(Application::getInstance()->getRenderSubsystem()->HDR, Application::getInstance()->getRenderSubsystem()->HDR_ACTIVATED_ALWAYS_NIGHTMARES);
		setEffect(Application::getInstance()->getRenderSubsystem()->RADIAL_BLUR, Application::getInstance()->getRenderSubsystem()->RADIAL_BLUR_ACTIVATED_ALWAYS_NIGHTMARES);
		setEffect(Application::getInstance()->getRenderSubsystem()->MOTION_BLUR, Application::getInstance()->getRenderSubsystem()->MOTION_BLUR_ACTIVATED_ALWAYS_NIGHTMARES);

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
		//mRenderComponentViewport->setBloomAmount(1-perc);
		//setBloomEffectIfPossible(DREAMS,false);
		//setBloomEffectIfPossible(DREAMS,true);
		break;
	case NIGHTMARES:
		//mRenderComponentViewport->setBloomAmount(perc);
		//setBloomEffectIfPossible(NIGHTMARES,false);
		//setBloomEffectIfPossible(NIGHTMARES,true);
		break;
	default:
		break;
	}
}

void GameObjectViewport::setEffect(std::string effectName, bool activated)
{
	mRenderComponentViewport->setEffect(effectName,activated);
}

void GameObjectViewport::setBloomEffectIfPossible(int world, bool enabled)
{
	if ((world == DREAMS && 
		 !Application::getInstance()->getRenderSubsystem()->BLOOM_ACTIVATED_ALWAYS_DREAMS) ||	
		(world == NIGHTMARES && 
		 !Application::getInstance()->getRenderSubsystem()->BLOOM_ACTIVATED_ALWAYS_NIGHTMARES))
	{
		mGameWorldManager->getGameObjectViewport()->setEffect(
			Application::getInstance()->getRenderSubsystem()->BLOOM, 
			enabled);
	}
}

void GameObjectViewport::setHDREffectIfPossible(int world, bool enabled)
{
	if ((world == DREAMS && 
		 !Application::getInstance()->getRenderSubsystem()->HDR_ACTIVATED_ALWAYS_DREAMS) ||	
		(world == NIGHTMARES && 
		 !Application::getInstance()->getRenderSubsystem()->HDR_ACTIVATED_ALWAYS_NIGHTMARES))
	{
		mGameWorldManager->getGameObjectViewport()->setEffect(
			Application::getInstance()->getRenderSubsystem()->HDR, 
			enabled);
	}
}

void GameObjectViewport::setRadialBlurEffectIfPossible(int world, bool enabled)
{
	if ((world == DREAMS && 
		 !Application::getInstance()->getRenderSubsystem()->RADIAL_BLUR_ACTIVATED_ALWAYS_DREAMS) ||	
		(world == NIGHTMARES && 
		 !Application::getInstance()->getRenderSubsystem()->RADIAL_BLUR_ACTIVATED_ALWAYS_NIGHTMARES))
	{
		mGameWorldManager->getGameObjectViewport()->setEffect(
			Application::getInstance()->getRenderSubsystem()->RADIAL_BLUR, 
			enabled);
	}
}

void GameObjectViewport::setMotionBlurEffectIfPossible(int world, bool enabled)
{
	if ((world == DREAMS && 
		 !Application::getInstance()->getRenderSubsystem()->MOTION_BLUR_ACTIVATED_ALWAYS_DREAMS) ||	
		(world == NIGHTMARES && 
		 !Application::getInstance()->getRenderSubsystem()->MOTION_BLUR_ACTIVATED_ALWAYS_NIGHTMARES))
	{
		mGameWorldManager->getGameObjectViewport()->setEffect(
			Application::getInstance()->getRenderSubsystem()->MOTION_BLUR, 
			enabled);
	}
}

//-------------------------------------------------------------------------------------------
TGameObjectViewportParameters::TGameObjectViewportParameters() : TGameObjectParameters()
{

}

TGameObjectViewportParameters::~TGameObjectViewportParameters()
{

}