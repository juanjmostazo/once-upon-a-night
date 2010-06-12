#include "OUAN_Precompiled.h"

#include "HUDInGame.h"
#include "../../Event/Event.h"
#include "../../Event/EventManager.h"
using namespace OUAN;

HUDInGame::HUDInGame()
:HUDBase()
{
	mSelectedModeChanged=false;
}

HUDInGame::~HUDInGame()
{
	destroy();
}

void HUDInGame::init(int healthPoints, int numLives, int world)
{
	HUDBase::init(OVERLAY_INGAME_HUD);
	mHealthMaterial= Ogre::MaterialManager::getSingletonPtr()->getByName(MATERIAL_HEALTH);
	mRouletteMaterial=Ogre::MaterialManager::getSingletonPtr()->getByName(MATERIAL_ROULETTE);		

	mLives=Ogre::OverlayManager::getSingleton().getOverlayElement(OVERLAY_INGAME_HUD_LIVES_TEXT);

	mChangeWorldElapsedTime=0;
	mIsChangingWorld=false;

	initRouletteData();
	mCurrentRouletteState=ROULETTE_STATE_0;
	updateRouletteHUD();
	initHealthHud(healthPoints,numLives);

	if (world==DREAMS)
	{		
		hideElement(PANEL_ROULETTE);
		//showElement(PANEL_PILLOW_ROULE
	}
	else
	{
		showElement(PANEL_ROULETTE);
		//showElement(PANEL_PILLOW_ROULE
	}
}

void HUDInGame::destroy()
{
	hide();
	mRouletteData.clear();
	HUDBase::destroy();
}

void HUDInGame::initRouletteData()
{
	mRouletteData.clear();
	mRouletteData[ROULETTE_STATE_0].textureName=TEX_ROULETTE_COLOUR_RED;
	mRouletteData[ROULETTE_STATE_0].isAnimated=false;
	mRouletteData[ROULETTE_STATE_1].textureName=TEX_ROULETTE_COLOUR_BLUE;
	mRouletteData[ROULETTE_STATE_1].isAnimated=false;
	mRouletteData[ROULETTE_STATE_2].textureName=TEX_ROULETTE_COLOUR_GREEN;
	mRouletteData[ROULETTE_STATE_2].isAnimated=false;
	mRouletteData[ROULETTE_TRANSITION_12].textureName=TEX_ROULETTE_TRANSITION_BG;
	mRouletteData[ROULETTE_TRANSITION_12].isAnimated=true;
	mRouletteData[ROULETTE_TRANSITION_12].numFrames=TRANSITION_NFRAMES;
	mRouletteData[ROULETTE_TRANSITION_12].duration=TRANSITION_DURATION;
	mRouletteData[ROULETTE_TRANSITION_21].textureName=TEX_ROULETTE_TRANSITION_GB;
	mRouletteData[ROULETTE_TRANSITION_21].isAnimated=true;
	mRouletteData[ROULETTE_TRANSITION_21].numFrames=TRANSITION_NFRAMES;
	mRouletteData[ROULETTE_TRANSITION_21].duration=TRANSITION_DURATION;
	mRouletteData[ROULETTE_TRANSITION_01].textureName=TEX_ROULETTE_TRANSITION_RB;
	mRouletteData[ROULETTE_TRANSITION_01].isAnimated=true;
	mRouletteData[ROULETTE_TRANSITION_01].numFrames=TRANSITION_NFRAMES;
	mRouletteData[ROULETTE_TRANSITION_01].duration=TRANSITION_DURATION;
	mRouletteData[ROULETTE_TRANSITION_10].textureName=TEX_ROULETTE_TRANSITION_BR;
	mRouletteData[ROULETTE_TRANSITION_10].isAnimated=true;
	mRouletteData[ROULETTE_TRANSITION_10].numFrames=TRANSITION_NFRAMES;
	mRouletteData[ROULETTE_TRANSITION_10].duration=TRANSITION_DURATION;
	mRouletteData[ROULETTE_TRANSITION_02].textureName=TEX_ROULETTE_TRANSITION_RG;
	mRouletteData[ROULETTE_TRANSITION_02].isAnimated=true;
	mRouletteData[ROULETTE_TRANSITION_02].numFrames=TRANSITION_NFRAMES;
	mRouletteData[ROULETTE_TRANSITION_02].duration=TRANSITION_DURATION;
	mRouletteData[ROULETTE_TRANSITION_20].textureName=TEX_ROULETTE_TRANSITION_GR;
	mRouletteData[ROULETTE_TRANSITION_20].isAnimated=true;
	mRouletteData[ROULETTE_TRANSITION_20].numFrames=TRANSITION_NFRAMES;
	mRouletteData[ROULETTE_TRANSITION_20].duration=TRANSITION_DURATION;
}

