// ----------------------------------------------------------------------------
// Include the main OGRE header files
// Ogre.h just expands to including lots of individual OGRE header files
// ----------------------------------------------------------------------------
#include <Ogre.h>
#define SKYBOX "Sky/EarlyMorning"


int gChannelIndex;
// --------------------------------
//  Our own application framework
// ---------------------------------
#include "Application.h"
#include "SoundSubsystem.h"
using namespace OUAN;
class SoundDemoApp: public Application
{
private:
	double mKeyBuffer;
	int mIndex;
	int mEntityIndex;
	int mChannel;
	int mEntityChannelIndex;
	SoundSubsystemPtr mSubsystem;

protected:
	void setupScene()
	{
		TSoundSubsystemConfigData config;
		config.mDistanceFactor=DISTANCE_FACTOR;
		config.mDopplerScale=DOPPLER_SCALE;
		config.mRollOffScale=ROLLOFF_SCALE;

		config.mNumChannels=50;
		config.mMasterVolume=1.0;
		config.mMasterPitch=1.0;
		config.mMasterVolumeEnabled = true;

		//two music channels
		config.mMusicVolume=0.4;
		config.mMusicPitch=1.0;
		config.mMusicVolumeEnabled= true;
		config.mMusicNumChannels= 2;

		//21 sound effect channels
		config.mSfxVolume=1.0;
		config.mSfxPitch=1.0;
		config.mSfxVolumeEnabled= true;
		config.mSfxNumChannels= 48;

		mSubsystem->init(config);
		m_sceneManager = m_root->createSceneManager(Ogre::ST_GENERIC,"Default");
		createCameras();
		createViewports();	
		createScene();
	}
public:
	SoundDemoApp()
		:Application("Sound demo app")
		,mKeyBuffer(-1)
		,mChannel(-1)
		,mIndex(-1)
		,mEntityIndex(-1)
		,mEntityChannelIndex(-1)
	{
		mSubsystem=SoundSubsystemPtr(new SoundSubsystem());

	}
	~SoundDemoApp()
	{
		mSubsystem->cleanUp();
	}
	bool keyPressed(const OIS::KeyEvent& evt)
	{
		bool rc = Application::keyPressed(evt);
		if (evt.key==OIS::KC_P && mKeyBuffer<0)
		{
			mKeyBuffer=0.5;
		}
		if (evt.key==OIS::KC_R && mKeyBuffer<0)
		{
			int i;
			mSubsystem->playSound("test",i);
			mKeyBuffer=0.5;
		}
		if (evt.key==OIS::KC_T && mKeyBuffer<0)
		{
			mSubsystem->stopSound(gChannelIndex);
			mKeyBuffer=0.5;
		}
		if (evt.key==OIS::KC_H && mKeyBuffer<0)
		{
			mSubsystem->playMusic("Fire",gChannelIndex,true);
			mKeyBuffer=0.5;
		}
		if (evt.key==OIS::KC_U && mKeyBuffer<0)
		{
			mSubsystem->setChannelGroupVolume(SM_CHANNEL_MUSIC_GROUP,mSubsystem->getChannelGroupVolume(SM_CHANNEL_MUSIC_GROUP)+0.30);
			mKeyBuffer=0.5;
		}
		if (evt.key==OIS::KC_I && mKeyBuffer<0)
		{
			mSubsystem->setChannelGroupVolume(SM_CHANNEL_MUSIC_GROUP,mSubsystem->getChannelGroupVolume(SM_CHANNEL_MUSIC_GROUP)-0.30);
			mKeyBuffer=0.5;
		}
		return true;
	}
	
	void updateLogic(float elapsedTime)
	{
		checkCameraHeight();
		Application::updateLogic(elapsedTime);
		mSubsystem->set3DAttributes(m_camera->getParentSceneNode()->getPosition(),Ogre::Vector3::ZERO,
			m_camera->getParentSceneNode()->getOrientation()*Ogre::Vector3::UNIT_Z,Ogre::Vector3::UNIT_Y);
		mSubsystem->update(elapsedTime);
		mKeyBuffer-=elapsedTime;
	}
	void checkCameraHeight()
	{
		Ogre::RaySceneQuery *raySceneQuery = 
			m_sceneManager->
			createRayQuery(Ogre::Ray(m_camera->getPosition() + Ogre::Vector3(0,10000,0), 
			Ogre::Vector3::NEGATIVE_UNIT_Y));
		Ogre::RaySceneQueryResult& qryResult = raySceneQuery->execute();
		Ogre::RaySceneQueryResult::iterator i = qryResult.begin();
		if (i != qryResult.end() && i->worldFragment)
		{
			if (m_camera->getPosition().y < i->worldFragment->singleIntersection.y + 30)
			{
				m_camera->setPosition(m_camera->getPosition().x, i->worldFragment->singleIntersection.y + 30, m_camera->getPosition().z);
			}
		}

		delete raySceneQuery;
	}
	void createScene()
	{
		m_sceneManager->setAmbientLight(Ogre::ColourValue(1,1,1));
		m_sceneManager->setSkyBox(true,SKYBOX,99999*3,true);
		m_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_NONE);

		m_camera->setPosition(Ogre::Vector3(0,10,500));
		m_camera->lookAt(Ogre::Vector3::ZERO);
		m_camera->setNearClipDistance(5);
		m_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(m_camera);
		m_camera->setAspectRatio(Ogre::Real(m_viewport->getActualWidth())/Ogre::Real(m_viewport->getActualHeight()));

		//create our "guinea-pig" entities
		Ogre::Entity* entity = m_sceneManager->createEntity("Ninja","ninja.mesh");
		entity->setCastShadows(true);
		Ogre::SceneNode* sn = m_sceneManager->getRootSceneNode()->createChildSceneNode();
		sn->attachObject(entity);
		entity->getParentSceneNode()->setPosition(Ogre::Vector3::ZERO);
		entity->getParentSceneNode()->scale(50,50,50);

		//...and a plane on top of which it'll stand
		Ogre::Plane plane(Ogre::Vector3::UNIT_Y,0);
		Ogre::MeshManager::getSingleton().createPlane("Ground",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
			1500,1500,20,20,true,1,5,5,Ogre::Vector3::UNIT_Z);
		entity = m_sceneManager->createEntity("GroundEntity","Ground");
		m_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(entity);
		entity->setMaterialName("Examples/Rockwall");
		entity->setCastShadows(false);

		mSubsystem->addSound("Fire",SOUND_BASE_PATH+"Fire.mp3",SM_CHANNEL_MUSIC_GROUP,SOUND_FLAG_LOOP|SOUND_FLAG_HARDWARE|SOUND_FLAG_STREAM);
		mSubsystem->playMusic("Fire",gChannelIndex);
		//mSubsystem->playSound(mIndex,sn,&mChannel);

		Ogre::Entity* sphere = m_sceneManager->createEntity("Sphere1","sphere.mesh");
		//lightSphere->setMaterialName("Examples/Hilite/Yellow");
		Ogre::SceneNode* sphereNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
		sphereNode->attachObject(sphere);
		sphereNode->setPosition(200,0,0);
		sphereNode->scale(0.25,0.25,0.25);

		mSubsystem->addSound("test",SOUND_BASE_PATH+"test.wav",SM_CHANNEL_SFX_GROUP,SOUND_FLAG_HARDWARE);
		

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
		SoundDemoApp* app=new SoundDemoApp();
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