#include "OUAN_Precompiled.h"
#include "Utils.h"
#include "Logger.h"

using namespace OUAN;
using namespace Utils;

Random* Random::mInstance=NULL;

Random::Random()
{

}

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
	Logger::getInstance()->log("LUA: "+logMsg);
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
		Logger::getInstance()->log("Couldn't parse string to an hex value: string was empty");
	}
	return static_cast<int>(hexValue);
}

Ogre::Vector3 OUAN::Utils::getNodeWorldPosition(Ogre::Entity* entity, Ogre::Node* node)
{
	Ogre::Vector3 worldPos= node->_getDerivedPosition();

	//multiply with the parent derived transformation
	Ogre::Node* pParentNode = entity->getParentNode();
	Ogre::SceneNode* pSceneNode = entity->getParentSceneNode();
	Ogre::TagPoint* tp=NULL;
	while (pParentNode)
	{
		//process the current i_Node
		if (pParentNode != pSceneNode && (tp=dynamic_cast<Ogre::TagPoint*>(pParentNode)))
		{
			//this is a tag point (a connection point between 2 entities). which means it has a parent i_Node to be processed
			worldPos = tp->_getFullLocalTransform()*worldPos;
			pParentNode = tp->getParentEntity()->getParentNode();
		}
		else
		{
			//this is the scene i_Node meaning this is the last i_Node to process
			worldPos = pParentNode->_getFullTransform() * worldPos;
			break;
		}
	}
	return worldPos;
}

Ogre::Quaternion OUAN::Utils::getNodeWorldOrientation(Ogre::Entity* ent, Ogre::Node* node)
{
	Ogre::Quaternion worldOrient = node->_getDerivedOrientation();

	//multiply with the parent derived transformation
	Ogre::Node* pParentNode = ent->getParentNode();
	Ogre::SceneNode* pSceneNode = ent->getParentSceneNode();
	Ogre::TagPoint* tp=NULL;
	while (pParentNode)
	{
		//process the current i_Node
		if (pParentNode != pSceneNode && (tp=dynamic_cast<Ogre::TagPoint*>(pParentNode)))
		{
			worldOrient= tp->_getDerivedOrientation() * worldOrient;
			pParentNode = tp->getParentEntity()->getParentNode();
		}
		else
		{
			//this is the scene i_Node meaning this is the last i_Node to process
			worldOrient = pParentNode->_getDerivedOrientation() * worldOrient;
			break;
		}
	}
	return worldOrient;
}

std::string OUAN::Utils::toString(double doubleValue)
{
	std::ostringstream outStr;
	outStr.str("");
	outStr<<doubleValue;
	return outStr.str();
}

std::string OUAN::Utils::toString(float floatValue)
{
	std::ostringstream outStr;
	outStr.str("");
	outStr<<floatValue;
	return outStr.str();
}

std::string OUAN::Utils::toString(long longValue)
{
	std::ostringstream outStr;
	outStr.str("");
	outStr<<longValue;
	return outStr.str();
}

std::string OUAN::Utils::toString(int intValue)
{
	std::ostringstream outStr;
	outStr.str("");
	outStr<<intValue;
	return outStr.str();
}

std::string OUAN::Utils::toString(char charValue)
{
	std::ostringstream outStr;
	outStr.str("");
	outStr<<charValue;
	return outStr.str();
}

std::string OUAN::Utils::toString(bool boolValue)
{
	std::ostringstream outStr;
	outStr.str("");
	outStr<<boolValue;
	return outStr.str();
}