/*
 * task_scheduler.h
 *
 *  Created on: 13/04/2016
 *      Author: Bruno Eiterer
 */

#ifndef EPS_TASK_SCHEDULER_H_
#define EPS_TASK_SCHEDULER_H_

extern volatile float mean_power;
extern volatile float mean_current;
extern volatile int acr_msb;
extern volatile int acr_lsb;



void task_scheduler(void);


#endif /* EPS_TASK_SCHEDULER_H_ */
