///////////////////////////////////
// PAlib ARM7_MP3_DSWIFI core    //
//  by fincs                     //
///////////////////////////////////

#include <PA7.h>

void PA_VBL(){
	PA_InputGetAndSend();

	// Legacy IPC
	PA_LegacyIPCManage();

	// ASlib
	AS_SoundVBL();

	// Wifi
	Wifi_Update();
}

int main(){
	// Initialize PAlib and initialize the sound hardware (for ASlib)
	PA_Init(true);

	// Initialize ASlib
	AS_Init();

	// Initialize Wifi
	installWifiFIFO();

	irqSet(IRQ_VBLANK, PA_VBL);

	irqEnable(IRQ_VBLANK);

	for(;;){ // Keep the ARM7 mostly idle...
		swiWaitForVBlank();
		AS_MP3Engine(); // ...except for this ;_;
	}
}
