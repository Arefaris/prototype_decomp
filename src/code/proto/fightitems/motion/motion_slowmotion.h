// Fight items of the motion group: SlowMotionTrack (unit 0x101B3980 - 0x101B3FC0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_SLOWMOTION_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_SLOWMOTION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::SlowMotionTrack (16 vftable slots, 0x2C bytes)
			class SlowMotionTrack : public fight::Track
			{
			public:
				// 0x101B3A90
				SlowMotionTrack();
				virtual ~SlowMotionTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101165E0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetSimulationRate(float newValue);
				bool SetFadeInTime(float newValue);
				bool SetSimulationDuration(float newValue);
				bool SetFadeOutTime(float newValue);
				bool SetRealTime(bool newValue);
				bool SetAbortOnEnd(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float fadeInTime;  // +0x10
					float fadeOutTime;  // +0x14
					float simulationDuration;  // +0x18
					float simulationRate;  // +0x1C
					float timeBegin;  // +0x20
					float timeEnd;  // +0x24
					bool abortOnEnd;  // +0x28
					bool realTime;  // +0x29
					unsigned char unknown2A[0x2];
			};

			extern fight::Property** gSlowMotionTrackProperties;
			fight::TrackFactory* CreateSlowMotionTrackFactory(const char* name);
			void RegisterSlowMotionTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
