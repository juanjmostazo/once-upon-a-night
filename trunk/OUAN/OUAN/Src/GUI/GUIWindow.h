#ifndef GUIWINDOWH_H
#define GUIWINDOWH_H
#include <cegui/CEGUI.h>
class GUIWindow
{
private:
	std::string mLayoutName;
	CEGUI::Window* mSheet;
public:
	void init(const std::string& layoutName);
	void destroy();
	CEGUI::Window* getSheet() const;
};
#endif