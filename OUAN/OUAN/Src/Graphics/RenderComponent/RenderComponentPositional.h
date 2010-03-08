#ifndef RenderComponentPositionalH_H
#define RenderComponentPositionalH_H

#include "RenderComponent.h"
#include "../RenderSubsystem.h"
namespace OUAN
{
	class RenderComponentPositional: public RenderComponent
	{
	private:
		RenderSubsystemPtr mRenderSubsystem;
		Ogre::SceneNode * mSceneNode;
	public:

		RenderComponentPositional(const std::string& type="");
		~RenderComponentPositional();

		Ogre::SceneNode * getSceneNode() const;
		void setSceneNode(Ogre::SceneNode *);	


		Vector3 getPosition() const;
		Quaternion getOrientation() const;
		//values in degrees
		double getYaw() const;
		double getPitch() const;
		double getRoll() const;



		RenderSubsystemPtr getRenderSubsystem() const;
		void setRenderSubsystem(RenderSubsystemPtr renderSubsystem);

		void setAsCameraTarget();
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