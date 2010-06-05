#ifndef GUIINGAMEH_H
#define GUIINGAMEH_H
#include "GUIDefs.h"
#include "GUIWindow.h"
#include "../OUAN.h"
namespace OUAN{
	class GUIInGame: public GUIWindow
	{
	public:
		void bindEvents();
		bool onBackToGame (const CEGUI::EventArgs& args);
		bool onOptions(const CEGUI::EventArgs& args);
		bool onBackToMenu(const CEGUI::EventArgs& args);
		bool onQuit(const CEGUI::EventArgs& args);

		void initGUI(GameStatePtr parentGameState);

	};
}
#endif