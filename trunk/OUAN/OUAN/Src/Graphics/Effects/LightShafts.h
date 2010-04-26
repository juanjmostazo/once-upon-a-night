#ifndef LIGHTSHAFTSH_H
#define LIGHTSHAFTSH_H

#include <Ogre.h>

namespace OUAN
{

	const std::string CAMERA_SUFFIX="Camera";
	const std::string BILLBOARDSET_SUFFIX="PrjBillboardSet";
	const std::string MATERIAL_SUFFIX="Material";
	const std::string DEPTH_MATERIAL_SUFFIX="Depth";
	const std::string RTT_SUFFIX="RTT";
	const std::string LIGHT_SUFFIX="Light";


	typedef struct 
	{
		Ogre::Radian innerAngle;
		Ogre::Radian outerAngle;
		Ogre::Real falloff;
		Ogre::ColourValue diffuse;
		Ogre::ColourValue specular;	
		bool attenuate;
		Ogre::Real attenuationRange;
		Ogre::Real attenuationConstant;
		Ogre::Real attenuationLinear;
		Ogre::Real attenuationQuadratic;
	} TSpotlightSettings;

	typedef struct  
	{
		Ogre::Vector3 position;
		Ogre::Quaternion orientation;
		Ogre::String cookieName;
		Ogre::Real nearClipDistance;
		Ogre::Real farClipDistance;
		Ogre::Real aspectRatio;
		Ogre::Radian fovy;
		bool showDebug;
		int numberOfPlanes;

		//Light properties
		bool useSpotLight;
		TSpotlightSettings spotlightSettings;

	} TProjectorSettings;

	class LightShaftsProjector
	{
	public: 
		void setCookie(const Ogre::String& cookieName);
		void update(float elapsedTime);
		void updateTextureProjectionMatrix();
		void createLightShafts(const int& numberOfPlanes);
		void createLightCameraRTT();
		void initProjector(const TProjectorSettings& projectorSettings);
		void initSpotlight(const TSpotlightSettings& spotlightSettings);
		void setProjectorName(const Ogre::String& projectorName);
		void toggle();
		void flipRotateEnabled();
		void hide();
		void show();

		LightShaftsProjector(Ogre::SceneManager* sceneManager, Ogre::String baseMaterialName,Ogre::SceneNode* sceneNode=NULL);
		virtual ~LightShaftsProjector();

	protected:
		Ogre::SceneManager* mSceneManager;
		Ogre::BillboardSet* mBillboardSet;
		Ogre::Camera*		mProjectorCamera;
		Ogre::SceneNode*	mProjectorSceneNode;
		Ogre::String		mProjectorName;
		Ogre::Light*		mLight;
		Ogre::String		mBaseMaterialName;
		bool				mSwitchedOn;
		bool				mRotateEnabled;
	};

	// Just for change all entities materials in depth rtt
	class LightDepthMapRttListener : public Ogre::RenderTargetListener
	{
	public:
		LightDepthMapRttListener(Ogre::SceneManager *sm,Ogre::BillboardSet* billboardSet, Ogre::String depthMaterialName);

		void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
		void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);

	private:
		std::queue<Ogre::String> mMaterials;	
		Ogre::SceneManager *mSceneMgr;
		Ogre::String mDepthMaterialName;
		Ogre::BillboardSet* mBillboardSet;
	};

}
#endif