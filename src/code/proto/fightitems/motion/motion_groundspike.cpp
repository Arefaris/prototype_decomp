// Fight items of the motion group: GroundSpikeParentConditionGroupCondition, GroundSpikeTestStateCondition, GroundSpikeClusterDescendTrack, GroundSpikeConfigureAutoOffshootsTrack, GroundSpikeSpawnClusterTrack, GroundSpikeAnimateClusterRadiiTrack, GroundSpikeSpawnOffshootTrack (unit 0x101753C0 - 0x10177EA0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_groundspike.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gGroundSpikeParentConditionGroupConditionProperties;  // 0x1125469C

			// FUNCTION: ENGINE 0x101753C0
			fight::ConditionList* GroundSpikeParentConditionGroupCondition::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x101758F0
			fight::Property* GroundSpikeParentConditionGroupCondition::GetProperty(int index)
			{
				return gGroundSpikeParentConditionGroupConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10175910
			void GroundSpikeParentConditionGroupCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGroundSpikeParentConditionGroupConditionProperties);
			}

			// FUNCTION: ENGINE 0x10175920
			GroundSpikeParentConditionGroupCondition::GroundSpikeParentConditionGroupCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x10175950
			GroundSpikeParentConditionGroupCondition::~GroundSpikeParentConditionGroupCondition()
			{
			}

			// FUNCTION: ENGINE 0x101768A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GroundSpikeParentConditionGroupCondition::RegisterProperties()
			{
				if (gGroundSpikeParentConditionGroupConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyConditionGroup<GroundSpikeParentConditionGroupCondition>("conditions", &GroundSpikeParentConditionGroupCondition::SetConditions);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gGroundSpikeParentConditionGroupConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10176750
			fight::ConditionFactory* CreateGroundSpikeParentConditionGroupConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GroundSpikeParentConditionGroupCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10176F00
			void RegisterGroundSpikeParentConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GroundSpikeParentConditionGroupCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGroundSpikeTestStateConditionProperties;  // 0x112546A0

			// FUNCTION: ENGINE 0x101753D0
			bool GroundSpikeTestStateCondition::SetTestType(int newValue)
			{
				testType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175970
			fight::Property* GroundSpikeTestStateCondition::GetProperty(int index)
			{
				return gGroundSpikeTestStateConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10175990
			void GroundSpikeTestStateCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGroundSpikeTestStateConditionProperties);
			}

			// FUNCTION: ENGINE 0x101759A0
			GroundSpikeTestStateCondition::GroundSpikeTestStateCondition() : fight::Condition(0), testType(0)
			{
			}

			// FUNCTION: ENGINE 0x101759D0
			GroundSpikeTestStateCondition::~GroundSpikeTestStateCondition()
			{
			}

			// FUNCTION: ENGINE 0x10176940
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GroundSpikeTestStateCondition::RegisterProperties()
			{
				if (gGroundSpikeTestStateConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<GroundSpikeTestStateCondition>("testType", gGroundSpikeTestStateConditionTestTypeTable, gGroundSpikeTestStateConditionTestTypeCount, &GroundSpikeTestStateCondition::SetTestType);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gGroundSpikeTestStateConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10176780
			fight::ConditionFactory* CreateGroundSpikeTestStateConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GroundSpikeTestStateCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10176F30
			void RegisterGroundSpikeTestStateConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GroundSpikeTestStateCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGroundSpikeClusterDescendTrackProperties;  // 0x112546A4

			// FUNCTION: ENGINE 0x101753E0
			bool GroundSpikeClusterDescendTrack::SetApplyToOffshoots(bool newValue)
			{
				applyToOffshoots = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101753F0
			bool GroundSpikeClusterDescendTrack::SetDescendDuration(float newValue)
			{
				descendDuration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175410
			bool GroundSpikeClusterDescendTrack::SetDescendDelayMin(float newValue)
			{
				descendDelayMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175430
			bool GroundSpikeClusterDescendTrack::SetDescendDelayMax(float newValue)
			{
				descendDelayMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175470
			bool GroundSpikeClusterDescendTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175450
			bool GroundSpikeClusterDescendTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101759E0
			fight::Property* GroundSpikeClusterDescendTrack::GetProperty(int index)
			{
				return gGroundSpikeClusterDescendTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10175A00
			void GroundSpikeClusterDescendTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGroundSpikeClusterDescendTrackProperties);
			}

			// FUNCTION: ENGINE 0x10175A10
			GroundSpikeClusterDescendTrack::GroundSpikeClusterDescendTrack() : descendDelayMax(0.5f), descendDelayMin(0.0f), descendDuration(0.2f), timeBegin(0.0f), timeEnd(0.0f), applyToOffshoots(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10175A70
			float GroundSpikeClusterDescendTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10175A80
			float GroundSpikeClusterDescendTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10175A90
			GroundSpikeClusterDescendTrack::~GroundSpikeClusterDescendTrack()
			{
			}

			// FUNCTION: ENGINE 0x101769F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GroundSpikeClusterDescendTrack::RegisterProperties()
			{
				if (gGroundSpikeClusterDescendTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<GroundSpikeClusterDescendTrack>("applyToOffshoots", &GroundSpikeClusterDescendTrack::SetApplyToOffshoots);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeClusterDescendTrack>("descendDuration", &GroundSpikeClusterDescendTrack::SetDescendDuration);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeClusterDescendTrack>("descendDelayMin", &GroundSpikeClusterDescendTrack::SetDescendDelayMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeClusterDescendTrack>("descendDelayMax", &GroundSpikeClusterDescendTrack::SetDescendDelayMax);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeClusterDescendTrack>("timeBegin", &GroundSpikeClusterDescendTrack::SetTimeBegin);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeClusterDescendTrack>("timeEnd", &GroundSpikeClusterDescendTrack::SetTimeEnd);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gGroundSpikeClusterDescendTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101767B0
			fight::TrackFactory* CreateGroundSpikeClusterDescendTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GroundSpikeClusterDescendTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10176F60
			void RegisterGroundSpikeClusterDescendTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GroundSpikeClusterDescendTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGroundSpikeConfigureAutoOffshootsTrackProperties;  // 0x112546A8

			// FUNCTION: ENGINE 0x10175C00
			bool GroundSpikeConfigureAutoOffshootsTrack::SetType(const fight::Name& newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175490
			bool GroundSpikeConfigureAutoOffshootsTrack::SetStep(float newValue)
			{
				step = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101754B0
			bool GroundSpikeConfigureAutoOffshootsTrack::SetMaxDistance(float newValue)
			{
				maxDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101754D0
			bool GroundSpikeConfigureAutoOffshootsTrack::SetOffsetAngleMin(float newValue)
			{
				offsetAngleMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101754F0
			bool GroundSpikeConfigureAutoOffshootsTrack::SetOffsetAngleMax(float newValue)
			{
				offsetAngleMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10175510
			bool GroundSpikeConfigureAutoOffshootsTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175530
			bool GroundSpikeConfigureAutoOffshootsTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175AA0
			fight::Property* GroundSpikeConfigureAutoOffshootsTrack::GetProperty(int index)
			{
				return gGroundSpikeConfigureAutoOffshootsTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10175AC0
			void GroundSpikeConfigureAutoOffshootsTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGroundSpikeConfigureAutoOffshootsTrackProperties);
			}

			// FUNCTION: ENGINE 0x10175D30
			GroundSpikeConfigureAutoOffshootsTrack::GroundSpikeConfigureAutoOffshootsTrack() : maxDistance(2e+01f), offsetAngleMax(0.7853982f), offsetAngleMin(0.7853982f), step(5.0f), timeBegin(0.0f), timeEnd(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10175DA0
			float GroundSpikeConfigureAutoOffshootsTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10175DB0
			float GroundSpikeConfigureAutoOffshootsTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10175DC0
			GroundSpikeConfigureAutoOffshootsTrack::~GroundSpikeConfigureAutoOffshootsTrack()
			{
			}

			// FUNCTION: ENGINE 0x10177280
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GroundSpikeConfigureAutoOffshootsTrack::RegisterProperties()
			{
				if (gGroundSpikeConfigureAutoOffshootsTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<GroundSpikeConfigureAutoOffshootsTrack>("type", &GroundSpikeConfigureAutoOffshootsTrack::SetType);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeConfigureAutoOffshootsTrack>("step", &GroundSpikeConfigureAutoOffshootsTrack::SetStep);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeConfigureAutoOffshootsTrack>("maxDistance", &GroundSpikeConfigureAutoOffshootsTrack::SetMaxDistance);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeConfigureAutoOffshootsTrack>("offsetAngleMin", &GroundSpikeConfigureAutoOffshootsTrack::SetOffsetAngleMin);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeConfigureAutoOffshootsTrack>("offsetAngleMax", &GroundSpikeConfigureAutoOffshootsTrack::SetOffsetAngleMax);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeConfigureAutoOffshootsTrack>("timeBegin", &GroundSpikeConfigureAutoOffshootsTrack::SetTimeBegin);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeConfigureAutoOffshootsTrack>("timeEnd", &GroundSpikeConfigureAutoOffshootsTrack::SetTimeEnd);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gGroundSpikeConfigureAutoOffshootsTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101767E0
			fight::TrackFactory* CreateGroundSpikeConfigureAutoOffshootsTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GroundSpikeConfigureAutoOffshootsTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10176F90
			void RegisterGroundSpikeConfigureAutoOffshootsTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GroundSpikeConfigureAutoOffshootsTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGroundSpikeSpawnClusterTrackProperties;  // 0x112546AC

			// FUNCTION: ENGINE 0x10175C20
			bool GroundSpikeSpawnClusterTrack::SetLargeType(const fight::Name& newValue)
			{
				largeType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175C40
			bool GroundSpikeSpawnClusterTrack::SetMidType(const fight::Name& newValue)
			{
				midType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175C60
			bool GroundSpikeSpawnClusterTrack::SetSmallType(const fight::Name& newValue)
			{
				smallType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175550
			bool GroundSpikeSpawnClusterTrack::SetLargeFrac(float newValue)
			{
				largeFrac = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175570
			bool GroundSpikeSpawnClusterTrack::SetMidFrac(float newValue)
			{
				midFrac = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175590
			bool GroundSpikeSpawnClusterTrack::SetSmallFrac(float newValue)
			{
				smallFrac = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101755B0
			bool GroundSpikeSpawnClusterTrack::SetMinShards(int newValue)
			{
				minShards = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101755C0
			bool GroundSpikeSpawnClusterTrack::SetMaxShards(int newValue)
			{
				maxShards = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101755D0
			bool GroundSpikeSpawnClusterTrack::SetSpawnRadius(float newValue)
			{
				spawnRadius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101755F0
			bool GroundSpikeSpawnClusterTrack::SetSpreadRadius(float newValue)
			{
				spreadRadius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175610
			bool GroundSpikeSpawnClusterTrack::SetTimingRandomizerFrac(float newValue)
			{
				timingRandomizerFrac = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175630
			bool GroundSpikeSpawnClusterTrack::SetAscendTimeMin(float newValue)
			{
				ascendTimeMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175650
			bool GroundSpikeSpawnClusterTrack::SetAscendTimeMax(float newValue)
			{
				ascendTimeMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175670
			bool GroundSpikeSpawnClusterTrack::SetTwistMin(float newValue)
			{
				twistMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175690
			bool GroundSpikeSpawnClusterTrack::SetTwistMax(float newValue)
			{
				twistMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101756B0
			bool GroundSpikeSpawnClusterTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101756D0
			bool GroundSpikeSpawnClusterTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175AD0
			fight::Property* GroundSpikeSpawnClusterTrack::GetProperty(int index)
			{
				return gGroundSpikeSpawnClusterTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10175AF0
			void GroundSpikeSpawnClusterTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGroundSpikeSpawnClusterTrackProperties);
			}

			// FUNCTION: ENGINE 0x10175DD0
			GroundSpikeSpawnClusterTrack::GroundSpikeSpawnClusterTrack() : ascendTimeMax(0.5f), ascendTimeMin(0.25f), largeFrac(0.4f), midFrac(0.3f), smallFrac(0.3f), spawnRadius(1.0f), spreadRadius(1.0f), timeBegin(0.0f), timeEnd(0.0f), timingRandomizerFrac(0.5f), twistMax(0.0f), twistMin(0.0f), maxShards(5), minShards(5)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10175EA0
			float GroundSpikeSpawnClusterTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10175EB0
			float GroundSpikeSpawnClusterTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10175EC0
			GroundSpikeSpawnClusterTrack::~GroundSpikeSpawnClusterTrack()
			{
			}

			// FUNCTION: ENGINE 0x10177490
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GroundSpikeSpawnClusterTrack::RegisterProperties()
			{
				if (gGroundSpikeSpawnClusterTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<GroundSpikeSpawnClusterTrack>("largeType", &GroundSpikeSpawnClusterTrack::SetLargeType);
					properties[0] = property;
					property = new fight::PropertyName<GroundSpikeSpawnClusterTrack>("midType", &GroundSpikeSpawnClusterTrack::SetMidType);
					properties[1] = property;
					property = new fight::PropertyName<GroundSpikeSpawnClusterTrack>("smallType", &GroundSpikeSpawnClusterTrack::SetSmallType);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeSpawnClusterTrack>("largeFrac", &GroundSpikeSpawnClusterTrack::SetLargeFrac);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeSpawnClusterTrack>("midFrac", &GroundSpikeSpawnClusterTrack::SetMidFrac);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeSpawnClusterTrack>("smallFrac", &GroundSpikeSpawnClusterTrack::SetSmallFrac);
					properties[5] = property;
					property = new fight::PropertyIntConstRange<GroundSpikeSpawnClusterTrack>("minShards", &GroundSpikeSpawnClusterTrack::SetMinShards);
					properties[6] = property;
					property = new fight::PropertyIntConstRange<GroundSpikeSpawnClusterTrack>("maxShards", &GroundSpikeSpawnClusterTrack::SetMaxShards);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeSpawnClusterTrack>("spawnRadius", &GroundSpikeSpawnClusterTrack::SetSpawnRadius);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeSpawnClusterTrack>("spreadRadius", &GroundSpikeSpawnClusterTrack::SetSpreadRadius);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeSpawnClusterTrack>("timingRandomizerFrac", &GroundSpikeSpawnClusterTrack::SetTimingRandomizerFrac);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeSpawnClusterTrack>("ascendTimeMin", &GroundSpikeSpawnClusterTrack::SetAscendTimeMin);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeSpawnClusterTrack>("ascendTimeMax", &GroundSpikeSpawnClusterTrack::SetAscendTimeMax);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeSpawnClusterTrack>("twistMin", &GroundSpikeSpawnClusterTrack::SetTwistMin);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeSpawnClusterTrack>("twistMax", &GroundSpikeSpawnClusterTrack::SetTwistMax);
					properties[14] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeSpawnClusterTrack>("timeBegin", &GroundSpikeSpawnClusterTrack::SetTimeBegin);
					properties[15] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeSpawnClusterTrack>("timeEnd", &GroundSpikeSpawnClusterTrack::SetTimeEnd);
					properties[16] = property;
					fight::RegisterPropertyList(properties, &gGroundSpikeSpawnClusterTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10176810
			fight::TrackFactory* CreateGroundSpikeSpawnClusterTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GroundSpikeSpawnClusterTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10176FC0
			void RegisterGroundSpikeSpawnClusterTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GroundSpikeSpawnClusterTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGroundSpikeAnimateClusterRadiiTrackProperties;  // 0x112546B0

			// FUNCTION: ENGINE 0x101756F0
			bool GroundSpikeAnimateClusterRadiiTrack::SetDelay(float newValue)
			{
				delay = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175710
			bool GroundSpikeAnimateClusterRadiiTrack::SetSpawnRadiusVelocityType(int newValue)
			{
				spawnRadiusVelocityType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175720
			bool GroundSpikeAnimateClusterRadiiTrack::SetSpawnEndRadiusScalar(float newValue)
			{
				spawnEndRadiusScalar = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175740
			bool GroundSpikeAnimateClusterRadiiTrack::SetSpreadRadiusVelocityType(int newValue)
			{
				spreadRadiusVelocityType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175750
			bool GroundSpikeAnimateClusterRadiiTrack::SetSpreadEndRadiusScalar(float newValue)
			{
				spreadEndRadiusScalar = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175770
			bool GroundSpikeAnimateClusterRadiiTrack::SetOffsetVelocityType(int newValue)
			{
				offsetVelocityType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175780
			bool GroundSpikeAnimateClusterRadiiTrack::SetOffsetAtEnd(float newValue)
			{
				offsetAtEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101757A0
			bool GroundSpikeAnimateClusterRadiiTrack::SetAnimationTimeMin(float newValue)
			{
				animationTimeMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101757C0
			bool GroundSpikeAnimateClusterRadiiTrack::SetAnimationTimeMax(float newValue)
			{
				animationTimeMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101757E0
			bool GroundSpikeAnimateClusterRadiiTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175800
			bool GroundSpikeAnimateClusterRadiiTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175B00
			fight::Property* GroundSpikeAnimateClusterRadiiTrack::GetProperty(int index)
			{
				return gGroundSpikeAnimateClusterRadiiTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10175B20
			void GroundSpikeAnimateClusterRadiiTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGroundSpikeAnimateClusterRadiiTrackProperties);
			}

			// FUNCTION: ENGINE 0x10175B30
			GroundSpikeAnimateClusterRadiiTrack::GroundSpikeAnimateClusterRadiiTrack() : animationTimeMax(1.0f), animationTimeMin(1.0f), delay(0.0f), offsetAtEnd(0.0f), spawnEndRadiusScalar(1.0f), spreadEndRadiusScalar(1.0f), timeBegin(0.0f), timeEnd(0.0f), offsetVelocityType(0), spawnRadiusVelocityType(0), spreadRadiusVelocityType(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10175BA0
			float GroundSpikeAnimateClusterRadiiTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10175BB0
			float GroundSpikeAnimateClusterRadiiTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10175BC0
			GroundSpikeAnimateClusterRadiiTrack::~GroundSpikeAnimateClusterRadiiTrack()
			{
			}

			// FUNCTION: ENGINE 0x10176BC0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GroundSpikeAnimateClusterRadiiTrack::RegisterProperties()
			{
				if (gGroundSpikeAnimateClusterRadiiTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<GroundSpikeAnimateClusterRadiiTrack>("delay", &GroundSpikeAnimateClusterRadiiTrack::SetDelay);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<GroundSpikeAnimateClusterRadiiTrack>("spawnRadiusVelocityType", gGroundSpikeAnimateClusterRadiiTrackSpawnRadiusVelocityTypeTable, gGroundSpikeAnimateClusterRadiiTrackSpawnRadiusVelocityTypeCount, &GroundSpikeAnimateClusterRadiiTrack::SetSpawnRadiusVelocityType);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeAnimateClusterRadiiTrack>("spawnEndRadiusScalar", &GroundSpikeAnimateClusterRadiiTrack::SetSpawnEndRadiusScalar);
					properties[2] = property;
					property = new fight::PropertyEnumConstList<GroundSpikeAnimateClusterRadiiTrack>("spreadRadiusVelocityType", gGroundSpikeAnimateClusterRadiiTrackSpawnRadiusVelocityTypeTable, gGroundSpikeAnimateClusterRadiiTrackSpawnRadiusVelocityTypeCount, &GroundSpikeAnimateClusterRadiiTrack::SetSpreadRadiusVelocityType);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeAnimateClusterRadiiTrack>("spreadEndRadiusScalar", &GroundSpikeAnimateClusterRadiiTrack::SetSpreadEndRadiusScalar);
					properties[4] = property;
					property = new fight::PropertyEnumConstList<GroundSpikeAnimateClusterRadiiTrack>("offsetVelocityType", gGroundSpikeAnimateClusterRadiiTrackSpawnRadiusVelocityTypeTable, gGroundSpikeAnimateClusterRadiiTrackSpawnRadiusVelocityTypeCount, &GroundSpikeAnimateClusterRadiiTrack::SetOffsetVelocityType);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeAnimateClusterRadiiTrack>("offsetAtEnd", &GroundSpikeAnimateClusterRadiiTrack::SetOffsetAtEnd);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeAnimateClusterRadiiTrack>("animationTimeMin", &GroundSpikeAnimateClusterRadiiTrack::SetAnimationTimeMin);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeAnimateClusterRadiiTrack>("animationTimeMax", &GroundSpikeAnimateClusterRadiiTrack::SetAnimationTimeMax);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeAnimateClusterRadiiTrack>("timeBegin", &GroundSpikeAnimateClusterRadiiTrack::SetTimeBegin);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeAnimateClusterRadiiTrack>("timeEnd", &GroundSpikeAnimateClusterRadiiTrack::SetTimeEnd);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gGroundSpikeAnimateClusterRadiiTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10176840
			fight::TrackFactory* CreateGroundSpikeAnimateClusterRadiiTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GroundSpikeAnimateClusterRadiiTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10176FF0
			void RegisterGroundSpikeAnimateClusterRadiiTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GroundSpikeAnimateClusterRadiiTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gGroundSpikeSpawnOffshootTrackProperties;  // 0x112546B4

			// FUNCTION: ENGINE 0x10175C80
			bool GroundSpikeSpawnOffshootTrack::SetType(const fight::Name& newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175820
			bool GroundSpikeSpawnOffshootTrack::SetNumMin(int newValue)
			{
				numMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175830
			bool GroundSpikeSpawnOffshootTrack::SetNumMax(int newValue)
			{
				numMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175840
			bool GroundSpikeSpawnOffshootTrack::SetIsForSuperSpike(bool newValue)
			{
				isForSuperSpike = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175850
			bool GroundSpikeSpawnOffshootTrack::SetMaxArc(float newValue)
			{
				maxArc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10175870
			bool GroundSpikeSpawnOffshootTrack::SetAngleOffsetMin(float newValue)
			{
				angleOffsetMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10175890
			bool GroundSpikeSpawnOffshootTrack::SetAngleOffsetMax(float newValue)
			{
				angleOffsetMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101758B0
			bool GroundSpikeSpawnOffshootTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101758D0
			bool GroundSpikeSpawnOffshootTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10175BD0
			fight::Property* GroundSpikeSpawnOffshootTrack::GetProperty(int index)
			{
				return gGroundSpikeSpawnOffshootTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10175BF0
			void GroundSpikeSpawnOffshootTrack::ClearProperties()
			{
				fight::FreePropertyList(&gGroundSpikeSpawnOffshootTrackProperties);
			}

			// FUNCTION: ENGINE 0x10175F00
			GroundSpikeSpawnOffshootTrack::GroundSpikeSpawnOffshootTrack() : angleOffsetMax(0.7853982f), angleOffsetMin(0.7853982f), maxArc(1.5707964f), timeBegin(0.0f), timeEnd(0.0f), numMax(1), numMin(1), isForSuperSpike(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10175F70
			float GroundSpikeSpawnOffshootTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10175F80
			float GroundSpikeSpawnOffshootTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10175F90
			GroundSpikeSpawnOffshootTrack::~GroundSpikeSpawnOffshootTrack()
			{
			}

			// FUNCTION: ENGINE 0x10177900
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GroundSpikeSpawnOffshootTrack::RegisterProperties()
			{
				if (gGroundSpikeSpawnOffshootTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<GroundSpikeSpawnOffshootTrack>("type", &GroundSpikeSpawnOffshootTrack::SetType);
					properties[0] = property;
					property = new fight::PropertyIntConstRange<GroundSpikeSpawnOffshootTrack>("numMin", &GroundSpikeSpawnOffshootTrack::SetNumMin);
					properties[1] = property;
					property = new fight::PropertyIntConstRange<GroundSpikeSpawnOffshootTrack>("numMax", &GroundSpikeSpawnOffshootTrack::SetNumMax);
					properties[2] = property;
					property = new fight::PropertyBool<GroundSpikeSpawnOffshootTrack>("isForSuperSpike", &GroundSpikeSpawnOffshootTrack::SetIsForSuperSpike);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeSpawnOffshootTrack>("maxArc", &GroundSpikeSpawnOffshootTrack::SetMaxArc);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeSpawnOffshootTrack>("angleOffsetMin", &GroundSpikeSpawnOffshootTrack::SetAngleOffsetMin);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeSpawnOffshootTrack>("angleOffsetMax", &GroundSpikeSpawnOffshootTrack::SetAngleOffsetMax);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeSpawnOffshootTrack>("timeBegin", &GroundSpikeSpawnOffshootTrack::SetTimeBegin);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<GroundSpikeSpawnOffshootTrack>("timeEnd", &GroundSpikeSpawnOffshootTrack::SetTimeEnd);
					properties[8] = property;
					fight::RegisterPropertyList(properties, &gGroundSpikeSpawnOffshootTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10176870
			fight::TrackFactory* CreateGroundSpikeSpawnOffshootTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<GroundSpikeSpawnOffshootTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10177020
			void RegisterGroundSpikeSpawnOffshootTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<GroundSpikeSpawnOffshootTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyConditionGroup<GroundSpikeParentConditionGroupCondition>;
			template class fight::ConditionFactoryTemplate<GroundSpikeParentConditionGroupCondition>;
			template class fight::ConditionFactoryCasterTemplate<GroundSpikeParentConditionGroupCondition>;
			template class fight::PropertyEnumConstList<GroundSpikeTestStateCondition>;
			template class fight::ConditionFactoryTemplate<GroundSpikeTestStateCondition>;
			template class fight::ConditionFactoryCasterTemplate<GroundSpikeTestStateCondition>;
			template class fight::PropertyBool<GroundSpikeClusterDescendTrack>;
			template class fight::PropertyFloatConstRange<GroundSpikeClusterDescendTrack>;
			template class fight::TrackFactoryTemplate<GroundSpikeClusterDescendTrack>;
			template class fight::TrackFactoryCasterTemplate<GroundSpikeClusterDescendTrack>;
			template class fight::PropertyName<GroundSpikeConfigureAutoOffshootsTrack>;
			template class fight::PropertyFloatConstRange<GroundSpikeConfigureAutoOffshootsTrack>;
			template class fight::TrackFactoryTemplate<GroundSpikeConfigureAutoOffshootsTrack>;
			template class fight::TrackFactoryCasterTemplate<GroundSpikeConfigureAutoOffshootsTrack>;
			template class fight::PropertyName<GroundSpikeSpawnClusterTrack>;
			template class fight::PropertyFloatConstRange<GroundSpikeSpawnClusterTrack>;
			template class fight::PropertyIntConstRange<GroundSpikeSpawnClusterTrack>;
			template class fight::TrackFactoryTemplate<GroundSpikeSpawnClusterTrack>;
			template class fight::TrackFactoryCasterTemplate<GroundSpikeSpawnClusterTrack>;
			template class fight::PropertyFloatConstRange<GroundSpikeAnimateClusterRadiiTrack>;
			template class fight::PropertyEnumConstList<GroundSpikeAnimateClusterRadiiTrack>;
			template class fight::TrackFactoryTemplate<GroundSpikeAnimateClusterRadiiTrack>;
			template class fight::TrackFactoryCasterTemplate<GroundSpikeAnimateClusterRadiiTrack>;
			template class fight::PropertyName<GroundSpikeSpawnOffshootTrack>;
			template class fight::PropertyIntConstRange<GroundSpikeSpawnOffshootTrack>;
			template class fight::PropertyBool<GroundSpikeSpawnOffshootTrack>;
			template class fight::PropertyFloatConstRange<GroundSpikeSpawnOffshootTrack>;
			template class fight::TrackFactoryTemplate<GroundSpikeSpawnOffshootTrack>;
			template class fight::TrackFactoryCasterTemplate<GroundSpikeSpawnOffshootTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10175CA0
// FUNCTION: ENGINE 0x10175CD0
// FUNCTION: ENGINE 0x10175D00
// FUNCTION: ENGINE 0x10175ED0
// FUNCTION: ENGINE 0x10175FA0
// FUNCTION: ENGINE 0x10175FB0
// FUNCTION: ENGINE 0x10175FE0
// FUNCTION: ENGINE 0x10175FF0
// FUNCTION: ENGINE 0x10176020
// FUNCTION: ENGINE 0x10176030
// FUNCTION: ENGINE 0x10176060
// FUNCTION: ENGINE 0x10176070
// FUNCTION: ENGINE 0x101760A0
// FUNCTION: ENGINE 0x101760B0
// FUNCTION: ENGINE 0x101760E0
// FUNCTION: ENGINE 0x101760F0
// FUNCTION: ENGINE 0x10176120
// FUNCTION: ENGINE 0x10176130
// FUNCTION: ENGINE 0x10176160
// FUNCTION: ENGINE 0x10176190
// FUNCTION: ENGINE 0x101761C0
// FUNCTION: ENGINE 0x101761F0
// FUNCTION: ENGINE 0x10176220
// FUNCTION: ENGINE 0x10176240
// FUNCTION: ENGINE 0x10176280
// FUNCTION: ENGINE 0x10176290
// FUNCTION: ENGINE 0x101762C0
// FUNCTION: ENGINE 0x101762E0
// FUNCTION: ENGINE 0x101762F0
// FUNCTION: ENGINE 0x10176320
// FUNCTION: ENGINE 0x10176340
// FUNCTION: ENGINE 0x10176350
// FUNCTION: ENGINE 0x10176380
// FUNCTION: ENGINE 0x101763B0
// FUNCTION: ENGINE 0x101763C0
// FUNCTION: ENGINE 0x101763F0
// FUNCTION: ENGINE 0x10176420
// FUNCTION: ENGINE 0x10176430
// FUNCTION: ENGINE 0x10176460
// FUNCTION: ENGINE 0x10176490
// FUNCTION: ENGINE 0x101764A0
// FUNCTION: ENGINE 0x101764D0
// FUNCTION: ENGINE 0x101764F0
// FUNCTION: ENGINE 0x10176500
// FUNCTION: ENGINE 0x10176530
// FUNCTION: ENGINE 0x10176560
// FUNCTION: ENGINE 0x10176570
// FUNCTION: ENGINE 0x101765B0
// FUNCTION: ENGINE 0x101765C0
// FUNCTION: ENGINE 0x101765F0
// FUNCTION: ENGINE 0x10176610
// FUNCTION: ENGINE 0x10176620
// FUNCTION: ENGINE 0x10176650
// FUNCTION: ENGINE 0x10176670
// FUNCTION: ENGINE 0x10176680
// FUNCTION: ENGINE 0x101766B0
// FUNCTION: ENGINE 0x101766D0
// FUNCTION: ENGINE 0x101766E0
// FUNCTION: ENGINE 0x10176710
// FUNCTION: ENGINE 0x10176740
// FUNCTION: ENGINE 0x10177050
// FUNCTION: ENGINE 0x10177080
// FUNCTION: ENGINE 0x101770A0
// FUNCTION: ENGINE 0x101770D0
// FUNCTION: ENGINE 0x101770F0
// FUNCTION: ENGINE 0x10177120
// FUNCTION: ENGINE 0x10177140
// FUNCTION: ENGINE 0x10177170
// FUNCTION: ENGINE 0x10177190
// FUNCTION: ENGINE 0x101771C0
// FUNCTION: ENGINE 0x101771E0
// FUNCTION: ENGINE 0x10177210
// FUNCTION: ENGINE 0x10177230
// FUNCTION: ENGINE 0x10177260
// FUNCTION: ENGINE 0x10177B80
// FUNCTION: ENGINE 0x10177BD0
// FUNCTION: ENGINE 0x10177C20
// FUNCTION: ENGINE 0x10177C70
// FUNCTION: ENGINE 0x10177CC0
// FUNCTION: ENGINE 0x10177CF0
// FUNCTION: ENGINE 0x10177D10
// FUNCTION: ENGINE 0x10177D40
// FUNCTION: ENGINE 0x10177D60
// FUNCTION: ENGINE 0x10177D90
// FUNCTION: ENGINE 0x10177DB0
// FUNCTION: ENGINE 0x10177E00
// FUNCTION: ENGINE 0x10177E50
