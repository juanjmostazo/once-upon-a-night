#ifndef RenderComponentEntityH_H
#define RenderComponentEntityH_H

#include "RenderComponent.h"

namespace OUAN
{

	typedef std::map<std::string, Ogre::AnimationState*> TAnimationStateMap;
	class RenderComponentEntity: public RenderComponent
	{
	private:
		Ogre::Entity * mEntity;

		/// Map with the set of animation state pointers that are available for the entity, 
		/// so they can be easily accessed.
		TAnimationStateMap mAnimations;
		
		/// Current animation playing (Perhaps we might keep track of two active animations, for blending purposes)
		std::string mCurrentAnimationName;
		Ogre::AnimationState* mCurrentAnimation;
		
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

		Ogre::Entity * getEntity() const;
		void setEntity(Ogre::Entity *,bool existInDreams,bool existInNightmares);

		void setVisible(bool visible);
		bool isVisible();

		void update(double elapsedTime);

		void initAnimations(std::vector<TRenderComponentEntityAnimParams> entityAnimParams);
		void changeAnimation(const std::string& newAnimation /*TODO: Add options*/);
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
	};
}

#endif