void HUDInGame::initHealthHud(int healthPoints, int numLives)
{
	mHealthHudTextures[0]=TEX_HEALTH_HUD_NAME_EMPTY;
	mHealthHudTextures[1]=TEX_HEALTH_HUD_NAME_X1;
	mHealthHudTextures[2]=TEX_HEALTH_HUD_NAME_X2;
	mHealthHudTextures[3]=TEX_HEALTH_HUD_NAME_FULL;

	updateHealthHUD(healthPoints,numLives);
}

void HUDInGame::spinRoulette(bool forward)
{
	int increment=forward?1:-1;
	bool isColourRouletteState=mCurrentRouletteState==ROULETTE_STATE_1 || 
		mCurrentRouletteState==ROULETTE_STATE_0 || mCurrentRouletteState == ROULETTE_STATE_2;
	if (isColourRouletteState)
	{	
		int next=(mCurrentRouletteState+increment)%NUM_ROULETTE_STATES;
		if (next<0) next+=NUM_ROULETTE_STATES;
		mCurrentRouletteState=static_cast<TRouletteState>(next);
		updateRouletteHUD();
	}	
}

void HUDInGame::updateRoulette()
{
	bool isLeftTransition = mCurrentRouletteState== ROULETTE_TRANSITION_02 ||
		mCurrentRouletteState == ROULETTE_TRANSITION_21 || mCurrentRouletteState==ROULETTE_TRANSITION_10;
	bool isRightTransition = mCurrentRouletteState==ROULETTE_TRANSITION_01 ||
		mCurrentRouletteState == ROULETTE_TRANSITION_12 || mCurrentRouletteState==ROULETTE_TRANSITION_20;
	int increment=0;
	if (isLeftTransition)
		increment=-2;
	else if (isRightTransition)
		increment=2;
	//---
	if ((isLeftTransition || isRightTransition) && isRouletteAnimationFinished())
	{
		int next=(mCurrentRouletteState+increment)%NUM_ROULETTE_STATES;
		if (next<0) next+=NUM_ROULETTE_STATES;
		mCurrentRouletteState=static_cast<TRouletteState>(next);
		mSelectedModeChanged=true;
		updateRouletteHUD();
	}
}

bool HUDInGame::isRouletteAnimationFinished()
{
	if (mRouletteData[mCurrentRouletteState].isAnimated)
	{		
		if (!mRouletteMaterial.isNull())
		{
			int currentFrame=mRouletteMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getCurrentFrame();
			int lastFrame=mRouletteMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getNumFrames()-1;
			return currentFrame==lastFrame;
		}
		else Logger::getInstance()->log("Material name not found. Function HUDInGame::isRouletteAnimationFinished");
		return false;
	}
	return false;
}

void HUDInGame::updateRouletteHUD()
{
	if (!mRouletteMaterial.isNull())
	{
		if (mRouletteData[mCurrentRouletteState].isAnimated)
			mRouletteMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAnimatedTextureName(
				mRouletteData[mCurrentRouletteState].textureName,
				mRouletteData[mCurrentRouletteState].numFrames,
				mRouletteData[mCurrentRouletteState].duration
			);
		else
			mRouletteMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(
				mRouletteData[mCurrentRouletteState].textureName
			);		
	}
	else Logger::getInstance()->log("Material name not found. Function HUDInGame::setTextureData");
}

