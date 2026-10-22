// The lists of conditions and tracks a fight node owns (ConditionList, TrackGroup) and the next links of their items;
// part of the unit 0x105A2440 - 0x105B3680.
#include "code/engine/fight/reader.h"
#include "code/engine/fight/trackfactory.h"

namespace fight
{
	// FUNCTION: ENGINE 0x105A7A60
	ConditionList::ConditionList()
		: head(0)
	{
	}

	// FUNCTION: ENGINE 0x105A7C90
	ConditionList::~ConditionList()
	{
		Clear();
	}

	// FUNCTION: ENGINE 0x105A7B20
	void ConditionList::Clear()
	{
		Condition* item = head;
		while (item != 0)
		{
			Condition* current = item;
			item = current->next;
			current->next = 0;
			delete current;
		}
		head = 0;
	}

	// FUNCTION: ENGINE 0x105A7F10
	TrackGroup::TrackGroup()
		: head(0)
	{
	}

	// FUNCTION: ENGINE 0x105A8140
	TrackGroup::~TrackGroup()
	{
		Clear();
	}

	// FUNCTION: ENGINE 0x105A7FD0
	void TrackGroup::Clear()
	{
		Track* item = head;
		while (item != 0)
		{
			Track* current = item;
			item = current->next;
			current->next = 0;
			delete current;
		}
		head = 0;
	}

