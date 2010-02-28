#ifndef SOUNDSUBSYSTEMH_H
#define SOUNDSUBSYSTEMH_H

#include <fmod.hpp>
#include <Ogre.h>

#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>
#include <boost/array.hpp>



namespace OUAN
{
	class SoundSubsystem;
	typedef boost::shared_ptr<SoundSubsystem> SoundSubsystemPtr;

	const std::string SOUND_BASE_PATH="../media/snd/";
	//const std::string SOUND_BASE_PATH="../../Resources/media/snd/";

	struct FMODHelper
	{
		static FMOD_VECTOR toFMODVec(const Ogre::Vector3& vec);
		static Ogre::Vector3 toOgreVec3 (const FMOD_VECTOR& vec);
	};

	typedef enum{
		SOUND_FLAG_LOOP		= 0x1,
		SOUND_FLAG_HARDWARE	= 0x2,
		SOUND_FLAG_3D		= 0x4,
		SOUND_FLAG_STREAM	= 0x8
	} TSoundFlag;


		const int INITIAL_VECTOR_SIZE=100;
		const int INCREASE_VECTOR_SIZE=20;

		const double DOPPLER_SCALE=0.0;
		const double DISTANCE_FACTOR=10;
		const double ROLLOFF_SCALE= 1.0;

	typedef struct  
	{
		std::string mId;
		std::string mFileName;
		std::string mChannelGroupID;
		bool mLoop;
		bool mHardware;
		bool m3D;
		bool mStream;
	}TSoundData;

	class Sound
	{
	public:
		TSoundData mSoundData;
		FMOD::Sound* mFMODSound;
		std::string mChannelGroupID;
	};

	typedef boost::shared_ptr<Sound> SoundPtr;
	typedef std::map<std::string,SoundPtr>   TSoundMap;
	typedef TSoundMap::iterator  TSoundMapIterator;
	
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
		virtual void update(double elapsedTime);
		virtual double getPitch();
		virtual double getVolume();

		FMOD_CHANNELINDEX getChannelIndex(int channelIndex);
		FMOD::Channel* getChannel(int index);
		int getFreeChannelIndex();
	};
	typedef boost::shared_ptr<ChannelGroup> ChannelGroupPtr;
	typedef std::map<std::string,ChannelGroupPtr>	TChannelGroupMap;


	//typedef std::map<std::string,ChannelGroupEx*>	TChannelGroupMap;
	const std::string SM_CHANNEL_MASTER_GROUP		=	"MasterGroup";
	const std::string SM_CHANNEL_MUSIC_GROUP		=	"MusicGroup";
	const std::string SM_CHANNEL_SFX_GROUP			=	"SFXGroup";	

	typedef struct  
	{
		// 3D sound attributes
		double mDopplerScale;
		double mDistanceFactor;
		double mRollOffScale;

		// Global sound controls
		double mMasterVolume;
		double mMasterPitch;
		bool mMasterVolumeEnabled;
		int mNumChannels;

		// Audio effects sound controls
		double mSfxVolume;
		double mSfxPitch;
		bool mSfxVolumeEnabled;
		int mSfxNumChannels;

		// Music effects sound controls
		double mMusicVolume;
		double mMusicPitch;
		bool mMusicVolumeEnabled;
		int mMusicNumChannels;

	} TSoundSubsystemConfigData;

	/// Audio manager. It controls reproduction of sounds
	/// Code adapted from http://www.ogre3d.org/wiki/index.php/FMOD_SoundManager
	class SoundSubsystem
	{
	public:
		/// Default constructor
		SoundSubsystem();
		
		/// Default destructor
		virtual ~SoundSubsystem();
		
		/// Initialise subsystem
		virtual bool init(TSoundSubsystemConfigData& configData);
		void cleanUp();
		//virtual bool init(OUAN::ConfigurationPtr config);

		virtual void set3DMinMaxDistance(const std::string& channelId, double minDistance, double maxDistance);

		//virtual bool loadSounds(const std::string& soundListFile);
		
		virtual bool addSound(const TSoundData& soundData);
		virtual bool addSound(const std::string& soundID,
			const std::string& sound,
			const std::string& channelID=SM_CHANNEL_SFX_GROUP,
			int soundFlag=SOUND_FLAG_HARDWARE);

		virtual bool setChannelGroupVolume(const std::string& channelGroupID, double volume);
		virtual bool setChannelGroupPitch(const std::string& channelGroupID, double pitch);
		virtual bool pauseChannelGroup(const std::string& channelGroupID, bool overrideMute);
		//virtual bool stopChannelGroup(const std::string& channelGroupID);

		virtual bool playSound(const std::string& id, int& channelIndex);
		virtual bool play3DSound(const std::string& id, const Ogre::Vector3& position, 
			int& channelIndex,const Ogre::Vector3& velocity = Ogre::Vector3::ZERO);
		virtual bool playMusic(const std::string& id,int& channelIndex,bool override=false);

		virtual bool stopSound(int channelIndex);

		virtual void set3DAttributes(const Ogre::Vector3& position,const Ogre::Vector3& velocity,const Ogre::Vector3& forward,const Ogre::Vector3& up);
		virtual bool update(double elapsedTime);

		virtual double getChannelGroupVolume(const std::string& id);
		virtual double getChannelGroupPitch(const std::string& id);

		virtual TSoundSubsystemConfigData getConfigData();

	private:
		FMOD::System* mSystem;
		TChannelGroupMap mChannelGroupMap;

		TSoundMap mSoundMap;
		std::string mLastMusic;
	
		TSoundSubsystemConfigData mConfigData;
		TSoundSubsystemConfigData mOldConfigData;

		virtual bool _playSound(const std::string& id, ChannelGroupPtr outChannel, int& channelIndex);
	};
}
#endif 