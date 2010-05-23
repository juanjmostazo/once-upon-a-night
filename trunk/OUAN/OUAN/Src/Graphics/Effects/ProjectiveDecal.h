#ifndef PROJECTIVEDECALH_H
#define PROJECTIVEDECALH_H
#include "../../OUAN.h"
namespace OUAN
{
	const std::string DECAL_PROJECTOR_NODE_SUFFIX="DecalProjNode";
	const std::string DECAL_FILTER_PROJECTOR_NODE_SUFFIX="DecalFilterProjNode";
	const std::string DECAL_PASS_SUFFIX="ReceiveDecalPass";

	typedef struct 
	{
		Ogre::SceneNode* projectorNode;
		Ogre::Vector3 projectorOffset;
		std::string projectorName;

		std::string textureName;
		std::string filterTextureName;

		int tintColour;
	} TDecalParams;

	class ProjectiveDecal
	{
	private:
		Ogre::SceneManager* mSceneManager;
	
		Ogre::SceneNode* mProjectorNode;
		Ogre::Vector3 mPosition;
		std::string mProjectorName;

		Ogre::Frustum* mFrustum;
		Ogre::Frustum* mFilterFrustum;
		
		std::string mTextureName;
		std::string mFilterTextureName;

		Ogre::ColourValue mTintColour;

		std::set<std::string> mTargets;		
		void stopMaterialsFromReceivingDecal();
		void makeMaterialsReceiveDecal();

		bool mVisible;

	public:
		ProjectiveDecal();
		virtual ~ProjectiveDecal();

		void createProjector(TDecalParams decalParams, Ogre::SceneManager* sceneManager, TGameObjectContainer* objs);
		void destroyProjector();
		//void update(double elapsedSeconds);
		void show();
		void hide();
		void changeColour(int tintColour);
		bool isVisible() const;
		void setVisible(bool isVisible);
	};
}
#endif