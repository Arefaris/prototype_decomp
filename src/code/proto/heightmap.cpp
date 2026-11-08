#include "code/proto/heightmap.h"
#include <math.h>
#include <new>
#include <string.h>

namespace engine
{
	namespace driving
	{
		extern const float gOne;
		extern const float gHalf;
	}
}

namespace proto
{

#define PROTO_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x10393120
	content::ClassInfo* Heightmap::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::Heightmap";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10394BC0
	content::MemberList* Heightmap::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Heightmap, float, 0>("p"),
				PROTO_OFFSET(Heightmap, gridSize), "gridSize" },
			{ content::GetMemberPrimitiveMetaType<Heightmap, int, 0>("p"),
				PROTO_OFFSET(Heightmap, sizeX), "sizex" },
			{ content::GetMemberPrimitiveMetaType<Heightmap, int, 1>("p"),
				PROTO_OFFSET(Heightmap, sizeY), "sizey" },
			{ content::GetMemberPrimitiveMetaType<Heightmap, int, 2>("p"),
				PROTO_OFFSET(Heightmap, marginX), "marginx" },
			{ content::GetMemberPrimitiveMetaType<Heightmap, int, 3>("p"),
				PROTO_OFFSET(Heightmap, marginY), "marginy" },
			{ content::GetMemberVectorMetaType<Heightmap, 0>("p"), 0x20, "minVec" },
			{ content::GetMemberPrimitiveMetaType<Heightmap, float, 1>("p"),
				PROTO_OFFSET(Heightmap, minHeight), "minHeight" },
			{ content::GetMemberPrimitiveMetaType<Heightmap, float, 2>("p"),
				PROTO_OFFSET(Heightmap, maxHeight), "maxHeight" },
			{ content::GetMemberPrimitiveMetaType<Heightmap, float, 3>("p"),
				PROTO_OFFSET(Heightmap, quantum), "quantum" },
			{ content::GetClassMetaType<math::AABB>(), PROTO_OFFSET(Heightmap, aabb), "aabb" },
			{ content::GetArrayDynamicMetaType<Heightmap, HeightArray>(
				content::GetMemberPrimitiveMetaType<Heightmap, unsigned short, 0>("p"), "p"),
				PROTO_OFFSET(Heightmap, data), "data" }
		};
		sList.members = sMembers;
		sList.count = 11;
		return &sList;
	}

	// FUNCTION: ENGINE 0x103954E0
	Heightmap::Heightmap() : gridSize(0.0f), inverseGridSize(0.0f), sizeX(0), sizeY(0), marginX(0), marginY(0), minVec(math::kZeroVector), minHeight(0.0f),
		maxHeight(0.0f), quantum(0.0f)
	{
		aabb.Reset();
		pool.Init(0, 0x14, 0x1000, core::GetCurrentHeap(), "HeightmapPool", 0x10);
	}

	// FUNCTION: ENGINE 0x10395080
	Heightmap::~Heightmap()
	{
		data.Free();
		sizeY = 0;
		sizeX = 0;
		HeightCache::Iterator iterator(&cache);
		for (void* item = iterator.First(); item != 0; item = iterator.Next())
		{
			pool.Free(item);
		}
		cache.Clear();
	}

	// FUNCTION: ENGINE 0x103902C0
	void HeightCache::Resize(unsigned int count)
	{
		core::HeapScope scope(heap);
		unsigned int oldCount = bucketCount;
		void** oldSlots = slots;
		int* oldKeys = keys;
		bucketCount = count;
		slots = new void*[count];
		keys = new int[bucketCount];
		removedCount = 0;
		usedCount = 0;
		for (unsigned int i = 0; i < bucketCount; i++)
		{
			slots[i] = 0;
			keys[i] = 0;
		}
		if (oldSlots != 0)
		{
			for (unsigned int i = 0; i < oldCount; i++)
			{
				if (oldSlots[i] != 0 && oldSlots[i] != &removedMarker)
				{
					Insert(&oldKeys[i], oldSlots[i]);
				}
			}
			operator delete[](oldSlots);
			operator delete[](oldKeys);
		}
	}

	// FUNCTION: ENGINE 0x1038DCA0
	// NONMATCHING: the engine schedules the stores of the key, start and step differently around the register saves (6.5 %)
#ifdef NONMATCHING
	void* HeightCache::Probe::StartInsert(const int* newKey)
	{
		key = *newKey;
		int hash = *newKey;
		start = Mask(hash);
		step = Step(hash);
		unsigned int position = start;
		while (table->slots[position] != 0 && table->keys[position] != key
			&& table->slots[position] != &table->removedMarker)
		{
			position = (position + step) & (table->bucketCount - 1);
			if (position == start)
			{
				current = position;
				return 0;
			}
		}
		current = position;
		return table->slots[position];
	}
#endif

	// FUNCTION: ENGINE 0x1038DC00
	// NONMATCHING: the engine schedules the stores of the key, start and step differently around the register saves (9.5 %)
