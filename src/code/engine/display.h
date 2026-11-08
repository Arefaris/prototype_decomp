// engine::Display (name guess): the display settings object (0x1127F35C, unit 0x10616xxx, no assert path); member
// names are guesses. GetAspectRatio (0x10616740) divides the floats at +0x80C and +0x810.
#ifndef ENGINE_DISPLAY_H
#define ENGINE_DISPLAY_H

#include "code/pure3d/displaysettings.h"
#include "code/pure3d/pddi/dx9/d3d9.h"

namespace pure3d
{
	class dxTexture;
}

namespace engine
{
	class Display : public pure3d::DisplaySettings
	{
	public:
		// 0x10617A30: the display over a Direct3D object (a 0x834-byte object)
		Display(IDirect3D9* direct3D);
		// 0x10617BF0: lets go of the device and the pool
		~Display();
		float GetAspectRatio();
		// 0x10616130
		int GetWidth();
		// 0x10616140: 32 (the depth of the colour); 0x10616150: the int at +0x20 (1 when windowed)
		int GetUnknown10616140();
		int GetUnknown20();
		// 0x10616160 / 0x10616170: the Direct3D object and the device it made
		IDirect3D9* GetDirect3D();
		IDirect3DDevice9* GetDevice();
		// 0x1061C010: the filter the levels of a texture are stretched with (D3DTEXF_LINEAR when the device does it, else
		// D3DTEXF_POINT)
		int GetStretchFilter();
		// 0x10616180: the byte at +0x78C; 0x106161A0 answers 0
		bool GetUnknown78C();
		int Unknown106161A0();
		// 0x10616720 / 0x10616730 / 0x10616750 / 0x10616760: the counter at +0x7FC, the float at +0x800, the float at
		// +0x804 over the one at +0x808, the texture of the back buffer
		int* GetUnknown7FC();
		float GetUnknown800();
		float GetUnknown804Ratio();
		pure3d::dxTexture* GetBackBufferTexture();
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
		// 0x10616050: sets the back buffer and the depth buffer as the device's targets (name unknown)
		void Unknown10616050();
		// 0x106182C0: makes the device (or resets the one there is) from the display's settings; the answer is
		// whether there is a device afterwards. The argument, when there is one, is handed to 0x106174D0 first.
		bool Unknown106182C0(void* unknown);
		// 0x106160D0, 0x10615FE0, 0x10616660, 0x10617560, 0x106180B0: steps of the reset and of the
		// device's creation (names unknown); 0x106180B0 picks the size and the refresh rate of a full-screen mode
		void Unknown106160D0();
		void Unknown10615FE0();
		void Unknown10616660();
		void Unknown10617560();
		void Unknown106180B0(int* width, int* height, unsigned int* refreshRate, unsigned int format);
		// 0x106164B0: the place of a back buffer format among the six the modes are listed for, -1 for none
		int GetFormatIndex(unsigned int format);
		// 0x10616500: the list of modes of that format (the one before the first when it is none of the six)
		struct Block;
		Block* GetModeList(unsigned int format);
		// 0x10616EA0: whether any mode was listed for the back buffer format
		bool Unknown10616EA0(unsigned int format);
		// 0x10616EE0: whether the size is one of the sizes the display takes
		bool Unknown10616EE0(unsigned int width, unsigned int height);
		// 0x10616F20: whether a mode of that size is listed for the format and the size is one the display takes
		bool Unknown10616F20(unsigned int width, unsigned int height, unsigned int format);
		// 0x10616540: whether the device is lost for good and has to be reset, or the window was resized
		bool Unknown10616540();
		// 0x10616580: whether the device takes the multisample type with the two formats of the back buffer
		bool Unknown10616580(int multiSampleType);
		// 0x10616620: takes the multisample mode when the device takes its type
		bool Unknown10616620(int mode);
		// 0x10616320: the three gamma values Unknown10616C90 was given
		void GetGamma(float* a, float* b, float* c);
		// 0x10616C90: the same value three times (the one at +0x10)
		void Unknown10616C90(float a, float b, float c);

		// 0x138: the Direct3D object, 0x13C: the device it made
		IDirect3D9* d3d;
		IDirect3DDevice9* device;
		// 0x140: the gamma ramp the device had
		unsigned char gammaRamp[0x740 - 0x140];
		// 0x740 / 0x744: the back buffer and the depth buffer the device made
		IDirect3DSurface9* backBuffer;
		IDirect3DSurface9* depthStencil;
		// 0x748: the parameters the device is made and reset with
		D3DPRESENT_PARAMETERS presentParameters;
		struct Gamma
		{
			Gamma()
			{
				values[0] = 1.0f;
				values[1] = 1.0f;
				values[2] = 1.0f;
			}

			float values[3];
		};
		Gamma gamma;
		bool unknown78C;
		// 0x78D / 0x78E: set once the reset is through (names unknown)
		bool unknown78D;
		bool unknown78E;
		// 0x1061CA00 reads it: stretch a texture's levels with a linear filter
		bool unknown78F;
		// 0x790: a device capability bit (DevCaps2, bit 4)
		bool unknown790;
		bool unknown791;
		unsigned char unknown792[2];
		// 0x794 / 0x798: the largest texture the device takes
		unsigned int maxTextureWidth;
		unsigned int maxTextureHeight;
		// 0x79C: the display modes (D3DDISPLAYMODE) of each of the six back buffer formats (names guessed)
		struct Block
		{
			Block()
			{
				begin = 0;
				cursor = 0;
				end = 0;
			}
			// makes the room for that many bytes
			void Create(unsigned int size)
			{
				begin = new char[size];
				if (begin != 0)
				{
					cursor = begin;
					end = begin + size;
					return;
				}
				cursor = 0;
				end = 0;
			}
			~Block()
			{
				cursor = begin;
				if (begin != 0)
				{
					delete[] begin;
				}
			}

			char* begin;
			char* cursor;
			char* end;
			int unknownC;
		};
		Block blocks[6];
		// 0x7FC: counts the mode changes; 0x800 - 0x820: the ratios of the screen's shape (0x808 is the height over
		// the width, the rest are ones and that ratio again)
		int unknown7FC;
		float unknown800;
		float unknown804;
		float unknown808;
		float unknown80C;
		float unknown810;
		float unknown814;
		float unknown818;
		float unknown81C;
		float unknown820;
		bool unknown824;
		int unknown828;
		// 0x82C: the texture that stands for the back buffer
		pure3d::dxTexture* backBufferTexture;
		bool unknown830;
	};
	// 0x10616AD0: a step of the reset that takes the device (name unknown)
	void Unknown10616AD0(IDirect3DDevice9* device);

	extern Display* gDisplay;
	// 0x11276D34: the object the back end renders through (0x10617A30 installs it; name guess)
	extern Display* gRenderDisplay;
	// 0x10615F30
	void SetRenderDisplay(Display* display);
}

#endif
