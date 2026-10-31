// Fight items of the motion group: ReactionThrowSpinAngleCondition, ReactionThrowTrack (unit 0x101A8330 - 0x101A9500; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_REACTIONTHROW_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_REACTIONTHROW_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::ReactionThrowSpinAngleCondition (10 vftable slots, 0x14 bytes)
			class ReactionThrowSpinAngleCondition : public fight::Condition
			{
			public:
				// 0x101A8630
				ReactionThrowSpinAngleCondition();
				virtual ~ReactionThrowSpinAngleCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10109C00, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetAngle(float newValue);
				bool SetArc(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float angle;  // +0xC
					float arc;  // +0x10
			};

			extern fight::Property** gReactionThrowSpinAngleConditionProperties;
			fight::ConditionFactory* CreateReactionThrowSpinAngleConditionFactory(const char* name);
			void RegisterReactionThrowSpinAngleConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionThrowTrack (16 vftable slots, 0xA0 bytes)
			class ReactionThrowTrack : public fight::Track
			{
			public:
				// 0x101A8700
				ReactionThrowTrack();
				virtual ~ReactionThrowTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1010B140, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetDamageMin(float newValue);
				bool SetDamageMax(float newValue);
				bool SetSpinAxisX(const math::Vector& newValue);
				bool SetSpinAxisY(const math::Vector& newValue);
				bool SetSelfDamageScale(float newValue);
				bool SetUsePuppet(bool newValue);
				bool SetOrientOffset(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);
				bool SetPhysicalVelocityCheckDelay(float newValue);
				bool SetStopAtVelocityRatio(float newValue);
				bool SetThreatName(const fight::Name& newValue);
				bool SetThreatRadiusScale(float newValue);
				bool SetThreatProjectedDist(float newValue);
				fight::BranchHolder* SetOnCollision();
				bool SetCollisionInterruptPriority(int newValue);
				bool SetCollisionReactionDelay(float newValue);
				bool SetMaxHitEffects(int newValue);
				bool SetOverrideTargetClass(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder onCollision;  // +0x10
					unsigned char unknown34[0x4];
					fight::Name threatName;  // +0x38
					math::Vector spinAxisX;  // +0x40
					math::Vector spinAxisY;  // +0x4C
					float blendInTime;  // +0x58
					float blendOutTime;  // +0x5C
					float collisionReactionDelay;  // +0x60
					float damageMax;  // +0x64
					float damageMin;  // +0x68
					float orientOffset;  // +0x6C
					float physicalVelocityCheckDelay;  // +0x70
					float selfDamageScale;  // +0x74
					float stopAtVelocityRatio;  // +0x78
					float threatProjectedDist;  // +0x7C
					float threatRadiusScale;  // +0x80
					float timeBegin;  // +0x84
					float timeEnd;  // +0x88
					int collisionInterruptPriority;  // +0x8C
					int maxHitEffects;  // +0x90
					int overrideTargetClass;  // +0x94
					int priority;  // +0x98
					bool usePuppet;  // +0x9C
					unsigned char unknown9D[0x3];
			};

			extern fight::Property** gReactionThrowTrackProperties;
			fight::TrackFactory* CreateReactionThrowTrackFactory(const char* name);
			void RegisterReactionThrowTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
