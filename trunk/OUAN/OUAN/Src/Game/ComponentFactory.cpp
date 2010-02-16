#include "ComponentFactory.h"
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

//[TODO: Uncomment!!]

//ComponentPtr ComponentFactory::createOgreComponent(TObjectParameters params,GameObjectPtr gameObject,RenderSubsystemPtr renderSubsystem)
//{
//	//Look out for possible specializations (something such as "LightOgreComponent", for instance)
//	OgreComponentPtr ogreComponent= OgreComponentPtr(new OgreComponent()); 
//	Ogre::Entity entity=renderSubsystem->getSceneManager()->createEntity(params.name, params.meshfile);
//	entity->setCastShadows(params.castShadows);
//	entity->setMaterialName(...)
//	ogreComponent->setEntity(entity);
//	
//	Ogre::SceneNode node = renderSubsystem->getSceneManager()->getRootSceneNode()->createChildSceneNode(gameObject->getId());
//	node->setPosition(params.position)
//	node->attachObject(entity);
//	ogreComponent->setSceneNode(node);
//
//	//remaining Ogre-related inits
//
//	//[TODO] Subscribe to events triggered by the gameObject (which, in return, may have been triggered as a response
//	// to some other component/game object event)
//	// DO NOT mistake them for input events!!
//
//	ogreComponent->setParent(gameObject);	
//	gameObject->addComponent(ogreComponent);  
//}