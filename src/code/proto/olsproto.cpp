// engine::OLSProfileProto: see olsproto.h. Unit 0x104DC8F0 - 0x104DCBF0 (no assert path; the file name is a guess).
#include "code/proto/olsproto.h"

namespace engine
{
	// The description of the game's profile slots (seventeen entries of five words, 0x1109C520)
	extern OLSProfileSlot gProfileSlots[17];

	// FUNCTION: ENGINE 0x104DC8F0
	OLSProfileProto::OLSProfileProto(int count) : OLSProfile(4, count + 0x11)
	{
		for (int i = 0; i < 17; i++)
		{
			SetSlot(i, &gProfileSlots[i]);
		}
	}

	// FUNCTION: ENGINE 0x104DC970
	OLSProfileProto::~OLSProfileProto()
	{
	}

	// FUNCTION: ENGINE 0x104DC980
	void OLSProfileProto::Slot1()
	{
	}

	// FUNCTION: ENGINE 0x104DC990
	void OLSProfileProto::Slot2()
	{
		RegisterMethods();
	}

	// FUNCTION: ENGINE 0x104DCA10
	void OLSProfileProto::Slot3(int a)
	{
	}

	// FUNCTION: ENGINE 0x104DCBA0
	void OLSProfileProto::Slot4(int a, int b, int c, int d, int e)
	{
		OLSProfileMessage message(2);
		message.user = a;
		message.unknownC = 0;
		OLS::Get()->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x104DC9A0
	void OLSProfileProto::Slot5(int a, int b, int c, int d, int e)
	{
		Unknown10889320(a, b, 0, d, 0);
	}

	// FUNCTION: ENGINE 0x104DC9C0
	void OLSProfileProto::Slot6(int a, int b)
	{
		OLSProfileMessage message(1);
		OLS::Get()->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x104DCA30
	void OLSProfileProto::Slot8(int a, int b)
	{
		OLSProfileMessage message(3);
		OLS::Get()->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x104DCA80
	void OLSProfileProto::Slot9(int a, int b)
	{
		OLSProfileMessage message(3);
		message.unknown10 = entries[a].user;
		message.user = a;
		message.unknownC = 0;
		OLS::Get()->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x104DCB00
	void OLSProfileProto::Slot10(int a, int b)
	{
		OLSProfileMessage message(3);
		message.unknown10 = entries[a].user;
		message.user = a;
		message.unknownC = 0;
		OLS::Get()->SendMessage(&message);
	}

	// FUNCTION: ENGINE 0x104DCAF0
	void OLSProfileProto::Slot11(int a, int b)
	{
	}

	// FUNCTION: ENGINE 0x104DCB90
	void OLSProfileProto::Slot13(int a, int b)
	{
	}

	// FUNCTION: ENGINE 0x104DCB70
	void OLSProfileProto::Slot14(int a)
	{
	}

	// FUNCTION: ENGINE 0x104DCB80
	void OLSProfileProto::Slot15(int a, int b)
	{
	}

	// FUNCTION: ENGINE 0x104DCA20
	void OLSProfileProto::Slot16(int a)
	{
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x104DC880
// FUNCTION: ENGINE 0x104DCC50
