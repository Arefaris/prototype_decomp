// engine::Display (name guess): the display settings object (0x1127F35C, unit 0x10616xxx, no assert path); member
// names are guesses. GetAspectRatio (0x10616740) divides the floats at +0x80C and +0x810.
#ifndef ENGINE_DISPLAY_H
#define ENGINE_DISPLAY_H

namespace engine
{
	class Display
	{
	public:
		float GetAspectRatio();
		// 0x10616130
		int GetWidth();
		// 0x10616120: the int at +8
		int GetUnknown8();

		int unknown0;
		int width;
		int unknown8;
	};
	extern Display* gDisplay;
}

#endif
