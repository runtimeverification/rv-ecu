#ifndef _CAN_DO_H
#define _CAN_DO_H
#include "stm32f10x_can.h"
#include "stm32f10x.h"

// in both of these enums, order matters, so do not change
typedef enum {Wiper, Headlight, NUM_COMPONENTS} Component;
typedef enum {Off, Pulse, Low, Medium, High, Auto, NUM_ACTIONS} Action;

// makes <c> do <a> <times> times 
int CAN_Do(Component c, Action a, uint32_t times);
#endif
