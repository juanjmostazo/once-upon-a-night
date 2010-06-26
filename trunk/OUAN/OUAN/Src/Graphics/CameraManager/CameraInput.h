#ifndef CameraInputH_H
#define CameraInputH_H
#include "../../OUAN.h"
namespace OUAN
{
	class CameraInput
	{
	private:
		void loadConfig();
	public:

		CameraInput();
		~CameraInput();

		CameraParametersPtr mCameraParameters;

		Ogre::Vector2 mRotation;
		Ogre::Vector3 mTranslation;



	};


}

#endif