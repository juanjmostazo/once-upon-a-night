#ifndef XMLParserH_H
#define XMLParserH_H

#include "../OUAN.h"
namespace OUAN
{
	class XMLParser
	{
		protected:
			TiXmlDocument *XMLDoc;
			TiXmlElement *XMLRootNode;

			void parseLevelRoot(TiXmlElement *XMLNode);
			void parseElements(TiXmlElement *XMLNode);
			void parseElement(TiXmlElement *XMLNode);
			void addXMLGameObjectNode(const std::string& worldName,const std::string& gameObjectType,TiXmlElement *XMLNode);
			void addXMLNodeCustomProperties();
			void setNames();

			//Trajectory Parsing
			void parseTrajectory(TiXmlElement *XMLTrajectoryStartNode);
			TiXmlElement * findNode(const std::string&  nodeName);

			//WalkabilityMapParsing
			void parseWalkabilityMap(TiXmlElement *XMLWalkabilityMap);


			//Game Object names processors
			bool isDreams(const std::string&  worldName,const std::string&  gameObjectType);
			bool isNightmares(const std::string&  worldName,const std::string&  gameObjectType);
			std::string getBaseName(const std::string&  worldName,const std::string&  gameObjectType);
			std::string getNightmaresName(const std::string&  baseName,const std::string&  gameObjectType);
			std::string getDreamsName(const std::string&  baseName,const std::string&  gameObjectType);

			//Vector containing all GameObject types
			std::vector<std::string> gameObjectTypes;

			//Map containing all the GameObject custom properties documents
			std::map<std::string,TiXmlDocument *> XMLCustomProperties;

			//Parse all GameObject's types and its custom properties file .ctp
			void parseGameObjectTypes();
			//Parses custom properties file (.ctp) the specifies game object type and adds it to XMLCustomProperties map 
			void parseCustomProperties(const std::string&  gameObjectType);

			//Returns a node containing the custom properties for the specified game object type
			TiXmlElement * getXMLCustomProperties(const std::string&  gameObjectType);

			//Attribute parser
			OUAN::String getAttrib(TiXmlElement *XMLNode, const OUAN::String &parameter, const OUAN::String &defaultValue = "");
			
			//Property string parser
			OUAN::String getPropertyString(TiXmlElement *XMLNode, const OUAN::String &attrib_name, bool logErrors=true);

		public:
			XMLParser();
			virtual ~XMLParser();

			void init();
			void clearLevelInfo();

			void parseLevel(const String& SceneName);

			//Map containing all the parsed game objects
			XMLGameObjectContainer mXMLGameObjectContainer;

			//Map containing all the parsed trajectories
			XMLTrajectoryContainer mXMLTrajectoryContainer;
			std::vector<std::string> mCameraTrajectoryNames;

			//Map containing all the parsed walkability maps
			XMLWalkabilityMapContainer mXMLWalkabilityMapContainer;

			//Map containing all the parsed scene nodes
			XMLSceneNodeContainer mXMLSceneNodeContainer;
	};

}
#endif
