// The in-game heads-up display (the members the fight actions call; the class is larger).
#ifndef PROTO_FRONTENDHUD_H
#define PROTO_FRONTENDHUD_H

namespace proto
{
	class FrontEndHud
	{
	public:
		// 0x104B1110: hides the elements of a mask (name guess)
		void HideElements(int mask);
		// 0x104B10D0: shows the elements of a mask (name guess)
		void ShowElements(int mask);
		// 0x104B1090: shows or hides the whole display (name guess)
		void SetVisible(bool visible);
	};

	// 0x104B0A00
	FrontEndHud* GetFrontEndHud();
}

#endif
