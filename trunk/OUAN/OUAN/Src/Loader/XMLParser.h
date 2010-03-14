#ifndef XMLParserH_H
#define XMLParserH_H

#include "../OUAN.h"
#include "XMLTrajectory.h"
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
			void addXMLGameObjectNode(std::string worldName,std::string gameObjectType,TiXmlElement *XMLNode);
			void addXMLNodeCustomProperties();
			void setNames();

			//Trajectory Parsing
			void parseTrajectory(TiXmlElement *XMLTrajectoryStartNode);
			TiXmlElement * findTrajectoryNode(std::string trajectoryNodeName);

			//Game Object names processors
			bool isDreams(std::string worldName,std::string gameObjectType);
			bool isNightmares(std::string worldName,std::string gameObjectType);
			std::string getBaseName(std::string worldName,std::string gameObjectType);
			std::string getNightmaresName(std::string baseName,std::string gameObjectType);
			std::string getDreamsName(std::string baseName,std::string gameObjectType);

			//Vector containing all GameObject types
			std::vector<std::string> gameObjectTypes;

			//Map containing all the GameObject custom properties documents
			std::map<std::string,TiXmlDocument *> XMLCustomProperties;

			//Parse all GameObject's types and its custom properties file .ctp
			void parseGameObjectTypes();
			//Parses custom properties file (.ctp) the specifies game object type and adds it to XMLCustomProperties map 
			void parseCustomProperties(std::string gameObjectType);

			//Returns a node containing the custom properties for the specified game object type
			TiXmlElement * getXMLCustomProperties(std::string gameObjectType);

			//Attribute parser
			OUAN::String getAttrib(TiXmlElement *XMLNode, const OUAN::String &parameter, const OUAN::String &defaultValue = "");
			
			//Property string parser
			OUAN::String getPropertyString(TiXmlElement *XMLNode, const OUAN::String &attrib_name, bool logErrors=true);

		public:
			XMLParser();
			virtual ~XMLParser();

			void init();
			void clearLevelInfo();

			void parseLevel(String SceneName);

			//Map containing all the parsed game objects
			std::map<std::string,XMLGameObject> XMLGameObjectContainer;
			typedef std::map<std::string,XMLGameObject>::iterator XMLGameObjectContainerIterator;

			//Map containing all the parsed trajectories
			std::map<std::string,XMLTrajectory> XMLTrajectoryContainer;
			typedef std::map<std::string,XMLTrajectory>::iterator XMLTrajectoryContainerIterator;
	};

}
#endif
