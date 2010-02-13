#ifndef DOT_SCENELOADER_H
#define DOT_SCENELOADER_H

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

	class nodeProperty
	{
	public:
		String nodeName;
		String propertyNm;
		String valueName;
		String typeName;

		nodeProperty(const String &node, const String &propertyName, const String &value, const String &type)
			: nodeName(node), propertyNm(propertyName), valueName(value), typeName(type) {}
	};

	class OgSceneLoader
	{
	public:
		OgSceneLoader() : mSceneMgr(0) {}
		virtual ~OgSceneLoader() {}

		void parseOgScene(const String &SceneName, const String &groupName, SceneManager *yourSceneMgr, SceneNode *pAttachNode = NULL, const String &sPrependNode = "");
		String getProperty(const String &ndNm, const String &prop);

		std::vector<nodeProperty> nodeProperties;
		std::vector<String> staticObjects;
		std::vector<String> dynamicObjects;

	protected:
		SceneManager *mSceneMgr;
		SceneNode *mAttachNode;
		String m_sGroupName;
		String m_sPrependNode;

		void processScene(TiXmlElement *XMLRoot);

		void processProject(TiXmlElement *XMLNode);
		void processObject(TiXmlElement *XMLNode);

		void processExternals(TiXmlElement *XMLNode);
		void processEnvironment(TiXmlElement *XMLNode);
		void processResourceLocations(TiXmlElement *XMLNode);
		void processTerrain(TiXmlElement *XMLNode);
		void processOctree(TiXmlElement *XMLNode);
		void processLight(TiXmlElement *XMLNode);
		void processLightSceneNode(TiXmlElement *XMLNode);
		void processCamera(TiXmlElement *XMLNode);

		void processSceneNode(TiXmlElement *XMLNode);
		void processLookTarget(TiXmlElement *XMLNode);
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
		void processSkyPlane(TiXmlElement *XMLNode);
		void processClipping(TiXmlElement *XMLNode);

		void loadMeshFile(String meshfile);
		void loadEntity(String name,String meshfile,bool castshadows);
		void loadSubEntity(String name,int num,String material,bool visible);
		void loadSceneNode(String name,String parentSceneNodeName,Vector3 position,Quaternion orientation,Vector3 scale,String autotracktarget);
		void loadLight(String name,int lighttype,ColourValue diffuse,ColourValue specular,Vector3 direction,bool castshadows,Vector3 lightrange,Vector4 attenuation,Real power);
		void loadParticleSystem(String name,String particle,bool castshadows);
		void loadBillboard(String billBoardSetName,ColourValue colour,Vector2 dimensions,Vector3 position,Real rotation,int texcoordindex,Vector4 texrect);
		void loadBillboardSet(String name,String material,int billboardorigin,int billboardrotationtype,int billboardtype,Real defaultheight,Real defaultwidth,bool pointrendering,Real renderdistance,bool sorting);

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
			OGITOR_BBT_ORIENTED_COMMON,
			OGITOR_BBT_ORIENTED_SELF,
			OGITOR_BBT_PERPENDICULAR_COMMON,
			OGITOR_BBT_PERPENDICULAR_SELF,
			OGITOR_BBT_POINT
		};

		enum BillboardOriginTypes
		{
			OGITOR_BBO_BOTTOM_CENTER,
			OGITOR_BBO_BOTTOM_LEFT,
			OGITOR_BBO_BOTTOM_RIGHT,
			OGITOR_BBO_CENTER,
			OGITOR_BBO_CENTER_LEFT,
			OGITOR_BBO_CENTER_RIGHT,
			OGITOR_BBO_TOP_CENTER,
			OGITOR_BBO_TOP_LEFT,
			OGITOR_BBO_TOP_RIGHT
		};

		enum BillboardRotationTypeTypes
		{
			OGITOR_BBR_TEXCOORD,
			OGITOR_BBR_VERTEX
		};

	};
}

#endif // DOT_SCENELOADER_H