#ifdef NONMATCHING
	void* HeightCache::Probe::Find(const int* newKey)
	{
		key = *newKey;
		int hash = *newKey;
		start = Mask(hash);
		step = Step(hash);
		unsigned int position = start;
		while ((table->slots[position] != 0 && table->keys[position] != key)
			|| table->slots[position] == &table->removedMarker)
		{
			position = (position + step) & (table->bucketCount - 1);
			if (position == start)
			{
				current = position;
				return 0;
			}
		}
		current = position;
		return table->slots[position];
	}
#endif

	// FUNCTION: ENGINE 0x1038CA20
	void* HeightCache::Probe::Next()
	{
		unsigned int position = (current + step) & (table->bucketCount - 1);
		while (table->slots[position] != 0 && table->keys[position] != key
			&& table->slots[position] != &table->removedMarker)
		{
			if (position == start)
			{
				current = position;
				return 0;
			}
			position = (position + step) & (table->bucketCount - 1);
		}
		current = position;
		return table->slots[position];
	}

	// FUNCTION: ENGINE 0x10393340
	// NONMATCHING: the engine hoists the mask before the position (83.5 %)
#ifdef NONMATCHING
	void* HeightCache::Probe::FindNext()
	{
		unsigned int position = current;
		do
		{
			position = (position + step) & (table->bucketCount - 1);
			if ((table->slots[position] == 0 || table->keys[position] == key)
				&& table->slots[position] != &table->removedMarker)
			{
				break;
			}
			if (position == start)
			{
				current = position;
				return 0;
			}
		}
		while (true);
		current = position;
		return table->slots[position];
	}
#endif

	// FUNCTION: ENGINE 0x103901B0
	// NONMATCHING: the engine keeps the index of the slot in a register for both stores (69.1 %)
#ifdef NONMATCHING
	void HeightCache::Insert(const int* key, void* item)
	{
		Probe probe(this);
		void* found = probe.StartInsert(key);
		while (found != 0 && found != &probe.table->removedMarker)
		{
			found = probe.Next();
		}
		void** slot = &slots[probe.current];
		if (*slot == &removedMarker)
		{
			removedCount--;
		}
		*slot = item;
		keys[probe.current] = *key;
		usedCount++;
		if (usedCount * 100 / bucketCount > maxLoadPercent)
		{
			Resize(bucketCount * 2);
		}
	}
#endif

	// FUNCTION: ENGINE 0x10394E80
	void HeightCache::Rehash()
	{
		void** slotCopy = (void**)core::HeapAlloc(1, bucketCount * 4);
		memcpy(slotCopy, slots, bucketCount * 4);
		int* keyCopy = (int*)core::HeapAlloc(1, bucketCount * 4);
		for (unsigned int i = 0; i < bucketCount; i++)
		{
			keyCopy[i] = keys[i];
		}
		removedCount = 0;
		usedCount = 0;
		for (unsigned int i = 0; i < bucketCount; i++)
		{
			slots[i] = 0;
			keys[i] = 0;
		}
		for (unsigned int i = 0; i < bucketCount; i++)
		{
			if (slotCopy[i] != 0 && slotCopy[i] != &removedMarker)
			{
				Insert(&keyCopy[i], slotCopy[i]);
			}
		}
		core::Free(slotCopy);
		core::Free(keyCopy);
	}

	// FUNCTION: ENGINE 0x103951F0
	int HeightCache::Remove(void* item)
	{
		int removed = 0;
		for (unsigned int i = 0; i < bucketCount; i++)
		{
			if (slots[i] == item)
			{
				slots[i] = &removedMarker;
				keys[i] = 0;
				removedCount++;
				removed++;
				usedCount--;
			}
		}
		if (shrinks && removedCount > maxRemoved)
		{
			Rehash();
		}
		return removed;
	}

	// FUNCTION: ENGINE 0x103937F0
	void Heightmap::SetHeight(int x, int y, float height)
	{
		if (x >= 0 && x < sizeX && y >= 0 && y < sizeY)
		{
			data[sizeY * x + y] = (unsigned short)(int)((height - minHeight) / quantum);
		}
	}

	// FUNCTION: ENGINE 0x10393D90
	float Heightmap::GetHeight(int x, int y)
	{
		if (x >= 0 && x < sizeX && y >= 0 && y < sizeY)
		{
			float stored = (float)data[sizeY * x + y];
			if (stored > 20000.0f)
			{
				return stored;
			}
			return quantum * stored + minHeight;
		}
		return 20001.0f;
	}

	// FUNCTION: ENGINE 0x10394640
	// NONMATCHING: ours unrolls the inner loop four times, the engine's does not (3.9 %)
