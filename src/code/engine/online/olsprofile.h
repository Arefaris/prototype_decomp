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

	class OLSProfile
	{
	public:
		virtual ~OLSProfile();
		virtual void Slot1() = 0;
		virtual void Slot2() = 0;
		virtual void Slot3() = 0;
		// vftable slots 4 - 6 (0x10888D20, 0x10888DF0, 0x10888E00): do nothing
		virtual void Slot4(int a, int b, int c, int d, int e);
		virtual void Slot5(int a, int b, int c, int d, int e);
		virtual void Slot6(int a, int b);
		// vftable slot 7 (0x10888E10): makes the profile of the index the current one (-1 for none) and tells the
		// online services
		virtual void SelectProfile(int index);
		virtual void Slot8() = 0;
		virtual void Slot9() = 0;
		virtual void Slot10() = 0;
		virtual void Slot11() = 0;
		// vftable slot 12 (0x10888F00)
		virtual bool Slot12();
		virtual void Slot13() = 0;
		// vftable slots 14 - 16 (0x10889D50, 0x10889D60, 0x10889D70) and 17 - 19 (shared with other classes)
		virtual void Slot14(int a);
		virtual void Slot15(int a);
		virtual void Slot16(int a);
		virtual const char* Slot17();
		virtual void Slot18(int a);
		virtual void Slot19(int a);

		// 0x10888EC0: the user of the profile at the index, null when it has none
		OLSUser* GetUser(unsigned int index);

		unsigned char unknown4[0x14 - 4];
		int currentProfile;  // +0x14
	};
}

#endif
