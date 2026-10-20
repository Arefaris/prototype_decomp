// The game object functions of the scripts (unit 0x10867B80 - 0x1086C900, no assert path: the file name and every
// name here are guesses): the native function objects the scripts call (go_*) and the message classes they send.
// This part is the script functions' own instantiations of engine::Function1..4 (RTTI names Function2<void, LuaGOH,
// Name> and so on): each of them has its constructor, its Call and its Invoke here.
#include "code/core/name.h"
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectmessages.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/luascriptmanager.h"
#include "code/math/vector.h"

// FUNCTION: ENGINE 0x10868760
// FUNCTION: ENGINE 0x108687C0
// FUNCTION: ENGINE 0x10868800
template class Function2<void, engine::LuaGOH, core::Name<core::CaseSensitiveKey> >;
// FUNCTION: ENGINE 0x10868840
// FUNCTION: ENGINE 0x10868890
// EQUIVALENT: the temporary of the returned handle has its own frame slot where the engine's shares the dead argument's, 88.3 %
// FUNCTION: ENGINE 0x108688D0
template class Function1<engine::LuaGOH, core::Name<core::CaseSensitiveKey> >;
// FUNCTION: ENGINE 0x10868920
// FUNCTION: ENGINE 0x10868980
// FUNCTION: ENGINE 0x108689C0
template class Function2<const char*, engine::LuaGOH, core::Name<core::CaseSensitiveKey> >;
// FUNCTION: ENGINE 0x10868A10
// FUNCTION: ENGINE 0x10868A70
// FUNCTION: ENGINE 0x10868AC0
template class Function2<engine::LuaGOH, engine::LuaGOH, core::Name<core::CaseSensitiveKey> >;
// FUNCTION: ENGINE 0x10868B10
// FUNCTION: ENGINE 0x10868B70
// FUNCTION: ENGINE 0x10868BB0
template class Function2<int, engine::LuaGOH, core::Name<core::CaseSensitiveKey> >;
// FUNCTION: ENGINE 0x10868C00
// FUNCTION: ENGINE 0x10868C60
// FUNCTION: ENGINE 0x10868CB0
template class Function2<float, engine::LuaGOH, core::Name<core::CaseSensitiveKey> >;
// FUNCTION: ENGINE 0x10868D10
// FUNCTION: ENGINE 0x10868D60
// FUNCTION: ENGINE 0x10868DC0
template class Function1<math::Vector, core::Name<core::CaseSensitiveKey> >;
// FUNCTION: ENGINE 0x10868E20
// FUNCTION: ENGINE 0x10868E80
// EQUIVALENT: the temporary of the returned name has its own frame slot where the engine's shares the dead argument's, 91.7 %
// FUNCTION: ENGINE 0x10868EE0
template class Function2<core::Name<core::CaseSensitiveKey>, engine::LuaGOH, core::Name<core::CaseSensitiveKey> >;
// FUNCTION: ENGINE 0x10868F00
// FUNCTION: ENGINE 0x10868F60
// FUNCTION: ENGINE 0x10868FA0
template class Function2<bool, engine::LuaGOH, core::Name<core::CaseSensitiveKey> >;
// FUNCTION: ENGINE 0x10868FF0
// FUNCTION: ENGINE 0x10869060
// FUNCTION: ENGINE 0x108690B0
template class Function3<bool, engine::LuaGOH, core::Name<core::CaseSensitiveKey>, const char*>;
// FUNCTION: ENGINE 0x10869100
// FUNCTION: ENGINE 0x108691A0
template class Function4<void, engine::LuaGOH, const char*, int, bool>;
// FUNCTION: ENGINE 0x108691D0
// FUNCTION: ENGINE 0x10869240
// FUNCTION: ENGINE 0x10869280
template class Function3<void, engine::LuaGOH, core::Name<core::CaseSensitiveKey>, int>;
// FUNCTION: ENGINE 0x108692C0
// FUNCTION: ENGINE 0x10869330
// FUNCTION: ENGINE 0x10869370
template class Function3<void, engine::LuaGOH, core::Name<core::CaseSensitiveKey>, float>;
// FUNCTION: ENGINE 0x108693C0
// FUNCTION: ENGINE 0x10869430
// FUNCTION: ENGINE 0x10869470
template class Function3<void, engine::LuaGOH, core::Name<core::CaseSensitiveKey>, const char*>;
// FUNCTION: ENGINE 0x108694B0
// FUNCTION: ENGINE 0x10869510
// FUNCTION: ENGINE 0x10869570
template class Function2<math::Vector, engine::LuaGOH, core::Name<core::CaseSensitiveKey> >;
// FUNCTION: ENGINE 0x108695E0
// FUNCTION: ENGINE 0x10869650
// FUNCTION: ENGINE 0x108696B0
template class Function3<void, engine::LuaGOH, core::Name<core::CaseSensitiveKey>, math::Vector>;
// FUNCTION: ENGINE 0x10869710
// FUNCTION: ENGINE 0x10869780
// FUNCTION: ENGINE 0x108697C0
template class Function3<void, engine::LuaGOH, math::Vector, int>;

