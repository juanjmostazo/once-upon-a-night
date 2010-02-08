//Lighting effects test

//The code to render the flashlight halo has been taken from the 'light shafts with shadows and noise
//support' demo by Xavier Verguín González, inspired in return on the ATI paper
//http://ati.amd.com/developer/gdc/mitchell_lightshafts.pdf
//The lens flare effect adapted from the snippet on http://www.ogre3d.org/wiki/index.php/Displaying_LensFlare
//and Alan Gordie's article on http://www.gamedev.net/reference/articles/article813.asp
//Basic Ogre light examples are adapted from the tutorial on http://www.ogre3d.org/wiki/index.php/Basic_Tutorial_2

// -----------------------------just-----------------------------------------------
// Include the main OGRE header files
// Ogre.h  expands to including lots of individual OGRE header files
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

//-----------------------------------
//Light shafts effect
#include "LightShafts.h"

//Assign a flashlight colour from a light shafts' 'cookie' value.
typedef std::map<int,Ogre::ColourValue> TFlashlightColourMap;
TFlashlightColourMap gFlashlightColours;

//Initialize the map <cookie,colourvalue>
void initFlashlightColourMap()
{
	gFlashlightColours.clear();
	gFlashlightColours[0]=Ogre::ColourValue::White;
	gFlashlightColours[1]=Ogre::ColourValue::Red;
	gFlashlightColours[2]=Ogre::ColourValue::Green;
	gFlashlightColours[3]=Ogre::ColourValue::Blue;
}

TProjectorSettings gFlashlightSettings;
void initFlashlightSettings()
{
	gFlashlightSettings.cookieName="";//It'll be set in the initialization method

	gFlashlightSettings.nearClipDistance=8;
	gFlashlightSettings.farClipDistance=60;
	gFlashlightSettings.fovy=Ogre::Degree(17.5);
	gFlashlightSettings.aspectRatio=1.0f;	
	gFlashlightSettings.numberOfPlanes=100;
	gFlashlightSettings.position=Ogre::Vector3(20,17.5f,0);
	gFlashlightSettings.direction=Ogre::Vector3::NEGATIVE_UNIT_X;
	gFlashlightSettings.showDebug=false;

	gFlashlightSettings.useSpotLight=true;
	gFlashlightSettings.spotlightSettings.diffuse=Ogre::ColourValue::Black; //To be set by the flashlight
	gFlashlightSettings.spotlightSettings.specular=Ogre::ColourValue::Black;
	gFlashlightSettings.spotlightSettings.falloff=1.0f;
	gFlashlightSettings.spotlightSettings.innerAngle=Ogre::Degree(5);
	gFlashlightSettings.spotlightSettings.outerAngle=Ogre::Degree(15);
	gFlashlightSettings.spotlightSettings.attenuate=true;
	gFlashlightSettings.spotlightSettings.attenuationRange=500;
	gFlashlightSettings.spotlightSettings.attenuationConstant=1.0;
	gFlashlightSettings.spotlightSettings.attenuationLinear=0.005;
	gFlashlightSettings.spotlightSettings.attenuationQuadratic=0.0002;

}

typedef std::map<Ogre::String,LightShaftsProjector*> TShafts;
const int MAX_SHAFTS=4;
const Ogre::String SHAFTS_NAME="shaft";
Ogre::Vector3 SHAFTS_POSITIONS[MAX_SHAFTS] =
{
	Ogre::Vector3(-300,100,-300),
	Ogre::Vector3(300,100,-300),
	Ogre::Vector3(-300,100,300),
	Ogre::Vector3(300,100,300),
};

