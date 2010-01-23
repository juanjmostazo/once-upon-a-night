//Lighting effects test

//The code to render the flashlight halo has been taken from the 'light shafts with shadows and noise
//support' demo by Xavier Verguín González, inspired in return on the ATI paper
//http://ati.amd.com/developer/gdc/mitchell_lightshafts.pdf
//The lens flare effect adapted from the snippet on http://www.ogre3d.org/wiki/index.php/Displaying_LensFlare
//and Alan Gordie's article on http://www.gamedev.net/reference/articles/article813.asp
//Basic Ogre light examples are adapted from the tutorial on http://www.ogre3d.org/wiki/index.php/Basic_Tutorial_2

// ----------------------------------------------------------------------------
// Include the main OGRE header files
// Ogre.h just expands to including lots of individual OGRE header files
// ----------------------------------------------------------------------------
#include <Ogre.h>
#include <map>

// --------------------------------
//  Our own application framework
// ---------------------------------
#include "Application.h"

//  --------------------------------
//  Lens flare effect implementation
#include "LensFlare.h"


// ----------------------------------------------------------------------------
// Light shafts demo variables
// ----------------------------------------------------------------------------

/// Main light billboard set
Ogre::BillboardSet *gBillboardSet = 0;
/// Camera used for rendering the shadow map and as light frustum
Ogre::Camera       *gLightCamera = 0;
/// Light camera scene node
Ogre::SceneNode    *gLightCameraSN = 0;

// Scene nodes for the entities used in the demo
Ogre::SceneNode		*gKnotSN = 0;
Ogre::SceneNode		*gFlashlightSN = 0;

//Cookie - Flashlight colour map
typedef std::map<int,Ogre::ColourValue> TFlashlightColourMap;
TFlashlightColourMap gFlashlightColours;
void initFlashlightColourMap()
{
	gFlashlightColours.clear();
	gFlashlightColours[0]=Ogre::ColourValue::White;
	gFlashlightColours[1]=Ogre::ColourValue::White;
	gFlashlightColours[2]=Ogre::ColourValue::Red;
	gFlashlightColours[3]=Ogre::ColourValue::Green;
	gFlashlightColours[4]=Ogre::ColourValue::Blue;
}

// ----------------------
// Lens flare effect
// ----------------------
LensFlare* gLensFlare;

// Current cookie selected
int mCurrentCookie = 2;

class LightingDemoApp: public Application
{
public:
	long mKeyBuffer;
	bool mRotateEnable;
	bool mRotateKnot;
	
	
	LightingDemoApp()
		:Application("Lighting demo")
		,mKeyBuffer(-1)
		,mRotateEnable(false)
		,mRotateKnot(false)
	{}
	
