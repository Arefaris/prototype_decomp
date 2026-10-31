// Fight items of the ai group: TargetHostileCondition, TargetClassCondition, TargetDefenseCondition, TargetAlertSubStateCondition, AutoTargetConditionGroupCondition, TargetCanSeeCondition, TargetAlertStateCondition, ChangedTargetSinceCondition, TargetableCondition, TargetConditionGroupCondition, TargetIsTankCondition, TargetIsPlayerCondition, TargetingCondition, TargetIsHelicopterCondition, AutoTargetingCondition (unit 0x1024F860 - 0x102527C0; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_target.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gTargetHostileConditionProperties;  // 0x11255BCC

			// FUNCTION: ENGINE 0x1024F860
			bool TargetHostileCondition::SetIsHostile(bool newValue)
			{
				isHostile = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024F9B0
			fight::Property* TargetHostileCondition::GetProperty(int index)
			{
				return gTargetHostileConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1024F9D0
			void TargetHostileCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetHostileConditionProperties);
			}

			// FUNCTION: ENGINE 0x1024F9E0
			TargetHostileCondition::TargetHostileCondition() : fight::Condition(0), isHostile(true)
			{
			}

			// FUNCTION: ENGINE 0x1024FA00
			TargetHostileCondition::~TargetHostileCondition()
			{
			}

			// FUNCTION: ENGINE 0x10251280
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetHostileCondition::RegisterProperties()
			{
				if (gTargetHostileConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<TargetHostileCondition>("isHostile", &TargetHostileCondition::SetIsHostile);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gTargetHostileConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10250FB0
			fight::ConditionFactory* CreateTargetHostileConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetHostileCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10251BA0
			void RegisterTargetHostileConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetHostileCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetClassConditionProperties;  // 0x11255BD0

			// FUNCTION: ENGINE 0x1024F870
			bool TargetClassCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024F880
			bool TargetClassCondition::SetTargetClass(int newValue)
			{
				targetClass = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024FA10
			fight::Property* TargetClassCondition::GetProperty(int index)
			{
				return gTargetClassConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1024FA30
			void TargetClassCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetClassConditionProperties);
			}

			// FUNCTION: ENGINE 0x1024FA40
			TargetClassCondition::TargetClassCondition() : fight::Condition(0), compare(0), targetClass(0)
			{
			}

			// FUNCTION: ENGINE 0x1024FA70
			TargetClassCondition::~TargetClassCondition()
			{
			}

			// FUNCTION: ENGINE 0x10251320
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetClassCondition::RegisterProperties()
			{
				if (gTargetClassConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<TargetClassCondition>("compare", motion::gClassNameConditionCompareTable, motion::gClassNameConditionCompareCount, &TargetClassCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<TargetClassCondition>("targetClass", motion::gAutoTargetTrackMinPriorityTargetClassTable, motion::gAutoTargetTrackMinPriorityTargetClassCount, &TargetClassCondition::SetTargetClass);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gTargetClassConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10250FE0
			fight::ConditionFactory* CreateTargetClassConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetClassCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10251BD0
			void RegisterTargetClassConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetClassCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetDefenseConditionProperties;  // 0x11255BD4

			// FUNCTION: ENGINE 0x1024F890
			bool TargetDefenseCondition::SetDefense(int newValue)
			{
				defense = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024F8A0
			bool TargetDefenseCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024F8B0
			bool TargetDefenseCondition::SetValue(float newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024FA80
			fight::Property* TargetDefenseCondition::GetProperty(int index)
			{
				return gTargetDefenseConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1024FAA0
			void TargetDefenseCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetDefenseConditionProperties);
			}

			// FUNCTION: ENGINE 0x1024FAB0
			TargetDefenseCondition::TargetDefenseCondition() : fight::Condition(0), value(0.0f), compare(4), defense(0)
			{
			}

			// FUNCTION: ENGINE 0x1024FAF0
			TargetDefenseCondition::~TargetDefenseCondition()
			{
			}

			// FUNCTION: ENGINE 0x10251420
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetDefenseCondition::RegisterProperties()
			{
				if (gTargetDefenseConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<TargetDefenseCondition>("defense", gTargetDefenseConditionDefenseTable, gTargetDefenseConditionDefenseCount, &TargetDefenseCondition::SetDefense);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<TargetDefenseCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &TargetDefenseCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TargetDefenseCondition>("value", &TargetDefenseCondition::SetValue);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gTargetDefenseConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10251010
			fight::ConditionFactory* CreateTargetDefenseConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetDefenseCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10251C00
			void RegisterTargetDefenseConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetDefenseCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetAlertSubStateConditionProperties;  // 0x11255BD8

			// FUNCTION: ENGINE 0x1024F8D0
			bool TargetAlertSubStateCondition::SetSubState(int newValue)
			{
				subState = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024FB00
			fight::Property* TargetAlertSubStateCondition::GetProperty(int index)
			{
				return gTargetAlertSubStateConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1024FB20
			void TargetAlertSubStateCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetAlertSubStateConditionProperties);
			}

			// FUNCTION: ENGINE 0x1024FB30
			TargetAlertSubStateCondition::TargetAlertSubStateCondition() : fight::Condition(0), subState(0)
			{
			}

			// FUNCTION: ENGINE 0x1024FB60
			TargetAlertSubStateCondition::~TargetAlertSubStateCondition()
			{
			}

			// FUNCTION: ENGINE 0x10251560
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetAlertSubStateCondition::RegisterProperties()
			{
				if (gTargetAlertSubStateConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<TargetAlertSubStateCondition>("subState", gTargetAlertSubStateConditionSubStateTable, gTargetAlertSubStateConditionSubStateCount, &TargetAlertSubStateCondition::SetSubState);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gTargetAlertSubStateConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10251040
			fight::ConditionFactory* CreateTargetAlertSubStateConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetAlertSubStateCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10251C30
			void RegisterTargetAlertSubStateConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetAlertSubStateCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gAutoTargetConditionGroupConditionProperties;  // 0x11255BDC

			// FUNCTION: ENGINE 0x1024F8E0
			fight::ConditionList* AutoTargetConditionGroupCondition::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x1024FB70
			fight::Property* AutoTargetConditionGroupCondition::GetProperty(int index)
			{
				return gAutoTargetConditionGroupConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1024FB90
			void AutoTargetConditionGroupCondition::ClearProperties()
			{
				fight::FreePropertyList(&gAutoTargetConditionGroupConditionProperties);
			}

			// FUNCTION: ENGINE 0x1024FBA0
			AutoTargetConditionGroupCondition::AutoTargetConditionGroupCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1024FBD0
			AutoTargetConditionGroupCondition::~AutoTargetConditionGroupCondition()
			{
			}

			// FUNCTION: ENGINE 0x10251610
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AutoTargetConditionGroupCondition::RegisterProperties()
			{
				if (gAutoTargetConditionGroupConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyConditionGroup<AutoTargetConditionGroupCondition>("conditions", &AutoTargetConditionGroupCondition::SetConditions);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gAutoTargetConditionGroupConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10251070
			fight::ConditionFactory* CreateAutoTargetConditionGroupConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AutoTargetConditionGroupCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10251C60
			void RegisterAutoTargetConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AutoTargetConditionGroupCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetCanSeeConditionProperties;  // 0x11255BE0

			// FUNCTION: ENGINE 0x1024F8F0
			bool TargetCanSeeCondition::SetSeen(bool newValue)
			{
				seen = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024F900
			bool TargetCanSeeCondition::SetSince(float newValue)
			{
				since = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024FBF0
			fight::Property* TargetCanSeeCondition::GetProperty(int index)
			{
				return gTargetCanSeeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1024FC10
			void TargetCanSeeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetCanSeeConditionProperties);
			}

			// FUNCTION: ENGINE 0x1024FC20
			TargetCanSeeCondition::TargetCanSeeCondition() : fight::Condition(0), since(0.0f), seen(false)
			{
			}

			// FUNCTION: ENGINE 0x1024FC50
			TargetCanSeeCondition::~TargetCanSeeCondition()
			{
			}

			// FUNCTION: ENGINE 0x102516B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetCanSeeCondition::RegisterProperties()
			{
				if (gTargetCanSeeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<TargetCanSeeCondition>("seen", &TargetCanSeeCondition::SetSeen);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TargetCanSeeCondition>("since", &TargetCanSeeCondition::SetSince);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gTargetCanSeeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102510A0
			fight::ConditionFactory* CreateTargetCanSeeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetCanSeeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10251C90
			void RegisterTargetCanSeeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetCanSeeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetAlertStateConditionProperties;  // 0x11255BE4

			// FUNCTION: ENGINE 0x1024F920
			bool TargetAlertStateCondition::SetState(int newValue)
			{
				state = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024FC60
			fight::Property* TargetAlertStateCondition::GetProperty(int index)
			{
				return gTargetAlertStateConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1024FC80
			void TargetAlertStateCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetAlertStateConditionProperties);
			}

			// FUNCTION: ENGINE 0x1024FC90
			TargetAlertStateCondition::TargetAlertStateCondition() : fight::Condition(0), state(0)
			{
			}

			// FUNCTION: ENGINE 0x1024FCC0
			TargetAlertStateCondition::~TargetAlertStateCondition()
			{
			}

			// FUNCTION: ENGINE 0x10251790
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetAlertStateCondition::RegisterProperties()
			{
				if (gTargetAlertStateConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<TargetAlertStateCondition>("state", gTargetAlertStateConditionStateTable, gTargetAlertStateConditionStateCount, &TargetAlertStateCondition::SetState);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gTargetAlertStateConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102510D0
			fight::ConditionFactory* CreateTargetAlertStateConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetAlertStateCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10251CC0
			void RegisterTargetAlertStateConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetAlertStateCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gChangedTargetSinceConditionProperties;  // 0x11255BE8

			// FUNCTION: ENGINE 0x10250090
			bool ChangedTargetSinceCondition::SetTimer(const fight::Name& newValue)
			{
				timer = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024F930
			bool ChangedTargetSinceCondition::SetTime(float newValue)
			{
				time = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024FCD0
			fight::Property* ChangedTargetSinceCondition::GetProperty(int index)
			{
				return gChangedTargetSinceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1024FCF0
			void ChangedTargetSinceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gChangedTargetSinceConditionProperties);
			}

			// FUNCTION: ENGINE 0x10250200
			ChangedTargetSinceCondition::ChangedTargetSinceCondition() : fight::Condition(0), time(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x10250230
			ChangedTargetSinceCondition::~ChangedTargetSinceCondition()
			{
			}

			// FUNCTION: ENGINE 0x10252280
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ChangedTargetSinceCondition::RegisterProperties()
			{
				if (gChangedTargetSinceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<ChangedTargetSinceCondition>("timer", &ChangedTargetSinceCondition::SetTimer);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ChangedTargetSinceCondition>("time", &ChangedTargetSinceCondition::SetTime);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gChangedTargetSinceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10251100
			fight::ConditionFactory* CreateChangedTargetSinceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ChangedTargetSinceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10251CF0
			void RegisterChangedTargetSinceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ChangedTargetSinceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetableConditionProperties;  // 0x11255BEC

			// FUNCTION: ENGINE 0x1024F950
			bool TargetableCondition::SetIsTargetable(bool newValue)
			{
				isTargetable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024FD00
			fight::Property* TargetableCondition::GetProperty(int index)
			{
				return gTargetableConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1024FD20
			void TargetableCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetableConditionProperties);
			}

			// FUNCTION: ENGINE 0x1024FD30
			TargetableCondition::TargetableCondition() : fight::Condition(0), isTargetable(true)
			{
			}

			// FUNCTION: ENGINE 0x1024FD50
			TargetableCondition::~TargetableCondition()
			{
			}

			// FUNCTION: ENGINE 0x10251840
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetableCondition::RegisterProperties()
			{
				if (gTargetableConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<TargetableCondition>("isTargetable", &TargetableCondition::SetIsTargetable);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gTargetableConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10251130
			fight::ConditionFactory* CreateTargetableConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetableCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10251D20
			void RegisterTargetableConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetableCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetConditionGroupConditionProperties;  // 0x11255BF0

			// FUNCTION: ENGINE 0x1024F960
			fight::ConditionList* TargetConditionGroupCondition::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x1024FD60
			fight::Property* TargetConditionGroupCondition::GetProperty(int index)
			{
				return gTargetConditionGroupConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1024FD80
			void TargetConditionGroupCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetConditionGroupConditionProperties);
			}

			// FUNCTION: ENGINE 0x1024FD90
			TargetConditionGroupCondition::TargetConditionGroupCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1024FDC0
			TargetConditionGroupCondition::~TargetConditionGroupCondition()
			{
			}

			// FUNCTION: ENGINE 0x102518E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetConditionGroupCondition::RegisterProperties()
			{
				if (gTargetConditionGroupConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyConditionGroup<TargetConditionGroupCondition>("conditions", &TargetConditionGroupCondition::SetConditions);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gTargetConditionGroupConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10251160
			fight::ConditionFactory* CreateTargetConditionGroupConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetConditionGroupCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10251D50
			void RegisterTargetConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetConditionGroupCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetIsTankConditionProperties;  // 0x11255BF4

			// FUNCTION: ENGINE 0x1024FE40
			fight::Property* TargetIsTankCondition::GetProperty(int index)
			{
				return gTargetIsTankConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1024FE60
			void TargetIsTankCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetIsTankConditionProperties);
			}

			// FUNCTION: ENGINE 0x1024FE70
			TargetIsTankCondition::TargetIsTankCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1024FE90
			TargetIsTankCondition::~TargetIsTankCondition()
			{
			}

			// FUNCTION: ENGINE 0x1024FDE0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetIsTankCondition::RegisterProperties()
			{
				if (gTargetIsTankConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gTargetIsTankConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10251190
			fight::ConditionFactory* CreateTargetIsTankConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetIsTankCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10251D80
			void RegisterTargetIsTankConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetIsTankCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetIsPlayerConditionProperties;  // 0x11255BF8

			// FUNCTION: ENGINE 0x1024F970
			bool TargetIsPlayerCondition::SetIs(bool newValue)
			{
				is = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024FEA0
			fight::Property* TargetIsPlayerCondition::GetProperty(int index)
			{
				return gTargetIsPlayerConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1024FEC0
			void TargetIsPlayerCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetIsPlayerConditionProperties);
			}

			// FUNCTION: ENGINE 0x1024FED0
			TargetIsPlayerCondition::TargetIsPlayerCondition() : fight::Condition(0), is(true)
			{
			}

			// FUNCTION: ENGINE 0x1024FEF0
			TargetIsPlayerCondition::~TargetIsPlayerCondition()
			{
			}

			// FUNCTION: ENGINE 0x10251980
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetIsPlayerCondition::RegisterProperties()
			{
				if (gTargetIsPlayerConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<TargetIsPlayerCondition>("is", &TargetIsPlayerCondition::SetIs);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gTargetIsPlayerConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102511C0
			fight::ConditionFactory* CreateTargetIsPlayerConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetIsPlayerCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10251DB0
			void RegisterTargetIsPlayerConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetIsPlayerCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetingConditionProperties;  // 0x11255BFC

			// FUNCTION: ENGINE 0x1024F980
			bool TargetingCondition::SetIsTargeting(bool newValue)
			{
				isTargeting = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024F990
			bool TargetingCondition::SetIncludeAutoTarget(bool newValue)
			{
				includeAutoTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1024FF00
			fight::Property* TargetingCondition::GetProperty(int index)
			{
				return gTargetingConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1024FF20
			void TargetingCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetingConditionProperties);
			}

			// FUNCTION: ENGINE 0x1024FF30
			TargetingCondition::TargetingCondition() : fight::Condition(0), includeAutoTarget(true), isTargeting(true)
			{
			}

			// FUNCTION: ENGINE 0x1024FF60
			TargetingCondition::~TargetingCondition()
			{
			}

			// FUNCTION: ENGINE 0x10251A20
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetingCondition::RegisterProperties()
			{
				if (gTargetingConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<TargetingCondition>("isTargeting", &TargetingCondition::SetIsTargeting);
					properties[0] = property;
					property = new fight::PropertyBool<TargetingCondition>("includeAutoTarget", &TargetingCondition::SetIncludeAutoTarget);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gTargetingConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x102511F0
			fight::ConditionFactory* CreateTargetingConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetingCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10251DE0
			void RegisterTargetingConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetingCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetIsHelicopterConditionProperties;  // 0x11255C00

			// FUNCTION: ENGINE 0x1024FFD0
			fight::Property* TargetIsHelicopterCondition::GetProperty(int index)
			{
				return gTargetIsHelicopterConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1024FFF0
			void TargetIsHelicopterCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetIsHelicopterConditionProperties);
			}

			// FUNCTION: ENGINE 0x10250000
			TargetIsHelicopterCondition::TargetIsHelicopterCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x10250020
			TargetIsHelicopterCondition::~TargetIsHelicopterCondition()
			{
			}

			// FUNCTION: ENGINE 0x1024FF70
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetIsHelicopterCondition::RegisterProperties()
			{
				if (gTargetIsHelicopterConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gTargetIsHelicopterConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10251220
			fight::ConditionFactory* CreateTargetIsHelicopterConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetIsHelicopterCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10251E10
			void RegisterTargetIsHelicopterConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetIsHelicopterCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gAutoTargetingConditionProperties;  // 0x11255C04

			// FUNCTION: ENGINE 0x1024F9A0
			bool AutoTargetingCondition::SetIsAutoTargeting(bool newValue)
			{
				isAutoTargeting = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10250030
			fight::Property* AutoTargetingCondition::GetProperty(int index)
			{
				return gAutoTargetingConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10250050
			void AutoTargetingCondition::ClearProperties()
			{
				fight::FreePropertyList(&gAutoTargetingConditionProperties);
			}

			// FUNCTION: ENGINE 0x10250060
			AutoTargetingCondition::AutoTargetingCondition() : fight::Condition(0), isAutoTargeting(true)
			{
			}

			// FUNCTION: ENGINE 0x10250080
			AutoTargetingCondition::~AutoTargetingCondition()
			{
			}

			// FUNCTION: ENGINE 0x10251B00
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AutoTargetingCondition::RegisterProperties()
			{
				if (gAutoTargetingConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<AutoTargetingCondition>("isAutoTargeting", &AutoTargetingCondition::SetIsAutoTargeting);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gAutoTargetingConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10251250
			fight::ConditionFactory* CreateAutoTargetingConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AutoTargetingCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10251E40
			void RegisterAutoTargetingConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<AutoTargetingCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyBool<TargetHostileCondition>;
			template class fight::ConditionFactoryTemplate<TargetHostileCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetHostileCondition>;
			template class fight::PropertyEnumConstList<TargetClassCondition>;
			template class fight::ConditionFactoryTemplate<TargetClassCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetClassCondition>;
			template class fight::PropertyEnumConstList<TargetDefenseCondition>;
			template class fight::PropertyFloatConstRange<TargetDefenseCondition>;
			template class fight::ConditionFactoryTemplate<TargetDefenseCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetDefenseCondition>;
			template class fight::PropertyEnumConstList<TargetAlertSubStateCondition>;
			template class fight::ConditionFactoryTemplate<TargetAlertSubStateCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetAlertSubStateCondition>;
			template class fight::PropertyConditionGroup<AutoTargetConditionGroupCondition>;
			template class fight::ConditionFactoryTemplate<AutoTargetConditionGroupCondition>;
			template class fight::ConditionFactoryCasterTemplate<AutoTargetConditionGroupCondition>;
			template class fight::PropertyBool<TargetCanSeeCondition>;
			template class fight::PropertyFloatConstRange<TargetCanSeeCondition>;
			template class fight::ConditionFactoryTemplate<TargetCanSeeCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetCanSeeCondition>;
			template class fight::PropertyEnumConstList<TargetAlertStateCondition>;
			template class fight::ConditionFactoryTemplate<TargetAlertStateCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetAlertStateCondition>;
			template class fight::PropertyName<ChangedTargetSinceCondition>;
			template class fight::PropertyFloatConstRange<ChangedTargetSinceCondition>;
			template class fight::ConditionFactoryTemplate<ChangedTargetSinceCondition>;
			template class fight::ConditionFactoryCasterTemplate<ChangedTargetSinceCondition>;
			template class fight::PropertyBool<TargetableCondition>;
			template class fight::ConditionFactoryTemplate<TargetableCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetableCondition>;
			template class fight::PropertyConditionGroup<TargetConditionGroupCondition>;
			template class fight::ConditionFactoryTemplate<TargetConditionGroupCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetConditionGroupCondition>;
			template class fight::ConditionFactoryTemplate<TargetIsTankCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetIsTankCondition>;
			template class fight::PropertyBool<TargetIsPlayerCondition>;
			template class fight::ConditionFactoryTemplate<TargetIsPlayerCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetIsPlayerCondition>;
			template class fight::PropertyBool<TargetingCondition>;
			template class fight::ConditionFactoryTemplate<TargetingCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetingCondition>;
			template class fight::ConditionFactoryTemplate<TargetIsHelicopterCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetIsHelicopterCondition>;
			template class fight::PropertyBool<AutoTargetingCondition>;
			template class fight::ConditionFactoryTemplate<AutoTargetingCondition>;
			template class fight::ConditionFactoryCasterTemplate<AutoTargetingCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102500B0
// FUNCTION: ENGINE 0x102500E0
// FUNCTION: ENGINE 0x10250110
// FUNCTION: ENGINE 0x10250140
// FUNCTION: ENGINE 0x10250170
// FUNCTION: ENGINE 0x102501A0
// FUNCTION: ENGINE 0x102501D0
// FUNCTION: ENGINE 0x10250240
// FUNCTION: ENGINE 0x10250270
// FUNCTION: ENGINE 0x102502A0
// FUNCTION: ENGINE 0x102502D0
// FUNCTION: ENGINE 0x10250300
// FUNCTION: ENGINE 0x10250330
// FUNCTION: ENGINE 0x10250360
// FUNCTION: ENGINE 0x10250390
// FUNCTION: ENGINE 0x102503A0
// FUNCTION: ENGINE 0x102503D0
// FUNCTION: ENGINE 0x102503E0
// FUNCTION: ENGINE 0x10250410
// FUNCTION: ENGINE 0x10250420
// FUNCTION: ENGINE 0x10250450
// FUNCTION: ENGINE 0x10250460
// FUNCTION: ENGINE 0x10250490
// FUNCTION: ENGINE 0x102504A0
// FUNCTION: ENGINE 0x102504D0
// FUNCTION: ENGINE 0x102504E0
// FUNCTION: ENGINE 0x10250510
// FUNCTION: ENGINE 0x10250520
// FUNCTION: ENGINE 0x10250550
// FUNCTION: ENGINE 0x10250560
// FUNCTION: ENGINE 0x10250590
// FUNCTION: ENGINE 0x102505A0
// FUNCTION: ENGINE 0x102505D0
// FUNCTION: ENGINE 0x102505E0
// FUNCTION: ENGINE 0x10250610
// FUNCTION: ENGINE 0x10250620
// FUNCTION: ENGINE 0x10250650
// FUNCTION: ENGINE 0x10250680
// FUNCTION: ENGINE 0x102506A0
// FUNCTION: ENGINE 0x102506F0
// FUNCTION: ENGINE 0x10250700
// FUNCTION: ENGINE 0x10250730
// FUNCTION: ENGINE 0x10250740
// FUNCTION: ENGINE 0x10250770
// FUNCTION: ENGINE 0x10250780
// FUNCTION: ENGINE 0x102507B0
// FUNCTION: ENGINE 0x102507E0
// FUNCTION: ENGINE 0x10250800
// FUNCTION: ENGINE 0x10250850
// FUNCTION: ENGINE 0x10250860
// FUNCTION: ENGINE 0x10250890
// FUNCTION: ENGINE 0x102508C0
// FUNCTION: ENGINE 0x102508F0
// FUNCTION: ENGINE 0x10250910
// FUNCTION: ENGINE 0x10250920
// FUNCTION: ENGINE 0x10250960
// FUNCTION: ENGINE 0x10250970
// FUNCTION: ENGINE 0x102509A0
// FUNCTION: ENGINE 0x102509C0
// FUNCTION: ENGINE 0x102509D0
// FUNCTION: ENGINE 0x10250A10
// FUNCTION: ENGINE 0x10250A20
// FUNCTION: ENGINE 0x10250A50
// FUNCTION: ENGINE 0x10250A70
// FUNCTION: ENGINE 0x10250A80
// FUNCTION: ENGINE 0x10250AB0
// FUNCTION: ENGINE 0x10250AE0
// FUNCTION: ENGINE 0x10250AF0
// FUNCTION: ENGINE 0x10250B30
// FUNCTION: ENGINE 0x10250B40
// FUNCTION: ENGINE 0x10250B70
// FUNCTION: ENGINE 0x10250B90
// FUNCTION: ENGINE 0x10250BA0
// FUNCTION: ENGINE 0x10250BD0
// FUNCTION: ENGINE 0x10250BF0
// FUNCTION: ENGINE 0x10250C20
// FUNCTION: ENGINE 0x10250C40
// FUNCTION: ENGINE 0x10250C50
// FUNCTION: ENGINE 0x10250C80
// FUNCTION: ENGINE 0x10250CB0
// FUNCTION: ENGINE 0x10250CC0
// FUNCTION: ENGINE 0x10250D00
// FUNCTION: ENGINE 0x10250D10
// FUNCTION: ENGINE 0x10250D40
// FUNCTION: ENGINE 0x10250D60
// FUNCTION: ENGINE 0x10250D70
// FUNCTION: ENGINE 0x10250DA0
// FUNCTION: ENGINE 0x10250DD0
// FUNCTION: ENGINE 0x10250DE0
// FUNCTION: ENGINE 0x10250E10
// FUNCTION: ENGINE 0x10250E30
// FUNCTION: ENGINE 0x10250E40
// FUNCTION: ENGINE 0x10250E70
// FUNCTION: ENGINE 0x10250E90
// FUNCTION: ENGINE 0x10250EC0
// FUNCTION: ENGINE 0x10250EE0
// FUNCTION: ENGINE 0x10250EF0
// FUNCTION: ENGINE 0x10250F20
// FUNCTION: ENGINE 0x10250F40
// FUNCTION: ENGINE 0x10250F50
// FUNCTION: ENGINE 0x10250F80
// FUNCTION: ENGINE 0x10250FA0
// FUNCTION: ENGINE 0x10251E70
// FUNCTION: ENGINE 0x10251EA0
// FUNCTION: ENGINE 0x10251EC0
// FUNCTION: ENGINE 0x10251EF0
// FUNCTION: ENGINE 0x10251F10
// FUNCTION: ENGINE 0x10251F40
// FUNCTION: ENGINE 0x10251F60
// FUNCTION: ENGINE 0x10251F90
// FUNCTION: ENGINE 0x10251FB0
// FUNCTION: ENGINE 0x10251FE0
// FUNCTION: ENGINE 0x10252000
// FUNCTION: ENGINE 0x10252030
// FUNCTION: ENGINE 0x10252050
// FUNCTION: ENGINE 0x10252080
// FUNCTION: ENGINE 0x102520A0
// FUNCTION: ENGINE 0x102520D0
// FUNCTION: ENGINE 0x102520F0
// FUNCTION: ENGINE 0x10252120
// FUNCTION: ENGINE 0x10252140
// FUNCTION: ENGINE 0x10252170
// FUNCTION: ENGINE 0x10252190
// FUNCTION: ENGINE 0x102521C0
// FUNCTION: ENGINE 0x102521E0
// FUNCTION: ENGINE 0x10252210
// FUNCTION: ENGINE 0x10252230
// FUNCTION: ENGINE 0x10252260
// FUNCTION: ENGINE 0x10252360
// FUNCTION: ENGINE 0x102523B0
// FUNCTION: ENGINE 0x10252400
// FUNCTION: ENGINE 0x10252450
// FUNCTION: ENGINE 0x102524A0
// FUNCTION: ENGINE 0x102524F0
// FUNCTION: ENGINE 0x10252540
// FUNCTION: ENGINE 0x10252590
// FUNCTION: ENGINE 0x102525E0
// FUNCTION: ENGINE 0x10252630
// FUNCTION: ENGINE 0x10252680
// FUNCTION: ENGINE 0x102526D0
// FUNCTION: ENGINE 0x10252720
// FUNCTION: ENGINE 0x10252750
// FUNCTION: ENGINE 0x10252770
