// The branches a fight file is made of: the reference, the chunk, the bank, the store and the node, their property
// lists and factories, and the action that starts a branch from a chunk (part of the unit 0x105A2440 - 0x105B3680; the
// declarations are in chunk.h).
#include "code/engine/fight/chunk.h"
#include "code/core/heap.h"
#include "code/engine/fight/fightsystem.h"
#include "code/engine/fight/params.h"
#include "code/engine/fight/reader.h"
#include "code/engine/system/streampackage.h"
#include <new>

namespace engine
{
	// 0x10098F50: stores a reference counted pointer
	void AssignRefCounted(core::IRefCount** slot, core::IRefCount* value);
}

namespace fight
{
	// The keys a chunk is read by
	extern core::Name<core::CaseSensitiveKey> gChunkIndexKey;
	extern core::Name<core::CaseSensitiveKey> gChunkNameKey;
	extern core::Name<core::CaseSensitiveKey> gChunkContextKey;
	extern core::Name<core::CaseSensitiveKey> gBranchPathKey;
	extern core::Name<core::CaseSensitiveKey> gBranchOffsetKey;
	extern core::Name<core::CaseSensitiveKey> gBranchFlagKey;

	// The names the branch kinds register their factories under
	extern const char* const gReferenceBranchName;
	extern const char* const gStoreBranchName;
	extern const char* const gBankBranchName;
	extern const char* const gNodeBranchName;

	// GLOBAL: ENGINE 0x11276218
	Property** gReferenceProperties;
	// GLOBAL: ENGINE 0x11276238
	Property** gBankProperties;
	// GLOBAL: ENGINE 0x11276248
	Property** gNodeProperties;

	// ---- fight::Params ---------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105AA820
	Params::Params(int newValue)
		: value(newValue)
	{
	}

	// FUNCTION: ENGINE 0x105AA840
	Params::~Params()
	{
	}

	// ---- fight::BranchFactory --------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105A2690
	BranchFactory::BranchFactory()
	{
	}

	// FUNCTION: ENGINE 0x105A26B0
	BranchFactory::~BranchFactory()
	{
	}

	// FUNCTION: ENGINE 0x105A30A0
	void Branch::ListChild(Item* child)
	{
		Branch* root = GetFirstOfTree();
		if (root != 0)
		{
			((Chunk*)root)->AddNotification(this, child);
		}
	}

	// ---- fight::Reference ------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105AA360
	BranchHolder* Reference::GetTarget()
	{
		return &target;
	}

	// FUNCTION: ENGINE 0x105AA370
	ConditionList* Reference::GetConditions()
	{
		return &conditions;
	}

	// FUNCTION: ENGINE 0x105AA380
	Property* Reference::GetProperty(int index)
	{
		return gReferenceProperties[index];
	}

	// FUNCTION: ENGINE 0x105AA390
	void Reference::ClearProperties()
	{
		FreePropertyList(&gReferenceProperties);
	}

	// FUNCTION: ENGINE 0x105AA3A0
	Reference::Reference()
		: target(0), running(0)
	{
	}

	// FUNCTION: ENGINE 0x105AA3E0
	Reference::~Reference()
	{
	}

	// FUNCTION: ENGINE 0x105AA410
	// EQUIVALENT: the engine moves the result into eax after restoring edi, ours before; 96.0 %
	Branch* Reference::ResolveTarget()
	{
		int steps = 0;
		Branch* branch = target.GetBranch();
		if (branch != 0)
		{
			do
			{
				if (dynamic_cast<Reference*>(branch) == 0)
				{
					return branch;
				}
				steps = steps + 1;
				if (steps > 0x100 || branch == this)
				{
					return 0;
				}
				branch = ((Reference*)branch)->target.GetBranch();
			}
			while (branch != 0);
		}
		return branch;
	}

