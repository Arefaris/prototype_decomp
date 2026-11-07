// proto::AlertBehaviour (RTTI and reflection names; base engine::Behaviour): sounds an alert (proto::AiAlert) in
// the area around its object so that the pedestrians nearby react to it. Reflected: alertRadius, alertType,
// broadcastFrequency, broadcastForever and timeBroadcasting. Unit 0x1042E3D0 - 0x1042EEE0 (no assert path; the
// file name is a guess). The reflected names are original, the rest is guessed; only the construction and the
// reflection are reconstructed.
#ifndef PROTO_BEHAVIOURS_ALERTBEHAVIOUR_H
#define PROTO_BEHAVIOURS_ALERTBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace proto
{
	// RTTI proto::AiAlert: the kinds of alert (24 values; its reflection is in another unit, 0x103608E0)
	enum AiAlert
	{
		AI_ALERT_COUNT = 0x18
	};

	class AlertBehaviour : public engine::Behaviour
	{
	public:
		// 0x1042E410
		explicit AlertBehaviour(engine::GameObject* newOwner);
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 3 (0x1042E4F0)
		virtual void OnActiveChanged(bool active);
		// vftable slot 4 (0x1042EB90)
		virtual void Update(float dt, unsigned short mask);
		// vftable slot 6 (0x1042EB40)
		virtual void OnMessage(engine::Message* message);

		int alertType;  // +0xC
		float alertRadius;  // +0x10
		float unknown14;  // +0x14
		int broadcastFrequency;  // +0x18
		bool broadcastForever;  // +0x1C
		float timeBroadcasting;  // +0x20
		engine::HandleBase unknown24;  // +0x24
		engine::HandleBase unknown28;  // +0x28
		int unknown2C;  // +0x2C
		int unknown30;  // +0x30
		int unknown34;  // +0x34
	};
}

#endif
