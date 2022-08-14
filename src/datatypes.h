#ifndef TPSX_DATATYPES_H
#define TPSX_DATATYPES_H

#include <inttypes.h>
#include <math.h>

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

//pixel
struct TPSX_PixelRGBA
{
	u8 r;
	u8 g;
	u8 b;
	u8 a;
} typedef TPSX_PixelRGBA;

struct TPSX_PixelBGRA
{
    u8 b;
    u8 g;
    u8 r;
    u8 a;
} typedef TPSX_PixelBGRA;
typedef u32 TPSX_Pixel32; //generic pixel

enum TPSX_PixelType {TPSX_RGBA, TPSX_BGRA};

#endif /* TPSX_DATATYPES_H */