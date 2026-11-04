// proto::MissileBehaviour (RTTI and reflection names; base proto::WeaponBehaviour) and the load objects around it:
// proto::MissileProfile (base proto::AmmoProfileBase: how a missile flies, tracks and hits) and proto::MissileSpin (how
// it turns around its axes). Unit 0x10467C00 - 0x10469A00 and the code behind it up to 0x1046D3F0 (no assert path; the
// file name is a guess). The reflected names are original, the rest is guessed; the reflection, the construction and
// the destruction are reconstructed, the flight is left to the engine.
#ifndef PROTO_BEHAVIOURS_MISSILEBEHAVIOUR_H
#define PROTO_BEHAVIOURS_MISSILEBEHAVIOUR_H

#include "code/proto/behaviours/weaponbehaviour.h"
#include "code/ravenphysics/context.h"
#include "code/ravenphysics/intersectionproperties.h"

namespace proto
{
	// How a missile turns while it flies (RTTI proto::MissileSpin; 0x34 bytes)
	struct MissileSpin : public content::MetaLoadObject
	{
		// 0x10468380
		MissileSpin();
		// 0x10468420 (the deleting destructor is 0x10468430)
		virtual ~MissileSpin()
		{
		}
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		math::Vector axisX;  // +8
		math::Vector axisY;  // +0x14
		float minSpeedX;  // +0x20
		float minSpeedY;  // +0x24
		float maxSpeedX;  // +0x28
		float maxSpeedY;  // +0x2C
		bool initialOrientationRandom;  // +0x30
	};

	// The ammunition of a missile (RTTI proto::MissileProfile; 0xC4 bytes)
	struct MissileProfile : public AmmoProfileBase
	{
		// 0x10467CE0
		MissileProfile();
		// 0x10468460 (the deleting destructor is 0x10469940)
		virtual ~MissileProfile();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		float initialVelocity;  // +0x68
		float initialDeceleration;  // +0x6C
		float acceleration;  // +0x70
		float gravity;  // +0x74
		float timeToLive;  // +0x78
		float maxTurningVelocity;  // +0x7C
		float airFriction;  // +0x80
		float airFrictionIncreaseRate;  // +0x84
		float length;  // +0x88
		float timeToLockon;  // +0x8C
		bool performTracking;  // +0x90
		bool interpolateMaxTurningVelocity;  // +0x91
		bool useOriginatorToRequestToken;  // +0x92
		float proximity;  // +0x94
		float minDotBetweenHeadings;  // +0x98
		bool inheritSpawnerVelocity;  // +0x9C
		bool useOriginatorToValidateCollision;  // +0x9D
		bool startTrackingWhenHigher;  // +0x9E
		bool perfectlyAccurateTracking;  // +0x9F
		int trackingPosition;  // +0xA0
		float trackingDelay;  // +0xA4
		float changingAccuracySpeed;  // +0xA8
		float effectScale;  // +0xAC
		float effectScaleX;  // +0xB0
		float effectScaleY;  // +0xB4
		float thickness;  // +0xB8
		MissileSpin* spin;  // +0xBC
		ravenphysics::IntersectionPropertiesLoader* intersectionProperties;  // +0xC0
	};

	class MissileBehaviour : public WeaponBehaviour
	{
	public:
		// The intersection properties with a word behind them (name guess)
		struct IntersectionFilter
		{
			IntersectionFilter() : unknown8(0)
			{
			}

			ravenphysics::IntersectionProperties properties;
			int unknown8;
		};

		// 0x1046D160
		explicit MissileBehaviour(engine::GameObject* newOwner);
		// 0x10468490 (the deleting destructor is 0x10469970)
		virtual ~MissileBehaviour();
		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 1 (0x10467E30): the clip holds the one missile
		virtual void Slot1();
		// vftable slot 2 (0x1046BCD0) / 4 (0x10469AB0) / 5 (0x104684C0) / 6 (0x1046BF60), left to the engine
		virtual bool Slot2();
		virtual void Update(float dt, unsigned short mask);
		virtual void OnPostedMessage(engine::Message* message);
		virtual void OnMessage(engine::Message* message);
		// vftable slot 8 (0x1046AD20) / 10 (0x10468030)
		virtual void Slot8(int a, int b, float c);
		virtual void Slot10(int unused);
		// vftable slot 12 (0x10467E50) / 13 (0x104684F0)
		virtual AmmoProfileBase* GetAmmoProfile();
		virtual void SetAmmoProfile(AmmoProfileBase* profile);
		// 0x1046BCF0: stops the missile (name guess)
		void Stop();
		// vftable slot 14 (0x1046C1C0) / 15 (0x1046C540) / 16 (0x1046C780) / 17 (0x10468C80), left to the engine
		virtual void Slot14(float dt);
		virtual void Slot15();
		virtual void Slot16();
		virtual void Slot17(int a);

		engine::HandleBase unknown68;
		engine::HandleBase unknown6C;
		unsigned char unknown70[0x80 - 0x70];
		math::Vector unknown80;
		math::Vector unknown8C;
		unsigned char unknown98[0xA4 - 0x98];
		math::Vector unknownA4;
		float unknownB0;
		engine::HandleBase unknownB4;
		unsigned char unknownB8[2];
		bool unknownBA;
		float unknownBC;
		float unknownC0;
		float unknownC4;
		float unknownC8;
		float unknownCC;
		float unknownD0;
		float unknownD4;
		float unknownD8;
		float unknownDC;
		bool unknownE0;
		bool unknownE1;
		unsigned char unknownE2;
		bool unknownE3;
		float unknownE4;
		float unknownE8;
		float unknownEC;
		IntersectionFilter unknownF0;
		int unknownFC;
		float unknown100;
		MissileProfile* ammoProfile;  // +0x104
	};
}

#endif
