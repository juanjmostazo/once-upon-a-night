#ifndef RenderComponentPlaneH_H
#define RenderComponentPlaneH_H

#include "RenderComponent.h"

namespace OUAN
{
	class RenderComponentPlane: public RenderComponent
	{
	private:
		Ogre::Entity* mPlane;
	public:

		RenderComponentPlane(const std::string& type="");
		~RenderComponentPlane();

		Ogre::Entity * getPlane() const;
		void setPlane(Ogre::Entity *);

	};

	class TRenderComponentPlaneParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentPlaneParameters();
		~TRenderComponentPlaneParameters();

		String material;
		bool hasNormals;
		Real distance;
		Real height;
		Real width;
		Vector3 normal;
		int numCoordSets;
		int Utile;
		int Vtile;
		int Xsegments;
		int Ysegments;

		QueryFlags cameraCollisionType;

		Ogre::uint8 queueID;
	};


}

#endif