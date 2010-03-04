#ifndef GAMEOBJECTH_H
#define GAMEOBJECTH_H

#include "../../OUAN.h"

namespace OUAN
{
	class GameObject{
	private:
		/// GameObject identifier (i.e, "pc_ony")
		std::string mName;
	public:
		//Constructor
		GameObject(const std::string& name);
		//Destructor
		~GameObject();

		/// Return entity name (i.e, its "type" identifier)
		/// @return name of the entity
		const std::string& getName() const;

		/// Update object
		virtual void update(long elapsedTime);

		// Sets the GameObject to Dreams
		virtual void setDreamsMode();
		// Sets the GameObject to Nightmares
		virtual void setNightmaresMode();

		//TODO: Add event-related methods
	};

	class TGameObjectParameters
	{
	public:
		TGameObjectParameters();
		~TGameObjectParameters();

		std::string name;
		std::string dreamsName;
		std::string nightmaresName;
	};
}
#endif