#ifndef TPSX_PIXEL_H
#define TPSX_PIXEL_H

#include "tpsx.h"

#define INV_255 0.00392f //is 1.0f / 255.0f;

static inline void TPSX_DrawPixelRGBA(void *pixel_ptr, TPSX_PixelRGBA pixel)
{
    TPSX_PixelRGBA *surface = (TPSX_PixelRGBA*)pixel_ptr;
    float factor = pixel.a * INV_255;
    surface->r = surface->r * (1.0f - factor) + pixel.r * factor;
    surface->g = surface->g * (1.0f - factor) + pixel.g * factor;
    surface->b = surface->b * (1.0f - factor) + pixel.b * factor;
    surface->a = surface->a * (1.0f - factor) + pixel.a * factor;
};

static inline void TPSX_DrawPixelBGRA(void *pixel_ptr, TPSX_PixelBGRA pixel)
{
    TPSX_PixelBGRA *surface = (TPSX_PixelBGRA*)pixel_ptr;
    float factor = pixel.a * INV_255;
    surface->r = surface->r * (1.0f - factor) + pixel.r * factor;
    surface->g = surface->g * (1.0f - factor) + pixel.g * factor;
    surface->b = surface->b * (1.0f - factor) + pixel.b * factor;
    surface->a = surface->a * (1.0f - factor) + pixel.a * factor;
};

#endif /* TPSX_PIXEL_H */
