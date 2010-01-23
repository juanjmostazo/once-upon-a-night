//
#include "Configuration.h"

#include "tinyxml.h"
#include <iostream>


Configuration::Configuration()
{
	configMap.clear();
}

Configuration::~Configuration()
{
}

bool Configuration::loadFromFile(const std::string& fileName, unsigned int flags)
{
	TiXmlDocument doc(fileName.c_str());
	if (!doc.LoadFile()){
		return  false; //Let the client of this class handle this
	} 

	TiXmlHandle docHandle(&doc);
	TiXmlElement* elementPtr= docHandle.FirstChildElement().Element();
	if(!elementPtr) return false;
	
	std::string elemName = elementPtr->Value();
	TiXmlHandle rootHandle(elementPtr);
	
	configMap.clear();

	for (elementPtr=rootHandle.FirstChild("Options").FirstChild().Element();elementPtr!=NULL;
			elementPtr=elementPtr->NextSiblingElement())
	{
		if(elementPtr->Attribute("key"))
		{
			std::string key=elementPtr->Attribute("key");
			std::string value=elementPtr->GetText();
			configMap[key]=value;
		}
	}

	return true;
}
bool Configuration::saveToFile(const std::string& fileName, unsigned int flags) const
{	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	doc.LinkEndChild( decl ); 

	TiXmlElement * root = new TiXmlElement("Configuration");  
	doc.LinkEndChild( root );  

	TiXmlComment * comment = new TiXmlComment();
	std::string s="Config options";
	comment->SetValue(s.c_str());  
	root->LinkEndChild( comment ); 

	TiXmlElement * optionsNode = new TiXmlElement("Options");  
	root->LinkEndChild( optionsNode);

	for (TConfigMapConstIterator iter=configMap.begin(); iter != configMap.end(); ++iter)
	{
		TiXmlElement * option = new TiXmlElement( "Option" );  
		option->SetAttribute("key", iter->first.c_str());
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
	else return false;

}
void Configuration::setOption (const std::string& key, const std::string& value, bool replaceExisting)
{
	if (!hasOption(key) || replaceExisting)
		configMap [key]=value;
}

TConfigMapConstIterator  Configuration::begin() const
{
	return configMap.begin();
}
TConfigMapConstIterator Configuration::end() const
{
	return configMap.end();
}