#ifdef NONMATCHING
	void Heightmap::FillWindow(int x, int y, unsigned int size, int margin, bool outsideHigh)
	{
		int firstX;
		int firstY;
		int count;
		if ((size & 1) == 0)
		{
			size = size >> 1;
			firstY = (y - size) - margin;
			firstX = ((x - size) - margin) + 1;
			count = (margin + size) * 2;
		}
		else
		{
			unsigned int half = (size - 1) >> 1;
			firstX = (x - half) - margin;
			firstY = (y - half) - margin;
			count = (half + margin) * 2 + 1;
		}
		window.originX = firstX;
		window.originY = firstY;
		for (int j = 0; j < count; j++)
		{
			int cellX = firstX;
			for (int i = 0; i < count; i++)
			{
				float height;
				if (cellX < 0 || cellX >= sizeX || j + firstY < 0 || j + firstY >= sizeY ||
					(height = (float)data[cellX * sizeY + j + firstY]) > 20000.0f)
				{
					height = outsideHigh ? 65535.0f : 0.0f;
				}
				else
				{
					height = quantum * height + minHeight;
				}
				window.values[(((j - window.originY) + firstY) * 6 - window.originX) + i + firstX] = height;
				cellX++;
			}
		}
	}

#endif

	// FUNCTION: ENGINE 0x1038C160
	float Heightmap::GetWindowHeight(int x, int y)
	{
		return window.values[(y - window.originY) * 6 - window.originX + x];
	}

	// FUNCTION: ENGINE 0x1038C180
	// NONMATCHING: the engine computes the cell index first and keeps the output in eax (61.1 %)
#ifdef NONMATCHING
	void Heightmap::GetWindowPoint(math::Vector* out, int x, int y)
	{
		float size = gridSize;
		out->x = (float)x * size + minVec.x;
		out->y = window.values[(y - window.originY) * 6 - window.originX + x] + minVec.y;
		out->z = (float)y * size + minVec.z;
	}

#endif

	// FUNCTION: ENGINE 0x1038C1F0
	// NONMATCHING: the same order of the index and the output registers (best 10.9 %)
#ifdef NONMATCHING
	void Heightmap::GetWindowCellCenter(math::Vector* out, int x, int y)
	{
		float size = gridSize;
		float half = size * engine::driving::gHalf;
		out->x = (float)x * size + minVec.x + half;
		out->y = window.values[(y - window.originY) * 6 - window.originX + x] + minVec.y;
		out->z = ((float)y * size - half) + minVec.z;
	}

#endif

	// FUNCTION: ENGINE 0x103951D0
	void Heightmap::Slot3(int unused)
	{
	}

	// FUNCTION: ENGINE 0x10393160
	// NONMATCHING: the engine stores the inverse grid size after reserving the call frame (88 %)
#ifdef NONMATCHING
	bool Heightmap::Slot5()
	{
		inverseGridSize = engine::driving::gOne / gridSize;
		halfRows = (int)ceil((float)sizeY * engine::driving::gHalf);
		return true;
	}
#endif
}


template class container::ArrayDynamic<unsigned short, container::AllocatorNew>;


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x103931B0
// FUNCTION: ENGINE 0x103931C0
// FUNCTION: ENGINE 0x103931F0
// FUNCTION: ENGINE 0x10393250
// FUNCTION: ENGINE 0x103932C0
// FUNCTION: ENGINE 0x103932F0
// FUNCTION: ENGINE 0x103933B0
// FUNCTION: ENGINE 0x103933F0
// FUNCTION: ENGINE 0x10393400
// FUNCTION: ENGINE 0x103937E0
// FUNCTION: ENGINE 0x10393850
// FUNCTION: ENGINE 0x10393870
// FUNCTION: ENGINE 0x103938C0
// FUNCTION: ENGINE 0x103938D0
// FUNCTION: ENGINE 0x10393910
// FUNCTION: ENGINE 0x10393950
// FUNCTION: ENGINE 0x10393990
// FUNCTION: ENGINE 0x103939D0
// FUNCTION: ENGINE 0x10393A10
// FUNCTION: ENGINE 0x10393A50
// FUNCTION: ENGINE 0x10393A90
// FUNCTION: ENGINE 0x10393AD0
// FUNCTION: ENGINE 0x10393B20
// FUNCTION: ENGINE 0x10393B30
// FUNCTION: ENGINE 0x10393B50
// FUNCTION: ENGINE 0x10393B70
// FUNCTION: ENGINE 0x10393BD0
// FUNCTION: ENGINE 0x10393BE0
// FUNCTION: ENGINE 0x10393BF0
// FUNCTION: ENGINE 0x10393C10
// FUNCTION: ENGINE 0x10393C30
// FUNCTION: ENGINE 0x10393C60
// FUNCTION: ENGINE 0x10393CD0
// FUNCTION: ENGINE 0x10393CF0
// FUNCTION: ENGINE 0x10393D10
// FUNCTION: ENGINE 0x10393D50
// FUNCTION: ENGINE 0x10394960
// FUNCTION: ENGINE 0x103949E0
// FUNCTION: ENGINE 0x103949F0
// FUNCTION: ENGINE 0x10394A50
// FUNCTION: ENGINE 0x10394AA0
// FUNCTION: ENGINE 0x10394E60
// FUNCTION: ENGINE 0x10394F90
// FUNCTION: ENGINE 0x10395260
// FUNCTION: ENGINE 0x103952B0
