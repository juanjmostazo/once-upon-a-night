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

		std::string mTexture3DName;
		double mVCut;
		double mVScale;

		double mInitColorR;
		double mInitColorG;
		double mInitColorB;
		double mEndColorR;
		double mEndColorG;
		double mEndColorB;

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