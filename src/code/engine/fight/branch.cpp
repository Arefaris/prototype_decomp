// The branch tree of the fight system: the entity and branch base classes, their children and the lists of the nodes
// that watch them (part of the unit 0x105A2440 - 0x105A5F00; the declarations are in branch.h).
#include "code/core/heap.h"
#include "code/core/criticalsection.h"
#include "code/engine/fight/chunk.h"
#include "code/engine/fight/fightsystem.h"
#include "code/engine/fight/reader.h"
#include "code/engine/fight/trackfactory.h"
#include "code/core/hash.h"
#include "code/core/strings.h"
#include "code/engine/system/streampackage.h"
#include <stdlib.h>

namespace fight
{
	// The length of the text a name's hash is written as (0x10E2C7BC), the separator of the paths (0x110B4254) and the
	// hashes of the path parts that stand for the parent and for the branch itself (0x11276190 / 0x11276148)
	extern const int gNameHashTextLength;
	extern const char* gPathSeparator;
	extern unsigned __int64 gParentPathHash;
	extern unsigned __int64 gSelfPathHash;
	// The text of the name a branch is stored under (0x110B426C) and the keys of its path, its offset and its flag
	// (0x112761A8 / 0x112761E0 / 0x112761D0)
	extern const char* gBranchNameText;
	extern core::Name<core::CaseSensitiveKey> gBranchPathKey;
	extern core::Name<core::CaseSensitiveKey> gBranchOffsetKey;
	extern core::Name<core::CaseSensitiveKey> gBranchFlagKey;

	// 0x105A7510 (the random source of the fight core)
	float GetRandomValue(core::IRefCount* owner);

	// Holds the load listeners' critical section while it lives
	struct WatcherLock
	{
		WatcherLock()
			: lock(engine::gLoadListeners->lock)
		{
			core::CriticalSectionEnter(lock);
		}
		~WatcherLock()
		{
			core::CriticalSectionLeave(lock);
		}

		void* lock;
	};

	__forceinline void Param::VisitProperties2(int owner)
	{
		int index = 0;
		Property* property = GetProperty(index);
		if (property != 0)
		{
			do
			{
				property->Slot2((int)this, owner);
				index = index + 1;
				property = GetProperty(index);
			}
			while (property != 0);
		}
	}

	__forceinline void Param::VisitProperties3(int owner)
	{
		int index = 0;
		Property* property = GetProperty(index);
		if (property != 0)
		{
			do
			{
				property->Slot3((int)this, owner);
				index = index + 1;
				property = GetProperty(index);
			}
			while (property != 0);
		}
	}

	__forceinline void Param::VisitProperties6(int owner, void* reader)
	{
		int index = 0;
		Property* property = Slot1(index);
		if (property != 0)
		{
			do
			{
				if (!property->IsNull())
				{
					property->Slot6((int)this, owner, reader);
				}
				index = index + 1;
				property = Slot1(index);
			}
			while (property != 0);
		}
	}

	// FUNCTION: ENGINE 0x105A5120
	// EQUIVALENT: scheduling (the engine stores the reference count before it forms the name's address); 73.5 %
	Entity::Entity()
	{
	}

	// FUNCTION: ENGINE 0x105A5150
	Entity::~Entity()
	{
	}

	// ---- The tree ---------------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A25F0
	int Branch::GetIndex() const
	{
		return index;
	}

	// FUNCTION: ENGINE 0x105A2600
	void Branch::SetIndex(int newIndex)
	{
		index = newIndex;
	}

	// FUNCTION: ENGINE 0x105A2610
	Branch* Branch::GetParent() const
	{
		return parent;
	}

	// FUNCTION: ENGINE 0x105A2620
	Branch* Branch::GetNextSibling() const
	{
		return nextSibling;
	}

	// FUNCTION: ENGINE 0x105A26D0
	void Branch::Slot14(Branch* newParent)
	{
		parent = newParent;
	}

