#ifndef XMLSceneNodeH_H
#define XMLSceneNodeH_H

#include "../OUAN.h"

namespace OUAN
{

	class XMLSceneNode
	{
	public:
		XMLSceneNode();
		virtual ~XMLSceneNode();

		std::string name;
		TiXmlElement *XMLNode;
	};

}

#endif // XMLSceneNodeH_H
