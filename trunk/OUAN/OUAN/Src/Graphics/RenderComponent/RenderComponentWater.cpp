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
	mCurrentAnimation=NULL;
	mCurrentAnimationName="";
}

RenderComponentWater::~RenderComponentWater()
{
	mEntity=NULL;
	for (TAnimationStateMap::iterator it=mAnimations.begin();it!=mAnimations.end();++it)
	{
		it->second=NULL;
	}
	mAnimations.clear();
}

Ogre::Entity* RenderComponentWater::getEntity() const
{
	return mEntity;
}

void RenderComponentWater::setEntity(Ogre::Entity* entity)
{
	mEntity=entity;

	if(mEntity)
	{
		mDreamsMaterial=WorldNameConverter::getDreamsName(mEntity->getSubEntity(0)->getMaterialName().c_str());
		mNightmaresMaterial=WorldNameConverter::getNightmaresName(mEntity->getSubEntity(0)->getMaterialName().c_str());
		mChangeWorldMaterial=WorldNameConverter::getChangeWorldName(mEntity->getSubEntity(0)->getMaterialName().c_str());
	}
}

void RenderComponentWater::setVisible(bool visible)
{
	mEntity->setVisible(visible);
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

void RenderComponentWater::initAnimations(std::vector<TRenderComponentEntityAnimParams> entityAnimParams)
{
	mAnimations.clear();
	mCurrentAnimationName="";
	if (mCurrentAnimation)
	{
		mCurrentAnimation=NULL; //Remember it is a pointer to an instance managed by Ogre, so we shouldn't delete it here.
	}
	if (!entityAnimParams.empty())
	{
		mIsAnimated=true;
		std::string animName;
		for (std::vector<TRenderComponentEntityAnimParams>::const_iterator it= entityAnimParams.begin();
			it!=entityAnimParams.end();++it)
		{
			if (mEntity)
			{
				animName=(*it).name;
				try
				{
					mAnimations[animName]=mEntity->getAnimationState(animName);
				}
				catch(Ogre::ItemIdentityException)
				{
					Logger::getInstance()->log("ANIMATION STATE NOT FOUND: "+animName);
				}
				if (mAnimations[animName])
				{
					mAnimations[animName]->setEnabled(false);
					mAnimations[animName]->setLoop((*it).loop);
				}
			}
		}
	}
	else mIsAnimated=false;
	//Initialise the animations mapping
}
void RenderComponentWater::changeAnimation(const std::string& newAnimation /*TODO: Add options*/)
{
	if (mCurrentAnimation)
		mCurrentAnimation->setEnabled(false);

	mCurrentAnimationName=newAnimation;
	mCurrentAnimation= mAnimations[newAnimation];
	if (mCurrentAnimation)
	{
		mCurrentAnimation->setEnabled(true);		
		mCurrentAnimation->setTimePosition(0);
	}
}
Ogre::AnimationState* RenderComponentWater::getCurrentAnimation() const
{
	return mCurrentAnimation;
}
std::string RenderComponentWater::getCurrentAnimationName() const
{
	return mCurrentAnimationName;
}

bool RenderComponentWater::isAnimated() const
{
	return mIsAnimated;
}

void RenderComponentWater::update(double elapsedTime)
{
	RenderComponent::update(elapsedTime);
	//if (mCurrentAnimation && mCurrentAnimation->getEnabled())
	//{
	//	mCurrentAnimation->addTime(elapsedTime);//check what time unit arrives here
	//	if (mCurrentAnimation->hasEnded())
	//	{
	//		AnimationEndedEventPtr evt = AnimationEndedEventPtr(new AnimationEndedEvent(getParent(), mCurrentAnimation->getAnimationName()));
	//		getParent()->getGameWorldManager()->addEvent(evt);
	//	}
	//}

 //   //// Hide plane and objects below the water
 //   mEntity->setVisible(false);
 //   //std::vector<Entity*>::iterator i, iend;
 //   //iend = belowWaterEnts.end();
 //   //for (i = belowWaterEnts.begin(); i != iend; ++i)
 //   //{
 //   //    (*i)->setVisible(false);
 //   //}
	//mGameWorldManager->getGameObjectOny()->getRenderComponentWater()->setVisible(false);
 //   mCameraManager->getActiveCamera()->enableReflection(mReflectionPlane);

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


void RenderComponentWater::setMaterial(std::string material)
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

		if (Ogre::MaterialManager::getSingleton().resourceExists(material))
		{
			subEnt->setMaterial(Ogre::MaterialManager::getSingleton().getByName(material));
		}
		else
		{
			Logger::getInstance()->log("[RenderComponentWater] material "+material+" does not exist.");
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


TRenderComponentWaterParameters::TRenderComponentWaterParameters() : TRenderComponentParameters()
{

}

TRenderComponentWaterParameters::~TRenderComponentWaterParameters()
{

}

