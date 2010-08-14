#include "OUAN_Precompiled.h"

#include "RenderComponentWater.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameObject/GameObjectOny.h"
#include "../../Game/GameWorldManager.h"
#include "../../Event/EventDefs.h"
#include "../CameraManager/CameraManager.h"
#include "../../Game/WorldNameConverter.h"

using namespace OUAN;
using namespace Ogre;

RenderComponentWater::RenderComponentWater(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_ENTITY)
{
}

RenderComponentWater::~RenderComponentWater()
{
}

Ogre::Entity* RenderComponentWater::getEntity() const
{
	return mEntity;
}

void RenderComponentWater::setEntity(Ogre::Entity* entity,bool existInDreams,bool existInNightmares)
{
	mEntity=entity;

	Ogre::SubEntity* subEnt;
	unsigned int i;

	mDreamsMaterial.clear();
	mNightmaresMaterial.clear();
	mChangeWorldMaterial.clear();

	if(mEntity)
	{
		for ( i = 0; i < mEntity->getNumSubEntities(); i++)
		{
			// Get the material of this sub entity and build the clone material name
			subEnt = mEntity->getSubEntity(i);

			if(subEnt)
			{
				mDreamsMaterial.push_back(WorldNameConverter::getDreamsName(subEnt->getMaterialName().c_str()));
				mNightmaresMaterial.push_back(WorldNameConverter::getNightmaresName(subEnt->getMaterialName().c_str()));
				mChangeWorldMaterial.push_back(WorldNameConverter::getChangeWorldName(subEnt->getMaterialName().c_str()));
				mChangeWorldMaterial[i]=setChangeWorldMaterialTransparentTextures(mChangeWorldMaterial[i],existInDreams,existInNightmares);
			}
		}
	}
}

void RenderComponentWater::setVisible(bool visible)
{
	Ogre::SceneNode * pSceneNode;
	pSceneNode=getParent()->getPositionalComponent()->getSceneNode();

	if(visible)
	{
		if(!mEntity->isAttached())
		{
			pSceneNode->attachObject(mEntity);
		}
	}
	else
	{
		if(mEntity->isAttached() && mEntity->getParentSceneNode()->getName().compare(pSceneNode->getName())==0)
		{
			pSceneNode->detachObject(mEntity->getName());
		}
	}
}

void RenderComponentWater::initFresnelReflection(CameraManagerPtr pCameraManager,GameWorldManagerPtr pGameWorldManager)
{
	//mCameraManager=pCameraManager;
	//mGameWorldManager=pGameWorldManager;

 //   // Check prerequisites first
	//const RenderSystemCapabilities* caps = Root::getSingleton().getRenderSystem()->getCapabilities();
 //   if (!caps->hasCapability(RSC_VERTEX_PROGRAM) || !(caps->hasCapability(RSC_FRAGMENT_PROGRAM)))
 //   {
 //       OGRE_EXCEPT(1, "Your card does not support vertex and fragment programs, so cannot "
 //           " run Once Upon a Night. Sorry!", 
 //           "Fresnel::createScene");
 //   }
 //   else
 //   {
 //       if (!GpuProgramManager::getSingleton().isSyntaxSupported("arbfp1") &&
 //           !GpuProgramManager::getSingleton().isSyntaxSupported("ps_2_0") &&
	//		!GpuProgramManager::getSingleton().isSyntaxSupported("ps_1_4")
	//		)
 //       {
 //           OGRE_EXCEPT(1, "Your card does not support advanced fragment programs, "
 //               "so cannot run Once Upon a Night. Sorry!", 
 //           "Fresnel::createScene");
 //       }
 //   }

 //  TexturePtr mTexture = TextureManager::getSingleton().createManual( "Refraction", 
	//	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, 
	//	512, 512, 0, PF_R8G8B8, TU_RENDERTARGET );
 //   //RenderTexture* rttTex = mRoot->getRenderSystem()->createRenderTexture( "Refraction", 512, 512 );
 //   RenderTarget *rttTex = mTexture->getBuffer()->getRenderTarget();
 //   {
 //       Viewport *v = rttTex->addViewport( mCameraManager->getActiveCamera() );
 //       MaterialPtr mat = MaterialManager::getSingleton().getByName("Examples/FresnelReflectionRefraction");
 //       mat->getTechnique(0)->getPass(0)->getTextureUnitState(2)->setTextureName("Refraction");
 //       v->setOverlaysEnabled(false);
 //   }
 //   
	//mTexture = TextureManager::getSingleton().createManual( "Reflection", 
	//	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, 
	//	512, 512, 0, PF_R8G8B8, TU_RENDERTARGET );
 //   //rttTex = mRoot->getRenderSystem()->createRenderTexture( "Reflection", 512, 512 );
 //   rttTex = mTexture->getBuffer()->getRenderTarget();
 //   {
	//	Viewport *v = rttTex->addViewport( mCameraManager->getActiveCamera() );
 //       MaterialPtr mat = MaterialManager::getSingleton().getByName("Examples/FresnelReflectionRefraction");
 //       mat->getTechnique(0)->getPass(0)->getTextureUnitState(1)->setTextureName("Reflection");
 //       v->setOverlaysEnabled(false);
 //   }

	//mEntity->setMaterialName("Examples/FresnelReflectionRefraction");

 //   //mEntity->setVisible(false);

 //   mReflectionPlane.normal = Vector3::UNIT_Y;
	//mReflectionPlane.d=0;

 //   //MeshManager::getSingleton().createPlane("ReflectPlane",
 //   //    ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
 //   //    mReflectionPlane,
 //   //    700,1300,10,10,true,1,3,5,Vector3::UNIT_Z);
 //   //pPlaneEnt = mSceneMgr->createEntity( "plane", "ReflectPlane" );
 //   //pPlaneEnt->setMaterialName("Examples/FresnelReflectionRefraction");
 //   //mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(pPlaneEnt);
}


