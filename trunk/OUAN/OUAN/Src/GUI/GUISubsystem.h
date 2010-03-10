#ifndef GUISUBSYSTEMH_H
#define GUISUBSYSTEMH_H
#include "../OUAN.h"
namespace OUAN
{
	/// Convert OIS' mouse button ID to its CEGUI equivalent
	/// @param buttonId	mouse button ID from OIS
	/// @return CEGUI's mouse button identifier
	CEGUI::MouseButton convertMouseButton(const OIS::MouseButtonID& buttonId);

	/// This class encapsulates the functionality
	/// of our game's GUI subsystem
	/// It uses Crazy Eddie's GUI System (http://www.cegui.org.uk),
	/// in particular the implementation of the GUI renderer that comes
	/// bundled with Ogre 1.6.5
	/// It might be more flexible to make this class abstract and then
	/// provide concrete classes, for each renderer (ogre, directx, etc)
	/// However, since we building a game, not an engine, we've opted to use
	/// the OgreCEGUIRenderer directly
	class GUISubsystem
	{
	private:
		///	GUI renderer, using Ogre's implementation
		CEGUI::OgreCEGUIRenderer* mRenderer;
		/// Pointer to CEGUI's main system object
		CEGUI::System* mSystem;
		//TGUIEventBindingVector mBoundEvents;
		//std::vector<CEGUI::Event::ScopedConnection> mConnections;
	public:
		/// init CEGUI
		/// @param app	the application
		void init(OUAN::ApplicationPtr app);
		/// Draw the GUI
		/// @param app	the application
		/// void renderGUI(OUAN::ApplicationPtr app);
		/// Free memory
		void cleanUp();
		/// Reset the GUI subsyste, typically in response
		/// to a render subsystem reset
		/// @param app the parent application
		void reset(ApplicationPtr app);

		/// Inject the input system's keyboard event data to CEGUI
		/// @param eventType	the specific type of key event (e.g keyDown, keyUp)
		/// @param e			keyboard event data
		void injectKeyInput(const TGUIKeyboardEvent& eventType, const OIS::KeyEvent& e);
		/// Inject the input system's mouse event data to CEGUI
		/// @param eventType	the specific type of mouse event (e.g mouseDown, mouseMove,...)
		/// @param buttonid		mouse of the button that triggered the event
		/// @param e			mouse event data
		void injectMouseInput(const TGUIMouseEvent& eventType, const OIS::MouseButtonID& buttonId, const OIS::MouseEvent& e);
		/// Inject the elapsed time in seconds since the last call
		/// @param elapsed	time in seconds since the last call;
		void injectTimePulse(float elapsed);
		
		//[TODO]void injectJoystickInput();

		/// Creates GUI from the given CEGUI layout
		/// @param guiLayout CEGUI layout
		void createGUI(const std::string& guiLayout);
		/// Destroys current GUI
		void destroyGUI();

		/// [TODO]Create GUI using a custom-built GUI creator object
		/// @param	guiCreator GUI creator object
		// void createGUI (const GUICreator* guiCreator);

		/// Bind the CEGUI event with the specified name to a subscriber method
		/// @param eventName	name of the GUI event to bind to
		/// @param windowName	name of the window that'll generate the event
		/// @param subscriber	callback object containing the function to handle the event
		void bindEvent(const CEGUI::String& eventName, const std::string& windowName, CEGUI::Event::Subscriber subscriber);

		//void unbindEvent(const CEGUI::String& eventName, const std::string& windowName);
		//void unbindAllEvents();

		/// init resource groups
		void initResourceGroups();

		void clearRenderer();

		void loadScheme(std::string schemeName, std::string mouseCursor);
	};
}
#endif