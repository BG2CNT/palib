#include <nds/system.h>

#include "PA_Internal.h"

// Some pseudocode for this function
// micvol(x) uses static variable oldsmp = 0
// micvol(x) = (oldsmp + smpfix(x)) / 2, oldsmp = smpfix(x)
// smpfix(x) = abs(x) * 2
u8 PA_ReadMicVol(){
	static u8 oldsmp = 0;
	s8 smp_s = micReadData8() ^ 0x80;
	u8 smp = ((smp_s < 0) ? (-smp_s) : smp_s) << 1;
	return oldsmp = (oldsmp + smp) >> 1;
}

void PA_InputGetAndSend(void){
	// The following is already managed by libnds:
	// Keys, Stylus, RTC, Powerdown, Screen lights, Led blink
	inputGetAndSend(); // a piece of cake isn't it?

	// Handle the remaining things (battery, temperature, microphone volume)
	PA_FifoMsg msg;
	msg.type = PA_MSG_INPUT;

	// Battery
	msg.InputMsg.battery = getBatteryLevel();

	// Temperature
	msg.InputMsg.temperature = tscReadTemperature();
	msg.InputMsg.tdiode1 = 0; // This is internal system information, don't
	msg.InputMsg.tdiode2 = 0; // expose it to the developer.

	// Microphone volume
	msg.InputMsg.micvol = PA_ReadMicVol();

	// Send the data
	PA_SendFifoMsg(msg);
}
