#include "LightShafts.h"

using namespace OUAN;

LightShaftsProjector::LightShaftsProjector(Ogre::SceneManager* sceneManager,Ogre::String baseMaterialName, Ogre::SceneNode* sceneNode)
:mSceneManager(sceneManager)
,mBillboardSet(NULL)
,mProjectorCamera(NULL)
,mProjectorSceneNode(sceneNode)
,mProjectorName("")
,mLight(NULL)
,mBaseMaterialName(baseMaterialName)
,mSwitchedOn(false)
,mRotateEnabled(false)
{

}

LightShaftsProjector::~LightShaftsProjector()
{
	mSceneManager=NULL;
	if (mSceneManager)
	{
		mSceneManager->destroyCamera(mProjectorName+CAMERA_SUFFIX);
		mSceneManager->destroyBillboardSet(mProjectorName+BILLBOARDSET_SUFFIX);
	}
}

void LightShaftsProjector::setCookie(const Ogre::String& cookieName)
{
	static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(mProjectorName+MATERIAL_SUFFIX))->
		getTechnique(0)->getPass(0)->getTextureUnitState(1)->
		setTextureName(cookieName);
}

void LightShaftsProjector::update(float elapsedTime)
{

	// Upload current position to light shafts materials
	static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(mProjectorName+MATERIAL_SUFFIX))->
		getTechnique(0)->getPass(0)->getFragmentProgramParameters()->
		setNamedConstant( "uLightPosition", mProjectorSceneNode->getPosition());
	static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(mProjectorName+DEPTH_MATERIAL_SUFFIX))->
		getTechnique(0)->getPass(0)->getFragmentProgramParameters()->
		setNamedConstant( "uLightPosition", mProjectorSceneNode->getPosition());

	// We've to update the texture projection matrix
	updateTextureProjectionMatrix();
}

void LightShaftsProjector::updateTextureProjectionMatrix()
{
	const Ogre::Matrix4 PROJECTIONCLIPSPACE2DTOIMAGESPACE_PERSPECTIVE(
		0.5,    0,    0,  0.5,
		0,   -0.5,    0,  0.5,
		0,      0,    1,    0,
		0,      0,    0,    1);

	Ogre::Matrix4 TexViewProj = 
		PROJECTIONCLIPSPACE2DTOIMAGESPACE_PERSPECTIVE * 
		mProjectorCamera->getProjectionMatrixWithRSDepth() * 
		mProjectorCamera->getViewMatrix(); 

	static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(mProjectorName+MATERIAL_SUFFIX))->
		getTechnique(0)->getPass(0)->getVertexProgramParameters()->
		setNamedConstant( "uTexViewProj", TexViewProj );
}

void LightShaftsProjector::setProjectorName(const Ogre::String& name)
{
	mProjectorName=name;
}

void LightShaftsProjector::initProjector(const TProjectorSettings& projectorSettings)
{
	//Fist, clone base materials in case we're using shafts with different settings
	static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(mBaseMaterialName))->clone(mProjectorName+MATERIAL_SUFFIX);
	static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(mBaseMaterialName+DEPTH_MATERIAL_SUFFIX))->clone(mProjectorName+DEPTH_MATERIAL_SUFFIX);

	//Initialize camera	
	if (!mSceneManager->hasCamera(mProjectorName+CAMERA_SUFFIX))
	{
		mProjectorCamera = mSceneManager->createCamera(mProjectorName+CAMERA_SUFFIX);
	}
	else
	{
		mProjectorCamera = mSceneManager->getCamera(mProjectorName+CAMERA_SUFFIX);
	}

	mProjectorCamera->setProjectionType(Ogre::PT_PERSPECTIVE);
	mProjectorCamera->setNearClipDistance(projectorSettings.nearClipDistance);
	mProjectorCamera->setFarClipDistance(projectorSettings.farClipDistance);
	mProjectorCamera->setAspectRatio(projectorSettings.aspectRatio);
	mProjectorCamera->setFOVy(projectorSettings.fovy);

	if (projectorSettings.showDebug) //show frustum
	{
		mProjectorCamera->setDebugDisplayEnabled(true);
		mProjectorCamera->setVisible(true);
	}

	//Initialize scene node properties
	if (!mProjectorSceneNode)
	{
		mProjectorSceneNode = mSceneManager->getRootSceneNode()->createChildSceneNode(
			"light_shafts#" + Application::getInstance()->getStringUniqueId());
	}

	mProjectorSceneNode->setOrientation(projectorSettings.orientation);	
	mProjectorSceneNode->attachObject(mProjectorCamera);

	//Initialize billboard set
	if (!mSceneManager->hasBillboardSet(mProjectorName+BILLBOARDSET_SUFFIX))
	{
		mBillboardSet = mSceneManager->createBillboardSet(mProjectorName+BILLBOARDSET_SUFFIX,1);
	}
	else
	{
		mBillboardSet= mSceneManager->getBillboardSet(mProjectorName+BILLBOARDSET_SUFFIX);
	}

	mBillboardSet->setMaterialName(mProjectorName+MATERIAL_SUFFIX);
	mBillboardSet->setBillboardRotationType(Ogre::BBR_VERTEX);
	mBillboardSet->setCastShadows(false);
	mProjectorSceneNode->attachObject(mBillboardSet);

	//Initialize spotlight, in case the projector must be used as a light source as well
	if (projectorSettings.useSpotLight)
	{
		initSpotlight(projectorSettings.spotlightSettings);
	}

	//Inject material variables to the shaders
	static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(mProjectorName+MATERIAL_SUFFIX))->
		getTechnique(0)->getPass(0)->getTextureUnitState(1)->
		setTextureName(projectorSettings.cookieName);
	static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(mProjectorName+MATERIAL_SUFFIX))->
		getTechnique(0)->getPass(0)->getFragmentProgramParameters()->
		setNamedConstant( "uLightFarClipDistance", mProjectorCamera->getNearClipDistance()+mProjectorCamera->getFarClipDistance());
	static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(mProjectorName+DEPTH_MATERIAL_SUFFIX))->
		getTechnique(0)->getPass(0)->getFragmentProgramParameters()->
		setNamedConstant( "uLightFarClipDistance", mProjectorCamera->getNearClipDistance()+mProjectorCamera->getFarClipDistance());

	createLightShafts(projectorSettings.numberOfPlanes);
	createLightCameraRTT();
}

