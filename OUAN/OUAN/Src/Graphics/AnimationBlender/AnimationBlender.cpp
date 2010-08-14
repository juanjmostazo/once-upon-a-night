#include "OUAN_Precompiled.h"

#include "AnimationBlender.h"
using namespace OUAN;

AnimationBlender::AnimationBlender( Ogre::Entity *entity ) : mEntity(entity) 
,mSource(NULL)
,mTarget(NULL)
,mManualAnimation(NULL)
,mSrcTimeScale(1.0)
,mTgtTimeScale(1.0)
,mManualAnimationTimeScale(1.0)
{
}

AnimationBlender::~AnimationBlender()
{
	mEntity=NULL;
	mSource=NULL;
	mTarget=NULL;
	mManualAnimation=NULL;
	mVertexPoseKeyFrames.clear();
}

//-----Initializers

void AnimationBlender::init(const std::string&animation, const std::vector<std::string>& bones,
							bool loop, float timescale)
{
	_init(animation,loop,timescale);

	if (!bones.empty())
	{
		mSource->createBlendMask(mEntity->getSkeleton()->getNumBones());
		loadBoneMask(mSource,bones);
	}
	else mSource->destroyBlendMask();
	
}

void AnimationBlender::init(const std::string&animation, bool loop, float timescale,
							std::map<std::string,float>* bones)
{
	_init(animation,loop,timescale);

	if (bones)
	{
		mSource->createBlendMask(mEntity->getSkeleton()->getNumBones());
		loadBoneMask(mSource,bones);
	}
	else mSource->destroyBlendMask();
}

void AnimationBlender::_init(const std::string &animation, bool l, float timescale)
{
	Ogre::AnimationStateSet *set = mEntity->getAllAnimationStates();
	if (set)
	{
		Ogre::AnimationStateIterator it = set->getAnimationStateIterator();
		while(it.hasMoreElements())
		{
			Ogre::AnimationState *anim = it.getNext();
			anim->setEnabled(false);
			anim->setWeight(0);
			anim->setTimePosition(0);
		}

		mSource = mEntity->getAnimationState( animation );
		mSource->setEnabled(true);
		mSource->setWeight(1);
		mSrcTimeScale=timescale;
		mTimeleft = 0;
		mDuration = 1;
		mTarget = 0;
		mComplete = false;
		mLoop = l;

		mManualAnimation = NULL;
	}

}

//-----Update methods

void AnimationBlender::blend(const std::string& animation, TBlendingTransition transition,	
		   float duration, bool l, float timescale, std::map<std::string,float>* bones)
{
	Ogre::AnimationState* tgt=_blend(animation,transition,duration,l,timescale);
	if (tgt && bones)
	{
		tgt->createBlendMask(mEntity->getSkeleton()->getNumBones());
		loadBoneMask(tgt,bones);
	}
	else if (tgt)
		tgt->destroyBlendMask();
}

void AnimationBlender::blend(const std::string& animation, 	TBlendingTransition transition,	
							float duration,  const std::vector<std::string>& bones,
							 bool l, float timescale)
{
	Ogre::AnimationState* tgt=_blend(animation,transition,duration,l,timescale);
	if (tgt && !bones.empty())
	{
		tgt->createBlendMask(mEntity->getSkeleton()->getNumBones());
		loadBoneMask(tgt,bones);
	}
	else if (tgt)
		tgt->destroyBlendMask();
}


Ogre::AnimationState* AnimationBlender::_blend( const std::string& animation, TBlendingTransition transition, float duration,bool l, float timescale)
{
	mLoop = l;
	Ogre::AnimationState* retVal=NULL;//Animation to apply the bone mask if necessary
	if( transition == AnimationBlender::BT_SWITCH)
	{
		// No blending; just disable the last animation state, and replace
		// it with the target animation
		if( mSource != 0 )
			mSource->setEnabled(false);
		mSource = mEntity->getAnimationState( animation );
		mSource->setEnabled(true);
		mSource->setWeight(1);
		mSource->setTimePosition(0);
		mSrcTimeScale=timescale;
		mTimeleft = 0;
		retVal=mSource;
	} 
	else 
	{ 
		Ogre::AnimationState *newTarget = mEntity->getAnimationState( animation );
		if( mTimeleft > 0 )
		{
			// oops, weren't finished yet
			if( newTarget == mTarget )
			{/* nothing to do! (ignoring duration here)*/}
			else if( newTarget == mSource )
			{
				// going back to the source state, so let's switch
				mSource = mTarget;
				mTarget = newTarget;
				mTimeleft = mDuration - mTimeleft; // i'm ignoring the new duration here
			}
			else
			{
				// ok, newTarget is really new, so either we simply replace the target with this one, or
				// we make the target the new source
				if( mTimeleft < mDuration * 0.5 )
				{
					// simply replace the target with this one
					mTarget->setEnabled(false);
					mTarget->setWeight(0);
				}
				else
				{
					// old target becomes new source
					mSource->setEnabled(false);
					mSource->setWeight(0);
					mSource = mTarget;
				} 
				mTarget = newTarget;
				mTarget->setEnabled(true);
				mTarget->setWeight( 1.0 - mTimeleft / mDuration );
				mTarget->setTimePosition(0);
				mTgtTimeScale=timescale;
				retVal=mTarget;
			}
		}
		else
		{
			// assert( target == 0, "target should be 0 when not blending" )
			// mSource->setEnabled(true);
			// mSource->setWeight(1);
			mTransition = transition;
			mTimeleft = mDuration = duration;
			mTarget = newTarget;
			mTarget->setEnabled(true);
			mTarget->setWeight(0);
			mTarget->setTimePosition(0);
			mTgtTimeScale=timescale;
			retVal=mTarget;
		}
	}
	return retVal;
}
void AnimationBlender::addTime( float time )
{
	if( mSource != 0 )
	{
		if( mTimeleft > 0 )
		{
			mTimeleft -= time;
			if( mTimeleft < 0 )
			{
				// finish blending
				mSource->setEnabled(false);
				mSource->setWeight(0);
				mSource = mTarget;
				mSource->setEnabled(true);
				mSource->setWeight(1);
				mTarget = 0;
			}
			else
			{
				// still blending, advance weights
				mSource->setWeight(mTimeleft / mDuration);
				mTarget->setWeight(1.0 - mTimeleft / mDuration);
				if(mTransition == AnimationBlender::BT_WHILEANIMATING)
					mTarget->addTime(time*mTgtTimeScale);
			}
		}
		if (mSource->getTimePosition() >= mSource->getLength())
		{
			mComplete = true;
		}
		else
		{
			mComplete= false;
		}
		mSource->addTime(time*mSrcTimeScale);
		mSource->setLoop(mLoop);
		if (mManualAnimation)
		{
			mManualAnimation->addTime(time*mManualAnimationTimeScale);
		}
	}
}

