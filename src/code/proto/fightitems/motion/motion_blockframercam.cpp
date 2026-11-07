// Fight items of the motion group: BlockFramerCamTrack (unit 0x1035D8B0 - 0x1035DC50; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_blockframercam.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gBlockFramerCamTrackProperties;  // 0x11263880

			// FUNCTION: ENGINE 0x1035D8B0
			bool BlockFramerCamTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035D8D0
			bool BlockFramerCamTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1035D8F0
			fight::Property* BlockFramerCamTrack::GetProperty(int index)
			{
				return gBlockFramerCamTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1035D910
			void BlockFramerCamTrack::ClearProperties()
			{
				fight::FreePropertyList(&gBlockFramerCamTrackProperties);
			}

			// FUNCTION: ENGINE 0x1035D920
			BlockFramerCamTrack::BlockFramerCamTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1035D960
			float BlockFramerCamTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1035D970
			float BlockFramerCamTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1035D980
			BlockFramerCamTrack::~BlockFramerCamTrack()
			{
			}

			// FUNCTION: ENGINE 0x1035DAA0
			// NONMATCHING: shrink-wrap (the engine saves esi in the entry block before the guard's branch, the compiler places the push after it)
#ifdef NONMATCHING
			void BlockFramerCamTrack::RegisterProperties()
			{
				if (gBlockFramerCamTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<BlockFramerCamTrack>("timeBegin", &BlockFramerCamTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<BlockFramerCamTrack>("timeEnd", &BlockFramerCamTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gBlockFramerCamTrackProperties);
				}
			}
#endif

			// FUNCTION: ENGINE 0x1035DA70
			fight::TrackFactory* CreateBlockFramerCamTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<BlockFramerCamTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1035DB80
			void RegisterBlockFramerCamTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<BlockFramerCamTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<BlockFramerCamTrack>;
			template class fight::TrackFactoryTemplate<BlockFramerCamTrack>;
			template class fight::TrackFactoryCasterTemplate<BlockFramerCamTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1035D990
// FUNCTION: ENGINE 0x1035D9C0
// FUNCTION: ENGINE 0x1035D9D0
// FUNCTION: ENGINE 0x1035DA00
// FUNCTION: ENGINE 0x1035DA30
// FUNCTION: ENGINE 0x1035DA60
// FUNCTION: ENGINE 0x1035DBB0
// FUNCTION: ENGINE 0x1035DBE0
// FUNCTION: ENGINE 0x1035DC00
