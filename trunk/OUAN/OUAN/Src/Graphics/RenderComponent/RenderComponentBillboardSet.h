#ifndef RenderComponentBillboardSetH_H
#define RenderComponentBillboardSetH_H

#include "RenderComponent.h"

namespace OUAN
{
	class RenderComponentBillboardSet: public RenderComponent
	{
	private:
		Ogre::BillboardSet * mBillboardSet;
	public:

		RenderComponentBillboardSet(const std::string& type="");
		~RenderComponentBillboardSet();

		Ogre::BillboardSet * getBillboardSet() const;
		void setBillboardSet(Ogre::BillboardSet *);

	};

	class TRenderComponentBillboardParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentBillboardParameters();
		~TRenderComponentBillboardParameters();

		ColourValue colour;
		Vector2 dimensions;
		Vector3 position;
		Real rotation;
		int texcoordindex;
		Vector4 texrect;

	};

	class TRenderComponentBillboardSetParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentBillboardSetParameters();
		~TRenderComponentBillboardSetParameters();

		String material;
		Ogre::BillboardOrigin billboardorigin;
		Ogre::BillboardRotationType billboardrotation;
		Ogre::BillboardType billboardtype;
		Real defaultheight;
		Real defaultwidth;
		bool pointrendering;
		Real renderdistance;
		bool sorting;
		std::vector<TRenderComponentBillboardParameters> tRenderComponentBillboardParameters;

	};


}

#endif