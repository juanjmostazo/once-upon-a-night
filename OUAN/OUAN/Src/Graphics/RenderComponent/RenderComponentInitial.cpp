#include "OUAN_Precompiled.h"

#include "RenderComponentInitial.h"

using namespace OUAN;

RenderComponentInitial::RenderComponentInitial(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_INITIAL)
{

}

RenderComponentInitial::~RenderComponentInitial()
{
	
}

Vector3 RenderComponentInitial::getPosition() const
{
	return mPosition;
}

void RenderComponentInitial::setPosition(Vector3 pPosition)
{
	mPosition=pPosition;
}

Quaternion RenderComponentInitial::getOrientation() const
{
	return mOrientation;
}

void RenderComponentInitial::setOrientation(Quaternion pOrientation)
{
	mOrientation=pOrientation;
}