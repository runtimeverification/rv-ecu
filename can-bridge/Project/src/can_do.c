#include "can_do.h"
#define TRUE 1
#define FALSE 0

// CAN message IDs for each component, in order
static int componentIDs[NUM_COMPONENTS] = {0xAF87110, 0xAF87010};
// Actual Ops
typedef void (*CANBusOp)(void);
static void WiperOff () {
	
}
static void WiperPulse() {
	//TODO
}


static CANBusOp ops[NUM_COMPONENTS][NUM_ACTIONS] = 
{
	/* Wiper */ {WiperOff, WiperPulse,0,0,0},
	/* headlight */ {0,0,0,0,0}
};

int CAN_Do(Component c, Action a, unsigned int times) {
	int componentID = componentIDs[c];
	
	if (c < NUM_COMPONENTS && a < NUM_ACTIONS)
		return FALSE;
	
	if (!ops[c][a])
		return FALSE;
	
	while(times-- > 0) {
		
	}
		
	return TRUE;
}

