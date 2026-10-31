// Fight items of the ai group: IsPoisonedCondition, PoisonedTimeCondition, CurePoisonTrack, PoisonTrack, SetPoisonCloudParametersTrack (unit 0x10244F30 - 0x10246860; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_POISON_H
#define PROTO_FIGHTITEMS_AI_AI_POISON_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata2.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::IsPoisonedCondition (10 vftable slots, 0x10 bytes)
			class IsPoisonedCondition : public fight::Condition
			{
			public:
				// 0x10245140
				IsPoisonedCondition();
				virtual ~IsPoisonedCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10207360, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetPoisonType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int poisonType;  // +0xC
			};

			extern fight::Property** gIsPoisonedConditionProperties;
			fight::ConditionFactory* CreateIsPoisonedConditionFactory(const char* name);
			void RegisterIsPoisonedConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::PoisonedTimeCondition (10 vftable slots, 0x18 bytes)
			class PoisonedTimeCondition : public fight::Condition
			{
			public:
				// 0x102451B0
				PoisonedTimeCondition();
				virtual ~PoisonedTimeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10207430, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompareTime(int newValue);
				bool SetTime(float newValue);
				bool SetPoisonType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float time;  // +0xC
					int compareTime;  // +0x10
					int poisonType;  // +0x14
			};

			extern fight::Property** gPoisonedTimeConditionProperties;
			fight::ConditionFactory* CreatePoisonedTimeConditionFactory(const char* name);
			void RegisterPoisonedTimeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::CurePoisonTrack (16 vftable slots, 0x18 bytes)
			class CurePoisonTrack : public fight::Track
			{
			public:
				// 0x10245230
				CurePoisonTrack();
				virtual ~CurePoisonTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10207CC0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetPoisonType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					int poisonType;  // +0x14
			};

			extern fight::Property** gCurePoisonTrackProperties;
			fight::TrackFactory* CreateCurePoisonTrackFactory(const char* name);
			void RegisterCurePoisonTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::PoisonTrack (16 vftable slots, 0x38 bytes)
			class PoisonTrack : public fight::Track
			{
			public:
				// 0x10245430
				PoisonTrack();
				virtual ~PoisonTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10207B90, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetPoisonType(int newValue);
				bool SetDamageRate(float newValue);
				bool SetDamageSpikes(float newValue);
				bool SetTimeToHit(float newValue);
				bool SetExtraRandomTime(float newValue);
				bool SetPriority(int newValue);
				bool SetWho(int newValue);
				bool SetGrabSlot(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					float damageRate;  // +0x18
					float damageSpikes;  // +0x1C
					float extraRandomTime;  // +0x20
					float timeBegin;  // +0x24
					float timeToHit;  // +0x28
					int poisonType;  // +0x2C
					int priority;  // +0x30
					int who;  // +0x34
			};

			extern fight::Property** gPoisonTrackProperties;
			fight::TrackFactory* CreatePoisonTrackFactory(const char* name);
			void RegisterPoisonTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::SetPoisonCloudParametersTrack (16 vftable slots, 0x20 bytes)
			class SetPoisonCloudParametersTrack : public fight::Track
			{
			public:
				// 0x10245300
				SetPoisonCloudParametersTrack();
				virtual ~SetPoisonCloudParametersTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10207B40, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetGrowFacingDir(bool newValue);
				bool SetGrowDownDir(bool newValue);
				bool SetInheritFacingDir(bool newValue);
				bool SetFallToGroundSpeed(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float fallToGroundSpeed;  // +0x10
					float timeBegin;  // +0x14
					float timeEnd;  // +0x18
					bool growDownDir;  // +0x1C
					bool growFacingDir;  // +0x1D
					bool inheritFacingDir;  // +0x1E
					unsigned char unknown1F[0x1];
			};

			extern fight::Property** gSetPoisonCloudParametersTrackProperties;
			fight::TrackFactory* CreateSetPoisonCloudParametersTrackFactory(const char* name);
			void RegisterSetPoisonCloudParametersTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
