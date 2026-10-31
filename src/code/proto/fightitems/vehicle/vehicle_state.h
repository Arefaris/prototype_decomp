// Fight items of the vehicle group: StateCondition, SpeedCondition, WaitingForObjectCondition (unit 0x1027A6F0 - 0x1027B0F0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_VEHICLE_VEHICLE_STATE_H
#define PROTO_FIGHTITEMS_VEHICLE_VEHICLE_STATE_H

#include "code/proto/messages/ambientmessages.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/scenario/scenariodata.h"
#include "code/proto/fightitems/ai/aidata.h"
#include "code/proto/fightitems/vehicle/vehicledata.h"

namespace proto
{
	namespace fightitems
	{
		namespace vehicle
		{
			// RTTI: proto::fightitems::vehicle::StateCondition (10 vftable slots, 0x10 bytes)
			class StateCondition : public fight::Condition
			{
			public:
				// 0x1027A770
				StateCondition();
				virtual ~StateCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10277060, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetState(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int state;  // +0xC
			};

			extern fight::Property** gStateConditionProperties;
			fight::ConditionFactory* CreateStateConditionFactory(const char* name);
			void RegisterStateConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::vehicle::SpeedCondition (10 vftable slots, 0x14 bytes)
			class SpeedCondition : public fight::Condition
			{
			public:
				// 0x1027A7E0
				SpeedCondition();
				virtual ~SpeedCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10277110, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetSince(int newValue);
				bool SetSpeed(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float speed;  // +0xC
					int since;  // +0x10
			};

			extern fight::Property** gSpeedConditionProperties;
			fight::ConditionFactory* CreateSpeedConditionFactory(const char* name);
			void RegisterSpeedConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::vehicle::WaitingForObjectCondition (10 vftable slots, 0x10 bytes)
			class WaitingForObjectCondition : public fight::Condition
			{
			public:
				// 0x1027A860
				WaitingForObjectCondition();
				virtual ~WaitingForObjectCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x10277260, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetWaiting(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool waiting;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gWaitingForObjectConditionProperties;
			fight::ConditionFactory* CreateWaitingForObjectConditionFactory(const char* name);
			void RegisterWaitingForObjectConditionFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
