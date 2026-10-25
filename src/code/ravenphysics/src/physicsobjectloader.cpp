// The loader of the physics content (RTTI: ravenphysics::PhysicsObjectLoader) and what it keeps in its lists: unit
// 0x1067C400 - 0x1067F800, no assert path, so the file name is a guess. Its chunk handler is in
// pure3d/loaders/loader1067f4d0.cpp.
#include "code/content/chunkhandler.h"
#include "code/content/loadinventory.h"
#include "code/core/heap.h"
#include "code/core/refptr.h"
#include "code/ravenphysics/constraints/constraints.h"
#include "code/ravenphysics/context.h"
#include "code/ravenphysics/massproperties.h"
#include "code/ravenphysics/collisionvolumefactory.h"
#include "code/ravenphysics/material.h"
#include "code/ravenphysics/physicsobjectloader.h"
#include <new>

namespace ravenphysics
{
	// The class meta types of the constraints (0x1065D3D0 - 0x1065DDD0, another unit: the engine keeps one instance of
	// each there; names guessed)
	content::ClassMetaType* GetBallInSocketMetaType();
	content::ClassMetaType* GetHingeMetaType();
	content::ClassMetaType* GetInsideOfConeMetaType();
	content::ClassMetaType* GetInsideOfSphereMetaType();
	content::ClassMetaType* GetAlign2AxesMetaType();
	content::ClassMetaType* GetSliderMetaType();
	content::ClassMetaType* GetSpringAlongAxisMetaType();
	content::ClassMetaType* GetAngularSpringMetaType();
	content::ClassMetaType* GetAngularVelocityMetaType();
	content::ClassMetaType* GetPerpendicular2AxesMetaType();

	// The object of the name in one of the lists, or else the one the inventory has under it (and then kept in the list
	// when there is room); null for none
	template<class T>
	T* FindLoaded(content::LoadInventory* inventory, const char* text, LoaderList* list)
	{
		core::Name<core::CaseSensitiveKey> name(text, 1);
		LoaderEntry* entries = list->begin;
		for (unsigned int i = 0; i < (unsigned int)(list->end - entries); i++)
		{
			if (entries[i].name == name)
			{
				return (T*)entries[i].object;
			}
		}
		T* found = inventory->Find<T>(name);
		if (found != 0)
		{
			LoaderEntry* last = list->end;
			LoaderEntry* limit = list->capacity;
			if (last != limit)
			{
				LoaderEntry entry;
				entry.name = name;
				entry.object = found;
				if (last < limit)
				{
					list->end = last + 1;
					if (last != 0)
					{
						new (last) LoaderEntry(entry);
					}
				}
			}
		}
		return found;
	}

	// FUNCTION: ENGINE 0x1067D4F0
	// EQUIVALENT: the same search, call of the inventory and append in the same order; the engine keeps the list in esi, the first entry in ebp, the index in edi and the entry in ebx, ours rotates the four, 72.5 %
	template MaterialLoader* FindLoaded<MaterialLoader>(content::LoadInventory*, const char*, LoaderList*);
	// FUNCTION: ENGINE 0x1067D5D0
	// EQUIVALENT: the same search, call of the inventory and append in the same order; the engine keeps the list in esi, the first entry in ebp, the index in edi and the entry in ebx, ours rotates the four, 72.5 %
	template IntersectionPropertiesLoader* FindLoaded<IntersectionPropertiesLoader>(content::LoadInventory*, const char*,
		LoaderList*);
	// FUNCTION: ENGINE 0x1067D6B0
	// EQUIVALENT: the same search, call of the inventory and append in the same order; the engine keeps the list in esi, the first entry in ebp, the index in edi and the entry in ebx, ours rotates the four, 72.5 %
	template MassProperties* FindLoaded<MassProperties>(content::LoadInventory*, const char*, LoaderList*);

	// The creators of the constraints the loader reads: a new constraint of the kind and the meta type of its class
	// (names guessed)
	// FUNCTION: ENGINE 0x1067CA80
	void CreateBallInSocket(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintBallInSocket;
		*type = GetBallInSocketMetaType();
	}

