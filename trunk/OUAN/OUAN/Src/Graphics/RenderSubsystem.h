#ifndef RENDERSUBSYSTEMH_H
#define RENDERSUBSYSTEMH_H

#include "../OUAN.h"
#include <NxOgre.h>
#include <NxOgreOGRE3D.h>
#include <NxOgreAddonCharacterController.h>

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

		/// init the subsystem from the options read in the configuration file
		void init (ApplicationPtr app,OUAN::ConfigurationPtr config);		
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

		/// Create visual debugger
		void createVisualDebugger(OUAN::ConfigurationPtr config);

		/// Create debug floor for physics
		void createDebugFloor(OUAN::ConfigurationPtr config);

		/// Load resources [TODO: Make this level dependent?]
		void initResourceGroups(OUAN::ConfigurationPtr config);

		/// Setup the scene [TODO: Make this level dependent?]
		void defaultSetupScene(OUAN::ConfigurationPtr config);
		//Scene configuration methods
		
		/// Create the scene, and place initial objects on it
		void createScene();

		/// Create overlays
		void createOverlays();

		/// Translate/Rotate camera's position with mouse
		void moveCamera(const OIS::MouseEvent &e);
		/// Translate/Rotate camera's position according to the given relative translations
		/// @param xRel	relative translation along the X Axis
		/// @param yRel	relative translation along the Y Axis
		/// @param zRel relative translation along the Z Axis
		void moveCamera(double xRel, double yRel, double zRel);

		/// Translate camera according to the given coordinate axis
		/// @param worldCoordinateAxis
		void translateCamera(TCoordinateAxis worldCoordinateAxis);

		/// Render scene at current frame
		/// @return <b>true</b> if the frame was successfully rendered
		bool render();

		/// Return read-only pointer to the main window
		/// @return main window
		Ogre::RenderWindow* getWindow() const;

		/// Return read-only pointer to the camera
		/// @return camera
		CameraManager* getCameraManager() const;


		/// Return read-only pointer to the scene manager
		/// @return scene manager
		Ogre::SceneManager* getSceneManager() const;

		/// Tell if the window has been closed
		/// @return <b>true</b> if the window has been closed
		bool isWindowClosed() const;
		
		/// Update the parameters that control the camera's
		/// movement
		/// @param	elapsedTime	time since last frame was processed
		void updateCameraParams(double elapsedTime);
		
		//Object creators

		Ogre::Entity* createEntity(Ogre::String name,TRenderComponentEntityParameters tEntityParameters);
		Ogre::SceneNode* createSceneNode(Ogre::String name,TRenderComponentPositionalParameters tSceneNodeParameters);
		Ogre::Light* createLight(Ogre::String name,TRenderComponentLightParameters TRenderComponentLightParameters);
		Ogre::ParticleSystem* createParticleSystem(Ogre::String name,TRenderComponentParticleSystemParameters TRenderComponentParticleSystemParameters);
		Ogre::BillboardSet* createBillboardSet(Ogre::String name,TRenderComponentBillboardSetParameters TRenderComponentBillboardSetParameters);
		Ogre::Viewport* createViewport(Ogre::String name,TRenderComponentViewportParameters TRenderComponentViewportParameters);
		Ogre::Camera* createCamera(Ogre::String name,TRenderComponentCameraParameters tRenderComponentCameraParameters);
		Ogre::SceneManager* createSceneManager(Ogre::String name,TRenderComponentSceneParameters TRenderComponentSceneParameters);

		/// Getters and setters
		Ogre::String getDebugMessage();
		void setDebugMessage(Ogre::String debugMessage);

		/// Update stats
		void updateStats();

		/// Update debug info
		void updateDebugInfo();

		/// Update visual debugger stuff
		void updateVisualDebugger();
		// Control visual debugger's visibility
		/// Turn on visual debugger
		void showVisualDebugger();
		/// Turn off visual debugger
		void hideVisualDebugger();

		/// Turn on debug overlay's visibility
		void showDebugOverlay();
		/// Turn off debug overlay's visibility
		void hideDebugOverlay();
		
		/// Display HUD
		void showHUD();


	protected:
		/// the application
		OUAN::ApplicationPtr mApp;

		/// Creators not used outside the render subsystem
		void createSubEntity(Ogre::Entity *pEntity,int num,String material,bool visible);
		void createMeshFile(String meshfile);
		void createBillboard(Ogre::BillboardSet * pBillboardSet,ColourValue colour,Vector2 dimensions,Vector3 position,Real rotation,int texcoordindex,Vector4 texrect);
		void createSkyBox(bool active, String material, Real distance);
		void createSkyDome(bool active, String material);


		/// Ogre root object
		RootPtr mRoot;

		/// Scene manager
		Ogre::SceneManager* mSceneManager;

		/// Main window
		// [IMPORTANT: notice a shared_ptr is not used here, since we don't 'own' the 
		// window]
		Ogre::RenderWindow* mWindow;

		/// Camera Manager
		CameraManager* mCameraManager;

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

		/// NxOgre Render System
		NxOgre::VisualDebugger*	mNxOgreVisualDebugger;
		OGRE3DRenderable*		mNxOgreVisualDebuggerRenderable;
		Ogre::SceneNode*		mNxOgreVisualDebuggerNode;

		/// Debug message, to be written by other subsystems
		Ogre::String debugMessage;
	};
}
#endif
