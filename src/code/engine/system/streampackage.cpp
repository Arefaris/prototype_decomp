#include "code/engine/system/streampackage.h"
#include "code/core/heap.h"
#include "code/engine/system/enginememory.h"

namespace engine
{
	// The state to go to from each state on a load / unload request (STATE_NONE: stay)
	static const int sTransitions[2][StreamPackageInstance::STATE_COUNT] =
	{
		{ 1, 9, 1, 9, 9, 9, 9, 4, 0 },
		{ 9, 0, 9, 2, 7, 6, 9, 9, 9 }
	};

	// FUNCTION: ENGINE 0x107F9F70
	StreamPackage::ResourceList* StreamPackage::GetResourceList() const
	{
		return resources;
	}

	// FUNCTION: ENGINE 0x107F9F80
	unsigned int StreamPackage::GetInventoryInitialSize() const
	{
		return inventoryInitialSize;
	}

	// FUNCTION: ENGINE 0x107F9F90
	void StreamPackageInstance::SetEvicting(bool unused)
	{
		evicting = true;
	}

	// FUNCTION: ENGINE 0x107F9FA0
	// EQUIVALENT: the engine adds the state to request * 9 as a memory operand and loads the state again for the
	// comparison; ours keeps it in a register
	void StreamPackageInstance::Update(int unused)
	{
		for (;;)
		{
			if (request != REQUEST_NONE)
			{
				int next = sTransitions[request][state];
				if (next == STATE_NONE || next == state)
				{
					request = REQUEST_NONE;
				}
				else if (states[state]->Exit(next))
				{
					state = next;
					states[next]->Enter();
					request = REQUEST_NONE;
				}
			}
			int next = states[state]->Update();
			if (next == STATE_NONE)
			{
				return;
			}
			states[state]->Exit(next);
			state = next;
			states[next]->Enter();
		}
	}

	// FUNCTION: ENGINE 0x107FA050
	// EQUIVALENT: register choice in the AddRef call (the engine loads the vftable into eax, ours into edx)
	content::LoadInventory* StreamPackageInstance::CreateInventory()
	{
		{
			core::HeapScope scope(slot->heap);
			inventory = new content::LoadInventory(package->inventoryInitialSize);
		}
		inventory->AddRef();
		return inventory;
	}

	// FUNCTION: ENGINE 0x107FA0A0
	void StreamPackageInstance::SetPriority(unsigned short newPriority)
	{
		if (newPriority < priority)
		{
			priority = newPriority;
		}
	}

	// FUNCTION: ENGINE 0x107FA0C0
	unsigned short StreamPackageInstance::GetPriority() const
	{
		if (group != 0 && group->priority < priority)
		{
			return group->priority;
		}
		return priority;
	}

	// FUNCTION: ENGINE 0x107FA0E0
	int StreamPackageInstance::GetSlotGroupIndex() const
	{
		return StreamManager::GetSlotGroupIndex(package->slotGroup);
	}

