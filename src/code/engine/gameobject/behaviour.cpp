#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/system/enginememory.h"

namespace engine
{
	// FUNCTION: ENGINE 0x107EE450
	content::ClassInfo* Behaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::Behaviour";
		sInfo.code = "n";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x107EE490
	bool Behaviour::Slot2()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x107EE4A0
	void Behaviour::Listen(int messageType, bool listen)
	{
		if (owner != 0)
		{
			owner->behaviours.SetListening(messageType, this, listen);
		}
	}

	// FUNCTION: ENGINE 0x107EE4C0
	void Behaviour::Listen2(int messageType, bool listen)
	{
		if (owner != 0)
		{
			owner->behaviours.SetListening2(messageType, this, listen);
		}
	}

	// FUNCTION: ENGINE 0x107EE4E0
	void Behaviour::Remove(int value)
	{
		if (owner != 0)
		{
			owner->behaviours.Remove(value, this);
		}
	}

	// FUNCTION: ENGINE 0x107EE500
	bool Behaviour::Query1()
	{
		if (owner == 0)
		{
			return true;
		}
		return owner->behaviours.Query1(this);
	}

	// FUNCTION: ENGINE 0x107EE520
	bool Behaviour::Query2(int value)
	{
		if (owner == 0)
		{
			return false;
		}
		return owner->behaviours.Query2(value, this);
	}

	// FUNCTION: ENGINE 0x107EE540
	bool Behaviour::Query3()
	{
		if (owner == 0)
		{
			return false;
		}
		return owner->behaviours.Query3(this);
	}

	// FUNCTION: ENGINE 0x107EE560
	bool Behaviour::Query4(int value)
	{
		if (owner == 0)
		{
			return false;
		}
		return owner->behaviours.Query4(value, this);
	}

	// FUNCTION: ENGINE 0x107EE580
	void Behaviour::SetState(unsigned char mask)
	{
		state |= mask;
	}

	// FUNCTION: ENGINE 0x107EE590
	void Behaviour::ClearState(unsigned char mask)
	{
		state &= ~mask;
	}

	// FUNCTION: ENGINE 0x107EE5A0
	void Behaviour::Slot4(int a, int b)
	{
		// A warn-once whose report is compiled out of this build
		static bool sWarn = true;
		if (sWarn)
		{
			sWarn = false;
		}
	}

	// FUNCTION: ENGINE 0x107EE650
	Behaviour::Behaviour(BehaviourOwner* newOwner) : owner(newOwner), state(0), timeSliceFrameSkip(0)
	{
		requested.Clear();
		requested.SetBit(7);
		requested.SetBit(6);
	}

	// FUNCTION: ENGINE 0x107EE8D0
	// FUNCTION: ENGINE 0x107EE6A0
	Behaviour::~Behaviour()
	{
	}

	// FUNCTION: ENGINE 0x107EE6B0
	unsigned char Behaviour::GetInactiveMask() const
	{
		return flags.Get();
	}

	// FUNCTION: ENGINE 0x107EE6C0
	void Behaviour::SetInactiveMask(unsigned char mask)
	{
		flags.Set(flags.Get() | (mask & 0x3f));
	}

	// FUNCTION: ENGINE 0x107EE6E0
	bool Behaviour::ComputeActive()
	{
		unsigned char value = ~requested.Get() | ~flags.Get() | 0x80;
		return value == 0xff ? true : false;
	}

	// FUNCTION: ENGINE 0x107EE710
	void Behaviour::ApplyActive(bool active)
	{
		if (active)
		{
			requested.SetBit(7);
		}
		else
		{
			requested.ClearBit(7);
		}
		if (&owner->behaviours != this)
		{
			owner->behaviours.NotifyActiveChanged(this);
		}
	}

	// FUNCTION: ENGINE 0x107EE740
	void Behaviour::SetUpdating(bool updating)
	{
		if (updating)
		{
			flags.SetBit(7);
		}
		else
		{
			flags.ClearBit(7);
		}
	}

	// FUNCTION: ENGINE 0x107EE8F0
	void Behaviour::OnActiveChanged(bool active)
	{
		if (!flags.Test(7))
		{
			state &= ~STATE_DIRTY;
			if (active)
			{
				flags.ClearBit(6);
				ApplyActive(active);
				return;
			}
			flags.SetBit(6);
		}
		ApplyActive(active);
	}

	// FUNCTION: ENGINE 0x107EE940
	void Behaviour::Refresh()
	{
		SetUpdating(true);
		bool active = ComputeActive();
		if (requested.Test(7) != active)
		{
			OnActiveChanged(active);
		}
		SetUpdating(false);
	}

	// FUNCTION: ENGINE 0x107EEB50
	void Behaviour::SetEnabled(bool enabled)
	{
		state &= ~STATE_DIRTY;
		if (enabled)
		{
			flags.ClearBit(6);
		}
		else
		{
			flags.SetBit(6);
		}
		if (owner != 0)
		{
			Refresh();
		}
	}

	// FUNCTION: ENGINE 0x107EEB80
	void Behaviour::SetRequestBit(unsigned char bit, bool on)
	{
		if (on)
		{
			requested.SetBit(bit);
		}
		else
		{
			requested.ClearBit(bit);
		}
		Refresh();
	}

	// BitField<unsigned char>'s members (defined out of line in the header); the engine kept these copies here
	// FUNCTION: ENGINE 0x107EE5C0
	// FUNCTION: ENGINE 0x107EE5D0
	// FUNCTION: ENGINE 0x107EE5E0
	// FUNCTION: ENGINE 0x107EE5F0
	// FUNCTION: ENGINE 0x107EE600

	// FUNCTION: ENGINE 0x107EEA70
	content::MemberList* Behaviour::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberMetaType(&Behaviour::IsActive, &Behaviour::OnActiveChanged, "pn"), 0, "active" },
			{ content::GetMemberMetaType(&Behaviour::GetInactiveMask, &Behaviour::SetInactiveMask, "p"), 0,
				"inactiveMask" },
			{ content::GetPrimitiveMetaType<unsigned char>("p"),
				content::MemberOffset((int)&((Behaviour*)0)->timeSliceFrameSkip,
				(int)&((Behaviour*)0)->timeSliceFrameSkip), "timeSliceFrameSkip" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// The reflection templates instantiated for Behaviour (code/content/metatype.h): the member getter / setter
	// objects, the get / set meta types and the vcall thunk of the "active" setter
	// FUNCTION: ENGINE 0x107EE620
	// FUNCTION: ENGINE 0x107EE630
	// FUNCTION: ENGINE 0x107EE760
	// FUNCTION: ENGINE 0x107EE7A0
	// FUNCTION: ENGINE 0x107EE7C0
	// FUNCTION: ENGINE 0x107EE7D0
	// FUNCTION: ENGINE 0x107EE7F0
	// FUNCTION: ENGINE 0x107EE810
	// FUNCTION: ENGINE 0x107EE820
	// FUNCTION: ENGINE 0x107EE840
	// FUNCTION: ENGINE 0x107EE860
	// FUNCTION: ENGINE 0x107EE890
	// FUNCTION: ENGINE 0x107EE990
	// FUNCTION: ENGINE 0x107EEA00
}
