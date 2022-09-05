#ifndef TPSX_PIXEL_H
#define TPSX_PIXEL_H

#include "tpsx.h"

static inline void TPSX_DrawPixelRGBA(TPSX_Context *context, u16 pos_x, u16 pos_y, TPSX_PixelRGBA pixel)
{
    TPSX_PixelRGBA *surface = (TPSX_PixelRGBA*)context->target_surface;
    surface += pos_y * context->resx + pos_x;
    surface->r = surface->r * (1.0f - pixel.a * 1.0f/255.0f) + pixel.r * (pixel.a * 1.0f/255.0f);
    surface->g = surface->g * (1.0f - pixel.a * 1.0f/255.0f) + pixel.g * (pixel.a * 1.0f/255.0f);
    surface->b = surface->b * (1.0f - pixel.a * 1.0f/255.0f) + pixel.b * (pixel.a * 1.0f/255.0f);
    surface->a = surface->a * (1.0f - pixel.a * 1.0f/255.0f) + pixel.a * (pixel.a * 1.0f/255.0f);
};

static inline void TPSX_DrawPixelBGRA(TPSX_Context *context, u16 pos_x, u16 pos_y, TPSX_PixelBGRA pixel)
{
    TPSX_PixelBGRA *surface = (TPSX_PixelBGRA*)context->target_surface;
    surface += pos_y * context->resx + pos_x;
    surface->r = surface->r * (1.0f - pixel.a * 1.0f/255.0f) + pixel.r * (pixel.a * 1.0f/255.0f);
    surface->g = surface->g * (1.0f - pixel.a * 1.0f/255.0f) + pixel.g * (pixel.a * 1.0f/255.0f);
    surface->b = surface->b * (1.0f - pixel.a * 1.0f/255.0f) + pixel.b * (pixel.a * 1.0f/255.0f);
    surface->a = surface->a * (1.0f - pixel.a * 1.0f/255.0f) + pixel.a * (pixel.a * 1.0f/255.0f);
};

#endif /* TPSX_PIXEL_H */