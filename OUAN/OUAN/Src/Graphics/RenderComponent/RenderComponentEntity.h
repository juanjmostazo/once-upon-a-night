#ifndef RenderComponentEntityH_H
#define RenderComponentEntityH_H

#include "RenderComponent.h"
#include "../AnimationBlender/AnimationBlender.h"

namespace OUAN
{
	struct TTransitionData
	{
		std::string source;
		std::string target;
		AnimationBlender::TBlendingTransition blendType;
		float duration;
		//TODO: Allow definition of a map as well
		std::vector<std::string> sourceBlendMask;
		std::vector<std::string> targetBlendMask;
	};
	typedef std::map<std::string,TTransitionData> TTransitionMap;

	struct TAnimationData
	{
		std::string name;
		bool loop;
		float timescale;
		TTransitionMap transitions;
	};

	typedef std::map<std::string, TAnimationData> TAnimationStateMap;
	
	
	class RenderComponentEntity: public RenderComponent
	{
	private:
		Ogre::Entity * mEntity;

		AnimationBlender* mAnimationBlender;

		/// Map with the set of animation state pointers that are available for the entity, 
		/// so they can be easily accessed.
		TAnimationStateMap mAnimations;
		
		/// This can be replaced with a mAnimations.empty() check
		bool mIsAnimated;

		std::vector<std::string> mDreamsMaterial;
		std::vector<std::string> mNightmaresMaterial;
		std::vector<std::string> mChangeWorldMaterial;

		Ogre::ColourValue mTintColour;
		std::map<int,std::string> mOldMaterials;

	public:

		RenderComponentEntity(const std::string& type="");
		~RenderComponentEntity();

		void initAnimationBlender(const std::string& defaultAnimation);
		void destroyAnimationBlender();
		bool isLoopingAnimation (const std::string& animationName);
		bool hasFinishedAnimation(const std::string& animationName);
		bool hasAnimationBlender() const;

		void changeAnimation(const std::string& anim);
		bool hasAnimation(const std::string& anim);

		void changeAnimation(const std::string& animation,AnimationBlender::TBlendingTransition transition, 
			float duration, bool l=true, float timeScale=1.0);
		void setAnimationBlenderVertexKeyMap(const TKeyFrameMap& keyFrameMap);

		double getMaxBoundingBoxY();

		Ogre::Entity * getEntity() const;
		void setEntity(Ogre::Entity *,bool existInDreams,bool existInNightmares);

		void setVisible(bool visible);
		bool isVisible();

		void update(double elapsedTime);

		void initAnimations(std::vector<TRenderComponentEntityAnimParams> entityAnimParams);
		void setAnimationPosition(float pos);
		float getAnimationPosition() const;
		float getCurrentAnimationLength() const;
		
		Ogre::AnimationState* getCurrentAnimation() const;
		std::string getCurrentAnimationName() const;
		bool isAnimated() const;

		void attachGameObjectToBone(const std::string& boneName,GameObjectPtr gameObject);
		void detachGameObject(GameObjectPtr gameObject);

		void setMaterial(std::vector<std::string> & material);
		void setDreamsMaterials();
		void setNightmaresMaterials();
		void setChangeWorldMaterials();
		void setChangeWorldFactor(double factor);

		void setNewMaterial(std::string material,bool existInDreams,bool existInNightmares);

		void applyTint(const Ogre::ColourValue& tintColour);
		void removeTint();
		void setTintFactor(double tintFactor);
		bool isTintBeingApplied() const;

		//void prepareForNormalMapping();

	};
	class TRenderComponentEntityAnimParams: public TRenderComponentParameters{
		public: 
			TRenderComponentEntityAnimParams();
			~TRenderComponentEntityAnimParams();
			
			std::string name;
			bool loop;
			float timescale;
			TTransitionMap transitions;
	};
	class TRenderComponentSubEntityParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentSubEntityParameters();
		~TRenderComponentSubEntityParameters();

		String material;
		bool visible;
	};

	class TRenderComponentEntityParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentEntityParameters();
		~TRenderComponentEntityParameters();

		String meshfile;
		bool castshadows;
		QueryFlags cameraCollisionType;
		bool prepareForNormalMapping;

		std::vector<TRenderComponentSubEntityParameters> tRenderComponentSubEntityParameters;
		std::vector<TRenderComponentEntityAnimParams> tRenderComponentEntityAnimParams;

		Ogre::uint8 queueID;

		bool mInitManualAnimations;
		std::string mManualAnimationName;
		std::string initialAnimation;
		std::string initialAnimationAlt;
		std::string initialAnimationAlt2;
		std::string initialAnimationAlt3;
	};
}

#endif