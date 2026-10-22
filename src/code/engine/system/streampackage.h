// engine::StreamPackage (RTTI name; base content::MetaLoadObject, 7 vftable slots): a reflected group of resources the
// world streams in and out as one, with prerequisite packages, a slot group and tags that select its stream clients.
// While it is requested it owns a StreamPackageInstance (name guessed) that runs the load state machine over the
// engine::streampackagestates (RTTI names; another unit, 0x108A6070 - 0x108A6D20) and keeps the inventory, the
// resources' loaders and the clients. Unit 0x107F9F50 - 0x107FBE3C (no assert path; directory and file name are
// guesses). The reflected member names are original; the other names are guesses.
#ifndef ENGINE_SYSTEM_STREAMPACKAGE_H
#define ENGINE_SYSTEM_STREAMPACKAGE_H

#include "code/container/staticarray.h"
#include "code/container/string.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/content/stringmetatype.h"
#include "code/core/name.h"
#include "code/engine/system/tagset.h"
#include "code/math/vector.h"

namespace fight
{
	class TrackRegistry;
}

namespace engine
{
	class StreamPackage;
	class StreamPackageInstance;

	typedef container::AllocatorCoreStatic<12, 16> StreamAllocator;

	// Told when a stream package's resources load / unload; true when done (RTTI: 4 slots)
	class StreamClient
	{
	public:
		virtual ~StreamClient();
		virtual bool Load(StreamPackageInstance* instance) = 0;
		virtual bool Unload(StreamPackageInstance* instance) = 0;
		virtual void Slot3();
	};

	// A slot a loaded package occupies in a heap (0x10 bytes; 0x1083E6A0 is the constructor, 0x1083E6A0 - 0x1083E7A0
	// the unit it lives in)
	class StreamSlot
	{
	public:
		// 0x1083E6A0: no heap yet, no package
		StreamSlot();
		// 0x1083E6C0: destroys the heap the slot owns (the arrays of slots carry the element count in front)
		~StreamSlot();
		bool Attach(StreamPackage* newPackage);
		void Detach();
		// 0x1083E6F0: the state of the package in the slot, 9 (loaded) when it is empty (names guessed)
		int GetState() const;
		// 0x1083E710: true when the slot's heap holds nothing
		bool IsHeapEmpty() const;
		// 0x1083E740 / 0x1083E750 / 0x1083E7D0
		StreamPackage* GetPackage() const;
		StreamPackage* GetPackage2() const;
		bool GetUnknownD() const;

		int heap;
		StreamPackage* package;
		// The slot's number in its group
		int index;
		bool unknownC;
		bool unknownD;
		bool unknownE;
		unsigned char unknownF;
	};

	class StreamSlotGroup;

	// Makes the heap of a slot of group (the slot's handle, the group, the heap's name); the engine's default is 0x1083EB80
	typedef core::IMemoryAllocator* (*SlotHeapFactory)(int handle, StreamSlotGroup* group, const char* name);
	typedef void (*SlotHeapDestroyer)(int handle);

	// A group of package slots (RTTI engine::StreamSlotGroup, vftable 0x10E6F838, 0x70 bytes, base
	// content::MetaLoadObject; the manager's 0x1082D550 builds them); its packages get at least its priority. The
	// layout follows the constructor 0x1083EAD0 and Create; the names are guesses.
	// What a slot group builds the heap of its slots from (the group copies the three words into 0x24 - 0x2C)
	struct SlotHeapConfig
	{
		unsigned int size;
		bool flag;
		unsigned int alignment;
	};

	class StreamSlotGroup : public content::MetaLoadObject
	{
	public:
		// 0x1083EAD0: the group of slotCount slots under name; the manager's 0x1082D550 makes one and registers it
		StreamSlotGroup(const core::Name<core::CaseSensitiveKey>& name, unsigned int slotCount,
			const SlotHeapConfig* config, bool shared, bool unknown67);
		// vftable slot 7 (0x1083EC50): makes the group's slots and, for a group of several that is not shared, the
		// heap they share; the first argument is never read
		virtual void Create(int unused, bool immediate);
		// vftable slot 4 (0x1083EE40): leaves the manager and gives the slots and their heap back; false while a
		// package still holds a slot
		virtual bool IsReady();
		// vftable slot 6 (0x1083EAC0)
		virtual void SetName(const content::ObjectName& newName);
		// 0x1083EB70: the vftable stores of the base classes only
		~StreamSlotGroup();

