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
}