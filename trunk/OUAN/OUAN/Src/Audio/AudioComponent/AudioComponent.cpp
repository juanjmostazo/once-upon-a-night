#include "AudioComponent.h"

#include "../AudioSubsystem.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Game/GameObject/GameObject.h"
using namespace OUAN;

AudioComponent::AudioComponent(AudioSubsystemPtr audioSS)
:Component(COMPONENT_TYPE_AUDIO)
,mAudioSS(audioSS)
{
	mSounds.clear();
}
AudioComponent::~AudioComponent()
{
	mSounds.clear();
	mAudioSS.reset();
}

void AudioComponent::update(long elapsedTime)
{
	RenderComponentPositionalPtr position;
	if (mParent->isEnabled() && mParent->hasPositionalComponent() 
		&& (position=mParent->getPositionalComponent()).get())
	{		
		for (TAudioComponentMap::const_iterator it=mSounds.begin();it!=mSounds.end();++it)
		{
			try
			{
				if (mAudioSS->is3DSound(it->first) && mAudioSS->isChannelPlaying(it->second))
				{
					//Velocity is not taken into account. We're not caring about the Doppler effect at the moment.
					mAudioSS->updateChannel3DAttributes(it->second,position->getSceneNode()->getPosition(),Ogre::Vector3::ZERO);
				}
			}
			catch (std::exception& e)
			{
				Logger::getInstance()->log(e.what());
			}
		}
	}
}
void AudioComponent::playSound(const std::string& soundID)
{
	if (mParent->isEnabled() && mSounds.find(soundID)!=mSounds.end())
	{
		if (mAudioSS->is3DSound(soundID) && mParent->hasPositionalComponent())
		{
			RenderComponentPositionalPtr position=mParent->getPositionalComponent();
			if (position.get())
				mAudioSS->play3DSound(soundID,position->getSceneNode()->getPosition(),mSounds[soundID]);
		}
		else
		{
			mAudioSS->playSound(soundID,mSounds[soundID]);
		}
	}
}
void AudioComponent::stopSound(const std::string& soundID)
{
	if (mSounds.find(soundID)!=mSounds.end())
	{
		mAudioSS->stopSound(mSounds[soundID]);
	}
}
void AudioComponent::setPauseSound(const std::string& soundID,bool pause)
{
	if(mSounds.find(soundID)!=mSounds.end())
	{
		mAudioSS->setPause(mSounds[soundID],pause);
	}
}
void AudioComponent::setSounds(const TAudioComponentMap& sounds)
{
	mSounds=sounds;
	for (TAudioComponentMap::const_iterator it=mSounds.begin();it!=mSounds.end();++it)
	{
		if (!mAudioSS->isLoaded(it->first))
			mAudioSS->load(it->first,AUDIO_RESOURCES_GROUP_NAME);
	}	
}