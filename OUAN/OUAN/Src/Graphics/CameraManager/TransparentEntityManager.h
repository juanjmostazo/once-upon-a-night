#ifndef TransparentEntityManagerH_H
#define TransparentEntityManagerH_H
#include "../../OUAN.h"
namespace OUAN
{
	class TransparentEntityManager
	{
	public:
		TransparentEntityManager();
		~TransparentEntityManager();

		void init();

		void clear();

		void add(Ogre::Entity * pEntity);
		void remove(std::string name);

		bool hasTransparentEntity(std::string name);
		void makeSolidEntitesNotIncluded(std::vector<Ogre::Entity*> & collisionEntities);

		void update(double elapsedTime);

	protected:
		std::map<std::string,TransparentEntity> mTransparentEntities;
		typedef std::map<std::string,TransparentEntity>::iterator TTransparentEntities;

		bool loadConfig();

		double mMinAlphaBlending;
		double mAlphaBlendingTime;
	};

}

#endif