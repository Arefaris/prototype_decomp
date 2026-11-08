// engine::controller::InputSystem (RTTI: derives from SlotManager and ControllerManagerInterface::Callback, the
// latter at offset 0x10) and the types around it. No assert path names the unit (0x107DF3B0 - 0x107E0710); the file
// name is a guess from the class. The InputSystem owns one PlayerInput (0x2C8 bytes, another unit) per controller and
// per remote player: controllers come first and are addressed by local ids 0xFE00 | index, the remote players
// follow. All member and method names are guesses unless noted.
#ifndef ENGINE_CONTROLLER_INPUTSYSTEM_H
#define ENGINE_CONTROLLER_INPUTSYSTEM_H

#include "code/container/map.h"
#include "code/engine/controller/controllerpacker.h"
#include "code/engine/updatecontext.h"
#include "code/container/slist.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"

namespace engine
{
	namespace controller
	{
		// RTTI: engine::controller::PlayerInfo (5 vftable slots, 0x20 bytes, made by the PlayerInfoFactory): the name of a
		// player and two ids
		class PlayerInfo
		{
		public:
			// 0x108A19C0
			PlayerInfo();
			// 0x108A1880 (slot 0 is the scalar deleting destructor 0x108A19D0)
			virtual ~PlayerInfo();
			// Slot 1 (0x108A18D0): the name and the two ids into a buffer; answers the bytes written
			virtual int Write(char* buffer, int size);
			// Slot 2 (0x108A1920): the same out of a buffer
			virtual void Read(const char* buffer, int size);
			// Slot 3 (0x108A1960)
			virtual void Assign(const PlayerInfo* other);
			// Slot 4 (0x108A1990): no name, ids -1
			virtual void Reset();

			// 0x108A1890: gives the player a name
			void SetName(const char* newName);
			// 0x108A18B0
			void SetIds(int first, int second);

			int unknown4;
			char name[16];  // +8
			int firstId;  // +0x18
			int secondId;  // +0x1C
		};

		// One player slot (another unit: constructor 0x108A15F0, destructor 0x108A1280). It is a list node of the
		// InputSystem's player lists, keyed by the id at 4.
		class PlayerInput : public container::SListBase::Node
		{
		public:
			PlayerInput();
			~PlayerInput();
			// 0x108A1290 / 0x108A17E0 (another unit)
			void Clear();
			void Update();
			// 0x108A11E0: the state of a control
			void SetControlState(int control, int state);
			// 0x108A1200: one of the two words of a control's bits
			void SetButtonBits(int control, unsigned int value, int which);
			// 0x108A1500 / 0x108A1640 / 0x108A1720: the dead zone of a stick (a square or a round one) and of all of them
			void ApplySquareDeadZone(int first, int second);
			void ApplyRoundDeadZone(int first, int second);
			void ApplyDeadZones();
			// 0x10845B50: a float of the axes (component 0 or 1 of the axis' pair); 0x10845B70 / 0x10845B80: the view
			// (out of line in the physical controller's unit; names guessed)
			void SetAxisFloat(int axis, float value, int component);
			void SetViewMatrix(const math::Matrix& matrix);
			void SetViewPosition(const math::Vector& position);
			PlayerInput* GetNext() const
			{
				return (PlayerInput*)next;
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
			PlayerInfo* GetInput() const
			{
				return input;
			}
			void SetInput(PlayerInfo* value)
			{
				input = value;
			}
			// Bit 2 set, or bit 0 set without bit 3
			bool IsActive() const
			{
				return (flags & 4) || ((flags & 1) && !(flags & 8));
			}

			// The state of a control (a button or a stick) in the contexts the player is in, in the unit 0x108810F0: the
			// bits of the control's two words (0x108810F0 is the out-of-line copy), or the low bit of the mask when the
			// player is not in the context
			bool IsControlSet(int control, unsigned int mask, unsigned int contextMask, int which) const
			{
				if ((context & contextMask) == 0)
				{
					return mask & 1;
				}
				return (buttons[control].bits[which] & mask) != 0;
			}

			// A stick's value and what goes with it
			struct AnalogState
			{
				float value;
				// what the physical controller writes for the stick (0x108472A0; name guessed)
				float input;
			};
			struct ButtonBits
			{
				unsigned int bits[2];
			};

			unsigned int id;
			unsigned int flags;
			// The player's view: the matrix and the position of its camera (0x108474E0; names guessed)
			math::Matrix viewMatrix;  // +0xC
			float viewPosition[3];  // +0x4C
			// What the physical controller reads: the values of the buttons (0x10846B00 / 0x108472A0; name guessed)
			float buttonValues[42];  // +0x58
			// +0x100: per control (0x2A of them): 0 for nothing, 1 for pressed, 2 for down, 3 for released
			int controlStates[42];
			AnalogState analog[17];  // +0x1A8
			ButtonBits buttons[17];  // +0x230
			int context;
			int slot;
			PlayerInfo* input;
			int unknown2C4;
		};

