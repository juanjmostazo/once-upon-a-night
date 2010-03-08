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

	};

}

#endif // XMLGAMEOBJECTH_H
