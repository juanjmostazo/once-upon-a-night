#include "TransparentEntityManager.h"
#include "TransparentEntity.h"
#include "../../Loader/Configuration.h"

using namespace OUAN;
using namespace Ogre;

TransparentEntityManager::TransparentEntityManager()
{
	clear();
}

TransparentEntityManager::~TransparentEntityManager()
{
}

void TransparentEntityManager::clear()
{
	mTransparentEntities.clear();
}

void TransparentEntityManager::init()
{
	clear();
	loadConfig();
}

bool TransparentEntityManager::loadConfig()
{
	Configuration config;
	std::string value;
	bool success;

	if (config.loadFromFile(CAMERA_CFG))
	{
		config.getOption("ALPHA_BLENDING_TIME", value); 
		mAlphaBlendingTime = atof(value.c_str());

		config.getOption("MIN_ALPHA_BLENDING", value); 
		mMinAlphaBlending = atof(value.c_str());

		success = true;
	} 
	else 
	{
		Ogre::LogManager::getSingleton().logMessage(CAMERA_CFG + " COULD NOT BE LOADED!");
		success = false;
	}

	return success;
}

bool TransparentEntityManager::hasTransparentEntity(std::string name)
{
	TTransparentEntities it;

	it=mTransparentEntities.find(name);

	return it!=mTransparentEntities.end();
}

void TransparentEntityManager::add(Ogre::Entity * pEntity)
{
	if(!hasTransparentEntity(pEntity->getName()))
	{
		mTransparentEntities[pEntity->getName()].init(pEntity,mMinAlphaBlending,mAlphaBlendingTime);
		mTransparentEntities[pEntity->getName()].makeTransparent();
	}
}

void TransparentEntityManager::remove(std::string name)
{
	TTransparentEntities it;

	it=mTransparentEntities.find(name);

	if(it!=mTransparentEntities.end())
	{
		mTransparentEntities.erase(it);
	}
}

void TransparentEntityManager::update(double elapsedTime)
{
	//TTransparentEntities tit;

	//for(tit=mTransparentEntities.begin();tit!=mTransparentEntities.end();tit++)
	//{
	//	tit->second.update(elapsedTime);

	//	if(tit->second.isSolid())
	//	{
	//		remove(tit->first);
	//	}
	//}
}

void TransparentEntityManager::makeSolidEntitesNotIncluded(std::vector<Ogre::Entity*> & collisionEntities)
{
	TTransparentEntities tit;
	unsigned int i;
	bool found;

	for(tit=mTransparentEntities.begin();tit!=mTransparentEntities.end();tit++)
	{	
		found=false;
		for(i=0;i<collisionEntities.size();i++)
		{
			if(collisionEntities[i]->getName().compare(tit->first)==0)
			{
				found=true;
				break;
			}
		}

		if(!found)
		{
			tit->second.makeSolid();
		}
	}

}