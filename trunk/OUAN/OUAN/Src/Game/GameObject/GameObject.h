#ifndef GAMEOBJECTH_H
#define GAMEOBJECTH_H

#include "../../OUAN.h"
#include "../../Event/EventManager.h"
#include "../../Event/EventHandler.h"

namespace OUAN
{
	class ObjectTextDisplay;
	const double DEFAULT_DISPLAY_LIFETIME=2.0;
	class GameObject
	{
	private:
		/// GameObject identifier (i.e, "tripollo#14")
		std::string mName;
		/// GameObject identifier (i.e. GameObjectTripolloDreams)
		std::string mType;
		/// GameObject attribute 
		bool mEnabled;
		/// GameObject number of updates
		long mNumUpdates;

	protected:
		double mDisplayLifetime;
		ObjectTextDisplay* mDisplayMsg;
		///Game world manager
		GameWorldManagerPtr mGameWorldManager;

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		virtual void changeToWorld(int newWorld, double perc);
		virtual void changeWorldFinished(int newWorld);
		virtual void changeWorldStarted(int newWorld);

		double mChangeWorldElapsedTime;
		bool mIsChangingWorld;
		double mChangeWorldDelay;
		int mWorld;
	public:
		//Constructor
		GameObject(const std::string& name,const std::string& type);
		//Destructor
		~GameObject();

		static GameObjectPtr Null;

		GameWorldManagerPtr getGameWorldManager();
		void setGameWorldManager(GameWorldManagerPtr gameWorldManager);

		/// Manages Game Object destruction
		virtual void destroy();

		/// Manages Game Object reset
		virtual void reset();

		//// Returns if it's first update
		bool isFirstUpdate();

		/// Return Game Object name (i.e, its identifier)
		/// @return name of the Game Object
		const std::string& getName();

		/// Return Game Object type
		/// @return type of the Game Object
		const std::string& getType() const;

		/// Update object
		virtual void update(double elapsedSeconds);


		/// Process collision event
		/// @param gameObject which has collision with
		virtual void processCollision(GameObjectPtr pGameObject);

		/// Process collision event
		/// @param gameObject which has collision with
		virtual void processEnterTrigger(GameObjectPtr pGameObject);

		/// Process collision event
		/// @param gameObject which has collision with
		virtual void processExitTrigger(GameObjectPtr pGameObject);

		/// Process animation ended event
		/// @param name of the object's animation that's finished
		virtual void processAnimationEnded(const std::string& animationName);

		void activateChangeWorld();
		void activateChangeWorldFast();

		// update logic component
		virtual void updateLogic(double elapsedSeconds);

		virtual bool isMoving();
		virtual bool isJumping();
		virtual bool cancelAutoCameraMovement();

		/// Disable the object
		virtual void disable();
		/// Enable the object
		virtual void enable();

		/// Check if the object is enabled
		bool isEnabled();

	/*	/// If applicable, increase the object's health points
		/// @param amount number of HP to increase
		virtual void increaseHP(int amount=1);
		/// If applicable, decrease the object's health points
		/// @param amount number of HP to decrease
		virtual void decreaseHP(int amount=1);
		
		/// If applicable, increase the object's number of lives
		/// @param amount of lives to increase
		virtual void increaseLives(int amount=1);
		/// If applicable, decrease the object's number of lives
		/// @param amount of lives to decrease
		virtual void decreaseLives(int amount=1);

		/// Additional actions to take after losing one life
		virtual void loseLife();

		/// Additional actions to take after losing all lives
		virtual void die();*/

		virtual bool hasPositionalComponent() const;
		virtual RenderComponentPositionalPtr getPositionalComponent() const;

		virtual bool hasPhysicsComponent() const;
		virtual PhysicsComponentPtr getPhysicsComponent() const;

		virtual bool hasRenderComponentEntity() const;
		virtual RenderComponentEntityPtr getEntityComponent() const;

		//QUERY METHODS (Used by LUA scripts)

	/*	/// Return number of lives (in practice, all enemies will have only 1 life, so it won't be used)
		int getNumLives() const;

		/// Return health points
		int getHealthPoints() const;

		/// Return base/maximum health points
		int getMaximumHealthPoints() const;

		/// Return sight distance
		int getLineOfSight() const;*/

		/// Compute distance from this object to the passed one
		double computeDistanceTo(GameObjectPtr other) const;

		virtual void setAttack(const std::string& newAttack);
		virtual void beginAttack();
		virtual void switchOff();
		virtual std::string translateWeaponMode(TWeaponMode weaponmode);
		virtual std::string getDefaultAttack();
		virtual bool canInitiateAttack();

		virtual WeaponComponentPtr getParentWeaponComponent() const;
		virtual bool hasParentWeaponComponent() const;

		virtual void activate();
		virtual bool canBeActivated() const;
		virtual void postUpdate();

		void displayText(const std::string& msg, const double& displayLifetime=DEFAULT_DISPLAY_LIFETIME);
		void disableDisplayMsg();

		void setChangeWorldDelay(double delay);
		double getChangeWorldDelay() const;
		bool isChangingWorld() const;

		void setChangeWorldElapsedTime(double time);
		double getChangeWorldElapsedTime() const;
		int getWorld();
	};

	class TGameObjectParameters
	{
	public:
		TGameObjectParameters();
		~TGameObjectParameters();

		std::string name;
		std::string dreamsName;
		std::string nightmaresName;

	};
}
#endif