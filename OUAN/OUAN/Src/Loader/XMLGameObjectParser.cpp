#include "XMLGameObjectParser.h"

using namespace OUAN;

XMLGameObjectParser::XMLGameObjectParser(){}
XMLGameObjectParser::~XMLGameObjectParser(){}

void XMLGameObjectParser::init()
{
	unsigned int i;

	this->XMLGameObjectContainer.clear();

	gameObjectTypes.clear();

	gameObjectTypes.push_back(GAME_OBJECT_TYPE_SCENE);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TERRAIN);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_LIGHT);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_CAMERA);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_BILLBOARDSET);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_PARTICLESYSTEM);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_ONY);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TRIPOLLO);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_PORTAL);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_EYE);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_ITEM_1UP);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_ITEM_MAXHP);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_VOLUMEBOX);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_VOLUMECAPSULE);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_VIEWPORT);

	for(i=0;i<gameObjectTypes.size();i++)
	{
		parseCustomProperties(gameObjectTypes[i]);
	}	
}

void XMLGameObjectParser::clearLevel()
{
	XMLGameObjectContainer.clear();
}

void XMLGameObjectParser::parseCustomProperties(std::string gameObjectType)
{
	std::string customPropertiesFilePath;

	customPropertiesFilePath=GAME_OBJECT_PARAMETERS_PATH+gameObjectType+".ctp";

	//Open Custom properties file
	XMLCustomProperties[gameObjectType] = new TiXmlDocument(customPropertiesFilePath.c_str());

	if (!XMLCustomProperties[gameObjectType]->LoadFile()){
		Ogre::LogManager::getSingleton().logMessage("Error reading "+customPropertiesFilePath);
	} 
}

TiXmlElement * XMLGameObjectParser::getXMLCustomProperties(std::string gameObjectType)
{

	TiXmlHandle docHandle(XMLCustomProperties[gameObjectType]);
	TiXmlElement *XMLNodeCustomProperties = docHandle.FirstChildElement().Element();

	return XMLNodeCustomProperties;
}

void XMLGameObjectParser::parseLevel(String level)
{
	std::string fullLevelPath=LEVELS_PATH+level+".ogscene";

	XMLDoc= new TiXmlDocument(fullLevelPath.c_str());

	if (!XMLDoc->LoadFile()){
		Ogre::LogManager::getSingleton().logMessage("[XMLGameObjectParser] Error reading "+fullLevelPath);
	}

	// Validate the File
	TiXmlElement * XMLRoot = XMLDoc->RootElement();
	if( String( XMLRoot->Value()) != "OGITORSCENE"  ) {
		Ogre::LogManager::getSingleton().logMessage( "[XMLGameObjectParser] Error: Invalid .ogscene File. Missing <OGITORSCENE>" );
		delete XMLDoc;      
		return;
	}

	// Process the scene
	parseLevelRoot(XMLRoot);

	addXMLNodeCustomPropertiess();

	setNames();

}
void XMLGameObjectParser::setNames()
{
	XMLGameObjectContainerIterator it;

	for(it = XMLGameObjectContainer.begin(); it != XMLGameObjectContainer.end(); it++)
	{
		it->second.dreamsName=getDreamsName(it->second.name,it->second.gameObjectType);
		it->second.nightmaresName=getNightmaresName(it->second.name,it->second.gameObjectType);
	}
}

void XMLGameObjectParser::addXMLNodeCustomPropertiess()
{
	XMLGameObjectContainerIterator it;

	for(it = XMLGameObjectContainer.begin(); it != XMLGameObjectContainer.end(); it++)
	{
		it->second.XMLNodeCustomProperties=getXMLCustomProperties(it->second.gameObjectType);
	}
}

void XMLGameObjectParser::parseLevelRoot(TiXmlElement *XMLNode)
{

	// Process the scene parameters
	String version = getAttrib(XMLNode, "version", "unknown");

	String message = "[XMLGameObjectParser] Parsing ogScene file with version " + version;

	//LogManager::getSingleton().logMessage(message);
	
	//Process scene objects
	parseGameObjects(XMLNode);

}

void XMLGameObjectParser::parseGameObjects(TiXmlElement *XMLNode)
{
	TiXmlElement *pElement;

	// Process OBJECTs of selected type
	pElement = XMLNode->FirstChildElement("OBJECT");
	while(pElement)
	{
		parseGameObject(pElement);

		pElement = pElement->NextSiblingElement("OBJECT");
	}
}

void XMLGameObjectParser::parseGameObject(TiXmlElement *XMLNode)
{
	unsigned int i;
	bool found=false;

	String name = getAttrib(XMLNode, "name");
	String gameObjectType;

	//Find out game object type
	for(i=0;i<gameObjectTypes.size();i++)
	{
		if(name.substr(0,gameObjectTypes[i].size()).compare(gameObjectTypes[i])==0)
		{
			found=true;
			gameObjectType=gameObjectTypes[i];
			break;
		}
	}

	if(found)
	{
		addXMLGameObjectNode(name,gameObjectType,XMLNode);
	}
	else
	{
		Ogre::LogManager::getSingleton().logMessage( "[XMLGameObjectParser] Game Object "+name+" has unrecognised Game Object Type");
	}

}

