// engine::Display: the display mode object. See display.h for the model; names are guesses.
#include <new>
#include <string.h>

#include "code/engine/display.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/pddi/dx9/dxdefaultpoolmanager.h"
#include "code/pure3d/pddi/dx9/dxtexture.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10615F20
	dxContext* GetContext()
	{
		return gContext;
	}

	// FUNCTION: ENGINE 0x1061B440
	void SetCurrentDevice(dxDevice* device)
	{
		gCurrentDevice = device;
	}

	// FUNCTION: ENGINE 0x1061F1C0
	void SetContext(dxContext* context)
	{
		gContext = context;
	}

	// FUNCTION: ENGINE 0x10615F40
	void SetD3DDevice(IDirect3DDevice9* device)
	{
		gD3DDevice = device;
	}

	// FUNCTION: ENGINE 0x10615F50
	IDirect3DDevice9* GetD3DDevice()
	{
		return gD3DDevice;
	}

	// FUNCTION: ENGINE 0x10615F80
	void NextVertexConstantPass()
	{
		gRenderStateCache->vertexPass += 1;
	}

	// FUNCTION: ENGINE 0x10615F90
	void NextPixelConstantPass()
	{
		gRenderStateCache->pixelPass += 1;
	}
}

namespace engine
{
	// The back buffer formats the modes are listed for (0x110BB574: A1R5G5B5, A2R10G10B10, A8R8G8B8, R5G6B5,
	// X1R5G5B5, X8R8G8B8)
	static unsigned int sBackBufferFormats[6] = {0x19, 0x23, 0x15, 0x17, 0x18, 0x16};

	// FUNCTION: ENGINE 0x10615F30
	void SetRenderDisplay(Display* display)
	{
		gRenderDisplay = display;
	}

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

