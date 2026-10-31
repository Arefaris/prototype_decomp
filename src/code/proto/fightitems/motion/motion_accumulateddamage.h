// Fight items of the motion group: AccumulatedDamageCondition, IsUndamageableCondition, DisableTimeWithNoDamageCounterTrack, IgnoreHitsTrack, TempRegenAbortTrack, HealthSetMultiplierTrack, AccumulatedDamageResetTrack, TempRegenerationTrack (unit 0x10177EA0 - 0x10179BB0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_ACCUMULATEDDAMAGE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_ACCUMULATEDDAMAGE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::AccumulatedDamageCondition (10 vftable slots, 0x14 bytes)
			class AccumulatedDamageCondition : public fight::Condition
			{
			public:
				// 0x101780B0
				AccumulatedDamageCondition();
				virtual ~AccumulatedDamageCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100D1CF0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetValue(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float value;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gAccumulatedDamageConditionProperties;
			fight::ConditionFactory* CreateAccumulatedDamageConditionFactory(const char* name);
			void RegisterAccumulatedDamageConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::IsUndamageableCondition (10 vftable slots, 0xC bytes)
			class IsUndamageableCondition : public fight::Condition
			{
			public:
				// 0x10178180
				IsUndamageableCondition();
				virtual ~IsUndamageableCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100D1DC0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

			};

			extern fight::Property** gIsUndamageableConditionProperties;
			fight::ConditionFactory* CreateIsUndamageableConditionFactory(const char* name);
			void RegisterIsUndamageableConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::DisableTimeWithNoDamageCounterTrack (16 vftable slots, 0x18 bytes)
			class DisableTimeWithNoDamageCounterTrack : public fight::Track
			{
			public:
				// 0x101781E0
				DisableTimeWithNoDamageCounterTrack();
				virtual ~DisableTimeWithNoDamageCounterTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100D2840, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
			};

			extern fight::Property** gDisableTimeWithNoDamageCounterTrackProperties;
			fight::TrackFactory* CreateDisableTimeWithNoDamageCounterTrackFactory(const char* name);
			void RegisterDisableTimeWithNoDamageCounterTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::IgnoreHitsTrack (16 vftable slots, 0x18 bytes)
			class IgnoreHitsTrack : public fight::Track
			{
			public:
				// 0x10178280
				IgnoreHitsTrack();
				virtual ~IgnoreHitsTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100D27F0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
			};

			extern fight::Property** gIgnoreHitsTrackProperties;
			fight::TrackFactory* CreateIgnoreHitsTrackFactory(const char* name);
			void RegisterIgnoreHitsTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TempRegenAbortTrack (16 vftable slots, 0x14 bytes)
			class TempRegenAbortTrack : public fight::Track
			{
			public:
				// 0x10178320
				TempRegenAbortTrack();
				virtual ~TempRegenAbortTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100D27A0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gTempRegenAbortTrackProperties;
			fight::TrackFactory* CreateTempRegenAbortTrackFactory(const char* name);
			void RegisterTempRegenAbortTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::HealthSetMultiplierTrack (16 vftable slots, 0x20 bytes)
			class HealthSetMultiplierTrack : public fight::Track
			{
			public:
				// 0x101783B0
				HealthSetMultiplierTrack();
				virtual ~HealthSetMultiplierTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100D26B0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetMultiplier(float newValue);
				bool SetRestoreOriginalOnEnd(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float multiplier;  // +0x10
					float timeBegin;  // +0x14
					float timeEnd;  // +0x18
					bool restoreOriginalOnEnd;  // +0x1C
					unsigned char unknown1D[0x3];
			};

			extern fight::Property** gHealthSetMultiplierTrackProperties;
			fight::TrackFactory* CreateHealthSetMultiplierTrackFactory(const char* name);
			void RegisterHealthSetMultiplierTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::AccumulatedDamageResetTrack (16 vftable slots, 0x14 bytes)
			class AccumulatedDamageResetTrack : public fight::Track
			{
			public:
				// 0x10178460
				AccumulatedDamageResetTrack();
				virtual ~AccumulatedDamageResetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100D2700, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gAccumulatedDamageResetTrackProperties;
			fight::TrackFactory* CreateAccumulatedDamageResetTrackFactory(const char* name);
			void RegisterAccumulatedDamageResetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TempRegenerationTrack (16 vftable slots, 0x20 bytes)
			class TempRegenerationTrack : public fight::Track
			{
			public:
				// 0x101784F0
				TempRegenerationTrack();
				virtual ~TempRegenerationTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100D2750, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetRegenRate(float newValue);
				bool SetRegenMaxHealthPercentage(float newValue);
				bool SetExpiry(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float expiry;  // +0x10
					float regenMaxHealthPercentage;  // +0x14
					float regenRate;  // +0x18
					float timeBegin;  // +0x1C
			};

			extern fight::Property** gTempRegenerationTrackProperties;
			fight::TrackFactory* CreateTempRegenerationTrackFactory(const char* name);
			void RegisterTempRegenerationTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
