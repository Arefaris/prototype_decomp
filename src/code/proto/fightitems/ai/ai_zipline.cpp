// Fight items of the ai group: ZiplineLandTrack, ZiplineTakeOffTrack (unit 0x10256A40 - 0x102573D0; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_zipline.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gZiplineLandTrackProperties;  // 0x11255C60

			// FUNCTION: ENGINE 0x10256A40
			bool ZiplineLandTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10256A60
			bool ZiplineLandTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10256A80
			bool ZiplineLandTrack::SetSpeed(const math::Vector& newValue)
			{
				speed.x = newValue.x;
				speed.y = newValue.y;
				speed.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10256B40
			fight::Property* ZiplineLandTrack::GetProperty(int index)
			{
				return gZiplineLandTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10256B60
			void ZiplineLandTrack::ClearProperties()
			{
				fight::FreePropertyList(&gZiplineLandTrackProperties);
			}

			// FUNCTION: ENGINE 0x10256B70
			ZiplineLandTrack::ZiplineLandTrack() : speed(0.0f, 0.0f, 0.0f), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10256BC0
			float ZiplineLandTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10256BD0
			float ZiplineLandTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10256BE0
			ZiplineLandTrack::~ZiplineLandTrack()
			{
			}

			// FUNCTION: ENGINE 0x10256F90
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ZiplineLandTrack::RegisterProperties()
			{
				if (gZiplineLandTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ZiplineLandTrack>("timeBegin", &ZiplineLandTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ZiplineLandTrack>("timeEnd", &ZiplineLandTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyVector<ZiplineLandTrack>("speed", &ZiplineLandTrack::SetSpeed);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gZiplineLandTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10256F30
			fight::TrackFactory* CreateZiplineLandTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ZiplineLandTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10257230
			void RegisterZiplineLandTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ZiplineLandTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gZiplineTakeOffTrackProperties;  // 0x11255C64

			// FUNCTION: ENGINE 0x10256AA0
			bool ZiplineTakeOffTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10256AC0
			bool ZiplineTakeOffTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10256AE0
			bool ZiplineTakeOffTrack::SetZiplineSpeed(const math::Vector& newValue)
			{
				ziplineSpeed.x = newValue.x;
				ziplineSpeed.y = newValue.y;
				ziplineSpeed.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10256B00
			bool ZiplineTakeOffTrack::SetZiplineTime(float newValue)
			{
				ziplineTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10256B20
			bool ZiplineTakeOffTrack::SetCharacterSpeed(const math::Vector& newValue)
			{
				characterSpeed.x = newValue.x;
				characterSpeed.y = newValue.y;
				characterSpeed.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x10256BF0
			fight::Property* ZiplineTakeOffTrack::GetProperty(int index)
			{
				return gZiplineTakeOffTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10256C10
			void ZiplineTakeOffTrack::ClearProperties()
			{
				fight::FreePropertyList(&gZiplineTakeOffTrackProperties);
			}

			// FUNCTION: ENGINE 0x10256C20
			ZiplineTakeOffTrack::ZiplineTakeOffTrack() : characterSpeed(0.0f, 0.0f, 0.0f), ziplineSpeed(0.0f, 0.0f, 0.0f), timeBegin(0.0f), timeEnd(-1.0f), ziplineTime(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10256C80
			float ZiplineTakeOffTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10256C90
			float ZiplineTakeOffTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10256CA0
			ZiplineTakeOffTrack::~ZiplineTakeOffTrack()
			{
			}

			// FUNCTION: ENGINE 0x102570A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ZiplineTakeOffTrack::RegisterProperties()
			{
				if (gZiplineTakeOffTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ZiplineTakeOffTrack>("timeBegin", &ZiplineTakeOffTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ZiplineTakeOffTrack>("timeEnd", &ZiplineTakeOffTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyVector<ZiplineTakeOffTrack>("ziplineSpeed", &ZiplineTakeOffTrack::SetZiplineSpeed);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<ZiplineTakeOffTrack>("ziplineTime", &ZiplineTakeOffTrack::SetZiplineTime);
					properties[3] = property;
					property = new fight::PropertyVector<ZiplineTakeOffTrack>("characterSpeed", &ZiplineTakeOffTrack::SetCharacterSpeed);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gZiplineTakeOffTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10256F60
			fight::TrackFactory* CreateZiplineTakeOffTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ZiplineTakeOffTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10257260
			void RegisterZiplineTakeOffTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ZiplineTakeOffTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<ZiplineLandTrack>;
			template class fight::PropertyVector<ZiplineLandTrack>;
			template class fight::TrackFactoryTemplate<ZiplineLandTrack>;
			template class fight::TrackFactoryCasterTemplate<ZiplineLandTrack>;
			template class fight::PropertyFloatConstRange<ZiplineTakeOffTrack>;
			template class fight::PropertyVector<ZiplineTakeOffTrack>;
			template class fight::TrackFactoryTemplate<ZiplineTakeOffTrack>;
			template class fight::TrackFactoryCasterTemplate<ZiplineTakeOffTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10256CB0
// FUNCTION: ENGINE 0x10256CE0
// FUNCTION: ENGINE 0x10256D10
// FUNCTION: ENGINE 0x10256D20
// FUNCTION: ENGINE 0x10256D50
// FUNCTION: ENGINE 0x10256D60
// FUNCTION: ENGINE 0x10256D90
// FUNCTION: ENGINE 0x10256DC0
// FUNCTION: ENGINE 0x10256DF0
// FUNCTION: ENGINE 0x10256E00
// FUNCTION: ENGINE 0x10256E30
// FUNCTION: ENGINE 0x10256E50
// FUNCTION: ENGINE 0x10256E60
// FUNCTION: ENGINE 0x10256E90
// FUNCTION: ENGINE 0x10256EC0
// FUNCTION: ENGINE 0x10256ED0
// FUNCTION: ENGINE 0x10256F00
// FUNCTION: ENGINE 0x10256F20
// FUNCTION: ENGINE 0x10257290
// FUNCTION: ENGINE 0x102572C0
// FUNCTION: ENGINE 0x102572E0
// FUNCTION: ENGINE 0x10257310
// FUNCTION: ENGINE 0x10257330
// FUNCTION: ENGINE 0x10257380
