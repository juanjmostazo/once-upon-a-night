
#ifndef __LOG_H__
#define __LOG_H__

#define LOG_FILE "log.txt"

#include <windows.h>

class cLog
{
public: 
    static cLog* Instance();
	void MsgLine(char *msg);
	void Msg(char *msg);
	void Lock();
	void Unlock();

private:
	bool locked;
    static cLog* _instance;
};

#endif