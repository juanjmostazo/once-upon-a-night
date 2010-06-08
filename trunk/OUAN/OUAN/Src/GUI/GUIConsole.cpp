#include "OUAN_Precompiled.h"

#include "GUIConsole.h"
#include "GUISubsystem.h"
#include "../Core/GameRunningState.h"
#include "../Application.h"
using namespace OUAN;
void GUIConsole::initGUI(GameStatePtr parentGameState)
{
	GUIWindow::initGUI(parentGameState);
	mParentGameState->getApp()->getGUISubsystem()->bindEvent(CEGUI::FrameWindow::EventCloseClicked,
		"OUAN/ConsoleWindow",
		CEGUI::Event::Subscriber(&GUIConsole::onConsoleCloseClicked,this));
	mNextLogRefresh=-1;
}
bool GUIConsole::onConsoleCloseClicked(const CEGUI::EventArgs& args)
{
	hideConsole();
	return true;
}
void GUIConsole::update(double elapsedSeconds)
{
	mNextLogRefresh-=elapsedSeconds;
	if (mNextLogRefresh<=0)
	{
		updateLog();
		mNextLogRefresh=LOG_REFRESH_TIME;
	}
}
void GUIConsole::updateLog()
{
	if (isVisible()){
		unsigned int nLines=CONSOLE_MAX_LINES;
		std::ifstream is(LOG_NAME.c_str()); 
		std::string line; 
		std::vector<std::string> lines; 
		while(getline(is, line)) 
		{ 
			lines.push_back(line); 
			if(lines.size() > nLines) 
				lines.erase(lines.begin()); 
		} 
		CEGUI::MultiLineEditbox* textField= static_cast<CEGUI::MultiLineEditbox*>(CEGUI::WindowManager::getSingletonPtr()->
			getWindow((CEGUI::utf8*)"OUAN/Console"));
		if (textField)
		{
			textField->setText("");
			std::string s;
			for (unsigned int i=0;i<lines.size();++i)
			{
				s.append(lines.at(i)+"\n");
			}
			textField->setText((CEGUI::utf8*)s.c_str());
			textField->setCaratIndex(textField->getText().length()-1);
		}
	}
}
void GUIConsole::hideConsole()
{
	setConsoleVisibility(false);
	mNextLogRefresh=-1;
	mParentGameState->getApp()->getGUISubsystem()->hideCursor();
}
void GUIConsole::showConsole()
{
	setConsoleVisibility(true);
	updateLog();
	mNextLogRefresh=LOG_REFRESH_TIME;
	mParentGameState->getApp()->getGUISubsystem()->showCursor();
}
void GUIConsole::setConsoleVisibility(bool visible)
{
	CEGUI::Window* console= CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)"OUAN/ConsoleWindow");
	if (console)
		console->setVisible(visible);
}
bool GUIConsole::isVisible()
{
	if (CEGUI::WindowManager::getSingletonPtr()->isWindowPresent((CEGUI::utf8*)"OUAN/ConsoleWindow"))
	{
		CEGUI::Window* console= CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)"OUAN/ConsoleWindow");
		return console && console->isVisible();
	}
	return false;
}