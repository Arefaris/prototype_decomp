#include <new>
#include "code/engine/render/effectcontroller.h"
#include "code/engine/render/effectmanager.h"

namespace engine
{
	// FUNCTION: ENGINE 0x10849610
	EffectController::EffectController(const int* newOwner, const core::Name<core::CaseSensitiveKey>& newName)
		: owner(*newOwner), name(newName)
	{
		list.begin = new int[5];
		if (list.begin != 0)
		{
			list.end = list.begin;
			list.capacity = list.begin + 5;
		}
		else
		{
			list.end = 0;
			list.capacity = 0;
		}
	}

	// FUNCTION: ENGINE 0x10849670
	EffectController::~EffectController()
	{
		if (!list.IsEmpty())
		{
			EffectController::StopAll();
		}
	}

	// FUNCTION: ENGINE 0x108495A0
	bool EffectController::AddEffect(const int* effect)
	{
		if (list.IsFull())
		{
			return false;
		}
		if (list.end < list.capacity)
		{
			int* slot = list.end;
			list.end = slot + 1;
			if (slot != 0)
			{
				*slot = *effect;
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x108495D0
	void EffectController::StopAll()
	{
		render::EffectManager* manager = render::GetEffectManager();
		if (manager != 0)
		{
			for (int* effect = list.begin; effect != list.end; ++effect)
			{
				manager->StopEffect(*effect, 0.0f);
			}
			list.end = list.begin;
		}
	}
}