		// 0x1083F5E0 / 0x1083EA40: a group without slots (the second takes the name)
		StreamSlotGroup();
		explicit StreamSlotGroup(const core::Name<core::CaseSensitiveKey>& newName);
		// 0x1083F680: replaces the slots by count new ones (the heaps are made for them again)
		void Reconfigure(unsigned int count, const SlotHeapConfig* newConfig);
		// 0x1083E860: the slot heap's size, flag and alignment
		void SetSlotHeapConfig(const SlotHeapConfig* newConfig);
		// 0x1083E8B0: the same as GetSlotHeapConfig with the size of all the slots when they share a heap
		int* GetGroupHeapConfig(int* out) const;
		// 0x1083E7E0 / 0x1083F310: the class's name and the reflected members
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
		// 0x1083E8F0: the slot a new package goes into (a loaded one that is free, else one in state 8)
		StreamSlot* FindFreeSlot() const;
		// 0x1083E7C0
		void SetSlotCount(unsigned int count);
		// 0x1083E840: the function that destroys the heap of a slot: the group's own, else the manager's, else the
		// default (0x1083E820)
		SlotHeapDestroyer GetSlotHeapDestroyer() const;

		// 0x1083EA30: the slot of that number
		StreamSlot* GetSlot(unsigned int index);
		// 0x1083EC30: the function that makes the heap of a slot: the group's own, else the manager's, else the default
		SlotHeapFactory GetSlotHeapFactory() const;
		// 0x1083E880: the size of the heap of a slot and the two flags it is made with (out[0], out[1] and out[2])
		int* GetSlotHeapConfig(int* out) const;
		// 0x1083E950 / 0x1083E990 / 0x1083E9E0: questions about the slots' state (the first counts the slots that
		// are in use and in state 9, the others ask whether one of them is loading; names unknown)
		unsigned int Unknown1083E950() const;
		bool Unknown1083E990() const;
		bool Unknown1083E9E0() const;

		core::Name<core::CaseSensitiveKey> name;   // +0x08
		StreamSlot* slots;                         // +0x10
		// The heap the slots of a group of several share (-1: none)
		int heap;                                  // +0x14
		core::IMemoryLinearAllocator* allocator;   // +0x18
		bool unknown1C;
		unsigned char unknown1D[3];
		unsigned int slotCount;                    // +0x20
		// The size of the heap of a slot is built from the first three (bytes, kilobytes, megabytes), the other
		// platforms' sizes are reflected members that are not used
		unsigned int slotWin32Bytes;
		unsigned int slotWin32KiloBytes;
		unsigned int slotWin32MegaBytes;
		unsigned int slotXenonBytes;
		unsigned int slotXenonKiloBytes;
		unsigned int slotXenonMegaBytes;
		unsigned int slotPS3CPUBytes;
		unsigned int slotPS3CPUKiloBytes;
		unsigned int slotPS3CPUMegaBytes;
		unsigned int slotPS3GPUBytes;
		unsigned int slotPS3GPUKiloBytes;
		unsigned int slotPS3GPUMegaBytes;
		int unknown54;
		unsigned char unknown58[4];
		// A group's own function that makes the heaps of its slots (null: the manager's, else the default)
		SlotHeapFactory factory;                   // +0x5C
		// ... and the one that destroys them (+0x60)
		SlotHeapDestroyer destroyer;
		unsigned short priority;                   // +0x64
		// A shared group's slots all use the heap of the first
		bool shared;                               // +0x66
		bool unknown67;
		bool unknown68;
		unsigned char unknown69[7];
	};

