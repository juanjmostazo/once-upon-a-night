#ifndef JULIA_MANAGER_H
#define JULIA_MANAGER_H

#include "../../OUAN.h"
#include "Julia.h"

namespace OUAN
{
	class JuliaManager
	{
	private:
		JuliaManager();
		static JuliaManager* mInstance;
		
		Julia mJulia;
		double mLastGlobalReal;
		double mLastGlobalImag;
		double mLastGlobalTheta;

	public:
		~JuliaManager();
		static JuliaManager* getInstance();

		Julia getJulia(double globalReal, double globalImag, double globalTheta);
	};
}

#endif