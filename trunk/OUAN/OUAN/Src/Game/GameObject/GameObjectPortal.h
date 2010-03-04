#ifndef GameObjectPortalH_H
#define GameObjectPortalH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentComplexTriangle.h"

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
		PhysicsComponentComplexTrianglePtr mPhysicsComponentComplexTriangle;

		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectPortal(const std::string& name);
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
		void setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional);

		/// Return positional component 
		/// @return positional component
		RenderComponentPositionalPtr getRenderComponentPositional() const;

		/// Set physics component
		void setPhysicsComponentComplexTriangle(PhysicsComponentComplexTrianglePtr pPhysicsComponentComplexTriangle);

		/// Get physics component
		PhysicsComponentComplexTrianglePtr getPhysicsComponentComplexTriangle();

		// Sets the GameObject to Dreams
		virtual void setDreamsMode();
		// Sets the GameObject to Nightmares
		virtual void setNightmaresMode();
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
		TPhysicsComponentComplexTriangleParameters tPhysicsComponentComplexTriangleParameters;
	};
}
#endif