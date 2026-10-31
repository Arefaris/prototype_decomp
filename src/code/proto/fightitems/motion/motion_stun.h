// Fight items of the motion group: StunnedCondition, StunTrack (unit 0x101B6980 - 0x101B7170; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_STUN_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_STUN_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction2.h"
#include "code/proto/fightitems/motion/motionmessages2.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::StunnedCondition (10 vftable slots, 0x10 bytes)
			class StunnedCondition : public fight::Condition
			{
			public:
				// 0x101B6A20
				StunnedCondition();
				virtual ~StunnedCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1011A190, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetStunned(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool stunned;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gStunnedConditionProperties;
			fight::ConditionFactory* CreateStunnedConditionFactory(const char* name);
			void RegisterStunnedConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::StunTrack (16 vftable slots, 0x20 bytes)
			class StunTrack : public fight::Track
			{
			public:
				// 0x101B6A80
				StunTrack();
				virtual ~StunTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1011A4C0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetOnBegin(int newValue);
				bool SetOnEnd(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					int onBegin;  // +0x18
					int onEnd;  // +0x1C
			};

			extern fight::Property** gStunTrackProperties;
			fight::TrackFactory* CreateStunTrackFactory(const char* name);
			void RegisterStunTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::StunAction (9 vftable slots, 0x2C bytes)
			class StunAction : public fight::Action
			{
			public:
				// 0x1011A2B0
				StunAction(StunTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x1011A160
				virtual ~StunAction();

				// vftable slot 5 (0x1011A350)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x1011A440)
				virtual void Slot6();

				core::Link<StunTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				bool unknown2C;  // +0x2C
				unsigned char unknown2D[0x3];
			};

			// ---- actions end
		}
	}
}

#endif
