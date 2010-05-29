#ifndef LevelLoaderH_H
#define LevelLoaderH_H

//OUAN
#include "../OUAN.h"
#include "../Audio/AudioDefs.h"
#include "XMLParser.h"
#include "Configuration.h"

namespace OUAN
{
	class GameObjectFactory;
	typedef boost::shared_ptr<GameObjectFactory> GameObjectFactoryPtr;

	class LevelLoader
	{
	public:
		LevelLoader();
		virtual ~LevelLoader();

		void init(OUAN::ApplicationPtr app);

		void loadLevel(String SceneName);

	protected:
		GameWorldManagerPtr mGameWorldManager;
		GameObjectFactoryPtr mGameObjectFactory;

		XMLParser mXMLParser;

		//Process GameObjects
		void processGameObjects();
		void processGameObjectBillboardClouds();
		void processGameObjectFractalClouds();
		void processGameObject(XMLGameObject *gameObject);

		//ProcessTrajectories
		void processTrajectories();
		void processTrajectory(XMLTrajectory *trajectory);
		TTrajectoryNodeParameters processTrajectoryNode(TiXmlElement *XMLNode);

		//ProcessWalkabilityMaps
		void processWalkabilityMaps();
		void processWalkabilityMap(XMLWalkabilityMap *walkabilityMap);
		TWalkabilityMapNodeParameters processWalkabilityMapNode(TiXmlElement *XMLNode);

		double DEFAULT_TRAJECTORY_SPEED;

		//Game Object Processors
		void processGameObjectBee_Butterfly(XMLGameObject* gameObject);
		void processGameObjectBillboardSet(XMLGameObject* gameObject);
		void processGameObjectBush(XMLGameObject* gameObject);
		void processGameObjectCamera(XMLGameObject* gameObject);
		void processGameObjectCarnivorousPlant(XMLGameObject* gameObject);
		void processGameObjectClockPiece(XMLGameObject* gameObject);
		void processGameObjectCryKing(XMLGameObject* gameObject);
		void processGameObjectDiamond(XMLGameObject* gameObject);
		void processGameObjectDiamondTree(XMLGameObject* gameObject);
		void processGameObjectDoor(XMLGameObject* gameObject);
		void processGameObjectDragon(XMLGameObject* gameObject);
		void processGameObjectEye(XMLGameObject* gameObject);
		void processGameObjectFlashLight(XMLGameObject* gameObject);
		void processGameObjectHeart(XMLGameObject* gameObject);
		void processGameObjectItem1UP(XMLGameObject* gameObject);
		void processGameObjectItemMaxHP(XMLGameObject* gameObject);
		void processGameObjectLight(XMLGameObject* gameObject);
		void processGameObjectMagicClock(XMLGameObject* gameObject);
		void processGameObjectNightGoblin(XMLGameObject* gameObject);
		void processGameObjectOny(XMLGameObject *gameObject);
		void processGameObjectParticleSystem(XMLGameObject* gameObject);
		void processGameObjectPillow(XMLGameObject *gameObject);
		void processGameObjectPlane(XMLGameObject *gameObject);
		void processGameObjectPlataform(XMLGameObject *gameObject);
		void processGameObjectPortal(XMLGameObject *gameObject);
		void processGameObjectProvisionalEntity(XMLGameObject* gameObject);
		void processGameObjectScaredPlant(XMLGameObject* gameObject);
		void processGameObjectScene(XMLGameObject* gameObject);
		void processGameObjectScepter(XMLGameObject* gameObject);
		void processGameObjectSkyBody(XMLGameObject* gameObject);
		void processGameObjectSnakeCreeper(XMLGameObject* gameObject);
		void processGameObjectSound(XMLGameObject* gameObject);
		void processGameObjectStoryBook(XMLGameObject* gameObject);
		void processGameObjectTentetieso(XMLGameObject* gameObject);
		void processGameObjectTerrain(XMLGameObject* gameObject);
		void processGameObjectTree(XMLGameObject* gameObject);
		void processGameObjectTriggerBox(XMLGameObject* gameObject);
		void processGameObjectTriggerCapsule(XMLGameObject* gameObject);
		void processGameObjectTripollito(XMLGameObject* gameObject);
		void processGameObjectTripolloDreams(XMLGameObject* gameObject);
		void processGameObjectViewport(XMLGameObject* gameObject);
		void processGameObjectWoodBox(XMLGameObject* gameObject);
		void processGameObjectWater(XMLGameObject* gameObject);
			//Special function to create a GameObjectCamera using Ogitor's viewport camera
		void processGameObjectViewportCamera(XMLGameObject* gameObject);

