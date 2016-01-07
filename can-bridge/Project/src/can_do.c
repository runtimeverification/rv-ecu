#include "can_do.h"
#define TRUE 1
#define FALSE 0
#define NULL 0
/* placeholder to use in op definition when component can't do an action, such 
 * as 'window high'
*/
#define NO_OP_DATA {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}

// defines all necessary CAN data for a component, including payloads for each action
typedef struct {
	uint32_t ID; // ID of component on BUS
	uint8_t DLC; // Data Length Count, in bytes
	uint8_t Data[NUM_ACTIONS][8]; // 2D array of CAN payload indexed by specific action
} CANOpData;
	
static CANOpData wiperData = 
{
	0xAF87110,
	3,
	{
		/* Off */ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		/* Pulse */ {0x02, 0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		/* and so on */ {0x40, 0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		{0x10, 0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		{0x04, 0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		NO_OP_DATA
	}
};

static CANOpData headlightData = 
{
	0x87010,
	2,
	{
		{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		{0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		{0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		NO_OP_DATA,
		{0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		{0x10,0x04,0x00,0x00,0x00,0x00,0x00,0x00},
	}
};

static void writeFrame(CANOpData *op, uint32_t dataInd) {
	CanTxMsg msg;
	int i = 0;
	uint8_t *payload = op->Data[dataInd];
	
	msg.IDE = CAN_Id_Extended;
	msg.RTR = CAN_RTR_Data;
	msg.ExtId = op->ID;
	msg.DLC = op->DLC;
	for (; i < 8; i++) {
		msg.Data[i] = payload[i]; 
	}
	CAN_Transmit(CAN1, &msg);
}
			
int CAN_Do(Component c, Action a, unsigned int times) {
	uint8_t *data;
	int i = 0;
	// fast but wasteful, TODO - make ops static and init once during life of program
	CANOpData *ops[NUM_COMPONENTS];
	ops[Wiper] = &wiperData;
	ops[Headlight] = &headlightData;
	
	// enums are uin32_ts, so no need to check < 0
	if (c >= NUM_COMPONENTS || a >= NUM_ACTIONS)
		return FALSE;
	
	// check if component can even do specified action
	data = ops[c]->Data[a];
	for (; i < 8; i++) {
		if (data[i] != 0xFF)
			break;
		if (i == 7)
			return FALSE; // no op data for this action
	}
	
	while(times-- > 0) {	
		writeFrame(ops[c], a);
	}
		
	return TRUE;
}
