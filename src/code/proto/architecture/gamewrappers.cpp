// The script method wrappers of the game top level of proto (CloudManager, GameDatabaseHelper, InGameState): the units that
// register methods of these classes with the script context instantiate engine::Function's Method and Closure templates for
// their signatures. The classes themselves are other files'; they are declared here as far as the signatures need them (a
// class with several bases has method pointers of two words, which the declarations below ask for).
#include "code/engine/function.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/math/vector.h"
#include "code/core/name.h"

namespace proto
{
	class CloudSpawnerBase
	{
	public:
		enum Priority
		{
			PriorityFirst
		};
	};
	class CloudManager
	{
	};
	class GameDatabaseHelperBase0
	{
	};
	class GameDatabaseHelperBase1
	{
	};
	class GameDatabaseHelper : public GameDatabaseHelperBase0, public GameDatabaseHelperBase1
	{
	};
	class InGameStateBase0
	{
	};
	class InGameStateBase1
	{
	};
	class InGameState : public InGameStateBase0, public InGameStateBase1
	{
	};
}

template class Method1<proto::CloudManager, bool, const char*>;
template class Closure1<proto::CloudManager, bool, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, bool, const char*>(const char*,
	proto::CloudManager*, bool (proto::CloudManager::*)(const char*));

template class Method1<proto::CloudManager, unsigned int, const char*>;
template class Closure1<proto::CloudManager, unsigned int, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, unsigned int, const char*>(const char*,
	proto::CloudManager*, unsigned int (proto::CloudManager::*)(const char*));

template class Method2<proto::CloudManager, void, const char*, proto::CloudSpawnerBase::Priority>;
template class Closure2<proto::CloudManager, void, const char*, proto::CloudSpawnerBase::Priority>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, void, const char*, proto::CloudSpawnerBase::Priority>(const char*,
	proto::CloudManager*, void (proto::CloudManager::*)(const char*, proto::CloudSpawnerBase::Priority));

template class Method1<proto::CloudManager, void, const char*>;
template class Closure1<proto::CloudManager, void, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, void, const char*>(const char*,
	proto::CloudManager*, void (proto::CloudManager::*)(const char*));

template class Method2<proto::CloudManager, void, const char*, bool>;
template class Closure2<proto::CloudManager, void, const char*, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, void, const char*, bool>(const char*,
	proto::CloudManager*, void (proto::CloudManager::*)(const char*, bool));

template class Method1<proto::CloudManager, void, int>;
template class Closure1<proto::CloudManager, void, int>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, void, int>(const char*,
	proto::CloudManager*, void (proto::CloudManager::*)(int));

template class Method2<proto::CloudManager, void, engine::LuaGOH, proto::CloudSpawnerBase::Priority>;
template class Closure2<proto::CloudManager, void, engine::LuaGOH, proto::CloudSpawnerBase::Priority>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, void, engine::LuaGOH, proto::CloudSpawnerBase::Priority>(const char*,
	proto::CloudManager*, void (proto::CloudManager::*)(engine::LuaGOH, proto::CloudSpawnerBase::Priority));

template class Method1<proto::CloudManager, void, engine::LuaGOH>;
template class Closure1<proto::CloudManager, void, engine::LuaGOH>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, void, engine::LuaGOH>(const char*,
	proto::CloudManager*, void (proto::CloudManager::*)(engine::LuaGOH));

template class Method2<proto::CloudManager, void, core::Name<core::CaseSensitiveKey>, proto::CloudSpawnerBase::Priority>;
template class Closure2<proto::CloudManager, void, core::Name<core::CaseSensitiveKey>, proto::CloudSpawnerBase::Priority>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, void, core::Name<core::CaseSensitiveKey>, proto::CloudSpawnerBase::Priority>(const char*,
	proto::CloudManager*, void (proto::CloudManager::*)(core::Name<core::CaseSensitiveKey>, proto::CloudSpawnerBase::Priority));

template class Method1<proto::CloudManager, void, core::Name<core::CaseSensitiveKey>>;
template class Closure1<proto::CloudManager, void, core::Name<core::CaseSensitiveKey>>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, void, core::Name<core::CaseSensitiveKey>>(const char*,
	proto::CloudManager*, void (proto::CloudManager::*)(core::Name<core::CaseSensitiveKey>));

template class Method2<proto::CloudManager, core::Name<core::CaseSensitiveKey>, const char*, const char*>;
template class Closure2<proto::CloudManager, core::Name<core::CaseSensitiveKey>, const char*, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, core::Name<core::CaseSensitiveKey>, const char*, const char*>(const char*,
	proto::CloudManager*, core::Name<core::CaseSensitiveKey> (proto::CloudManager::*)(const char*, const char*));

