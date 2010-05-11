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
		std::vector<Ogre::MaterialPtr> mSolidMaterial;
		std::vector<Ogre::MaterialPtr> mTransparentMaterial;

		double mMinAlphaBlending;
		double mAlphaBlendingTime;
		double mCurrentElapsedTime;

		bool mMakingTransparent;
		bool mMakingSolid;

		bool mIsSolid;


		void setSolidMaterials();
		void setTransparentMaterials();

		void setTransparentMaterialsAlpha(double alpha);
	};

}

#endif