#ifndef GUIDEFSH_H
#define GUIDEFSH_H

namespace OUAN
{
	//-------------------------------------
	//	GUI module-related constants, type definitions and forwarded declarations
	//-------------------------------------
	CLASS_DECLARATIONS_NO_PARAMS(GUISubsystem);
	CLASS_DECLARATIONS_NO_PARAMS(GUIWindow);
	CLASS_DECLARATIONS_NO_PARAMS(GUIOptionsMenu);
	CLASS_DECLARATIONS_NO_PARAMS(GUIMainMenu);
	CLASS_DECLARATIONS_NO_PARAMS(GUIExtrasMenu);
	CLASS_DECLARATIONS_NO_PARAMS(GUIConsole);
	CLASS_DECLARATIONS_NO_PARAMS(GUIInGame);
	CLASS_DECLARATIONS_NO_PARAMS(GUIStoryBook);

	/// Keyboard event types
	typedef enum{
		GUI_KEYDOWN,
		GUI_KEYUP,
	} TGUIKeyboardEvent;

	/// Mouse event types
	typedef enum{
		GUI_MOUSEDOWN,
		GUI_MOUSEUP,
		GUI_MOUSEMOVE,
		GUI_MOUSEWHEEL_UP,
		GUI_MOUSEWHEEL_DOWN
	} TGUIMouseEvent;
	const std::string GUI_LAYOUT_OPTIONS="OUAN_OptionsMenu.layout";
	const std::string GUI_LAYOUT_MAINMENU="OUAN_MainMenu.layout";
	const std::string GUI_LAYOUT_EXTRAS="OUAN_ExtrasMenu.layout";
	const std::string GUI_LAYOUT_CONSOLE="OUAN_Console.layout";
	const std::string GUI_LAYOUT_INGAMEMENU="OUAN_InGameMenu.layout";
	const std::string GUI_LAYOUT_STORYBOOK="OUAN_Storybook.layout";
}
#endif