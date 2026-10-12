// engine::Behaviour (RTTI name, 8 vftable slots, no base): a component of a GameObject. The owner's behaviour
// container (embedded in the GameObject at 0x20) schedules it and routes the message types it listens to. Unit
// 0x107EE450 - 0x107EEBBA; no assert path names it, the file name is a guess. The reflected members are "active",
// "inactiveMask" and "timeSliceFrameSkip" (strings of the unit's member table); other names are guesses.
#ifndef ENGINE_GAMEOBJECT_BEHAVIOUR_H
#define ENGINE_GAMEOBJECT_BEHAVIOUR_H

#include "code/container/arraydynamic.h"
#include <typeinfo>

namespace content
{
	struct ClassInfo;
	struct MemberList;
}

namespace engine
{
	class Behaviour;
	class GameObject;
	struct Message;
	class DispatchTable;

	// A small set of flag bits. The members are defined outside the class without inline, so every unit keeps its
	// own called copies (the constructor's and Test's copies the engine kept sit in other units).
	// The listening mask bit of a message type
	inline unsigned __int64 GetMessageBit(int type)
	{
		return (unsigned __int64)1 << type;
	}

	template<class T> class BitField
	{
	public:
		BitField();
		void Clear();
		T Get() const;
		void Set(T value);
		void SetBit(int bit);
		void ClearBit(int bit);
		bool Test(int bit) const;

		T bits;
	};

	template<class T> BitField<T>::BitField()
	{
		bits = 0;
	}

	template<class T> void BitField<T>::Clear()
	{
		bits = 0;
	}

	template<class T> T BitField<T>::Get() const
	{
		return bits;
	}

	template<class T> void BitField<T>::Set(T value)
	{
		bits = value;
	}

	template<class T> void BitField<T>::SetBit(int bit)
	{
		bits |= 1 << (unsigned char)bit;
	}

	template<class T> void BitField<T>::ClearBit(int bit)
	{
		bits &= ~(1 << (unsigned char)bit);
	}

	template<class T> bool BitField<T>::Test(int bit) const
	{
		return (bits & (1 << bit)) != 0;
	}

	class Behaviour
	{
	public:
		enum
		{
			// Bits of state (the byte at 8)
			STATE_DIRTY = 2
		};

		explicit Behaviour(GameObject* newOwner);

		// The reflection data: the class and its members ("active", "inactiveMask", "timeSliceFrameSkip")
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
		virtual void Slot0()
		{
		}
		virtual void Slot1()
		{
		}
		virtual bool Slot2();
		// Called when the computed activity changes
		virtual void OnActiveChanged(bool active);
		// Advances the behaviour by dt in the update passes of mask (the default warns once)
		virtual void Update(float dt, unsigned short mask);
		// Messages handed on by the game object: posted / sent (the controller distributes them; names guessed)
		virtual void OnPostedMessage(Message* message)
		{
		}
		virtual void OnMessage(Message* message)
		{
		}
		virtual ~Behaviour();

		// The "active" member's getter (0x10075C80, the copy the engine kept is in another unit) and setter
		bool IsActive() const
		{
			return requested.Test(7);
		}
		unsigned char GetInactiveMask() const;
		void SetInactiveMask(unsigned char mask);
		bool ComputeActive();
		void ApplyActive(bool active);
		void SetUpdating(bool updating);
		void Refresh();
		void SetEnabled(bool enabled);
		void SetRequestBit(unsigned char bit, bool on);

		void Listen(int messageType, bool listen);
		void Listen2(int messageType, bool listen);
		void Remove(unsigned char frameSkip);
		unsigned char GetFrameSkip();
		bool Query2(int value);
		bool Query3();
		bool Query4(int value);
		void SetState(unsigned char mask);
		void ClearState(unsigned char mask);

		GameObject* owner;
		unsigned char state;
		BitField<unsigned char> flags;
		BitField<unsigned char> requested;
		unsigned char timeSliceFrameSkip;
	};

