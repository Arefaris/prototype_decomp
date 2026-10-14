// d3d9.dll proxy for the original game (tools/re). Placed next to prototypef.exe it
// forwards Direct3DCreate9 to the system d3d9.dll and changes how the game's frames are presented; the game's code
// is untouched.
//   - The device is created windowed, in a movable window whose client area matches the back buffer
//     (opprobe_d3d9.ini: [proxy] windowed=0 keeps the game's own mode and window, e.g. on a handheld).
//   - The window keeps receiving "active" messages when it loses focus, so the game does not pause while it is
//     observed (opprobe_d3d9.ini in the game folder: [proxy] keepActive=0 turns this off).
//   - Screenshots straight from the back buffer: tools/re/opprobe.py writes the output path to
//     opprobe_shot.request in the game folder; the next frame is saved there as a BMP and the request is removed.
//     Every draw of that frame is recorded next to it (<path>.frame): vertex and pixel shader constants, shader
//     hashes, bound textures, blend and depth state and the render target, so the camera and the inputs of each
//     pixel shader can be recovered from what the game hands to Direct3D. Every render
//     target of that frame is saved as well each time the game switches away from it (<path>.rt<id>.bin: raw
//     texels, the last state wins), and every small texture (up to 256 x 256) it samples (<path>.tex<id>.dds).
//   - Control of the game (gamecontrol.cpp): requests in opprobe_cmd.request run Lua in the
//     game's script state, set the chase camera, and feed keys and mouse to its DirectInput devices.
#define CINTERFACE
#include <windows.h>
#include <d3d9.h>

#include "gamecontrol.hpp"

#include <cstdarg>
#include <cstdio>
#include <map>
#include <vector>

void proxyLog(const char* format, ...)
{
	// Shared for reading, so the log can be looked at while the game runs; two threads write to it
	static CRITICAL_SECTION lock;
	static FILE* file = nullptr;
	static const bool ready = (InitializeCriticalSection(&lock), true);
	(void)ready;
	EnterCriticalSection(&lock);
	if (file != nullptr || (file = _fsopen("opprobe_d3d9.log", "w", _SH_DENYWR)) != nullptr)
	{
		va_list args;
		va_start(args, format);
		vfprintf(file, format, args);
		va_end(args);
		fputc('\n', file);
		fflush(file);
	}
	LeaveCriticalSection(&lock);
}

