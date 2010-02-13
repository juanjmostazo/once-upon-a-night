#include "CameraFirstPersonController.h"

CameraFirstPersonController::CameraFirstPersonController(void)
{
}

CameraFirstPersonController::~CameraFirstPersonController(void)
{
}

void CameraFirstPersonController::setCamera(Ogre::Camera* camera)
{
	Ogre::SceneManager * pSceneManager;
	pSceneManager=camera->getSceneManager();
	// Create the camera's top node (which will only handle position).
	this->cameraNode = pSceneManager->getRootSceneNode()->createChildSceneNode();
	this->cameraNode->setPosition(-100,30,50);

	// Create the camera's yaw node as a child of camera's top node.
	this->cameraYawNode = this->cameraNode->createChildSceneNode();

	// Create the camera's pitch node as a child of camera's yaw node.
	this->cameraPitchNode = this->cameraYawNode->createChildSceneNode();

	// Create the camera's roll node as a child of camera's pitch node
	// and attach the camera to it.
	this->cameraRollNode = this->cameraPitchNode->createChildSceneNode();
	this->cameraRollNode->attachObject(camera);

}

void CameraFirstPersonController::processMouseInput(const OIS::MouseEvent& e)
{
	Ogre::Real pitchAngle;
	Ogre::Real pitchAngleSign;

	float mRotX=-e.state.X.rel*0.4;
	float mRotY=-e.state.Y.rel*0.4;

	// Yaws the camera according to the mouse relative movement.
	cameraYawNode->yaw(Ogre::Angle(mRotX));

	// Pitches the camera according to the mouse relative movement.
	cameraPitchNode->pitch(Ogre::Angle(mRotY));

	// Angle of rotation around the X-axis.
	pitchAngle = (2 * Ogre::Degree(Ogre::Math::ACos(this->cameraPitchNode->getOrientation().w)).valueDegrees());

	// Just to determine the sign of the angle we pick up above, the
	// value itself does not interest us.
	pitchAngleSign = cameraPitchNode->getOrientation().x;

	// Limit the pitch between -90 degress and +90 degrees, Quake3-style.
	if (pitchAngle > 90.0f)
	{
		if (pitchAngleSign > 0)
			// Set orientation to 90 degrees on X-axis.
			cameraPitchNode->setOrientation(Ogre::Quaternion(Ogre::Math::Sqrt(0.5f),
																   Ogre::Math::Sqrt(0.5f), 0, 0));
		else if (pitchAngleSign < 0)
			// Sets orientation to -90 degrees on X-axis.
			cameraPitchNode->setOrientation(Ogre::Quaternion(Ogre::Math::Sqrt(0.5f),
																   -Ogre::Math::Sqrt(0.5f), 0, 0));
	}

}

void CameraFirstPersonController::processKeyboardInput(SimpleInputManager* pSimpleInputManager,const float elapsedSeconds,float moveScale,float rotateScale)
{
	OIS::Keyboard* m_keyboard;
	m_keyboard=pSimpleInputManager->m_keyboard;

	Ogre::Vector3 translateVector= Ogre::Vector3(0,0,0);

	moveScale=moveScale*elapsedSeconds;
	rotateScale=rotateScale*elapsedSeconds;


	// Move camera upwards along to world's Y-axis.
	if(m_keyboard->isKeyDown(OIS::KC_PGUP))
		//this->translateVector.y = this->moveScale;
		cameraNode->setPosition(this->cameraNode->getPosition() + Ogre::Vector3(0, 5, 0));

	// Move camera downwards along to world's Y-axis.
	if(m_keyboard->isKeyDown(OIS::KC_PGDOWN))
		//this->translateVector.y = -(this->moveScale);
		cameraNode->setPosition(this->cameraNode->getPosition() - Ogre::Vector3(0, 5, 0));

	// Move camera forward.
	if(m_keyboard->isKeyDown(OIS::KC_UP))
		translateVector.z = -(moveScale);

	// Move camera backward.
	if(m_keyboard->isKeyDown(OIS::KC_DOWN))
		translateVector.z = moveScale;

	// Move camera left.
	if(m_keyboard->isKeyDown(OIS::KC_LEFT))
		translateVector.x = -(moveScale);

	// Move camera right.
	if(m_keyboard->isKeyDown(OIS::KC_RIGHT))
		translateVector.x = moveScale;

	// Rotate camera left.
	if(m_keyboard->isKeyDown(OIS::KC_Q))
		cameraYawNode->yaw(Ogre::Angle(rotateScale));

	// Rotate camera right.
	if(m_keyboard->isKeyDown(OIS::KC_D))
		cameraYawNode->yaw(Ogre::Angle(-(rotateScale)));

	// Strip all yaw rotation on the camera.
	if(m_keyboard->isKeyDown(OIS::KC_A))
		cameraYawNode->setOrientation(Ogre::Quaternion::IDENTITY);

	// Rotate camera upwards.
	if(m_keyboard->isKeyDown(OIS::KC_Z))
		cameraPitchNode->pitch(Ogre::Angle(rotateScale));

	// Rotate camera downwards.
	if(m_keyboard->isKeyDown(OIS::KC_S))
		cameraPitchNode->pitch(Ogre::Angle(-(rotateScale)));

	// Strip all pitch rotation on the camera.
	if(m_keyboard->isKeyDown(OIS::KC_E))
		cameraPitchNode->setOrientation(Ogre::Quaternion::IDENTITY);

	// Tilt camera on the left.
	if(m_keyboard->isKeyDown(OIS::KC_L))
		cameraRollNode->roll(Ogre::Angle(-(rotateScale)));

	// Tilt camera on the right.
	if(m_keyboard->isKeyDown(OIS::KC_M))
		cameraRollNode->roll(Ogre::Angle(rotateScale));

	// Strip all tilt applied to the camera.
	if(m_keyboard->isKeyDown(OIS::KC_P))
		cameraRollNode->setOrientation(Ogre::Quaternion::IDENTITY);

	// Strip all rotation to the camera.
	if(m_keyboard->isKeyDown(OIS::KC_O))
	{
		cameraYawNode->setOrientation(Ogre::Quaternion::IDENTITY);
		cameraPitchNode->setOrientation(Ogre::Quaternion::IDENTITY);
		cameraRollNode->setOrientation(Ogre::Quaternion::IDENTITY);
	}

	// Translates the camera according to the translate vector which is
	// controlled by the keyboard arrows.
	//
	// NOTE: We multiply the mTranslateVector by the cameraPitchNode's
	// orientation quaternion and the cameraYawNode's orientation
	// quaternion to translate the camera accoding to the camera's
	// orientation around the Y-axis and the X-axis.
	cameraNode->translate(cameraYawNode->getOrientation() *
								cameraPitchNode->getOrientation() *
								translateVector,
								Ogre::SceneNode::TS_LOCAL);
}
