#ifndef __LINE3D_H__
#define __LINE3D_H__

#include "../../OUAN.h"

using namespace Ogre;
using namespace std;
namespace OUAN
{
	#define POSITION_BINDING 0
	#define TEXCOORD_BINDING 1

	class Line3D:public SimpleRenderable
	{
	public:
	   Line3D(void);
	   ~Line3D(void);

	   void addPoint(const Ogre::Vector3 &p);
	   const Ogre::Vector3 &getPoint(unsigned short index) const;
	   unsigned short getNumPoints(void) const;
	   void updatePoint(unsigned short index, const Ogre::Vector3 &value);
	   void drawLine(Ogre::Vector3 &start, Ogre::Vector3 &end);
	   void drawLines(void);

	   Ogre::Real getSquaredViewDepth(const Camera *cam) const;
	   Ogre::Real getBoundingRadius(void) const;
	protected:
	   //void getWorldTransforms(Matrix4 *xform) const;
	   const Ogre::Quaternion &getWorldOrientation(void) const;
	   const Ogre::Vector3 &getWorldPosition(void) const;

	   vector<Ogre::Vector3> mPoints;
	   bool mDrawn;
	};
}

#endif /* __LINE3D_H__ */