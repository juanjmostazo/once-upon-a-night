#ifndef XMLGAMEOBJECTH_H
#define XMLGAMEOBJECTH_H

#include "../OUAN.h"

namespace OUAN
{
	class XMLGameObject
	{
	public:
		XMLGameObject();
		virtual ~XMLGameObject();

		std::string name;
		std::string dreamsName;
		std::string nightmaresName;
		std::string gameObjectType;
		TiXmlElement *XMLNodeDreams;
		TiXmlElement *XMLNodeNightmares;
		TiXmlElement *XMLNodeCustomProperties;

		//Returns gameObject->XMLDreamsNode if object exist both in dreams and nightmares, 
		//gameObject->XMLNightmaresNode if only exists on nightmares and  gameObject->XMLDreamsNode if only exists in dreams
		TiXmlElement * getMainXMLNode();
	};
}

#endif // XMLGAMEOBJECTH_H
