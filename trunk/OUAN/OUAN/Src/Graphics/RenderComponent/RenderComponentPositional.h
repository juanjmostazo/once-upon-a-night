#ifndef RenderComponentPositionalH_H
#define RenderComponentPositionalH_H

#include "RenderComponent.h"
#include "../RenderSubsystem.h"
namespace OUAN
{
	class RenderComponentPositional: public RenderComponent
	{
	private:
		CameraManagerPtr mCameraManager;
		Ogre::SceneNode * mSceneNode;

	public:
		RenderComponentPositional(const std::string& type="");
		~RenderComponentPositional();

		Ogre::SceneNode * getSceneNode() const;
		void setSceneNode(Ogre::SceneNode *);	

		void setPosition(Vector3 position);
		void setOrientation(Quaternion orientation);

		Vector3 getPosition() const;
		Quaternion getOrientation() const;

		//values in degrees
		double getYaw() const;
		double getPitch() const;
		double getRoll() const;

		CameraManagerPtr getCameraManager() const;
		void setCameraManager(CameraManagerPtr pCameraManager);

		/// Compute this component's distance to another positional component
		/// @param other the component from which the distance to this one will be calculated
		/// @return distance between this component and the passed one.
		double computeDistanceTo(RenderComponentPositionalPtr other);
	};

	class TRenderComponentPositionalParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentPositionalParameters();
		~TRenderComponentPositionalParameters();

		String parentSceneNodeName;
		Vector3 position;
		Quaternion orientation;
		Vector3 scale;
		String autotracktarget;
	};

}

#endif