#ifndef GUIWINDOWH_H
#define GUIWINDOWH_H
#include "GUIDefs.h"
#include "../OUAN.h"
namespace OUAN
{
	class GUIWindow
	{
	protected:
		std::string mLayoutName;
		CEGUI::Window* mSheet;
		/// Parent state
		GameStatePtr mParentGameState;
	public:
		GUIWindow();
		virtual ~GUIWindow();
		virtual void init(const std::string& layoutName,CEGUI::Window* sheet);
		virtual void initGUI(GameStatePtr parentGameState);
		virtual void destroy();
		virtual void setStrings(const std::string& language);
		CEGUI::Window* getSheet() const;
		void show();
		void hide();
	};
}
#endif