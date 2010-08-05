#include "OUAN_Precompiled.h"

#include "RenderComponentDecal.h"

#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameObject/GameObjectTerrainTriangle.h"
#include "../RenderComponent/RenderComponentEntity.h"
using namespace OUAN;

RenderComponentDecal::RenderComponentDecal(Ogre::SceneManager* sceneManager)
:RenderComponent(COMPONENT_TYPE_RENDER_DECAL)
,mSceneManager(sceneManager)
,mFrustum(NULL)
,mFilterFrustum(NULL)
,mProjectorNode(NULL)
,mVisible(false)
{
	mTargets.clear();
}
RenderComponentDecal::~RenderComponentDecal()
{

}

void RenderComponentDecal::initProjector(const std::string& 
	projectorName, const std::string& textureName,
	const Ogre::Vector3& projectorOffset,Ogre::SceneNode* projectorNode)
{
	mFrustum= new Ogre::Frustum();

	// Init projector
	mProjectorName = projectorName;
	mProjectorNode = projectorNode->createChildSceneNode(mProjectorName+DECAL_PROJECTOR_NODE_SUFFIX);
	mProjectorNode->attachObject(mFrustum);
	mProjectorNode->setPosition(projectorOffset);
	mTextureName=textureName;
}
void RenderComponentDecal::initFilterProjector(const std::string& filterTextureName)
{
	// Init projector filter, to prevent a back projection
	mFilterFrustum = new Ogre::Frustum();
	mFilterFrustum->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	
	if (mProjectorNode)
	{
		Ogre::SceneNode *filterNode = mProjectorNode->createChildSceneNode(mProjectorName+DECAL_FILTER_PROJECTOR_NODE_SUFFIX);
		filterNode->attachObject(mFilterFrustum);
		filterNode->setOrientation(Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_Y));
		mFilterTextureName=filterTextureName;
	}
}

void RenderComponentDecal::createProjector(TRenderComponentDecalParameters decalParams, Ogre::SceneManager* sceneManager, TGameObjectContainer *objs)
{
	destroyProjector();
	mSceneManager = sceneManager;

	mFrustum= new Ogre::Frustum();

	// Init projector
	mProjectorName = decalParams.projectorName;
	mProjectorNode = decalParams.projectorNode->createChildSceneNode(mProjectorName+DECAL_PROJECTOR_NODE_SUFFIX);
	mProjectorNode->attachObject(mFrustum);
	mProjectorNode->setPosition(decalParams.projectorOffset);
	mTextureName=decalParams.textureName;
	mTintColour.setAsRGBA(decalParams.tintColour);

	// Init projector filter, to prevent a back projection
	mFilterFrustum = new Ogre::Frustum();
	mFilterFrustum->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	Ogre::SceneNode *filterNode = mProjectorNode->createChildSceneNode(mProjectorName+DECAL_FILTER_PROJECTOR_NODE_SUFFIX);
	filterNode->attachObject(mFilterFrustum);
	filterNode->setOrientation(Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_Y));
	mFilterTextureName=decalParams.filterTextureName;
	mVisible=false;
}
void RenderComponentDecal::destroyProjector()
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
void RenderComponentDecal::stopMaterialsFromReceivingDecal()
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
void RenderComponentDecal::makeMaterialsReceiveDecal()
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
				pass->setDepthWriteEnabled(false);
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
void RenderComponentDecal::changeColour(int tintColour)
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
void RenderComponentDecal::show()
{
	if (!mVisible)
	{
		makeMaterialsReceiveDecal();
		mVisible=true;
	}

}
void RenderComponentDecal::hide()
{
	if (mVisible)
	{
		mVisible=false;
		stopMaterialsFromReceivingDecal();
	}

}
bool RenderComponentDecal::isVisible() const
{
	return mVisible;
}
void RenderComponentDecal::setVisible(bool isVisible)
{
	mVisible=isVisible;
}

void RenderComponentDecal::loadMaterials(TGameObjectContainer& gameObjects)
{
	Ogre::Entity* entity;
	GameObjectPtr obj;
	std::string objType;
	if (!gameObjects.empty())
		for (TGameObjectContainerIterator it=gameObjects.begin();
			it!=gameObjects.end();++it)
		{
			// NOTE: Ideally, there should be a set of already processed game
			// objects so we avoid processing them again.
			// However, since there are instances of the same type using
			// different materials, we can't do that, so we'll
			//be only filtering by material names.
			obj=it->second;
			if (existsEntity(obj))
			{		
				entity=obj->getEntityComponent()->getEntity();
				objType=obj->getType();
				if (objType.compare(GAME_OBJECT_TYPE_TERRAINTRIANGLE)==0)
					loadGOTerrainTriangleMaterials(obj);
				else loadSubEnts(entity);
			}
		}
}
bool RenderComponentDecal::existsEntity(GameObjectPtr obj)
{
	return obj->hasRenderComponentEntity() && 
		obj->getEntityComponent().get() && 
		obj->getEntityComponent()->getEntity();
}
bool RenderComponentDecal::isValidSubentity(Ogre::SubEntity* subEnt)
{
	return subEnt && !subEnt->getMaterial().isNull() &&
		mTargets.find(subEnt->getMaterial()->getName())==mTargets.end();
}
void RenderComponentDecal::loadSubEnts(Ogre::Entity* ent)
{
	for (unsigned int i=0;i<ent->getNumSubEntities();++i)
	{
		Ogre::SubEntity* subEnt = ent->getSubEntity(i);
		if (isValidSubentity(subEnt))
		{
			mTargets.insert(subEnt->getMaterial()->getName());
		}							
	}
}
void RenderComponentDecal::loadGOTerrainTriangleMaterials(GameObjectPtr obj)
{
	GameObjectTerrainTrianglePtr triangle = 
		BOOST_PTR_CAST(GameObjectTerrainTriangle,obj);
	if (triangle.get())
	{
		loadSubEnts(triangle->getRenderComponentEntityDreams()
			->getEntity());
		loadSubEnts(triangle->getRenderComponentEntityNightmares()
			->getEntity());
	}
}
void RenderComponentDecal::unloadMaterials()
{
	mTargets.clear();
}

TRenderComponentDecalParameters::TRenderComponentDecalParameters() : TRenderComponentParameters()
{

}

TRenderComponentDecalParameters::~TRenderComponentDecalParameters()
{

}
