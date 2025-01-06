///////////////////////////////////
// PAlib ARM7_MP3 core           //
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

	// ASlib
	AS_SoundVBL();
}

int main(int argc, char *argv[]){
	// Enable exception handler by default
	defaultExceptionHandler();

	// Initialize PAlib and initialize the sound hardware (for ASlib)
	PA_Init();

	// Callback called when the power button in a DSi console is pressed.
	setPowerButtonCB(PA_PowerButtonCallback);

	irqSet(IRQ_VBLANK, PA_VBL);
	irqEnable(IRQ_VBLANK);

	// Initialize ASlib
	AS_Init();

	while (!pa_exit_loop){ // Keep the ARM7 mostly idle...
		swiWaitForVBlank();
		AS_MP3Engine(); // ...except for this ;_;
	}

	return 0;
}