	// FUNCTION: ENGINE 0x1067CAC0
	void CreateHinge(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintHinge;
		*type = GetHingeMetaType();
	}

	// FUNCTION: ENGINE 0x1067CB00
	void CreateInsideOfCone(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintInsideOfCone;
		*type = GetInsideOfConeMetaType();
	}

	// FUNCTION: ENGINE 0x1067CB40
	void CreateInsideOfSphere(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintInsideOfSphere;
		*type = GetInsideOfSphereMetaType();
	}

	// FUNCTION: ENGINE 0x1067CB80
	void CreateAlign2Axes(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintAlign2Axes;
		*type = GetAlign2AxesMetaType();
	}

	// FUNCTION: ENGINE 0x1067CBC0
	void CreateSlider(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintSlider;
		*type = GetSliderMetaType();
	}

	// FUNCTION: ENGINE 0x1067CC40
	void CreateSpringAlongAxis(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintSpringAlongAxis;
		*type = GetSpringAlongAxisMetaType();
	}

	// FUNCTION: ENGINE 0x1067CC80
	void CreateAngularSpring(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintAngularSpring;
		*type = GetAngularSpringMetaType();
	}

	// FUNCTION: ENGINE 0x1067CCC0
	void CreateAngularVelocity(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintAngularVelocity;
		*type = GetAngularVelocityMetaType();
	}

	// FUNCTION: ENGINE 0x1067CD80
	void CreatePerpendicular2Axes(Constraint** object, content::ClassMetaType** type)
	{
		*object = new ConstraintPerpendicular2Axes;
		*type = GetPerpendicular2AxesMetaType();
	}
}

namespace ravenphysics
{
	// Room for count items from the current heap, 16-byte aligned (names guessed; one instance for each item size)
	template<class T>
	T* AllocateItems(int count)
	{
		return (T*)core::HeapAllocAligned(core::GetCurrentHeap(), (count * sizeof(T) + 0x1f) & 0xfffffff0, 16);
	}

	// Three 16-bit numbers
	struct UShort3
	{
		unsigned short values[3];
	};

	// FUNCTION: ENGINE 0x1067C6F0
	template math::Vector* AllocateItems<math::Vector>(int);
	// FUNCTION: ENGINE 0x1067C720
	template GridFace* AllocateItems<GridFace>(int);
	// FUNCTION: ENGINE 0x1067C740
	template UShort3* AllocateItems<UShort3>(int);
	// FUNCTION: ENGINE 0x1067C760
	template unsigned short* AllocateItems<unsigned short>(int);

	// One word of the stream
	static inline unsigned int ReadWord(content::ChunkReader* reader)
	{
		unsigned int value;
		reader->Read(&value, 1, 4, 1);
		return value;
	}

	// One word of the stream as a float
	static inline float ReadFloatWord(content::ChunkReader* reader)
	{
		union
		{
			unsigned int word;
			float number;
		} value;
		reader->Read(&value.word, 1, 4, 1);
		return value.number;
	}

	// Reads the properties of the faces of a mesh out of their chunk (0x1067DB30; name guessed)
	void ReadFaceProperties(content::ChunkReader* reader, CollisionMeshFactory* factory);

	// One float of the stream
	static inline float ReadFloatValue(content::ChunkReader* reader)
	{
		float value;
		reader->Read(&value, 1, 4, 1);
		return value;
	}

