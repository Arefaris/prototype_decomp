// Fight items of the motion group: SlowMotionTrack (unit 0x101B3980 - 0x101B3FC0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_SLOWMOTION_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_SLOWMOTION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

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

				// Accessors the engine keeps as unreferenced copies in the action half (names guessed)
				float GetSimulationRate() const;
				float GetFadeInTime() const;
				float GetSimulationDuration() const;
				float GetFadeOutTime() const;
				bool GetRealTime() const;
				bool GetAbortOnEnd() const;

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

			// ---- actions begin
			// RTTI: proto::fightitems::motion::SlowMotionAction (9 vftable slots, 0x38 bytes): slows the simulation down for the length of the track
			class SlowMotionAction : public fight::Action
			{
			public:
				// 0x10116340
				SlowMotionAction(SlowMotionTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101162A0
				virtual ~SlowMotionAction();

				// vftable slot 5 (0x10116430, the engine's)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101161A0, the engine's)
				virtual void Slot6();
				// vftable slot 7 (0x101164F0, the engine's)
				virtual bool Slot7(int arg, float value);

				core::Link<SlowMotionTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				int request;  // +0x2C
				float elapsed;  // +0x30
				float fadeInTime;  // +0x34
			};

			// ---- actions end
		}
	}
}

#endif
