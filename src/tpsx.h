#ifndef TPSX_H
#define TPSX_H

#include <stdbool.h>
#include <stdlib.h>
#include "datatypes.h"

struct TPSX_Context
{
	bool is_valid;

	//render target
	TPSX_Pixel32 *target_surface;
    enum TPSX_PixelType type;
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
void TPSX_ClearRenderTarget(TPSX_Context *context);

//transformations
void TPSX_TransformVertices(
    TPSX_Vertex *verts_in, 
    TPSX_Vertex *verts_out, 
    u32 num_verts,
    T_mat4 transform_matrix);

//textures
TPSX_Texture* TPSX_CreateTexture(
    TPSX_Pixel32 *surface,
    u8 width,
    u8 height,
    enum TPSX_PixelType type);
void TPSX_DestroyTexture(TPSX_Texture **texture);
TPSX_PixelRGBA TPSX_SampleFromTextureRGBA(TPSX_Texture *texture, T_vec2 pos);
TPSX_PixelBGRA TPSX_SampleFromTextureBGRA(TPSX_Texture *texture, T_vec2 pos);

//renderer
void TPSX_RenderMesh(
    TPSX_Context *context,
    TPSX_Vertex *verts,
    u32 num_verts,
    TPSX_Texture *tex);

//misc
void TPSX_SortTriangles(TPSX_Vertex *verts, u32 num_verts);

#endif /* TPSX_H */