	// Reads a convex hull: its box, centre, vertices, edges and faces, then the chunks of its tables, material and
	// properties (name guessed)
	// FUNCTION: ENGINE 0x1067D7C0
	void ReadConvexHull(CollisionConvexHullFactory* factory, content::ChunkReader* reader,
		content::LoadInventory* inventory)
	{
		ConvexHullData* hull = factory->hull->data;
		unsigned char propertiesLength;
		unsigned char materialLength;
		char text[0x100];
		ReadWord(reader);
		reader->Read(&hull->bounds.min, 3, 4, 1);
		reader->Read(&hull->bounds.max, 3, 4, 1);
		reader->Read(&hull->centre, 3, 4, 1);
		unsigned int vertices = ReadWord(reader);
		hull->vertexCount = (unsigned short)vertices;
		hull->vertices = new math::Vector[hull->vertexCount];
		reader->Read(hull->vertices, hull->vertexCount * 3, 4, 1);
		unsigned int edges = ReadWord(reader);
		hull->edgeCount = (unsigned short)(edges >> 1);
		hull->edges = (unsigned char*)new unsigned short[hull->edgeCount];
		reader->Read(hull->edges, hull->edgeCount * 2, 1, 1);
		unsigned int faces = ReadWord(reader);
		hull->faceCount = (unsigned short)faces;
		hull->faces = new math::Plane[hull->faceCount];
		reader->Read(hull->faces, hull->faceCount * 4, 4, 1);
		if (reader->HasChunk())
		{
			do
			{
				reader->BeginChunk();
				switch (reader->GetChunkId())
				{
				case 0x7021802:
					{
						reader->Read(&propertiesLength, 1, 1, 1);
						unsigned int length = propertiesLength;
						reader->Read(text, length, 1, 1);
						text[length] = 0;
						IntersectionPropertiesLoader* properties = FindLoaded<IntersectionPropertiesLoader>(inventory, text,
							&gStatArrayB);
						if (properties != 0)
						{
							core::RefAssign(factory->intersectionProperties, properties);
						}
					}
					break;
				case 0x7021801:
					{
						reader->Read(&materialLength, 1, 1, 1);
						unsigned int length = materialLength;
						reader->Read(text, length, 1, 1);
						text[length] = 0;
						MaterialLoader* material = FindLoaded<MaterialLoader>(inventory, text, &gStatArrayA);
						if (material != 0)
						{
							core::RefAssign(factory->material, material);
						}
					}
					break;
				case 0x7021006:
					{
						unsigned int size = ReadWord(reader);
						hull->unknown38 = size;
						hull->unknown44 = new char[size];
						reader->Read(hull->unknown44, size, 1, 1);
						unsigned int words = ReadWord(reader);
						hull->unknown3C = words;
						hull->unknown48 = new unsigned short[words];
						reader->Read(hull->unknown48, words, 2, 1);
						hull->unknown40 = ReadWord(reader);
						hull->unknown4C = new char[8];
						reader->Read(hull->unknown4C, 8, 1, 1);
					}
					break;
				}
				reader->EndChunk();
			}
			while (reader->HasChunk());
		}
	}

