#include "ProjectiveDecal.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../RenderComponent/ChangeWorldMaterial.h"
#include "../RenderComponent/RenderComponentEntity.h"
using namespace OUAN;

ProjectiveDecal::ProjectiveDecal()
:mSceneManager(NULL)
,mFrustum(NULL)
,mFilterFrustum(NULL)
,mProjectorNode(NULL)
,mVisible(false)
{

}
ProjectiveDecal::~ProjectiveDecal()
{

}

void ProjectiveDecal::createProjector(TDecalParams decalParams, Ogre::SceneManager* sceneManager, TGameObjectContainer *objs)
{
	destroyProjector();
	mSceneManager = sceneManager;
	
	mFrustum= new Ogre::Frustum();

	// Init projector
	mProjectorName = decalParams.projectorName;
	mProjectorNode = decalParams.projectorNode->createChildSceneNode(mProjectorName+DECAL_PROJECTOR_NODE_SUFFIX);
	mProjectorNode->attachObject(mFrustum);
	mProjectorNode->setPosition(decalParams.projectorOffset);//Fine-tune this, maybe pass a Vector parameter			
	mProjectorNode->setOrientation(mProjectorNode->getOrientation()*Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_Y));
	mTextureName=decalParams.textureName;
	mTintColour.setAsRGBA(decalParams.tintColour);

	// Init projector filter, to prevent a back projection
	mFilterFrustum = new Ogre::Frustum();
	mFilterFrustum->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	Ogre::SceneNode *filterNode = mProjectorNode->createChildSceneNode(mProjectorName+DECAL_FILTER_PROJECTOR_NODE_SUFFIX);
	filterNode->attachObject(mFilterFrustum);
	filterNode->setOrientation(Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_Y));
	mFilterTextureName=decalParams.filterTextureName;

	Ogre::Entity* entity;
	if (objs && !objs->empty())
	{
		for (TGameObjectContainerIterator it=objs->begin();it!=objs->end();++it)
		{
			//NOTE: Ideally, there should be a set of already processed game objects so we avoid processing them again.
			//However, since there are instances of the same type using different materials, we can't do that, so we'll
			//be only filtering by material names.
			if (it->second->hasRenderComponentEntity() && it->second->getEntityComponent().get() && 
				(entity=it->second->getEntityComponent()->getEntity()))
			{		
				if (it->second->getType().compare(GAME_OBJECT_TYPE_TERRAINTRIANGLE)==0 || 
					it->second->getType().compare(GAME_OBJECT_TYPE_TERRAINCONVEX)==0)
				{
					std::vector<std::string> origMatNames=it->second->getEntityComponent()->getOriginalMaterials();
					for (std::vector<std::string>::iterator it2 = origMatNames.begin();it2!=origMatNames.end();++it2)
					{
						if (mTargets.find(*it2)==mTargets.end())
						{
							mTargets.insert(*it2);
							Logger::getInstance()->log("Adding material" + Ogre::String(*it2));
						}
					}
					std::vector<ChangeWorldMaterialPtr> cwMats = it->second->getEntityComponent()->getChangeWorldMaterials();
					for (std::vector<ChangeWorldMaterialPtr>::iterator it2=cwMats.begin();it2!=cwMats.end();++it2)
					{
						if (mTargets.find((*it2)->getMaterialName())==mTargets.end())
						{
							mTargets.insert((*it2)->getMaterialName());
							Logger::getInstance()->log("Adding material" + Ogre::String((*it2)->getMaterialName()));
						}
					}
				}
				else
				{
					for (unsigned int i = 0; i < entity->getNumSubEntities(); ++i)
					{
						Ogre::SubEntity* subEnt = entity->getSubEntity(i);

						if (subEnt && !subEnt->getMaterial().isNull() && mTargets.find(subEnt->getMaterial()->getName())==mTargets.end())
						{
							mTargets.insert(subEnt->getMaterial()->getName());
						}
					}
				}
			}
		}

	}
	mVisible=false;
}
void ProjectiveDecal::destroyProjector()
{
	if(mSceneManager)
	{
		stopMaterialsFromReceivingDecal();
		mTargets.clear();
		if (mProjectorNode)
		{
			mSceneManager->destroySceneNode(mProjectorName+DECAL_FILTER_PROJECTOR_NODE_SUFFIX);
			mSceneManager->destroySceneNode(mProjectorNode); //this should remove its children nodes, but check just in case
			mProjectorNode=NULL;
		}
		if (mFrustum)
		{
			delete mFrustum;
			mFrustum=NULL;
		}
		if (mFilterFrustum)
		{
			delete mFilterFrustum;
			mFilterFrustum=NULL;
		}
		mSceneManager=NULL;
	}
	mVisible=false;	

}
void ProjectiveDecal::stopMaterialsFromReceivingDecal()
{
	if (!mTargets.empty())
	{
		for (std::set<std::string>::iterator it = mTargets.begin();it!=mTargets.end();++it)
		{
			std::string matName=*it;
			Ogre::MaterialPtr mat;
			Ogre::Pass* pass;
			if (!((mat=Ogre::MaterialManager::getSingletonPtr()->getByName(matName)).isNull()))
			{
				if (pass=mat->getTechnique(0)->getPass(mProjectorName+DECAL_PASS_SUFFIX))
				{
					mat->getTechnique(0)->removePass(pass->getIndex());
					pass=NULL;
				}
			}
		}
	}
}
void ProjectiveDecal::makeMaterialsReceiveDecal()
{
	if (!mTargets.empty())
	{
		for (std::set<std::string>::iterator it = mTargets.begin();it!=mTargets.end();++it)
		{
			Ogre::MaterialPtr mat=Ogre::MaterialManager::getSingletonPtr()->getByName(*it);
			if (!mat.isNull() && !mat->getTechnique(0)->getPass(mProjectorName+DECAL_PASS_SUFFIX))
			{
				// create a new pass in the material to render the decal
				Ogre::Pass *pass = mat->getTechnique(0)->createPass();
				pass->setName(mProjectorName+DECAL_PASS_SUFFIX);

				// set our pass to blend the decal over the model's regular texture
				pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
				pass->setDepthBias(1); //Z-fighting fix

				// set the decal to be self illuminated instead of lit by scene lighting
				pass->setLightingEnabled(false);

				// set up the decal's texture unit
				Ogre::TextureUnitState *texState = pass->createTextureUnitState(mTextureName);
				texState->setProjectiveTexturing(true, mFrustum);
				texState->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP);
				texState->setTextureFiltering(Ogre::FO_POINT, Ogre::FO_LINEAR, Ogre::FO_NONE);
				texState->setColourOperationEx(Ogre::LBX_MODULATE,Ogre::LBS_MANUAL,Ogre::LBS_CURRENT,mTintColour);

				// set up the filter texture's texture unit
				texState = pass->createTextureUnitState(mFilterTextureName);
				texState->setProjectiveTexturing(true, mFilterFrustum);
				texState->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP);
				texState->setTextureFiltering(Ogre::TFO_NONE);

				//if (mat->getTechnique(0)->getNumPasses()>1)
				//	mat->getTechnique(0)->movePass(pass->getIndex(),mat->getTechnique(0)->getNumPasses()-1);
			}
		}		
	}
}
void ProjectiveDecal::changeColour(int tintColour)
{
	mTintColour.setAsRGBA(tintColour);
	if (!mTargets.empty())
	{
		for (std::set<std::string>::iterator it = mTargets.begin();it!=mTargets.end();++it)
		{
			Ogre::MaterialPtr mat=Ogre::MaterialManager::getSingletonPtr()->getByName(*it);
			Ogre::Pass* pass;
			if (!mat.isNull() && (pass=mat->getTechnique(0)->getPass(mProjectorName+DECAL_PASS_SUFFIX))!=NULL)
			{
				Ogre::TextureUnitState *texState = pass->getTextureUnitState(mTextureName);
				if (texState)
					texState->setColourOperationEx(Ogre::LBX_MODULATE,Ogre::LBS_MANUAL,Ogre::LBS_CURRENT,mTintColour);
			}
		}
	}
}
void ProjectiveDecal::show()
{
	if (!mVisible)
	{
		makeMaterialsReceiveDecal();
		mVisible=true;
	}
	
}
void ProjectiveDecal::hide()
{
	if (mVisible)
	{
		mVisible=false;
		stopMaterialsFromReceivingDecal();
	}
	
}
bool ProjectiveDecal::isVisible() const
{
	return mVisible;
}
void ProjectiveDecal::setVisible(bool isVisible)
{
	mVisible=isVisible;
}