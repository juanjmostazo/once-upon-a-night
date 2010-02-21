#ifndef GameObjectTerrainH_H
#define GameObjectTerrainH_H
#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"

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

		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectTerrain(const std::string& name, const std::string& id);
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
		void setRenderComponentPositional(RenderComponentPositionalPtr pPositionalEntity);

		/// Return positional component 
		/// @return positional component
		RenderComponentPositionalPtr getRenderComponentPositional() const;
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
	};
}
#endif