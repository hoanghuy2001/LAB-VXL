#ifndef INC_CTRLTASK_H_
#define INC_CTRLTASK_H_

//BEGIN INCLUDE
#include "main.h"
#include "Timer.h"
//END INCLUDE

#define tWord 	unsigned int
#define tByte   unsigned char
#define SCH_MAX_TASKS 	10 //the number task we aim to
#define NO_TASK_ID 		0

//Error we can see in process
#define RETURN_ERROR 0x00;
#define RETURN_NORMOL 0x01;
#define ERROR_SCH_CANNOT_DELETE_TASK 0x02;
#define ERROR_SCH_TOO_MANY_TASKS 0x03;
tByte Error_code_G;

typedef struct {
	// Pointer to the task (must be a ’ void ( void ) ’ function )
	void (*pTask)(void);
	// Delay (ticks) until the function will (next) be run
	tWord Delay;
	// Interval (ticks) between subsequent runs .
	tWord Period;
	//Incremented (by scheduler) when task i s due to execute
	tByte RunMe;
} sTask;

sTask SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Init ( void );
//void SCH_Sort ( void );

void SCH_Dispatch_Tasks (void);
tByte SCH_Add_Task(void (*pFunction)() ,const tWord DELAY,const tWord PERIOD);
void SCH_Update(void);
tByte SCH_Delete_Task(const tByte TASK_INDEX);
void SCH_Go_To_Sleep(void);
#endif /* INC_CTRLTASK_H_ */