void LightShaftsProjector::initSpotlight(const TSpotlightSettings& spotlightSettings)
{
	mLight = mSceneManager->createLight(mProjectorName+LIGHT_SUFFIX);
	//mLight1->setCastShadows(true);
	mProjectorSceneNode->attachObject(mLight);
	mLight->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Z);
	mLight->setType(Ogre::Light::LT_SPOTLIGHT);
	mLight->setDiffuseColour(spotlightSettings.diffuse);
	mLight->setSpecularColour(spotlightSettings.specular);
	mLight->setSpotlightRange(spotlightSettings.innerAngle,spotlightSettings.outerAngle,spotlightSettings.falloff);	
	if (spotlightSettings.attenuate)
	{
		mLight->setAttenuation(spotlightSettings.attenuationRange,spotlightSettings.attenuationConstant,
			spotlightSettings.attenuationLinear,spotlightSettings.attenuationQuadratic);
	}
}

void LightShaftsProjector::createLightShafts(const int& numberOfPlanes)
{
	// Calculate the distance between planes
	float DistanceBetweenPlanes = (mProjectorCamera->getFarClipDistance() - mProjectorCamera->getNearClipDistance())/numberOfPlanes;

	// Get frustum corners to calculate near/far planes dimensions
	const Ogre::Vector3 *FrustumCorners = mProjectorCamera->getWorldSpaceCorners();

	// Calcule near and far planes dimensions
	float NearWidth  = (FrustumCorners[0] - FrustumCorners[1]).length(),
		NearHeigth = (FrustumCorners[1] - FrustumCorners[2]).length(),
		FarWidth   = (FrustumCorners[4] - FrustumCorners[5]).length(),
		FarHeigth  = (FrustumCorners[5] - FrustumCorners[6]).length();

	// Now width/height step
	float WidthStep  = (FarWidth-NearWidth)/numberOfPlanes,
		HeigthStep = (FarHeigth-NearHeigth)/numberOfPlanes;

	// Add billboards
	Ogre::Billboard *CurrentBB = 0;
	for(int k = 0; k < numberOfPlanes; k++)
	{
		CurrentBB = mBillboardSet->createBillboard(Ogre::Vector3(0, 0,-mProjectorCamera->getNearClipDistance() -k*DistanceBetweenPlanes), Ogre::ColourValue::White);
		CurrentBB->setDimensions(NearWidth + k*WidthStep, NearHeigth + k*HeigthStep);
	}	
}
void LightShaftsProjector::createLightCameraRTT()
{
	Ogre::String rttName = mProjectorName+RTT_SUFFIX;
	// Create a texture for use as rtt
	Ogre::TexturePtr LightCameraRTT = Ogre::TextureManager::getSingleton()
		.createManual(rttName ,
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::TEX_TYPE_2D,
		// 256*256 must be sufficient
		256, 
		256, 
		0,
		Ogre::PF_R8G8B8,
		Ogre::TU_RENDERTARGET);

	Ogre::RenderTarget* RT_Texture = LightCameraRTT->getBuffer()->getRenderTarget();

	Ogre::Viewport *RT_Texture_Viewport = RT_Texture->addViewport(mProjectorCamera);
	RT_Texture_Viewport->setClearEveryFrame(true);
	RT_Texture_Viewport->setBackgroundColour(Ogre::ColourValue::White);
	RT_Texture_Viewport->setOverlaysEnabled(false);
	RT_Texture_Viewport->setSkiesEnabled(false);

	// Add our depth listener
	RT_Texture->addListener(new LightDepthMapRttListener(mSceneManager,mBillboardSet,mProjectorName+DEPTH_MATERIAL_SUFFIX));

	// Fill the texture in our material
	static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName(mProjectorName+MATERIAL_SUFFIX))->
		getTechnique(0)->getPass(0)->getTextureUnitState(0)->
		setTextureName(rttName);
}

