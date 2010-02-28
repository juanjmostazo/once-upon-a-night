#include "SoundSubsystem.h"
#include <fmod_errors.h>
#include <algorithm>

using namespace Ogre;
using namespace OUAN;

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
Channel::Channel(FMOD::System* system,int index)
{
	mIsFree=true;
	mTimeAlive=0;
	mIndex = index;
	if(system->getChannel(mIndex,&mChannel) == FMOD_OK)
	{
	}
}

void Channel::set3DMinMaxDistance(double minDistance, double maxDistance)
{
	if (mChannel)
	{
		mChannel->set3DMinMaxDistance(minDistance,maxDistance);
	}
}
bool Channel::setChannelGroup(FMOD::ChannelGroup* channelGroup)
{
	return mChannel && mChannel->setChannelGroup(channelGroup)==FMOD_OK;
}
void Channel::setPanningPosition(int pos)
{
	if (mChannel)
	{
		mChannel->setPosition(pos,FMOD_TIMEUNIT_MS);
	}
}
bool Channel::isPlaying() const
{
	return mChannel && mChannel->isPlaying(NULL);
}
void Channel::setChannel(FMOD::Channel* channel)
{
	mChannel=channel;
}
bool Channel::setPaused(bool paused)
{
	return mChannel && mChannel->setPaused(paused)==FMOD_OK;
}
void Channel::resetTime()
{
	mTimeAlive=0.0;
}
void Channel::updateTime(double elapsedTime)
{
	mTimeAlive+=elapsedTime;
}
double Channel::getTime() const
{
	return mTimeAlive;
}
void Channel::set3DAttributes(const Ogre::Vector3& position, const Ogre::Vector3& velocity/* =Ogre::Vector3::ZERO */)
{
	FMOD_VECTOR pos = FMODHelper::toFMODVec(position);
	FMOD_VECTOR vel = FMODHelper::toFMODVec(velocity);
	if (mChannel)
		mChannel->set3DAttributes(&pos,&vel);
}
void Channel::setFree(bool free)
{
	mIsFree=free;
}
bool Channel::isFree() const
{
	return mIsFree;
}
FMOD_CHANNELINDEX Channel::getIndex(){
	return (FMOD_CHANNELINDEX)mIndex;
}

FMOD::Channel* Channel::getChannel()
{
	return mChannel;
}

ChannelGroup::ChannelGroup(FMOD::ChannelGroup* cg)
{
	mChannelGroup = cg;
	mNumChannels=-1;
}
FMOD_CHANNELINDEX ChannelGroup::getChannelIndex(int channelIndex)
{
	return mChannels[channelIndex]->getIndex();
}

ChannelGroup::ChannelGroup(FMOD::ChannelGroup* cg,
	int nc,FMOD::System* system,int& offset)
{
	mChannelGroup = cg;
	mNumChannels = nc;
	mChannels.clear();
	mChannels.assign(mNumChannels,ChannelPtr());
	for(int i=0; i<mNumChannels; i++)
	{
		mChannels[i] = ChannelPtr(new Channel(system,offset+i));
	}
	offset+=mNumChannels;
}
void ChannelGroup::release()
{
	if(mChannelGroup)
	{
		mChannelGroup->release();
	}

}
void ChannelGroup::setChannel(int index,
								FMOD::Channel* channel)
{
	mChannels[index]->setChannel(channel);
}
void ChannelGroup::set3DMinMaxDistance(double minDistance,
										 double maxDistance)
{
	for(int i=0; i<mNumChannels; i++)
	{
		mChannels[i]->set3DMinMaxDistance(minDistance,maxDistance);
	}
}
void ChannelGroup::set3DAttributes(int index,
									 const Ogre::Vector3& pos,
									 const Ogre::Vector3& vel)
{
	mChannels[index]->set3DAttributes(pos,vel);
}
bool ChannelGroup::play(int index)
{
	bool rc = false;
	if(mChannels[index]->setChannelGroup(mChannelGroup))
	{
		mChannels[index]->setPaused(false);
		mChannels[index]->setPanningPosition(0);
		rc = true;
	}
	return rc;
}
bool ChannelGroup::stop (int channelIndex)
{
	bool rc=false;
	FMOD::Channel* channel=getChannel(channelIndex);
	if (channel)
	{
		rc=(channel->stop()==FMOD_OK);
		mChannels[channelIndex]->setFree(true);
	}
	return rc;
}
void ChannelGroup::update(double dt)
{
	for(int i=0; i<mNumChannels; i++)
	{
		if(mChannels[i]->isPlaying())
		{
			mChannels[i]->setFree(false);
			mChannels[i]->updateTime(dt);
		}else{
			mChannels[i]->setFree(true);
		}
	}
}
bool ChannelGroup::setVolume(double val)
{
	return mChannelGroup && mChannelGroup->setVolume(val)==FMOD_OK;
}
bool ChannelGroup::setPitch(double val)
{
	return mChannelGroup && mChannelGroup->setPitch(val)==FMOD_OK;
}
bool ChannelGroup::setPaused(bool val)
{
	return mChannelGroup && mChannelGroup->setPaused(val)==FMOD_OK;
}
FMOD::Channel* ChannelGroup::getChannel(int index)
{
	if (index>=0 && index<mChannels.size())
	 return mChannels[index]->getChannel();
	return NULL;
}


