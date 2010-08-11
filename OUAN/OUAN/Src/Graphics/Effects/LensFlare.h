 /* ------------------------------------------------------------------------- */
 // File       : LensFlare.h
 // Project    : Long Forgotten Earth
 // Author     : David de Lorenzo
 /* ------------------------------------------------------------------------- */
 #ifndef _LENSFLARE_H_
 #define _LENSFLARE_H_

#define VOIDOBJECT 0
 
 /* ------------------------------------------------------------------------- */
 /// A lens Flare effect.
 /**
 This class will create a lensflare effect, between The light position and the 
 camera position.
 Some functions will allow to change the lensflare color effect, in case of coloured 
 light, for instance.
 */
 /* ------------------------------------------------------------------------- */

#include "../Line3D/Line3D.h"

namespace OUAN
{
	 class LensFlare
	 {
	 public:
		 LensFlare(Ogre::SceneManager* sceneMgr,Ogre::SceneNode* node,double LF_scale);
 		virtual ~LensFlare();
 		void    createLensFlare(double LF_scale);
 		void    update();
 		void    setVisible(bool visible);
		void    setHaloColour(Ogre::ColourValue color);
 		void    setBurstColour(Ogre::ColourValue color);
	    
	 protected:
 		Ogre::SceneManager* mSceneMgr;
 		Ogre::Camera*       mCamera;
 		Ogre::ColourValue   mColour;
 		Ogre::SceneNode*    mNode;
		Ogre::BillboardSet* mHaloSet;
   		Ogre::BillboardSet* mBurstSet;
 		bool                mHidden;

		Line3D * mDebugLine;
		Ogre::SceneNode* mDebugLineNode;

		void updateDebugLines();
	 };
}
 #endif