	// 0x1082D630: a free handle for a slot's heap, -1 when there is none; 0x1082E3F0: registers the group in the
	// manager under its name's hash
	int AllocateSlotHandle();
	void RegisterSlotGroup(StreamSlotGroup* group);
	// 0x1082EA10 / 0x1082D670 (the stream manager's unit, names guessed): takes the group out of the manager;
	// puts a slot heap handle back
	void UnregisterSlotGroup(StreamSlotGroup* group);
	void FreeSlotHandle(int handle);

	// The stream manager (RTTI: engine::StreamManager, base StreamClient; the singleton is 0x1130D350). Only the
	// statics the packages call are declared (0x1082BEC0 - 0x1082E990)
	class StreamManager : public StreamClient
	{
	public:
		struct Settings
		{
			unsigned int maxPackages;
			unsigned int maxPending;
			int unknown8[7];
			unsigned int maxDependents;
		};

		static Settings* GetSettings();
		static bool IsBusy();
		static void SetCurrentPackage(StreamPackage* package);
		static int GetSlotGroupIndex(const content::ObjectName& name);
		// Adds the clients whose tags match to clients
		static void FindClients(container::ArrayDynamicStatic<StreamClient*, StreamAllocator>* clients,
			const TagSet* tags);
		static void RemoveActive(StreamPackage* package);
		static void Register(StreamPackage* package);
		static void AddActive(StreamPackage* package);
		static StreamSlotGroup* FindSlotGroup(const content::ObjectName& name);
		static void Unregister(StreamPackage* package);

		unsigned char unknown4[0x4c - 4];
		Settings settings;
		unsigned char unknown74[0x88 - 0x74];
		// The functions that make and destroy the heaps of slots (null: the default; 0x1083EC30 / 0x1083E840)
		SlotHeapFactory slotHeapFactory;
		SlotHeapDestroyer slotHeapDestroyer;
		unsigned char unknown90[0x11C - 0x90];
		// The priority loads are made at while a group's packages are changing (0xFFFF: none; 0x1082E100 sets it)
		unsigned int transitionPriority;
	};

	extern StreamManager* gStreamManager;

	// 0x1130D388: the slot group name loads without a group of their own are made with (name guess)
	extern content::ObjectName gNoSlotGroup;

	// 0x1082E010 (the stream manager's unit): the package of name, null if none
	StreamPackage* FindStreamPackage(const core::Name<core::CaseSensitiveKey>& name);

	inline StreamManager::Settings* StreamManager::GetSettings()
	{
		return &gStreamManager->settings;
	}

	// Told around a package's resources loading (0x11276130; another unit, 0x105A4BB0 / 0x105A4BE0; names guessed)
	class LoadListeners
	{
	public:
		// The first context of the list (the others follow through the contexts' own links)
		fight::TrackRegistry* first;
		// The critical section the watchers of the branches are changed under
		unsigned char lock[0x18];

		void Begin(int unknown);
		void End(int unknown);
		// 0x105A4F40: puts a fight context at the end of the list (the head at +0, the next link at +0x10 of a context)
		void AddContext(fight::TrackRegistry* context);
		// 0x105A4B00 / 0x105A4B50: the number of contexts / the context at index (null when out of range)
		int GetCount();
		fight::TrackRegistry* GetContext(int index);
		// 0x100915F0: the context known by a kind of node's name (null when there is none; name guess)
		fight::TrackRegistry* FindContextByName(const char* name);
		// 0x105A4F90: the context known by name (null when there is none)
		fight::TrackRegistry* FindContext(const core::Name<core::CaseSensitiveKey>& name);
	};

	extern LoadListeners* gLoadListeners;

	// The name of packages without a slot group ("Undefined_SlotGroup", 0x11283CC0)
	extern content::ObjectName gUndefinedSlotGroup;

	// A state of StreamPackageInstance's machine (RTTI: 3 slots)
	class StreamPackageState
	{
	public:
		virtual void Enter() = 0;
		// True when the state may be left for next
		virtual bool Exit(int next) = 0;
		// The state to go to, or StreamPackageInstance::STATE_NONE
		virtual int Update() = 0;

