// Fight items of the motion group: UndergroundStateCondition, UndergroundSetTrack, AnchorToGroundTrack, UndergroundTeleportTrack (unit 0x101C3390 - 0x101C42E0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_underground.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gUndergroundStateConditionProperties;  // 0x11254BFC

			// FUNCTION: ENGINE 0x101C3390
			bool UndergroundStateCondition::SetState(int newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C3460
			fight::Property* UndergroundStateCondition::GetProperty(int index)
			{
				return gUndergroundStateConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101C3480
			void UndergroundStateCondition::ClearProperties()
			{
				fight::FreePropertyList(&gUndergroundStateConditionProperties);
			}

			// FUNCTION: ENGINE 0x101C3490
			UndergroundStateCondition::UndergroundStateCondition() : fight::Condition(0), state(0)
			{
			}

			// FUNCTION: ENGINE 0x101C34C0
			UndergroundStateCondition::~UndergroundStateCondition()
			{
			}

			// FUNCTION: ENGINE 0x101C3BF0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void UndergroundStateCondition::RegisterProperties()
			{
				if (gUndergroundStateConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<UndergroundStateCondition>("state", gUndergroundStateConditionStateTable, gUndergroundStateConditionStateCount, &UndergroundStateCondition::SetState);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gUndergroundStateConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C3B30
			fight::ConditionFactory* CreateUndergroundStateConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<UndergroundStateCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C3FA0
			void RegisterUndergroundStateConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<UndergroundStateCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gUndergroundSetTrackProperties;  // 0x11254C00

			// FUNCTION: ENGINE 0x101C33A0
			bool UndergroundSetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C33C0
			bool UndergroundSetTrack::SetUnderground(bool newValue)
			{
				underground = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C33D0
			bool UndergroundSetTrack::SetInstantaneous(bool newValue)
			{
				instantaneous = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C34D0
			fight::Property* UndergroundSetTrack::GetProperty(int index)
			{
				return gUndergroundSetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C34F0
			void UndergroundSetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gUndergroundSetTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C3500
			UndergroundSetTrack::UndergroundSetTrack() : timeBegin(0.0f), instantaneous(false), underground(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101C3540
			float UndergroundSetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C3550
			float UndergroundSetTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101C3560
			UndergroundSetTrack::~UndergroundSetTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C3CA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void UndergroundSetTrack::RegisterProperties()
			{
				if (gUndergroundSetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<UndergroundSetTrack>("timeBegin", &UndergroundSetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyBool<UndergroundSetTrack>("underground", &UndergroundSetTrack::SetUnderground);
					properties[1] = property;
					property = new fight::PropertyBool<UndergroundSetTrack>("instantaneous", &UndergroundSetTrack::SetInstantaneous);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gUndergroundSetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C3B60
			fight::TrackFactory* CreateUndergroundSetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<UndergroundSetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C3FD0
			void RegisterUndergroundSetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<UndergroundSetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gAnchorToGroundTrackProperties;  // 0x11254C04

			// FUNCTION: ENGINE 0x101C33E0
			bool AnchorToGroundTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C3400
			bool AnchorToGroundTrack::SetAnchor(bool newValue)
			{
				anchor = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C3410
			bool AnchorToGroundTrack::SetGroundLevel(bool newValue)
			{
				groundLevel = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C3570
			fight::Property* AnchorToGroundTrack::GetProperty(int index)
			{
				return gAnchorToGroundTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C3590
			void AnchorToGroundTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAnchorToGroundTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C35A0
			AnchorToGroundTrack::AnchorToGroundTrack() : timeBegin(0.0f), anchor(true), groundLevel(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101C35E0
			float AnchorToGroundTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C35F0
			float AnchorToGroundTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101C3600
			AnchorToGroundTrack::~AnchorToGroundTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C3DB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AnchorToGroundTrack::RegisterProperties()
			{
				if (gAnchorToGroundTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AnchorToGroundTrack>("timeBegin", &AnchorToGroundTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyBool<AnchorToGroundTrack>("anchor", &AnchorToGroundTrack::SetAnchor);
					properties[1] = property;
					property = new fight::PropertyBool<AnchorToGroundTrack>("groundLevel", &AnchorToGroundTrack::SetGroundLevel);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gAnchorToGroundTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C3B90
			fight::TrackFactory* CreateAnchorToGroundTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AnchorToGroundTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C4000
			void RegisterAnchorToGroundTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AnchorToGroundTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gUndergroundTeleportTrackProperties;  // 0x11254C08

			// FUNCTION: ENGINE 0x101C3420
			bool UndergroundTeleportTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C3440
			bool UndergroundTeleportTrack::SetDistanceUnderground(float newValue)
			{
				distanceUnderground = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C3610
			fight::Property* UndergroundTeleportTrack::GetProperty(int index)
			{
				return gUndergroundTeleportTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C3630
			void UndergroundTeleportTrack::ClearProperties()
			{
				fight::FreePropertyList(&gUndergroundTeleportTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C3640
			UndergroundTeleportTrack::UndergroundTeleportTrack() : distanceUnderground(5.0f), timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101C3680
			float UndergroundTeleportTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C3690
			float UndergroundTeleportTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101C36A0
			UndergroundTeleportTrack::~UndergroundTeleportTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C3EC0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void UndergroundTeleportTrack::RegisterProperties()
			{
				if (gUndergroundTeleportTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<UndergroundTeleportTrack>("timeBegin", &UndergroundTeleportTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<UndergroundTeleportTrack>("distanceUnderground", &UndergroundTeleportTrack::SetDistanceUnderground);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gUndergroundTeleportTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C3BC0
			fight::TrackFactory* CreateUndergroundTeleportTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<UndergroundTeleportTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C4030
			void RegisterUndergroundTeleportTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<UndergroundTeleportTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<UndergroundStateCondition>;
			template class fight::ConditionFactoryTemplate<UndergroundStateCondition>;
			template class fight::ConditionFactoryCasterTemplate<UndergroundStateCondition>;
			template class fight::PropertyFloatConstRange<UndergroundSetTrack>;
			template class fight::PropertyBool<UndergroundSetTrack>;
			template class fight::TrackFactoryTemplate<UndergroundSetTrack>;
			template class fight::TrackFactoryCasterTemplate<UndergroundSetTrack>;
			template class fight::PropertyFloatConstRange<AnchorToGroundTrack>;
			template class fight::PropertyBool<AnchorToGroundTrack>;
			template class fight::TrackFactoryTemplate<AnchorToGroundTrack>;
			template class fight::TrackFactoryCasterTemplate<AnchorToGroundTrack>;
			template class fight::PropertyFloatConstRange<UndergroundTeleportTrack>;
			template class fight::TrackFactoryTemplate<UndergroundTeleportTrack>;
			template class fight::TrackFactoryCasterTemplate<UndergroundTeleportTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101C36B0
// FUNCTION: ENGINE 0x101C36E0
// FUNCTION: ENGINE 0x101C3710
// FUNCTION: ENGINE 0x101C3740
// FUNCTION: ENGINE 0x101C3770
// FUNCTION: ENGINE 0x101C3780
// FUNCTION: ENGINE 0x101C37B0
// FUNCTION: ENGINE 0x101C37C0
// FUNCTION: ENGINE 0x101C37F0
// FUNCTION: ENGINE 0x101C3800
// FUNCTION: ENGINE 0x101C3830
// FUNCTION: ENGINE 0x101C3840
// FUNCTION: ENGINE 0x101C3870
// FUNCTION: ENGINE 0x101C38B0
// FUNCTION: ENGINE 0x101C38C0
// FUNCTION: ENGINE 0x101C38F0
// FUNCTION: ENGINE 0x101C3910
// FUNCTION: ENGINE 0x101C3920
// FUNCTION: ENGINE 0x101C3950
// FUNCTION: ENGINE 0x101C3980
// FUNCTION: ENGINE 0x101C3990
// FUNCTION: ENGINE 0x101C39C0
// FUNCTION: ENGINE 0x101C39E0
// FUNCTION: ENGINE 0x101C39F0
// FUNCTION: ENGINE 0x101C3A20
// FUNCTION: ENGINE 0x101C3A50
// FUNCTION: ENGINE 0x101C3A60
// FUNCTION: ENGINE 0x101C3A90
// FUNCTION: ENGINE 0x101C3AB0
// FUNCTION: ENGINE 0x101C3AC0
// FUNCTION: ENGINE 0x101C3AF0
// FUNCTION: ENGINE 0x101C3B20
// FUNCTION: ENGINE 0x101C4060
// FUNCTION: ENGINE 0x101C4090
// FUNCTION: ENGINE 0x101C40B0
// FUNCTION: ENGINE 0x101C40E0
// FUNCTION: ENGINE 0x101C4100
// FUNCTION: ENGINE 0x101C4130
// FUNCTION: ENGINE 0x101C4150
// FUNCTION: ENGINE 0x101C4180
// FUNCTION: ENGINE 0x101C41A0
// FUNCTION: ENGINE 0x101C41F0
// FUNCTION: ENGINE 0x101C4240
// FUNCTION: ENGINE 0x101C4290
