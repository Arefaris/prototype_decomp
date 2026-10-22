// engine::controller::InputSystem (RTTI: derives from SlotManager and ControllerManagerInterface::Callback, the
// latter at offset 0x10) and the types around it. No assert path names the unit (0x107DF3B0 - 0x107E0710); the file
// name is a guess from the class. The InputSystem owns one PlayerInfo (0x2C8 bytes, another unit) per controller and
// per remote player: controllers come first and are addressed by local ids 0xFE00 | index, the remote players
// follow. All member and method names are guesses unless noted.
#ifndef ENGINE_CONTROLLER_INPUTSYSTEM_H
#define ENGINE_CONTROLLER_INPUTSYSTEM_H

#include "code/container/slist.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"

namespace engine
{
	namespace controller
	{
		// The input object a player gets from the PlayerInfoFactory (type unknown; only these virtuals are used)
		class PlayerInput
		{
		public:
			virtual void Slot0() = 0;
			virtual void Slot1() = 0;
			virtual void Slot2() = 0;
			virtual void SetValue(int value) = 0;
			virtual void Reset() = 0;

			// 0x108A1890 (another unit): gives the input a name
			void SetName(const char* name);
		};

		// One player slot (another unit: constructor 0x108A15F0, destructor 0x108A1280). It is a list node of the
		// InputSystem's player lists, keyed by the id at 4.
		class PlayerInfo : public container::SListBase::Node
		{
		public:
			PlayerInfo();
			~PlayerInfo();
			// 0x108A1290 / 0x108A17E0 (another unit)
			void Clear();
			void Update();
			// 0x10845B50: a float of the axes (component 0 or 1 of the axis' pair); 0x10845B70 / 0x10845B80: the view
			// (out of line in the physical controller's unit; names guessed)
			void SetAxisFloat(int axis, float value, int component);
			void SetViewMatrix(const math::Matrix& matrix);
			void SetViewPosition(const math::Vector& position);
			PlayerInfo* GetNext() const
			{
				return (PlayerInfo*)next;
			}
			bool HasFlags(unsigned int mask) const
			{
				return (flags & mask) == mask;
			}
			void SetFlags(unsigned int mask)
			{
				flags |= mask;
			}
			void ClearFlags(unsigned int mask)
			{
				flags &= ~mask;
			}
			void ResetFlags()
			{
				flags = 0;
			}
			unsigned int GetFlags() const
			{
				return flags;
			}
			void SetId(unsigned int value)
			{
				id = value;
			}
			void SetContext(int value)
			{
				context = value;
			}
			void SetSlot(int value)
			{
				slot = value;
			}
			PlayerInput* GetInput() const
			{
				return input;
			}
			void SetInput(PlayerInput* value)
			{
				input = value;
			}
			// Bit 2 set, or bit 0 set without bit 3
			bool IsActive() const
			{
				return (flags & 4) || ((flags & 1) && !(flags & 8));
			}

			unsigned int id;
			unsigned int flags;
			// The player's view: the matrix and the position of its camera (0x108474E0; names guessed)
			math::Matrix viewMatrix;
			float viewPosition[3];
			// What the physical controller reads: the values of the buttons, and per axis a pair of floats whose
			// second is the value (0x10846B00 / 0x108472A0; names guessed)
			float buttons[42];
			unsigned char unknown100[0x1a8 - 0x100];
			struct AxisState
			{
				float unknown;
				float value;
			};
			AxisState axes[17];
			unsigned char unknown230[0x2b8 - 0x230];
			int context;
			int slot;
			PlayerInput* input;
			int unknown2C4;
		};

		// The slot table base (another unit): slots of {player id, PlayerInfo}
		class SlotManager
		{
		public:
			struct Slot
			{
				unsigned int id;
				PlayerInfo* info;
			};

			// 0x108A1CA0 / 0x108A1A20
			explicit SlotManager(int count);
			virtual ~SlotManager();
			virtual void Update() = 0;
			virtual void Notify(int a, int b) = 0;
			virtual void AssignSlot(int index, unsigned int id) = 0;

			// 0x108A1A50: the slot holding id, or -1
			int FindSlot(unsigned int id);
			// 0x108A1AB0
			void ResetSlots();
			// 0x108A1AF0
			void ReleaseSlot(unsigned int id, int value);
			// 0x108A1E50: an object updated with the frame time (type unknown)
			class Updater* GetUpdater();

