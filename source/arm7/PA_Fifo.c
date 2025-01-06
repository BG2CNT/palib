#include "PA_Internal.h"

void PA_InitFifo(){
	fifoSetDatamsgHandler(FIFO_PALIB, PA_FifoMsgHandler, 0);
	fifoSetValue32Handler(FIFO_PALIB, PA_FifoValHandler, 0);
}

void PA_FifoMsgHandler(int bytes, void* dummy){
	PA_FifoMsg msg;
	PA_GetFifoMsg(msg, bytes);
	switch(msg.type){
		// Get shared memory buffer from the ARM9
		case PA_SHARED_MEM_SET:
			PA_Transfer = msg.SharedMemSet.address;
			break;
		// Microphone record command
		case PA_MSG_MIC:
			PA_FifoMicMsg(&msg);
			break;
		// DS lite brightness change
		case PA_MSG_DSLBRIGHT:
			writePowerManagement(PM_DSLITE_REG, msg.DSLBrightMsg.brightness & 3);
			break;
		// PSG message
		case PA_MSG_PSG:
			PA_FifoPSGMsg(&msg);
			break;
	}
}

void PA_FifoValHandler(u32 type, void* dummy){
	switch(type){
		// Microphone stop command
		case PA_MSG_MICSTOP:
			PA_MicStop();
			break;
	}
}