//---------Bone mask management

void AnimationBlender::loadBoneMask(Ogre::AnimationState* target, const std::vector<std::string>& bones)
{
	if (mEntity && target && !bones.empty())
	{
		Ogre::Skeleton* skel=mEntity->getSkeleton();
		Ogre::Bone* b;
		Ogre::Skeleton::BoneIterator it=skel->getBoneIterator();
		while(it.hasMoreElements())
		{
			b=it.getNext(); //the it advances as well as getting the value
			if (std::find(bones.begin(),bones.end(),b->getName())!=bones.end())
			{
				target->setBlendMaskEntry(b->getHandle(),1.0);
			}
		}
	}
}
void AnimationBlender::loadBoneMask(Ogre::AnimationState* target, std::map<std::string,float>* bones)
{
	if (mEntity && target && bones && !bones->empty())
	{
		Ogre::Skeleton* skel=mEntity->getSkeleton();
		Ogre::Bone* b;
		Ogre::Skeleton::BoneIterator it=skel->getBoneIterator();
		while(it.hasMoreElements())
		{
			b=it.getNext(); //the it advances as well as getting the value
			if (bones->find(b->getName())!=bones->end())
			{
				std::string name=static_cast<std::string>(b->getName());
				target->setBlendMaskEntry(b->getHandle(),(*bones)[name]);
			}
		}
	}
}

//---- Utility getters

float AnimationBlender::getProgress()
{
	if (mDuration!=0.0)
		return mTimeleft/mDuration;
	return -1;
}
Ogre::AnimationState* AnimationBlender::getSource()
{
	return mSource;
}
Ogre::AnimationState* AnimationBlender::getTarget()
{
	return mTarget;
}

bool AnimationBlender::hasEnded() const
{
	return mComplete;
}

//-----------Manual animation management: The manual pose loading
// is done in the render subsystem!

//Modify the influence of the given pose
void AnimationBlender::updatePose(const std::string& poseName, float influence)
{
	//get the pose list
	Ogre::PoseList poseList = mEntity->getMesh()->getPoseList();
	int curPoseIndex = 0;
	//loop through each submesh
	int numSubMeshes = mEntity->getMesh()->getNumSubMeshes();
	//skip submesh 0 since it is the shared geometry, and we have no poses on that
	for(int curSubMesh = 1; curSubMesh <= numSubMeshes; curSubMesh++){
		//while the poses apply to the current submesh, check to see if the current pose matches the name, then get the next pose
		while(poseList[curPoseIndex]->getTarget() == curSubMesh){
			//get next pose and check if it's the one we want to update
			if(!poseList[curPoseIndex]->getName().compare(poseName)){
				//We found our pose, update it
				mVertexPoseKeyFrames[curSubMesh]->updatePoseReference(curPoseIndex, influence);
				// Dirty animation state since we're fudging this manually
				//If we don't notify dirty, Ogre doesn't know to update this state
				//and nothing happens
				mManualAnimation->getParent()->_notifyDirty();            
			}
			curPoseIndex++;
			if (curPoseIndex==poseList.size())
				break;
			//go to the next pose
		}
		//go to the next submesh
	}
}
void AnimationBlender::setManualAnimation(const std::string& manualAnimationName,float timeScale,bool loop,
										  float weight)
{
	resetManualAnimation();
	mManualAnimation=mEntity->getAnimationState(manualAnimationName);
	mManualAnimation->setWeight(weight);
	mManualAnimation->setEnabled(true);
	mManualAnimation->setLoop(loop);
}

void AnimationBlender::resetManualAnimation()
{
	if (mManualAnimation)
	{
		mManualAnimation->setWeight(0);
		mManualAnimation->setEnabled(false);
		mManualAnimation->setLoop(false);
		mManualAnimation=NULL;
	}
}
void AnimationBlender::setVertexPoseKeyFrames(const TKeyFrameMap& keyFrames)
{
	mVertexPoseKeyFrames=keyFrames;
}