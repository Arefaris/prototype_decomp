// engine::OLSProfileProto (RTTI name): the game's own layer of the online services' profile manager (engine::OLSProfile).
// It describes the profile slots of the game from a table in the image and sends the profile messages the base class
// leaves to its platform layer. Names other than the RTTI ones are guesses.
#ifndef PROTO_OLSPROTO_H
#define PROTO_OLSPROTO_H

#include "code/engine/online/ols.h"

namespace engine
{
	class OLSProfileProto : public OLSProfile
	{
	public:
		// 0x104DC8F0: the base keeps four slots and the number of entries given plus seventeen
		explicit OLSProfileProto(int count);
		// 0x104DC970
		virtual ~OLSProfileProto();

		// The platform layer's slots (the base class's are in olsprofile.h)
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3(int a);
		virtual void Slot4(int a, int b, int c, int d, int e);
		virtual void Slot5(int a, int b, int c, int d, int e);
		virtual void Slot6(int a, int b);
		virtual void Slot8(int a, int b);
		virtual void Slot9(int a, int b);
		virtual void Slot10(int a, int b);
		virtual void Slot11(int a, int b);
		virtual void Slot13(int a, int b);
		virtual void Slot14(int a);
		virtual void Slot15(int a, int b);
		virtual void Slot16(int a);
	};
}

#endif
