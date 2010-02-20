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
		/// Constructor. It receives the name of the component,
		/// which will serve as some sort of identifier for its parent
		/// gameObject and further siblings
		/// @param name component name
		Component(const std::string& name);
		/// Destructor
		virtual ~Component();

		/// Return component name
		/// @return component name
		const std::string& getName() const;
		
		/// set the name of the component
		/// @param name name of the component
		void setName(const std::string& name);

		/// Return component's family name
		/// @return component's family name
		const std::string& getFamily() const;

		/// set the component's parent GameObject
		/// @param parent the parent GameObject
		void setParent(GameObjectPtr parent);

		/// TODO: Read on Observer pattern to implement this
		//void registerEventCallback(const std::string& EventType, void (GameComponent::*fptr)(EventParams,GameObject));
		virtual void update(long elapsedTime)=0;

	protected:

		/// Component name
		std::string mName;
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