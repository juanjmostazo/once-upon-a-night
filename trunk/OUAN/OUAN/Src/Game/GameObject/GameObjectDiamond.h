#ifndef GameObjectDiamondH_H
#define GameObjectDiamondH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentVolumeBox.h"

namespace OUAN
{
	/// Class to hold GameObjectDiamond information
	class GameObjectDiamond : public GameObject, public boost::enable_shared_from_this<GameObjectDiamond>
	{
	private:
		
		/// Visual information
		RenderComponentEntityPtr mRenderComponentEntity;
		/// Position information
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentVolumeBoxPtr mPhysicsComponentVolumeBox;

		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectDiamond(const std::string& name);
		//Destructor
		~GameObjectDiamond();
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
		void setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox);

		/// Get physics component
		PhysicsComponentVolumeBoxPtr getPhysicsComponentVolumeBox();
	};

	class TGameObjectDiamondParameters: public TGameObjectParameters
	{
	public:
		TGameObjectDiamondParameters();
		~TGameObjectDiamondParameters();
		
		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentVolumeBoxParameters tPhysicsComponentVolumeBoxParameters;
	};
}
#endif