int ChannelGroup::getFreeChannelIndex()
{
	int rc = -1;
	float oldest = -1;
	//first look to see if there is a free channel
	for(int i=0; i<mNumChannels && rc==-1; i++)
	{
		if(mChannels[i]->isFree())
		{
			rc = i;
		}
	}

	if(rc==-1)
	{
		for(int i=0; i<mNumChannels; i++)
		{
			float time = mChannels[i]->getTime();
			if(time > oldest)
			{
				oldest = time;
				rc = i;
			}
		}
	}
	//we have found the oldest, now reset the time it has been alive.
	if(rc!=-1)
	{
		mChannels[rc]->setFree(true);
		mChannels[rc]->resetTime();
	}

	return rc;
}
double ChannelGroup::getVolume()
{
	float val = 1.0;
	if(mChannelGroup)
	{
		mChannelGroup->getVolume(&val);
	}
	return val;
}

double ChannelGroup::getPitch()
{
	float val = 1.0;
	if(mChannelGroup)
	{
		mChannelGroup->getPitch(&val);
	}
	return val;
}

SoundSubsystem::SoundSubsystem()
{
	mSystem=NULL;	
}
SoundSubsystem::~SoundSubsystem()
{
}

void SoundSubsystem::cleanUp()
{
	for(TSoundMapIterator i=mSoundMap.begin();i!=mSoundMap.end(); i++)
	{
		(i->second)->mFMODSound->release();
	}
	mSoundMap.clear();
	for(TChannelGroupMap::iterator i=mChannelGroupMap.begin();
		i!=mChannelGroupMap.end(); i++)
	{
		(i->second)->release();
	}
	mLastMusic = "";
	mChannelGroupMap.clear();
	mSystem->close();
	mSystem->release();
}
bool SoundSubsystem::init(TSoundSubsystemConfigData& desc)
{
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
	}
	return rc;
}
void SoundSubsystem::set3DMinMaxDistance(const std::string& channelID,	
									   double minDistance,
									   double maxDistance)
{
	if(mChannelGroupMap.find( channelID ) != mChannelGroupMap.end())
	{
		mChannelGroupMap[channelID]->set3DMinMaxDistance(minDistance,
			maxDistance);

	}
}


bool SoundSubsystem::addSound(const std::string& soundID,
							const std::string& sound,
							const std::string& channelID,
							int soundFlag)
{
	TSoundData sndData;
	sndData.mId=soundID;
	sndData.mFileName=sound;
	sndData.mChannelGroupID= channelID;
	sndData.mLoop=sndData.mStream=sndData.m3D=sndData.mHardware=false;

	if(soundFlag&SOUND_FLAG_LOOP)
	{
		sndData.mLoop=true;
	}
	if(soundFlag&SOUND_FLAG_HARDWARE)
	{
		sndData.mHardware=true;
	}
	if(soundFlag&SOUND_FLAG_3D)
	{
		sndData.m3D=true;
	}
	if(soundFlag&SOUND_FLAG_STREAM)
	{
		sndData.mStream=true;
	}

	return addSound(sndData);
}

bool SoundSubsystem::addSound(const TSoundData& desc)
{
	bool rc = false;
	FMOD_MODE   flag = 0;
	FMOD_RESULT result;
	if(mSystem)
	{
		if(desc.mLoop)
		{
			flag |= FMOD_LOOP_NORMAL;
		}
		if(desc.mHardware)
		{
			flag |= FMOD_HARDWARE;
		}

		if(desc.m3D)
		{
			flag |= FMOD_3D;
		}else{
			flag |= FMOD_2D;
		}
		//m_logFile.push_back("AddSound" + desc.id + " fn: " + desc.fn);
		FMOD::Sound* soundPtr;
		if(desc.mStream)
		{
			result = mSystem->createStream(desc.mFileName.c_str(), flag, 0, &soundPtr);
		}else{
			//MessageBox(0,desc.fn.c_str(),"FILE",0);
			result = mSystem->createSound(desc.mFileName.c_str(), flag,0, &soundPtr);
		}
		if (result == FMOD_OK)
		{
			rc = true;

			//m_logFile.push_back("AddSound" + desc.id + " fn: " + desc.fn + "Ok");

			SoundPtr sound(new Sound());
			sound->mChannelGroupID = desc.mChannelGroupID;
			sound->mFMODSound= soundPtr;
			mSoundMap[desc.mId] = sound;

		}
	}
	return rc;	
}



