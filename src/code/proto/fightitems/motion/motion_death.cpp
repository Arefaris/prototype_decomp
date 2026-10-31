// Fight items of the motion group: DeathOnEndTrack, DeathTrack (unit 0x10151930 - 0x101521B0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_death.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gDeathOnEndTrackProperties;  // 0x112543C0

			// FUNCTION: ENGINE 0x10151930
			bool DeathOnEndTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10151950
			bool DeathOnEndTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101519B0
			fight::Property* DeathOnEndTrack::GetProperty(int index)
			{
				return gDeathOnEndTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101519D0
			void DeathOnEndTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDeathOnEndTrackProperties);
			}

			// FUNCTION: ENGINE 0x101519E0
			DeathOnEndTrack::DeathOnEndTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10151A20
			float DeathOnEndTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10151A30
			float DeathOnEndTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10151A40
			DeathOnEndTrack::~DeathOnEndTrack()
			{
			}

			// FUNCTION: ENGINE 0x10151D90
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DeathOnEndTrack::RegisterProperties()
			{
				if (gDeathOnEndTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DeathOnEndTrack>("timeBegin", &DeathOnEndTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DeathOnEndTrack>("timeEnd", &DeathOnEndTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gDeathOnEndTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10151D30
			fight::TrackFactory* CreateDeathOnEndTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DeathOnEndTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10151E70
			void RegisterDeathOnEndTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DeathOnEndTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gDeathTrackProperties;  // 0x112543C4

			// FUNCTION: ENGINE 0x10151970
			bool DeathTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10151A80
			bool DeathTrack::SetDeadTemplate(const fight::Name& newValue)
			{
				deadTemplate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10151990
			bool DeathTrack::SetCopyDrawable(bool newValue)
			{
				copyDrawable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101519A0
			bool DeathTrack::SetGrabberIsOriginator(bool newValue)
			{
				grabberIsOriginator = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10151A50
			fight::Property* DeathTrack::GetProperty(int index)
			{
				return gDeathTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10151A70
			void DeathTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDeathTrackProperties);
			}

			// FUNCTION: ENGINE 0x10151AD0
			DeathTrack::DeathTrack() : timeBegin(0.0f), copyDrawable(true), grabberIsOriginator(false)
			{
			}

			// FUNCTION: ENGINE 0x10151B10
			float DeathTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10151B20
			float DeathTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10151B30
			DeathTrack::~DeathTrack()
			{
			}

			// FUNCTION: ENGINE 0x10151F70
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DeathTrack::RegisterProperties()
			{
				if (gDeathTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DeathTrack>("timeBegin", &DeathTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyName<DeathTrack>("deadTemplate", &DeathTrack::SetDeadTemplate);
					properties[1] = property;
					property = new fight::PropertyBool<DeathTrack>("copyDrawable", &DeathTrack::SetCopyDrawable);
					properties[2] = property;
					property = new fight::PropertyBool<DeathTrack>("grabberIsOriginator", &DeathTrack::SetGrabberIsOriginator);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gDeathTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10151D60
			fight::TrackFactory* CreateDeathTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DeathTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10151EA0
			void RegisterDeathTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DeathTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// ---- actions end
			template class fight::PropertyFloatConstRange<DeathOnEndTrack>;
			template class fight::TrackFactoryTemplate<DeathOnEndTrack>;
			template class fight::TrackFactoryCasterTemplate<DeathOnEndTrack>;
			template class fight::PropertyFloatConstRange<DeathTrack>;
			template class fight::PropertyName<DeathTrack>;
			template class fight::PropertyBool<DeathTrack>;
			template class fight::TrackFactoryTemplate<DeathTrack>;
			template class fight::TrackFactoryCasterTemplate<DeathTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
