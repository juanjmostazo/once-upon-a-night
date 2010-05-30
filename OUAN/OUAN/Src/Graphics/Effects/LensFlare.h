 /* ------------------------------------------------------------------------- */
 // File       : LensFlare.h
 // Project    : Long Forgotten Earth
 // Author     : David de Lorenzo
 /* ------------------------------------------------------------------------- */
 #ifndef _LENSFLARE_H_
 #define _LENSFLARE_H_

#define VOIDOBJECT 0

#include <Ogre.h>
 
 /* ------------------------------------------------------------------------- */
 /// A lens Flare effect.
 /**
 This class will create a lensflare effect, between The light position and the 
 camera position.
 Some functions will allow to change the lensflare color effect, in case of coloured 
 light, for instance.
 */
 /* ------------------------------------------------------------------------- */

namespace OUAN
{
	 class LensFlare
	 {
	 public:
		 LensFlare(Ogre::Camera* camera, Ogre::SceneManager* sceneMgr,Ogre::SceneNode* node);
 		virtual ~LensFlare();
 		void    createLensFlare();
 		void    update();
 		void    setVisible(bool visible);
		void    setLightPosition(Ogre::Vector3 pos);
		void    setHaloColour(Ogre::ColourValue color);
 		void    setBurstColour(Ogre::ColourValue color);

		void changeCamera(Ogre::Camera* cam);
	 
	 protected:
 		Ogre::SceneManager* mSceneMgr;
 		Ogre::Camera*       mCamera;
 		Ogre::ColourValue   mColour;
 		Ogre::SceneNode*    mNode;
		Ogre::BillboardSet* mHaloSet;
   		Ogre::BillboardSet* mBurstSet;
 		Ogre::Vector3       mLightPosition;
 		bool          mHidden;
	 };
}
 #endif