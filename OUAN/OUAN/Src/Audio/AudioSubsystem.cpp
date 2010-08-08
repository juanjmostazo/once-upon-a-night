#include "OUAN_Precompiled.h"

#include "AudioSubsystem.h"
#include "Channel.h"
#include "AudioScriptLoader.h"

#include "../Application.h"
#include "../Utils/Utils.h"

#include "../Event/Event.h"
#include "../Event/EventManager.h"


using namespace OUAN;

//--- Audio subsystem config data
void TAudioSubsystemConfigData::set(ConfigurationPtr config)
{
	if (config.get() && !config->isEmpty())
	{		
		// 3D sound attributes
		try
		{
			mDopplerScale=config->parseDouble(CONFIG_KEYS_DOPPLER_SCALE);
			mDistanceFactor=config->parseDouble(CONFIG_KEYS_DISTANCE_FACTOR);
			mRollOffScale=config->parseDouble(CONFIG_KEYS_ROLLOFF_SCALE);
			mMasterVolume=config->parseDouble(CONFIG_KEYS_MASTER_VOLUME);
			mMasterPitch=config->parseDouble(CONFIG_KEYS_MASTER_PITCH);
			mMasterVolumeEnabled=config->parseBool(CONFIG_KEYS_MASTER_ENABLED);
			mNumChannels=config->parseInt(CONFIG_KEYS_MASTER_NUM_CHANNELS);
			mMusicVolume=config->parseDouble(CONFIG_KEYS_MUSIC_VOLUME);
			mMusicPitch=config->parseDouble(CONFIG_KEYS_MUSIC_PITCH);
			mMusicVolumeEnabled=config->parseBool(CONFIG_KEYS_MUSIC_ENABLED);
			mMusicNumChannels=config->parseInt(CONFIG_KEYS_MUSIC_NUM_CHANNELS);
			mSfxVolume=config->parseDouble(CONFIG_KEYS_SFX_VOLUME);
			mSfxPitch=config->parseDouble(CONFIG_KEYS_SFX_PITCH);
			mSfxVolumeEnabled=config->parseBool(CONFIG_KEYS_SFX_ENABLED);
			mSfxNumChannels=config->parseInt(CONFIG_KEYS_SFX_NUM_CHANNELS);
			mFrameSkip=config->parseInt(CONFIG_KEYS_AUDIO_SUBSYSTEM_FRAME_SKIP);
		}
		catch (const std::exception& e)
		{
			Logger::getInstance()->log("[AudioSubsystemConfigData::set]An error happened while parsing the audio config file");
			Logger::getInstance()->log(e.what());
		}
	}
}

//--- FMOD'S VECTOR CONVERSION AUXILIARY FUNCTIONS

FMOD_VECTOR FMODHelper::toFMODVec(const Ogre::Vector3 &vec)
{

	FMOD_VECTOR rc;
	rc.x=vec.x;
	rc.y=vec.y;
	rc.z=vec.z;
	return rc;
}
Ogre::Vector3  FMODHelper::toOgreVec3(const FMOD_VECTOR& vec)
{
	Ogre::Vector3 rc;
	rc.x=vec.x;
	rc.y=vec.y;
	rc.z=vec.z;
	return rc;
}


//--- AUDIO SUBSYSTEM DEFS

AudioSubsystem::AudioSubsystem()
{
	mSystem=NULL;	
}
AudioSubsystem::~AudioSubsystem()
{
	
}

