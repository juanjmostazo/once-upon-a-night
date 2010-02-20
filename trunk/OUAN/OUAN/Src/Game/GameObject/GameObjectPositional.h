#ifndef GameObjectPositionalH_H
#define GameObjectPositionalH_H
#include "GameObject.h"
#include "../RenderComponent/RenderComponentSceneNode.h"
namespace OUAN
{
	class GameObjectPositional : public GameObject
	{
		RenderComponentSceneNodePtr mRenderComponentSceneNode;
	public:
		//Constructor
		GameObjectPositional(const std::string& name, const std::string& id);
		//Destructor
		~GameObjectPositional();

		RenderComponentSceneNodePtr getRenderComponentSceneNode() const;
		void setRenderComponentSceneNode(RenderComponentSceneNodePtr pRenderComponentSceneNode);
	};

	class TGameObjectPositionalParameters: public TGameObjectParameters
	{
	public:
		TGameObjectPositionalParameters();
		~TGameObjectPositionalParameters();

		TRenderComponentSceneNodeParameters tRenderComponentSceneNodeParameters;
	};

}
#endif