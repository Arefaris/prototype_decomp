// Fight items of the ai group: CheckTagAvailableSpaceCondition, HasCombatBudgetTokenCondition, RequestCombatBudgetTokenTrack (unit 0x10225F80 - 0x10226DB0; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_combatbudget.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gCheckTagAvailableSpaceConditionProperties;  // 0x112558E0

			// FUNCTION: ENGINE 0x10226180
			bool CheckTagAvailableSpaceCondition::SetTag(const fight::Name& newValue)
			{
				tag = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10225F80
			bool CheckTagAvailableSpaceCondition::SetLimit(int newValue)
			{
				limit = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10225F90
			bool CheckTagAvailableSpaceCondition::SetTryDespawnIfFull(bool newValue)
			{
				tryDespawnIfFull = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10225FA0
			bool CheckTagAvailableSpaceCondition::SetMinDespawnDistance(float newValue)
			{
				minDespawnDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10225FC0
			bool CheckTagAvailableSpaceCondition::SetObjRadius(float newValue)
			{
				objRadius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10226040
			fight::Property* CheckTagAvailableSpaceCondition::GetProperty(int index)
			{
				return gCheckTagAvailableSpaceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10226060
			void CheckTagAvailableSpaceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gCheckTagAvailableSpaceConditionProperties);
			}

			// FUNCTION: ENGINE 0x102261A0
			CheckTagAvailableSpaceCondition::CheckTagAvailableSpaceCondition() : fight::Condition(0), minDespawnDistance(1e+01f), objRadius(0.0f), limit(3), tryDespawnIfFull(true)
			{
			}

			// FUNCTION: ENGINE 0x102261F0
			CheckTagAvailableSpaceCondition::~CheckTagAvailableSpaceCondition()
			{
			}

			// FUNCTION: ENGINE 0x10226AE0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CheckTagAvailableSpaceCondition::RegisterProperties()
			{
				if (gCheckTagAvailableSpaceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<CheckTagAvailableSpaceCondition>("tag", &CheckTagAvailableSpaceCondition::SetTag);
					properties[0] = property;
					property = new fight::PropertyIntConstRange<CheckTagAvailableSpaceCondition>("limit", &CheckTagAvailableSpaceCondition::SetLimit);
					properties[1] = property;
					property = new fight::PropertyBool<CheckTagAvailableSpaceCondition>("tryDespawnIfFull", &CheckTagAvailableSpaceCondition::SetTryDespawnIfFull);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<CheckTagAvailableSpaceCondition>("minDespawnDistance", &CheckTagAvailableSpaceCondition::SetMinDespawnDistance);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<CheckTagAvailableSpaceCondition>("objRadius", &CheckTagAvailableSpaceCondition::SetObjRadius);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gCheckTagAvailableSpaceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102266B0
			fight::ConditionFactory* CreateCheckTagAvailableSpaceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<CheckTagAvailableSpaceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10226960
			void RegisterCheckTagAvailableSpaceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<CheckTagAvailableSpaceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gHasCombatBudgetTokenConditionProperties;  // 0x112558E4

			// FUNCTION: ENGINE 0x10225FE0
			bool HasCombatBudgetTokenCondition::SetRequestInAdvance(bool newValue)
			{
				requestInAdvance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10225FF0
			bool HasCombatBudgetTokenCondition::SetCombatType(int newValue)
			{
				combatType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10226000
			bool HasCombatBudgetTokenCondition::SetHasToken(bool newValue)
			{
				hasToken = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10226070
			fight::Property* HasCombatBudgetTokenCondition::GetProperty(int index)
			{
				return gHasCombatBudgetTokenConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10226090
			void HasCombatBudgetTokenCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHasCombatBudgetTokenConditionProperties);
			}

			// FUNCTION: ENGINE 0x102260A0
			HasCombatBudgetTokenCondition::HasCombatBudgetTokenCondition() : fight::Condition(0), combatType(0), hasToken(true), requestInAdvance(false)
			{
			}

			// FUNCTION: ENGINE 0x102260D0
			HasCombatBudgetTokenCondition::~HasCombatBudgetTokenCondition()
			{
			}

			// FUNCTION: ENGINE 0x10226740
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HasCombatBudgetTokenCondition::RegisterProperties()
			{
				if (gHasCombatBudgetTokenConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<HasCombatBudgetTokenCondition>("requestInAdvance", &HasCombatBudgetTokenCondition::SetRequestInAdvance);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<HasCombatBudgetTokenCondition>("combatType", gHasCombatBudgetTokenConditionCombatTypeTable, gHasCombatBudgetTokenConditionCombatTypeCount, &HasCombatBudgetTokenCondition::SetCombatType);
					properties[1] = property;
					property = new fight::PropertyBool<HasCombatBudgetTokenCondition>("hasToken", &HasCombatBudgetTokenCondition::SetHasToken);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gHasCombatBudgetTokenConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102266E0
			fight::ConditionFactory* CreateHasCombatBudgetTokenConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HasCombatBudgetTokenCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10226990
			void RegisterHasCombatBudgetTokenConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HasCombatBudgetTokenCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gRequestCombatBudgetTokenTrackProperties;  // 0x112558E8

			// FUNCTION: ENGINE 0x10226010
			bool RequestCombatBudgetTokenTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10226030
			bool RequestCombatBudgetTokenTrack::SetCombatType(int newValue)
			{
				combatType = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102260E0
			fight::Property* RequestCombatBudgetTokenTrack::GetProperty(int index)
			{
				return gRequestCombatBudgetTokenTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10226100
			void RequestCombatBudgetTokenTrack::ClearProperties()
			{
				fight::FreePropertyList(&gRequestCombatBudgetTokenTrackProperties);
			}

			// FUNCTION: ENGINE 0x10226110
			RequestCombatBudgetTokenTrack::RequestCombatBudgetTokenTrack() : timeBegin(0.0f), combatType(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10226150
			float RequestCombatBudgetTokenTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10226160
			float RequestCombatBudgetTokenTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x10226170
			RequestCombatBudgetTokenTrack::~RequestCombatBudgetTokenTrack()
			{
			}

			// FUNCTION: ENGINE 0x10226870
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void RequestCombatBudgetTokenTrack::RegisterProperties()
			{
				if (gRequestCombatBudgetTokenTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<RequestCombatBudgetTokenTrack>("timeBegin", &RequestCombatBudgetTokenTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<RequestCombatBudgetTokenTrack>("combatType", gHasCombatBudgetTokenConditionCombatTypeTable, gHasCombatBudgetTokenConditionCombatTypeCount, &RequestCombatBudgetTokenTrack::SetCombatType);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gRequestCombatBudgetTokenTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10226710
			fight::TrackFactory* CreateRequestCombatBudgetTokenTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<RequestCombatBudgetTokenTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102269C0
			void RegisterRequestCombatBudgetTokenTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<RequestCombatBudgetTokenTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}


			// FUNCTION: ENGINE 0x101E8100
			// EQUIVALENT: register choice and scheduling (the engine tests the limit in memory and loads it into esi after the first float, ours loads it first and keeps this in esi); same call with the same arguments (best 20.3 %)
			bool CheckTagAvailableSpaceCondition::Evaluate(int a, int b, int c, int d)
			{
				if (limit > 0)
				{
					proto::ByteFlag tryDespawn = { tryDespawnIfFull };
					int count = proto::Unknown103C4A00(&tag, limit, tryDespawn, minDespawnDistance, objRadius);
					return count < limit;
				}
				return true;
			}

			// FUNCTION: ENGINE 0x101E8200
			// EQUIVALENT: instruction selection (the engine clears eax / loads 1 into eax before the compare, ours reuses the result of the budget's Has in al); same calls in the same order (best 78.0 %)
			bool HasCombatBudgetTokenCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(AsOwner(c));
				if (requestInAdvance)
				{
					proto::gAISystem->budgets->Request(combatType, &handle);
				}
				bool wanted = hasToken;
				int type = combatType;
				return wanted == proto::gAISystem->budgets->Has(type, &handle);
			}

			// FUNCTION: ENGINE 0x101E84B0
			bool RequestCombatBudgetTokenAction::Slot5(int arg, float value)
			{
				if (link.object != 0)
				{
					proto::gAISystem->budgets->Request(link.object->combatType, &target);
				}
				return false;
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x101E83C0
			RequestCombatBudgetTokenAction::RequestCombatBudgetTokenAction(RequestCombatBudgetTokenTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x200), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101E84F0
			fight::Action* RequestCombatBudgetTokenTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new RequestCombatBudgetTokenAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyName<CheckTagAvailableSpaceCondition>;
			template class fight::PropertyIntConstRange<CheckTagAvailableSpaceCondition>;
			template class fight::PropertyBool<CheckTagAvailableSpaceCondition>;
			template class fight::PropertyFloatConstRange<CheckTagAvailableSpaceCondition>;
			template class fight::ConditionFactoryTemplate<CheckTagAvailableSpaceCondition>;
			template class fight::ConditionFactoryCasterTemplate<CheckTagAvailableSpaceCondition>;
			template class fight::PropertyBool<HasCombatBudgetTokenCondition>;
			template class fight::PropertyEnumConstList<HasCombatBudgetTokenCondition>;
			template class fight::ConditionFactoryTemplate<HasCombatBudgetTokenCondition>;
			template class fight::ConditionFactoryCasterTemplate<HasCombatBudgetTokenCondition>;
			template class fight::PropertyFloatConstRange<RequestCombatBudgetTokenTrack>;
			template class fight::PropertyEnumConstList<RequestCombatBudgetTokenTrack>;
			template class fight::TrackFactoryTemplate<RequestCombatBudgetTokenTrack>;
			template class fight::TrackFactoryCasterTemplate<RequestCombatBudgetTokenTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101E8470
// FUNCTION: ENGINE 0x10226200
// FUNCTION: ENGINE 0x10226230
// FUNCTION: ENGINE 0x10226260
// FUNCTION: ENGINE 0x10226270
// FUNCTION: ENGINE 0x102262A0
// FUNCTION: ENGINE 0x102262B0
// FUNCTION: ENGINE 0x102262E0
// FUNCTION: ENGINE 0x102262F0
// FUNCTION: ENGINE 0x10226320
// FUNCTION: ENGINE 0x10226350
// FUNCTION: ENGINE 0x10226380
// FUNCTION: ENGINE 0x102263A0
// FUNCTION: ENGINE 0x102263B0
// FUNCTION: ENGINE 0x102263E0
// FUNCTION: ENGINE 0x10226400
// FUNCTION: ENGINE 0x10226410
// FUNCTION: ENGINE 0x10226440
// FUNCTION: ENGINE 0x10226470
// FUNCTION: ENGINE 0x10226480
// FUNCTION: ENGINE 0x102264B0
// FUNCTION: ENGINE 0x102264D0
// FUNCTION: ENGINE 0x102264E0
// FUNCTION: ENGINE 0x10226520
// FUNCTION: ENGINE 0x10226530
// FUNCTION: ENGINE 0x10226560
// FUNCTION: ENGINE 0x10226580
// FUNCTION: ENGINE 0x10226590
// FUNCTION: ENGINE 0x102265C0
// FUNCTION: ENGINE 0x102265F0
// FUNCTION: ENGINE 0x10226600
// FUNCTION: ENGINE 0x10226640
// FUNCTION: ENGINE 0x10226650
// FUNCTION: ENGINE 0x10226680
// FUNCTION: ENGINE 0x102266A0
// FUNCTION: ENGINE 0x102269F0
// FUNCTION: ENGINE 0x10226A20
// FUNCTION: ENGINE 0x10226A40
// FUNCTION: ENGINE 0x10226A70
// FUNCTION: ENGINE 0x10226A90
// FUNCTION: ENGINE 0x10226AC0
// FUNCTION: ENGINE 0x10226C70
// FUNCTION: ENGINE 0x10226CC0
// FUNCTION: ENGINE 0x10226D10
// FUNCTION: ENGINE 0x10226D40
// FUNCTION: ENGINE 0x10226D60
