// engine::Behaviour (RTTI name, 8 vftable slots, no base): a component of a GameObject. The owner's behaviour
// container (embedded in the GameObject at 0x20) schedules it and routes the message types it listens to. Unit
// 0x107EE450 - 0x107EEBBA; no assert path names it, the file name is a guess. The reflected members are "active",
// "inactiveMask" and "timeSliceFrameSkip" (strings of the unit's member table); other names are guesses.
#ifndef ENGINE_GAMEOBJECT_BEHAVIOUR_H
#define ENGINE_GAMEOBJECT_BEHAVIOUR_H

namespace content
{
	struct ClassInfo;
	struct MemberList;
}

namespace engine
{
	class Behaviour;
	class BehaviourOwner;

	// A small set of flag bits. The members are defined outside the class without inline, so every unit keeps its
	// own called copies (the constructor's and Test's copies the engine kept sit in other units).
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

		explicit Behaviour(BehaviourOwner* newOwner);

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
		virtual void Slot4(int a, int b);
		virtual void Slot5(int a)
		{
		}
		virtual void Slot6(int a)
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
		void Remove(int value);
		bool Query1();
		bool Query2(int value);
		bool Query3();
		bool Query4(int value);
		void SetState(unsigned char mask);
		void ClearState(unsigned char mask);

		BehaviourOwner* owner;
		unsigned char state;
		BitField<unsigned char> flags;
		BitField<unsigned char> requested;
		unsigned char timeSliceFrameSkip;
	};

	// The GameObject's behaviour container (another unit, 0x1083xxxx): message type listening (a 64-bit mask) and
	// scheduling. Method meanings beyond SetListening are unknown.
	// It is a Behaviour itself (Behaviour::ApplyActive skips notifying the container about itself).
	class BehaviourContainer : public Behaviour
	{
	public:
		// 0x1083A420: the behaviour's activity changed
		void NotifyActiveChanged(Behaviour* behaviour);
		// 0x1083A530 / 0x1083A4B0: listen (or stop) for a message type
		void SetListening(int messageType, Behaviour* behaviour, bool listen);
		void SetListening2(int messageType, Behaviour* behaviour, bool listen);
		// 0x1083A5B0
		void Remove(int value, Behaviour* behaviour);
		// 0x10839860 / 0x10839690 / 0x108396F0 / 0x108397E0
		bool Query1(Behaviour* behaviour);
		bool Query2(int value, Behaviour* behaviour);
		bool Query3(Behaviour* behaviour);
		bool Query4(int value, Behaviour* behaviour);
	};

	class BehaviourOwner
	{
	public:
		unsigned char unknown0[0x20];
		BehaviourContainer behaviours;
	};
}

#endif
