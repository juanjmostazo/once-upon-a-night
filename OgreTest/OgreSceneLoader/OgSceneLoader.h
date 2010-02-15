#ifndef OG_SCENELOADER_H
#define OG_SCENELOADER_H

// Includes
#include <OgreString.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <vector>

// Forward declarations
class TiXmlElement;

namespace Ogre
{
	// Forward declarations
	class SceneManager;
	class SceneNode;

	class OgSceneLoader
	{
	public:
		OgSceneLoader() : mSceneMgr(0) {}
		virtual ~OgSceneLoader() {}

		void parseOgScene(const String &SceneName, const String &groupName, SceneManager *pSceneMgr, SceneNode *pAttachNode, Viewport *pViewport);

	protected:
		SceneManager *mSceneMgr;
		SceneNode *mAttachNode;
		Viewport *mViewport;
		String m_sGroupName;

		void processScene(TiXmlElement *XMLNode);
		void processProject(TiXmlElement *XMLNode);
		void processObjects(TiXmlElement *XMLNode,String type);
		void processObject(TiXmlElement *XMLNode);
		void processResourceLocations(TiXmlElement *XMLNode);
		void processTerrain(TiXmlElement *XMLNode);
		void processOctreeSceneManager(TiXmlElement *XMLNode);
		void processLight(TiXmlElement *XMLNode);
		void processSceneNodeNoScale(TiXmlElement *XMLNode);
		void processCamera(TiXmlElement *XMLNode);
		void processViewport(TiXmlElement *XMLNode);
		void processViewportCamera(TiXmlElement *XMLNode);
		void processSceneNode(TiXmlElement *XMLNode);
		void processTrackTarget(TiXmlElement *XMLNode);
		void processEntity(TiXmlElement *XMLNode);
		void processSubentities(String name,TiXmlElement *XMLNode);
		void processParticleSystem(TiXmlElement *XMLNode);
		void processBillboardSet(TiXmlElement *XMLNode);
		void processBillboards(String billBoardSetName,TiXmlElement *XMLNode);
		void processPlane(TiXmlElement *XMLNode);
		void processFog(TiXmlElement *XMLNode);
		void processSkyBox(TiXmlElement *XMLNode);
		void processSkyDome(TiXmlElement *XMLNode);
		void processShadows(TiXmlElement *XMLNode);

		void createMeshFile(String meshfile);
		void createEntity(String name,String meshfile,bool castshadows);
		void createSubEntity(String name,int num,String material,bool visible);
		void createSceneNode(String name,String parentSceneNodeName,Vector3 position,Quaternion orientation,Vector3 scale,String autotracktarget);
		void createLight(String name,int lighttype,ColourValue diffuse,ColourValue specular,Vector3 direction,bool castshadows,Vector3 lightrange,Vector4 attenuation,Real power);
		void createParticleSystem(String name,String particle,bool castshadows);
		void createBillboard(String billBoardSetName,ColourValue colour,Vector2 dimensions,Vector3 position,Real rotation,int texcoordindex,Vector4 texrect);
		void createBillboardSet(String name,String material,int billboardorigin,int billboardrotation,int billboardtype,Real defaultheight,Real defaultwidth,bool pointrendering,Real renderdistance,bool sorting);
		void createViewport(String name,ColourValue colour,int compositorcount,int index,bool overlays,bool shadows,bool skies);
		void createCamera(String name,Vector3 position,Quaternion orientation,String autotracktarget,bool autoaspectratio,Vector2 clipdistance,Real fov,int polygonmode, int viewmode);
		void createOctreeSceneManager(String name,ColourValue ambient);
		void createResourceLocations();
		void createSkyBox(bool active, String material, Real distance);
		void createSkyDome(bool active, String material);
		void createShadows();
		void createFog();
		void createPlane();

		String getAttrib(TiXmlElement *XMLNode, const String &parameter, const String &defaultValue = "");

		String getPropertyString(TiXmlElement *XMLNode, const String &attrib_name);
		Vector2 getPropertyVector2(TiXmlElement *XMLNode, const String &attrib_name);
		Vector3 getPropertyVector3(TiXmlElement *XMLNode, const String &attrib_name);
		Vector4 getPropertyVector4(TiXmlElement *XMLNode, const String &attrib_name);
		Quaternion getPropertyQuaternion(TiXmlElement *XMLNode, const String &attrib_name);
		ColourValue getPropertyColourValue(TiXmlElement *XMLNode, const String &attrib_name);
		bool getPropertyBool(TiXmlElement *XMLNode, const String &attrib_name);
		int getPropertyInt(TiXmlElement *XMLNode, const String &attrib_name);
		Real getPropertyReal(TiXmlElement *XMLNode, const String &attrib_name);

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

#endif // OG_SCENELOADER_H
