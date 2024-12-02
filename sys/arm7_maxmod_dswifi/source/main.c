///////////////////////////////////
// PAlib ARM7_MAXMOD_DSWIFI core //
//  by fincs                     //
///////////////////////////////////

#include <PA7.h>

void PA_VBL(){
	PA_InputGetAndSend();

	// Legacy IPC
	PA_LegacyIPCManage();

	// Wifi
	Wifi_Update();
}

int main(){
	// Initialize PAlib but don't initialize the sound hardware
	PA_Init(false);

	// Initialize Wifi
	installWifiFIFO();

	// Initialize Maxmod
	mmInstall(FIFO_MAXMOD);

	// Basic services...
	irqSet(IRQ_VBLANK, PA_VBL);

	irqEnable(IRQ_VBLANK);

	for(;;) // Keep the ARM7 mostly idle...
		swiWaitForVBlank();
}
