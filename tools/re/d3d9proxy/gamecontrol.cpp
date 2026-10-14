// Control of the running original. Everything here calls the engine's own functions or
// fills in what DirectInput returns; addresses are those of prototypeenginef.dll at its preferred base 0x10000000,
// checked against the bytes of each function before the first use.
//
// Requests: a tool writes opprobe_cmd.request in the game folder (atomically: write, then rename) and may post
// WAKE_MESSAGE to the game's window; Present also looks for the file every other frame and posts the message itself.
// The request runs inside the window procedure, on the game's main thread between two engine frames (the executable's
// message loop; the engine never pumps messages), and the answer goes to opprobe_cmd.result ("ok" or "error" on the
// first line, then the output). Access violations inside the engine are logged with their stack (logFault).
//
//   lua <code>                   run a Lua chunk in the game's script state; the values it returns are the output
//   camera <yaw> <pitch> [dist]  put the chase camera's orbit there (view yaw: 0 looks along +Z; pitch > 0 looks down)
//   keys <script>                hold keys for given times ("w:2,shift+w:1.5,:0.5"); runs on the game's input polls
//   mouse <dx> <dy>              a relative mouse move, given to the game's next mouse poll
//   release                      let go of every injected key and button
//   status                       threads, Lua state, input hooks and polls
#define CINTERFACE
#define DIRECTINPUT_VERSION 0x0800
#include "gamecontrol.hpp"

#include <dinput.h>

#include <atomic>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
#include <mutex>
#include <string>
#include <vector>

void proxyLog(const char* format, ...);

namespace
{
	const char* REQUEST_FILE = "opprobe_cmd.request";
	const char* RESULT_FILE = "opprobe_cmd.result";
	const char* RESULT_TEMP = "opprobe_cmd.result.tmp";

	HWND controlWindow = nullptr;
	DWORD mainThread = 0;
	DWORD presentThread = 0;
	std::atomic<bool> wakePosted {false};
	unsigned presentCount = 0;

	// --- Engine functions ---------------------------------------------------------------------------------------

	// The build the addresses were read from (PE time stamp of prototypeenginef.dll, Steam version)
	constexpr DWORD ENGINE_TIMESTAMP = 0x689E2026;

	struct EngineFunction
	{
		uintptr_t address;
		unsigned char prologue[6];
	};

	// Lua 5.1 (linked into the engine; lua_Number is float)
	constexpr EngineFunction LUA_GETTOP {0x1062C1B0, {0x8B, 0x4C, 0x24, 0x04, 0x8B, 0x41}};
	constexpr EngineFunction LUA_SETTOP {0x1062C1C0, {0x8B, 0x4C, 0x24, 0x08, 0x85, 0xC9}};
	constexpr EngineFunction LUA_TYPE {0x1062C370, {0x8B, 0x4C, 0x24, 0x08, 0x8B, 0x54}};
	constexpr EngineFunction LUA_TYPENAME {0x1062C390, {0x8B, 0x44, 0x24, 0x08, 0x83, 0xF8}};
	constexpr EngineFunction LUA_TOBOOLEAN {0x1062C5E0, {0x8B, 0x4C, 0x24, 0x08, 0x8B, 0x54}};
	constexpr EngineFunction LUA_TOLSTRING {0x1062C610, {0x56, 0x8B, 0x74, 0x24, 0x08, 0x57}};
	constexpr EngineFunction LUA_PCALL {0x1062CF20, {0x8B, 0x4C, 0x24, 0x10, 0x83, 0xEC}};
	constexpr EngineFunction LUAL_LOADBUFFER {0x10639D20, {0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x08}};
	// engine::LuaScriptManager: the one instance is at this global; its main lua_State at + 0x0C
	constexpr uintptr_t LUA_MANAGER_GLOBAL = 0x11284254;
	constexpr uintptr_t LUA_MANAGER_STATE = 0x0C;
	// proto::ChaseCamera
	constexpr uintptr_t CHASE_CAMERA_VTABLE = 0x10DF29A4;

	bool engineMatches()
	{
		static int checked = -1;
		if (checked < 0)
		{
			const auto* image = reinterpret_cast<const unsigned char*>(GetModuleHandleA("prototypeenginef.dll"));
			checked = 0;
			if (image == reinterpret_cast<const unsigned char*>(0x10000000))
			{
				const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(image);
				const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(image + dos->e_lfanew);
				checked = nt->FileHeader.TimeDateStamp == ENGINE_TIMESTAMP ? 1 : 0;
				proxyLog("engine time stamp 0x%08lX (%s)", nt->FileHeader.TimeDateStamp, checked ? "known" : "unknown build");
			}
			else
				proxyLog("prototypeenginef.dll is not at 0x10000000 (%p)", static_cast<const void*>(image));
		}
		return checked == 1;
	}

