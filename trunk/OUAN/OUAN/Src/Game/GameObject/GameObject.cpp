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
void GameObject::enable()
{
	Ogre::LogManager::getSingleton().logMessage("Enabling Game Object '" + mName + "'");
	mEnabled = true;
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


void GameObject::processChangeWorld(ChangeWorldEventPtr evt)
{
	changeWorld(evt->getNewWorld());
}


void GameObject::processCollision(GameObjectPtr pGameObject)
{

}


void GameObject::processEnterTrigger(GameObjectPtr pGameObject)
{

}

void GameObject::processExitTrigger(GameObjectPtr pGameObject)
{

}
void GameObject::processAnimationEnded(const std::string animationName)
{

}
void GameObject::updateLogic(double elapsedSeconds)
{

}

bool GameObject::hasPositionalComponent() const
{
	return false;
}
RenderComponentPositionalPtr GameObject::getPositionalComponent() const
{
	return RenderComponentPositionalPtr();
}

bool GameObject::hasPhysicsComponent() const
{
	return false;
}
PhysicsComponentPtr GameObject::getPhysicsComponent() const
{
	return PhysicsComponentPtr();
}

bool GameObject::hasRenderComponentEntity() const
{
	return false;
}
RenderComponentEntityPtr GameObject::getEntityComponent() const
{
	return RenderComponentEntityPtr();
}

double GameObject::computeDistanceTo(GameObjectPtr other) const
{
	if (hasPositionalComponent() && other->hasPositionalComponent())
	{
		return getPositionalComponent()->computeDistanceTo(other->getPositionalComponent());
	}
	return -1;
}
void GameObject::setAttack(const std::string& newAttack)
{

}
void GameObject::beginAttack()
{

}
void GameObject::switchOff()
{

}
std::string GameObject::translateWeaponMode(TWeaponMode weaponmode)
{
	return "";
}
std::string GameObject::getDefaultAttack()
{
	return "";
}
void GameObject::activate()
{

}
bool GameObject::canBeActivated() const
{
	return false;
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

