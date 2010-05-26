#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include "../../OUAN.h"

namespace OUAN
{
	class BufferManager
	{
	private:
		BufferManager();
		static BufferManager* mInstance;

		std::string mTexture3DName_1;
		std::string mTexture3DName_2;

	public:
		~BufferManager();
		static BufferManager* getInstance();

		void setBuffer(
			std::string texture3DName, double vCut, double vScale, 
			double juliaGlobalReal, double juliaGlobalImag, double juliaGlobalTheta,
			double initColorR, double initColorG, double initColorB,
			double endColorR, double endColorG, double endColorB);
	};
}

#endif