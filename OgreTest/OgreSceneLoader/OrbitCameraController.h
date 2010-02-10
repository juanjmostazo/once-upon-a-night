#ifndef __ORBIT_CAMERA_CONTROLLER__H__
#define __ORBIT_CAMERA_CONTROLLER__H__

namespace Ogre
{
	class Camera;
	class SceneNode;
}

class OrbitCameraController
{
public:
	OrbitCameraController( Ogre::Camera* camera );
	virtual ~OrbitCameraController();

	void setLookAtPosition( const float x, const float y, const float z );

	void resetOrientation();
	void setOrientation( const float yawDegrees, const float pitchDegrees );
	void addOrientation( const float yawDegrees, const float pitchDegrees );
	
	void setDistance( const float distance );
	void addDistance( const float distance );

private:
	
	Ogre::Camera* m_camera;

	Ogre::SceneNode* m_lookAtNode;
	Ogre::SceneNode* m_yawNode;
	Ogre::SceneNode* m_pitchNode;
};

#endif