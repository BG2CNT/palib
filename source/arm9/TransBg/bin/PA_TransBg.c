#include <PA_BgStruct.h>

#include "PA_TransBg_Tiles_bin.h"
#include "PA_TransBg_Map_bin.h"
#include "PA_TransBg_Pal_bin.h"

const PA_BgStruct PA_TransBg = {
	PA_BgNormal,
	256, 192,

	PA_TransBg_Tiles_bin,
	PA_TransBg_Map_bin,
	{PA_TransBg_Pal_bin},

	3584,
	{1536}
};
