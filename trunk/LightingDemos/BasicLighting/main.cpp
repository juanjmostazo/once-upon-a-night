//Basic Lighting demo

// ----------------------------------------------------------------------------
// Include the main OGRE header files
// Ogre.h just expands to including lots of individual OGRE header files
// ----------------------------------------------------------------------------
#include <Ogre.h>
#include <vector>
#include <map>

// --------------------------------
//  Our own application framework
// ---------------------------------
#include "Application.h"

const Ogre::ColourValue DEFAULT_AMBIENT_LIGHT = Ogre::ColourValue(0.1,0.1,0.1);

const Ogre::String ENTITY_NINJA = "Ninja";
const Ogre::String ENTITY_GROUND = "Ground";
const Ogre::String MESH_GROUND	= "Ground";
const Ogre::String ENTITY_SPHERE = "Sphere";

//Sets of test attenuation values
const int ATTENUATION_SETS_SIZE=4;
Ogre::Real ATTENUATION_SETS[ATTENUATION_SETS_SIZE][4]={
	//1st component: Range, 2nd: Constant, 3rd: Linear, 4th: 
	{600,1.0,0.007,0.0002},//default values
	{20,1.0,0.22,0.20},
	{325,1.0,0.014,0.0007},
	{3250,1.0,0.0014,0.000007}
};

//Sets of positions for the point light
const int POSITION_SET_SIZE=3;
Ogre::Vector3 POSITION_SETS[POSITION_SET_SIZE]={
	Ogre::Vector3(0, 150, 250),
	Ogre::Vector3(100,50,-100),
	Ogre::Vector3(0,300,0)
};

//Struct to hold all the information needed to setup a spotlight
//save for the halo, which'll be shown in the other demo
typedef struct{
	Ogre::Vector3 position;
	Ogre::Vector3 direction;
	Ogre::ColourValue diffuse;
	Ogre::ColourValue specular;
	Ogre::Radian	innerAngle;
	Ogre::Radian	outerAngle;
	Ogre::Real		falloff;
}TSpotlightData;

typedef std::map<Ogre::String,bool> TEnabledSpotlights;

//Spotlights info
const int SPOTLIGHT_NUM=4;
TSpotlightData gSpotlights[SPOTLIGHT_NUM]=
{
	{
		Ogre::Vector3(300,300,0),Ogre::Vector3(-1,-1,0),
		Ogre::ColourValue(0.0,0.0,1.0),Ogre::ColourValue(0.0,0.0,1.0),
		Ogre::Degree(15),Ogre::Degree(30),1.0
	},

	{
		Ogre::Vector3(500,100,500),Ogre::Vector3(-1,-1,-1),
		Ogre::ColourValue(0.0,1.0,1.0),Ogre::ColourValue(0.0,1.0,1.0),
		Ogre::Degree(35),Ogre::Degree(50),0.5
	},

	{
		Ogre::Vector3(-500,100,500),Ogre::Vector3(1,-1,-1),
		Ogre::ColourValue(1.0,0.0,0.0),Ogre::ColourValue(1.0,0.0,0.0),
		Ogre::Degree(20),Ogre::Degree(70),0.25
	},

	{
		Ogre::Vector3(400,100,-400),Ogre::Vector3(0,-1,0),
		Ogre::ColourValue(0.8,0.8,0.0),Ogre::ColourValue(0.8,0.8,0.0),
		Ogre::Degree(20),Ogre::Degree(60),4
	},

};



