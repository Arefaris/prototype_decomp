// The references to the triangles of mesh volumes (unit around 0x10667360 - 0x10668000, no assert path, so the file
// name is a guess).
#include "code/engine/driving/carattributes.h"
#include "code/math/worldbounds.h"
#include "code/ravenphysics/collision/meshfaceref.h"

namespace ravenphysics
{
	// The triangle last answered by GetWorldTriangle and the mesh and number it was made for (0x110BEF84, 0x110BEF8C and
	// 0x1127D434; names guessed)
	extern unsigned short gTriangleCacheFace;
	extern unsigned int gTriangleCacheMesh;
	extern math::Triangle gTriangleCache;

	// FUNCTION: ENGINE 0x106673A0
	// EQUIVALENT: the same differences, products and call to Normalize; two temporaries swap their registers (xmm0 and xmm2), 91.8 %
	void CalculateNormal(const math::Vector* a, const math::Vector* b, const math::Vector* c, math::Vector* normal)
	{
		math::Vector first;
		math::Vector second;
		second.x = a->x - c->x;
		second.y = a->y - c->y;
		second.z = a->z - c->z;
		first.y = a->y - b->y;
		first.z = a->z - b->z;
		first.x = a->x - b->x;
		normal->Cross(first, second);
		normal->Normalize();
	}

	// FUNCTION: ENGINE 0x10667370
	unsigned int GridFace::GetFlag0() const
	{
		return flag0;
	}

	// FUNCTION: ENGINE 0x10667380
	unsigned int GridFace::GetFlag1() const
	{
		return flag1;
	}

	// FUNCTION: ENGINE 0x10667390
	unsigned int GridFace::GetFlag2() const
	{
		return flag2;
	}

	// FUNCTION: ENGINE 0x10667660
	void MeshFaceRef::Set(CollisionVolume6* volume, unsigned short newFace)
	{
		if (volume != 0)
		{
			mesh.value = volume->handle.value;
		}
		else
		{
			mesh.value = 0xffffffff;
		}
		face = newFace;
	}

	// FUNCTION: ENGINE 0x10667690
	bool MeshFaceRef::IsValid() const
	{
		return mesh.IsValid() && face != 0xffff;
	}

	// FUNCTION: ENGINE 0x106676B0
	void MeshFaceRef::Clear()
	{
		mesh.value = 0xffffffff;
		face = 0xffff;
	}

	// FUNCTION: ENGINE 0x106676C0
	const math::Vector* MeshFaceRef::GetCorner(int corner) const
	{
		CollisionVolume6* volume = mesh.Get();
		return &volume->grid.vertices[volume->grid.faces[face].vertex[corner]];
	}

	// FUNCTION: ENGINE 0x10667760
	void MeshFaceRef::GetCorners(math::Vector* corners) const
	{
		int i = 3;
		do
		{
			i--;
			const math::Vector* corner = GetCorner(i);
			corners[i].x = corner->x;
			corners[i].y = corner->y;
			corners[i].z = corner->z;
		}
		while (i != 0);
	}

	// FUNCTION: ENGINE 0x106677E0
	void MeshFaceRef::GetCentre(math::Vector* centre) const
	{
		CollisionVolume6* volume = mesh.Get();
		const GridFace* record = &volume->grid.faces[face];
		const math::Vector* vertices = volume->grid.vertices;
		const math::Vector* first = &vertices[record->vertex[0]];
		centre->x = first->x;
		centre->y = first->y;
		centre->z = first->z;
		const math::Vector* second = &vertices[record->vertex[1]];
		centre->x = second->x + centre->x;
		centre->y = second->y + centre->y;
		centre->z = second->z + centre->z;
		const math::Vector* third = &vertices[record->vertex[2]];
		centre->x = centre->x + third->x;
		centre->y = third->y + centre->y;
		centre->z = third->z + centre->z;
		centre->x = centre->x * 0.33333334f;
		centre->y = centre->y * 0.33333334f;
		centre->z = centre->z * 0.33333334f;
	}

