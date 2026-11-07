// The packing of the players' controller state (engine::controller::ControllerPacker; code/engine/controller/
// controllerpacker.cpp; the file name is a guess, the unit starts at 0x108A23F0 and has no assert path). Names are guesses
// unless the RTTI gives them.
#include "code/engine/controller/inputsystem.h"
#include "code/engine/util/packbuffer.h"

namespace engine
{
	namespace controller
	{
		// FUNCTION: ENGINE 0x108A2690
		// NONMATCHING: shrink-wrap: the engine saves ebx and edi after the test of the count (50 %)
#ifdef NONMATCHING
		void ControllerPacker::UnpackAll(PlayerInput* players, unsigned char* buffer, int size)
		{
			util::UnPacker reader(buffer, size);
			int count = (char)reader.position[reader.buffer];
			reader.position++;
			for (int remaining = count; remaining != 0; remaining--)
			{
				Unpack(players, &reader);
			}
		}
#endif

		// FUNCTION: ENGINE 0x108A2700
		// NONMATCHING: the engine adds the buffer to the position in the other order in the address of the count (99.3 %)
#ifdef NONMATCHING
		bool ControllerPacker::VerifyAll(PlayerInput* players, unsigned char* buffer, int size)
		{
			util::UnPacker reader(buffer, size);
			int count = (char)reader.position[reader.buffer];
			reader.position++;
			for (unsigned int index = 0; index < (unsigned int)count; index++)
			{
				if (!Verify(players, &reader, false))
				{
					return false;
				}
			}
			return true;
		}
#endif

		// FUNCTION: ENGINE 0x108A3180
		// NONMATCHING: the engine keeps the packer's position in a stack slot and the loops in other registers (24.1 %)
#ifdef NONMATCHING
		int ControllerPacker::PackAll(PlayerInput* players, unsigned char* buffer, int size, bool localOnly, unsigned int flags)
		{
			char count = 0;
			for (PlayerInput* player = players; player != 0; player = (PlayerInput*)player->next)
			{
				if ((!localOnly || InputSystem::IsLocal(player->id)) && (player->flags & flags) == flags)
				{
					count++;
				}
			}
			util::Packer packer(buffer, size);
			packer.buffer[packer.position] = count;
			packer.position++;
			for (PlayerInput* player = players; player != 0; player = (PlayerInput*)player->next)
			{
				if ((!localOnly || InputSystem::IsLocal(player->id)) && (player->flags & flags) == flags)
				{
					Pack(player, &packer);
				}
			}
			return packer.position;
		}
#endif
	}
}
