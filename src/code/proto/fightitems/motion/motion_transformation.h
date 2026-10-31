// Fight items of the motion group: TransformationSlotActiveCondition, TransformationDesiredSensesCondition, ConsumptionNameCondition, TransformationSlotTransformDesiredCondition, TransformationConsumeDescriptionValidCondition, TransformationSlotValidCondition, TransformationAllowedCondition, TransformTrack, TransformationDisallowedTrack, TransformDesiredTrack, TransformCompleteTrack, TransformStartTrack, TransformationAllowedTrack, TransformFadeTrack (unit 0x101BF880 - 0x101C2D60; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_TRANSFORMATION_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_TRANSFORMATION_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::TransformationSlotActiveCondition (10 vftable slots, 0x20 bytes)
			class TransformationSlotActiveCondition : public fight::Condition
			{
			public:
				// 0x101C00E0
				TransformationSlotActiveCondition();
				virtual ~TransformationSlotActiveCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10121D10, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetSlotName(const fight::Name& newValue);
				bool SetIsActive(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name slotName;  // +0x10
					bool isActive;  // +0x18
					unsigned char unknown19[0x7];
			};

			extern fight::Property** gTransformationSlotActiveConditionProperties;
			fight::ConditionFactory* CreateTransformationSlotActiveConditionFactory(const char* name);
			void RegisterTransformationSlotActiveConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TransformationDesiredSensesCondition (10 vftable slots, 0x10 bytes)
			class TransformationDesiredSensesCondition : public fight::Condition
			{
			public:
				// 0x101BFB30
				TransformationDesiredSensesCondition();
				virtual ~TransformationDesiredSensesCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10122210, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetThermalVisionDesired(bool newValue);
				bool SetInfectedVisionDesired(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool infectedVisionDesired;  // +0xC
					bool thermalVisionDesired;  // +0xD
					unsigned char unknownE[0x2];
			};

			extern fight::Property** gTransformationDesiredSensesConditionProperties;
			fight::ConditionFactory* CreateTransformationDesiredSensesConditionFactory(const char* name);
			void RegisterTransformationDesiredSensesConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ConsumptionNameCondition (10 vftable slots, 0x20 bytes)
			class ConsumptionNameCondition : public fight::Condition
			{
			public:
				// 0x101C0150
				ConsumptionNameCondition();
				virtual ~ConsumptionNameCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10121B80, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetName(const fight::Name& newValue);
				bool SetIsActive(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name name;  // +0x10
					bool isActive;  // +0x18
					unsigned char unknown19[0x7];
			};

			extern fight::Property** gConsumptionNameConditionProperties;
			fight::ConditionFactory* CreateConsumptionNameConditionFactory(const char* name);
			void RegisterConsumptionNameConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TransformationSlotTransformDesiredCondition (10 vftable slots, 0x28 bytes)
			class TransformationSlotTransformDesiredCondition : public fight::Condition
			{
			public:
				// 0x101C0190
				TransformationSlotTransformDesiredCondition();
				virtual ~TransformationSlotTransformDesiredCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10121E00, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetSlotName(const fight::Name& newValue);
				bool SetTransformDesired(bool newValue);
				bool SetLoaded(bool newValue);
				bool SetLoading(bool newValue);
				bool SetMatchName(bool newValue);
				bool SetDesiredName(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name desiredName;  // +0x10
					fight::Name slotName;  // +0x18
					bool loaded;  // +0x20
					bool loading;  // +0x21
					bool matchName;  // +0x22
					bool transformDesired;  // +0x23
					unsigned char unknown24[0x4];
			};

			extern fight::Property** gTransformationSlotTransformDesiredConditionProperties;
			fight::ConditionFactory* CreateTransformationSlotTransformDesiredConditionFactory(const char* name);
			void RegisterTransformationSlotTransformDesiredConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TransformationConsumeDescriptionValidCondition (10 vftable slots, 0x10 bytes)
			class TransformationConsumeDescriptionValidCondition : public fight::Condition
			{
			public:
				// 0x101BFC00
				TransformationConsumeDescriptionValidCondition();
				virtual ~TransformationConsumeDescriptionValidCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10122160, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIsValid(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool isValid;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gTransformationConsumeDescriptionValidConditionProperties;
			fight::ConditionFactory* CreateTransformationConsumeDescriptionValidConditionFactory(const char* name);
			void RegisterTransformationConsumeDescriptionValidConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TransformationSlotValidCondition (10 vftable slots, 0x20 bytes)
			class TransformationSlotValidCondition : public fight::Condition
			{
			public:
				// 0x101C0220
				TransformationSlotValidCondition();
				virtual ~TransformationSlotValidCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10121FF0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetSlotName(const fight::Name& newValue);
				bool SetIsValid(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name slotName;  // +0x10
					bool isValid;  // +0x18
					unsigned char unknown19[0x7];
			};

			extern fight::Property** gTransformationSlotValidConditionProperties;
			fight::ConditionFactory* CreateTransformationSlotValidConditionFactory(const char* name);
			void RegisterTransformationSlotValidConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TransformationAllowedCondition (10 vftable slots, 0x10 bytes)
			class TransformationAllowedCondition : public fight::Condition
			{
			public:
				// 0x101BFC90
				TransformationAllowedCondition();
				virtual ~TransformationAllowedCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10121C60, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetAllowed(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool allowed;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gTransformationAllowedConditionProperties;
			fight::ConditionFactory* CreateTransformationAllowedConditionFactory(const char* name);
			void RegisterTransformationAllowedConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TransformTrack (16 vftable slots, 0x20 bytes)
			class TransformTrack : public fight::Track
			{
			public:
				// 0x101C0290
				TransformTrack();
				virtual ~TransformTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10123300, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetSlotName(const fight::Name& newValue);
				bool SetStealthy(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name slotName;  // +0x10
					float timeBegin;  // +0x18
					bool stealthy;  // +0x1C
					unsigned char unknown1D[0x3];
			};

			extern fight::Property** gTransformTrackProperties;
			fight::TrackFactory* CreateTransformTrackFactory(const char* name);
			void RegisterTransformTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TransformationDisallowedTrack (16 vftable slots, 0x18 bytes)
			class TransformationDisallowedTrack : public fight::Track
			{
			public:
				// 0x101BFD20
				TransformationDisallowedTrack();
				virtual ~TransformationDisallowedTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10123490, another unit)
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

			extern fight::Property** gTransformationDisallowedTrackProperties;
			fight::TrackFactory* CreateTransformationDisallowedTrackFactory(const char* name);
			void RegisterTransformationDisallowedTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TransformDesiredTrack (16 vftable slots, 0x28 bytes)
			class TransformDesiredTrack : public fight::Track
			{
			public:
				// 0x101C0320
				TransformDesiredTrack();
				virtual ~TransformDesiredTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101233F0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetSlotName(const fight::Name& newValue);
				bool SetTransformationDescription(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name slotName;  // +0x10
					fight::Name transformationDescription;  // +0x18
					float timeBegin;  // +0x20
					unsigned char unknown24[0x4];
			};

			extern fight::Property** gTransformDesiredTrackProperties;
			fight::TrackFactory* CreateTransformDesiredTrackFactory(const char* name);
			void RegisterTransformDesiredTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TransformCompleteTrack (16 vftable slots, 0x14 bytes)
			class TransformCompleteTrack : public fight::Track
			{
			public:
				// 0x101BFDF0
				TransformCompleteTrack();
				virtual ~TransformCompleteTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101233A0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gTransformCompleteTrackProperties;
			fight::TrackFactory* CreateTransformCompleteTrackFactory(const char* name);
			void RegisterTransformCompleteTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TransformStartTrack (16 vftable slots, 0x20 bytes)
			class TransformStartTrack : public fight::Track
			{
			public:
				// 0x101C03C0
				TransformStartTrack();
				virtual ~TransformStartTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10123350, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetSlotName(const fight::Name& newValue);
				bool SetStealthy(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name slotName;  // +0x10
					float timeBegin;  // +0x18
					bool stealthy;  // +0x1C
					unsigned char unknown1D[0x3];
			};

			extern fight::Property** gTransformStartTrackProperties;
			fight::TrackFactory* CreateTransformStartTrackFactory(const char* name);
			void RegisterTransformStartTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TransformationAllowedTrack (16 vftable slots, 0x18 bytes)
			class TransformationAllowedTrack : public fight::Track
			{
			public:
				// 0x101BFEA0
				TransformationAllowedTrack();
				virtual ~TransformationAllowedTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10123440, another unit)
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

			extern fight::Property** gTransformationAllowedTrackProperties;
			fight::TrackFactory* CreateTransformationAllowedTrackFactory(const char* name);
			void RegisterTransformationAllowedTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TransformFadeTrack (16 vftable slots, 0x20 bytes)
			class TransformFadeTrack : public fight::Track
			{
			public:
				// 0x101BFF40
				TransformFadeTrack();
				virtual ~TransformFadeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101232B0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetFadeAtBegin(float newValue);
				bool SetFadeAtEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float fadeAtBegin;  // +0x10
					float fadeAtEnd;  // +0x14
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
			};

			extern fight::Property** gTransformFadeTrackProperties;
			fight::TrackFactory* CreateTransformFadeTrackFactory(const char* name);
			void RegisterTransformFadeTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
