// Fight items of the motion group: HeliLocoTrack (unit 0x10179BB0 - 0x1017A690; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_HELILOCO_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_HELILOCO_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

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

			// ---- actions begin
			// RTTI: proto::fightitems::motion::HeliLocoAction (9 vftable slots, 0x6C bytes)
			class HeliLocoAction : public fight::Action
			{
			public:
				// 0x100D2D10
				HeliLocoAction(HeliLocoTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100D2B30
				virtual ~HeliLocoAction();

				// vftable slot 5 (0x100D2E10)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100D2B70)
				virtual void Slot6();
				// vftable slot 7 (0x100D3B00)
				virtual bool Slot7(int arg, float value);

				core::Link<HeliLocoTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				choreo::Driver* driver;  // +0x2C
				float unknown30;  // +0x30
				float unknown34;  // +0x34
				float unknown38;  // +0x38
				float unknown3C;  // +0x3C
				float unknown40;  // +0x40
				float unknown44;  // +0x44
				float unknown48;  // +0x48
				float unknown4C;  // +0x4C
				float unknown50;  // +0x50
				float unknown54;  // +0x54
				float unknown58;  // +0x58
				float unknown5C;  // +0x5C
				float unknown60;  // +0x60
				float unknown64;  // +0x64
				float unknown68;  // +0x68
			};

			// ---- actions end
		}
	}
}

#endif
