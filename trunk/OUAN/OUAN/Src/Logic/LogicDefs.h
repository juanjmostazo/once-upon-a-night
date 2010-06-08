#ifndef LOGICDEFSH_H
#define LOGICDEFSH_H
namespace OUAN
{

	/// Size of the number of states
	const int GAMESTATE_HISTORY_SIZE=5;
	class LogicSubsystem;
	typedef boost::shared_ptr<LogicSubsystem> LogicSubsystemPtr;
}
#endif