#ifndef UTILSH_H
#define UTILSH_H

#include <string>
#include <boost/random.hpp>
#include <boost/nondet_random.hpp>

namespace OUAN
{
	namespace Utils
	{
		const double DOUBLE_COMPARISON_DELTA=0.000001;
		class Random
		{
		private:
			boost::mt19937 mRandEngine;
			static Random* mInstance;
			Random();
		public:
			~Random();
			static Random* getInstance();
			void init(unsigned int seed);
			int getRandomInteger(int low, int high);
			double getRandomDouble(double low=0.0, double high=1.0);
		};

		void scriptLog (const std::string& logMsg);
		int parseInt(std::string& strValue);
	}
}
#endif