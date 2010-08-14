#ifndef ANIMATIONBLENDERH_H
#define ANIMATIONBLENDERH_H
namespace OUAN
{	
	//--------------------------------------------------------------
	// This class will combine the following two Ogre Wiki articles,		
	// plus several other enhancements.										
	// It'll be used to control animation blending							
	// http://www.ogre3d.org/tikiwiki/AnimationBlender						
	// http://www.ogre3d.org/tikiwiki/Generic+Manual+Pose+Loading			
	//--------------------------------------------------------------
	class AnimationBlender
	{
	public:
		enum TBlendingTransition
		{
			BT_SWITCH,			// Stop source and start dest
			BT_WHILEANIMATING,	// Cross fade, blend source animation out 
								//	while blending destination animation in
			BT_THENANIMATE,		// Blend source to first frame of dest, when done, start dest anim
			BT_MIX,				// Blend several animations together. (TODO)
		};

	private:
		Ogre::Entity *mEntity;
		
		//TODO: Replace with vectors to allow complex blends
		Ogre::AnimationState *mSource;
		float mSrcTimeScale;
		
		Ogre::AnimationState *mTarget;
		float mTgtTimeScale;
		
		//Support for manual pose animation: typically, facial animations
		Ogre::AnimationState *mManualAnimation;
		
		//Manual pose related attributes
		float mManualAnimationTimeScale;
		TKeyFrameMap mVertexPoseKeyFrames;
		
		float mTimeleft, mDuration;

		TBlendingTransition mTransition;

		bool mLoop;
		bool mLoopManual;

		bool mComplete;

		void loadBoneMask(Ogre::AnimationState* target, const std::vector<std::string>& bones);
		void loadBoneMask(Ogre::AnimationState* target, std::map<std::string,float>* bones);

		void _init( const std::string &animation, bool l=true, float timeScale=1.0);
		Ogre::AnimationState* _blend(const std::string& animation, TBlendingTransition transition, float duration, bool l=true, float timeScale=1.0);

	public: 
		AnimationBlender( Ogre::Entity *);
		/**
		*	@param	animation	name of the target animation to change to
		*	@param	transition	type of the animation transition to make
		*	@param	duration	for blending transitions, the fading duration
		*	@param	l			loop target animation
		*	@param	bones		array containing the bones that'll take part in the blending
		*						every other bone's weight will be set to 0
		*/
		void blend( const std::string& animation, TBlendingTransition transition, 
			float duration, const std::vector<std::string>& bones,bool l=true, float timeScale=1.0);
		void blend( const std::string& animation, TBlendingTransition transition, 
			float duration, bool l=true, float timeScale=1.0, std::map<std::string,float>* bones=NULL);

		void addTime(float);

		float getProgress(); //{ return mTimeleft/ mDuration; }
		Ogre::AnimationState *getSource();
		Ogre::AnimationState *getTarget();
		
		void init( const std::string &animation, const std::vector<std::string>& bones,
			bool l=true,float timeScale=1.0);
		void init( const std::string& animation, bool l=true, float timeScale=1.0,
			std::map<std::string,float>* bones=NULL);

		//This is to be loaded BEFORE the entity!
		void setManualAnimation(const std::string& manualAnimationName,float timeScale, 
			bool loop,float weight=1.0f);

		//Modify the influence of the given pose
		void updatePose(const std::string& poseName, float influence);
		
		//Disable manual animation
		void resetManualAnimation();


		~AnimationBlender() {}
	};

}

#endif