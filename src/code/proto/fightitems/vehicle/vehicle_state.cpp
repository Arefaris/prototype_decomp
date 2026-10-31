// Fight items of the vehicle group: StateCondition, SpeedCondition, WaitingForObjectCondition (unit 0x1027A6F0 - 0x1027B0F0; no assert path, the file name is a guess).
#include "code/proto/fightitems/vehicle/vehicle_state.h"

namespace proto
{
	namespace fightitems
	{
		namespace vehicle
		{
			fight::Property** gStateConditionProperties;  // 0x11256190

			// FUNCTION: ENGINE 0x1027A6F0
			bool StateCondition::SetState(int newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027A740
			fight::Property* StateCondition::GetProperty(int index)
			{
				return gStateConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1027A760
			void StateCondition::ClearProperties()
			{
				fight::FreePropertyList(&gStateConditionProperties);
			}

			// FUNCTION: ENGINE 0x1027A770
			StateCondition::StateCondition() : fight::Condition(0), state(-1)
			{
			}

			// FUNCTION: ENGINE 0x1027A7A0
			StateCondition::~StateCondition()
			{
			}

			// FUNCTION: ENGINE 0x1027AC50
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void StateCondition::RegisterProperties()
			{
				if (gStateConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyIntConstRange<StateCondition>("state", &StateCondition::SetState);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gStateConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1027ABC0
			fight::ConditionFactory* CreateStateConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<StateCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1027AE80
			void RegisterStateConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<StateCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gSpeedConditionProperties;  // 0x11256194

			// FUNCTION: ENGINE 0x1027A700
			bool SpeedCondition::SetSince(int newValue)
			{
				since = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027A710
			bool SpeedCondition::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027A7B0
			fight::Property* SpeedCondition::GetProperty(int index)
			{
				return gSpeedConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1027A7D0
			void SpeedCondition::ClearProperties()
			{
				fight::FreePropertyList(&gSpeedConditionProperties);
			}

			// FUNCTION: ENGINE 0x1027A7E0
			SpeedCondition::SpeedCondition() : fight::Condition(0), speed(-1.0f), since(0)
			{
			}

			// FUNCTION: ENGINE 0x1027A820
			SpeedCondition::~SpeedCondition()
			{
			}

			// FUNCTION: ENGINE 0x1027ACF0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SpeedCondition::RegisterProperties()
			{
				if (gSpeedConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<SpeedCondition>("since", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &SpeedCondition::SetSince);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SpeedCondition>("speed", &SpeedCondition::SetSpeed);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gSpeedConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1027ABF0
			fight::ConditionFactory* CreateSpeedConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SpeedCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1027AEB0
			void RegisterSpeedConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SpeedCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gWaitingForObjectConditionProperties;  // 0x11256198

			// FUNCTION: ENGINE 0x1027A730
			bool WaitingForObjectCondition::SetWaiting(bool newValue)
			{
				waiting = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027A830
			fight::Property* WaitingForObjectCondition::GetProperty(int index)
			{
				return gWaitingForObjectConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1027A850
			void WaitingForObjectCondition::ClearProperties()
			{
				fight::FreePropertyList(&gWaitingForObjectConditionProperties);
			}

			// FUNCTION: ENGINE 0x1027A860
			WaitingForObjectCondition::WaitingForObjectCondition() : fight::Condition(0), waiting(false)
			{
			}

			// FUNCTION: ENGINE 0x1027A880
			WaitingForObjectCondition::~WaitingForObjectCondition()
			{
			}

			// FUNCTION: ENGINE 0x1027ADE0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WaitingForObjectCondition::RegisterProperties()
			{
				if (gWaitingForObjectConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<WaitingForObjectCondition>("waiting", &WaitingForObjectCondition::SetWaiting);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gWaitingForObjectConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1027AC20
			fight::ConditionFactory* CreateWaitingForObjectConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<WaitingForObjectCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1027AEE0
			void RegisterWaitingForObjectConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<WaitingForObjectCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyIntConstRange<StateCondition>;
			template class fight::ConditionFactoryTemplate<StateCondition>;
			template class fight::ConditionFactoryCasterTemplate<StateCondition>;
			template class fight::PropertyEnumConstList<SpeedCondition>;
			template class fight::PropertyFloatConstRange<SpeedCondition>;
			template class fight::ConditionFactoryTemplate<SpeedCondition>;
			template class fight::ConditionFactoryCasterTemplate<SpeedCondition>;
			template class fight::PropertyBool<WaitingForObjectCondition>;
			template class fight::ConditionFactoryTemplate<WaitingForObjectCondition>;
			template class fight::ConditionFactoryCasterTemplate<WaitingForObjectCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1027A890
// FUNCTION: ENGINE 0x1027A8C0
// FUNCTION: ENGINE 0x1027A8F0
// FUNCTION: ENGINE 0x1027A920
// FUNCTION: ENGINE 0x1027A930
// FUNCTION: ENGINE 0x1027A960
// FUNCTION: ENGINE 0x1027A970
// FUNCTION: ENGINE 0x1027A9A0
// FUNCTION: ENGINE 0x1027A9B0
// FUNCTION: ENGINE 0x1027A9E0
// FUNCTION: ENGINE 0x1027AA10
// FUNCTION: ENGINE 0x1027AA30
// FUNCTION: ENGINE 0x1027AA40
// FUNCTION: ENGINE 0x1027AA80
// FUNCTION: ENGINE 0x1027AA90
// FUNCTION: ENGINE 0x1027AAC0
// FUNCTION: ENGINE 0x1027AAE0
// FUNCTION: ENGINE 0x1027AAF0
// FUNCTION: ENGINE 0x1027AB20
// FUNCTION: ENGINE 0x1027AB50
// FUNCTION: ENGINE 0x1027AB60
// FUNCTION: ENGINE 0x1027AB90
// FUNCTION: ENGINE 0x1027ABB0
// FUNCTION: ENGINE 0x1027AF10
// FUNCTION: ENGINE 0x1027AF40
// FUNCTION: ENGINE 0x1027AF60
// FUNCTION: ENGINE 0x1027AF90
// FUNCTION: ENGINE 0x1027AFB0
// FUNCTION: ENGINE 0x1027AFE0
// FUNCTION: ENGINE 0x1027B000
// FUNCTION: ENGINE 0x1027B050
// FUNCTION: ENGINE 0x1027B0A0
