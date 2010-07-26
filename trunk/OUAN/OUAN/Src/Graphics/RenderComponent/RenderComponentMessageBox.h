#ifndef RenderComponentMessageBoxH_H
#define RenderComponentMessageBoxH_H

#include "RenderComponent.h"

namespace OUAN
{	

	const std::string TEXTAREA_SUFFIX="/Message";
	const double DEFAULT_MESSAGEBOX_DURATION=2.0;	

	class RenderComponentMessageBox: public RenderComponent
	{
	private:
		Ogre::OverlayElement* mBasePanel;
		std::string mBasePanelName;
		
		Ogre::OverlayElement* mCharPanel; 
		std::string mCharPanelName;

		std::string mCharPanelMaterialName;

		std::string mMessage;

		double mDuration;

		bool mVisible;

		double mElapsedTime;
		
	public:
		
		RenderComponentMessageBox();
		~RenderComponentMessageBox();

		// Getters/setters

		const std::string& getBasePanelName() const;
		void setBasePanelName(const std::string& basePanelName);

		Ogre::OverlayElement* getBasePanel() const;
		void setBasePanel(const std::string& basePanelName);

		const std::string& getCharPanelName() const;
		void setCharPanelName(const std::string& charPanelName);

		Ogre::OverlayElement* getCharPanel() const;
		void setCharPanel(const std::string& charPanelName,
			const std::string& charPanelMaterialName);

		const std::string& getCharPanelMaterialName() const;
		void setCharPanelMaterialName(const std::string& charPanelMaterialName);

		const std::string& getMessage() const;
		void setMessage(const std::string& message);
		void setMessageBoxText();

		double getDuration() const;
		void setDuration(double duration);

		//Visibility methods
		void show();
		void hide();
		void setVisible(bool visible);
		bool isVisible() const;

		//Update method
		void update(double elapsedTime);
	};

	class TRenderComponentMessageBoxParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentMessageBoxParameters();
		~TRenderComponentMessageBoxParameters();

		std::string basePanelName;
		std::string charPanelName;
		std::string charPanelMaterialName;
		std::string mMessage;

		double duration;

		bool mVisible;
	};

}

#endif