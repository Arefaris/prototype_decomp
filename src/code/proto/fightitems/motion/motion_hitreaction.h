// Fight items of the motion group: HitReactionTrack, ReactionTimeExecuteTrack, ReactionHitExecuteTrack (unit 0x1017A690 - 0x1017C270; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_HITREACTION_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_HITREACTION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::HitReactionTrack (16 vftable slots, 0x58 bytes)
			class HitReactionTrack : public fight::Track
			{
			public:
				// 0x1017ABB0
				HitReactionTrack();
				virtual ~HitReactionTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100D5960, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetReactionTimeMin(float newValue);
				bool SetReactionTimeMax(float newValue);
				bool SetReactionDistanceMin(float newValue);
				bool SetReactionDistanceMax(float newValue);
				bool SetReactionHeightMin(float newValue);
				bool SetReactionHeightMax(float newValue);
				bool SetReactionDirection(const math::Vector& newValue);
				bool SetAttackType(int newValue);
				bool SetHitType(const fight::Name& newValue);
				bool SetDamageType(int newValue);
				bool SetCollisionFlag(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name collisionFlag;  // +0x10
					fight::Name hitType;  // +0x18
					math::Vector reactionDirection;  // +0x20
					float reactionDistanceMax;  // +0x2C
					float reactionDistanceMin;  // +0x30
					float reactionHeightMax;  // +0x34
					float reactionHeightMin;  // +0x38
					float reactionTimeMax;  // +0x3C
					float reactionTimeMin;  // +0x40
					float timeBegin;  // +0x44
					float timeEnd;  // +0x48
					int attackType;  // +0x4C
					int damageType;  // +0x50
					unsigned char unknown54[0x4];
			};

			extern fight::Property** gHitReactionTrackProperties;
			fight::TrackFactory* CreateHitReactionTrackFactory(const char* name);
			void RegisterHitReactionTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionTimeExecuteTrack (16 vftable slots, 0x20 bytes)
			class ReactionTimeExecuteTrack : public fight::Track
			{
			public:
				// 0x1017AA60
				ReactionTimeExecuteTrack();
				virtual ~ReactionTimeExecuteTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100D59F0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				fight::ConditionList* SetConditions();
				fight::TrackGroup* GetTracks();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::ConditionList conditions;  // +0x10
					fight::TrackGroup tracks;  // +0x14
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
			};

			extern fight::Property** gReactionTimeExecuteTrackProperties;
			fight::TrackFactory* CreateReactionTimeExecuteTrackFactory(const char* name);
			void RegisterReactionTimeExecuteTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReactionHitExecuteTrack (16 vftable slots, 0x88 bytes)
			class ReactionHitExecuteTrack : public fight::Track
			{
			public:
				// 0x1017ACB0
				ReactionHitExecuteTrack();
				virtual ~ReactionHitExecuteTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100D59A0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetReactionTimeMin(float newValue);
				bool SetReactionTimeMax(float newValue);
				bool SetReactionDistanceMin(float newValue);
				bool SetReactionDistanceMax(float newValue);
				bool SetReactionHeightMin(float newValue);
				bool SetReactionHeightMax(float newValue);
				bool SetReactionDirection(const math::Vector& newValue);
				bool SetExtraDamage(float newValue);
				bool SetUseOriginator(bool newValue);
				bool SetSendAlert(bool newValue);
				bool SetAttackType(int newValue);
				bool SetHitType(const fight::Name& newValue);
				bool SetDamageType(int newValue);
				bool SetCollisionFlag(const fight::Name& newValue);
				fight::BranchHolder* SetBranch();
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					unsigned char unknown34[0x4];
					fight::Name collisionFlag;  // +0x38
					fight::Name hitType;  // +0x40
					math::Vector reactionDirection;  // +0x48
					fight::ConditionList conditions;  // +0x54
					float extraDamage;  // +0x58
					float reactionDistanceMax;  // +0x5C
					float reactionDistanceMin;  // +0x60
					float reactionHeightMax;  // +0x64
					float reactionHeightMin;  // +0x68
					float reactionTimeMax;  // +0x6C
					float reactionTimeMin;  // +0x70
					float timeBegin;  // +0x74
					float timeEnd;  // +0x78
					int attackType;  // +0x7C
					int damageType;  // +0x80
					bool sendAlert;  // +0x84
					bool useOriginator;  // +0x85
					unsigned char unknown86[0x2];
			};

			extern fight::Property** gReactionHitExecuteTrackProperties;
			fight::TrackFactory* CreateReactionHitExecuteTrackFactory(const char* name);
			void RegisterReactionHitExecuteTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
