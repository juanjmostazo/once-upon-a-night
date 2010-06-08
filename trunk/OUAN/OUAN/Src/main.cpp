#include "OUAN_Precompiled.h"

#include "Application.h"

// ----------------------------------------------------------------------------
// Main function, just boots the application object
// ----------------------------------------------------------------------------

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
	try
	{
		int nArgs;
		char** cmdLine;

		nArgs=__argc;
		cmdLine=__argv;

		OUAN::ApplicationPtr app(new OUAN::Application());
		if (app->init(nArgs,cmdLine))
		{
			app->loadInitialState();
			app->go();
			app->cleanUp();		
		}
	}
	catch(Ogre::Exception& e)
	{
		MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}

	return 0;
}