#ifndef GameObjectMovableEntityH_H
#define GameObjectMovableEntityH_H
#include "GameObjectMovable.h"
namespace OUAN
{
	class GameObjectMovableEntity : public GameObjectMovable
	{
	private:
		RenderComponentEntityPtr mRenderComponentEntity;
		RenderComponentSceneNodePtr mRenderComponentSceneNode;
		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectMovableEntity(const std::string& name, const std::string& id);
		//Destructor
		~GameObjectMovableEntity();

		//get/set
		RenderComponentEntityPtr getRenderComponentEntity() const;
		void setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity);

		RenderComponentSceneNodePtr getRenderComponentSceneNode() const;
		void setRenderComponentSceneNode(RenderComponentSceneNodePtr pRenderComponentSceneNode);

	};
}
#endif