void RenderComponentWater::update(double elapsedTime)
{
	RenderComponent::update(elapsedTime);
}


void RenderComponentWater::postUpdate()
{
 //   //// Show plane and objects below the water
 //   mEntity->setVisible(true);
 //   //std::vector<Entity*>::iterator i, iend;
 //   //iend = belowWaterEnts.end();
 //   //for (i = belowWaterEnts.begin(); i != iend; ++i)
 //   //{
 //   //    (*i)->setVisible(true);
 //   //}
	//mGameWorldManager->getGameObjectOny()->getRenderComponentWater()->setVisible(true);
 //   mCameraManager->getActiveCamera()->disableReflection();
}


void RenderComponentWater::setMaterial(std::vector<std::string> & material)
{
	Ogre::SubEntity* subEnt;
	Ogre::MaterialPtr original_material;
	unsigned int i;

	for ( i = 0; i < mEntity->getNumSubEntities(); i++)
	{
		// Get the material of this sub entity and build the clone material name
		subEnt = mEntity->getSubEntity(i);
		original_material = subEnt->getMaterial();

		// Get/Create the clone material

		if (Ogre::MaterialManager::getSingleton().resourceExists(material[i]))
		{
			subEnt->setMaterial(Ogre::MaterialManager::getSingleton().getByName(material[i]));
		}
		else
		{
			Logger::getInstance()->log("[RenderComponentWater] material "+material[i]+" does not exist.");
		}
	}
}

void RenderComponentWater::setChangeWorldMaterials()
{
	setMaterial(mChangeWorldMaterial);
}

void RenderComponentWater::setDreamsMaterials()
{
	setMaterial(mDreamsMaterial);
}

void RenderComponentWater::setNightmaresMaterials()
{
	setMaterial(mNightmaresMaterial);
}

void RenderComponentWater::setChangeWorldFactor(double factor)
{
	Ogre::Technique * technique;
	Ogre::Pass * pass;
	Ogre::GpuProgramParametersSharedPtr params;
	unsigned int i;

	for ( i = 0; i < mChangeWorldMaterial.size(); i++)
	{
		Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName(mChangeWorldMaterial[i]);

		if(material.get())
		{
			technique= material->getTechnique(0);
			if(technique)
			{
				if(technique->getNumPasses()>0)
				{
					pass=technique->getPass(0);
					if(pass->hasFragmentProgram())
					{
						params=pass->getFragmentProgramParameters();

						if(params.get())
						{
							params->setNamedConstant("mix_factor",Ogre::Real(factor));
						}
					}
				}
			}
		}
	}
}

TRenderComponentWaterParameters::TRenderComponentWaterParameters() : TRenderComponentParameters()
{

}

TRenderComponentWaterParameters::~TRenderComponentWaterParameters()
{

}

