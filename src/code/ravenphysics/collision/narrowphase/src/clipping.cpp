#include "code/ravenphysics/collision/narrowphase/clipping.h"

namespace ravenphysics
{
	// Replaces an edge by the last one and lets the corners it joined lose it
	static inline void RemoveEdge(ClipList<ClipEdge>* edges, ClipEdge* edge, ClipVertex* first, ClipVertex* second)
	{
		first->refCount--;
		second->refCount--;
		edges->count--;
		ClipEdge* last = edges->data + edges->count;
		if (edge < last)
		{
			edge->tMin = last->tMin;
			edge->tMax = last->tMax;
			edge->first = last->first;
			edge->second = last->second;
			edge->payload[0] = last->payload[0];
			edge->payload[1] = last->payload[1];
			edge->payload[2] = last->payload[2];
			edge->payload[3] = last->payload[3];
			edge->payload[4] = last->payload[4];
			edge->payload[5] = last->payload[5];
		}
	}

	// FUNCTION: ENGINE 0x106C1320
	// NONMATCHING: the original walks the corners and planes with pointers biased to the middle of each element and
	// keeps fewer of the matrix elements in registers; the loops and the evaluation order are the same
#ifdef NONMATCHING
	void BuildClipLists(ConvexVolume* volume, ClipList<ClipVertex>* vertices, ClipList<ClipEdge>* edges,
		ClipList<ClipPlane>* planes)
	{
		unsigned int count = volume->mesh->vertexCount;
		vertices->count = count;
		if (count != 0)
		{
			float m10 = volume->transform.m[1][0];
			float m20 = volume->transform.m[2][0];
			float m00 = volume->transform.m[0][0];
			float m30 = volume->transform.m[3][0];
			float m21 = volume->transform.m[2][1];
			float m11 = volume->transform.m[1][1];
			float m01 = volume->transform.m[0][1];
			float m31 = volume->transform.m[3][1];
			float m22 = volume->transform.m[2][2];
			float m12 = volume->transform.m[1][2];
			float m02 = volume->transform.m[0][2];
			float m32 = volume->transform.m[3][2];
			ClipVertex* out = vertices->data;
			const float* in = volume->mesh->vertices;
			do
			{
				float z = in[2];
				float x = in[0];
				float y = in[1];
				out->x = x * m00 + z * m20 + y * m10 + m30;
				out->y = x * m01 + z * m21 + y * m11 + m31;
				out->z = x * m02 + z * m22 + y * m12 + m32;
				out->refCount = 0;
				in += 3;
				out++;
				count--;
			}
			while (count != 0);
		}
		count = volume->mesh->edgeCount;
		edges->count = count;
		const unsigned char* pairs = volume->mesh->edges;
		ClipEdge* edge = edges->data;
		for (unsigned int i = 0; i < count; i++)
		{
			edge->first = pairs[i * 2];
			edge->second = pairs[i * 2 + 1];
			edge->tMin = 0.0f;
			edge->tMax = 1.0f;
			edge++;
		}
		count = volume->mesh->planeCount;
		planes->count = count;
		if (count != 0)
		{
			float m00 = volume->transform.m[0][0];
			float m20 = volume->transform.m[2][0];
			float m10 = volume->transform.m[1][0];
			float m21 = volume->transform.m[2][1];
			float m11 = volume->transform.m[1][1];
			float m01 = volume->transform.m[0][1];
			float m22 = volume->transform.m[2][2];
			float m12 = volume->transform.m[1][2];
			float m02 = volume->transform.m[0][2];
			float m30 = volume->transform.m[3][0];
			float m31 = volume->transform.m[3][1];
			float m32 = volume->transform.m[3][2];
			ClipPlane* out = planes->data;
			const float* in = volume->mesh->planes;
			do
			{
				float x = in[0];
				float y = in[1];
				float z = in[2];
				float nx = m00 * x + m20 * z + m10 * y;
				float ny = m01 * x + m21 * z + m11 * y;
				float nz = m02 * x + m22 * z + m12 * y;
				out->unknown10 = 1;
				out->x = nx;
				out->y = ny;
				out->z = nz;
				out->d = in[3] - (m32 * nz + m30 * nx + m31 * ny);
				in += 4;
				out++;
				count--;
			}
			while (count != 0);
		}
	}
#endif

	// FUNCTION: ENGINE 0x106C0140
	// NONMATCHING: the original walks the edges with two pointers (edge and edge + 0x14, the other fields addressed
	// from the second) and ours with one; the branch layout lines up (about 45 % of the instructions)
#ifdef NONMATCHING
	void ClipEdges(ClipList<ClipEdge>* edges, ClipList<ClipVertex>* vertices, ClipList<ClipPlane>* planes)
	{
		ClipPlane* planeEnd = planes->data + planes->count;
		for (ClipPlane* plane = planes->data; plane != planeEnd; plane++)
		{
			ClipVertex* vertexEnd = vertices->data + vertices->count;
			for (ClipVertex* vertex = vertices->data; vertex != vertexEnd; vertex++)
			{
				if (vertex->refCount != 0)
				{
					vertex->distance = vertex->z * plane->z + vertex->y * plane->y + vertex->x * plane->x + plane->d;
				}
			}
			ClipEdge* edge = edges->data;
			ClipEdge* edgeEnd = edge + edges->count;
			while (edge != edgeEnd)
			{
				ClipVertex* first = vertices->data + edge->first;
				ClipVertex* second = vertices->data + edge->second;
				float firstDistance = first->distance;
				float secondDistance = second->distance;
				if (firstDistance > 0.0f)
				{
					if (secondDistance > 0.0f)
					{
						RemoveEdge(edges, edge, first, second);
						edgeEnd = edges->data + edges->count;
					}
					else
					{
						float t = firstDistance / (firstDistance - secondDistance);
						if (!(t > edge->tMin))
						{
							t = edge->tMin;
						}
						edge->tMin = t;
						if (t < edge->tMax)
						{
							edge++;
						}
						else
						{
							RemoveEdge(edges, edge, first, second);
							edgeEnd = edges->data + edges->count;
						}
					}
				}
				else if (secondDistance > 0.0f)
				{
					float t = firstDistance / (firstDistance - secondDistance);
					if (t > edge->tMax)
					{
						t = edge->tMax;
					}
					edge->tMax = t;
					if (edge->tMin < t)
					{
						edge++;
					}
					else
					{
						RemoveEdge(edges, edge, first, second);
						edgeEnd = edges->data + edges->count;
					}
				}
				else
				{
					edge++;
				}
			}
		}
	}
#endif
}
