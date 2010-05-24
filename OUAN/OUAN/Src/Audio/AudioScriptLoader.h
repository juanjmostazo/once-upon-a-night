#ifndef AUDIOSCRIPTLOADERH_H
#define AUDIOSCRIPTLOADERH_H
#include <boost/shared_ptr.hpp>
#include <Ogre.h>
#include "Sound.h"
namespace OUAN
{
	class AudioSubsystem;
	typedef boost::shared_ptr<AudioSubsystem> AudioSubsystemPtr;

	enum TAudioScriptSection
	{
		ASS_NONE,
		ASS_SOUND
	};
	struct TAudioScriptContext
	{
		TAudioScriptSection mSection;
		Ogre::String mGroupName;
		SoundPtr mSound;
		unsigned int mLineNo;
		Ogre::String mFileName;
	};
	typedef bool (*FP_AUDIOSCRIPT_ATTRIB_PARSER)(const Ogre::String& attribute, TAudioScriptContext& audioScriptContext, AudioSubsystemPtr audioSS);
	typedef std::map<Ogre::String, FP_AUDIOSCRIPT_ATTRIB_PARSER> TAudioScriptAttribParserList;

	class AudioScriptLoader
	{

		TAudioScriptContext mScriptContext;
		TAudioScriptAttribParserList mRootParsers;
		TAudioScriptAttribParserList mSoundParsers;
		
	public:
		AudioScriptLoader(AudioSubsystemPtr audioSS);
		virtual ~AudioScriptLoader();

		void parseScript(Ogre::DataStreamPtr& dataStream, const Ogre::String& groupName);
		bool parseLine(Ogre::String& line);
		bool invokeParser(Ogre::String& line, TAudioScriptAttribParserList& parsers);

		AudioSubsystemPtr mAudioSS;


	};
}
#endif