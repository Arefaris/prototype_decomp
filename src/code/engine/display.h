// engine::Display: the display settings object (0x1127F35C; another unit, names guessed): GetAspectRatio (0x10616740)
// divides the floats at +0x80C and +0x810.
#ifndef ENGINE_DISPLAY_H
#define ENGINE_DISPLAY_H

namespace engine
{
	class Display
	{
	public:
		float GetAspectRatio();
		// 0x10616130 / 0x10616120: the ints at +4 and +8
		int GetUnknown4();
		int GetUnknown8();
	};
	extern Display* gDisplay;
}

#endif