	// FUNCTION: ENGINE 0x105A2710
	const Branch* Branch::GetFirstOfTree() const
	{
		const Branch* node = this;
		if (!IsChunkRoot())
		{
			node = parent;
			if (node != 0)
			{
				do
				{
					if (node->IsChunkRoot())
					{
						break;
					}
					node = node->parent;
				}
				while (node != 0);
			}
		}
		return dynamic_cast<const Chunk*>(node);
	}

	// FUNCTION: ENGINE 0x105A2760
	Branch* Branch::GetFirstOfTree()
	{
		Branch* node = this;
		if (!IsChunkRoot())
		{
			node = parent;
			if (node != 0)
			{
				do
				{
					if (node->IsChunkRoot())
					{
						break;
					}
					node = node->parent;
				}
				while (node != 0);
			}
		}
		return dynamic_cast<Chunk*>(node);
	}

	// FUNCTION: ENGINE 0x105A2820
	Branch* Branch::GetNextAfterChildren()
	{
		Branch* node = this;
		if (node != 0)
		{
			do
			{
				Branch* following = node->nextSibling;
				if (following != 0)
				{
					return following;
				}
				node = node->parent;
			}
			while (node != 0);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105A2840
	Branch* Branch::GetNextOfTree()
	{
		if (firstChild != 0)
		{
			return firstChild;
		}
		return GetNextAfterChildren();
	}

	// FUNCTION: ENGINE 0x105A2850
	Branch* Branch::GetRoot()
	{
		Branch* node = this;
		Branch* above = node->parent;
		if (above != 0)
		{
			do
			{
				node = above;
				above = above->parent;
			}
			while (above != 0);
		}
		return node;
	}

	// FUNCTION: ENGINE 0x105A2870
	int Branch::GetDepth()
	{
		int depth = 0;
		for (Branch* node = parent; node != 0; node = node->parent)
		{
			depth = depth + 1;
		}
		return depth;
	}

	// FUNCTION: ENGINE 0x105A2890
	int Branch::GetChildCount()
	{
		int count = 0;
		for (Branch* node = firstChild; node != 0; node = node->nextSibling)
		{
			count = count + 1;
		}
		return count;
	}

	// FUNCTION: ENGINE 0x105A28E0
	Branch* Branch::GetChild(int position)
	{
		int current = 0;
		Branch* node = firstChild;
		if (node != 0)
		{
			do
			{
				if (position < current)
				{
					break;
				}
				if (position == current)
				{
					return node;
				}
				node = node->nextSibling;
				current = current + 1;
			}
			while (node != 0);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105A28B0
	const Branch* Branch::GetChild(int position) const
	{
		int current = 0;
		Branch* node = firstChild;
		if (node != 0)
		{
			do
			{
				if (position < current)
				{
					break;
				}
				if (position == current)
				{
					return node;
				}
				node = node->nextSibling;
				current = current + 1;
			}
			while (node != 0);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105A2910
	int Branch::IndexOfChild(const Branch* child)
	{
		int position = 0;
		for (Branch* node = firstChild; node != 0; node = node->nextSibling)
		{
			if (node == child)
			{
				return position;
			}
			position = position + 1;
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x105A2940
	bool Branch::IsAncestorOf(const Branch* other)
	{
		if (other != 0)
		{
			do
			{
				other = other->parent;
				if (other == this)
				{
					return true;
				}
			}
			while (other != 0);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A2A10
	void Branch::ReleaseChildren()
	{
		Branch** link = &firstChild;
		while (firstChild != 0)
		{
			Branch* child = *link;
			child->Slot9();
			child->Slot16(link);
			child->Release();
		}
		firstChild = 0;
	}

	// FUNCTION: ENGINE 0x105A2960
	void Branch::Slot15(Branch* newParent, Branch** link)
	{
		nextSibling = *link;
		*link = this;
		Slot14(newParent);
	}

	// FUNCTION: ENGINE 0x105A2980
	void Branch::Slot16(Branch** following)
	{
		*following = nextSibling;
		nextSibling = 0;
		Slot14(0);
	}

	// FUNCTION: ENGINE 0x105A29A0
	int Branch::AddChild(int position, Branch* child)
	{
		if (child == 0)
		{
			return -1;
		}
		Branch* previous = 0;
		int current = 0;
		Branch* node = firstChild;
		if (node != 0)
		{
			do
			{
				if (current == position)
				{
					break;
				}
				previous = node;
				node = node->nextSibling;
				current = current + 1;
			}
			while (node != 0);
		}
		Branch** link = previous != 0 ? &previous->nextSibling : &firstChild;
		child->Slot15(this, link);
		child->AddRef();
		return current;
	}

	// FUNCTION: ENGINE 0x105A2A00
	int Branch::AddChild(Branch* child)
	{
		return AddChild(-1, child);
	}

	// FUNCTION: ENGINE 0x105A2A50
	bool Branch::RemoveChild(int position)
	{
		Branch* previous = 0;
		int current = 0;
		Branch* node = firstChild;
		if (node != 0)
		{
			do
			{
				if (current > position)
				{
					break;
				}
				if (current == position)
				{
					node->Slot9();
					node->Slot16(previous != 0 ? &previous->nextSibling : &firstChild);
					node->Release();
					return true;
				}
				previous = node;
				node = node->nextSibling;
				current = current + 1;
			}
			while (node != 0);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A2AB0
	bool Branch::RemoveChild(Branch* child)
	{
		Branch* previous = 0;
		Branch* node = firstChild;
		if (node != 0)
		{
			do
			{
				if (node == child)
				{
					node->Slot9();
					node->Slot16(previous != 0 ? &previous->nextSibling : &firstChild);
					node->Release();
					return true;
				}
				previous = node;
				node = node->nextSibling;
			}
			while (node != 0);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A2C90
	void Branch::Slot9()
	{
		Slot17(0, 0);
	}

	// FUNCTION: ENGINE 0x105A2CA0
	void Branch::Slot7()
	{
		VisitProperties2((int)this);
		for (Branch* child = firstChild; child != 0; child = child->nextSibling)
		{
			child->Slot7();
		}
	}

	// FUNCTION: ENGINE 0x105A2D00
	void Branch::Slot8()
	{
		for (Branch* child = firstChild; child != 0; child = child->nextSibling)
		{
			child->Slot8();
		}
		VisitProperties3((int)this);
	}

	// FUNCTION: ENGINE 0x105A27B0
	TrackRegistry* Branch::Slot6()
	{
		engine::LoadListeners* listeners = engine::gLoadListeners;
		if (listeners == 0)
		{
			return 0;
		}
		Branch* top = this;
		while (top->parent != 0)
		{
			top = top->parent;
			if (top->IsChunkRoot())
			{
				TrackRegistry* context = top->Slot6();
				if (context != 0)
				{
					return context;
				}
			}
		}
		for (TrackRegistry* context = listeners->first; context != 0; context = context->next)
		{
			if (context->branches == top)
			{
				return context;
			}
		}
		return 0;
	}

	// ---- Construction and destruction -----------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A3D30
	// EQUIVALENT: scheduling (the engine stores the watcher list after the vftables, ours before); 73.6 %
	Branch::Branch()
		: parent(0), firstChild(0), nextSibling(0)
	{
		index = -1;
		watchers.head = 0;
	}

	// FUNCTION: ENGINE 0x105A3D70
	Property* Branch::GetProperty(int index)
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x105A3D80
	Branch::~Branch()
	{
		ReleaseChildren();
		Branch::Slot9();
		BranchWatch* node = watchers.head;
		if (node != 0)
		{
			do
			{
				BranchWatch* following = node->next;
				node->branch = 0;
				node->prev = 0;
				node->next = 0;
				node = following;
			}
			while (node != 0);
			watchers.head = 0;
		}
	}

	// ---- Watchers ---------------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A30F0
	void WatcherList::Remove(BranchWatch* node)
	{
		if (head == node)
		{
			BranchWatch* following = node->next;
			if (following != 0)
			{
				following->prev = node->prev;
			}
			head = head->next;
		}
		else
		{
			BranchWatch* before = node->prev;
			if (before != 0)
			{
				before->next = node->next;
			}
			BranchWatch* after = node->next;
			if (after != 0)
			{
				after->prev = node->prev;
			}
		}
		node->prev = 0;
		node->next = 0;
		node->branch = 0;
	}

	// FUNCTION: ENGINE 0x105A3A40
	// EQUIVALENT: instruction selection (the engine loads the listeners' address first and forms the lock's address with an lea, ours loads and adds); 22.7 %
	void Branch::Register(void* entry)
	{
		void* lock = engine::gLoadListeners->lock;
		core::CriticalSectionEnter(lock);
		BranchWatch* node = (BranchWatch*)entry;
		node->next = watchers.head;
		if (watchers.head != 0)
		{
			watchers.head->prev = node;
		}
		node->prev = 0;
		watchers.head = node;
		core::CriticalSectionLeave(lock);
	}

	// FUNCTION: ENGINE 0x105A3A90
	// EQUIVALENT: instruction selection (the engine loads the listeners' address first and forms the lock's address with an lea, ours loads and adds); 32.7 %
	void Branch::Unregister(void* entry)
	{
		void* lock = engine::gLoadListeners->lock;
		core::CriticalSectionEnter(lock);
		watchers.Remove((BranchWatch*)entry);
		core::CriticalSectionLeave(lock);
	}

	// FUNCTION: ENGINE 0x105A3AC0
	// EQUIVALENT: instruction selection (the engine loads the listeners' address first and forms the lock's address with an lea, ours loads and adds); 30.0 %
	void Branch::SetWatchers(BranchWatch* head)
	{
		void* lock = engine::gLoadListeners->lock;
		core::CriticalSectionEnter(lock);
		watchers.head = head;
		core::CriticalSectionLeave(lock);
	}

	// FUNCTION: ENGINE 0x105A3AF0
	void WatcherList::Retarget(Branch* unused, Branch* newBranch)
	{
		BranchWatch* node = head;
		if (node != 0)
		{
			do
			{
				BranchWatch* following = node->next;
				node->branch = newBranch;
				if (newBranch == 0)
				{
					node->prev = 0;
					node->next = 0;
				}
				node = following;
			}
			while (node != 0);
		}
		if (newBranch != 0)
		{
			newBranch->SetWatchers(head);
		}
		head = 0;
	}

	// ---- Moving between the branches ------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A3290
	Branch* Branch::GetLastOfTree()
	{
		Branch* node = this;
		Branch* last = 0;
		do
		{
			int count = node->GetChildCount();
			while (last == 0 && count > 0)
			{
				count = count - 1;
				last = node->GetChild(count);
				if (last != 0 && last->parent != node)
				{
					last = 0;
				}
			}
			if (last == 0)
			{
				last = node;
			}
			else if (last->GetChildCount() > 0)
			{
				node = last;
				last = 0;
			}
		}
		while (last == 0);
		return last;
	}

	// FUNCTION: ENGINE 0x105A32E0
	// EQUIVALENT: loop layout (the engine jumps back to the reset of the candidate, ours tests the position at the bottom); 81.7 %
	Branch* Branch::GetPreviousSiblingOrParent()
	{
		Branch* above = parent;
		if (above == 0)
		{
			return 0;
		}
		int count = above->GetChildCount();
		int position = 0;
		if (count > 0)
		{
			do
			{
				if (above->GetChild(position) == this)
				{
					if (position != 0)
					{
						Branch* sibling = 0;
						for (;;)
						{
							while (position > 0)
							{
								position = position - 1;
								sibling = above->GetChild(position);
								if (sibling == 0)
								{
									continue;
								}
								if (sibling->parent == above)
								{
									return sibling;
								}
								break;
							}
							if (position <= 0)
							{
								break;
							}
							sibling = 0;
						}
						if (sibling != 0)
						{
							return sibling;
						}
					}
					return above;
				}
				position = position + 1;
			}
			while (position < count);
		}
		return above;
	}

	// FUNCTION: ENGINE 0x105A3350
	// EQUIVALENT: loop layout (the engine jumps back to the reset of the candidate, ours tests the position at the bottom) and the candidate's register; 76.9 %
	Branch* Branch::GetPreviousOfTree()
	{
		Branch* above = parent;
		if (above == 0)
		{
			return 0;
		}
		int count = above->GetChildCount();
		int position = 0;
		if (count > 0)
		{
			do
			{
				if (above->GetChild(position) == this)
				{
					if (position != 0)
					{
						Branch* sibling = 0;
						for (;;)
						{
							while (position > 0)
							{
								position = position - 1;
								sibling = above->GetChild(position);
								if (sibling == 0)
								{
									continue;
								}
								if (sibling->parent == above)
								{
									return sibling->GetLastOfTree();
								}
								break;
							}
							if (position <= 0)
							{
								break;
							}
							sibling = 0;
						}
						if (sibling != 0)
						{
							return sibling->GetLastOfTree();
						}
					}
					return above;
				}
				position = position + 1;
			}
			while (position < count);
		}
		return above;
	}

	// FUNCTION: ENGINE 0x105A33C0
	int Branch::IndexOfChildNamed(const core::Name<core::CaseSensitiveKey>& childName)
	{
		int position = 0;
		for (Branch* node = firstChild; node != 0; node = node->nextSibling)
		{
			if (node->name == childName)
			{
				return position;
			}
			position = position + 1;
		}
		return -1;
	}

	// FUNCTION: ENGINE 0x105A3480
	Branch* Branch::FindNamedAbove(const core::Name<core::CaseSensitiveKey>& childName)
	{
		Branch* above = this;
		for (;;)
		{
			for (Branch* node = above->firstChild; node != 0; node = node->nextSibling)
			{
				if (node->name == childName)
				{
					return node;
				}
			}
			Branch* up = above->parent;
			if (up == 0)
			{
				return 0;
			}
			above = up;
		}
	}

	// FUNCTION: ENGINE 0x105A34D0
	Branch* Branch::FindChildNamed(const core::Name<core::CaseSensitiveKey>& childName)
	{
		for (Branch* node = firstChild; node != 0; node = node->nextSibling)
		{
			if (node->name == childName)
			{
				return node;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105A3510
	Branch* Branch::Slot10(Sequencer* sequencer, void* params, int a, bool b)
	{
		return PickChild(sequencer, params);
	}

	// FUNCTION: ENGINE 0x105A2EB0
	bool Branch::Slot11(Sequencer* sequencer, void* params, int a)
	{
		return false;
	}

	// FUNCTION: ENGINE 0x105A2EC0
	void Branch::Slot12(int a, core::IRefCount* b, Sequencer* sequencer)
	{
	}

	// ---- Changing the tree ------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A2B10
	// NONMATCHING: the registers of the child, the parent and the list walk are allocated in another order, 0.8 %
#ifdef NONMATCHING
	bool Branch::MoveChild(Branch* child, Branch* newParent, int newIndex)
	{
		if (child == 0 || newParent == 0)
		{
			return false;
		}
		Branch** head = &firstChild;
		Branch* node = firstChild;
		Branch* previous = 0;
		while (node != 0)
		{
			if (child == node)
			{
				if (newParent != this)
				{
					node->Slot16(previous != 0 ? &previous->nextSibling : head);
				}
				else
				{
					if (previous != 0)
					{
						previous->nextSibling = node->nextSibling;
					}
					else
					{
						*head = node->nextSibling;
					}
					node->nextSibling = 0;
				}
				Branch** link = &newParent->firstChild;
				Branch* following = newParent->firstChild;
				Branch* before = 0;
				int position = 0;
				if (following != 0)
				{
					do
					{
						if (position == newIndex)
						{
							break;
						}
						before = following;
						following = following->nextSibling;
						position = position + 1;
					}
					while (following != 0);
				}
				if (newParent != this)
				{
					node->Slot15(newParent, before != 0 ? &before->nextSibling : link);
					return true;
				}
				if (before != 0)
				{
					before->nextSibling = node;
					node->nextSibling = following;
					return true;
				}
				*link = node;
				node->nextSibling = following;
				return true;
			}
			previous = node;
			node = node->nextSibling;
		}
		return false;
	}
#endif

	// FUNCTION: ENGINE 0x105A2C00
	void Branch::ReplaceChild(Branch* oldChild, Branch* newChild)
	{
		if (oldChild != newChild)
		{
			Branch* previous = 0;
			Branch* node = firstChild;
			if (node != 0)
			{
				do
				{
					if (node == oldChild)
					{
						oldChild->Slot9();
						oldChild->Slot16(previous != 0 ? &previous->nextSibling : &firstChild);
						newChild->Slot15(this, previous != 0 ? &previous->nextSibling : &firstChild);
						newChild->AddRef();
						oldChild->Release();
						return;
					}
					previous = node;
					node = node->nextSibling;
				}
				while (node != 0);
			}
		}
	}

	// FUNCTION: ENGINE 0x105A3430
	bool Branch::MoveChildToIndex(int fromIndex, int toIndex)
	{
		return MoveChild(GetChild(fromIndex), this, toIndex);
	}

	// FUNCTION: ENGINE 0x105A3460
	bool Branch::MoveChild(Branch* child, int toIndex)
	{
		return MoveChild(child, this, toIndex);
	}

	// FUNCTION: ENGINE 0x105A3400
	bool Branch::IsNameBefore(const Branch* other) const
	{
		const char* first = name.GetText();
		const char* second = other->name.GetText();
		if (core::StrICmp(first, second) < 0)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x105A3B30
	void Branch::SortChildren(bool deep)
	{
		int count = GetChildCount();
		int position = 0;
		if (count > 0)
		{
			do
			{
				int other = position + 1;
				if (other < count)
				{
					do
					{
						Branch* first = GetChild(position);
						Branch* second = GetChild(other);
						if (second->IsNameBefore(first))
						{
							MoveChildToIndex(other, position);
						}
						other = other + 1;
					}
					while (other < count);
				}
				position = position + 1;
			}
			while (position < count);
		}
		if (deep)
		{
			for (int i = 0; i < count; i++)
			{
				GetChild(i)->SortChildren(deep);
			}
		}
	}

	// ---- Picking and running --------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A2D60
	// EQUIVALENT: scheduling (the engine stores the float local after pushing the arguments, ours before); 79.2 %
	Branch* Branch::PickChild(Sequencer* sequencer, void* params)
	{
		float total = 0.0f;
		Branch* child = firstChild;
		if (child != 0)
		{
			do
			{
				float weight = 0.0f;
				Branch* chosen = child->Slot10(sequencer, params, (int)&weight, true);
				if (chosen != 0)
				{
					if (weight > 0.0f)
					{
						total = weight + total;
					}
					else
					{
						return chosen;
					}
				}
				child = child->nextSibling;
			}
			while (child != 0);
			if (total <= 0.0f)
			{
				return 0;
			}
			float pick = GetRandomValue((core::IRefCount*)params) * total;
			float sum = 0.0f;
			child = firstChild;
			if (child != 0)
			{
				do
				{
					float weight = 0.0f;
					Branch* chosen = child->Slot10(sequencer, params, (int)&weight, true);
					if (chosen != 0 && weight > 0.0f)
					{
						sum = weight + sum;
						if (sum >= pick)
						{
							return chosen;
						}
					}
					child = child->nextSibling;
				}
				while (child != 0);
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105A2E50
	Branch* Branch::RunNext(Sequencer* sequencer, void* params, Branch* stop)
	{
		Branch* node = GetNextAfterChildren();
		if (node != 0)
		{
			do
			{
				if (node == stop->GetNextAfterChildren())
				{
					return 0;
				}
				Branch* chosen = node->Slot10(sequencer, params, 0, true);
				if (chosen != 0)
				{
					return chosen;
				}
				node = node->GetNextAfterChildren();
			}
			while (node != 0);
		}
		return 0;
	}

	// ---- Names and paths --------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A2ED0
	static __declspec(noinline) unsigned __int64 ParseNameHash(const char* text)
	{
		if (text[0] == '0' && text[1] == 'x' && core::StrLen(text) == gNameHashTextLength)
		{
			char digits[9];
			core::StrNCpy(digits, text + 2, 9u);
			char* end;
			unsigned int high = strtoul(digits, &end, 16);
			unsigned int low = strtoul(text + 10, &end, 16);
			return (unsigned __int64)high * 0x100000000ui64 + low;
		}
		return core::Hash64(text, 0);
	}

	// FUNCTION: ENGINE 0x105A3530
	int Branch::GetPathLength(int flag)
	{
		int length = name.GetHash() != 0 ? gNameHashTextLength : 0;
		for (Branch* node = parent; node != 0; node = node->parent)
		{
			length = length + 1;
			length = length + (node->name.GetHash() != 0 ? gNameHashTextLength : 0);
		}
		return length + 1;
	}

	// FUNCTION: ENGINE 0x105A3590
	bool Branch::GetPath(char* buffer, int size, int flag)
	{
		char scratch[1024];
		unsigned __int64 hash = name.GetHash();
		if (hash == 0)
		{
			if (size > 0)
			{
				buffer[0] = 0;
			}
		}
		else
		{
			core::SNPrintf(buffer, size, "0x%08x%08x", (unsigned int)(hash >> 32), (unsigned int)hash);
		}
		for (Branch* node = parent; node != 0; node = node->parent)
		{
			hash = node->name.GetHash();
			if (hash == 0)
			{
				core::SNPrintf(scratch, 1024, "%s%s", gPathSeparator, buffer);
			}
			else
			{
				core::SNPrintf(scratch, 1024, "0x%08x%08x%s%s", (unsigned int)(hash >> 32), (unsigned int)hash, gPathSeparator, buffer);
			}
			core::SNPrintf(buffer, size, "%s", scratch);
		}
		core::SNPrintf(scratch, 1024, "%s%s", gPathSeparator, buffer);
		core::SNPrintf(buffer, size, "%s", scratch);
		return true;
	}

	// FUNCTION: ENGINE 0x105A3690
	// EQUIVALENT: register allocation (the engine keeps the path in edi and the hash in esi:ebx, ours the other way round); 85.2 %
	Branch* Branch::FindInTree(const char* path)
	{
		char buffer[1024];
		const char* separator = gPathSeparator;
		if (path[0] == separator[0])
		{
			path = path + 1;
		}
		char* out = buffer;
		while (path[0] != 0 && path[0] != separator[0])
		{
			*out = path[0];
			path = path + 1;
			out = out + 1;
		}
		*out = 0;
		unsigned __int64 hash = ParseNameHash(buffer);
		if (hash == name.GetHash())
		{
			if (path[0] == 0)
			{
				return this;
			}
			for (Branch* child = firstChild; child != 0; child = child->nextSibling)
			{
				Branch* found = child->FindInTree(path);
				if (found != 0)
				{
					return found;
				}
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x105A3740
	Branch* Branch::FindByPath(const char* path)
	{
		char buffer[1024];
		if (path == 0 || path[0] == 0)
		{
			return this;
		}
		const char* separator = gPathSeparator;
		if (path[0] == separator[0])
		{
			Branch* root = GetRoot();
			if (root != 0)
			{
				return root->FindInTree(path);
			}
			return 0;
		}
		char* out = buffer;
		do
		{
			if (path[0] == separator[0])
			{
				break;
			}
			*out = path[0];
			path = path + 1;
			out = out + 1;
		}
		while (path[0] != 0);
		*out = 0;
		unsigned __int64 hash = ParseNameHash(buffer);
		if (path[0] != 0)
		{
			path = path + 1;
		}
		if (hash == gParentPathHash)
		{
			if (parent != 0)
			{
				return parent->FindByPath(path);
			}
			return 0;
		}
		if (hash != gSelfPathHash)
		{
			for (Branch* child = firstChild; child != 0; child = child->nextSibling)
			{
				if (child->name.GetHash() == hash)
				{
					return child->FindByPath(path);
				}
			}
			return 0;
		}
		return FindByPath(path);
	}

	// ---- Merging and reading --------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A3C60
	// EQUIVALENT: register allocation (the engine keeps the children in edi / esi, ours the other way round); 90.0 %
	void Branch::Slot17(Branch* other, int argument)
	{
		watchers.Retarget(this, other);
		Branch* child = firstChild;
		Branch* match = other != 0 ? other->firstChild : 0;
		if (child != 0)
		{
			do
			{
				if (other != 0 && match != 0)
				{
					if (child->name.GetHash() != match->name.GetHash())
					{
						match = 0;
					}
				}
				child->Slot17(match, argument);
				child = child->nextSibling;
				match = match != 0 ? match->nextSibling : 0;
			}
			while (child != 0);
		}
		Param* otherPart = other;
		MergeProperties(otherPart, argument);
	}

	// FUNCTION: ENGINE 0x105A2F60
	bool Branch::ReadProperties(Reader* reader)
	{
		VisitProperties6((int)this, reader);
		return true;
	}

	// FUNCTION: ENGINE 0x105A2FC0
	bool Branch::LoadChildren(Chunk* owner, Reader* reader, int position)
	{
		TrackRegistry* context = owner->Slot6();
		if (reader->HasChild())
		{
			do
			{
				int before = GetChildCount();
				const core::Name<core::CaseSensitiveKey>* childName = reader->GetChildName();
				BranchFactory* factory = context != 0 ? context->FindBranchFactory(*childName) : 0;
				if (factory == 0)
				{
					ReportReadError(reader, "");
					reader->SkipChild();
				}
				else
				{
					Branch* child = factory->CreateBranch();
					child->AddRef();
					child->Slot14(this);
					child->Slot13(childName, owner, reader, position);
					child->Release();
				}
				if (GetChildCount() > before && position >= 0)
				{
					position = position + 1;
				}
			}
			while (reader->HasChild());
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105A3860
	// EQUIVALENT: register allocation (the engine keeps the reader in edi and the branch in esi, the parent found by the path in ebp) and the place of that copy; 88.6 %
	bool Branch::ReadHeader(Chunk* owner, Reader* reader, int position)
	{
		reader->ReadName(core::Name<core::CaseSensitiveKey>(gBranchNameText, 1), this);
		char path[1024] = { 0 };
		reader->ReadString(gBranchPathKey, path, 1024);
		int offset = 0;
		reader->ReadInt(gBranchOffsetKey, &offset);
		if (!reader->UsesNumbers())
		{
			bool flag = false;
			reader->ReadBool(gBranchFlagKey, &flag);
		}
		Branch* target = parent;
		if (path[0] != 0)
		{
			if (path[0] == '/')
			{
				TrackRegistry* context = Slot6();
				if (context != 0)
				{
					Branch* found = context->branches->FindInTree(path);
					if (found != 0 && found != parent)
					{
						ReportReadError(reader, "", path);
						target = found;
					}
				}
			}
			else
			{
				Branch* found = owner->FindByPath(path);
				if (found != 0)
				{
					target = found;
				}
			}
		}
		bool result = false;
		if (target != 0)
		{
			int where = position;
			if (position < 0)
			{
				int best = -1;
				int bestIndex = -1;
				int count = target->GetChildCount();
				for (int i = 0; i < count; i++)
				{
					Branch* candidate = target->GetChild(i);
					if (candidate->index > bestIndex)
					{
						bestIndex = candidate->index;
						best = i;
					}
				}
				if (best >= 0)
				{
					where = best + offset;
					if (where < 0)
					{
						where = 0;
					}
					else if (where > count)
					{
						where = count;
					}
				}
			}
			result = target->AddChild(where, this) >= 0;
			if (!result)
			{
				ReportReadError(reader, "");
			}
		}
		if (position < 0 && target != 0 && target->index >= 0)
		{
			index = owner->NextIndex();
		}
		return result;
	}

	// FUNCTION: ENGINE 0x105A3BE0
	bool Branch::Slot13(const core::Name<core::CaseSensitiveKey>* key, Chunk* owner, Reader* reader, int position)
	{
		if (!reader->HasChild())
		{
			return false;
		}
		if (*reader->GetChildName() != *key)
		{
			return false;
		}
		reader->EnterChild(*key);
		ReadHeader(owner, reader, position);
		ReadProperties(reader);
		LoadChildren(owner, reader, -1);
		reader->ExitChild();
		return true;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x105A26C0
// FUNCTION: ENGINE 0x105A3DD0
// FUNCTION: ENGINE 0x105A5170
