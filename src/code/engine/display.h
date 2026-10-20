// engine::Display (name guess): the display settings object (0x1127F35C, unit 0x10616xxx, no assert path); member
// names are guesses. GetAspectRatio (0x10616740) divides the floats at +0x80C and +0x810.
#ifndef ENGINE_DISPLAY_H
#define ENGINE_DISPLAY_H

#include "code/pure3d/pddi/dx9/d3d9.h"

namespace engine
{
	class Display
	{
	public:
		// 0x10617A30: the display over a Direct3D object (a 0x834-byte object)
		Display(IDirect3D9* direct3D);
		// 0x10617BF0: lets go of the device and the pool
		~Display();
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
		// 0x10616BB0: resets the device with the display's parameters and makes the pool's resources again
		void Unknown10616BB0();
		// 0x106182C0: makes the device (or resets the one there is) from the display's settings; the answer is
		// whether there is a device afterwards. The argument, when there is one, is handed to 0x106174D0 first.
		bool Unknown106182C0(void* unknown);
		// 0x106160D0, 0x10615FE0, 0x10616660, 0x106174D0, 0x10617560, 0x106180B0: steps of the reset and of the
		// device's creation (names unknown); 0x106180B0 picks the size and the refresh rate of a full-screen mode
		void Unknown106160D0();
		void Unknown10615FE0();
		void Unknown10616660();
		void Unknown106174D0(void* unknown);
		void Unknown10617560();
		void Unknown106180B0(int* width, int* height, unsigned int* refreshRate, unsigned int format);
		// 0x10616C90: the same value three times (the one at +0x10)
		void Unknown10616C90(float a, float b, float c);

		// The window the display lives in
		int unknown0;
		int width;
		int unknown8;
		unsigned char unknownC[4];
		float unknown10;
		unsigned char unknown14[0x20 - 0x14];
		// 0x20: 1 when the display is windowed
		int unknown20;
		unsigned char unknown24[0x2C - 0x24];
		// 0x2C: whether the device waits for the vertical blank
		bool unknown2C;
		unsigned char unknown2D[0x134 - 0x2D];
		int unknown134;
		// 0x138: the Direct3D object, 0x13C: the device it made
		IDirect3D9* d3d;
		IDirect3DDevice9* device;
		// 0x140: the gamma ramp the device had
		unsigned char gammaRamp[0x748 - 0x140];
		// 0x748: the parameters the device is made and reset with
		D3DPRESENT_PARAMETERS presentParameters;
		unsigned char unknown780[0x78D - 0x780];
		// 0x78D / 0x78E: set once the reset is through (names unknown)
		bool unknown78D;
		bool unknown78E;
		// 0x1061CA00 reads it: stretch a texture's levels with a linear filter
		bool unknown78F;
		// 0x790: a device capability bit (DevCaps2, bit 4)
		bool unknown790;
		unsigned char unknown791[3];
		// 0x794 / 0x798: the largest texture the device takes
		unsigned int maxTextureWidth;
		unsigned int maxTextureHeight;
		unsigned char unknown79C[0x828 - 0x79C];
		int unknown828;
		unsigned char unknown82C[0x834 - 0x82C];
	};
	// 0x10616AD0: a step of the reset that takes the device (name unknown)
	void Unknown10616AD0(IDirect3DDevice9* device);

	extern Display* gDisplay;
	// 0x11276D34: the object the back end renders through (0x10617A30 installs it; name guess)
	extern Display* gRenderDisplay;
}

#endif
