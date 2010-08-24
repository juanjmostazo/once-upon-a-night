#include "OUAN_Precompiled.h"

#include "XMLParser.h"
#include "XMLGameObject.h"
#include "XMLTrajectory.h"
#include "XMLWalkabilityMap.h"
#include "XMLSceneNode.h"

using namespace OUAN;

XMLParser::XMLParser(){}
XMLParser::~XMLParser(){}

void XMLParser::init()
{
	clearLevelInfo();
}

void XMLParser::clearLevelInfo()
{
	XMLGameObjectContainerIterator it;

	mXMLGameObjectContainer.clear();
	gameObjectTypes.clear();
	XMLCustomProperties.clear();

	mXMLTrajectoryContainer.clear();
	mXMLWalkabilityMapContainer.clear();

	mCameraTrajectoryNames.clear();

	for(it = mXMLGameObjectContainer.begin(); it != mXMLGameObjectContainer.end(); it++)
	{
		it->second.XMLNodeDreams=NULL;
		it->second.XMLNodeNightmares=NULL;
		it->second.XMLNodeCustomProperties=NULL;
	}
}

void XMLParser::parseGameObjectTypes()
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
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TRIGGERBOX);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TRIGGERCAPSULE);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_NIGHTGOBLIN);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_CRYKING);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_BOSS);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_MAGICCLOCK);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_PILLOW);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_FLASHLIGHT);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TENTETIESO);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_BEE_BUTTERFLY);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_STORYBOOK);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_HEART);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_DIAMONDTREE);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_DIAMOND);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_SCAREDPLANT);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_CLOCKPIECE);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_SNAKECREEPER);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_SOUND);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_CARNIVOROUSPLANT);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_SCEPTER);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TREE12);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TREE11);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TREE10);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TREE1);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TREE2);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TREE3);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TREE4);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TREE5);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TREE6);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TREE7);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TREE8);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TREE9);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_DOOR);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_PLATAFORM);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TRASPASABLE3);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TRASPASABLE2);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TRASPASABLE1);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TRASPASABLE);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_CLOUD);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_WOODBOX);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_WATER);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_PLANE);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_SKYBODY);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TOWER);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_FOG);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TRIGGER_CAMERA);	
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_SIGNPOST);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_NEST);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_SWITCH);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_BOMB);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_LEVEL_ENTRANCE);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_TOTEM);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_INVISIBLE_WALL);
	gameObjectTypes.push_back(GAME_OBJECT_TYPE_BREAKABLE_ROCK);

	for(i=0;i<gameObjectTypes.size();i++)
	{
		parseCustomProperties(gameObjectTypes[i]);
	}	
}

void XMLParser::parseCustomProperties(const std::string& gameObjectType)
{
	std::string customPropertiesFilePath;

	customPropertiesFilePath=GAME_OBJECT_PARAMETERS_PATH+gameObjectType+".ctp";

	//Open Custom properties file
	XMLCustomProperties[gameObjectType] = new TiXmlDocument(customPropertiesFilePath.c_str());

	if (!XMLCustomProperties[gameObjectType]->LoadFile()){
		Logger::getInstance()->log("[XMLParser] Error reading "+customPropertiesFilePath);
	} 
}

TiXmlElement * XMLParser::getXMLCustomProperties(const std::string& gameObjectType)
{

	TiXmlHandle docHandle(XMLCustomProperties[gameObjectType]);
	TiXmlElement *XMLNodeCustomProperties = docHandle.FirstChildElement().Element();

	return XMLNodeCustomProperties;
}

void XMLParser::parseLevel(const String& level)
{

	std::string fullLevelPath=LEVELS_PATH+level+".ogscene";

	XMLDoc= new TiXmlDocument(fullLevelPath.c_str());

	if (!XMLDoc->LoadFile()){
		Logger::getInstance()->log("[XMLParser] Error reading "+fullLevelPath);
	}

	// Validate the File
	TiXmlElement * XMLRoot = XMLDoc->RootElement();
	if( String( XMLRoot->Value()) != "OGITORSCENE"  ) {
		Logger::getInstance()->log( "[XMLParser] Error: Invalid .ogscene File. Missing <OGITORSCENE>" );
		delete XMLDoc;      
		return;
	}

	//Set XML Root node
	XMLRootNode=XMLRoot;

	// Parse all GameObjects' types and its custom properties file .ctp
	parseGameObjectTypes();

	// Process the scene
	parseLevelRoot(XMLRoot);

	addXMLNodeCustomProperties();

	// set GameObjects' names
	setNames();

}