	// FUNCTION: ENGINE 0x106678C0
	// EQUIVALENT: the same loads, sums and stores; the engine adds the third corner's x as centre + corner, ours as corner + centre (an addition commutes), 55.8 %
	void MeshFaceRef::GetWorldCentre(math::Vector* centre) const
	{
		CollisionVolume6* volume = mesh.Get();
		const GridFace* record = &volume->grid.faces[face];
		const math::Vector* first = &volume->grid.vertices[record->vertex[0]];
		centre->x = first->x;
		centre->y = first->y;
		centre->z = first->z;
		const math::Vector* second = &volume->grid.vertices[record->vertex[1]];
		centre->x = second->x + centre->x;
		centre->y = second->y + centre->y;
		centre->z = second->z + centre->z;
		const math::Vector* third = &volume->grid.vertices[record->vertex[2]];
		centre->x = centre->x + third->x;
		centre->y = third->y + centre->y;
		centre->z = third->z + centre->z;
		centre->x = centre->x * 0.33333334f;
		centre->y = centre->y * 0.33333334f;
		centre->z = centre->z * 0.33333334f;
		if (volume->grid.transformed)
		{
			centre->Transform(volume->grid.matrix);
		}
	}

	// FUNCTION: ENGINE 0x106679C0
	void MeshFaceRef::GetCornerSum(math::Vector* sum) const
	{
		CollisionVolume6* volume = mesh.Get();
		const GridFace* record = &volume->grid.faces[face];
		const math::Vector* vertices = volume->grid.vertices;
		const math::Vector* first = &vertices[record->vertex[0]];
		sum->x = first->x;
		sum->y = first->y;
		sum->z = first->z;
		const math::Vector* second = &vertices[record->vertex[1]];
		sum->x = second->x + sum->x;
		sum->y = second->y + sum->y;
		sum->z = second->z + sum->z;
		const math::Vector* third = &vertices[record->vertex[2]];
		sum->x = sum->x + third->x;
		sum->y = third->y + sum->y;
		sum->z = third->z + sum->z;
	}

	// FUNCTION: ENGINE 0x10667A70
	// EQUIVALENT: the same loads, sums and stores; the engine adds the third corner's x as sum + corner, ours as corner + sum (an addition commutes), 94.1 %
	void MeshFaceRef::GetWorldCornerSum(math::Vector* sum) const
	{
		CollisionVolume6* volume = mesh.Get();
		const GridFace* record = &volume->grid.faces[face];
		const math::Vector* first = &volume->grid.vertices[record->vertex[0]];
		sum->x = first->x;
		sum->y = first->y;
		sum->z = first->z;
		const math::Vector* second = &volume->grid.vertices[record->vertex[1]];
		sum->x = second->x + sum->x;
		sum->y = second->y + sum->y;
		sum->z = second->z + sum->z;
		const math::Vector* third = &volume->grid.vertices[record->vertex[2]];
		sum->x = sum->x + third->x;
		sum->y = third->y + sum->y;
		sum->z = third->z + sum->z;
		if (volume->grid.transformed)
		{
			sum->Transform(volume->grid.matrix);
		}
	}

	// FUNCTION: ENGINE 0x10667BC0
	unsigned int MeshFaceRef::GetFlag0() const
	{
		unsigned short index = face;
		return mesh.Get()->grid.faces[index].flag0;
	}

	// FUNCTION: ENGINE 0x10667BE0
	unsigned int MeshFaceRef::GetFlag1() const
	{
		unsigned short index = face;
		return mesh.Get()->grid.faces[index].flag1;
	}

	// FUNCTION: ENGINE 0x10667C00
	unsigned int MeshFaceRef::GetFlag2() const
	{
		unsigned short index = face;
		return mesh.Get()->grid.faces[index].flag2;
	}

	// FUNCTION: ENGINE 0x10667C20
	unsigned int MeshFaceRef::GetProperty() const
	{
		unsigned short index = face;
		return mesh.Get()->grid.faces[index].flags >> 3 & 0x3f;
	}

	// FUNCTION: ENGINE 0x10667430
	unsigned short MeshRecord::GetFace(int index) const
	{
		return unknown[1 + index];
	}

	// FUNCTION: ENGINE 0x10667440
	unsigned short MeshRecord::GetNeighbour(int index) const
	{
		return unknown[4 + index];
	}

