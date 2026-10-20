// The game object functions of the scripts (unit 0x10867B80 - 0x1086C900, no assert path: the file name and every
// name here are guesses): the native function objects the scripts call (go_*) and the message classes they send.
// This part is the script functions' own instantiations of engine::Function1..4 (RTTI names Function2<void, LuaGOH,
// Name> and so on): each of them has its constructor, its Call and its Invoke here.
#include "code/core/name.h"
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/gameobjectmessages.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/gameobject/messagerouter.h"
#include "code/engine/system/streampackage.h"
#include "code/engine/luascriptmanager.h"
#include "code/lua/lua.h"
#include "code/math/matrix.h"
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

	// The name of the motion context (0x111C17D0)
	extern const char* gMotionContextName;
	// The name of the game objects' inventory (0x11283700)
	extern content::ObjectName gGameObjectsName;
	// 0x108024C0 / 0x108034C0 (luascriptmanager.cpp): the name a script passed, the game object it passed
	void LuaGetNameArgument(lua_State* L, int index, core::Name<core::CaseSensitiveKey>* name);
	GameObject* LuaToGameObject(lua_State* L, int index);

	// The access to a named attribute of type T (the units that write attributes keep their own copies: int, float
	// and bool here)
	template<class T> AttributeWriter<T> GameObject::GetAttributeWriter(const content::ObjectName& name)
	{
		BaseAttribute* attribute = FindAttribute(name);
		if (attribute != 0)
		{
			T* value = &static_cast<Attribute<T>*>(attribute)->Get();
			return AttributeWriter<T>(name, this, value);
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
	// The writer of a vector comes from another unit (0x10257690)
	template<> AttributeWriter<math::Vector> GameObject::GetAttributeWriter<math::Vector>(const content::ObjectName&);

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
	// EQUIVALENT: the engine's frame is four bytes larger: its temporary for the handle does not share the slot of the writer
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
	// EQUIVALENT: the engine's frame is four bytes larger: its temporary for the handle does not share the slot of the writer
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
	// EQUIVALENT: the engine's frame is four bytes larger: its temporary for the handle does not share the slot of the writer
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
		fight::TrackRegistry::BranchTable* table = context->branches;
		fight::Branch* branch = table->FindByPath(path);
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
				fight::TrackRegistry::BranchTable* table = context->branches;
				fight::Branch* branch = table->FindByPath(path);
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
}
