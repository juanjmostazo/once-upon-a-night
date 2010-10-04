#include "OUAN_Precompiled.h"
#include "Utils.h"
#include "Logger.h"
#include "../Graphics/RenderSubsystem.h"

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
LUATimer::LUATimer()
:mSeconds(0)
{
}
void LUATimer::reset()
{
	mSeconds=0;
}
void LUATimer::addTime(double secs)
{
	mSeconds+=secs;
}
double LUATimer::getTime()
{
	return mSeconds;
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
	outStr<<std::boolalpha<<boolValue;
	return outStr.str();
}

void OUAN::Utils::createRectangle (const TTexturedRectangleDesc& description, 
										   Ogre::Rectangle2D*& rectangle, RenderSubsystemPtr renderSS)
{
	rectangle= new Ogre::Rectangle2D(true);
	rectangle->setCorners(description.leftCorner, description.topCorner, 
		description.rightCorner, description.bottomCorner);
	rectangle->setRenderQueueGroup(description.renderQueue);
	rectangle->setBoundingBox(description.axisAlignedBox);
	// Create background material	
	rectangle->setMaterial(description.materialName);

	Ogre::SceneNode* screenNode;
	if (!renderSS->getSceneManager()->hasSceneNode(description.sceneNodeName))
	{
		Ogre::SceneNode* root = renderSS->getSceneManager()->getRootSceneNode();
		screenNode= root->createChildSceneNode(description.sceneNodeName);
	}
	else
	{
		screenNode= renderSS->getSceneManager()->getSceneNode(description.sceneNodeName);
	}
	screenNode->attachObject(rectangle);
}

void OUAN::Utils::destroyRectangle(Ogre::Rectangle2D*& rect,
	RenderSubsystemPtr renderSs)
{	
	if (rect)
	{
		std::string sceneNodeName=rect->getParentSceneNode()->getName();
		rect->detatchFromParent();
		renderSs->getSceneManager()->destroySceneNode(sceneNodeName);
		SAFEDELETE(rect);			
	}
}

void OUAN::Utils::createTexturedRectangle (const TTexturedRectangleDesc& description, 
	Ogre::Rectangle2D*& rectangle, RenderSubsystemPtr renderSS)
{
	rectangle= new Ogre::Rectangle2D(true);
	rectangle->setCorners(description.leftCorner, description.topCorner, 
		description.rightCorner, description.bottomCorner);
	rectangle->setRenderQueueGroup(description.renderQueue);
	rectangle->setBoundingBox(description.axisAlignedBox);
	// Create background material
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(description.materialName,
		description.materialGroup);
	material->getTechnique(0)->getPass(0)->createTextureUnitState();
	if (description.textureAnimation)
	{
		material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAnimatedTextureName(
			description.textureName,
			description.texAnimNumFrames,
			description.texAnimDuration);
	}
	else
		material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(description.textureName);
	if (description.alphaBlending){
		material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
	}
	material->getTechnique(0)->getPass(0)->setCullingMode(Ogre::CULL_NONE);   
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(description.depthWrite);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	if (description.alphaRejection)
	{
		material->getTechnique(0)->getPass(0)->setAlphaRejectSettings(description.alphaRejectionFunction,description.alphaRejectionValue,description.alphaToCoverage);
	}

	rectangle->setMaterial(description.materialName);

	Ogre::SceneNode* screenNode;
	if (!renderSS->getSceneManager()->hasSceneNode(description.sceneNodeName))
	{
		Ogre::SceneNode* root = renderSS->getSceneManager()->getRootSceneNode();
		screenNode= root->createChildSceneNode(description.sceneNodeName);
	}
	else
	{
		screenNode= renderSS->getSceneManager()->getSceneNode(description.sceneNodeName);
	}
	screenNode->attachObject(rectangle);
}

void OUAN::Utils::destroyTexturedRectangle(Ogre::Rectangle2D*& rect,const std::string& materialName, 
	RenderSubsystemPtr renderSs)
{
	if (Ogre::MaterialManager::getSingleton().resourceExists(materialName))
	{
		Ogre::MaterialPtr mat;
		Ogre::TextureUnitState* tex;

		mat=Ogre::MaterialManager::getSingleton().getByName(materialName);
		tex=mat->getTechnique(0)->getPass(0)->getTextureUnitState(0);
		tex->setTextureName(Ogre::String(""));
		if (rect)
		{
			std::string sceneNodeName=rect->getParentSceneNode()->getName();
			rect->detatchFromParent();
			renderSs->getSceneManager()->destroySceneNode(sceneNodeName);
			SAFEDELETE(rect);
			Ogre::MaterialManager::getSingleton().remove(materialName);
		}
	}
}

const std::string OUAN::Utils::replaceAll(const std::string& source, const std::string& replaceWhat, 
										  const std::string& replaceWithWhat)
{
	std::string result = source;
	while(1)
	{
		std::string::size_type pos = result.find(replaceWhat);
		if (pos == String::npos) break;
		result.replace(pos,replaceWhat.size(),replaceWithWhat);
	}
	return result;
}
Ogre::UTFString OUAN::Utils::convertToUTF(const Ogre::String& str)
{
	Ogre::UTFString UTFString;
	int i;
	Ogre::UTFString::code_point cp;
	for (i=0; i<(int)str.size(); ++i)
	{
		cp = str[i];
		cp &= 0xFF;
		UTFString.append(1, cp);
	}
	return UTFString;
}