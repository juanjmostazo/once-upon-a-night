#ifndef ChangeWorldMaterialH_H
#define ChangeWorldMaterialH_H

#include "../../OUAN.h"
namespace OUAN
{
	//ChangeWorldMaterial names
	const std::string MATERIAL_BLENDING_NAME="blending";
	const std::string MATERIAL_EROSION_NAME="erosion";

	class TPassParameters
	{
	public:
		TPassParameters();
		~TPassParameters();
		bool depth_write;
		bool lighting;
	};

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

	};

	class ChangeWorldMaterial
	{
	public:
		ChangeWorldMaterial();
		~ChangeWorldMaterial();

		void setChangeWorldFactor(double factor);
		bool init(std::string id,TChangeWorldMaterialParameters tChangeWorldMaterialParameters, Ogre::MaterialPtr pMaterial1, Ogre::MaterialPtr pMaterial2);

		std::string getMaterialName();
		void randomize();

		void update(double elapsedSeconds);

	protected:

		std::string mName;
		std::string mId;
		ChangeWorldType mType; 

		double mDisplacement;
		double mFactor;

		Vector3 mScrollAnimationSpeed;
		Vector3 mScrollBlendingSpeed;

		Vector3 mScrollAnimationCurrent;
		Vector3 mScrollBlendingCurrent;

		std::string getDiffuseTexture(Ogre::MaterialPtr material);
		Vector3 getCurrentScrollAnimation(Ogre::MaterialPtr material);
		TPassParameters getPassParameters(Ogre::MaterialPtr material);
		void setTPassParameters(Ogre::Pass * pass,TPassParameters passParameters);

		std::string createMaterial(TChangeWorldMaterialParameters tChangeWorldMaterialParameters, std::string diffuseTexture1, std::string diffuseTexture2,TPassParameters TPassParameters);

		void createMaterialBlending(TChangeWorldMaterialParameters tChangeWorldMaterialParameters,Ogre::MaterialPtr clone, std::string diffuseTexture1, std::string diffuseTexture2,TPassParameters TPassParameters);
		void createMaterialErosion(TChangeWorldMaterialParameters tChangeWorldMaterialParameters,Ogre::MaterialPtr clone, std::string diffuseTexture1, std::string diffuseTexture2,TPassParameters TPassParameters);
	
		std::string getChangeWorldTypeName(ChangeWorldType type);

		Ogre::MaterialPtr findMaterial(std::string name);
	};

}

#endif