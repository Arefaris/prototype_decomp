// Fight items of the motion group: ReactionFloatTrack, TokenSetFloatDelayTrack (unit 0x101A69E0 - 0x101A73A0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_REACTIONFLOAT_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_REACTIONFLOAT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::ReactionFloatTrack (16 vftable slots, 0x2C bytes)
			class ReactionFloatTrack : public fight::Track
			{
			public:
				// 0x101A6B10
				ReactionFloatTrack();
				virtual ~ReactionFloatTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101083D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetSnapToPushback(bool newValue);
				bool SetOrientation(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float blendInTime;  // +0x10
					float blendOutTime;  // +0x14
					float orientation;  // +0x18
					float timeBegin;  // +0x1C
					float timeEnd;  // +0x20
					int priority;  // +0x24
					bool snapToPushback;  // +0x28
					unsigned char unknown29[0x3];
			};

			extern fight::Property** gReactionFloatTrackProperties;
			fight::TrackFactory* CreateReactionFloatTrackFactory(const char* name);
			void RegisterReactionFloatTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TokenSetFloatDelayTrack (16 vftable slots, 0x18 bytes)
			class TokenSetFloatDelayTrack : public fight::Track
			{
			public:
				// 0x101A6BD0
				TokenSetFloatDelayTrack();
				virtual ~TokenSetFloatDelayTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10108430, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetFloatDelay(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float floatDelay;  // +0x10
					float timeBegin;  // +0x14
			};

			extern fight::Property** gTokenSetFloatDelayTrackProperties;
			fight::TrackFactory* CreateTokenSetFloatDelayTrackFactory(const char* name);
			void RegisterTokenSetFloatDelayTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
