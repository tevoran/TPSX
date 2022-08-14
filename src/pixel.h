#ifndef TPSX_PIXEL
#define TPSX_PIXEL

#include "tpsx.h"

static inline void TPSX_DrawPixelRGBA(TPSX_Context *context, u16 pos_x, u16 pos_y, TPSX_PixelRGBA pixel)
{
    TPSX_PixelRGBA *surface = (TPSX_PixelRGBA*)context->target_surface;
	surface[pos_y * context->resx + pos_x] = pixel;
};

static inline void TPSX_DrawPixelBGRA(TPSX_Context *context, u16 pos_x, u16 pos_y, TPSX_PixelBGRA pixel)
{
    TPSX_PixelBGRA *surface = (TPSX_PixelBGRA*)context->target_surface;
    surface[pos_y * context->resx + pos_x] = pixel;
};

#endif /* TPSX_PIXEL */