	// FUNCTION: ENGINE 0x105AA480
	Branch* Reference::Slot10(Sequencer* sequencer, void* params, int a, bool b)
	{
		if (running > 0)
		{
			running = 0;
			return 0;
		}
		running = running + 1;
		Branch* result = 0;
		if (conditions.Evaluate((int)this, (int)sequencer, (int)params, a))
		{
			Branch* branch = target.GetBranch();
			if (branch != 0)
			{
				result = branch->Slot10(sequencer, params, a, b);
			}
		}
		running = running - 1;
		return result;
	}

	// FUNCTION: ENGINE 0x105AA630
	// EQUIVALENT: shrink-wrap: the engine saves esi and edi before it tests the list, ours after; 96.0 %
	void Reference::RegisterProperties()
	{
		if (gReferenceProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyBranch<Reference>("reference", &Reference::GetTarget);
			properties[0] = property;
			property = new PropertyConditionGroup<Reference>("conditions", &Reference::GetConditions);
			properties[1] = property;
			RegisterPropertyList(properties, &gReferenceProperties);
		}
	}

	template class PropertyBranch<Reference>;
	template class PropertyConditionGroup<Reference>;
	template class BranchFactoryTemplate<Reference>;
	template class BranchFactoryCasterTemplate<BranchFactoryTemplate<Reference> >;

	// FUNCTION: ENGINE 0x105AA610
	BranchFactory* CreateReferenceBranchFactory(const char* name)
	{
		BranchFactoryCasterTemplate<BranchFactoryTemplate<Reference> > caster;
		return FindBranchFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105AA6F0
	void RegisterReferenceBranchFactory(TrackRegistry* registry)
	{
		BranchFactoryCasterTemplate<BranchFactoryTemplate<Reference> > caster;
		registry->AddFactory(FindBranchFactory(gReferenceBranchName, &caster));
	}

	// ---- fight::Chunk ----------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105AAA00
	Chunk::Chunk()
	{
		loaded = 0;
		context = 0;
		dependents = 0;
		dependentOf = 0;
		pendingNext = 0;
		notifications = 0;
		lastNotification = 0;
	}

	// FUNCTION: ENGINE 0x105AAA30
	bool Chunk::IsChunkRoot() const
	{
		return true;
	}

	// FUNCTION: ENGINE 0x105AAA40
	TrackRegistry* Chunk::Slot6()
	{
		return context;
	}

	// FUNCTION: ENGINE 0x105AAA50
	void Chunk::Slot17(Branch* other, int argument)
	{
		Branch::Slot17(other, argument);
		Chunk* chunk = (Chunk*)other;
		if (chunk != 0)
		{
			Chunk* node = chunk->dependents;
			chunk->dependentOf = 0;
			for (; node != 0; node = node->dependents)
			{
				node->dependentOf = chunk;
			}
		}
		else
		{
			for (Chunk* node = dependents; node != 0;)
			{
				Chunk* following = node->dependents;
				node->dependentOf = 0;
				node->dependents = 0;
				node = following;
			}
		}
		dependents = 0;
	}

	// FUNCTION: ENGINE 0x105AAAB0
	int Chunk::NextIndex()
	{
		indexCounter = indexCounter + 1;
		return indexCounter;
	}

	// FUNCTION: ENGINE 0x105AAAC0
	void Chunk::AddNotification(Branch* branch, Item* item)
	{
		int heap = core::SetCurrentHeap(GetHeapId(1));
		ChunkNotification* note = new ChunkNotification(branch, item);
		if (lastNotification == 0)
		{
			notifications = note;
			lastNotification = note;
		}
		else
		{
			lastNotification->next = note;
			lastNotification = note;
		}
		core::SetCurrentHeap(heap);
	}

	// FUNCTION: ENGINE 0x105AAB30
	void Chunk::AddDependent(Chunk* chunk)
	{
		chunk->dependentOf = this;
		chunk->dependents = dependents;
		dependents = chunk;
	}

	// FUNCTION: ENGINE 0x105AAB50
	void Chunk::RemoveDependent(Chunk* chunk)
	{
		Chunk** link = &dependents;
		if (*link != 0)
		{
			Chunk* node;
			do
			{
				node = *link;
				if (node == chunk)
				{
					*link = chunk->dependents;
					chunk->dependents = 0;
					chunk->dependentOf = 0;
					return;
				}
				link = &node->dependents;
			}
			while (node->dependents != 0);
		}
	}

	// FUNCTION: ENGINE 0x105AAB90
	bool Chunk::Slot13(const core::Name<core::CaseSensitiveKey>* key, Chunk* owner, Reader* reader, int position)
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
		int version = 0;
		reader->ReadInt(gChunkIndexKey, &version);
		index = 0;
		indexCounter = 0;
		reader->ReadName(gChunkNameKey, this);
		Reader::Name contextName;
		reader->ReadName(gChunkContextKey, &contextName);
		char path[16];
		reader->ReadString(gBranchPathKey, path, 16);
		if (engine::gLoadListeners != 0)
		{
			context = engine::gLoadListeners->FindContext(contextName);
			if (context == 0)
			{
				ReportReadError(reader, "");
			}
		}
		else
		{
			ReportReadError(reader, "");
			context = 0;
		}
		if (context != 0)
		{
			context->AddPending((TrackRegistry::PendingItem*)this);
		}
		offset = 0;
		reader->ReadInt(gBranchOffsetKey, &offset);
		if (!reader->UsesNumbers())
		{
			bool flag = false;
			reader->ReadBool(gBranchFlagKey, &flag);
		}
		LoadChildren(this, reader, -1);
		reader->ExitChild();
		return true;
	}

