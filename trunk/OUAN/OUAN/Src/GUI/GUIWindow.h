#ifndef GUIWINDOWH_H
#define GUIWINDOWH_H
#include "GUIDefs.h"
#include "../OUAN.h"
namespace OUAN
{
	const std::string CEGUIWIN_ID_CREDITS="OUANExtras/TempCreditsBox";
	const std::string STRING_KEY_CREDITS="EXTRAS_SCREEN_CREDITS";

	class GUIWindow
	{
	protected:
		std::string mLayoutName;
		CEGUI::Window* mSheet;
		/// Parent state
		GameStatePtr mParentGameState;

		void setGUIStrings(std::string windowNames[],int windowNamesLen);
	public:
		GUIWindow();
		virtual ~GUIWindow();
		virtual void init(const std::string& layoutName,CEGUI::Window* sheet);
		virtual void initGUI(GameStatePtr parentGameState);
		virtual void destroy();
		virtual void setStrings();
		CEGUI::Window* getSheet() const;
		void show();
		void hide();
	};
}
#endif