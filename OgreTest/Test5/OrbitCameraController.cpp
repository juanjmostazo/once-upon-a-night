#include "OrbitCameraController.h"

#include <cassert>

#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreSceneNode.h>

OrbitCameraController::OrbitCameraController( Ogre::Camera* camera )
: m_camera( camera )
, m_lookAtNode( NULL )
, m_yawNode( NULL )
, m_pitchNode( NULL )
{
	assert( camera != NULL );
	assert( camera->getParentNode() == NULL );

	Ogre::SceneManager* sceneManager = camera->getSceneManager();

	m_lookAtNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	m_yawNode = m_lookAtNode->createChildSceneNode();
	m_pitchNode = m_yawNode->createChildSceneNode();
	m_pitchNode->attachObject( camera );
}

OrbitCameraController::~OrbitCameraController()
{

}

void OrbitCameraController::setLookAtPosition( const float x, const float y, const float z )
{
	m_lookAtNode->setPosition( x, y, z );
}

void OrbitCameraController::resetOrientation()
{
	m_yawNode->resetOrientation();
	m_pitchNode->resetOrientation();
}

void OrbitCameraController::setOrientation( const float yawDegrees, const float pitchDegrees )
{
	resetOrientation();
	addOrientation( yawDegrees, pitchDegrees );
}

void OrbitCameraController::addOrientation( const float yawDegrees, const float pitchDegrees )
{
	m_yawNode->yaw( Ogre::Degree( yawDegrees ) );
	m_pitchNode->pitch( Ogre::Degree( pitchDegrees ) );
}

void OrbitCameraController::setDistance( const float distance )
{
	m_camera->setPosition( 0, 0, distance );
}

void OrbitCameraController::addDistance( const float distance )
{
	m_camera->setPosition( m_camera->getPosition() + Ogre::Vector3( 0, 0, distance ) );
}