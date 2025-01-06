#include <PA_BgStruct.h>

#include "PA_BmpFont1_Tiles_bin.h"
#include "PA_BmpFont1_Map_bin.h"
#include "PA_BmpFont1_Sizes_bin.h"

const PA_BgStruct PA_BmpFont1 = {
	PA_Font1bit,
	256, 64,

	PA_BmpFont1_Tiles_bin,
	PA_BmpFont1_Map_bin,
	{PA_BmpFont1_Sizes_bin},

	6720,
	{8}
};
