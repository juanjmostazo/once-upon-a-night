#ifndef UTILSH_H
#define UTILSH_H

#include <string>
#include <boost/random.hpp>
#include <boost/nondet_random.hpp>

namespace Ogre
{
	class Entity;
	class Node;
	class Vector3;
	class Quaternion;
}

namespace OUAN
{
	namespace Utils
	{
		const double DOUBLE_COMPARISON_DELTA=0.000001;
		class Random
		{
		private:
			boost::mt19937 mRandEngine;
			static Random* mInstance;
			Random();
		public:
			~Random();
			static Random* getInstance();
			void init(unsigned int seed);
			int getRandomInteger(int low, int high);
			double getRandomDouble(double low=0.0, double high=1.0);
		};

		void scriptLog (const std::string& logMsg);
		int parseInt(std::string& strValue);

		Ogre::Vector3 getNodeWorldPosition(Ogre::Entity* entity, Ogre::Node* node);
		Ogre::Quaternion getNodeWorldOrientation(Ogre::Entity* entity, Ogre::Node* node);
		std::string toString(double doubleValue);
		std::string toString(float floatValue);
		std::string toString(long longValue);
		std::string toString(int intValue);
		std::string toString(char charValue);
		std::string toString(bool boolValue);
	}
}
#endif