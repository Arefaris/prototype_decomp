// The scenario's Lua fight nodes (RTTI: engine::scenario::LuaTrack, LuaAction and LuaCondition) and the hook the
// scripting runs around a node's script (unit 0x10808840 - 0x10809B90, next to the scenario string track). A track
// keeps a script text; when its action is created the text is compiled into a function that an action runs as a
// coroutine, and a condition compiles its text as an expression. File and member names are guesses.
#ifndef ENGINE_SCENARIO_LUATRACKS_H
#define ENGINE_SCENARIO_LUATRACKS_H

#include "code/core/linklist.h"
#include "code/core/refptr.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/fight/trackfactory.h"

namespace engine
{
	class GameObject;
	class LuaScriptManager;

	// 0x105AA250 (another unit): keeps a copy of a text in a buffer of its own, freeing the old one; answers the copy
	// and sets its length (the length is 0 and the copy null when the text is empty)
	char* AssignString(char* old, int* length, const char* text, int newLength);

	// What the script hook is asked about: the manager that runs the script (null when none does), the object the
	// script runs for and the node's name; the hook answers the game object of the owner
	struct ScriptHookArgs
	{
		// 0x10808840 (also kept as a function; the callers store the members themselves)
		ScriptHookArgs(LuaScriptManager* newManager, core::IRefCount* newOwner, const char* newName)
			: manager(newManager), owner(newOwner), name(newName), object(0)
		{
		}

		LuaScriptManager* manager;
		core::IRefCount* owner;
		const char* name;
		GameObject* object;
	};

	// The hook is called before a script runs (the second flag false) and after it (true); data is its own
	typedef bool (*ScriptHook)(void* data, bool keepOpen, bool finish, ScriptHookArgs* args);

	// 0x10808890 / 0x108088B0 / 0x108088D0: the installed hook (0x111BF298) and its data (0x11284B58)
	void SetScriptHook(ScriptHook hook, void* data);
	void GetScriptHook(ScriptHook* hook, void** data);
	void CallScriptHook(ScriptHookArgs* args, bool finish);
	// 0x10808DA0: the hook the game starts with
	bool DefaultScriptHook(void* data, bool keepOpen, bool finish, ScriptHookArgs* args);

	namespace scenario
	{
		class LuaTrack;

		// RTTI: engine::scenario::LuaTrack (16 vftable slots, 0x24 bytes)
		class LuaTrack : public fight::Track
		{
		public:
			// 0x10808910
			LuaTrack();
			virtual ~LuaTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 5
			virtual bool Slot5(int a, int b, int c);
			// vftable slot 6
			virtual void Slot6(int a, int b);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float value);
			bool SetTimeEnd(float value);
			bool SetScript(const char* text, int length);

			// Compiles the script into a function (an error is shown and nothing is kept)
			void Compile(fight::Track* listener);
			// Drops the compiled function
			void ReleaseFunction();

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

			float timeBegin;  // +0x10
			float timeEnd;  // +0x14
			char* script;  // +0x18
			int scriptLength;  // +0x1C
			// The reference of the compiled function
			int function;  // +0x20
		};

		extern fight::Property** gLuaTrackProperties;

		fight::TrackFactory* CreateLuaTrackFactory(const char* name);
		void RegisterLuaTrackFactory(fight::TrackRegistry* registry, const char* name);

		// RTTI: engine::scenario::LuaAction (9 vftable slots, 0x44 bytes): runs the track's function as a coroutine
		class LuaAction : public fight::Action
		{
		public:
			// 0x108091B0
			LuaAction(fight::Track* listener, LuaTrack* newTrack, core::IRefCount* newOwner, int reference);
			virtual ~LuaAction();

			// vftable slot 5 (0x10808C30): starts the coroutine
			virtual bool Slot5(int arg, float value);
			// vftable slot 6 (0x108089F0): the action was stopped; the coroutine and the function are dropped
			virtual void Slot6();
			// vftable slot 7 (0x10809270): resumes the coroutine; false when it ended
			virtual bool Slot7(int arg, float value);

			// Drops the coroutine and the function
			void ReleaseReferences();

			core::Link<LuaTrack> link;  // +0x1C
			core::RefPtr<core::IRefCount> owner;  // +0x28
			TrackWatch watch;  // +0x2C
			int coroutine;  // +0x38
			int function;  // +0x3C
			int environment;  // +0x40
		};

		// RTTI: engine::scenario::LuaCondition (10 vftable slots, 0x18 bytes): the script is an expression
		class LuaCondition : public fight::Condition
		{
		public:
			// 0x10809610
			LuaCondition();
			virtual ~LuaCondition();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 5
			virtual bool Slot5(int a, int b, int c);
			// vftable slot 6
			virtual void Slot6(int a, int b);
			// vftable slot 9 (0x10809670): runs the expression for the object in d
			virtual bool Evaluate(int a, int b, int c, int d);

			bool SetScript(const char* text, int length);
			void ReleaseFunction();

			static void RegisterProperties();
			static void ClearProperties();

			char* script;  // +0xC
			int scriptLength;  // +0x10
			int function;  // +0x14
		};

		extern fight::Property** gLuaConditionProperties;

		fight::ConditionFactory* CreateLuaConditionFactory(const char* name);
		void RegisterLuaConditionFactory(fight::TrackRegistry* registry, const char* name);
	}
}

#endif
