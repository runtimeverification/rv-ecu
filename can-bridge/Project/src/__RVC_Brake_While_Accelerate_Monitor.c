#include "can_do.h"
#include "stm3210c_eval_lcd.h"
#include <stdlib.h>
static int __RVC_state = 0; 
extern uint32_t StateUnsafe;
int __RVC_Brake_While_Accelerate_match = 0;
int	__RVC_Brake_While_Accelerate_fail = 0;


void
__RVC_Brake_While_Accelerate_reset(void)
{
  __RVC_state = 0;
 }

static int __RVC_BRAKE_WHILE_ACCELERATE_THROTTLE_LOW[] = {-1,-1,-1,-1,};
static int __RVC_BRAKE_WHILE_ACCELERATE_THROTTLE_HIGH[] = {-1,1, 1, -1,};
static int __RVC_BRAKE_WHILE_ACCELERATE_BRAKE_HIGH[] = {2, 3, 2, 3, };
static int __RVC_BRAKE_WHILE_ACCELERATE_BRAKE_LOW[] = {-1,-1,-1,-1,};


void
__RVC_Brake_While_Accelerate_throttle_low()
{
{
    LCD_DisplayStringLine(LCD_LINE_1, (uint8_t*) "throttle released");
  }
  __RVC_state = __RVC_BRAKE_WHILE_ACCELERATE_THROTTLE_LOW[__RVC_state];
  __RVC_Brake_While_Accelerate_match = __RVC_state == 3;
	__RVC_Brake_While_Accelerate_fail = __RVC_state == -1;
if(__RVC_Brake_While_Accelerate_fail)
 {
     __RVC_Brake_While_Accelerate_reset();
 }
 
if(__RVC_Brake_While_Accelerate_match)
{
{
	StateUnsafe = 1;
  }}
}

void
__RVC_Brake_While_Accelerate_brake_low()
{
{
    LCD_DisplayStringLine(LCD_LINE_2, (uint8_t*) "brakes released");
  }
__RVC_state = __RVC_BRAKE_WHILE_ACCELERATE_BRAKE_LOW[__RVC_state];
  __RVC_Brake_While_Accelerate_match = __RVC_state == 3;
	__RVC_Brake_While_Accelerate_fail = __RVC_state == -1;

	if(__RVC_Brake_While_Accelerate_fail)
 {
     __RVC_Brake_While_Accelerate_reset();
 }
 
if(__RVC_Brake_While_Accelerate_match)
{
{
    // Unsafe state
	StateUnsafe = 1;
  }}
}

void
__RVC_Brake_While_Accelerate_throttle_high()
{
{
    LCD_DisplayStringLine(LCD_LINE_1, (uint8_t*)"throttle applied");
  }
__RVC_state = __RVC_BRAKE_WHILE_ACCELERATE_THROTTLE_HIGH[__RVC_state];
  __RVC_Brake_While_Accelerate_match = __RVC_state == 3;
	__RVC_Brake_While_Accelerate_fail = __RVC_state == -1;

	if(__RVC_Brake_While_Accelerate_fail)
 {
     __RVC_Brake_While_Accelerate_reset();
 }
 
if(__RVC_Brake_While_Accelerate_match)
{
{
    // Unsafe state
	StateUnsafe = 1;
  }}
}

void
__RVC_Brake_While_Accelerate_brake_high()
{
{
    LCD_DisplayStringLine(LCD_LINE_2, (uint8_t*) "brakes applied");
  }
__RVC_state = __RVC_BRAKE_WHILE_ACCELERATE_BRAKE_HIGH[__RVC_state];
  __RVC_Brake_While_Accelerate_match = __RVC_state == 3;
	__RVC_Brake_While_Accelerate_fail = __RVC_state == -1;

	if(__RVC_Brake_While_Accelerate_fail)
 {
     __RVC_Brake_While_Accelerate_reset();
 }
 
if(__RVC_Brake_While_Accelerate_match)
{
{
    // Unsafe state
	StateUnsafe = 1;
  }}
}


