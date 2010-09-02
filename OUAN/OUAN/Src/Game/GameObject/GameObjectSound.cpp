#include "OUAN_Precompiled.h"

#include "GameObjectSound.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectSound::GameObjectSound(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_SOUND)
{

}

GameObjectSound::~GameObjectSound()
{

}

TGameObjectSoundType GameObjectSound::getSoundType() const
{
	return mSoundType;
}
void GameObjectSound::setSoundType(TGameObjectSoundType soundType)
{
	mSoundType=soundType;
}

AudioComponentPtr GameObjectSound::getAudioComponentDreams() const
{
	return mAudioComponentDreams;
}

void GameObjectSound::setAudioComponentDreams(AudioComponentPtr audioComponent)
{
	mAudioComponentDreams=audioComponent;
}
AudioComponentPtr GameObjectSound::getAudioComponentNightmares() const
{
	return mAudioComponentNightmares;
}

void GameObjectSound::setAudioComponentNightmares(AudioComponentPtr audioComponent)
{
	mAudioComponentNightmares=audioComponent;
}

void GameObjectSound::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}
RenderComponentPositionalPtr GameObjectSound::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectSound::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}
RenderComponentInitialPtr GameObjectSound::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectSound::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		if (mAudioComponentDreams.get())
		{
			mAudioComponentDreams->playSound(mCurrentDreamsSoundID);
		}
		if (mAudioComponentNightmares.get())
		{
			mAudioComponentNightmares->stopSound(mCurrentDreamsSoundID);
		}
		break;
	case NIGHTMARES:
		if (mAudioComponentDreams.get())
		{
			mAudioComponentDreams->stopSound(mCurrentDreamsSoundID);
		}
		if (mAudioComponentNightmares.get())
		{
			mAudioComponentNightmares->playSound(mCurrentDreamsSoundID);
		}
		break;
	default:
		break;
	}
}

void GameObjectSound::changeWorldStarted(int newWorld)
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

void GameObjectSound::changeToWorld(int newWorld, double perc)
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

void GameObjectSound::reset()
{
	GameObject::reset();
	if (mRenderComponentPositional.get())
	{
		mRenderComponentPositional->setPosition(mRenderComponentInitial->getPosition());
		mRenderComponentPositional->setOrientation(mRenderComponentInitial->getOrientation());
	}
	if (mAudioComponentDreams.get())
	{
		mAudioComponentDreams->stopSound(mCurrentDreamsSoundID);
	}
	if (mAudioComponentNightmares.get())
	{
		mAudioComponentNightmares->stopSound(mCurrentDreamsSoundID);
	}

	play(mGameWorldManager->getWorld()==DREAMS?mCurrentDreamsSoundID:mCurrentNightmaresSoundID);
}

bool GameObjectSound::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectSound::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectSound::hasAudioComponent() const
{
	return true;
}
AudioComponentPtr GameObjectSound::getAudioComponentInstance() const
{
	switch (mGameWorldManager->getWorld())
	{
	case DREAMS:
		return mAudioComponentDreams;
	case NIGHTMARES:
		return mAudioComponentNightmares;
	default:
		return AudioComponentPtr();
	}
}

void GameObjectSound::play(const std::string& soundID)
{
	switch(mGameWorldManager->getWorld())
	{
	case DREAMS:
		mAudioComponentDreams->playSound(soundID);
		break;
	case NIGHTMARES:
		mAudioComponentNightmares->playSound(soundID);
		break;
	}
}
void GameObjectSound::stop(const std::string& soundID)
{
	switch(mGameWorldManager->getWorld())
	{
	case DREAMS:
		mAudioComponentDreams->stopSound(soundID);
		break;
	case NIGHTMARES:
		mAudioComponentNightmares->stopSound(soundID);
		break;
	}
}

void GameObjectSound::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
}
const std::string& GameObjectSound::getCurrentDreamsSoundId() const
{
	return mCurrentDreamsSoundID;
}
void GameObjectSound::setCurrentDreamsSoundId(const std::string& soundId)
{
	mCurrentDreamsSoundID=soundId;
}

const std::string& GameObjectSound::getCurrentNightmaresSoundId() const
{
	return mCurrentNightmaresSoundID;
}
void GameObjectSound::setCurrentNightmaresSoundId(const std::string& soundId)
{
	mCurrentNightmaresSoundID=soundId;
}
TGameObjectSoundParameters::TGameObjectSoundParameters() : TGameObjectParameters()
{

}

TGameObjectSoundParameters::~TGameObjectSoundParameters()
{

}