#ifndef UTILSH_H
#define UTILSH_H

namespace Ogre
{
	class Entity;
	class Node;
	class Vector3;
	class Quaternion;
}

namespace OUAN
{
	class RenderSubsystem;
	typedef boost::shared_ptr<RenderSubsystem> RenderSubsystemPtr;

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

		//--------------------------------
		// LUA Exports

		void scriptLog (const std::string& logMsg);

		class LUATimer
		{
		private:
			double mSeconds;
		public:
			LUATimer();
			void reset();
			void addTime(double secs);
			double getTime();
		};

		//--------------------------------
		int parseInt(std::string& strValue);

		Ogre::Vector3 getNodeWorldPosition(Ogre::Entity* entity, Ogre::Node* node);
		Ogre::Quaternion getNodeWorldOrientation(Ogre::Entity* entity, Ogre::Node* node);
		std::string toString(double doubleValue);
		std::string toString(float floatValue);
		std::string toString(long longValue);
		std::string toString(int intValue);
		std::string toString(char charValue);
		std::string toString(bool boolValue);

		const std::string replaceAll(const std::string& source, const std::string& replaceWhat, 
			const std::string& replaceWithWhat);


		struct TTexturedRectangleDesc
		{
			double leftCorner, rightCorner, topCorner, bottomCorner;
			Ogre::RenderQueueGroupID renderQueue;
			Ogre::AxisAlignedBox axisAlignedBox;

			std::string materialName;
			std::string materialGroup;
			std::string textureName;
			std::string sceneNodeName;

			bool alphaRejection;
			unsigned char alphaRejectionValue;
			Ogre::CompareFunction alphaRejectionFunction;
			bool depthWrite;
			bool alphaToCoverage;

			bool textureAnimation;
			int texAnimNumFrames;
			double texAnimDuration;
			

			TTexturedRectangleDesc()
				:alphaRejection(false)
				,depthWrite(false)
			{

			}
		};

		void createTexturedRectangle (const TTexturedRectangleDesc& description, Ogre::Rectangle2D*& rectangle,
			RenderSubsystemPtr renderSS);
		void destroyTexturedRectangle (Ogre::Rectangle2D*&, const std::string& materialName, RenderSubsystemPtr renderSs);

		Ogre::UTFString convertToUTF(const Ogre::String& str);
	}

}
#endif