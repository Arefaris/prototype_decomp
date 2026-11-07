// engine::controller::IControllerPacker, ControllerPacker and ControllerPackerLossLess (RTTI names): pack the state of
// the players' controllers into the bytes the online layer sends, and read them back; and the snapshot the physical
// controller manager keeps of the packed state. Unit 0x108A23F0 - 0x108A4A20 (no assert path; the file name is a
// guess); the method names are guesses.
#ifndef ENGINE_CONTROLLER_CONTROLLERPACKER_H
#define ENGINE_CONTROLLER_CONTROLLERPACKER_H

#include "code/core/time.h"

namespace engine
{
	namespace util
	{
		class Packer;
		class UnPacker;
	}

	namespace controller
	{
		class PlayerInput;

		// RTTI: IControllerPacker (6 pure slots)
		class IControllerPacker
		{
		public:
			// Writes the state of one player
			virtual void Pack(PlayerInput* player, util::Packer* packer) = 0;
			// Reads one player's state into the player of the list with the id it names; answers that player
			virtual PlayerInput* Unpack(PlayerInput* players, util::UnPacker* reader) = 0;
			// Reads one player's state (the player is looked up by its id, nothing is written when apply is false)
			virtual bool Verify(PlayerInput* players, util::UnPacker* reader, bool apply) = 0;
			// Writes the count of the players of the list that match (all the local ones when localOnly is set, with the
			// flags) and each one's state; answers the bytes used
			virtual int PackAll(PlayerInput* players, unsigned char* buffer, int size, bool localOnly, unsigned int flags) = 0;
			// Reads the count and that many states
			virtual void UnpackAll(PlayerInput* players, unsigned char* buffer, int size) = 0;
			// The same, answering false at the first state that does not read
			virtual bool VerifyAll(PlayerInput* players, unsigned char* buffer, int size) = 0;
		};

		// RTTI: ControllerPacker (0xC bytes): the size of one packed player is measured by packing a default one
		class ControllerPacker : public IControllerPacker
		{
		public:
			// 0x108A2B10
			ControllerPacker();
			virtual void Pack(PlayerInput* player, util::Packer* packer);
			virtual PlayerInput* Unpack(PlayerInput* players, util::UnPacker* reader);
			virtual bool Verify(PlayerInput* players, util::UnPacker* reader, bool apply);
			virtual int PackAll(PlayerInput* players, unsigned char* buffer, int size, bool localOnly, unsigned int flags);
			virtual void UnpackAll(PlayerInput* players, unsigned char* buffer, int size);
			virtual bool VerifyAll(PlayerInput* players, unsigned char* buffer, int size);

			int packedBytes;  // +4
			int bufferSize;  // +8
		};

		// RTTI: ControllerPackerLossLess (0xC bytes): the same with the axes as whole floats
		class ControllerPackerLossLess : public ControllerPacker
		{
		public:
			// 0x108A4A20
			ControllerPackerLossLess();
			virtual void Pack(PlayerInput* player, util::Packer* packer);
			virtual PlayerInput* Unpack(PlayerInput* players, util::UnPacker* reader);
		};

		// The packed state of all players at one moment (0x1C bytes; the class name is a guess)
		class ControllerSnapshot
		{
		public:
			// 0x108A2790: a null packer is the input system's own
			explicit ControllerSnapshot(ControllerPacker* newPacker);
			// 0x108A27E0
			~ControllerSnapshot();
			// 0x108A27F0: packs the local players of the list
			int Capture(PlayerInput* players, unsigned int flags);
			// 0x108A2820 / 0x108A2840
			void Restore(PlayerInput* players);
			bool Check(PlayerInput* players);

			int unknown0;
			bool unknown4;
			core::Time time;  // +8
			ControllerPacker* packer;  // +0x14
			unsigned char* data;  // +0x18
		};
	}
}

#endif
