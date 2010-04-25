#ifndef __LOGGER_H__
#define __LOGGER_H__

#define LOG_FILE "custom_log.txt"

#include "../OUAN.h"
#include <windows.h>

namespace OUAN
{
	class Logger
	{
	public: 
		static Logger* Instance();
		void MsgLine(char *msg);
		void Msg(char *msg);
		void Lock();
		void Unlock();

	private:
		bool locked;
		static Logger* _instance;
	};
}

#endif