// proto::CoOpBehaviour (RTTI and reflection names; base engine::Behaviour): the co-op bookkeeping of a character: the
// states of a pending respawn, of the partner's death and of the pairing volume, which it reflects as object members
// (proto::RespawnState, PlayerDeadState and PairingVolumeState are plain data with no reflected members; their layouts
// are not recovered). Unit 0x104DAD00 - 0x104DBC00 (no assert path; the file name is a guess). The reflected member
// names are original, the rest is guessed.
#ifndef PROTO_COOPBEHAVIOUR_H
#define PROTO_COOPBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"

namespace proto
{
	class RespawnState
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	};

	class PlayerDeadState
	{
	public:
		~PlayerDeadState()
		{
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	};

	class PairingVolumeState
	{
	public:
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();
	};

	class CoOpBehaviour : public engine::Behaviour
	{
	public:
		// 0x104DAEC0
		explicit CoOpBehaviour(engine::GameObject* newOwner);
		// 0x104DB960 (deleting destructor 0x104DBB80)
		virtual ~CoOpBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slots 1, 4 and 6 (0x104DAF20, 0x104DB8E0, 0x104DB980)
		virtual void Slot1();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		RespawnState* respawnPendingState;  // +0xC
		PlayerDeadState* partnerDeadState;  // +0x10
		PairingVolumeState* pairingVolumeState;  // +0x14
	};
}

#endif
