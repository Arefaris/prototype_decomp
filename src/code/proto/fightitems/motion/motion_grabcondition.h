// Fight items of the motion group: GrabbedCondition, GrabbedConditionGroupCondition, HaveGrabTargetCondition, GrabSlotObjectTemplateCondition, GrabbedClassNameCondition, IsGrabbableCondition, GrabbedGrabbableClassCondition, GrabbedBySlotCondition, GrabbedByPlayerCondition, GrabSlotClassNameCondition, GrabSlotDistanceCondition, GrabTargetConditionGroupCondition, GrabSlotGrabbableClassCondition, GrabbableSizeCondition, GrabSlotConditionGroupCondition, TargetIsGrabTargetCondition, GrabSlotCondition, TargetCanGrabCondition, GrabSlotMassCondition, GrabbableClassCondition, GrabTargetAngleCondition, GrabTargetDistanceCondition (unit 0x10163FA0 - 0x10169790; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_GRABCONDITION_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_GRABCONDITION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::GrabbedCondition (10 vftable slots, 0x10 bytes)
			class GrabbedCondition : public fight::Condition
			{
			public:
				// 0x10164230
				GrabbedCondition();
				virtual ~GrabbedCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C25C0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIsGrabbed(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool isGrabbed;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gGrabbedConditionProperties;
			fight::ConditionFactory* CreateGrabbedConditionFactory(const char* name);
			void RegisterGrabbedConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabbedConditionGroupCondition (10 vftable slots, 0x10 bytes)
			class GrabbedConditionGroupCondition : public fight::Condition
			{
			public:
				// 0x10164290
				GrabbedConditionGroupCondition();
				virtual ~GrabbedConditionGroupCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C29E0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::ConditionList conditions;  // +0xC
			};

			extern fight::Property** gGrabbedConditionGroupConditionProperties;
			fight::ConditionFactory* CreateGrabbedConditionGroupConditionFactory(const char* name);
			void RegisterGrabbedConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::HaveGrabTargetCondition (10 vftable slots, 0x28 bytes)
			class HaveGrabTargetCondition : public fight::Condition
			{
			public:
				// 0x10164AA0
				HaveGrabTargetCondition();
				virtual ~HaveGrabTargetCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C3500, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetHave(bool newValue);
				bool SetUseStoredProperties(bool newValue);
				bool SetCollideWith(int newValue);
				bool SetIgnore(int newValue);
				bool SetValidGrabbableClass(const fight::Name& newValue);
				bool SetRange(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name validGrabbableClass;  // +0x10
					float range;  // +0x18
					int collideWith;  // +0x1C
					int ignore;  // +0x20
					bool have;  // +0x24
					bool useStoredProperties;  // +0x25
					unsigned char unknown26[0x2];
			};

			extern fight::Property** gHaveGrabTargetConditionProperties;
			fight::ConditionFactory* CreateHaveGrabTargetConditionFactory(const char* name);
			void RegisterHaveGrabTargetConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabSlotObjectTemplateCondition (10 vftable slots, 0x28 bytes)
			class GrabSlotObjectTemplateCondition : public fight::Condition
			{
			public:
				// 0x10164B00
				GrabSlotObjectTemplateCondition();
				virtual ~GrabSlotObjectTemplateCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C3000, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetCompare(int newValue);
				bool SetObjectTemplate(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name grabSlot;  // +0x10
					fight::Name objectTemplate;  // +0x18
					int compare;  // +0x20
					unsigned char unknown24[0x4];
			};

			extern fight::Property** gGrabSlotObjectTemplateConditionProperties;
			fight::ConditionFactory* CreateGrabSlotObjectTemplateConditionFactory(const char* name);
			void RegisterGrabSlotObjectTemplateConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabbedClassNameCondition (10 vftable slots, 0x20 bytes)
			class GrabbedClassNameCondition : public fight::Condition
			{
			public:
				// 0x10164B50
				GrabbedClassNameCondition();
				virtual ~GrabbedClassNameCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C2F30, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetClassName(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name className;  // +0x10
					int compare;  // +0x18
					unsigned char unknown1C[0x4];
			};

			extern fight::Property** gGrabbedClassNameConditionProperties;
			fight::ConditionFactory* CreateGrabbedClassNameConditionFactory(const char* name);
			void RegisterGrabbedClassNameConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::IsGrabbableCondition (10 vftable slots, 0x10 bytes)
			class IsGrabbableCondition : public fight::Condition
			{
			public:
				// 0x101643A0
				IsGrabbableCondition();
				virtual ~IsGrabbableCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C3FC0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIs(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool is;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gIsGrabbableConditionProperties;
			fight::ConditionFactory* CreateIsGrabbableConditionFactory(const char* name);
			void RegisterIsGrabbableConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabbedGrabbableClassCondition (10 vftable slots, 0x20 bytes)
			class GrabbedGrabbableClassCondition : public fight::Condition
			{
			public:
				// 0x10164BC0
				GrabbedGrabbableClassCondition();
				virtual ~GrabbedGrabbableClassCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C2E50, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetGrabbableClass(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name grabbableClass;  // +0x10
					int compare;  // +0x18
					unsigned char unknown1C[0x4];
			};

			extern fight::Property** gGrabbedGrabbableClassConditionProperties;
			fight::ConditionFactory* CreateGrabbedGrabbableClassConditionFactory(const char* name);
			void RegisterGrabbedGrabbableClassConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabbedBySlotCondition (10 vftable slots, 0x20 bytes)
			class GrabbedBySlotCondition : public fight::Condition
			{
			public:
				// 0x10164C00
				GrabbedBySlotCondition();
				virtual ~GrabbedBySlotCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C26C0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIsGrabbed(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name grabSlot;  // +0x10
					bool isGrabbed;  // +0x18
					unsigned char unknown19[0x7];
			};

			extern fight::Property** gGrabbedBySlotConditionProperties;
			fight::ConditionFactory* CreateGrabbedBySlotConditionFactory(const char* name);
			void RegisterGrabbedBySlotConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabbedByPlayerCondition (10 vftable slots, 0x10 bytes)
			class GrabbedByPlayerCondition : public fight::Condition
			{
			public:
				// 0x10164460
				GrabbedByPlayerCondition();
				virtual ~GrabbedByPlayerCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C2640, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIsGrabbedByPlayer(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool isGrabbedByPlayer;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gGrabbedByPlayerConditionProperties;
			fight::ConditionFactory* CreateGrabbedByPlayerConditionFactory(const char* name);
			void RegisterGrabbedByPlayerConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabSlotClassNameCondition (10 vftable slots, 0x28 bytes)
			class GrabSlotClassNameCondition : public fight::Condition
			{
			public:
				// 0x10164C70
				GrabSlotClassNameCondition();
				virtual ~GrabSlotClassNameCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C33D0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetCompare(int newValue);
				bool SetClassName(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name className;  // +0x10
					fight::Name grabSlot;  // +0x18
					int compare;  // +0x20
					unsigned char unknown24[0x4];
			};

			extern fight::Property** gGrabSlotClassNameConditionProperties;
			fight::ConditionFactory* CreateGrabSlotClassNameConditionFactory(const char* name);
			void RegisterGrabSlotClassNameConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabSlotDistanceCondition (10 vftable slots, 0x28 bytes)
			class GrabSlotDistanceCondition : public fight::Condition
			{
			public:
				// 0x10164CC0
				GrabSlotDistanceCondition();
				virtual ~GrabSlotDistanceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C30F0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetDirection(int newValue);
				bool SetCompare(int newValue);
				bool SetDistance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name grabSlot;  // +0x10
					float distance;  // +0x18
					int compare;  // +0x1C
					int direction;  // +0x20
					unsigned char unknown24[0x4];
			};

			extern fight::Property** gGrabSlotDistanceConditionProperties;
			fight::ConditionFactory* CreateGrabSlotDistanceConditionFactory(const char* name);
			void RegisterGrabSlotDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabTargetConditionGroupCondition (10 vftable slots, 0x10 bytes)
			class GrabTargetConditionGroupCondition : public fight::Condition
			{
			public:
				// 0x10164520
				GrabTargetConditionGroupCondition();
				virtual ~GrabTargetConditionGroupCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C3960, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::ConditionList conditions;  // +0xC
			};

			extern fight::Property** gGrabTargetConditionGroupConditionProperties;
			fight::ConditionFactory* CreateGrabTargetConditionGroupConditionFactory(const char* name);
			void RegisterGrabTargetConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabSlotGrabbableClassCondition (10 vftable slots, 0x28 bytes)
			class GrabSlotGrabbableClassCondition : public fight::Condition
			{
			public:
				// 0x10164D50
				GrabSlotGrabbableClassCondition();
				virtual ~GrabSlotGrabbableClassCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C2D10, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetCompare(int newValue);
				bool SetGrabbableClass(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name grabSlot;  // +0x10
					fight::Name grabbableClass;  // +0x18
					int compare;  // +0x20
					unsigned char unknown24[0x4];
			};

			extern fight::Property** gGrabSlotGrabbableClassConditionProperties;
			fight::ConditionFactory* CreateGrabSlotGrabbableClassConditionFactory(const char* name);
			void RegisterGrabSlotGrabbableClassConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabbableSizeCondition (10 vftable slots, 0x20 bytes)
			class GrabbableSizeCondition : public fight::Condition
			{
			public:
				// 0x10164DA0
				GrabbableSizeCondition();
				virtual ~GrabbableSizeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C2C40, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetGrabbableSize(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name grabbableSize;  // +0x10
					int compare;  // +0x18
					unsigned char unknown1C[0x4];
			};

			extern fight::Property** gGrabbableSizeConditionProperties;
			fight::ConditionFactory* CreateGrabbableSizeConditionFactory(const char* name);
			void RegisterGrabbableSizeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabSlotConditionGroupCondition (10 vftable slots, 0x20 bytes)
			class GrabSlotConditionGroupCondition : public fight::Condition
			{
			public:
				// 0x10164DE0
				GrabSlotConditionGroupCondition();
				virtual ~GrabSlotConditionGroupCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C2840, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetGrabSlot(const fight::Name& newValue);
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name grabSlot;  // +0x10
					fight::ConditionList conditions;  // +0x18
					unsigned char unknown1C[0x4];
			};

			extern fight::Property** gGrabSlotConditionGroupConditionProperties;
			fight::ConditionFactory* CreateGrabSlotConditionGroupConditionFactory(const char* name);
			void RegisterGrabSlotConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TargetIsGrabTargetCondition (10 vftable slots, 0x10 bytes)
			class TargetIsGrabTargetCondition : public fight::Condition
			{
			public:
				// 0x10164630
				TargetIsGrabTargetCondition();
				virtual ~TargetIsGrabTargetCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C3E40, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIs(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool is;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gTargetIsGrabTargetConditionProperties;
			fight::ConditionFactory* CreateTargetIsGrabTargetConditionFactory(const char* name);
			void RegisterTargetIsGrabTargetConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabSlotCondition (10 vftable slots, 0x20 bytes)
			class GrabSlotCondition : public fight::Condition
			{
			public:
				// 0x10164E60
				GrabSlotCondition();
				virtual ~GrabSlotCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C24B0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetIsGrabbing(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name grabSlot;  // +0x10
					bool isGrabbing;  // +0x18
					unsigned char unknown19[0x7];
			};

			extern fight::Property** gGrabSlotConditionProperties;
			fight::ConditionFactory* CreateGrabSlotConditionFactory(const char* name);
			void RegisterGrabSlotConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TargetCanGrabCondition (10 vftable slots, 0x10 bytes)
			class TargetCanGrabCondition : public fight::Condition
			{
			public:
				// 0x101646C0
				TargetCanGrabCondition();
				virtual ~TargetCanGrabCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C3C90, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetSetGrabTarget(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool setGrabTarget;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gTargetCanGrabConditionProperties;
			fight::ConditionFactory* CreateTargetCanGrabConditionFactory(const char* name);
			void RegisterTargetCanGrabConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabSlotMassCondition (10 vftable slots, 0x20 bytes)
			class GrabSlotMassCondition : public fight::Condition
			{
			public:
				// 0x10164ED0
				GrabSlotMassCondition();
				virtual ~GrabSlotMassCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C3290, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetCompare(int newValue);
				bool SetMass(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name grabSlot;  // +0x10
					float mass;  // +0x18
					int compare;  // +0x1C
			};

			extern fight::Property** gGrabSlotMassConditionProperties;
			fight::ConditionFactory* CreateGrabSlotMassConditionFactory(const char* name);
			void RegisterGrabSlotMassConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabbableClassCondition (10 vftable slots, 0x20 bytes)
			class GrabbableClassCondition : public fight::Condition
			{
			public:
				// 0x10164F20
				GrabbableClassCondition();
				virtual ~GrabbableClassCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C2B70, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetGrabbableClass(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name grabbableClass;  // +0x10
					int compare;  // +0x18
					unsigned char unknown1C[0x4];
			};

			extern fight::Property** gGrabbableClassConditionProperties;
			fight::ConditionFactory* CreateGrabbableClassConditionFactory(const char* name);
			void RegisterGrabbableClassConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabTargetAngleCondition (10 vftable slots, 0x18 bytes)
			class GrabTargetAngleCondition : public fight::Condition
			{
			public:
				// 0x10164780
				GrabTargetAngleCondition();
				virtual ~GrabTargetAngleCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C3660, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetAngle(float newValue);
				bool SetUseMovementDirection(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float angle;  // +0xC
					int compare;  // +0x10
					bool useMovementDirection;  // +0x14
					unsigned char unknown15[0x3];
			};

			extern fight::Property** gGrabTargetAngleConditionProperties;
			fight::ConditionFactory* CreateGrabTargetAngleConditionFactory(const char* name);
			void RegisterGrabTargetAngleConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::GrabTargetDistanceCondition (10 vftable slots, 0x18 bytes)
			class GrabTargetDistanceCondition : public fight::Condition
			{
			public:
				// 0x101647F0
				GrabTargetDistanceCondition();
				virtual ~GrabTargetDistanceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C3AF0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDirection(int newValue);
				bool SetCompare(int newValue);
				bool SetDistance(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float distance;  // +0xC
					int compare;  // +0x10
					int direction;  // +0x14
			};

			extern fight::Property** gGrabTargetDistanceConditionProperties;
			fight::ConditionFactory* CreateGrabTargetDistanceConditionFactory(const char* name);
			void RegisterGrabTargetDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