	template <typename Function>
	Function engine(const EngineFunction& function, std::string& error)
	{
		if (!engineMatches())
		{
			error = "unknown engine build";
			return nullptr;
		}
		if (memcmp(reinterpret_cast<const void*>(function.address), function.prologue, sizeof(function.prologue)) != 0)
		{
			char text[64];
			sprintf_s(text, "engine function 0x%08X does not match", unsigned(function.address));
			error = text;
			return nullptr;
		}
		return reinterpret_cast<Function>(function.address);
	}

	// --- Lua ------------------------------------------------------------------------------------------------------

	struct LuaState;
	using LuaGetTop = int(__cdecl*)(LuaState*);
	using LuaSetTop = void(__cdecl*)(LuaState*, int);
	using LuaType = int(__cdecl*)(LuaState*, int);
	using LuaTypeName = const char*(__cdecl*)(LuaState*, int);
	using LuaToBoolean = int(__cdecl*)(LuaState*, int);
	using LuaToLString = const char*(__cdecl*)(LuaState*, int, size_t*);
	using LuaPCall = int(__cdecl*)(LuaState*, int, int, int);
	using LuaLoadBuffer = int(__cdecl*)(LuaState*, const char*, size_t, const char*);

	// Runs the chunk and appends what it returned (one value per line) or the error message
	bool runLua(const std::string& code, std::string& output)
	{
		std::string error;
		const auto getTop = engine<LuaGetTop>(LUA_GETTOP, error);
		const auto setTop = engine<LuaSetTop>(LUA_SETTOP, error);
		const auto type = engine<LuaType>(LUA_TYPE, error);
		const auto typeName = engine<LuaTypeName>(LUA_TYPENAME, error);
		const auto toBoolean = engine<LuaToBoolean>(LUA_TOBOOLEAN, error);
		const auto toLString = engine<LuaToLString>(LUA_TOLSTRING, error);
		const auto pcall = engine<LuaPCall>(LUA_PCALL, error);
		const auto loadBuffer = engine<LuaLoadBuffer>(LUAL_LOADBUFFER, error);
		if (!error.empty())
		{
			output = error;
			return false;
		}
		const uintptr_t manager = *reinterpret_cast<const uintptr_t*>(LUA_MANAGER_GLOBAL);
		LuaState* state = manager != 0 ? *reinterpret_cast<LuaState* const*>(manager + LUA_MANAGER_STATE) : nullptr;
		if (state == nullptr)
		{
			output = "no Lua state yet";
			return false;
		}
		const int top = getTop(state);
		int status = loadBuffer(state, code.data(), code.size(), "=opprobe");
		if (status == 0)
			status = pcall(state, 0, -1, 0);
		const int count = getTop(state) - top;
		for (int i = 1; i <= count; ++i)
		{
			const int index = top + i;
			const int kind = type(state, index);
			// Numbers and strings as text, booleans as true or false, anything else by its type name
			if (kind == 3 || kind == 4)
			{
				size_t length = 0;
				const char* text = toLString(state, index, &length);
				output.append(text != nullptr ? std::string(text, length) : std::string());
			}
			else if (kind == 1)
				output.append(toBoolean(state, index) != 0 ? "true" : "false");
			else
				output.append(typeName(state, kind));
			output.push_back('\n');
		}
		setTop(state, top);
		return status == 0;
	}

	// SEH around engine calls: a fault in the game's code is reported instead of ending the game
	bool runLuaGuarded(const std::string& code, std::string& output)
	{
		bool (*function)(const std::string&, std::string&) = &runLua;
		__try
		{
			return function(code, output);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			output += "exception in the game's code";
			return false;
		}
	}

	// --- Chase camera ---------------------------------------------------------------------------------------------

	uintptr_t chaseCamera = 0;

	// Heap memory of the game: committed, private, read-write and cached (no write-combined or uncached memory of the
	// driver), and not this thread's stack (which holds the value searched for)
	bool scannable(const MEMORY_BASIC_INFORMATION& info, const void* stackBase)
	{
		const DWORD protect = info.Protect & 0xFF;
		return info.State == MEM_COMMIT && info.Type == MEM_PRIVATE && !(info.Protect & (PAGE_GUARD | PAGE_NOCACHE | PAGE_WRITECOMBINE))
			&& (protect == PAGE_READWRITE || protect == PAGE_EXECUTE_READWRITE) && info.AllocationBase != stackBase;
	}