		//RenderComponent Processors
		TRenderComponentSceneParameters processRenderComponentScene(TiXmlElement *XMLOgitorNode,TiXmlElement *XMLCustomPropertiesNode);
		TRenderComponentSkyBoxParameters processRenderComponentSkyBox(TiXmlElement *XMLCustomPropertiesNode);
		TRenderComponentSkyDomeParameters processRenderComponentSkyDome(TiXmlElement *XMLCustomPropertiesNode);
		TRenderComponentPositionalParameters processRenderComponentPositional(TiXmlElement *XMLNode);
		TRenderComponentPositionalParameters processRenderComponentPositionalNoScale(TiXmlElement *XMLNode);
		TRenderComponentEntityParameters processRenderComponentEntity(TiXmlElement *XMLNode, int world, TiXmlElement* XMLCustomPropertiesNode=NULL);
		TRenderComponentLightParameters processRenderComponentLight(TiXmlElement *XMLNode);
		TRenderComponentParticleSystemParameters processRenderComponentParticleSystem(TiXmlElement *XMLNode);
		TRenderComponentQuadHaloParameters processRenderComponentQuadHalo(TiXmlElement *XMLNode);
		TRenderComponentFractalVolumeParameters processRenderComponentFractalVolume(TiXmlElement *XMLNode);
		TRenderComponentBillboardSetParameters processRenderComponentBillboardSet(TiXmlElement *XMLNode);
		TRenderComponentCameraParameters processRenderComponentCamera(TiXmlElement *XMLNode);
		TRenderComponentCameraParameters processRenderComponentCameraViewport(TiXmlElement *XMLNode);
		TRenderComponentViewportParameters processRenderComponentViewport(TiXmlElement *XMLNode);
		TRenderComponentPlaneParameters processRenderComponentPlane(TiXmlElement *XMLNode);
		void processRenderComponentSubEntities(std::vector<TRenderComponentSubEntityParameters>  &tRenderComponentSubEntityParameters,
			TiXmlElement *XMLNode);
		void processRenderComponentBillboards(std::vector<TRenderComponentBillboardParameters>  &tRenderComponentBillboardParameters,
			TiXmlElement *XMLNode);
		void processRenderComponentEntityAnimParams(std::vector<TRenderComponentEntityAnimParams>& renderComponentEntityAnimParameters,
			TiXmlElement* XMLNode, int world);
		QueryFlags processCameraCollisionType(TiXmlElement *XMLNode);
		Ogre::uint8 processRenderQueueId(TiXmlElement *XMLNode);