TProjectorSettings gShaftSettings;
void initShaftSettings()
{
	gShaftSettings.cookieName="TestCookie.png";

	gShaftSettings.nearClipDistance=8;
	gShaftSettings.farClipDistance=90;
	gShaftSettings.fovy=Ogre::Degree(17.5);
	gShaftSettings.aspectRatio=1.0f;	
	gShaftSettings.numberOfPlanes=100;
	gShaftSettings.position=Ogre::Vector3::ZERO;
	gShaftSettings.direction=Ogre::Vector3::NEGATIVE_UNIT_Y;
	gShaftSettings.showDebug=false;

	gShaftSettings.useSpotLight=false;
	//gShaftSettings.spotlightSettings.diffuse=Ogre::ColourValue(0.7,0.6,1);
	//gShaftSettings.spotlightSettings.specular=Ogre::ColourValue(0.7,0.6,1);
	//gShaftSettings.spotlightSettings.falloff=0.2f;
	//gShaftSettings.spotlightSettings.innerAngle=Ogre::Degree(10);
	//gShaftSettings.spotlightSettings.outerAngle=Ogre::Degree(15);
	//gShaftSettings.spotlightSettings.attenuate=false;

}

class Flashlight: public LightShaftsProjector
{
private:
	TFlashlightColourMap mFlashlightColours;
	int mCurrentCookie;
	int mMaxCookies;
	void setFlashlightColours(const TFlashlightColourMap& flashlightColours)
	{
		mFlashlightColours=flashlightColours;
	}
public:
	Flashlight(Ogre::SceneManager* sceneManager,Ogre::String baseMaterialName)
	:LightShaftsProjector(sceneManager,baseMaterialName)
	,mCurrentCookie(-1)
	,mMaxCookies(-1)
	{
		mFlashlightColours.clear();
	}
	~Flashlight()
	{

	}
	void init(int initialCookie,int maxCookies, TProjectorSettings& settings,const TFlashlightColourMap& flashlightColours)
	{
		mCurrentCookie=initialCookie;
		mMaxCookies=maxCookies;
		setFlashlightColours(flashlightColours);
		setProjectorName("Flashlight");
		settings.cookieName=Ogre::String("Cookie"+Ogre::StringConverter::toString(initialCookie+1)+".png");
		settings.spotlightSettings.diffuse=Ogre::ColourValue(mFlashlightColours[initialCookie]);
		settings.spotlightSettings.specular=Ogre::ColourValue(mFlashlightColours[initialCookie]);
		initProjector(settings);
		createFlashlightEntity();
	}
	void changeNextColour()
	{
		mCurrentCookie=(mCurrentCookie+1)%mMaxCookies;
		if (mLight)
		{
			mLight->setDiffuseColour(mFlashlightColours[mCurrentCookie]);
			mLight->setSpecularColour(mFlashlightColours[mCurrentCookie]);
		}
		setCookie("Cookie"+Ogre::StringConverter::toString(mCurrentCookie+1)+".png");
	}
	void createFlashlightEntity()
	{		
		Ogre::Entity *flashlightEntity = mSceneManager->createEntity("Flashlight","flashlight.mesh");
		mProjectorSceneNode->createChildSceneNode()->attachObject(flashlightEntity);
		flashlightEntity ->setMaterialName("Examples/Hilite/Yellow");
		flashlightEntity ->setCastShadows(true);
		//flashlightEntity->getParentSceneNode()->setPosition(-1,0,0);
		flashlightEntity->getParentSceneNode()->translate(Ogre::Vector3(0,0,-1));
		flashlightEntity->getParentSceneNode()->yaw(Degree(180.0));
	}
};


