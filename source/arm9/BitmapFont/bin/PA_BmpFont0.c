#include <PA_BgStruct.h>

#include "PA_BmpFont0_Tiles_bin.h"
#include "PA_BmpFont0_Map_bin.h"
#include "PA_BmpFont0_Sizes_bin.h"

const PA_BgStruct PA_BmpFont0 = {
	PA_Font1bit,
	256, 64,

	PA_BmpFont0_Tiles_bin,
	PA_BmpFont0_Map_bin,
	{PA_BmpFont0_Sizes_bin},

	6400,
	{6}
};
