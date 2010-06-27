#include "OUAN_Precompiled.h"

#include "GUIMainMenu.h"
#include "GUISubsystem.h"
#include "../Core/MainMenuState.h"
#include "../Application.h"
using namespace OUAN;
void GUIMainMenu::initGUI(GameStatePtr parentGameState)
{
	GUIWindow::initGUI(parentGameState);
	mParentGameState->getApp()->getGUISubsystem()->bindEvent(CEGUI::PushButton::EventClicked,
		"OUANMainMenu/Quit",
		CEGUI::Event::Subscriber(&GUIMainMenu::onQuit,this));

	mParentGameState->getApp()->getGUISubsystem()->bindEvent(CEGUI::PushButton::EventClicked,
		"OUANMainMenu/Play",
		CEGUI::Event::Subscriber(&GUIMainMenu::onPlay,this));

	mParentGameState->getApp()->getGUISubsystem()->bindEvent(CEGUI::PushButton::EventClicked,
		"OUANMainMenu/Options",
		CEGUI::Event::Subscriber(&GUIMainMenu::onOptions,this));
	mParentGameState->getApp()->getGUISubsystem()->bindEvent(CEGUI::PushButton::EventClicked,
		"OUANMainMenu/Extras",
		CEGUI::Event::Subscriber(&GUIMainMenu::onExtras,this));

	ConfigurationPtr config = ConfigurationPtr(new Configuration());
	setStrings(parentGameState->getApp()->getCurrentLanguage());
}
bool GUIMainMenu::onPlay(const CEGUI::EventArgs& args)
{
	(static_cast<MainMenuState*>(mParentGameState.get()))->gotoPlay();
	return true;
}
bool GUIMainMenu::onOptions(const CEGUI::EventArgs& args)
{
	(static_cast<MainMenuState*>(mParentGameState.get()))->gotoOptions();
	return true;
}
bool GUIMainMenu::onExtras (const CEGUI::EventArgs& args)
{
	(static_cast<MainMenuState*>(mParentGameState.get()))->gotoExtras();
		return true;
}
bool GUIMainMenu::onQuit(const CEGUI::EventArgs& args)
{
	(static_cast<MainMenuState*>(mParentGameState.get()))->quit();
	return true;
}
void GUIMainMenu::setStrings(const std::string& language)
{
	ConfigurationPtr texts=mParentGameState->getApp()->getMenusTextStrings();
	if (texts.get())
	{

		std::string windowNames[] = {MAINMENU_CEGUIWIN_ID_PLAY,MAINMENU_CEGUIWIN_ID_OPTIONS,
			MAINMENU_CEGUIWIN_ID_EXTRAS,MAINMENU_CEGUIWIN_ID_EXIT};
		std::string defaultValues[]={"MAINMENU_SCREEN_PLAY","MAINMENU_SCREEN_OPTIONS",
			"MAINMENU_SCREEN_EXTRAS","MAINMENU_SCREEN_QUIT"};
		int windowNamesLen=4;
		std::string stringKey="";
		std::string stringVal="";
		CEGUI::Window* win=NULL;
		for (int i=0;i<windowNamesLen;i++)
		{
			win=CEGUI::WindowManager::getSingletonPtr()->getWindow(windowNames[i]);
			if (win)
			{
				stringVal="";
				stringKey=win->getText().c_str();
				texts->getOption(stringKey,stringVal);
				if (stringVal.empty())
				{
					texts->getOption(defaultValues[i],stringVal);
				}
				win->setText(stringVal);
			}
		}
	}	 
}