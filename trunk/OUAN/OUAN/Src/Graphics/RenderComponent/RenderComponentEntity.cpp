#include "RenderComponentEntity.h"
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
				mAnimations[animName]=mEntity->getAnimationState(animName);
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
		mCurrentAnimation->setEnabled(true);
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
		mCurrentAnimation->addTime(elapsedTime);//check what time unit arrives here
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