void LightShaftsProjector::toggle()
{
	mSwitchedOn=!mSwitchedOn;
	if (!mSwitchedOn) //detach projector
	{
		mProjectorSceneNode->detachObject(mBillboardSet);
		mProjectorSceneNode->detachObject(mProjectorCamera);
		if(mLight) mProjectorSceneNode->detachObject(mLight);
	}
	else //reattach projector
	{
		mProjectorSceneNode->attachObject(mBillboardSet);
		mProjectorSceneNode->attachObject(mProjectorCamera);
		if (mLight) mProjectorSceneNode->attachObject(mLight);
	}

}
void LightShaftsProjector::flipRotateEnabled()
{
	mRotateEnabled=!mRotateEnabled;
}

void LightShaftsProjector::show()
{
	if (mProjectorSceneNode)
	{
		if (!mBillboardSet->isAttached())
		mProjectorSceneNode->attachObject(mBillboardSet);
		if (!mProjectorCamera->isAttached())
		mProjectorSceneNode->attachObject(mProjectorCamera);
		if (mLight && !mLight->isAttached()) mProjectorSceneNode->attachObject(mLight);
	}
	
}

void LightShaftsProjector::hide()
{
	if (mProjectorSceneNode)
	{
		if (mBillboardSet->isAttached())
			mProjectorSceneNode->detachObject(mBillboardSet);
		if (mProjectorCamera->isAttached())
			mProjectorSceneNode->detachObject(mProjectorCamera);
		if (mLight && mLight->isAttached())
			mProjectorSceneNode->detachObject(mLight);
	}
}

//--- RENDERTARGET listener's methods
LightDepthMapRttListener::LightDepthMapRttListener(Ogre::SceneManager *sm,Ogre::BillboardSet* billboardSet, Ogre::String depthMaterialName)
:mSceneMgr(sm)
,mDepthMaterialName(depthMaterialName),
mBillboardSet(billboardSet)
{

}

void LightDepthMapRttListener::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
	mMaterials.empty();
	//Hide light shafts projectors' billboard sets
	Ogre::SceneManager::MovableObjectIterator BBSIterator = mSceneMgr->getMovableObjectIterator("BillboardSet");
	while (BBSIterator.hasMoreElements())
	{
		Ogre::BillboardSet* bbSet = static_cast<Ogre::BillboardSet*>(BBSIterator.peekNextValue());
		if (Ogre::StringUtil::endsWith(bbSet->getName(),BILLBOARDSET_SUFFIX))
		{
			bbSet->setVisible(false);
		}
		BBSIterator.moveNext();
	}

	Ogre::SceneManager::MovableObjectIterator EntityIterator = mSceneMgr->getMovableObjectIterator("Entity");
	Ogre::Entity * CurrentEntity = NULL;
	unsigned int k = 0;
	while( EntityIterator.hasMoreElements() )
	{
		CurrentEntity = static_cast<Ogre::Entity *>(EntityIterator.peekNextValue());
		for( k = 0; k < CurrentEntity->getNumSubEntities(); k++ )
		{
			mMaterials.push(CurrentEntity->getSubEntity(k)->getMaterialName());
			CurrentEntity->getSubEntity(k)->setMaterialName(mDepthMaterialName);
		}

		EntityIterator.moveNext();
	}
}

void LightDepthMapRttListener::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
	//Unhide light shafts projectors' billboard sets
	Ogre::SceneManager::MovableObjectIterator BBSIterator = mSceneMgr->getMovableObjectIterator("BillboardSet");
	while (BBSIterator.hasMoreElements())
	{
		Ogre::BillboardSet* bbSet = static_cast<Ogre::BillboardSet*>(BBSIterator.peekNextValue());
		if (Ogre::StringUtil::endsWith(bbSet->getName(),BILLBOARDSET_SUFFIX))
		{
			bbSet->setVisible(true);
		}
		BBSIterator.moveNext();
	}

	Ogre::SceneManager::MovableObjectIterator EntityIterator = mSceneMgr->getMovableObjectIterator("Entity");
	Ogre::Entity * CurrentEntity = NULL;
	unsigned int k = 0;

	while( EntityIterator.hasMoreElements() )
	{
		CurrentEntity = static_cast<Ogre::Entity *>(EntityIterator.peekNextValue());
		for( k = 0; k < CurrentEntity->getNumSubEntities(); k++ )
		{
			CurrentEntity->getSubEntity(k)->setMaterialName(mMaterials.front());
			mMaterials.pop();
		}

		EntityIterator.moveNext();
	}
}