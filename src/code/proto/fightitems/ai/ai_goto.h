// Fight items of the ai group: HasFixedDestinationCondition, HasFixedAreaDestinationCondition, DumbGotoTrack, DumbGotoLODTrack, GoToTrack (unit 0x102338F0 - 0x10234D10; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_GOTO_H
#define PROTO_FIGHTITEMS_AI_AI_GOTO_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::HasFixedDestinationCondition (10 vftable slots, 0x10 bytes)
			class HasFixedDestinationCondition : public fight::Condition
			{
			public:
				// 0x10233AB0
				HasFixedDestinationCondition();
				virtual ~HasFixedDestinationCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101F65C0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetHasDestination(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool hasDestination;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gHasFixedDestinationConditionProperties;
			fight::ConditionFactory* CreateHasFixedDestinationConditionFactory(const char* name);
			void RegisterHasFixedDestinationConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::HasFixedAreaDestinationCondition (10 vftable slots, 0x10 bytes)
			class HasFixedAreaDestinationCondition : public fight::Condition
			{
			public:
				// 0x10233B10
				HasFixedAreaDestinationCondition();
				virtual ~HasFixedAreaDestinationCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101F6660, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetHasDestination(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool hasDestination;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gHasFixedAreaDestinationConditionProperties;
			fight::ConditionFactory* CreateHasFixedAreaDestinationConditionFactory(const char* name);
			void RegisterHasFixedAreaDestinationConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::DumbGotoTrack (16 vftable slots, 0x24 bytes)
			class DumbGotoTrack : public fight::Track
			{
			public:
				// 0x10233B70
				DumbGotoTrack();
				virtual ~DumbGotoTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F7170, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTolerance(float newValue);
				bool SetBrakingDistance(float newValue);
				bool SetClearDestination(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float brakingDistance;  // +0x10
					float timeBegin;  // +0x14
					float timeEnd;  // +0x18
					float tolerance;  // +0x1C
					bool clearDestination;  // +0x20
					unsigned char unknown21[0x3];
			};

			extern fight::Property** gDumbGotoTrackProperties;
			fight::TrackFactory* CreateDumbGotoTrackFactory(const char* name);
			void RegisterDumbGotoTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::DumbGotoLODTrack (16 vftable slots, 0x24 bytes)
			class DumbGotoLODTrack : public fight::Track
			{
			public:
				// 0x10233C20
				DumbGotoLODTrack();
				virtual ~DumbGotoLODTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F7A00, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTolerance(float newValue);
				bool SetBrakingDistance(float newValue);
				bool SetClearDestination(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float brakingDistance;  // +0x10
					float timeBegin;  // +0x14
					float timeEnd;  // +0x18
					float tolerance;  // +0x1C
					bool clearDestination;  // +0x20
					unsigned char unknown21[0x3];
			};

			extern fight::Property** gDumbGotoLODTrackProperties;
			fight::TrackFactory* CreateDumbGotoLODTrackFactory(const char* name);
			void RegisterDumbGotoLODTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::GoToTrack (16 vftable slots, 0x1C bytes)
			class GoToTrack : public fight::Track
			{
			public:
				// 0x10233CD0
				GoToTrack();
				virtual ~GoToTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F7080, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetClearDestination(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					bool clearDestination;  // +0x18
					unsigned char unknown19[0x3];
			};

			extern fight::Property** gGoToTrackProperties;
			fight::TrackFactory* CreateGoToTrackFactory(const char* name);
			void RegisterGoToTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// RTTI: proto::fightitems::ai::GoToAction (9 vftable slots, 0x48 bytes)
			class GoToAction : public fight::Action
			{
			public:
				// 0x101F6AA0
				GoToAction(GoToTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101F6720
				virtual ~GoToAction();

				// vftable slot 5 (0x101F6040)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101F6070)
				virtual void Slot6();
				// vftable slot 7 (0x101F70D0)
				virtual bool Slot7(int arg, float value);

				core::Link<GoToTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				int unknown2C;  // +0x2C
				math::Vector unknown30;  // +0x30
				math::Vector unknown3C;  // +0x3C
			};
			// RTTI: proto::fightitems::ai::DumbGotoAction (9 vftable slots, 0x48 bytes)
			class DumbGotoAction : public fight::Action
			{
			public:
				// 0x101F6DE0
				DumbGotoAction(DumbGotoTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101F6770
				virtual ~DumbGotoAction();

				// vftable slot 5 (0x101F67A0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101F71C0)
				virtual void Slot6();
				// vftable slot 7 (0x101F71D0)
				virtual bool Slot7(int arg, float value);

				// 0x101F6EB0: tells the object to forget the destination (name guess)
				void ClearDestination();

				core::Link<DumbGotoTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				math::Vector unknown2C;  // +0x2C
				unsigned char unknown38[0xC];
				bool unknown44;  // +0x44
				unsigned char unknown45[0x3];
			};
			// ---- actions end
		}
	}
}

#endif
