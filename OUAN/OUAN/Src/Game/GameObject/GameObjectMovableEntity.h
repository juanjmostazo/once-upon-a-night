#ifndef GameObjectMovableEntityH_H
#define GameObjectMovableEntityH_H
#include "GameObjectMovable.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"
namespace OUAN
{
	class GameObjectMovableEntity : public GameObjectMovable
	{
	private:
		RenderComponentEntityPtr mRenderComponentEntity;

		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectMovableEntity(const std::string& name, const std::string& id);
		//Destructor
		~GameObjectMovableEntity();

		//get/set
		RenderComponentEntityPtr getRenderComponentEntity() const;
		void setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity);

	};

	class TGameObjectMovableEntityParameters: public TGameObjectMovableParameters
	{
	public:
		TGameObjectMovableEntityParameters();
		~TGameObjectMovableEntityParameters();

		TRenderComponentEntityParameters tRenderComponentEntityParameters;
	};
}
#endif