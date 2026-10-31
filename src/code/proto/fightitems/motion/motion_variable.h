// Fight items of the motion group: VariableNameCompareCondition, TimerCompareCondition, OutOfCombatTimerCondition, VariableIntCompareCondition, TimerContinousSetTrack, VariableNameSetTrack, TimerSetTrack, VariableIntSetTrack, VariableIntTemporarySetTrack (unit 0x101C5300 - 0x101C8410; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_VARIABLE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_VARIABLE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::VariableNameCompareCondition (10 vftable slots, 0x28 bytes)
			class VariableNameCompareCondition : public fight::Condition
			{
			public:
				// 0x101C58F0
				VariableNameCompareCondition();
				virtual ~VariableNameCompareCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101287B0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetVariable(const fight::Name& newValue);
				bool SetCompare(int newValue);
				bool SetValue(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name value;  // +0x10
					fight::Name variable;  // +0x18
					int compare;  // +0x20
					unsigned char unknown24[0x4];
			};

			extern fight::Property** gVariableNameCompareConditionProperties;
			fight::ConditionFactory* CreateVariableNameCompareConditionFactory(const char* name);
			void RegisterVariableNameCompareConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TimerCompareCondition (10 vftable slots, 0x20 bytes)
			class TimerCompareCondition : public fight::Condition
			{
			public:
				// 0x101C5940
				TimerCompareCondition();
				virtual ~TimerCompareCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101288A0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetTimer(const fight::Name& newValue);
				bool SetCompare(int newValue);
				bool SetTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name timer;  // +0x10
					float time;  // +0x18
					int compare;  // +0x1C
			};

			extern fight::Property** gTimerCompareConditionProperties;
			fight::ConditionFactory* CreateTimerCompareConditionFactory(const char* name);
			void RegisterTimerCompareConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::OutOfCombatTimerCondition (10 vftable slots, 0x14 bytes)
			class OutOfCombatTimerCondition : public fight::Condition
			{
			public:
				// 0x101C5630
				OutOfCombatTimerCondition();
				virtual ~OutOfCombatTimerCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10128A90, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float time;  // +0xC
					int compare;  // +0x10
			};

			extern fight::Property** gOutOfCombatTimerConditionProperties;
			fight::ConditionFactory* CreateOutOfCombatTimerConditionFactory(const char* name);
			void RegisterOutOfCombatTimerConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::VariableIntCompareCondition (10 vftable slots, 0x20 bytes)
			class VariableIntCompareCondition : public fight::Condition
			{
			public:
				// 0x101C59C0
				VariableIntCompareCondition();
				virtual ~VariableIntCompareCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10128670, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetVariable(const fight::Name& newValue);
				bool SetCompare(int newValue);
				bool SetValue(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name variable;  // +0x10
					int compare;  // +0x18
					int value;  // +0x1C
			};

			extern fight::Property** gVariableIntCompareConditionProperties;
			fight::ConditionFactory* CreateVariableIntCompareConditionFactory(const char* name);
			void RegisterVariableIntCompareConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TimerContinousSetTrack (16 vftable slots, 0x30 bytes)
			class TimerContinousSetTrack : public fight::Track
			{
			public:
				// 0x101C5A10
				TimerContinousSetTrack();
				virtual ~TimerContinousSetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10129810, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTimer(const fight::Name& newValue);
				bool SetTime(float newValue);
				bool SetIncrementing(bool newValue);
				bool SetRandomRange(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name timer;  // +0x10
					float randomRange;  // +0x18
					float time;  // +0x1C
					float timeBegin;  // +0x20
					float timeEnd;  // +0x24
					bool incrementing;  // +0x28
					unsigned char unknown29[0x7];
			};

			extern fight::Property** gTimerContinousSetTrackProperties;
			fight::TrackFactory* CreateTimerContinousSetTrackFactory(const char* name);
			void RegisterTimerContinousSetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::VariableNameSetTrack (16 vftable slots, 0x28 bytes)
			class VariableNameSetTrack : public fight::Track
			{
			public:
				// 0x101C5AA0
				VariableNameSetTrack();
				virtual ~VariableNameSetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10129770, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetVariable(const fight::Name& newValue);
				bool SetValue(const fight::Name& newValue);
				bool SetPersistent(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name value;  // +0x10
					fight::Name variable;  // +0x18
					float timeBegin;  // +0x20
					bool persistent;  // +0x24
					unsigned char unknown25[0x3];
			};

			extern fight::Property** gVariableNameSetTrackProperties;
			fight::TrackFactory* CreateVariableNameSetTrackFactory(const char* name);
			void RegisterVariableNameSetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::TimerSetTrack (16 vftable slots, 0x28 bytes)
			class TimerSetTrack : public fight::Track
			{
			public:
				// 0x101C5B20
				TimerSetTrack();
				virtual ~TimerSetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101297C0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimer(const fight::Name& newValue);
				bool SetTime(float newValue);
				bool SetIncrementing(bool newValue);
				bool SetRandomRange(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name timer;  // +0x10
					float randomRange;  // +0x18
					float time;  // +0x1C
					float timeBegin;  // +0x20
					bool incrementing;  // +0x24
					unsigned char unknown25[0x3];
			};

			extern fight::Property** gTimerSetTrackProperties;
			fight::TrackFactory* CreateTimerSetTrackFactory(const char* name);
			void RegisterTimerSetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::VariableIntSetTrack (16 vftable slots, 0x28 bytes)
			class VariableIntSetTrack : public fight::Track
			{
			public:
				// 0x101C5BA0
				VariableIntSetTrack();
				virtual ~VariableIntSetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10129720, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetVariable(const fight::Name& newValue);
				bool SetOperator(int newValue);
				bool SetValue(int newValue);
				bool SetPersistent(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name variable;  // +0x10
					float timeBegin;  // +0x18
					int operatorValue;  // +0x1C
					int value;  // +0x20
					bool persistent;  // +0x24
					unsigned char unknown25[0x3];
			};

			extern fight::Property** gVariableIntSetTrackProperties;
			fight::TrackFactory* CreateVariableIntSetTrackFactory(const char* name);
			void RegisterVariableIntSetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::VariableIntTemporarySetTrack (16 vftable slots, 0x40 bytes)
			class VariableIntTemporarySetTrack : public fight::Track
			{
			public:
				// 0x101C5C20
				VariableIntTemporarySetTrack();
				virtual ~VariableIntTemporarySetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10129860, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetVariable(const fight::Name& newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetUseGrabber(bool newValue);
				bool SetOperatorBegin(int newValue);
				bool SetOperatorEnd(int newValue);
				bool SetBeginValue(int newValue);
				bool SetEndValue(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					fight::Name variable;  // +0x18
					float timeBegin;  // +0x20
					float timeEnd;  // +0x24
					int beginValue;  // +0x28
					int endValue;  // +0x2C
					int operatorBegin;  // +0x30
					int operatorEnd;  // +0x34
					bool useGrabber;  // +0x38
					unsigned char unknown39[0x7];
			};

			extern fight::Property** gVariableIntTemporarySetTrackProperties;
			fight::TrackFactory* CreateVariableIntTemporarySetTrackFactory(const char* name);
			void RegisterVariableIntTemporarySetTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
