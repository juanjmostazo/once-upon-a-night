#ifndef AUDIOSUBSYSTEMH_H
#define AUDIOSUBSYSTEMH_H
#include "AudioDefs.h"
#include "Sound.h"
#include "../OUAN.h"
#include "../Event/Event.h"
#include "../Event/EventManager.h"
namespace OUAN
{
	const std::string AUDIO_RESOURCE_PATH="../../Resources/Sounds/SoundFiles/";

	/// Audio manager. It controls reproduction of sounds
	class AudioScriptLoader; 
	typedef boost::shared_ptr<AudioScriptLoader> AudioScriptLoaderPtr;

	class AudioSubsystem: public Ogre::ResourceManager, public boost::enable_shared_from_this<AudioSubsystem>
	{
	protected:

		// must implement this from ResourceManager's interface
		Ogre::Resource *createImpl(const Ogre::String &name, Ogre::ResourceHandle handle, 
			const Ogre::String &group, bool isManual, Ogre::ManualResourceLoader *loader, 
			const Ogre::NameValuePairList *createParams);
	public:
		/// Default constructor
		AudioSubsystem();

		/// Default destructor
		virtual ~AudioSubsystem();

		/// Initialise subsystem
		bool init(TAudioSubsystemConfigData& configData, ApplicationPtr app);
		void cleanUp();
		// bool init(OUAN::ConfigurationPtr config);

		void set3DMinMaxDistance(const std::string& channelId, double minDistance, double maxDistance);

		// bool loadSounds(const std::string& soundListFile);

		 //bool addSound(const TSoundData& soundData);
		 //bool addSound(const std::string& soundID,
			//const std::string& sound,
			//const std::string& channelID=SM_CHANNEL_SFX_GROUP,
			//int soundFlag=SOUND_FLAG_HARDWARE);
		
		 //void removeSound(const std::string& soundID);
		 //void loadSounds(std::vector<TSoundData> soundBank);
		 //void unloadSounds();
		 SoundPtr getSound(const std::string& soundID);

		 bool is3DSound(const std::string& soundID);
		 bool isChannelPlaying(int channelID,const std::string& channelGroupID=SM_CHANNEL_SFX_GROUP);
		 void updateChannel3DAttributes(int channelID, const Ogre::Vector3& position,const Ogre::Vector3& velocity);
		 void updateChannel3DMinMaxDistance(int channelID, double minDistance, double maxDistance);

		 bool setChannelGroupVolume(const std::string& channelGroupID, double volume);
		 bool setChannelGroupPitch(const std::string& channelGroupID, double pitch);
		 bool pauseChannelGroup(const std::string& channelGroupID, bool overrideMute);
		// bool stopChannelGroup(const std::string& channelGroupID);
		 bool setChannelVolume(int channelID,double volume, const std::string& channelGroupID);
		 double getChannelVolume(int channelID, const std::string& channelGroupID);
		 void setMusicVolume(int channelID,double volume);
		 double getMusicVolume(int channelID);
		 bool isMusicPlaying(int channelID);
		
		 bool playSound(const std::string& id, int& channelIndex);
		 bool play3DSound(const std::string& id, const Ogre::Vector3& position, 
			int& channelIndex,const Ogre::Vector3& velocity = Ogre::Vector3::ZERO);
		 bool playMusic(const std::string& id,int& channelIndex,bool override=false);

		 bool stopSound(int channelIndex,const std::string& channelGroupID=SM_CHANNEL_SFX_GROUP);
		 bool stopMusic(int channelIndex);
		 bool setPause(int channelIndex, bool pause);

		 void set3DAttributes(const Ogre::Vector3& position,const Ogre::Vector3& velocity,const Ogre::Vector3& forward,const Ogre::Vector3& up);
		 bool update(double elapsedTime);

		 double getChannelGroupVolume(const std::string& id);
		 double getChannelGroupPitch(const std::string& id);

		 TAudioSubsystemConfigData getConfigData();
		 void setConfigData(const TAudioSubsystemConfigData& audioCfg);

		void saveCurrentConfigData(const std::string& configFileName=SOUND_CONFIG_FILE);

		ApplicationPtr getApplication();

		int getFrameSkip() const;
		void setFrameSkip(int frameSkip);

		virtual SoundPtr load(const Ogre::String &name, const Ogre::String &group);
		
		void parseScript(Ogre::DataStreamPtr& stream, const Ogre::String& groupName);

		bool createSoundImplementation(const TSoundData& soundData, FMOD::Sound*& FMODSound);
		bool destroySoundImplementation(FMOD::Sound*& FMODSound);

	private:
		FMOD::System* mSystem;
		TChannelGroupMap mChannelGroupMap;
		
		std::string mLastMusic;

		TAudioSubsystemConfigData mConfigData;
		TAudioSubsystemConfigData mOldConfigData;

		bool _playSound(const std::string& id, ChannelGroupPtr outChannel, int& channelIndex);

		ApplicationPtr mApp;
		
		int mFrameSkip;

		AudioScriptLoaderPtr mAudioScriptLoader;

	};
}
#endif