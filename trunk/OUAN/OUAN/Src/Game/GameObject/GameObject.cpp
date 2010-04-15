#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectPtr GameObject::Null;

GameObject::GameObject(const std::string& name,const std::string& type)
{
	mName=name;
	mType=type;
	reset();
}

GameObject::~GameObject()
{

}

void GameObject::destroy()
{
	
}

void GameObject::reset()
{
	mEnabled=true;
	mNumUpdates=0;
}

bool GameObject::isFirstUpdate()
{
	return mNumUpdates <= 1;
}

void GameObject::update(double elapsedSeconds)
{
	mNumUpdates++;
}

void GameObject::changeWorld(int world)
{

}

const std::string& GameObject::getName()
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
	
	if (mEnabled && mLogicComponent.get())
	{
		if (mLogicComponent->getHealthPoints()>0 && mLogicComponent->getNumLives()>0)
		{
			mLogicComponent->setHealthPoints(mLogicComponent->getHealthPoints()-amount<0
				?0
				:mLogicComponent->getHealthPoints()-amount);
			if (mLogicComponent->getHealthPoints()==0)
			{
				decreaseLives();				
			}
		}
	}
}
void GameObject::increaseLives(int amount)
{
	getLogicComponent()->setNumLives(getLogicComponent()->getNumLives()+amount);
}
void GameObject::decreaseLives(int amount)
{
	getLogicComponent()->setNumLives(getLogicComponent()->getNumLives()-amount);
	if (getLogicComponent()->getNumLives()<=0)
	{
		getLogicComponent()->setNumLives(0);//safety assignment.
		die();
	}
	else
		loseLife();
}
void GameObject::die()
{
	//TODO: ADDITIONAL STUFF (Or redefine in subclass for type-specific behaviour)
	disable();
}
bool GameObject::hasPositionalComponent() const
{
	return false;
}
RenderComponentPositionalPtr GameObject::getPositionalComponent() const
{
	return RenderComponentPositionalPtr();
}
void GameObject::loseLife()
{
	mLogicComponent->setHealthPoints(mLogicComponent->getInitialHealthPoints());
}
int GameObject::getNumLives() const
{
	if (mLogicComponent)
		return mLogicComponent->getNumLives();
	return -1;
}
int GameObject::getHealthPoints() const
{
	if (mLogicComponent)
		return mLogicComponent->getHealthPoints();
	return -1;
}

int GameObject::getMaximumHealthPoints() const
{
	if (mLogicComponent)
		return mLogicComponent->getHealthPoints();
	return -1;
}

int GameObject::getLineOfSight() const
{
	if (mLogicComponent)
		return mLogicComponent->getLineOfSight();
	return -1;
}
double GameObject::computeDistanceTo(GameObjectPtr other) const
{
	if (hasPositionalComponent() && other->hasPositionalComponent())
	{
		return getPositionalComponent()->computeDistanceTo(other->getPositionalComponent());
	}
	return -1;
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

