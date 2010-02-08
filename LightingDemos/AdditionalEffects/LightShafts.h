#ifndef LIGHTSHAFTSH_H
#define LIGHTSHAFTSH_H

#include <Ogre.h>

#define CAMERA_SUFFIX "Camera"
#define BILLBOARDSET_SUFFIX "PrjBillboardSet"
#define MATERIAL_SUFFIX "Material"
#define DEPTH_MATERIAL_SUFFIX "Depth"
#define RTT_SUFFIX "RTT"
#define LIGHT_SUFFIX "Light"


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
	Ogre::Vector3 direction;
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

	LightShaftsProjector(Ogre::SceneManager* sceneManager, Ogre::String baseMaterialName);
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
	Ogre::Vector3		mOriginalDirection;
};

// Just for change all entities materials in depth rtt
class LightDepthMapRttListener : public Ogre::RenderTargetListener
{
public:
	LightDepthMapRttListener(Ogre::SceneManager *sm,Ogre::BillboardSet* billboardSet, Ogre::String depthMaterialName);

	void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
	void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);

private:
	std::queue<std::string> mMaterials;	
	Ogre::SceneManager *mSceneMgr;
	Ogre::String mDepthMaterialName;
	Ogre::BillboardSet* mBillboardSet;
};
#endif