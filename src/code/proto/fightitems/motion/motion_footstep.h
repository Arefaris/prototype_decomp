// Fight items of the motion group: FootstepTrack, JawFlapTrack (unit 0x101B3FC0 - 0x101B4CC0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_FOOTSTEP_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_FOOTSTEP_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction2.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::FootstepTrack (16 vftable slots, 0x28 bytes)
			class FootstepTrack : public fight::Track
			{
			public:
				// 0x101B41F0
				FootstepTrack();
				virtual ~FootstepTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101173A0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetPhase(float newValue);
				bool SetFootstepMapName(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name footstepMapName;  // +0x10
					float phase;  // +0x18
					float timeBegin;  // +0x1C
					float timeEnd;  // +0x20
					unsigned char unknown24[0x4];
			};

			extern fight::Property** gFootstepTrackProperties;
			fight::TrackFactory* CreateFootstepTrackFactory(const char* name);
			void RegisterFootstepTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::JawFlapTrack (16 vftable slots, 0x48 bytes)
			class JawFlapTrack : public fight::Track
			{
			public:
				// 0x101B4270
				JawFlapTrack();
				virtual ~JawFlapTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101173F0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetAngleMin(float newValue);
				bool SetAngleMax(float newValue);
				bool SetThresholdMin(float newValue);
				bool SetThresholdMax(float newValue);
				bool SetJoint(const fight::Name& newValue);
				bool SetAxis(const math::Vector& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name joint;  // +0x10
					math::Vector axis;  // +0x18
					float angleMax;  // +0x24
					float angleMin;  // +0x28
					float blendInTime;  // +0x2C
					float blendOutTime;  // +0x30
					float thresholdMax;  // +0x34
					float thresholdMin;  // +0x38
					float timeBegin;  // +0x3C
					float timeEnd;  // +0x40
					int priority;  // +0x44
			};

			extern fight::Property** gJawFlapTrackProperties;
			fight::TrackFactory* CreateJawFlapTrackFactory(const char* name);
			void RegisterJawFlapTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// RTTI: proto::fightitems::motion::FootstepAction (9 vftable slots, 0x30 bytes)
			class FootstepAction : public fight::Action
			{
			public:
				// 0x10116DA0
				FootstepAction(FootstepTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10116BA0
				virtual ~FootstepAction();

				// vftable slot 5 (0x101167D0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101167E0)
				virtual void Slot6();
				// vftable slot 7 (0x10117480)
				virtual bool Slot7(int arg, float value);

				engine::GameObjectHandle target;  // +0x1C
				core::Link<FootstepTrack> link;  // +0x20
				unsigned char unknown2C[0x4];
			};

			// ---- actions end
		}
	}
}

#endif