	// The GameObject's behaviour controller (RTTI engine::BehaviourController, another unit, 0x1083xxxx): message type listening (a
	// 64-bit mask) and scheduling. Method meanings beyond SetListening are unknown.
	// It is a Behaviour itself (Behaviour::ApplyActive skips notifying the container about itself).
	class BehaviourController : public Behaviour
	{
	public:
		// The controller's scheduling of one behaviour (8 bytes): the time not yet handed to it, the update passes in
		// the low 13 bits of flags (0x2000: updated this frame, 0x4000: scheduled, 0x8000: active), and the frame
		// skip with its phase
		struct ScheduleEntry
		{
			ScheduleEntry()
			{
				time = 0.0f;
				frameSkip = 1;
				phase = 0;
				flags = 0x4000;
			}
			unsigned short GetPasses() const
			{
				return passes;
			}
			bool TestPasses(unsigned short mask) const
			{
				return (flags & mask) != 0;
			}
			bool IsActive() const
			{
				return active;
			}
			void SetActive(bool value)
			{
				if (value)
				{
					active = 1;
				}
				else
				{
					active = 0;
				}
			}
			bool IsScheduled() const
			{
				return scheduled;
			}
			void SetScheduled(bool value)
			{
				if (value)
				{
					scheduled = 1;
				}
				else
				{
					scheduled = 0;
				}
			}
			bool IsUpdated() const
			{
				return updated;
			}
			void SetUpdated(bool value)
			{
				if (value)
				{
					updated = 1;
				}
				else
				{
					updated = 0;
				}
			}

			float time;
			union
			{
				struct
				{
					unsigned short passes : 13;
					unsigned short updated : 1;
					unsigned short scheduled : 1;
					unsigned short active : 1;
				};
				unsigned short flags;
			};
			unsigned char frameSkip;
			unsigned char phase;
		};

		// The message types one behaviour listens for
		struct MessageMask
		{
			MessageMask()
			{
				bits = 0;
			}

			unsigned __int64 bits;
		};

		// 0x1083AAA0 / 0x1083AB00
		explicit BehaviourController(GameObject* newOwner);
		virtual ~BehaviourController();

		// 0x10839340 / 0x1083A9C0: the controller's reflection data ("updateTimeScalar", "behaviours")
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// The vftable: slots 1 - 3 and 5 - 7 override Behaviour's, 8 - 10 are the controller's own
		// Ends the owner's construction: compacts the behaviour list and its tables into the construction heap, then
		// gives every behaviour its slot 0
		virtual void Slot0();
		virtual void Slot1();
		virtual bool Slot2();
		virtual void OnActiveChanged(bool active);
		virtual void OnPostedMessage(Message* message);
		virtual void OnMessage(Message* message);
		// Sets a request bit of every behaviour / enables or disables them all / deletes them all
		virtual void SetRequestBitAll(unsigned char bit, bool on);
		virtual void SetEnabledAll(bool enabled);
		virtual void RemoveAll();

		void AddBehaviour(Behaviour* behaviour);
		// Creates the schedule of a behaviour (the one being constructed may have created it already)
		void RegisterBehaviour(Behaviour* behaviour);
		int IndexOf(Behaviour* behaviour);
		ScheduleEntry* GetSchedule(Behaviour* behaviour);
		MessageMask* GetMessageMask(Behaviour* behaviour);
		void UpdatePasses(unsigned short mask, bool add);
		void UpdateListening(int messageType, bool listen);
		void NotifyActiveChanged(Behaviour* behaviour);
		// The behaviour's update passes: add or remove mask (named after its caller Behaviour::Listen2)
		void SetListening2(int mask, Behaviour* behaviour, bool add);
		void SetListening(int messageType, Behaviour* behaviour, bool listen);
		// The behaviour updates every frameSkip-th frame, in a phase shared by the behaviours of the same skip
		void Remove(unsigned char frameSkip, Behaviour* behaviour);
		void SetTimeSliceFrameSkip(unsigned char frameSkip);
		void HandleMessage(Message* message);
		// Updates the behaviours of the passes in mask
		void UpdateBehaviours(float dt, unsigned short mask);
		unsigned char GetFrameSkip(Behaviour* behaviour);
		bool Query2(int mask, Behaviour* behaviour);
		bool Query3(Behaviour* behaviour);
		bool Query4(int messageType, Behaviour* behaviour);
		bool SetEnabledOfType(const type_info& type, bool enabled);
		bool IsActiveOfType(const type_info& type);

		// True when a behaviour listens for messages of type
		bool IsListening(int type) const
		{
			return (GetMessageBit(type) & listenMask) != 0;
		}

		float updateTimeScalar;
		container::ArrayDynamicHeap<Behaviour*> behaviours;
		// Bit n: a behaviour listens for message type n
		unsigned __int64 listenMask;
		// The update passes of the object (UpdateGameObjects' mask)
		unsigned short updateMask;
		bool dirty;
		// The number of schedules (they are created before the behaviours are added)
		unsigned char scheduleCount;
		ScheduleEntry* schedule;
		MessageMask* messageMasks;
		DispatchTable* dispatch;
	};
}

#endif
