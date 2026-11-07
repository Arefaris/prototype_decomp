// Fight items of the motion group: HasFailedPatsyCondition, IsPatsyCondition, PatsyDeadCondition, HasPatsyCondition, PatsyConditionGroupCondition, IsFailedPatsyCondition, PatsyCreateTrack, ClearFailedPatsyTrack, ClearPatsyTrack (unit 0x1019A8A0 - 0x1019C4A0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_PATSY_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_PATSY_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

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

			// ---- actions begin
			// 0x103B8B20: the health an object answers (name guess)
			float GetObjectHealth(engine::GameObject* object);

			// RTTI: proto::fightitems::motion::PatsyCreateAction (9 vftable slots, 0x34 bytes): gives the object the patsy picked from the track's who
			class PatsyCreateAction : public fight::Action
			{
			public:
				// 0x10101E90
				PatsyCreateAction(PatsyCreateTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* newOwner);
				// 0x10101010
				virtual ~PatsyCreateAction();

				// vftable slot 5 (0x101019D0)
				virtual bool Slot5(int arg, float value);

				// 0x10101A60: the handle the track's who names (name guess)
				engine::GameObjectHandle GetWho(engine::GameObject* object);

				core::Link<PatsyCreateTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				core::IRefCount* owner;  // +0x2C
				engine::GameObjectHandle patsy;  // +0x30
			};

			// RTTI: proto::fightitems::motion::ClearPatsyAction (9 vftable slots, 0x30 bytes): takes the patsy away from the object
			class ClearPatsyAction : public fight::Action
			{
			public:
				// 0x10101B80
				ClearPatsyAction(ClearPatsyTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* newOwner);
				// 0x10101070
				virtual ~ClearPatsyAction();

				// vftable slot 5 (0x10101C40)
				virtual bool Slot5(int arg, float value);

				core::Link<ClearPatsyTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				core::IRefCount* owner;  // +0x2C
			};

			// RTTI: proto::fightitems::motion::ClearFailedPatsyAction (9 vftable slots, 0x30 bytes): takes the failed patsy away from the object
			class ClearFailedPatsyAction : public fight::Action
			{
			public:
				// 0x10101D30
				ClearFailedPatsyAction(ClearFailedPatsyTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* newOwner);
				// 0x101010D0
				virtual ~ClearFailedPatsyAction();

				// vftable slot 5 (0x10101DF0)
				virtual bool Slot5(int arg, float value);

				core::Link<ClearFailedPatsyTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				core::IRefCount* owner;  // +0x2C
			};

			// 0x10100D10
			bool RegisterHasPatsyFactories(fight::TrackRegistry* registry);

			// ---- actions end
		}
	}
}

#endif