	// FUNCTION: ENGINE 0x107FA0F0
	bool StreamPackageInstance::AttachSlot(StreamSlot* newSlot)
	{
		if (newSlot->Attach(package))
		{
			slot = newSlot;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107FA120
	void StreamPackageInstance::DetachSlot()
	{
		if (slot != 0)
		{
			slot->Detach();
			slot = 0;
		}
	}

	// FUNCTION: ENGINE 0x107FA140
	const char* StreamPackageInstance::GetStateName(int index) const
	{
		if (index == STATE_NONE)
		{
			return "";
		}
		return states[index]->GetName();
	}

	// FUNCTION: ENGINE 0x107FA160
	void StreamPackageInstance::SetUnknown96(bool value)
	{
		unknown96 = value;
	}

	// FUNCTION: ENGINE 0x107FA170
	bool StreamPackageInstance::GetUnknown96() const
	{
		return unknown96;
	}

	// FUNCTION: ENGINE 0x107FA180
	void StreamPackageInstance::SetLoadEnabled(bool value)
	{
		loadEnabled = value;
	}

	// FUNCTION: ENGINE 0x107FA190
	bool StreamPackageInstance::IsLoadEnabled() const
	{
		return loadEnabled;
	}

	// FUNCTION: ENGINE 0x107FA1A0
	bool StreamPackageInstance::IsLoaded() const
	{
		return state == STATE_LOADED;
	}

	// FUNCTION: ENGINE 0x107FA1B0
	bool StreamPackageInstance::IsLoadingActive() const
	{
		bool active = false;
		if (state == STATE_LOADING)
		{
			active = ((streampackagestates::Loading*)states[STATE_LOADING])->IsActive();
		}
		return active;
	}

	// FUNCTION: ENGINE 0x107FA300
	void StreamPackageInstance::Load()
	{
		request = REQUEST_LOAD;
		Update(0);
	}

	// FUNCTION: ENGINE 0x107FA320
	void StreamPackageInstance::Unload()
	{
		request = REQUEST_UNLOAD;
		Update(0);
	}

	// FUNCTION: ENGINE 0x107FA340
	content::LoadObject* StreamPackageInstance::GetObject(int index) const
	{
		return objects.begin[index];
	}

	// FUNCTION: ENGINE 0x107FA350
	void StreamPackageInstance::SetObject(int index, content::LoadObject* object)
	{
		objects.begin[index] = object;
	}

	// FUNCTION: ENGINE 0x107FA370
	void StreamPackageInstance::SetSlotGroup(const content::ObjectName& name)
	{
		if (name != slotGroupName)
		{
			StreamSlotGroup* newGroup = StreamManager::FindSlotGroup(name);
			if (newGroup != 0)
			{
				slotGroupName = name;
				group = newGroup;
			}
		}
	}

	// FUNCTION: ENGINE 0x107FA570
	bool StreamPackageInstance::UpdateClientUnloading()
	{
		StreamManager::IsBusy();
		StreamClient** it = loadedClients.begin;
		StreamClient** end = loadedClients.end;
		while (it != end)
		{
			StreamClient* client = *it;
			if (client->Unload(this))
			{
				loadedClients.EraseFast(it);
				end = loadedClients.end;
				clients.PushBack(client);
			}
			else
			{
				it++;
			}
		}
		if (loadedClients.IsEmpty() && inventory->IsReady())
		{
			loadersDone = false;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x107FA5F0
	void StreamPackageInstance::RemoveClient(StreamClient* client)
	{
		StreamClient** it = loadedClients.begin;
		StreamClient** end = loadedClients.end;
		while (it != end)
		{
			if (*it == client)
			{
				loadedClients.EraseFast(it);
				end = loadedClients.end;
			}
			else
			{
				it++;
			}
		}
		it = clients.begin;
		end = clients.end;
		while (it != end)
		{
			if (*it == client)
			{
				clients.EraseFast(it);
				end = clients.end;
			}
			else
			{
				it++;
			}
		}
	}

	// FUNCTION: ENGINE 0x107FA760
	void StreamPackageInstance::ReleaseLoaders()
	{
		int i = loaders.Size();
		while (i-- != 0)
		{
			loaders[i]->IsReady();
			loaders[i]->Release();
		}
		loaders.Reset();
	}

	// FUNCTION: ENGINE 0x107FA7A0
	bool StreamPackageInstance::UpdateClientLoading()
	{
		if (!loadEnabled)
		{
			return false;
		}
		if (!loadersDone)
		{
			StreamManager::SetCurrentPackage(package);
			gLoadListeners->Begin(0);
			unsigned int count = loaders.Size();
			if (count != 0)
			{
				for (unsigned int i = 0; i < count; i++)
				{
					loaders[i]->Slot3((int)inventory);
				}
				ReleaseLoaders();
			}
			else
			{
				content::LoadInventory::Iterator it(inventory, true);
				it.index = (unsigned int)-1;
				for (core::IRefCount* object = it.NextObject(); object != 0; object = it.NextObject())
				{
					content::LoadObject* loadObject = dynamic_cast<content::LoadObject*>(object);
					if (loadObject != 0)
					{
						loadObject->Slot3((int)inventory);
					}
				}
			}
			StreamManager::SetCurrentPackage(0);
			loadersDone = true;
			gLoadListeners->End(0);
		}
		StreamClient** it = clients.begin;
		StreamClient** end = clients.end;
		while (it != end)
		{
			StreamClient* client = *it;
			if (client->Load(this))
			{
				clients.EraseFast(it);
				end = clients.end;
				loadedClients.PushBack(client);
			}
			else
			{
				it++;
			}
		}
		return clients.IsEmpty();
	}

	// FUNCTION: ENGINE 0x107FA960
	StreamPackageInstance::StreamPackageInstance(StreamPackage* newPackage)
		: loadedClients(StreamManager::GetSettings()->maxPackages + StreamManager::GetSettings()->maxPending,
			StreamAllocator()),
		clients(StreamManager::GetSettings()->maxPackages + StreamManager::GetSettings()->maxPending,
			StreamAllocator()),
		dependents(StreamManager::GetSettings()->maxDependents, StreamAllocator()),
		inventory(0),
		priority(0xFFFF),
		loaders(newPackage->resources->Size(), StreamAllocator()),
		objects(newPackage->resources->Size(), StreamAllocator()),
		package(newPackage),
		slotGroupName(gUndefinedSlotGroup)
	{
		group = StreamManager::FindSlotGroup(newPackage->slotGroup);
		slot = 0;
		state = STATE_UNLOADED;
		request = REQUEST_NONE;
		evicting = false;
		loadersDone = false;
		unknown96 = false;
		loadEnabled = true;
		unknown98 = false;
		int count = newPackage->resources->Size();
		for (int i = 0; i < count; i++)
		{
			objects.begin[i] = 0;
		}
		StreamManager::FindClients(&clients, &package->tags);
		states[STATE_UNLOADED] = new (0xc) streampackagestates::Unloaded(this);
		states[STATE_WAIT_FOR_PREREQUISITES] = new (0xc) streampackagestates::WaitForPrerequisites(this);
		states[STATE_CANCEL_LOADING] = new (0xc) streampackagestates::CancelLoading(this);
		states[STATE_LOADING] = new (0xc) streampackagestates::Loading(this);
		states[STATE_CLIENT_LOADING] = new (0xc) streampackagestates::ClientLoading(this);
		states[STATE_LOADED] = new (0xc) streampackagestates::Loaded(this);
		states[STATE_WAIT_FOR_UNLOADS] = new (0xc) streampackagestates::WaitForUnloads(this);
		states[STATE_CLIENT_UNLOADING] = new (0xc) streampackagestates::ClientUnloading(this);
		states[STATE_EVICTABLE] = new (0xc) streampackagestates::Evictable(this);
	}

	// FUNCTION: ENGINE 0x107FABC0
	StreamPackageInstance::~StreamPackageInstance()
	{
		for (int i = 0; i < STATE_COUNT; i++)
		{
			delete states[i];
		}
	}

	// FUNCTION: ENGINE 0x107FAC50
	void StreamPackageInstance::ReleaseInventory()
	{
		ReleaseLoaders();
		if (inventory != 0)
		{
			inventory->Clear();
			inventory->Release();
			inventory = 0;
		}
	}

	// FUNCTION: ENGINE 0x107FAC80
	const char* StreamPackage::GetTags()
	{
		return tags.ToString();
	}

	// FUNCTION: ENGINE 0x107FAC90
	bool StreamPackage::GetSync() const
	{
		return sync;
	}

	// FUNCTION: ENGINE 0x107FAD40
	StreamPackageInstance::PackageList* StreamPackageInstance::GetDependents()
	{
		return &dependents;
	}

	// FUNCTION: ENGINE 0x107FAD50
	bool StreamPackageInstance::IsEvicting() const
	{
		return evicting;
	}

	// FUNCTION: ENGINE 0x107FAD60
	const content::ObjectName& StreamPackageInstance::GetSlotGroupName() const
	{
		return slotGroupName;
	}

	// FUNCTION: ENGINE 0x107FAD70
	StreamSlotGroup* StreamPackageInstance::GetSlotGroup() const
	{
		return group;
	}

	// FUNCTION: ENGINE 0x107FAD80
	content::ClassInfo* StreamPackage::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::StreamPackage";
		sInfo.code = "pnr";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x107FADC0
	void StreamPackage::Slot3(int unused)
	{
		StreamManager::Register(this);
	}

	// FUNCTION: ENGINE 0x107FADD0
	void StreamPackage::SetEvicting(bool value)
	{
		instance->SetEvicting(value);
	}

	// FUNCTION: ENGINE 0x107FADE0
	content::LoadInventory* StreamPackage::GetInventory() const
	{
		if (instance != 0)
		{
			return instance->inventory;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x107FADF0
	const char* StreamPackage::GetPrerequisites()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x107FAE00
	int StreamPackage::GetState() const
	{
		if (instance != 0)
		{
			return instance->state;
		}
		return StreamPackageInstance::STATE_UNLOADED;
	}

	// FUNCTION: ENGINE 0x107FB020
	bool StreamPackage::IsLoading() const
	{
		int current = GetState();
		return current == StreamPackageInstance::STATE_WAIT_FOR_PREREQUISITES ||
			current == StreamPackageInstance::STATE_LOADING || current == StreamPackageInstance::STATE_CLIENT_LOADING;
	}

	// FUNCTION: ENGINE 0x107FB040
	bool StreamPackage::IsLoaded() const
	{
		return GetState() == StreamPackageInstance::STATE_LOADED;
	}

	// FUNCTION: ENGINE 0x107FB050
	bool StreamPackage::IsUnloading() const
	{
		int current = GetState();
		return current == StreamPackageInstance::STATE_CANCEL_LOADING ||
			current == StreamPackageInstance::STATE_WAIT_FOR_UNLOADS ||
			current == StreamPackageInstance::STATE_CLIENT_UNLOADING || current == StreamPackageInstance::STATE_EVICTABLE;
	}

	// FUNCTION: ENGINE 0x107FB080
	bool StreamPackage::IsUnloaded() const
	{
		return GetState() == StreamPackageInstance::STATE_UNLOADED;
	}

	// FUNCTION: ENGINE 0x107FB090
	const char* StreamPackage::GetResources()
	{
		static container::StringC<256> sText;
		sText.Clear();
		if (resources != 0)
		{
			for (String** it = resources->begin; it != resources->end; it++)
			{
				sText.Append(**it);
			}
		}
		return sText.buffer;
	}

	// FUNCTION: ENGINE 0x107FB110
	void StreamPackage::Update()
	{
		instance->Update(0);
		if (instance->state == StreamPackageInstance::STATE_UNLOADED)
		{
			StreamManager::RemoveActive(this);
			delete instance;
			instance = 0;
		}
	}

	// FUNCTION: ENGINE 0x107FB450
	void StreamPackage::Load(StreamPackage* requester, unsigned short newPriority,
		const content::ObjectName& newSlotGroup, bool counted)
	{
		if (instance == 0)
		{
			instance = new (0xc) StreamPackageInstance(this);
			instance->SetSlotGroup(newSlotGroup);
			StreamManager::AddActive(this);
		}
		StreamPackageInstance* current = instance;
		if (current->slotGroupName != newSlotGroup || current->group == 0)
		{
			return;
		}
		requestCount++;
		if (counted)
		{
			countedRequests++;
		}
		current->SetPriority(newPriority);
		instance->Load();
		if (requester != 0)
		{
			instance->dependents.PushBack(requester);
		}
	}

	// FUNCTION: ENGINE 0x107FB500
	void StreamPackage::Unload(StreamPackage* requester, bool counted)
	{
		if (requestCount == 0)
		{
			return;
		}
		if (requester != 0)
		{
			StreamPackageInstance* current = instance;
			current->dependents.EraseFast(current->dependents.Find(requester));
		}
		if (--requestCount == 0)
		{
			instance->Unload();
		}
		if (counted && countedRequests != 0)
		{
			countedRequests--;
		}
	}

	// FUNCTION: ENGINE 0x107FB570
	void StreamPackage::Unload(StreamPackage* requester)
	{
		Unload(requester, false);
	}

	// FUNCTION: ENGINE 0x107FB580
	void StreamPackage::SetPrerequisites(const char* text)
	{
		if (text != 0 && *text != 0)
		{
			prerequisiteText = new (0xc) String(text, StreamAllocator());
		}
	}

	// FUNCTION: ENGINE 0x107FB630
	static void AddPrerequisite(const char* name, void* context)
	{
		content::ObjectName prerequisiteName(name, 1);
		StreamPackage* prerequisite = FindStreamPackage(prerequisiteName);
		if (prerequisite != 0)
		{
			((StreamPackage*)context)->prerequisites->PushBack(prerequisite);
		}
	}

	// FUNCTION: ENGINE 0x107FB680
	static void AddResource(const char* name, void* context)
	{
		StreamPackage::String* resource = new (0xc) StreamPackage::String(name);
		((StreamPackage*)context)->resources->PushBack(resource);
	}

	// FUNCTION: ENGINE 0x107FB970
	void StreamPackage::ResolvePrerequisites()
	{
		if (prerequisiteText != 0 && prerequisites == 0)
		{
			prerequisites = new (0xc) PackageList(prerequisiteText->Count(';') + 1, StreamAllocator());
			prerequisiteText->ForEachToken(';', AddPrerequisite, this);
		}
	}

	// FUNCTION: ENGINE 0x107FB9D0
	void StreamPackage::ReleaseRequests()
	{
		if (requestCount > 1)
		{
			requestCount = 1;
			Unload(0);
			instance->SetEvicting(true);
		}
		else if (requestCount == 1)
		{
			Unload(0);
			instance->SetEvicting(false);
		}
		else if (instance != 0 && !instance->evicting)
		{
			instance->SetEvicting(false);
		}
	}

	// FUNCTION: ENGINE 0x107FBA30
	void StreamPackage::SetResources(const char* text)
	{
		if (text != 0 && *text != 0)
		{
			container::StringLiteral literal(text);
			unsigned int count = literal.Count(';') + 1;
			resources = new (0xc) ResourceList(count, StreamAllocator());
			literal.ForEachToken(';', AddResource, this);
		}
	}

	// FUNCTION: ENGINE 0x107FBAC0
	content::MemberList* StreamPackage::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<StreamPackage>(true, true, "pnr"),
				content::MemberOffset(&((StreamPackage*)0)->slotGroup, (int)&((StreamPackage*)0)->slotGroup),
				"slotGroup" },
			{ content::GetStringMemberMetaType<StreamPackage, 0>(&StreamPackage::GetPrerequisites,
				&StreamPackage::SetPrerequisites, "pnr"), 0, "prerequisites" },
			{ content::GetStringMemberMetaType<StreamPackage, 1>(&StreamPackage::GetResources,
				&StreamPackage::SetResources, "pnr"), 0, "resources" },
			{ content::GetStringMemberMetaType<StreamPackage, 2>(&StreamPackage::GetTags, &StreamPackage::SetTags,
				"pnr"), 0, "tags" },
			{ content::GetMemberMetaType<StreamPackage, bool>(&StreamPackage::GetSync, &StreamPackage::SetSync, "pnr"),
				0, "sync" },
			{ content::GetMemberPrimitiveMetaType<StreamPackage, unsigned int, 0>("pn"),
				content::MemberOffset(&((StreamPackage*)0)->xenonMaxSize, (int)&((StreamPackage*)0)->xenonMaxSize),
				"xenonMaxSize" },
			{ content::GetMemberMetaType<StreamPackage, unsigned int>(&StreamPackage::GetInventoryInitialSize,
				&StreamPackage::SetInventoryInitialSize, "pn"), 0, "inventoryInitialSize" }
		};
		sList.members = sMembers;
		sList.count = 7;
		return &sList;
	}

	// FUNCTION: ENGINE 0x107FBC70
	bool StreamPackage::IsReady()
	{
		StreamManager::Unregister(this);
		ReleaseRequests();
		return instance == 0;
	}

	// FUNCTION: ENGINE 0x107FBC90
	// EQUIVALENT: scheduling (the engine stores the reference count before taking the address of slotGroup)
	StreamPackage::StreamPackage(const content::ObjectName& newName)
		: name(newName), prerequisiteText(0), prerequisites(0), resources(0), requestCount(0), countedRequests(0),
		instance(0)
	{
		sync = true;
		xenonMaxSize = 0;
		unknown58 = 0.0f;
		inventoryInitialSize = 0x400;
	}

	// FUNCTION: ENGINE 0x107FBD00
	void StreamPackage::SetName(const content::ObjectName& newName)
	{
		name = newName;
	}

	// FUNCTION: ENGINE 0x107FBD10
	StreamPackage::~StreamPackage()
	{
		delete prerequisiteText;
		delete prerequisites;
		if (resources != 0)
		{
			for (unsigned int i = resources->Size(); i != 0; )
			{
				i--;
				delete (*resources)[i];
			}
			delete resources;
		}
	}

	// FUNCTION: ENGINE 0x107FBDC0
	// EQUIVALENT: scheduling, as the other constructor
	StreamPackage::StreamPackage()
		: prerequisiteText(0), prerequisites(0), resources(0), requestCount(0), countedRequests(0), instance(0)
	{
		sync = true;
		xenonMaxSize = 1000000000;
		unknown58 = 0.0f;
		inventoryInitialSize = 0x400;
	}

	void StreamPackage::SetInventoryInitialSize(unsigned int value)
	{
		inventoryInitialSize = value;
	}

	void StreamPackage::SetTags(const char* text)
	{
		tags.FromString(text);
	}

	void StreamPackage::SetSync(bool value)
	{
		sync = value;
	}
}

// Kept copies: the lists' and strings' members, the string / primitive meta type getters and setters, the member
// meta type getters, the state name and the stream manager settings accessors, the scalar deleting destructors
// FUNCTION: ENGINE 0x107F9F50
// FUNCTION: ENGINE 0x107F9F60
// FUNCTION: ENGINE 0x107FA1F0
// FUNCTION: ENGINE 0x107FA200
// FUNCTION: ENGINE 0x107FA210
// FUNCTION: ENGINE 0x107FA220
// FUNCTION: ENGINE 0x107FA230
// FUNCTION: ENGINE 0x107FA3B0
// FUNCTION: ENGINE 0x107FA3E0
// FUNCTION: ENGINE 0x107FA400
// FUNCTION: ENGINE 0x107FA460
// FUNCTION: ENGINE 0x107FA4B0
// FUNCTION: ENGINE 0x107FA650
// FUNCTION: ENGINE 0x107FA670
// FUNCTION: ENGINE 0x107FA690
// FUNCTION: ENGINE 0x107FA6B0
// FUNCTION: ENGINE 0x107FA6E0
// FUNCTION: ENGINE 0x107FA730
// FUNCTION: ENGINE 0x107FA750
// FUNCTION: ENGINE 0x107FA920
// FUNCTION: ENGINE 0x107FA940
// FUNCTION: ENGINE 0x107FACA0
// FUNCTION: ENGINE 0x107FACD0
// FUNCTION: ENGINE 0x107FAD00
// FUNCTION: ENGINE 0x107FAE20
// FUNCTION: ENGINE 0x107FAE90
// FUNCTION: ENGINE 0x107FAF00
// FUNCTION: ENGINE 0x107FAF60
// FUNCTION: ENGINE 0x107FAF80
// FUNCTION: ENGINE 0x107FAFB0
// FUNCTION: ENGINE 0x107FAFF0
// FUNCTION: ENGINE 0x107FB000
// FUNCTION: ENGINE 0x107FB160
// FUNCTION: ENGINE 0x107FB190
// FUNCTION: ENGINE 0x107FB1B0
// FUNCTION: ENGINE 0x107FB1D0
// FUNCTION: ENGINE 0x107FB220
// FUNCTION: ENGINE 0x107FB230
// FUNCTION: ENGINE 0x107FB240
// FUNCTION: ENGINE 0x107FB250
// FUNCTION: ENGINE 0x107FB280
// FUNCTION: ENGINE 0x107FB2A0
// FUNCTION: ENGINE 0x107FB2D0
// FUNCTION: ENGINE 0x107FB310
// FUNCTION: ENGINE 0x107FB360
// FUNCTION: ENGINE 0x107FB380
// FUNCTION: ENGINE 0x107FB390
// FUNCTION: ENGINE 0x107FB3B0
// FUNCTION: ENGINE 0x107FB3D0
// FUNCTION: ENGINE 0x107FB3E0
// FUNCTION: ENGINE 0x107FB400
// FUNCTION: ENGINE 0x107FB420
// FUNCTION: ENGINE 0x107FB430
// FUNCTION: ENGINE 0x107FB710
// FUNCTION: ENGINE 0x107FB780
// FUNCTION: ENGINE 0x107FB7F0
// FUNCTION: ENGINE 0x107FB860
// FUNCTION: ENGINE 0x107FB8D0
// FUNCTION: ENGINE 0x107FB940
// FUNCTION: ENGINE 0x107FBAA0
// FUNCTION: ENGINE 0x107FBC40
// FUNCTION: ENGINE 0x107FBE20
