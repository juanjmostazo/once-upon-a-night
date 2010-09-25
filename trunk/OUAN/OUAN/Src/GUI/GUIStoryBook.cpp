#include "OUAN_Precompiled.h"

#include "GUIStorybook.h"
#include "GUISubsystem.h"
#include "../Core/GameRunningState.h"
#include "../Application.h"
using namespace OUAN;
void GUIStoryBook::initGUI(GameStatePtr parentGameState)
{
	GUIWindow::initGUI(parentGameState);
	setStrings();
}

void GUIStoryBook::update(double elapsedSeconds)
{

}
void GUIStoryBook::hideBook()
{
	setBookVisibility(false);
}
void GUIStoryBook::showBook()
{
	setBookVisibility(true);
}
void GUIStoryBook::setBookVisibility(bool visible)
{
	CEGUI::Window* book= CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)"OUANStory/Background");
	if (book)
		book->setVisible(visible);
}
bool GUIStoryBook::isVisible()
{
	if (CEGUI::WindowManager::getSingletonPtr()->isWindowPresent((CEGUI::utf8*)"OUANStory/Background"))
	{
		CEGUI::Window* book= CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)"OUANStory/Background");
		return book && book->isVisible();
	}
	return false;
}

void GUIStoryBook::setPageText(int pageNumber,const std::string& text, bool readable)
{
	std::stringstream winNameStr;
	winNameStr<<CEGUIWIN_ID_PAGE_PREFIX<<pageNumber;
	CEGUI::Window* win=CEGUI::WindowManager::getSingletonPtr()->getWindow(winNameStr.str());
	if (win)
	{
		if (!readable)
			win->setFont(STORY_ENCRYPTED_FONT);
		win->setText(text);
	}
}

void GUIStoryBook::setStrings()
{
	std::string windowNames[] = {CEGUIWIN_ID_STORY_EXIT};
	int windowNamesLen=1;
	setGUIStrings(windowNames,windowNamesLen);
}