	// FUNCTION: ENGINE 0x105A7D00
	bool ConditionList::LoadChildren(Branch* owner, Reader* reader, int index)
	{
		Condition* previous = 0;
		int position = 0;
		Condition* node = head;
		for (; node != 0; node = node->next)
		{
			if (index < 0 || position > index || position == index)
			{
				break;
			}
			previous = node;
			position = position + 1;
		}
		TrackRegistry* registry = 0;
		if (owner != 0)
		{
			registry = owner->Slot6();
		}
		while (reader->HasChild())
		{
			const Reader::Name* name = reader->GetChildName();
			ConditionFactory* factory = 0;
			if (registry != 0)
			{
				factory = registry->FindConditionFactory(*name);
			}
			if (factory == 0)
			{
				ReportReadError(reader, "");
				reader->SkipChild();
			}
			else
			{
				Condition* item = (Condition*)factory->Make();
				if (item->Slot5((int)name, (int)owner, (int)reader))
				{
					item->SetNext(node);
					if (previous != 0)
					{
						previous->SetNext(item);
					}
					else
					{
						SetHead(this, item);
					}
					previous = item;
				}
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105A7E10
	bool ConditionList::Load(const core::Name<core::CaseSensitiveKey>& key, int context, Reader* reader)
	{
		if (!reader->HasChild())
		{
			return false;
		}
		if (*reader->GetChildName() != key)
		{
			return false;
		}
		reader->EnterChild(key);
		LoadChildren((Branch*)context, reader, -1);
		reader->ExitChild();
		return true;
	}

	// FUNCTION: ENGINE 0x105A81B0
	bool TrackGroup::LoadChildren(Branch* owner, Reader* reader, int index)
	{
		Track* previous = 0;
		int position = 0;
		Track* node = head;
		for (; node != 0; node = node->next)
		{
			if (index < 0 || position > index || position == index)
			{
				break;
			}
			previous = node;
			position = position + 1;
		}
		TrackRegistry* registry = 0;
		if (owner != 0)
		{
			registry = owner->Slot6();
		}
		while (reader->HasChild())
		{
			const Reader::Name* name = reader->GetChildName();
			TrackFactory* factory = 0;
			if (registry != 0)
			{
				factory = registry->FindTrackFactory(*name);
			}
			if (factory == 0)
			{
				ReportReadError(reader, "");
				reader->SkipChild();
			}
			else
			{
				Track* item = (Track*)factory->Make();
				if (item->Slot5((int)name, (int)owner, (int)reader))
				{
					item->SetNext(node);
					if (previous != 0)
					{
						previous->SetNext(item);
					}
					else
					{
						SetHead(this, item);
					}
					previous = item;
				}
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105A82C0
	bool TrackGroup::Load(const core::Name<core::CaseSensitiveKey>& key, int context, Reader* reader)
	{
		if (!reader->HasChild())
		{
			return false;
		}
		if (*reader->GetChildName() != key)
		{
			return false;
		}
		reader->EnterChild(key);
		LoadChildren((Branch*)context, reader, -1);
		reader->ExitChild();
		return true;
	}

	// FUNCTION: ENGINE 0x105A7A70
	int ConditionList::GetCount() const
	{
		int count = 0;
		for (const Condition* item = head; item != 0; item = item->next)
		{
			count = count + 1;
		}
		return count;
	}

	// FUNCTION: ENGINE 0x105A7A90
	// EQUIVALENT: the engine compares the index with the position (cmp index, position / jl), ours the other way round (cmp position, index / jg); 94.6 %
	Condition* ConditionList::GetAt(int index)
	{
		int position = 0;
		Condition* item = head;
		while (item != 0 && position <= index)
		{
			if (position == index)
			{
				return item;
			}
			item = item->next;
			position = position + 1;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105A7AC0
	// EQUIVALENT: the engine compares the index with the position (cmp index, position / jl), ours the other way round (cmp position, index / jg); 94.6 %
	const Condition* ConditionList::GetAtConst(int index) const
	{
		int position = 0;
		const Condition* item = head;
		while (item != 0 && position <= index)
		{
			if (position == index)
			{
				return item;
			}
			item = item->next;
			position = position + 1;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105A7AF0
	int ConditionList::IndexOf(const Condition* item) const
	{
		const Condition* current = head;
		int position = 0;
		while (true)
		{
			if (current == 0)
			{
				return -1;
			}
			if (current == item)
			{
				break;
			}
			current = current->next;
			position = position + 1;
		}
		return position;
	}

	// FUNCTION: ENGINE 0x105A7B60
	void ConditionList::ForEachSlot2(int arg)
	{
		for (Condition* item = head; item != 0; item = item->next)
		{
			item->Slot2(arg);
		}
	}

	// FUNCTION: ENGINE 0x105A7B90
	void ConditionList::ForEachSlot3(int arg)
	{
		for (Condition* item = head; item != 0; item = item->next)
		{
			item->Slot3(arg);
		}
	}

	// FUNCTION: ENGINE 0x105A7BC0
	void ConditionList::ForEachSlot4(int arg)
	{
		for (Condition* item = head; item != 0; item = item->next)
		{
			item->Slot4(arg);
		}
	}

	// FUNCTION: ENGINE 0x105A7C80
	void SetHead(ConditionList* list, Condition* item)
	{
		list->head = item;
	}

	// FUNCTION: ENGINE 0x105A7CA0
	int ConditionList::Add(Condition* item)
	{
		if (item == 0)
		{
			return -1;
		}
		Condition* last = 0;
		int count = 0;
		Condition* current = head;
		while (current != 0)
		{
			last = current;
			current = current->next;
			count = count + 1;
		}
		item->SetNext(current);
		if (last != 0)
		{
			last->SetNext(item);
			return count;
		}
		SetHead(this, item);
		return count;
	}

	// FUNCTION: ENGINE 0x105A7E80
	int ConditionList::Insert(int index, Condition* item)
	{
		if (item == 0)
		{
			return -1;
		}
		if (index < 0)
		{
			return Add(item);
		}
		Condition* previous = 0;
		Condition* current = head;
		int position = 0;
		while (current != 0 && position <= index && position != index)
		{
			previous = current;
			current = current->next;
			position = position + 1;
		}
		item->SetNext(current);
		if (previous != 0)
		{
			previous->SetNext(item);
			return position;
		}
		SetHead(this, item);
		return position;
	}

	// FUNCTION: ENGINE 0x105A98E0
	void Condition::SetNext(Condition* newNext)
	{
		if (next != 0)
		{
			delete next;
		}
		next = newNext;
	}

	// FUNCTION: ENGINE 0x105A7F20
	int TrackGroup::GetCount() const
	{
		int count = 0;
		for (const Track* item = head; item != 0; item = item->next)
		{
			count = count + 1;
		}
		return count;
	}

	// FUNCTION: ENGINE 0x105A7F40
	// EQUIVALENT: the engine compares the index with the position (cmp index, position / jl), ours the other way round (cmp position, index / jg); 94.6 %
	Track* TrackGroup::GetAt(int index)
	{
		int position = 0;
		Track* item = head;
		while (item != 0 && position <= index)
		{
			if (position == index)
			{
				return item;
			}
			item = item->next;
			position = position + 1;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105A7F70
	// EQUIVALENT: the engine compares the index with the position (cmp index, position / jl), ours the other way round (cmp position, index / jg); 94.6 %
	const Track* TrackGroup::GetAtConst(int index) const
	{
		int position = 0;
		const Track* item = head;
		while (item != 0 && position <= index)
		{
			if (position == index)
			{
				return item;
			}
			item = item->next;
			position = position + 1;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105A7FA0
	int TrackGroup::IndexOf(const Track* item) const
	{
		const Track* current = head;
		int position = 0;
		while (true)
		{
			if (current == 0)
			{
				return -1;
			}
			if (current == item)
			{
				break;
			}
			current = current->next;
			position = position + 1;
		}
		return position;
	}

	// FUNCTION: ENGINE 0x105A8010
	void TrackGroup::ForEachSlot2(int arg)
	{
		for (Track* item = head; item != 0; item = item->next)
		{
			item->Slot2(arg);
		}
	}

	// FUNCTION: ENGINE 0x105A8040
	void TrackGroup::ForEachSlot3(int arg)
	{
		for (Track* item = head; item != 0; item = item->next)
		{
			item->Slot3(arg);
		}
	}

	// FUNCTION: ENGINE 0x105A8070
	void TrackGroup::ForEachSlot4(int arg)
	{
		for (Track* item = head; item != 0; item = item->next)
		{
			item->Slot4(arg);
		}
	}

	// FUNCTION: ENGINE 0x105A80F0
	void TrackGroup::ForEachSlot14(TrackGroup* other, int arg)
	{
		Track* item = head;
		Track* match = other != 0 ? other->head : 0;
		while (item != 0)
		{
			item->Slot14((int)match, arg);
			item = item->next;
			if (match != 0)
			{
				match = match->next;
			}
		}
	}

	// FUNCTION: ENGINE 0x105A8130
	void SetHead(TrackGroup* group, Track* item)
	{
		group->head = item;
	}

	// FUNCTION: ENGINE 0x105A8150
	int TrackGroup::Add(Track* item)
	{
		if (item == 0)
		{
			return -1;
		}
		Track* last = 0;
		int count = 0;
		Track* current = head;
		while (current != 0)
		{
			last = current;
			current = current->next;
			count = count + 1;
		}
		item->SetNext(current);
		if (last != 0)
		{
			last->SetNext(item);
			return count;
		}
		SetHead(this, item);
		return count;
	}

	// FUNCTION: ENGINE 0x105A8330
	int TrackGroup::Insert(int index, Track* item)
	{
		if (item == 0)
		{
			return -1;
		}
		if (index < 0)
		{
			return Add(item);
		}
		Track* previous = 0;
		Track* current = head;
		int position = 0;
		while (current != 0 && position <= index && position != index)
		{
			previous = current;
			current = current->next;
			position = position + 1;
		}
		item->SetNext(current);
		if (previous != 0)
		{
			previous->SetNext(item);
			return position;
		}
		SetHead(this, item);
		return position;
	}

	// FUNCTION: ENGINE 0x105A9F60
	void Track::SetNext(Track* newNext)
	{
		if (next != 0)
		{
			delete next;
		}
		next = newNext;
	}
}
