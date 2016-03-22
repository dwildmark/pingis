/*
 * task_com.h
 *
 *
 *  Author: Spellabbet
 */ 


#ifndef TASK_COM_H_
#define TASK_COM_H_

#define TASK_COM_STACKSIZE	(2048/sizeof(portSTACK_TYPE))

void task_com(void *pvParameters);

#endif /* TASK_COM_H_ */