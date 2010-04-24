#include "RenderComponentEntity.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameWorldManager.h"
#include "../../Event/EventDefs.h"
using namespace OUAN;

RenderComponentEntity::RenderComponentEntity(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_ENTITY)
{
	mCurrentAnimation=NULL;
	mCurrentAnimationName="";
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
	mEntity=entity;
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
					Ogre::LogManager::getSingletonPtr()->logMessage("ANIMATION STATE NOT FOUND: "+animName);
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
	if (mCurrentAnimation)
	{
		mCurrentAnimation->addTime(elapsedTime);//check what time unit arrives here
		if (mCurrentAnimation->hasEnded())
		{
			AnimationEndedEventPtr evt = AnimationEndedEventPtr(new AnimationEndedEvent(getParent(), mCurrentAnimation->getAnimationName()));
			getParent()->getGameWorldManager()->addEvent(evt);
		}
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
		Ogre::LogManager::getSingletonPtr()->logMessage(msg);
	}
		
}
void RenderComponentEntity::detachGameObject(GameObjectPtr gameObject)
{
	if (gameObject.get() && gameObject->hasRenderComponentEntity())
	{
		mEntity->detachObjectFromBone(gameObject->getEntityComponent()->getEntity());
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
