#include "OUAN_Precompiled.h"

#include "RenderComponentViewport.h"
#include "../RenderSubsystem.h"
using namespace OUAN;

RenderComponentViewport::RenderComponentViewport(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_VIEWPORT)
{
}

RenderComponentViewport::~RenderComponentViewport()
{
	mViewport=NULL;
}

Ogre::Viewport* RenderComponentViewport::getViewport() const
{
	return mViewport;
}

void RenderComponentViewport::prepareEffects()
{
	/// Motion blur effect
	Ogre::CompositorPtr comp3 = Ogre::CompositorManager::getSingleton().create(
			mRenderSubsystem->MOTION_BLUR, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME
		);
	{
		Ogre::CompositionTechnique *t = comp3->createTechnique();
		{
			Ogre::CompositionTechnique::TextureDefinition *def = t->createTextureDefinition("scene");
			def->width = 0;
			def->height = 0;
			def->formatList.push_back(Ogre::PF_R8G8B8);
		}
		{
			Ogre::CompositionTechnique::TextureDefinition *def = t->createTextureDefinition("sum");
			def->width = 0;
			def->height = 0;
			def->formatList.push_back(Ogre::PF_R8G8B8);
		}
		{
			Ogre::CompositionTechnique::TextureDefinition *def = t->createTextureDefinition("temp");
			def->width = 0;
			def->height = 0;
			def->formatList.push_back(Ogre::PF_R8G8B8);
		}
		/// Render scene
		{
			Ogre::CompositionTargetPass *tp = t->createTargetPass();
			tp->setInputMode(Ogre::CompositionTargetPass::IM_PREVIOUS);
			tp->setOutputName("scene");
		}
		/// Initialisation pass for sum texture
		{
			Ogre::CompositionTargetPass *tp = t->createTargetPass();
			tp->setInputMode(Ogre::CompositionTargetPass::IM_PREVIOUS);
			tp->setOutputName("sum");
			tp->setOnlyInitial(true);
		}
		/// Do the motion blur
		{
			Ogre::CompositionTargetPass *tp = t->createTargetPass();
			tp->setInputMode(Ogre::CompositionTargetPass::IM_NONE);
			tp->setOutputName("temp");
			{ Ogre::CompositionPass *pass = tp->createPass();
			pass->setType(Ogre::CompositionPass::PT_RENDERQUAD);
			pass->setMaterialName("Ogre/Compositor/Combine");
			pass->setInput(0, "scene");
			pass->setInput(1, "sum");
			}
		}
		/// Copy back sum texture
		{
			Ogre::CompositionTargetPass *tp = t->createTargetPass();
			tp->setInputMode(Ogre::CompositionTargetPass::IM_NONE);
			tp->setOutputName("sum");
			{ Ogre::CompositionPass *pass = tp->createPass();
			pass->setType(Ogre::CompositionPass::PT_RENDERQUAD);
			pass->setMaterialName("Ogre/Compositor/Copyback");
			pass->setInput(0, "temp");
			}
		}
		/// Display result
		{
			Ogre::CompositionTargetPass *tp = t->getOutputTargetPass();
			tp->setInputMode(Ogre::CompositionTargetPass::IM_NONE);
			{ Ogre::CompositionPass *pass = tp->createPass();
			pass->setType(Ogre::CompositionPass::PT_RENDERQUAD);
			pass->setMaterialName("Ogre/Compositor/MotionBlur");
			pass->setInput(0, "sum");
			}
		}
	}
}

void RenderComponentViewport::initEffects()
{
	Ogre::CompositorInstance* inst;

	inst = Ogre::CompositorManager::getSingleton().addCompositor(mViewport, mRenderSubsystem->CHANGEWORLD);
	inst->setEnabled(false);
	//inst->addListener( new ChangeWorldCompositorListener );
	
	//inst = Ogre::CompositorManager::getSingleton().addCompositor(mViewport, mRenderSubsystem->BLOOM,1);
	//inst->setEnabled(false);
	//
	//inst=Ogre::CompositorManager::getSingleton().addCompositor(mViewport, mRenderSubsystem->HDR,2);
	//inst->setEnabled(false);
	//
	//inst=Ogre::CompositorManager::getSingleton().addCompositor(mViewport, mRenderSubsystem->RADIAL_BLUR,3);
	//inst->setEnabled(false);

	//inst=Ogre::CompositorManager::getSingleton().addCompositor(mViewport, mRenderSubsystem->MOTION_BLUR,4);
	//inst->setEnabled(false);

	//inst=Ogre::CompositorManager::getSingleton().addCompositor(mViewport,"ssao");
	//inst->setEnabled(true);
}

void RenderComponentViewport::setViewport(Ogre::Viewport* viewport)
{
	mViewport=viewport;
}

void RenderComponentViewport::setEffect(std::string effectName, bool activated)
{
	Ogre::CompositorManager::getSingleton().setCompositorEnabled(mViewport, effectName, activated);
}

void RenderComponentViewport::setRenderSubsystem(RenderSubsystemPtr pRenderSubsystem)
{
	mRenderSubsystem=pRenderSubsystem;
}

RenderSubsystemPtr RenderComponentViewport::getRenderSubsystem() const
{
	return mRenderSubsystem;
}

void RenderComponentViewport::setBloomAmount(double perc)
{
	//Ogre::MaterialPtr material;
	//Ogre::Technique * technique;
	//Ogre::Pass * pass;
	//Ogre::GpuProgramParametersSharedPtr params;

	////perc=Ogre::Math::Clamp<double>(perc,0.0f,1.0f);

	//material=Ogre::MaterialManager::getSingleton().getByName(mRenderSubsystem->BLOOM_BLEND_MATERIAL);

	//technique=material->getTechnique(0);
	//pass=technique->getPass(0);
	//params = pass->getFragmentProgramParameters();
	//params->setNamedConstant("BlurWeight",Ogre::Real(mRenderSubsystem->MAX_BLOOM_BLEND*perc));
}

TRenderComponentViewportParameters::TRenderComponentViewportParameters() : TRenderComponentParameters()
{
}
TRenderComponentViewportParameters::~TRenderComponentViewportParameters()
{
}