		const char* GetName() const
		{
			return name;
		}

		const char* name;
		StreamPackageInstance* instance;

	protected:
		// The states inline it (the engine keeps a copy at 0x108A6010 nothing calls)
		StreamPackageState(const char* newName, StreamPackageInstance* newInstance) : name(newName), instance(newInstance)
		{
		}
	};

	namespace streampackagestates
	{
		class Unloaded : public StreamPackageState
		{
		public:
			explicit Unloaded(StreamPackageInstance* instance);
			virtual void Enter();
			virtual bool Exit(int next);
			virtual int Update();
		};

		class WaitForPrerequisites : public StreamPackageState
		{
		public:
			explicit WaitForPrerequisites(StreamPackageInstance* instance);
			virtual void Enter();
			virtual bool Exit(int next);
			virtual int Update();
		};

		class CancelLoading : public StreamPackageState
		{
		public:
			explicit CancelLoading(StreamPackageInstance* instance);
			virtual void Enter();
			virtual bool Exit(int next);
			virtual int Update();

			bool unknownC;
		};

		class Loading : public StreamPackageState
		{
		public:
			explicit Loading(StreamPackageInstance* instance);
			virtual void Enter();
			virtual bool Exit(int next);
			virtual int Update();
			// 0x108A60A0: true when this is the state that is loading now
			bool IsActive() const;

			int total;  // +0xC
			int unknown10;
			int unknown14;
			int unknown18;
			bool unknown1C;
		};

		class ClientLoading : public StreamPackageState
		{
		public:
			explicit ClientLoading(StreamPackageInstance* instance);
			virtual void Enter();
			virtual bool Exit(int next);
			virtual int Update();

			unsigned char unknownC;
		};

		class Loaded : public StreamPackageState
		{
		public:
			explicit Loaded(StreamPackageInstance* instance);
			virtual void Enter();
			virtual bool Exit(int next);
			virtual int Update();
		};

		class WaitForUnloads : public StreamPackageState
		{
		public:
			explicit WaitForUnloads(StreamPackageInstance* instance);
			virtual void Enter();
			virtual bool Exit(int next);
			virtual int Update();
		};

		class ClientUnloading : public StreamPackageState
		{
		public:
			explicit ClientUnloading(StreamPackageInstance* instance);
			virtual void Enter();
			virtual bool Exit(int next);
			virtual int Update();

			bool unknownC;
		};

		class Evictable : public StreamPackageState
		{
		public:
			explicit Evictable(StreamPackageInstance* instance);
			virtual void Enter();
			virtual bool Exit(int next);
			virtual int Update();

			unsigned int deadline;  // +0xC
			bool unknown10;
		};
	}

	class StreamPackageInstance
	{
	public:
		enum
		{
			STATE_UNLOADED,
			STATE_WAIT_FOR_PREREQUISITES,
			STATE_CANCEL_LOADING,
			STATE_LOADING,
			STATE_CLIENT_LOADING,
			STATE_LOADED,
			STATE_WAIT_FOR_UNLOADS,
			STATE_CLIENT_UNLOADING,
			STATE_EVICTABLE,
			STATE_COUNT,
			STATE_NONE = STATE_COUNT
		};

		enum
		{
			REQUEST_LOAD,
			REQUEST_UNLOAD,
			REQUEST_NONE
		};

		typedef container::ArrayDynamicStatic<StreamClient*, StreamAllocator> ClientList;
		typedef container::ArrayDynamicStatic<StreamPackage*, StreamAllocator> PackageList;
		typedef container::ArrayDynamicStatic<content::LoadObject*, StreamAllocator> LoaderList;

		explicit StreamPackageInstance(StreamPackage* newPackage);
		~StreamPackageInstance();

