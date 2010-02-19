#ifndef OG_LevelLoader_H
#define OG_LevelLoader_H

//OUAN
#include "../OUAN.h"

namespace OUAN
{
	class LevelLoader
	{
	public:
		LevelLoader();
		virtual ~LevelLoader();

		void initialise(OUAN::ApplicationPtr app);

		void loadLevel(String SceneName,String resourceGroupName="General");


	protected:
		GameWorldManagerPtr pGameWorldManager;



		void processScene(TiXmlElement *XMLNode);
		void processProject(TiXmlElement *XMLNode);
		void processObjects(TiXmlElement *XMLNode,OUAN::String type);
		void processObject(TiXmlElement *XMLNode);
		void processResourceLocations(TiXmlElement *XMLNode);
		void processTerrain(TiXmlElement *XMLNode);
		void processOctreeSceneManager(TiXmlElement *XMLNode);
		void processLight(TiXmlElement *XMLNode);
		void processSceneNodeNoScale(TiXmlElement *XMLNode);
		void processCamera(TiXmlElement *XMLNode);
		void processViewport(TiXmlElement *XMLNode);
		void processViewportCamera(TiXmlElement *XMLNode);
		TRenderComponentSceneNodeParameters processSceneNode(TiXmlElement *XMLNode);
		void processTrackTarget(TiXmlElement *XMLNode);
		void processEntity(TiXmlElement *XMLNode);
		void processSubentities(std::vector<TRenderComponentSubEntityParameters>  &TRenderComponentSubEntityParameters ,TiXmlElement *XMLNode);
		void processParticleSystem(TiXmlElement *XMLNode);
		void processBillboardSet(TiXmlElement *XMLNode);
		void processBillboards(std::vector<TRenderComponentBillboardParameters> &TRenderComponentBillboardParameters,TiXmlElement *XMLNode);
		//TODO: void processPlane(TiXmlElement *XMLNode);
		//TODO: void processFog(TiXmlElement *XMLNode);
		TRenderComponentSkyBoxParameters processSkyBox(TiXmlElement *XMLNode);
		TRenderComponentSkyDomeParameters processSkyDome(TiXmlElement *XMLNode);
		//TODO: void processShadows(TiXmlElement *XMLNode);
		//TODO: void processTrajectory(TiXmlElement *XMLNode);

		OUAN::String getAttrib(TiXmlElement *XMLNode, const OUAN::String &parameter, const OUAN::String &defaultValue = "");

		OUAN::String getPropertyString(TiXmlElement *XMLNode, const OUAN::String &attrib_name);
		OUAN::Vector2 getPropertyVector2(TiXmlElement *XMLNode, const OUAN::String &attrib_name);
		OUAN::Vector3 getPropertyVector3(TiXmlElement *XMLNode, const OUAN::String &attrib_name);
		OUAN::Vector4 getPropertyVector4(TiXmlElement *XMLNode, const OUAN::String &attrib_name);
		OUAN::Quaternion getPropertyQuaternion(TiXmlElement *XMLNode, const OUAN::String &attrib_name);
		OUAN::ColourValue getPropertyColourValue(TiXmlElement *XMLNode, const OUAN::String &attrib_name);
		bool getPropertyBool(TiXmlElement *XMLNode, const OUAN::String &attrib_name);
		int getPropertyInt(TiXmlElement *XMLNode, const OUAN::String &attrib_name);
		OUAN::Real getPropertyReal(TiXmlElement *XMLNode, const OUAN::String &attrib_name);

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
