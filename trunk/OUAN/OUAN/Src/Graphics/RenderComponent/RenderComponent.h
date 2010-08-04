#ifndef RenderComponentH_H
#define RenderComponentH_H

#include "../../Component/Component.h"
namespace OUAN
{
	class RenderComponent: public Component
	{
	public:
		RenderComponent(const std::string& type="");
		~RenderComponent();

		virtual void update(long elapsedTime);
	protected:
		virtual std::string setChangeWorldMaterialTransparentTextures(std::string changeWorldMaterial,bool existInDreams,bool existInNightmares);

		//Event handlers
		//void onDoSomething(EventData,emitter, ...);
		//void onDoSomethingElse(...);
	};

	class TRenderComponentParameters: public TComponentParameters
	{
	public:
		TRenderComponentParameters();
		~TRenderComponentParameters();
	};
}

#endif