	bool readablePointer(uintptr_t address)
	{
		MEMORY_BASIC_INFORMATION info {};
		return address >= 0x10000 && VirtualQuery(reinterpret_cast<void*>(address), &info, sizeof(info)) && info.State == MEM_COMMIT
			&& !(info.Protect & PAGE_GUARD) && (info.Protect & 0xFF) != PAGE_NOACCESS;
	}

	// Objects whose first dword is the vtable and whose sub-object at + 0x14 exists (the chase camera's view)
	uintptr_t scanForVtable(uintptr_t vtable)
	{
		MEMORY_BASIC_INFORMATION here {};
		VirtualQuery(&here, &here, sizeof(here));
		const void* stackBase = here.AllocationBase;
		uintptr_t found = 0;
		int count = 0;
		MEMORY_BASIC_INFORMATION info {};
		for (uintptr_t address = 0x10000; address < 0xFFFF0000 && VirtualQuery(reinterpret_cast<void*>(address), &info, sizeof(info));
			address = uintptr_t(info.BaseAddress) + info.RegionSize)
		{
			if (uintptr_t(info.BaseAddress) + info.RegionSize < address)
				break;
			if (!scannable(info, stackBase))
				continue;
			const auto* words = static_cast<const uintptr_t*>(info.BaseAddress);
			const size_t n = info.RegionSize / 4;
			for (size_t i = 0; i + 8 < n; ++i)
			{
				if (words[i] == vtable && readablePointer(words[i + 5]))
				{
					found = uintptr_t(words + i);
					++count;
				}
			}
		}
		if (count != 1)
			proxyLog("vtable 0x%08X: %d objects", unsigned(vtable), count);
		return count == 1 ? found : 0;
	}

	uintptr_t findCamera()
	{
		if (chaseCamera != 0 && *reinterpret_cast<const uintptr_t*>(chaseCamera) == CHASE_CAMERA_VTABLE)
			return chaseCamera;
		chaseCamera = 0;
		__try
		{
			chaseCamera = scanForVtable(CHASE_CAMERA_VTABLE);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			chaseCamera = 0;
		}
		return chaseCamera;
	}

	float& cameraFloat(uintptr_t camera, uintptr_t offset)
	{
		return *reinterpret_cast<float*>(camera + offset);
	}

	// The orbit is (radius, direction from the focus to the camera, elevation), radians; the fields and their meaning
	// are the camera's ("held" regime: the orbit stays as the player left it)
	bool setCamera(float viewYaw, float viewPitch, float distance, std::string& output)
	{
		const uintptr_t camera = findCamera();
		if (camera == 0)
		{
			output = "chase camera not found";
			return false;
		}
		if (distance <= 0.0f)
			distance = cameraFloat(camera, 0x1E0);
		const float yaw = (viewYaw + 180.0f) * 0.01745329252f;
		const float pitch = viewPitch * 0.01745329252f;
		const float focus[3] {cameraFloat(camera, 0x190), cameraFloat(camera, 0x194), cameraFloat(camera, 0x198)};
		const float offset[3] {distance * cosf(pitch) * sinf(yaw), distance * sinf(pitch), distance * cosf(pitch) * cosf(yaw)};
		for (const uintptr_t field : {0x1ECu, 0x1F8u, 0x204u, 0x29Cu})
			for (int i = 0; i < 3; ++i)
				cameraFloat(camera, field + 4 * i) = focus[i] + offset[i];
		for (const uintptr_t field : {0x1E0u, 0x290u, 0x2D8u, 0xC98u})
		{
			cameraFloat(camera, field) = distance;
			cameraFloat(camera, field + 4) = yaw;
			cameraFloat(camera, field + 8) = pitch;
		}
		cameraFloat(camera, 0x5C) = distance;
		for (const uintptr_t field : {0x210u, 0x214u, 0x2A8u, 0x2ACu})
			cameraFloat(camera, field) = 0.0f;
		// Held: as after a mouse look (device 3), the hold never runs out, the last look input was just now
		*reinterpret_cast<unsigned*>(camera + 0x80) = 3;
		cameraFloat(camera, 0xCAC) = 1.0e9f;
		cameraFloat(camera, 0xCA8) = 0.0f;
		char text[160];
		sprintf_s(text, "camera 0x%08X: orbit %.2f m, direction %.2f, elevation %.2f", unsigned(camera), distance,
			fmodf(fmodf(viewYaw + 180.0f, 360.0f) + 360.0f, 360.0f), viewPitch);
		output = text;
		return true;
	}

