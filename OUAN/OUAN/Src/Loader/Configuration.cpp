//
#include "Configuration.h"

#include "../TinyXML/tinyxml.h"
#include <iostream>

using namespace OUAN;

Configuration::Configuration()
{
	configMap.clear();
}

Configuration::~Configuration()
{
	configMap.clear();
}

bool Configuration::loadFromFile(const std::string& fileName, unsigned int flags)
{
	TiXmlDocument doc(fileName.c_str());
	if (!doc.LoadFile()){
		Ogre::LogManager::getSingleton().logMessage("ERROR! [Configuration] Error reading file "+fileName);
		return  false; //Let the client of this class handle this
	} 

	TiXmlHandle docHandle(&doc);
	TiXmlElement* elementPtr= docHandle.FirstChildElement().Element();
	if(!elementPtr) return false;
	
	std::string elemName = elementPtr->Value();
	TiXmlHandle rootHandle(elementPtr);
	
	configMap.clear();

	for (elementPtr=rootHandle.FirstChild(XML_ELEMENT_OPTIONS.c_str()).FirstChild(XML_ELEMENT_OPTION.c_str()).Element();elementPtr!=NULL;
			elementPtr=elementPtr->NextSiblingElement())
	{
		if(elementPtr->Attribute(XML_ELEMENT_OPTION_ATTRIBUTE_KEY.c_str()))
		{
			std::string key=elementPtr->Attribute(XML_ELEMENT_OPTION_ATTRIBUTE_KEY.c_str());
			std::string value=elementPtr->GetText();
			configMap[key]=value;
		}
	}

	return true;
}

bool Configuration::saveToFile(const std::string& fileName, unsigned int flags) const
{	
	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration(XML_DECLARATION_VERSION.c_str(), 
		XML_DECLARATION_ENCODING.c_str(), XML_DECLARATION_STANDALONE.c_str());  
	doc.LinkEndChild( decl ); 

	TiXmlElement * root = new TiXmlElement(XML_ELEMENT_ROOT.c_str());  
	doc.LinkEndChild( root );  

	TiXmlComment * comment = new TiXmlComment();
	std::string s=XML_COMMENT;
	comment->SetValue(s.c_str());  
	root->LinkEndChild( comment ); 

	TiXmlElement * optionsNode = new TiXmlElement(XML_ELEMENT_OPTIONS.c_str());  
	root->LinkEndChild( optionsNode);

	for (TConfigMapConstIterator iter=configMap.begin(); iter != configMap.end(); ++iter)
	{
		TiXmlElement * option = new TiXmlElement(XML_ELEMENT_OPTION.c_str());  
		option->SetAttribute(XML_ELEMENT_OPTION_ATTRIBUTE_KEY.c_str(), iter->first.c_str());
		option->LinkEndChild(new TiXmlText(iter->second.c_str()));
		optionsNode->LinkEndChild(option);  
	}
	doc.SaveFile(fileName.c_str());
	return true;
}

void Configuration::setMap(const TConfigMap& newMap)
{
	configMap=newMap;
}

void Configuration::addOptions(const TConfigMap& newMap, bool replaceExisting)
{
	for (TConfigMapConstIterator it=newMap.begin();it!=newMap.end();++it)
	{
		if (!hasOption(it->first) || replaceExisting) //Option already exists
			configMap[it->first]=it->second;
	}
}

bool Configuration::hasOption(const std::string& key) const
{
	return configMap.count(key)>0;
}
bool Configuration::getOption(const std::string& key, std::string& value)
{
	if (hasOption(key))
	{
		value=configMap[key];
		return true;
	}
	else
	{
		Ogre::LogManager::getSingleton().logMessage("ERROR! [Configuration] Error reading option "+key);
		return false;
	}

}
void Configuration::setOption (const std::string& key, const std::string& value, bool replaceExisting)
{
	if (!hasOption(key) || replaceExisting)
		configMap [key]=value;
}
std::string Configuration::operator[](const std::string& key)
{
	if (hasOption(key))
		return configMap[key];
	return "";
}

TConfigMapConstIterator  Configuration::begin() const
{
	return configMap.begin();
}

TConfigMapConstIterator Configuration::end() const
{
	return configMap.end();
}
bool Configuration::isEmpty() const
{
	return configMap.empty();
}
double Configuration::parseDouble(const std::string& key)
{
	std::string value;
	std::stringstream strm;
	getOption(key,value);
	double doubleVal;
	if (!value.empty())
	{
		strm.str(value);
		strm>>doubleVal;
		return doubleVal;
	}
	else throw std::exception("An error happened while parsing a double: Key wasn't found in the map, or its value is empty");
}
int Configuration::parseInt(const std::string& key)
{
	std::string value;
	std::stringstream strm;
	getOption(key,value);
	int intVal;
	if (!value.empty())
	{
		strm.str(value);
		strm>>intVal;
		return intVal;
	}
	else throw std::exception("An error happened while parsing an integer: Key wasn't found in the map, or its value is empty");
}
long Configuration::parseLong(const std::string& key)
{
	std::string value;
	std::stringstream strm;
	getOption(key,value);
	long longVal;
	if (!value.empty())
	{
		strm.str(value);
		strm>>longVal;
		return longVal;
	}
	else throw std::exception("An error happened while parsing a long: Key wasn't found in the map, or its value is empty");
}
float Configuration::parseFloat(const std::string& key)
{
	std::string value;
	std::stringstream strm;
	getOption(key,value);
	float floatVal;
	if (!value.empty())
	{
		strm.str(value);
		strm>>floatVal;
		return floatVal;
	}
	else throw std::exception("An error happened while parsing a float: Key wasn't found in the map, or its value is empty");
}
bool Configuration::parseBool(const std::string& key)
{
	std::string value;
	std::stringstream strm;
	getOption(key,value);
	bool boolVal;
	if (!value.empty())
	{
		strm.str(value);
		strm>>boolVal;
		return boolVal;
	}
	else throw std::exception("An error happened while parsing a bool: Key wasn't found in the map, or its value is empty");
}