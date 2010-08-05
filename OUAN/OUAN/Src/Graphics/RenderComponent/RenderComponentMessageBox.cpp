#include "OUAN_Precompiled.h"

#include "RenderComponentMessageBox.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameWorldManager.h"

using namespace OUAN;

RenderComponentMessageBox::RenderComponentMessageBox()
:RenderComponent(COMPONENT_TYPE_RENDER_MESSAGEBOX)
,mBasePanel(NULL)
,mBasePanelName("")
,mCharPanel(NULL)
,mCharPanelName("")
,mVisible(false)
,mMessage("")
,mDuration(0.0)
,mElapsedTime(-1.0)
{
}
RenderComponentMessageBox::~RenderComponentMessageBox()
{
}

const std::string& RenderComponentMessageBox::getBasePanelName() const
{
	return mBasePanelName;
}
void RenderComponentMessageBox::setBasePanelName(const std::string& basePanelName)
{
	mBasePanelName=basePanelName;
}

const std::string& RenderComponentMessageBox::getCharPanelName() const
{
	return mCharPanelName;
}
void RenderComponentMessageBox::setCharPanelName(const std::string& charPanelName)
{
	mCharPanelName=charPanelName;
}

const std::string& RenderComponentMessageBox::getCharPanelMaterialName() const
{
	return mCharPanelMaterialName;
}
void RenderComponentMessageBox::setCharPanelMaterialName(const std::string& charPanelMaterialName)
{
	mCharPanelMaterialName=charPanelMaterialName;
}

const std::string& RenderComponentMessageBox::getMessage() const
{
	return mMessage;
}
void RenderComponentMessageBox::setMessage(const std::string& message)
{
	mMessage=message;	
}
void RenderComponentMessageBox::setMessageBoxText()
{
	if (mBasePanel)
	{
		std::string textName(mBasePanelName);
		textName.append(TEXTAREA_SUFFIX);
		Ogre::OverlayElement* text = Ogre::OverlayManager::getSingleton().getOverlayElement(textName);
		if (text)
		{
			text->setCaption(mParent->getTranslation(mMessage));
		}
	}
}

double RenderComponentMessageBox::getDuration() const
{
	return mDuration;
}
void RenderComponentMessageBox::setDuration(double duration)
{
	mDuration=duration;
}
Ogre::OverlayElement* RenderComponentMessageBox::getBasePanel() const
{
	return mBasePanel;
}
void RenderComponentMessageBox::setBasePanel(const std::string& basePanelName)
{
	mBasePanel=Ogre::OverlayManager::getSingleton().getOverlayElement(basePanelName);
}
Ogre::OverlayElement* RenderComponentMessageBox::getCharPanel() const
{
	return mCharPanel;
}
void RenderComponentMessageBox::setCharPanel(const std::string& charPanelName, const std::string& charPanelMaterialName)
{
	Ogre::OverlayManager ovlMgr = Ogre::OverlayManager::getSingleton();
	mCharPanel=ovlMgr.getOverlayElement(charPanelName);
	if (!charPanelMaterialName.empty())
	{
		mCharPanel->setMaterialName(charPanelMaterialName);
	}
}

//Visibility methods
void RenderComponentMessageBox::show()
{
	setVisible(true);
}
void RenderComponentMessageBox::hide()
{
	setVisible(false);
}
void RenderComponentMessageBox::setVisible(bool visible)
{
	mVisible=visible;
	mElapsedTime=(visible)?0:-1;
	//Quick and dirty hack. The most correct way to do this would be using
	//a "MessageBoxVisible" event that was captured by the HUD.
	if (mBasePanel)
	{
		if(visible) 
		{
			mBasePanel->show();
		}
		else 
		{
			mBasePanel->hide();
		}
	}
	MsgBoxVisibilityChangedEventPtr evt = MsgBoxVisibilityChangedEventPtr(
		new MsgBoxVisibilityChangedEvent(visible));
	mParent->getGameWorldManager()->addEvent(evt);
	evt.reset();
}
bool RenderComponentMessageBox::isVisible() const
{
	return mVisible;
}
void RenderComponentMessageBox::update(double elapsedTime)
{
	if (mElapsedTime>=0)	
	{
		mElapsedTime+=elapsedTime;
		if (mElapsedTime>mDuration)
		{
			hide();
		}
	}
}
//-------------------
TRenderComponentMessageBoxParameters::TRenderComponentMessageBoxParameters() : TRenderComponentParameters()
{

}

TRenderComponentMessageBoxParameters::~TRenderComponentMessageBoxParameters()
{

}
	