void AudioSubsystem::cleanUp()
{
	for(TChannelGroupMap::iterator i=mChannelGroupMap.begin();
		i!=mChannelGroupMap.end(); i++)
	{
		(i->second)->release();
	}
	mLastMusic.clear();
	mChannelGroupMap.clear();
	mSystem->close();
	mSystem->release();
	
	Ogre::ResourceGroupManager::getSingleton()._unregisterResourceManager(mResourceType);
}
bool AudioSubsystem::init(TAudioSubsystemConfigData& desc, ApplicationPtr app)
{
	mApp=app;
	mFrameSkip=desc.mFrameSkip;

	bool rc = false;
	//attempt to create the system
	mOldConfigData=desc;
	mConfigData=desc;
	//	m_logFile.push_back("SoundManager::init()");

	if (FMOD_OK ==FMOD::System_Create(&mSystem))
	{
		//m_logFile.push_back("SoundManager::init create system Okay");
		rc = true;
	}

	if(rc && FMOD_OK == mSystem->init(desc.mNumChannels, FMOD_INIT_NORMAL, 0))
	{
		//m_logFile.push_back("SoundManager::init system ok");
		rc = true;
	}
	mSystem->set3DSettings(desc.mDopplerScale,desc.mDistanceFactor,
		desc.mRollOffScale);
	if(rc)
	{

		FMOD::ChannelGroup*			channelGroups[3];

		//get the master group
		mSystem->getMasterChannelGroup(&channelGroups[0]);

		//create various channel groups
		mSystem->createChannelGroup(SM_CHANNEL_MUSIC_GROUP.c_str(),	
			&channelGroups[1]);

		mSystem->createChannelGroup(SM_CHANNEL_SFX_GROUP.c_str(),		
			&channelGroups[2]);

		//add these groups to the master group
		channelGroups[0]->addGroup(channelGroups[1]);
		channelGroups[0]->addGroup(channelGroups[2]);

		mChannelGroupMap.clear();
		mChannelGroupMap[SM_CHANNEL_MASTER_GROUP] = ChannelGroupPtr(new ChannelGroup(channelGroups[0]));

		channelGroups[0]->setVolume(desc.mMasterVolume);
		channelGroups[1]->setVolume(desc.mMusicVolume);
		channelGroups[2]->setVolume(desc.mSfxVolume);

		channelGroups[0]->setPitch(desc.mMasterPitch);
		channelGroups[1]->setPitch(desc.mMusicPitch);
		channelGroups[2]->setPitch(desc.mSfxPitch);

		int offset = 0;
		mChannelGroupMap[SM_CHANNEL_MUSIC_GROUP]  = ChannelGroupPtr(
			new ChannelGroup(channelGroups[1],desc.mMusicNumChannels,
			mSystem,offset));

		mChannelGroupMap[SM_CHANNEL_SFX_GROUP]	 = ChannelGroupPtr( 
			new ChannelGroup(channelGroups[2],desc.mSfxNumChannels,
			mSystem,offset));

		if (!desc.mMasterVolumeEnabled)
		{
			pauseChannelGroup(SM_CHANNEL_MASTER_GROUP,true);
		}
		if (!desc.mMusicVolumeEnabled)
		{
			pauseChannelGroup(SM_CHANNEL_MUSIC_GROUP,true);
		}
		if (!desc.mSfxVolumeEnabled)
		{
			pauseChannelGroup(SM_CHANNEL_SFX_GROUP,true);
		}
	}

	//Resource management init
	mResourceType = "Sound";

	// low, because it will likely reference other resources
	mLoadOrder = 30.0f;

	mScriptPatterns.push_back("*.sound");
	Ogre::ResourceGroupManager::getSingleton()._registerScriptLoader(this);

	// this is how we register the ResourceManager with OGRE
	Ogre::ResourceGroupManager::getSingleton()._registerResourceManager(mResourceType, this);

	return rc;
}
void AudioSubsystem::set3DMinMaxDistance(const std::string& channelID,	
										 double minDistance,
										 double maxDistance)
{
	if(mChannelGroupMap.find( channelID ) != mChannelGroupMap.end())
	{
		mChannelGroupMap[channelID]->set3DMinMaxDistance(minDistance,
			maxDistance);

	}
}

