#ifndef GUIDEFSH_H
#define GUIDEFSH_H
#include <boost/shared_ptr.hpp>
#include <cegui/CEGUI.h>
#include <OgreCEGUIRenderer.h>
namespace OUAN
{
	//-------------------------------------
	//	GUI module-related constants, type definitions and forwarded declarations
	//-------------------------------------
	class GUISubsystem;
	typedef boost::shared_ptr<GUISubsystem> GUISubsystemPtr;
	class GUIWindow;
	typedef boost::shared_ptr<GUIWindow> GUIWindowPtr;

	class GUIOptionsMenu;
	typedef boost::shared_ptr<GUIOptionsMenu> GUIOptionsMenuPtr;

	class GUIMainMenu;
	typedef boost::shared_ptr<GUIMainMenu> GUIMainMenuPtr;
	class GUIExtrasMenu;
	typedef boost::shared_ptr<GUIExtrasMenu> GUIExtrasMenuPtr;
	class GUIConsole;
	typedef boost::shared_ptr<GUIConsole> GUIConsolePtr;

	class GUIInGame;
	typedef boost::shared_ptr<GUIInGame> GUIInGamePtr;

	/// Keyboard event types
	typedef enum{
		GUI_KEYDOWN,
		GUI_KEYUP,
	} TGUIKeyboardEvent;

	/// Mouse event types ([TODO - Incomplete: Mouse wheel events should be added as well]
	typedef enum{
		GUI_MOUSEDOWN,
		GUI_MOUSEUP,
		GUI_MOUSEMOVE,
	} TGUIMouseEvent;
	const std::string GUI_LAYOUT_OPTIONS="OUAN_OptionsMenu.layout";
	const std::string GUI_LAYOUT_MAINMENU="OUAN_MainMenu.layout";
	const std::string GUI_LAYOUT_EXTRAS="OUAN_ExtrasMenu.layout";
	const std::string GUI_LAYOUT_CONSOLE="OUAN_Console.layout";
	const std::string GUI_LAYOUT_INGAMEMENU="OUAN_InGameMenu.layout";
}
#endif