#ifndef GUIEXTRASMENUH_H
#define GUIEXTRASMENUH_H
#include "GUIDefs.h"
#include "GUIWindow.h"
#include "../OUAN.h"
namespace OUAN{
	const std::string STRING_KEY_LABEL="EXTRAS_SCREEN_LABEL";
	const std::string STRING_KEY_BACK="EXTRAS_SCREEN_BACK";

	const std::string CEGUIWIN_ID_LABEL="OUANExtras/CreditLabel";
	const std::string CEGUIWIN_ID_BACK="OUANExtras/Back";

	class GUIExtrasMenu: public GUIWindow
	{
		public:
			void bindEvents();
			bool onBackToMenu(const CEGUI::EventArgs& args);
			void initGUI(GameStatePtr parentGameState);
			void setStrings();

	};
}
#endif