#include "OUAN_Precompiled.h"

#include "RenderComponentGlow.h"

using namespace OUAN;

RenderComponentGlow::RenderComponentGlow(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_GLOW)
,mVisible(false)
{

}

RenderComponentGlow::~RenderComponentGlow()
{

}

Ogre::SceneNode* RenderComponentGlow::getSceneNode() const
{
	return mSceneNode;
}

void RenderComponentGlow::setSceneNode(Ogre::SceneNode* sceneNode)
{
	mSceneNode = sceneNode;
}

Ogre::Entity* RenderComponentGlow::getEntity() const
{
	return mEntity;
}

void RenderComponentGlow::setEntity(Ogre::Entity* entity)
{
	mEntity = entity;
}

void RenderComponentGlow::setVisible(bool visible)
{
	mVisible=visible;
	mSceneNode->setVisible(mVisible);	

	if (mVisible)
	{
		setUpShaders();
	}
}

bool RenderComponentGlow::isVisible()
{
	return mVisible;
}

void RenderComponentGlow::setParams(double time_scale, double size_scale, double expand_width, double expand_grow, double alpha, double color_r, double color_g, double color_b)
{
	mTime_scale = time_scale;
	mSize_scale = size_scale;
	mExpand_width = expand_width;
	mExpand_grow = expand_grow;
	mAlpha = alpha;
	mColor_r = color_r;
	mColor_g = color_g;
	mColor_b = color_b;
}

void RenderComponentGlow::setUpShaders()
{
	Ogre::MaterialPtr glowMaterial = getEntity()->getSubEntity(0)->getMaterial();

	for (unsigned int i=0; i<glowMaterial->getBestTechnique()->getNumPasses(); i++)
	{
		if (glowMaterial->getBestTechnique()->getPass(i)->hasVertexProgram())
		{
			Ogre::GpuProgramParametersSharedPtr vertexParams = 
				glowMaterial->getBestTechnique()->getPass(i)->getVertexProgramParameters();

			if (vertexParams->_findNamedConstantDefinition("time_scale"))
			{
				vertexParams->setNamedConstant("time_scale", Ogre::Real(mTime_scale));
			}
			if (vertexParams->_findNamedConstantDefinition("size_scale"))
			{
				vertexParams->setNamedConstant("size_scale", Ogre::Real(mSize_scale));
			}
			if (vertexParams->_findNamedConstantDefinition("expand_width"))
			{
				vertexParams->setNamedConstant("expand_width", Ogre::Real(mExpand_width));
			}
			if (vertexParams->_findNamedConstantDefinition("expand_grow"))
			{
				vertexParams->setNamedConstant("expand_grow", Ogre::Real(mExpand_grow));
			}
		}

		if (glowMaterial->getBestTechnique()->getPass(i)->hasFragmentProgram())
		{
			Ogre::GpuProgramParametersSharedPtr pixelParams = 
				glowMaterial->getBestTechnique()->getPass(i)->getFragmentProgramParameters();

			if (pixelParams->_findNamedConstantDefinition("time_scale"))
			{
				pixelParams->setNamedConstant("time_scale", Ogre::Real(mTime_scale));
			}
			if (pixelParams->_findNamedConstantDefinition("alpha"))
			{
				pixelParams->setNamedConstant("alpha", Ogre::Real(mAlpha));
			}
			if (pixelParams->_findNamedConstantDefinition("color_r"))
			{
				pixelParams->setNamedConstant("color_r", Ogre::Real(mColor_r));
			}
			if (pixelParams->_findNamedConstantDefinition("color_g"))
			{
				pixelParams->setNamedConstant("color_g", Ogre::Real(mColor_g));
			}
			if (pixelParams->_findNamedConstantDefinition("color_b"))
			{
				pixelParams->setNamedConstant("color_b", Ogre::Real(mColor_b));
			}
		}
	}
}

TRenderComponentGlowParameters::TRenderComponentGlowParameters() : TRenderComponentParameters()
{

}

TRenderComponentGlowParameters::~TRenderComponentGlowParameters()
{

}
