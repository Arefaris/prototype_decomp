// The editor's lists of the scenario system (see the header).
#include <algorithm>

#include "code/engine/scenario/scenariolisters.h"

#include "code/engine/scenariomessage.h"
#include <new>

// The array members the lists' Add and the sorts of the lists use, as copies of their own
namespace container
{
	template engine::scenario::MessageEntry* ArrayFixed<engine::scenario::MessageEntry, 96>::AllocateBack();
	template engine::scenario::MessageEntry* ArrayFixed<engine::scenario::MessageEntry, 96>::End();
	template engine::scenario::AffiliateEntry* ArrayFixed<engine::scenario::AffiliateEntry, 384>::AllocateBack();
	template engine::scenario::AffiliateEntry* ArrayFixed<engine::scenario::AffiliateEntry, 384>::End();
}

namespace engine
{
	namespace scenario
	{
		ScenarioMessageLister gScenarioMessageLister;
		AffiliateLister gAffiliateLister;

		// FUNCTION: ENGINE 0x10830370
		static bool CompareNames(const core::Name<core::CaseSensitiveKey>& first,
			const core::Name<core::CaseSensitiveKey>& second)
		{
			return first < second;
		}

		// FUNCTION: ENGINE 0x10830380
		bool MessageEntry::operator<(const MessageEntry& other) const
		{
			return CompareNames(name, other.name);
		}

		// FUNCTION: ENGINE 0x10830480
		bool AffiliateEntry::operator<(const AffiliateEntry& other) const
		{
			return CompareNames(name, other.name);
		}

		// FUNCTION: ENGINE 0x10830390
		int ScenarioMessageLister::GetCount() const
		{
			return entries.Size();
		}

		// FUNCTION: ENGINE 0x108303A0
		const core::Name<core::CaseSensitiveKey>* ScenarioMessageLister::GetName(int index)
		{
			if (index >= 0 && index < entries.Size())
			{
				return &entries[index].name;
			}
			return &gEmptyListName;
		}

		// FUNCTION: ENGINE 0x108303D0
		void ScenarioMessageLister::Slot2()
		{
			for (unsigned int i = 0; i < (unsigned int)entries.Size(); i++)
			{
				entries[i].name.SetText(0);
			}
		}

		// FUNCTION: ENGINE 0x10830410
		// NONMATCHING: the engine clears the first word of the temporary name before its constructor runs and schedules the key address after the stack adjustment (95 percent of the instructions)
#ifdef NONMATCHING
		void ScenarioMessageLister::Add(const char* text, int value)
		{
			MessageEntry* slot = entries.AllocateBack();
			if (slot != 0)
			{
				core::Name<core::CaseSensitiveKey> name(text, 1);
				new (slot) MessageEntry(name, value);
			}
		}
#endif

		// FUNCTION: ENGINE 0x10830470
		int ScenarioMessageLister::GetValue(int index) const
		{
			return entries.Data()[index].value;
		}

		// FUNCTION: ENGINE 0x10830490
		int AffiliateLister::GetCount() const
		{
			return entries.Size();
		}

		// FUNCTION: ENGINE 0x108304A0
		const core::Name<core::CaseSensitiveKey>* AffiliateLister::GetName(int index)
		{
			if (index >= 0 && index < entries.Size())
			{
				return &entries[index].name;
			}
			return &gEmptyListName;
		}

		// FUNCTION: ENGINE 0x108304D0
		void AffiliateLister::Slot2()
		{
			for (unsigned int i = 0; i < (unsigned int)entries.Size(); i++)
			{
				entries[i].name.SetText(0);
			}
		}

		// FUNCTION: ENGINE 0x10830510
		// NONMATCHING: the engine clears the first word of the temporary name before its constructor runs and schedules the key address after the stack adjustment (95 percent of the instructions)
#ifdef NONMATCHING
		void AffiliateLister::Add(const char* text, int value)
		{
			AffiliateEntry* slot = entries.AllocateBack();
			if (slot != 0)
			{
				core::Name<core::CaseSensitiveKey> name(text, 1);
				new (slot) AffiliateEntry(name, value);
			}
		}
#endif

		// FUNCTION: ENGINE 0x10830570
		int AffiliateLister::GetValue(int index) const
		{
			return entries.Data()[index].value;
		}

