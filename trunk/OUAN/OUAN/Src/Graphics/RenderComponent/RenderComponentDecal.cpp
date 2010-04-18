#include "RenderComponentDecal.h"
using namespace OUAN;

RenderComponentDecal::RenderComponentDecal(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_DECAL)
{

}

RenderComponentDecal::~RenderComponentDecal()
{
	//mDecal=NULL;
}
//
//Ogre::Decal* RenderComponentDecal::getDecal() const
//{
//	return mDecal;
//}

//void RenderComponentDecal::setDecal(Ogre::Decal* Decal)
//{
//	mDecal=Decal;
//}

void RenderComponentDecal::setVisible(bool visible)
{
	//mDecal->setVisible(visible);
}

TRenderComponentDecalParameters::TRenderComponentDecalParameters() : TRenderComponentParameters()
{

}

TRenderComponentDecalParameters::~TRenderComponentDecalParameters()
{

}
