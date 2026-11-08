#include "code/engine/gamelink.h"
#include "code/engine/online/replay.h"
#include "code/engine/system/syncobject.h"
#include <new>

namespace engine
{
	// One press the recording keeps (12 bytes, 0x1130D778)
	struct RecordedSync
	{
		SyncMessage message;
		int type;
	};

	// GLOBAL: ENGINE 0x1130DC28
	SyncObjectFactory* gSyncFactories[10];
	// GLOBAL: ENGINE 0x1130DC58
	SyncOwner* gSyncOwner;
	// GLOBAL: ENGINE 0x1130DC5C
	NetConnection* gSyncConnection;
	// GLOBAL: ENGINE 0x1130DC55
	bool gSyncEnabled;
	// GLOBAL: ENGINE 0x1130DC54
	bool gSyncFactoriesReady;
	// GLOBAL: ENGINE 0x1130DC50
	int gRecordedCount;
	// GLOBAL: ENGINE 0x111DBE28
	unsigned int gSyncAllMachines = 0xFFFFFFFF;
	// GLOBAL: ENGINE 0x1130D458
	unsigned int gPendingTimes[100];
	// GLOBAL: ENGINE 0x1130D5E8
	SyncObject* gPendingObjects[100];
	// GLOBAL: ENGINE 0x1130D778
	RecordedSync gRecordedSyncs[100];

	// FUNCTION: ENGINE 0x108339B0
	SyncObject::SyncObject() : machines(0), sent(0), pressed(0), completed(0), state(0)
	{
	}

	// FUNCTION: ENGINE 0x10833890
	SyncObject::~SyncObject()
	{
	}

	// FUNCTION: ENGINE 0x108338A0
	void SyncObject::OnPress(const SyncMessage* message)
	{
		if (message->value != sent && state != 1)
		{
			sent = message->value;
			SendSyncMessage(0, message);
		}
	}

	// FUNCTION: ENGINE 0x108338D0
	void SyncObject::OnRelease(const SyncMessage* message)
	{
		if (message->value == sent)
		{
			state = 1;
			SendSyncMessage(1, message);
		}
	}

	// FUNCTION: ENGINE 0x108338F0
	void SyncObject::Reset()
	{
		sent = 0;
		pressed = 0;
		completed = 0;
		machines = 0;
		state = 0;
	}

	// FUNCTION: ENGINE 0x108339F0
	void SyncObject::ResetIf(unsigned char newValue)
	{
		if (newValue == completed)
		{
			Reset();
		}
	}

	// FUNCTION: ENGINE 0x10833AF0
	SyncObjectDefault::SyncObjectDefault() : factory(0)
	{
	}

	// FUNCTION: ENGINE 0x10833A10
	void SyncObjectDefault::Press(unsigned char newValue)
	{
		SyncMessage message;
		message.factory = factory->id;
		message.value = newValue;
		message.index = this - factory->objects;
		OnPress(&message);
	}

	// FUNCTION: ENGINE 0x10833A40
	void SyncObjectDefault::Release(unsigned char newValue)
	{
		SyncMessage message;
		message.factory = factory->id;
		message.value = newValue;
		message.index = this - factory->objects;
		OnRelease(&message);
	}

	// FUNCTION: ENGINE 0x10833870
	void SyncObjectDefault::SetFactory(SyncObjectFactoryDefault* newFactory)
	{
		factory = newFactory;
	}

	// FUNCTION: ENGINE 0x10833990
	int SyncObjectDefault::GetFactoryId() const
	{
		return factory->id;
	}

	// FUNCTION: ENGINE 0x108339A0
	int SyncObjectDefault::GetIndex() const
	{
		return this - factory->objects;
	}

	// FUNCTION: ENGINE 0x10833B10
	SyncObjectFactoryDefault::SyncObjectFactoryDefault(unsigned char newId, int newCount, int newPerOwner)
		: SyncObjectFactory(newId)
	{
		count = newCount;
		perOwner = newPerOwner;
		int total = newCount * newPerOwner;
		objects = new SyncObjectDefault[total];
		for (int i = 0; i < total; i++)
		{
			objects[i].factory = this;
		}
	}

	// FUNCTION: ENGINE 0x10833910
	SyncObjectFactoryDefault::~SyncObjectFactoryDefault()
	{
		delete[] objects;
	}

	// FUNCTION: ENGINE 0x10833950
	SyncObject* SyncObjectFactoryDefault::GetObject(const SyncMessage* message)
	{
		return objects + message->index;
	}

	// FUNCTION: ENGINE 0x10833960
	void SyncObjectFactoryDefault::Update()
	{
	}

	// FUNCTION: ENGINE 0x10833880
	int SyncObjectFactoryDefault::IndexOf(const SyncObjectDefault* object) const
	{
		return object - objects;
	}

