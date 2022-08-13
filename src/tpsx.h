#ifndef TPSX_H
#define TPSX_H

#include <inttypes.h>
#include <stdbool.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#define TPSX_VALID true;
#define TPSX_NOT_VALID false;

struct TPSX_PixelRGBA
{
	u8 r;
	u8 g;
	u8 b;
	u8 a;
} typedef TPSX_PixelRGBA;

struct TPSX_Context
{
	bool is_valid;

	//render target
	TPSX_PixelRGBA *target_surface;
	u16 resx;
	u16 resy;
} typedef TPSX_Context;

static inline void TPSX_DrawPixel(TPSX_Context *context, u16 pos_x, u16 pos_y, TPSX_PixelRGBA pixel)
{
	context->target_surface[pos_y * context->resx + pos_x] = pixel;
};

//context
TPSX_Context* TPSX_CreateContext(void *render_target, u16 resx, u16 resy);
void TPSX_DestroyContext(TPSX_Context **context);

#endif /* TPSX_H */