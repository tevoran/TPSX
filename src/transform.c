#include "tpsx.h"

void TPSX_TransformVertices(
    TPSX_Vertex *verts_in, 
    TPSX_Vertex *verts_out, 
    u32 num_verts,
    T_mat4 transform_matrix)
{
	for(u32 i = 0; i < num_verts; i++)
	{
		T_vec4 v4_in;
		T_vec4 v4_out;
		v4_in.x = verts_in[i].pos.x;
		v4_in.y = verts_in[i].pos.y;
		v4_in.z = verts_in[i].pos.z;
		v4_in.w = 1.0f; 
		v4_out = T_m4_v4_mul(transform_matrix, v4_in);
		verts_out[i].pos.x = v4_out.x;
		verts_out[i].pos.y = v4_out.y;
		verts_out[i].pos.z = v4_out.z / v4_out.w;

		verts_out[i].normal = verts_in[i].normal;
		verts_out[i].tex_coord = verts_in[i].tex_coord;
	}
}