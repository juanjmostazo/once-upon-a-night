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