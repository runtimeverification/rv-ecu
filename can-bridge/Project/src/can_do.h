#ifndef _CAN_DO_H
#define _CAN_DO_H
#include "stm32f10x_can.h"
#include "stm32f10x.h"
#include <string.h>

// in both of these enums, order matters, so do not change
typedef enum {Wiper, Headlight, Door, NUM_COMPONENTS} Component;
typedef enum {Off, Pulse, Low, Medium, High, Auto, NUM_ACTIONS} Action;
// aliases for door
#define Lock Pulse
#define Unlock Off
#define Actuate Auto
// makes <c> do <a> <times> times 
int CAN_Do(Component c, Action a, uint32_t times);

// correctly sets component and action for given CAN message
// if rx is from an unknown component or contains an unknokwn action,
// we return 0
int CAN_Decode(CanRxMsg *rx, Component *c, Action *a);
#endif
