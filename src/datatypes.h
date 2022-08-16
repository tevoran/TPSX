#ifndef TPSX_DATATYPES_H
#define TPSX_DATATYPES_H

#include <math.h>
#include <Tlib/inttypes.h>
#include <Tlib/math.h>

#define TPSX_VALID true
#define TPSX_NOT_VALID false

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

//vertex
struct TPSX_Vertex
{
	T_vec3 pos;
	T_vec3 normal;
	T_vec2 tex_coord;
} typedef TPSX_Vertex;

#endif /* TPSX_DATATYPES_H */