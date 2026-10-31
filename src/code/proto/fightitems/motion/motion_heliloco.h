// Fight items of the motion group: HeliLocoTrack (unit 0x10179BB0 - 0x1017A690; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_HELILOCO_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_HELILOCO_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::HeliLocoTrack (16 vftable slots, 0x68 bytes)
			class HeliLocoTrack : public fight::Track
			{
			public:
				// 0x10179E10
				HeliLocoTrack();
				virtual ~HeliLocoTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100D3AB0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetAcceleration(float newValue);
				bool SetVelocity(float newValue);
				bool SetExtraFallingVelocity(float newValue);
				bool SetTurnAcceleration(float newValue);
				bool SetTurnVelocity(float newValue);
				bool SetMinimum(const math::Vector& newValue);
				bool SetMaximum(const math::Vector& newValue);
				bool SetTiltMax(float newValue);
				bool SetTiltDampingConstant(float newValue);
				bool SetTiltSpringConstant(float newValue);
				bool SetVelocityToAngleFactor(float newValue);
				bool SetMaxWashEffectHeight(float newValue);
				bool SetWashEffectFrequency(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector maximum;  // +0x10
					math::Vector minimum;  // +0x1C
					float acceleration;  // +0x28
					float blendInTime;  // +0x2C
					float blendOutTime;  // +0x30
					float extraFallingVelocity;  // +0x34
					float maxWashEffectHeight;  // +0x38
					float tiltDampingConstant;  // +0x3C
					float tiltMax;  // +0x40
					float tiltSpringConstant;  // +0x44
					float timeBegin;  // +0x48
					float timeEnd;  // +0x4C
					float turnAcceleration;  // +0x50
					float turnVelocity;  // +0x54
					float velocity;  // +0x58
					float velocityToAngleFactor;  // +0x5C
					float washEffectFrequency;  // +0x60
					int priority;  // +0x64
			};

			extern fight::Property** gHeliLocoTrackProperties;
			fight::TrackFactory* CreateHeliLocoTrackFactory(const char* name);
			void RegisterHeliLocoTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
