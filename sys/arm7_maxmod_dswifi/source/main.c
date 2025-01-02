///////////////////////////////////
// PAlib ARM7_MAXMOD_DSWIFI core //
//  by fincs                     //
///////////////////////////////////

#include <PA7.h>

static volatile bool pa_exit_loop = false;

static void PA_PowerButtonCallback(void){
	pa_exit_loop = true;
}

static void PA_VBL(void){
	PA_InputGetAndSend();

	// Legacy IPC
	PA_LegacyIPCManage();

	// Wifi
	Wifi_Update();
}

int main(int argc, char *argv[]){
	// Enable exception handler by default
	defaultExceptionHandler();

	// Initialize PAlib and initialize the sound hardware
	PA_Init();

	// Initialize Wifi
	installWifiFIFO();

	// Initialize Maxmod
	mmInstall(FIFO_MAXMOD);

	// Callback called when the power button in a DSi console is pressed.
	setPowerButtonCB(PA_PowerButtonCallback);

	irqSet(IRQ_VBLANK, PA_VBL);
	irqEnable(IRQ_VBLANK);

	while (!pa_exit_loop){ // Keep the ARM7 mostly idle...
		swiWaitForVBlank();
	}

	return 0;
}
