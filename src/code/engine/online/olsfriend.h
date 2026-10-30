// engine::OLSFriend (RTTI name): the interface the online service's friend list is driven through. Its script
// methods are registered by the unit that owns it (Method / Closure wrappers in olsfriendwrappers.cpp); the
// interface itself has 23 virtual slots whose defaults do nothing. Slot names and signatures are guesses from the
// default bodies; the unit is 0x108EA320 - 0x108EA510 (no assert path, file name guessed).
#ifndef ENGINE_ONLINE_OLSFRIEND_H
#define ENGINE_ONLINE_OLSFRIEND_H

namespace engine
{
	// A string of wide characters the front end shows (0x108A5560 / 0x108A5570: constructor and destructor, another unit)
	class WideStringBuffer
	{
	public:
		WideStringBuffer();
		~WideStringBuffer();

		unsigned char unknown0[8];
	};

	// What the friend list keeps for one friend (0x1C bytes; the destructor is 0x108E9C30)
	struct OLSFriendEntry
	{
		~OLSFriendEntry();

		WideStringBuffer name;  // +0
		int unknown8;
		int unknownC;
		int unknown10;
		WideStringBuffer status;  // +0x14
	};

	class OLSFriend
	{
	public:
		// 0x108EA8A0 is the deleting destructor, 0x108EA320 the body
		virtual ~OLSFriend();
		// vftable slots 1 - 22: the defaults (0x108EA390 - 0x108EA4E0)
		virtual void Slot1()
		{
		}
		virtual void Slot2()
		{
		}
		virtual void Slot3()
		{
		}
		virtual bool Slot4(int a)
		{
			return false;
		}
		virtual bool Slot5()
		{
			return false;
		}
		virtual void Slot6()
		{
		}
		virtual void Slot7()
		{
		}
		virtual void Slot8()
		{
		}
		virtual void Slot9(int a)
		{
		}
		virtual void Slot10(int a)
		{
		}
		virtual void Slot11(int a)
		{
		}
		virtual void Slot12(int a)
		{
		}
		virtual void Slot13(int a)
		{
		}
		virtual void Slot14(int a)
		{
		}
		virtual void Slot15(int a, int b, int c)
		{
		}
		virtual void Slot16(int a, int b, int c)
		{
		}
		virtual void Slot17(int a, WideStringBuffer b)
		{
		}
		virtual void Slot18(int a)
		{
		}
		virtual void Slot19(int a)
		{
		}
		virtual void Slot20()
		{
		}
		virtual void Slot21(int a)
		{
		}
		virtual void Slot22(int a)
		{
		}

		int unknown4;
		int unknown8;
		OLSFriendEntry* entries;  // +0xC (allocated with new[])
	};
}

#endif
