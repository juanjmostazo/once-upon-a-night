#ifndef GUISTORYBOOKH_H
#define GUISTORYBOOKH_H
#include "GUIDefs.h"
#include "GUIWindow.h"
namespace OUAN
{

	const std::string CEGUIWIN_ID_STORY_EXIT="OUANStory/Label";
	const std::string CEGUIWIN_ID_PAGE_PREFIX="OUANStory/Page";
	const std::string STORY_READABLE_FONT="book-14";
	const std::string STORY_ENCRYPTED_FONT="Telerin-10";

	class GUIStoryBook: public GUIWindow
	{
	public:
		void initGUI(GameStatePtr parentGameState);		

		void hideBook();
		void showBook();
		void setBookVisibility(bool visible);
		bool isVisible();
		void update(double elapsedSeconds);

		void setPageText(int pageNumber,const std::string& text, bool readable=true);
		void setStrings();
	};
}
#endif