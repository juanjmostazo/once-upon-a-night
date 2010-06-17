#ifndef GUIINGAMEH_H
#define GUIINGAMEH_H
#include "GUIDefs.h"
#include "GUIWindow.h"
#include "../OUAN.h"
namespace OUAN{
	const std::string INGAME_STRING_KEY_BTG="INGAME_MENU_SCREEN_BTG";
	const std::string INGAME_STRING_KEY_BTM="INGAME_MENU_SCREEN_BTM";
	const std::string INGAME_STRING_KEY_EXIT="INGAME_MENU_SCREEN_EXIT";
	const std::string INGAME_STRING_KEY_OPTIONS="INGAME_MENU_SCREEN_OPTIONS";

	const std::string INGAME_CEGUIWIN_ID_BTG="OUANInGameMenu/Return";
	const std::string INGAME_CEGUIWIN_ID_BTM="OUANInGameMenu/GameQuit";
	const std::string INGAME_CEGUIWIN_ID_EXIT="OUANInGameMenu/AppQuit";
	const std::string INGAME_CEGUIWIN_ID_OPTIONS="OUANInGameMenu/Options";
	class GUIInGame: public GUIWindow
	{
	public:
		void bindEvents();
		bool onBackToGame (const CEGUI::EventArgs& args);
		bool onOptions(const CEGUI::EventArgs& args);
		bool onBackToMenu(const CEGUI::EventArgs& args);
		bool onQuit(const CEGUI::EventArgs& args);

		void initGUI(GameStatePtr parentGameState);

		void setStrings(const std::string& language);

	};
}
#endif