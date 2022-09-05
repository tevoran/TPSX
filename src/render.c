#include "tpsx.h"

void TPSX_RenderMesh(
    TPSX_Context *context,
    TPSX_Vertex *verts,
    u32 num_verts,
    TPSX_Texture *tex)
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
		min.x = (i32)T_f_min(v0.x, v1.x);
		min.x = (i32)T_f_min(min.x, v2.x);
		min.y = (i32)T_f_min(v0.y, v1.y);
		min.y = (i32)T_f_min(min.y, v2.y);
		max.x = (i32)T_f_max(v0.x, v1.x) + 1;
		max.x = (i32)T_f_max(max.x, v2.x) + 1;
		max.y = (i32)T_f_max(v0.y, v1.y) + 1;
		max.y = (i32)T_f_max(max.y, v2.y) + 1;

		//stop if triangle is outside the screen
		if(max.x < 0.0f)
		{
			continue;
		}		
		if(max.y < 0.0f)
		{
			continue;
		}
		if(min.x > context->resx)
		{
			continue;
		}
		if(min.y > context->resy)
		{
			continue;
		}

		//crop bounding box to the surface if necessary
		min.x = (i32)T_f_max(min.x, 0);
		min.y = (i32)T_f_max(min.y, 0);
		max.x = (i32)T_f_min(max.x, context->resx);
		max.y = (i32)T_f_min(max.y, context->resy);

		//render loop
		TPSX_PixelBGRA pixel_bgra = {255, 0, 255, 0};
		TPSX_PixelRGBA pixel_rgba = {255, 0, 255, 0};
		for(int iy = min.y; iy < max.y; iy++)
		{
			for(int ix = min.x; ix < max.x; ix++)
			{
				current.x = ix;
				current.y = iy;

				T_vec3 bary = T_get_barycentric_coords(v0, v1, v2, current);
				if(	bary.x > 0.0f &&
					bary.y > 0.0f &&
					bary.z > 0.0f)
				{
					if(!tex)
					{
						if(context->type == TPSX_BGRA)
						{
							TPSX_DrawPixelBGRA(context, ix, iy, pixel_bgra);
						}
						else
						{
							TPSX_DrawPixelRGBA(context, ix, iy, pixel_rgba);
						}
					}
					else
					{
						T_vec2 tex_pos;
						tex_pos.u =
							verts[i].tex_coord.u * bary.x +
							verts[i+1].tex_coord.u * bary.y +
							verts[i+2].tex_coord.u * bary.z;
						tex_pos.v =
							verts[i].tex_coord.v * bary.x +
							verts[i+1].tex_coord.v * bary.y +
							verts[i+2].tex_coord.v * bary.z;

						if(context->type == TPSX_BGRA)
						{
							TPSX_PixelBGRA texel = TPSX_SampleFromTextureBGRA(
								tex,
								tex_pos);
							TPSX_DrawPixelBGRA(context, ix, iy, texel);
						}
						else
						{
							TPSX_PixelRGBA texel = TPSX_SampleFromTextureRGBA(
								tex,
								tex_pos);
							TPSX_DrawPixelRGBA(context, ix, iy, texel);
						}

					}
				}
			}
		}		
	}
}