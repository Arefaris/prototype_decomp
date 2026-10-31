// Fight items of the motion group: RadioHQTrack, ScenarioEventRadioAttemptTrack (unit 0x101A0B00 - 0x101A1160; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_RADIOHQ_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_RADIOHQ_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::RadioHQTrack (16 vftable slots, 0x14 bytes)
			class RadioHQTrack : public fight::Track
			{
			public:
				// 0x101A0B70
				RadioHQTrack();
				virtual ~RadioHQTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101060D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gRadioHQTrackProperties;
			fight::TrackFactory* CreateRadioHQTrackFactory(const char* name);
			void RegisterRadioHQTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ScenarioEventRadioAttemptTrack (16 vftable slots, 0x14 bytes)
			class ScenarioEventRadioAttemptTrack : public fight::Track
			{
			public:
				// 0x101A0C00
				ScenarioEventRadioAttemptTrack();
				virtual ~ScenarioEventRadioAttemptTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10106120, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gScenarioEventRadioAttemptTrackProperties;
			fight::TrackFactory* CreateScenarioEventRadioAttemptTrackFactory(const char* name);
			void RegisterScenarioEventRadioAttemptTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
