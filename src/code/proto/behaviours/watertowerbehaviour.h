// proto::WaterTowerBehaviour (RTTI and reflection names; base engine::Behaviour): the infected water tower. It keeps
// two fight variables of its object ("infected" and "scanState") up to date. Reflected: forceInfected. Unit
// 0x10406A70 - 0x10407440 (no assert path; the file name is a guess). The reflected name is original, the rest is
// guessed; only the construction, the reflection and the variable accessors are reconstructed.
#ifndef PROTO_BEHAVIOURS_WATERTOWERBEHAVIOUR_H
#define PROTO_BEHAVIOURS_WATERTOWERBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"

namespace proto
{
	class WaterTowerBehaviour : public engine::Behaviour
	{
	public:
		// 0x10406AB0
		explicit WaterTowerBehaviour(engine::GameObject* newOwner);
		// 0x10406B00 (the deleting destructor is 0x10406B50)
		virtual ~WaterTowerBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10406E90)
		virtual void Slot1();
		// vftable slot 4 (0x10407100)
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 5 (0x10407080)
		virtual void OnPostedMessage(engine::Message* message);
		// vftable slot 6 (0x10406FE0)
		virtual void OnMessage(engine::Message* message);

		// 0x10406B80, 0x10406C00: the fight variable "infected" of the object (names guessed)
		int GetInfected();
		void SetInfected(int value);
		// 0x10406C80, 0x10406D00: the fight variable "scanState"
		int GetScanState();
		void SetScanState(int value);

		bool forceInfected;  // +0xC
		float unknown10;  // +0x10
		bool unknown14;  // +0x14
	};
}

#endif
