#include "OUAN_Precompiled.h"

#include "GUIWindow.h"
#include "../Application.h"
#include "../Loader/Configuration.h"
#include "../Core/GameState.h"
using namespace OUAN;
GUIWindow::GUIWindow()
:mSheet(NULL)
{
}
GUIWindow::~GUIWindow()
{
	// we don't own the window, so we can't delete it
	mSheet=NULL;
}
void GUIWindow::init(const std::string& layoutName,CEGUI::Window* sheet)
{
	mLayoutName=layoutName;
	mSheet=sheet;
}
void GUIWindow::destroy()
{
	mSheet=NULL;
}
CEGUI::Window* GUIWindow::getSheet() const
{
	return mSheet;
}
void GUIWindow::initGUI(GameStatePtr parentGameState)
{
	mParentGameState=parentGameState;
}
void GUIWindow::show()
{
	if (mSheet)
		mSheet->show();
}
void GUIWindow::hide()
{
	if (mSheet)
		mSheet->hide();
}
void GUIWindow::setStrings()
{

}

void GUIWindow::setGUIStrings(std::string windowNames[],int windowNamesLen)
{
	ConfigurationPtr texts=mParentGameState->getApp()->getMenusTextStrings();
	if (texts.get())
	{		
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