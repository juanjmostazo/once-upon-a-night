#ifndef GameObjectNonMovableLightH_H
#define GameObjectNonMovableLightH_H
#include "GameObjectNonMovable.h"
#include "../../Graphics/RenderComponent/RenderComponentLight.h"
namespace OUAN
{
	class GameObjectNonMovableLight : public GameObjectNonMovable
	{
	private:
		RenderComponentLightPtr mRenderComponentLight;

		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectNonMovableLight(const std::string& name, const std::string& id);
		//Destructor
		~GameObjectNonMovableLight();

		//get/set
		RenderComponentLightPtr getRenderComponentLight() const;
		void setRenderComponentLight(RenderComponentLightPtr pRenderComponentLight);


	};

	class TGameObjectNonMovableLightParameters: public TGameObjectNonMovableParameters
	{
	public:
		TGameObjectNonMovableLightParameters();
		~TGameObjectNonMovableLightParameters();
		
		TRenderComponentLightParameters tRenderComponentLightParameters;

	};
}
#endif