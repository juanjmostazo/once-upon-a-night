#include "HUDInGame.h"
#include <Ogre.h>

using namespace OUAN;

HUDInGame::HUDInGame()
:HUDBase()
{

}
HUDInGame::~HUDInGame()
{
	destroy();
}
void HUDInGame::init(int healthPoints, int numLives)
{
	HUDBase::init(OVERLAY_INGAME_HUD);
	mHealthMaterial= Ogre::MaterialManager::getSingletonPtr()->getByName(MATERIAL_HEALTH);
	mRouletteMaterial=Ogre::MaterialManager::getSingletonPtr()->getByName(MATERIAL_ROULETTE);		

	mLives=Ogre::OverlayManager::getSingleton().getOverlayElement(OVERLAY_INGAME_HUD_LIVES_TEXT);

	initRouletteData();
	mCurrentRouletteState=ROULETTE_COLOUR_RED;
	updateRouletteHUD();
	initHealthHud(healthPoints,numLives);
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
	mRouletteData[ROULETTE_COLOUR_RED].textureName=TEX_ROULETTE_COLOUR_RED;
	mRouletteData[ROULETTE_COLOUR_RED].isAnimated=false;
	mRouletteData[ROULETTE_COLOUR_BLUE].textureName=TEX_ROULETTE_COLOUR_BLUE;
	mRouletteData[ROULETTE_COLOUR_BLUE].isAnimated=false;
	mRouletteData[ROULETTE_COLOUR_GREEN].textureName=TEX_ROULETTE_COLOUR_GREEN;
	mRouletteData[ROULETTE_COLOUR_GREEN].isAnimated=false;
	mRouletteData[ROULETTE_TRANSITION_BLUEGREEN].textureName=TEX_ROULETTE_TRANSITION_BG;
	mRouletteData[ROULETTE_TRANSITION_BLUEGREEN].isAnimated=true;
	mRouletteData[ROULETTE_TRANSITION_BLUEGREEN].numFrames=TRANSITION_NFRAMES;
	mRouletteData[ROULETTE_TRANSITION_BLUEGREEN].duration=TRANSITION_DURATION;
	mRouletteData[ROULETTE_TRANSITION_GREENBLUE].textureName=TEX_ROULETTE_TRANSITION_GB;
	mRouletteData[ROULETTE_TRANSITION_GREENBLUE].isAnimated=true;
	mRouletteData[ROULETTE_TRANSITION_GREENBLUE].numFrames=TRANSITION_NFRAMES;
	mRouletteData[ROULETTE_TRANSITION_GREENBLUE].duration=TRANSITION_DURATION;
	mRouletteData[ROULETTE_TRANSITION_REDBLUE].textureName=TEX_ROULETTE_TRANSITION_RB;
	mRouletteData[ROULETTE_TRANSITION_REDBLUE].isAnimated=true;
	mRouletteData[ROULETTE_TRANSITION_REDBLUE].numFrames=TRANSITION_NFRAMES;
	mRouletteData[ROULETTE_TRANSITION_REDBLUE].duration=TRANSITION_DURATION;
	mRouletteData[ROULETTE_TRANSITION_BLUERED].textureName=TEX_ROULETTE_TRANSITION_BR;
	mRouletteData[ROULETTE_TRANSITION_BLUERED].isAnimated=true;
	mRouletteData[ROULETTE_TRANSITION_BLUERED].numFrames=TRANSITION_NFRAMES;
	mRouletteData[ROULETTE_TRANSITION_BLUERED].duration=TRANSITION_DURATION;
	mRouletteData[ROULETTE_TRANSITION_REDGREEN].textureName=TEX_ROULETTE_TRANSITION_RG;
	mRouletteData[ROULETTE_TRANSITION_REDGREEN].isAnimated=true;
	mRouletteData[ROULETTE_TRANSITION_REDGREEN].numFrames=TRANSITION_NFRAMES;
	mRouletteData[ROULETTE_TRANSITION_REDGREEN].duration=TRANSITION_DURATION;
	mRouletteData[ROULETTE_TRANSITION_GREENRED].textureName=TEX_ROULETTE_TRANSITION_GR;
	mRouletteData[ROULETTE_TRANSITION_GREENRED].isAnimated=true;
	mRouletteData[ROULETTE_TRANSITION_GREENRED].numFrames=TRANSITION_NFRAMES;
	mRouletteData[ROULETTE_TRANSITION_GREENRED].duration=TRANSITION_DURATION;
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
	bool isColourRouletteState=mCurrentRouletteState==ROULETTE_COLOUR_BLUE || 
		mCurrentRouletteState==ROULETTE_COLOUR_RED || mCurrentRouletteState == ROULETTE_COLOUR_GREEN;
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
	bool isLeftTransition = mCurrentRouletteState== ROULETTE_TRANSITION_REDGREEN ||
		mCurrentRouletteState == ROULETTE_TRANSITION_GREENBLUE || mCurrentRouletteState==ROULETTE_TRANSITION_BLUERED;
	bool isRightTransition = mCurrentRouletteState==ROULETTE_TRANSITION_REDBLUE ||
		mCurrentRouletteState == ROULETTE_TRANSITION_BLUEGREEN || mCurrentRouletteState==ROULETTE_TRANSITION_GREENRED;
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
		else Ogre::LogManager::getSingletonPtr()->logMessage("Material name not found. Function HUDInGame::isRouletteAnimationFinished");
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
	else Ogre::LogManager::getSingletonPtr()->logMessage("Material name not found. Function HUDInGame::setTextureData");
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
void HUDInGame::update(long elapsedTime, int healthPoints, int numLives)
{
	updateRoulette();
	updateHealthHUD(healthPoints,numLives);
}