	bool setCameraGuarded(float yaw, float pitch, float distance, std::string& output)
	{
		bool (*function)(float, float, float, std::string&) = &setCamera;
		__try
		{
			return function(yaw, pitch, distance, output);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			chaseCamera = 0;
			output += "exception while writing the camera";
			return false;
		}
	}

	// --- Injected input -------------------------------------------------------------------------------------------

	// A key script: steps of (scan codes held, seconds); mouse buttons are scan codes 0x100 + button
	struct Step
	{
		std::vector<unsigned> keys;
		double seconds = 0.0;
	};

	std::mutex inputMutex;
	std::vector<Step> script;
	LARGE_INTEGER scriptStart {};
	bool scriptStarted = false;
	std::atomic<long> mouseX {0};
	std::atomic<long> mouseY {0};
	std::atomic<unsigned> keyboardPolls {0};
	std::atomic<unsigned> mousePolls {0};
	std::atomic<unsigned> bufferedPolls {0};
	std::atomic<DWORD> inputThread {0};

	const std::map<std::string, unsigned>& keyNames()
	{
		static const std::map<std::string, unsigned> names {{"escape", 0x01}, {"1", 0x02}, {"2", 0x03}, {"3", 0x04}, {"4", 0x05},
			{"5", 0x06}, {"q", 0x10}, {"w", 0x11}, {"e", 0x12}, {"r", 0x13}, {"t", 0x14}, {"enter", 0x1C}, {"ctrl", 0x1D},
			{"a", 0x1E}, {"s", 0x1F}, {"d", 0x20}, {"f", 0x21}, {"g", 0x22}, {"shift", 0x2A}, {"z", 0x2C}, {"x", 0x2D},
			{"c", 0x2E}, {"v", 0x2F}, {"space", 0x39}, {"tab", 0x0F}, {"alt", 0x38}, {"up", 0xC8}, {"down", 0xD0},
			{"left", 0xCB}, {"right", 0xCD}, {"lmb", 0x100}, {"rmb", 0x101}, {"mmb", 0x102},
			// the power hot keys F1 - F11
			{"f1", 0x3B}, {"f2", 0x3C}, {"f3", 0x3D}, {"f4", 0x3E}, {"f5", 0x3F}, {"f6", 0x40}, {"f7", 0x41}, {"f8", 0x42}, {"f9", 0x43},
			{"f10", 0x44}, {"f11", 0x57}};
		return names;
	}

	bool parseScript(const std::string& text, std::vector<Step>& steps, std::string& error)
	{
		size_t start = 0;
		while (start <= text.size())
		{
			size_t end = text.find(',', start);
			if (end == std::string::npos)
				end = text.size();
			const std::string item = text.substr(start, end - start);
			const size_t colon = item.rfind(':');
			if (colon == std::string::npos)
			{
				error = "a step needs keys:seconds: " + item;
				return false;
			}
			Step step;
			step.seconds = atof(item.c_str() + colon + 1);
			const std::string names = item.substr(0, colon);
			size_t from = 0;
			while (from < names.size())
			{
				size_t plus = names.find('+', from);
				if (plus == std::string::npos)
					plus = names.size();
				const std::string name = names.substr(from, plus - from);
				if (!name.empty())
				{
					const auto it = keyNames().find(name);
					if (it != keyNames().end())
						step.keys.push_back(it->second);
					else if (name.size() > 2 && name[0] == '0' && name[1] == 'x')
						step.keys.push_back(unsigned(strtoul(name.c_str(), nullptr, 16)));
					else
					{
						error = "unknown key " + name;
						return false;
					}
				}
				from = plus + 1;
			}
			steps.push_back(step);
			start = end + 1;
		}
		return true;
	}

