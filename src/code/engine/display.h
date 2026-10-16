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
		// 0x10616190: the int at +0x28 (the sample count the surfaces of the device are made with)
		int GetUnknown28();

		int unknown0;
		int width;
		int unknown8;
		unsigned char unknownC[0x78F - 0xC];
		// 0x1061CA00 reads it: stretch a texture's levels with a linear filter
		bool unknown78F;
	};
	extern Display* gDisplay;
	// 0x11276D34: the object the back end renders through (0x10617A30 installs it; name guess)
	extern Display* gRenderDisplay;
}

#endif
