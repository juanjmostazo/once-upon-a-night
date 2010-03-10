#ifndef GameObjectOnyH_H
#define GameObjectOnyH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"

namespace OUAN
{
	/// Main character game object
	class GameObjectOny : public GameObject, public boost::enable_shared_from_this<GameObjectOny>
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

		/// Entity falling state
		bool mFalling;

		/// Jump time
		double mFallTime;

		/// Jump speed
		double mFallSpeed;

		/// Tells wether the entity is on the Surface
		bool mOnSurface;

		/// Visual component data
		RenderComponentEntityPtr mRenderComponentEntityDreams;
		RenderComponentEntityPtr mRenderComponentEntityNightmares;
		/// Positional component data
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentCharacterPtr mPhysicsComponentCharacter;

		/// Health-related information (i.e, current HP and number of lives)
		//HealthComponentPtr mHealthComponent;
		
		/// Weapon wielding component
		//WeaponComponentPtr mWeaponComponent;

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

		/// Init jump
		void initJump(); 

		/// Return if theentity is jumping
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

		/// Init fall speed
		void initFall();

		/// Return if the entity is falling
		bool isFalling() const;

		/// Set if the entity is falling
		void setFalling(bool pFalling);

		/// Return fall time
		double getFallTime() const;

		/// Set fall time
		void setFallTime(double pFallTime);

		/// Return fall speed
		double getFallSpeed() const;

		/// Set fall speed
		void setFallSpeed(double pFallSpeed);
		
		/// Return if it's on Surface
		bool isOnSurface();

		/// Set on Surface
		void setOnSurface(bool pOnSurface);

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
		void setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter);

		/// Get physics component
		PhysicsComponentCharacterPtr getPhysicsComponentCharacter();

		/// Update object
		virtual void update(double elapsedSeconds);
		
		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeWorld(int world);

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
		TRenderComponentEntityParameters tRenderComponentEntityDreamsParameters;
		TRenderComponentEntityParameters tRenderComponentEntityNightmaresParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters;		
	};

}
#endif