#include "OUAN_Precompiled.h"

#include "XMLGameObject.h"

using namespace OUAN;

XMLGameObject::XMLGameObject()
{
	XMLNodeDreams=0;
	XMLNodeNightmares=0;
	XMLNodeCustomProperties=0;
}

XMLGameObject::~XMLGameObject()
{

}

TiXmlElement * XMLGameObject::getMainXMLNode()
{
	//Object exists both in dreams and nightmares
	if(XMLNodeDreams && XMLNodeNightmares)
	{
		//If it exists in both worlds we use Dreams parameters for render components
		return XMLNodeDreams;
	}
	//Object exists only in dreams
	else if(XMLNodeDreams && !XMLNodeNightmares)
	{
		return XMLNodeDreams;
	}
	//Object exists only in nightmares
	else if(!XMLNodeDreams && XMLNodeNightmares)
	{
		return XMLNodeNightmares;
	}
	else
	{
		return NULL;
	}
}