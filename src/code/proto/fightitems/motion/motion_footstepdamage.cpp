// Fight items of the motion group: FootstepDamageTrack (unit 0x101610C0 - 0x10161980; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_footstepdamage.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gFootstepDamageTrackProperties;  // 0x11254540

			// FUNCTION: ENGINE 0x101610C0
			bool FootstepDamageTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101610E0
			bool FootstepDamageTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10161100
			bool FootstepDamageTrack::SetPhase(float newValue)
			{
				phase = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101611D0
			bool FootstepDamageTrack::SetJointName(const fight::Name& newValue)
			{
				jointName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10161120
			bool FootstepDamageTrack::SetJointOffset(const math::Vector& newValue)
			{
				jointOffset.x = newValue.x;
				jointOffset.y = newValue.y;
				jointOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10161140
			bool FootstepDamageTrack::SetDamageType(int newValue)
			{
				damageType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10161150
			bool FootstepDamageTrack::SetAttackType(int newValue)
			{
				attackType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101611F0
			bool FootstepDamageTrack::SetHitType(const fight::Name& newValue)
			{
				hitType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10161210
			bool FootstepDamageTrack::SetEffectType(const fight::Name& newValue)
			{
				effectType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10161160
			bool FootstepDamageTrack::SetScaleX(float newValue)
			{
				scaleX = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10161180
			bool FootstepDamageTrack::SetScaleY(float newValue)
			{
				scaleY = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101611A0
			fight::Property* FootstepDamageTrack::GetProperty(int index)
			{
				return gFootstepDamageTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101611C0
			void FootstepDamageTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFootstepDamageTrackProperties);
			}

			// FUNCTION: ENGINE 0x10161230
			FootstepDamageTrack::FootstepDamageTrack() : jointOffset(0.0f, 0.0f, 0.0f), phase(0.0f), scaleX(1.0f), scaleY(1.0f), timeBegin(0.0f), timeEnd(-1.0f), attackType(0), damageType(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101612D0
			float FootstepDamageTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101612E0
			float FootstepDamageTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101612F0
			FootstepDamageTrack::~FootstepDamageTrack()
			{
			}

			// FUNCTION: ENGINE 0x101615B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FootstepDamageTrack::RegisterProperties()
			{
				if (gFootstepDamageTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FootstepDamageTrack>("timeBegin", &FootstepDamageTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FootstepDamageTrack>("timeEnd", &FootstepDamageTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FootstepDamageTrack>("phase", &FootstepDamageTrack::SetPhase);
					properties[2] = property;
					property = new fight::PropertyNameList<FootstepDamageTrack>("jointName", &FootstepDamageTrack::SetJointName);
					properties[3] = property;
					property = new fight::PropertyVector<FootstepDamageTrack>("jointOffset", &FootstepDamageTrack::SetJointOffset);
					properties[4] = property;
					property = new fight::PropertyEnumConstList<FootstepDamageTrack>("damageType", gDevastatorTargetHitTrackDamageTypeTable, gDevastatorTargetHitTrackDamageTypeCount, &FootstepDamageTrack::SetDamageType);
					properties[5] = property;
					property = new fight::PropertyEnumConstList<FootstepDamageTrack>("attackType", gTendrilDevastatorTrackAttackTypeTable, gTendrilDevastatorTrackAttackTypeCount, &FootstepDamageTrack::SetAttackType);
					properties[6] = property;
					property = new fight::PropertyNameList<FootstepDamageTrack>("hitType", &FootstepDamageTrack::SetHitType);
					properties[7] = property;
					property = new fight::PropertyNameList<FootstepDamageTrack>("effectType", &FootstepDamageTrack::SetEffectType);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<FootstepDamageTrack>("scaleX", &FootstepDamageTrack::SetScaleX);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<FootstepDamageTrack>("scaleY", &FootstepDamageTrack::SetScaleY);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gFootstepDamageTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101614F0
			fight::TrackFactory* CreateFootstepDamageTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FootstepDamageTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10161520
			void RegisterFootstepDamageTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FootstepDamageTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<FootstepDamageTrack>;
			template class fight::PropertyNameList<FootstepDamageTrack>;
			template class fight::PropertyVector<FootstepDamageTrack>;
			template class fight::PropertyEnumConstList<FootstepDamageTrack>;
			template class fight::TrackFactoryTemplate<FootstepDamageTrack>;
			template class fight::TrackFactoryCasterTemplate<FootstepDamageTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10161300
// FUNCTION: ENGINE 0x10161310
// FUNCTION: ENGINE 0x10161340
// FUNCTION: ENGINE 0x10161370
// FUNCTION: ENGINE 0x101613A0
// FUNCTION: ENGINE 0x101613D0
// FUNCTION: ENGINE 0x101613E0
// FUNCTION: ENGINE 0x10161410
// FUNCTION: ENGINE 0x10161430
// FUNCTION: ENGINE 0x10161440
// FUNCTION: ENGINE 0x10161480
// FUNCTION: ENGINE 0x10161490
// FUNCTION: ENGINE 0x101614C0
// FUNCTION: ENGINE 0x101614E0
// FUNCTION: ENGINE 0x10161550
// FUNCTION: ENGINE 0x10161580
// FUNCTION: ENGINE 0x101615A0
// FUNCTION: ENGINE 0x101618E0
// FUNCTION: ENGINE 0x10161910
// FUNCTION: ENGINE 0x10161930
