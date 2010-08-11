#include "OUAN_Precompiled.h"

/* ------------------------------------------------------------------------- */
 // File       : LensFlare.cpp
 // Project    : Long Forgotten Earth
 // Author     : David de Lorenzo
 /* ------------------------------------------------------------------------- */
#include "LensFlare.h"
#include "../../Utils/Logger.h"
#include "../../Application.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObjectOny.h"
#include "../../Graphics/RenderSubSystem.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Graphics/CameraManager/CameraManager.h"

 using namespace OUAN;
 /* ------------------------------------------------------------------------- */
 /// Constructor
 /// @param LightPosition The 3D position of the Light, relative to the camera.
 /// @param camera        The camera on which the lensflare effect will appear.
 /// @param SceneMgr      Pointer on the SceneManager.
 /* ------------------------------------------------------------------------- */
LensFlare::LensFlare(Ogre::SceneManager* SceneMgr, Ogre::SceneNode* sceneNode,double LF_scale)
:mSceneMgr(SceneMgr)
,mHidden(true)
 {
 	mSceneMgr      = SceneMgr;
 	mHidden        = true;

	mNode = sceneNode->createChildSceneNode("mLensFlareNode");

	mNode->setScale(1/sceneNode->getScale());
	mNode->setVisible(true);

	mDebugLineNode = sceneNode->createChildSceneNode("mLensFlareDebugLineNode");
	mDebugLineNode->setPosition(-mNode->_getDerivedPosition());

 	createLensFlare(LF_scale);
 }
 
 /* ------------------------------------------------------------------------- */
 /// Destructor
 /* ------------------------------------------------------------------------- */
 LensFlare::~LensFlare()
 {
 	mNode->detachObject(mHaloSet);
 	mNode->detachObject(mBurstSet);
 	mSceneMgr->destroyBillboardSet(mHaloSet);
 	mSceneMgr->destroyBillboardSet(mBurstSet);
 } 

 /* ------------------------------------------------------------------------- */
 /// this function creates and shows all the LensFlare graphical elements.
 /* ------------------------------------------------------------------------- */
 void LensFlare::createLensFlare(double LF_scale)
 {
 	// -----------------------------------------------------
 	// We create 2 sets of billboards for the lensflare
 	// -----------------------------------------------------
 	mHaloSet = mSceneMgr->createBillboardSet("halo");
 	mHaloSet->setMaterialName("lensflare/halo");
 	mHaloSet->setCullIndividually(true);
 	mHaloSet->setQueryFlags(VOIDOBJECT);	// They should not be detected by rays.
 
 	mBurstSet= mSceneMgr->createBillboardSet("burst");
 	mBurstSet->setMaterialName("lensflare/burst");
 	mBurstSet->setCullIndividually(true);
 	mBurstSet->setQueryFlags(VOIDOBJECT);	
 
 	// The node is located at the light source.
 	//mNode  = mSceneMgr->getRootSceneNode()->createChildSceneNode();
 
 	mNode->attachObject(mBurstSet);
 	mNode->attachObject(mHaloSet);
 
 	// -------------------------------
 	// Creation of the Halo billboards
 	// -------------------------------
	mHaloSet->setRenderQueueGroup(Ogre::RENDER_QUEUE_SKIES_LATE);
	Ogre::Billboard* LF_Halo1 = mHaloSet->createBillboard(0,0,0);
 	LF_Halo1->setDimensions(LF_scale*0.5,LF_scale*0.5);
 	Ogre::Billboard* LF_Halo2 = mHaloSet->createBillboard(0,0,0);
 	LF_Halo2->setDimensions(LF_scale,LF_scale);
 	Ogre::Billboard* LF_Halo3 = mHaloSet->createBillboard(0,0,0);
 	LF_Halo3->setDimensions(LF_scale*0.25,LF_scale*0.25);
 
 	// -------------------------------
 	// Creation of the "Burst" billboards
 	// -------------------------------
	mBurstSet->setRenderQueueGroup(Ogre::RENDER_QUEUE_SKIES_LATE);
 	Ogre::Billboard* LF_Burst1 = mBurstSet->createBillboard(0,0,0);
 	LF_Burst1->setDimensions(LF_scale*0.25,LF_scale*0.25);
 	Ogre::Billboard* LF_Burst2 = mBurstSet->createBillboard(0,0,0);
 	LF_Burst2->setDimensions(LF_scale*0.5,LF_scale*0.5);
 	Ogre::Billboard* LF_Burst3 = mBurstSet->createBillboard(0,0,0);
 	LF_Burst3->setDimensions(LF_scale*0.25,LF_scale*0.25);
 } 

 /* -------------------------------------------------------------------------- */
 /// This function updates the lensflare effect. 
 /** This function should be called by your frameListener.
 */
 /* -------------------------------------------------------------------------- */
 void LensFlare::update()
{

	mCamera=Application::getInstance()->getCameraManager()->getCamera();
   // If the Light is out of the Camera field Of View, the lensflare is hidden.
   if (!mCamera->isVisible(mNode->_getDerivedPosition())) 
   {
      this->setVisible(false);  
   }
   else 
   {
	   // Distance between camera position and ligt
	   Ogre::Real LightDistance  = (mCamera->getPosition() - mNode->_getDerivedPosition()).length();

	   // normalized vector (length 1)
	   Ogre::Vector3 CameraVect  = mCamera->getDirection();
	   CameraVect.normalise();

	   // Apply transformations
	   CameraVect = mCamera->getPosition() + (LightDistance * CameraVect);

	   // The LensFlare effect takes place along this vector.
	   Ogre::Vector3 LFvect = (CameraVect - mNode->_getDerivedPosition());

	   // sprite dimension (to be adjusted, but not necessary)
	   LFvect += Ogre::Vector3(-64,-64,0);  

	   //Logger::getInstance()->log("#### LENSFLARE IS VISIBLE");
	   //Logger::getInstance()->log("## LIGHTPOSITION: " + Ogre::StringConverter::toString(mLightPosition));
	   //Logger::getInstance()->log("## CAMERAPOS: " + Ogre::StringConverter::toString(mCamera->getPosition()));
	   //Logger::getInstance()->log("## CAMERAVECT: " + Ogre::StringConverter::toString(CameraVect));
	   //Logger::getInstance()->log("## LIGHTDISTANCE: " + Ogre::StringConverter::toString(LightDistance));
	   //Logger::getInstance()->log("## LFVect: " + Ogre::StringConverter::toString(LFvect));

	   // The different sprites are placed along this line.
	   mHaloSet->getBillboard(0)->setPosition( LFvect*0.500);
	   mHaloSet->getBillboard(1)->setPosition( LFvect*0.125);
	   mHaloSet->getBillboard(2)->setPosition(-LFvect*0.250);

	   mBurstSet->getBillboard(0)->setPosition( LFvect*0.333);
	   mBurstSet->getBillboard(1)->setPosition(-LFvect*0.500);
	   mBurstSet->getBillboard(2)->setPosition(-LFvect*0.180);

	   // We redraw the lensflare (in case it was previouly out of the camera field, and hidden)
	   this->setVisible(true);  
   }
	  
    //TODO enable this when required
	//updateDebugLines();
}

 /* ------------------------------------------------------------------------- */
 /// This function shows (or hide) the lensflare effect.
 /* ------------------------------------------------------------------------- */
 void LensFlare::setVisible(bool visible)
 {	
 	mHaloSet->setVisible(visible);
 	mBurstSet->setVisible(visible);

 	mHidden = !visible;
 }

 /* ------------------------------------------------------------------------- */
 /// This function changes the colour of the burst. 
 /* ------------------------------------------------------------------------- */
 void LensFlare::setBurstColour(Ogre::ColourValue color)
 {
 	mBurstSet->getBillboard(0)->setColour(color);
 	mBurstSet->getBillboard(1)->setColour(color*0.8);
 	mBurstSet->getBillboard(2)->setColour(color*0.6);
 } 

 /* ------------------------------------------------------------------------- */
 /// This function changes the colour of the halos. 
 /* ------------------------------------------------------------------------- */
 void LensFlare::setHaloColour(Ogre::ColourValue color)
 { 
 	mHaloSet->getBillboard(0)->setColour(color*0.8);
 	mHaloSet->getBillboard(1)->setColour(color*0.6);
 	mHaloSet->getBillboard(2)->setColour(color);
 }

