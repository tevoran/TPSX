#include "tpsx.h"

void TPSX_SortTriangles(TPSX_Vertex *verts, u32 num_verts)
{
	//selectsort
	for(u32 i = 0; i < num_verts; i = i + 3)
	{
		f32 avg_z = (verts[i].pos.z +
			verts[i + 1].pos.z + 
			verts[i + 2].pos.z) * 0.33f; 
		u32 i_change = i;
		for(u32 j = i + 3; j < num_verts; j = j + 3)
		{
			if((verts[j].pos.z + 
				verts[j + 1 ].pos.z + 
				verts[j + 2].pos.z) * 0.33f > avg_z)
			{
				i_change = j;
				avg_z = (verts[j].pos.z + 
					verts[j + 1 ].pos.z + 
					verts[j + 2].pos.z) * 0.33f;
			}
		}
		TPSX_Vertex v0, v1, v2;
		v0 = verts[i];
		v1 = verts[i + 1];
		v2 = verts[i + 2];

		verts[i] = verts[i_change];
		verts[i + 1] = verts[i_change + 1];
		verts[i + 2] = verts[i_change + 2];

		verts[i_change] = v0;
		verts[i_change + 1] = v1;
		verts[i_change + 2] = v2;
	}
}