	// FUNCTION: ENGINE 0x105AACE0
	void Chunk::Slot3(int argument)
	{
		if (loaded == 0)
		{
			loaded = 1;
			if (context != 0)
			{
				context->RemovePending((TrackRegistry::PendingItem*)this, 1);
				Branch* root = context->branches;
				if (root != 0)
				{
					Branch* existing = root->FindChildNamed(name);
					if (existing != 0)
					{
						if (existing->IsChunkRoot())
						{
							((Chunk*)existing)->AddDependent(this);
						}
					}
					else
					{
						context->BeginLoading(false);
						if (root->AddChild(offset, this) >= 0)
						{
							context->MarkChanged();
						}
						context->EndLoading(false);
					}
				}
			}
			while (notifications != 0)
			{
				ChunkNotification* note = notifications;
				notifications = note->next;
				note->item->Slot6((int)note->branch, argument);
				delete note;
			}
			lastNotification = 0;
		}
	}

	// FUNCTION: ENGINE 0x105AADB0
	// EQUIVALENT: shrink-wrap: the engine saves edi before it tests the parent, ours after the call through the vftable; 93.5 %
	bool Chunk::IsReady()
	{
		if (loaded == 1)
		{
			Chunk* owner = dependentOf;
			loaded = 0;
			if (owner != 0)
			{
				owner->RemoveDependent(this);
				dependentOf = 0;
				return true;
			}
			if (parent != 0)
			{
				Slot8();
				Chunk* dependent = dependents;
				Slot17(dependent, 0);
				if (dependent != 0)
				{
					parent->ReplaceChild(this, dependent);
				}
				else
				{
					context->BeginLoading(true);
					parent->RemoveChild(this);
					context->EndLoading(true);
				}
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x105AAE30
	Chunk::~Chunk()
	{
		while (notifications != 0)
		{
			ChunkNotification* note = notifications;
			notifications = note->next;
			delete note;
		}
		lastNotification = 0;
		if (context != 0)
		{
			context->RemovePending((TrackRegistry::PendingItem*)this, 0);
		}
		IsReady();
	}

	// The copy of the action store this part of the unit has
	// FUNCTION: ENGINE 0x105A3F70
	void StoreAction(Action*& slot, Action* value)
	{
		if (value != 0)
		{
			value->AddRef();
		}
		if (slot != 0)
		{
			slot->Release();
		}
		slot = value;
	}

	// FUNCTION: ENGINE 0x105A40A0
	bool Sequencer::QueueBranch(Branch* branch, void* owner)
	{
		if (branch == 0)
		{
			return false;
		}
		int heap = core::SetCurrentHeap(GetHeapId(2));
		QueuedBranchAction* action = new QueuedBranchAction(branch, (int)this, (core::IRefCount*)owner);
		if (unknown30 == 0)
		{
			StoreAction(scheduled, action);
		}
		else
		{
			unknown30->SetNext(action);
		}
		StoreAction(unknown30, action);
		core::SetCurrentHeap(heap);
		return true;
	}

	// ---- fight::QueuedBranchAction ---------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105AAED0
	QueuedBranchAction::QueuedBranchAction(Branch* newBranch, int newArgument, core::IRefCount* newOwner)
		: Action(0x760), link(newBranch), argument(newArgument), owner(0)
	{
		engine::AssignRefCounted(&owner, newOwner);
		timeBegin = 0.0f;
		unknown14 = -1.0f;
	}

	// FUNCTION: ENGINE 0x105AAF50
	QueuedBranchAction::~QueuedBranchAction()
	{
		core::SafeReleaseRef(owner);
		sequencer.End();
	}

	// FUNCTION: ENGINE 0x105AAEB0
	Sequencer* QueuedBranchAction::GetChild()
	{
		return &sequencer;
	}

	// FUNCTION: ENGINE 0x105AAEC0
	void QueuedBranchAction::Slot6()
	{
		sequencer.Reset();
	}

	// FUNCTION: ENGINE 0x105AAFB0
	bool QueuedBranchAction::Slot5(int arg, float value)
	{
		if (link.branch == 0)
		{
			return false;
		}
		sequencer.SetPending(link.branch, argument, owner, 0);
		return sequencer.Unknown105A45A0(true);
	}

	// ---- fight::Bank and fight::Store ------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105AD2E0
	ConditionList* Bank::GetConditions()
	{
		return &conditions;
	}

	// FUNCTION: ENGINE 0x105AD2F0
	Property* Bank::GetProperty(int index)
	{
		return gBankProperties[index];
	}

	// FUNCTION: ENGINE 0x105AD300
	void Bank::ClearProperties()
	{
		FreePropertyList(&gBankProperties);
	}

	// FUNCTION: ENGINE 0x105AD310
	Bank::Bank()
	{
	}

	// FUNCTION: ENGINE 0x105AD340
	Bank::~Bank()
	{
	}

	// FUNCTION: ENGINE 0x105AD360
	Branch* Bank::Slot10(Sequencer* sequencer, void* params, int a, bool b)
	{
		if (!conditions.Evaluate((int)this, (int)sequencer, (int)params, a))
		{
			return 0;
		}
		return Branch::Slot10(sequencer, params, a, b);
	}

	// FUNCTION: ENGINE 0x105AD490
	// EQUIVALENT: shrink-wrap: the engine saves esi and edi before it tests the list, ours saves edi only around the allocation; 54.2 %
	void Bank::RegisterProperties()
	{
		if (gBankProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyConditionGroup<Bank>("conditions", &Bank::GetConditions);
			properties[0] = property;
			RegisterPropertyList(properties, &gBankProperties);
		}
	}

	// FUNCTION: ENGINE 0x105AD0D0
	Store::Store()
	{
	}

	// FUNCTION: ENGINE 0x105AD0F0
	Store::~Store()
	{
	}

	// FUNCTION: ENGINE 0x105AD110
	Branch* Store::Slot10(Sequencer* sequencer, void* params, int a, bool b)
	{
		if (b)
		{
			return 0;
		}
		return Bank::Slot10(sequencer, params, a, false);
	}

	template class PropertyConditionGroup<Bank>;
	template class BranchFactoryTemplate<Bank>;
	template class BranchFactoryCasterTemplate<BranchFactoryTemplate<Bank> >;
	template class BranchFactoryTemplate<Store>;
	template class BranchFactoryCasterTemplate<BranchFactoryTemplate<Store> >;

	// FUNCTION: ENGINE 0x105AD240
	BranchFactory* CreateStoreBranchFactory(const char* name)
	{
		BranchFactoryCasterTemplate<BranchFactoryTemplate<Store> > caster;
		return FindBranchFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105AD2B0
	void RegisterStoreBranchFactory(TrackRegistry* registry)
	{
		BranchFactoryCasterTemplate<BranchFactoryTemplate<Store> > caster;
		registry->AddFactory(FindBranchFactory(gStoreBranchName, &caster));
	}

	// FUNCTION: ENGINE 0x105AD470
	BranchFactory* CreateBankBranchFactory(const char* name)
	{
		BranchFactoryCasterTemplate<BranchFactoryTemplate<Bank> > caster;
		return FindBranchFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105AD510
	void RegisterBankBranchFactory(TrackRegistry* registry)
	{
		BranchFactoryCasterTemplate<BranchFactoryTemplate<Bank> > caster;
		registry->AddFactory(FindBranchFactory(gBankBranchName, &caster));
	}

	// ---- fight::Node -----------------------------------------------------------------------------------------------

	// FUNCTION: ENGINE 0x105AD640
	bool Node::SetImmediate(bool value)
	{
		immediate = value;
		return true;
	}

	// FUNCTION: ENGINE 0x105AD650
	ConditionList* Node::GetConditions()
	{
		return &conditions;
	}

	// The engine keeps one copy of the getter of the tracks for every class that has one like it
	// FUNCTION: ENGINE 0x103B8190
	TrackGroup* Node::GetTracks()
	{
		return &tracks;
	}

	// FUNCTION: ENGINE 0x105AD660
	Property* Node::GetProperty(int index)
	{
		return gNodeProperties[index];
	}

	// FUNCTION: ENGINE 0x105AD670
	void Node::ClearProperties()
	{
		FreePropertyList(&gNodeProperties);
	}

	// FUNCTION: ENGINE 0x105AD680
	Node::Node()
		: immediate(true)
	{
	}

	// FUNCTION: ENGINE 0x105AD6B0
	Node::~Node()
	{
	}

	// FUNCTION: ENGINE 0x105AD6F0
	Branch* Node::Slot10(Sequencer* sequencer, void* params, int a, bool b)
	{
		return conditions.Evaluate((int)this, (int)sequencer, (int)params, a) ? this : 0;
	}

	// FUNCTION: ENGINE 0x105AD720
	bool Node::Slot11(Sequencer* sequencer, void* params, int a)
	{
		if (immediate)
		{
			return sequencer->SetPending(this, (int)sequencer, (core::IRefCount*)params, a);
		}
		if (tracks.head == 0)
		{
			return false;
		}
		return sequencer->QueueBranch(this, params);
	}

	// FUNCTION: ENGINE 0x105AD760
	void Node::Slot12(int a, core::IRefCount* b, Sequencer* sequencer)
	{
		tracks.Unknown105A80A0((int)this, a, (int)b, sequencer);
	}

	// FUNCTION: ENGINE 0x105AD940
	// EQUIVALENT: shrink-wrap: the engine saves esi and edi before it tests the list, ours after; 97.0 %
	void Node::RegisterProperties()
	{
		if (gNodeProperties == 0)
		{
			Property* properties[256] = { 0 };
			Property* property = 0;
			property = new PropertyBool<Node>("override", &Node::SetImmediate);
			properties[0] = property;
			property = new PropertyConditionGroup<Node>("conditions", &Node::GetConditions);
			properties[1] = property;
			property = new PropertyTrackGroup<Node>("tracks", &Node::GetTracks);
			properties[2] = property;
			RegisterPropertyList(properties, &gNodeProperties);
		}
	}

	template class PropertyBool<Node>;
	template class PropertyConditionGroup<Node>;
	template class PropertyTrackGroup<Node>;
	template class BranchFactoryTemplate<Node>;
	template class BranchFactoryCasterTemplate<BranchFactoryTemplate<Node> >;

	// FUNCTION: ENGINE 0x105AD920
	BranchFactory* CreateNodeBranchFactory(const char* name)
	{
		BranchFactoryCasterTemplate<BranchFactoryTemplate<Node> > caster;
		return FindBranchFactory(name, &caster);
	}

	// FUNCTION: ENGINE 0x105ADA30
	void RegisterNodeBranchFactory(TrackRegistry* registry)
	{
		BranchFactoryCasterTemplate<BranchFactoryTemplate<Node> > caster;
		registry->AddFactory(FindBranchFactory(gNodeBranchName, &caster));
	}

	// FUNCTION: ENGINE 0x105A6570
	void RegisterBranchFactories(TrackRegistry* registry)
	{
		RegisterNodeBranchFactory(registry);
		RegisterBankBranchFactory(registry);
		RegisterStoreBranchFactory(registry);
		RegisterReferenceBranchFactory(registry);
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x105AA4F0
// FUNCTION: ENGINE 0x105AA510
// FUNCTION: ENGINE 0x105AA520
// FUNCTION: ENGINE 0x105AA550
// FUNCTION: ENGINE 0x105AA580
// FUNCTION: ENGINE 0x105AA5B0
// FUNCTION: ENGINE 0x105AA5E0
// FUNCTION: ENGINE 0x105AA720
// FUNCTION: ENGINE 0x105AA760
// FUNCTION: ENGINE 0x105AA780
// FUNCTION: ENGINE 0x105AA7A0
// FUNCTION: ENGINE 0x105AA7D0
// FUNCTION: ENGINE 0x105AA850
// FUNCTION: ENGINE 0x105AA9E0
// FUNCTION: ENGINE 0x105AAE90
// FUNCTION: ENGINE 0x105AAF90
// FUNCTION: ENGINE 0x105AC560
// FUNCTION: ENGINE 0x105AD130
// FUNCTION: ENGINE 0x105AD150
// FUNCTION: ENGINE 0x105AD160
// FUNCTION: ENGINE 0x105AD190
// FUNCTION: ENGINE 0x105AD1D0
// FUNCTION: ENGINE 0x105AD1F0
// FUNCTION: ENGINE 0x105AD210
// FUNCTION: ENGINE 0x105AD260
// FUNCTION: ENGINE 0x105AD3B0
// FUNCTION: ENGINE 0x105AD3D0
// FUNCTION: ENGINE 0x105AD3E0
// FUNCTION: ENGINE 0x105AD410
// FUNCTION: ENGINE 0x105AD440
// FUNCTION: ENGINE 0x105AD540
// FUNCTION: ENGINE 0x105AD580
// FUNCTION: ENGINE 0x105AD5A0
// FUNCTION: ENGINE 0x105AD5C0
// FUNCTION: ENGINE 0x105AD5F0
// FUNCTION: ENGINE 0x105AD780
// FUNCTION: ENGINE 0x105AD7A0
// FUNCTION: ENGINE 0x105AD7B0
// FUNCTION: ENGINE 0x105AD7E0
// FUNCTION: ENGINE 0x105AD810
// FUNCTION: ENGINE 0x105AD850
// FUNCTION: ENGINE 0x105AD860
// FUNCTION: ENGINE 0x105AD890
// FUNCTION: ENGINE 0x105AD8C0
// FUNCTION: ENGINE 0x105AD8F0
// FUNCTION: ENGINE 0x105ADA60
// FUNCTION: ENGINE 0x105ADAA0
// FUNCTION: ENGINE 0x105ADAC0
// FUNCTION: ENGINE 0x105ADAE0
// FUNCTION: ENGINE 0x105ADB10
