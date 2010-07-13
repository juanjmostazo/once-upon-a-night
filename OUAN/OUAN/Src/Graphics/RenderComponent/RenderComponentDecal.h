#ifndef RenderComponentDecalH_H
#define RenderComponentDecalH_H

#include "RenderComponent.h"

namespace OUAN
{
	const std::string DECAL_PROJECTOR_NODE_SUFFIX="DecalProjNode";
	const std::string DECAL_FILTER_PROJECTOR_NODE_SUFFIX="DecalFilterProjNode";
	const std::string DECAL_PASS_SUFFIX="ReceiveDecalPass";

	class RenderComponentDecal: public RenderComponent
	{
	private:
		Ogre::SceneManager* mSceneManager;

		Ogre::SceneNode * mProjectorNode;
		Ogre::Frustum * mDecalFrustrum;

		Ogre::Vector3 mPosition;
		std::string mProjectorName;

		Ogre::Frustum* mFrustum;
		Ogre::Frustum* mFilterFrustum;

		std::string mTextureName;
		std::string mFilterTextureName;

		Ogre::ColourValue mTintColour;

		std::set<std::string> mTargets;		


		bool mVisible;

		//methods refactored for improved readability:
		bool existsEntity(GameObjectPtr obj);
		bool isValidSubentity(Ogre::SubEntity* subEnt);
		void loadGOTerrainTriangleMaterials(GameObjectPtr obj);
		void loadSubEnts(Ogre::Entity* ent);

	public:
		void stopMaterialsFromReceivingDecal();
		void makeMaterialsReceiveDecal();

		RenderComponentDecal(Ogre::SceneManager* sceneManager=NULL);
		~RenderComponentDecal();

		void createProjector(TRenderComponentDecalParameters decalParams, 
			Ogre::SceneManager* sceneManager, TGameObjectContainer* objs);
		void destroyProjector();
		void initProjector(const std::string&  projectorName, 
			const std::string& textureName,
			const Ogre::Vector3& projectorOffset,
			Ogre::SceneNode* projectorNode);
		void initFilterProjector(const std::string& filterTextureName);
		
		//void update(double elapsedSeconds);
		void show();
		void hide();
		void changeColour(int tintColour);
		bool isVisible() const;
		void setVisible(bool isVisible);

		void loadMaterials(TGameObjectContainer& gameObjects);
		void unloadMaterials();
	};

	class TRenderComponentDecalParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentDecalParameters();
		~TRenderComponentDecalParameters();

		Ogre::SceneNode* projectorNode;
		Ogre::Vector3 projectorOffset;
		std::string projectorName;

		std::string textureName;
		std::string filterTextureName;

		int tintColour;
	};

}

#endif