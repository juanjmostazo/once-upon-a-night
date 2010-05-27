#ifndef GameObjectSoundH_H
#define GameObjectSoundH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Audio/AudioComponent/AudioComponent.h"
//#include "../../Logic/LogicComponent/LogicComponent.h"

namespace OUAN
{
	enum TGameObjectSoundType
	{
		SOUNDTYPE_POSITIONAL=0,
		SOUNDTYPE_AMBIENT,
		SOUNDTYPE_EVENT
	};
	/// Models a light source object
	class GameObjectSound : public GameObject, public boost::enable_shared_from_this<GameObjectSound>
	{
	private:
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;
	
		AudioComponentPtr mAudioComponentDreams;
		AudioComponentPtr mAudioComponentNightmares;

		TGameObjectSoundType mSoundType;

		std::string mCurrentDreamsSoundID;
		std::string mCurrentNightmaresSoundID;
	public:
		//Constructor
		GameObjectSound(const std::string& name);
		//Destructor
		~GameObjectSound();
		/// Set logic component
		void setAudioComponentDreams(AudioComponentPtr audioComponentDreams);

		/// return logic component
		AudioComponentPtr getAudioComponentDreams() const;

		/// Set logic component
		void setAudioComponentNightmares(AudioComponentPtr audioComponentNightmares);

		/// return logic component
		AudioComponentPtr getAudioComponentNightmares() const;

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

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);

		TGameObjectSoundType getSoundType() const;
		void setSoundType(TGameObjectSoundType soundType);

		void update(double elapsedSeconds);

		const std::string& getCurrentDreamsSoundId() const;
		void setCurrentDreamsSoundId(const std::string& soundId);

		const std::string& getCurrentNightmaresSoundId() const;
		void setCurrentNightmaresSoundId(const std::string& soundId);


		/// Reset object
		virtual void reset();

		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;

		bool hasAudioComponent() const;
		AudioComponentPtr getAudioComponentInstance() const;

		void play(const std::string& soundID);
		void stop(const std::string& soundID);

	};

	/// Transport object carrying around data from the level loader
	/// to the light object
	class TGameObjectSoundParameters: public TGameObjectParameters
	{
	public:
		/// Default constructor
		TGameObjectSoundParameters();
		/// Default destructor
		~TGameObjectSoundParameters();

		TGameObjectSoundType soundType;

		std::string currentDreamsSoundID;
		std::string currentNightmaresSoundID;

		/// Light-specific parameters
		TAudioComponentMap tAudioComponentDreamsParameters;
		TAudioComponentMap tAudioComponentNightmaresParameters;
		/// Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;
	};
}
#endif