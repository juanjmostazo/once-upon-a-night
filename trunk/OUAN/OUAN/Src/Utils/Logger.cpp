#include "Logger.h"
#include "../Loader/Configuration.h"

using namespace OUAN;

Logger* Logger::mInstance=NULL;

Logger::Logger() : mEnabled(false)
{
	Configuration config;
	std::string value;

	if (config.loadFromFile(LOGGER_CFG))
	{
		config.getOption("ENABLED", value);
		mEnabled = value.compare("TRUE") == 0;
	}
}

Logger::~Logger()
{
	if (mInstance)
	{
		delete mInstance;
		mInstance=NULL;
	}
}

Logger* Logger::getInstance()
{
	if (!mInstance)
	{
		mInstance = new Logger();
	}
	return mInstance;
}

void Logger::log(Ogre::String message)
{
	if (mEnabled)
	{
		Ogre::LogManager::getSingleton().logMessage(message);
	}
}