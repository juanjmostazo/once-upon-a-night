#ifndef LogicComponentH_H
#define LogicComponentH_H

#include "../../Component/Component.h"
namespace OUAN
{

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
		void setState(int state);

		int getOldState(int index=0) const;

		std::string getScriptFilename() const;
		void setScriptFilename(const std::string& scriptFilename);

		std::string getScriptFunction() const;
		void setScriptFunction(const std::string& scriptFunction);

		virtual void update(double elapsedTime);

		bool isStateChanged() const;
		void setStateChanged(bool stateChanged);
		
		void initStateHistory();

		virtual void processCollision(GameObjectPtr pGameObject);
		virtual void processEnterTrigger(GameObjectPtr pGameObject);
		virtual void processExitTrigger(GameObjectPtr pGameObject);

	private:

		int mState;
		int mLastFrameState;
		/// Filename of the script that'll be executed by the logic subsystem
		/// to update this component's parent game object
		std::string mScriptFilename;
		
		/// Name of the script function that'll handle the state update
		std::string mScriptFunction;

		/// Size of the number of states
		int stateHistory[GAMESTATE_HISTORY_SIZE];

		bool mStateChanged;

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