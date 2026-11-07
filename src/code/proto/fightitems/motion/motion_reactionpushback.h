// Fight items of the motion group: ReactionPushbackOrientTrack, ReactionPushbackTrack (unit 0x101A73A0 - 0x101A8000; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_REACTIONPUSHBACK_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_REACTIONPUSHBACK_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::ReactionPushbackOrientTrack (16 vftable slots, 0x28 bytes)
			class ReactionPushbackOrientTrack : public fight::Track
			{
			public:
				// 0x101A7580
				ReactionPushbackOrientTrack();
				virtual ~ReactionPushbackOrientTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10109290, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
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
			};

			extern fight::Property** gReactionPushbackOrientTrackProperties;
			fight::TrackFactory* CreateReactionPushbackOrientTrackFactory(const char* name);
			void RegisterReactionPushbackOrientTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionPushbackTrack (16 vftable slots, 0x34 bytes)
			class ReactionPushbackTrack : public fight::Track
			{
			public:
				// 0x101A7640
				ReactionPushbackTrack();
				virtual ~ReactionPushbackTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10109230, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMaxDistance(float newValue);
				bool SetSnapToPushback(bool newValue);
				bool SetOrientation(float newValue);
				bool SetProneSpin(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

				// Accessors the engine keeps as unreferenced copies in the action half (names guessed)
				float GetMaxDistance() const;
				bool GetSnapToPushback() const;
				int GetPriority() const;
				float GetBlendInTime() const;
				float GetBlendOutTime() const;

					float blendInTime;  // +0x10
					float blendOutTime;  // +0x14
					float maxDistance;  // +0x18
					float orientation;  // +0x1C
					float proneSpin;  // +0x20
					float timeBegin;  // +0x24
					float timeEnd;  // +0x28
					int priority;  // +0x2C
					bool snapToPushback;  // +0x30
					unsigned char unknown31[0x3];
			};

			extern fight::Property** gReactionPushbackTrackProperties;
			fight::TrackFactory* CreateReactionPushbackTrackFactory(const char* name);
			void RegisterReactionPushbackTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::ReactionPushbackAction (9 vftable slots, 0x54 bytes): pushes the object back by the hit's impulse
			class ReactionPushbackAction : public fight::Action
			{
			public:
				// 0x10108900
				ReactionPushbackAction(ReactionPushbackTrack* newTrack, TrackOwner* owner);
				// 0x10108680
				virtual ~ReactionPushbackAction();

				// vftable slot 5 (0x10108A00, the engine's)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101086D0)
				virtual void Slot6();
				// vftable slot 7 (0x10108E10, the engine's)
				virtual bool Slot7(int arg, float value);

				float unknown1C;  // +0x1C
				engine::GameObjectHandle target;  // +0x20
				core::IRefCount* event;  // +0x24
				float unknown28;  // +0x28
				float unknown2C;  // +0x2C
				float unknown30;  // +0x30
				float unknown34;  // +0x34
				choreo::Driver* driver;  // +0x38
				float unknown3C;  // +0x3C
				core::Link<ReactionPushbackTrack> link;  // +0x40
				float unknown4C;  // +0x4C
				unsigned char unknown50[0x4];
			};

			// RTTI: proto::fightitems::motion::ReactionPushbackOrientAction (9 vftable slots, 0x34 bytes)
			class ReactionPushbackOrientAction : public fight::Action
			{
			public:
				// 0x10109000
				ReactionPushbackOrientAction(ReactionPushbackOrientTrack* newTrack, TrackOwner* owner);
				// 0x10108760
				virtual ~ReactionPushbackOrientAction();

				// vftable slot 5 (0x101090C0, the engine's)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101087B0)
				virtual void Slot6();

				core::Link<ReactionPushbackOrientTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				core::IRefCount* event;  // +0x2C
				choreo::Driver* driver;  // +0x30
			};

			// ---- actions end
		}
	}
}

#endif
