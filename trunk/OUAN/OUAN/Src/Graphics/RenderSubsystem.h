#ifndef RENDERSUBSYSTEMH_H
#define RENDERSUBSYSTEMH_H

#include "../OUAN.h"
#include <NxOgre.h>
#include <NxOgreOGRE3D.h>
#include <NxOgreAddonCharacterController.h>

#include "ParticleUniverseSystemManager.h"
#include "Bar/LoadingBar.h"

namespace OUAN
{
	const int DEFAULT_SHADOW_TEXTURE_COUNT=4;
	const int DEFAULT_SHADOW_TEXTURE_SIZE=256;
	const Ogre::PixelFormat DEFAULT_SHADOW_TEXTURE_PIXEL_FORMAT=Ogre::PF_FLOAT16_GR;
	const std::string DEFAULT_SHADOW_TEXTURE_CASTER_MATERIAL="shadow_caster";
	const bool DEFAULT_SHADOW_CASTER_RENDER_BACK_FACES=false;

	const std::string SHADOWS_CONFIG_PATH="../../Config/shadows-cfg.xml";
	//Config keys
	const std::string CONFIG_KEYS_SHADOW_TEXTURE_CASTER_MATERIAL="SHADOW_TEXTURE_CASTER_MATERIAL";
	const std::string CONFIG_KEYS_SHADOW_TEXTURE_COUNT="SHADOW_TEXTURE_COUNT";
	const std::string CONFIG_KEYS_SHADOW_TEXTURE_SIZE="SHADOW_TEXTURE_SIZE";
	const std::string CONFIG_KEYS_SHADOW_TEXTURE_PIXEL_FORMAT="SHADOW_TEXTURE_PIXEL_FORMAT";
	const std::string CONFIG_KEYS_SHADOW_TEXTURE_CASTER_RENDER_BACK_FACES="SHADOW_RENDER_BACK_FACES";

	class SSAOListener: public Ogre::CompositorInstance::Listener
	{
	private:
		Ogre::Camera* mCam;
	public:
		SSAOListener();
		void setCamera(Ogre::Camera* cam);
		void notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat);
	};

	class ShadowListener: public Ogre::SceneManager::Listener
	{
		// this is a callback we'll be using to set up our shadow camera
		void shadowTextureCasterPreViewProj(Ogre::Light *light, Ogre::Camera *cam, size_t);
		void shadowTexturesUpdated(size_t);
		void shadowTextureReceiverPreViewProj(Ogre::Light*, Ogre::Frustum*);
		void preFindVisibleObjects(Ogre::SceneManager*, Ogre::SceneManager::IlluminationRenderStage, Ogre::Viewport*);
		void postFindVisibleObjects(Ogre::SceneManager*, Ogre::SceneManager::IlluminationRenderStage, Ogre::Viewport*);
	};

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
		bool init (OUAN::ConfigurationPtr config);

		void create(ApplicationPtr app,OUAN::ConfigurationPtr config);

		/// Free memory used by the rendering subsystem
		void cleanUp();

		/// Create Ogre root object
		void createRoot(OUAN::ConfigurationPtr config);

		/// Define resource paths
		void defineResources(OUAN::ConfigurationPtr config);

		/// Sets up Ogre rendering system
		bool setupRenderSystem(OUAN::ConfigurationPtr config);

		/// Create main window
		void createRenderWindow(OUAN::ConfigurationPtr config);

		/// Create visual debugger
		void createVisualDebugger(OUAN::ConfigurationPtr config);

		/// Create debug floor for physics
		void createDebugFloor(OUAN::ConfigurationPtr config);

		void initShadows();

		/// Load resources [TODO: Make this level dependent?]
		void initResourceGroups(OUAN::ConfigurationPtr config);

		/// Set ambient specular and diffuse mateial components off
		void initMaterials();

		/// Init textures 3d
		void initTextures3D();

		///set lightmaps
		void setLightmaps(Ogre::Entity * pEntity);

		/// Clear current Scene
		void clear();

		/// Create overlays
		void createOverlays();

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
		Ogre::Entity* createPlane(Ogre::String nodeName,Ogre::String name,TRenderComponentPlaneParameters tPlaneParameters);
		Ogre::Entity* createEntity(Ogre::String nodeName,Ogre::String name,TRenderComponentEntityParameters tEntityParameters);
		Ogre::SceneNode* createSceneNode(Ogre::String name,TRenderComponentPositionalParameters tSceneNodeParameters);
		Ogre::Light* createLight(Ogre::String name,TRenderComponentLightParameters TRenderComponentLightParameters);
		std::vector<ParticleUniverse::ParticleSystem*> createParticleSystems(Ogre::String name,TRenderComponentParticleSystemParameters TRenderComponentParticleSystemParameters, RenderComponentPositionalPtr pRenderComponentPositional);
		Ogre::BillboardSet* createBillboardSet(Ogre::String nodeName,Ogre::String name,TRenderComponentBillboardSetParameters TRenderComponentBillboardSetParameters);
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

		/// Load params from config file
		bool loadConfig();

		/// Compositor name values
		std::string BLOOM;
		std::string HDR;
		std::string RADIAL_BLUR;
		std::string MOTION_BLUR;

		bool BLOOM_ACTIVATED_ALWAYS_DREAMS;
		bool BLOOM_ACTIVATED_ALWAYS_NIGHTMARES;
		std::string BLOOM_BLEND_MATERIAL;
		double MAX_BLOOM_BLEND;

		bool HDR_ACTIVATED_ALWAYS_DREAMS;
		bool HDR_ACTIVATED_ALWAYS_NIGHTMARES;

		bool RADIAL_BLUR_ACTIVATED_ALWAYS_DREAMS;
		bool RADIAL_BLUR_ACTIVATED_ALWAYS_NIGHTMARES;

		bool MOTION_BLUR_ACTIVATED_ALWAYS_DREAMS;
		bool MOTION_BLUR_ACTIVATED_ALWAYS_NIGHTMARES;

		// BAR STUFF
		int mNumGroups;
		double mReadProportion;

		// WORK IN PROGRESS!!!
		SSAOListener ssaoListener;

		Ogre::TexturePtr getTexture3D(std::string texture3D);

		TextureRendererPtr getTextureRenderer();

		void initTextureRenderer();

	protected:
		/// the application
		OUAN::ApplicationPtr mApp;

		/// Creators not used outside the render subsystem
		void createSubEntity(Ogre::Entity *pEntity,int num,String material,bool visible);
		void createMeshFile(String meshfile, bool prepareForNormalMapping=false);
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

		/// Loading bar
		LoadingBar mLoadingBar;

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

		// For the soft shadows: WORK IN PROGRESS
		ShadowListener shadowListener;

		// Texture 3D variables
		bool mTexturesInitialized;

		Ogre::TexturePtr mTexture3D_1_8;
		Ogre::TexturePtr mTexture3D_1_16;
		Ogre::TexturePtr mTexture3D_1_32;
		Ogre::TexturePtr mTexture3D_1_64;
		Ogre::TexturePtr mTexture3D_1_128;

		Ogre::TexturePtr mTexture3D_2_8;
		Ogre::TexturePtr mTexture3D_2_16;
		Ogre::TexturePtr mTexture3D_2_32;
		Ogre::TexturePtr mTexture3D_2_64;
		Ogre::TexturePtr mTexture3D_2_128;

		TextureRendererPtr mTextureRenderer;
	};
}
#endif
