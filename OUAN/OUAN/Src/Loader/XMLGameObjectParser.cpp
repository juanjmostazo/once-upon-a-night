#include "XMLGameObjectParser.h"
#include "XMLGameObject.h"

using namespace OUAN;

XMLGameObjectParser::XMLGameObjectParser(){}
XMLGameObjectParser::~XMLGameObjectParser(){}

void XMLGameObjectParser::init()
{
	clearLevelInfo();
}

void XMLGameObjectParser::clearLevelInfo()
{
	XMLGameObjectContainerIterator it;

	XMLGameObjectContainer.clear();
	gameObjectTypes.clear();
	XMLCustomProperties.clear();

	for(it = XMLGameObjectContainer.begin(); it != XMLGameObjectContainer.end(); it++)
	{
		it->second.XMLNodeDreams=NULL;
		it->second.XMLNodeNightmares=NULL;
		it->second.XMLNodeCustomProperties=NULL;
	}

}

void XMLGameObjectParser::parseGameObjectTypes()
{
	unsigned int i;

	gameObjectTypes.clear();

	gameObjectTypes.push_back(GAME_OBJECT_TYPE_SCENE);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_VIEWPORT);
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
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_NIGHTGOBLIN);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_CRYKING);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_DRAGON);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_MAGIC_CLOCK);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_PILLOW);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_FLASHLIGHT);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TENTENTIESO);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_BEE_BUTTERFLY);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_SNAKE_CREEPER_CARNIVOROUS_PLANT);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_DIAMOND_TREE);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_STORYBOOK);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_HEART);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_DIAMOND);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_SCARED_PLANT);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TREE);

	for(i=0;i<gameObjectTypes.size();i++)
	{
		parseCustomProperties(gameObjectTypes[i]);
	}	
}

void XMLGameObjectParser::parseCustomProperties(std::string gameObjectType)
{
	std::string customPropertiesFilePath;

	customPropertiesFilePath=GAME_OBJECT_PARAMETERS_PATH+gameObjectType+".ctp";

	//Open Custom properties file
	XMLCustomProperties[gameObjectType] = new TiXmlDocument(customPropertiesFilePath.c_str());

	if (!XMLCustomProperties[gameObjectType]->LoadFile()){
		Ogre::LogManager::getSingleton().logMessage("[XMLGameObjectParser] Error reading "+customPropertiesFilePath);
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

	// Parse all GameObjects' types and its custom properties file .ctp
	parseGameObjectTypes();

	// Process the scene
	parseLevelRoot(XMLRoot);

	addXMLNodeCustomProperties();

	// set GameObjects' names
	setNames();

}
void XMLGameObjectParser::setNames()
{
	XMLGameObjectContainerIterator it;

	for(it = XMLGameObjectContainer.begin(); it != XMLGameObjectContainer.end(); it++)
	{
		//special cases
		if(it->second.gameObjectType.compare(GAME_OBJECT_TYPE_SCENE)==0)
		{
			it->second.dreamsName=it->second.name;
			it->second.nightmaresName=it->second.name;
		}
		else if(it->second.gameObjectType.compare(GAME_OBJECT_TYPE_VIEWPORT)==0)
		{
			it->second.dreamsName=it->second.name;
			it->second.nightmaresName=it->second.name;
		}
		else if(it->second.gameObjectType.compare(GAME_OBJECT_TYPE_CAMERA)==0)
		{
			it->second.dreamsName=it->second.name;
			it->second.nightmaresName=it->second.name;
		}
		//default case
		else
		{
			it->second.dreamsName=getDreamsName(it->second.name,it->second.gameObjectType);
			it->second.nightmaresName=getNightmaresName(it->second.name,it->second.gameObjectType);
		}
	}
}

void XMLGameObjectParser::addXMLNodeCustomProperties()
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

void XMLGameObjectParser::parseTrajectory(TiXmlElement *XMLNode)
{
	
}

void XMLGameObjectParser::parseGameObject(TiXmlElement *XMLNode)
{
	unsigned int i;
	bool found=false;

	String name = getAttrib(XMLNode, "name");
	String type = getAttrib(XMLNode, "typename");
	String gameObjectType;

	if(type.compare("Marker Object")==0)
	{
		//Not a GameObject

		//String trajectoryName = getPropertyString(XMLNode,"trajectory::name",false);
		//if(trajectoryName.compare("")!=0)
		//{
		//	//Parse Trajectory
		//	parseTrajectory(XMLNode);
		//}
		return;
	}

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
		Ogre::LogManager::getSingleton().logMessage("[XMLGameObjectParser] Game Object "+name+" has unrecognised Game Object Type");
	}

}

void XMLGameObjectParser::addXMLGameObjectNode(std::string worldName,std::string gameObjectType,TiXmlElement *XMLNode)
{
	std::string baseName;

	//special cases
	if(gameObjectType.compare(GAME_OBJECT_TYPE_SCENE)==0)
	{
		baseName=worldName;
		XMLGameObjectContainer[baseName].name=baseName;
		XMLGameObjectContainer[baseName].gameObjectType=gameObjectType;

		XMLGameObjectContainer[baseName].XMLNodeDreams=XMLNode;
	}
	else if(gameObjectType.compare(GAME_OBJECT_TYPE_VIEWPORT)==0)
	{
		baseName=worldName;
		XMLGameObjectContainer[baseName].name=baseName;
		XMLGameObjectContainer[baseName].gameObjectType=gameObjectType;

		XMLGameObjectContainer[baseName].XMLNodeDreams=XMLNode;
	}
	else if(gameObjectType.compare(GAME_OBJECT_TYPE_CAMERA)==0)
	{
		baseName=worldName;
		XMLGameObjectContainer[baseName].name=baseName;
		XMLGameObjectContainer[baseName].gameObjectType=gameObjectType;

		XMLGameObjectContainer[baseName].XMLNodeDreams=XMLNode;
	}
	//default case
	else
	{
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

