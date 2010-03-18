#ifndef GUICONSOLEH_H
#define GUICONSOLEH_H
#include "GUIDefs.h"
#include "GUIWindow.h"
namespace OUAN
{

	const double LOG_REFRESH_TIME=2; //IN SECONDS
	const std::string LOG_NAME="Ogre.log"; //Research Ogre::LogListener class
	const int CONSOLE_MAX_LINES=50;

	class GUIConsole: public GUIWindow
	{
	private:
		double mNextLogRefresh;
	public:
		void initGUI(GameStatePtr parentGameState);
		bool onConsoleCloseClicked(const CEGUI::EventArgs& args);

		void hideConsole();
		void showConsole();
		void setConsoleVisibility(bool visible);
		bool isVisible();
		void update(double elapsedSeconds);
		void updateLog();
	};
}
#endif