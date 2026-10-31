// Fight items of the motion group: ShieldHealthCondition, ShieldStateCondition, ShieldProtectingCondition, ShieldDeployTrack, ShieldSetStateTrack, ShieldReflectTrack (unit 0x101AB8A0 - 0x101ACEE0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_shield.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gShieldHealthConditionProperties;  // 0x11254A6C

			// FUNCTION: ENGINE 0x101AB8A0
			bool ShieldHealthCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AB8B0
			bool ShieldHealthCondition::SetHealthPercentage(float newValue)
			{
				healthPercentage = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AB9B0
			fight::Property* ShieldHealthCondition::GetProperty(int index)
			{
				return gShieldHealthConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101AB9D0
			void ShieldHealthCondition::ClearProperties()
			{
				fight::FreePropertyList(&gShieldHealthConditionProperties);
			}

			// FUNCTION: ENGINE 0x101AB9E0
			ShieldHealthCondition::ShieldHealthCondition() : fight::Condition(0), healthPercentage(1e+02f), compare(4)
			{
			}

			// FUNCTION: ENGINE 0x101ABA20
			ShieldHealthCondition::~ShieldHealthCondition()
			{
			}

			// FUNCTION: ENGINE 0x101AC5E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShieldHealthCondition::RegisterProperties()
			{
				if (gShieldHealthConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ShieldHealthCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ShieldHealthCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ShieldHealthCondition>("healthPercentage", &ShieldHealthCondition::SetHealthPercentage);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gShieldHealthConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AC4C0
			fight::ConditionFactory* CreateShieldHealthConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShieldHealthCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101ACAA0
			void RegisterShieldHealthConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShieldHealthCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gShieldStateConditionProperties;  // 0x11254A70

			// FUNCTION: ENGINE 0x101AB8D0
			bool ShieldStateCondition::SetState(int newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ABA30
			fight::Property* ShieldStateCondition::GetProperty(int index)
			{
				return gShieldStateConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101ABA50
			void ShieldStateCondition::ClearProperties()
			{
				fight::FreePropertyList(&gShieldStateConditionProperties);
			}

			// FUNCTION: ENGINE 0x101ABA60
			ShieldStateCondition::ShieldStateCondition() : fight::Condition(0), state(0)
			{
			}

			// FUNCTION: ENGINE 0x101ABA90
			ShieldStateCondition::~ShieldStateCondition()
			{
			}

			// FUNCTION: ENGINE 0x101AC6D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShieldStateCondition::RegisterProperties()
			{
				if (gShieldStateConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ShieldStateCondition>("state", gShieldStateConditionStateTable, gShieldStateConditionStateCount, &ShieldStateCondition::SetState);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gShieldStateConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AC4F0
			fight::ConditionFactory* CreateShieldStateConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShieldStateCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101ACAD0
			void RegisterShieldStateConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShieldStateCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gShieldProtectingConditionProperties;  // 0x11254A74

			// FUNCTION: ENGINE 0x101ABB00
			fight::Property* ShieldProtectingCondition::GetProperty(int index)
			{
				return gShieldProtectingConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101ABB20
			void ShieldProtectingCondition::ClearProperties()
			{
				fight::FreePropertyList(&gShieldProtectingConditionProperties);
			}

			// FUNCTION: ENGINE 0x101ABB30
			ShieldProtectingCondition::ShieldProtectingCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x101ABB50
			ShieldProtectingCondition::~ShieldProtectingCondition()
			{
			}

			// FUNCTION: ENGINE 0x101ABAA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShieldProtectingCondition::RegisterProperties()
			{
				if (gShieldProtectingConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gShieldProtectingConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AC520
			fight::ConditionFactory* CreateShieldProtectingConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShieldProtectingCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101ACB00
			void RegisterShieldProtectingConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShieldProtectingCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gShieldDeployTrackProperties;  // 0x11254A78

			// FUNCTION: ENGINE 0x101AB8E0
			bool ShieldDeployTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AB900
			bool ShieldDeployTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ABB60
			fight::Property* ShieldDeployTrack::GetProperty(int index)
			{
				return gShieldDeployTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101ABB80
			void ShieldDeployTrack::ClearProperties()
			{
				fight::FreePropertyList(&gShieldDeployTrackProperties);
			}

			// FUNCTION: ENGINE 0x101ABB90
			ShieldDeployTrack::ShieldDeployTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101ABBD0
			float ShieldDeployTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101ABBE0
			float ShieldDeployTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101ABBF0
			ShieldDeployTrack::~ShieldDeployTrack()
			{
			}

			// FUNCTION: ENGINE 0x101AC780
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShieldDeployTrack::RegisterProperties()
			{
				if (gShieldDeployTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ShieldDeployTrack>("timeBegin", &ShieldDeployTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ShieldDeployTrack>("timeEnd", &ShieldDeployTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gShieldDeployTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AC550
			fight::TrackFactory* CreateShieldDeployTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShieldDeployTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101ACB30
			void RegisterShieldDeployTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShieldDeployTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gShieldSetStateTrackProperties;  // 0x11254A7C

			// FUNCTION: ENGINE 0x101AB920
			bool ShieldSetStateTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AB940
			bool ShieldSetStateTrack::SetState(int newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ABC00
			fight::Property* ShieldSetStateTrack::GetProperty(int index)
			{
				return gShieldSetStateTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101ABC20
			void ShieldSetStateTrack::ClearProperties()
			{
				fight::FreePropertyList(&gShieldSetStateTrackProperties);
			}

			// FUNCTION: ENGINE 0x101ABC30
			ShieldSetStateTrack::ShieldSetStateTrack() : timeBegin(0.0f), state(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101ABC70
			float ShieldSetStateTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101ABC80
			float ShieldSetStateTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101ABC90
			ShieldSetStateTrack::~ShieldSetStateTrack()
			{
			}

			// FUNCTION: ENGINE 0x101AC860
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShieldSetStateTrack::RegisterProperties()
			{
				if (gShieldSetStateTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ShieldSetStateTrack>("timeBegin", &ShieldSetStateTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<ShieldSetStateTrack>("state", gShieldStateConditionStateTable, gShieldStateConditionStateCount, &ShieldSetStateTrack::SetState);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gShieldSetStateTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AC580
			fight::TrackFactory* CreateShieldSetStateTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShieldSetStateTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101ACB60
			void RegisterShieldSetStateTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShieldSetStateTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gShieldReflectTrackProperties;  // 0x11254A80

			// FUNCTION: ENGINE 0x101AB950
			bool ShieldReflectTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AB970
			bool ShieldReflectTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AB990
			bool ShieldReflectTrack::SetReflectBullets(bool newValue)
			{
				reflectBullets = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AB9A0
			bool ShieldReflectTrack::SetReflectMissiles(bool newValue)
			{
				reflectMissiles = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ABCA0
			fight::Property* ShieldReflectTrack::GetProperty(int index)
			{
				return gShieldReflectTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101ABCC0
			void ShieldReflectTrack::ClearProperties()
			{
				fight::FreePropertyList(&gShieldReflectTrackProperties);
			}

			// FUNCTION: ENGINE 0x101ABCD0
			ShieldReflectTrack::ShieldReflectTrack() : timeBegin(0.0f), timeEnd(-1.0f), reflectBullets(true), reflectMissiles(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101ABD20
			float ShieldReflectTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101ABD30
			float ShieldReflectTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101ABD40
			ShieldReflectTrack::~ShieldReflectTrack()
			{
			}

			// FUNCTION: ENGINE 0x101AC950
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShieldReflectTrack::RegisterProperties()
			{
				if (gShieldReflectTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ShieldReflectTrack>("timeBegin", &ShieldReflectTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ShieldReflectTrack>("timeEnd", &ShieldReflectTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<ShieldReflectTrack>("reflectBullets", &ShieldReflectTrack::SetReflectBullets);
					properties[2] = property;
					property = new fight::PropertyBool<ShieldReflectTrack>("reflectMissiles", &ShieldReflectTrack::SetReflectMissiles);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gShieldReflectTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AC5B0
			fight::TrackFactory* CreateShieldReflectTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShieldReflectTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101ACB90
			void RegisterShieldReflectTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShieldReflectTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// FUNCTION: ENGINE 0x1010F8C0
			ShieldSetStateAction::ShieldSetStateAction(ShieldSetStateTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x1010F660
			ShieldSetStateAction::~ShieldSetStateAction()
			{
			}

			// FUNCTION: ENGINE 0x1010FBE0
			// EQUIVALENT: the range test of the owner kind is add ecx, 0xFFFF0000 where ours has sub ecx, 0x10000 (the same value), the engine loads the handle into esi where ours uses ecx (93.4 %)
			fight::Action* ShieldSetStateTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				TrackOwner* actionOwner = AsActionOwner(owner);
				return new ShieldSetStateAction(this, actionOwner->handle);
			}

			// FUNCTION: ENGINE 0x1010FA00
			ShieldReflectAction::ShieldReflectAction(ShieldReflectTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x1010F7B0
			ShieldReflectAction::~ShieldReflectAction()
			{
			}

			// FUNCTION: ENGINE 0x1010FC40
			// EQUIVALENT: the range test of the owner kind is add ecx, 0xFFFF0000 where ours has sub ecx, 0x10000 (the same value), the engine loads the handle into esi where ours uses ecx (93.4 %)
			fight::Action* ShieldReflectTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				TrackOwner* actionOwner = AsActionOwner(owner);
				return new ShieldReflectAction(this, actionOwner->handle);
			}

			// FUNCTION: ENGINE 0x1010F970
			// EQUIVALENT: block order (the engine falls into the failure return and jumps to the body) (26.1 %)
			bool ShieldSetStateAction::Slot5(int arg, float value)
			{
				if (link.object != 0)
				{
					engine::GameObject* object = target.Get();
					if (object != 0)
					{
						ShieldSetStateMessage message(link.object->state);
						object->SendMessage(&message);
						return true;
					}
				}
				return false;
			}

			// FUNCTION: ENGINE 0x1010FAB0
			// EQUIVALENT: block order (the engine falls into the failure return and jumps to the body) (26.2 %)
			bool ShieldReflectAction::Slot5(int arg, float value)
			{
				if (link.object != 0)
				{
					engine::GameObject* object = target.Get();
					if (object != 0)
					{
						ShieldReflectStartMessage message(link.object->reflectBullets, link.object->reflectMissiles);
						object->SendMessage(&message);
						return true;
					}
				}
				return false;
			}

			// FUNCTION: ENGINE 0x1010FB50
			void ShieldReflectAction::Slot6()
			{
				engine::GameObject* object = target.Get();
				if (object != 0)
				{
					ShieldReflectStopMessage message(link.object->reflectBullets, link.object->reflectMissiles);
					object->SendMessage(&message);
				}
			}

			// FUNCTION: ENGINE 0x1010F590
			// EQUIVALENT: block order (the engine falls into the failure return and jumps to the body) (56.6 %)
			bool ShieldStateCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object != 0)
				{
					ShieldGetStateMessage message(6);
					object->SendMessage(&message);
					return state == message.state;
				}
				return false;
			}

			// FUNCTION: ENGINE 0x1010F4E0
			bool ShieldProtectingCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object != 0)
				{
					ShieldGetStateMessage message(6);
					object->SendMessage(&message);
					if (message.state != 6 && message.state != 5)
					{
						return true;
					}
				}
				return false;
			}

			// FUNCTION: ENGINE 0x1010F3D0
			// EQUIVALENT: operand order of the two comiss compares (the same comparisons) (94.0 %)
			bool ShieldHealthCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObject* object = engine::GetObjectHandle(AsOwner(c)).Get();
				if (object != 0)
				{
					ShieldGetHealthMessage message;
					object->SendMessage(&message);
					if (message.health >= 0.0f && message.maxHealth >= 0.0f)
					{
						float percentage = message.health / message.maxHealth;
						float limit = healthPercentage;
						return fight::CompareFloats(compare, &percentage, &limit);
					}
				}
				return false;
			}

			// ---- actions end
			template class fight::PropertyEnumConstList<ShieldHealthCondition>;
			template class fight::PropertyFloatConstRange<ShieldHealthCondition>;
			template class fight::ConditionFactoryTemplate<ShieldHealthCondition>;
			template class fight::ConditionFactoryCasterTemplate<ShieldHealthCondition>;
			template class fight::PropertyEnumConstList<ShieldStateCondition>;
			template class fight::ConditionFactoryTemplate<ShieldStateCondition>;
			template class fight::ConditionFactoryCasterTemplate<ShieldStateCondition>;
			template class fight::ConditionFactoryTemplate<ShieldProtectingCondition>;
			template class fight::ConditionFactoryCasterTemplate<ShieldProtectingCondition>;
			template class fight::PropertyFloatConstRange<ShieldDeployTrack>;
			template class fight::TrackFactoryTemplate<ShieldDeployTrack>;
			template class fight::TrackFactoryCasterTemplate<ShieldDeployTrack>;
			template class fight::PropertyFloatConstRange<ShieldSetStateTrack>;
			template class fight::PropertyEnumConstList<ShieldSetStateTrack>;
			template class fight::TrackFactoryTemplate<ShieldSetStateTrack>;
			template class fight::TrackFactoryCasterTemplate<ShieldSetStateTrack>;
			template class fight::PropertyFloatConstRange<ShieldReflectTrack>;
			template class fight::PropertyBool<ShieldReflectTrack>;
			template class fight::TrackFactoryTemplate<ShieldReflectTrack>;
			template class fight::TrackFactoryCasterTemplate<ShieldReflectTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1010EF80
// FUNCTION: ENGINE 0x1010EFC0
// FUNCTION: ENGINE 0x1010EFD0
// FUNCTION: ENGINE 0x1010F000
// FUNCTION: ENGINE 0x1010F010
// FUNCTION: ENGINE 0x1010F050
// FUNCTION: ENGINE 0x1010F060
// FUNCTION: ENGINE 0x1010F0A0
// FUNCTION: ENGINE 0x1010F150
// FUNCTION: ENGINE 0x1010F180
// FUNCTION: ENGINE 0x1010F1B0
// FUNCTION: ENGINE 0x1010F1E0
// FUNCTION: ENGINE 0x1010F210
// FUNCTION: ENGINE 0x1010F2D0
// FUNCTION: ENGINE 0x1010F2F0
// FUNCTION: ENGINE 0x1010F320
// FUNCTION: ENGINE 0x1010F380
// FUNCTION: ENGINE 0x1010F940
// FUNCTION: ENGINE 0x1010FA80
// FUNCTION: ENGINE 0x101ABD50
// FUNCTION: ENGINE 0x101ABD80
// FUNCTION: ENGINE 0x101ABDB0
// FUNCTION: ENGINE 0x101ABDE0
// FUNCTION: ENGINE 0x101ABE10
// FUNCTION: ENGINE 0x101ABE40
// FUNCTION: ENGINE 0x101ABE70
// FUNCTION: ENGINE 0x101ABE80
// FUNCTION: ENGINE 0x101ABEB0
// FUNCTION: ENGINE 0x101ABEC0
// FUNCTION: ENGINE 0x101ABEF0
// FUNCTION: ENGINE 0x101ABF00
// FUNCTION: ENGINE 0x101ABF30
// FUNCTION: ENGINE 0x101ABF60
// FUNCTION: ENGINE 0x101ABF80
// FUNCTION: ENGINE 0x101ABFD0
// FUNCTION: ENGINE 0x101ABFE0
// FUNCTION: ENGINE 0x101AC010
// FUNCTION: ENGINE 0x101AC020
// FUNCTION: ENGINE 0x101AC050
// FUNCTION: ENGINE 0x101AC060
// FUNCTION: ENGINE 0x101AC090
// FUNCTION: ENGINE 0x101AC0D0
// FUNCTION: ENGINE 0x101AC0E0
// FUNCTION: ENGINE 0x101AC110
// FUNCTION: ENGINE 0x101AC130
// FUNCTION: ENGINE 0x101AC140
// FUNCTION: ENGINE 0x101AC170
// FUNCTION: ENGINE 0x101AC1A0
// FUNCTION: ENGINE 0x101AC1B0
// FUNCTION: ENGINE 0x101AC1F0
// FUNCTION: ENGINE 0x101AC200
// FUNCTION: ENGINE 0x101AC230
// FUNCTION: ENGINE 0x101AC250
// FUNCTION: ENGINE 0x101AC260
// FUNCTION: ENGINE 0x101AC290
// FUNCTION: ENGINE 0x101AC2C0
// FUNCTION: ENGINE 0x101AC2D0
// FUNCTION: ENGINE 0x101AC300
// FUNCTION: ENGINE 0x101AC330
// FUNCTION: ENGINE 0x101AC340
// FUNCTION: ENGINE 0x101AC380
// FUNCTION: ENGINE 0x101AC390
// FUNCTION: ENGINE 0x101AC3C0
// FUNCTION: ENGINE 0x101AC3E0
// FUNCTION: ENGINE 0x101AC3F0
// FUNCTION: ENGINE 0x101AC420
// FUNCTION: ENGINE 0x101AC450
// FUNCTION: ENGINE 0x101AC460
// FUNCTION: ENGINE 0x101AC490
// FUNCTION: ENGINE 0x101AC4B0
// FUNCTION: ENGINE 0x101ACBC0
// FUNCTION: ENGINE 0x101ACBF0
// FUNCTION: ENGINE 0x101ACC10
// FUNCTION: ENGINE 0x101ACC40
// FUNCTION: ENGINE 0x101ACC60
// FUNCTION: ENGINE 0x101ACC90
// FUNCTION: ENGINE 0x101ACCB0
// FUNCTION: ENGINE 0x101ACCE0
// FUNCTION: ENGINE 0x101ACD00
// FUNCTION: ENGINE 0x101ACD30
// FUNCTION: ENGINE 0x101ACD50
// FUNCTION: ENGINE 0x101ACDA0
// FUNCTION: ENGINE 0x101ACDF0
// FUNCTION: ENGINE 0x101ACE40
// FUNCTION: ENGINE 0x101ACE90
