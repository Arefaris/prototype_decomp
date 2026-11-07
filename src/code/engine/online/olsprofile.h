// engine::OLSProfile (RTTI name): the online services' profile manager, the OLS singleton's object at +0x78. It
// keeps the profiles the signed-in users picked and which of them is the current one; the platform layers derive from
// it (engine::OLSProfileProto) and implement the pure slots. Of the class only what other units use is declared; the
// vftable has 20 slots. Names other than the RTTI ones are guesses.
#ifndef ENGINE_ONLINE_OLSPROFILE_H
#define ENGINE_ONLINE_OLSPROFILE_H

namespace engine
{
	// A signed-in user (+0xC: the controller the user plays on)
	class OLSUser
	{
	public:
		int unknown0[3];
		unsigned int controller;
	};

	// What the profile manager keeps for one profile slot (0x18 bytes): the user that picked it (-1 for none) and
	// whether the profile is a guest's (names guessed)
	struct OLSProfileEntry
	{
		int unknown0;
		int user;  // +4
		bool guest;  // +8
		unsigned char unknown9[0x18 - 9];
	};

	// What the platform layer describes a profile slot with (five words, kept at OLSProfile +0x1C)
	struct OLSProfileSlot
	{
		int unknown0;
		int unknown4;
		int unknown8;
		int unknownC;
		int unknown10;
	};

	class OLSProfile
	{
	public:
		virtual ~OLSProfile();
		virtual void Slot1() = 0;
		virtual void Slot2() = 0;
		virtual void Slot3(int a) = 0;
		// vftable slots 4 - 6 (0x10888D20, 0x10888DF0, 0x10888E00): do nothing
		virtual void Slot4(int a, int b, int c, int d, int e);
		virtual void Slot5(int a, int b, int c, int d, int e);
		virtual void Slot6(int a, int b);
		// vftable slot 7 (0x10888E10): makes the profile of the index the current one (-1 for none) and tells the
		// online services
		virtual void SelectProfile(int index);
<<<<<<< HEAD
		virtual void Slot8() = 0;
		virtual void Slot9() = 0;
		virtual void Slot10() = 0;
		virtual void Slot11(int profileIndex, int achievementId) = 0;
=======
		virtual void Slot8(int a, int b) = 0;
		virtual void Slot9(int a, int b) = 0;
		virtual void Slot10(int a, int b) = 0;
		virtual void Slot11(int a, int b) = 0;
>>>>>>> sn-by
		// vftable slot 12 (0x10888F00)
		virtual bool Slot12();
		virtual void Slot13(int a, int b) = 0;
		// vftable slots 14 - 16 (0x10889D50, 0x10889D60, 0x10889D70) and 17 - 19 (0x104DC940, 0x104DC950, 0x104DC960)
		virtual void Slot14(int a);
		virtual void Slot15(int a, int b);
		virtual void Slot16(int a);
		virtual const char* Slot17();
		virtual void Slot18(int a);
		virtual void Slot19(int a);

		// The base class's constructor (0x10889C50): the number of profile slots and of entries
		OLSProfile(int newSlotCount, int newEntryCount);
		// 0x10888CD0: copies the description of the profile slot (five words) into the table of the entries' description
		void SetSlot(int index, const OLSProfileSlot* slot);
		// 0x1088A050: registers the script methods of the profile manager
		void RegisterMethods();
		// 0x10889320: the base form of the fifth slot; the platform layer calls it with two arguments cleared
		void Unknown10889320(int a, int b, int c, int d, int e);

		// 0x10888EC0: the user of the profile at the index, null when it has none
		OLSUser* GetUser(unsigned int index);

		int profileCount;  // +4
		unsigned char unknown8[0x14 - 8];
		int currentProfile;  // +0x14
		OLSProfileEntry* entries;  // +0x18
		OLSProfileSlot* slots;  // +0x1C
		unsigned char unknown20[0x124 - 0x20];
	};
}

#endif
