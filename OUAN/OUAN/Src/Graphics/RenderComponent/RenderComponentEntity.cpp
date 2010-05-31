#include "RenderComponentEntity.h"
#include "ChangeWorldMaterial.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameWorldManager.h"
#include "../../Event/EventDefs.h"

using namespace OUAN;

RenderComponentEntity::RenderComponentEntity(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_ENTITY)
{
	mCurrentAnimation=NULL;
	mCurrentAnimationName="";
	mEntity=NULL;
}

RenderComponentEntity::~RenderComponentEntity()
{
	mEntity=NULL;
	for (TAnimationStateMap::iterator it=mAnimations.begin();it!=mAnimations.end();++it)
	{
		it->second=NULL;
	}
	mAnimations.clear();
}

Ogre::Entity* RenderComponentEntity::getEntity() const
{
	return mEntity;
}

void RenderComponentEntity::setEntity(Ogre::Entity* entity)
{
	Ogre::SubEntity* subEnt;
	Ogre::MaterialPtr original_material;
	unsigned int i;

	mEntity=entity;

	if(mEntity)
	{
		mOriginalMaterials.clear();

		for ( i = 0; i < mEntity->getNumSubEntities(); i++)
		{
			// Get the material of this sub entity and build the clone material name
			subEnt = mEntity->getSubEntity(i);
			original_material = subEnt->getMaterial();

			//Add material to the material stack 
			mOriginalMaterials.push_back(original_material->getName());
		}
	}
}

void RenderComponentEntity::setVisible(bool visible)
{
	mEntity->setVisible(visible);
}
void RenderComponentEntity::initAnimations(std::vector<TRenderComponentEntityAnimParams> entityAnimParams)
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
void RenderComponentEntity::changeAnimation(const std::string& newAnimation /*TODO: Add options*/)
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
Ogre::AnimationState* RenderComponentEntity::getCurrentAnimation() const
{
	return mCurrentAnimation;
}
std::string RenderComponentEntity::getCurrentAnimationName() const
{
	return mCurrentAnimationName;
}

bool RenderComponentEntity::isAnimated() const
{
	return mIsAnimated;
}
void RenderComponentEntity::update(double elapsedTime)
{
	unsigned int i;

	if (mCurrentAnimation && mCurrentAnimation->getEnabled())
	{
		mCurrentAnimation->addTime(elapsedTime);//check what time unit arrives here
		if (mCurrentAnimation->hasEnded())
		{
			AnimationEndedEventPtr evt = AnimationEndedEventPtr(new AnimationEndedEvent(getParent(), mCurrentAnimation->getAnimationName()));
			getParent()->getGameWorldManager()->addEvent(evt);
		}
	}

	for ( i=0; i<mChangeWorldMaterials.size(); i++)
	{
		mChangeWorldMaterials[i]->update(elapsedTime);
	}
}
void RenderComponentEntity::attachGameObjectToBone(const std::string& boneName,GameObjectPtr gameObject)
{
	bool isValidEntity = mEntity->hasSkeleton() && mEntity->getSkeleton()->hasBone(boneName);
	bool isValidGO = gameObject.get() && gameObject->hasRenderComponentEntity() && !gameObject->getEntityComponent()->getEntity()->isAttached();
	if ( isValidEntity && isValidGO)
	{		
		mEntity->attachObjectToBone(boneName,gameObject->getEntityComponent()->getEntity());
	}
	else
	{
		std::string msg = "RCENTITY - Invalid attempt to attach ";
		msg.append(gameObject.get()?gameObject->getName():"NULL");
		msg.append(" game object to ").append(getParent()->getName());
		Logger::getInstance()->log(msg);
	}
		
}
void RenderComponentEntity::detachGameObject(GameObjectPtr gameObject)
{
	if (gameObject.get() && gameObject->hasRenderComponentEntity())
	{
		mEntity->detachObjectFromBone(gameObject->getEntityComponent()->getEntity());
	}
}

void RenderComponentEntity::setMaterial(std::string material)
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
			Logger::getInstance()->log("[RenderComponentEntity] material "+material+" does not exist.");
		}

		//Add material to the material stack 
		mOriginalMaterials.push_back(original_material->getName());
	}
}

void RenderComponentEntity::setOriginalMaterials()
{
	Ogre::SubEntity* subEnt;
	unsigned int i;

	for ( i = 0; i < mEntity->getNumSubEntities(); i++)
	{
		// Get the material of this sub entity and build the clone material name
		subEnt = mEntity->getSubEntity(i);

		// Get/Create the clone material

		if (Ogre::MaterialManager::getSingleton().resourceExists(mOriginalMaterials[i]))
		{
			subEnt->setMaterial(Ogre::MaterialManager::getSingleton().getByName(mOriginalMaterials[i]));
		}
		else
		{
			Logger::getInstance()->log("[RenderComponentEntity] material "+mOriginalMaterials[i]+" does not exist.");
		}
	}
}