	// Keys held now by the script (scan codes), and whether a script is running at all
	bool currentKeys(std::vector<unsigned>& keys)
	{
		std::lock_guard lock(inputMutex);
		if (script.empty())
			return false;
		LARGE_INTEGER now, frequency;
		QueryPerformanceCounter(&now);
		QueryPerformanceFrequency(&frequency);
		if (!scriptStarted)
		{
			scriptStart = now;
			scriptStarted = true;
		}
		double elapsed = double(now.QuadPart - scriptStart.QuadPart) / double(frequency.QuadPart);
		for (const Step& step : script)
		{
			if (elapsed < step.seconds)
			{
				keys = step.keys;
				return true;
			}
			elapsed -= step.seconds;
		}
		script.clear();
		return false;
	}

	using AcquireFunction = HRESULT(STDMETHODCALLTYPE*)(void*);
	using GetDeviceStateFunction = HRESULT(STDMETHODCALLTYPE*)(void*, DWORD, LPVOID);
	using GetDeviceDataFunction = HRESULT(STDMETHODCALLTYPE*)(void*, DWORD, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);

	// The original methods per device vtable (ANSI and wide differ); filled before the vtable is patched
	struct HookedTable
	{
		void* vtable = nullptr;
		AcquireFunction acquire = nullptr;
		GetDeviceStateFunction getDeviceState = nullptr;
		GetDeviceDataFunction getDeviceData = nullptr;
	};
	HookedTable hookedTables[4] {};
	std::atomic<unsigned> hookedCount {0};

	const HookedTable* tableOf(void* device)
	{
		void* vtable = *static_cast<void**>(device);
		for (unsigned i = 0; i < hookedCount; ++i)
			if (hookedTables[i].vtable == vtable)
				return &hookedTables[i];
		return nullptr;
	}

	bool lost(HRESULT result)
	{
		return result == DIERR_NOTACQUIRED || result == DIERR_INPUTLOST;
	}

	// The game acquires its devices in the foreground cooperative level, which fails while its window is behind another;
	// it then stops reading them. Acquire reports success, so the game keeps polling (and gets nothing but the injected
	// input while the window is behind, see getDeviceState).
	HRESULT STDMETHODCALLTYPE acquire(void* device)
	{
		const HookedTable* table = tableOf(device);
		const HRESULT result = table != nullptr ? table->acquire(device) : DIERR_GENERIC;
		return FAILED(result) && result != DIERR_INVALIDPARAM ? DI_OK : result;
	}

	// Where the game's data format puts each input. The engine builds its own formats (0x106430B0): one DWORD per
	// device object, in the order DirectInput enumerates them, objects of unknown type left out. For the keyboard it
	// also keeps a table from scan code to object index at KEY_INDEX_TABLE (filled by its EnumObjects callback,
	// 0x10642EF0).
	constexpr uintptr_t KEY_INDEX_TABLE = 0x1127900C;

	struct DeviceLayout
	{
		void* device = nullptr;
		DWORD kind = 0;  // DI8DEVTYPE_KEYBOARD, DI8DEVTYPE_MOUSE or another type
		int x = -1;      // mouse axes and buttons: DWORD index in the game's format
		int y = -1;
		int buttons[8] {-1, -1, -1, -1, -1, -1, -1, -1};
		int buttonCount = 0;
		int index = 0;   // while enumerating
	};
	DeviceLayout layouts[16] {};
	unsigned layoutCount = 0;

	BOOL CALLBACK countObject(LPCDIDEVICEOBJECTINSTANCEA object, LPVOID context)
	{
		auto& layout = *static_cast<DeviceLayout*>(context);
		if (object->guidType == GUID_Unknown)
			return DIENUM_CONTINUE;
		if (object->guidType == GUID_XAxis && layout.x < 0)
			layout.x = layout.index;
		else if (object->guidType == GUID_YAxis && layout.y < 0)
			layout.y = layout.index;
		else if (object->guidType == GUID_Button && layout.buttonCount < 8)
			layout.buttons[layout.buttonCount++] = layout.index;
		++layout.index;
		return DIENUM_CONTINUE;
	}

	// Polls run on the game's main thread only (checked: the input thread is the window's thread)
	const DeviceLayout& layoutOf(void* device)
	{
		for (unsigned i = 0; i < layoutCount; ++i)
			if (layouts[i].device == device)
				return layouts[i];
		static DeviceLayout unknown;
		if (layoutCount >= std::size(layouts))
			return unknown;
		DeviceLayout& layout = layouts[layoutCount];
		layout.device = device;
		auto* input = static_cast<IDirectInputDevice8A*>(device);
		DIDEVCAPS caps {};
		caps.dwSize = sizeof(caps);
		if (SUCCEEDED(input->lpVtbl->GetCapabilities(input, &caps)))
			layout.kind = GET_DIDEVICE_TYPE(caps.dwDevType);
		if (layout.kind == DI8DEVTYPE_MOUSE)
			input->lpVtbl->EnumObjects(input, &countObject, &layout, DIDFT_ALL);
		proxyLog("input: device %p kind 0x%02lX, %d objects, x %d y %d, %d buttons", device, layout.kind, layout.index, layout.x, layout.y,
			layout.buttonCount);
		++layoutCount;
		return layout;
	}

