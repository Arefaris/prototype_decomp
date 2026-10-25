// The game object functions of the scripts (unit 0x10867B80 - 0x1086C900, no assert path: the file name and every
// name here are guesses): the native function objects the scripts call (go_*) and the message classes they send.
// This part is the script functions' own instantiations of engine::Function1..4 (RTTI names Function2<void, LuaGOH,
// Name> and so on): each of them has its constructor, its Call and its Invoke here.
#include "code/container/arrayfixed.h"
#include "code/core/name.h"
#include "code/core/strings.h"
#include "code/core/thread.h"
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/genericscriptvalue.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/gameobjectmessages.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/engine/scenariomessage.h"
#include "code/engine/system/streampackage.h"
#include "code/engine/luascriptmanager.h"
#include "code/lua/lua.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"
#include "code/math/worldbounds.h"

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

	// The name of the motion context (0x111C17D0)
	extern const char* gMotionContextName;
	// The name of the game objects' inventory (0x11283700)
	extern content::ObjectName gGameObjectsName;
	// 0x108024C0 / 0x108034C0 (luascriptmanager.cpp): the name a script passed, the game object it passed
	void LuaGetNameArgument(lua_State* L, int index, core::Name<core::CaseSensitiveKey>* name);
	GameObject* LuaToGameObject(lua_State* L, int index);
	// 0x10853890 (another unit): the service pump, and 0x10853B30: the object log call, which does nothing
	class ServicePump;
	ServicePump* GetServicePump();
	void LogGameObject(GameObject* gameObject, const char* text);

	// The access to a named attribute of type T (the units that write attributes keep their own copies: int, float
	// and bool here)
	template<class T> AttributeWriter<T> GameObject::GetAttributeWriter(const content::ObjectName& name)
	{
		BaseAttribute* attribute = FindAttribute(name);
		if (attribute != 0)
		{
			T* value = &static_cast<Attribute<T>*>(attribute)->Get();
			return AttributeWriter<T>(value, name, this);
		}
		return AttributeWriter<T>();
	}

	// The destructors of the three writers (they notify the object when a value was written) are the compiler's
	// FUNCTION: ENGINE 0x1086B210
	// FUNCTION: ENGINE 0x1086B230
	// FUNCTION: ENGINE 0x1086B250
	// FUNCTION: ENGINE 0x1086B270
	template AttributeWriter<int> GameObject::GetAttributeWriter<int>(const content::ObjectName&);
	// FUNCTION: ENGINE 0x1086B2D0
	template AttributeWriter<float> GameObject::GetAttributeWriter<float>(const content::ObjectName&);
	// FUNCTION: ENGINE 0x1086B330
	template AttributeWriter<bool> GameObject::GetAttributeWriter<bool>(const content::ObjectName&);
	// The writer of a script value is made here from the attribute lookup
	template<> void GameObject::SetAttribute<GenericScriptValue>(const content::ObjectName& name,
		const GenericScriptValue& value, bool unknown);
	// and the one of a script value is expanded where it is used
	template<> inline AttributeWriter<GenericScriptValue> GameObject::GetAttributeWriter<GenericScriptValue>(
		const content::ObjectName& name)
	{
		BaseAttribute* attribute = FindAttribute(name);
		if (attribute != 0)
		{
			GenericScriptValue* value = &static_cast<Attribute<GenericScriptValue>*>(attribute)->Get();
			return AttributeWriter<GenericScriptValue>(value, name, this);
		}
		return AttributeWriter<GenericScriptValue>();
	}
	// The writer of a vector comes from another unit (0x10257690)
	template<> AttributeWriter<math::Vector> GameObject::GetAttributeWriter<math::Vector>(const content::ObjectName&);
	// and the one of a name too (0x10081FE0)
	template<> AttributeWriter<ScriptName> GameObject::GetAttributeWriter<ScriptName>(const content::ObjectName&);

	// 0x1020A2E0 (the kept copy the other units' calls reach): the iterator moves to the next handle whose object is
	// still there
	inline void HandleIterator::SkipInvalid()
	{
		GameObjectHandle* end = array->end;
		GameObjectHandle* item = handle;
		if (item != end)
		{
			do
			{
				unsigned short index = item->index;
				if (index != 0xFFFF)
				{
					GameObjectEntry* entry = &GetGameObjectEntries()[index];
					if (entry->serial == item->serial && entry->object != 0)
					{
						break;
					}
				}
				item++;
			}
			while (item != end);
		}
		handle = item;
	}

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

	// FUNCTION: ENGINE 0x1086A570
	math::Vector go_GetPosition(LuaGOH object)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			const math::Matrix& transform = gameObject->transform->value;
			return math::Vector(transform.m[3][0], transform.m[3][1], transform.m[3][2]);
		}
		SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
		return math::Vector(3.402823466e+38f, 3.402823466e+38f, 3.402823466e+38f);
	}

	// FUNCTION: ENGINE 0x1086A600
	math::Vector go_GetOrientation(LuaGOH object)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			const math::Matrix& transform = gameObject->transform->value;
			return -math::Vector(transform.m[2][0], transform.m[2][1], transform.m[2][2]);
		}
		SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
		return math::Vector(3.402823466e+38f, 3.402823466e+38f, 3.402823466e+38f);
	}

	// FUNCTION: ENGINE 0x1086A6B0
	math::Vector go_GetPositionByName(ScriptName name)
	{
		GameObject* gameObject = FindGameObject(name, *(const ScriptName*)"").Get();
		if (gameObject != 0)
		{
			const math::Matrix& transform = gameObject->transform->value;
			return math::Vector(transform.m[3][0], transform.m[3][1], transform.m[3][2]);
		}
		SetScriptError(GetScriptManager(), "Could not find GameObject '%s'", name.GetText());
		return math::Vector(3.402823466e+38f, 3.402823466e+38f, 3.402823466e+38f);
	}

	// FUNCTION: ENGINE 0x1086A750
	math::Vector go_GetOrientationByName(ScriptName name)
	{
		GameObject* gameObject = FindGameObject(name, *(const ScriptName*)"").Get();
		if (gameObject != 0)
		{
			const math::Matrix& transform = gameObject->transform->value;
			return -math::Vector(transform.m[2][0], transform.m[2][1], transform.m[2][2]);
		}
		SetScriptError(GetScriptManager(), "Could not find GameObject '%s'", name.GetText());
		return math::Vector(3.402823466e+38f, 3.402823466e+38f, 3.402823466e+38f);
	}

	// FUNCTION: ENGINE 0x10869D30
	void go_Reset(LuaGOH object)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			ResetMessage message;
			gameObject->SendMessage(&message);
		}
	}

	// FUNCTION: ENGINE 0x10869FF0
	ScriptName go_GetUIDAttr(LuaGOH object, ScriptName name)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject == 0)
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
			return ScriptName((const char*)0, 1);
		}
		BaseAttribute* attribute = gameObject->FindAttribute(name);
		if (attribute != 0)
		{
			ScriptName* value = &static_cast<Attribute<ScriptName>*>(attribute)->value;
			if (value != 0)
			{
				return *value;
			}
		}
		return ScriptName();
	}

	// FUNCTION: ENGINE 0x1086A810
	void go_SetBroadcastStateChanges(LuaGOH object, bool broadcast)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			SetBroadcastStateChangesMessage message(broadcast);
			gameObject->SendMessage(&message);
			return;
		}
		SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
	}

	// FUNCTION: ENGINE 0x1086AB60
	void phys_EnablePhysics(LuaGOH object, bool enabled)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			PhysicsSetEnabledMessage message(enabled);
			gameObject->SendMessage(&message);
			return;
		}
		SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
	}

	// FUNCTION: ENGINE 0x1086ABF0
	void phys_WakeUpObject(LuaGOH object)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			PhysicsWakeUpMessage message;
			gameObject->SendMessage(&message);
			return;
		}
		SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
	}

	// FUNCTION: ENGINE 0x1086AC80
	void phys_SetLinearVelocity(LuaGOH object, math::Vector velocity, int mode)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			PhysicsSetLinearVelocityMessage message(velocity, mode);
			gameObject->SendMessage(&message);
			return;
		}
		SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
	}

	// FUNCTION: ENGINE 0x1086AD30
	void phys_SetAngularVelocity(LuaGOH object, math::Vector velocity, int mode)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			PhysicsSetAngularVelocityMessage message(velocity, mode);
			gameObject->SendMessage(&message);
			return;
		}
		SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
	}

	// FUNCTION: ENGINE 0x1086AFE0
	void go_LockCharacterIntention(LuaGOH object, bool locked)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			CharacterIntentionLockMessage message(locked);
			gameObject->SendMessage(&message);
			return;
		}
		SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
	}

	// FUNCTION: ENGINE 0x1086B070
	void go_ClearCharacterIntention(LuaGOH object)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			CharacterIntentionClearMessage message;
			gameObject->SendMessage(&message);
			return;
		}
		SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
	}

	// The engine's go_AddTag and go_RemoveTag call the router functions declared as RouterRemove and RouterQuery
	// (0x107EE3E0 / 0x107EE400): the declarations' names are the other way round
	// FUNCTION: ENGINE 0x1086ADE0
	void go_AddTag(LuaGOH object, ScriptName tag)
	{
		GameObjectHandle handle = DeserializeHandle(object);
		if (!handle.IsValid())
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
			return;
		}
		handle.RouterRemove(*static_cast<const MessageListeners*>(&tag));
	}

	// FUNCTION: ENGINE 0x1086AE40
	void go_RemoveTag(LuaGOH object, ScriptName tag)
	{
		GameObjectHandle handle = DeserializeHandle(object);
		if (!handle.IsValid())
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
			return;
		}
		handle.RouterQuery(*static_cast<const MessageListeners*>(&tag));
	}

	// FUNCTION: ENGINE 0x1086BB00
	void go_SetIntAttr(LuaGOH object, ScriptName name, int value)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject == 0)
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
			return;
		}
		AttributeWriter<int> writer = gameObject->GetAttributeWriter<int>(name);
		if (writer.value != 0)
		{
			*writer.value = value;
		}
		else
		{
			gameObject->SetAttribute(name, value, false);
		}
	}

	// FUNCTION: ENGINE 0x1086BBA0
	void go_SetFloatAttr(LuaGOH object, ScriptName name, float value)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject == 0)
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
			return;
		}
		AttributeWriter<float> writer = gameObject->GetAttributeWriter<float>(name);
		if (writer.value != 0)
		{
			*writer.value = value;
		}
		else
		{
			gameObject->SetAttribute(name, value, false);
		}
	}

	// FUNCTION: ENGINE 0x1086BDF0
	void go_SetVectorAttr(LuaGOH object, ScriptName name, math::Vector value)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject == 0)
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
			return;
		}
		AttributeWriter<math::Vector> writer = gameObject->GetAttributeWriter<math::Vector>(name);
		if (writer.value != 0)
		{
			math::Vector* target = writer.value;
			target->x = value.x;
			target->y = value.y;
			target->z = value.z;
		}
		else
		{
			gameObject->SetAttribute(name, value, false);
		}
	}

	// The messages the unit keeps constructors, destructors and deleting destructors of (the compiler's, out of line)
	// FUNCTION: ENGINE 0x10867B80
	// FUNCTION: ENGINE 0x10867BB0
	// FUNCTION: ENGINE 0x10867FC0
	// FUNCTION: ENGINE 0x10867BC0
	// FUNCTION: ENGINE 0x10867BF0
	// FUNCTION: ENGINE 0x10867FE0
	// FUNCTION: ENGINE 0x10867C00
	// FUNCTION: ENGINE 0x10867C20
	// FUNCTION: ENGINE 0x10868000
	// FUNCTION: ENGINE 0x10867C30
	// FUNCTION: ENGINE 0x10867C60
	// FUNCTION: ENGINE 0x10868020

	// FUNCTION: ENGINE 0x10868540
	void PlayMotionBranch(GameObject* gameObject, const char* path, int mode, bool flag)
	{
		if (gameObject == 0)
		{
			return;
		}
		LoadListeners* listeners = gLoadListeners;
		fight::TrackRegistry* context = listeners->FindContext(ScriptName(gMotionContextName, 1));
		fight::Branch* table = context->branches;
		fight::Branch* branch = table->FindInTree(path);
		if (branch != 0)
		{
			PlayBranchMessage message(branch, mode, flag);
			gameObject->SendMessage(&message);
			return;
		}
		SetScriptError(GetScriptManager(), "PlayMotionBranchByPath: Could not find branch '%s'", path);
	}

	// FUNCTION: ENGINE 0x1086A9C0
	void go_PlayMotionBranchByPath(LuaGOH object, const char* path, int mode, bool flag)
	{
		if (path != 0)
		{
			GameObject* gameObject = DeserializeHandle(object).Get();
			if (gameObject != 0)
			{
				PlayMotionBranch(gameObject, path, mode, flag);
				return;
			}
			SetScriptError(GetScriptManager(), "PlayMotionBranchByPath: Invalid GameObjectHandle");
			return;
		}
		SetScriptError(GetScriptManager(), "PlayMotionBranchByPath: Invalid path");
	}

	// FUNCTION: ENGINE 0x1086AA50
	// EQUIVALENT: the shared tail selects the message into a register where the engine pushes each one directly, 93.7 %
	bool go_IsPlayingBranchByPath(LuaGOH object, const char* path, bool exact)
	{
		if (path != 0)
		{
			GameObject* gameObject = DeserializeHandle(object).Get();
			if (gameObject != 0)
			{
				LoadListeners* listeners = gLoadListeners;
				fight::TrackRegistry* context = listeners->FindContext(ScriptName(gMotionContextName, 1));
				fight::Branch* table = context->branches;
				fight::Branch* branch = table->FindInTree(path);
				if (branch != 0)
				{
					IsPlayingBranchMessage message(branch, exact);
					gameObject->PostMessage(&message);
					return message.playing;
				}
				SetScriptError(GetScriptManager(), "IsPlayingMotionBranchByPath: Could not find branch '%s'", path);
				return false;
			}
		}
		SetScriptError(GetScriptManager(), path != 0 ? "IsPlayingMotionBranchByPath: Invalid GameObjectHandle" :
			"IsPlayingMotionBranchByPath: Invalid path");
		return false;
	}

	// FUNCTION: ENGINE 0x10869800
	int go_IsValid(lua_State* L)
	{
		if (lua_type(L, 1) != LUA_TNIL)
		{
			if (lua_type(L, 1) == LUA_TLIGHTUSERDATA)
			{
				LuaGOH object;
				object.value = (unsigned int)lua_touserdata(L, 1);
				GameObject* gameObject = DeserializeHandle(object).Get();
				lua_pushboolean(L, gameObject != 0);
				return 1;
			}
		}
		lua_pushboolean(L, 0);
		return 1;
	}

	// FUNCTION: ENGINE 0x10869DA0
	// EQUIVALENT: the block that serves a found object is laid out before the one that pushes nil, the engine's after it, 81.2 %
	int go_FindGOHByName(lua_State* L)
	{
		ScriptName name;
		LuaGetNameArgument(L, 1, &name);
		GameObjectHandle handle = SearchGameObject(name, gGameObjectsName);
		if (handle.IsValid() || (handle = FindGameObject(name, *(const ScriptName*)""), handle.IsValid()))
		{
			LuaGOH saved = SerializeHandle(handle);
			lua_pushlightuserdata(L, (void*)saved.value);
			return 1;
		}
		lua_pushnil(L);
		return 1;
	}

	// The engine's go_AddTag, go_RemoveTag and go_HasTag call the router functions declared as RouterRemove,
	// RouterQuery and RouterAdd
	// FUNCTION: ENGINE 0x1086AEA0
	bool go_HasTag(LuaGOH object, ScriptName tag)
	{
		GameObjectHandle handle = DeserializeHandle(object);
		if (!handle.IsValid())
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
			return false;
		}
		return handle.RouterAdd(*static_cast<const MessageListeners*>(&tag));
	}

	// FUNCTION: ENGINE 0x1086AF00
	void gamelink_ObjectLog(LuaGOH object, const char* text)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			GetServicePump();
			LogGameObject(gameObject, text);
		}
	}

	// FUNCTION: ENGINE 0x1086B0F0
	// EQUIVALENT: the engine loads the serial with a movzx where ours moves it into dx, and its message address goes
	// through edx where ours uses eax, 97.4 %
	ScriptName go_GetActiveSupportingLimbName(LuaGOH object)
	{
		ScriptName result;
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			SupportingLimbGetActiveMessage message;
			gameObject->SendMessage(&message);
			if (message.limb != 0 && *message.limb != 0)
			{
				result = (*message.limb)->name;
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x1086B190
	bool go_OnSupportingSurface(LuaGOH object)
	{
		bool result = false;
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			CharacterQueryCollisionStateMessage message;
			gameObject->SendMessage(&message);
			if (message.state != 0)
			{
				result = *message.state;
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10867C80
	int go_SetSimThreadPriorityNormal(lua_State* L)
	{
		core::SetThreadPriority((core::Thread*)core::GetThreadData(), 2);
		return 1;
	}

	// FUNCTION: ENGINE 0x10867CA0
	int go_SetSimThreadPriorityHigh(lua_State* L)
	{
		core::SetThreadPriority((core::Thread*)core::GetThreadData(), 4);
		return 1;
	}

	// FUNCTION: ENGINE 0x10868250
	LuaGOH go_FindGOHByUID(ScriptName uid)
	{
		GameObjectHandle handle = FindGameObject(uid, *(const ScriptName*)"");
		return SerializeHandle(handle);
	}

	// FUNCTION: ENGINE 0x10869F10
	ScriptName go_GetState(LuaGOH object)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			ScriptName second("", 1);
			ScriptName first("", 1);
			GetPlaybackStateMessage message(first, second);
			gameObject->PostMessage(&message);
			return message.state;
		}
		return ScriptName();
	}

	// FUNCTION: ENGINE 0x1086AF50
	void go_PrintFightDiagnostics(LuaGOH object)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			FightPrintDiagnosticsMessage message;
			gameObject->SendMessage(&message);
			return;
		}
		SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
	}

	// FUNCTION: ENGINE 0x1086BD30
	// EQUIVALENT: the engine passes the temporary name of the fallback by the constructor's result where ours takes
	// its address again, 84.0 %
	void go_SetUIDAttr(LuaGOH object, ScriptName name, const char* value)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject == 0)
		{
			SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
			return;
		}
		AttributeWriter<ScriptName> writer = gameObject->GetAttributeWriter<ScriptName>(name);
		if (writer.value != 0)
		{
			ScriptName newValue(value, 1);
			*writer.value = newValue;
		}
		else
		{
			const ScriptName& newValue = ScriptName(value, 1);
			gameObject->SetAttribute(name, newValue, false);
		}
	}

	// FUNCTION: ENGINE 0x10869E70
	// EQUIVALENT: the handle is kept in ecx and the entry address in eax where ours swaps them (cmp cx / cmp ax change
	// the encoding length), 53.8 %
	int go_FindTransientGOHByName(lua_State* L)
	{
		ScriptName name;
		LuaGetNameArgument(L, 1, &name);
		GameObjectHandle handle = SearchGameObject(name, gGameObjectsName);
		if (handle.IsValid())
		{
			LuaGOH saved = SerializeHandle(handle);
			lua_pushlightuserdata(L, (void*)saved.value);
			return 1;
		}
		lua_pushnil(L);
		return 1;
	}

	// FUNCTION: ENGINE 0x1086A8A0
	// EQUIVALENT: the engine pushes the address of the up vector before it computes the facing vector's last two
	// components, and it takes eax where ours takes ecx for the matrix address, 76 %
	void go_Teleport(LuaGOH object, math::Vector position, math::Vector direction)
	{
		GameObject* gameObject = DeserializeHandle(object).Get();
		if (gameObject != 0)
		{
			math::Matrix matrix;
			matrix.Identity();
			matrix.SetTranslation(position);
			if (direction.IsZero())
			{
				SetScriptError(GetScriptManager(), "Must have non-zero direction vector.");
				gameObject->SetTransform(matrix);
				return;
			}
			math::Vector up(0.0f, 1.0f, 0.0f);
			matrix.SetBasis(math::Vector(math::WORLD_MIN - direction.x, math::WORLD_MIN - direction.y,
				math::WORLD_MIN - direction.z), up);
			gameObject->SetTransform(matrix);
			return;
		}
		SetScriptError(GetScriptManager(), "Invalid GameObjectHandle");
	}

	// 0x107EF1D0 (gameobjectsystem.cpp): the list of the channel
	MessageListenerRef GetListeners(MessageListeners* listeners);
	// 0x11276940: the name of the prop whose logic tree is asked (name guessed)
	extern ScriptName gUnknownName11276940;
	// The channel the scenario messages of the scripts go to (0x11315F68)
	extern MessageListeners gScenarioListeners;
	// The text of the script that makes a handle persistable (0x111CF2A4)
	extern const char* gLuaGOHPersistScript;

	// FUNCTION: ENGINE 0x10867CD0
	void CreateLuaGOHMetatable()
	{
		lua_State* L = GetScriptManager()->state;
		lua_pushlightuserdata(L, 0);
		lua_createtable(L, 0, 0);
		lua_pushvalue(L, -1);
		lua_setmetatable(L, -3);
		lua_pushlstring(L, "__index", 7);
		lua_getfield(L, LUA_GLOBALSINDEX, "go_GetGenericAttr");
		lua_rawset(L, -3);
		lua_pushlstring(L, "__newindex", 10);
		lua_getfield(L, LUA_GLOBALSINDEX, "go_SetGenericAttr");
		lua_rawset(L, -3);
		lua_pushlstring(L, "__metatable", 11);
		lua_pushlstring(L, "metatable access protected -- talk to a programmer", 50);
		lua_rawset(L, -3);
		luaL_loadbuffer(L, gLuaGOHPersistScript, core::StrLen(gLuaGOHPersistScript), "=LuaGOHPersistScript");
		lua_pcall(L, 0, LUA_MULTRET, 0);
		lua_pushlstring(L, "__persist", 9);
		lua_insert(L, -2);
		lua_rawset(L, -3);
		lua_settop(L, -3);
	}

	// FUNCTION: ENGINE 0x10868050
	// EQUIVALENT: shrink-wrap (the engine saves ebp in the entry block, ours after the early exit) and the handle
	// argument is built in a pushed slot there where ours pushes the loaded value, 47.3 %
	int scenario_PostEventString(lua_State* L)
	{
		GameObjectHandle handles[4];
		unsigned int count = lua_gettop(L) - 1;
		if ((int)count > 4)
		{
			count = 4;
		}
		for (unsigned int i = 0; i < count; i++)
		{
			if (lua_type(L, 2 + i) != LUA_TLIGHTUSERDATA)
			{
				luaL_argerror(L, 2 + i, "expected GameObjectHandle");
			}
			LuaGOH object;
			object.value = (unsigned int)lua_touserdata(L, 2 + i);
			handles[i] = DeserializeHandle(object);
		}
		ScriptName name;
		LuaGetNameArgument(L, 1, &name);
		StringMessage message(name);
		for (int i = 0; i < 4; i++)
		{
			message.handles[i] = handles[i];
		}
		SendMessage(&message, &gScenarioListeners);
		return 0;
	}

	// FUNCTION: ENGINE 0x10868410
	// EQUIVALENT: the engine's frame is eight bytes smaller: the temporary of the comparison shares the slot of one of
	// the names the message was made from, 95.3 %
	int go_QueryState(lua_State* L)
	{
		const char* prefix = 0;
		const char* state;
		GameObject* gameObject = LuaToGameObject(L, 1);
		if (lua_gettop(L) == 3)
		{
			prefix = luaL_checklstring(L, 2, 0);
			state = luaL_checklstring(L, 3, 0);
		}
		else if (lua_gettop(L) == 2)
		{
			state = luaL_checklstring(L, 2, 0);
		}
		else
		{
			luaL_error(L, "wrong number of arguments");
			lua_pushboolean(L, 0);
			return 1;
		}
		if (gameObject != 0)
		{
			ScriptName second(state, 1);
			ScriptName first(prefix, 1);
			GetPlaybackStateMessage message(first, second);
			gameObject->PostMessage(&message);
			lua_pushboolean(L, message.state == ScriptName(state, 1));
			return 1;
		}
		luaL_error(L, "Invalid GameObjectHandle");
		lua_pushboolean(L, 0);
		return 1;
	}

	// FUNCTION: ENGINE 0x10868280
	// EQUIVALENT: the engine keeps the object in a stack slot (ours in a register, so its frame is four bytes
	// larger) and removes the arguments of the error call before the next call where ours removes both at once, 74.7 %
	int go_SetState(lua_State* L)
	{
		bool toggle = false;
		const char* prefix = 0;
		const char* state;
		GameObject* gameObject = LuaToGameObject(L, 1);
		if (lua_gettop(L) == 4)
		{
			prefix = luaL_checklstring(L, 2, 0);
			state = luaL_checklstring(L, 3, 0);
			toggle = lua_toboolean(L, 4) != 0;
		}
		else if (lua_gettop(L) == 3)
		{
			prefix = luaL_checklstring(L, 2, 0);
			state = luaL_checklstring(L, 3, 0);
		}
		else if (lua_gettop(L) == 2)
		{
			state = luaL_checklstring(L, 2, 0);
		}
		else
		{
			luaL_error(L, "wrong number of arguments");
			lua_pushboolean(L, 0);
			return 1;
		}
		if (gameObject != 0)
		{
			SetPropLogicStateMessage message(ScriptName(prefix, 1), state, !toggle, false, 0.0f);
			gameObject->SendMessage(&message);
			if (!message.succeeded)
			{
				if (prefix != 0)
				{
					luaL_error(L, "Set State failed, prop '%s' has no logic tree state named '%s/%s'",
						gUnknownName11276940.GetText(), prefix, state);
					lua_pushboolean(L, 0);
					return 1;
				}
				luaL_error(L, "Set State failed, prop '%s' has no logic tree state named '%s'",
					gUnknownName11276940.GetText(), state);
				lua_pushboolean(L, 0);
				return 1;
			}
			lua_pushboolean(L, 1);
			return 1;
		}
		luaL_error(L, "Invalid GameObjectHandle");
		lua_pushboolean(L, 0);
		return 1;
	}

	// FUNCTION: ENGINE 0x1086B9A0
	// EQUIVALENT: the engine copies the end iterator into the argument slot of the comparison (a dead store of its
	// array pointer that makes the frame eight bytes larger) and keeps the iterator's handle in a register that is
	// stored back before each call to the iterator's skip, 76.5 %
	int go_GetAllTagged(lua_State* L)
	{
		ScriptName tag;
		LuaGetNameArgument(L, 1, &tag);
		MessageListeners* listeners = static_cast<MessageListeners*>(&tag);
		int count = CountListeners(listeners);
		lua_createtable(L, count, 0);
		if (count > 0)
		{
			int index = 1;
			MessageListenerRef ref = GetListeners(listeners);
			for (HandleIterator it = ref.list != 0 ? ref.list->Begin() : HandleIterator();
				it != (ref.list != 0 ? ref.list->End() : HandleIterator()); ++it)
			{
				LuaGOH saved = SerializeHandle(*it.handle);
				lua_pushlightuserdata(L, (void*)saved.value);
				lua_rawseti(L, -2, index);
				index++;
			}
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x10869B10
	int go_GetGenericAttr(lua_State* L)
	{
		GameObject* gameObject = LuaToGameObject(L, 1);
		ScriptName name;
		LuaGetNameArgument(L, 2, &name);
		BaseAttribute* attribute = gameObject->FindAttribute(name);
		if (attribute != 0)
		{
			GenericScriptValue* value = &static_cast<Attribute<GenericScriptValue>*>(attribute)->value;
			if (value != 0)
			{
				value->PushToLua(L);
				return 1;
			}
		}
		lua_pushnil(L);
		return 1;
	}

	// FUNCTION: ENGINE 0x1086BC50
	int go_SetGenericAttr(lua_State* L)
	{
		GameObject* gameObject = LuaToGameObject(L, 1);
		ScriptName name;
		LuaGetNameArgument(L, 2, &name);
		luaL_checkany(L, 3);
		AttributeWriter<GenericScriptValue> writer = gameObject->GetAttributeWriter<GenericScriptValue>(name);
		if (writer.value != 0)
		{
			writer.value->SetFromLua(L, 3);
		}
		else
		{
			GenericScriptValue value;
			value.SetFromLua(L, 3);
			gameObject->SetAttribute(name, value, false);
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x1086BEB0
	// EQUIVALENT: the engine copies the end iterator into the argument slot of the comparison (a dead store of its
	// array pointer that makes the frame eight bytes larger), 63.5 %
	int go_GetListWithAllTags(lua_State* L)
	{
		container::ArrayFixed<ScriptName, 16> tags;
		char buffer[256];
		core::StrCpy(buffer, lua_tolstring(L, 1, 0));
		for (char* token = core::StrTok(buffer, " "); token != 0; token = core::StrTok(0, " "))
		{
			tags.PushBack(ScriptName(token, 1));
		}
		MessageListeners* first = static_cast<MessageListeners*>(&tags[0]);
		lua_createtable(L, CountListeners(first), 0);
		int index = 1;
		MessageListenerRef ref = GetListeners(first);
		for (HandleIterator it = ref.list != 0 ? ref.list->Begin() : HandleIterator();
			it != (ref.list != 0 ? ref.list->End() : HandleIterator()); ++it)
		{
			bool all = true;
			for (unsigned int i = 1; i < (unsigned int)tags.Size(); i++)
			{
				if (!it.handle->RouterAdd(*static_cast<MessageListeners*>(&tags[i])))
				{
					all = false;
					break;
				}
			}
			if (all)
			{
				LuaGOH saved = SerializeHandle(*it.handle);
				lua_pushlightuserdata(L, (void*)saved.value);
				lua_rawseti(L, -2, index);
				index++;
			}
		}
		return 1;
	}

	// FUNCTION: ENGINE 0x10867C70
	const char* go_GetDebugName(LuaGOH object)
	{
		return 0;
	}

	// 0x11315F50: the owner the game object functions are registered under (name guessed)
	extern int gGameObjectScriptOwner;

	// 0x1082FDC0 / 0x1082C910 (other units)
	void scenario_SetTutorialMode(bool enabled);
	void go_DumpPackageInfo();

	// FUNCTION: ENGINE 0x10867DD0
	void UnregisterGameObjectCommands()
	{
		LuaScriptManager* manager = GetScriptManager();
		manager->Unregister(&gGameObjectScriptOwner);
	}

	// FUNCTION: ENGINE 0x1086C0F0
	void RegisterGameObjectCommands()
	{
		LuaScriptManager* manager = GetScriptManager();
		manager->SetOwner(&gGameObjectScriptOwner);
		manager->Register("go_DeleteAttr", go_DeleteAttr);
		manager->Register("go_Reset", go_Reset);
		manager->Register("go_FindGOHByUID", go_FindGOHByUID);
		manager->Register("go_GetAttrTypeDebug", go_GetAttrTypeDebug);
		manager->Register("go_GetDebugName", go_GetDebugName);
		manager->Register("go_GetDamageScale", go_GetDamageScale);
		manager->Register("go_GetHealth", go_GetHealth);
		manager->Register("go_GetGOHAttr", go_GetGOHAttr);
		manager->Register("go_GetIntAttr", go_GetIntAttr);
		manager->Register("go_GetFloatAttr", go_GetFloatAttr);
		manager->Register("go_GetMaxHealth", go_GetMaxHealth);
		manager->Register("go_GetOrientation", go_GetOrientation);
		manager->Register("go_GetOrientationByName", go_GetOrientationByName);
		manager->Register("go_GetPosition", go_GetPosition);
		manager->Register("go_GetPositionByName", go_GetPositionByName);
		manager->Register("go_GetState", go_GetState);
		manager->Register("go_GetUIDAttr", go_GetUIDAttr);
		manager->Register("go_HasAttr", go_HasAttr);
		manager->Register("go_MatchUIDAttr", go_MatchUIDAttr);
		manager->Register("go_PlayMotionBranchByPath", go_PlayMotionBranchByPath);
		manager->Register("go_IsPlayingBranchByPath", go_IsPlayingBranchByPath);
		manager->Register("go_SetBroadcastStateChanges", go_SetBroadcastStateChanges);
		manager->Register("go_SetDamageable", go_SetDamageable);
		manager->Register("go_SetDamageScale", go_SetDamageScale);
		manager->Register("go_SetHealth", go_SetHealth);
		manager->Register("go_SetIntAttr", go_SetIntAttr);
		manager->Register("go_SetFloatAttr", go_SetFloatAttr);
		manager->Register("go_SetMaxHealth", go_SetMaxHealth);
		manager->Register("go_SetMinHealth", go_SetMinHealth);
		manager->Register("go_SetUIDAttr", go_SetUIDAttr);
		manager->Register("go_GetVectorAttr", go_GetVectorAttr);
		manager->Register("go_SetVectorAttr", go_SetVectorAttr);
		manager->Register("go_Teleport", go_Teleport);
		manager->Register("phys_EnablePhysics", phys_EnablePhysics);
		manager->Register("phys_WakeUpObject", phys_WakeUpObject);
		manager->Register("phys_SetLinearVelocity", phys_SetLinearVelocity);
		manager->Register("phys_SetAngularVelocity", phys_SetAngularVelocity);
		manager->Register("scenario_SetTutorialMode", scenario_SetTutorialMode);
		manager->Register("go_AddTag", go_AddTag);
		manager->Register("go_RemoveTag", go_RemoveTag);
		manager->Register("go_HasTag", go_HasTag);
		manager->Register("gamelink_ObjectLog", gamelink_ObjectLog);
		manager->Register("go_DumpPackageInfo", go_DumpPackageInfo);
		manager->Register("go_GetActiveSupportingLimbName", go_GetActiveSupportingLimbName);
		manager->Register("go_OnSupportingSurface", go_OnSupportingSurface);
		manager->Register("go_PrintFightDiagnostics", go_PrintFightDiagnostics);
		manager->Register("go_LockCharacterIntention", go_LockCharacterIntention);
		manager->Register("go_ClearCharacterIntention", go_ClearCharacterIntention);
		manager->RegisterCFunction("scenario_PostEventString", scenario_PostEventString);
		manager->RegisterCFunction("go_FindGOHByName", go_FindGOHByName);
		manager->RegisterCFunction("go_FindTransientGOHByName", go_FindTransientGOHByName);
		manager->RegisterCFunction("go_IsValid", go_IsValid);
		manager->RegisterCFunction("go_SetState", go_SetState);
		manager->RegisterCFunction("go_QueryState", go_QueryState);
		manager->RegisterCFunction("go_GetAllTagged", go_GetAllTagged);
		manager->RegisterCFunction("go_GetListWithAllTags", go_GetListWithAllTags);
		manager->RegisterCFunction("go_GetGenericAttr", go_GetGenericAttr);
		manager->RegisterCFunction("go_SetGenericAttr", go_SetGenericAttr);
		manager->RegisterCFunction("go_SetSimThreadPriorityNormal", go_SetSimThreadPriorityNormal);
		manager->RegisterCFunction("go_SetSimThreadPriorityHigh", go_SetSimThreadPriorityHigh);
		manager->ClearOwner();
		CreateLuaGOHMetatable();
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10867970
// FUNCTION: ENGINE 0x10867E70
// FUNCTION: ENGINE 0x10867E80
// FUNCTION: ENGINE 0x10867E90
// FUNCTION: ENGINE 0x10867EA0
// FUNCTION: ENGINE 0x10867EC0
// FUNCTION: ENGINE 0x10867EE0
// FUNCTION: ENGINE 0x10868600
// FUNCTION: ENGINE 0x10868670
// FUNCTION: ENGINE 0x10868690
// FUNCTION: ENGINE 0x108686C0
// FUNCTION: ENGINE 0x108686E0
// FUNCTION: ENGINE 0x10868710
// FUNCTION: ENGINE 0x10868730
// FUNCTION: ENGINE 0x1086BAC0
// FUNCTION: ENGINE 0x1086BAD0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102801D0
// FUNCTION: ENGINE 0x10280230
// FUNCTION: ENGINE 0x10280250
// FUNCTION: ENGINE 0x10280280
// FUNCTION: ENGINE 0x102802F0
// FUNCTION: ENGINE 0x10280310
// FUNCTION: ENGINE 0x10280BB0
// FUNCTION: ENGINE 0x10280C10
// FUNCTION: ENGINE 0x10280C60
// FUNCTION: ENGINE 0x10280CB0
// FUNCTION: ENGINE 0x10280D20
// FUNCTION: ENGINE 0x10280D40
// FUNCTION: ENGINE 0x10280D60
// FUNCTION: ENGINE 0x10280DC0
// FUNCTION: ENGINE 0x10280DD0
// FUNCTION: ENGINE 0x10281520
// FUNCTION: ENGINE 0x10281580
// FUNCTION: ENGINE 0x102815B0
// FUNCTION: ENGINE 0x102815F0
// FUNCTION: ENGINE 0x10281670
// FUNCTION: ENGINE 0x102816B0
// FUNCTION: ENGINE 0x102816F0
// FUNCTION: ENGINE 0x10281760
// FUNCTION: ENGINE 0x10281780
// FUNCTION: ENGINE 0x10281A10
// FUNCTION: ENGINE 0x10281A90
// FUNCTION: ENGINE 0x10281B00
// FUNCTION: ENGINE 0x10493D70
// FUNCTION: ENGINE 0x10493D90
// FUNCTION: ENGINE 0x102826C0
// FUNCTION: ENGINE 0x10282720
// FUNCTION: ENGINE 0x10282740
// FUNCTION: ENGINE 0x10282FE0
// FUNCTION: ENGINE 0x10283040
// FUNCTION: ENGINE 0x10283090
// FUNCTION: ENGINE 0x10284010
// FUNCTION: ENGINE 0x10284040
// FUNCTION: ENGINE 0x10284070
// FUNCTION: ENGINE 0x102840A0
// FUNCTION: ENGINE 0x102840D0
// FUNCTION: ENGINE 0x10288FF0
// FUNCTION: ENGINE 0x10289080
// FUNCTION: ENGINE 0x10289490
// FUNCTION: ENGINE 0x10289580
// FUNCTION: ENGINE 0x10289910
// FUNCTION: ENGINE 0x1028A480
