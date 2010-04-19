#include "Utils.h"
#include <Ogre.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace OUAN;
using namespace Utils;

Random* Random::mInstance=NULL;
Random::Random()
{}
Random::~Random()
{
	if (mInstance)
	{
		delete mInstance;
		mInstance=NULL;
	}
}
Random* Random::getInstance()
{
	if (!mInstance)
	{
		mInstance = new Random();
	}
	return mInstance;
}
void Random::init(unsigned int seed)
{
	mRandEngine.seed(seed);
}
int Random::getRandomInteger(int low, int high)
{
	boost::uniform_int<> distribution(low, high);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > next(mRandEngine,distribution);
	return next();
}
double Random::getRandomDouble(double low, double high)
{
	if (fabs(low-0.0)<=DOUBLE_COMPARISON_DELTA && fabs(high-1.0)<=DOUBLE_COMPARISON_DELTA)
	{
		boost::uniform_01<> distribution;
		boost::variate_generator<boost::mt19937&, boost::uniform_01<> > next(mRandEngine,distribution);
		return next();
	}
	else
	{
		boost::uniform_real<> distribution(low,high);
		boost::variate_generator<boost::mt19937&, boost::uniform_real<> > next(mRandEngine,distribution);
		return next();
	}
}

void OUAN::Utils::scriptLog (const std::string& logMsg)
{
	Ogre::LogManager::getSingletonPtr()->logMessage("LUA: "+logMsg);
}
int OUAN::Utils::parseInt(std::string& strValue)
{
	unsigned int hexValue=0;
	try
	{
		if (!strValue.empty())
		{
			std::stringstream in(strValue);			
			in >> std::hex>>hexValue;
		}
		else throw std::exception();
	}
	catch (const std::exception&)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("Couldn't parse string to an hex value: string was empty");
	}
	return static_cast<int>(hexValue);
}