			Slot* slots;
			// The number of slots (the fight conditions on the online session read it as the number of players)
			int slotCount;
			int unknownC;
		};

		// The controller manager the InputSystem drives (RTTI: ControllerManagerInterface, 5 slots)
		class ControllerManagerInterface
		{
		public:
			// The receiver of the manager's events (RTTI: ControllerManagerInterface::Callback, 3 slots, all pure)
			class Callback
			{
			public:
				virtual void OnFlags(unsigned int id, unsigned int flags, bool set, int which) = 0;
				virtual void OnValue(unsigned int id, int value) = 0;
				virtual void OnRelease(unsigned int id, int value) = 0;
			};

			virtual void SetFlags(unsigned int id, unsigned int flags, bool set) = 0;
			virtual void SetValue(unsigned int id, int value) = 0;
			virtual void Refresh() = 0;
			virtual void Collect(container::SListBase* players) = 0;
			virtual void CollectActive(container::SListBase* players, float time) = 0;

			Callback* callback;
		};

		class Updater
		{
		public:
			virtual void Update(float time) = 0;
		};

		// RTTI: PhysicalControllerManager (another unit; constructor 0x108A0BB0, destructor 0x108A0970)
		class PhysicalControllerManager : public ControllerManagerInterface
		{
		public:
			explicit PhysicalControllerManager(int controllerCount);
			~PhysicalControllerManager();
			virtual void SetFlags(unsigned int id, unsigned int flags, bool set);
			virtual void SetValue(unsigned int id, int value);
			virtual void Refresh();
			virtual void Collect(container::SListBase* players);
			virtual void CollectActive(container::SListBase* players, float time);
			// 0x108A0A20: motor 0 / 1 of the controller
			void SetVibration(unsigned int id, int motor, float a, float b, float c, float d);

			// 0x38 bytes in all (InputSystem allocates it); the rest is unknown
			unsigned char unknown8[0x38 - 8];
		};

		// RTTI: PlayerInfoFactoryInterface (2 slots, no virtual destructor) and PlayerInfoFactory (slots 0 and 1 in
		// another unit, 0x108A19F0 / 0x108A19A0; its destructor is slot 2)
		class PlayerInfoFactoryInterface
		{
		public:
			PlayerInfoFactoryInterface()
			{
			}
			virtual PlayerInput* Create() = 0;
			virtual void Destroy(PlayerInput* input) = 0;
		};

		class PlayerInfoFactory : public PlayerInfoFactoryInterface
		{
		public:
			virtual PlayerInput* Create();
			virtual void Destroy(PlayerInput* input);
			virtual ~PlayerInfoFactory()
			{
			}
		};

		// Something the InputSystem owns at 0x40 and deletes through its virtual destructor (slot 1); type unknown
		class InputOverride
		{
		public:
			virtual void Slot0() = 0;
			virtual ~InputOverride() = 0;
		};

		// The two extra objects the configuration may provide (12 bytes each, constructed by 0x108A2B10 / 0x108A4A20
		// in another unit when it does not)
		class InputHelperA
		{
		public:
			InputHelperA();
			int unknown[3];
		};
		class InputHelperB
		{
		public:
			InputHelperB();
			int unknown[3];
		};

		class InputSystem : public SlotManager, public ControllerManagerInterface::Callback
		{
		public:
			// The 13 words InputSystem copies; defaults from 0x107DF4E0
			class Config
			{
			public:
				Config();

				int playerCount;
				int controllerCount;
				int unknown8;
				// The heap the InputSystem is created in (and allocates from while constructing)
				int heap;
				// The context every controller starts with
				int defaultContext;
				float deadZone;
				bool flag18;
				InputHelperA* helperA;
				InputHelperB* helperB;
				bool flag24;
				int unknown28;
				int unknown2C;
				const char* name;
			};

			// The listeners told about player changes (RTTI: InputSystem::InputCallback, a list node after the vftable)
			class InputCallback : public container::SListLite<InputCallback>::Node
			{
			public:
				// The defaults do nothing (0x107F6B40 - 0x107F6B60, kept in the database unit)
				virtual void OnFlags(unsigned int id, int local, unsigned int flags, bool set)
				{
				}
				virtual void OnValue(unsigned int id, int local, PlayerInput* input)
				{
				}
				virtual void OnNotify(int a, int b, int c)
				{
				}
			};