	void injectKeyboard(unsigned char* data, DWORD size, const std::vector<unsigned>& keys)
	{
		const auto* indices = reinterpret_cast<const DWORD*>(KEY_INDEX_TABLE);
		for (const unsigned key : keys)
		{
			if (key >= 256)
				continue;
			if (size == 256)
				data[key] = 0x80;
			else if (engineMatches() && indices[key] < size / 4)
				data[4 * indices[key]] = 0x80;
		}
	}

	void injectMouse(unsigned char* data, DWORD size, const DeviceLayout& layout, const std::vector<unsigned>& keys)
	{
		const long dx = mouseX.exchange(0), dy = mouseY.exchange(0);
		const bool standard = size == sizeof(DIMOUSESTATE) || size == sizeof(DIMOUSESTATE2);
		const int x = standard ? 0 : layout.x, y = standard ? 1 : layout.y;
		if (x >= 0 && DWORD(4 * x + 4) <= size)
			reinterpret_cast<LONG*>(data)[x] += dx;
		if (y >= 0 && DWORD(4 * y + 4) <= size)
			reinterpret_cast<LONG*>(data)[y] += dy;
		for (const unsigned key : keys)
		{
			if (key < 0x100 || key >= 0x108)
				continue;
			const unsigned button = key - 0x100;
			const int offset = standard ? int(12 + button) : (int(button) < layout.buttonCount ? 4 * layout.buttons[button] : -1);
			if (offset >= 0 && DWORD(offset) < size)
				data[offset] = 0x80;
		}
	}

	HRESULT STDMETHODCALLTYPE getDeviceState(void* device, DWORD size, LPVOID data)
	{
		const HookedTable* table = tableOf(device);
		if (table == nullptr)
			return DIERR_GENERIC;
		HRESULT result = table->getDeviceState(device, size, data);
		// Not really acquired (see acquire): try again, it works once the window is in front
		if (lost(result) && SUCCEEDED(table->acquire(device)))
			result = table->getDeviceState(device, size, data);
		inputThread = GetCurrentThreadId();
		if (data == nullptr)
			return result;
		// In the background the game gets a device at rest, plus what is injected
		if (lost(result) || result == DIERR_OTHERAPPHASPRIO)
		{
			memset(data, 0, size);
			result = DI_OK;
		}
		const DeviceLayout& layout = layoutOf(device);
		std::vector<unsigned> keys;
		currentKeys(keys);
		if (layout.kind == DI8DEVTYPE_KEYBOARD)
		{
			++keyboardPolls;
			injectKeyboard(static_cast<unsigned char*>(data), size, keys);
		}
		else if (layout.kind == DI8DEVTYPE_MOUSE)
		{
			++mousePolls;
			injectMouse(static_cast<unsigned char*>(data), size, layout, keys);
		}
		return result;
	}

	HRESULT STDMETHODCALLTYPE getDeviceData(void* device, DWORD size, LPDIDEVICEOBJECTDATA data, LPDWORD count, DWORD flags)
	{
		++bufferedPolls;
		const HookedTable* table = tableOf(device);
		if (table == nullptr)
			return DIERR_GENERIC;
		const HRESULT result = table->getDeviceData(device, size, data, count, flags);
		if ((lost(result) || result == DIERR_OTHERAPPHASPRIO) && count != nullptr)
		{
			*count = 0;
			return DI_OK;
		}
		return result;
	}

	template <typename Function>
	void patchSlot(Function* slot, Function hook)
	{
		DWORD protection = 0;
		VirtualProtect(slot, sizeof(*slot), PAGE_EXECUTE_READWRITE, &protection);
		*slot = hook;
		VirtualProtect(slot, sizeof(*slot), protection, &protection);
	}

