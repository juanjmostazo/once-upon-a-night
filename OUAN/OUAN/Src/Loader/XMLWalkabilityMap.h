#ifndef XMLWALKABILITYMAPH_H
#define XMLWALKABILITYMAPH_H

#include "../OUAN.h"

namespace OUAN
{

	class XMLWalkabilityMap
	{
	public:
		XMLWalkabilityMap();
		virtual ~XMLWalkabilityMap();

		std::string name;
		std::vector<TiXmlElement *> walkabilityMapNodes;

	};

}

#endif // XMLTRAJECTORYH_H
