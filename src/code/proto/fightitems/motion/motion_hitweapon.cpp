// Fight items of the motion group: HitWeaponTrack (unit 0x1017C270 - 0x1017CA90; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_hitweapon.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gHitWeaponTrackProperties;  // 0x112546FC

			// FUNCTION: ENGINE 0x1017C270
			bool HitWeaponTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017C290
			bool HitWeaponTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017C350
			bool HitWeaponTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017C2B0
			bool HitWeaponTrack::SetCollisionCountMax(int newValue)
			{
				collisionCountMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017C2C0
			bool HitWeaponTrack::SetDamage(float newValue)
			{
				damage = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017C2E0
			bool HitWeaponTrack::SetDamageType(int newValue)
			{
				damageType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017C2F0
			bool HitWeaponTrack::SetImpulse(const math::Vector& newValue)
			{
				impulse.x = newValue.x;
				impulse.y = newValue.y;
				impulse.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1017C310
			fight::BranchHolder* HitWeaponTrack::SetReceiverBranch()
			{
				return &receiverBranch;
			}

			// FUNCTION: ENGINE 0x1017C320
			fight::Property* HitWeaponTrack::GetProperty(int index)
			{
				return gHitWeaponTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1017C340
			void HitWeaponTrack::ClearProperties()
			{
				fight::FreePropertyList(&gHitWeaponTrackProperties);
			}

			// FUNCTION: ENGINE 0x1017C370
			HitWeaponTrack::HitWeaponTrack() : receiverBranch(0), impulse(0.0f, 0.0f, 0.0f), damage(1.0f), timeBegin(0.0f), timeEnd(0.0f), collisionCountMax(1), damageType(0)
			{
			}

			// FUNCTION: ENGINE 0x1017C3F0
			float HitWeaponTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1017C400
			float HitWeaponTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1017C410
			HitWeaponTrack::~HitWeaponTrack()
			{
			}

			// FUNCTION: ENGINE 0x1017C790
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HitWeaponTrack::RegisterProperties()
			{
				if (gHitWeaponTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<HitWeaponTrack>("timeBegin", &HitWeaponTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<HitWeaponTrack>("timeEnd", &HitWeaponTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyNameList<HitWeaponTrack>("grabSlot", &HitWeaponTrack::SetGrabSlot);
					properties[2] = property;
					property = new fight::PropertyIntConstRange<HitWeaponTrack>("collisionCountMax", &HitWeaponTrack::SetCollisionCountMax);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<HitWeaponTrack>("damage", &HitWeaponTrack::SetDamage);
					properties[4] = property;
					property = new fight::PropertyEnumConstList<HitWeaponTrack>("damageType", gDevastatorTargetHitTrackDamageTypeTable, gDevastatorTargetHitTrackDamageTypeCount, &HitWeaponTrack::SetDamageType);
					properties[5] = property;
					property = new fight::PropertyVector<HitWeaponTrack>("impulse", &HitWeaponTrack::SetImpulse);
					properties[6] = property;
					property = new fight::PropertyBranch<HitWeaponTrack>("receiverBranch", &HitWeaponTrack::SetReceiverBranch);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gHitWeaponTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1017C6D0
			fight::TrackFactory* CreateHitWeaponTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<HitWeaponTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1017C700
			void RegisterHitWeaponTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<HitWeaponTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<HitWeaponTrack>;
			template class fight::PropertyNameList<HitWeaponTrack>;
			template class fight::PropertyIntConstRange<HitWeaponTrack>;
			template class fight::PropertyEnumConstList<HitWeaponTrack>;
			template class fight::PropertyVector<HitWeaponTrack>;
			template class fight::PropertyBranch<HitWeaponTrack>;
			template class fight::TrackFactoryTemplate<HitWeaponTrack>;
			template class fight::TrackFactoryCasterTemplate<HitWeaponTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1017C430
// FUNCTION: ENGINE 0x1017C440
// FUNCTION: ENGINE 0x1017C470
// FUNCTION: ENGINE 0x1017C4A0
// FUNCTION: ENGINE 0x1017C4D0
// FUNCTION: ENGINE 0x1017C500
// FUNCTION: ENGINE 0x1017C510
// FUNCTION: ENGINE 0x1017C540
// FUNCTION: ENGINE 0x1017C560
// FUNCTION: ENGINE 0x1017C570
// FUNCTION: ENGINE 0x1017C5B0
// FUNCTION: ENGINE 0x1017C5C0
// FUNCTION: ENGINE 0x1017C5F0
// FUNCTION: ENGINE 0x1017C610
// FUNCTION: ENGINE 0x1017C620
// FUNCTION: ENGINE 0x1017C650
// FUNCTION: ENGINE 0x1017C670
// FUNCTION: ENGINE 0x1017C680
// FUNCTION: ENGINE 0x1017C6B0
// FUNCTION: ENGINE 0x1017C730
// FUNCTION: ENGINE 0x1017C760
// FUNCTION: ENGINE 0x1017C780
// FUNCTION: ENGINE 0x1017C9F0
// FUNCTION: ENGINE 0x1017CA20
// FUNCTION: ENGINE 0x1017CA40
