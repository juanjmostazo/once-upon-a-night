#ifndef COMPONENTFACTORYH_H
#define COMPONENTFACTORYH_H
#include "../OUAN.h"

namespace OUAN
{
	/// Class in charge for
	/// creating components
	class ComponentFactory
	{
	private:
		/// the factory instance
		static ComponentFactory* mInstance;
		/// Default constructor
		ComponentFactory(){}
		~ComponentFactory(){delete mInstance;}
	public:
		///return instance of the factory
		///@return factory's instance
		static ComponentFactory* getInstance();

		///create and return an void ogre component, to initialise a field use get/set
		/// @param gameObject the component's parent object
		/// @return pointer to the newly created Ogre component instance
		OgreComponentPtr ComponentFactory::createOgreComponent(GameObjectPtr gameObject);
		
		
		//create and return a physics component
		//ComponentPtr createPhysicsComponent(TObjectParameters,GameObjectPtr,PhysicsSubsystemPtr);
		//[TODO: Others]
	};
}

#endif