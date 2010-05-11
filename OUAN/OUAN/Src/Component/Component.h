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

		/// Return the component's parent GameObject
		/// @return this component's parent GameObject
		GameObjectPtr getParent();

		/// Return the component's parent GameObject name
		/// @return this component's parent GameObject name
		const std::string& getParentName();

		/// Update component
		virtual void update(double elapsedSeconds);

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