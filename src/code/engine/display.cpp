// engine::Display: the display mode object. See display.h for the model; names are guesses.
#include <string.h>

#include "code/engine/display.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/pddi/dx9/dxdefaultpoolmanager.h"

namespace engine
{
	// FUNCTION: ENGINE 0x10615FA0
	// EQUIVALENT: the engine keeps the constant 1 in a register for the test of the window mode and the flag it sets, this compiler uses immediates, 12.2 %
	void Display::OnSize(void* window, unsigned int message, unsigned int wParam, long lParam)
	{
		if (message == 5 && unknown20 == 1)
		{
			unsigned int newWidth = lParam & 0xFFFF;
			unsigned int newHeight = (unsigned int)lParam >> 16;
			presentParameters.BackBufferWidth = newWidth;
			presentParameters.BackBufferHeight = newHeight;
			if (newWidth > 0)
			{
				unknown78E = true;
			}
		}
	}

	// FUNCTION: ENGINE 0x10615FE0
	void Display::Unknown10615FE0()
	{
		device->lpVtbl->GetBackBuffer(device, 0, 0, 0, &backBuffer);
		device->lpVtbl->GetDepthStencilSurface(device, &depthStencil);
		pure3d::dxSurface* surface = new pure3d::dxSurface();
		surface->SetSurface(depthStencil);
		backBufferTexture->SetSurface(surface);
	}

	// FUNCTION: ENGINE 0x10616050
	void Display::Unknown10616050()
	{
		device->lpVtbl->SetRenderTarget(device, 0, backBuffer);
		device->lpVtbl->SetRenderTarget(device, 1, 0);
		device->lpVtbl->SetRenderTarget(device, 2, 0);
		device->lpVtbl->SetRenderTarget(device, 3, 0);
		device->lpVtbl->SetDepthStencilSurface(device, depthStencil);
	}

	// FUNCTION: ENGINE 0x106160D0
	void Display::Unknown106160D0()
	{
		if (backBuffer != 0)
		{
			backBuffer->Release();
			backBuffer = 0;
		}
		if (depthStencil != 0)
		{
			depthStencil->Release();
			depthStencil = 0;
		}
		backBufferTexture->SetSurface(0);
	}

	// FUNCTION: ENGINE 0x10616120
	int Display::GetUnknown8()
	{
		return unknown8;
	}

	// FUNCTION: ENGINE 0x10616130
	int Display::GetWidth()
	{
		return width;
	}

	// FUNCTION: ENGINE 0x10616190
	int Display::GetUnknown28()
	{
		return unknown28;
	}

	// FUNCTION: ENGINE 0x106162D0
	void Display::Unknown106162D0()
	{
		if (!unknown78E)
		{
			if (unknown78D)
			{
				unknown78D = false;
				return;
			}
			device->lpVtbl->Present(device, 0, 0, 0, 0);
			if (!unknown2D)
			{
				pure3d::gContext->Unknown68();
			}
		}
	}

	// FUNCTION: ENGINE 0x10616660
	void Display::Unknown10616660()
	{
		unknown7FC += 1;
		float one = 1.0f;
		unknown800 = one;
		unknown804 = one;
		if (unknown791 == 0)
		{
			unknown808 = (float)GetUnknown8() / (float)GetWidth();
		}
		else
		{
			unknown808 = (float)pure3d::gContext->targetHeight / (float)pure3d::gContext->targetWidth;
		}
		float ratio = unknown808;
		unknown80C = one;
		unknown810 = ratio;
		unknown814 = one;
		unknown818 = ratio;
		unknown81C = one;
		unknown820 = ratio;
	}

	// FUNCTION: ENGINE 0x10616AD0
	void Unknown10616AD0(IDirect3DDevice9* device)
	{
		for (unsigned int sampler = 0; sampler < 4; sampler++)
		{
			for (unsigned int state = 0; state < 0x50; state++)
			{
				int value = pure3d::gRenderStateCache->samplerStates[sampler][state];
				if (value != -1)
				{
					device->lpVtbl->SetSamplerState(device, sampler + 0x101, state, value);
				}
			}
		}
		for (unsigned int sampler = 0; sampler < 16; sampler++)
		{
			for (unsigned int state = 0; state < 0x50; state++)
			{
				int value = pure3d::gRenderStateCache->samplerStates[sampler + 4][state];
				if (value != -1)
				{
					device->lpVtbl->SetSamplerState(device, sampler, state, value);
				}
			}
		}
		for (unsigned int state = 0; state < 400; state++)
		{
			int value = pure3d::gRenderStateCache->renderStates[state];
			if (value != -1)
			{
				device->lpVtbl->SetRenderState(device, state, value);
			}
		}
		pure3d::gRenderStateCache->vertexPass += 1;
		pure3d::gRenderStateCache->pixelPass += 1;
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
	// mode, this compiler before it (one instruction apart); every call and every value is the same.
	// About 1700 compilations did not move it: every order of the capability stores and of the window-mode test (with
	// and without the reference for the first store), references or locals for the stores and the capability words,
	// the type of the window-mode flag and the place of the display-mode local (97.7 % at best, with another
	// instruction displaced). The two bits as mask tests (`(caps & 0x200) != 0`), a compiler barrier after every
	// statement of the body and every order of the present parameters' stores leave it at 97.5 %.
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
