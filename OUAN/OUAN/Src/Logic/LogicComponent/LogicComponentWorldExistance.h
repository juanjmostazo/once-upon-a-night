#ifndef LogicComponentWorldExistanceH_H
#define LogicComponentWorldExistanceH_H

#include "LogicComponent.h"

namespace OUAN
{
	class LogicComponentWorldExistance: public LogicComponent
	{
	private:
		/// Existance in each world
		bool existsInDreams;
		bool existsInNightmares;
	public:

		LogicComponentWorldExistance(const std::string& type="");
		~LogicComponentWorldExistance();

		bool getExistsInDreams() const;
		void setExistsInDreams(bool existsInDreams);

		bool getExistsInNightmares() const;
		void setExistsInNightmares(bool existsInNightmares);
	};

	class TLogicComponentWorldExistanceParameters: public TLogicComponentParameters
	{
	public:
		TLogicComponentWorldExistanceParameters();
		~TLogicComponentWorldExistanceParameters();

		/// Existance in each world
		bool existsInDreams;
		bool existsInNightmares;

	};

}

#endif