void XMLParser::setNames()
{
	XMLGameObjectContainerIterator it;

	for(it = mXMLGameObjectContainer.begin(); it != mXMLGameObjectContainer.end(); it++)
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

void XMLParser::addXMLNodeCustomProperties()
{
	XMLGameObjectContainerIterator it;

	for(it = mXMLGameObjectContainer.begin(); it != mXMLGameObjectContainer.end(); it++)
	{
		it->second.XMLNodeCustomProperties=getXMLCustomProperties(it->second.gameObjectType);
	}
}

void XMLParser::parseLevelRoot(TiXmlElement *XMLNode)
{

	// Process the scene parameters
	String version = getAttrib(XMLNode, "version", "unknown");

	String message = "[XMLParser] Parsing ogScene file with version " + version;
	
	//Process scene elements
	parseElements(XMLNode);

}

void XMLParser::parseElements(TiXmlElement *XMLNode)
{
	TiXmlElement *pElement;

	// Process OBJECTs of selected type
	pElement = XMLNode->FirstChildElement("OBJECT");
	while(pElement)
	{
		parseElement(pElement);

		pElement = pElement->NextSiblingElement("OBJECT");
	}
}

TiXmlElement * XMLParser::findNode(const std::string& nodeName)
{
	TiXmlElement *pElement;
	String name;
	String type;
	bool found=false;

	// Find the OBJECT node which contains the trajectoryNode with trajectoryNodeName
	pElement = XMLRootNode->FirstChildElement("OBJECT");
	while(pElement)
	{
		name = getAttrib(pElement, "name");
		type = getAttrib(pElement, "typename");

		if(type.compare("Marker Object")==0 && name.compare(nodeName)==0)
		{
			return pElement;
		}

		pElement = pElement->NextSiblingElement("OBJECT");
	}

	if(!found)
	{
		throw "trajectory node "+nodeName+" not found";
	}
	return NULL;
}

void XMLParser::parseWalkabilityMap(TiXmlElement *XMLWalkabilityMap)
{
	int i;
	std::string currentWalkabilityMapNode;
	String walkabilityMapName;

	//Get trajectory name
	walkabilityMapName = getPropertyString(XMLWalkabilityMap,"walkability map::name",false);

 	try
	{
		mXMLWalkabilityMapContainer[walkabilityMapName].name=walkabilityMapName;

		//process all Trajectory Nodes
		i=0;
		while(true)
		{
			//Process Trajectory Node

			//get current trajectory node
			currentWalkabilityMapNode=getPropertyString(XMLWalkabilityMap,"walkability map::node#"+StringConverter::toString(i),false);

			//if there is no more nodes we end
			if(currentWalkabilityMapNode.compare("")==0) break;

			//find current trajectory node
			mXMLWalkabilityMapContainer[walkabilityMapName].walkabilityMapNodes.push_back(findNode(currentWalkabilityMapNode));

			i++;
		}
	}
	catch( std::string error )
	{
		Logger::getInstance()->log("[XMLParser] Error parsing walkablity map "+walkabilityMapName+": "+error);	
		return;
	}
}

void XMLParser::parseTrajectory(TiXmlElement *XMLTrajectoryStartNode)
{
	int i;
	std::string currentTrajectoryNode;
	String trajectoryName;

	//Get trajectory name
	trajectoryName = getPropertyString(XMLTrajectoryStartNode,"trajectory::name",false);

 	try
	{
		mXMLTrajectoryContainer[trajectoryName].name=trajectoryName;

		//process all Trajectory Nodes
		i=0;
		while(true)
		{
			//Process Trajectory Node

			//get current trajectory node
			currentTrajectoryNode=getPropertyString(XMLTrajectoryStartNode,"trajectory::node#"+StringConverter::toString(i),false);

			//if there is no more nodes we end
			if(currentTrajectoryNode.compare("")==0) break;

			//find current trajectory node
			mXMLTrajectoryContainer[trajectoryName].mTrajectoryNodes.push_back(findNode(currentTrajectoryNode));

			i++;
		}


	}
	catch( std::string error )
	{
		Logger::getInstance()->log("[XMLParser] Error parsing trajectory "+trajectoryName+": "+error);	
		return;
	}
}

void XMLParser::parseElement(TiXmlElement *XMLNode)
{
	unsigned int i;
	bool found=false;

	String name = getAttrib(XMLNode, "name");
	String type = getAttrib(XMLNode, "typename");
	String parentNode= getAttrib(XMLNode,"parentnode");
	String gameObjectType;

	if(type.compare("Marker Object")==0)
	{
		//Parse Trajectory
		String trajectoryName = getPropertyString(XMLNode,"trajectory::name",false);
		if(trajectoryName.compare("")!=0)
		{
			//Trajectory start node
			parseTrajectory(XMLNode);
			//check if it's a camera trajectory
			if(parentNode.compare(OGITOR_CAMERA_TRAJECTORY_NODE)==0)
			{
				mCameraTrajectoryNames.push_back(trajectoryName);
			}
		}

		//Parse Trajectory
		String walkabilityMapName = getPropertyString(XMLNode,"walkability map::name",false);
		if(walkabilityMapName.compare("")!=0)
		{
			//Trajectory start node
			parseWalkabilityMap(XMLNode);
		}

		//Parse Sound
		if (name.substr(0,GAME_OBJECT_TYPE_SOUND.length()).compare(GAME_OBJECT_TYPE_SOUND)==0)
		{
			addXMLGameObjectNode(name,GAME_OBJECT_TYPE_SOUND,XMLNode);
		}

		return;
	}
	else if(type.compare("Node Object")==0)
	{
		//Node Object
		XMLSceneNode node;
		node.name=name;
		node.XMLNode=XMLNode;
		mXMLSceneNodeContainer.push_back(node);
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
		//Logger::getInstance()->log("[XMLParser] Game Object "+gameObjectType);
		addXMLGameObjectNode(name,gameObjectType,XMLNode);
	}
	else
	{
		Logger::getInstance()->log("[XMLParser] Game Object "+name+" has unrecognised Game Object Type");
	}
}

void XMLParser::addXMLGameObjectNode(const std::string& worldName, const std::string& gameObjectType,TiXmlElement *XMLNode)
{
	std::string baseName;

	//special cases
	if(gameObjectType.compare(GAME_OBJECT_TYPE_SCENE)==0)
	{
		baseName=worldName;
		mXMLGameObjectContainer[baseName].name=baseName;
		mXMLGameObjectContainer[baseName].gameObjectType=gameObjectType;

		mXMLGameObjectContainer[baseName].XMLNodeDreams=XMLNode;
	}
	else if(gameObjectType.compare(GAME_OBJECT_TYPE_VIEWPORT)==0)
	{
		baseName=worldName;
		mXMLGameObjectContainer[baseName].name=baseName;
		mXMLGameObjectContainer[baseName].gameObjectType=gameObjectType;

		mXMLGameObjectContainer[baseName].XMLNodeDreams=XMLNode;
	}
	else if(gameObjectType.compare(GAME_OBJECT_TYPE_CAMERA)==0)
	{
		baseName=worldName;
		mXMLGameObjectContainer[baseName].name=baseName;
		mXMLGameObjectContainer[baseName].gameObjectType=gameObjectType;

		mXMLGameObjectContainer[baseName].XMLNodeDreams=XMLNode;
	}
	//default case
	else
	{
		baseName=getBaseName(worldName,gameObjectType);

		mXMLGameObjectContainer[baseName].name=baseName;
		mXMLGameObjectContainer[baseName].gameObjectType=gameObjectType;

		if(isDreams(worldName,gameObjectType))
		{
			mXMLGameObjectContainer[baseName].XMLNodeDreams=XMLNode;
		}
		else if(isNightmares(worldName,gameObjectType))
		{
			mXMLGameObjectContainer[baseName].XMLNodeNightmares=XMLNode;
		}
	}
}

bool XMLParser::isDreams(const std::string& worldName,const std::string& gameObjectType)
{
	return 	worldName[gameObjectType.size()+1]=='d';
}

bool XMLParser::isNightmares(const std::string& worldName,const std::string& gameObjectType)
{
	return 	worldName[gameObjectType.size()+1]=='n';
}

std::string XMLParser::getBaseName(const std::string& worldName, const std::string& gameObjectType)
{
	std::string baseName;

	baseName=gameObjectType+worldName.substr(gameObjectType.size()+2,worldName.size()-gameObjectType.size()+2);

	return	baseName;
}		

std::string XMLParser::getNightmaresName(const std::string& baseName,const std::string& gameObjectType)
{
	std::string nightmaresName;

	nightmaresName=gameObjectType+"_n"+baseName.substr(gameObjectType.size(),baseName.size()-gameObjectType.size());

	return	nightmaresName;
}
std::string XMLParser::getDreamsName(const std::string& baseName,const std::string & gameObjectType)
{
	std::string dreamsName;

	dreamsName=gameObjectType+"_d"+baseName.substr(gameObjectType.size(),baseName.size()-gameObjectType.size());

	return	dreamsName;
}

String XMLParser::getAttrib(TiXmlElement *XMLNode, const String &attrib, const String &defaultValue)
{
	if(XMLNode->Attribute(attrib.c_str()))
		return XMLNode->Attribute(attrib.c_str());
	else
		return defaultValue;
}

String XMLParser::getPropertyString(TiXmlElement *XMLNode, const String &attrib_name, bool logErrors)
{
	TiXmlElement *pElement;
	TiXmlElement *XMLNodeCustomProperties;
	String propertyName;
	String result="";
	bool found=false;

	if(!XMLNode)
	{
		throw std::string("Missing XML Node!");
	}
	else
	{

		// Process all PROPERTY of the XML node
		pElement = XMLNode->FirstChildElement("PROPERTY");
		while(pElement)
		{
			propertyName = getAttrib(pElement, "id");

			//Logger::getInstance()->log("[LevelLoader] parsing "+propertyName+" property!");

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

				//Logger::getInstance()->log("[LevelLoader] parsing "+propertyName+" property!");

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
			if(logErrors)
			{
				throw std::string("Error parsing "+attrib_name+" attribute!");
			}
		}
	}
	return result;
}