		template<class Message> void RegisterMessageKind(int event, const char* name)
		{
			gScenarioMessageLister.Add(name, event);
			ScenarioHandleInfo info = Message::GetHandleInfo();
			for (unsigned int i = 0; i < info.count; i++)
			{
				gAffiliateLister.Add(info.names[i], i);
			}
		}

		// FUNCTION: ENGINE 0x10830580
		template void RegisterMessageKind<ScenarioInitializeMessage>(int, const char*);
		// FUNCTION: ENGINE 0x108305F0
		template void RegisterMessageKind<ObjectDestroyedMessage>(int, const char*);
		// FUNCTION: ENGINE 0x10830660
		template void RegisterMessageKind<ObjectStateChangedMessage>(int, const char*);
		// FUNCTION: ENGINE 0x108306D0
		template void RegisterMessageKind<StringMessage>(int, const char*);
		// FUNCTION: ENGINE 0x10830740
		template void RegisterMessageKind<EnterTriggerMessage>(int, const char*);
		// FUNCTION: ENGINE 0x108307B0
		template void RegisterMessageKind<ExitTriggerMessage>(int, const char*);
		// FUNCTION: ENGINE 0x10830820
		template void RegisterMessageKind<ScenarioNISBeginMessage>(int, const char*);
		// FUNCTION: ENGINE 0x10830890
		template void RegisterMessageKind<ScenarioNISEndMessage>(int, const char*);
		// FUNCTION: ENGINE 0x10830900
		template void RegisterMessageKind<ScenarioNISLoadCompleteMessage>(int, const char*);
		// FUNCTION: ENGINE 0x10830970
		template void RegisterMessageKind<ScenarioStreamPackageLoadedMessage>(int, const char*);
		// FUNCTION: ENGINE 0x108309E0
		template void RegisterMessageKind<ScenarioStreamPackageUnloadedMessage>(int, const char*);

		// FUNCTION: ENGINE 0x108322D0
		// NONMATCHING: the engine calls std::sort where this inlines it into the call of _Sort (35 percent)
#ifdef NONMATCHING
		void ScenarioMessageLister::Sort()
		{
			std::sort(entries.Begin(), entries.End());
		}
#endif

		// FUNCTION: ENGINE 0x108322F0
		// NONMATCHING: the engine calls std::sort where this inlines it into the call of _Sort (35 percent)
#ifdef NONMATCHING
		void AffiliateLister::Sort()
		{
			std::sort(entries.Begin(), entries.End());
		}
#endif

		// FUNCTION: ENGINE 0x10831E90
		void ScenarioMessageLister::Reset()
		{
			entries.Reset();
		}

		// FUNCTION: ENGINE 0x10831EA0
		void AffiliateLister::Reset()
		{
			entries.Reset();
		}

		// FUNCTION: ENGINE 0x10832310
		void SortListers()
		{
			gScenarioMessageLister.Sort();
			gAffiliateLister.Sort();
		}

		// FUNCTION: ENGINE 0x10832070
		void ResetListers()
		{
			gAffiliateLister.Reset();
			gScenarioMessageLister.Reset();
		}
	}
}

