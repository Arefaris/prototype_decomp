// Fight items of the motion group: SupportingLimbTestSurfaceNormalVelocityArcCondition, SupportingLimbTestSurfaceNormalAngleCondition, SupportingLimbSurfaceIntersectionPropertiesCondition, SupportingLimbTestSurfaceVelocityAngleCondition, SupportingLimbTestTimeToImpactCondition, SupportingSurfaceNormalVelocityArcCondition, SupportingSurfaceConditionGroupCondition, SupportingLimbTestSurfaceDistanceCondition, SupportingLimbTestSwitchSurfacesCondition, SupportingLimbTestSurfaceConditionGroupCondition, SupportingLimbSetActiveTrack, SupportingLimbTestTrack, SupportingLimbSetActiveRangeTrack, SurfaceMoveAtVelocityTrack, SupportingLimbSetDirectionTrack (unit 0x101B7170 - 0x101BBA40; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_SUPPORTINGLIMB_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_SUPPORTINGLIMB_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::SupportingLimbTestSurfaceNormalVelocityArcCondition (10 vftable slots, 0x18 bytes)
			class SupportingLimbTestSurfaceNormalVelocityArcCondition : public fight::Condition
			{
			public:
				// 0x101B7690
				SupportingLimbTestSurfaceNormalVelocityArcCondition();
				virtual ~SupportingLimbTestSurfaceNormalVelocityArcCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1011BBD0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetVelocityType(int newValue);
				bool SetCompare(int newValue);
				bool SetArc(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float arc;  // +0xC
					int compare;  // +0x10
					int velocityType;  // +0x14
			};

			extern fight::Property** gSupportingLimbTestSurfaceNormalVelocityArcConditionProperties;
			fight::ConditionFactory* CreateSupportingLimbTestSurfaceNormalVelocityArcConditionFactory(const char* name);
			void RegisterSupportingLimbTestSurfaceNormalVelocityArcConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SupportingLimbTestSurfaceNormalAngleCondition (10 vftable slots, 0x20 bytes)
			class SupportingLimbTestSurfaceNormalAngleCondition : public fight::Condition
			{
			public:
				// 0x101B7710
				SupportingLimbTestSurfaceNormalAngleCondition();
				virtual ~SupportingLimbTestSurfaceNormalAngleCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1011B0B0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetNormal(const math::Vector& newValue);
				bool SetCompare(int newValue);
				bool SetAngle(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector normal;  // +0xC
					float angle;  // +0x18
					int compare;  // +0x1C
			};

			extern fight::Property** gSupportingLimbTestSurfaceNormalAngleConditionProperties;
			fight::ConditionFactory* CreateSupportingLimbTestSurfaceNormalAngleConditionFactory(const char* name);
			void RegisterSupportingLimbTestSurfaceNormalAngleConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SupportingLimbSurfaceIntersectionPropertiesCondition (10 vftable slots, 0x14 bytes)
			class SupportingLimbSurfaceIntersectionPropertiesCondition : public fight::Condition
			{
			public:
				// 0x101B77A0
				SupportingLimbSurfaceIntersectionPropertiesCondition();
				virtual ~SupportingLimbSurfaceIntersectionPropertiesCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1011B5E0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetTestBits(int newValue);
				bool SetMatchAgainst(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int matchAgainst;  // +0xC
					int testBits;  // +0x10
			};

			extern fight::Property** gSupportingLimbSurfaceIntersectionPropertiesConditionProperties;
			fight::ConditionFactory* CreateSupportingLimbSurfaceIntersectionPropertiesConditionFactory(const char* name);
			void RegisterSupportingLimbSurfaceIntersectionPropertiesConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SupportingLimbTestSurfaceVelocityAngleCondition (10 vftable slots, 0x28 bytes)
			class SupportingLimbTestSurfaceVelocityAngleCondition : public fight::Condition
			{
			public:
				// 0x101B7810
				SupportingLimbTestSurfaceVelocityAngleCondition();
				virtual ~SupportingLimbTestSurfaceVelocityAngleCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1011B6F0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetVelocityType(int newValue);
				bool SetZeroVector(const math::Vector& newValue);
				bool SetAngle(float newValue);
				bool SetArc(float newValue);
				bool SetUseExcessVelocity(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector zeroVector;  // +0xC
					float angle;  // +0x18
					float arc;  // +0x1C
					int velocityType;  // +0x20
					bool useExcessVelocity;  // +0x24
					unsigned char unknown25[0x3];
			};

			extern fight::Property** gSupportingLimbTestSurfaceVelocityAngleConditionProperties;
			fight::ConditionFactory* CreateSupportingLimbTestSurfaceVelocityAngleConditionFactory(const char* name);
			void RegisterSupportingLimbTestSurfaceVelocityAngleConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SupportingLimbTestTimeToImpactCondition (10 vftable slots, 0x14 bytes)
			class SupportingLimbTestTimeToImpactCondition : public fight::Condition
			{
			public:
				// 0x101B78B0
				SupportingLimbTestTimeToImpactCondition();
				virtual ~SupportingLimbTestTimeToImpactCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1011B300, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetTimeToImpact(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeToImpact;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gSupportingLimbTestTimeToImpactConditionProperties;
			fight::ConditionFactory* CreateSupportingLimbTestTimeToImpactConditionFactory(const char* name);
			void RegisterSupportingLimbTestTimeToImpactConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SupportingSurfaceNormalVelocityArcCondition (10 vftable slots, 0x18 bytes)
			class SupportingSurfaceNormalVelocityArcCondition : public fight::Condition
			{
			public:
				// 0x101B7920
				SupportingSurfaceNormalVelocityArcCondition();
				virtual ~SupportingSurfaceNormalVelocityArcCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1011BD60, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetVelocityType(int newValue);
				bool SetCompare(int newValue);
				bool SetArc(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float arc;  // +0xC
					int compare;  // +0x10
					int velocityType;  // +0x14
			};

			extern fight::Property** gSupportingSurfaceNormalVelocityArcConditionProperties;
			fight::ConditionFactory* CreateSupportingSurfaceNormalVelocityArcConditionFactory(const char* name);
			void RegisterSupportingSurfaceNormalVelocityArcConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SupportingSurfaceConditionGroupCondition (10 vftable slots, 0x10 bytes)
			class SupportingSurfaceConditionGroupCondition : public fight::Condition
			{
			public:
				// 0x101B79A0
				SupportingSurfaceConditionGroupCondition();
				virtual ~SupportingSurfaceConditionGroupCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1011BF40, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::ConditionList conditions;  // +0xC
			};

			extern fight::Property** gSupportingSurfaceConditionGroupConditionProperties;
			fight::ConditionFactory* CreateSupportingSurfaceConditionGroupConditionFactory(const char* name);
			void RegisterSupportingSurfaceConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SupportingLimbTestSurfaceDistanceCondition (10 vftable slots, 0x14 bytes)
			class SupportingLimbTestSurfaceDistanceCondition : public fight::Condition
			{
			public:
				// 0x101B7A20
				SupportingLimbTestSurfaceDistanceCondition();
				virtual ~SupportingLimbTestSurfaceDistanceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1011B200, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetDistance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distance;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gSupportingLimbTestSurfaceDistanceConditionProperties;
			fight::ConditionFactory* CreateSupportingLimbTestSurfaceDistanceConditionFactory(const char* name);
			void RegisterSupportingLimbTestSurfaceDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SupportingLimbTestSwitchSurfacesCondition (10 vftable slots, 0x10 bytes)
			class SupportingLimbTestSwitchSurfacesCondition : public fight::Condition
			{
			public:
				// 0x101B7A90
				SupportingLimbTestSwitchSurfacesCondition();
				virtual ~SupportingLimbTestSwitchSurfacesCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1011AA60, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetSwitchSurfaces(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool switchSurfaces;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gSupportingLimbTestSwitchSurfacesConditionProperties;
			fight::ConditionFactory* CreateSupportingLimbTestSwitchSurfacesConditionFactory(const char* name);
			void RegisterSupportingLimbTestSwitchSurfacesConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SupportingLimbTestSurfaceConditionGroupCondition (10 vftable slots, 0x10 bytes)
			class SupportingLimbTestSurfaceConditionGroupCondition : public fight::Condition
			{
			public:
				// 0x101B7AF0
				SupportingLimbTestSurfaceConditionGroupCondition();
				virtual ~SupportingLimbTestSurfaceConditionGroupCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1011ABE0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::ConditionList conditions;  // +0xC
			};

			extern fight::Property** gSupportingLimbTestSurfaceConditionGroupConditionProperties;
			fight::ConditionFactory* CreateSupportingLimbTestSurfaceConditionGroupConditionFactory(const char* name);
			void RegisterSupportingLimbTestSurfaceConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SupportingLimbSetActiveTrack (16 vftable slots, 0x20 bytes)
			class SupportingLimbSetActiveTrack : public fight::Track
			{
			public:
				// 0x101B7FB0
				SupportingLimbSetActiveTrack();
				virtual ~SupportingLimbSetActiveTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1011DED0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetSupportingLimb(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name supportingLimb;  // +0x10
					float timeBegin;  // +0x18
					unsigned char unknown1C[0x4];
			};

			extern fight::Property** gSupportingLimbSetActiveTrackProperties;
			fight::TrackFactory* CreateSupportingLimbSetActiveTrackFactory(const char* name);
			void RegisterSupportingLimbSetActiveTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SupportingLimbTestTrack (16 vftable slots, 0x80 bytes)
			class SupportingLimbTestTrack : public fight::Track
			{
			public:
				// 0x101B8020
				SupportingLimbTestTrack();
				virtual ~SupportingLimbTestTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1011DE40, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetSupportingLimb(const fight::Name& newValue);
				bool SetDirection(const math::Vector& newValue);
				bool SetOffset(const math::Vector& newValue);
				bool SetRadius(float newValue);
				bool SetArc(float newValue);
				bool SetExtraDistance(float newValue);
				bool SetUseInput(bool newValue);
				bool SetMaxInputArc(float newValue);
				bool SetUsePreviousSurface(bool newValue);
				bool SetUseMotion(bool newValue);
				bool SetSwitchSurfaces(bool newValue);
				fight::BranchHolder* SetBranch();
				bool SetPriority(int newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::BranchHolder branch;  // +0x10
					unsigned char unknown34[0x4];
					fight::Name supportingLimb;  // +0x38
					math::Vector direction;  // +0x40
					math::Vector offset;  // +0x4C
					fight::ConditionList conditions;  // +0x58
					float arc;  // +0x5C
					float extraDistance;  // +0x60
					float maxInputArc;  // +0x64
					float radius;  // +0x68
					float timeBegin;  // +0x6C
					float timeEnd;  // +0x70
					int priority;  // +0x74
					bool switchSurfaces;  // +0x78
					bool useInput;  // +0x79
					bool useMotion;  // +0x7A
					bool usePreviousSurface;  // +0x7B
					unsigned char unknown7C[0x4];
			};

			extern fight::Property** gSupportingLimbTestTrackProperties;
			fight::TrackFactory* CreateSupportingLimbTestTrackFactory(const char* name);
			void RegisterSupportingLimbTestTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SupportingLimbSetActiveRangeTrack (16 vftable slots, 0x28 bytes)
			class SupportingLimbSetActiveRangeTrack : public fight::Track
			{
			public:
				// 0x101B8150
				SupportingLimbSetActiveRangeTrack();
				virtual ~SupportingLimbSetActiveRangeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1011DF50, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetOnBegin(const fight::Name& newValue);
				bool SetOnEnd(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name onBegin;  // +0x10
					fight::Name onEnd;  // +0x18
					float timeBegin;  // +0x20
					float timeEnd;  // +0x24
			};

			extern fight::Property** gSupportingLimbSetActiveRangeTrackProperties;
			fight::TrackFactory* CreateSupportingLimbSetActiveRangeTrackFactory(const char* name);
			void RegisterSupportingLimbSetActiveRangeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SurfaceMoveAtVelocityTrack (16 vftable slots, 0x38 bytes)
			class SurfaceMoveAtVelocityTrack : public fight::Track
			{
			public:
				// 0x101B7C00
				SurfaceMoveAtVelocityTrack();
				virtual ~SurfaceMoveAtVelocityTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1011E010, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetVelocity(const math::Vector& newValue);
				bool SetOrientation(float newValue);
				bool SetPreserveMomentum(bool newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector velocity;  // +0x10
					float blendInTime;  // +0x1C
					float blendOutTime;  // +0x20
					float orientation;  // +0x24
					float timeBegin;  // +0x28
					float timeEnd;  // +0x2C
					int priority;  // +0x30
					bool preserveMomentum;  // +0x34
					unsigned char unknown35[0x3];
			};

			extern fight::Property** gSurfaceMoveAtVelocityTrackProperties;
			fight::TrackFactory* CreateSurfaceMoveAtVelocityTrackFactory(const char* name);
			void RegisterSurfaceMoveAtVelocityTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SupportingLimbSetDirectionTrack (16 vftable slots, 0x20 bytes)
			class SupportingLimbSetDirectionTrack : public fight::Track
			{
			public:
				// 0x101B7CD0
				SupportingLimbSetDirectionTrack();
				virtual ~SupportingLimbSetDirectionTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1011DFB0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetDirection(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector direction;  // +0x10
					float timeBegin;  // +0x1C
			};

			extern fight::Property** gSupportingLimbSetDirectionTrackProperties;
			fight::TrackFactory* CreateSupportingLimbSetDirectionTrackFactory(const char* name);
			void RegisterSupportingLimbSetDirectionTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
