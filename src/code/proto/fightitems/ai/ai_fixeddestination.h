// Fight items of the ai group: FixedDestinationDistanceCondition, FixedDestinationGotoTrack, FixedDestinationJumpToTrack, ClearFixedAreaDestinationTrack, FixedDestinationFlytoTrack (unit 0x102305F0 - 0x10231FB0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_FIXEDDESTINATION_H
#define PROTO_FIGHTITEMS_AI_AI_FIXEDDESTINATION_H

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
			// RTTI: proto::fightitems::ai::FixedDestinationDistanceCondition (10 vftable slots, 0x18 bytes)
			class FixedDestinationDistanceCondition : public fight::Condition
			{
			public:
				// 0x102308A0
				FixedDestinationDistanceCondition();
				virtual ~FixedDestinationDistanceCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101F16D0, another unit)
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

			extern fight::Property** gFixedDestinationDistanceConditionProperties;
			fight::ConditionFactory* CreateFixedDestinationDistanceConditionFactory(const char* name);
			void RegisterFixedDestinationDistanceConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::FixedDestinationGotoTrack (16 vftable slots, 0x20 bytes)
			class FixedDestinationGotoTrack : public fight::Track
			{
			public:
				// 0x10230920
				FixedDestinationGotoTrack();
				virtual ~FixedDestinationGotoTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F2720, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTolerance(float newValue);
				bool SetBraking(bool newValue);
				bool SetIgnoreRestrictions(bool newValue);
				bool SetClearDestination(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					float tolerance;  // +0x18
					bool braking;  // +0x1C
					bool clearDestination;  // +0x1D
					bool ignoreRestrictions;  // +0x1E
					unsigned char unknown1F[0x1];
			};

			extern fight::Property** gFixedDestinationGotoTrackProperties;
			fight::TrackFactory* CreateFixedDestinationGotoTrackFactory(const char* name);
			void RegisterFixedDestinationGotoTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::FixedDestinationJumpToTrack (16 vftable slots, 0x1C bytes)
			class FixedDestinationJumpToTrack : public fight::Track
			{
			public:
				// 0x102309D0
				FixedDestinationJumpToTrack();
				virtual ~FixedDestinationJumpToTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F2AB0, another unit)
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

			extern fight::Property** gFixedDestinationJumpToTrackProperties;
			fight::TrackFactory* CreateFixedDestinationJumpToTrackFactory(const char* name);
			void RegisterFixedDestinationJumpToTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ClearFixedAreaDestinationTrack (16 vftable slots, 0x1C bytes)
			class ClearFixedAreaDestinationTrack : public fight::Track
			{
			public:
				// 0x10230A70
				ClearFixedAreaDestinationTrack();
				virtual ~ClearFixedAreaDestinationTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F2B00, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetClearOnBegin(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					bool clearOnBegin;  // +0x18
					unsigned char unknown19[0x3];
			};

			extern fight::Property** gClearFixedAreaDestinationTrackProperties;
			fight::TrackFactory* CreateClearFixedAreaDestinationTrackFactory(const char* name);
			void RegisterClearFixedAreaDestinationTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::FixedDestinationFlytoTrack (16 vftable slots, 0x38 bytes)
			class FixedDestinationFlytoTrack : public fight::Track
			{
			public:
				// 0x10230B10
				FixedDestinationFlytoTrack();
				virtual ~FixedDestinationFlytoTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101F2A60, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTolerance(float newValue);
				bool SetBraking(bool newValue);
				bool SetIgnoreRestrictions(bool newValue);
				bool SetClearDestination(bool newValue);
				bool SetFreeArea(float newValue);
				bool SetMinHeight(float newValue);
				bool SetMaxSpeed(float newValue);
				bool SetSpeedFactor(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector speedFactor;  // +0x10
					float freeArea;  // +0x1C
					float maxSpeed;  // +0x20
					float minHeight;  // +0x24
					float timeBegin;  // +0x28
					float timeEnd;  // +0x2C
					float tolerance;  // +0x30
					bool braking;  // +0x34
					bool clearDestination;  // +0x35
					bool ignoreRestrictions;  // +0x36
					unsigned char unknown37[0x1];
			};

			extern fight::Property** gFixedDestinationFlytoTrackProperties;
			fight::TrackFactory* CreateFixedDestinationFlytoTrackFactory(const char* name);
			void RegisterFixedDestinationFlytoTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::ai::ClearFixedAreaDestinationAction (9 vftable slots, 0x2C bytes)
			class ClearFixedAreaDestinationAction : public fight::Action
			{
			public:
				// 0x101F2560
				ClearFixedAreaDestinationAction(ClearFixedAreaDestinationTrack* newTrack, engine::GameObjectHandle newTarget, core::IRefCount* effect, fight::Track* listener);
				// 0x101F16A0
				virtual ~ClearFixedAreaDestinationAction();

				// vftable slot 5 (0x101F2610)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101F26A0)
				virtual void Slot6();

				core::Link<ClearFixedAreaDestinationTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
