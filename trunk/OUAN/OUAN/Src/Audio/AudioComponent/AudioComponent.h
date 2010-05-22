#ifndef AUDIOCOMPONENTH_H
#define AUDIOCOMPONENTH_H

#include "../../Component/Component.h"

namespace OUAN{
	/// The keys represent sound identifiers, whereas the values
	/// will be the channel indexes.
	typedef std::map<std::string, int> TAudioComponentMap;

	class AudioSubsystem;
	typedef boost::shared_ptr<AudioSubsystem> AudioSubsystemPtr;

	class AudioComponent: public Component
	{
	public:
		AudioComponent(AudioSubsystemPtr audioSS);
		~AudioComponent();

		void update(long elapsedTime);
		void playSound(const std::string& soundID);
		void stopSound(const std::string& soundID);
		void setPauseSound(const std::string& soundID,bool pause);

		void setSounds(const TAudioComponentMap& sounds);
	private:
		TAudioComponentMap mSounds;
		AudioSubsystemPtr mAudioSS;
	};
}
#endif