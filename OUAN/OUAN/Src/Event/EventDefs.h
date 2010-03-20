#ifndef EVENTPRIORITIESH_H
#define EVENTPRIORITIESH_H
namespace OUAN
{
	// Event types
	typedef enum{
		EVENT_TYPE_GAMEOVER,	
		EVENT_TYPE_ONY_DEATH,
		EVENT_TYPE_CHANGEWORLD,
		EVENT_TYPE_CHARACTERS_COLLISION,
		EVENT_TYPE_CHARACTER_IN_TRIGGER
	} TEventType;


	// Priority values for all event types: 0 is highest
	const int EVT_PRIORITY_GAMEOVER=0;
	const int EVT_PRIORITY_ONY_DEATH=1;	//Ony loses 1 live
	const int EVT_PRIORITY_CHANGEWORLD=2;
	const int EVT_PRIORITY_CHARACTERS_COLLISION=3;
	const int EVT_PRIORITY_CHARACTER_IN_TRIGGER=4;
	//...
}

#endif