// The sorts of the lists are the toolchain's <algorithm> for the entries; the unit keeps the instances it
// needs as COMDAT functions of its own
template void std::_Med3<engine::scenario::MessageEntry*>(engine::scenario::MessageEntry*, engine::scenario::MessageEntry*, engine::scenario::MessageEntry*);
template void std::_Med3<engine::scenario::AffiliateEntry*>(engine::scenario::AffiliateEntry*, engine::scenario::AffiliateEntry*, engine::scenario::AffiliateEntry*);
template void std::_Push_heap<engine::scenario::MessageEntry*, int, engine::scenario::MessageEntry>(engine::scenario::MessageEntry*, int, int, engine::scenario::MessageEntry);
template void std::_Push_heap<engine::scenario::AffiliateEntry*, int, engine::scenario::AffiliateEntry>(engine::scenario::AffiliateEntry*, int, int, engine::scenario::AffiliateEntry);
template void std::_Median<engine::scenario::MessageEntry*>(engine::scenario::MessageEntry*, engine::scenario::MessageEntry*, engine::scenario::MessageEntry*);
template void std::_Median<engine::scenario::AffiliateEntry*>(engine::scenario::AffiliateEntry*, engine::scenario::AffiliateEntry*, engine::scenario::AffiliateEntry*);
template void std::_Adjust_heap<engine::scenario::MessageEntry*, int, engine::scenario::MessageEntry>(engine::scenario::MessageEntry*, int, int, engine::scenario::MessageEntry);
template void std::_Adjust_heap<engine::scenario::AffiliateEntry*, int, engine::scenario::AffiliateEntry>(engine::scenario::AffiliateEntry*, int, int, engine::scenario::AffiliateEntry);
template void std::_Make_heap<engine::scenario::MessageEntry*, int, engine::scenario::MessageEntry>(engine::scenario::MessageEntry*, engine::scenario::MessageEntry*, int*, engine::scenario::MessageEntry*);
template void std::_Make_heap<engine::scenario::AffiliateEntry*, int, engine::scenario::AffiliateEntry>(engine::scenario::AffiliateEntry*, engine::scenario::AffiliateEntry*, int*, engine::scenario::AffiliateEntry*);
template std::pair<engine::scenario::MessageEntry*, engine::scenario::MessageEntry*> std::_Unguarded_partition<engine::scenario::MessageEntry*>(engine::scenario::MessageEntry*, engine::scenario::MessageEntry*);
template std::pair<engine::scenario::AffiliateEntry*, engine::scenario::AffiliateEntry*> std::_Unguarded_partition<engine::scenario::AffiliateEntry*>(engine::scenario::AffiliateEntry*, engine::scenario::AffiliateEntry*);
template void std::_Insertion_sort1<engine::scenario::MessageEntry*, engine::scenario::MessageEntry>(engine::scenario::MessageEntry*, engine::scenario::MessageEntry*, engine::scenario::MessageEntry*);
template void std::_Insertion_sort1<engine::scenario::AffiliateEntry*, engine::scenario::AffiliateEntry>(engine::scenario::AffiliateEntry*, engine::scenario::AffiliateEntry*, engine::scenario::AffiliateEntry*);
template void std::_Sort_heap<engine::scenario::MessageEntry*>(engine::scenario::MessageEntry*, engine::scenario::MessageEntry*);
template void std::_Sort_heap<engine::scenario::AffiliateEntry*>(engine::scenario::AffiliateEntry*, engine::scenario::AffiliateEntry*);
template void std::_Sort<engine::scenario::MessageEntry*, int>(engine::scenario::MessageEntry*, engine::scenario::MessageEntry*, int);
template void std::_Sort<engine::scenario::AffiliateEntry*, int>(engine::scenario::AffiliateEntry*, engine::scenario::AffiliateEntry*, int);
template void std::sort<engine::scenario::MessageEntry*>(engine::scenario::MessageEntry*, engine::scenario::MessageEntry*);
template void std::sort<engine::scenario::AffiliateEntry*>(engine::scenario::AffiliateEntry*, engine::scenario::AffiliateEntry*);

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1082FAD0
// FUNCTION: ENGINE 0x1082FB10
// FUNCTION: ENGINE 0x1082FB50
// FUNCTION: ENGINE 0x1082FB90
// FUNCTION: ENGINE 0x1082FBD0
// FUNCTION: ENGINE 0x1082FC10
// FUNCTION: ENGINE 0x1082FC60
// FUNCTION: ENGINE 0x1082FCA0
// FUNCTION: ENGINE 0x1082FCE0
// FUNCTION: ENGINE 0x1082FD20
// FUNCTION: ENGINE 0x1082FD60
// FUNCTION: ENGINE 0x1082FDA0
// FUNCTION: ENGINE 0x1082FDE0
// FUNCTION: ENGINE 0x1082FDF0
// FUNCTION: ENGINE 0x1082FE00
// FUNCTION: ENGINE 0x1082FE10
// FUNCTION: ENGINE 0x1082FE20
// FUNCTION: ENGINE 0x1082FE30
// FUNCTION: ENGINE 0x1082FE60
// FUNCTION: ENGINE 0x1082FE70
// FUNCTION: ENGINE 0x1082FE80
// FUNCTION: ENGINE 0x1082FE90
// FUNCTION: ENGINE 0x1082FEA0
// FUNCTION: ENGINE 0x1082FEB0
// FUNCTION: ENGINE 0x1082FF40
// FUNCTION: ENGINE 0x1082FF50
// FUNCTION: ENGINE 0x1082FF60
// FUNCTION: ENGINE 0x1082FF70
// FUNCTION: ENGINE 0x1082FF80
// FUNCTION: ENGINE 0x1082FFA0
// FUNCTION: ENGINE 0x1082FFC0
// FUNCTION: ENGINE 0x1082FFD0
// FUNCTION: ENGINE 0x1082FFE0
// FUNCTION: ENGINE 0x1082FFF0
// FUNCTION: ENGINE 0x10830000
// FUNCTION: ENGINE 0x10830020
// FUNCTION: ENGINE 0x10830040
// FUNCTION: ENGINE 0x10830060
// FUNCTION: ENGINE 0x10830120
// FUNCTION: ENGINE 0x10830130
// FUNCTION: ENGINE 0x10830140
// FUNCTION: ENGINE 0x10830150
// FUNCTION: ENGINE 0x10830160
// FUNCTION: ENGINE 0x108301A0
// FUNCTION: ENGINE 0x10830A50
// FUNCTION: ENGINE 0x10830A70
// FUNCTION: ENGINE 0x10830A90
// FUNCTION: ENGINE 0x10830AA0
// FUNCTION: ENGINE 0x10830B50
// EQUIVALENT: the engine keeps the copied value in a register across the name assignments where this reloads it from the stack temporary (same calls and stores in the same order)
// FUNCTION: ENGINE 0x10830C20
// EQUIVALENT: the engine keeps the copied value in a register across the name assignments where this reloads it from the stack temporary (same calls and stores in the same order)
// FUNCTION: ENGINE 0x10830CF0
// FUNCTION: ENGINE 0x10830D70
// FUNCTION: ENGINE 0x10830DC0
// FUNCTION: ENGINE 0x10830E40
// FUNCTION: ENGINE 0x10830EE0
// FUNCTION: ENGINE 0x10830EF0
// FUNCTION: ENGINE 0x10830F00
// FUNCTION: ENGINE 0x10830F90
// FUNCTION: ENGINE 0x10831020
// FUNCTION: ENGINE 0x108310E0
// FUNCTION: ENGINE 0x10831130
// FUNCTION: ENGINE 0x108311F0
// FUNCTION: ENGINE 0x10831240
// FUNCTION: ENGINE 0x10831290
// FUNCTION: ENGINE 0x108313D0
// FUNCTION: ENGINE 0x108313E0
// FUNCTION: ENGINE 0x108313F0
// EQUIVALENT: register choices and a few schedules of the loop bodies (same calls and stores in the same order)
// FUNCTION: ENGINE 0x108316E0
// EQUIVALENT: register choices and a few schedules of the loop bodies (same calls and stores in the same order)
// FUNCTION: ENGINE 0x108319D0
// FUNCTION: ENGINE 0x10831A30
// EQUIVALENT: register choices and a few schedules (same calls and stores in the same order)
// FUNCTION: ENGINE 0x10831B30
// FUNCTION: ENGINE 0x10831B90
// EQUIVALENT: register choices and a few schedules (same calls and stores in the same order)
// FUNCTION: ENGINE 0x10831C90
// EQUIVALENT: register choices (same calls and stores in the same order)
// FUNCTION: ENGINE 0x10831D00
// EQUIVALENT: register choices (same calls and stores in the same order)
// FUNCTION: ENGINE 0x10831D70
// FUNCTION: ENGINE 0x10831D80
// FUNCTION: ENGINE 0x10831D90
// FUNCTION: ENGINE 0x10831DC0
// FUNCTION: ENGINE 0x10831DE0
// FUNCTION: ENGINE 0x10831E10
// FUNCTION: ENGINE 0x10831E30
// FUNCTION: ENGINE 0x10831E60
// FUNCTION: ENGINE 0x10831EB0
// FUNCTION: ENGINE 0x10831EC0
// FUNCTION: ENGINE 0x10831ED0
// EQUIVALENT: the engine keeps the end offset in a stack slot where this computes it into a register (same calls and stores in the same order)
// FUNCTION: ENGINE 0x10831F70
// EQUIVALENT: the engine keeps the end offset in a stack slot where this computes it into a register (same calls and stores in the same order)
// FUNCTION: ENGINE 0x10832010
// FUNCTION: ENGINE 0x10832030
// FUNCTION: ENGINE 0x10832050
// FUNCTION: ENGINE 0x10832060
// FUNCTION: ENGINE 0x10832090
// FUNCTION: ENGINE 0x108320A0
// FUNCTION: ENGINE 0x108320B0
// FUNCTION: ENGINE 0x10832180
