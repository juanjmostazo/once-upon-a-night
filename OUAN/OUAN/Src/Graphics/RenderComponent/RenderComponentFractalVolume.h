#ifndef RenderComponentFractalVolumeH_H
#define RenderComponentFractalVolumeH_H

#include "RenderComponent.h"

#include "../Volume/VolumeRenderable.h"

namespace OUAN
{
	class RenderComponentFractalVolume : public RenderComponent
	{
	private:
		VolumeRenderable* mFractalVolume;
		Ogre::SceneNode* mSceneNode;
		Ogre::Vector3 mRotationDegrees;
		
	public:
		RenderComponentFractalVolume(const std::string& type="");
		~RenderComponentFractalVolume();

		VolumeRenderable* getFractalVolume() const;
		void setFractalVolume(VolumeRenderable* fractalVolume);

		Ogre::SceneNode* getSceneNode() const;
		void setSceneNode(Ogre::SceneNode* sceneNode);

		Ogre::Vector3 getRotationDegrees() const;
		void setRotationDegrees(Ogre::Vector3 rotationDegrees);

		void setVisible(bool visible);
		void update(double elapsedSeconds);
	};

	class TRenderComponentFractalVolumeParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentFractalVolumeParameters();
		~TRenderComponentFractalVolumeParameters();

		std::string texture3D;

		double juliaGlobalReal;
		double juliaGlobalImag;
		double juliaGlobalTheta;

		double vScale;
		double vCut;
		double vSlices;
		double vSize;

		double offsetX;
		double offsetY;
		double offsetZ;

		double rotationDegreesX;
		double rotationDegreesY;
		double rotationDegreesZ;

		double colorR;
		double colorG;
		double colorB;
	};
}

#endif