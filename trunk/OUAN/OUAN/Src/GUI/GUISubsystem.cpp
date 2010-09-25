#include "OUAN_Precompiled.h"

#include "GUISubsystem.h"
#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"

#include "GUIWindow.h"
#include "GUIOptionsMenu.h"
#include "GUIMainMenu.h"
#include "GUIConsole.h"
#include "GUIExtrasMenu.h"
#include "GUIInGame.h"
#include "GUIStorybook.h"

using namespace OUAN;
CEGUI::MouseButton OUAN::convertMouseButton(const OIS::MouseButtonID& buttonId)
{
	switch (buttonId)
	{
	case OIS::MB_Left:
		return CEGUI::LeftButton;

	case OIS::MB_Right:
		return CEGUI::RightButton;

	case OIS::MB_Middle:
		return CEGUI::MiddleButton;

	default:
		return CEGUI::LeftButton;
	}
}
void GUISubsystem::init(ApplicationPtr app)
{	
	mRenderer=new CEGUI::OgreCEGUIRenderer(app->getRenderSubsystem()->getWindow(),
		Ogre::RENDER_QUEUE_OVERLAY,false,3000,
		app->getRenderSubsystem()->getSceneManager());
	mSystem = new CEGUI::System(mRenderer);
	//TODO: Refine this method
	loadScheme("OUANLookSkin.scheme","OUANLook");
}
void GUISubsystem::loadScheme(std::string schemeName, std::string mouseCursor)
{
	try{
		if (!CEGUI::SchemeManager::getSingletonPtr()->isSchemePresent((CEGUI::utf8*)schemeName.c_str()))
			CEGUI::SchemeManager::getSingleton().loadScheme((CEGUI::utf8*)schemeName.c_str());
	}
	catch(CEGUI::AlreadyExistsException aece)
	{
		// This is already loaded, no need to do it again.
	}
	mSystem->setDefaultMouseCursor((CEGUI::utf8*)mouseCursor.c_str(), (CEGUI::utf8*)"MouseArrow");
	mSystem->setDefaultFont((CEGUI::utf8*)"BlueHighway-12");
}
void GUISubsystem::reset(ApplicationPtr app)
{
	cleanUp();
	init(app);
}
void GUISubsystem::clearRenderer()
{
	if (mRenderer)
	{
		mRenderer->setTargetSceneManager(NULL);
	}
}

void GUISubsystem::cleanUp()
{
	if (mSystem) delete mSystem;
	if (mRenderer) delete mRenderer;
}

void GUISubsystem::injectKeyInput(const TGUIKeyboardEvent& eventType, const OIS::KeyEvent& e)
{
	if (mSystem)
	{
		switch (eventType)
		{
		case GUI_KEYDOWN:
			mSystem->injectKeyDown(e.key);
			mSystem->injectChar(e.text);
			break;
		case GUI_KEYUP:
			mSystem->injectKeyUp(e.key);
			break;
		}

	}
}
void GUISubsystem::injectMouseInput(const TGUIMouseEvent& eventType, const OIS::MouseButtonID& buttonId, const OIS::MouseEvent& e)
{
	if(mSystem)
	{
		switch(eventType)
		{
		case GUI_MOUSEDOWN:
			mSystem->injectMouseButtonDown(convertMouseButton(buttonId));
			break;
		case GUI_MOUSEUP:
			mSystem->injectMouseButtonUp(convertMouseButton(buttonId));
			break;
		case GUI_MOUSEMOVE:
			mSystem->injectMouseMove(e.state.X.rel,e.state.Y.rel);
			break;
		}
	}
}
void GUISubsystem::injectTimePulse(float elapsed)
{
	if(mSystem)
		mSystem->injectTimePulse(elapsed);
}
GUIWindowPtr GUISubsystem::createGUI(const std::string& guiLayout)
{
	GUIWindowPtr ptr;
	if (!guiLayout.empty())
	{
		CEGUI::Window* sheet = CEGUI::WindowManager::getSingleton().loadWindowLayout(CEGUI::String(guiLayout));
		mSystem->setGUISheet(sheet);
		if (guiLayout.compare(GUI_LAYOUT_OPTIONS)==0)
			ptr.reset(new GUIOptionsMenu());
		else if (guiLayout.compare(GUI_LAYOUT_MAINMENU)==0)
			ptr.reset(new GUIMainMenu());
		else if (guiLayout.compare(GUI_LAYOUT_EXTRAS)==0)
			ptr.reset(new GUIExtrasMenu());
		else if (guiLayout.compare(GUI_LAYOUT_CONSOLE)==0)
			ptr.reset(new GUIConsole());
		else if (guiLayout.compare(GUI_LAYOUT_INGAMEMENU)==0)
			ptr.reset(new GUIInGame());
		else if (guiLayout.compare(GUI_LAYOUT_STORYBOOK)==0)
			ptr.reset(new GUIStoryBook());
		//Add more inits as needed
		else ptr.reset(new GUIWindow());
		ptr->init(guiLayout,sheet);
	}
	return ptr;
}
void GUISubsystem::destroyGUI()
{
	//WARNING: There may be a bug from CEGUI's version bundled with Ogre here. 
	//if an Unhandled Exception is thrown, consider updating to version 0.7
	CEGUI::System::getSingleton().getGUISheet()->destroy();
	CEGUI::System::getSingleton().setGUISheet(NULL);
}
void GUISubsystem::hideGUI()
{
	CEGUI::System::getSingleton().getGUISheet()->hide();
}
void GUISubsystem::showGUI()
{
	CEGUI::System::getSingleton().getGUISheet()->show();
}

void GUISubsystem::bindEvent(const CEGUI::String& eventName, const std::string& windowName,CEGUI::Event::Subscriber subscriber)
{
	CEGUI::WindowManager *wmgr = CEGUI::WindowManager::getSingletonPtr();
	CEGUI::Window *triggerWindow = wmgr->getWindow((CEGUI::utf8*)windowName.c_str());	
	triggerWindow->subscribeEvent(eventName,subscriber);
}
void GUISubsystem::setCursorVisibility(bool visible)
{
	CEGUI::MouseCursor::getSingleton().setVisible(visible);
}
void GUISubsystem::showCursor()
{
	CEGUI::MouseCursor::getSingleton().show();
}
void GUISubsystem::hideCursor()
{
	CEGUI::MouseCursor::getSingleton().hide();
}