# Code example #
The method GUISubsystem::createGUI() returns a shared pointer to a GUIWindow base class.

If we want to downcast that pointer to a smart pointer to an instance of a subclass, we need to use boost::dynamic\_pointer\_cast. The way to achieve this would be:

```
mGUI = boost::dynamic_pointer_cast<GUIConsole>(mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_CONSOLE));
```

UPDATE: On our project, a convenience macro has been defined to improve readability. From now on, the use of BOOST\_PTR\_CAST(Type, variable) is advised.

The previous example would, therefore, be changed to:

```
mGUI = BOOST_PTR_CAST(GUIConsole,mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_CONSOLE));
```