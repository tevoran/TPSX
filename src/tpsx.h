#ifndef TPSX_H
#define TPSX_H

#include <stdbool.h>
#include "datatypes.h"

struct TPSX_Context
{
	bool is_valid;

	//render target
	TPSX_Pixel32 *target_surface;
    enum TPSX_PixelType surface_type;
	u16 resx;
	u16 resy;
} typedef TPSX_Context;

#include "pixel.h"

//context
TPSX_Context* TPSX_CreateContext(
    void *render_target,
    u16 resx,
    u16 resy,
    enum TPSX_PixelType type);
void TPSX_DestroyContext(TPSX_Context **context);

//render
void TPSX_RenderMesh(
    TPSX_Context *context,
    TPSX_Vertex *verts,
    u32 num_verts,
    T_mat4 *transforms,
    u32 num_transforms);

#endif /* TPSX_H */