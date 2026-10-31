// Fight items of the ai group: HasTrafficPathCondition, ActivateVehicleBehaviourTrack (unit 0x1021B3C0 - 0x1021BA30; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_vehiclebehaviour.h"
#include "code/proto/fightitems/ai/aicodemessages.h"
#include "code/proto/fightitems/ai/aicodecommon.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gHasTrafficPathConditionProperties;  // 0x11255810

			// FUNCTION: ENGINE 0x1021B3C0
			bool HasTrafficPathCondition::SetHas(bool newValue)
			{
				has = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021B410
			fight::Property* HasTrafficPathCondition::GetProperty(int index)
			{
				return gHasTrafficPathConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1021B430
			void HasTrafficPathCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHasTrafficPathConditionProperties);
			}

			// FUNCTION: ENGINE 0x1021B440
			HasTrafficPathCondition::HasTrafficPathCondition() : fight::Condition(0), has(true)
			{
			}

			// FUNCTION: ENGINE 0x1021B460
			HasTrafficPathCondition::~HasTrafficPathCondition()
			{
			}

			// FUNCTION: ENGINE 0x1021B710
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HasTrafficPathCondition::RegisterProperties()
			{
				if (gHasTrafficPathConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<HasTrafficPathCondition>("has", &HasTrafficPathCondition::SetHas);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gHasTrafficPathConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1021B6B0
			fight::ConditionFactory* CreateHasTrafficPathConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HasTrafficPathCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1021B890
			void RegisterHasTrafficPathConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HasTrafficPathCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gActivateVehicleBehaviourTrackProperties;  // 0x11255814

			// FUNCTION: ENGINE 0x1021B3D0
			bool ActivateVehicleBehaviourTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021B3F0
			bool ActivateVehicleBehaviourTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021B470
			fight::Property* ActivateVehicleBehaviourTrack::GetProperty(int index)
			{
				return gActivateVehicleBehaviourTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1021B490
			void ActivateVehicleBehaviourTrack::ClearProperties()
			{
				fight::FreePropertyList(&gActivateVehicleBehaviourTrackProperties);
			}

			// FUNCTION: ENGINE 0x1021B4A0
			ActivateVehicleBehaviourTrack::ActivateVehicleBehaviourTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x1021B4D0
			float ActivateVehicleBehaviourTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1021B4E0
			float ActivateVehicleBehaviourTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1021B4F0
			ActivateVehicleBehaviourTrack::~ActivateVehicleBehaviourTrack()
			{
			}

			// FUNCTION: ENGINE 0x1021B7B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ActivateVehicleBehaviourTrack::RegisterProperties()
			{
				if (gActivateVehicleBehaviourTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ActivateVehicleBehaviourTrack>("timeBegin", &ActivateVehicleBehaviourTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ActivateVehicleBehaviourTrack>("timeEnd", &ActivateVehicleBehaviourTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gActivateVehicleBehaviourTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1021B6E0
			fight::TrackFactory* CreateActivateVehicleBehaviourTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ActivateVehicleBehaviourTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1021B8C0
			void RegisterActivateVehicleBehaviourTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ActivateVehicleBehaviourTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x101DE320
			ActivateVehicleBehaviourAction::ActivateVehicleBehaviourAction(ActivateVehicleBehaviourTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101DE150
			ActivateVehicleBehaviourAction::~ActivateVehicleBehaviourAction()
			{
			}

			// FUNCTION: ENGINE 0x101DDF90
			bool ActivateVehicleBehaviourAction::Slot7(int arg, float value)
			{
				return true;
			}

			// FUNCTION: ENGINE 0x101DE3D0
			fight::Action* ActivateVehicleBehaviourTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ActivateVehicleBehaviourAction(this, handle);
			}

			// FUNCTION: ENGINE 0x101DE080
			bool HasTrafficPathCondition::Evaluate(int a, int b, int c, int d)
			{
				bool found = false;
				engine::GameObject* object = engine::GetObjectHandle((core::IRefCount*)c).Get();
				if (object != 0)
				{
					GetTrafficPathMessage message;
					object->SendMessage(&message);
					if (message.path != 0 && message.path->begin != message.path->end)
					{
						found = true;
					}
				}
				return found == has;
			}

			// FUNCTION: ENGINE 0x101DE180
			bool ActivateVehicleBehaviourAction::Slot5(int arg, float value)
			{
				if (target.Get() == 0)
				{
					return false;
				}
				engine::GameObject* object = target.Get();
				ActivateVehicleMovementBehaviourMessage message(true);
				object->SendMessage(&message);
				return true;
			}

			// FUNCTION: ENGINE 0x101DE230
			void ActivateVehicleBehaviourAction::Slot6()
			{
				if (target.Get() != 0)
				{
					engine::GameObject* object = target.Get();
					ActivateVehicleMovementBehaviourMessage message(false);
					object->SendMessage(&message);
				}
			}


			// ---- actions end
			template class fight::PropertyBool<HasTrafficPathCondition>;
			template class fight::ConditionFactoryTemplate<HasTrafficPathCondition>;
			template class fight::ConditionFactoryCasterTemplate<HasTrafficPathCondition>;
			template class fight::PropertyFloatConstRange<ActivateVehicleBehaviourTrack>;
			template class fight::TrackFactoryTemplate<ActivateVehicleBehaviourTrack>;
			template class fight::TrackFactoryCasterTemplate<ActivateVehicleBehaviourTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101DD790
// FUNCTION: ENGINE 0x101DD7F0
// FUNCTION: ENGINE 0x101DD990
// FUNCTION: ENGINE 0x101DDA30
// FUNCTION: ENGINE 0x101DDF10
// FUNCTION: ENGINE 0x101DDF40
// FUNCTION: ENGINE 0x101DDF50
// FUNCTION: ENGINE 0x101DDFB0
// FUNCTION: ENGINE 0x101DDFE0
// FUNCTION: ENGINE 0x101DE3A0
// FUNCTION: ENGINE 0x1021B500
// FUNCTION: ENGINE 0x1021B530
// FUNCTION: ENGINE 0x1021B560
// FUNCTION: ENGINE 0x1021B570
// FUNCTION: ENGINE 0x1021B5A0
// FUNCTION: ENGINE 0x1021B5B0
// FUNCTION: ENGINE 0x1021B5E0
// FUNCTION: ENGINE 0x1021B610
// FUNCTION: ENGINE 0x1021B630
// FUNCTION: ENGINE 0x1021B640
// FUNCTION: ENGINE 0x1021B670
// FUNCTION: ENGINE 0x1021B6A0
// FUNCTION: ENGINE 0x1021B8F0
// FUNCTION: ENGINE 0x1021B920
// FUNCTION: ENGINE 0x1021B940
// FUNCTION: ENGINE 0x1021B970
// FUNCTION: ENGINE 0x1021B990
// FUNCTION: ENGINE 0x1021B9E0
