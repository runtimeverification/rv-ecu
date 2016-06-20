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

// one struct per reverse engineered component
static CANOpData wiperData = 
{
	0xAF87110,
	3,
	{
		/* Off */ {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		/* Pulse */ {0x02, 0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		/* Low */ {0x40, 0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		/* Med */ {0x10, 0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		/* High */ {0x04, 0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		/* Auto */ NO_OP_DATA
	}
};

static CANOpData doorData = 
{
	0xEF81296,
	1,
	{
		{0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		{0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		NO_OP_DATA,
		NO_OP_DATA,
		NO_OP_DATA,
		{0xC1,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
	}
};

static CANOpData headlightData = 
{
	0xAF87010,
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
	
	msg.IDE = CAN_Id_Extended;
	msg.RTR = CAN_RTR_Data;
	msg.ExtId = op->ID;
	msg.DLC = op->DLC;
	for (; i < 8; i++) {
		msg.Data[i] = op->Data[dataInd][i]; 
	}
	CAN_Transmit(CAN1, &msg);
}

// some state for effecient book keeping
static CANOpData *ops[NUM_COMPONENTS];
static int opsLoaded = FALSE;
static void loadOps() {
	ops[Wiper] = &wiperData;
	ops[Headlight] = &headlightData;
	ops[Door] = &doorData;
	opsLoaded = TRUE;
}	

int CAN_Do(Component c, Action a, unsigned int times) {
	uint8_t *data;
	int i = 0;

	if (!opsLoaded) {
		loadOps();
	}
	// enums are uin32_ts, so no need to check < 0
	if (c >= NUM_COMPONENTS || a >= NUM_ACTIONS)
		return FALSE;
	
/*	if (c == Door && a == Actuate) {
		writeFrame(ops[c], Actuate);
		writeFrame(ops[c], High);
		return TRUE;
	}
*/
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

int CAN_Decode(CanRxMsg *msg, Component *c, Action *a) {
	if (!opsLoaded) {
		loadOps();
	}
	// set correct component for c
	*c = Wiper;
	for (; (*c) < NUM_COMPONENTS; (*c)++) {
		if (msg->ExtId == ops[*c]->ID) {
			break;
		}
		if ((*c) == NUM_COMPONENTS - 1)
			return FALSE;
	}
	
	*a = Off;
	for (;(*a) < NUM_ACTIONS; (*a)++) {
		if(!memcmp(msg->Data, ops[*c]->Data[*a], 8))
			break;
	}
	
	if ((*a) == NUM_ACTIONS)
		return FALSE;
	
	return TRUE;
}
