// proto::ZoneBehaviour (RTTI and reflection names; base engine::Behaviour): a zone of the open world (military zone,
// outbreak, war) with a radius and a strength that fades in and out; it shows the zone on the HUD and sends the zone
// messages (type 0x34). Reflected: the radius, the zone type, the zone strength and whether it renders its effects.
// Unit 0x105726B0 - 0x10573300 (no assert path; the file name is a guess). The reflected names are original, the rest is
// guessed; only the reflection and the strength accessors are reconstructed.
#ifndef PROTO_ZONEBEHAVIOUR_H
#define PROTO_ZONEBEHAVIOUR_H

#include "code/content/metatype.h"
#include "code/engine/gameobject/behaviour.h"
#include "code/engine/message.h"

namespace proto
{
	class ZoneBehaviour : public engine::Behaviour
	{
	public:
		// The kinds of zone (reflected as proto::ZoneBehaviour::ZoneType)
		enum ZoneType
		{
			ZONE_MILITARY = 0,
			ZONE_OUTBREAK = 1,
			ZONE_WAR = 2
		};

		// 0x105726F0
		explicit ZoneBehaviour(engine::GameObject* newOwner);
		// 0x10572DD0
		virtual ~ZoneBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10572E00), 3 (0x10572FA0), 4 (0x105728C0) and 6 (0x10572FE0)
		virtual void Slot1();
		virtual void OnActiveChanged(bool active);
		virtual void Update(float dt, unsigned short mask);
		virtual void OnMessage(engine::Message* message);

		// 0x10572C90: sets the strength the zone fades to (kept between 0 and 1)
		void SetZoneStrength(float value);
		// 0x10565930: the strength the zone fades to
		float GetZoneStrength() const;
		// 0x10572A70: the strength the zone has now
		float GetStrength() const;
		// 0x10572B50: tells the HUD about the zone's position and strength
		void UpdateEffects();

		float targetStrength;  // +0xC
		unsigned char unknown10[0xC];
		float radius;  // +0x1C
		int unknown20;
		int zoneType;  // +0x24
		bool initialised;  // +0x28
		bool unknown29;
		bool renderEffectsState;  // +0x2A
		float strength;  // +0x2C
		unsigned char unknown30[0x44];
	};
}

#endif
