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
	setStrings();
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
void GUIExtrasMenu::setStrings()
{
	std::string windowNames[] = {CEGUIWIN_ID_BACK,CEGUIWIN_ID_LABEL,CEGUIWIN_ID_CREDITS};
	int windowNamesLen=3;
	setGUIStrings(windowNames,windowNamesLen);
}