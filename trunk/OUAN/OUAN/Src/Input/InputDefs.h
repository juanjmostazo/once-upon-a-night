#ifndef INPUTDEFSH_H
#define INPUTDEFSH_H
#include <map>
#include <string>
//--------
//-- Input-related typedefs
//-----
typedef std::map<std::string,std::pair<int,int>> TControlInputMapping;
typedef enum{
	DEVICE_KEYB_MOUSE=0,
	DEVICE_PAD_PSX,
} TInputDevice;
#endif