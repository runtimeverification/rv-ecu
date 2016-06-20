#include <stdio.h>
#include "can_do.h"
#include <stdlib.h>
#include "stm3210c_eval_lcd.h"
#include "__RVC_DoorLocks_Monitor.h"
static int __RVC_state = 0; 
extern Component c;
extern Action a;

int __RVC_DoorLocks_unsafe = 0;

void
__RVC_DoorLocks_reset(void)
{
  __RVC_state = 0;
	c = Door;
	a = Actuate;
 }

static int __RVC_DOORLOCKS_DOORUNLOCK[] = {2, -1,2, };
static int __RVC_DOORLOCKS_DOORLOCK[] = {0, -1,0, };
static int __RVC_DOORLOCKS_DOORCLOSE[] = {0, -1,2, };
static int __RVC_DOORLOCKS_DOOROPEN[] = {1, -1,2, };

void
__RVC_DoorLocks_doorUnlock()

{ // Door unlocked }
__RVC_state = __RVC_DOORLOCKS_DOORUNLOCK[__RVC_state];
  __RVC_DoorLocks_unsafe = __RVC_state == 1;
	c = NUM_COMPONENTS;
	a = NUM_ACTIONS;
	LCD_DisplayStringLine(LCD_LINE_4, (uint8_t*) "Doors Unlocked");
if(__RVC_DoorLocks_unsafe)
{
{
    c = Door;
	  a = Actuate;
	__RVC_DoorLocks_reset();
  }}
}

void
__RVC_DoorLocks_doorLock()

{ // Door locked }
__RVC_state = __RVC_DOORLOCKS_DOORLOCK[__RVC_state];
  __RVC_DoorLocks_unsafe = __RVC_state == 1;
	c = NUM_COMPONENTS;
	a = NUM_ACTIONS;
	LCD_DisplayStringLine(LCD_LINE_4, (uint8_t*) "Doors Locked");
if(__RVC_DoorLocks_unsafe)
{
{
    c = Door;
		a = Actuate;
		__RVC_DoorLocks_reset();
  }}
}

void
__RVC_DoorLocks_doorClose()

{ // Door closed }
__RVC_state = __RVC_DOORLOCKS_DOORCLOSE[__RVC_state];
  __RVC_DoorLocks_unsafe = __RVC_state == 1;
		c = NUM_COMPONENTS;
	a = NUM_ACTIONS;
	LCD_DisplayStringLine(LCD_LINE_5, (uint8_t*) "Doors Closed");
if(__RVC_DoorLocks_unsafe)
{
{
		c = Door;
		a = Actuate;
		__RVC_DoorLocks_reset();
  }}
}

void
__RVC_DoorLocks_doorOpen()

{ // Door opened }
__RVC_state = __RVC_DOORLOCKS_DOOROPEN[__RVC_state];
  __RVC_DoorLocks_unsafe = __RVC_state == 1;
		c = NUM_COMPONENTS;
	a = NUM_ACTIONS;
	LCD_DisplayStringLine(LCD_LINE_5, (uint8_t*) "Doors Open");
if(__RVC_DoorLocks_unsafe)
{
{
    c = Door;
	  a = Actuate;
		__RVC_DoorLocks_reset();
  }}
}