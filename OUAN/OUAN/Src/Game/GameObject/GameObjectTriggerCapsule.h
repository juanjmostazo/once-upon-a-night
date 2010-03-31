#ifndef GameObjectTriggerCapsuleH_H
#define GameObjectTriggerCapsuleH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentVolumeCapsule.h"

namespace OUAN
{
	/// Class to hold volume capsule information
	class GameObjectTriggerCapsule : public GameObject, public boost::enable_shared_from_this<GameObjectTriggerCapsule>
	{
	private:
		/// Visual information - ONLY SHOWN IN DEBUG MODE
		RenderComponentEntityPtr mRenderComponentEntity;
		/// Position information
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentVolumeCapsulePtr mPhysicsComponentVolumeCapsule;

		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectTriggerCapsule(const std::string& name);
		//Destructor
		~GameObjectTriggerCapsule();
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
		void setPhysicsComponentVolumeCapsule(PhysicsComponentVolumeCapsulePtr pPhysicsComponentVolumeCapsule);

		/// Get physics component
		PhysicsComponentVolumeCapsulePtr getPhysicsComponentVolumeCapsule();

		/// Show or hide the component
		void changeVisibility();

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeWorld(int world);

		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;
	};

	class TGameObjectTriggerCapsuleParameters: public TGameObjectParameters
	{
	public:
		TGameObjectTriggerCapsuleParameters();
		~TGameObjectTriggerCapsuleParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentVolumeCapsuleParameters tPhysicsComponentVolumeCapsuleParameters;
	};
}
#endif