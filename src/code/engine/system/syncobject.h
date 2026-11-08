// engine::SyncObject, SyncObjectFactory and their Default classes (RTTI names, namespace engine): the input state the
// machines of an online game (or a replay) agree on. A factory keeps a table of sync objects (by the object index of
// a message) and hands the one a message names; a message names the factory, a value and the object's index. The
// objects count presses and releases of the value they follow. Unit 0x10833330 - 0x10833BC0 (no assert path; the file
// name is a guess); the member names are guesses.
#ifndef ENGINE_SYSTEM_SYNCOBJECT_H
#define ENGINE_SYSTEM_SYNCOBJECT_H

namespace engine
{
	class NetConnection;
	class NetSession;

	// What the machines exchange about one object (8 bytes)
	struct SyncMessage
	{
		unsigned char factory;
		unsigned char value;
		int index;
	};

	class SyncObject
	{
	public:
		// 0x108339B0
		SyncObject();
		// 0x10833890 (the deleting destructor is 0x108339D0)
		virtual ~SyncObject();
		virtual void Press(unsigned char value) = 0;
		virtual void Release(unsigned char value) = 0;

		// 0x108338A0 / 0x108338D0: a press or release a message reports
		void OnPress(const SyncMessage* message);
		void OnRelease(const SyncMessage* message);
		// 0x108338F0
		void Reset();
		// 0x108339F0: resets when the value is the completed one
		void ResetIf(unsigned char value);

		unsigned int machines;    // +4: the machines that reported the value
		unsigned char sent;       // +8: the value this machine reported
		unsigned char pressed;    // +9: the value the machines agree on
		unsigned char completed;  // +0xA: the value every machine reported
		unsigned char state;      // +0xB: 1 once this machine released the value
	};

	class SyncObjectFactory
	{
	public:
		// 0x10833820 (out of line only in the engine's copy; the derived constructor inlines it)
		SyncObjectFactory(unsigned char newId) : id(newId)
		{
		}
		virtual ~SyncObjectFactory()
		{
		}
		// The object a message is about
		virtual SyncObject* GetObject(const SyncMessage* message) = 0;
		virtual void Update() = 0;

		unsigned char id;  // +4
	};

	class SyncObjectFactoryDefault;

	class SyncObjectDefault : public SyncObject
	{
	public:
		// The default constructor 0x10833AF0 is the one the factory's vector constructor calls
		SyncObjectDefault();
		virtual void Press(unsigned char value);
		virtual void Release(unsigned char value);

		// 0x10833870
		void SetFactory(SyncObjectFactoryDefault* newFactory);
		// 0x10833990 / 0x108339A0
		int GetFactoryId() const;
		int GetIndex() const;

		SyncObjectFactoryDefault* factory;  // +0xC
	};

	class SyncObjectFactoryDefault : public SyncObjectFactory
	{
	public:
		// 0x10833B10: count * perOwner objects
		SyncObjectFactoryDefault(unsigned char newId, int newCount, int newPerOwner);
		virtual ~SyncObjectFactoryDefault();
		virtual SyncObject* GetObject(const SyncMessage* message);
		virtual void Update();

		// 0x10833880
		int IndexOf(const SyncObjectDefault* object) const;

		int count;                   // +8
		int perOwner;                // +0xC
		SyncObjectDefault* objects;  // +0x10
	};

	// What the sync owns on the net library's side (names guessed): the machines that take part and the session
	struct SyncOwner
	{
		unsigned char unknown0[0x20];
		unsigned int machines;  // +0x20
		unsigned int unknown24;
		NetSession* session;  // +0x28
	};

	// The factories by id (0x1130DC28, ten of them) and the global state of the sync (0x1130DC50 - 0x1130DC5C)
	extern SyncObjectFactory* gSyncFactories[10];
	extern SyncOwner* gSyncOwner;
	extern NetConnection* gSyncConnection;
	extern bool gSyncEnabled;
	extern bool gSyncFactoriesReady;
	extern int gRecordedCount;
	// The machines every sync object waits for, until a session says otherwise (0x111DBE28)
	extern unsigned int gSyncAllMachines;

	// 0x10833330: clears the table of factories
	void InitSyncFactories();
	// 0x10833380 / 0x108333D0: opens the connection of the sync on the owner's session and closes it
	void StartSync(SyncOwner* owner, int unknown, int capacity);
	void StopSync();
	// 0x10833400 / 0x10833430: puts the factory in its slot of the table (by its id) and takes it out
	void RegisterSyncFactory(SyncObjectFactory* factory);
	void UnregisterSyncFactory(SyncObjectFactory* factory);
	// 0x10833450: a message of the machines in the mask (type 0: pressed, 1: released); answers the object it is about
	SyncObject* ApplySyncMessage(const unsigned int* machines, int type, const SyncMessage* message);
	// 0x10833570 / 0x10833580
	void SetSyncEnabled(bool enabled);
	bool GetSyncEnabled();
	// 0x108336A0: true once every object the recorded presses made is released
	bool RecordedInputsReady();
	// 0x10833790 / 0x108336F0: reports a message to the other machines (or applies it here) and takes what came in
	void SendSyncMessage(int type, const SyncMessage* message);
	void UpdateSync();
}

#endif
