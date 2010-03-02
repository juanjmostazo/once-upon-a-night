#include "CameraControllerFirstPerson.h"
#include "../../Input/FullInputManager.h"

using namespace OUAN;

CameraControllerFirstPerson::CameraControllerFirstPerson() : CameraController()
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
}

void CameraControllerFirstPerson::setCamera(Ogre::Camera* pCamera)
{

	//reset controller first person nodes
	this->cameraNode->resetToInitialState();
	this->cameraYawNode->resetToInitialState();
	this->cameraPitchNode->resetToInitialState();
	this->cameraRollNode->resetToInitialState();
	this->cameraRollNode->detachAllObjects();

	//set camera
	this->mCamera=pCamera;

	//set parameters of the new camera to the nodes
	this->cameraNode->setPosition(mCamera->getPosition());
	this->cameraYawNode->yaw(mCamera->getOrientation().getYaw());
	this->cameraPitchNode->pitch(mCamera->getOrientation().getPitch());
	this->cameraRollNode->roll(mCamera->getOrientation().getRoll());

	//set position and rotation of new camera to zero
	mCamera->setPosition(0,0,0);
	mCamera->setOrientation(Ogre::Quaternion::IDENTITY);

	//attach new camera to roll node
	this->cameraRollNode->attachObject(mCamera);
}

void CameraControllerFirstPerson::processRelativeMotion(double xRel, double yRel, double zRel)
{
	Ogre::Real pitchAngle;
	Ogre::Real pitchAngleSign;

	double mRotX=-xRel*0.3;
	double mRotY=-yRel*0.3;
	double mRotZ=zRel*0.3;

	// Yaws the camera according to the mouse relative movement.
	cameraYawNode->yaw(Ogre::Angle(mRotX));

	// Pitches the camera according to the mouse relative movement.
	cameraPitchNode->pitch(Ogre::Angle(mRotY));

	// Go forward or back using mouse wheel
	processSimpleTranslation(Ogre::Vector3::NEGATIVE_UNIT_Z * mRotZ);

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

void CameraControllerFirstPerson::processSimpleTranslation(Ogre::Vector3 translationVector)
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

TCameraControllerType CameraControllerFirstPerson::getControllerType()
{
	return OUAN::CAMERA_FIRST_PERSON;
}