// The registrations of the script functions: each makes the function object and adds it to the script manager (the
// one-argument form is defined here only: the units that register one call the engine's copies)
template<class R, class A> inline void engine::LuaScriptManager::Register(const char* name, R (*function)(A))
{
	AddFunction(name, new Function1<R, A>(name, function));
}

typedef core::Name<core::CaseSensitiveKey> ScriptName;

// FUNCTION: ENGINE 0x1086B390
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, ScriptName>(const char*,
	void (*)(engine::LuaGOH, ScriptName));
// FUNCTION: ENGINE 0x1086B3E0
template void engine::LuaScriptManager::Register<engine::LuaGOH, ScriptName>(const char*,
	engine::LuaGOH (*)(ScriptName));
// FUNCTION: ENGINE 0x1086B460
template void engine::LuaScriptManager::Register<const char*, engine::LuaGOH, ScriptName>(const char*,
	const char* (*)(engine::LuaGOH, ScriptName));
// FUNCTION: ENGINE 0x1086B4B0
template void engine::LuaScriptManager::Register<engine::LuaGOH, engine::LuaGOH, ScriptName>(const char*,
	engine::LuaGOH (*)(engine::LuaGOH, ScriptName));
// FUNCTION: ENGINE 0x1086B500
template void engine::LuaScriptManager::Register<int, engine::LuaGOH, ScriptName>(const char*,
	int (*)(engine::LuaGOH, ScriptName));
// FUNCTION: ENGINE 0x1086B550
template void engine::LuaScriptManager::Register<float, engine::LuaGOH, ScriptName>(const char*,
	float (*)(engine::LuaGOH, ScriptName));
// FUNCTION: ENGINE 0x1086B5A0
template void engine::LuaScriptManager::Register<math::Vector, ScriptName>(const char*,
	math::Vector (*)(ScriptName));
// FUNCTION: ENGINE 0x1086B620
template void engine::LuaScriptManager::Register<ScriptName, engine::LuaGOH, ScriptName>(const char*,
	ScriptName (*)(engine::LuaGOH, ScriptName));
// FUNCTION: ENGINE 0x1086B670
template void engine::LuaScriptManager::Register<bool, engine::LuaGOH, ScriptName>(const char*,
	bool (*)(engine::LuaGOH, ScriptName));
// FUNCTION: ENGINE 0x1086B6C0
template void engine::LuaScriptManager::Register<bool, engine::LuaGOH, ScriptName, const char*>(const char*,
	bool (*)(engine::LuaGOH, ScriptName, const char*));
// FUNCTION: ENGINE 0x1086B710
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, const char*, int, bool>(const char*,
	void (*)(engine::LuaGOH, const char*, int, bool));
// FUNCTION: ENGINE 0x1086B760
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, ScriptName, int>(const char*,
	void (*)(engine::LuaGOH, ScriptName, int));
// FUNCTION: ENGINE 0x1086B7B0
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, ScriptName, float>(const char*,
	void (*)(engine::LuaGOH, ScriptName, float));
// FUNCTION: ENGINE 0x1086B800
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, ScriptName, const char*>(const char*,
	void (*)(engine::LuaGOH, ScriptName, const char*));
// FUNCTION: ENGINE 0x1086B850
template void engine::LuaScriptManager::Register<math::Vector, engine::LuaGOH, ScriptName>(const char*,
	math::Vector (*)(engine::LuaGOH, ScriptName));
// FUNCTION: ENGINE 0x1086B8A0
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, ScriptName, math::Vector>(const char*,
	void (*)(engine::LuaGOH, ScriptName, math::Vector));
// FUNCTION: ENGINE 0x1086B8F0
template void engine::LuaScriptManager::Register<void, engine::LuaGOH, math::Vector, int>(const char*,
	void (*)(engine::LuaGOH, math::Vector, int));

namespace math
{
	// 0x11283234: the zero vector the engine copies (name guessed)
	extern const Vector kZeroVector;
}

namespace engine
{
	typedef core::Name<core::CaseSensitiveKey> ScriptName;

