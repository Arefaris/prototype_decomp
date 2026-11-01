// The per-player input state (engine::controller::PlayerInfo, code/engine/controller/playerinfo.cpp; the file name is
// a guess, the unit starts at 0x108A1280). Names are guesses.
#include "code/engine/controller/inputsystem.h"

namespace engine
{
	namespace controller
	{
		// FUNCTION: ENGINE 0x108A1280
		PlayerInfo::~PlayerInfo()
		{
		}

		// FUNCTION: ENGINE 0x108A1290
		void PlayerInfo::Clear()
		{
			for (int index = 0; index < 42; index++)
			{
				buttonValues[index] = 0.0f;
				controlStates[index] = 0;
			}
			for (int control = 0; control < 17; control++)
			{
				for (int part = 0; part < 2; part++)
				{
					(&analog[control].value)[part] = 0.0f;
					buttons[control].bits[part] = 1;
				}
			}
		}

		// FUNCTION: ENGINE 0x108A15F0
		// EQUIVALENT: register choice: the engine loads the id -1 into ecx after it copies this into esi, ours into eax before the push (81 %)
		PlayerInfo::PlayerInfo()
		{
			id = 0xffffffff;
			slot = -1;
			flags = 0;
			context = 3;
			input = 0;
			unknown2C4 = 0;
			viewMatrix.Identity();
			viewPosition[2] = 0.0f;
			viewPosition[1] = 0.0f;
			viewPosition[0] = 0.0f;
			Clear();
		}
	}
}
