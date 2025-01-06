#include <PA_BgStruct.h>

#include "PA_BmpFont3_Tiles_bin.h"
#include "PA_BmpFont3_Map_bin.h"
#include "PA_BmpFont3_Sizes_bin.h"

const PA_BgStruct PA_BmpFont3 = {
	PA_Font1bit,
	512, 128,

	PA_BmpFont3_Tiles_bin,
	PA_BmpFont3_Map_bin,
	{PA_BmpFont3_Sizes_bin},

	12544,
	{12}
};
