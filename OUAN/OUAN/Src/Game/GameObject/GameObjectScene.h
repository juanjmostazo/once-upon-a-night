#ifndef GameObjectSceneH_H
#define GameObjectSceneH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentScene.h"

namespace OUAN
{
	class GameObjectScene : public GameObject, public boost::enable_shared_from_this<GameObjectScene>
	{
	private:
		RenderComponentScenePtr mRenderComponentScene;
	public:
		//Constructor
		GameObjectScene(const std::string& name);
		//Destructor
		~GameObjectScene();

		//get/set
		RenderComponentScenePtr getRenderComponentScene() const;
		void setRenderComponentScene(RenderComponentScenePtr pRenderComponentScene);

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);

		void setDreamsRender();
		void setNightmaresRender();
		void setChangeWorldRender();
		void setChangeWorldFactor(double factor);

		void update(double elapsedSeconds);

	};

	class TGameObjectSceneParameters: public TGameObjectParameters
	{
	public:
		TGameObjectSceneParameters();
		~TGameObjectSceneParameters();

		TRenderComponentSceneParameters tRenderComponentSceneParameters;
	};
}
#endif