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

		/// Clear current Scene
		void clear();

		/// Create overlays
		void createOverlays();

		/// Translate/Rotate camera's position with mouse
		void moveCamera(Ogre::Vector2 cameraRotation);

		/// Translate camera according to the given coordinate axis
		/// @param worldCoordinateAxis
		//void translateCamera(TCoordinateAxis worldCoordinateAxis);

		/// Render scene at current frame
		/// @return <b>true</b> if the frame was successfully rendered
		bool render();

		/// Return read-only pointer to the main window
		/// @return main window
		Ogre::RenderWindow* getWindow() const;

		/// Return read-only pointer to the camera manager
		/// @return camera manager
		CameraManager* getCameraManager() const;

		/// Return read-only pointer to the trajectory manager
		/// @return trajectory manager
		TrajectoryManager* getTrajectoryManager() const;

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

		/// Set target for camera manager
		/// @param	renderComponentPositional is the RenderComponentPositional which we will set as the camera's target
		void setCameraTarget(RenderComponentPositional * renderComponentPositional);

		void setHealthHudData(const std::string& overlayName, int numLives, const std::string& healthMaterialName, const std::string& texName);
		
		//Object creators

		Ogre::Entity* createEntity(Ogre::String nodeName,Ogre::String name,TRenderComponentEntityParameters tEntityParameters,QueryFlags flags=QUERYFLAGS_NONE);
		Ogre::SceneNode* createSceneNode(Ogre::String name,TRenderComponentPositionalParameters tSceneNodeParameters);
		Ogre::Light* createLight(Ogre::String name,TRenderComponentLightParameters TRenderComponentLightParameters);
		Ogre::ParticleSystem* createParticleSystem(Ogre::String name,TRenderComponentParticleSystemParameters TRenderComponentParticleSystemParameters);
		Ogre::BillboardSet* createBillboardSet(Ogre::String name,TRenderComponentBillboardSetParameters TRenderComponentBillboardSetParameters);
		Ogre::Viewport* setViewportParameters(Ogre::String name,TRenderComponentViewportParameters TRenderComponentViewportParameters);
		RenderComponentCameraPtr createCamera(Ogre::String name,TRenderComponentCameraParameters tRenderComponentCameraParameters);
		Ogre::SceneManager* setSceneParameters(Ogre::String name,TRenderComponentSceneParameters TRenderComponentSceneParameters);

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

		/// Activates next camera
		void changeCamera();
		/// Activates next camera controller type
		void changeCameraController();

		/// Hides the overlay named 'overlayName', if found
		/// @param overlayName	name of the overlay to hide
		void hideOverlay(const std::string& overlayName);
		/// Display the overlay named 'overlayName', if found
		void showOverlay(const std::string& overlayName);
		/// Hide the overlay element named as 'overlayName' if found
		/// @param overlayName name of the overlay element
		void hideOverlayElement(const std::string& overlayName);
		/// Display the overlay element named as 'overlayName' if found
		/// @param overlayName name of the overlay element
		void showOverlayElement(const std::string& overlayName);

		void pauseRendering();
		void resumeRendering();

		void clearScene();
		void resetScene();

		void captureScene(const std::string& name);

		void setTextureData (const std::string& materialName, const std::string& textureName, 
			bool isAnimated, int numFrames, float duration);
		bool isAnimatedTextureFinished(const std::string& materialName);

	protected:
		/// the application
		OUAN::ApplicationPtr mApp;

		/// Creators not used outside the render subsystem
		void createSubEntity(Ogre::Entity *pEntity,int num,String material,bool visible);
		void createMeshFile(String meshfile);
		void createBillboard(Ogre::BillboardSet * pBillboardSet,ColourValue colour,Vector2 dimensions,Vector3 position,Real rotation,int texcoordindex,Vector4 texrect);

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

		/// Pointer to the trajectory manager
		TrajectoryManager* mTrajectoryManager;

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
