// Fight items of the scenario group: PlayFMVTrack (unit 0x101D9FB0 - 0x101DA5C0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_SCENARIO_SCENARIO_PLAYFMV_H
#define PROTO_FIGHTITEMS_SCENARIO_SCENARIO_PLAYFMV_H

#include "code/core/linklist.h"
#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/scenario/scenariodata.h"

namespace engine
{
	// 0x1082F990 (fmvplayer.cpp declares the fourth argument as an int; the caller passes a float)
	void PlayMovie(const char* path, bool unknown12, int id, float unused, bool unknown13, bool unknown11, int unknown14, bool unknown15);
}

namespace proto
{
	namespace fightitems
	{
		namespace scenario
		{
			// RTTI: proto::fightitems::scenario::PlayFMVTrack (16 vftable slots, 0x28 bytes)
			class PlayFMVTrack : public fight::Track
			{
			public:
				// 0x101DA070
				PlayFMVTrack();
				virtual ~PlayFMVTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101D6830, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetFilename(const char* newValue);
				bool SetAudioIndex(int newValue);
				bool SetStartFrame(float newValue);
				bool SetEndFrame(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					char* filename;  // +0x10
					float endFrame;  // +0x14
					float startFrame;  // +0x18
					float timeBegin;  // +0x1C
					float timeEnd;  // +0x20
					int audioIndex;  // +0x24
			};

			extern fight::Property** gPlayFMVTrackProperties;
			fight::TrackFactory* CreatePlayFMVTrackFactory(const char* name);
			void RegisterPlayFMVTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::scenario::PlayFMVAction (9 vftable slots, size 0x2C): plays the track's movie
			class PlayFMVAction : public fight::Action
			{
			public:
				// 0x101D6750 (the destructor is 0x101D66B0, the deleting destructor 0x101D67C0)
				PlayFMVAction(PlayFMVTrack* newTrack);
				virtual ~PlayFMVAction();

				// vftable slot 5 (0x101D67F0) and slot 6 (0x101D65F0)
				virtual bool Slot5(int arg, float value);
				virtual void Slot6();

				unsigned int unknown1C;
				core::Link<PlayFMVTrack> link;  // +0x20
			};
		}
	}
}

#endif
