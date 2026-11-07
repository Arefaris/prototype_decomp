// Fight items of the motion group: ReactionFloatTrack, TokenSetFloatDelayTrack (unit 0x101A69E0 - 0x101A73A0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_REACTIONFLOAT_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_REACTIONFLOAT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

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

				// Accessors the engine keeps as unreferenced copies in the action half (names guessed)
				bool GetSnapToPushback() const;
				int GetPriority() const;
				float GetBlendInTime() const;
				float GetBlendOutTime() const;

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

				// Accessors the engine keeps as unreferenced copies in the action half (names guessed)
				float GetFloatDelay() const;

					float floatDelay;  // +0x10
					float timeBegin;  // +0x14
			};

			extern fight::Property** gTokenSetFloatDelayTrackProperties;
			fight::TrackFactory* CreateTokenSetFloatDelayTrackFactory(const char* name);
			void RegisterTokenSetFloatDelayTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::ReactionFloatAction (9 vftable slots, 0x48 bytes): lets the object float after the hit
			class ReactionFloatAction : public fight::Action
			{
			public:
				// 0x10107CF0
				ReactionFloatAction(ReactionFloatTrack* newTrack, TrackOwner* owner);
				// 0x10107B00
				virtual ~ReactionFloatAction();

				// vftable slot 5 (0x10107DE0, the engine's)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10107B50)
				virtual void Slot6();
				// vftable slot 7 (0x10108090, the engine's)
				virtual bool Slot7(int arg, float value);

				engine::GameObjectHandle target;  // +0x1C
				float unknown20;  // +0x20
				core::IRefCount* event;  // +0x24
				choreo::Driver* driver;  // +0x28
				float unknown2C;  // +0x2C
				core::Link<ReactionFloatTrack> link;  // +0x30
				float unknown3C;  // +0x3C
				float unknown40;  // +0x40
				float unknown44;  // +0x44
			};

			// RTTI: proto::fightitems::motion::TokenSetFloatDelayAction (9 vftable slots, 0x2C bytes)
			class TokenSetFloatDelayAction : public fight::Action
			{
			public:
				// 0x101082A0
				TokenSetFloatDelayAction(TokenSetFloatDelayTrack* newTrack, TrackOwner* owner);
				// 0x10108310 is the scalar deleting destructor
				virtual ~TokenSetFloatDelayAction();

				// vftable slot 5 (0x10108340)
				virtual bool Slot5(int arg, float value);

				engine::GameObjectHandle target;  // +0x1C
				core::Link<TokenSetFloatDelayTrack> link;  // +0x20
			};

			// ---- actions end
		}
	}
}

#endif