class AdditionalEffectsLightingDemo: public Application
{
	public:	
		AdditionalEffectsLightingDemo()
			:Application("Additional Lighting Effects Demo")
			,mKeyBuffer(-1)
			,mRotateKnot(false)
			,mLensFlare(NULL)
			,mFlashlight(NULL)
		{}
		void updateLogic(float elapsedTime)
		{
			if(m_camera->getPosition().y<17.5)//TODO: Replace with rayscenequery
				m_camera->setPosition(m_camera->getPosition().x,m_camera->getPosition().y+17.5,m_camera->getPosition().z);
			Application::updateLogic(elapsedTime);
			
			mLensFlare->update();
			mFlashlight->update(elapsedTime);

			for (int i=0;i<MAX_SHAFTS;i++)
			{
				mShafts[SHAFTS_NAME+Ogre::StringConverter::toString(i+1)]->update(elapsedTime);
			}

			if (mRotateKnot)
			{
				mKnotSN->setOrientation(
					Ogre::Quaternion(
					Ogre::Degree(Ogre::Root::getSingleton().getTimer()->getMilliseconds()/50),
					Ogre::Vector3::UNIT_Y));
			}

			mKeyBuffer -= elapsedTime;
		}
		bool keyPressed(const OIS::KeyEvent& evt)
		{
			Application::keyPressed(evt);
			if(mLensFlare)
				mLensFlare->update();//update flare with the camera (TODO? replace if redundant)
			if (evt.key==OIS::KC_B && mKeyBuffer < 0)
			{
				mRotateKnot = !mRotateKnot;
				mKeyBuffer = 0.5;
			}
			//Turn on/off the flashlight
			if (evt.key==OIS::KC_O && mKeyBuffer<0)
			{
				mFlashlight->toggle();
				mKeyBuffer=0.5;
			}

			// Change flashlight cookie
			if (evt.key==OIS::KC_N && mKeyBuffer < 0)
			{
				mFlashlight->changeNextColour();
				mKeyBuffer = 0.5;
			}

			//Toggle shafts
			int shaftIndex=-1;
			if (evt.key>=OIS::KC_1 && evt.key<=OIS::KC_4 && mKeyBuffer<0)
			{
				shaftIndex=evt.key-1;	
				mKeyBuffer=0.5;
			}
			int shaftRotationIndex=-1;
			if (evt.key>=OIS::KC_5 && evt.key<=OIS::KC_8 && mKeyBuffer<0)
			{
				shaftRotationIndex=evt.key-5;	
				mKeyBuffer=0.5;
			}
			//
			if(shaftIndex>0)
			{
				Ogre::String name=SHAFTS_NAME+Ogre::StringConverter::toString(shaftIndex);
				mShafts[name]->toggle();
			}
			if (shaftRotationIndex>0)
			{
				Ogre::String name=SHAFTS_NAME+Ogre::StringConverter::toString(shaftRotationIndex);
				mShafts[name]->flipRotateEnabled();
			}

			return true;
		}

