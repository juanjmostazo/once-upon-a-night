#ifndef ChangeWorldMaterialH_H
#define ChangeWorldMaterialH_H

#include "../../OUAN.h"
namespace OUAN
{
	//ChangeWorldMaterial names
	const std::string MATERIAL_BLENDING_NAME="blending";
	const std::string MATERIAL_EROSION_NAME="erosion";

	class ChangeWorldMaterial
	{
	public:
		ChangeWorldMaterial();
		~ChangeWorldMaterial();

		void setChangeWorldFactor(double factor);
		bool init(std::string id,ChangeWorldType type, Ogre::MaterialPtr pMaterial1, Ogre::MaterialPtr pMaterial2);

		std::string getMaterialName();

	protected:
		std::string mName;
		std::string mId;
		ChangeWorldType mType; 

		std::string getDiffuseTexture(Ogre::MaterialPtr material);
		bool getLighting(Ogre::MaterialPtr material);
		bool getDepthWrite(Ogre::MaterialPtr material);
		std::string createMaterial(ChangeWorldType type, std::string diffuseTexture1, std::string diffuseTexture2,bool lighting,bool depth_write);

		void createMaterialBlending(Ogre::MaterialPtr clone, std::string diffuseTexture1, std::string diffuseTexture2,bool lighting,bool depth_write);
		void createMaterialErosion(Ogre::MaterialPtr clone, std::string diffuseTexture1, std::string diffuseTexture2,bool lighting,bool depth_write);
	
		std::string getChangeWorldTypeName(ChangeWorldType type);

		Ogre::MaterialPtr findMaterial(std::string name);
	};

}

#endif