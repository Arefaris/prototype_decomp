// Fight items of the proplogic group: OnCollisionTrack, WaitOnCollisionTrack (unit 0x1025EFA0 - 0x1025FC60; no assert path, the file name is a guess).
#include "code/proto/fightitems/proplogic/proplogic_oncollision.h"

namespace proto
{
	namespace fightitems
	{
		namespace proplogic
		{
			fight::Property** gOnCollisionTrackProperties;  // 0x11255D38

			// FUNCTION: ENGINE 0x1025EFA0
			bool OnCollisionTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025EFC0
			bool OnCollisionTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025EFE0
			bool OnCollisionTrack::SetCollideWith(int newValue)
			{
				collideWith = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025EFF0
			bool OnCollisionTrack::SetImpulseThreshold(float newValue)
			{
				impulseThreshold = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025F010
			fight::BranchHolder* OnCollisionTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x1025F020
			bool OnCollisionTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025F030
			fight::ConditionList* OnCollisionTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x1025F0B0
			fight::Property* OnCollisionTrack::GetProperty(int index)
			{
				return gOnCollisionTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1025F0D0
			void OnCollisionTrack::ClearProperties()
			{
				fight::FreePropertyList(&gOnCollisionTrackProperties);
			}

			// FUNCTION: ENGINE 0x1025F0E0
			OnCollisionTrack::OnCollisionTrack() : branch(0), impulseThreshold(0.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(0), collideWith(gOnCollisionTrackCollideWithDefault)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1025F150
			float OnCollisionTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1025F160
			float OnCollisionTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1025F170
			OnCollisionTrack::~OnCollisionTrack()
			{
			}

			// FUNCTION: ENGINE 0x1025F730
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void OnCollisionTrack::RegisterProperties()
			{
				if (gOnCollisionTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<OnCollisionTrack>("timeBegin", &OnCollisionTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<OnCollisionTrack>("timeEnd", &OnCollisionTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBitfieldConstList<OnCollisionTrack>("collideWith", motion::gDetectObbCollisionConditionCollideWithTable, motion::gDetectObbCollisionConditionCollideWithCount, &OnCollisionTrack::SetCollideWith);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<OnCollisionTrack>("impulseThreshold", &OnCollisionTrack::SetImpulseThreshold);
					properties[3] = property;
					property = new fight::PropertyBranch<OnCollisionTrack>("branch", &OnCollisionTrack::SetBranch);
					properties[4] = property;
					property = new fight::PropertyIntConstRange<OnCollisionTrack>("priority", &OnCollisionTrack::SetPriority);
					properties[5] = property;
					property = new fight::PropertyConditionGroup<OnCollisionTrack>("conditions", &OnCollisionTrack::SetConditions);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gOnCollisionTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1025F6D0
			fight::TrackFactory* CreateOnCollisionTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<OnCollisionTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1025FAC0
			void RegisterOnCollisionTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<OnCollisionTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gWaitOnCollisionTrackProperties;  // 0x11255D3C

			// FUNCTION: ENGINE 0x1025F040
			bool WaitOnCollisionTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025F060
			bool WaitOnCollisionTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025F080
			bool WaitOnCollisionTrack::SetCollideWith(int newValue)
			{
				collideWith = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025F090
			bool WaitOnCollisionTrack::SetImpulseThreshold(float newValue)
			{
				impulseThreshold = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1025F1A0
			fight::Property* WaitOnCollisionTrack::GetProperty(int index)
			{
				return gWaitOnCollisionTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1025F1C0
			void WaitOnCollisionTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWaitOnCollisionTrackProperties);
			}

			// FUNCTION: ENGINE 0x1025F1D0
			WaitOnCollisionTrack::WaitOnCollisionTrack() : impulseThreshold(0.0f), timeBegin(0.0f), timeEnd(-1.0f), collideWith(gWaitOnCollisionTrackCollideWithDefault)
			{
			}

			// FUNCTION: ENGINE 0x1025F220
			float WaitOnCollisionTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1025F230
			float WaitOnCollisionTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1025F240
			WaitOnCollisionTrack::~WaitOnCollisionTrack()
			{
			}

			// FUNCTION: ENGINE 0x1025F950
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WaitOnCollisionTrack::RegisterProperties()
			{
				if (gWaitOnCollisionTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WaitOnCollisionTrack>("timeBegin", &WaitOnCollisionTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<WaitOnCollisionTrack>("timeEnd", &WaitOnCollisionTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBitfieldConstList<WaitOnCollisionTrack>("collideWith", motion::gDetectObbCollisionConditionCollideWithTable, motion::gDetectObbCollisionConditionCollideWithCount, &WaitOnCollisionTrack::SetCollideWith);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<WaitOnCollisionTrack>("impulseThreshold", &WaitOnCollisionTrack::SetImpulseThreshold);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gWaitOnCollisionTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1025F700
			fight::TrackFactory* CreateWaitOnCollisionTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WaitOnCollisionTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1025FAF0
			void RegisterWaitOnCollisionTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WaitOnCollisionTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyFloatConstRange<OnCollisionTrack>;
			template class fight::PropertyBitfieldConstList<OnCollisionTrack>;
			template class fight::PropertyBranch<OnCollisionTrack>;
			template class fight::PropertyIntConstRange<OnCollisionTrack>;
			template class fight::PropertyConditionGroup<OnCollisionTrack>;
			template class fight::TrackFactoryTemplate<OnCollisionTrack>;
			template class fight::TrackFactoryCasterTemplate<OnCollisionTrack>;
			template class fight::PropertyFloatConstRange<WaitOnCollisionTrack>;
			template class fight::PropertyBitfieldConstList<WaitOnCollisionTrack>;
			template class fight::TrackFactoryTemplate<WaitOnCollisionTrack>;
			template class fight::TrackFactoryCasterTemplate<WaitOnCollisionTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1025F250
// FUNCTION: ENGINE 0x1025F280
// FUNCTION: ENGINE 0x1025F2B0
// FUNCTION: ENGINE 0x1025F2C0
// FUNCTION: ENGINE 0x1025F2F0
// FUNCTION: ENGINE 0x1025F300
// FUNCTION: ENGINE 0x1025F330
// FUNCTION: ENGINE 0x1025F360
// FUNCTION: ENGINE 0x1025F390
// FUNCTION: ENGINE 0x1025F3A0
// FUNCTION: ENGINE 0x1025F3E0
// FUNCTION: ENGINE 0x1025F3F0
// FUNCTION: ENGINE 0x1025F410
// FUNCTION: ENGINE 0x1025F420
// FUNCTION: ENGINE 0x1025F480
// FUNCTION: ENGINE 0x1025F4B0
// FUNCTION: ENGINE 0x1025F4D0
// FUNCTION: ENGINE 0x1025F500
// FUNCTION: ENGINE 0x1025F520
// FUNCTION: ENGINE 0x1025F530
// FUNCTION: ENGINE 0x1025F560
// FUNCTION: ENGINE 0x1025F580
// FUNCTION: ENGINE 0x1025F5B0
// FUNCTION: ENGINE 0x1025F5E0
// FUNCTION: ENGINE 0x1025F5F0
// FUNCTION: ENGINE 0x1025F630
// FUNCTION: ENGINE 0x1025F640
// FUNCTION: ENGINE 0x1025F660
// FUNCTION: ENGINE 0x1025F670
// FUNCTION: ENGINE 0x1025FB20
// FUNCTION: ENGINE 0x1025FB50
// FUNCTION: ENGINE 0x1025FB70
// FUNCTION: ENGINE 0x1025FBA0
// FUNCTION: ENGINE 0x1025FBC0
// FUNCTION: ENGINE 0x1025FC10