	// FUNCTION: ENGINE 0x10667450
	bool CollisionVolume6::IsTransformed() const
	{
		return grid.transformed;
	}

	// FUNCTION: ENGINE 0x10667460
	MeshRecord* CollisionVolume6::GetRecord(unsigned short index)
	{
		return grid.unknownEC + index;
	}

	// FUNCTION: ENGINE 0x10667480
	unsigned short* CollisionVolume6::GetRecordIndex(unsigned short index)
	{
		return grid.unknownE4 + index;
	}

	// FUNCTION: ENGINE 0x106674A0
	int CollisionVolume6::GetRecordCount() const
	{
		return grid.unknownE8;
	}

	// FUNCTION: ENGINE 0x10667610
	ConvexMesh* CollisionVolume6::GetMesh() const
	{
		return mesh;
	}

	// FUNCTION: ENGINE 0x10667C90
	CollisionVolume* ConvexMesh::GetVolume(int index)
	{
		return geometry.begin[index].volume;
	}

	// FUNCTION: ENGINE 0x10667620
	CollisionHandle* CollisionVolume6::GetHandle()
	{
		return &handle;
	}

	// FUNCTION: ENGINE 0x10667630
	unsigned char* BroadPhaseGrid::GetSlotData(unsigned short index)
	{
		if (slot->unknown8 != 0)
		{
			return index * slot->unknownC + slot->unknown8;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10667D80
	unsigned char* CollisionVolume6::GetSlotData(unsigned short index)
	{
		if (grid.slot->unknown8 != 0)
		{
			return index * grid.slot->unknownC + grid.slot->unknown8;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x106674B0
	// EQUIVALENT: the same differences, products and call to Normalize; the six differences are scheduled in another order and the registers of the temporaries differ, 84.8 %
	void CollisionVolume6::GetFaceNormal(const GridFace* face, math::Vector* normal)
	{
		const math::Vector* vertices = grid.vertices;
		const math::Vector& c = vertices[face->vertex[2]];
		const math::Vector& b = vertices[face->vertex[1]];
		const math::Vector& a = vertices[face->vertex[0]];
		math::Vector first;
		math::Vector second;
		second.y = a.y - c.y;
		first.z = a.z - b.z;
		second.x = a.x - c.x;
		second.z = a.z - c.z;
		first.x = a.x - b.x;
		first.y = a.y - b.y;
		normal->Cross(first, second);
		normal->Normalize();
	}

	// FUNCTION: ENGINE 0x106676F0
	void MeshFaceRef::GetWorldCorner(int corner, math::Vector* out) const
	{
		CollisionVolume6* volume = mesh.Get();
		unsigned short vertex = volume->grid.faces[face].vertex[corner];
		if (volume->grid.transformed)
		{
			volume->grid.matrix.Transform(volume->grid.vertices[vertex], *out);
			return;
		}
		const math::Vector* source = &volume->grid.vertices[vertex];
		out->x = source->x;
		out->y = source->y;
		out->z = source->z;
	}

	// FUNCTION: ENGINE 0x10667DE0
	void MeshFaceRef::GetWorldTriangle(math::Triangle* out) const
	{
		if (gTriangleCacheFace == face && gTriangleCacheMesh == mesh.value)
		{
			out->a.x = gTriangleCache.a.x;
			out->a.y = gTriangleCache.a.y;
			out->a.z = gTriangleCache.a.z;
			out->b.x = gTriangleCache.b.x;
			out->b.y = gTriangleCache.b.y;
			out->b.z = gTriangleCache.b.z;
			out->c.x = gTriangleCache.c.x;
			out->c.y = gTriangleCache.c.y;
			out->c.z = gTriangleCache.c.z;
			return;
		}
		math::Vector* corners = &out->a;
		int i = 3;
		do
		{
			i--;
			GetWorldCorner(i, &corners[i]);
		}
		while (i != 0);
		gTriangleCacheFace = face;
		gTriangleCacheMesh = mesh.value;
		gTriangleCache.a.x = out->a.x;
		gTriangleCache.a.y = out->a.y;
		gTriangleCache.a.z = out->a.z;
		gTriangleCache.b.x = out->b.x;
		gTriangleCache.b.y = out->b.y;
		gTriangleCache.b.z = out->b.z;
		gTriangleCache.c.x = out->c.x;
		gTriangleCache.c.y = out->c.y;
		gTriangleCache.c.z = out->c.z;
	}

	// FUNCTION: ENGINE 0x10667F30
	math::Triangle MeshFaceRef::GetWorldTriangleCopy() const
	{
		math::Triangle result;
		GetWorldTriangle(&result);
		return result;
	}

#ifdef NONMATCHING
	// The vector turned by the rotation part of the matrix, as the mesh code writes it out
	static inline void RotateVector(const math::Matrix& matrix, math::Vector* vector)
	{
		float x = vector->x;
		float y = vector->y;
		float z = vector->z;
		float rx = x * matrix.m[0][0] + y * matrix.m[1][0] + z * matrix.m[2][0];
		float ry = x * matrix.m[0][1] + y * matrix.m[1][1] + z * matrix.m[2][1];
		float rz = x * matrix.m[0][2] + y * matrix.m[1][2] + z * matrix.m[2][2];
		vector->x = rx;
		vector->y = ry;
		vector->z = rz;
	}
#endif

	// FUNCTION: ENGINE 0x10667560
	// NONMATCHING: the sums of the rotation are added in another association (xmm terms in the order z, y, x instead of the engine's y, z, x for the first and x, y, z for the others); the rest is the same, 69.4 %
#ifdef NONMATCHING
	void CollisionVolume6::GetWorldFaceNormal(const GridFace* face, math::Vector* normal)
	{
		GetFaceNormal(face, normal);
		if (grid.transformed)
		{
			RotateVector(grid.matrix, normal);
		}
	}
#endif

	// FUNCTION: ENGINE 0x10667CA0
	void CollisionVolume6::GetFaceNormalAt(unsigned short index, math::Vector* normal)
	{
		GetFaceNormal(&grid.faces[index], normal);
	}

	// FUNCTION: ENGINE 0x10667CC0
	// NONMATCHING: the sums of the rotation are added in another association (xmm terms in the order z, y, x instead of the engine's y, z, x for the first and x, y, z for the others); the rest is the same, 44.0 %
#ifdef NONMATCHING
	void CollisionVolume6::GetWorldFaceNormalAt(unsigned short index, math::Vector* normal)
	{
		GetFaceNormal(&grid.faces[index], normal);
		if (grid.transformed)
		{
			RotateVector(grid.matrix, normal);
		}
	}
#endif

	// FUNCTION: ENGINE 0x10667F50
	void MeshFaceRef::GetNormal(math::Vector* normal) const
	{
		unsigned short index = face;
		CollisionVolume6* volume = mesh.Get();
		volume->GetFaceNormal(&volume->grid.faces[index], normal);
	}

	// FUNCTION: ENGINE 0x10667F80
	// NONMATCHING: the sums of the rotation are added in another association (xmm terms in the order z, y, x instead of the engine's y, z, x for the first and x, y, z for the others); the rest is the same, 72.8 %
#ifdef NONMATCHING
	void MeshFaceRef::GetWorldNormal(math::Vector* normal) const
	{
		unsigned short index = face;
		CollisionVolume6* volume = mesh.Get();
		volume->GetFaceNormal(&volume->grid.faces[index], normal);
		if (volume->grid.transformed)
		{
			RotateVector(volume->grid.matrix, normal);
		}
	}
#endif

	// FUNCTION: ENGINE 0x10667B40
	bool MeshFaceRef::HasNeighbour(int edge) const
	{
		CollisionVolume6* volume = mesh.Get();
		unsigned short* neighbours = volume->grid.slot->unknown4;
		if (neighbours == 0)
		{
			return false;
		}
		if (neighbours[edge + face * 3] != 0xffff)
		{
			return true;
		}
		if (volume->grid.unknownE8 == 0)
		{
			return false;
		}
		unsigned short record = volume->grid.unknownE4[face];
		if (record == 0xffff)
		{
			return false;
		}
		bool found = volume->grid.unknownEC[record].unknown[4 + edge] != 0xffff;
		return found;
	}

	// FUNCTION: ENGINE 0x10668040
	float MeshFaceRef::GetHeight() const
	{
		float low = GetCorner(2)->y;
		float high = low;
		int i = 2;
		do
		{
			i--;
			float y = GetCorner(i)->y;
			if (high < y)
			{
				high = y;
			}
			if (!(y > low))
			{
				low = y;
			}
		}
		while (i != 0);
		return high - low;
	}

	// FUNCTION: ENGINE 0x106680A0
	// EQUIVALENT: the same loads, tests and the same call of Set; the engine pushes the number in each branch and shares the rest of the call, ours shares all of it, 37.9 %
	MeshFaceRef MeshFaceRef::GetNeighbourRef(int edge) const
	{
		CollisionVolume6* volume = mesh.Get();
		unsigned short neighbour = volume->grid.slot->unknown4[edge + face * 3];
		CollisionVolume6* target;
		if (neighbour != 0xffff)
		{
			target = volume;
		}
		else
		{
			MeshRecord* record = volume->grid.unknownEC + volume->grid.unknownE4[face];
			target = static_cast<CollisionVolume6*>(volume->mesh->geometry.begin[record->unknown[1 + edge]].volume);
			neighbour = record->unknown[4 + edge];
		}
		MeshFaceRef result;
		result.Set(target, neighbour);
		return result;
	}

	// FUNCTION: ENGINE 0x10667C50
	bool XZLine::IsAbove(const math::Vector* point) const
	{
		return point->z * b + point->x * a > math::WORLD_MIN - c;
	}

	// The same test where the engine's code has it inline
	static inline bool IsAboveInline(const XZLine* line, const math::Vector* point)
	{
		return point->z * line->b + point->x * line->a > math::WORLD_MIN - line->c;
	}

	// FUNCTION: ENGINE 0x10668120
	// EQUIVALENT: the same differences, cross product, call to Normalize and dot product in the same order; two difference registers are swapped and the dot product multiplies the operands the other way round, 92.2 %
	float MeshFaceRef::GetSlope() const
	{
		static math::Vector down(0.0f, -1.0f, 0.0f);
		math::Triangle triangle;
		GetWorldTriangle(&triangle);
		math::Vector first;
		math::Vector second;
		first.y = triangle.a.y - triangle.b.y;
		second.z = triangle.a.z - triangle.c.z;
		second.x = triangle.a.x - triangle.c.x;
		second.y = triangle.a.y - triangle.c.y;
		first.x = triangle.a.x - triangle.b.x;
		first.z = triangle.a.z - triangle.b.z;
		math::Vector normal;
		normal.Cross(first, second);
		normal.Normalize();
		return down.Dot(normal) + engine::driving::gOne;
	}

	// FUNCTION: ENGINE 0x10668220
	int MeshFaceRef::FindCornerXZ(const XZLine* line, const math::Vector* point) const
	{
		int result = 0xffff;
		math::Triangle triangle;
		GetWorldTriangle(&triangle);
		if (!triangle.ContainsXZ(*point))
		{
			bool first = IsAboveInline(line, &triangle.a);
			bool second = IsAboveInline(line, &triangle.b);
			if (first && !second)
			{
				result = 0;
			}
			else
			{
				bool third = IsAboveInline(line, &triangle.c);
				if (second && !third)
				{
					result = 1;
				}
				else if (third && !first)
				{
					result = 2;
				}
			}
		}
		return result;
	}
}

namespace math
{
	// FUNCTION: ENGINE 0x106672E0
	// EQUIVALENT: the same differences, products and call to Normalize; two temporaries swap their registers, 92.1 %
	void Triangle::GetNormal(Vector* normal) const
	{
		Vector first;
		Vector second;
		second.x = a.x - c.x;
		first.y = a.y - b.y;
		second.z = a.z - c.z;
		second.y = a.y - c.y;
		first.x = a.x - b.x;
		first.z = a.z - b.z;
		normal->Cross(first, second);
		normal->Normalize();
	}
}

// Kept copies of inline functions and template members this unit makes (compiler-made or header-defined, so the
// annotations stand without a definition)
// FUNCTION: ENGINE 0x106677A0