		// The slot table base (another unit): slots of {player id, PlayerInput}
		class SlotManager
		{
		public:
			struct Slot
			{
				// 0x108A1A10 (the array constructor's element: an empty slot holds the id -1)
				Slot();

				unsigned int id;
				PlayerInput* info;
			};

			// 0x108A1CA0 / 0x108A1A20
			explicit SlotManager(int count);
			virtual ~SlotManager();
			// Slot 1 (0x108A1AF0): lets go of the slot of id, or of the slot with that index (-1: none, -2: all)
			virtual void ReleaseSlot(unsigned int id, int slot);
			// Slot 2 (0x108A1A40): nothing
			virtual void Notify(int a, int b)
			{
			}
			// Slot 3 (0x108A1C40)
			virtual void AssignSlot(int index, unsigned int id);

			// 0x108A1A50: the slot holding id, or -1
			int FindSlot(unsigned int id);
			// 0x108A1AB0
			void ResetSlots();
			// 0x108A1A80: counts the slots in use into slotCount (name guess)
			void CountSlots();
			// 0x108A1C60: lets go of the slots whose id carries that kind in its second byte (name guess)
			void ReleaseSlotsOfKind(unsigned int kind);
			// 0x108A1E50: the keyboard (a jump to 0x108D6AA0, which answers the one instance)
			static class Keyboard* GetKeyboard();

			Slot* slots;
			// The number of slots in use (the fight conditions on the online session read it as the number of players)
			int slotCount;
			// The number of slots the table has
			int capacity;
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
			virtual void Release(unsigned int id, int slot) = 0;
			virtual void Collect(container::SListBase* players) = 0;
			virtual void CollectActive(container::SListBase* players, float time) = 0;

			Callback* callback;
		};

		// A key event as the keyboard hands it to its callbacks (20 bytes, passed by value; names guessed)
		struct KeyEvent
		{
			// 0: the key went down, 1: it repeats, 2: it went up
			int state;
			// The virtual key
			int key;
			// The modifier flags at that moment (1: alt, 2: control, 4: shift, 8 and 0x10: two more)
			unsigned int modifiers;
			// The character the key makes with those modifiers
			unsigned char character;
			// The scan code of the key on the layout of the thread
			int scanCode;
		};

		// The characters a key makes: plain, with shift, with control and with alt (0 when none)
		struct KeyCharacters
		{
			unsigned char plain;
			unsigned char shifted;
			unsigned char control;
			unsigned char alt;
		};

		// The nodes of the key map come from the global array new and delete
		struct KeyAllocator
		{
			static void* Alloc(unsigned int size)
			{
				return operator new[](size);
			}
			static void Free(void* block)
			{
				operator delete[](block);
			}
		};
		typedef container::Map<int, KeyCharacters, KeyAllocator> KeyMap;

		// RTTI: engine::controller::Keyboard (base of KeyboardWin32): updated with the frame time by the InputSystem;
		// keeps a list of callbacks and stays enabled while it has one (0x2C bytes)
		class Keyboard
		{
		public:
			// RTTI: Keyboard::Callback (one pure virtual slot); a list node after the vftable
			class Callback : public container::SListLite<Callback>::Node
			{
			public:
				virtual void OnKey(KeyEvent event) = 0;
			};

			// 0x108A2180: the key map is made from the table of the keys that make characters
			Keyboard();
			// The key map is emptied (0x108A1FE0 frees each node)
			~Keyboard()
			{
			}
			// 0x108A20C0: the character a key makes with the modifiers
			unsigned char GetCharacter(int key, unsigned int modifiers);

			// Vftable slots 0 - 2 (0x108A2260, 0x108A1E60, 0x108A1E70): the base does nothing and is never enabled
			virtual void Update(float time)
			{
			}
			virtual bool IsEnabled()
			{
				return false;
			}
			virtual void SetEnabled(bool enabled)
			{
			}

