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
		// 0x106162D0: puts the display's state back (called around the render device's frame calls)
		void Unknown106162D0();
		// 0x10615FA0: takes the size of a WM_SIZE message (the message must be 5 and the flag at +0x20 set)
		void OnSize(void* window, unsigned int message, unsigned int wParam, long lParam);

		int unknown0;
		int width;
		int unknown8;
	};
	extern Display* gDisplay;
}

#endif
