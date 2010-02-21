#ifndef GameObjectNonMovableTerrainH_H
#define GameObjectNonMovableTerrainH_H
#include "GameObjectNonMovableEntity.h"
#include "../../Graphics/RenderComponent/RenderComponentEntity.h"

namespace OUAN
{
	class GameObjectNonMovableTerrain : public GameObjectNonMovableEntity
	{
	private:
		RenderComponentEntityPtr mRenderComponentEntity;

		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectNonMovableTerrain(const std::string& name, const std::string& id);
		//Destructor
		~GameObjectNonMovableTerrain();

		//get/set
		RenderComponentEntityPtr getRenderComponentEntity() const;
		void setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity);
	};

	class TGameObjectNonMovableTerrainParameters: public TGameObjectNonMovableEntityParameters
	{
	public:
		TGameObjectNonMovableTerrainParameters();
		~TGameObjectNonMovableTerrainParameters();
		
		TRenderComponentEntityParameters tRenderComponentEntityParameters;
	};
}
#endif