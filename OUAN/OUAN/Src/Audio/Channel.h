#ifndef CHANNELH_H
#define CHANNELH_H

#include <Ogre.h>
#include <fmod.hpp>
#include <boost/shared_ptr.hpp>

namespace FMOD
{
	class Channel;
	class System;
	class ChannelGroup;
}

namespace OUAN
{
	class Channel
	{
	private:
		Ogre::Vector3 mPosition; //replace with PositionalComponent
		Ogre::Vector3 mPrevPosition;
		FMOD::Channel* mChannel;
		bool mIsFree;
		double mTimeAlive;
		int mIndex;
	public:
		Channel(FMOD::System* system,int index);
		virtual void setPanningPosition(int pos);
		virtual void set3DAttributes (const Ogre::Vector3& position, const Ogre::Vector3& velocity=Ogre::Vector3::ZERO);
		virtual void set3DMinMaxDistance(double minDistance, double maxDistance);
		virtual bool setPaused(bool paused);
		virtual bool setChannelGroup(FMOD::ChannelGroup* channelGroup);
		virtual bool isPlaying() const;
		virtual void resetTime();
		virtual void updateTime(double elapsedTime);
		virtual double getTime() const;
		virtual void setFree(bool free);
		virtual bool isFree() const;
		virtual FMOD_CHANNELINDEX getIndex();
		virtual void setChannel(FMOD::Channel* channel);
		virtual FMOD::Channel* getChannel();
	};
	typedef boost::shared_ptr<Channel> ChannelPtr;
	typedef std::vector<ChannelPtr> TChannelVector;

	class ChannelGroup
	{
		FMOD::ChannelGroup* mChannelGroup;
		int mNumChannels;
		TChannelVector mChannels;//refactor to stl container
	public:
		ChannelGroup(FMOD::ChannelGroup* cg);
		ChannelGroup(FMOD::ChannelGroup* cg, int numChannels,FMOD::System* system,int& offset);

		virtual void setChannel(int index, FMOD::Channel* channel);
		virtual void release();
		virtual void set3DMinMaxDistance(double minDistance, double maxDistance);
		virtual void set3DAttributes(int channelIndex, const Ogre::Vector3& position, 
			const Ogre::Vector3& vel = Ogre::Vector3::ZERO);
		virtual bool setVolume(double volume);
		virtual bool setPitch(double pan);
		virtual bool setPaused(bool paused);
		virtual bool play (int channelIndex);
		virtual bool stop (int channelIndex);
		virtual void update(double elapsedSeconds);
		virtual double getPitch();
		virtual double getVolume();

		FMOD_CHANNELINDEX getChannelIndex(int channelIndex);
		FMOD::Channel* getChannel(int index);
		ChannelPtr getChannelObject(int index);
		int getFreeChannelIndex();
	};
}
#endif