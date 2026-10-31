// Fight items of the motion group: FootstepDamageTrack (unit 0x101610C0 - 0x10161980; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_FOOTSTEPDAMAGE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_FOOTSTEPDAMAGE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::FootstepDamageTrack (16 vftable slots, 0x50 bytes)
			class FootstepDamageTrack : public fight::Track
			{
			public:
				// 0x10161230
				FootstepDamageTrack();
				virtual ~FootstepDamageTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100C0530, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetPhase(float newValue);
				bool SetJointName(const fight::Name& newValue);
				bool SetJointOffset(const math::Vector& newValue);
				bool SetDamageType(int newValue);
				bool SetAttackType(int newValue);
				bool SetHitType(const fight::Name& newValue);
				bool SetEffectType(const fight::Name& newValue);
				bool SetScaleX(float newValue);
				bool SetScaleY(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name effectType;  // +0x10
					fight::Name hitType;  // +0x18
					fight::Name jointName;  // +0x20
					math::Vector jointOffset;  // +0x28
					float phase;  // +0x34
					float scaleX;  // +0x38
					float scaleY;  // +0x3C
					float timeBegin;  // +0x40
					float timeEnd;  // +0x44
					int attackType;  // +0x48
					int damageType;  // +0x4C
			};

			extern fight::Property** gFootstepDamageTrackProperties;
			fight::TrackFactory* CreateFootstepDamageTrackFactory(const char* name);
			void RegisterFootstepDamageTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