			// Per controller: a stack of up to five contexts
			struct ContextStack
			{
				int items[5];
				int count;
			};

			explicit InputSystem(const Config& config);
			virtual ~InputSystem();
			virtual void Update();
			virtual void Notify(int a, int b);
			virtual void AssignSlot(int index, unsigned int id);
			virtual void OnFlags(unsigned int id, unsigned int flags, bool set, int which);
			virtual void OnValue(unsigned int id, int value);
			virtual void OnRelease(unsigned int id, int value);

			static InputSystem* sInstance;
			static InputSystem* Get();
			// Inline; 0x10825AF0 (in poimanager.cpp's range) is a kept copy
			int GetPlayerCount() const
			{
				return playerCount;
			}
			static void Create(const Config& config);
			static void Destroy();
			// The player in list whose id matches
			PlayerInfo* FindPlayer(unsigned int id, container::SListBase* list);
			PlayerInfo* FindConnected(unsigned int id)
			{
				return FindPlayer(id, &connected);
			}

			// Inline (0x107F71A0 is a kept copy in the database unit)
			void AddCallback(InputCallback* callback)
			{
				callbacks.PushBack(callback);
			}
			static bool IsLocal(unsigned int id)
			{
				return (id & 0xffffff00) == 0xfe00;
			}
			PlayerInfo* GetPlayer(unsigned int id)
			{
				return &players[(unsigned char)id];
			}
			int GetControllerCount() const
			{
				return controllerCount;
			}
			static unsigned int LocalId(int index)
			{
				return (unsigned char)index | 0xfe00;
			}
			// The remote player with id, or a free remote slot taken for it
			PlayerInfo* FindRemote(unsigned int id)
			{
				for (int i = controllerCount; i < playerCount + controllerCount; i++)
				{
					if (players[i].id == id)
					{
						return &players[i];
					}
				}
				return 0;
			}
			PlayerInfo* AllocRemote(unsigned int id)
			{
				for (int i = controllerCount; i < playerCount + controllerCount; i++)
				{
					if (players[i].id == 0xffffffff)
					{
						players[i].id = id;
						players[i].flags = 0;
						return &players[i];
					}
				}
				return 0;
			}
			// Gives the slot holding id to it again
			void RefreshSlot(unsigned int id)
			{
				int slot = FindSlot(id);
				if (slot >= 0)
				{
					AssignSlot(slot, id);
				}
			}
			void RemoveConnected(PlayerInfo* info, unsigned int id)
			{
				connected.Remove(info);
				info->input->Reset();
				info->id = 0xffffffff;
				RefreshSlot(id);
			}

			void SetPlayerFlags(unsigned int id, unsigned int flags);
			void ClearPlayerFlags(unsigned int id, unsigned int flags);
			void PushContext(unsigned int id, int context);
			void PopContext(unsigned int id);
			int GetContext(unsigned int id);
			void ClearRemotePlayers();
			void ClearControllers();
			void SetFactory(PlayerInfoFactoryInterface* newFactory);
			void Reset();
			// Inline (StopVibration expands it); 0x107DF600 is the kept copy
			void SetVibration(unsigned int id, int motor, float a, float b, float c, float d)
			{
				physical->SetVibration(id, motor, a, b, c, d);
			}
			void CollectPlayers();
			void UpdatePlayers(int a, int b, float time);
			void StopVibration();
			void SetValue(unsigned int id, int value);
			void NotifyFlags(unsigned int id, int local, unsigned int flags, bool set);
			void UpdateLocal(unsigned int id, unsigned int flags, bool set);
			void UpdateRemote(unsigned int id, unsigned int flags, bool set);
			void ResetAll();
			void SetManager(ControllerManagerInterface* newManager, bool reset);

			int playerCount;
			int controllerCount;
			PlayerInfo* players;
			container::SListBase connected;
			container::SListBase active;
			int pending;
			PhysicalControllerManager* physical;
			InputOverride* override;
			ControllerManagerInterface* manager;
			PlayerInfoFactoryInterface* factory;
			container::SListLite<InputCallback> callbacks;
			ContextStack* contexts;
			Config config;
		};
	}
}

#endif
