#ifndef RENDERSUBSYSTEMH_H
#define RENDERSUBSYSTEMH_H

#include "../OUAN.h"

namespace OUAN
{
	/// This class will encapsulate the rendering functionality
	/// Atm, the rendering engine it's based on is Ogre3D
	class RenderSubsystem
	{
	public:
		/// Constructor: Sets window name according to the parameter
		/// @param windowName the name of the main window
		RenderSubsystem(std::string windowName=DEFAULT_WIN_NAME);

		/// Destructor
		virtual ~RenderSubsystem();

		/// Initialise the subsystem from the options read in the configuration file
		void initialise (ApplicationPtr app,OUAN::ConfigurationPtr config);		
		/// Free memory used by the rendering subsystem
		void cleanUp();

		/// Create Ogre root object
		void createRoot(OUAN::ConfigurationPtr config);

		/// Define resource paths
		void defineResources(OUAN::ConfigurationPtr config);

		/// Sets up Ogre rendering system
		void setupRenderSystem(OUAN::ConfigurationPtr config);
		
		/// Create main window
		void createRenderWindow(OUAN::ConfigurationPtr config);

		/// Load resources [TODO: Make this level dependent?]
		void initialiseResourceGroups(OUAN::ConfigurationPtr config);

		/// Setup the scene [TODO: Make this level dependent?]
		void setupScene(OUAN::ConfigurationPtr config);
		//Scene configuration methods
		
		/// Create the scene, and place initial objects on it
		void createScene();
		/// Create cameras
		void createCameras();
		/// Create viewports
		void createViewports();

		/// Translate/Rotate camera's position with mouse
		void moveCamera(const OIS::MouseEvent &e);

		/// Render scene at current frame
		/// @return <b>true</b> if the frame was successfully rendered
		bool render();

		/// Return read-only pointer to the main window
		/// @return main window
		Ogre::RenderWindow* getWindow() const;
		/// Return read-only pointer to the camera
		/// @return camera
		Ogre::Camera* getCamera() const;
		/// Return read-only pointer to the viewport
		/// @return viewport
		Ogre::Viewport* getViewport() const;

		/// Return read-only pointer to the scene manager
		/// @return scene manager
		Ogre::SceneManager* getSceneManager() const;

		CameraControllerFirstPerson* getCameraControllerFirstPerson() const;

		/// Tell if the window has been closed
		/// @return <b>true</b> if the window has been closed
		bool isWindowClosed() const;

		/// Change camera position at relative increments
		/// @param ratio scaling ratio to increase/decrease speed
		void relativeMoveCam(const int& ratio=1);
		
		/// Update the parameters that control the camera's
		/// movement
		/// @param	elapsedTime	time since last frame was processed
		void updateCameraParams(float elapsedTime);

		/// Translate camera position according to a given coordinate axis
		/// @param	coordAxis	coordinate axis in whose direction the camera position
		///						will be translated
		void translateCam(const TCoordinateAxis& coordAxis);
		

		//Object creators
		void createMeshFile(String meshfile);
		Ogre::Entity* createEntity(String name,String meshfile,bool castshadows);
		void createSubEntity(String name,int num,String material,bool visible);
		Ogre::SceneNode* createSceneNode(String name,String parentSceneNodeName,Vector3 position,Quaternion orientation,Vector3 scale,String autotracktarget);
		Ogre::Light* createLight(String name,Ogre::Light::LightTypes lighttype,ColourValue diffuse,ColourValue specular,Vector3 direction,bool castshadows,Vector3 lightrange,Vector4 attenuation,Real power);
		Ogre::ParticleSystem* createParticleSystem(String name,String particle,bool castshadows);
		void createBillboard(String billBoardSetName,ColourValue colour,Vector2 dimensions,Vector3 position,Real rotation,int texcoordindex,Vector4 texrect);
		Ogre::BillboardSet* createBillboardSet(OUAN::String name,OUAN::String material,Ogre::BillboardOrigin billboardorigin,Ogre::BillboardRotationType billboardrotation,Ogre::BillboardType billboardtype,OUAN::Real defaultheight,OUAN::Real defaultwidth,bool pointrendering,OUAN::Real renderdistance,bool sorting);
		void createViewport(String name,ColourValue colour,int compositorcount,int index,bool overlays,bool shadows,bool skies);
		Ogre::Camera* createCamera(String name,Vector3 position,Quaternion orientation,String autotracktarget,bool autoaspectratio,Vector2 clipdistance,Real fov,Ogre::PolygonMode polygonmode, int viewmode);
		void createOctreeSceneManager(String name,ColourValue ambient);
		void createSkyBox(bool active, String material, Real distance);
		void createSkyDome(bool active, String material);

	protected:
		/// the application
		OUAN::ApplicationPtr mApp;

		/// Ogre root object
		boost::shared_ptr<Ogre::Root> mRoot;

		/// Main window
		// [IMPORTANT: notice a shared_ptr is not used here, since we don't 'own' the 
		// window]
		Ogre::RenderWindow* mWindow;

		/// Scene manager
		Ogre::SceneManager* mSceneManager;

		/// Main camera
		Ogre::Camera* mCamera;

		/// Camera Controller
		CameraControllerFirstPerson* mCameraControllerFirstPerson;

		/// Viewport
		Ogre::Viewport* mViewport;

		/// Window name
		std::string mWindowName;

		//Attributes used to handle the default
		//camera movements

		/// Vector used to translate the camera's position accordingly
		Ogre::Vector3			mTranslateVector;
		/// Camera movement speed
		Ogre::Real				mMoveSpeed; 
		/// Camera movement scale
		Ogre::Real				mMoveScale; 
		/// Camera rotation speed
		Ogre::Degree			mRotateSpeed; 
		/// Camera rotation scale
		Ogre::Degree			mRotScale;

	};
}
#endif
