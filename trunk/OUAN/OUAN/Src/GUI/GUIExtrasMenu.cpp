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
}
void GUIExtrasMenu::bindEvents()
{
	mParentGameState->getApp()->getGUISubsystem()->bindEvent(CEGUI::PushButton::EventClicked,
		"OUANExtras/Back",
		CEGUI::Event::Subscriber(&GUIExtrasMenu::onBackToMenu,this));
}
bool GUIExtrasMenu::onBackToMenu(const CEGUI::EventArgs& args)
{
	(static_cast<ExtrasState*>(mParentGameState.get()))->backToMenu();
	return true;
}
	