		// Runs the machine: takes the pending request, then updates states until one stays
		void Update(int unused);
		content::LoadInventory* CreateInventory();
		void SetPriority(unsigned short newPriority);
		unsigned short GetPriority() const;
		int GetSlotGroupIndex() const;
		bool AttachSlot(StreamSlot* newSlot);
		void DetachSlot();
		const char* GetStateName(int index) const;
		void SetUnknown96(bool value);
		bool GetUnknown96() const;
		void SetLoadEnabled(bool value);
		bool IsLoadEnabled() const;
		bool IsLoaded() const;
		bool IsLoadingActive() const;
		void Load();
		void Unload();
		content::LoadObject* GetObject(int index) const;
		void SetObject(int index, content::LoadObject* object);
		void SetSlotGroup(const content::ObjectName& name);
		// Steps the clients' unloading / loading; true when every client is done
		bool UpdateClientUnloading();
		bool UpdateClientLoading();
		void RemoveClient(StreamClient* client);
		// Releases the resources' loaders
		void ReleaseLoaders();
		void ReleaseInventory();
		PackageList* GetDependents();
		bool IsEvicting() const;
		const content::ObjectName& GetSlotGroupName() const;
		StreamSlotGroup* GetSlotGroup() const;
		// Marks the package evictable (the argument is not used)
		void SetEvicting(bool unused);

		ClientList loadedClients;
		ClientList clients;
		PackageList dependents;
		content::LoadInventory* inventory;
		unsigned short priority;
		LoaderList loaders;
		container::ArrayFixedStatic<content::LoadObject*, StreamAllocator> objects;
		StreamPackage* package;
		content::ObjectName slotGroupName;
		StreamSlotGroup* group;
		StreamSlot* slot;
		StreamPackageState* states[STATE_COUNT];
		int state;
		int request;
		bool evicting;
		bool loadersDone;
		bool unknown96;
		bool loadEnabled;
		bool unknown98;
		int unknown9C;
	};

	class StreamPackage : public content::MetaLoadObject
	{
	public:
		typedef container::StringDynamic<StreamAllocator> String;
		typedef container::ArrayDynamicStatic<StreamPackage*, StreamAllocator> PackageList;
		typedef container::ArrayDynamicStatic<String*, StreamAllocator> ResourceList;

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		StreamPackage();
		explicit StreamPackage(const content::ObjectName& newName);
		virtual ~StreamPackage();
		// Registers the package with the stream manager
		virtual void Slot3(int unused);
		// Unregisters and unloads; true once the instance is gone
		virtual bool IsReady();
		virtual void SetName(const content::ObjectName& newName);

		ResourceList* GetResourceList() const;
		unsigned int GetInventoryInitialSize() const;
		void SetInventoryInitialSize(unsigned int value);
		const char* GetTags();
		void SetTags(const char* text);
		bool GetSync() const;
		void SetSync(bool value);
		void SetEvicting(bool value);
		content::LoadInventory* GetInventory() const;
		const char* GetPrerequisites();
		void SetPrerequisites(const char* text);
		const char* GetResources();
		void SetResources(const char* text);
		int GetState() const;
		bool IsLoading() const;
		bool IsLoaded() const;
		bool IsUnloading() const;
		bool IsUnloaded() const;
		// Updates the instance and deletes it once unloaded
		void Update();
		// Asks for the package, on behalf of requester (a package that needs it, or null)
		void Load(StreamPackage* requester, unsigned short newPriority, const content::ObjectName& newSlotGroup,
			bool counted);
		void Unload(StreamPackage* requester, bool counted);
		void Unload(StreamPackage* requester);
		void ResolvePrerequisites();
		// Drops every request
		void ReleaseRequests();

		content::ObjectName slotGroup;
		content::ObjectName name;
		String* prerequisiteText;
		PackageList* prerequisites;
		ResourceList* resources;
		unsigned int requestCount;
		unsigned int countedRequests;
		StreamPackageInstance* instance;
		TagSet tags;
		bool sync;
		unsigned int xenonMaxSize;
		// Where the package sits: the centre of the trigger's box when the manager collects it
		math::Vector unknown4C;
		float unknown58;
		unsigned int inventoryInitialSize;
	};
}

#endif
