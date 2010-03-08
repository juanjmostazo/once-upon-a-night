#ifndef XMLGAMEOBJECTPARSERH_H
#define XMLGAMEOBJECTPARSERH_H

#include "../OUAN.h"

namespace OUAN
{
	class XMLGameObjectParser
	{
		protected:
			TiXmlDocument *XMLDoc;

			void parseLevelRoot(TiXmlElement *XMLNode);
			void parseGameObjects(TiXmlElement *XMLNode);
			void parseGameObject(TiXmlElement *XMLNode);
			void addXMLGameObjectNode(std::string worldName,std::string gameObjectType,TiXmlElement *XMLNode);
			void addXMLNodeCustomProperties();
			void setNames();

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

			//Properties parsers
			OUAN::String getPropertyString(TiXmlElement *XMLNode, const OUAN::String &attrib_name);
			OUAN::Vector2 getPropertyVector2(TiXmlElement *XMLNode, const OUAN::String &attrib_name);
			OUAN::Vector3 getPropertyVector3(TiXmlElement *XMLNode, const OUAN::String &attrib_name);
			OUAN::Vector4 getPropertyVector4(TiXmlElement *XMLNode, const OUAN::String &attrib_name);
			OUAN::Quaternion getPropertyQuaternion(TiXmlElement *XMLNode, const OUAN::String &attrib_name);
			OUAN::ColourValue getPropertyColourValue(TiXmlElement *XMLNode, const OUAN::String &attrib_name);
			bool getPropertyBool(TiXmlElement *XMLNode, const OUAN::String &attrib_name);
			int getPropertyInt(TiXmlElement *XMLNode, const OUAN::String &attrib_name);
			OUAN::Real getPropertyReal(TiXmlElement *XMLNode, const OUAN::String &attrib_name);

		public:
			XMLGameObjectParser();
			virtual ~XMLGameObjectParser();

			void init();
			void clearLevelInfo();

			void parseLevel(String SceneName);

			//Map containing all the parsed objects
			std::map<std::string,XMLGameObject> XMLGameObjectContainer;
			typedef std::map<std::string,XMLGameObject>::iterator XMLGameObjectContainerIterator;

	};

}
#endif
