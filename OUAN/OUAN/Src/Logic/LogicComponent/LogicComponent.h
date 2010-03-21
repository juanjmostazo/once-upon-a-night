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

		int getHealthPoints() const;
		void setHealthPoints(int healthPoints);

		int getNumLives() const;
		void setNumLives(int numLives);

		std::string getScriptFilename() const;
		void setScriptFilename(const std::string& scriptFilename);

		virtual void update(long elapsedTime);
	private:
		/// Number of lives of the component
		int mNumLives;
		/// Health points of the component
		int mHealthPoints;
		/// Logic state of the parent game object
		int mState;
		/// Filename of the script that'll be executed by the logic subsystem
		/// to update this component's parent game object
		std::string mScriptFilename;

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
		int defaultState;
		int numLives;
		int healthPoints;
	};
}

#endif