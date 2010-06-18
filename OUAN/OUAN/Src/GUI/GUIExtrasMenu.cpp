#include "OUAN_Precompiled.h"

#include "GUIExtrasMenu.h"
#include "GUISubsystem.h"
#include "../Core/ExtrasState.h"
#include "../Application.h"
using namespace OUAN;
void GUIExtrasMenu::initGUI(GameStatePtr parentGameState)
{
	GUIWindow::initGUI(parentGameState);
	bindEvents();
	setStrings(parentGameState->getApp()->getCurrentLanguage());
}
void GUIExtrasMenu::bindEvents()
{
	mParentGameState->getApp()->getGUISubsystem()->bindEvent(CEGUI::PushButton::EventClicked,
		CEGUIWIN_ID_BACK,
		CEGUI::Event::Subscriber(&GUIExtrasMenu::onBackToMenu,this));
}
bool GUIExtrasMenu::onBackToMenu(const CEGUI::EventArgs& args)
{
	(static_cast<ExtrasState*>(mParentGameState.get()))->backToMenu();
	return true;
}
void GUIExtrasMenu::setStrings(const std::string& language)
{
	ConfigurationPtr texts=mParentGameState->getApp()->getMenusTextStrings();
	if (texts.get())
	{

		std::string windowNames[] = {CEGUIWIN_ID_BACK,CEGUIWIN_ID_LABEL,CEGUIWIN_ID_CREDITS};
		int windowNamesLen=3;
		std::string stringKey="";
		std::string stringVal="";
		CEGUI::Window* win=NULL;
		for (int i=0;i<windowNamesLen;i++)
		{
			win=CEGUI::WindowManager::getSingletonPtr()->getWindow(windowNames[i]);
			if (win)
			{
				stringKey=win->getText().c_str();
				// Horrible hack to get the credits edit box to display text correctly
				// For some mysterious reason, the read value from getText() doesn't compare to
				// the expected value when read from a MultilineEditBox (even though the documentation
				// states that getText may be used as well @_@)
				if (windowNames[i].compare(CEGUIWIN_ID_CREDITS)==0)				
					stringKey=STRING_KEY_CREDITS;
				texts->getOption(stringKey,stringVal);
				win->setText(stringVal);
			}
		}
	}	 
}