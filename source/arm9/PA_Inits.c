#include <PA9.h>
#include <locale.h>

// Text stuff
#include "PA_TiledFont_Map_bin.h"
#include "PA_TiledFont_Tiles_bin.h"
#include "PA_TiledFont_Pal_bin.h"

#include "BitmapFont/all_gfx.h"

#include "PA_BmpFont0_Tiles_bin.h"
#include "PA_BmpFont1_Tiles_bin.h"
#include "PA_BmpFont2_Tiles_bin.h"
#include "PA_BmpFont3_Tiles_bin.h"
#include "PA_BmpFont4_Tiles_bin.h"

static void PAFillBitTextSizes(){
	pa_bittextsizes[0] = PA_BmpFont0_Tiles_bin_size;
	pa_bittextsizes[1] = PA_BmpFont1_Tiles_bin_size;
	pa_bittextsizes[2] = PA_BmpFont2_Tiles_bin_size;
	pa_bittextsizes[3] = PA_BmpFont3_Tiles_bin_size;
	pa_bittextsizes[4] = PA_BmpFont4_Tiles_bin_size;

	pa_bittextpoliceheight[0] = PA_BmpFont0.FontHeight;
	pa_bittextpoliceheight[1] = PA_BmpFont1.FontHeight;
	pa_bittextpoliceheight[2] = PA_BmpFont2.FontHeight;
	pa_bittextpoliceheight[3] = PA_BmpFont3.FontHeight;
	pa_bittextpoliceheight[4] = PA_BmpFont4.FontHeight;
}

// For the window fade system
const s16 winfades[][4] = {
	{4, 3, -4, -3},
	{4, 0, -4,  0},
	{8, 0,  0,  0},
	{0, 0, -8,  0},
	{0, 6, -8,  0},
	{8, 0,  0, -6},
	{0, 0, -8, -6},
	{8, 6,  0,  0},
};

void PA_UpdateSpriteVBL(void);
extern funcpointer SpriteVBL;

void PA_Init2D(){
	// Turn on the 2D cores and unset the switch screens flag
	REG_POWERCNT &= ~SWITCH_SCREENS;
	powerOn(POWER_2D_A | POWER_2D_B);

	// Set up the 2D cores
	videoSetMode   (MODE_0_2D |               // mode 0 (3D/text - text - text - text)
	                DISPLAY_SPR_ACTIVE |      // enable sprites
	                DISPLAY_SPR_1D |          // sprite VRAM 1D mapping
	                DISPLAY_SPR_1D_SIZE_128 | // sprite VRAM boundary 128
	                DISPLAY_SPR_1D_BMP);      // bitmap sprite VRAM 1D mapping

	videoSetModeSub(MODE_0_2D |               // mode 0 (3D/text - text - text - text)
	                DISPLAY_SPR_ACTIVE |      // enable sprites
	                DISPLAY_SPR_1D |          // sprite VRAM 1D mapping
	                DISPLAY_SPR_1D_SIZE_128 | // sprite VRAM boundary 128
	                DISPLAY_SPR_1D_BMP);      // bitmap sprite VRAM 1D mapping

	// Prepare some VRAM banks for graphics
	vramSetPrimaryBanks(VRAM_A_MAIN_SPRITE, VRAM_B_MAIN_BG_0x06000000, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);

	// Initialize extended palettes
	PA_InitBgExtPal();
	PA_InitSpriteExtPal();

	// Initialize the background and sprite system
	PA_ResetBgSys();
	PA_ResetSpriteSys();

	// VBL Inits
	SpriteVBL = PA_UpdateSpriteVBL;
}

extern funcpointer MotionVBL;
extern funcpointer PaddleVBL;
extern funcpointer GHPadVBL;

// The shared memory base address used to be 0x02FFF100, and it went up to
// 0x03000000 (0xF00 bytes).
//
// In DS mode, this is an uncached mirror of main RAM.  It is required to use
// unchached memory to communicate between the ARM9 and ARM7 because the code of
// PAlib and its associated libraries isn't prepared to handle the cache of the
// ARM9.
//
// In DSi mode this is in cached main RAM (because it's 4 times bigger), so we
// need a more intelligent way to define the location of the buffer. PAlib
// allocates this buffer in main RAM, and the ARM9 is in charge of using the
// uncached mirror of this address (using memUncached()) and passing the regular
// address in main RAM to the ARM7.
ALIGN(CACHE_LINE_SIZE) static char PA_TransferBuffer[0xF00] = { 0 };
volatile PA_TransferRegion *volatile PA_Transfer = NULL;

static void PA_SetupSharedMemory(void)
{
	PA_Transfer = memUncached(PA_TransferBuffer);

	DC_FlushRange(PA_TransferBuffer, sizeof(PA_TransferBuffer));

	PA_FifoMsg msg;
	msg.type = PA_SHARED_MEM_SET;
	msg.SharedMemSet.address = PA_TransferBuffer;
	PA_SendFifoMsg(msg);
}

void PA_Init(){
	// Wait a couple frames to provide a sensible starting point
	swiWaitForVBlank();
	swiWaitForVBlank();

	PA_InitFifo();
	PA_SetupSharedMemory();

	PA_Init2D();
	pa_checklid = 1; // Autocheck lid by default
	_PA_LidDown = 0;
	//setlocale(LC_ALL, "C"); // Disable UTF-8 in newlib (TODO: Is this needed?)
	PA_VBLCountersReset();
	PA_VBLFunctionReset();

	PAFillBitTextSizes();

	for(int i = 0; i < 2; i ++){
		PA_SetBrightness(i, 0);
		PA_font[i]      = 0;
		PA_textmap[i]   = (u16*) PA_TiledFont_Map_bin;
		PA_texttiles[i] = (u8*)  PA_TiledFont_Tiles_bin;
		PA_textpal[i]   = (u16*) PA_TiledFont_Pal_bin;
	}

	PA_UpdateUserInfo();
	PA_ResetRecoSys();           // Reco system init
	PA_SetScreenSpace(48);       // Default spacing
	PA_GifInfo.StartFrame = 0;   // start from the beginning
	PA_GifInfo.EndFrame = 10000; // random high number
	MotionVBL = PA_Nothing;
	PaddleVBL = PA_Nothing;
	GHPadVBL  = PA_Nothing;

	PA_UpdateRTC();
	PA_InitRand();

	// Initialize the VBlank function
	irqSet(IRQ_VBLANK, PA_vblFunc);
	//irqEnable(IRQ_VBLANK); // libnds already does this
}
