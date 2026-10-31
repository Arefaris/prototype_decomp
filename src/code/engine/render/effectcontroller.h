// engine::EffectController (RTTI name; a reference-counted fight node that keeps the effects an action started and
// stops them): the base of the controllers of single effects (the driving dust controller derives from it and adds
// the start of an effect). The unit is 0x10849570 - 0x108496D0; names other than the RTTI one are guesses.
#ifndef ENGINE_RENDER_EFFECTCONTROLLER_H
#define ENGINE_RENDER_EFFECTCONTROLLER_H

#include "code/core/name.h"
#include "code/engine/fight/sequencer.h"

namespace engine
{
	// The handles an EffectController holds
	struct EffectList
	{
		~EffectList()
		{
			end = begin;
			if (begin != 0)
			{
				delete[] begin;
			}
		}
		bool IsEmpty() const
		{
			return begin == end;
		}
		bool IsFull() const
		{
			return end == capacity;
		}
		int* begin;
		int* end;
		int* capacity;
	};

	class EffectController : public fight::RefCounted
	{
	public:
		// 0x10849610: the first argument is read through (its word is kept), the name is copied; the list of effect
		// handles has room for five
		EffectController(const int* newOwner, const core::Name<core::CaseSensitiveKey>& newName);
		// 0x10849670 (the deleting destructor is 0x108496B0): stops what is still running
		virtual ~EffectController();
		// vftable slot 3 (0x108495A0): keeps the handle of an effect; false when the list is full
		virtual bool AddEffect(const int* effect);
		// vftable slot 4: pure
		virtual void Slot4() = 0;
		// vftable slot 5 (0x108495D0): stops every effect the controller holds at once and forgets them
		virtual void StopAll();

		int owner;
		int unknownC;
		core::Name<core::CaseSensitiveKey> name;
		EffectList list;
	};
}

#endif
