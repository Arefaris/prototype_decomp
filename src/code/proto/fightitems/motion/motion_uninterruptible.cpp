// Fight items of the motion group: InvulnerableTrack, SpecificUninterruptibleTrack, UninterruptibleTrack (unit 0x101C42E0 - 0x101C4FB0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_uninterruptible.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gInvulnerableTrackProperties;  // 0x11254C10

			// FUNCTION: ENGINE 0x101C42E0
			bool InvulnerableTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C4300
			bool InvulnerableTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C43E0
			fight::Property* InvulnerableTrack::GetProperty(int index)
			{
				return gInvulnerableTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C4400
			void InvulnerableTrack::ClearProperties()
			{
				fight::FreePropertyList(&gInvulnerableTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C4410
			InvulnerableTrack::InvulnerableTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101C4450
			float InvulnerableTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C4460
			float InvulnerableTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101C4470
			InvulnerableTrack::~InvulnerableTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C49C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void InvulnerableTrack::RegisterProperties()
			{
				if (gInvulnerableTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<InvulnerableTrack>("timeBegin", &InvulnerableTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<InvulnerableTrack>("timeEnd", &InvulnerableTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gInvulnerableTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C4930
			fight::TrackFactory* CreateInvulnerableTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<InvulnerableTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C4D40
			void RegisterInvulnerableTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<InvulnerableTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSpecificUninterruptibleTrackProperties;  // 0x11254C14

			// FUNCTION: ENGINE 0x101C4320
			bool SpecificUninterruptibleTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C4340
			bool SpecificUninterruptibleTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C4360
			bool SpecificUninterruptibleTrack::SetIgnoreGrabs(bool newValue)
			{
				ignoreGrabs = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C4480
			fight::Property* SpecificUninterruptibleTrack::GetProperty(int index)
			{
				return gSpecificUninterruptibleTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C44A0
			void SpecificUninterruptibleTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSpecificUninterruptibleTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C44B0
			SpecificUninterruptibleTrack::SpecificUninterruptibleTrack() : timeBegin(0.0f), timeEnd(-1.0f), ignoreGrabs(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101C44F0
			float SpecificUninterruptibleTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C4500
			float SpecificUninterruptibleTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101C4510
			SpecificUninterruptibleTrack::~SpecificUninterruptibleTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C4AA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SpecificUninterruptibleTrack::RegisterProperties()
			{
				if (gSpecificUninterruptibleTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SpecificUninterruptibleTrack>("timeBegin", &SpecificUninterruptibleTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SpecificUninterruptibleTrack>("timeEnd", &SpecificUninterruptibleTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<SpecificUninterruptibleTrack>("ignoreGrabs", &SpecificUninterruptibleTrack::SetIgnoreGrabs);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gSpecificUninterruptibleTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C4960
			fight::TrackFactory* CreateSpecificUninterruptibleTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SpecificUninterruptibleTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C4D70
			void RegisterSpecificUninterruptibleTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SpecificUninterruptibleTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gUninterruptibleTrackProperties;  // 0x11254C18

			// FUNCTION: ENGINE 0x101C4370
			bool UninterruptibleTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C4390
			bool UninterruptibleTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C43B0
			bool UninterruptibleTrack::SetIgnoreHits(bool newValue)
			{
				ignoreHits = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C43C0
			bool UninterruptibleTrack::SetIgnoreGrabs(bool newValue)
			{
				ignoreGrabs = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C43D0
			bool UninterruptibleTrack::SetAllowDevastatorGrabs(bool newValue)
			{
				allowDevastatorGrabs = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C4520
			fight::Property* UninterruptibleTrack::GetProperty(int index)
			{
				return gUninterruptibleTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C4540
			void UninterruptibleTrack::ClearProperties()
			{
				fight::FreePropertyList(&gUninterruptibleTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C4550
			UninterruptibleTrack::UninterruptibleTrack() : timeBegin(0.0f), timeEnd(-1.0f), allowDevastatorGrabs(false), ignoreGrabs(true), ignoreHits(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101C45A0
			float UninterruptibleTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C45B0
			float UninterruptibleTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101C45C0
			UninterruptibleTrack::~UninterruptibleTrack()
			{
			}

			// FUNCTION: ENGINE 0x101C4BB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void UninterruptibleTrack::RegisterProperties()
			{
				if (gUninterruptibleTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<UninterruptibleTrack>("timeBegin", &UninterruptibleTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<UninterruptibleTrack>("timeEnd", &UninterruptibleTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<UninterruptibleTrack>("ignoreHits", &UninterruptibleTrack::SetIgnoreHits);
					properties[2] = property;
					property = new fight::PropertyBool<UninterruptibleTrack>("ignoreGrabs", &UninterruptibleTrack::SetIgnoreGrabs);
					properties[3] = property;
					property = new fight::PropertyBool<UninterruptibleTrack>("allowDevastatorGrabs", &UninterruptibleTrack::SetAllowDevastatorGrabs);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gUninterruptibleTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C4990
			fight::TrackFactory* CreateUninterruptibleTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<UninterruptibleTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101C4DA0
			void RegisterUninterruptibleTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<UninterruptibleTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<InvulnerableTrack>;
			template class fight::TrackFactoryTemplate<InvulnerableTrack>;
			template class fight::TrackFactoryCasterTemplate<InvulnerableTrack>;
			template class fight::PropertyFloatConstRange<SpecificUninterruptibleTrack>;
			template class fight::PropertyBool<SpecificUninterruptibleTrack>;
			template class fight::TrackFactoryTemplate<SpecificUninterruptibleTrack>;
			template class fight::TrackFactoryCasterTemplate<SpecificUninterruptibleTrack>;
			template class fight::PropertyFloatConstRange<UninterruptibleTrack>;
			template class fight::PropertyBool<UninterruptibleTrack>;
			template class fight::TrackFactoryTemplate<UninterruptibleTrack>;
			template class fight::TrackFactoryCasterTemplate<UninterruptibleTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101C45D0
// FUNCTION: ENGINE 0x101C4600
// FUNCTION: ENGINE 0x101C4630
// FUNCTION: ENGINE 0x101C4660
// FUNCTION: ENGINE 0x101C4670
// FUNCTION: ENGINE 0x101C46A0
// FUNCTION: ENGINE 0x101C46B0
// FUNCTION: ENGINE 0x101C46E0
// FUNCTION: ENGINE 0x101C46F0
// FUNCTION: ENGINE 0x101C4720
// FUNCTION: ENGINE 0x101C4750
// FUNCTION: ENGINE 0x101C4780
// FUNCTION: ENGINE 0x101C4790
// FUNCTION: ENGINE 0x101C47C0
// FUNCTION: ENGINE 0x101C47F0
// FUNCTION: ENGINE 0x101C4800
// FUNCTION: ENGINE 0x101C4830
// FUNCTION: ENGINE 0x101C4850
// FUNCTION: ENGINE 0x101C4860
// FUNCTION: ENGINE 0x101C4890
// FUNCTION: ENGINE 0x101C48C0
// FUNCTION: ENGINE 0x101C48D0
// FUNCTION: ENGINE 0x101C4900
// FUNCTION: ENGINE 0x101C4920
// FUNCTION: ENGINE 0x101C4DD0
// FUNCTION: ENGINE 0x101C4E00
// FUNCTION: ENGINE 0x101C4E20
// FUNCTION: ENGINE 0x101C4E50
// FUNCTION: ENGINE 0x101C4E70
// FUNCTION: ENGINE 0x101C4EA0
// FUNCTION: ENGINE 0x101C4EC0
// FUNCTION: ENGINE 0x101C4F10
// FUNCTION: ENGINE 0x101C4F60
