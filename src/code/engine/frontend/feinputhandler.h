// engine::FEInputHandler (RTTI name): the front end's input handler. It listens to the keyboard (as a keyboard callback,
// while the front end wants the keys), forwards keys, the mouse and the pads' buttons and sticks to the movie's
// ActionScript (AS_KeyboardEvent, AS_SetMouseCursor, AS_HandleInput) and registers the natives fe_EnableOnInput,
// fe_SetDeadZone, fe_IsMouseVisible and fe_SetInputFocus. One instance lives in gFEInputHandler. Unit 0x108810F0 -
// 0x10882140 (no assert path; the file name is a guess). Names other than the RTTI ones are guesses.
#ifndef ENGINE_FRONTEND_FEINPUTHANDLER_H
#define ENGINE_FRONTEND_FEINPUTHANDLER_H

#include "code/engine/controller/inputsystem.h"

namespace engine
{
	class FEInputHandler : public controller::Keyboard::Callback
	{
	public:
		// 0x10881FF0: registers the natives
		FEInputHandler();
		// 0x10881BF0: unregisters the natives and lets go of the keyboard (0x10881E30 is a deleting destructor nothing
		// calls)
		~FEInputHandler();

		// vftable slot 0 (0x108812D0): tells the movie about the key
		virtual void OnKey(int code, int modifiers, int character, bool down, int unknown);

		// 0x108816E0 (fe_EnableOnInput)
		void EnableOnInput(bool enable);
		// 0x10881540 (fe_SetDeadZone): answers the dead zone it had
		float SetDeadZone(float deadZone);
		// 0x108812A0 (fe_IsMouseVisible)
		bool IsMouseVisible();
		// 0x10881560 (fe_SetInputFocus)
		void SetInputFocus(const char* name);
	};

	// The instance (0x11316C90)
	extern FEInputHandler* gFEInputHandler;

	// 0x108820F0: makes the instance in the heap
	void CreateFEInputHandler(int heap);
}

#endif