namespace
{
	using CreateFunction = IDirect3D9*(WINAPI*)(UINT);
	using CreateDeviceFunction = HRESULT(STDMETHODCALLTYPE*)(IDirect3D9*, UINT, D3DDEVTYPE, HWND, DWORD, D3DPRESENT_PARAMETERS*,
		IDirect3DDevice9**);
	using ResetFunction = HRESULT(STDMETHODCALLTYPE*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
	using PresentFunction = HRESULT(STDMETHODCALLTYPE*)(IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*);
	using SetConstantsFunction = HRESULT(STDMETHODCALLTYPE*)(IDirect3DDevice9*, UINT, const float*, UINT);
	using DrawIndexedFunction = HRESULT(STDMETHODCALLTYPE*)(IDirect3DDevice9*, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT);
	using DrawFunction = HRESULT(STDMETHODCALLTYPE*)(IDirect3DDevice9*, D3DPRIMITIVETYPE, UINT, UINT);
	using DrawUpFunction = HRESULT(STDMETHODCALLTYPE*)(IDirect3DDevice9*, D3DPRIMITIVETYPE, UINT, const void*, UINT);
	using SetTextureFunction = HRESULT(STDMETHODCALLTYPE*)(IDirect3DDevice9*, DWORD, IDirect3DBaseTexture9*);
	using SetRenderStateFunction = HRESULT(STDMETHODCALLTYPE*)(IDirect3DDevice9*, D3DRENDERSTATETYPE, DWORD);
	using SetSamplerStateFunction = HRESULT(STDMETHODCALLTYPE*)(IDirect3DDevice9*, DWORD, D3DSAMPLERSTATETYPE, DWORD);
	using SetVertexShaderFunction = HRESULT(STDMETHODCALLTYPE*)(IDirect3DDevice9*, IDirect3DVertexShader9*);
	using SetPixelShaderFunction = HRESULT(STDMETHODCALLTYPE*)(IDirect3DDevice9*, IDirect3DPixelShader9*);
	using SetRenderTargetFunction = HRESULT(STDMETHODCALLTYPE*)(IDirect3DDevice9*, DWORD, IDirect3DSurface9*);
	using SetViewportFunction = HRESULT(STDMETHODCALLTYPE*)(IDirect3DDevice9*, const D3DVIEWPORT9*);

	// What is recorded per draw of the captured frame
	constexpr UINT VS_REGISTERS = 96;
	constexpr UINT PS_REGISTERS = 64;
	constexpr UINT STAGES = 8;
	constexpr std::size_t RECORDED_DRAWS = 20000;
	// Render states kept per draw, in this order
	constexpr D3DRENDERSTATETYPE RECORDED_STATES[] = {D3DRS_ALPHABLENDENABLE, D3DRS_SRCBLEND, D3DRS_DESTBLEND, D3DRS_BLENDOP,
		D3DRS_ZENABLE, D3DRS_ZWRITEENABLE, D3DRS_ZFUNC, D3DRS_CULLMODE, D3DRS_ALPHATESTENABLE, D3DRS_ALPHAREF, D3DRS_SRGBWRITEENABLE,
		D3DRS_COLORWRITEENABLE, D3DRS_SEPARATEALPHABLENDENABLE, D3DRS_SRCBLENDALPHA, D3DRS_DESTBLENDALPHA, D3DRS_STENCILENABLE};
	constexpr UINT STATE_COUNT = UINT(sizeof(RECORDED_STATES) / sizeof(RECORDED_STATES[0]));

	struct TextureInfo
	{
		UINT id = 0;      // order of first use in the captured frame (0: none)
		UINT width = 0;
		UINT height = 0;  // 0 for a cube map
		UINT format = 0;
		UINT srgb = 0;    // D3DSAMP_SRGBTEXTURE of the stage
	};

	struct DrawRecord
	{
		UINT kind = 0;    // 0 indexed, 1 non-indexed, 2 from user memory
		UINT primitiveType = 0;
		UINT primitives = 0;
		UINT vertices = 0;
		UINT vertexShader = 0;   // FNV-1a of the shader bytecode (0: fixed function)
		UINT pixelShader = 0;
		UINT targetWidth = 0;
		UINT targetHeight = 0;
		UINT targetFormat = 0;
		UINT targetId = 0;
		UINT viewport[4] {};     // x, y, width, height
		UINT states[STATE_COUNT] {};
		TextureInfo textures[STAGES] {};
		float vsConstants[VS_REGISTERS][4] {};
		float psConstants[PS_REGISTERS][4] {};
	};

	const char* REQUEST_FILE = "opprobe_shot.request";

	CreateDeviceFunction realCreateDevice = nullptr;
	ResetFunction realReset = nullptr;
	PresentFunction realPresent = nullptr;
	SetConstantsFunction realSetConstants = nullptr;
	SetConstantsFunction realSetPsConstants = nullptr;
	DrawIndexedFunction realDrawIndexed = nullptr;
	DrawFunction realDraw = nullptr;
	DrawUpFunction realDrawUp = nullptr;
	SetTextureFunction realSetTexture = nullptr;
	SetRenderStateFunction realSetRenderState = nullptr;
	SetSamplerStateFunction realSetSamplerState = nullptr;
	SetVertexShaderFunction realSetVertexShader = nullptr;
	SetPixelShaderFunction realSetPixelShader = nullptr;
	SetRenderTargetFunction realSetRenderTarget = nullptr;
	SetViewportFunction realSetViewport = nullptr;
	D3DVIEWPORT9 currentViewport {};
	std::map<const void*, bool> savedTextures;

	float shaderConstants[256][4] {};
	float pixelConstants[256][4] {};
	IDirect3DBaseTexture9* boundTextures[STAGES] {};
	DWORD samplerSrgb[STAGES] {};
	DWORD renderStates[256] {};
	IDirect3DVertexShader9* vertexShader = nullptr;
	IDirect3DPixelShader9* pixelShader = nullptr;
	IDirect3DSurface9* renderTarget = nullptr;
	std::map<const void*, UINT> shaderHashes;
	std::map<const void*, UINT> resourceIds;

	bool recording = false;
	char capturePath[MAX_PATH] {};
	std::vector<DrawRecord> draws;
	WNDPROC realWindowProc = nullptr;
	HWND gameWindow = nullptr;
	unsigned frame = 0;

	template <typename... Arguments>
	void log(const char* format, Arguments... arguments)
	{
		proxyLog(format, arguments...);
	}

	bool option(const wchar_t* name, int fallback)
	{
		wchar_t path[MAX_PATH];
		GetFullPathNameW(L"opprobe_d3d9.ini", MAX_PATH, path, nullptr);
		return GetPrivateProfileIntW(L"proxy", name, fallback, path) != 0;
	}

	// Vtables of Direct3D objects live in read-only memory of the system DLL
	template <typename Function>
	void patch(Function* slot, Function hook, Function& original)
	{
		DWORD protection = 0;
		VirtualProtect(slot, sizeof(*slot), PAGE_EXECUTE_READWRITE, &protection);
		original = *slot;
		*slot = hook;
		VirtualProtect(slot, sizeof(*slot), protection, &protection);
	}

	bool keepActiveOption = true;

	// Deactivation messages are turned into activation, so the game keeps simulating and rendering in the background.
	// The procedure also serves the control requests, on the game's main thread.
	LRESULT CALLBACK windowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (gamecontrol::onMessage(window, message))
			return 0;
		switch (keepActiveOption ? message : 0u)
		{
			case WM_ACTIVATEAPP:
				wParam = TRUE;
				break;
			case WM_ACTIVATE:
				wParam = MAKEWPARAM(WA_ACTIVE, 0);
				break;
			case WM_NCACTIVATE:
				wParam = TRUE;
				break;
			case WM_KILLFOCUS:
				return 0;
			default:
				break;
		}
		return IsWindowUnicode(window) ? CallWindowProcW(realWindowProc, window, message, wParam, lParam)
									   : CallWindowProcA(realWindowProc, window, message, wParam, lParam);
	}

