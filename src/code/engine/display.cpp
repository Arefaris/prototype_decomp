// engine::Display: the display mode object. See display.h for the model; names are guesses.
#include <string.h>

#include "code/engine/display.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/pddi/dx9/dxdefaultpoolmanager.h"

namespace engine
{
	// FUNCTION: ENGINE 0x10616130
	int Display::GetWidth()
	{
		return width;
	}

	// FUNCTION: ENGINE 0x10616BB0
	void Display::Unknown10616BB0()
	{
		Unknown106160D0();
		pure3d::ReleaseDefaultPool();
		device->lpVtbl->Reset(device, &presentParameters);
		if (gD3DDevice->lpVtbl->TestCooperativeLevel(gD3DDevice) >= 0)
		{
			pure3d::RestoreDefaultPool();
			Unknown10615FE0();
			pure3d::gContext->Unknown1061F620(presentParameters.BackBufferWidth, presentParameters.BackBufferHeight);
			pure3d::gContext->Unknown1061F950(0.0f, 0.0f, (float)presentParameters.BackBufferWidth,
				(float)presentParameters.BackBufferHeight);
			width = presentParameters.BackBufferWidth;
			unknown8 = presentParameters.BackBufferHeight;
			Unknown10616660();
			Unknown10616AD0(device);
			unknown78D = true;
			unknown78E = false;
		}
	}

	// FUNCTION: ENGINE 0x106182C0
	// EQUIVALENT: scheduling (97.5 %): the engine stores the largest texture height after the compare of the window
	// mode, this compiler before it (one instruction apart); every call and every value is the same
	bool Display::Unknown106182C0(void* unknown)
	{
		if (unknown != 0)
		{
			Unknown106174D0(unknown);
		}
		Unknown10617560();
		memset(&presentParameters, 0, sizeof(presentParameters));
		D3DCAPS9 caps;
		d3d->lpVtbl->GetDeviceCaps(d3d, 0, 1, &caps);
		// Stored through a reference: the store then stays ahead of the loads of the other capabilities
		bool& stretchFilter = unknown78F;
		stretchFilter = (caps.StretchRectFilterCaps >> 9) & 1;
		unknown790 = (caps.DevCaps2 >> 4) & 1;
		maxTextureWidth = caps.MaxTextureWidth;
		maxTextureHeight = caps.MaxTextureHeight;
		bool fullScreen = unknown20 != 1;
		D3DDISPLAYMODE mode;
		d3d->lpVtbl->GetAdapterDisplayMode(d3d, 0, &mode);
		unsigned int refreshRate;
		if (fullScreen)
		{
			Unknown106180B0(&width, &unknown8, &refreshRate, mode.Format);
		}
		presentParameters.hDeviceWindow = (void*)unknown0;
		presentParameters.Windowed = !fullScreen;
		presentParameters.BackBufferCount = 1;
		presentParameters.MultiSampleType = 0;
		presentParameters.SwapEffect = 1;
		presentParameters.BackBufferWidth = width;
		presentParameters.BackBufferHeight = unknown8;
		presentParameters.BackBufferFormat = mode.Format;
		presentParameters.EnableAutoDepthStencil = 1;
		presentParameters.FullScreen_RefreshRateInHz = fullScreen ? refreshRate : 0;
		presentParameters.AutoDepthStencilFormat = 0x4B;
		presentParameters.PresentationInterval = unknown2C != 0 ? 1 : 0x80000000;
		if (device != 0)
		{
			pure3d::ReleaseDefaultPool();
			device->lpVtbl->Reset(device, &presentParameters);
			unknown78D = true;
		}
		else
		{
			d3d->lpVtbl->CreateDevice(d3d, 0, 1, (void*)unknown0, 0x44, &presentParameters, &device);
			gD3DDevice = device;
			Unknown10615FE0();
			device->lpVtbl->GetGammaRamp(device, 0, gammaRamp);
		}
		Unknown10616C90(unknown10, unknown10, unknown10);
		pure3d::Unknown106256A0(device);
		Unknown10616660();
		unknown828 = unknown134;
		return device != 0;
	}
}