		//PhysicComponent Processors
		TPhysicsComponentCharacterParameters processPhysicsComponentCharacter(TiXmlElement *XMLNode,std::string suffix="");
		TPhysicsComponentComplexConvexParameters processPhysicsComponentComplexConvex(TiXmlElement *XMLNode,std::string nxsFile,std::string suffix="");
		TPhysicsComponentComplexTriangleParameters processPhysicsComponentComplexTriangle(TiXmlElement *XMLNode,std::string nxsFile,std::string suffix="");
		TPhysicsComponentSimpleBoxParameters processPhysicsComponentSimpleBox(TiXmlElement *XMLNode,std::string suffix="");
		TPhysicsComponentSimpleCapsuleParameters processPhysicsComponentSimpleCapsule(TiXmlElement *XMLNode,std::string suffix="");
		TPhysicsComponentVolumeBoxParameters processPhysicsComponentVolumeBox(TiXmlElement *XMLCustomPropertiesNode,std::string suffix="");
		TPhysicsComponentVolumeCapsuleParameters processPhysicsComponentVolumeCapsule(TiXmlElement *XMLCustomPropertiesNode,std::string suffix="");
		TPhysicsComponentVolumeBoxParameters processPhysicsComponentVolumeBoxUsingScale(TiXmlElement *XMLCustomPropertiesNode,TiXmlElement *XMLRenderInfoNode,std::string suffix="");
		TPhysicsComponentVolumeCapsuleParameters processPhysicsComponentVolumeCapsuleUsingScale(TiXmlElement *XMLCustomPropertiesNode,TiXmlElement *XMLRenderInfoNode,std::string suffix="");
		TPhysicsComponentVolumeConvexParameters processPhysicsComponentVolumeConvex(TiXmlElement *XMLCustomPropertiesNode);
		TPhysicsComponentVolumeConvexParameters processPhysicsComponentVolumeConvex(TiXmlElement *XMLCustomPropertiesNode,std::string nxsFile);

		//LogicComponent Processors		
		TLogicComponentParameters processLogicComponent(TiXmlElement *XMLNodeDreams,
			TiXmlElement *XMLNodeNightmares, TiXmlElement* XMLNodeCustomProperties);
		TAttackComponentParameters processAttackComponent(TiXmlElement* XMLNode);
		TWeaponComponentParameters processWeaponComponent(TiXmlElement* XMLNode);
		TLogicComponentOnyParameters processLogicComponentOny(TiXmlElement *XMLNodeDreams,
			TiXmlElement *XMLNodeNightmares, TiXmlElement* XMLNodeCustomProperties);
		TLogicComponentItemParameters processLogicComponentItem(TiXmlElement *XMLNodeDreams,
			TiXmlElement *XMLNodeNightmares, TiXmlElement* XMLNodeCustomProperties);
		TLogicComponentBreakableParameters processLogicComponentBreakable(TiXmlElement *XMLNodeDreams,
			TiXmlElement *XMLNodeNightmares, TiXmlElement* XMLNodeCustomProperties);
		TLogicComponentEnemyParameters processLogicComponentEnemy(TiXmlElement *XMLNodeDreams,
			TiXmlElement *XMLNodeNightmares, TiXmlElement* XMLNodeCustomProperties);
		TLogicComponentUsableParameters processLogicComponentUsable(TiXmlElement *XMLNodeDreams,
			TiXmlElement *XMLNodeNightmares, TiXmlElement* XMLNodeCustomProperties);
		TLogicComponentPropParameters processLogicComponentProp(TiXmlElement *XMLNodeDreams,
			TiXmlElement *XMLNodeNightmares, TiXmlElement* XMLNodeCustomProperties);
		TLogicComponentTriggerParameters processLogicComponentTrigger(TiXmlElement *XMLNodeDreams,
			TiXmlElement *XMLNodeNightmares, TiXmlElement* XMLNodeCustomProperties);

		//
		TAudioComponentMap processAudioComponent(TiXmlElement* XMLNode);

		//ChangeWorldMaterials parameters
		TChangeWorldMaterialParameters processChangeWorldMaterialParameters(TiXmlElement* XMLNode);

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

		enum CameraCollisionTypes
		{
			OGITOR_CAMERA_COLLISION_MOVE_TO_TARGET,
			OGITOR_CAMERA_COLLISION_ROTX_POSITIVE,
			OGITOR_CAMERA_COLLISION_ROTX_NEGATIVE,
			OGITOR_NONE
		};

		enum OgitorChangeWorldTypes
		{
			OGITOR_CW_BLENDING,
			OGITOR_CW_EROSION,
			OGITOR_CW_EROSION_TRANSPARENT
		};

	};
}

#endif // OG_LevelLoader_H
