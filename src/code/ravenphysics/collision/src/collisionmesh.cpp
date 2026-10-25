// The mesh volume's own functions, kept apart from the unit that calls them (their definitions are not visible to the
// compiler there). The file name is a guess.
#include "code/ravenphysics/collision/collisionobject.h"

namespace ravenphysics
{
	// FUNCTION: ENGINE 0x10665DA0
	void CollisionVolume6::PrintMesh()
	{
	}

	// FUNCTION: ENGINE 0x10662960
	unsigned short GridFace::GetVertex(int index) const
	{
		return vertex[index];
	}

	// FUNCTION: ENGINE 0x10662970
	math::Vector* CollisionVolume6::GetVertex(unsigned short index)
	{
		return grid.vertices + index;
	}

	// FUNCTION: ENGINE 0x10662990
	unsigned short* CollisionVolume6::GetNeighbours(unsigned short face)
	{
		return grid.slot->unknown4 + face * 3;
	}

	// FUNCTION: ENGINE 0x10662E40
	void MeshSlot::SetRecordSize(unsigned int size)
	{
		unknownC = size;
	}

	// FUNCTION: ENGINE 0x10663DF0
	math::Vector* CollisionVolume3::GetWorld()
	{
		return &world;
	}

	// FUNCTION: ENGINE 0x10663E00
	void CollisionVolume3::UpdateBounds()
	{
		bounds.SetTransformed(matrix, localBox);
	}

	// FUNCTION: ENGINE 0x10663E20
	CollisionVolume3* CollisionVolume4::GetMaterials()
	{
		return &materials;
	}
}
