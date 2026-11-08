// pure3d::RenderPassChain (the object at +0x68 of the context; unit 0x1074D530 - 0x1074D760, the file name is a guess).
// Names are guesses.
#include "code/core/heap.h"
#include "code/core/memory/twowayallocator.h"
#include "code/pure3d/context.h"
#include "code/pure3d/pddi.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x1074D530
	RenderPassChain::RenderPassChain(int newHeap, int firstHeap, int secondHeap)
	{
		heap = newHeap;
		heapIndices[0] = firstHeap;
		currentHeap = 0;
		current = 0;
		size = 0;
		count = 0;
		maxCount = 0;
		allocators[1] = 0;
		allocators[0] = 0;
		heapIndices[1] = secondHeap;
		peaks[1] = 0;
		peaks[0] = 0;
		unknown38 = 0;
		query = 0;
	}

	// FUNCTION: ENGINE 0x1074D570
	void RenderPassChain::Destroy()
	{
		if (size != 0)
		{
			pddi->Unknown9();
			allocators[0]->Release();
			allocators[1]->Release();
			allocators[1] = 0;
			allocators[0] = 0;
			size = 0;
			peaks[1] = 0;
			peaks[0] = 0;
			count = 0;
			maxCount = 0;
			current = 0;
			currentHeap = heapIndices[0];
		}
	}

	// FUNCTION: ENGINE 0x1074D5C0
	void RenderPassChain::Create(unsigned int newSize, unsigned int newSize2)
	{
		if (size > 0)
		{
			Destroy();
		}
		size = newSize >> 1;
		size2 = newSize2 >> 1;
		allocators[0] = core::NewTwoWayAllocator(size, heap, "DynamicVertexBuffer[0]", 16);
		allocators[0]->AddRef();
		allocators[1] = core::NewTwoWayAllocator(size, heap, "DynamicVertexBuffer[1]", 16);
		allocators[1]->AddRef();
		core::RegisterHeap(heapIndices[0], heap, allocators[0]);
		core::RegisterHeap(heapIndices[1], heap, allocators[1]);
	}

	// FUNCTION: ENGINE 0x1074D650
	void RenderPassChain::Update()
	{
		for (unsigned int i = 0; i < count; i++)
		{
			objects[i]->Release();
		}
		if (count > maxCount)
		{
			maxCount = count;
		}
		count = 0;
		unsigned int free0;
		unsigned int free1;
		allocators[0]->GetStat(7, (int*)&free0);
		allocators[1]->GetStat(7, (int*)&free1);
		if (free0 > peaks[0])
		{
			peaks[0] = free0;
		}
		if (free1 > peaks[1])
		{
			peaks[1] = free1;
		}
		current ^= 1;
		if (query == 0)
		{
			query = pddi->Unknown18();
			pddi->Unknown20(query);
		}
		else
		{
			pddi->Unknown21(query);
			pddi->Unknown20(query);
		}
		allocators[current]->Reset();
		currentHeap = heapIndices[current];
	}

	// FUNCTION: ENGINE 0x1074D730
	RenderPassChain::~RenderPassChain()
	{
		if (query != 0)
		{
			pddi->Unknown19(query);
		}
		Destroy();
		core::UnregisterHeap(heapIndices[0]);
		core::UnregisterHeap(heapIndices[1]);
	}
}
