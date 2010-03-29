#ifndef GameObjectClockPieceH_H
#define GameObjectClockPieceH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentVolumeBox.h"

namespace OUAN
{
	/// Class to hold GameObjectClockPiece information
	class GameObjectClockPiece : public GameObject, public boost::enable_shared_from_this<GameObjectClockPiece>
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
		GameObjectClockPiece(const std::string& name);
		//Destructor
		~GameObjectClockPiece();
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

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeWorld(int world);
	};

	class TGameObjectClockPieceParameters: public TGameObjectParameters
	{
	public:
		TGameObjectClockPieceParameters();
		~TGameObjectClockPieceParameters();
		
		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentVolumeBoxParameters tPhysicsComponentVolumeBoxParameters;
	};
}
#endif