#ifndef GAMEOBJECTH_H
#define GAMEOBJECTH_H
#include "../../OUAN.h"
namespace OUAN
{
	class GameObject{
	private:
		/// Entity identifier (i.e, "pc_ony")
		std::string mName;
		/// Unique instance identifier (i.e, "e_tripollo_d_0020")
		std::string mId;
		/// Component container
		TComponentContainer mComponents;

	public:
		//Constructor
		GameObject(const std::string& name, const std::string& id);
		//Destructor
		~GameObject();

		/// Update object
		void onUpdate(long elapsedTime);

		/// Add the component with the given name to the object
		/// @param name			component type identifier
		/// @param component	the component to add
		void addComponent(const std::string& name, ComponentPtr component);

		/// Query gameObject for a given component
		/// @param name of the component to query
		/// @return <b>true</b> if the required component is found
		bool hasComponent(const std::string& name);

		/// Return the component under the given name
		/// @param name		name of the component to retrieve
		/// @return			the required component, if present
		ComponentPtr getComponent(const std::string& name);

		/// Return entity name (i.e, its "type" identifier)
		/// @return name of the entity
		const std::string& getName() const;
		/// Return the concrete instance's unique identifier
		/// @return id of the entity
		const std::string& getId() const;

		//TODO: Add event-related methods
	};
}
#endif