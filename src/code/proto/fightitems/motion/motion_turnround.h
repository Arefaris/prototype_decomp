// Fight items of the motion group: TurnRoundTrack (unit 0x101C2D60 - 0x101C3390; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_TURNROUND_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_TURNROUND_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::TurnRoundTrack (16 vftable slots, 0x2C bytes)
			class TurnRoundTrack : public fight::Track
			{
			public:
				// 0x101C2E50
				TurnRoundTrack();
				virtual ~TurnRoundTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10123D00, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTurningVelocity(float newValue);
				bool SetIncludeAutoTarget(bool newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float blendInTime;  // +0x10
					float blendOutTime;  // +0x14
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
					float turningVelocity;  // +0x20
					int priority;  // +0x24
					bool includeAutoTarget;  // +0x28
					unsigned char unknown29[0x3];
			};

			extern fight::Property** gTurnRoundTrackProperties;
			fight::TrackFactory* CreateTurnRoundTrackFactory(const char* name);
			void RegisterTurnRoundTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
