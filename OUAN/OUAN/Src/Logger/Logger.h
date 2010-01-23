#ifndef __LOGGER_H__
#define __LOGGER_H__

#define LOG_FILE "log.txt"

#include <windows.h>

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

#endif