		void initCameraSettings()
		{
			m_camera->setFarClipDistance(3000);
			m_camera->setNearClipDistance(0.25f);		
			m_camera->setPosition(25,50,0);
			m_camera->lookAt(0,17.5f,0);
		}
		void initRoom()
		{
			// Set a floor plane
			Ogre::MovablePlane *mPlane = new MovablePlane("FloorPlane");
			mPlane->normal = Vector3::UNIT_Y;
			mPlane->d = 0;
			MeshManager::getSingleton().createPlane("FloorPlaneMesh",
				ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, *mPlane,
				1500,1500,50,50,true,1,5,5,Vector3::UNIT_Z);
			Ogre::Entity *pPlaneEnt = m_sceneManager->createEntity("Plane", "FloorPlaneMesh");
			pPlaneEnt->setMaterialName("Examples/Rockwall");
			pPlaneEnt->setCastShadows(false);
			SceneNode* pPlaneNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
			pPlaneNode->attachObject(pPlaneEnt);
			pPlaneNode->setPosition(0,0,0);

			Ogre::Entity *wall = m_sceneManager->createEntity("Wall","wall.mesh");
			wall->setMaterialName("MyWallMaterial");
			wall->setCastShadows(false);
			Ogre::SceneNode* wallSN = m_sceneManager->getRootSceneNode()->createChildSceneNode();
			wallSN->attachObject(wall);
			wallSN->setPosition(-200,40,0);
			wallSN->scale(8,10,20);
		}
		void initSun()
		{
			Ogre::Vector3 sunPosition(0,3250,0);
			Ogre::Light *mLight0 = m_sceneManager->createLight("SunLight");
			mLight0->setType(Light::LT_POINT);
			mLight0->setPosition(sunPosition);
			mLight0->setDiffuseColour(0.5,0.5,0);
			mLight0->setSpecularColour(0.5,0.5,0);
			mLight0->setAttenuation(4000,1.0,0.0012,0.000005);
			Entity* lightSphere = m_sceneManager->createEntity("LightSphere","sphere.mesh");
			lightSphere->setMaterialName("Examples/Hilite/Yellow");
			SceneNode* lightSphereNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
			lightSphereNode->attachObject(lightSphere);
			lightSphereNode->setPosition(sunPosition);
			lightSphereNode->scale(0.5,0.5,0.5);
			mLensFlare = new LensFlare(mLight0->getPosition()-m_camera->getPosition(),m_camera, m_sceneManager);
		}
		void initShafts()
		{
			for (int i=0;i<MAX_SHAFTS;i++)
			{
				Ogre::String name=SHAFTS_NAME+Ogre::StringConverter::toString(i+1); //names will range from 1..4
				LightShaftsProjector* shaft = new LightShaftsProjector(m_sceneManager,"LightShafts");
				shaft->setProjectorName(name);
				gShaftSettings.position=SHAFTS_POSITIONS[i];
				shaft->initProjector(gShaftSettings);
				mShafts[name]=shaft;

			}
		}
		void createScene()
		{

			initCameraSettings();
			m_sceneManager->setAmbientLight(Ogre::ColourValue(0.2,0.2,0.2));
			m_sceneManager->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
			m_sceneManager->setSkyBox(true,"Examples/StormySkyBox");				
			
			initFlashlightColourMap();
			initFlashlightSettings();
			initShaftSettings();
			
			mFlashlight=new Flashlight(m_sceneManager,"LightShafts");
			mFlashlight->init(0,4,gFlashlightSettings,gFlashlightColours);

			initShafts();
			initRoom();
			initSun();

			// Set a knot
			Ogre::Entity *entity = m_sceneManager->createEntity("Knot", "knot.mesh");
			entity->setMaterialName("Knot");
			entity->setCastShadows(true);
			entity->setVisible(true);
			mKnotSN = m_sceneManager->getRootSceneNode()->createChildSceneNode();
			mKnotSN->attachObject(entity);
			mKnotSN->setPosition(-30, 17.5f, 0);
			mKnotSN->setScale(0.05, 0.05, 0.05);

		}
	void cleanUp()
	{
		if(mFlashlight)
			delete mFlashlight;
		if(mLensFlare)
			delete mLensFlare;
		mShafts.clear();
	}
	void updateStats()
	{
		Application::updateStats();	

		Ogre::String message = "F1 - Toggle debug displays\n";
		message+="O - Toggle flashlight on/off\n";
		message+="B - Toggle rotate knot on/off\n";
		message+="N - Change flashlight colour\n";	
		message+="1,2,3,4 - Toggle light shafts[1..4]\n";
		message+="5,6,7,8 - Toggle light shafts[n-4] rotation\n";

		m_debugWindow->setText(message);
		m_debugWindow->setAlpha(0.5);
		m_debugWindow->setSize(CEGUI::UVector2(CEGUI::UDim(0.5, 0), CEGUI::UDim(0.2, 0)));	
	}
	private:
		bool mRotateKnot;
		float mKeyBuffer;
		LensFlare* mLensFlare;
		Flashlight* mFlashlight;
		TShafts mShafts;
		Ogre::SceneNode* mKnotSN;

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
		AdditionalEffectsLightingDemo* app=new AdditionalEffectsLightingDemo();
		app->initialise();
		app->go();
		app->cleanUp();
		delete app;
	}
	catch(Ogre::Exception& e)
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