void LensFlare::updateDebugLines()
{
	mCamera=Application::getInstance()->getCameraManager()->getCamera();

	mDebugLineNode->detachAllObjects();
	mDebugLineNode->setVisible(!mHidden);

	if (!mHidden)
	{
		mDebugLine = new Line3D();

		mDebugLine->addPoint(mCamera->getPosition());
		mDebugLine->addPoint(mNode->_getDerivedPosition());

		mDebugLine->setMaterial("red");
		mDebugLineNode->attachObject(mDebugLine);

		mDebugLine->drawLines();

		Logger::getInstance()->log("## DEBUGLINES");
		Logger::getInstance()->log("## POINTA: " + Ogre::StringConverter::toString(mDebugLine->getPoint(0)));
		Logger::getInstance()->log("## POINTB: " + Ogre::StringConverter::toString(mDebugLine->getPoint(1)));
		Logger::getInstance()->log("## Visible: " + Ogre::StringConverter::toString(!mHidden));
		Logger::getInstance()->log("## NodePosition: " + Ogre::StringConverter::toString(mDebugLineNode->_getDerivedPosition()));
		Logger::getInstance()->log("## ParentNodePosition: " + Ogre::StringConverter::toString(mDebugLineNode->getParentSceneNode()->getPosition()));
	}
}