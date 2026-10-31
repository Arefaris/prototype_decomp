// Fight items of the ai group: DriverStateCondition, VehicleStateCondition, SetVehicleStateTrack (unit 0x10255E00 - 0x10256A40; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_VEHICLESTATE_H
#define PROTO_FIGHTITEMS_AI_AI_VEHICLESTATE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata2.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::DriverStateCondition (10 vftable slots, 0x20 bytes)
			class DriverStateCondition : public fight::Condition
			{
			public:
				// 0x10255F50
				DriverStateCondition();
				virtual ~DriverStateCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1021A0D0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetValue(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name value;  // +0x10
					int compare;  // +0x18
					unsigned char unknown1C[0x4];
			};

			extern fight::Property** gDriverStateConditionProperties;
			fight::ConditionFactory* CreateDriverStateConditionFactory(const char* name);
			void RegisterDriverStateConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::VehicleStateCondition (10 vftable slots, 0x20 bytes)
			class VehicleStateCondition : public fight::Condition
			{
			public:
				// 0x10255F90
				VehicleStateCondition();
				virtual ~VehicleStateCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x1021A010, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetValue(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name value;  // +0x10
					int compare;  // +0x18
					unsigned char unknown1C[0x4];
			};

			extern fight::Property** gVehicleStateConditionProperties;
			fight::ConditionFactory* CreateVehicleStateConditionFactory(const char* name);
			void RegisterVehicleStateConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::SetVehicleStateTrack (16 vftable slots, 0x20 bytes)
			class SetVehicleStateTrack : public fight::Track
			{
			public:
				// 0x10255FD0
				SetVehicleStateTrack();
				virtual ~SetVehicleStateTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1021A380, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetValue(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name value;  // +0x10
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
			};

			extern fight::Property** gSetVehicleStateTrackProperties;
			fight::TrackFactory* CreateSetVehicleStateTrackFactory(const char* name);
			void RegisterSetVehicleStateTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::ai::SetVehicleStateAction (9 vftable slots, 0x2C bytes)
			class SetVehicleStateAction : public fight::Action
			{
			public:
				// 0x1021A200
				SetVehicleStateAction(SetVehicleStateTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10219FE0
				virtual ~SetVehicleStateAction();

				// vftable slot 5 (0x10219DA0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10219DB0)
				virtual void Slot6();
				// vftable slot 7 (0x1021A2B0)
				virtual bool Slot7(int arg, float value);

				core::Link<SetVehicleStateTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