	// FUNCTION: ENGINE 0x10616320
	void Display::GetGamma(float* a, float* b, float* c)
	{
		*a = gamma.values[0];
		*b = gamma.values[1];
		*c = gamma.values[2];
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

	// FUNCTION: ENGINE 0x10616140
	int Display::GetUnknown10616140()
	{
		return 0x20;
	}

	// FUNCTION: ENGINE 0x10616150
	int Display::GetUnknown20()
	{
		return unknown20;
	}

	// FUNCTION: ENGINE 0x10616160
	IDirect3D9* Display::GetDirect3D()
	{
		return d3d;
	}

	// FUNCTION: ENGINE 0x10616170
	IDirect3DDevice9* Display::GetDevice()
	{
		return device;
	}

	// FUNCTION: ENGINE 0x10616180
	bool Display::GetUnknown78C()
	{
		return unknown78C;
	}

	// FUNCTION: ENGINE 0x106161A0
	int Display::Unknown106161A0()
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x10616720
	int* Display::GetUnknown7FC()
	{
		return &unknown7FC;
	}

	// FUNCTION: ENGINE 0x10616730
	float Display::GetUnknown800()
	{
		return unknown800;
	}

	// FUNCTION: ENGINE 0x10616740
	float Display::GetAspectRatio()
	{
		return unknown80C / unknown810;
	}

	// FUNCTION: ENGINE 0x10616750
	float Display::GetUnknown804Ratio()
	{
		return unknown804 / unknown808;
	}

	// FUNCTION: ENGINE 0x10616760
	pure3d::dxTexture* Display::GetBackBufferTexture()
	{
		return backBufferTexture;
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
		presentParameters.hDeviceWindow = (void*)window;
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
			d3d->lpVtbl->CreateDevice(d3d, 0, 1, (void*)window, 0x44, &presentParameters, &device);
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

namespace pure3d
{
	// FUNCTION: ENGINE 0x106179B0
	DisplaySettings::DisplaySettings()
	{
		width = 0x280;
		unknown8 = 0x1E0;
		unknownC = 0x20;
		unknown10 = 1.0f;
		unknown18 = 7;
		unknown14 = 2;
		unknown28 = 0;
		unknown2C = false;
		unknown2D = true;
		unknown2E = false;
		unknown2F = true;
		unknown1C = 8;
		unknown20 = 1;
		unknown24 = false;
		unknown134 = 0;
	}
}

namespace engine
{
	// FUNCTION: ENGINE 0x10617A30
	Display::Display(IDirect3D9* direct3D)
		: d3d(direct3D), device(0), unknown78D(false), unknown78E(false), unknown78F(false), unknown790(false),
		unknown791(false), maxTextureWidth(0), maxTextureHeight(0), unknown7FC(0), unknown800(1.0f),
		unknown804(1.0f), unknown808(1.0f), unknown80C(1.0f), unknown810(1.0f), unknown814(1.0f),
		unknown818(1.0f), unknown81C(1.0f), unknown820(1.0f), unknown824(false), unknown828(0),
		backBufferTexture(0), unknown830(false)
	{
		pure3d::CreateRenderStateCache();
		gRenderDisplay = this;
		for (int i = 0; i < 6; i++)
		{
			blocks[i].Create(0x1000);
		}
		unknown78C = false;
		width = 0;
		unknown8 = 0;
		backBufferTexture = new pure3d::dxTexture(0);
		backBufferTexture->AddRef();
	}

	// FUNCTION: ENGINE 0x10617BF0
	// NONMATCHING: scheduling: the engine loads the first two cursors' blocks before it stores the first, ours loads three ahead, best 90.0%
#ifdef NONMATCHING
	Display::~Display()
	{
		pure3d::ShutdownDefaultPool();
		Unknown106160D0();
		if (backBufferTexture != 0)
		{
			backBufferTexture->Release();
		}
		pure3d::DestroyRenderStateCache();
		if (device != 0)
		{
			device->lpVtbl->Release(device);
			device = 0;
			gD3DDevice = 0;
		}
		blocks[0].cursor = blocks[0].begin;
		blocks[1].cursor = blocks[1].begin;
		blocks[2].cursor = blocks[2].begin;
		blocks[3].cursor = blocks[3].begin;
		blocks[4].cursor = blocks[4].begin;
		blocks[5].cursor = blocks[5].begin;
	}
#endif
}

namespace engine
{
	// FUNCTION: ENGINE 0x106164B0
	int Display::GetFormatIndex(unsigned int format)
	{
		int result = -1;
		for (unsigned int i = 0; i < 6; i++)
		{
			if (sBackBufferFormats[i] == format)
			{
				result = i;
				break;
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10616500
	Display::Block* Display::GetModeList(unsigned int format)
	{
		int index = -1;
		for (unsigned int i = 0; i < 6; i++)
		{
			if (sBackBufferFormats[i] == format)
			{
				index = i;
				break;
			}
		}
		return &blocks[index];
	}

	// FUNCTION: ENGINE 0x10616540
	bool Display::Unknown10616540()
	{
		HRESULT result = gD3DDevice->lpVtbl->TestCooperativeLevel(gD3DDevice);
		if (result < 0)
		{
			if (result == (HRESULT)0x88760869)
			{
				return true;
			}
		}
		else if (unknown78E && !unknown824)
		{
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10616580
	bool Display::Unknown10616580(int multiSampleType)
	{
		if (multiSampleType != 0)
		{
			HRESULT colour = d3d->lpVtbl->CheckDeviceMultiSampleType(d3d, 0, 1, (D3DFORMAT)0x15, unknown20 == 1,
				(D3DMULTISAMPLE_TYPE)multiSampleType, 0);
			HRESULT depth = d3d->lpVtbl->CheckDeviceMultiSampleType(d3d, 0, 1, (D3DFORMAT)0x71, unknown20 == 1,
				(D3DMULTISAMPLE_TYPE)multiSampleType, 0);
			if (colour < 0 || depth < 0)
			{
				return false;
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x10616620
	bool Display::Unknown10616620(int mode)
	{
		bool taken = Unknown10616580(pure3d::GetMultiSampleType(mode));
		if (taken)
		{
			unknown28 = mode;
			presentParameters.MultiSampleType = (D3DMULTISAMPLE_TYPE)0;
			unknown78E = true;
		}
		return taken;
	}
}
