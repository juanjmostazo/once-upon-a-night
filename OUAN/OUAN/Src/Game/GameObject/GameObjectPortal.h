#ifndef GameObjectPortalH_H
#define GameObjectPortalH_H
#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentComplexNonMovable.h"

namespace OUAN
{
	/// Class to hold Portal information
	class GameObjectPortal : public GameObject
	{
	private:
		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntity;
		/// Position information
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentComplexNonMovablePtr mPhysicsComponentComplexNonMovable;

		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectPortal(const std::string& name, const std::string& id);
		//Destructor
		~GameObjectPortal();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntity() const;

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity);

		/// Set positional component
		/// @param pRenderComponentPositional the component containing the positional information
		void setRenderComponentPositional(RenderComponentPositionalPtr pPositionalEntity);

		/// Return positional component 
		/// @return positional component
		RenderComponentPositionalPtr getRenderComponentPositional() const;

		/// Set physics component
		void setPhysicsComponentComplexNonMovable(PhysicsComponentComplexNonMovablePtr pPhysicsComponentComplexNonMovable);

		/// Get physics component
		PhysicsComponentComplexNonMovablePtr getPhysicsComponentComplexNonMovable();
	};

	class TGameObjectPortalParameters: public TGameObjectParameters
	{
	public:
		TGameObjectPortalParameters();
		~TGameObjectPortalParameters();
		
		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentComplexNonMovableParameters tPhysicsComponentComplexNonMovableParameters;
	};
}
#endif