//
//bool AudioSubsystem::addSound(const std::string& soundID,
//							  const std::string& sound,
//							  const std::string& channelID,
//							  int soundFlag)
//{
//	TSoundData sndData;
//	sndData.mId=soundID;
//	sndData.mFileName=sound;
//	sndData.mChannelGroupID= channelID;
//	sndData.mLoop=sndData.mStream=sndData.m3D=sndData.mHardware=false;
//
//	if(soundFlag&SOUND_FLAG_LOOP)
//	{
//		sndData.mLoop=true;
//	}
//	if(soundFlag&SOUND_FLAG_HARDWARE)
//	{
//		sndData.mHardware=true;
//	}
//	if(soundFlag&SOUND_FLAG_3D)
//	{
//		sndData.m3D=true;
//	}
//	if(soundFlag&SOUND_FLAG_STREAM)
//	{
//		sndData.mStream=true;
//	}
//
//	return addSound(sndData);
//}
//
//bool AudioSubsystem::addSound(const TSoundData& desc)
//{
//	bool rc = false;
//	FMOD_MODE   flag = 0;
//	FMOD_RESULT result;
//	if(mSystem)
//	{
//		if(desc.mLoop)
//		{
//			flag |= FMOD_LOOP_NORMAL;
//		}
//		if(desc.mHardware)
//		{
//			flag |= FMOD_HARDWARE;
//		}
//
//		if(desc.m3D)
//		{
//			flag |= FMOD_3D;
//		}else{
//			flag |= FMOD_2D;
//		}
//		//m_logFile.push_back("AddSound" + desc.id + " fn: " + desc.fn);
//		FMOD::Sound* soundPtr;
//		std::string filename=AUDIO_RESOURCE_PATH+desc.mFileName;
//		if(desc.mStream)
//		{
//			result = mSystem->createStream(filename.c_str(), flag, 0, &soundPtr);
//		}else{
//			//MessageBox(0,desc.fn.c_str(),"FILE",0);
//			result = mSystem->createSound(filename.c_str(), flag,0, &soundPtr);
//		}
//		if (result == FMOD_OK)
//		{
//			rc = true;
//
//			//m_logFile.push_back("AddSound" + desc.id + " fn: " + desc.fn + "Ok");
//
//			SoundPtr sound(new Sound());
//			sound->mSoundData.mChannelGroupID = desc.mChannelGroupID;
//			sound->mFMODSound= soundPtr;
//			mSoundMap[desc.mId] = sound;
//
//		}
//	}
//	return rc;	
//}



bool AudioSubsystem::setChannelGroupVolume(const std::string& id,
										   double volume)
{
	bool rc = false;
	if(mChannelGroupMap.find(id)!=mChannelGroupMap.end())
	{
		if(mChannelGroupMap[id]->setVolume(volume))
		{
			rc=true;
		}
	}
	return rc;
}
bool AudioSubsystem::setChannelGroupPitch(const std::string& id,
										  double volume)
{
	bool rc = false;
	if(mChannelGroupMap.find(id)!=mChannelGroupMap.end())
	{
		if(mChannelGroupMap[id]->setPitch(volume))
		{
			rc=true;
		}
	}
	return rc;
}
bool AudioSubsystem::pauseChannelGroup(const std::string& id,
									   bool overrideMute)
{
	bool rc = false;
	if(mChannelGroupMap.find(id)!=mChannelGroupMap.end())
	{
		if(mChannelGroupMap[id]->setPaused(overrideMute))
		{
			rc=true;
		}
	}
	return rc;
}

bool AudioSubsystem::play3DSound(const std::string& id,
								 const Ogre::Vector3& pos,
								 int& channelIndex,
								 const Ogre::Vector3& vel)
{
	bool rc = false;
	ChannelGroupPtr outChannel= ChannelGroupPtr();
	int cIndex;
	if(_playSound(id,outChannel,cIndex))
	{
		SoundPtr soundPtr = getByName(id);
		if (!soundPtr.isNull())
		{
			std::string cgid = soundPtr->mSoundData.mChannelGroupID;

			mChannelGroupMap[cgid]->set3DMinMaxDistance(cIndex,soundPtr->mSoundData.minDistance,soundPtr->mSoundData.maxDistance);
			mChannelGroupMap[cgid]->set3DAttributes( cIndex,pos,vel );
			mChannelGroupMap[cgid]->play( cIndex);		
			soundPtr.setNull();
		}
		channelIndex=cIndex;
		rc = true;

	}
	return rc;
}
bool AudioSubsystem::playMusic(const std::string& id, int& channelIndex,
							   bool overRide)
{
	bool rc = false;
	ChannelGroupPtr outChannel = ChannelGroupPtr();
	int cIndex;
	if(overRide == true || id != mLastMusic)
	{
		if(_playSound(id,outChannel,cIndex))
		{
			SoundPtr soundPtr = getByName(id);
			if (!soundPtr.isNull())
			{
				std::string cgid = soundPtr->mSoundData.mChannelGroupID;			
				mChannelGroupMap[cgid]->play( cIndex);
				mLastMusic= id;
				soundPtr.setNull();
			}			
			channelIndex=cIndex;
			rc = true;
		}
	}
	return rc;
}


