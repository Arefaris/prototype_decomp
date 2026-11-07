#include "code/proto/combatbudgetmanager.h"

#include <math.h>
#include <new>

#include "code/engine/camera/director.h"
#include "code/engine/function.h"
#include "code/engine/luascriptmanager.h"
#include "code/pure3d/camera.h"

namespace engine
{
	extern core::Name<core::CaseSensitiveKey> gCombatPriority;
}

namespace proto
{
	CombatBudget::Token::Token(const engine::GameObjectHandle* newHandle, float newPriority, float newTimer)
		: handle(*newHandle), granted(false), timer(newTimer), priority(newPriority)
	{
	}

	// FUNCTION: ENGINE 0x10389E40
	void CombatBudget::Configure(int capacity, int newMax, float newTimeout, int newHeuristic)
	{
		tokens.Create(capacity);
		max = newMax;
		timeout = newTimeout;
		heuristic = newHeuristic;
	}

	// FUNCTION: ENGINE 0x1038A480
	void CombatBudget::ReleaseTokens()
	{
		tokens.Free();
	}

	// FUNCTION: ENGINE 0x10389A60
	CombatBudget::Token* CombatBudget::Find(const engine::GameObjectHandle* handle)
	{
		unsigned int size = tokens.Size();
		for (unsigned int i = 0; i < size; i++)
		{
			if (tokens[i].handle == *handle)
			{
				return &tokens[i];
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10389AB0
	int CombatBudget::CountAtLeast(float value)
	{
		int result = 0;
		unsigned int size = tokens.Size();
		for (unsigned int i = 0; i < size; i++)
		{
			if (value <= tokens[i].priority)
			{
				result++;
			}
		}
		return result;
	}

	// FUNCTION: ENGINE 0x1038A100
	bool CombatBudget::Unknown1038A100(const engine::GameObjectHandle* handle)
	{
		Token* token = Find(handle);
		return token != 0 && token->granted;
	}

	// FUNCTION: ENGINE 0x10389EC0
	// NONMATCHING: the engine looks the handle up twice (IsValid, then a Get of its own) with the master table in edi and this in ebx; ours merges the lookups (47.8 % of the instructions the same)
#ifdef NONMATCHING
	void CombatBudget::Update(float delta)
	{
		Token* token = tokens.begin;
		if (heuristic == 0)
		{
			while (token != tokens.end)
			{
				token->timer -= delta;
				if (token->timer <= 0.0f)
				{
					if (token->handle.IsValid())
					{
						engine::GameObject* object = token->handle.Get();
						Unknown103B9940(object, 0x13, "");
					}
					count--;
					Token* last = tokens.end;
					for (Token* next = token + 1; next != last; next++)
					{
						next[-1] = *next;
					}
					tokens.end--;
				}
				else
				{
					token++;
				}
			}
		}
		else
		{
			while (token != tokens.end)
			{
				token->timer -= delta;
				if (token->timer <= 0.0f || !token->handle.IsValid())
				{
					if (token->granted)
					{
						count--;
						if (token->handle.IsValid())
						{
							engine::GameObject* object = token->handle.Get();
							Unknown103B9940(object, 0x13, "");
						}
					}
					Token* last = tokens.end;
					for (Token* next = token + 1; next != last; next++)
					{
						next[-1] = *next;
					}
					tokens.end--;
				}
				else
				{
					token++;
				}
			}
		}
	}
#endif

	// FUNCTION: ENGINE 0x1038A130
	// NONMATCHING: the locals take other stack slots (91.2 %)
#ifdef NONMATCHING
	float CombatBudget::GetPriority(const engine::GameObjectHandle* handle, ByteFlag granted)
	{
		float weight;
		float scale;
		engine::GameObject* object = handle->Get();
		if (object == 0)
		{
			return -1.0f;
		}
		math::Matrix* matrix = object->transform->GetPointer();
		math::Vector position(matrix->m[3][0], matrix->m[3][1], matrix->m[3][2]);
		float visible;
		float distance = sqrt(Unknown103C0F80(&position));
		if (!(5.0f > distance))
		{
			distance = 5.0f;
		}
		engine::BaseAttribute* attribute = object->FindAttribute(engine::gCombatPriority);
		if (attribute != 0 && &((engine::ConstAttribute<float>*)attribute)->value != 0)
		{
			weight = ((engine::ConstAttribute<float>*)attribute)->value;
		}
		else
		{
			weight = 1.0f;
		}
		bool inside = false;
		for (int i = 0; i < 1; i++)
		{
			pure3d::Camera* camera = (pure3d::Camera*)engine::camera::Director::Get()->GetCameraUnknown44(i, 0);
			if (camera->IsPointInside(&position))
			{
				inside = true;
				break;
			}
		}
		visible = inside ? 2.0f : 1.0f;
		scale = granted.value ? 1.5f : 1.0f;
		return weight / distance * scale * visible;
	}
#endif

	// FUNCTION: ENGINE 0x1038A4C0
	// NONMATCHING: the engine reserves the frame of the flag before the first test, shrink-wrap (56.5 % of the instructions the same, the registers differ)
#ifdef NONMATCHING
	void CombatBudget::Unknown1038A4C0(const engine::GameObjectHandle* handle)
	{
		if (heuristic == 0)

		{
			if (count < max && tokens.Size() < tokens.Capacity())
			{
				Token* token = new (tokens.Grow()) Token(handle, 1.0f, timeout);
				count++;
				token->granted = true;
			}
			return;
		}
		unsigned int size = tokens.Size();
		Token* token = Find(handle);
		ByteFlag granted = {token != 0 && token->granted};
		float priority = GetPriority(handle, granted);
		if (token == 0)
		{
			if (size < tokens.Capacity())
			{
				token = new (tokens.Grow()) Token(handle, priority, timeout);
			}
			else
			{
				float lowest = priority;
				for (unsigned int i = 0; i < size; i++)
				{
					if (!tokens[i].granted && tokens[i].priority < lowest)
					{
						lowest = tokens[i].priority;
						token = &tokens[i];
					}
				}
				if (token == 0)
				{
					return;
				}
				token->handle = *handle;
			}
		}
		token->priority = priority;
		int active = count;
		int limit = max;
		if (limit <= active)
		{
			active = CountAtLeast(priority) - 1;
		}
		if (!token->granted || active < limit)
		{
			token->timer = timeout;
		}
		if (!token->granted && active < limit)
		{
			count++;
			token->granted = true;
		}
	}
#endif

	// FUNCTION: ENGINE 0x10389850
	void CombatBudgetManager::Enable(bool value)
	{
		enabled = value;
	}

	// FUNCTION: ENGINE 0x10389A00
	void CombatBudgetManager::SetMax(int type, int value)
	{
		budgets[type].max = value;
	}

	// FUNCTION: ENGINE 0x10389A20
	void CombatBudgetManager::SetTimeout(int type, float value)
	{
		budgets[type].timeout = value;
	}

	// FUNCTION: ENGINE 0x10389A40
	void CombatBudgetManager::SetHeuristic(int type, int value)
	{
		budgets[type].heuristic = value;
	}

	// FUNCTION: ENGINE 0x10389890
	void CombatBudgetManager::UnregisterScripts()
	{
		engine::LuaScriptManager* script = engine::GetScriptManager();
		script->Unregister(this);
	}

	// FUNCTION: ENGINE 0x1038A9D0
	void CombatBudgetManager::RegisterScripts()
	{
		engine::LuaScriptManager* script = engine::GetScriptManager();
		script->SetOwner(this);
		script->RegisterMethod("ai_cbm_Enable", this, &CombatBudgetManager::Enable);
		script->RegisterMethod("ai_cbm_SetMax", this, &CombatBudgetManager::SetMax);
		script->RegisterMethod("ai_cbm_SetTimeout", this, &CombatBudgetManager::SetTimeout);
		script->RegisterMethod("ai_cbm_SetHeuristic", this, &CombatBudgetManager::SetHeuristic);
		script->ClearOwner();
	}

	// FUNCTION: ENGINE 0x1038AC40
	CombatBudgetManager::CombatBudgetManager() : enabled(true)
	{
		budgets[0].Configure(20, 4, 1.0f, 1);
		budgets[1].Configure(20, 2, 2.0f, 1);
		budgets[2].Configure(2, 2, 5.0f, 0);
		budgets[3].Configure(1, 1, 0.0f, 0);
		RegisterScripts();
	}

	// FUNCTION: ENGINE 0x1038A960
	CombatBudgetManager::~CombatBudgetManager()
	{
		UnregisterScripts();
		for (int i = 0; i < 4; i++)
		{
			budgets[i].ReleaseTokens();
		}
	}

	// FUNCTION: ENGINE 0x1038A440
	void CombatBudgetManager::Update(float delta)
	{
		for (int i = 0; i < 4; i++)
		{
			budgets[i].Update(delta);
		}
	}
}

template class container::ArrayDynamic<proto::CombatBudget::Token, container::AllocatorNew>;
template class Method1<proto::CombatBudgetManager, void, bool>;
template class Method2<proto::CombatBudgetManager, void, int, int>;
template class Method2<proto::CombatBudgetManager, void, int, float>;
template class Closure1<proto::CombatBudgetManager, void, bool>;
template class Closure2<proto::CombatBudgetManager, void, int, int>;
template class Closure2<proto::CombatBudgetManager, void, int, float>;


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10389860
// FUNCTION: ENGINE 0x103898B0
// FUNCTION: ENGINE 0x103898C0
// FUNCTION: ENGINE 0x103898D0
// FUNCTION: ENGINE 0x103898E0
// FUNCTION: ENGINE 0x103898F0
// FUNCTION: ENGINE 0x10389900
// FUNCTION: ENGINE 0x10389910
// FUNCTION: ENGINE 0x10389930
// FUNCTION: ENGINE 0x103899A0
// FUNCTION: ENGINE 0x103899B0
// FUNCTION: ENGINE 0x103899F0
// FUNCTION: ENGINE 0x10389B70
// FUNCTION: ENGINE 0x10389B80
// FUNCTION: ENGINE 0x10389BE0
// FUNCTION: ENGINE 0x10389C20
// FUNCTION: ENGINE 0x10389C80
// FUNCTION: ENGINE 0x10389CA0
// FUNCTION: ENGINE 0x10389CC0
// FUNCTION: ENGINE 0x10389D30
// FUNCTION: ENGINE 0x10389D50
// FUNCTION: ENGINE 0x10389D70
// FUNCTION: ENGINE 0x10389DE0
// FUNCTION: ENGINE 0x10389E00
// FUNCTION: ENGINE 0x1038A2B0
// FUNCTION: ENGINE 0x1038A2F0
// FUNCTION: ENGINE 0x1038A300
// FUNCTION: ENGINE 0x1038A370
// FUNCTION: ENGINE 0x1038A390
// FUNCTION: ENGINE 0x1038A3C0
// FUNCTION: ENGINE 0x1038A3E0
// FUNCTION: ENGINE 0x1038A410
// FUNCTION: ENGINE 0x1038A760
// FUNCTION: ENGINE 0x1038A780
// FUNCTION: ENGINE 0x1038A7E0
// FUNCTION: ENGINE 0x1038A850
// FUNCTION: ENGINE 0x1038A8C0
// FUNCTION: ENGINE 0x1038A8E0
