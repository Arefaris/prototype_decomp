// The base classes of the fight nodes (Item, Condition, Track), the factories that make them and the helpers that
// copy texts (part of the unit 0x105A2440 - 0x105B3680; the declarations are in sequencer.h and trackfactory.h).
#include "code/core/heap.h"
#include "code/engine/fight/fightsystem.h"
#include "code/engine/fight/reader.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/system/streampackage.h"
#include <intrin.h>
#include <new>
#include <string.h>

namespace fight
{
	// The name the conditions read a flag by when their node has no value (0x112761C0), and the texts the tracks read
	// theirs by (0x110B4284 / 0x110B4288)
	extern Name gConditionFlagName;
	extern const char* gTrackDisabledText;
	extern const char* gTrackSlaveText;

	// ---- fight::Item ----------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A9A40
	Item::~Item()
	{
	}

	// FUNCTION: ENGINE 0x105A9A50
	void Item::Slot2(int arg)
	{
		int index = 0;
		Property* property = GetProperty(index);
		if (property != 0)
		{
			do
			{
				property->Slot5((int)this, arg);
				index = index + 1;
				property = GetProperty(index);
			}
			while (property != 0);
		}
	}

	// FUNCTION: ENGINE 0x105A9A90
	void Item::Slot3(int arg)
	{
		int index = 0;
		Property* property = GetProperty(index);
		if (property != 0)
		{
			do
			{
				property->Slot2((int)this, arg);
				index = index + 1;
				property = GetProperty(index);
			}
			while (property != 0);
		}
	}

	// FUNCTION: ENGINE 0x105A9AD0
	void Item::Slot4(int arg)
	{
		int index = 0;
		Property* property = GetProperty(index);
		if (property != 0)
		{
			do
			{
				property->Slot3((int)this, arg);
				index = index + 1;
				property = GetProperty(index);
			}
			while (property != 0);
		}
	}