bool AudioSubsystem::playSound(const std::string& id,int& channelIndex)
{
	bool rc = false;
	ChannelGroupPtr outChannel = ChannelGroupPtr();
	int cIndex;
	if(_playSound(id,outChannel,cIndex))
	{
		SoundPtr soundPtr = getByName(id);
		if (!soundPtr.isNull())
		{
			std::string cgid = soundPtr->mSoundData.mChannelGroupID;			
			mChannelGroupMap[cgid]->play( cIndex);
			soundPtr.setNull();
		}
		rc = true;
		channelIndex=cIndex;
	}
	return rc;
}

bool AudioSubsystem::_playSound(const std::string& id,
								ChannelGroupPtr outChannel,
								int& channelIndex)
{
	bool rc = false;
	if(mSystem)
	{
		SoundPtr soundPtr = getByName(id);
		if(!soundPtr.isNull())
		{

			std::string cgid = soundPtr->mSoundData.mChannelGroupID;
			if(mChannelGroupMap.find(cgid)!=mChannelGroupMap.end())
			{
				FMOD_RESULT hr;
				outChannel = mChannelGroupMap[cgid];

				//find a free channel.
				if (!(outChannel->getChannelObject(channelIndex).get() && outChannel->getChannelObject(channelIndex)->isFree()))
					channelIndex = mChannelGroupMap[cgid]->getFreeChannelIndex();
				if(channelIndex!=-1)
				{
					bool masterEnabled = mConfigData.mMasterVolumeEnabled;
					bool musicEnabled = (cgid==SM_CHANNEL_MUSIC_GROUP)	&& 
						mConfigData.mMusicVolumeEnabled;
					bool sfxEnabled = cgid==SM_CHANNEL_SFX_GROUP		&& 
						mConfigData.mSfxVolumeEnabled;

					if(musicEnabled || sfxEnabled)
					{
						int tmp = channelIndex;
						FMOD_CHANNELINDEX cid = outChannel->getChannelIndex(tmp);

						FMOD::Channel* channel = outChannel->getChannel(tmp);

						hr = mSystem->playSound(cid,
							soundPtr->getFMODSound(), 
							true, 
							&channel);
						outChannel->getChannelObject(tmp)->setVolume(soundPtr->mSoundData.volume);
						outChannel->setChannel(tmp,channel);
						outChannel->getChannelObject(tmp)->setFree(false);

						rc = true;
					}
				}
			}
			soundPtr.setNull();
		}
	}
	return rc;
}

