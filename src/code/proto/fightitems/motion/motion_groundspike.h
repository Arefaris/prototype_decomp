// Fight items of the motion group: GroundSpikeParentConditionGroupCondition, GroundSpikeTestStateCondition, GroundSpikeClusterDescendTrack, GroundSpikeConfigureAutoOffshootsTrack, GroundSpikeSpawnClusterTrack, GroundSpikeAnimateClusterRadiiTrack, GroundSpikeSpawnOffshootTrack (unit 0x101753C0 - 0x10177EA0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_GROUNDSPIKE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_GROUNDSPIKE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::GroundSpikeParentConditionGroupCondition (10 vftable slots, 0x10 bytes)
			class GroundSpikeParentConditionGroupCondition : public fight::Condition
			{
			public:
				// 0x10175920
				GroundSpikeParentConditionGroupCondition();
				virtual ~GroundSpikeParentConditionGroupCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100CF6D0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::ConditionList conditions;  // +0xC
			};

			extern fight::Property** gGroundSpikeParentConditionGroupConditionProperties;
			fight::ConditionFactory* CreateGroundSpikeParentConditionGroupConditionFactory(const char* name);
			void RegisterGroundSpikeParentConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GroundSpikeTestStateCondition (10 vftable slots, 0x10 bytes)
			class GroundSpikeTestStateCondition : public fight::Condition
			{
			public:
				// 0x101759A0
				GroundSpikeTestStateCondition();
				virtual ~GroundSpikeTestStateCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100CF4A0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetTestType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int testType;  // +0xC
			};

			extern fight::Property** gGroundSpikeTestStateConditionProperties;
			fight::ConditionFactory* CreateGroundSpikeTestStateConditionFactory(const char* name);
			void RegisterGroundSpikeTestStateConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GroundSpikeClusterDescendTrack (16 vftable slots, 0x28 bytes)
			class GroundSpikeClusterDescendTrack : public fight::Track
			{
			public:
				// 0x10175A10
				GroundSpikeClusterDescendTrack();
				virtual ~GroundSpikeClusterDescendTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100D0EF0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetApplyToOffshoots(bool newValue);
				bool SetDescendDuration(float newValue);
				bool SetDescendDelayMin(float newValue);
				bool SetDescendDelayMax(float newValue);
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float descendDelayMax;  // +0x10
					float descendDelayMin;  // +0x14
					float descendDuration;  // +0x18
					float timeBegin;  // +0x1C
					float timeEnd;  // +0x20
					bool applyToOffshoots;  // +0x24
					unsigned char unknown25[0x3];
			};

			extern fight::Property** gGroundSpikeClusterDescendTrackProperties;
			fight::TrackFactory* CreateGroundSpikeClusterDescendTrackFactory(const char* name);
			void RegisterGroundSpikeClusterDescendTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GroundSpikeConfigureAutoOffshootsTrack (16 vftable slots, 0x30 bytes)
			class GroundSpikeConfigureAutoOffshootsTrack : public fight::Track
			{
			public:
				// 0x10175D30
				GroundSpikeConfigureAutoOffshootsTrack();
				virtual ~GroundSpikeConfigureAutoOffshootsTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100D0F40, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetType(const fight::Name& newValue);
				bool SetStep(float newValue);
				bool SetMaxDistance(float newValue);
				bool SetOffsetAngleMin(float newValue);
				bool SetOffsetAngleMax(float newValue);
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name type;  // +0x10
					float maxDistance;  // +0x18
					float offsetAngleMax;  // +0x1C
					float offsetAngleMin;  // +0x20
					float step;  // +0x24
					float timeBegin;  // +0x28
					float timeEnd;  // +0x2C
			};

			extern fight::Property** gGroundSpikeConfigureAutoOffshootsTrackProperties;
			fight::TrackFactory* CreateGroundSpikeConfigureAutoOffshootsTrackFactory(const char* name);
			void RegisterGroundSpikeConfigureAutoOffshootsTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GroundSpikeSpawnClusterTrack (16 vftable slots, 0x60 bytes)
			class GroundSpikeSpawnClusterTrack : public fight::Track
			{
			public:
				// 0x10175DD0
				GroundSpikeSpawnClusterTrack();
				virtual ~GroundSpikeSpawnClusterTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100D0AE0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetLargeType(const fight::Name& newValue);
				bool SetMidType(const fight::Name& newValue);
				bool SetSmallType(const fight::Name& newValue);
				bool SetLargeFrac(float newValue);
				bool SetMidFrac(float newValue);
				bool SetSmallFrac(float newValue);
				bool SetMinShards(int newValue);
				bool SetMaxShards(int newValue);
				bool SetSpawnRadius(float newValue);
				bool SetSpreadRadius(float newValue);
				bool SetTimingRandomizerFrac(float newValue);
				bool SetAscendTimeMin(float newValue);
				bool SetAscendTimeMax(float newValue);
				bool SetTwistMin(float newValue);
				bool SetTwistMax(float newValue);
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name largeType;  // +0x10
					fight::Name midType;  // +0x18
					fight::Name smallType;  // +0x20
					float ascendTimeMax;  // +0x28
					float ascendTimeMin;  // +0x2C
					float largeFrac;  // +0x30
					float midFrac;  // +0x34
					float smallFrac;  // +0x38
					float spawnRadius;  // +0x3C
					float spreadRadius;  // +0x40
					float timeBegin;  // +0x44
					float timeEnd;  // +0x48
					float timingRandomizerFrac;  // +0x4C
					float twistMax;  // +0x50
					float twistMin;  // +0x54
					int maxShards;  // +0x58
					int minShards;  // +0x5C
			};

			extern fight::Property** gGroundSpikeSpawnClusterTrackProperties;
			fight::TrackFactory* CreateGroundSpikeSpawnClusterTrackFactory(const char* name);
			void RegisterGroundSpikeSpawnClusterTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GroundSpikeAnimateClusterRadiiTrack (16 vftable slots, 0x3C bytes)
			class GroundSpikeAnimateClusterRadiiTrack : public fight::Track
			{
			public:
				// 0x10175B30
				GroundSpikeAnimateClusterRadiiTrack();
				virtual ~GroundSpikeAnimateClusterRadiiTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100D0EA0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetDelay(float newValue);
				bool SetSpawnRadiusVelocityType(int newValue);
				bool SetSpawnEndRadiusScalar(float newValue);
				bool SetSpreadRadiusVelocityType(int newValue);
				bool SetSpreadEndRadiusScalar(float newValue);
				bool SetOffsetVelocityType(int newValue);
				bool SetOffsetAtEnd(float newValue);
				bool SetAnimationTimeMin(float newValue);
				bool SetAnimationTimeMax(float newValue);
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float animationTimeMax;  // +0x10
					float animationTimeMin;  // +0x14
					float delay;  // +0x18
					float offsetAtEnd;  // +0x1C
					float spawnEndRadiusScalar;  // +0x20
					float spreadEndRadiusScalar;  // +0x24
					float timeBegin;  // +0x28
					float timeEnd;  // +0x2C
					int offsetVelocityType;  // +0x30
					int spawnRadiusVelocityType;  // +0x34
					int spreadRadiusVelocityType;  // +0x38
			};

			extern fight::Property** gGroundSpikeAnimateClusterRadiiTrackProperties;
			fight::TrackFactory* CreateGroundSpikeAnimateClusterRadiiTrackFactory(const char* name);
			void RegisterGroundSpikeAnimateClusterRadiiTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GroundSpikeSpawnOffshootTrack (16 vftable slots, 0x38 bytes)
			class GroundSpikeSpawnOffshootTrack : public fight::Track
			{
			public:
				// 0x10175F00
				GroundSpikeSpawnOffshootTrack();
				virtual ~GroundSpikeSpawnOffshootTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100D0950, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetType(const fight::Name& newValue);
				bool SetNumMin(int newValue);
				bool SetNumMax(int newValue);
				bool SetIsForSuperSpike(bool newValue);
				bool SetMaxArc(float newValue);
				bool SetAngleOffsetMin(float newValue);
				bool SetAngleOffsetMax(float newValue);
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name type;  // +0x10
					float angleOffsetMax;  // +0x18
					float angleOffsetMin;  // +0x1C
					float maxArc;  // +0x20
					float timeBegin;  // +0x24
					float timeEnd;  // +0x28
					int numMax;  // +0x2C
					int numMin;  // +0x30
					bool isForSuperSpike;  // +0x34
					unsigned char unknown35[0x3];
			};

			extern fight::Property** gGroundSpikeSpawnOffshootTrackProperties;
			fight::TrackFactory* CreateGroundSpikeSpawnOffshootTrackFactory(const char* name);
			void RegisterGroundSpikeSpawnOffshootTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
