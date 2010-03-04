#ifndef GameObjectSceneH_H
#define GameObjectSceneH_H

#include "GameObject.h"
#include "../../Graphics/RenderComponent/RenderComponentScene.h"

namespace OUAN
{
	class GameObjectScene : public GameObject
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

		// Sets the GameObject to Dreams
		virtual void setDreamsMode();
		// Sets the GameObject to Nightmares
		virtual void setNightmaresMode();
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