void AudioSubsystem::set3DAttributes(const Ogre::Vector3& pos,
									 const Ogre::Vector3& vel,
									 const Ogre::Vector3& forward,
									 const Ogre::Vector3& up)
{
	FMOD_VECTOR    listenerPos		= FMODHelper::toFMODVec(pos);
	FMOD_VECTOR    listenerForward	= FMODHelper::toFMODVec(forward);
	FMOD_VECTOR    listenerUp		= FMODHelper::toFMODVec(up);
	FMOD_VECTOR    listenerVelocity  = FMODHelper::toFMODVec(vel);
	mSystem->set3DListenerAttributes(0, 
		&listenerPos,
		&listenerVelocity, 
		&listenerForward, 
		&listenerUp);
}
bool AudioSubsystem::update(double elapsedSeconds)
{
	bool rc = false;
	FMOD_RESULT hr;

	if(mSystem)
	{
		if (mOldConfigData.mDopplerScale!=mConfigData.mDopplerScale || mOldConfigData.mDistanceFactor!=mConfigData.mDistanceFactor
			|| mOldConfigData.mRollOffScale!=mConfigData.mRollOffScale)
		{
			mOldConfigData.mDopplerScale=mConfigData.mDopplerScale;
			mOldConfigData.mDistanceFactor=mConfigData.mDistanceFactor;
			mOldConfigData.mRollOffScale=mConfigData.mRollOffScale;
			mSystem->set3DSettings(mConfigData.mDopplerScale,mConfigData.mDistanceFactor,
				mConfigData.mRollOffScale);
		}
		////master group
		if(mOldConfigData.mMasterVolumeEnabled!=mConfigData.mMasterVolumeEnabled)
		{
			bool pauseMasterChannel = !mConfigData.mMasterVolumeEnabled;
			//pause master
			pauseChannelGroup(SM_CHANNEL_MASTER_GROUP,pauseMasterChannel);

			if(!pauseMasterChannel)
			{
				//pause music
				pauseChannelGroup(SM_CHANNEL_MUSIC_GROUP,!mConfigData.mMusicVolumeEnabled);
				pauseChannelGroup(SM_CHANNEL_SFX_GROUP,!mConfigData.mSfxVolumeEnabled);
			}
			mOldConfigData.mMasterVolumeEnabled= mConfigData.mMasterVolumeEnabled;
		}
		if(mOldConfigData.mMasterPitch!=mConfigData.mMasterPitch)
		{
			setChannelGroupPitch(SM_CHANNEL_MASTER_GROUP,mConfigData.mMasterPitch);
			mOldConfigData.mMasterPitch=mConfigData.mMasterPitch;
		}
		if(mOldConfigData.mMasterVolume!=mConfigData.mMasterVolume)
		{
			setChannelGroupVolume(SM_CHANNEL_MASTER_GROUP,mConfigData.mMasterVolume);
			mOldConfigData.mMasterVolume = mConfigData.mMasterVolume;
		}

		//sfx group
		if(mOldConfigData.mSfxVolumeEnabled!=mConfigData.mSfxVolumeEnabled)
		{
			pauseChannelGroup(SM_CHANNEL_SFX_GROUP,!mConfigData.mSfxVolumeEnabled);
			mOldConfigData.mSfxVolumeEnabled=mConfigData.mSfxVolumeEnabled;
		}
		if(mOldConfigData.mSfxPitch!=mConfigData.mSfxPitch)
		{
			setChannelGroupPitch(SM_CHANNEL_SFX_GROUP,mOldConfigData.mSfxPitch);
			mOldConfigData.mSfxPitch= mConfigData.mSfxPitch;
		}
		if( mOldConfigData.mSfxVolume!=mConfigData.mSfxVolume)
		{
			setChannelGroupVolume(SM_CHANNEL_SFX_GROUP,mConfigData.mSfxVolume);
			mOldConfigData.mSfxVolume= mConfigData.mSfxVolume;
		}

		//music group
		if(mOldConfigData.mMusicVolumeEnabled!=mConfigData.mMusicVolumeEnabled)
		{
			pauseChannelGroup(SM_CHANNEL_MUSIC_GROUP,!mConfigData.mMusicVolumeEnabled);
			mOldConfigData.mMusicVolumeEnabled= mConfigData.mMusicVolumeEnabled;
		}
		if(mOldConfigData.mMusicPitch!=mConfigData.mMusicPitch)
		{
			setChannelGroupPitch(SM_CHANNEL_MUSIC_GROUP,mConfigData.mMusicPitch);
			mOldConfigData.mMusicPitch= mConfigData.mMusicPitch;
		}
		if(mOldConfigData.mMusicVolume!=mConfigData.mMusicVolume)
		{
			setChannelGroupVolume(SM_CHANNEL_MUSIC_GROUP,mConfigData.mMusicVolume);
			mOldConfigData.mMusicVolume= mConfigData.mMusicVolume;
		}

		hr = mSystem->update();
		if(hr==FMOD_OK)
		{
			for(TChannelGroupMap::iterator i=mChannelGroupMap.begin(); 
				i!=mChannelGroupMap.end(); i++)
			{
				i->second->update(elapsedSeconds);
			}

			rc=true;
		}
	}
	return rc;
}
TAudioSubsystemConfigData AudioSubsystem::getConfigData()
{
	return mConfigData;
}
void AudioSubsystem::setConfigData(const TAudioSubsystemConfigData& configData)
{
	mConfigData=configData;
}
double AudioSubsystem::getChannelGroupVolume(const std::string& id)
{
	float volume = 1.0;
	if(mChannelGroupMap.find(id)!=mChannelGroupMap.end())
	{
		volume = mChannelGroupMap[id]->getVolume();
	}
	return volume;
}

