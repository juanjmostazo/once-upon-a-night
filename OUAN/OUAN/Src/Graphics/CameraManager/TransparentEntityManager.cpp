#include "TransparentEntityManager.h"
#include "TransparentEntity.h"
#include "../../Loader/Configuration.h"

using namespace OUAN;
using namespace Ogre;

TransparentEntityManager::TransparentEntityManager()
{
	clear();
	mMinAlphaBlending=0;
	mAlphaBlendingSpeed=0;
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
		config.getOption("ALPHA_BLENDING_SPEED", value); 
		mAlphaBlendingSpeed = atof(value.c_str());

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
		Ogre::LogManager::getSingleton().logMessage("[TransparentEntityManager] adding "+pEntity->getName());
		mTransparentEntities[pEntity->getName()].reset(new TransparentEntity());
		mTransparentEntities[pEntity->getName()]->init(pEntity,mMinAlphaBlending,mAlphaBlendingSpeed);
	}
}

void TransparentEntityManager::remove(std::string name)
{
	TTransparentEntities it;

	it=mTransparentEntities.find(name);

	if(it!=mTransparentEntities.end())
	{
		mTransparentEntities.clear();
		mTransparentEntities.erase(it);
	}
}

void TransparentEntityManager::update(double elapsedTime)
{
	TTransparentEntities tit;
	unsigned int i;
	std::vector<std::string> toRemove;

	for(tit=mTransparentEntities.begin();tit!=mTransparentEntities.end();tit++)
	{
		//Ogre::LogManager::getSingleton().logMessage("update collision entity: "+tit->first);
		tit->second->update(elapsedTime);
	}

	//for(tit=mTransparentEntities.begin();tit!=mTransparentEntities.end();tit++)
	//{	
	//	if(tit->second->isSolid())
	//	{
	//		toRemove.push_back(tit->first);
	//	}
	//}
	//for(i=0;i<toRemove.size();i++)
	//{
	//	remove(toRemove[i]);
	//}

}

void TransparentEntityManager::addCurrentCollisionTransparentEntities(std::vector<Ogre::Entity*> & collisionEntities)
{
	TTransparentEntities tit,lastTit;
	unsigned int i;
	bool found;

	//Ogre::LogManager::getSingleton().logMessage("UPDATING TRANSPARENT ENTITIES");
	//Ogre::LogManager::getSingleton().logMessage("current list");
	//for(tit=mTransparentEntities.begin();tit!=mTransparentEntities.end();tit++)
	//{	
	//	Ogre::LogManager::getSingleton().logMessage(tit->first);
	//}
	//Ogre::LogManager::getSingleton().logMessage("making transparent");
	for(i=0;i<collisionEntities.size();i++)
	{
		//Ogre::LogManager::getSingleton().logMessage(collisionEntities[i]->getName());
		add(collisionEntities[i]);
		mTransparentEntities[collisionEntities[i]->getName()]->makeTransparent();
	}
	//Ogre::LogManager::getSingleton().logMessage("making solid");
	for(tit=mTransparentEntities.begin();tit!=mTransparentEntities.end();tit++)
	{	
		found=false;
		for(i=0;i<collisionEntities.size();i++)
		{
			if(collisionEntities[i]->getName().compare(Ogre::String(tit->first))==0)
			{
				found=true;
			}
		}

		if(!found)
		{
			//Ogre::LogManager::getSingleton().logMessage(tit->first);
			tit->second->makeSolid();
		}
	}

}