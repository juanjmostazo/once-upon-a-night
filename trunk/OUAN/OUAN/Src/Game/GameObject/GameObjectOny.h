#ifndef GameObjectOnyH_H
#define GameObjectOnyH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"

namespace OUAN
{
	/// Main character game object
	class GameObjectOny : public GameObject
	{
	private:
		/// Entity movement flags, will be updated every frame
		int mMovementFlags;

		/// Entity jumping state
		bool mJumping;

		/// Jump time
		double mJumpTime;

		/// Jump speed
		double mJumpSpeed;

		/// Visual component data
		RenderComponentEntityPtr mRenderComponentEntity;
		/// Positional component data
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentCharacterPtr mPhysicsComponentCharacter;

	public:
		//Constructor
		/// @param name	name of the object, specific to the class
		/// @param id	unique identifier of the instance
		GameObjectOny(const std::string& name);
		//Destructor
		~GameObjectOny();

		/// Return movement flags
		int getMovementFlags() const;

		/// Set movement flags
		void setMovementFlags(int pMovementFlags);

		/// Return if the entity is jumping
		bool isJumping() const;

		/// Set if the entity is jumping
		void setJumping(bool pJumping);

		/// Return jump time
		double getJumpTime() const;

		/// Set jump time
		void setJumpTime(double pJumpTime);

		/// Return jump speed
		double getJumpSpeed() const;

		/// Set jump speed
		void setJumpSpeed(double pJumpSpeed);

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
		void setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter);

		/// Get physics component
		PhysicsComponentCharacterPtr getPhysicsComponentCharacter();

		/// Update object
		virtual void update(double elapsedSeconds);
		// Sets the GameObject to Dreams
		virtual void setDreamsMode();
		// Sets the GameObject to Nightmares
		virtual void setNightmaresMode();
	};

	/// Carries data between the level loader and the object factories
	class TGameObjectOnyParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectOnyParameters();
		/// Default destructor
		~TGameObjectOnyParameters();
		
		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters;
	};

}
#endif