#ifndef GameObjectTotemH_H
#define GameObjectTotemH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentSimpleBox.h"
#include "../../Logic/LogicComponent/LogicComponent.h"

namespace OUAN
{
	const double LEVEL_DISTANCE=87;
	const double LEVEL_MOVEMENT_SPEED=5;
	const int NUM_LEVELS=3;
	const std::string CHANGE_WORLD_ATTACHED="changeworld#platform_big";

	const std::string TOTEM_SOUND_LEVEL_DOWN="totem_level_down";

	/// Class to hold Tower information
	class GameObjectTotem : public GameObject, public boost::enable_shared_from_this<GameObjectTotem>
	{
	private:
		
		/// Visual component
		RenderComponentEntityPtr mRenderComponentEntity;

		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
		/// Physics information
		PhysicsComponentSimpleBoxPtr mPhysicsComponentSimpleBox;
		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPtr mLogicComponent;
		//TODO: think what happens when world changes with the rendercomponent

		AudioComponentPtr mAudioComponent;

		double mLevelTarget;
		int mLevel;

	public:
		//Constructor
		GameObjectTotem(const std::string& name);
		//Destructor
		~GameObjectTotem();
		/// Set logic component
		void setLogicComponent(LogicComponentPtr logicComponent);

		/// return logic component
		LogicComponentPtr getLogicComponent();

		/// Return render component entity 
		/// @return render component entity
		RenderComponentEntityPtr getRenderComponentEntity() const;
	
		/// Set render component
		/// @param pRenderComponentEntity
		void setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity);

		/// Set audio component
		/// @param pAudioComponent
		AudioComponentPtr getAudioComponent() const;
		void setAudioComponent(AudioComponentPtr audioComponent);


		/// Set positional component
		/// @param pRenderComponentPositional the component containing the positional information
		void setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional);

		/// Set initial component
		void setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial);

		/// Return positional component 
		/// @return positional component
		RenderComponentPositionalPtr getRenderComponentPositional() const;

		/// Return initial component 
		/// @return initial component
		RenderComponentInitialPtr getRenderComponentInitial() const;

		/// Set physics component
		void setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox);

		/// Get physics component
		PhysicsComponentSimpleBoxPtr getPhysicsComponentSimpleBox() const;

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);

		/// Reset object
		virtual void reset();

		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;

		bool hasRenderComponentEntity() const;
		RenderComponentEntityPtr getEntityComponent() const;
		void setChangeWorldFactor(double factor);
		
		bool hasLogicComponent() const;
		LogicComponentPtr getLogicComponentInstance() const;

		/// Update object
		virtual void update(double elapsedSeconds);

		void levelDown();
	};

	class TGameObjectTotemParameters: public TGameObjectParameters
	{
	public:
		TGameObjectTotemParameters();
		~TGameObjectTotemParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentEntityParameters tRenderComponentEntityParameters;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Physics parameters
		TPhysicsComponentSimpleBoxParameters tPhysicsComponentSimpleBoxParameters;

		///Logic parameters
		TLogicComponentParameters tLogicComponentParameters;

		/// Audio component params
		TAudioComponentMap tAudioComponentParameters;
	};
}
#endif