	// Reads a mesh: the box and the scale of its grid, the vertices, the triangles with their neighbours, the tree, then
	// the chunks of its material, the properties of its faces and its own properties (name guessed)
	// FUNCTION: ENGINE 0x1067E5B0
	// EQUIVALENT: the same reads, allocations and calls in the same order; the frame differs only in the places of the local words (the engine keeps the word read last at esp+0x10, ours at esp+0x18) , 97.4 %
	void ReadMeshGrid(CollisionMeshFactory* factory, content::ChunkReader* reader, content::LoadInventory* inventory)
	{
		BroadPhaseGrid* grid = factory->grid;
		MeshSlot* slot = grid->slot;
		ReadWord(reader);
		reader->Read(&grid->bounds.min, 3, 4, 1);
		reader->Read(&grid->bounds.max, 3, 4, 1);
		unsigned int vertices = ReadWord(reader);
		grid->unknown90 = (unsigned short)vertices;
		grid->vertices = AllocateItems<math::Vector>((unsigned short)vertices);
		reader->Read(grid->vertices, grid->unknown90 * 3, 4, 1);
		unsigned int faces = ReadWord(reader);
		if (faces != 0)
		{
			grid->unknown92 = (unsigned short)faces;
			grid->faces = AllocateItems<GridFace>((unsigned short)faces);
			reader->Read(grid->faces, grid->unknown92 * 4, 2, 1);
		}
		faces = ReadWord(reader);
		if (faces != 0)
		{
			grid->unknown92 = (unsigned short)faces;
			grid->faces = AllocateItems<GridFace>((unsigned short)faces);
			slot->unknown4 = (unsigned short*)AllocateItems<UShort3>(grid->unknown92);
			for (int i = 0; i < grid->unknown92; i++)
			{
				unsigned short first;
				unsigned short second;
				unsigned short third;
				unsigned short fourth;
				unsigned short fifth;
				unsigned short sixth;
				unsigned int seventh;
				reader->Read(&first, 1, 2, 1);
				grid->faces[i].vertex[0] = first;
				reader->Read(&second, 1, 2, 1);
				grid->faces[i].vertex[1] = second;
				reader->Read(&third, 1, 2, 1);
				grid->faces[i].vertex[2] = third;
				reader->Read(&fourth, 1, 2, 1);
				grid->faces[i].flags = fourth;
				reader->Read(&fifth, 1, 2, 1);
				slot->unknown4[i * 3] = fifth;
				reader->Read(&sixth, 1, 2, 1);
				slot->unknown4[i * 3 + 1] = sixth;
				reader->Read(&seventh, 1, 2, 1);
				slot->unknown4[i * 3 + 2] = (unsigned short)seventh;
			}
		}
		grid->unknown8C = ReadWord(reader);
		grid->tree = AllocateItems<unsigned short>(grid->unknown8C);
		reader->Read(grid->tree, grid->unknown8C, 2, 1);
		grid->unknown8C = grid->unknown8C * 2;
		reader->Read(&grid->scale, 3, 4, 1);
		grid->unknownC4 = ReadFloatWord(reader);
		grid->unknownC8 = false;
		if (reader->HasChunk())
		{
			do
			{
				reader->BeginChunk();
				switch (reader->GetChunkId())
				{
				case 0x7021801:
					{
						unsigned char materialLength;
						char text[0x100];
						reader->Read(&materialLength, 1, 1, 1);
						unsigned int length = materialLength;
						reader->Read(text, length, 1, 1);
						text[length] = 0;
						MaterialLoader* material = FindLoaded<MaterialLoader>(inventory, text, &gStatArrayA);
						if (material != 0)
						{
							core::RefAssign(factory->material, material);
							unsigned char index = material->index;
							for (unsigned int i = 0; i < grid->unknown92; i++)
							{
								GridFace* face = grid->faces + i;
								face->flags = (face->flags & 0xfe07) | (unsigned short)((index & 0x3f) << 3);
							}
						}
					}
					break;
				case 0x7016000:
					ReadFaceProperties(reader, factory);
					break;
				case 0x7021008:
					ReadWord(reader);
					slot->unknown4 = (unsigned short*)new UShort3[grid->unknown92];
					reader->Read(slot->unknown4, grid->unknown92 * 3, 2, 1);
					break;
				case 0x7021802:
					{
						unsigned char propertiesLength;
						char text[0x100];
						reader->Read(&propertiesLength, 1, 1, 1);
						unsigned int length = propertiesLength;
						reader->Read(text, length, 1, 1);
						text[length] = 0;
						IntersectionPropertiesLoader* properties = FindLoaded<IntersectionPropertiesLoader>(inventory, text,
							&gStatArrayB);
						if (properties != 0)
						{
							core::RefAssign(factory->intersectionProperties, properties);
							unsigned short index = properties->index;
							for (unsigned int i = 0; i < grid->unknown92; i++)
							{
								GridFace* face = grid->faces + i;
								face->flags = (face->flags & 0x81ff) | (unsigned short)((index & 0x3f) << 9);
							}
						}
					}
					break;
				}
				reader->EndChunk();
			}
			while (reader->HasChunk());
		}
	}
}

namespace content
{
	// FUNCTION: ENGINE 0x1067C400
	float ChunkStream::ReadFloat()
	{
		float value;
		Read(&value, 1, 4, 1);
		return value;
	}

	// FUNCTION: ENGINE 0x1067C420
	float ChunkReader::ReadFloat()
	{
		float value;
		Read(&value, 1, 4, 1);
		return value;
	}

	// FUNCTION: ENGINE 0x1067C440
	void ChunkReader::ReadVector(math::Vector* vector)
	{
		Read(vector, 3, 4, 1);
	}
}
