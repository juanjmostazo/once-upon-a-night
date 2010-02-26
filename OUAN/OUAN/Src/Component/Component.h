#ifndef GAMECOMPONENTH_H
#define GAMECOMPONENTH_H
#include "../OUAN.h"
namespace OUAN
{
	///Implement a trait of a game object
	/// (for example, its physical world representation,
	///  its rendering properties, additional effects,...)
	class Component
	{
	public:
		/// Constructor. It receives the type of the component,
		/// which will serve as some sort of identifier for its parent
		/// gameObject and further siblings
		/// @param type component type
		Component(const std::string& type);
		/// Destructor
		virtual ~Component();

		/// Return component type
		/// @return component type
		const std::string& getType() const;
		
		/// set the type of the component
		/// @param type type of the component
		void setType(const std::string& type);

		/// Return component's family type
		/// @return component's family type
		const std::string& getFamily() const;

		/// set the component's parent GameObject
		/// @param parent the parent GameObject
		void setParent(GameObjectPtr parent);

		/// TODO: Read on Observer pattern to implement this
		//void registerEventCallback(const std::string& EventType, void (GameComponent::*fptr)(EventParams,GameObject));
		virtual void update(long elapsedTime)=0;

	protected:

		/// Component type
		std::string mType;
		/// parent GameObject
		GameObjectPtr mParent;
	};

	class TComponentParameters
	{
	public:
		TComponentParameters();
		~TComponentParameters();
	};
}
#endif