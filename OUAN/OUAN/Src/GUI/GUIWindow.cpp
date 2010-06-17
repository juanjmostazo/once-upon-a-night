#include "OUAN_Precompiled.h"

#include "GUIWindow.h"
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

void GUIWindow::setStrings(const std::string &language)
{

}