			// Inline (kept copies at 0x108815D0 / 0x10881610 in the front end input unit)
			void AddCallback(Callback* callback)
			{
				callbacks.PushBack(callback);
				if (!IsEnabled())
				{
					SetEnabled(true);
				}
			}
			void RemoveCallback(Callback* callback)
			{
				callbacks.Remove(callback);
				int count = callbacks.count;
				bool enabled = IsEnabled();
				bool empty = count == 0;
				if (enabled == empty)
				{
					SetEnabled(callbacks.count != 0);
				}
			}

			container::SListLite<Callback> callbacks;
			KeyMap keys;  // +0x10
		};

		// RTTI: PhysicalControllerManager (5 vftable slots, 0x38 bytes): the controllers by slot, and the packed state of
		// the players it last collected
		class PhysicalControllerManager : public ControllerManagerInterface
		{
		public:
			// 0x108A0BB0 / 0x108A0970
			explicit PhysicalControllerManager(int controllerCount);
			~PhysicalControllerManager();
			// Slots 0 - 2 (0x108A0B60, 0x108A0B80, 0x108A0B90): handed on to the callback
			virtual void SetFlags(unsigned int id, unsigned int flags, bool set);
			virtual void SetValue(unsigned int id, int value);
			virtual void Release(unsigned int id, int slot);
			// Slot 3 (0x108A0C20) and 4 (0x108A0DB0)
			virtual void Collect(container::SListBase* players);
			virtual void CollectActive(container::SListBase* players, float time);
			// 0x108A0A20: motor 0 / 1 of the controller
			void SetVibration(unsigned int id, int motor, float a, float b, float c, float d);
			// 0x108A0990: sets the controller object of the slot (and its flags, when the manager has a callback)
			void SetController(unsigned int id, class PhysicalController* controller);
			// 0x108A09D0: takes the controller away
			void RemoveController(unsigned int id);
			// 0x108A0B40: the controller (and the one that shares its input) the manager answers for
			void Select(int secondary, unsigned int primary);
			// 0x108A0BA0
			unsigned int GetSelected() const
			{
				return selected;
			}

			int controllerCount;  // +8
			class PhysicalController** controllers;  // +0xC
			ControllerSnapshot snapshot;  // +0x10
			unsigned int selected;  // +0x2C
			unsigned int secondary;  // +0x30
			bool unknown34;
		};

		// RTTI: PlayerInfoFactoryInterface (2 slots, no virtual destructor) and PlayerInfoFactory (slots 0 and 1 in
		// another unit, 0x108A19F0 / 0x108A19A0; its destructor is slot 2)
		class PlayerInfoFactoryInterface
		{
		public:
			PlayerInfoFactoryInterface()
			{
			}
			virtual PlayerInfo* Create() = 0;
			virtual void Destroy(PlayerInfo* input) = 0;
		};

		class PlayerInfoFactory : public PlayerInfoFactoryInterface
		{
		public:
			virtual PlayerInfo* Create();
			virtual void Destroy(PlayerInfo* input);
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
				ControllerPacker* helperA;
				ControllerPackerLossLess* helperB;
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
				virtual void OnValue(unsigned int id, int local, PlayerInfo* input)
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
			virtual void ReleaseSlot(unsigned int id, int slot);
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
			PlayerInput* FindPlayer(unsigned int id, container::SListBase* list);
			PlayerInput* FindConnected(unsigned int id)
			{
				return FindPlayer(id, &connected);
			}

			// Inline (0x107F71A0 is a kept copy in the database unit)
			void AddCallback(InputCallback* callback)
			{
				callbacks.PushBack(callback);
			}
			void RemoveCallback(InputCallback* callback)
			{
				callbacks.Remove(callback);
			}
			static bool IsLocal(unsigned int id)
			{
				return (id & 0xffffff00) == 0xfe00;
			}
			PlayerInput* GetPlayer(unsigned int id)
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
			PlayerInput* FindRemote(unsigned int id)
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
			PlayerInput* AllocRemote(unsigned int id)
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
			void RemoveConnected(PlayerInput* info, unsigned int id)
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
			// 0x107DF600: out of line (StopVibration expands the call of the manager itself)
			void SetVibration(unsigned int id, int motor, float a, float b, float c, float d);
			void CollectPlayers();
			void UpdatePlayers(UpdateContext context);
			void StopVibration();
			void SetValue(unsigned int id, int value);
			void NotifyFlags(unsigned int id, int local, unsigned int flags, bool set);
			void UpdateLocal(unsigned int id, unsigned int flags, bool set);
			void UpdateRemote(unsigned int id, unsigned int flags, bool set);
			void ResetAll();
			void SetManager(ControllerManagerInterface* newManager, bool reset);

			int playerCount;
			int controllerCount;
			PlayerInput* players;
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
