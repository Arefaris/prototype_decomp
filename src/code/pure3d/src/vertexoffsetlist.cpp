// pure3d::VertexOffsetList (unit around 0x1073EC50 - 0x1073F8B0; file name guessed from the class). Names are guesses.
#include <new>
#include <string.h>

#include "code/pure3d/primitive.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1073EF40
	void VertexOffsetList::BlendPosition(int vertex, const math::Vector* target, float weight)
	{
		math::Vector* offset = &positionOffsets[vertex];
		offset->x = (target->x - offset->x) * weight + offset->x;
		offset->y = (target->y - offset->y) * weight + offset->y;
		offset->z = (target->z - offset->z) * weight + offset->z;
	}

	// FUNCTION: ENGINE 0x1073EFB0
	void VertexOffsetList::BlendNormal(int vertex, const math::Vector* target, float weight)
	{
		math::Vector* offset = &normalOffsets[vertex];
		offset->x = (target->x - offset->x) * weight + offset->x;
		offset->y = (target->y - offset->y) * weight + offset->y;
		offset->z = (target->z - offset->z) * weight + offset->z;
	}

	// FUNCTION: ENGINE 0x1073F020
	void VertexOffsetList::BlendUnknown18(int vertex, const math::Vector* target, float weight)
	{
		math::Vector* offset = &unknown18[vertex];
		offset->x = (target->x - offset->x) * weight + offset->x;
		offset->y = (target->y - offset->y) * weight + offset->y;
		offset->z = (target->z - offset->z) * weight + offset->z;
	}

	// FUNCTION: ENGINE 0x1073F090
	void VertexOffsetList::BlendTangent(int vertex, const math::Vector* target, float weight)
	{
		math::Vector* offset = &tangentOffsets[vertex];
		offset->x = (target->x - offset->x) * weight + offset->x;
		offset->y = (target->y - offset->y) * weight + offset->y;
		offset->z = (target->z - offset->z) * weight + offset->z;
	}

	// FUNCTION: ENGINE 0x1073F100
	void VertexOffsetList::BlendTexCoords(int vertex, const math::Vector2* target, int set, float weight)
	{
		math::Vector2* offset = &texCoordOffsets[set][vertex];
		offset->x = (target->x - offset->x) * weight + offset->x;
		offset->y = (target->y - offset->y) * weight + offset->y;
	}

	// FUNCTION: ENGINE 0x1073F150
	void VertexOffsetList::BlendColour(int vertex, const ColourOffset* target, int set, float weight)
	{
		colourOffsets[set][vertex].x = (short)(int)((float)(target->x - colourOffsets[set][vertex].x) * weight) +
			colourOffsets[set][vertex].x;
		colourOffsets[set][vertex].y = (short)(int)((float)(target->y - colourOffsets[set][vertex].y) * weight) +
			colourOffsets[set][vertex].y;
		colourOffsets[set][vertex].z = (short)(int)((float)(target->z - colourOffsets[set][vertex].z) * weight) +
			colourOffsets[set][vertex].z;
		colourOffsets[set][vertex].w = (short)(int)((float)(target->w - colourOffsets[set][vertex].w) * weight) +
			colourOffsets[set][vertex].w;
	}

	// FUNCTION: ENGINE 0x1073F220
	void VertexOffsetList::Prepare()
	{
		if (positionOffsets != 0)
		{
			memset(positionOffsets, 0, count * sizeof(math::Vector));
		}
		if (normalOffsets != 0)
		{
			memset(normalOffsets, 0, count * sizeof(math::Vector));
		}
		if (unknown18 != 0)
		{
			memset(unknown18, 0, count * sizeof(math::Vector));
		}
		if (tangentOffsets != 0)
		{
			memset(tangentOffsets, 0, count * sizeof(math::Vector));
		}
		for (int i = 0; i < 4; i++)
		{
			if (texCoordOffsets[i] != 0)
			{
				memset(texCoordOffsets[i], 0, count * sizeof(math::Vector2));
			}
		}
		for (int i = 0; i < 2; i++)
		{
			if (colourOffsets[i] != 0)
			{
				memset(colourOffsets[i], 0, count * sizeof(ColourOffset));
			}
		}
	}

	// FUNCTION: ENGINE 0x1073F300
	void VertexOffsetList::AllocatePositions()
	{
		if (positionOffsets == 0)
		{
			positionOffsets = new math::Vector[count];
			flags |= 0x10;
		}
	}

	// FUNCTION: ENGINE 0x1073F330
	void VertexOffsetList::FreePositions()
	{
		delete[] positionOffsets;
		flags &= ~0x10;
		positionOffsets = 0;
	}

	// FUNCTION: ENGINE 0x1073F350
	void VertexOffsetList::AllocateNormals()
	{
		if (normalOffsets == 0)
		{
			normalOffsets = new math::Vector[count];
			flags |= 0x20;
		}
	}

	// FUNCTION: ENGINE 0x1073F380
	void VertexOffsetList::FreeNormals()
	{
		delete[] normalOffsets;
		flags &= ~0x20;
		normalOffsets = 0;
	}

	// FUNCTION: ENGINE 0x1073F3A0
	void VertexOffsetList::AllocateUnknown18()
	{
		if (unknown18 == 0)
		{
			unknown18 = new math::Vector[count];
			flags |= 0x4000;
		}
	}

	// FUNCTION: ENGINE 0x1073F3E0
	void VertexOffsetList::FreeUnknown18()
	{
		delete[] unknown18;
		flags &= ~0x4000;
		unknown18 = 0;
	}

	// FUNCTION: ENGINE 0x1073F400
	void VertexOffsetList::AllocateTangents()
	{
		if (tangentOffsets == 0)
		{
			tangentOffsets = new math::Vector[count];
			flags |= 0x8000;
		}
	}

	// FUNCTION: ENGINE 0x1073F440
	void VertexOffsetList::FreeTangents()
	{
		delete[] tangentOffsets;
		flags &= ~0x8000;
		tangentOffsets = 0;
	}

	// FUNCTION: ENGINE 0x1073F460
	void VertexOffsetList::AllocateTexCoords(int set)
	{
		if (texCoordOffsets[set] == 0)
		{
			texCoordOffsets[set] = new math::Vector2[count];
			flags |= 1 << set;
		}
	}

	// FUNCTION: ENGINE 0x1073F4D0
	void VertexOffsetList::AllocateColours(int set)
	{
		if (colourOffsets[set] == 0)
		{
			colourOffsets[set] = new ColourOffset[count];
			flags |= 0x40 << set;
		}
	}

	// FUNCTION: ENGINE 0x1073F540
	void VertexOffsetList::FreeColours(int set)
	{
		delete[] colourOffsets[set];
		colourOffsets[set] = 0;
		flags &= ~(0x40 << set);
	}

	// FUNCTION: ENGINE 0x1073F590
	// EQUIVALENT: the engine stores the base vftable before it zeroes the register it keeps the zero in; ours stores it
	// after the flag test (96.4 %)
	VertexOffsetList::VertexOffsetList(int newCount, unsigned int newFlags)
		: RefCounted(NO_BARRIER)
	{
		flags = 0;
		count = newCount;
		positionOffsets = 0;
		normalOffsets = 0;
		unknown18 = 0;
		tangentOffsets = 0;
		texCoordOffsets[0] = 0;
		texCoordOffsets[1] = 0;
		texCoordOffsets[2] = 0;
		texCoordOffsets[3] = 0;
		colourOffsets[0] = 0;
		colourOffsets[1] = 0;
		if (newFlags != 0)
		{
			if (newFlags & 0x10)
			{
				AllocatePositions();
			}
			if (newFlags & 0x20)
			{
				AllocateNormals();
			}
			if (newFlags & 0x4000)
			{
				AllocateUnknown18();
			}
			if (newFlags & 0x8000)
			{
				AllocateTangents();
			}
			for (unsigned int i = 0; i < 4; i++)
			{
				if (newFlags & (1 << i))
				{
					AllocateTexCoords(i);
				}
			}
			for (unsigned int i = 0; i < 2; i++)
			{
				if (newFlags & (0x40 << i))
				{
					AllocateColours(i);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x1073F660
	VertexOffsetList::VertexOffsetList(const VertexOffsetList& other)
		: RefCounted(NO_BARRIER)
	{
		flags = other.flags;
		count = other.count;
		positionOffsets = 0;
		normalOffsets = 0;
		unknown18 = 0;
		tangentOffsets = 0;
		if (other.positionOffsets != 0)
		{
			AllocatePositions();
			memcpy(positionOffsets, other.positionOffsets, count * sizeof(math::Vector));
		}
		if (other.normalOffsets != 0)
		{
			AllocateNormals();
			memcpy(normalOffsets, other.normalOffsets, count * sizeof(math::Vector));
		}
		if (other.unknown18 != 0)
		{
			AllocateUnknown18();
			memcpy(unknown18, other.unknown18, count * sizeof(math::Vector));
		}
		if (other.tangentOffsets != 0)
		{
			AllocateTangents();
			memcpy(tangentOffsets, other.tangentOffsets, count * sizeof(math::Vector));
		}
		for (unsigned int i = 0; i < 4; i++)
		{
			texCoordOffsets[i] = 0;
			if (other.texCoordOffsets[i] != 0)
			{
				AllocateTexCoords(i);
				memcpy(texCoordOffsets[i], other.texCoordOffsets[i], count * sizeof(math::Vector2));
			}
		}
		for (unsigned int i = 0; i < 2; i++)
		{
			colourOffsets[i] = 0;
			if (other.colourOffsets[i] != 0)
			{
				AllocateColours(i);
				memcpy(colourOffsets[i], other.colourOffsets[i], count * sizeof(ColourOffset));
			}
		}
	}

	// FUNCTION: ENGINE 0x1073F7E0
	VertexOffsetList::~VertexOffsetList()
	{
		if (positionOffsets != 0)
		{
			delete[] positionOffsets;
		}
		if (normalOffsets != 0)
		{
			delete[] normalOffsets;
		}
		if (unknown18 != 0)
		{
			delete[] unknown18;
		}
		if (tangentOffsets != 0)
		{
			delete[] tangentOffsets;
		}
		for (int i = 0; i < 4; i++)
		{
			if (texCoordOffsets[i] != 0)
			{
				delete[] texCoordOffsets[i];
			}
		}
		for (int i = 0; i < 2; i++)
		{
			if (colourOffsets[i] != 0)
			{
				delete[] colourOffsets[i];
			}
		}
	}

	// FUNCTION: ENGINE 0x1073F880
	unsigned int VertexOffsetList::GetFlags()
	{
		return flags;
	}
}