bool SoundSubsystem::setChannelGroupVolume(const std::string& id,
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
bool SoundSubsystem::setChannelGroupPitch(const std::string& id,
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
bool SoundSubsystem::pauseChannelGroup(const std::string& id,
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

bool SoundSubsystem::play3DSound(const std::string& id,
							   const Ogre::Vector3& pos,
								int& channelIndex,
							   const Ogre::Vector3& vel)
{
	bool rc = false;
	ChannelGroupPtr outChannel= ChannelGroupPtr();
	int cIndex;
	if(_playSound(id,outChannel,cIndex))
	{
		SoundPtr soundPtr = SoundPtr();
		if(mSoundMap.find(id)!=mSoundMap.end())
		{
			soundPtr = mSoundMap[id];
			std::string cgid = soundPtr->mChannelGroupID;

			mChannelGroupMap[cgid]->set3DAttributes( cIndex,pos,vel );
			mChannelGroupMap[cgid]->play( cIndex);
		}

		channelIndex=cIndex;
		rc = true;
	}
	return rc;
}
bool SoundSubsystem::playMusic(const std::string& id, int& channelIndex,
	bool overRide)
{
	bool rc = false;
	ChannelGroupPtr outChannel = ChannelGroupPtr();
	int cIndex;
	if(overRide == true || id != mLastMusic)
	{
		if(_playSound(id,outChannel,cIndex))
		{
			SoundPtr soundPtr = SoundPtr();
			if(mSoundMap.find(id)!=mSoundMap.end())
			{
				soundPtr = mSoundMap[id];
				std::string cgid = soundPtr->mChannelGroupID;

				mChannelGroupMap[cgid]->play( cIndex);

				mLastMusic= id;
			}
			channelIndex=cIndex;
			rc = true;
		}
	}
	return rc;
}


bool SoundSubsystem::playSound(const std::string& id,int& channelIndex)
{
	bool rc = false;
	ChannelGroupPtr outChannel = ChannelGroupPtr();
	int cIndex;
	if(_playSound(id,outChannel,cIndex))
	{
		SoundPtr soundPtr = SoundPtr();
		if(mSoundMap.find(id)!=mSoundMap.end())
		{
			soundPtr = mSoundMap[id];
			std::string cgid = soundPtr->mChannelGroupID;
			mChannelGroupMap[cgid]->play(cIndex);
		}
		rc = true;
		channelIndex=cIndex;
	}
	return rc;
}

bool SoundSubsystem::_playSound(const std::string& id,
							  ChannelGroupPtr outChannel,
							  int& channelIndex)
{
	SoundPtr soundPtr = SoundPtr();
	bool rc = false;
	if(mSystem)
	{
		if(mSoundMap.find(id)!=mSoundMap.end())
		{
			soundPtr = mSoundMap[id];
			std::string cgid = soundPtr->mChannelGroupID;
			if(soundPtr && mChannelGroupMap.find(cgid)!=mChannelGroupMap.end())
			{
				FMOD_RESULT hr;
				outChannel = mChannelGroupMap[cgid];

				//find a free channel.
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
							soundPtr->mFMODSound, 
							true, 
							&channel);
						outChannel->setChannel(tmp,channel);

						rc = true;
					}
				}
			}
		}
	}
	return rc;
}

void SoundSubsystem::set3DAttributes(const Ogre::Vector3& pos,
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
bool SoundSubsystem::update(double elapsedTime)
{
	bool rc = false;
	FMOD_RESULT hr;
	if(mSystem)
	{
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
				i->second->update(elapsedTime);
			}

			rc=true;
		}
	}
	return rc;
}
TSoundSubsystemConfigData SoundSubsystem::getConfigData()
{
	return mConfigData;
}
double SoundSubsystem::getChannelGroupVolume(const std::string& id)
{
	float volume = 1.0;
	if(mChannelGroupMap.find(id)!=mChannelGroupMap.end())
	{
		volume = mChannelGroupMap[id]->getVolume();
	}
	return volume;
}

double SoundSubsystem::getChannelGroupPitch(const std::string& id)
{
	double pitch = 1.0;
	if(mChannelGroupMap.find(id)!=mChannelGroupMap.end())
	{
		pitch = mChannelGroupMap[id]->getPitch();
	}
	return pitch;
}
bool SoundSubsystem::stopSound(int channelIndex)
{
	bool result=false;
	if(mSystem)
	{
		ChannelGroupPtr currentGroup;
		for (TChannelGroupMap::iterator it=mChannelGroupMap.begin();it!=mChannelGroupMap.end();++it)
		{
			currentGroup=it->second;
			FMOD::Channel* ch;
			if (ch=currentGroup->getChannel(channelIndex))
			{
				result= currentGroup->stop(channelIndex);				
				break;
			}
		}
	}
	return result;
}