#ifndef WorldNameConverterH_H
#define WorldNameConverterH_H

#include "../OUAN.h"

namespace OUAN
{
	class WorldNameConverter
	{
	private:

	protected:

	public:
		//Constructor
		WorldNameConverter();
		//Destructor
		~WorldNameConverter();

		static std::string getBaseName(std::string name);
		static std::string getDreamsName(std::string name);
		static std::string getNightmaresName(std::string name);
		static std::string getChangeWorldName(std::string name);
	};
}
#endif