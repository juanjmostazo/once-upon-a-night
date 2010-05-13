#ifndef GameObjectCloudH_H
#define GameObjectCloudH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentFractalVolume.h"
#include "../../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Logic/LogicComponent/LogicComponent.h"

#define CLOUD_FRACTAL_VOLUME_SET_SIZE 4

namespace OUAN
{
	/// Class to hold Cloud information
	class GameObjectCloud : public GameObject, public boost::enable_shared_from_this<GameObjectCloud>
	{
	private:
		/// Visual component
		std::vector<RenderComponentFractalVolumePtr> mRenderComponentFractalVolumeSetDreams;
		std::vector<RenderComponentFractalVolumePtr> mRenderComponentFractalVolumeSetNightmares;
		/// Position information
		RenderComponentInitialPtr mRenderComponentInitial;
		RenderComponentPositionalPtr mRenderComponentPositional;

		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPtr mLogicComponent;

	public:
		//Constructor
		GameObjectCloud(const std::string& name);
		//Destructor
		~GameObjectCloud();
		/// Set logic component
		void setLogicComponent(LogicComponentPtr logicComponent);

		/// return logic component
		LogicComponentPtr getLogicComponent();

		/// Return render component entity 
		/// @return render component entity
		std::vector<RenderComponentFractalVolume> getRenderComponentFractalVolumeSetDreams();
		std::vector<RenderComponentFractalVolume> getRenderComponentFractalVolumeSetNightmares();

		/// Set render component
		/// @param pRenderComponentFractalVolume
		void setRenderComponentFractalVolumeDreams(RenderComponentFractalVolumePtr pRenderComponentFractalVolumeDreams, int pPosition);
		void setRenderComponentFractalVolumeNightmares(RenderComponentFractalVolumePtr pRenderComponentFractalVolumeNightmares, int pPosition);

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
		void changeWorld(int world);

		/// Reset object
		virtual void reset();

		/// 
		bool hasPositionalComponent() const;
		RenderComponentPositionalPtr getPositionalComponent() const;

		// update logic component
		void updateLogic(double elapsedSeconds);
	};

	class TGameObjectCloudParameters: public TGameObjectParameters
	{
	public:
		TGameObjectCloudParameters();
		~TGameObjectCloudParameters();

		///Parameters specific to an Ogre Entity
		TRenderComponentFractalVolumeParameters tRenderComponentFractalVolumeSetDreamsParameters;
		TRenderComponentFractalVolumeParameters tRenderComponentFractalVolumeSetNightmaresParameters;

		double tFractalVolumeSetInnerSeparation;

		///Positional parameters
		TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

		///Logic parameters
		TLogicComponentParameters tLogicComponentParameters;
	};
}
#endif