	void hookTable(IDirectInputDevice8AVtbl* table)
	{
		for (unsigned i = 0; i < hookedCount; ++i)
			if (hookedTables[i].vtable == table)
				return;
		if (hookedCount >= std::size(hookedTables))
			return;
		HookedTable& entry = hookedTables[hookedCount];
		entry.vtable = table;
		entry.acquire = reinterpret_cast<AcquireFunction>(table->Acquire);
		entry.getDeviceState = reinterpret_cast<GetDeviceStateFunction>(table->GetDeviceState);
		entry.getDeviceData = reinterpret_cast<GetDeviceDataFunction>(table->GetDeviceData);
		++hookedCount;
		patchSlot(reinterpret_cast<AcquireFunction*>(&table->Acquire), &acquire);
		patchSlot(reinterpret_cast<GetDeviceStateFunction*>(&table->GetDeviceState), &getDeviceState);
		patchSlot(reinterpret_cast<GetDeviceDataFunction*>(&table->GetDeviceData), &getDeviceData);
	}

	// Writes the answer next to the request, atomically for the reader
	void answer(bool ok, const std::string& output)
	{
		FILE* file = nullptr;
		if (fopen_s(&file, RESULT_TEMP, "wb") != 0)
			return;
		fputs(ok ? "ok\n" : "error\n", file);
		fwrite(output.data(), 1, output.size(), file);
		fclose(file);
		MoveFileExA(RESULT_TEMP, RESULT_FILE, MOVEFILE_REPLACE_EXISTING);
	}

	std::string readRequest()
	{
		std::string text;
		FILE* file = nullptr;
		if (fopen_s(&file, REQUEST_FILE, "rb") != 0)
			return text;
		char buffer[4096];
		size_t read = 0;
		while ((read = fread(buffer, 1, sizeof(buffer), file)) > 0)
			text.append(buffer, read);
		fclose(file);
		return text;
	}

	bool execute(const std::string& request, std::string& output)
	{
		const size_t space = request.find_first_of(" \r\n");
		const std::string verb = request.substr(0, space);
		const std::string rest = space == std::string::npos ? std::string() : request.substr(space + 1);
		if (verb == "lua")
			return runLuaGuarded(rest, output);
		if (verb == "camera")
		{
			float yaw = 0.0f, pitch = 0.0f, distance = 0.0f;
			if (sscanf_s(rest.c_str(), "%f %f %f", &yaw, &pitch, &distance) < 2)
			{
				output = "camera <yaw> <pitch> [distance]";
				return false;
			}
			return setCameraGuarded(yaw, pitch, distance, output);
		}
		if (verb == "keys")
		{
			std::vector<Step> steps;
			std::string trimmed = rest;
			while (!trimmed.empty() && (trimmed.back() == '\n' || trimmed.back() == '\r' || trimmed.back() == ' '))
				trimmed.pop_back();
			if (!parseScript(trimmed, steps, output))
				return false;
			double total = 0.0;
			for (const Step& step : steps)
				total += step.seconds;
			std::lock_guard lock(inputMutex);
			script = steps;
			scriptStarted = false;
			char text[64];
			sprintf_s(text, "%u steps, %.3f s", unsigned(steps.size()), total);
			output = text;
			return true;
		}
		if (verb == "mouse")
		{
			long dx = 0, dy = 0;
			if (sscanf_s(rest.c_str(), "%ld %ld", &dx, &dy) != 2)
			{
				output = "mouse <dx> <dy>";
				return false;
			}
			mouseX += dx;
			mouseY += dy;
			output = "queued";
			return true;
		}
		if (verb == "release")
		{
			std::lock_guard lock(inputMutex);
			script.clear();
			mouseX = 0;
			mouseY = 0;
			output = "released";
			return true;
		}
		if (verb == "status")
		{
			std::vector<unsigned> keys;
			const bool running = currentKeys(keys);
			char text[512];
			sprintf_s(text,
				"main thread %lu, present thread %lu, input thread %lu, this thread %lu\n"
				"engine %s, Lua manager 0x%08X\n"
				"input hooks: %u vtables; polls keyboard %u, mouse %u, buffered %u; script %s\n",
				mainThread, presentThread, DWORD(inputThread), GetCurrentThreadId(), engineMatches() ? "known" : "unknown",
				unsigned(*reinterpret_cast<const uintptr_t*>(LUA_MANAGER_GLOBAL)), unsigned(hookedCount),
				unsigned(keyboardPolls), unsigned(mousePolls), unsigned(bufferedPolls), running ? "running" : "idle");
			output = text;
			return true;
		}
		output = "unknown request: " + verb;
		return false;
	}

