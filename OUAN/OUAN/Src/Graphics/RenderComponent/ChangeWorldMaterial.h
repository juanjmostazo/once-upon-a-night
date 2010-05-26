#ifndef ChangeWorldMaterialH_H
#define ChangeWorldMaterialH_H

#include "../../OUAN.h"
namespace OUAN
{
	//ChangeWorldMaterial names
	const std::string MATERIAL_BLENDING_NAME="blending";
	const std::string MATERIAL_EROSION_NAME="erosion";
	const std::string MATERIAL_EROSION_TRANSPARENT_NAME="erosion_transparent";

	class TChangeWorldMaterialParameters
	{
	public:
		TChangeWorldMaterialParameters();
		~TChangeWorldMaterialParameters();

		ChangeWorldType type;
		std::string blending_texture;
		Vector3 scroll_animation;
		Vector3 scroll_blending;
		double tiling;
		double blending_amount;
		bool randomize;

	};

	class ChangeWorldMaterial
	{
	public:
		ChangeWorldMaterial();
		~ChangeWorldMaterial();

		void setChangeWorldFactor(double factor);

		bool init(std::string id,TChangeWorldMaterialParameters tChangeWorldMaterialParameters, Ogre::MaterialPtr pMaterial1, Ogre::MaterialPtr pMaterial2);
		bool init(std::string id,TChangeWorldMaterialParameters tChangeWorldMaterialParameters, Ogre::MaterialPtr pMaterial1);

		std::string getMaterialName();
		void randomize();

		void update(double elapsedSeconds);

		void setPointOfInterest(Vector3 pointOfInterest);

	protected:

		std::string mName;
		std::string mId;
		ChangeWorldType mType; 

		Vector3 mPointOfInterest;

		double mDisplacement;
		double mFactor;
		bool mRandomize;

		Vector3 mScrollAnimationSpeed;
		Vector3 mScrollBlendingSpeed;

		Vector3 mScrollAnimationCurrent;
		Vector3 mScrollBlendingCurrent;

		Vector3 mChangeWorldBlendingTiling;
		Vector3 mTiling;

		void getMaterialParameters(TChangeWorldMaterialParameters tChangeWorldMaterialParameters,Ogre::MaterialPtr material);

		std::string getDiffuseTexture(Ogre::MaterialPtr material);
		void getTextureParameters(Ogre::MaterialPtr material);

		void setPassParameters(Ogre::Pass * pass,Ogre::MaterialPtr original_material);

		std::string createMaterial(TChangeWorldMaterialParameters tChangeWorldMaterialParameters,Ogre::MaterialPtr original_material, std::string diffuseTexture1, std::string diffuseTexture2);

		void createMaterialBlending(TChangeWorldMaterialParameters tChangeWorldMaterialParameters,Ogre::MaterialPtr original_material,Ogre::MaterialPtr change_world_material_clone, std::string diffuseTexture1, std::string diffuseTexture2);
		void createMaterialErosion(TChangeWorldMaterialParameters tChangeWorldMaterialParameters,Ogre::MaterialPtr original_material,Ogre::MaterialPtr change_world_material_clone, std::string diffuseTexture1, std::string diffuseTexture2);
		void createMaterialErosionTransparent(TChangeWorldMaterialParameters tChangeWorldMaterialParameters,Ogre::MaterialPtr original_material,Ogre::MaterialPtr change_world_material_clone,std::string diffuseTexture1);

		std::string getChangeWorldTypeName(ChangeWorldType type);

		Ogre::MaterialPtr findMaterial(std::string name);
	};

}

#endif