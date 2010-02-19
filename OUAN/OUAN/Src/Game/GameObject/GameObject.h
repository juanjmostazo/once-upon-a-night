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

	public:
		//Constructor
		GameObject(const std::string& name, const std::string& id);
		//Destructor
		~GameObject();

		/// Return entity name (i.e, its "type" identifier)
		/// @return name of the entity
		const std::string& getName() const;
		/// Return the concrete instance's unique identifier
		/// @return id of the entity
		const std::string& getId() const;

		/// Update object
		virtual void update(long elapsedTime);

		//TODO: Add event-related methods
	};
}
#endif