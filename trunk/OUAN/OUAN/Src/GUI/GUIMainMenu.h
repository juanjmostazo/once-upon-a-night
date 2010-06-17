#ifndef GUIMAINMENUH_H
#define GUIMAINMENUH_H
#include "GUIWindow.h"
namespace OUAN
{
	//Values to be read from the texts file
	const std::string MAINMENU_STRING_KEY_EXIT="MAINMENU_SCREEN_QUIT";
	const std::string MAINMENU_STRING_KEY_PLAY="MAINMENU_SCREEN_PLAY";
	const std::string MAINMENU_STRING_KEY_EXTRAS="MAINMENU_SCREEN_EXTRAS";
	const std::string MAINMENU_STRING_KEY_OPTIONS="MAINMENU_SCREEN_OPTIONS";
	//CEGUI identifiers
	const std::string MAINMENU_CEGUIWIN_ID_PLAY="OUANMainMenu/Play";
	const std::string MAINMENU_CEGUIWIN_ID_OPTIONS="OUANMainMenu/Options";
	const std::string MAINMENU_CEGUIWIN_ID_EXTRAS="OUANMainMenu/Extras";
	const std::string MAINMENU_CEGUIWIN_ID_EXIT="OUANMainMenu/Quit";		

	class GUIMainMenu: public GUIWindow
	{
	public:
		void initGUI(GameStatePtr parentGameState);
		bool onPlay(const CEGUI::EventArgs& args);	
		bool onOptions(const CEGUI::EventArgs& args);
		bool onExtras (const CEGUI::EventArgs& args);
		bool onQuit(const CEGUI::EventArgs& args);

		void setStrings(const std::string& language);

	};
}
#endif