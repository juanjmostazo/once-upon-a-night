#ifndef GameObjectTerrainTriangleH_H
#define GameObjectTerrainTriangleH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentComplexTriangle.h"

namespace OUAN
{
	/// Class to hold terrain information
	class GameObjectTerrainTriangle : public GameObject, public boost::enable_shared_from_this<GameObjectTerrainTriangle>
	{
	private:
		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntityDreams;
		RenderComponentEntityPtr mRenderComponentEntityNightmares;
		/// Position information
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentComplexTrianglePtr mPhysicsComponentComplexTriangle;

		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectTerrainTriangle(const std::string& name);
		//Destructor
		~GameObjectTerrainTriangle();
		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntityDreams() const;
		RenderComponentEntityPtr getRenderComponentEntityNightmares() const;

		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams);
		void setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares);

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

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeWorld(int world);

	};

	class TGameObjectTerrainTriangleParameters: public TGameObjectParameters
	{
	public:
		TGameObjectTerrainTriangleParameters();
		~TGameObjectTerrainTriangleParameters();
		
		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityDreamsParameters;
		TRenderComponentEntityParameters tRenderComponentEntityNightmaresParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentComplexTriangleParameters tPhysicsComponentComplexTriangleParameters;

	};
}
#endif