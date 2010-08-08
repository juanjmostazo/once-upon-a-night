#include "OUAN_Precompiled.h"

#include "Sound.h"
#include "AudioSubsystem.h"

using namespace OUAN;

Sound::Sound(Ogre::ResourceManager* creator, const Ogre::String& name,
			 Ogre::ResourceHandle handle, const Ogre::String& group, 
			 bool isManual,Ogre::ManualResourceLoader* loader)
:Ogre::Resource(creator, name, handle, group, isManual, loader)
,mFMODSound(NULL)
{
	mSoundData.mId.clear();
	mSoundData.mChannelGroupID.clear();
	mSoundData.mFileName.clear();
	mSoundData.m3D=mSoundData.mStream=mSoundData.mHardware=mSoundData.mLoop=false;
	mSoundData.minDistance=mSoundData.maxDistance==0.0;
	mSoundData.volume=1.0;
	
	createParamDictionary("Sound");
}

Sound::~Sound()
{
	unload();
}
void Sound::loadImpl()
{
	AudioSubsystem* audioSS= dynamic_cast<AudioSubsystem*> (mCreator);
	if (audioSS)
	{
		audioSS->createSoundImplementation(mSoundData,mFMODSound);
		//audioSS->createFMODSound(mSoundData,mFMODSound);
	}
}
void Sound::unloadImpl()
{
	AudioSubsystem* audioSS= dynamic_cast<AudioSubsystem*> (mCreator);
	if (audioSS)
	{
		audioSS->destroySoundImplementation(mFMODSound);
		//audioSS->destroyFMODSound(mFMODSound);
		mFMODSound=NULL;
	}
}
size_t Sound::calculateSize() const
{
	size_t totalSize=sizeof(TSoundData)+sizeof(FMOD::Sound*);
	return totalSize;
}

FMOD::Sound* Sound::getFMODSound() const
{
	return mFMODSound;
}
void Sound::setFMODSound(FMOD::Sound* FMODSound)
{
	mFMODSound=FMODSound;
}