double AudioSubsystem::getChannelGroupPitch(const std::string& id)
{
	double pitch = 1.0;
	if(mChannelGroupMap.find(id)!=mChannelGroupMap.end())
	{
		pitch = mChannelGroupMap[id]->getPitch();
	}
	return pitch;
}
bool AudioSubsystem::stopSound(int channelIndex, const std::string& channelGroupID)
{
	return mChannelGroupMap[channelGroupID]->stop(channelIndex);
}
bool AudioSubsystem::stopMusic(int channelIndex)
{
	try
	{
		
		if (channelIndex>=0 && isMusicPlaying(channelIndex))
			return stopSound(channelIndex,SM_CHANNEL_MUSIC_GROUP);
		else return false;
	}
	catch (std::exception& e)
	{
		throw e;
	}	
}
void AudioSubsystem::stopAllSounds()
{
	for(TChannelGroupMap::iterator i=mChannelGroupMap.begin();
		i!=mChannelGroupMap.end(); i++)
	{
		(i->second)->stopSounds();
	}

}
bool AudioSubsystem::setPause(int channelIndex, bool pause, const std::string& channelGroup)
{
	ChannelPtr ch=mChannelGroupMap[channelGroup]->getChannelObject(channelIndex);
	if (ch.get())
	{
		return ch->setPaused(pause);
	}
	std::stringstream msg("");
	msg<<"AudioSubsystem::setPause() - Channel at index "<<channelIndex<<" is NULL";
	throw std::exception (msg.str().c_str());
}

ApplicationPtr AudioSubsystem::getApplication()
{
	return mApp;
}
//void AudioSubsystem::removeSound(const std::string& soundID)
//{
//	if (!mSoundMap.empty() && mSoundMap.find(soundID)!=mSoundMap.end())
//	{
//		SoundPtr sound= mSoundMap[soundID];
//		sound->mFMODSound->release();
//		sound.reset();
//		mSoundMap.erase(soundID);
//	}
//}
//void AudioSubsystem::loadSounds(std::vector<TSoundData> soundBank)
//{
//	unloadSounds();
//	if (!soundBank.empty())
//	{
//		for (std::vector<TSoundData>::iterator it = soundBank.begin();it!=soundBank.end();++it)
//		{
//
//			addSound(*it);		
//		}
//	}
//}
//void AudioSubsystem::unloadSounds()
//{
//	// NOTE: Check if channels should be released as well, in case FMOD
//	// does not handle that.
//	for(TSoundMapIterator i=mSoundMap.begin();i!=mSoundMap.end(); i++)
//	{
//		(i->second)->mFMODSound->release();
//	}
//	mSoundMap.clear();	
//}

