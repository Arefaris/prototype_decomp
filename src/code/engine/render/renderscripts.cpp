// The script functions of the renderer (this unit 0x10853250 - 0x10853580; no assert path, the file name is a guess):
// the letterbox and the fades of the cinematics, a few switches of the render debug display (most of which do
// nothing in this build) and the registration of all of them with the script manager.
#include "code/engine/drawableregistry.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"
#include "code/engine/render/async/canvas.h"
#include "code/engine/render/async/shaderparameter.h"
#include "code/lua/lua.h"

// The form without arguments is another unit's (0x10280020), not an inline expansion
template<> void engine::LuaScriptManager::Register<void>(const char* name, void (*function)());

namespace engine
{
	// 0x10826850 / 0x108490D0 (other units): the shadow range hack and the sub-frame interpolation switch of the renderer
	void SetGlobalShadowRangeHack(float value);
	void SetSubframeInterpolation(bool value);

	namespace render
	{
		// The identity under which the renderer's script functions are registered (0x11315380)
		char gRenderScriptsOwner;

		// FUNCTION: ENGINE 0x10853250
		void ScriptLetterBoxOn()
		{
			QueueCanvas108BCAC0(0.1909f, false, 0.0f, false, 0.0f);
		}

		// FUNCTION: ENGINE 0x10853280
		void ScriptLetterBoxOff()
		{
			QueueCanvas108BCB00(true, 0.5f, false, 0.0f);
		}

		// FUNCTION: ENGINE 0x108532A0
		void ScriptFadeToBlack(float time)
		{
			QueueCanvas108BCA10(1.0f, false, 0.0f, true, time, false, false);
		}

		// FUNCTION: ENGINE 0x108532D0
		void ScriptFadeFromBlack(float time)
		{
			QueueCanvas108BCA80(false, 0.0f, true, time, false);
		}

		// FUNCTION: ENGINE 0x108532F0
		void ScriptFadeToWhite(float time)
		{
			QueueCanvas108BCA10(1.0f, false, 0.0f, true, time, true, false);
		}

		// FUNCTION: ENGINE 0x10853320
		void ScriptFadeFromWhite(float time)
		{
			QueueCanvas108BCA80(false, 0.0f, true, time, false);
		}

		// FUNCTION: ENGINE 0x10853340
		void ScriptSaturateToWhite(float time)
		{
			QueueCanvas108BCA10(1.0f, false, 0.0f, true, time, true, true);
		}

		// FUNCTION: ENGINE 0x10853370
		void ScriptDesaturateFromWhite(float time)
		{
			QueueCanvas108BCA80(false, 0.0f, true, time, true);
		}
		// FUNCTION: ENGINE 0x10853390
		void ScriptToggleFrameRate()
		{
		}

		// FUNCTION: ENGINE 0x108533A0
		void ScriptToggleTesterInfo()
		{
		}

		// FUNCTION: ENGINE 0x108533B0
		void ScriptToggleAIInfo()
		{
		}

		// FUNCTION: ENGINE 0x108533C0
		void ScriptNothing()
		{
		}

		// FUNCTION: ENGINE 0x108533D0
		int ScriptDebugDrawGetLayers(lua_State* L)
		{
			lua_createtable(L, 0, 0);
			return 1;
		}

		// FUNCTION: ENGINE 0x108533F0
		void ScriptDebugDrawEnableByIndex(unsigned int index, bool enabled)
		{
		}

		// FUNCTION: ENGINE 0x10853400
		void ScriptDetachMainThread(bool value)
		{
			GetDrawableRegistry()->SetDetachMainThread(value);
		}

		// FUNCTION: ENGINE 0x10853420
		void UnregisterRenderScripts()
		{
			LuaScriptManager* manager = GetScriptManager();
			manager->Unregister(&gRenderScriptsOwner);
		}

		// FUNCTION: ENGINE 0x10853440
		void ScriptEnableFBEffect(const char* name, bool enabled)
		{
			core::Name<core::CaseSensitiveKey> effect(name, 1);
			SetParameterEnabled(effect, enabled);
		}
		// FUNCTION: ENGINE 0x10853560
		void RegisterRenderScripts()
		{
			LuaScriptManager* manager = GetScriptManager();
			manager->SetOwner(&gRenderScriptsOwner);
			manager->Register("nism_LetterBoxOn", ScriptLetterBoxOn);
			manager->Register("nism_LetterBoxOff", ScriptLetterBoxOff);
			manager->Register("nism_FadeToBlack", ScriptFadeToBlack);
			manager->Register("nism_FadeFromBlack", ScriptFadeFromBlack);
			manager->Register("nism_FadeToWhite", ScriptFadeToWhite);
			manager->Register("nism_FadeFromWhite", ScriptFadeFromWhite);
			manager->Register("nism_SaturateToWhite", ScriptSaturateToWhite);
			manager->Register("nism_DesaturateFromWhite", ScriptDesaturateFromWhite);
			manager->Register("rm_EnableFBEffect", ScriptEnableFBEffect);
			manager->Register("rm_SetGlobalShadowRangeHack", SetGlobalShadowRangeHack);
			manager->AddFunction("rm_ToggleFrameRate", new Function0<void>("rm_ToggleFrameRate", ScriptToggleFrameRate));
			manager->AddFunction("rm_ToggleTesterInfo", new Function0<void>("rm_ToggleTesterInfo", ScriptToggleTesterInfo));
			manager->AddFunction("rm_ToggleAIInfo", new Function0<void>("rm_ToggleAIInfo", ScriptToggleAIInfo));
			manager->Register("debugdraw_EnableByIndex", ScriptDebugDrawEnableByIndex);
			manager->Register("render_DetachMainThread", ScriptDetachMainThread);
			manager->Register("render_SubframeInterpolation", SetSubframeInterpolation);
			manager->RegisterCFunction("debugdraw_GetLayers", ScriptDebugDrawGetLayers);
			manager->ClearOwner();
		}
	}
}

template class Function2<void, unsigned int, bool>;
template void engine::LuaScriptManager::Register<void, unsigned int, bool>(const char*, void (*)(unsigned int, bool));

// The wrappers this unit instantiates for debugdraw_EnableByIndex, in address order:
// FUNCTION: ENGINE 0x10853470
// FUNCTION: ENGINE 0x108534D0
// FUNCTION: ENGINE 0x108534F0
// FUNCTION: ENGINE 0x10853510
