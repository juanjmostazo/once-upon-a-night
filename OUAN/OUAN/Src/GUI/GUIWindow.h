#ifndef GUIWINDOWH_H
#define GUIWINDOWH_H
#include "GUIDefs.h"
namespace OUAN
{
	class GUIWindow
	{
	protected:
		std::string mLayoutName;
		CEGUI::Window* mSheet;
	public:
		GUIWindow();
		virtual ~GUIWindow();
		virtual void init(const std::string& layoutName,CEGUI::Window* sheet);
		virtual void destroy();
		CEGUI::Window* getSheet() const;
	};
}
#endif