	void updateLogic(long elapsedTime)
	{
		Application::updateLogic(elapsedTime);
		// Update light position
		updatePosition(elapsedTime);
		gLensFlare->update();
		mKeyBuffer -= elapsedTime;
	}
	bool keyPressed(const OIS::KeyEvent& evt)
	{
		Application::keyPressed(evt);
		if (evt.key==OIS::KC_B && mKeyBuffer < 0)
		{
			mRotateKnot = !mRotateKnot;
			mKeyBuffer = 500;
		}

		// Change light cookie
		if (evt.key==OIS::KC_N && mKeyBuffer < 0)
		{
			mCurrentCookie++;

			if (mCurrentCookie > 4)
			{
				mCurrentCookie = 0;
			}

			Ogre::Light *mLight1 = m_sceneManager->getLight("Flashlight");
			if(mLight1)
			{
				mLight1->setDiffuseColour(gFlashlightColours[mCurrentCookie]);
				mLight1->setSpecularColour(gFlashlightColours[mCurrentCookie]);
			}


			static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("LightShafts"))->
				getTechnique(0)->getPass(0)->getTextureUnitState(1)->
				setTextureName("Cookie" + Ogre::StringConverter::toString(mCurrentCookie) + ".png");

			mKeyBuffer = 500;
		}
		return true;
	}
	void updatePosition(unsigned long elapsedTime)
	{
		// Just a simple circular trajectory
		const Ogre::Real& SimulationTime = Ogre::Root::getSingleton().getTimer()->getMilliseconds();
		Ogre::Real Radius = 3;

		gLightCameraSN->setPosition(gLightCameraSN->getPosition().x,
			                        gLightCameraSN->getPosition().y,
									gLightCameraSN->getPosition().z);
		//gLightCameraSN->setPosition(Ogre::Math::Sin(SimulationTime/1000)*Radius,
		//	gLightCameraSN->getPosition().y,
		//	Ogre::Math::Cos(SimulationTime/1000)*Radius);

		// Set the the scene node direction to 0,KnotHeight,0 point
		/*Ogre::Vector3 NormalisedDirection = (Ogre::Vector3(gKnotSN->getPosition().x,0,0)-gLightCameraSN->getPosition()).normalisedCopy();
		gLightCameraSN->setDirection(NormalisedDirection, Ogre::Node::TS_WORLD);*/

		// Upload current position to light shafts materials
		static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("LightShafts"))->
			getTechnique(0)->getPass(0)->getFragmentProgramParameters()->
			setNamedConstant( "uLightPosition", gLightCameraSN->getPosition());
		static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("LightShaftsDepth"))->
			getTechnique(0)->getPass(0)->getFragmentProgramParameters()->
			setNamedConstant( "uLightPosition", gLightCameraSN->getPosition());

		// We've to update the texture projection matrix
        updateTextureProjectionMatrix();

		if (mRotateKnot)
		{
			gKnotSN->setOrientation(
				Ogre::Quaternion(
				      Ogre::Degree(Ogre::Root::getSingleton().getTimer()->getMilliseconds()/50),
				      Ogre::Vector3(0,1,0)));
		}
	}
	//No need to touch this ;)
	void updateTextureProjectionMatrix()
	{
		const Ogre::Matrix4 PROJECTIONCLIPSPACE2DTOIMAGESPACE_PERSPECTIVE(
			0.5,    0,    0,  0.5,
			0,   -0.5,    0,  0.5,
			0,      0,    1,    0,
			0,      0,    0,    1);

		Ogre::Matrix4 TexViewProj = 
			PROJECTIONCLIPSPACE2DTOIMAGESPACE_PERSPECTIVE * 
			gLightCamera->getProjectionMatrixWithRSDepth() * 
			gLightCamera->getViewMatrix(); 

		static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("LightShafts"))->
			getTechnique(0)->getPass(0)->getVertexProgramParameters()->
			setNamedConstant( "uTexViewProj", TexViewProj );
	}
	void createScene()
	{
		// Set some camera params
		m_camera->setFarClipDistance(3000);
		m_camera->setNearClipDistance(0.25f);		
		m_camera->setPosition(25,50,0);
		m_camera->lookAt(0,17.5f,0);

		m_sceneManager->setAmbientLight(ColourValue(0.2,0.2,0.2));
		m_sceneManager->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

		// Set up light 0
		initLightSphere();
		initFlashlight();
		initFloor();

		// Set a knot
		Ogre::Entity *mKnot = m_sceneManager->createEntity("Knot", "knot.mesh");
		mKnot->setMaterialName("Knot");
		mKnot->setCastShadows(true);
		gKnotSN = m_sceneManager->getRootSceneNode()->createChildSceneNode();
		gKnotSN->attachObject(mKnot);
		gKnotSN->setPosition(0, 17.5f, 0);
		gKnotSN->setScale(0.0225, 0.0225, 0.0225);
	}

	void initFloor() 
	{
		// Set a floor plane
		Ogre::MovablePlane *mPlane = new MovablePlane("FloorPlane");
		mPlane->normal = Vector3::UNIT_Y;
		mPlane->d = 0;
		MeshManager::getSingleton().createPlane("FloorPlaneMesh",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, *mPlane,
			1500,1500,50,50,true,1,5,5,Vector3::UNIT_Z);

		Ogre::Entity *pPlaneEnt = m_sceneManager->createEntity("Plane", "FloorPlaneMesh");
		pPlaneEnt->setMaterialName("rockwall");
		pPlaneEnt->setCastShadows(false);
		SceneNode* pPlaneNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
		pPlaneNode->attachObject(pPlaneEnt);
		pPlaneNode->setPosition(0,0,0);
	}
	void initFlashlight() 
	{
		// Set up our light camera
		gLightCamera = m_sceneManager->createCamera("LightCamera");
		gLightCamera->setProjectionType(Ogre::PT_PERSPECTIVE);
		// Not forget to set near+far distance in materials
		gLightCamera->setNearClipDistance(8);
		gLightCamera->setFarClipDistance(40);
		gLightCamera->setAspectRatio(1);
		gLightCamera->setFOVy(Ogre::Degree(17.5f));
		gLightCamera->setDebugDisplayEnabled(true);
		gLightCamera->setVisible(false);//Hides frustrum
		gLightCameraSN = m_sceneManager->getRootSceneNode()->createChildSceneNode();
		gLightCameraSN->setPosition(22,17.5f,0);
		gLightCameraSN->attachObject(gLightCamera);

		gLightCameraSN->setDirection(-1,0 , 0);

		Ogre::Entity *mFlashlight = m_sceneManager->createEntity("Flashlight","flashlight.mesh");
		mFlashlight->setMaterialName("Flashlight");
		gFlashlightSN = m_sceneManager->getRootSceneNode()->createChildSceneNode();
		gFlashlightSN->attachObject(mFlashlight);
		gFlashlightSN->setPosition(20,17.5f,0);
		gFlashlightSN->yaw(Degree(-90.0));		

		Ogre::Light *mLight1 = m_sceneManager->createLight("Flashlight");
		mLight1->setType(Light::LT_SPOTLIGHT);
		mLight1->setDiffuseColour(Ogre::ColourValue::White);
		mLight1->setSpecularColour(Ogre::ColourValue::White);
		mLight1->setPosition(Vector3::ZERO);
		mLight1->setDirection(Vector3::NEGATIVE_UNIT_Z);
		mLight1->setSpotlightRange(Degree(5), Degree(15));
		//mLight1->setAttenuation(40,1,0,0);
		gLightCameraSN->attachObject(mLight1);


		// Create our billboardset for volumetric rendering
		gBillboardSet = m_sceneManager->createBillboardSet("LightBillboardSet", 1);
		gBillboardSet->setMaterialName("LightShafts");
		gBillboardSet->setBillboardRotationType(Ogre::BBR_VERTEX);
		gBillboardSet->setCastShadows(false);
		gLightCameraSN->attachObject(gBillboardSet);

		// Create a rush of billboards according to the frustum of the camera(gLightCamera)
		// After it, we can use the lightcamera/billboards scenenode like a light projector
		createLightShafts(gBillboardSet, gLightCamera, 100);

		// Creating a RRT for depth/shadow map
		createLightCameraRTT();
	}
	void initLightSphere() 
	{
		Ogre::Light *mLight0 = m_sceneManager->createLight("Light0");
		mLight0->setType(Light::LT_POINT);
		mLight0->setPosition(50,1500,0);
		mLight0->setDiffuseColour(1,1,0);
		mLight0->setSpecularColour(1, 1, 1);
		Entity* lightSphere = m_sceneManager->createEntity("LightSphere","sphere.mesh");
		//lightSphere->setMaterialName("Examples/Hilite/Yellow");
		SceneNode* lightSphereNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
		lightSphereNode->attachObject(lightSphere);
		lightSphereNode->setPosition(50,2000,0);
		lightSphereNode->scale(0.25,0.25,0.25);
		gLensFlare = new LensFlare(mLight0->getPosition()-m_camera->getPosition(),m_camera, m_sceneManager);
	}
	bool createLightShafts(Ogre::BillboardSet* Billboard, Ogre::Camera *LightCamera, const int &NumberOfPlanes)
	{
		// Calculate the distance between planes
		float DistanceBetweenPlanes = (LightCamera->getFarClipDistance() - LightCamera->getNearClipDistance())/NumberOfPlanes;

		// Get frustum corners to calculate near/far planes dimensions
		const Ogre::Vector3 *FrustumCorners = LightCamera->getWorldSpaceCorners();

		// Calcule near and far planes dimensions
		float NearWidth  = (FrustumCorners[0] - FrustumCorners[1]).length(),
			NearHeigth = (FrustumCorners[1] - FrustumCorners[2]).length(),
			FarWidth   = (FrustumCorners[4] - FrustumCorners[5]).length(),
			FarHeigth  = (FrustumCorners[5] - FrustumCorners[6]).length();

		// Now width/height step
		float WidthStep  = (FarWidth-NearWidth)/NumberOfPlanes,
			HeigthStep = (FarHeigth-NearHeigth)/NumberOfPlanes;

		// Add billboards
		Ogre::Billboard *CurrentBB = 0;
		for(int k = 0; k < NumberOfPlanes; k++)
		{
			CurrentBB = Billboard->createBillboard(Ogre::Vector3(0, 0,-LightCamera->getNearClipDistance() -k*DistanceBetweenPlanes), ColourValue::White);
			CurrentBB->setDimensions(NearWidth + k*WidthStep, NearHeigth + k*HeigthStep);
		}

		return true;
	}

	void createLightCameraRTT()
	{
		// Creat a texture for use as rtt
		Ogre::TexturePtr LightCameraRTT = Ogre::TextureManager::getSingleton()
			.createManual("LightDepthMap",
			"General",
			Ogre::TEX_TYPE_2D,
			// 256*256 must be sufficient
			256, 
			256, 
			0,
			Ogre::PF_R8G8B8,
			Ogre::TU_RENDERTARGET);

		Ogre::RenderTarget* RT_Texture = LightCameraRTT->getBuffer()->getRenderTarget();

		Ogre::Viewport *RT_Texture_Viewport = RT_Texture->addViewport(gLightCamera);
		RT_Texture_Viewport->setClearEveryFrame(true);
		RT_Texture_Viewport->setBackgroundColour(Ogre::ColourValue::White);
		RT_Texture_Viewport->setOverlaysEnabled(false);
		RT_Texture_Viewport->setSkiesEnabled(false);

		// Add our depth listener
		RT_Texture->addListener(new LightDepthMapRttListener(m_sceneManager));

		// Fill the texture in our material
		static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("LightShafts"))->
			getTechnique(0)->getPass(0)->getTextureUnitState(0)->
			setTextureName("LightDepthMap");
	}

	// Just for change all entities materials in depth rtt
	class LightDepthMapRttListener : public Ogre::RenderTargetListener
	{
	public:
		LightDepthMapRttListener(Ogre::SceneManager *sm)
			: mSceneMgr(sm)
		{
		}

		void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
		{
			Ogre::SceneManager::MovableObjectIterator EntityIterator = mSceneMgr->getMovableObjectIterator("Entity");
			Ogre::Entity * CurrentEntity = NULL;
			unsigned int k = 0;

			mMaterials.empty();

			gBillboardSet->setVisible(false);

			while( EntityIterator.hasMoreElements() )
			{
				CurrentEntity = static_cast<Ogre::Entity *>(EntityIterator.peekNextValue());
				for( k = 0; k < CurrentEntity->getNumSubEntities(); k++ )
				{
					mMaterials.push(CurrentEntity->getSubEntity(k)->getMaterialName());
					CurrentEntity->getSubEntity(k)->setMaterialName("LightShaftsDepth");
				}

				EntityIterator.moveNext();
			}
		}

		void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
		{
			Ogre::SceneManager::MovableObjectIterator EntityIterator = mSceneMgr->getMovableObjectIterator("Entity");
			Ogre::Entity * CurrentEntity = NULL;
			unsigned int k = 0;

			gBillboardSet->setVisible(true);

			while( EntityIterator.hasMoreElements() )
			{
				CurrentEntity = static_cast<Ogre::Entity *>(EntityIterator.peekNextValue());
				for( k = 0; k < CurrentEntity->getNumSubEntities(); k++ )
				{
					CurrentEntity->getSubEntity(k)->setMaterialName(mMaterials.front());
					mMaterials.pop();
				}

				EntityIterator.moveNext();
			}
		}

		std::queue<std::string> mMaterials;	
		Ogre::SceneManager *mSceneMgr;
	};
};
	
// ----------------------------------------------------------------------------
// Main function, just boots the application object
// ----------------------------------------------------------------------------
#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{
	try
	{
		initFlashlightColourMap();
		LightingDemoApp* app=new LightingDemoApp();
		app->initialise();
		app->go();
		app->cleanUp();
		delete app;
	}
	catch(Exception& e)
	{
#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		fprintf(stderr, "An exception has occurred: %s\n",
			e.getFullDescription().c_str());
#endif
	}

	return 0;
}