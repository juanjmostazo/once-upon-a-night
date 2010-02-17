#include "ComponentFactory.h"
#include "GameObject.h"
#include "OgreComponent.h"

using namespace OUAN;

ComponentFactory* ComponentFactory::mInstance=NULL;

ComponentFactory* ComponentFactory::getInstance()
{
	if (mInstance)
		return mInstance;
	else{
		mInstance=new ComponentFactory();
		return mInstance;
	}
}



OgreComponentPtr ComponentFactory::createOgreComponent(GameObjectPtr gameObject)
{

	if(!gameObject->hasComponent(OUAN::COMPONENT_NAME_OGRE))
	{
		//Create void Ogre Component, to initialise fields use get/set
		OgreComponentPtr ogreComponent = OgreComponentPtr(new OgreComponent()); 

		ogreComponent->setParent(gameObject);	
		gameObject->addComponent(COMPONENT_NAME_OGRE,ogreComponent);

		return ogreComponent;
	}
	else
	{
		//TODO: return Object's ogre component

		return OgreComponentPtr(new OgreComponent());
	}


}