void XMLGameObjectParser::addXMLGameObjectNode(std::string worldName,std::string gameObjectType,TiXmlElement *XMLNode)
{
	std::string baseName;

	baseName=getBaseName(worldName,gameObjectType);

	XMLGameObjectContainer[baseName].name=baseName;
	XMLGameObjectContainer[baseName].gameObjectType=gameObjectType;

	if(isDreams(worldName,gameObjectType))
	{
		XMLGameObjectContainer[baseName].XMLNodeDreams=XMLNode;
	}
	else if(isNightmares(worldName,gameObjectType))
	{
		XMLGameObjectContainer[baseName].XMLNodeNightmares=XMLNode;
	}

}

bool XMLGameObjectParser::isDreams(std::string worldName,std::string gameObjectType)
{
	return 	worldName[gameObjectType.size()+1]=='d';
}
bool XMLGameObjectParser::isNightmares(std::string worldName,std::string gameObjectType)
{
	return 	worldName[gameObjectType.size()+1]=='n';
}

std::string XMLGameObjectParser::getBaseName(std::string worldName,std::string gameObjectType)
{
	std::string baseName;

	baseName=gameObjectType+worldName.substr(gameObjectType.size()+2,worldName.size()-gameObjectType.size()+2);

	return	baseName;
}		


std::string XMLGameObjectParser::getNightmaresName(std::string baseName,std::string gameObjectType)
{
	std::string nightmaresName;

	nightmaresName=gameObjectType+"_n"+baseName.substr(gameObjectType.size(),baseName.size()-gameObjectType.size());

	return	nightmaresName;
}
std::string XMLGameObjectParser::getDreamsName(std::string baseName,std::string gameObjectType)
{
	std::string dreamsName;

	dreamsName=gameObjectType+"_d"+baseName.substr(gameObjectType.size(),baseName.size()-gameObjectType.size());

	return	dreamsName;
}


String XMLGameObjectParser::getAttrib(TiXmlElement *XMLNode, const String &attrib, const String &defaultValue)
{
	if(XMLNode->Attribute(attrib.c_str()))
		return XMLNode->Attribute(attrib.c_str());
	else
		return defaultValue;
}


String XMLGameObjectParser::getPropertyString(TiXmlElement *XMLNode, const String &attrib_name)
{
	TiXmlElement *pElement;
	TiXmlElement *XMLNodeCustomProperties;
	String propertyName;
	String result="";
	bool found=false;

	// Process all PROPERTY of the XML node
	pElement = XMLNode->FirstChildElement("PROPERTY");
	while(pElement)
	{
		propertyName = getAttrib(pElement, "id");

		//Ogre::LogManager::getSingleton().logMessage("[LevelLoader] parsing "+propertyName+" property!");

		if(propertyName.compare(attrib_name)==0)
		{
			// Get the attribute value
			result = getAttrib(pElement, "value");
			found=true;
		}
		pElement = pElement->NextSiblingElement("PROPERTY");
	}

	XMLNodeCustomProperties = XMLNode->FirstChildElement("CUSTOMPROPERTIES");

	// Process all CUSTOMPROPERTIES
	if(XMLNodeCustomProperties)
	{
		pElement = XMLNodeCustomProperties->FirstChildElement("PROPERTY");
		while(pElement)
		{
			propertyName = getAttrib(pElement, "id");

			//Ogre::LogManager::getSingleton().logMessage("[LevelLoader] parsing "+propertyName+" property!");

			if(propertyName.compare(attrib_name)==0)
			{
				// Get the attribute value
				result = getAttrib(pElement, "value");
				found=true;
			}
			pElement = pElement->NextSiblingElement("PROPERTY");
		}
	}

	if(!found)
	{
		Ogre::LogManager::getSingleton().logMessage("[LevelLoader] Error parsing "+attrib_name+" attribute!");
	}
	return result;
}

Vector2 XMLGameObjectParser::getPropertyVector2(TiXmlElement *XMLNode, const String &attrib_name)
{
	return StringConverter::parseVector2(getPropertyString(XMLNode,attrib_name));
}

Vector3 XMLGameObjectParser::getPropertyVector3(TiXmlElement *XMLNode, const String &attrib_name)
{
	return StringConverter::parseVector3(getPropertyString(XMLNode,attrib_name));
}

Vector4 XMLGameObjectParser::getPropertyVector4(TiXmlElement *XMLNode, const String &attrib_name)
{
	return StringConverter::parseVector4(getPropertyString(XMLNode,attrib_name));
}

Quaternion XMLGameObjectParser::getPropertyQuaternion(TiXmlElement *XMLNode, const String &attrib_name)
{
	return StringConverter::parseQuaternion(getPropertyString(XMLNode,attrib_name));
}

ColourValue XMLGameObjectParser::getPropertyColourValue(TiXmlElement *XMLNode, const String &attrib_name)
{
	return StringConverter::parseColourValue(getPropertyString(XMLNode,attrib_name));
}

bool XMLGameObjectParser::getPropertyBool(TiXmlElement *XMLNode, const String &attrib_name)
{
	 return StringConverter::parseBool(getPropertyString(XMLNode,attrib_name));
}

int XMLGameObjectParser::getPropertyInt(TiXmlElement *XMLNode, const String &attrib_name)
{
	 return StringConverter::parseInt(getPropertyString(XMLNode,attrib_name));
}

Real XMLGameObjectParser::getPropertyReal(TiXmlElement *XMLNode, const String &attrib_name)
{
	 return StringConverter::parseReal(getPropertyString(XMLNode,attrib_name));
}

