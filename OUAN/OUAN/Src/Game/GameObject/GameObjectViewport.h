#ifndef GameObjectViewportH_H
#define GameObjectViewportH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentViewport.h"

namespace OUAN
{
	/// Class to hold Viewport information
	class GameObjectViewport : public GameObject, public boost::enable_shared_from_this<GameObjectViewport>
	{
	private:
		/// Viewport information
		RenderComponentViewportPtr mRenderComponentViewport;

		//TODO: think what happens when world changes with the viewportcomponent
	public:
		//Constructor
		GameObjectViewport(const std::string& name);
		//Destructor
		~GameObjectViewport();
		/// Return render component viewport 
		/// @return render component viewport
		RenderComponentViewportPtr getRenderComponentViewport() const;

		/// Set render component
		/// @param pRenderComponentViewport
		void setRenderComponentViewport(RenderComponentViewportPtr pRenderComponentViewport);

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);

		void setEffect(std::string effectName, bool activated);

		void setBloomEffectIfPossible(int world, bool enabled);
		void setHDREffectIfPossible(int world, bool enabled);
		void setRadialBlurEffectIfPossible(int world, bool enabled);
		void setMotionBlurEffectIfPossible(int world, bool enabled);
	};

	class TGameObjectViewportParameters: public TGameObjectParameters
	{
	public:
		TGameObjectViewportParameters();
		~TGameObjectViewportParameters();
		
		///Parameters specific Viewport
		TRenderComponentViewportParameters tRenderComponentViewportParameters;
	};
}
#endif