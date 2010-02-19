#ifndef GameObjectNonMovableEntityH_H
#define GameObjectNonMovableEntityH_H
#include "GameObjectNonMovable.h"
namespace OUAN
{
	class GameObjectNonMovableEntity : public GameObjectNonMovable
	{
	private:
		RenderComponentEntityPtr mRenderComponentEntity;
		RenderComponentSceneNodePtr mRenderComponentSceneNode;
		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectNonMovableEntity(const std::string& name, const std::string& id);
		//Destructor
		~GameObjectNonMovableEntity();

		//get/set
		RenderComponentEntityPtr getRenderComponentEntity() const;
		void setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity);

		RenderComponentSceneNodePtr getRenderComponentSceneNode() const;
		void setRenderComponentSceneNode(RenderComponentSceneNodePtr pRenderComponentSceneNode);

	};
}
#endif