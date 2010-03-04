#ifndef GameObjectTerrainH_H
#define GameObjectTerrainH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentComplexTriangle.h"
//#include "../../Physics/PhysicsComponent/PhysicsComponentComplexConvex.h"

namespace OUAN
{
	/// Class to hold terrain information
	class GameObjectTerrain : public GameObject
	{
	private:
		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntity;
		/// Position information
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentComplexTrianglePtr mPhysicsComponentComplexTriangle;
		//PhysicsComponentComplexConvexPtr mPhysicsComponentComplexConvex;

		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectTerrain(const std::string& name);
		//Destructor
		~GameObjectTerrain();
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
		//void setPhysicsComponentComplexConvex(PhysicsComponentComplexConvexPtr pPhysicsComponentComplexConvex);

		/// Get physics component
		PhysicsComponentComplexTrianglePtr getPhysicsComponentComplexTriangle();
		//PhysicsComponentComplexConvexPtr getPhysicsComponentComplexConvex();

		// Sets the GameObject to Dreams
		virtual void setDreamsMode();
		// Sets the GameObject to Nightmares
		virtual void setNightmaresMode();
	};

	class TGameObjectTerrainParameters: public TGameObjectParameters
	{
	public:
		TGameObjectTerrainParameters();
		~TGameObjectTerrainParameters();
		
		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentComplexTriangleParameters tPhysicsComponentComplexTriangleParameters;
		//TPhysicsComponentComplexConvexParameters tPhysicsComponentComplexConvexParameters;
	};
}
#endif