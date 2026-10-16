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

	// A group of package slots (another unit; 0x70 bytes and polymorphic, layout in the worklist); its packages get
	// at least its priority
	struct StreamSlotGroup
	{
		int unknown0[0x64 / 4];
		unsigned short priority;
	};

	// A slot a loaded package occupies in a heap (another unit, 0x1083E6A0 / 0x1083E760 / 0x1083E7A0; 0x10 bytes,
	// layout in the worklist)
	class StreamSlot
	{
	public:
		bool Attach(StreamPackage* package);
		void Detach();

		int heap;
	};

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
	};

	extern StreamManager* gStreamManager;

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
		void Begin(int unknown);
		void End(int unknown);
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

			int unknownC;
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

			int unknownC[5];
		};

		class ClientLoading : public StreamPackageState
		{
		public:
			explicit ClientLoading(StreamPackageInstance* instance);
			virtual void Enter();
			virtual bool Exit(int next);
			virtual int Update();

			int unknownC;
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

			int unknownC;
		};

		class Evictable : public StreamPackageState
		{
		public:
			explicit Evictable(StreamPackageInstance* instance);
			virtual void Enter();
			virtual bool Exit(int next);
			virtual int Update();

			int unknownC[2];
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
