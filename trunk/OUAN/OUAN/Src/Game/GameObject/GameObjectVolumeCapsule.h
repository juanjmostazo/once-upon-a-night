#ifndef GameObjectVolumeCapsuleH_H
#define GameObjectVolumeCapsuleH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentVolumeCapsule.h"

namespace OUAN
{
	/// Class to hold volume capsule information
	class GameObjectVolumeCapsule : public GameObject
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
		GameObjectVolumeCapsule(const std::string& name);
		//Destructor
		~GameObjectVolumeCapsule();
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

		// Sets the GameObject to Dreams
		virtual void setDreamsMode();
		// Sets the GameObject to Nightmares
		virtual void setNightmaresMode();
	};

	class TGameObjectVolumeCapsuleParameters: public TGameObjectParameters
	{
	public:
		TGameObjectVolumeCapsuleParameters();
		~TGameObjectVolumeCapsuleParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentVolumeCapsuleParameters tPhysicsComponentVolumeCapsuleParameters;
	};
}
#endif