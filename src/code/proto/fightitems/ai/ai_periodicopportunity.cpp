// Fight items of the ai group: PeriodicOpportunityTrack, DelayedSequenceTrack (unit 0x10244160 - 0x10244F30; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_periodicopportunity.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gPeriodicOpportunityTrackProperties;  // 0x11255B30

			// FUNCTION: ENGINE 0x10244160
			bool PeriodicOpportunityTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10244180
			bool PeriodicOpportunityTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102441A0
			bool PeriodicOpportunityTrack::SetTimeHook(float newValue)
			{
				timeHook = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102441C0
			bool PeriodicOpportunityTrack::SetPeriod(float newValue)
			{
				period = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102441E0
			fight::BranchHolder* PeriodicOpportunityTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x102441F0
			bool PeriodicOpportunityTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10244200
			fight::ConditionList* PeriodicOpportunityTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x102442D0
			fight::Property* PeriodicOpportunityTrack::GetProperty(int index)
			{
				return gPeriodicOpportunityTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x102442F0
			void PeriodicOpportunityTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPeriodicOpportunityTrackProperties);
			}

			// FUNCTION: ENGINE 0x10244300
			PeriodicOpportunityTrack::PeriodicOpportunityTrack() : branch(0), period(0.0f), timeBegin(0.0f), timeEnd(-1.0f), timeHook(0.0f), priority(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10244370
			float PeriodicOpportunityTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10244380
			float PeriodicOpportunityTrack::Slot10() const
			{
				return -1.0f;
			}

			// FUNCTION: ENGINE 0x10244390
			PeriodicOpportunityTrack::~PeriodicOpportunityTrack()
			{
			}

			// FUNCTION: ENGINE 0x10244930
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PeriodicOpportunityTrack::RegisterProperties()
			{
				if (gPeriodicOpportunityTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PeriodicOpportunityTrack>("timeBegin", &PeriodicOpportunityTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PeriodicOpportunityTrack>("timeEnd", &PeriodicOpportunityTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<PeriodicOpportunityTrack>("timeHook", &PeriodicOpportunityTrack::SetTimeHook);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<PeriodicOpportunityTrack>("period", &PeriodicOpportunityTrack::SetPeriod);
					properties[3] = property;
					property = new fight::PropertyBranch<PeriodicOpportunityTrack>("branch", &PeriodicOpportunityTrack::SetBranch);
					properties[4] = property;
					property = new fight::PropertyIntConstRange<PeriodicOpportunityTrack>("priority", &PeriodicOpportunityTrack::SetPriority);
					properties[5] = property;
					property = new fight::PropertyConditionGroup<PeriodicOpportunityTrack>("conditions", &PeriodicOpportunityTrack::SetConditions);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gPeriodicOpportunityTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x102448D0
			fight::TrackFactory* CreatePeriodicOpportunityTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PeriodicOpportunityTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10244D90
			void RegisterPeriodicOpportunityTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PeriodicOpportunityTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gDelayedSequenceTrackProperties;  // 0x11255B34

			// FUNCTION: ENGINE 0x10244210
			bool DelayedSequenceTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10244230
			bool DelayedSequenceTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10244250
			bool DelayedSequenceTrack::SetMinDelay(float newValue)
			{
				minDelay = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10244270
			bool DelayedSequenceTrack::SetMaxDelay(float newValue)
			{
				maxDelay = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10244290
			bool DelayedSequenceTrack::SetForceSequenceWhenNotBusy(bool newValue)
			{
				forceSequenceWhenNotBusy = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102442A0
			fight::BranchHolder* DelayedSequenceTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x102442B0
			bool DelayedSequenceTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102442C0
			fight::ConditionList* DelayedSequenceTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x102443C0
			fight::Property* DelayedSequenceTrack::GetProperty(int index)
			{
				return gDelayedSequenceTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x102443E0
			void DelayedSequenceTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDelayedSequenceTrackProperties);
			}

			// FUNCTION: ENGINE 0x102443F0
			DelayedSequenceTrack::DelayedSequenceTrack() : branch(0), maxDelay(0.0f), minDelay(0.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(0), forceSequenceWhenNotBusy(false)
			{
			}

			// FUNCTION: ENGINE 0x10244460
			float DelayedSequenceTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10244470
			float DelayedSequenceTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10244480
			DelayedSequenceTrack::~DelayedSequenceTrack()
			{
			}

			// FUNCTION: ENGINE 0x10244B40
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DelayedSequenceTrack::RegisterProperties()
			{
				if (gDelayedSequenceTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DelayedSequenceTrack>("timeBegin", &DelayedSequenceTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DelayedSequenceTrack>("timeEnd", &DelayedSequenceTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DelayedSequenceTrack>("minDelay", &DelayedSequenceTrack::SetMinDelay);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<DelayedSequenceTrack>("maxDelay", &DelayedSequenceTrack::SetMaxDelay);
					properties[3] = property;
					property = new fight::PropertyBool<DelayedSequenceTrack>("forceSequenceWhenNotBusy", &DelayedSequenceTrack::SetForceSequenceWhenNotBusy);
					properties[4] = property;
					property = new fight::PropertyBranch<DelayedSequenceTrack>("branch", &DelayedSequenceTrack::SetBranch);
					properties[5] = property;
					property = new fight::PropertyIntConstRange<DelayedSequenceTrack>("priority", &DelayedSequenceTrack::SetPriority);
					properties[6] = property;
					property = new fight::PropertyConditionGroup<DelayedSequenceTrack>("conditions", &DelayedSequenceTrack::SetConditions);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gDelayedSequenceTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10244900
			fight::TrackFactory* CreateDelayedSequenceTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DelayedSequenceTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10244DC0
			void RegisterDelayedSequenceTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DelayedSequenceTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyFloatConstRange<PeriodicOpportunityTrack>;
			template class fight::PropertyBranch<PeriodicOpportunityTrack>;
			template class fight::PropertyIntConstRange<PeriodicOpportunityTrack>;
			template class fight::PropertyConditionGroup<PeriodicOpportunityTrack>;
			template class fight::TrackFactoryTemplate<PeriodicOpportunityTrack>;
			template class fight::TrackFactoryCasterTemplate<PeriodicOpportunityTrack>;
			template class fight::PropertyFloatConstRange<DelayedSequenceTrack>;
			template class fight::PropertyBool<DelayedSequenceTrack>;
			template class fight::PropertyBranch<DelayedSequenceTrack>;
			template class fight::PropertyIntConstRange<DelayedSequenceTrack>;
			template class fight::PropertyConditionGroup<DelayedSequenceTrack>;
			template class fight::TrackFactoryTemplate<DelayedSequenceTrack>;
			template class fight::TrackFactoryCasterTemplate<DelayedSequenceTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102444B0
// FUNCTION: ENGINE 0x102444E0
// FUNCTION: ENGINE 0x10244510
// FUNCTION: ENGINE 0x10244520
// FUNCTION: ENGINE 0x10244550
// FUNCTION: ENGINE 0x10244560
// FUNCTION: ENGINE 0x10244590
// FUNCTION: ENGINE 0x102445C0
// FUNCTION: ENGINE 0x102445F0
// FUNCTION: ENGINE 0x10244600
// FUNCTION: ENGINE 0x10244630
// FUNCTION: ENGINE 0x10244650
// FUNCTION: ENGINE 0x10244680
// FUNCTION: ENGINE 0x102446A0
// FUNCTION: ENGINE 0x102446B0
// FUNCTION: ENGINE 0x102446E0
// FUNCTION: ENGINE 0x10244700
// FUNCTION: ENGINE 0x10244730
// FUNCTION: ENGINE 0x10244760
// FUNCTION: ENGINE 0x10244770
// FUNCTION: ENGINE 0x102447A0
// FUNCTION: ENGINE 0x102447C0
// FUNCTION: ENGINE 0x102447D0
// FUNCTION: ENGINE 0x10244800
// FUNCTION: ENGINE 0x10244820
// FUNCTION: ENGINE 0x10244850
// FUNCTION: ENGINE 0x10244870
// FUNCTION: ENGINE 0x10244880
// FUNCTION: ENGINE 0x102448B0
// FUNCTION: ENGINE 0x10244DF0
// FUNCTION: ENGINE 0x10244E20
// FUNCTION: ENGINE 0x10244E40
// FUNCTION: ENGINE 0x10244E70
// FUNCTION: ENGINE 0x10244E90
// FUNCTION: ENGINE 0x10244EE0
