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

			// ---- actions end
		}
	}
}

#endif
