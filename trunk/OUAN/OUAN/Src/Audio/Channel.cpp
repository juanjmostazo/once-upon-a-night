#include "Channel.h"
#include "AudioDefs.h"
using namespace OUAN;
//--- CHANNEL DEFINITIONS

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
		mChannel->set3DMinMaxDistance(static_cast<float>(minDistance),static_cast<float>(maxDistance));
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
	bool isPlaying;
	return mChannel && (mChannel->isPlaying(&isPlaying)==FMOD_OK) && isPlaying;
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

//--- CHANNEL GROUP DEFINITIONS

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
	if (index>=0 && (unsigned int)index<mChannels.size())	
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
ChannelPtr ChannelGroup::getChannelObject(int index)
{
	if (!mChannels.empty() && index>=0 && (unsigned int)index<mChannels.size())
		return mChannels[index];
	return ChannelPtr();
}