#include "CameraControllerFirstPerson.h"
#include "../../Input/FullInputManager.h"

using namespace OUAN;

CameraControllerFirstPerson::CameraControllerFirstPerson()
{
}

CameraControllerFirstPerson::~CameraControllerFirstPerson()
{
}

void CameraControllerFirstPerson::init(Ogre::SceneManager * pSceneManager)
{
	// Create the camera's top node (which will only handle position).
	this->cameraNode = pSceneManager->getRootSceneNode()->createChildSceneNode();
	
	// Create the camera's yaw node as a child of camera's top node.
	this->cameraYawNode = this->cameraNode->createChildSceneNode();

	// Create the camera's pitch node as a child of camera's yaw node.
	this->cameraPitchNode = this->cameraYawNode->createChildSceneNode();

	// Create the camera's roll node as a child of camera's pitch node
	// and attach the camera to it.
	this->cameraRollNode = this->cameraPitchNode->createChildSceneNode();

	//Create the camera's offset node as a child of camera's roll node
	this->cameraOffsetNode = this->cameraRollNode->createChildSceneNode();

	mCamera=pSceneManager->createCamera(OUAN::MAIN_CAMERA_NAME);


}

void CameraControllerFirstPerson::setCamera(Ogre::Camera* pCamera)
{
	//TODO FIX THIS CRAP
	this->mCamera=pCamera;
	this->cameraNode->setPosition(mCamera->getPosition());
	this->cameraYawNode->yaw(mCamera->getOrientation().getYaw());
	this->cameraPitchNode->pitch(mCamera->getOrientation().getPitch());
	this->cameraRollNode->roll(mCamera->getOrientation().getRoll());
	this->cameraOffsetNode->setPosition(-mCamera->getPosition());
	this->cameraOffsetNode->setOrientation(-mCamera->getOrientation());
	this->cameraOffsetNode->attachObject(mCamera);
}

void CameraControllerFirstPerson::processMouseInput(const OIS::MouseEvent& e)
{
	processRelativeMotion(e.state.X.rel,e.state.Y.rel);
}
void CameraControllerFirstPerson::processRelativeMotion(double xRel, double yRel)
{
	Ogre::Real pitchAngle;
	Ogre::Real pitchAngleSign;

	double mRotX=-xRel*0.3;
	double mRotY=-yRel*0.3;

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

void CameraControllerFirstPerson::processInput(OIS::Keyboard* keyboard,double elapsedTime)
{
	// THIS PARAMS MUST BE SET WITHIN AN EXNTERN FILE
	double moveScale=60;
	double rotateScale=5;

	Ogre::Vector3 translateVector= Ogre::Vector3(0,0,0);

	moveScale=moveScale*elapsedTime;
	rotateScale=rotateScale*elapsedTime;


	// Move camera upwards along to world's Y-axis.
	if(keyboard->isKeyDown(OIS::KC_PGUP))
		//this->translateVector.y = this->moveScale;
		cameraNode->setPosition(this->cameraNode->getPosition() + Ogre::Vector3(0, moveScale, 0));

	// Move camera downwards along to world's Y-axis.
	if(keyboard->isKeyDown(OIS::KC_PGDOWN))
		//this->translateVector.y = -(this->moveScale);
		cameraNode->setPosition(this->cameraNode->getPosition() - Ogre::Vector3(0, moveScale, 0));

	// Move camera forward.
	if(keyboard->isKeyDown(OIS::KC_UP))
		translateVector.z = -(moveScale);

	// Move camera backward.
	if(keyboard->isKeyDown(OIS::KC_DOWN))
		translateVector.z = moveScale;

	// Move camera left.
	if(keyboard->isKeyDown(OIS::KC_LEFT))
		translateVector.x = -(moveScale);

	// Move camera right.
	if(keyboard->isKeyDown(OIS::KC_RIGHT))
		translateVector.x = moveScale;

	// Rotate camera left.
	if(keyboard->isKeyDown(OIS::KC_Q))
		cameraYawNode->yaw(Ogre::Angle(rotateScale));

	// Rotate camera right.
	if(keyboard->isKeyDown(OIS::KC_D))
		cameraYawNode->yaw(Ogre::Angle(-(rotateScale)));

	// Strip all yaw rotation on the camera.
	if(keyboard->isKeyDown(OIS::KC_A))
		cameraYawNode->setOrientation(Ogre::Quaternion::IDENTITY);

	// Rotate camera upwards.
	if(keyboard->isKeyDown(OIS::KC_Z))
		cameraPitchNode->pitch(Ogre::Angle(rotateScale));

	// Rotate camera downwards.
	if(keyboard->isKeyDown(OIS::KC_S))
		cameraPitchNode->pitch(Ogre::Angle(-(rotateScale)));

	// Strip all pitch rotation on the camera.
	if(keyboard->isKeyDown(OIS::KC_E))
		cameraPitchNode->setOrientation(Ogre::Quaternion::IDENTITY);

	// Tilt camera on the left.
	if(keyboard->isKeyDown(OIS::KC_L))
		cameraRollNode->roll(Ogre::Angle(-(rotateScale)));

	// Tilt camera on the right.
	if(keyboard->isKeyDown(OIS::KC_M))
		cameraRollNode->roll(Ogre::Angle(rotateScale));

	// Strip all tilt applied to the camera.
	if(keyboard->isKeyDown(OIS::KC_P))
		cameraRollNode->setOrientation(Ogre::Quaternion::IDENTITY);

	// Strip all rotation to the camera.
	if(keyboard->isKeyDown(OIS::KC_O))
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
	//Ogre::LogManager::getSingleton().logMessage("Processing camera keyboard");
}
void CameraControllerFirstPerson::processSimpleTranslation(const Ogre::Vector3& translationVector)
{
	double moveScale=0.1f;
	Ogre::Vector3 translation = moveScale*translationVector;
	// Translates the camera according to the translate vector which is
	// controlled by the keyboard arrows.
	//
	// NOTE: We multiply the mTranslateVector by the cameraPitchNode's
	// orientation quaternion and the cameraYawNode's orientation
	// quaternion to translate the camera accoding to the camera's
	// orientation around the Y-axis and the X-axis.
	cameraNode->translate(cameraYawNode->getOrientation() *
		cameraPitchNode->getOrientation() *
		translation,
		Ogre::SceneNode::TS_LOCAL);
}