	// A fault in the engine is written to the log with the return addresses on the stack (diagnosis of crashes of
	// the original under control; the exception goes on to the game's own handlers unchanged)
	LONG CALLBACK logFault(EXCEPTION_POINTERS* exception)
	{
		static std::atomic<int> logged {0};
		const EXCEPTION_RECORD* record = exception->ExceptionRecord;
		const uintptr_t at = uintptr_t(record->ExceptionAddress);
		if (record->ExceptionCode != EXCEPTION_ACCESS_VIOLATION || at < 0x10000000 || at >= 0x11400000 || logged >= 8)
			return EXCEPTION_CONTINUE_SEARCH;
		++logged;
		const CONTEXT* context = exception->ContextRecord;
		proxyLog("fault: access violation at 0x%08X (%s 0x%08X), thread %lu, eax %08lX ecx %08lX edx %08lX esi %08lX edi %08lX",
			unsigned(at), record->ExceptionInformation[0] ? "write" : "read", unsigned(record->ExceptionInformation[1]),
			GetCurrentThreadId(), context->Eax, context->Ecx, context->Edx, context->Esi, context->Edi);
		char line[512] {};
		int length = 0;
		const auto* stack = reinterpret_cast<const uintptr_t*>(context->Esp);
		for (int i = 0, shown = 0; i < 512 && shown < 24; ++i)
		{
			uintptr_t value = 0;
			__try
			{
				value = stack[i];
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				break;
			}
			if (value >= 0x10001000 && value < 0x10B00000)
			{
				length += sprintf_s(line + length, sizeof(line) - length, " %08X", unsigned(value));
				++shown;
			}
		}
		proxyLog("fault: stack%s", line);
		return EXCEPTION_CONTINUE_SEARCH;
	}
}

namespace gamecontrol
{
	void attach(HWND window)
	{
		static PVOID handler = AddVectoredExceptionHandler(0, &logFault);
		(void)handler;
		controlWindow = window;
		mainThread = GetWindowThreadProcessId(window, nullptr);
		proxyLog("control: window %p, its thread %lu", static_cast<void*>(window), mainThread);
	}

	void onPresent()
	{
		if (presentThread == 0)
		{
			presentThread = GetCurrentThreadId();
			proxyLog("control: first present on thread %lu", presentThread);
		}
		if (controlWindow == nullptr || ++presentCount % 2 != 0 || wakePosted)
			return;
		if (GetFileAttributesA(REQUEST_FILE) != INVALID_FILE_ATTRIBUTES)
		{
			wakePosted = true;
			PostMessageW(controlWindow, WAKE_MESSAGE, 0, 0);
		}
	}

	bool onMessage(HWND, UINT message)
	{
		if (message != WAKE_MESSAGE)
			return false;
		wakePosted = false;
		if (GetFileAttributesA(REQUEST_FILE) == INVALID_FILE_ATTRIBUTES)
			return true;
		const std::string request = readRequest();
		std::string output;
		const bool ok = execute(request, output);
		answer(ok, output);
		DeleteFileA(REQUEST_FILE);
		return true;
	}

	void hookInput()
	{
		static bool done = false;
		if (done)
			return;
		done = true;
		const HMODULE module = LoadLibraryW(L"dinput8.dll");
		using CreateFunction = HRESULT(WINAPI*)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);
		const auto create = module != nullptr ? reinterpret_cast<CreateFunction>(GetProcAddress(module, "DirectInput8Create")) : nullptr;
		if (create == nullptr)
			return proxyLog("input: no DirectInput8Create");
		// Our own keyboard and mouse devices only lend their vtables, which every device of the module shares
		const IID* interfaces[] = {&IID_IDirectInput8A, &IID_IDirectInput8W};
		const GUID* devices[] = {&GUID_SysKeyboard, &GUID_SysMouse};
		for (const IID* id : interfaces)
		{
			IDirectInput8A* input = nullptr;
			if (FAILED(create(GetModuleHandleW(nullptr), DIRECTINPUT_VERSION, *id, reinterpret_cast<LPVOID*>(&input), nullptr)))
				continue;
			for (const GUID* guid : devices)
			{
				IDirectInputDevice8A* device = nullptr;
				if (FAILED(input->lpVtbl->CreateDevice(input, *guid, &device, nullptr)))
					continue;
				hookTable(device->lpVtbl);
				device->lpVtbl->Release(device);
			}
			input->lpVtbl->Release(input);
		}
		proxyLog("input: %u device vtables hooked", unsigned(hookedCount));
	}
}
