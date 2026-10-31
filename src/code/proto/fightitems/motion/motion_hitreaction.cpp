// Fight items of the motion group: HitReactionTrack, ReactionTimeExecuteTrack, ReactionHitExecuteTrack (unit 0x1017A690 - 0x1017C270; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_hitreaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gHitReactionTrackProperties;  // 0x112546EC

			// FUNCTION: ENGINE 0x1017A690
			bool HitReactionTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A6B0
			bool HitReactionTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A6D0
			bool HitReactionTrack::SetReactionTimeMin(float newValue)
			{
				reactionTimeMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A6F0
			bool HitReactionTrack::SetReactionTimeMax(float newValue)
			{
				reactionTimeMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A710
			bool HitReactionTrack::SetReactionDistanceMin(float newValue)
			{
				reactionDistanceMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A730
			bool HitReactionTrack::SetReactionDistanceMax(float newValue)
			{
				reactionDistanceMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A750
			bool HitReactionTrack::SetReactionHeightMin(float newValue)
			{
				reactionHeightMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A770
			bool HitReactionTrack::SetReactionHeightMax(float newValue)
			{
				reactionHeightMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A790
			bool HitReactionTrack::SetReactionDirection(const math::Vector& newValue)
			{
				reactionDirection.x = newValue.x;
				reactionDirection.y = newValue.y;
				reactionDirection.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A7B0
			bool HitReactionTrack::SetAttackType(int newValue)
			{
				attackType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017AB30
			bool HitReactionTrack::SetHitType(const fight::Name& newValue)
			{
				hitType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A7C0
			bool HitReactionTrack::SetDamageType(int newValue)
			{
				damageType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017AB50
			bool HitReactionTrack::SetCollisionFlag(const fight::Name& newValue)
			{
				collisionFlag = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017AA00
			fight::Property* HitReactionTrack::GetProperty(int index)
			{
				return gHitReactionTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1017AA20
			void HitReactionTrack::ClearProperties()
			{
				fight::FreePropertyList(&gHitReactionTrackProperties);
			}

			// FUNCTION: ENGINE 0x1017ABB0
			HitReactionTrack::HitReactionTrack() : reactionDirection(0.0f, 0.0f, -1.0f), reactionDistanceMax(1.0f), reactionDistanceMin(1.0f), reactionHeightMax(0.0f), reactionHeightMin(0.0f), reactionTimeMax(1.0f), reactionTimeMin(1.0f), timeBegin(0.0f), timeEnd(-1.0f), attackType(0), damageType(0)
			{
			}

			// FUNCTION: ENGINE 0x1017AC50
			float HitReactionTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1017AC60
			float HitReactionTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1017AC70
			HitReactionTrack::~HitReactionTrack()
			{
			}

			// FUNCTION: ENGINE 0x1017B850
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HitReactionTrack::RegisterProperties()
			{
				if (gHitReactionTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<HitReactionTrack>("timeBegin", &HitReactionTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<HitReactionTrack>("timeEnd", &HitReactionTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<HitReactionTrack>("reactionTimeMin", &HitReactionTrack::SetReactionTimeMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<HitReactionTrack>("reactionTimeMax", &HitReactionTrack::SetReactionTimeMax);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<HitReactionTrack>("reactionDistanceMin", &HitReactionTrack::SetReactionDistanceMin);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<HitReactionTrack>("reactionDistanceMax", &HitReactionTrack::SetReactionDistanceMax);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<HitReactionTrack>("reactionHeightMin", &HitReactionTrack::SetReactionHeightMin);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<HitReactionTrack>("reactionHeightMax", &HitReactionTrack::SetReactionHeightMax);
					properties[7] = property;
					property = new fight::PropertyVector<HitReactionTrack>("reactionDirection", &HitReactionTrack::SetReactionDirection);
					properties[8] = property;
					property = new fight::PropertyEnumConstList<HitReactionTrack>("attackType", gTendrilDevastatorTrackAttackTypeTable, gTendrilDevastatorTrackAttackTypeCount, &HitReactionTrack::SetAttackType);
					properties[9] = property;
					property = new fight::PropertyNameList<HitReactionTrack>("hitType", &HitReactionTrack::SetHitType);
					properties[10] = property;
					property = new fight::PropertyEnumConstList<HitReactionTrack>("damageType", gDevastatorTargetHitTrackDamageTypeTable, gDevastatorTargetHitTrackDamageTypeCount, &HitReactionTrack::SetDamageType);
					properties[11] = property;
					property = new fight::PropertyName<HitReactionTrack>("collisionFlag", &HitReactionTrack::SetCollisionFlag);
					properties[12] = property;
					fight::RegisterPropertyList(properties, &gHitReactionTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1017B430
			fight::TrackFactory* CreateHitReactionTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<HitReactionTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1017B610
			void RegisterHitReactionTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<HitReactionTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gReactionTimeExecuteTrackProperties;  // 0x112546F0

			// FUNCTION: ENGINE 0x1017A7D0
			bool ReactionTimeExecuteTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A7F0
			bool ReactionTimeExecuteTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A810
			fight::ConditionList* ReactionTimeExecuteTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x1017A820
			fight::TrackGroup* ReactionTimeExecuteTrack::GetTracks()
			{
				return &tracks;
			}

			// FUNCTION: ENGINE 0x1017AA30
			fight::Property* ReactionTimeExecuteTrack::GetProperty(int index)
			{
				return gReactionTimeExecuteTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1017AA50
			void ReactionTimeExecuteTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReactionTimeExecuteTrackProperties);
			}

			// FUNCTION: ENGINE 0x1017AA60
			ReactionTimeExecuteTrack::ReactionTimeExecuteTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x1017AAB0
			float ReactionTimeExecuteTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1017AAC0
			float ReactionTimeExecuteTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1017AAD0
			ReactionTimeExecuteTrack::~ReactionTimeExecuteTrack()
			{
			}

			// FUNCTION: ENGINE 0x1017B4C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionTimeExecuteTrack::RegisterProperties()
			{
				if (gReactionTimeExecuteTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReactionTimeExecuteTrack>("timeBegin", &ReactionTimeExecuteTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReactionTimeExecuteTrack>("timeEnd", &ReactionTimeExecuteTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyConditionGroup<ReactionTimeExecuteTrack>("conditions", &ReactionTimeExecuteTrack::SetConditions);
					properties[2] = property;
					property = new fight::PropertyTrackGroup<ReactionTimeExecuteTrack>("tracks", &ReactionTimeExecuteTrack::GetTracks);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gReactionTimeExecuteTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1017B460
			fight::TrackFactory* CreateReactionTimeExecuteTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionTimeExecuteTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1017B640
			void RegisterReactionTimeExecuteTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionTimeExecuteTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gReactionHitExecuteTrackProperties;  // 0x112546F4

			// FUNCTION: ENGINE 0x1017A830
			bool ReactionHitExecuteTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A850
			bool ReactionHitExecuteTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A870
			bool ReactionHitExecuteTrack::SetReactionTimeMin(float newValue)
			{
				reactionTimeMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A890
			bool ReactionHitExecuteTrack::SetReactionTimeMax(float newValue)
			{
				reactionTimeMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A8B0
			bool ReactionHitExecuteTrack::SetReactionDistanceMin(float newValue)
			{
				reactionDistanceMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A8D0
			bool ReactionHitExecuteTrack::SetReactionDistanceMax(float newValue)
			{
				reactionDistanceMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A8F0
			bool ReactionHitExecuteTrack::SetReactionHeightMin(float newValue)
			{
				reactionHeightMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A910
			bool ReactionHitExecuteTrack::SetReactionHeightMax(float newValue)
			{
				reactionHeightMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A930
			bool ReactionHitExecuteTrack::SetReactionDirection(const math::Vector& newValue)
			{
				reactionDirection.x = newValue.x;
				reactionDirection.y = newValue.y;
				reactionDirection.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A950
			bool ReactionHitExecuteTrack::SetExtraDamage(float newValue)
			{
				extraDamage = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A970
			bool ReactionHitExecuteTrack::SetUseOriginator(bool newValue)
			{
				useOriginator = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A990
			bool ReactionHitExecuteTrack::SetSendAlert(bool newValue)
			{
				sendAlert = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A9B0
			bool ReactionHitExecuteTrack::SetAttackType(int newValue)
			{
				attackType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017AB70
			bool ReactionHitExecuteTrack::SetHitType(const fight::Name& newValue)
			{
				hitType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A9C0
			bool ReactionHitExecuteTrack::SetDamageType(int newValue)
			{
				damageType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017AB90
			bool ReactionHitExecuteTrack::SetCollisionFlag(const fight::Name& newValue)
			{
				collisionFlag = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1017A9E0
			fight::BranchHolder* ReactionHitExecuteTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x1017A9F0
			fight::ConditionList* ReactionHitExecuteTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x1017AB00
			fight::Property* ReactionHitExecuteTrack::GetProperty(int index)
			{
				return gReactionHitExecuteTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1017AB20
			void ReactionHitExecuteTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReactionHitExecuteTrackProperties);
			}

			// FUNCTION: ENGINE 0x1017ACB0
			ReactionHitExecuteTrack::ReactionHitExecuteTrack() : branch(0), reactionDirection(0.0f, 0.0f, -1.0f), extraDamage(0.0f), reactionDistanceMax(1.0f), reactionDistanceMin(1.0f), reactionHeightMax(0.0f), reactionHeightMin(0.0f), reactionTimeMax(1.0f), reactionTimeMin(1.0f), timeBegin(0.0f), timeEnd(-1.0f), attackType(0), damageType(0), sendAlert(true), useOriginator(false)
			{
			}

			// FUNCTION: ENGINE 0x1017AD90
			float ReactionHitExecuteTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1017ADA0
			float ReactionHitExecuteTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1017ADB0
			ReactionHitExecuteTrack::~ReactionHitExecuteTrack()
			{
			}

			// FUNCTION: ENGINE 0x1017BBF0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReactionHitExecuteTrack::RegisterProperties()
			{
				if (gReactionHitExecuteTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReactionHitExecuteTrack>("timeBegin", &ReactionHitExecuteTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitExecuteTrack>("timeEnd", &ReactionHitExecuteTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitExecuteTrack>("reactionTimeMin", &ReactionHitExecuteTrack::SetReactionTimeMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitExecuteTrack>("reactionTimeMax", &ReactionHitExecuteTrack::SetReactionTimeMax);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitExecuteTrack>("reactionDistanceMin", &ReactionHitExecuteTrack::SetReactionDistanceMin);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitExecuteTrack>("reactionDistanceMax", &ReactionHitExecuteTrack::SetReactionDistanceMax);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitExecuteTrack>("reactionHeightMin", &ReactionHitExecuteTrack::SetReactionHeightMin);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitExecuteTrack>("reactionHeightMax", &ReactionHitExecuteTrack::SetReactionHeightMax);
					properties[7] = property;
					property = new fight::PropertyVector<ReactionHitExecuteTrack>("reactionDirection", &ReactionHitExecuteTrack::SetReactionDirection);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<ReactionHitExecuteTrack>("extraDamage", &ReactionHitExecuteTrack::SetExtraDamage);
					properties[9] = property;
					property = new fight::PropertyBool<ReactionHitExecuteTrack>("useOriginator", &ReactionHitExecuteTrack::SetUseOriginator);
					properties[10] = property;
					property = new fight::PropertyBool<ReactionHitExecuteTrack>("sendAlert", &ReactionHitExecuteTrack::SetSendAlert);
					properties[11] = property;
					property = new fight::PropertyEnumConstList<ReactionHitExecuteTrack>("attackType", gTendrilDevastatorTrackAttackTypeTable, gTendrilDevastatorTrackAttackTypeCount, &ReactionHitExecuteTrack::SetAttackType);
					properties[12] = property;
					property = new fight::PropertyNameList<ReactionHitExecuteTrack>("hitType", &ReactionHitExecuteTrack::SetHitType);
					properties[13] = property;
					property = new fight::PropertyEnumConstList<ReactionHitExecuteTrack>("damageType", gDevastatorTargetHitTrackDamageTypeTable, gDevastatorTargetHitTrackDamageTypeCount, &ReactionHitExecuteTrack::SetDamageType);
					properties[14] = property;
					property = new fight::PropertyName<ReactionHitExecuteTrack>("collisionFlag", &ReactionHitExecuteTrack::SetCollisionFlag);
					properties[15] = property;
					property = new fight::PropertyBranch<ReactionHitExecuteTrack>("branch", &ReactionHitExecuteTrack::SetBranch);
					properties[16] = property;
					property = new fight::PropertyConditionGroup<ReactionHitExecuteTrack>("conditions", &ReactionHitExecuteTrack::SetConditions);
					properties[17] = property;
					fight::RegisterPropertyList(properties, &gReactionHitExecuteTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1017B490
			fight::TrackFactory* CreateReactionHitExecuteTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionHitExecuteTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1017B670
			void RegisterReactionHitExecuteTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReactionHitExecuteTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<HitReactionTrack>;
			template class fight::PropertyVector<HitReactionTrack>;
			template class fight::PropertyEnumConstList<HitReactionTrack>;
			template class fight::PropertyNameList<HitReactionTrack>;
			template class fight::PropertyName<HitReactionTrack>;
			template class fight::TrackFactoryTemplate<HitReactionTrack>;
			template class fight::TrackFactoryCasterTemplate<HitReactionTrack>;
			template class fight::PropertyFloatConstRange<ReactionTimeExecuteTrack>;
			template class fight::PropertyConditionGroup<ReactionTimeExecuteTrack>;
			template class fight::PropertyTrackGroup<ReactionTimeExecuteTrack>;
			template class fight::TrackFactoryTemplate<ReactionTimeExecuteTrack>;
			template class fight::TrackFactoryCasterTemplate<ReactionTimeExecuteTrack>;
			template class fight::PropertyFloatConstRange<ReactionHitExecuteTrack>;
			template class fight::PropertyVector<ReactionHitExecuteTrack>;
			template class fight::PropertyBool<ReactionHitExecuteTrack>;
			template class fight::PropertyEnumConstList<ReactionHitExecuteTrack>;
			template class fight::PropertyNameList<ReactionHitExecuteTrack>;
			template class fight::PropertyName<ReactionHitExecuteTrack>;
			template class fight::PropertyBranch<ReactionHitExecuteTrack>;
			template class fight::PropertyConditionGroup<ReactionHitExecuteTrack>;
			template class fight::TrackFactoryTemplate<ReactionHitExecuteTrack>;
			template class fight::TrackFactoryCasterTemplate<ReactionHitExecuteTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1017AC80
// FUNCTION: ENGINE 0x1017ADF0
// FUNCTION: ENGINE 0x1017AE00
// FUNCTION: ENGINE 0x1017AE30
// FUNCTION: ENGINE 0x1017AE40
// FUNCTION: ENGINE 0x1017AE70
// FUNCTION: ENGINE 0x1017AE80
// FUNCTION: ENGINE 0x1017AEB0
// FUNCTION: ENGINE 0x1017AEE0
// FUNCTION: ENGINE 0x1017AF10
// FUNCTION: ENGINE 0x1017AF40
// FUNCTION: ENGINE 0x1017AF70
// FUNCTION: ENGINE 0x1017AF80
// FUNCTION: ENGINE 0x1017AFB0
// FUNCTION: ENGINE 0x1017AFD0
// FUNCTION: ENGINE 0x1017AFE0
// FUNCTION: ENGINE 0x1017B020
// FUNCTION: ENGINE 0x1017B030
// FUNCTION: ENGINE 0x1017B060
// FUNCTION: ENGINE 0x1017B080
// FUNCTION: ENGINE 0x1017B090
// FUNCTION: ENGINE 0x1017B0C0
// FUNCTION: ENGINE 0x1017B0F0
// FUNCTION: ENGINE 0x1017B100
// FUNCTION: ENGINE 0x1017B130
// FUNCTION: ENGINE 0x1017B150
// FUNCTION: ENGINE 0x1017B190
// FUNCTION: ENGINE 0x1017B1B0
// FUNCTION: ENGINE 0x1017B1E0
// FUNCTION: ENGINE 0x1017B210
// FUNCTION: ENGINE 0x1017B220
// FUNCTION: ENGINE 0x1017B250
// FUNCTION: ENGINE 0x1017B270
// FUNCTION: ENGINE 0x1017B280
// FUNCTION: ENGINE 0x1017B2B0
// FUNCTION: ENGINE 0x1017B2D0
// FUNCTION: ENGINE 0x1017B2E0
// FUNCTION: ENGINE 0x1017B320
// FUNCTION: ENGINE 0x1017B330
// FUNCTION: ENGINE 0x1017B360
// FUNCTION: ENGINE 0x1017B380
// FUNCTION: ENGINE 0x1017B390
// FUNCTION: ENGINE 0x1017B3C0
// FUNCTION: ENGINE 0x1017B3E0
// FUNCTION: ENGINE 0x1017B410
// FUNCTION: ENGINE 0x1017B6A0
// FUNCTION: ENGINE 0x1017B6D0
// FUNCTION: ENGINE 0x1017B6F0
// FUNCTION: ENGINE 0x1017B700
// FUNCTION: ENGINE 0x1017B730
// FUNCTION: ENGINE 0x1017B750
// FUNCTION: ENGINE 0x1017B780
// FUNCTION: ENGINE 0x1017B7A0
// FUNCTION: ENGINE 0x1017B7B0
// FUNCTION: ENGINE 0x1017B7E0
// FUNCTION: ENGINE 0x1017B800
// FUNCTION: ENGINE 0x1017B830
// FUNCTION: ENGINE 0x1017C0D0
// FUNCTION: ENGINE 0x1017C120
// FUNCTION: ENGINE 0x1017C150
// FUNCTION: ENGINE 0x1017C170
// FUNCTION: ENGINE 0x1017C1A0
// FUNCTION: ENGINE 0x1017C1D0
// FUNCTION: ENGINE 0x1017C220
