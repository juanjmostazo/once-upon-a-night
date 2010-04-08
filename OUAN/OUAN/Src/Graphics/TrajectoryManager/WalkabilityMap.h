#ifndef WalkabilityMapH_H
#define WalkabilityMapH_H

#include "../../OUAN.h"

namespace OUAN
{
	class WalkabilityMap
	{
	private:


	public:

		WalkabilityMap();
		~WalkabilityMap();


	};

	class TWalkabilityMapParameters
	{
	public:
		TWalkabilityMapParameters();
		~TWalkabilityMapParameters();

		String name;
		std::vector<TWalkabilityMapNodeParameters> walkabilityNodes;
	};

	class TWalkabilityMapNodeParameters
	{
	public:
		TWalkabilityMapNodeParameters();
		~TWalkabilityMapNodeParameters();

		std::vector<String> neighbors;
	};


}

#endif