void RenderComponentEntity::setChangeWorldMaterials()
{
	//Logger::getInstance()->log("[RenderComponentEntity] setChangeWorldMaterials "+mEntity->getName());

	Ogre::SubEntity* subEnt;
	unsigned int i;

	for ( i = 0; i < mChangeWorldMaterials.size() && i <mEntity->getNumSubEntities(); i++)
	{

		subEnt = mEntity->getSubEntity(i);

		// Get/Create the clone material

		if (Ogre::MaterialManager::getSingleton().resourceExists(mChangeWorldMaterials[i]->getMaterialName()))
		{
			subEnt->setMaterial(Ogre::MaterialManager::getSingleton().getByName(mChangeWorldMaterials[i]->getMaterialName()));
		}
		else
		{
			Logger::getInstance()->log("[RenderComponentEntity] material "+mChangeWorldMaterials[i]->getMaterialName()+" does not exist.");
		}
	}
}

void RenderComponentEntity::initChangeWorldMaterials(TChangeWorldMaterialParameters tChangeWorldMaterialParameters)
{
	unsigned int i;
	
	ChangeWorldMaterialPtr pChangeWorldMaterial;

	mChangeWorldMaterials.clear();

	bool materialCreated;

	for ( i = 0; i < mEntity->getNumSubEntities() ; i++)
	{

		pChangeWorldMaterial.reset(new ChangeWorldMaterial());

		materialCreated=pChangeWorldMaterial->init(mEntity->getName(),tChangeWorldMaterialParameters,
			mEntity->getSubEntity(i)->getMaterial());

		if(materialCreated)
		{
			mEntity->getSubEntity(i)->setMaterialName(pChangeWorldMaterial->getMaterialName());
			mChangeWorldMaterials.push_back(pChangeWorldMaterial);
		}
		//else
		//{
		//	mChangeWorldMaterials.push_back(mEntity->getSubEntity(i)->getMaterial()->getName());
		//}

	}
	//for ( ; i < mEntity->getNumSubEntities(); i++)
	//{
	//	mChangeWorldMaterials.push_back(mEntity->getSubEntity(i)->getMaterial()->getName());
	//}

	setChangeWorldMaterials();
}

void RenderComponentEntity::initChangeWorldMaterials(TChangeWorldMaterialParameters tChangeWorldMaterialParameters,RenderComponentEntityPtr pOtherComponentEntity)
{
	unsigned int i;

	Ogre::Entity * pOtherEntity;

	ChangeWorldMaterialPtr pChangeWorldMaterial;

	pOtherEntity=pOtherComponentEntity->getEntity();

	if(!pOtherEntity)
	{
		initChangeWorldMaterials(tChangeWorldMaterialParameters);
		return;
	}

	mChangeWorldMaterials.clear();

	bool materialCreated;

	for ( i = 0; (i < mEntity->getNumSubEntities()) &&  (i < pOtherEntity->getNumSubEntities()) ; i++)
	{

		pChangeWorldMaterial.reset(new ChangeWorldMaterial());

		materialCreated=pChangeWorldMaterial->init(mEntity->getName(),tChangeWorldMaterialParameters,
			mEntity->getSubEntity(i)->getMaterial(),
			pOtherEntity->getSubEntity(i)->getMaterial());

		if(materialCreated)
		{
			mEntity->getSubEntity(i)->setMaterialName(pChangeWorldMaterial->getMaterialName());
			mChangeWorldMaterials.push_back(pChangeWorldMaterial);
		}
		//else
		//{
		//	mChangeWorldMaterials.push_back(mEntity->getSubEntity(i)->getMaterial()->getName());
		//}
	}
	//for ( ; i < mEntity->getNumSubEntities(); i++)
	//{
	//	mChangeWorldMaterials.push_back(mEntity->getSubEntity(i)->getMaterial()->getName());
	//}

	setChangeWorldMaterials();
}

void RenderComponentEntity::setChangeWorldFactor(double factor)
{
	//Logger::getInstance()->log("[RenderComponentEntity] setChangeWorldFactor "+mEntity->getName());
	unsigned int i;
	for(i=0;i<mChangeWorldMaterials.size();i++)
	{
		mChangeWorldMaterials[i]->setChangeWorldFactor(factor);
	}
}

void RenderComponentEntity::setChangeWorldMaterialsPointOfInterest(Vector3 pointOfInterest)
{
	//Logger::getInstance()->log("[RenderComponentEntity] setChangeWorldFactor "+mEntity->getName());
	unsigned int i;
	for(i=0;i<mChangeWorldMaterials.size();i++)
	{
		mChangeWorldMaterials[i]->setPointOfInterest(pointOfInterest);
	}
}

void RenderComponentEntity::randomizeChangeWorldMaterials()
{
	unsigned int i;
	for(i=0;i<mChangeWorldMaterials.size();i++)
	{
		mChangeWorldMaterials[i]->randomize();
	}
}


//--- Entity parameters

TRenderComponentEntityParameters::TRenderComponentEntityParameters() : TRenderComponentParameters()
{

}

TRenderComponentEntityParameters::~TRenderComponentEntityParameters()
{

}
//--- Subentities parameters

TRenderComponentSubEntityParameters::TRenderComponentSubEntityParameters() : TRenderComponentParameters()
{

}


TRenderComponentSubEntityParameters::~TRenderComponentSubEntityParameters()
{

}

//--- Entity animation parameters

TRenderComponentEntityAnimParams::TRenderComponentEntityAnimParams()
:TRenderComponentParameters()
{

}
TRenderComponentEntityAnimParams::~TRenderComponentEntityAnimParams()
{

}
