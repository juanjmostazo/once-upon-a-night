#ifndef AUDIODEFSH_H
#define AUDIODEFSH_H

#include <windows.h>
#include <fmod.hpp>
#include <Ogre.h>

#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

namespace OUAN
{
	//Channel groups names
	const std::string SM_CHANNEL_MASTER_GROUP		=	"MasterGroup";
	const std::string SM_CHANNEL_MUSIC_GROUP		=	"MusicGroup";
	const std::string SM_CHANNEL_SFX_GROUP			=	"SFXGroup";	

	//Audio resources path
	const std::string SOUND_RESOURCES_PATH="../../Resources/Music/";

	//Sound vector size info
	const int INITIAL_VECTOR_SIZE=100;
	const int INCREASE_VECTOR_SIZE=20;

	//FMOD defaut values for 3D Audio
	const double DOPPLER_SCALE=0.0;
	const double DISTANCE_FACTOR=10;
	const double ROLLOFF_SCALE= 1.0;

	//Forwarded declarations and typedefs
	class AudioSubsystem;
	typedef boost::shared_ptr<AudioSubsystem> AudioSubsystemPtr;

	class Sound;
	typedef boost::shared_ptr<Sound> SoundPtr;

	typedef std::map<std::string,SoundPtr>   TSoundMap;
	typedef TSoundMap::iterator  TSoundMapIterator;

	class Channel;
	typedef boost::shared_ptr<Channel> ChannelPtr;
	typedef std::vector<ChannelPtr> TChannelVector;

	class ChannelGroup;
	typedef boost::shared_ptr<ChannelGroup> ChannelGroupPtr;
	typedef std::map<std::string,ChannelGroupPtr>	TChannelGroupMap;

	//Vector conversion auxiliary functions
	struct FMODHelper
	{
		static FMOD_VECTOR toFMODVec(const Ogre::Vector3& vec);
		static Ogre::Vector3 toOgreVec3 (const FMOD_VECTOR& vec);
	};

	//Sound type flags
	typedef enum{
		SOUND_FLAG_LOOP		= 0x1,
		SOUND_FLAG_HARDWARE	= 0x2,
		SOUND_FLAG_3D		= 0x4,
		SOUND_FLAG_STREAM	= 0x8
	} TSoundFlag;

}
#endif