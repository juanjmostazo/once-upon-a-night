#ifndef LogicComponentH_H
#define LogicComponentH_H

#include "../../Component/Component.h"
namespace OUAN
{
	const double MAX_TIME_SPENT=100;
	class LogicComponent: public Component
	{
	public:
		LogicComponent(const std::string& type="");
		~LogicComponent();

		bool existsInDreams() const;
		void setExistsInDreams(bool existsInDreams);

		bool existsInNightmares() const;
		void setExistsInNightmares(bool existsInNightmares);

		int getState() const;
		virtual void setState(int state);

		int getOldState(int index=0) const;

		std::string getScriptFilename() const;
		void setScriptFilename(const std::string& scriptFilename);

		std::string getScriptFunction() const;
		void setScriptFunction(const std::string& scriptFunction);

		virtual void update(double elapsedTime);

		double getTimeSpent() const;
		void setTimeSpent(double timeSpent);

		bool isStateChanged() const;
		void setStateChanged(bool stateChanged);

		bool isOnWater() const;
		void setOnWater(bool onWater);

		int getLastFrameState() const;
		
		void initStateHistory();

		virtual void processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal);
		virtual void processEnterTrigger(GameObjectPtr pGameObject);
		virtual void processExitTrigger(GameObjectPtr pGameObject);

		virtual void changeAnimation(const std::string& animationName);
		virtual bool isLoopingAnimation(const std::string& animationName) const;
		virtual bool hasFinishedAnimation(const std::string& animationName) const;

		void printMessage(const std::string& msg,double time=DEFAULT_DISPLAY_LIFETIME);
		bool isEnabled() const;
		void setCurrentWorldVisibility(bool visibility);

	protected:
		int mState;
		int mLastFrameState;
		bool mOnWater;

		/// Size of the number of states
		int stateHistory[GAMESTATE_HISTORY_SIZE];

		bool mStateChanged;
		double mTimeSpent;

	private:
		/// Filename of the script that'll be executed by the logic subsystem
		/// to update this component's parent game object
		std::string mScriptFilename;
		
		/// Name of the script function that'll handle the state update
		std::string mScriptFunction;


		bool mExistsInDreams;
		bool mExistsInNightmares;
	};
	
	class TLogicComponentParameters: public TComponentParameters
	{
	public:
		TLogicComponentParameters();
		~TLogicComponentParameters();

		/// Existence in each world
		bool existsInDreams;
		bool existsInNightmares;

		std::string scriptFilename;
		std::string scriptFunction;

		int defaultState;
	};
}

#endif