	void keepActive(HWND window)
	{
		if (window == nullptr || realWindowProc != nullptr)
			return;
		keepActiveOption = option(L"keepActive", 1);
		realWindowProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&windowProc)));
		log("keepActive %d: window procedure %p replaced", int(keepActiveOption), reinterpret_cast<void*>(realWindowProc));
		gamecontrol::attach(window);
	}

	void makeWindowed(D3DPRESENT_PARAMETERS* parameters, HWND window)
	{
		if (parameters == nullptr)
			return;
		log("present parameters: %ux%u format %u windowed %d refresh %u", parameters->BackBufferWidth, parameters->BackBufferHeight,
			parameters->BackBufferFormat, parameters->Windowed, parameters->FullScreen_RefreshRateInHz);
		// [proxy] windowed=0 leaves the game's own display mode and window alone (handhelds, where the game owns the screen)
		if (!option(L"windowed", 1))
			return;
		parameters->Windowed = TRUE;
		parameters->FullScreen_RefreshRateInHz = 0;
		if (window == nullptr || parameters->BackBufferWidth == 0)
			return;
		// A window with a caption, so it can be moved to another monitor
		const LONG style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		SetWindowLongW(window, GWL_STYLE, style | WS_VISIBLE);
		SetWindowLongW(window, GWL_EXSTYLE, 0);
		RECT bounds {0, 0, LONG(parameters->BackBufferWidth), LONG(parameters->BackBufferHeight)};
		AdjustWindowRect(&bounds, style, FALSE);
		SetWindowPos(window, HWND_NOTOPMOST, 40, 40, bounds.right - bounds.left, bounds.bottom - bounds.top, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
	}

	// 24-bit bottom-up BMP from 32-bit BGRA rows
	bool writeBmp(const char* path, const unsigned char* pixels, int pitch, int width, int height)
	{
		FILE* file = nullptr;
		if (fopen_s(&file, path, "wb") != 0)
			return false;
		const int rowBytes = (width * 3 + 3) & ~3;
		BITMAPFILEHEADER header {};
		BITMAPINFOHEADER info {};
		header.bfType = 0x4D42;
		header.bfOffBits = sizeof(header) + sizeof(info);
		header.bfSize = header.bfOffBits + DWORD(rowBytes) * DWORD(height);
		info.biSize = sizeof(info);
		info.biWidth = width;
		info.biHeight = height;
		info.biPlanes = 1;
		info.biBitCount = 24;
		fwrite(&header, sizeof(header), 1, file);
		fwrite(&info, sizeof(info), 1, file);
		std::vector<unsigned char> row(std::size_t(rowBytes), 0);
		for (int y = height - 1; y >= 0; --y)
		{
			const unsigned char* source = pixels + std::size_t(y) * std::size_t(pitch);
			for (int x = 0; x < width; ++x)
			{
				row[std::size_t(x) * 3 + 0] = source[x * 4 + 0];
				row[std::size_t(x) * 3 + 1] = source[x * 4 + 1];
				row[std::size_t(x) * 3 + 2] = source[x * 4 + 2];
			}
			fwrite(row.data(), 1, row.size(), file);
		}
		fclose(file);
		return true;
	}

	void saveBackBuffer(IDirect3DDevice9* device, const char* path)
	{
		IDirect3DSurface9* backBuffer = nullptr;
		if (FAILED(device->lpVtbl->GetBackBuffer(device, 0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer)))
			return log("screenshot: no back buffer");
		D3DSURFACE_DESC description {};
		backBuffer->lpVtbl->GetDesc(backBuffer, &description);
		IDirect3DSurface9* copy = nullptr;
		HRESULT result = device->lpVtbl->CreateOffscreenPlainSurface(device, description.Width, description.Height, description.Format,
			D3DPOOL_SYSTEMMEM, &copy, nullptr);
		if (SUCCEEDED(result))
			result = device->lpVtbl->GetRenderTargetData(device, backBuffer, copy);
		D3DLOCKED_RECT locked {};
		if (SUCCEEDED(result))
			result = copy->lpVtbl->LockRect(copy, &locked, nullptr, D3DLOCK_READONLY);
		if (SUCCEEDED(result) && (description.Format == D3DFMT_X8R8G8B8 || description.Format == D3DFMT_A8R8G8B8))
		{
			const bool written = writeBmp(path, static_cast<const unsigned char*>(locked.pBits), locked.Pitch, int(description.Width),
				int(description.Height));
			log("screenshot %ux%u -> %s (%s)", description.Width, description.Height, path, written ? "written" : "write failed");
		}
		else
			log("screenshot failed: 0x%08lX, format %u", result, description.Format);
		if (SUCCEEDED(result))
			copy->lpVtbl->UnlockRect(copy);
		if (copy != nullptr)
			copy->lpVtbl->Release(copy);
		backBuffer->lpVtbl->Release(backBuffer);
	}

	HRESULT STDMETHODCALLTYPE setConstants(IDirect3DDevice9* device, UINT start, const float* data, UINT count)
	{
		if (data != nullptr && start < 256)
			memcpy(shaderConstants[start], data, std::size_t(min(count, 256 - start)) * sizeof(float[4]));
		return realSetConstants(device, start, data, count);
	}

	HRESULT STDMETHODCALLTYPE setPsConstants(IDirect3DDevice9* device, UINT start, const float* data, UINT count)
	{
		if (data != nullptr && start < 256)
			memcpy(pixelConstants[start], data, std::size_t(min(count, 256 - start)) * sizeof(float[4]));
		return realSetPsConstants(device, start, data, count);
	}

	HRESULT STDMETHODCALLTYPE setTexture(IDirect3DDevice9* device, DWORD stage, IDirect3DBaseTexture9* texture)
	{
		if (stage < STAGES)
			boundTextures[stage] = texture;
		return realSetTexture(device, stage, texture);
	}

	HRESULT STDMETHODCALLTYPE setRenderState(IDirect3DDevice9* device, D3DRENDERSTATETYPE state, DWORD value)
	{
		if (UINT(state) < 256)
			renderStates[state] = value;
		return realSetRenderState(device, state, value);
	}

	HRESULT STDMETHODCALLTYPE setSamplerState(IDirect3DDevice9* device, DWORD sampler, D3DSAMPLERSTATETYPE type, DWORD value)
	{
		if (sampler < STAGES && type == D3DSAMP_SRGBTEXTURE)
			samplerSrgb[sampler] = value;
		return realSetSamplerState(device, sampler, type, value);
	}

	HRESULT STDMETHODCALLTYPE setVertexShader(IDirect3DDevice9* device, IDirect3DVertexShader9* shader)
	{
		vertexShader = shader;
		return realSetVertexShader(device, shader);
	}

	HRESULT STDMETHODCALLTYPE setPixelShader(IDirect3DDevice9* device, IDirect3DPixelShader9* shader)
	{
		pixelShader = shader;
		return realSetPixelShader(device, shader);
	}

	UINT resourceId(const void* resource);

	// Raw copy of a render target: header {"OPRT", width, height, format, pitch} and the rows as stored
	void saveTarget(IDirect3DDevice9* device, IDirect3DSurface9* target)
	{
		D3DSURFACE_DESC description {};
		target->lpVtbl->GetDesc(target, &description);
		if (description.Width < 64 || description.Format == D3DFMT_UNKNOWN || description.Format == D3DFORMAT(0x4C4C554E))
			return;
		IDirect3DSurface9* copy = nullptr;
		HRESULT result = device->lpVtbl->CreateOffscreenPlainSurface(device, description.Width, description.Height, description.Format,
			D3DPOOL_SYSTEMMEM, &copy, nullptr);
		if (SUCCEEDED(result))
			result = device->lpVtbl->GetRenderTargetData(device, target, copy);
		D3DLOCKED_RECT locked {};
		if (SUCCEEDED(result))
			result = copy->lpVtbl->LockRect(copy, &locked, nullptr, D3DLOCK_READONLY);
		if (SUCCEEDED(result))
		{
			char path[MAX_PATH + 32];
			sprintf_s(path, "%s.rt%u.bin", capturePath, resourceId(target));
			FILE* file = nullptr;
			if (fopen_s(&file, path, "wb") == 0)
			{
				const UINT header[5] = {0x5452504F, description.Width, description.Height, UINT(description.Format), UINT(locked.Pitch)};
				fwrite(header, sizeof(header), 1, file);
				fwrite(locked.pBits, 1, std::size_t(locked.Pitch) * description.Height, file);
				fclose(file);
			}
			copy->lpVtbl->UnlockRect(copy);
		}
		else
			log("render target %ux%u format %u not saved: 0x%08lX", description.Width, description.Height, description.Format, result);
		if (copy != nullptr)
			copy->lpVtbl->Release(copy);
	}

	HRESULT STDMETHODCALLTYPE setRenderTarget(IDirect3DDevice9* device, DWORD index, IDirect3DSurface9* target)
	{
		if (index == 0)
		{
			// The target the game leaves is complete for this pass; a later pass may draw into it again and save it
			// once more
			if (recording && renderTarget != nullptr && renderTarget != target)
				saveTarget(device, renderTarget);
			renderTarget = target;
		}
		return realSetRenderTarget(device, index, target);
	}

	HRESULT STDMETHODCALLTYPE setViewport(IDirect3DDevice9* device, const D3DVIEWPORT9* viewport)
	{
		if (viewport != nullptr)
			currentViewport = *viewport;
		return realSetViewport(device, viewport);
	}

	UINT fnv(const unsigned char* data, std::size_t size)
	{
		UINT hash = 2166136261u;
		for (std::size_t i = 0; i < size; ++i)
			hash = (hash ^ data[i]) * 16777619u;
		return hash;
	}

	// Shaders are identified by a hash of their bytecode, the same in every session; the bytecode itself is not kept
	template <typename Shader>
	UINT shaderHash(Shader* shader)
	{
		if (shader == nullptr)
			return 0;
		if (const auto it = shaderHashes.find(shader); it != shaderHashes.end())
			return it->second;
		UINT size = 0;
		shader->lpVtbl->GetFunction(shader, nullptr, &size);
		std::vector<unsigned char> code(size);
		UINT hash = 0;
		if (size > 0 && SUCCEEDED(shader->lpVtbl->GetFunction(shader, code.data(), &size)))
			hash = fnv(code.data(), size);
		shaderHashes[shader] = hash;
		return hash;
	}

	UINT resourceId(const void* resource)
	{
		if (resource == nullptr)
			return 0;
		const auto [it, added] = resourceIds.emplace(resource, UINT(resourceIds.size() + 1));
		return it->second;
	}

	void textureInfo(IDirect3DBaseTexture9* texture, TextureInfo& info)
	{
		info.id = resourceId(texture);
		D3DSURFACE_DESC description {};
		switch (texture->lpVtbl->GetType(texture))
		{
			case D3DRTYPE_TEXTURE:
			{
				auto* plain = reinterpret_cast<IDirect3DTexture9*>(texture);
				plain->lpVtbl->GetLevelDesc(plain, 0, &description);
				info.height = description.Height;
				break;
			}
			case D3DRTYPE_CUBETEXTURE:
			{
				auto* cube = reinterpret_cast<IDirect3DCubeTexture9*>(texture);
				cube->lpVtbl->GetLevelDesc(cube, 0, &description);
				break;
			}
			default:
				return;
		}
		info.width = description.Width;
		info.format = UINT(description.Format);
	}

	// Level 0 of a small managed 2D texture as a DDS file (DXT1/3/5 or 32-bit), so it can be identified
	void saveTexture(IDirect3DBaseTexture9* texture)
	{
		if (savedTextures.contains(texture) || texture->lpVtbl->GetType(texture) != D3DRTYPE_TEXTURE)
			return;
		savedTextures[texture] = true;
		auto* plain = reinterpret_cast<IDirect3DTexture9*>(texture);
		D3DSURFACE_DESC description {};
		plain->lpVtbl->GetLevelDesc(plain, 0, &description);
		if (description.Width > 256 || description.Height > 256 || description.Pool != D3DPOOL_MANAGED)
			return;
		UINT blockBytes = 0;
		switch (UINT(description.Format))
		{
			case D3DFMT_DXT1:
				blockBytes = 8;
				break;
			case D3DFMT_DXT3:
			case D3DFMT_DXT5:
				blockBytes = 16;
				break;
			case D3DFMT_A8R8G8B8:
			case D3DFMT_X8R8G8B8:
				break;
			default:
				return;
		}
		D3DLOCKED_RECT locked {};
		if (FAILED(plain->lpVtbl->LockRect(plain, 0, &locked, nullptr, D3DLOCK_READONLY)))
			return;
		const UINT rows = blockBytes != 0 ? (description.Height + 3) / 4 : description.Height;
		const UINT rowBytes = blockBytes != 0 ? (description.Width + 3) / 4 * blockBytes : description.Width * 4;
		char path[MAX_PATH + 32];
		sprintf_s(path, "%s.tex%u.dds", capturePath, resourceId(texture));
		FILE* file = nullptr;
		if (fopen_s(&file, path, "wb") == 0)
		{
			// Minimal DDS header: magic, size 124, flags, height, width, pitch, depth, mips, 11 reserved, pixel format
			UINT header[32] {};
			header[0] = 0x20534444;
			header[1] = 124;
			header[2] = 0x1007 | (blockBytes != 0 ? 0x80000 : 0x8);
			header[3] = description.Height;
			header[4] = description.Width;
			header[5] = blockBytes != 0 ? rowBytes * rows : rowBytes;
			header[7] = 1;
			header[19] = 32;
			if (blockBytes != 0)
			{
				header[20] = 0x4;
				header[21] = UINT(description.Format);
			}
			else
			{
				header[20] = 0x41;
				header[22] = 32;
				header[23] = 0x00FF0000;
				header[24] = 0x0000FF00;
				header[25] = 0x000000FF;
				header[26] = 0xFF000000;
			}
			header[27] = 0x1000;
			fwrite(header, sizeof(header), 1, file);
			for (UINT row = 0; row < rows; ++row)
				fwrite(static_cast<const unsigned char*>(locked.pBits) + std::size_t(row) * std::size_t(locked.Pitch), 1, rowBytes, file);
			fclose(file);
		}
		plain->lpVtbl->UnlockRect(plain, 0);
	}

	// The camera trace (opprobe_trace.request holds the output path): every frame, its time and the distinct perspective
	// matrices its draws used (c0..c3, with c4), so the camera can be followed without a full capture (tools/re/scenario.py)
	const char* TRACE_FILE = "opprobe_trace.request";
	FILE* traceFile = nullptr;
	struct TraceCamera
	{
		UINT draws = 0;
		float constants[5][4] {};
	};
	TraceCamera traceCameras[16] {};
	UINT traceCount = 0;

	// A rigid view times a perspective projection (as camera.py's isPerspective): unit w axis, x and y axes orthogonal,
	// a field of view of 20-120 degrees and an aspect of 0.5-3; at(i, k) reads it as stored or transposed
	bool perspectiveAs(bool transposed)
	{
		const auto at = [&](int i, int k) { return transposed ? shaderConstants[k][i] : shaderConstants[i][k]; };
		const float x[3] {at(0, 0), at(0, 1), at(0, 2)}, y[3] {at(1, 0), at(1, 1), at(1, 2)}, w[3] {at(3, 0), at(3, 1), at(3, 2)};
		const float lx = sqrtf(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]), ly = sqrtf(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);
		const float lw = sqrtf(w[0] * w[0] + w[1] * w[1] + w[2] * w[2]);
		if (fabsf(lw - 1.0f) > 0.02f || lx < 1e-3f || ly < 1e-3f)
			return false;
		const float fov = 2.0f * atanf(1.0f / ly) * 57.2958f, aspect = ly / lx;
		return fov > 20.0f && fov < 120.0f && aspect > 0.5f && aspect < 3.0f && fabsf(x[0] * y[0] + x[1] * y[1] + x[2] * y[2]) < 0.01f * lx * ly;
	}

	bool perspective()
	{
		return perspectiveAs(true) || perspectiveAs(false);
	}

	void traceDraw()
	{
		if (traceFile == nullptr || !perspective())
			return;
		for (UINT i = 0; i < traceCount; ++i)
		{
			if (memcmp(traceCameras[i].constants, shaderConstants, sizeof(float[4][4])) == 0)
			{
				++traceCameras[i].draws;
				return;
			}
		}
		if (traceCount < 16)
		{
			traceCameras[traceCount].draws = 1;
			memcpy(traceCameras[traceCount].constants, shaderConstants, sizeof(float[5][4]));
			++traceCount;
		}
	}

	void record(UINT kind, D3DPRIMITIVETYPE type, UINT primitives, UINT vertices)
	{
		traceDraw();
		if (!recording || draws.size() >= RECORDED_DRAWS)
			return;
		DrawRecord& record = draws.emplace_back();
		record.kind = kind;
		record.primitiveType = UINT(type);
		record.primitives = primitives;
		record.vertices = vertices;
		record.vertexShader = shaderHash(vertexShader);
		record.pixelShader = shaderHash(pixelShader);
		if (renderTarget != nullptr)
		{
			D3DSURFACE_DESC description {};
			renderTarget->lpVtbl->GetDesc(renderTarget, &description);
			record.targetWidth = description.Width;
			record.targetHeight = description.Height;
			record.targetFormat = UINT(description.Format);
			record.targetId = resourceId(renderTarget);
		}
		record.viewport[0] = currentViewport.X;
		record.viewport[1] = currentViewport.Y;
		record.viewport[2] = currentViewport.Width;
		record.viewport[3] = currentViewport.Height;
		for (UINT i = 0; i < STATE_COUNT; ++i)
			record.states[i] = renderStates[RECORDED_STATES[i]];
		for (UINT stage = 0; stage < STAGES; ++stage)
		{
			if (boundTextures[stage] == nullptr)
				continue;
			textureInfo(boundTextures[stage], record.textures[stage]);
			saveTexture(boundTextures[stage]);
			record.textures[stage].srgb = samplerSrgb[stage];
		}
		memcpy(record.vsConstants, shaderConstants, sizeof(record.vsConstants));
		memcpy(record.psConstants, pixelConstants, sizeof(record.psConstants));
	}

	HRESULT STDMETHODCALLTYPE drawIndexed(IDirect3DDevice9* device, D3DPRIMITIVETYPE type, INT baseVertex, UINT minIndex, UINT vertices,
		UINT startIndex, UINT primitives)
	{
		record(0, type, primitives, vertices);
		return realDrawIndexed(device, type, baseVertex, minIndex, vertices, startIndex, primitives);
	}

	HRESULT STDMETHODCALLTYPE draw(IDirect3DDevice9* device, D3DPRIMITIVETYPE type, UINT startVertex, UINT primitives)
	{
		record(1, type, primitives, 0);
		return realDraw(device, type, startVertex, primitives);
	}

	HRESULT STDMETHODCALLTYPE drawUp(IDirect3DDevice9* device, D3DPRIMITIVETYPE type, UINT primitives, const void* data, UINT stride)
	{
		record(2, type, primitives, 0);
		return realDrawUp(device, type, primitives, data, stride);
	}

	void writeFrame(const char* imagePath)
	{
		char path[MAX_PATH + 8];
		sprintf_s(path, "%s.frame", imagePath);
		FILE* file = nullptr;
		if (fopen_s(&file, path, "wb") != 0)
			return;
		// "OPF2", draws, record size, VS registers, PS registers, stages, states
		const UINT header[7] = {0x3246504F, UINT(draws.size()), UINT(sizeof(DrawRecord)), VS_REGISTERS, PS_REGISTERS, STAGES, STATE_COUNT};
		fwrite(header, sizeof(header), 1, file);
		for (const DrawRecord& record : draws)
			fwrite(&record, sizeof(record), 1, file);
		fclose(file);
		log("%u draws -> %s", UINT(draws.size()), path);
	}

	HRESULT STDMETHODCALLTYPE present(IDirect3DDevice9* device, const RECT* source, const RECT* destination, HWND window, const RGNDATA* dirty)
	{
		gamecontrol::onPresent();
		// The camera trace: one record per frame (time, count, then count x (draws, c0..c4))
		if (traceFile != nullptr)
		{
			LARGE_INTEGER now;
			QueryPerformanceCounter(&now);
			fwrite(&now.QuadPart, sizeof(now.QuadPart), 1, traceFile);
			fwrite(&traceCount, sizeof(traceCount), 1, traceFile);
			for (UINT i = 0; i < traceCount; ++i)
				fwrite(&traceCameras[i], sizeof(TraceCamera), 1, traceFile);
			traceCount = 0;
		}
		if (frame % 8 == 4)
		{
			const bool wanted = GetFileAttributesA(TRACE_FILE) != INVALID_FILE_ATTRIBUTES;
			if (wanted && traceFile == nullptr)
			{
				char path[MAX_PATH] {};
				FILE* request = nullptr;
				if (fopen_s(&request, TRACE_FILE, "rb") == 0)
				{
					fread(path, 1, sizeof(path) - 1, request);
					fclose(request);
				}
				for (char* end = path + strlen(path); end > path && (end[-1] == '\n' || end[-1] == '\r' || end[-1] == ' '); --end)
					end[-1] = 0;
				if (path[0] != 0 && fopen_s(&traceFile, path, "wb") == 0)
				{
					LARGE_INTEGER frequency;
					QueryPerformanceFrequency(&frequency);
					const UINT magic = 0x3154504F; // "OPT1"
					fwrite(&magic, sizeof(magic), 1, traceFile);
					fwrite(&frequency.QuadPart, sizeof(frequency.QuadPart), 1, traceFile);
					traceCount = 0;
					log("camera trace -> %s", path);
				}
			}
			else if (!wanted && traceFile != nullptr)
			{
				fclose(traceFile);
				traceFile = nullptr;
				log("camera trace closed");
			}
		}
		// The frame that was recorded is complete: save its image and draws
		if (recording)
		{
			recording = false;
			saveBackBuffer(device, capturePath);
			writeFrame(capturePath);
			DeleteFileA(REQUEST_FILE);
		}
		// A request is checked every few frames: a file test per frame is cheap but not free
		else if (++frame % 8 == 0 && GetFileAttributesA(REQUEST_FILE) != INVALID_FILE_ATTRIBUTES)
		{
			char path[MAX_PATH] {};
			FILE* file = nullptr;
			if (fopen_s(&file, REQUEST_FILE, "rb") == 0)
			{
				fread(path, 1, sizeof(path) - 1, file);
				fclose(file);
			}
			for (char* end = path + strlen(path); end > path && (end[-1] == '\n' || end[-1] == '\r' || end[-1] == ' '); --end)
				end[-1] = 0;
			if (path[0] != 0)
			{
				strcpy_s(capturePath, path);
				draws.clear();
				draws.reserve(4096);
				resourceIds.clear();
				savedTextures.clear();
				recording = true;
			}
			else
				DeleteFileA(REQUEST_FILE);
		}
		return realPresent(device, source, destination, window, dirty);
	}

	HRESULT STDMETHODCALLTYPE reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* parameters)
	{
		makeWindowed(parameters, gameWindow);
		const HRESULT result = realReset(device, parameters);
		log("Reset -> 0x%08lX", result);
		return result;
	}

	HRESULT STDMETHODCALLTYPE createDevice(IDirect3D9* direct3d, UINT adapter, D3DDEVTYPE type, HWND focus, DWORD flags,
		D3DPRESENT_PARAMETERS* parameters, IDirect3DDevice9** device)
	{
		gameWindow = parameters != nullptr && parameters->hDeviceWindow != nullptr ? parameters->hDeviceWindow : focus;
		makeWindowed(parameters, gameWindow);
		keepActive(gameWindow);
		const HRESULT result = realCreateDevice(direct3d, adapter, type, focus, flags, parameters, device);
		log("CreateDevice -> 0x%08lX (flags 0x%08lX)", result, flags);
		if (SUCCEEDED(result) && device != nullptr && *device != nullptr && realReset == nullptr)
		{
			IDirect3DDevice9Vtbl* table = (*device)->lpVtbl;
			patch(&table->Reset, &reset, realReset);
			patch(&table->Present, &present, realPresent);
			patch(&table->SetVertexShaderConstantF, &setConstants, realSetConstants);
			patch(&table->SetPixelShaderConstantF, &setPsConstants, realSetPsConstants);
			patch(&table->DrawIndexedPrimitive, &drawIndexed, realDrawIndexed);
			patch(&table->DrawPrimitive, &draw, realDraw);
			patch(&table->DrawPrimitiveUP, &drawUp, realDrawUp);
			patch(&table->SetTexture, &setTexture, realSetTexture);
			patch(&table->SetRenderState, &setRenderState, realSetRenderState);
			patch(&table->SetSamplerState, &setSamplerState, realSetSamplerState);
			patch(&table->SetVertexShader, &setVertexShader, realSetVertexShader);
			patch(&table->SetPixelShader, &setPixelShader, realSetPixelShader);
			patch(&table->SetRenderTarget, &setRenderTarget, realSetRenderTarget);
			patch(&table->SetViewport, &setViewport, realSetViewport);
			gamecontrol::hookInput();
		}
		return result;
	}
}

extern "C" IDirect3D9* WINAPI Direct3DCreate9(UINT version)
{
	static CreateFunction realCreate = nullptr;
	if (realCreate == nullptr)
	{
		wchar_t path[MAX_PATH];
		GetSystemDirectoryW(path, MAX_PATH);
		wcscat_s(path, L"\\d3d9.dll");
		const HMODULE system = LoadLibraryW(path);
		realCreate = system != nullptr ? reinterpret_cast<CreateFunction>(GetProcAddress(system, "Direct3DCreate9")) : nullptr;
		log("system d3d9: %p, Direct3DCreate9: %p", static_cast<void*>(system), reinterpret_cast<void*>(realCreate));
		if (realCreate == nullptr)
			return nullptr;
	}
	IDirect3D9* direct3d = realCreate(version);
	if (direct3d != nullptr && realCreateDevice == nullptr)
		patch(&direct3d->lpVtbl->CreateDevice, &createDevice, realCreateDevice);
	return direct3d;
}
