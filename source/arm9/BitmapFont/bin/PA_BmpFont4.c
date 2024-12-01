#include <PA_BgStruct.h>

#include "PA_BmpFont4_Tiles_bin.h"
#include "PA_BmpFont4_Map_bin.h"
#include "PA_BmpFont4_Sizes_bin.h"

const PA_BgStruct PA_BmpFont4 = {
	PA_Font1bit,
	512, 128,

	PA_BmpFont4_Tiles_bin,
	PA_BmpFont4_Map_bin,
	{PA_BmpFont4_Sizes_bin},

	16768,
	{14}
};
