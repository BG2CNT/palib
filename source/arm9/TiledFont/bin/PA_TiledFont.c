#include <PA_BgStruct.h>

#include "PA_TiledFont_Tiles_bin.h"
#include "PA_TiledFont_Map_bin.h"
#include "PA_TiledFont_Pal_bin.h"

const PA_BgStruct PA_TiledFont = {
	PA_BgNormal,
	256, 192,

	PA_TiledFont_Tiles_bin,
	PA_TiledFont_Map_bin,
	{PA_TiledFont_Pal_bin},

	13248,
	{1536}
};
