#ifndef GAMESTATEMANAGERH_H
#define GAMESTATEMANAGERH_H

#include "../OUAN.h"
namespace OUAN
{	
	/// Type definition to alias a vector of state pointers as a state stack
	typedef std::vector<GameStatePtr> TGameStateStack;	

	/// Manage a stack of game states, providing methods to change the current state
	/// and manipulate the stack
	class GameStateManager
	{
	public:
		/// Change the current state to the one given as a parameter
		/// @param	state	state to change to
		void changeState(GameStatePtr state, ApplicationPtr app);

		/// Push the given state to the stack
		///	@param	state to add to the stack
		void pushState(GameStatePtr state, ApplicationPtr app);

		/// Pops the state at the stack's top
		void popState();

		/// Return current state (i.e, the state at the stack's top)
		/// @return current state
		GameStatePtr getCurrentState() const;

		bool stateChanged();

		GameStateType getCurrentGameStateType();

		void update();
	private: 
		/// the stack of states
		TGameStateStack mStates;
		bool mStateChanged;
	};
}
#endif