#include "cLog.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

cLog* cLog::_instance = 0;

cLog* cLog::Instance()
{
	FILE *f;

    if (_instance == 0)
	{
        _instance = new cLog;
		_instance->Unlock();

		f=fopen("log.txt","w");
		fclose(f);
    }
    return _instance;
}

/**************************************************************************
	msg
**************************************************************************/
void cLog::MsgLine(char *msg)
{
	if (!locked){
		FILE *f;
		char s[256];

		ZeroMemory(s,sizeof(s));

		sprintf(s,"%s\n",msg);
		f=fopen("log.txt","a+");
		fwrite(s,sizeof(char),strlen(s),f);
		fclose(f);
	}
}

void cLog::Msg(char *msg)
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

void cLog::Lock()
{
	locked = true;
}

void cLog::Unlock()
{
	locked = false;
}