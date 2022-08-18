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

	for(u32 i = 0; i < num_verts; i = i+3)
	{
		T_vec2 v0, v1, v2, current;
		//converting vertices to screenspace
		v0.x = verts[i].pos.x * context->resx;
		v0.y = verts[i].pos.y * context->resy;
		v1.x = verts[i + 1].pos.x * context->resx;
		v1.y = verts[i + 1].pos.y * context->resy;
		v2.x = verts[i + 2].pos.x * context->resx;
		v2.y = verts[i + 2].pos.y * context->resy;

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

		//render loop
		TPSX_PixelBGRA pixel = {255, 0, 255, 0};
		for(int iy = min.y; iy < max.y; iy++)
		{
			for(int ix = min.x; ix < max.x; ix++)
			{
				current.x = ix;
				current.y = iy;
				T_vec3 bary = T_get_barycentric_coords(v0, v1, v2, current);
				if(	bary.x >= 0.0f &&
					bary.y >= 0.0f &&
					bary.z >= 0.0f)
				{
					TPSX_DrawPixelBGRA(context, ix, iy, pixel);
				}
			}
		}		
	}
}