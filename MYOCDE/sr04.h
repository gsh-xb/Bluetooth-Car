#ifndef __SR04_H
#define __SR04_H

#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"


/*
PA2 ---- TRIG 	���
PA3 ---- ECHO	����
*/

#define TRIG	PCout(6)
#define ECHO	PCin(8)


void Sr04_Init(void);
u16 Get_Sr04_Distance(void);



#endif
