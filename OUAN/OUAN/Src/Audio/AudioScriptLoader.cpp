#include "OUAN_Precompiled.h"

#include "AudioScriptLoader.h"
#include "AudioDefs.h"
#include "AudioSubsystem.h"
using namespace OUAN;

void logParseError(const Ogre::String& error, const TAudioScriptContext& context)
{
	// log material name only if filename not specified
	if (context.mFileName.empty() && !context.mSound.isNull())
	{
		Logger::getInstance()->log(
			"Error in sound " + context.mSound->getName() +
			" : " + error);
	}
	else
	{
		if (!context.mSound.isNull())
		{
			Logger::getInstance()->log(
				"Error in sound " + context.mSound->getName() +
				" at line " + Ogre::StringConverter::toString(context.mLineNo) +
				" of " + context.mFileName+ ": " + error);
		}
		else
		{
			Logger::getInstance()->log(
				"Error at line " + Ogre::StringConverter::toString(context.mLineNo) +
				" of " + context.mFileName+ ": " + error);
		}
	}
}

bool parseSound(const Ogre::String& params, TAudioScriptContext& audioScriptContext, AudioSubsystemPtr audioSS)
{
	audioScriptContext.mSound=
		audioSS->create(params, audioScriptContext.mGroupName);
	audioScriptContext.mSound->mSoundData.mId=params;
	audioScriptContext.mSound->_notifyOrigin(audioScriptContext.mFileName);

	// update section
	audioScriptContext.mSection= ASS_SOUND;

	// Return TRUE because this must be followed by a {
	return true;
}
bool parseSoundFile(const Ogre::String& params, TAudioScriptContext& audioScriptContext, AudioSubsystemPtr audioSS)
{
	if (!audioScriptContext.mSound.isNull())
	{
		audioScriptContext.mSound->mSoundData.mFileName=params;
	}
	return false;
}
bool parseSoundType(const Ogre::String& params, TAudioScriptContext& audioScriptContext, AudioSubsystemPtr audioSS)
{
	if (!audioScriptContext.mSound.isNull())
	{
		if (params=="sfx")
			audioScriptContext.mSound->mSoundData.mChannelGroupID=SM_CHANNEL_SFX_GROUP;
		else if (params=="music")
			audioScriptContext.mSound->mSoundData.mChannelGroupID=SM_CHANNEL_MUSIC_GROUP;
		else
			logParseError(
			"Invalid value for \"sound_type\": must be either \"sfx\" or \"music\"",
			audioScriptContext);
	}
	return false;
}
bool parse3D(const Ogre::String& params, TAudioScriptContext& audioScriptContext, AudioSubsystemPtr audioSS)
{
	if (!audioScriptContext.mSound.isNull())
	{
		audioScriptContext.mSound->mSoundData.m3D=Ogre::StringConverter::parseBool(params);
	}
	return false;
}
bool parseLoop(const Ogre::String& params, TAudioScriptContext& audioScriptContext, AudioSubsystemPtr audioSS)
{
	if (!audioScriptContext.mSound.isNull())
	{
		audioScriptContext.mSound->mSoundData.mLoop=Ogre::StringConverter::parseBool(params);
	}
	return false;
}
bool parseStream(const Ogre::String& params, TAudioScriptContext& audioScriptContext, AudioSubsystemPtr audioSS)
{
	if (!audioScriptContext.mSound.isNull())
	{
		audioScriptContext.mSound->mSoundData.mStream=Ogre::StringConverter::parseBool(params);
	}
	return false;
}
bool parseHardware(const Ogre::String& params, TAudioScriptContext& audioScriptContext, AudioSubsystemPtr audioSS)
{
	if (!audioScriptContext.mSound.isNull())
	{
		audioScriptContext.mSound->mSoundData.mHardware=Ogre::StringConverter::parseBool(params);
	}
	return false;
}
bool parseMinMaxDistance(const Ogre::String& params, TAudioScriptContext& audioScriptContext, AudioSubsystemPtr audioSS)
{
	Ogre::StringVector vecparams = Ogre::StringUtil::split(params, " \t");
	if (vecparams.size()!=2)
	{
		logParseError(
			"Wrong number of params: min_max_distance must be followed by two real values",
			audioScriptContext);
	}
	if (!audioScriptContext.mSound.isNull())
	{
		audioScriptContext.mSound->mSoundData.minDistance=Ogre::StringConverter::parseReal(vecparams[0]);
		audioScriptContext.mSound->mSoundData.maxDistance=Ogre::StringConverter::parseReal(vecparams[1]);
	}
	return false;
}
AudioScriptLoader::AudioScriptLoader(AudioSubsystemPtr audioSS)
{
	mRootParsers.insert(TAudioScriptAttribParserList::value_type("sound",(FP_AUDIOSCRIPT_ATTRIB_PARSER)parseSound));

	mSoundParsers.insert(TAudioScriptAttribParserList::value_type("sound_file",(FP_AUDIOSCRIPT_ATTRIB_PARSER)parseSoundFile));
	mSoundParsers.insert(TAudioScriptAttribParserList::value_type("sound_type",(FP_AUDIOSCRIPT_ATTRIB_PARSER)parseSoundType));
	mSoundParsers.insert(TAudioScriptAttribParserList::value_type("3D",(FP_AUDIOSCRIPT_ATTRIB_PARSER)parse3D));
	mSoundParsers.insert(TAudioScriptAttribParserList::value_type("loop",(FP_AUDIOSCRIPT_ATTRIB_PARSER)parseLoop));
	mSoundParsers.insert(TAudioScriptAttribParserList::value_type("stream",(FP_AUDIOSCRIPT_ATTRIB_PARSER)parseStream));
	mSoundParsers.insert(TAudioScriptAttribParserList::value_type("hardware",(FP_AUDIOSCRIPT_ATTRIB_PARSER)parseHardware));
	mSoundParsers.insert(TAudioScriptAttribParserList::value_type("min_max_distance",(FP_AUDIOSCRIPT_ATTRIB_PARSER)parseMinMaxDistance));
	
	mScriptContext.mSection= ASS_NONE;
	mScriptContext.mSound.setNull();
	mScriptContext.mLineNo = 0;
	mScriptContext.mFileName.clear();
	mScriptContext.mGroupName.clear();

	mAudioSS=audioSS;

}
AudioScriptLoader::~AudioScriptLoader()
{
	mRootParsers.clear();
	mSoundParsers.clear();
	if (!mScriptContext.mSound.isNull())	
		mScriptContext.mSound.setNull();
}
void AudioScriptLoader::parseScript(Ogre::DataStreamPtr& dataStream, const Ogre::String& groupName)
{
	Ogre::String line;
	bool nextIsOpenBrace = false;

	mScriptContext.mSection = ASS_NONE;
	mScriptContext.mSection= ASS_NONE;
	mScriptContext.mSound.setNull();
	mScriptContext.mLineNo = 0;
	mScriptContext.mFileName=dataStream->getName();
	mScriptContext.mGroupName=groupName;

	Logger::getInstance()->log("About to start parsing sound script "+dataStream->getName());

	while(!dataStream->eof())
	{
		line = dataStream->getLine();
		mScriptContext.mLineNo++;

		// DEBUG LINE
		//Logger::getInstance()->log("About to attempt line(#" +
		//	Ogre::StringConverter::toString(mScriptContext.mLineNo) + "): " + line);

		// Ignore comments & blanks
		if (!(line.length() == 0 || line.substr(0,2) == "//"))
		{
			if (nextIsOpenBrace)
			{
				// NB, parser will have changed context already
				if (line != "{")
				{
					logParseError("Expecting '{' but got " +
						line + " instead.", mScriptContext);
				}
				nextIsOpenBrace = false;
			}
			else
			{
				nextIsOpenBrace = parseLine(line);
			}

		}
	}

	// Check all braces were closed
	if (mScriptContext.mSection != ASS_NONE)
	{
		logParseError("Unexpected end of file.", mScriptContext);
	}

	// Make sure we invalidate our context shared pointer (don't wanna hold on)
	mScriptContext.mSound.setNull();
}
bool AudioScriptLoader::parseLine(Ogre::String& line)
{
	switch(mScriptContext.mSection)
	{
	case ASS_NONE:
		if (line == "}")
		{
			logParseError("Unexpected terminating brace.", mScriptContext);
			return false;
		}
		else
		{
			// find & invoke a parser
			return invokeParser(line, mRootParsers);
		}
		break;
	case ASS_SOUND:
		if (line == "}")
		{

			mScriptContext.mSection = ASS_NONE;
			mScriptContext.mSound.setNull();
		}
		else
		{
			// find & invoke a parser
			return invokeParser(line, mSoundParsers);
		}
		break;
	}
	return false;
}
bool AudioScriptLoader::invokeParser(String& line, TAudioScriptAttribParserList& parsers)
{
	// First, split line on first divisor only
	Ogre::StringVector splitCmd(Ogre::StringUtil::split(line, " \t", 1));

	// Find attribute parser
	TAudioScriptAttribParserList::iterator iparser = parsers.find(splitCmd[0]);
	if (iparser == parsers.end())
	{
		// BAD command. BAD!
		logParseError("Unrecognised command: " + splitCmd[0], mScriptContext);
		return false;
	}
	else
	{
		Ogre::String cmd;
		if(splitCmd.size() >= 2)
			cmd = splitCmd[1];
		// Use parser, make sure we have 2 params before using splitCmd[1]
		return iparser->second( cmd, mScriptContext,mAudioSS );
	}
}