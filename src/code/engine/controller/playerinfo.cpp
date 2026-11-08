// The per-player input state (engine::controller::PlayerInput, code/engine/controller/playerinfo.cpp; the file name is
// a guess, the unit starts at 0x108A1280). Names are guesses.
#include "code/engine/controller/inputsystem.h"
#include "code/core/strings.h"
#include <math.h>
#include <string.h>

namespace choreo
{
	extern const float gMinusOne;
}

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace engine
{
	namespace controller
	{
		// FUNCTION: ENGINE 0x108A1280
		PlayerInput::~PlayerInput()
		{
		}

		// FUNCTION: ENGINE 0x108A1290
		void PlayerInput::Clear()
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

		// FUNCTION: ENGINE 0x108A11E0
		void PlayerInput::SetControlState(int control, int state)
		{
			controlStates[control] = state;
		}

		// FUNCTION: ENGINE 0x108A1200
		void PlayerInput::SetButtonBits(int control, unsigned int value, int which)
		{
			buttons[control].bits[which] = value;
		}

		// FUNCTION: ENGINE 0x108A1500
		// NONMATCHING: the engine loads the dead zone after both stick values and keeps the two clamp bounds in registers (61.5 %)
#ifdef NONMATCHING
		void PlayerInput::ApplySquareDeadZone(int first, int second)
		{
			float x = analog[first].input;
			float y = analog[second].input;
			InputSystem* system = InputSystem::Get();
			float lengthSquared = y * y + x * x;
			float deadZone = system->config.deadZone;
			if (deadZone * deadZone > lengthSquared)
			{
				analog[first].value = 0.0f;
				analog[second].value = 0.0f;
				return;
			}
			float low = choreo::gMinusOne;
			float high = engine::driving::gOne;
			float clampedX = x;
			if (!(clampedX - low >= 0.0f))
			{
				clampedX = low;
			}
			if (clampedX - high >= 0.0f)
			{
				clampedX = high;
			}
			analog[first].value = clampedX;
			if (!(y - low >= 0.0f))
			{
				y = low;
			}
			if (y - high >= 0.0f)
			{
				y = high;
			}
			analog[second].value = y;
		}
#endif

		// FUNCTION: ENGINE 0x108A1640
		// NONMATCHING: the length stays in a stack word across the call and the frame is eight bytes (10 %)
#ifdef NONMATCHING
		void PlayerInput::ApplyRoundDeadZone(int first, int second)
		{
			float x = analog[first].input;
			float y = analog[second].input;
			float length = sqrtf(y * y + x * x);
			float deadZone = InputSystem::Get()->config.deadZone;
			if (length <= deadZone)
			{
				analog[first].value = 0.0f;
				analog[second].value = 0.0f;
			}
			else
			{
				float scale = (length - deadZone) / (engine::driving::gOne - deadZone);
				if (scale < 0.0f)
				{
					scale = 0.0f;
				}
				if (scale - engine::driving::gOne >= 0.0f)
				{
					scale = engine::driving::gOne;
				}
				float inverse = engine::driving::gOne / length;
				analog[first].value = scale * (inverse * x);
				analog[second].value = scale * (inverse * y);
			}
		}
#endif

		// FUNCTION: ENGINE 0x108A1720
		void PlayerInput::ApplyDeadZones()
		{
			if (InputSystem::Get()->config.flag18)
			{
				ApplyRoundDeadZone(0, 1);
				ApplyRoundDeadZone(2, 3);
				ApplyRoundDeadZone(4, 5);
				ApplyRoundDeadZone(9, 10);
				ApplyRoundDeadZone(11, 12);
				ApplyRoundDeadZone(13, 14);
				ApplyRoundDeadZone(15, 16);
			}
			else
			{
				ApplySquareDeadZone(0, 1);
				ApplySquareDeadZone(2, 3);
				ApplySquareDeadZone(4, 5);
				ApplySquareDeadZone(9, 10);
				ApplySquareDeadZone(11, 12);
				ApplySquareDeadZone(13, 14);
				ApplySquareDeadZone(15, 16);
			}
			analog[6].value = analog[6].input;
			analog[7].value = analog[7].input;
		}

		// FUNCTION: ENGINE 0x108A15F0
		// EQUIVALENT: register choice: the engine loads the id -1 into ecx after it copies this into esi, ours into eax before the push (81 %)
		PlayerInput::PlayerInput()
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

		// FUNCTION: ENGINE 0x108A1880
		PlayerInfo::~PlayerInfo()
		{
		}

		// FUNCTION: ENGINE 0x108A1890
		void PlayerInfo::SetName(const char* newName)
		{
			core::StrNCpy(name, newName, 0x10);
		}

		// FUNCTION: ENGINE 0x108A18B0
		void PlayerInfo::SetIds(int first, int second)
		{
			firstId = first;
			secondId = second;
		}

		// FUNCTION: ENGINE 0x108A18D0
		int PlayerInfo::Write(char* buffer, int size)
		{
			core::StrNCpy(buffer, name, size);
			int length = strlen(name) + 1;
			if (length + 8 < size)
			{
				*(int*)(buffer + length) = firstId;
				*(int*)(buffer + length + 4) = secondId;
				return length + 8;
			}
			return length;
		}

		// FUNCTION: ENGINE 0x108A1920
		void PlayerInfo::Read(const char* buffer, int size)
		{
			SetName(buffer);
			int length = strlen(name) + 1;
			if (size > length)
			{
				firstId = *(const int*)(buffer + length);
				secondId = *(const int*)(buffer + length + 4);
			}
		}

		// FUNCTION: ENGINE 0x108A1960
		void PlayerInfo::Assign(const PlayerInfo* other)
		{
			core::StrNCpy(name, other->name, 0x10);
			firstId = other->firstId;
			secondId = other->secondId;
		}

		// FUNCTION: ENGINE 0x108A1990
		void PlayerInfo::Reset()
		{
			name[0] = 0;
			firstId = -1;
			secondId = -1;
		}

		// FUNCTION: ENGINE 0x108A19C0
		PlayerInfo::PlayerInfo()
		{
			Reset();
		}

		// FUNCTION: ENGINE 0x108A19A0
		void PlayerInfoFactory::Destroy(PlayerInfo* info)
		{
			delete info;
		}

		// FUNCTION: ENGINE 0x108A19F0
		PlayerInfo* PlayerInfoFactory::Create()
		{
			return new PlayerInfo;
		}
	}
}