class BasicLightingDemoApp: public Application
{
private:
	bool mIsAmbientEnabled;
	float mKeyBuffer;
	Ogre::ShadowTechnique mCurrentShadowTechnique;
	Ogre::Light* mPointLight;
	Ogre::Light* mDirectionalLight;	
	int mCurrentAttenuationSet;
	int mCurrentPositionSet;
	TEnabledSpotlights mSpotlights;

public:
	BasicLightingDemoApp()
		:Application("Basic Lighting Demo")
		,mKeyBuffer(-1)
		,mIsAmbientEnabled(true)
		,mPointLight(NULL)
		,mDirectionalLight(NULL)
		//By default we'll use additive stencil shadows
		,mCurrentShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE)
		,mCurrentAttenuationSet(0)
		,mCurrentPositionSet(0)
	{
		mSpotlights.clear();
	}
	~BasicLightingDemoApp()
	{}
	void updateLogic(float elapsedTime)
	{
		Application::updateLogic(elapsedTime);
		mKeyBuffer -= elapsedTime;
	}
	bool keyPressed(const OIS::KeyEvent& evt)
	{
		Application::keyPressed(evt);
		if (evt.key==OIS::KC_F2 && mKeyBuffer<0)
		{
			if(mDirectionalLight)
			{
				mDirectionalLight->getParentSceneNode()->rotate(Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_Y));
			}
			mKeyBuffer=0.5;
		}
		if (evt.key==OIS::KC_F3 && mKeyBuffer<0)
		{
			if(mDirectionalLight)
			{
				mDirectionalLight->getParentSceneNode()->rotate(Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3::UNIT_X));
			}
			mKeyBuffer=0.5;
		}
		if (evt.key==OIS::KC_F4 && mKeyBuffer<0)
		{
			if(mPointLight)
			{

				mCurrentAttenuationSet=(mCurrentAttenuationSet+1)%ATTENUATION_SETS_SIZE;
				mPointLight->setAttenuation(ATTENUATION_SETS[mCurrentAttenuationSet][0],
					ATTENUATION_SETS[mCurrentAttenuationSet][1],
					ATTENUATION_SETS[mCurrentAttenuationSet][2],
					ATTENUATION_SETS[mCurrentAttenuationSet][3]);
			}
			mKeyBuffer=0.5;
		}
		if (evt.key==OIS::KC_F5 && mKeyBuffer<0)
		{
			//Since the ShadowTechnique enum doesn't list their techniques in order,
			//use a switch instead of increasing the value
			switch (mCurrentShadowTechnique)
			{
			case Ogre::SHADOWTYPE_NONE:
				mCurrentShadowTechnique=Ogre::SHADOWTYPE_STENCIL_ADDITIVE;
				break;
			case Ogre::SHADOWTYPE_STENCIL_ADDITIVE:
				mCurrentShadowTechnique=Ogre::SHADOWTYPE_STENCIL_MODULATIVE;
				break;
			case Ogre::SHADOWTYPE_STENCIL_MODULATIVE:
				mCurrentShadowTechnique=Ogre::SHADOWTYPE_TEXTURE_MODULATIVE;
				break;
			case Ogre::SHADOWTYPE_TEXTURE_MODULATIVE:
					mCurrentShadowTechnique=Ogre::SHADOWTYPE_NONE;
					break;
			default: break;
			}
			m_sceneManager->setShadowTechnique(mCurrentShadowTechnique);
			mKeyBuffer=0.5;
		}
		if (evt.key==OIS::KC_F6 && mKeyBuffer<0)
		{
			mIsAmbientEnabled=!mIsAmbientEnabled;
			m_sceneManager->setAmbientLight(mIsAmbientEnabled?DEFAULT_AMBIENT_LIGHT:Ogre::ColourValue::ZERO);
			mKeyBuffer=0.5;
		}
		if (evt.key==OIS::KC_F7 && mKeyBuffer<0)
		{
			if(mPointLight)
			{
				mCurrentPositionSet=(mCurrentPositionSet+1)%POSITION_SET_SIZE;
				Ogre::SceneNode* sceneNode = mPointLight->getParentSceneNode();
				sceneNode->setPosition(POSITION_SETS[mCurrentPositionSet]);
			}
			mKeyBuffer=0.5;
		}
		int spotlightIndex=-1;
		if (evt.key>=OIS::KC_1 && evt.key<=OIS::KC_4 && mKeyBuffer<0)
		{
			spotlightIndex=evt.key-1;	
			mKeyBuffer=0.5;
		}
		//
		if(spotlightIndex>0)
		{
			Ogre::String name="Spotlight"+Ogre::StringConverter::toString(spotlightIndex);
			mSpotlights[name]=!mSpotlights[name];
			m_sceneManager->getLight(name)->setVisible(mSpotlights[name]);
		}
		return true;
	}
	void initCameraSettings()
	{
		m_camera->setPosition(Ogre::Vector3(0,10,500));
		m_camera->lookAt(Ogre::Vector3::ZERO);
		m_camera->setNearClipDistance(5);
		m_camera->setAspectRatio(Ogre::Real(m_viewport->getActualWidth())/Ogre::Real(m_viewport->getActualHeight()));
	}
	void initGround()
	{
		Ogre::Plane plane(Ogre::Vector3::UNIT_Y,0);
		Ogre::MeshManager::getSingleton().createPlane(MESH_GROUND,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
			1500,1500,20,20,true,1,5,5,Ogre::Vector3::UNIT_Z);
		Ogre::Entity* entity = m_sceneManager->createEntity(ENTITY_GROUND,MESH_GROUND);
		m_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(entity);
		entity->setMaterialName("Examples/Rockwall");
		entity->setCastShadows(false);

	}
	void initPointLight()
	{
		mPointLight = m_sceneManager->createLight("PointLight");
		mPointLight->setType(Ogre::Light::LT_POINT);		

		mPointLight->setDiffuseColour(1.0,1.0,1.0);
		mPointLight->setSpecularColour(1.0,1.0,1.0);
		mPointLight->setAttenuation(600,1.0,0.007,0.0002);

		Ogre::SceneNode* sceneNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
		sceneNode->attachObject(mPointLight);
		sceneNode->setPosition(POSITION_SETS[mCurrentPositionSet]);
	}
	void initDirectionalLight()
	{
		mDirectionalLight= m_sceneManager->createLight("DirectionalLight");
		mDirectionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
		mDirectionalLight->setDiffuseColour(Ogre::ColourValue(.25, .25, 0));
		mDirectionalLight->setSpecularColour(Ogre::ColourValue(.25, .25, 0));
		//mDirectionalLight->setDirection(Ogre::Vector3::NEGATIVE_UNIT_X); 
		
		Ogre::SceneNode* sceneNode =m_sceneManager->getRootSceneNode()->createChildSceneNode();
		sceneNode->setDirection(Ogre::Vector3::NEGATIVE_UNIT_X);
		sceneNode->attachObject(mDirectionalLight);
	}
	void initSpotLights()
	{
		Ogre::Light* light;
		for (int i=0;i<SPOTLIGHT_NUM;i++)
		{
			Ogre::String name="Spotlight"+Ogre::StringConverter::toString(i+1);
			light= m_sceneManager->createLight(name);
			light->setType(Ogre::Light::LT_SPOTLIGHT);
			light->setPosition(gSpotlights[i].position);
			light->setDirection(gSpotlights[i].direction);
			light->setDiffuseColour(gSpotlights[i].diffuse);
			light->setSpecularColour(gSpotlights[i].specular);			
			light->setSpotlightRange(gSpotlights[i].innerAngle,gSpotlights[i].outerAngle,gSpotlights[i].falloff);

			mSpotlights[name]=true;
		}
	}
	void createScene()
	{
		//Init camera settings
		initCameraSettings();

		//set up global settings for lighting and shadows
		m_sceneManager->setAmbientLight(mIsAmbientEnabled?DEFAULT_AMBIENT_LIGHT:Ogre::ColourValue::ZERO);
		m_sceneManager->setShadowTechnique(mCurrentShadowTechnique);

		//create our "guinea-pig" entities
		Ogre::Entity* entity = m_sceneManager->createEntity(ENTITY_NINJA,"ninja.mesh");
		entity->setCastShadows(true);
		m_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(entity);

		//...and a plane on top of which it'll stand
		initGround();

		Ogre::Entity* sphere = m_sceneManager->createEntity("Sphere1","sphere.mesh");
		sphere->setMaterialName("MyMaterials/Bluish");
		sphere->setCastShadows(true);	

		Ogre::SceneNode* sceneNode =m_sceneManager->getRootSceneNode()->createChildSceneNode();
		sceneNode->attachObject(sphere);
		sceneNode->scale(0.25,0.25,0.25);
		sceneNode->setPosition(50,10,250);

		sphere = m_sceneManager->createEntity("Sphere2","sphere.mesh");
		sphere->setMaterialName("MyMaterials/Orange");
		sphere->setCastShadows(true);		

		sceneNode =m_sceneManager->getRootSceneNode()->createChildSceneNode();
		sceneNode->setPosition(Ogre::Vector3(0,10,250));
		sceneNode->attachObject(sphere);
		sceneNode->scale(0.25,0.25,0.25);


		initPointLight();
		initDirectionalLight();
		initSpotLights();

	}
	//Updates stats and prints debug info
	void updateStats()
	{
		Application::updateStats();

		Ogre::OverlayElement* guiDbg = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/DebugText");
		guiDbg->setTop(0);

		Ogre::String message = "";
		if (mPointLight)
		{
			message+="Range: "+ Ogre::StringConverter::toString(mPointLight->getAttenuationRange());
			message+="\n: Constant: "+Ogre::StringConverter::toString(mPointLight->getAttenuationConstant());
			message+="\n: Linear: "+Ogre::StringConverter::toString(mPointLight->getAttenuationLinear());
			message+="\n: Quadratic: "+Ogre::StringConverter::toString(mPointLight->getAttenuationQuadric());
			message+="\n Position: ("+Ogre::StringConverter::toString(mPointLight->getParentSceneNode()->getPosition())+")\n";

		}
		guiDbg->setCaption(message);
		
		
		message = "F1 - Toggle debug displays\n";
		message+="F2 - Rotate directional light around Y axis";
		message+="\nF3 - Rotate directional light around X axis";
		message+="\nF4 - Change point light's attenuation set\n";
		message+="F5 - Toggle shadow technique: current ";
		message+=getTechniqueName(mCurrentShadowTechnique);
		message+="\nF6 - Toggle ambient lighting. Currently ";
		message+= (mIsAmbientEnabled?"enabled\n":"disabled\n");
		message+="\nF7 - Change point light's position\n";
		message+="\n1,2,3,4 - Toggle spotlights[1..4]\n";

		m_debugWindow->setText(message);
		m_debugWindow->setAlpha(0.5);
		m_debugWindow->setSize(CEGUI::UVector2(CEGUI::UDim(0.5, 0), CEGUI::UDim(0.3, 0)));	
	}
	//Convenience method to get the technique's name
	Ogre::String getTechniqueName(Ogre::ShadowTechnique technique)
	{
		switch (technique)
		{
		case Ogre::SHADOWTYPE_NONE: return "SHADOWTYPE_NONE";
		case Ogre::SHADOWTYPE_STENCIL_ADDITIVE:return "SHADOWTYPE_STENCIL_ADDITIVE";
		case Ogre::SHADOWTYPE_STENCIL_MODULATIVE:return "SHADOWTYPE_STENCIL_MODULATIVE";
		case Ogre::SHADOWTYPE_TEXTURE_MODULATIVE:return "SHADOWTYPE_TEXTURE_MODULATIVE";
		default:return "";
		}
	}
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
		BasicLightingDemoApp* app=new BasicLightingDemoApp();
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