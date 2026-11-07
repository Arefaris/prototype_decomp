// proto::CombatBudgetManager (RTTI name through the Method / Closure instances of its script functions): the combat
// budgets of the AI system (gAISystem +0x14, 0x84 bytes), one pool of tokens per combat type. A character asks for a
// token before it attacks; the pool grants a limited number at a time and takes a token back when its timer runs
// out. Unit 0x10389850 - 0x1038AD20 (no assert path; the file name is a guess); class and member names are guesses
// except the ones the script functions (ai_cbm_Enable, ai_cbm_SetMax, ai_cbm_SetTimeout, ai_cbm_SetHeuristic) give.
#ifndef PROTO_COMBATBUDGETMANAGER_H
#define PROTO_COMBATBUDGETMANAGER_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/vector.h"

namespace proto
{
	// 0x103C0F80: how far the position is from the nearest of the things the combat looks at (name guess)
	float Unknown103C0F80(const math::Vector* position);

	// 0x103B9940: tells an object about a change of its combat budget (name guess)
	void Unknown103B9940(engine::GameObject* object, int kind, const char* text);

	// One combat type's pool of tokens (0x20 bytes)
	class CombatBudget
	{
	public:
		// A character that holds a token or waits for one (0x10 bytes)
		struct Token
		{
			Token()
			{
			}
			Token(const engine::GameObjectHandle* newHandle, float newPriority, float newTimer);

			engine::GameObjectHandle handle;  // +0
			bool granted;  // +4
			float timer;  // +8
			float priority;  // +0xC
		};

		typedef container::ArrayDynamic<Token, container::AllocatorNew> TokenArray;

		CombatBudget() : count(0)
		{
		}
		~CombatBudget()
		{
			ReleaseTokens();
		}

		// 0x10389E40: room for capacity tokens, at most newMax granted at a time
		void Configure(int capacity, int newMax, float newTimeout, int newHeuristic);
		// 0x1038A480
		void ReleaseTokens();
		// 0x10389A60: the token of a character
		Token* Find(const engine::GameObjectHandle* handle);
		// 0x10389AB0: how many tokens have a priority of at least value
		int CountAtLeast(float value);
		// 0x10389EC0: counts the timers down and takes the tokens back that ran out
		void Update(float delta);
		// 0x1038A130: how much the object wants a token (name guess)
		static float GetPriority(const engine::GameObjectHandle* handle, bool granted);
		// 0x1038A4C0: asks for a token for an object
		void Unknown1038A4C0(const engine::GameObjectHandle* handle);
		// 0x1038A100: whether the object holds a token
		bool Unknown1038A100(const engine::GameObjectHandle* handle);

		float timeout;  // +0
		int max;  // +4
		int count;  // +8
		int heuristic;  // +0xC
		TokenArray tokens;  // +0x10
		unsigned char unknown1C[4];
	};

	// The combat budgets (0x84 bytes): the flag that turns them on, then one pool per combat type
	class CombatBudgetManager
	{
	public:
		// 0x1038AC40: registers the script functions
		CombatBudgetManager();
		// 0x1038A960
		~CombatBudgetManager();

		// 0x10389850 (ai_cbm_Enable)
		void Enable(bool value);
		// 0x10389A00 (ai_cbm_SetMax)
		void SetMax(int type, int value);
		// 0x10389A20 (ai_cbm_SetTimeout)
		void SetTimeout(int type, float value);
		// 0x10389A40 (ai_cbm_SetHeuristic)
		void SetHeuristic(int type, int value);
		// 0x1038A440: updates every pool
		void Update(float delta);
		// 0x1038A9D0
		void RegisterScripts();
		// 0x10389890
		void UnregisterScripts();

		void Request(int type, const engine::GameObjectHandle* handle)
		{
			if (enabled)
			{
				budgets[type].Unknown1038A4C0(handle);
			}
		}

		bool Has(int type, const engine::GameObjectHandle* handle)
		{
			if (enabled && !budgets[type].Unknown1038A100(handle))
			{
				return false;
			}
			return true;
		}

		bool enabled;  // +0
		unsigned char unknown1[3];
		CombatBudget budgets[4];  // +4
	};
}

namespace container
{
	// The engine erases a token with the call of AssignRange
	template<> struct ArrayEraseInline<proto::CombatBudget::Token>
	{
		enum
		{
			value = 0
		};
	};
}

#endif
