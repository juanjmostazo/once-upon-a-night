#ifndef EVENTPRIORITIESH_H
#define EVENTPRIORITIESH_H
namespace OUAN
{
	// Event types
	typedef enum{
		EVENT_TYPE_GAMEOVER,	
		EVENT_TYPE_ONY_DEATH,
		EVENT_TYPE_CHANGEWORLD,
	} TEventType;


	// Priority values for all event types: 0 is highest	const int EVT_PRIORITY_GAME_OVER=0;
	const int EVT_PRIORITY_GAMEOVER=0;
	const int EVT_PRIORITY_ONY_DEATH=1;	//Ony loses 1 live
	const int EVT_PRIORITY_CHANGEWORLD=2;
	//...
}

#endif