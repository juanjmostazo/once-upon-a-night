#ifndef RenderComponentWaterH_H
#define RenderComponentWaterH_H

#include "RenderComponent.h"
#include "RenderComponentEntity.h"
#include "../CameraManager/CameraManager.h"
#include "../../Game/GameWorldManager.h"
namespace OUAN
{
	typedef std::map<std::string, Ogre::AnimationState*> TAnimationStateMap;
	class RenderComponentWater: public RenderComponent
	{
	private:

		Ogre::Plane mReflectionPlane;
		Ogre::Entity * mEntity;
		CameraManagerPtr mCameraManager;
		GameWorldManagerPtr mGameWorldManager;

		/// Map with the set of animation state pointers that are available for the entity, 
		/// so they can be easily accessed.
		TAnimationStateMap mAnimations;
		
		/// Current animation playing (Perhaps we might keep track of two active animations, for blending purposes)
		std::string mCurrentAnimationName;
		Ogre::AnimationState* mCurrentAnimation;
		
		/// This can be replaced with a mAnimations.empty() check
		bool mIsAnimated;

	public:

		RenderComponentWater(const std::string& type="");
		~RenderComponentWater();

		Ogre::Entity * getEntity() const;
		void setEntity(Ogre::Entity *);

		void setVisible(bool visible);

		void update(double elapsedTime);
		void postUpdate();

		void initAnimations(std::vector<TRenderComponentEntityAnimParams> entityAnimParams);
		void initFresnelReflection(CameraManagerPtr pCameraManager,GameWorldManagerPtr pGameWorldManager);
		void changeAnimation(const std::string& newAnimation /*TODO: Add options*/);
		Ogre::AnimationState* getCurrentAnimation() const;
		std::string getCurrentAnimationName() const;
		bool isAnimated() const;	
	};


	class TRenderComponentWaterParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentWaterParameters();
		~TRenderComponentWaterParameters();

		TRenderComponentEntityParameters tRenderComponentEntityParameters;

	};
}

#endif