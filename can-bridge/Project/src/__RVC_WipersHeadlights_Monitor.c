#include <stdio.h>
#include "can_do.h"
#include <stdlib.h>
#include "stm3210c_eval_lcd.h"
extern Component c;
extern Action a;

static int __RVC_state = 0; 

int __RVC_WipersHeadlights_wipersOnUnsafe = 0;

void
__RVC_WipersHeadlights_reset(void)
{
  __RVC_state = 0;
 }

static int __RVC_WIPERSHEADLIGHTS_HEADLIGHTSON[] = {3, 1, 1, 3, };
static int __RVC_WIPERSHEADLIGHTS_WIPERSON[] = {2, 1, 2, 1, };
static int __RVC_WIPERSHEADLIGHTS_WIPERSOFF[] = {0, 3, 0, 3, };
static int __RVC_WIPERSHEADLIGHTS_HEADLIGHTSOFF[] = {0, 2, 2, 0, };

void
__RVC_WipersHeadlights_headlightsOff()
{
__RVC_state = __RVC_WIPERSHEADLIGHTS_HEADLIGHTSOFF[__RVC_state];
  __RVC_WipersHeadlights_wipersOnUnsafe = __RVC_state == 2;
  c = NUM_COMPONENTS;
	a = NUM_ACTIONS;
	LCD_DisplayStringLine(LCD_LINE_4, (uint8_t*) "headlights off");
if(__RVC_WipersHeadlights_wipersOnUnsafe)
{
{
     c = Headlight;
		 a = High;
  }}
}

void
__RVC_WipersHeadlights_headlightsOn()
{
__RVC_state = __RVC_WIPERSHEADLIGHTS_HEADLIGHTSON[__RVC_state];
  __RVC_WipersHeadlights_wipersOnUnsafe = __RVC_state == 2;
  c = NUM_COMPONENTS;
	a = NUM_ACTIONS;
	LCD_DisplayStringLine(LCD_LINE_4, (uint8_t*) "headlights on");
if(__RVC_WipersHeadlights_wipersOnUnsafe)
{
{
		 c = Headlight;
		 a = Off;
  }}
}

void
__RVC_WipersHeadlights_wipersOn()
{
__RVC_state = __RVC_WIPERSHEADLIGHTS_WIPERSON[__RVC_state];
  __RVC_WipersHeadlights_wipersOnUnsafe = __RVC_state == 2;
  c = NUM_COMPONENTS;
	a = NUM_ACTIONS;
	LCD_DisplayStringLine(LCD_LINE_5, (uint8_t*) "wipers on");
	if(__RVC_WipersHeadlights_wipersOnUnsafe)
{
{
     c = Headlight;
		 a = High;
  }}
}

void
__RVC_WipersHeadlights_wipersOff()
{
__RVC_state = __RVC_WIPERSHEADLIGHTS_WIPERSOFF[__RVC_state];
  __RVC_WipersHeadlights_wipersOnUnsafe = __RVC_state == 2;
  c = NUM_COMPONENTS;
	a = NUM_ACTIONS;
	LCD_DisplayStringLine(LCD_LINE_5, (uint8_t*) "wipers off");
if(__RVC_WipersHeadlights_wipersOnUnsafe)
{
{
     c = Headlight;
	   a = High;
  }}

}
