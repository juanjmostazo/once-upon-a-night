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
		void changeWorld(int world);

		/// Attach all event handlers for this class.
		// This method will have to be redefined by all GameObject subclasses to register all the event handlers
		void registerHandlers();
		/// Detach all event handlers.
		// This method will have to be redefined by all GameObject subclasses to unregister all the event handlers
		void unregisterHandlers();

		//Event handler methods
		void processChangeWorld(ChangeWorldEventPtr evt);
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