#include "JuliaManager.h"

using namespace OUAN;

JuliaManager* JuliaManager::mInstance = 0;

JuliaManager::JuliaManager()
{
	mLastGlobalReal = -1;
	mLastGlobalImag = -1;
	mLastGlobalTheta = -1;
}

JuliaManager::~JuliaManager()
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = 0;
	}
}

JuliaManager* JuliaManager::getInstance()
{
	if (!mInstance)
	{
		mInstance = new JuliaManager();
	}

	return mInstance;
}

Julia JuliaManager::getJulia(double globalReal, double globalImag, double globalTheta)
{
	if (globalReal != mLastGlobalReal || 
		globalImag != mLastGlobalImag || 
		globalTheta != mLastGlobalTheta)
	{
		Ogre::LogManager::getSingleton().logMessage("[Julia MANAGER] Re-Setting julia");

		Julia julia((float)globalReal, (float)globalImag, (float)globalTheta);
		
		mJulia = julia;
		mLastGlobalReal = globalReal;
		mLastGlobalImag = globalImag;
		mLastGlobalTheta = globalTheta;
	}

	return mJulia;
}