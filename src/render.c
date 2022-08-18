#include "tpsx.h"

void TPSX_RenderMesh(
    TPSX_Context *context,
    TPSX_Vertex *verts,
    u32 num_verts,
    T_mat4 *transforms,
    u32 num_transforms)
{
	if(!context)
	{
		return;
	}
	if(context->is_valid == TPSX_NOT_VALID)
	{
		return;
	}
	if(!verts)
	{
		return;
	}
	if(!num_verts)
	{
		return;
	}
	if(!transforms)
	{
		return;
	}
	if(!num_transforms)
	{
		return;
	}

	T_vec2 v0, v1, v2, current;
	//converting vertices to screenspace
	v0.x = verts[0].pos.x * context->resx;
	v0.y = verts[0].pos.y * context->resy;
	v1.x = verts[1].pos.x * context->resx;
	v1.y = verts[1].pos.y * context->resy;
	v2.x = verts[2].pos.x * context->resx;
	v2.y = verts[2].pos.y * context->resy;

	//bounding box
	T_vec2 min, max;
	min.x = (u32)T_f_min(v0.x, v1.x);
	min.x = (u32)T_f_min(min.x, v2.x);
	min.y = (u32)T_f_min(v0.y, v1.y);
	min.y = (u32)T_f_min(min.y, v2.y);
	max.x = (u32)T_f_max(v0.x, v1.x) + 1;
	max.x = (u32)T_f_max(max.x, v2.x) + 1;
	max.y = (u32)T_f_max(v0.y, v1.y) + 1;
	max.y = (u32)T_f_max(max.y, v2.y) + 1;

	//barycentric coords
	current.x = min.x;
	current.y = min.y;
	T_vec3 bary = T_get_barycentric_coords(v0, v1, v2, current);
	current.x = min.x + 1.0f;
	current.y = min.y;
	T_vec3 bary_delta_line = T_get_barycentric_coords(v0, v1, v2, current);
	bary_delta_line = T_v3_sub(bary, bary_delta_line);
	current.x = min.x;
	current.y = min.y + 1.0f;
	T_vec3 bary_delta_row = T_get_barycentric_coords(v0, v1, v2, current);
	bary_delta_row = T_v3_sub(bary, bary_delta_row);
	T_vec3 bary_current_line = bary;

	TPSX_PixelBGRA pixel = {255, 0, 255, 0};
	for(int iy = min.y; iy < max.y; iy++)
	{
		bary = bary_current_line;

		for(int ix = min.x; ix < max.x; ix++)
		{
			if(	bary.x >= 0.0f && bary.x <= 1.0f &&
				bary.y >= 0.0f && bary.y <= 1.0f &&
				bary.z >= 0.0f && bary.z <= 1.0f)
			{
				TPSX_DrawPixelBGRA(context, ix, iy, pixel);
			}
			bary = T_v3_add(bary, bary_delta_line);
	printf("bary: x: %f y: %f z: %f\n", bary.x, bary.y, bary.z);

		}
		bary_current_line = T_v3_add(bary_current_line, bary_delta_row);
	}
}