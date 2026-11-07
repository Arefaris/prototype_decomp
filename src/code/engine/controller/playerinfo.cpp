// The per-player input state (engine::controller::PlayerInput, code/engine/controller/playerinfo.cpp; the file name is
// a guess, the unit starts at 0x108A1280). Names are guesses.
#include "code/engine/controller/inputsystem.h"
#include "code/core/strings.h"
#include <string.h>

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