	// FUNCTION: ENGINE 0x105A9B10
	bool Item::Slot8(int context, void* reader)
	{
		int index = 0;
		Property* property = Slot1(index);
		if (property != 0)
		{
			do
			{
				if (!property->IsNull())
				{
					property->Slot6((int)this, context, reader);
				}
				index = index + 1;
				property = Slot1(index);
			}
			while (property != 0);
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105A9B70
	void Item::Slot6(int a, int b)
	{
	}

	// FUNCTION: ENGINE 0x105A9B80
	bool Item::Slot5(int key, int context, int source)
	{
		Reader* reader = (Reader*)source;
		if (!reader->HasChild())
		{
			return false;
		}
		const Name* child = reader->GetChildName();
		if (*child != *(const Name*)key)
		{
			return false;
		}
		reader->EnterChild(*child);
		Slot8(context, reader);
		reader->ExitChild();
		return true;
	}

	// ---- fight::Condition -----------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A99E0
	Condition::Condition(int newOp)
		: next(0), op(newOp)
	{
	}

	// FUNCTION: ENGINE 0x105A9A00
	Condition::~Condition()
	{
		SetNext(0);
	}

	// FUNCTION: ENGINE 0x105A9910
	bool Condition::Slot5(int key, int context, int source)
	{
		Reader* reader = (Reader*)source;
		if (!reader->HasChild())
		{
			return false;
		}
		const Name* child = reader->GetChildName();
		if (*child != *(const Name*)key)
		{
			return false;
		}
		reader->EnterChild(*child);
		if (!reader->UsesNumbers())
		{
			bool flag = false;
			reader->ReadBool(gConditionFlagName, &flag);
		}
		Slot8(context, reader);
		reader->ExitChild();
		return true;
	}

	// ---- fight::Track ---------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105AA160
	Track::Track()
		: next(0), watchList(), unknownC(0)
	{
	}

	// FUNCTION: ENGINE 0x105AA180
	Track::~Track()
	{
		SetNext(0);
		core::Link<Track>* node = watchList.head;
		if (node != 0)
		{
			do
			{
				core::Link<Track>* following = node->next;
				node->object = 0;
				node->prev = 0;
				node->next = 0;
				node = following;
			}
			while (node != 0);
			watchList.head = 0;
		}
	}

	// FUNCTION: ENGINE 0x105A9D00
	Action* Track::MakeAction(Track* listener, core::IRefCount* effect, core::IRefCount* owner)
	{
		return CreateAction(listener, effect, owner);
	}

	// FUNCTION: ENGINE 0x105A9D10
	// EQUIVALENT: the engine merges the flag bits with a memory xor and picks the sequencer with a conditional move, ours
	// loads the flags first and branches; 67.6 %
	bool Track::Start(Track* listener, core::IRefCount* effect, core::IRefCount* owner, Sequencer* sequencer)
	{
		Action* action = MakeAction(listener, effect, owner);
		if (action == 0)
		{
			return false;
		}
		action->timeBegin += GetTimeBegin();
		action->unknown14 += Slot10();
		action->flags.all ^= (unknownC ^ action->flags.all) & 3;
		Sequencer* target = sequencer != 0 ? sequencer : (Sequencer*)effect;
		return target->Schedule(action);
	}

	// FUNCTION: ENGINE 0x105A9F90
	// EQUIVALENT: register allocation (the engine keeps the track in edi, the child name in ebx and saves ebp for the flag read) and the address of the reader's slot, which ours forms ahead of the name's construction; 44.7 %
	bool Track::Slot5(int key, int context, int source)
	{
		Reader* reader = (Reader*)source;
		if (!reader->HasChild())
		{
			return false;
		}
		const Name* child = reader->GetChildName();
		if (*child != *(const Name*)key)
		{
			return false;
		}
		reader->EnterChild(*child);
		if (!reader->UsesNumbers())
		{
			bool disabled = false;
			reader->ReadBool(Name(gTrackDisabledText, 1), &disabled);
		}
		int slave = 0;
		reader->ReadInt(Name(gTrackSlaveText, 1), &slave);
		unknownC = slave;
		Slot8(context, reader);
		reader->ExitChild();
		return true;
	}

	// ---- The factories --------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A9E40
	TrackFactory::TrackFactory(const char* newName, void (*registerProperties)(), void (*newClearProperties)())
		: name(newName, 1), refCount(0), clearProperties(newClearProperties)
	{
		if (registerProperties != 0)
		{
			registerProperties();
		}
	}

	// FUNCTION: ENGINE 0x105A9E80
	TrackFactory::~TrackFactory()
	{
		if (clearProperties != 0)
		{
			clearProperties();
		}
	}

	// FUNCTION: ENGINE 0x105A9F30
	long TrackFactory::AddRef()
	{
		long* count = &refCount;
		return _InterlockedExchangeAdd(count, 1);
	}

	// FUNCTION: ENGINE 0x105AA0B0
	// EQUIVALENT: the engine adds -1 into edx and decrements the answer explicitly, and keeps a spare stack word; ours
	// uses ecx; 22.4 %
	void TrackFactory::Release()
	{
		if (_InterlockedExchangeAdd(&refCount, -1) - 1 == 0)
		{
			_InterlockedExchange(&refCount, 0x8000000);
			delete this;
		}
	}

	// FUNCTION: ENGINE 0x105A9880
	long ConditionFactory::AddRef()
	{
		long* count = &refCount;
		return _InterlockedExchangeAdd(count, 1);
	}

	// FUNCTION: ENGINE 0x105A99A0
	// EQUIVALENT: the engine adds -1 into edx and decrements the answer explicitly, and keeps a spare stack word; ours
	// uses ecx; 22.4 %
	void ConditionFactory::Release()
	{
		if (_InterlockedExchangeAdd(&refCount, -1) - 1 == 0)
		{
			_InterlockedExchange(&refCount, 0x8000000);
			delete this;
		}
	}

	// FUNCTION: ENGINE 0x105A9CF0
	void* TrackFactory::Make()
	{
		return CreateTrack();
	}

	// FUNCTION: ENGINE 0x105A9790
	ConditionFactory::ConditionFactory(const char* newName, void (*registerProperties)(), void (*newClearProperties)())
		: name(newName, 1), refCount(0), clearProperties(newClearProperties)
	{
		if (registerProperties != 0)
		{
			registerProperties();
		}
	}

	// FUNCTION: ENGINE 0x105A97D0
	ConditionFactory::~ConditionFactory()
	{
		if (clearProperties != 0)
		{
			clearProperties();
		}
	}

	// FUNCTION: ENGINE 0x105A9720
	void* ConditionFactory::Make()
	{
		return CreateCondition();
	}

	// FUNCTION: ENGINE 0x105A9E90
	TrackFactory* FindTrackFactory(const char* name, TrackFactoryCaster* caster)
	{
		int heap = core::SetCurrentHeap(GetHeapId(0));
		if (engine::gLoadListeners != 0)
		{
			for (TrackRegistry* registry = engine::gLoadListeners->first; registry != 0; registry = registry->next)
			{
				TrackFactory* found = registry->FindTrackFactory(Name(name, 1));
				if (caster->IsType(found))
				{
					core::SetCurrentHeap(heap);
					return found;
				}
			}
		}
		TrackFactory* created = caster->CreateFactory(name);
		core::SetCurrentHeap(heap);
		return created;
	}

	// FUNCTION: ENGINE 0x105A31F0
	BranchFactory* FindBranchFactory(const char* name, BranchFactoryCaster* caster)
	{
		int heap = core::SetCurrentHeap(GetHeapId(0));
		if (engine::gLoadListeners != 0)
		{
			for (TrackRegistry* registry = engine::gLoadListeners->first; registry != 0; registry = registry->next)
			{
				BranchFactory* found = registry->FindBranchFactory(Name(name, 1));
				if (caster->IsType(found))
				{
					core::SetCurrentHeap(heap);
					return found;
				}
			}
		}
		BranchFactory* created = caster->CreateFactory(name);
		core::SetCurrentHeap(heap);
		return created;
	}

	// FUNCTION: ENGINE 0x105A97E0
	ConditionFactory* FindConditionFactory(const char* name, ConditionFactoryCaster* caster)
	{
		int heap = core::SetCurrentHeap(GetHeapId(0));
		if (engine::gLoadListeners != 0)
		{
			for (TrackRegistry* registry = engine::gLoadListeners->first; registry != 0; registry = registry->next)
			{
				ConditionFactory* found = registry->FindConditionFactory(Name(name, 1));
				if (caster->IsType(found))
				{
					core::SetCurrentHeap(heap);
					return found;
				}
			}
		}
		ConditionFactory* created = caster->CreateFactory(name);
		core::SetCurrentHeap(heap);
		return created;
	}

	// ---- Text helpers ---------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105AA1F0
	// EQUIVALENT: register allocation (the engine keeps the old text in ebp, ours leaves it on the stack) and the scheduling of the stack clean-up; 25.8 %
	char* ReplaceString(char* old, const char* text)
	{
		if (text != 0)
		{
			int length = (int)strlen(text);
			if (length > 0)
			{
				char* copy = new char[length + 1];
				int count;
				core::StrNCpyCount(copy, text, length + 1, &count);
				delete[] old;
				return copy;
			}
		}
		delete[] old;
		return 0;
	}
}

namespace engine
{
	// FUNCTION: ENGINE 0x105AA250
	// EQUIVALENT: register allocation (the engine keeps the old text in ebp, ours leaves it on the stack) and the scheduling of the stack clean-up; 25.3 %
	char* AssignString(char* old, int* newLength, const char* text, int length)
	{
		if (text != 0 && length > 0)
		{
			char* copy = new char[length + 1];
			memcpy(copy, text, length);
			copy[length] = 0;
			*newLength = length;
			delete[] old;
			return copy;
		}
		*newLength = 0;
		delete[] old;
		return 0;
	}
}

namespace core
{
	// FUNCTION: ENGINE 0x105AA070
	template<class T> void LinkList<T>::Retarget(T* unused, T* newObject)
	{
		Link<T>* node = head;
		if (node != 0)
		{
			do
			{
				Link<T>* following = node->next;
				node->object = newObject;
				if (newObject == 0)
				{
					node->prev = 0;
					node->next = 0;
				}
				node = following;
			}
			while (node != 0);
		}
		if (newObject != 0)
		{
			newObject->watchList.head = head;
		}
		head = 0;
	}
}

namespace fight
{
	// FUNCTION: ENGINE 0x105AA2B0
	void Param::MergeProperties(Param* other, int arg)
	{
		int index = 0;
		Property* property;
		do
		{
			property = GetProperty(index);
			Property* otherProperty = other != 0 ? other->GetProperty(index) : 0;
			if (property != 0)
			{
				if (otherProperty != 0)
				{
					if (otherProperty->GetType() != property->GetType() || otherProperty->name != property->name)
					{
						otherProperty = 0;
					}
				}
				property->Slot4((int)this, (int)otherProperty, (int)other, arg);
				if (otherProperty == 0)
				{
					other = 0;
				}
			}
			index = index + 1;
		}
		while (property != 0);
	}

	// FUNCTION: ENGINE 0x105AA0F0
	void Track::Slot14(int a, int b)
	{
		MergeProperties((Item*)a, b);
		Track* other = dynamic_cast<Track*>((Item*)a);
		watchList.Retarget(this, other);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x105A98B0
// FUNCTION: ENGINE 0x105A98C0
// FUNCTION: ENGINE 0x105A9A20
// FUNCTION: ENGINE 0x105AA1C0
