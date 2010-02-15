#include "Logger.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

using namespace OUAN;

Logger* Logger::_instance = 0;

Logger* Logger::Instance()
{
	FILE *f;

    if (_instance == 0)
	{
        _instance = new Logger;
		_instance->Unlock();

		f=fopen(LOG_FILE,"w");
		fclose(f);
    }
    return _instance;
}

/**************************************************************************
	msg
**************************************************************************/
void Logger::MsgLine(char *msg)
{
	if (!locked){
		FILE *f;
		char s[256];

		ZeroMemory(s,sizeof(s));

		sprintf(s,"%s\n",msg);
		f=fopen(LOG_FILE,"a+");
		fwrite(s,sizeof(char),strlen(s),f);
		fclose(f);
	}
}

void Logger::Msg(char *msg)
{
	if (!locked){
		FILE *f;
		char s[256];

		ZeroMemory(s,sizeof(s));

		sprintf(s,"%s",msg);
		f=fopen(LOG_FILE,"a+");
		fwrite(s,sizeof(char),strlen(s),f);
		fclose(f);
	}
}

void Logger::Lock()
{
	locked = true;
}

void Logger::Unlock()
{
	locked = false;
}