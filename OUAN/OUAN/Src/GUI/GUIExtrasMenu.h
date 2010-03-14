#ifndef GUIEXTRASMENUH_H
#define GUIEXTRASMENUH_H
#include "GUIDefs.h"
#include "GUIWindow.h"
#include "../OUAN.h"
namespace OUAN{
	class GUIExtrasMenu: public GUIWindow
	{
		public:
			void bindEvents();
			bool onBackToMenu(const CEGUI::EventArgs& args);
			void initGUI(GameStatePtr parentGameState);

	};
}
#endif