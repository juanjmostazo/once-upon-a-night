#include "RenderComponentBillboardSet.h"
using namespace OUAN;

RenderComponentBillboardSet::RenderComponentBillboardSet(const std::string& name)
:RenderComponent(COMPONENT_NAME_RENDER_BILLBOARD_SET)
{
}
RenderComponentBillboardSet::~RenderComponentBillboardSet()
{
	mBillboardSet=NULL;
}

Ogre::BillboardSet* RenderComponentBillboardSet::getBillboardSet() const
{
	return mBillboardSet;
}
void RenderComponentBillboardSet::setBillboardSet(Ogre::BillboardSet* billboardSet)
{
	mBillboardSet=billboardSet;
}

TRenderComponentBillboardSetParameters::TRenderComponentBillboardSetParameters() : TRenderComponentParameters()
{
}
TRenderComponentBillboardSetParameters::~TRenderComponentBillboardSetParameters()
{
}

TRenderComponentBillboardParameters::TRenderComponentBillboardParameters() : TRenderComponentParameters()
{
}
TRenderComponentBillboardParameters::~TRenderComponentBillboardParameters()
{
}

