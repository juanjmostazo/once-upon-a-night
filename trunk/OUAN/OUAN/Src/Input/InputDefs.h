#ifndef INPUTDEFSH_H
#define INPUTDEFSH_H
//--------
//-- Input-related typedefs
//-----
struct InputMappingEntry
{
	int keyCode;
	int padId;
	std::string stringKey;
};
typedef std::map<std::string,InputMappingEntry> TControlInputMapping;
typedef enum{
	DEVICE_KEYB_MOUSE=0,
	DEVICE_PAD_PSX,
} TInputDevice;
#endif