void AudioSubsystem::saveCurrentConfigData(const std::string& configFileName)
{
	ConfigurationPtr config = ConfigurationPtr(new Configuration());
	TConfigMap options;
	options[CONFIG_KEYS_DOPPLER_SCALE]= Utils::toString(mConfigData.mDopplerScale);
	options[CONFIG_KEYS_DISTANCE_FACTOR]= Utils::toString(mConfigData.mDistanceFactor);
	options[CONFIG_KEYS_ROLLOFF_SCALE]= Utils::toString(mConfigData.mRollOffScale);
	options[CONFIG_KEYS_MASTER_VOLUME]= Utils::toString(mConfigData.mMasterVolume);
	options[CONFIG_KEYS_MASTER_PITCH]= Utils::toString(mConfigData.mMasterPitch);
	options[CONFIG_KEYS_MASTER_ENABLED]= Utils::toString(mConfigData.mMasterVolumeEnabled);
	options[CONFIG_KEYS_MASTER_NUM_CHANNELS]= Utils::toString(mConfigData.mNumChannels);

	options[CONFIG_KEYS_SFX_VOLUME]= Utils::toString(mConfigData.mSfxVolume);
	options[CONFIG_KEYS_SFX_PITCH]= Utils::toString(mConfigData.mSfxPitch);
	options[CONFIG_KEYS_SFX_ENABLED]= Utils::toString(mConfigData.mSfxVolumeEnabled);
	options[CONFIG_KEYS_SFX_NUM_CHANNELS]= Utils::toString(mConfigData.mSfxNumChannels);

	options[CONFIG_KEYS_MUSIC_VOLUME]= Utils::toString(mConfigData.mMusicVolume);
	options[CONFIG_KEYS_MUSIC_PITCH]= Utils::toString(mConfigData.mMusicPitch);
	options[CONFIG_KEYS_MUSIC_ENABLED]= Utils::toString(mConfigData.mMusicVolumeEnabled);
	options[CONFIG_KEYS_MUSIC_NUM_CHANNELS]= Utils::toString(mConfigData.mMusicNumChannels);

	options[CONFIG_KEYS_AUDIO_SUBSYSTEM_FRAME_SKIP]= Utils::toString(mConfigData.mFrameSkip);

	config->addOptions(options);
	std::string filePath = SOUND_RESOURCES_PATH+"/"+configFileName;
	config->saveToFile(filePath);
}
SoundPtr AudioSubsystem::getSound(const std::string& soundID)
{
	/*if (!mSoundMap.empty() && mSoundMap.find(soundID)!=mSoundMap.end())
		return mSoundMap[soundID];*/
	return getByName(soundID);
}
bool AudioSubsystem::is3DSound(const std::string& soundID)
{
	SoundPtr sound=getSound(soundID);
	if (!sound.isNull())
	{
		return sound->mSoundData.m3D;
	}
	std::stringstream msg("");
	msg<<"AudioSubsystem::is3DSound - Sound with id "<<soundID<<" does not exist";
	throw std::exception (msg.str().c_str());
}
bool AudioSubsystem::isChannelPlaying(int channelID,const std::string& channelGroupID)
{
	ChannelPtr ch=mChannelGroupMap[channelGroupID]->getChannelObject(channelID);
	if (ch)
		return ch->isPlaying();
	return false;
}
bool AudioSubsystem::isChannelPaused(int channelID,const std::string& channelGroupID)
{
	ChannelPtr ch=mChannelGroupMap[channelGroupID]->getChannelObject(channelID);
	if (ch)
		return ch->isPaused();
	return false;
}
bool AudioSubsystem::isMusicPlaying(int channelID)
{
	return mConfigData.mMasterVolumeEnabled && mConfigData.mMusicVolumeEnabled && isChannelPlaying(channelID,SM_CHANNEL_MUSIC_GROUP);
}
bool AudioSubsystem::isSfxPlaying(int channelID)
{
	return mConfigData.mMasterVolumeEnabled && mConfigData.mSfxVolumeEnabled && isChannelPlaying(channelID,SM_CHANNEL_SFX_GROUP);
}
void AudioSubsystem::updateChannel3DAttributes(int channelID, const Ogre::Vector3& position,const Ogre::Vector3& velocity)
{
	ChannelPtr ch=mChannelGroupMap[SM_CHANNEL_MASTER_GROUP]->getChannelObject(channelID);
	if (ch.get())
		ch->set3DAttributes(position,velocity);
	else 
	{
		std::stringstream msg("");
		msg<<"AudioSubsystem::updateChannel3DAttributes- Channel at index"<<channelID<<" is NULL";
		throw std::exception (msg.str().c_str());
	}
}
void AudioSubsystem::updateChannel3DMinMaxDistance(int channelID, double minDistance, double maxDistance)
{
	ChannelPtr ch=mChannelGroupMap[SM_CHANNEL_MASTER_GROUP]->getChannelObject(channelID);
	if (ch.get())
		ch->set3DMinMaxDistance(minDistance,maxDistance);
	else 
	{
		std::stringstream msg("");
		msg<<"AudioSubsystem::updateChannel3DMinMaxDistance() - Channel at index"<<channelID<<" is NULL";
		throw std::exception (msg.str().c_str());
	}
}
int AudioSubsystem::getFrameSkip() const
{
	return mFrameSkip;
}
void AudioSubsystem::setFrameSkip(int frameSkip)
{
	mFrameSkip=frameSkip;
}
bool AudioSubsystem::setChannelVolume(int channelID,double volume, const std::string& channelGroupID=SM_CHANNEL_SFX_GROUP)
{
	ChannelPtr ch=mChannelGroupMap[channelGroupID]->getChannelObject(channelID);
	if (ch.get())
		return ch->setVolume(volume);
	else 
	{
		std::stringstream msg("");
		msg<<"AudioSubsystem::setChannelVolume() - Channel at index"<<channelID<<" is NULL";
		throw std::exception (msg.str().c_str());
	}
}
double AudioSubsystem::getChannelVolume(int channelID,const std::string& channelGroupID=SM_CHANNEL_SFX_GROUP)
{
	ChannelPtr ch=mChannelGroupMap[channelGroupID]->getChannelObject(channelID);
	if (ch.get())
	{
		return ch->getVolume();
	}
	else 
	{
		std::stringstream msg("");
		msg<<"AudioSubsystem::getChannelVolume() - Channel at index"<<channelID<<" is NULL";
		throw std::exception (msg.str().c_str());
	}
}
void AudioSubsystem::setMusicVolume(int channelID,double volume)
{
	setChannelVolume(channelID,volume,SM_CHANNEL_MUSIC_GROUP);
}
double AudioSubsystem::getMusicVolume(int channelID)
{
	return getChannelVolume(channelID,SM_CHANNEL_MUSIC_GROUP);
}
bool AudioSubsystem::createSoundImplementation(const TSoundData& soundData, FMOD::Sound*& FMODSound)
{
	bool rc = false;
	FMOD_MODE   flag = 0;
	FMOD_RESULT result;
	if(mSystem)
	{
		if(soundData.mLoop)
		{
			flag |= FMOD_LOOP_NORMAL;
		}
		if(soundData.mHardware)
		{
			flag |= FMOD_HARDWARE;
		}

		if(soundData.m3D)
		{
			flag |= FMOD_3D;
		}else{
			flag |= FMOD_2D;
		}

		std::string filename=AUDIO_RESOURCE_PATH+soundData.mFileName;
		if(soundData.mStream)
		{
			result = mSystem->createStream(filename.c_str(), flag, 0, &FMODSound);
		}else{
			//MessageBox(0,desc.fn.c_str(),"FILE",0);
			result = mSystem->createSound(filename.c_str(), flag,0, &FMODSound);
		}
		if (result==FMOD_OK)
		{
			rc=true;
		}	
		else
		{
			std::stringstream errMsg("");
			errMsg<<"Error creating FMOD Sound. Error message returned - "<<FMOD_ErrorString(result);
			Logger::getInstance()->log(errMsg.str());
				
		}
	}	
	return rc;	
}
bool AudioSubsystem::destroySoundImplementation(FMOD::Sound*& FMODSound)
{
	if (FMODSound)
	{
		return (FMODSound->release()==FMOD_OK);
	}
	return false;
}
//------------------------------
// Resource manager methods
//------------------------------	
SoundPtr AudioSubsystem::load(const Ogre::String &name, const Ogre::String &group)
{
	SoundPtr snd = getByName(name);

	if (snd.isNull())
		snd= create(name, group);

	snd->load();
	return snd;
}
bool AudioSubsystem::isLoaded(const Ogre::String& soundName)
{
	SoundPtr snd = getByName(soundName);
	return (!snd.isNull() && snd->isLoaded());
}
Ogre::Resource* AudioSubsystem::createImpl(const Ogre::String &name, Ogre::ResourceHandle handle, 
											const Ogre::String &group, bool isManual, Ogre::ManualResourceLoader *loader, 
											const Ogre::NameValuePairList *createParams)
{
	return new Sound(this, name, handle, group, isManual, loader);
}

void AudioSubsystem::parseScript(Ogre::DataStreamPtr& stream, const Ogre::String& groupName)
{

	AudioScriptLoader audioScriptLoader(shared_from_this());
	audioScriptLoader.parseScript(stream,groupName);
}