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

		RenderComponentBillboardSet(const std::string& name="");
		~RenderComponentBillboardSet();

		Ogre::BillboardSet * getBillboardSet() const;
		void setBillboardSet(Ogre::BillboardSet *);

	};
}

#endif