template class Method1<proto::CloudManager, engine::LuaGOH, core::Name<core::CaseSensitiveKey>>;
template class Closure1<proto::CloudManager, engine::LuaGOH, core::Name<core::CaseSensitiveKey>>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, engine::LuaGOH, core::Name<core::CaseSensitiveKey>>(const char*,
	proto::CloudManager*, engine::LuaGOH (proto::CloudManager::*)(core::Name<core::CaseSensitiveKey>));

template class Method1<proto::CloudManager, bool, core::Name<core::CaseSensitiveKey>>;
template class Closure1<proto::CloudManager, bool, core::Name<core::CaseSensitiveKey>>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, bool, core::Name<core::CaseSensitiveKey>>(const char*,
	proto::CloudManager*, bool (proto::CloudManager::*)(core::Name<core::CaseSensitiveKey>));

template class Method1<proto::CloudManager, math::Vector, engine::LuaGOH>;
template class Closure1<proto::CloudManager, math::Vector, engine::LuaGOH>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, math::Vector, engine::LuaGOH>(const char*,
	proto::CloudManager*, math::Vector (proto::CloudManager::*)(engine::LuaGOH));

template class Method3<proto::CloudManager, void, engine::LuaGOH, math::Vector, math::Vector>;
template class Closure3<proto::CloudManager, void, engine::LuaGOH, math::Vector, math::Vector>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, void, engine::LuaGOH, math::Vector, math::Vector>(const char*,
	proto::CloudManager*, void (proto::CloudManager::*)(engine::LuaGOH, math::Vector, math::Vector));

template class Method2<proto::CloudManager, void, engine::LuaGOH, bool>;
template class Closure2<proto::CloudManager, void, engine::LuaGOH, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, void, engine::LuaGOH, bool>(const char*,
	proto::CloudManager*, void (proto::CloudManager::*)(engine::LuaGOH, bool));

template class Method1<proto::CloudManager, bool, engine::LuaGOH>;
template class Closure1<proto::CloudManager, bool, engine::LuaGOH>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, bool, engine::LuaGOH>(const char*,
	proto::CloudManager*, bool (proto::CloudManager::*)(engine::LuaGOH));

template class Method1<proto::CloudManager, math::Vector, const char*>;
template class Closure1<proto::CloudManager, math::Vector, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, math::Vector, const char*>(const char*,
	proto::CloudManager*, math::Vector (proto::CloudManager::*)(const char*));

template class Method1<proto::CloudManager, float, engine::LuaGOH>;
template class Closure1<proto::CloudManager, float, engine::LuaGOH>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, float, engine::LuaGOH>(const char*,
	proto::CloudManager*, float (proto::CloudManager::*)(engine::LuaGOH));

template class Method2<proto::CloudManager, void, engine::LuaGOH, float>;
template class Closure2<proto::CloudManager, void, engine::LuaGOH, float>;
template void engine::LuaScriptManager::RegisterMethod<proto::CloudManager, void, engine::LuaGOH, float>(const char*,
	proto::CloudManager*, void (proto::CloudManager::*)(engine::LuaGOH, float));

#pragma pointers_to_members(full_generality, multiple_inheritance)

template class Method2<proto::GameDatabaseHelper, void, const char*, const char*>;
template class Closure2<proto::GameDatabaseHelper, void, const char*, const char*>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameDatabaseHelper, void, const char*, const char*>(const char*,
	proto::GameDatabaseHelper*, void (proto::GameDatabaseHelper::*)(const char*, const char*));

template class Method0<proto::GameDatabaseHelper, unsigned int>;
template class Closure0<proto::GameDatabaseHelper, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameDatabaseHelper, unsigned int>(const char*,
	proto::GameDatabaseHelper*, unsigned int (proto::GameDatabaseHelper::*)());

template class Method1<proto::GameDatabaseHelper, const char*, unsigned int>;
template class Closure1<proto::GameDatabaseHelper, const char*, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameDatabaseHelper, const char*, unsigned int>(const char*,
	proto::GameDatabaseHelper*, const char* (proto::GameDatabaseHelper::*)(unsigned int));

template class Method2<proto::GameDatabaseHelper, void, const char*, unsigned int>;
template class Closure2<proto::GameDatabaseHelper, void, const char*, unsigned int>;
template void engine::LuaScriptManager::RegisterMethod<proto::GameDatabaseHelper, void, const char*, unsigned int>(const char*,
	proto::GameDatabaseHelper*, void (proto::GameDatabaseHelper::*)(const char*, unsigned int));

template class Method0<proto::InGameState, void>;
template class Closure0<proto::InGameState, void>;
template void engine::LuaScriptManager::RegisterMethod<proto::InGameState, void>(const char*,
	proto::InGameState*, void (proto::InGameState::*)());

template class Method1<proto::InGameState, void, bool>;
template class Closure1<proto::InGameState, void, bool>;
template void engine::LuaScriptManager::RegisterMethod<proto::InGameState, void, bool>(const char*,
	proto::InGameState*, void (proto::InGameState::*)(bool));

