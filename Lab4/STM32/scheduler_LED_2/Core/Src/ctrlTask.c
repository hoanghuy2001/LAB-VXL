#include "ctrlTask.h"
#include "main.h"
void SCH_Init ( void ) {
	tByte Index;
	for(Index = 0 ; Index < SCH_MAX_TASKS ; Index++){
		SCH_Delete_Task(Index);
	}
	TimerInit();
}
void SCH_Update( void ) {
	tByte Index;
	// NOTE: calculations are in *TICKS* ( not milliseconds )
	for ( Index = 0 ; Index < SCH_MAX_TASKS; Index++) {
		// Check if there is a task at this location
		if(SCH_tasks_G[Index].pTask){
			if(SCH_tasks_G[Index].Delay == 0){
				// The task is due to run
				// Inc the RunMe flag
				SCH_tasks_G[Index].RunMe += 1 ;
				if( SCH_tasks_G[Index].Period) {
					// Schedule periodic tasks to run again
					SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
				}
			}
			else {
				SCH_tasks_G[Index].Delay -= 1;
			}
		}
	}
}


//Task_Name: the name of the function (task) that you wish to schedule
//Initial_Delay: the delay (in ticks) before task is first executed. If set to 0, the task is executed immediately.
//Period: the interval (in ticks) between repeated executions of the task. If set to 0, the task is executed only once
tByte SCH_Add_Task(void (*pFunction)() ,const tWord DELAY,const tWord PERIOD){
	tByte Index = 0;
	while (( SCH_tasks_G[Index].pTask != 0) && ( Index < SCH_MAX_TASKS)){
		Index++;
	}
	// Have we reached the end of the list ?
	if (Index == SCH_MAX_TASKS){
		// Task list is full
		// Set the global error variable
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, SET);
		Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
		// Also return an error code
		return SCH_MAX_TASKS;
	}
	// If we ’re here , there i s a space in the task array
	SCH_tasks_G[Index].Delay = DELAY / TIMER_INTERUPT;
	SCH_tasks_G[Index].Period = PERIOD / TIMER_INTERUPT;
	SCH_tasks_G[Index].pTask = pFunction;
	SCH_tasks_G[Index].RunMe = 0;
	// return position of task (to allow later deletion )
	return Index;
}

void SCH_Dispatch_Tasks (void) {
	tByte Index;
	// Dispatches (runs ) the next task ( if one is ready )
	for ( Index = 0 ; Index < SCH_MAX_TASKS; Index++) {
		if(SCH_tasks_G[Index].RunMe > 0){
			(*SCH_tasks_G[Index].pTask)();
			SCH_tasks_G[Index].RunMe -= 1;
			if( SCH_tasks_G[Index].Period == 0){
				SCH_Delete_Task(Index);
			}
		}
	}
}
tByte SCH_Delete_Task(const tByte TASK_INDEX){
	unsigned char Return_code ;
	if ( SCH_tasks_G[TASK_INDEX ] . pTask == 0) {
		Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
		Return_code = RETURN_ERROR;
	}
	else {
		Return_code = RETURN_ERROR;
	}
	SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
	SCH_tasks_G[TASK_INDEX].Period = 0;
	SCH_tasks_G[TASK_INDEX].RunMe = 0;
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	return Return_code ; // return status
}

