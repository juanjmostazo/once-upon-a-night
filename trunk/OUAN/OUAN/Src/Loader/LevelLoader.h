#ifndef LevelLoaderH_H
#define LevelLoaderH_H

//OUAN
#include "../OUAN.h"
#include "XMLGameObjectParser.h"
namespace OUAN
{
	class LevelLoader
	{
	public:
		LevelLoader();
		virtual ~LevelLoader();

		void init(OUAN::ApplicationPtr app);

		void loadLevel(String SceneName);


	protected:
		GameWorldManagerPtr mGameWorldManager;

		XMLGameObjectParser mXMLGameObjectParser;

		void processGameObjects();
		void processGameObject(XMLGameObject *gameObject);

		//Game Object Processors
		void processGameObjectScene(XMLGameObject* gameObject);
		void processGameObjectViewport(XMLGameObject* gameObject);
		void processGameObjectOny(XMLGameObject *gameObject);
		void processGameObjectTripollo(XMLGameObject* gameObject);
		void processGameObjectTerrain(XMLGameObject* gameObject);
		void processGameObjectLight(XMLGameObject* gameObject);
		void processGameObjectParticleSystem(XMLGameObject* gameObject);
		void processGameObjectBillboardSet(XMLGameObject* gameObject);
		void processGameObjectPortal(XMLGameObject* gameObject);
		void processGameObjectItemMaxHP(XMLGameObject* gameObject);
		void processGameObjectItem1UP(XMLGameObject* gameObject);
		void processGameObjectEye(XMLGameObject* gameObject);
		void processGameObjectCamera(XMLGameObject* gameObject);
		void processGameObjectVolumeBox(XMLGameObject* gameObject);
		void processGameObjectVolumeCapsule(XMLGameObject* gameObject);
		void processGameObjectProvisionalEntity(XMLGameObject* gameObject);

		//RenderComponent Processors
		TRenderComponentSceneParameters processRenderComponentScene(TiXmlElement *XMLNode);
		TRenderComponentSkyBoxParameters processRenderComponentSkyBox(TiXmlElement *XMLNode);
		TRenderComponentSkyDomeParameters processRenderComponentSkyDome(TiXmlElement *XMLNode);
		TRenderComponentPositionalParameters processRenderComponentPositional(TiXmlElement *XMLNode);
		TRenderComponentPositionalParameters processRenderComponentPositionalNoScale(TiXmlElement *XMLNode);
		TRenderComponentEntityParameters processRenderComponentEntity(TiXmlElement *XMLNode);
		TRenderComponentLightParameters processRenderComponentLight(TiXmlElement *XMLNode);
		TRenderComponentParticleSystemParameters processRenderComponentParticleSystem(TiXmlElement *XMLNode);
		TRenderComponentBillboardSetParameters processRenderComponentBillboardSet(TiXmlElement *XMLNode);
		TRenderComponentCameraParameters processRenderComponentCamera(TiXmlElement *XMLNode);
		TRenderComponentViewportParameters processRenderComponentViewport(TiXmlElement *XMLNode);
		void processRenderComponentSubEntities(std::vector<TRenderComponentSubEntityParameters>  &tRenderComponentSubEntityParameters ,TiXmlElement *XMLNode);
		void processRenderComponentBillboards(std::vector<TRenderComponentBillboardParameters>  &tRenderComponentBillboardParameters ,TiXmlElement *XMLNode);

		//PhysicComponent Processors
		TPhysicsComponentCharacterParameters processPhysicsComponentCharacter(TiXmlElement *XMLNode);
		TPhysicsComponentComplexConvexParameters processPhysicsComponentComplexConvex(TiXmlElement *XMLNode,std::string meshfile);
		TPhysicsComponentComplexTriangleParameters processPhysicsComponentComplexTriangle(TiXmlElement *XMLNode,std::string meshfile);
		TPhysicsComponentSimpleBoxParameters processPhysicsComponentSimpleBox(TiXmlElement *XMLNode);
		TPhysicsComponentSimpleCapsuleParameters processPhysicsComponentSimpleCapsule(TiXmlElement *XMLNode);
		TPhysicsComponentVolumeBoxParameters processPhysicsComponentVolumeBox(TiXmlElement *XMLCustomPropertiesNode,TiXmlElement *XMLRenderInfoNode);
		TPhysicsComponentVolumeCapsuleParameters processPhysicsComponentVolumeCapsule(TiXmlElement *XMLNode);

		//LogicComponent Processors
		TLogicComponentWorldExistanceParameters processLogicComponentWorldExistance(TiXmlElement *XMLNodeDreams,TiXmlElement *XMLNodeNightmares);


		OUAN::String getAttrib(TiXmlElement *XMLNode, const OUAN::String &parameter, const OUAN::String &defaultValue = "");

		OUAN::String getPropertyString(TiXmlElement *XMLNode, const OUAN::String &attrib_name, bool logErrors=true);
		OUAN::Vector2 getPropertyVector2(TiXmlElement *XMLNode, const OUAN::String &attrib_name, bool logErrors=true);
		OUAN::Vector3 getPropertyVector3(TiXmlElement *XMLNode, const OUAN::String &attrib_name, bool logErrors=true);
		OUAN::Vector4 getPropertyVector4(TiXmlElement *XMLNode, const OUAN::String &attrib_name, bool logErrors=true);
		OUAN::Quaternion getPropertyQuaternion(TiXmlElement *XMLNode, const OUAN::String &attrib_name, bool logErrors=true);
		OUAN::ColourValue getPropertyColourValue(TiXmlElement *XMLNode, const OUAN::String &attrib_name, bool logErrors=true);
		bool getPropertyBool(TiXmlElement *XMLNode, const OUAN::String &attrib_name, bool logErrors=true);
		int getPropertyInt(TiXmlElement *XMLNode, const OUAN::String &attrib_name, bool logErrors=true);
		OUAN::Real getPropertyReal(TiXmlElement *XMLNode, const OUAN::String &attrib_name, bool logErrors=true);

		enum LightTypes
		{
			OGITOR_LT_POINT,
			OGITOR_LT_DIRECTIONAL,
			OGITOR_LT_SPOTLIGHT
		};

		enum BillboardTypeTypes
		{
			OGITOR_BBT_POINT,
			OGITOR_BBT_ORIENTED_COMMON,
			OGITOR_BBT_ORIENTED_SELF,
			OGITOR_BBT_PERPENDICULAR_COMMON,
			OGITOR_BBT_PERPENDICULAR_SELF,
		};

		enum BillboardOriginTypes
		{
			OGITOR_BBO_TOP_LEFT, 	
			OGITOR_BBO_TOP_CENTER, 	
			OGITOR_BBO_TOP_RIGHT, 	
			OGITOR_BBO_CENTER_LEFT, 	
			OGITOR_BBO_CENTER, 	
			OGITOR_BBO_CENTER_RIGHT, 	
			OGITOR_BBO_BOTTOM_LEFT, 	
			OGITOR_BBO_BOTTOM_CENTER, 	
			OGITOR_BBO_BOTTOM_RIGHT 	
		};

		enum BillboardRotationTypeTypes
		{
			OGITOR_BBR_VERTEX,
			OGITOR_BBR_TEXCOORD
		};

		enum PolygonModeTypes
		{
			OGITOR_PM_NOT_USED,
			OGITOR_PM_POINTS,
			OGITOR_PM_WIREFRAME,
			OGITOR_PM_SOLID
		};

	};
}

#endif // OG_LevelLoader_H
