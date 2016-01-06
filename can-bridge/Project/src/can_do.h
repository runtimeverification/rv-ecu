#ifndef _CAN_DO_H
#define _CAN_DO_H
#include "stm32f10x_can.h"

typedef enum Component {Wiper, Headlight, NUM_COMPONENTS} Component;
typedef enum Action {Off, Pulse, Low, Medium, High, NUM_ACTIONS} Action;
// list allowed ops in order they appear in enum

int CAN_Do(Component c, Action a, unsigned int times);
#endif
