// Fight items of the motion group: MotionStateCondition, MotionStateTrack (unit 0x101B5FB0 - 0x101B6980; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_MOTIONSTATE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_MOTIONSTATE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/proto/fightitems/motion/motionmessages.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::MotionStateCondition (10 vftable slots, 0x20 bytes)
			class MotionStateCondition : public fight::Condition
			{
			public:
				// 0x101B60A0
				MotionStateCondition();
				virtual ~MotionStateCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10119C30, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetState(int newValue);
				bool SetName(const fight::Name& newValue);
				bool SetMatch(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name name;  // +0x10
					int state;  // +0x18
					bool match;  // +0x1C
					unsigned char unknown1D[0x3];
			};

			extern fight::Property** gMotionStateConditionProperties;
			fight::ConditionFactory* CreateMotionStateConditionFactory(const char* name);
			void RegisterMotionStateConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::MotionStateTrack (16 vftable slots, 0x20 bytes)
			class MotionStateTrack : public fight::Track
			{
			public:
				// 0x101B60E0
				MotionStateTrack();
				virtual ~MotionStateTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10119EE0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetState(int newValue);
				bool SetName(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name name;  // +0x10
					float timeBegin;  // +0x18
					int state;  // +0x1C
			};

			extern fight::Property** gMotionStateTrackProperties;
			fight::TrackFactory* CreateMotionStateTrackFactory(const char* name);
			void RegisterMotionStateTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// RTTI: proto::fightitems::motion::MotionStateAction (9 vftable slots, 0x2C bytes)
			class MotionStateAction : public fight::Action
			{
			public:
				// 0x10119D90
				MotionStateAction(MotionStateTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10119C00
				virtual ~MotionStateAction();

				// vftable slot 5 (0x10119E40)
				virtual bool Slot5(int arg, float value);

				core::Link<MotionStateTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
