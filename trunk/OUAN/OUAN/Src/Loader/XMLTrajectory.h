#ifndef XMLTRAJECTORYH_H
#define XMLTRAJECTORYH_H

#include "../OUAN.h"

namespace OUAN
{

	class XMLTrajectory
	{
	public:
		XMLTrajectory();
		virtual ~XMLTrajectory();

		std::string name;
		std::vector<TiXmlElement *> mTrajectoryNodes;

	};

}

#endif // XMLTRAJECTORYH_H
