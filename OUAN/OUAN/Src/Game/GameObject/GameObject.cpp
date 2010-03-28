#include "GameObject.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectPtr GameObject::Null;

GameObject::GameObject(const std::string& name,const std::string& type)
{
	mName=name;
	mType=type;
	mEnabled=true;
}

GameObject::~GameObject()
{

}

void GameObject::destroy()
{
	
}

void GameObject::update(double elapsedSeconds)
{

}

void GameObject::changeWorld(int world)
{

}

const std::string& GameObject::getName() const
{
	return mName;
}

const std::string& GameObject::getType() const
{
	return mType;
}

void GameObject::disable()
{
	Ogre::LogManager::getSingleton().logMessage("Disabling Game Object '" + mName + "'");
	mEnabled = false;
}

bool GameObject::isEnabled()
{
	return mEnabled;
}

GameWorldManagerPtr GameObject::getGameWorldManager()
{
	return mGameWorldManager;
}
void GameObject::setGameWorldManager(GameWorldManagerPtr gameWorldManager)
{
	mGameWorldManager=gameWorldManager;
}

/// Set logic component
void GameObject::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObject::getLogicComponent()
{
	return mLogicComponent;
}

void GameObject::processChangeWorld(ChangeWorldEventPtr evt)
{
	changeWorld(evt->getNewWorld());
}
void GameObject::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
void GameObject::increaseHP(int amount)
{
	if (mEnabled && mLogicComponent.get())
	{
		if (mLogicComponent->getHealthPoints()+amount>mLogicComponent->getInitialHealthPoints())
			mLogicComponent->setHealthPoints(mLogicComponent->getInitialHealthPoints());
		else mLogicComponent->setHealthPoints(mLogicComponent->getHealthPoints()+amount);
	}
}
void GameObject::decreaseHP(int amount)
{
	std::ostringstream s;
	s.str("");
	s<<"Decreasing "<<getName()<<" health";
	Ogre::LogManager::getSingletonPtr()->logMessage(s.str());
	s.str("");
	s<<"Current HP: "<<mLogicComponent->getHealthPoints()<<" , Num. lives: "<<mLogicComponent->getNumLives();
	Ogre::LogManager::getSingletonPtr()->logMessage(s.str());
	if (mEnabled && mLogicComponent.get())
	{
		if (mLogicComponent->getHealthPoints()>0 && mLogicComponent->getNumLives()>0)
		{
			mLogicComponent->setHealthPoints(mLogicComponent->getHealthPoints()-amount<0
				?0
				:mLogicComponent->getHealthPoints()-amount);
			if (mLogicComponent->getHealthPoints()==0)
			{
				mLogicComponent->setNumLives(mLogicComponent->getNumLives()-1);
				if (mLogicComponent->getNumLives()==0)
				{
					mGameWorldManager->setGameBeaten(false);
					mGameWorldManager->setGameOver(true);
				}
				else
					mLogicComponent->setHealthPoints(mLogicComponent->getInitialHealthPoints());
			}
		}
		s.str("");
		s<<"New HP: "<<mLogicComponent->getHealthPoints()<<" , New N. lives: "<<mLogicComponent->getNumLives();
		Ogre::LogManager::getSingletonPtr()->logMessage(s.str());
	}
}

//-------------------------------------------------------

TGameObjectParameters::TGameObjectParameters()
{
	this->name="";
	this->dreamsName="";
	this->nightmaresName="";
}

TGameObjectParameters::~TGameObjectParameters()
{

}

