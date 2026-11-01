// Fight items of the motion group: JointTrack (unit 0x10181890 - 0x10182180; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_JOINT_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_JOINT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/proto/fightitems/motion/motionhelpers.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::JointTrack (16 vftable slots, 0x48 bytes)
			class JointTrack : public fight::Track
			{
			public:
				// 0x10181A20
				JointTrack();
				virtual ~JointTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100DC3E0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetUseRestPose(bool newValue);
				bool SetHasTranslation(bool newValue);
				bool SetTranslation(const math::Vector& newValue);
				bool SetHasRotation(bool newValue);
				bool SetRotation(const math::Vector& newValue);
				bool SetPriority(int newValue);
				bool SetAutomaticBlendTimes(bool newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name joint;  // +0x10
					math::Vector rotation;  // +0x18
					math::Vector translation;  // +0x24
					float blendInTime;  // +0x30
					float blendOutTime;  // +0x34
					float timeBegin;  // +0x38
					float timeEnd;  // +0x3C
					int priority;  // +0x40
					bool automaticBlendTimes;  // +0x44
					bool hasRotation;  // +0x45
					bool hasTranslation;  // +0x46
					bool useRestPose;  // +0x47
			};

			extern fight::Property** gJointTrackProperties;
			fight::TrackFactory* CreateJointTrackFactory(const char* name);
			void RegisterJointTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::JointAction (9 vftable slots, 0x6C bytes)
			class JointAction : public fight::Action
			{
			public:
				// 0x100DBD10
				JointAction(JointTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100DBC00
				virtual ~JointAction();

				// vftable slot 5 (0x100DBDB0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100DBC40)
				virtual void Slot6();
				// vftable slot 7 (0x100DC230)
				virtual bool Slot7(int arg, float value);

				core::Link<JointTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				choreo::Driver* driver;  // +0x2C
				unsigned char unknown30[0x38];
				float unknown68;  // +0x68
			};

			// ---- actions end
		}
	}
}

#endif
