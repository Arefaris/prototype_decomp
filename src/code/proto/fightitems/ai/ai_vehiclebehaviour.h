// Fight items of the ai group: HasTrafficPathCondition, ActivateVehicleBehaviourTrack (unit 0x1021B3C0 - 0x1021BA30; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_VEHICLEBEHAVIOUR_H
#define PROTO_FIGHTITEMS_AI_AI_VEHICLEBEHAVIOUR_H

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
			// RTTI: proto::fightitems::ai::HasTrafficPathCondition (10 vftable slots, 0x10 bytes)
			class HasTrafficPathCondition : public fight::Condition
			{
			public:
				// 0x1021B440
				HasTrafficPathCondition();
				virtual ~HasTrafficPathCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101DE080, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetHas(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool has;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gHasTrafficPathConditionProperties;
			fight::ConditionFactory* CreateHasTrafficPathConditionFactory(const char* name);
			void RegisterHasTrafficPathConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::ai::ActivateVehicleBehaviourTrack (16 vftable slots, 0x18 bytes)
			class ActivateVehicleBehaviourTrack : public fight::Track
			{
			public:
				// 0x1021B4A0
				ActivateVehicleBehaviourTrack();
				virtual ~ActivateVehicleBehaviourTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101DE3D0, another unit)
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

			extern fight::Property** gActivateVehicleBehaviourTrackProperties;
			fight::TrackFactory* CreateActivateVehicleBehaviourTrackFactory(const char* name);
			void RegisterActivateVehicleBehaviourTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::ai::ActivateVehicleBehaviourAction (9 vftable slots, 0x2C bytes)
			class ActivateVehicleBehaviourAction : public fight::Action
			{
			public:
				// 0x101DE320
				ActivateVehicleBehaviourAction(ActivateVehicleBehaviourTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x101DE150
				virtual ~ActivateVehicleBehaviourAction();

				// vftable slot 5 (0x101DE180)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x101DE230)
				virtual void Slot6();
				// vftable slot 7 (0x101DDF90)
				virtual bool Slot7(int arg, float value);

				core::Link<ActivateVehicleBehaviourTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
			};

			// ---- actions end
		}
	}
}

#endif