	// FUNCTION: ENGINE 0x10833330
	void InitSyncFactories()
	{
		if (!gSyncFactoriesReady)
		{
			for (int i = 0; i < 10; i++)
			{
				gSyncFactories[i] = 0;
			}
			gSyncFactoriesReady = true;
		}
	}

	// FUNCTION: ENGINE 0x10833380
	void StartSync(SyncOwner* owner, int unknown, int capacity)
	{
		if (!gSyncFactoriesReady)
		{
			InitSyncFactories();
		}
		gSyncOwner = owner;
		gSyncEnabled = true;
		NetSession* session = owner->session;
		gSyncConnection = session->Open(4, unknown, capacity);
		for (int i = 0; i < 100; i++)
		{
			gPendingTimes[i] = 0;
		}
	}

	// FUNCTION: ENGINE 0x108333D0
	void StopSync()
	{
		gSyncOwner->session->Close(gSyncConnection);
		gSyncConnection = 0;
		gSyncEnabled = false;
		gSyncOwner = 0;
	}

	// FUNCTION: ENGINE 0x10833400
	void RegisterSyncFactory(SyncObjectFactory* factory)
	{
		if (!gSyncFactoriesReady)
		{
			InitSyncFactories();
		}
		gSyncFactories[factory->id] = factory;
	}

	// FUNCTION: ENGINE 0x10833430
	void UnregisterSyncFactory(SyncObjectFactory* factory)
	{
		gSyncFactories[factory->id] = 0;
	}

	// FUNCTION: ENGINE 0x10833450
	// NONMATCHING: the engine reloads the mask after clearing the bits (cmp mem, 0) and builds the record offset as
	// x3 then two adds; ours reuses the flags and scales with a lea (62 % by bytes, the code is the same)
#ifdef NONMATCHING
	SyncObject* ApplySyncMessage(const unsigned int* machines, int type, const SyncMessage* message)
	{
		SyncObject* object = gSyncFactories[message->factory]->GetObject(message);
		Replay* replay = gReplay;
		unsigned int required = gSyncAllMachines;
		if (replay != 0 && replay->GetPlaybackFlagA4())
		{
			required = 3;
		}
		else if (gSyncEnabled && gSyncOwner != 0)
		{
			required = gSyncOwner->machines;
		}
		switch (type)
		{
		case 0:
			if (message->value == object->pressed || object->pressed == 0)
			{
				object->machines |= *machines;
				unsigned char value = message->value;
				object->pressed = value;
				if ((object->machines & required) == required)
				{
					object->completed = value;
					if (replay != 0 && replay->HasRecording())
					{
						RecordedSync* recorded = &gRecordedSyncs[gRecordedCount];
						recorded->type = 0;
						recorded->message = *message;
						gRecordedCount++;
					}
				}
			}
			break;
		case 1:
			if (message->value == object->pressed)
			{
				if (object->state == 1)
				{
					object->state = ((object->machines & required) == required) + 2;
					object->sent = 0;
				}
				object->machines &= ~*machines;
				if (object->machines == 0)
				{
					object->pressed = 0;
				}
			}
			break;
		}
		return object;
	}
#endif

	// FUNCTION: ENGINE 0x10833570
	void SetSyncEnabled(bool enabled)
	{
		gSyncEnabled = enabled;
	}

	// FUNCTION: ENGINE 0x10833580
	bool GetSyncEnabled()
	{
		return gSyncEnabled;
	}

	// FUNCTION: ENGINE 0x108336A0
	bool RecordedInputsReady()
	{
		int count = gRecordedCount;
		for (int i = 0; i < count; i++)
		{
			SyncObject* object = gPendingObjects[i];
			if (object != 0)
			{
				if (object->sent != object->completed)
				{
					return false;
				}
				gPendingObjects[i] = 0;
				gPendingTimes[i] = 0;
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10833790
	void SendSyncMessage(int type, const SyncMessage* message)
	{
		if (gSyncEnabled && gSyncConnection != 0)
		{
			int target = GetNetSystem()->unknown20;
			gSyncConnection->Send(target, type, (const char*)message, 8, 1);
		}
		else
		{
			unsigned int machines = gSyncAllMachines;
			if (gReplay != 0 && gReplay->GetPlaybackFlagA4())
			{
				machines = 1;
			}
			ApplySyncMessage(&machines, type, message);
		}
	}

	// FUNCTION: ENGINE 0x108336F0
	void UpdateSync()
	{
		if (gSyncConnection != 0)
		{
			char buffer[8];
			unsigned int length;
			unsigned char flag;
			int* source;
			while (gSyncConnection->Receive(buffer, 8, &length, &flag, &source) != 0)
			{
				ApplySyncMessage((const unsigned int*)source, flag, (const SyncMessage*)buffer);
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (gSyncFactories[i] != 0)
			{
				gSyncFactories[i]->Update();
			}
		}
	}
}
