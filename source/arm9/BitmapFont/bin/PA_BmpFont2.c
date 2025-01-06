#include <PA_BgStruct.h>

#include "PA_BmpFont2_Tiles_bin.h"
#include "PA_BmpFont2_Map_bin.h"
#include "PA_BmpFont2_Sizes_bin.h"

const PA_BgStruct PA_BmpFont2 = {
	PA_Font1bit,
	512, 128,

	PA_BmpFont2_Tiles_bin,
	PA_BmpFont2_Map_bin,
	{PA_BmpFont2_Sizes_bin},

	7360,
	{9}
};
