// Fight items of the motion group: HasFailedPatsyCondition, IsPatsyCondition, PatsyDeadCondition, HasPatsyCondition, PatsyConditionGroupCondition, IsFailedPatsyCondition, PatsyCreateTrack, ClearFailedPatsyTrack, ClearPatsyTrack (unit 0x1019A8A0 - 0x1019C4A0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_PATSY_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_PATSY_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::HasFailedPatsyCondition (10 vftable slots, 0x10 bytes)
			class HasFailedPatsyCondition : public fight::Condition
			{
			public:
				// 0x1019A9A0
				HasFailedPatsyCondition();
				virtual ~HasFailedPatsyCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10101230, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetHas(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool has;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gHasFailedPatsyConditionProperties;
			fight::ConditionFactory* CreateHasFailedPatsyConditionFactory(const char* name);
			void RegisterHasFailedPatsyConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::IsPatsyCondition (10 vftable slots, 0x10 bytes)
			class IsPatsyCondition : public fight::Condition
			{
			public:
				// 0x1019AA00
				IsPatsyCondition();
				virtual ~IsPatsyCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10101350, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIs(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool is;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gIsPatsyConditionProperties;
			fight::ConditionFactory* CreateIsPatsyConditionFactory(const char* name);
			void RegisterIsPatsyConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::PatsyDeadCondition (10 vftable slots, 0x10 bytes)
			class PatsyDeadCondition : public fight::Condition
			{
			public:
				// 0x1019AA60
				PatsyDeadCondition();
				virtual ~PatsyDeadCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10101750, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetDead(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool dead;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gPatsyDeadConditionProperties;
			fight::ConditionFactory* CreatePatsyDeadConditionFactory(const char* name);
			void RegisterPatsyDeadConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::HasPatsyCondition (10 vftable slots, 0x10 bytes)
			class HasPatsyCondition : public fight::Condition
			{
			public:
				// 0x1019AAC0
				HasPatsyCondition();
				virtual ~HasPatsyCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10101110, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetHas(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool has;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gHasPatsyConditionProperties;
			fight::ConditionFactory* CreateHasPatsyConditionFactory(const char* name);
			void RegisterHasPatsyConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::PatsyConditionGroupCondition (10 vftable slots, 0x10 bytes)
			class PatsyConditionGroupCondition : public fight::Condition
			{
			public:
				// 0x1019AB20
				PatsyConditionGroupCondition();
				virtual ~PatsyConditionGroupCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10101610, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				fight::ConditionList* SetConditions();

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::ConditionList conditions;  // +0xC
			};

			extern fight::Property** gPatsyConditionGroupConditionProperties;
			fight::ConditionFactory* CreatePatsyConditionGroupConditionFactory(const char* name);
			void RegisterPatsyConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::IsFailedPatsyCondition (10 vftable slots, 0x10 bytes)
			class IsFailedPatsyCondition : public fight::Condition
			{
			public:
				// 0x1019ABA0
				IsFailedPatsyCondition();
				virtual ~IsFailedPatsyCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101014B0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetIs(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool is;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gIsFailedPatsyConditionProperties;
			fight::ConditionFactory* CreateIsFailedPatsyConditionFactory(const char* name);
			void RegisterIsFailedPatsyConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::PatsyCreateTrack (16 vftable slots, 0x18 bytes)
			class PatsyCreateTrack : public fight::Track
			{
			public:
				// 0x1019AC00
				PatsyCreateTrack();
				virtual ~PatsyCreateTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10102010, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetWho(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					int who;  // +0x14
			};

			extern fight::Property** gPatsyCreateTrackProperties;
			fight::TrackFactory* CreatePatsyCreateTrackFactory(const char* name);
			void RegisterPatsyCreateTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ClearFailedPatsyTrack (16 vftable slots, 0x14 bytes)
			class ClearFailedPatsyTrack : public fight::Track
			{
			public:
				// 0x1019ACA0
				ClearFailedPatsyTrack();
				virtual ~ClearFailedPatsyTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10101FC0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gClearFailedPatsyTrackProperties;
			fight::TrackFactory* CreateClearFailedPatsyTrackFactory(const char* name);
			void RegisterClearFailedPatsyTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ClearPatsyTrack (16 vftable slots, 0x14 bytes)
			class ClearPatsyTrack : public fight::Track
			{
			public:
				// 0x1019AD30
				ClearPatsyTrack();
				virtual ~ClearPatsyTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10101F70, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
			};

			extern fight::Property** gClearPatsyTrackProperties;
			fight::TrackFactory* CreateClearPatsyTrackFactory(const char* name);
			void RegisterClearPatsyTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
