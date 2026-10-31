// Fight items of the scenario group: PlayFMVTrack (unit 0x101D9FB0 - 0x101DA5C0; no assert path, the file name is a guess).
#include "code/core/linklist.h"
#include "code/proto/fightitems/scenario/scenario_playfmv.h"
#include <new>

namespace proto
{
	namespace fightitems
	{
		namespace scenario
		{
			fight::Property** gPlayFMVTrackProperties;  // 0x11254DC0

			// FUNCTION: ENGINE 0x101D9FB0
			bool PlayFMVTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101D9FD0
			bool PlayFMVTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DA120
			bool PlayFMVTrack::SetFilename(const char* newValue)
			{
				filename = fight::ReplaceString(filename, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101D9FF0
			bool PlayFMVTrack::SetAudioIndex(int newValue)
			{
				audioIndex = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DA000
			bool PlayFMVTrack::SetStartFrame(float newValue)
			{
				startFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DA020
			bool PlayFMVTrack::SetEndFrame(float newValue)
			{
				endFrame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101DA040
			fight::Property* PlayFMVTrack::GetProperty(int index)
			{
				return gPlayFMVTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101DA060
			void PlayFMVTrack::ClearProperties()
			{
				fight::FreePropertyList(&gPlayFMVTrackProperties);
			}

			// FUNCTION: ENGINE 0x101DA070
			PlayFMVTrack::PlayFMVTrack() : filename(0), endFrame(-1.0f), startFrame(0.0f), timeBegin(0.0f), timeEnd(-1.0f), audioIndex(-1)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101DA0D0
			float PlayFMVTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101DA0E0
			float PlayFMVTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101DA0F0
			PlayFMVTrack::~PlayFMVTrack()
			{
				delete[] filename;
			}

			// FUNCTION: ENGINE 0x101DA320
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void PlayFMVTrack::RegisterProperties()
			{
				if (gPlayFMVTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<PlayFMVTrack>("timeBegin", &PlayFMVTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<PlayFMVTrack>("timeEnd", &PlayFMVTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyString<PlayFMVTrack>("filename", &PlayFMVTrack::SetFilename);
					properties[2] = property;
					property = new fight::PropertyIntConstRange<PlayFMVTrack>("audioIndex", &PlayFMVTrack::SetAudioIndex);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<PlayFMVTrack>("startFrame", &PlayFMVTrack::SetStartFrame);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<PlayFMVTrack>("endFrame", &PlayFMVTrack::SetEndFrame);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gPlayFMVTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101DA2F0
			fight::TrackFactory* CreatePlayFMVTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<PlayFMVTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101DA4F0
			void RegisterPlayFMVTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<PlayFMVTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyFloatConstRange<PlayFMVTrack>;
			template class fight::PropertyString<PlayFMVTrack>;
			template class fight::PropertyIntConstRange<PlayFMVTrack>;
			template class fight::TrackFactoryTemplate<PlayFMVTrack>;
			template class fight::TrackFactoryCasterTemplate<PlayFMVTrack>;

			// FUNCTION: ENGINE 0x101D6750
			PlayFMVAction::PlayFMVAction(PlayFMVTrack* newTrack) : fight::Action(0xE00), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x101D66B0
			PlayFMVAction::~PlayFMVAction()
			{
			}

			// FUNCTION: ENGINE 0x101D67F0
			bool PlayFMVAction::Slot5(int arg, float value)
			{
				if (link.object == 0)
				{
					return false;
				}
				engine::PlayMovie(link.object->filename, false, -1, -1.0f, true, false, 0, false);
				return true;
			}

			// FUNCTION: ENGINE 0x101D65F0
			void PlayFMVAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101D6830
			fight::Action* PlayFMVTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				return new PlayFMVAction(this);
			}
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101D6610
// FUNCTION: ENGINE 0x101D6640
// FUNCTION: ENGINE 0x101D67C0
// FUNCTION: ENGINE 0x101DA150
// FUNCTION: ENGINE 0x101DA180
// FUNCTION: ENGINE 0x101DA190
// FUNCTION: ENGINE 0x101DA1C0
// FUNCTION: ENGINE 0x101DA1F0
// FUNCTION: ENGINE 0x101DA220
// FUNCTION: ENGINE 0x101DA230
// FUNCTION: ENGINE 0x101DA260
// FUNCTION: ENGINE 0x101DA280
// FUNCTION: ENGINE 0x101DA290
// FUNCTION: ENGINE 0x101DA2C0
// FUNCTION: ENGINE 0x101DA2E0
// FUNCTION: ENGINE 0x101DA520
// FUNCTION: ENGINE 0x101DA550
// FUNCTION: ENGINE 0x101DA570