	// FUNCTION: ENGINE 0x10869CD0
	void go_DeleteAttr(LuaGOH object, ScriptName name)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject == 0)
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
			return;
		}
		gameObject->RemoveDynamicAttribute(name);
	}

	// FUNCTION: ENGINE 0x10869A30
	int go_GetIntAttr(LuaGOH object, ScriptName name)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject == 0)
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
			return 0;
		}
		BaseAttribute* attribute = gameObject->FindAttribute(name);
		if (attribute != 0)
		{
			int* value = &static_cast<Attribute<int>*>(attribute)->value;
			if (value != 0)
			{
				return *value;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x108698B0
	bool go_HasAttr(LuaGOH object, ScriptName name)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject == 0)
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
			return false;
		}
		return gameObject->FindAttribute(name) != 0;
	}

	// FUNCTION: ENGINE 0x10869920
	const char* go_GetAttrTypeDebug(LuaGOH object, ScriptName name)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject == 0)
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
			return 0;
		}
		return "unknown";
	}

	// FUNCTION: ENGINE 0x10869AA0
	float go_GetFloatAttr(LuaGOH object, ScriptName name)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject == 0)
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
			return 0.0f;
		}
		BaseAttribute* attribute = gameObject->FindAttribute(name);
		if (attribute != 0)
		{
			float* value = &static_cast<Attribute<float>*>(attribute)->value;
			if (value != 0)
			{
				return *value;
			}
		}
		return 0.0f;
	}

	// FUNCTION: ENGINE 0x10869C20
	math::Vector go_GetVectorAttr(LuaGOH object, ScriptName name)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject == 0)
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
			return math::kZeroVector;
		}
		BaseAttribute* attribute = gameObject->FindAttribute(name);
		if (attribute != 0)
		{
			math::Vector* value = &static_cast<Attribute<math::Vector>*>(attribute)->value;
			if (value != 0)
			{
				return *value;
			}
		}
		return math::kZeroVector;
	}

	// FUNCTION: ENGINE 0x10869980
	LuaGOH go_GetGOHAttr(LuaGOH object, ScriptName name)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		GameObjectHandle result;
		if (gameObject == 0)
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
			LuaGOH invalid;
			invalid.value = 0;
			return invalid;
		}
		BaseAttribute* attribute = gameObject->FindAttribute(name);
		if (attribute != 0)
		{
			GameObjectHandle* value = &static_cast<Attribute<GameObjectHandle>*>(attribute)->value;
			if (value != 0)
			{
				result = *value;
				return SerializeHandle(result);
			}
		}
		return SerializeHandle(result);
	}

	// FUNCTION: ENGINE 0x10869B80
	bool go_MatchUIDAttr(LuaGOH object, ScriptName name, const char* uid)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject == 0)
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
			return false;
		}
		BaseAttribute* attribute = gameObject->FindAttribute(name);
		if (attribute != 0)
		{
			ScriptName* value = &static_cast<Attribute<ScriptName>*>(attribute)->value;
			if (value != 0)
			{
				ScriptName expected(uid, 1);
				return *value == expected;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1086A090
	void go_SetHealth(LuaGOH object, float health)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			SetHealthMessage message(health);
			gameObject->SendMessage(&message);
			return;
		}
		SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
	}

	// FUNCTION: ENGINE 0x1086A120
	float go_GetHealth(LuaGOH object)
	{
		float result = 3.402823466e+38f;
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			GetHealthMessage message;
			gameObject->PostMessage(&message);
			result = message.health;
		}
		else
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
		}
		return result;
	}

	// FUNCTION: ENGINE 0x1086A1D0
	void go_SetMaxHealth(LuaGOH object, float maxHealth)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			SetMaxHealthMessage message(maxHealth);
			gameObject->SendMessage(&message);
			return;
		}
		SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
	}

	// FUNCTION: ENGINE 0x1086A260
	float go_GetMaxHealth(LuaGOH object)
	{
		float result = 3.402823466e+38f;
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			GetHealthMessage message;
			gameObject->PostMessage(&message);
			result = message.maxHealth;
		}
		else
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
		}
		return result;
	}

	// FUNCTION: ENGINE 0x1086A310
	void go_SetMinHealth(LuaGOH object, float minHealth)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			SetMinHealthMessage message(minHealth);
			gameObject->SendMessage(&message);
			return;
		}
		SetScriptError(GetScriptManager(), "Invalid GameObjectHandle in go_SetMinHealth");
	}

	// FUNCTION: ENGINE 0x1086A3A0
	void go_SetDamageScale(LuaGOH object, float scale)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			SetDamageScaleMessage message(scale);
			gameObject->SendMessage(&message);
			return;
		}
		SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
	}

	// FUNCTION: ENGINE 0x1086A430
	float go_GetDamageScale(LuaGOH object)
	{
		float result = 1.0f;
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			GetDamageScaleMessage message;
			gameObject->PostMessage(&message);
			result = message.scale;
		}
		else
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
		}
		return result;
	}

	// FUNCTION: ENGINE 0x1086A4E0
	void go_SetDamageable(LuaGOH object, bool damageable)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			SetUndamageableMessage message(!damageable);
			gameObject->SendMessage(&message);
			return;
		}
		SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
	}
}
