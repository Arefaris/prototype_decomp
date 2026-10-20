#include "code/core/heap.h"
#include "code/ravenphysics/collision/collisionobject.h"
#include "code/ravenphysics/common/stackallocator.h"
#include "code/ravenphysics/context.h"
#include "code/ravenphysics/physics.h"

namespace ravenphysics
{
	// The functions this unit calls in the others (names are guesses)
	void Unknown1065D330();
	void Unknown1065D250();
	void Unknown1065E5D0();
	void Unknown1065E6D0();
	void Unknown1066AA00(int count);
	void Unknown106A7070();
	void Unknown10669C10(float first, float second);
	void Unknown106A6E10();
	void Unknown106A7010();
	void Unknown106A70E0();
	void Unknown1066A900();
	void Unknown106A6E80();
	void Unknown106A6E20();
	extern const CollisionHandle gInvalidCollisionHandle;

	// A pointer triple of 16-byte elements the library keeps in globals (begin, end, end of storage)
	struct StatArray
	{
		char (*begin)[16];
		char (*end)[16];
		char (*capacityEnd)[16];
	};
	extern StatArray gStatArrayA;   // 0x1127E468
	extern StatArray gStatArrayB;   // 0x1127E458
	extern StatArray gStatArrayC;   // 0x1127E448
	extern int gMaterialCount;      // 0x1127D510
	extern int gUnknown1127E42C;

	// FUNCTION: ENGINE 0x10661950
	unsigned int ScratchStack::GetHighWater()
	{
		return sHighWater - (unsigned int)sBegin;
	}

	// FUNCTION: ENGINE 0x10661960
	unsigned int ScratchStack::GetPeak()
	{
		return sUnknown - (unsigned int)sBegin;
	}

	// FUNCTION: ENGINE 0x10661970
	void ScratchStack::RestartHighWater()
	{
		if ((unsigned int)sUnknown < sHighWater)
		{
			sUnknown = sHighWater;
		}
		sHighWater = (unsigned int)sCurrent;
	}

	// FUNCTION: ENGINE 0x106619A0
	unsigned int ScratchStack::GetSize()
	{
		return sEnd - sBegin;
	}

	// FUNCTION: ENGINE 0x106619B0
	InitSettings::InitSettings()
	{
		materialCapacity = 0x40;
		intersectionPropertyCapacity = 0x40;
		unknown8 = 0;
		scratchStackSize = 0x580000;
		collisionObjectCapacity = 0x1400;
		unknown14 = 100.0f;
		unknown18 = 100.0f;
		unknown1C = 0x40;
		unknown20 = 0x40;
		unknown24 = 0x40;
	}

	// FUNCTION: ENGINE 0x10661A40
	void Shutdown()
	{
		Unknown106A70E0();
		Unknown1066A900();
		ClearIntersectionPropertyRegistry();
		ScratchStack::Free();
		gCollisionObjectTable->Remove(const_cast<CollisionHandle*>(&gInvalidCollisionHandle));
		DestroyCollisionObjectTable();
		Unknown106A6E80();
		Unknown106A6E20();
	}

	// FUNCTION: ENGINE 0x10661B10
	void Init(const InitSettings* settings)
	{
		CreateCollisionObjectTable(settings->collisionObjectCapacity);
		gCollisionObjectTable->Register(0, const_cast<CollisionHandle*>(&gInvalidCollisionHandle));
		Unknown1065D330();
		Unknown1065D250();
		Unknown1065E5D0();
		Unknown1065E6D0();
		Unknown1066AA00(settings->materialCapacity);
		CreateIntersectionPropertyRegistry(settings->intersectionPropertyCapacity);
		Unknown106A7070();
		gUnknown1127E42C = settings->unknown8;
		ScratchStack::Create(settings->scratchStackSize, core::GetCurrentHeap(), false);
		Unknown10669C10(settings->unknown14, settings->unknown18);
		gSettings = *settings;
		Unknown106A6E10();
		Unknown106A7010();
	}

	// FUNCTION: ENGINE 0x10661BB0
	void GetStatistics(Statistics* statistics)
	{
		statistics->materialCount = gMaterialCount;
		statistics->materialCapacity = gSettings.materialCapacity;
		statistics->intersectionPropertyCount = GetIntersectionPropertyCount();
		statistics->intersectionPropertyCapacity = gSettings.intersectionPropertyCapacity;
		statistics->collisionObjectCount = (unsigned short)(gCollisionObjectTable->free.capacity - gCollisionObjectTable->free.size);
		statistics->collisionObjectCapacity = gSettings.collisionObjectCapacity;
		statistics->scratchStackSize = ScratchStack::sEnd - ScratchStack::sBegin;
		statistics->scratchStackUsed = ScratchStack::sHighWater - (unsigned int)ScratchStack::sBegin;
		if ((unsigned int)ScratchStack::sUnknown < ScratchStack::sHighWater)
		{
			ScratchStack::sUnknown = ScratchStack::sHighWater;
		}
		ScratchStack::sHighWater = (unsigned int)ScratchStack::sCurrent;
		statistics->scratchStackPeak = ScratchStack::sUnknown - (unsigned int)ScratchStack::sBegin;
		statistics->arrayASize = gStatArrayA.end - gStatArrayA.begin;
		statistics->arrayACapacity = gStatArrayA.capacityEnd - gStatArrayA.begin;
		statistics->arrayBSize = gStatArrayB.end - gStatArrayB.begin;
		statistics->arrayBCapacity = gStatArrayB.capacityEnd - gStatArrayB.begin;
		statistics->arrayCSize = gStatArrayC.end - gStatArrayC.begin;
		statistics->arrayCCapacity = gStatArrayC.capacityEnd - gStatArrayC.begin;
	}
}
