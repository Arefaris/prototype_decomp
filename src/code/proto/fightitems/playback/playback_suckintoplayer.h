// Fight items of the playback group: SuckIntoPlayerTrack (unit 0x102573D0 - 0x1025BC30; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_PLAYBACK_PLAYBACK_SUCKINTOPLAYER_H
#define PROTO_FIGHTITEMS_PLAYBACK_PLAYBACK_SUCKINTOPLAYER_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/scenario/scenariodata.h"
#include "code/proto/fightitems/ai/aidata.h"
#include "code/proto/fightitems/playback/playbackdata.h"

namespace proto
{
	namespace fightitems
	{
		namespace playback
		{
			// RTTI: proto::fightitems::playback::SuckIntoPlayerTrack (16 vftable slots, 0x60 bytes)
			class SuckIntoPlayerTrack : public fight::Track
			{
			public:
				// 0x1025B610
				SuckIntoPlayerTrack();
				virtual ~SuckIntoPlayerTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10257D40, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetInitialVelocity(float newValue);
				bool SetMaxVelocity(float newValue);
				bool SetAcceleration(float newValue);
				bool SetFadeDistStart(float newValue);
				bool SetScaleDistStart(float newValue);
				bool SetScaleEnd(float newValue);
				bool SetOffset(const math::Vector& newValue);
				fight::BranchHolder* SetWhenFinished();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder whenFinished;  // +0x10
					math::Vector offset;  // +0x34
					float acceleration;  // +0x40
					float fadeDistStart;  // +0x44
					float initialVelocity;  // +0x48
					float maxVelocity;  // +0x4C
					float scaleDistStart;  // +0x50
					float scaleEnd;  // +0x54
					float timeBegin;  // +0x58
					float timeEnd;  // +0x5C
			};

			extern fight::Property** gSuckIntoPlayerTrackProperties;
			fight::TrackFactory* CreateSuckIntoPlayerTrackFactory(const char* name);
			void RegisterSuckIntoPlayerTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