void HUDInGame::updateHealthHUD(int healthPoints, int numLives)
{
	if (mLives)
	{
		std::ostringstream livesText;
		livesText.str("");
		livesText<<'x'<<numLives;
		mLives->setCaption(livesText.str());
	}		
	if (!mHealthMaterial.isNull())
	{
		mHealthMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(mHealthHudTextures[healthPoints]);	
	}
}

void HUDInGame::update(double elapsedSeconds, int healthPoints, int numLives)
{
	updateRoulette();
	updateHealthHUD(healthPoints,numLives);

	if(mIsChangingWorld)
	{
		mChangeWorldElapsedTime+=elapsedSeconds;
		if(mChangeWorldElapsedTime>=mChangeWorldTotalTime)
		{
			changeToWorld(mWorld,1);
			changeWorldFinished(mWorld);
			mIsChangingWorld=false;
		}
		else
		{
			changeToWorld(mWorld,mChangeWorldElapsedTime/mChangeWorldTotalTime);
		}
	}
}
bool HUDInGame::isSelectedModeChanged()
{
	return mSelectedModeChanged;
}

void HUDInGame::setSelectedModeChanged(bool selectedModeChanged)
{
	mSelectedModeChanged=selectedModeChanged;
}

TRouletteState HUDInGame::getCurrentState() const
{
	return mCurrentRouletteState;
}

void HUDInGame::registerEventHandlers(EventManagerPtr evtMgr)
{
	boost::shared_ptr<HUDInGame> this_ = shared_from_this();
	if (evtMgr.get())
	{
		EventHandlerPtr eh = EventHandlerPtr(new EventHandler<HUDInGame,ChangeWorldEvent>(this_,&HUDInGame::processChangeWorld));
		evtMgr->registerHandler(eh,EVENT_TYPE_CHANGEWORLD);

	}
}

void HUDInGame::unregisterEventHandlers(EventManagerPtr evtMgr)
{
	boost::shared_ptr<HUDInGame> this_ = shared_from_this();
	if (evtMgr.get())
	{
		EventHandlerPtr eh = EventHandlerPtr(new EventHandler<HUDInGame,ChangeWorldEvent>(this_,&HUDInGame::processChangeWorld));
		evtMgr->unregisterHandler(eh,EVENT_TYPE_CHANGEWORLD);
	}
}

void HUDInGame::processChangeWorld(ChangeWorldEventPtr evt)
{
	mWorld=evt->getNewWorld();
	mChangeWorldTotalTime=evt->time;

	if (evt->fast)
	{
		activateChangeWorldFast();
	}
	else
	{
		activateChangeWorld();
	}
}

void HUDInGame::activateChangeWorldFast()
{
	changeWorldFinished(mChangeWorldTotalTime);
	mIsChangingWorld=false;
}

void HUDInGame::activateChangeWorld()
{
	if(mIsChangingWorld)
	{
		mChangeWorldElapsedTime=mChangeWorldTotalTime-mChangeWorldElapsedTime;
	}
	else
	{
		changeWorldStarted(mWorld);
		mChangeWorldElapsedTime=0;
		mIsChangingWorld=true;
	}

}

void HUDInGame::changeWorldFinished(int newWorld)
{
	switch(newWorld)
	{
	case DREAMS:
		hideElement(PANEL_ROULETTE);
		//TODO:
		//showElement(PANEL_PILLOW_ROULETTE);
		break;
	case NIGHTMARES:
		showElement(PANEL_ROULETTE);
		mCurrentRouletteState=ROULETTE_STATE_0;
		updateRouletteHUD();
		mSelectedModeChanged=true;
		//TOD:
		//hideElement(PANEL_PILLOW_ROULETTE);
		break;
	default:
		break;
	}
}

void HUDInGame::changeWorldStarted(int newWorld)
{
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

void HUDInGame::changeToWorld(int newWorld, double perc)
{
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