#ifndef TransparentEntityH_H
#define TransparentEntityH_H
#include "../../OUAN.h"
namespace OUAN
{
	class TransparentEntity
	{
	public:
		TransparentEntity();
		~TransparentEntity();

		void init(Ogre::Entity * pEntity,double minAlphaBlending,double alphaBlendingTime);

		void makeSolid();
		void makeTransparent();

		bool isSolid();
		bool isTransparent();

		void clear();

		void update(double elapsedTime);

		std::string getName();

	protected:
		Ogre::Entity * mEntity;
		std::vector<std::string> mSolidMaterial;
		std::vector<std::string> mTransparentMaterial;
		std::vector<Ogre::TextureUnitState *> mTransparentMaterialTextures;

		//Ogre::uint8 originalRenderQueue;

		double mMinAlphaBlending;
		double mAlphaBlendingSpeed;
		double mCurrentAlpha;

		enum TransparentEntityState
		{
			TES_SOLID,
			TES_TRANSPARENT,
			TES_MAKING_SOLID,
			TES_MAKING_TRANSPARENT
		};

		TransparentEntityState mState;

		void setSolidMaterials();
		void setTransparentMaterials();

		void setTransparentMaterialsAlpha(double alpha);
	};

}

#endif