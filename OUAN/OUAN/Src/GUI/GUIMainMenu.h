#ifndef GUIMAINMENUH_H
#define GUIMAINMENUH_H
#include "GUIWindow.h"
namespace OUAN
{
	class GUIMainMenu: public GUIWindow
	{
	public:
		void initGUI(GameStatePtr parentGameState);
		bool onPlay(const CEGUI::EventArgs& args);	
		bool onOptions(const CEGUI::EventArgs& args);
		bool onExtras (const CEGUI::EventArgs& args);
		bool onQuit(const CEGUI::EventArgs& args);

	};
}
#endif