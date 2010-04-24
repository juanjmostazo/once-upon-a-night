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

		/// Set ambient specular and diffuse mateial components off
		void initMaterials();

		///set lightmaps
		void setLightmaps(Ogre::Entity * pEntity);

		/// Clear current Scene
		void clear();

		/// Create overlays
		void createOverlays();


		/// Translate camera according to the given coordinate axis
		/// @param worldCoordinateAxis
		//void translateCamera(TCoordinateAxis worldCoordinateAxis);

		/// Render scene at current frame
		/// @return <b>true</b> if the frame was successfully rendered
		bool render();

		/// Return read-only pointer to the main window
		/// @return main window
		Ogre::RenderWindow* getWindow() const;

		/// Return read-only pointer to the ogre root
		/// @return ogre root
		RootPtr getRoot() const;

		/// Return read-only pointer to the scene manager
		/// @return scene manager
		Ogre::SceneManager* getSceneManager() const;

		/// Tell if the window has been closed
		/// @return <b>true</b> if the window has been closed
		bool isWindowClosed() const;
		
	
		//Object creators
		Ogre::Entity* createEntity(Ogre::String nodeName,Ogre::String name,TRenderComponentEntityParameters tEntityParameters,QueryFlags flags=QUERYFLAGS_NONE);
		Ogre::SceneNode* createSceneNode(Ogre::String name,TRenderComponentPositionalParameters tSceneNodeParameters);
		Ogre::Light* createLight(Ogre::String name,TRenderComponentLightParameters TRenderComponentLightParameters);
		Ogre::ParticleSystem* createParticleSystem(Ogre::String name,TRenderComponentParticleSystemParameters TRenderComponentParticleSystemParameters);
		Ogre::BillboardSet* createBillboardSet(Ogre::String name,TRenderComponentBillboardSetParameters TRenderComponentBillboardSetParameters);
		Ogre::SceneManager* setSceneParameters(Ogre::String name,TRenderComponentSceneParameters TRenderComponentSceneParameters);
		RenderComponentDecalPtr createDecal(GameObjectPtr gameObject,TRenderComponentDecalParameters tRenderComponentDecalParameters);


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
