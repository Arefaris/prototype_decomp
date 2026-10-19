#include "code/core/criticalsection.h"
#include "code/core/heap.h"
#include "code/engine/system/desynchunter.h"
#include <new>

namespace engine
{
	// GLOBAL: ENGINE 0x1130CCF4
	int DesyncHunter::sThread;
	// GLOBAL: ENGINE 0x1130CCF8
	DesyncHunter* DesyncHunter::sInstance;
	// GLOBAL: ENGINE 0x1130CCE8
	unsigned char DesyncHunter::sModeStack[10];
	// GLOBAL: ENGINE 0x1130CCFC
	unsigned int DesyncHunter::sModeDepth;
	// GLOBAL: ENGINE 0x111C3054
	unsigned char DesyncHunter::sMode = 1;

	// FUNCTION: ENGINE 0x108214E0
	DesyncSettings* DesyncHunter::GetSettings()
	{
		return &gDesyncSettings;
	}

	// FUNCTION: ENGINE 0x108214F0
	void DesyncHunter::RecordThread()
	{
		sThread = core::GetThreadData();
	}

	// FUNCTION: ENGINE 0x10821500
	void DesyncHunter::SetInstance(DesyncHunter* hunter)
	{
		sInstance = hunter;
	}

	// FUNCTION: ENGINE 0x10821510
	DesyncHunter* DesyncHunter::GetInstance()
	{
		return sInstance;
	}

	// FUNCTION: ENGINE 0x10821520
	void DesyncHunter::UpdateInstance()
	{
		if (sInstance != 0)
		{
			sInstance->Update();
		}
	}

	// FUNCTION: ENGINE 0x10821540
	void DesyncHunter::StartInstance()
	{
		if (sInstance != 0)
		{
			sInstance->Start();
		}
	}

	// FUNCTION: ENGINE 0x10821560
	void DesyncHunter::StopInstance()
	{
		if (sInstance != 0)
		{
			sInstance->Stop();
		}
	}

	// FUNCTION: ENGINE 0x10821580
	void DesyncHunter::PushMode(unsigned char mode)
	{
		if (sModeDepth < 10)
		{
			sModeStack[sModeDepth] = sMode;
			sModeDepth++;
			sMode = mode;
		}
	}

	// FUNCTION: ENGINE 0x108215B0
	void DesyncHunter::PopMode()
	{
		if (sModeDepth > 0)
		{
			sModeDepth--;
			sMode = sModeStack[sModeDepth];
		}
	}

	// FUNCTION: ENGINE 0x108215D0
	unsigned char DesyncHunter::GetMode()
	{
		return sMode;
	}

	// FUNCTION: ENGINE 0x108215E0
	DesyncHunter::DesyncHunter() : state(0), last(0)
	{
		core::HeapScope scope(0x82);
		checker = new DesyncChecker(gDesyncSettings.size, gDesyncSettings.count, gDesyncSettings.flag);
	}

	// FUNCTION: ENGINE 0x10821680
	void DesyncHunter::Start()
	{
		state = 1;
	}

	// FUNCTION: ENGINE 0x10821690
	void DesyncHunter::Stop()
	{
		state = 0;
	}

	// FUNCTION: ENGINE 0x108216A0
	void DesyncHunter::Update()
	{
		switch (state)
		{
		case 1:
			checker->Reset();
			last = checker->GetValue();
			break;
		case 2:
			checker->Verify();
			last = checker->GetValue();
			break;
		}
	}

	// FUNCTION: ENGINE 0x108216E0
	DesyncHunter::~DesyncHunter()
	{
		delete checker;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108214D0
// FUNCTION: ENGINE 0x10821660
// FUNCTION: ENGINE 0x10821700
