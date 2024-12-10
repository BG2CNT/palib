#include "PA_Internal.h"
#include <string.h>

extern bool sleepIsEnabled; // from libnds

volatile PA_TransferRegion *volatile PA_Transfer = NULL;

void PA_Init(void){

	enableSound();

	// Disable libnds autosleep
	sleepIsEnabled = false;

	// Read user settings like the touch screen settings
	readUserSettings();

	// Initialize touch screen
	touchInit();

	// Initialize the basic part of the system
	irqInit();
	fifoInit();

	// Send input data as soon as possible
	inputGetAndSend();

	// Sleep mode, storage, firmware...
	installSystemFIFO();

	// Initialize the PAlib Fifo channel
	PA_InitFifo();

	// Stop LED blinking
	ledBlink(0);

	// Wait until the IPC buffer has been sent from the ARM9
	while (PA_Transfer == NULL);

	// Read current date from the RTC and setup an interrupt to update the time
	// regularly. The interrupt simply adds one second every time, it doesn't
	// read the date. Reading the RTC is very slow, so it's a bad idea to do it
	// frequently.
	initClockIRQTimer(3);

	// Init microphone
	micOn();
}
