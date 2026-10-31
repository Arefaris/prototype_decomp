// Fight items of the motion group: GrabbedCondition, GrabbedConditionGroupCondition, HaveGrabTargetCondition, GrabSlotObjectTemplateCondition, GrabbedClassNameCondition, IsGrabbableCondition, GrabbedGrabbableClassCondition, GrabbedBySlotCondition, GrabbedByPlayerCondition, GrabSlotClassNameCondition, GrabSlotDistanceCondition, GrabTargetConditionGroupCondition, GrabSlotGrabbableClassCondition, GrabbableSizeCondition, GrabSlotConditionGroupCondition, TargetIsGrabTargetCondition, GrabSlotCondition, TargetCanGrabCondition, GrabSlotMassCondition, GrabbableClassCondition, GrabTargetAngleCondition, GrabTargetDistanceCondition (unit 0x10163FA0 - 0x10169790; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_grabcondition.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gGrabbedConditionProperties;  // 0x11254570

			// FUNCTION: ENGINE 0x10163FA0
			bool GrabbedCondition::SetIsGrabbed(bool newValue)
			{
				isGrabbed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164200
			fight::Property* GrabbedCondition::GetProperty(int index)
			{
				return gGrabbedConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10164220
			void GrabbedCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGrabbedConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164230
			GrabbedCondition::GrabbedCondition() : fight::Condition(0), isGrabbed(true)
			{
			}

			// FUNCTION: ENGINE 0x10164250
			GrabbedCondition::~GrabbedCondition()
			{
			}

			// FUNCTION: ENGINE 0x10166AC0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabbedCondition::RegisterProperties()
			{
				if (gGrabbedConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<GrabbedCondition>("isGrabbed", &GrabbedCondition::SetIsGrabbed);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gGrabbedConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101666A0
			fight::ConditionFactory* CreateGrabbedConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabbedCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10167190
			void RegisterGrabbedConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabbedCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGrabbedConditionGroupConditionProperties;  // 0x11254574

			// FUNCTION: ENGINE 0x10163FB0
			fight::ConditionList* GrabbedConditionGroupCondition::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x10164260
			fight::Property* GrabbedConditionGroupCondition::GetProperty(int index)
			{
				return gGrabbedConditionGroupConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10164280
			void GrabbedConditionGroupCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGrabbedConditionGroupConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164290
			GrabbedConditionGroupCondition::GrabbedConditionGroupCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x101642C0
			GrabbedConditionGroupCondition::~GrabbedConditionGroupCondition()
			{
			}

			// FUNCTION: ENGINE 0x10166B60
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabbedConditionGroupCondition::RegisterProperties()
			{
				if (gGrabbedConditionGroupConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyConditionGroup<GrabbedConditionGroupCondition>("conditions", &GrabbedConditionGroupCondition::SetConditions);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gGrabbedConditionGroupConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101666D0
			fight::ConditionFactory* CreateGrabbedConditionGroupConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabbedConditionGroupCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101671C0
			void RegisterGrabbedConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabbedConditionGroupCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gHaveGrabTargetConditionProperties;  // 0x11254578

			// FUNCTION: ENGINE 0x10163FC0
			bool HaveGrabTargetCondition::SetHave(bool newValue)
			{
				have = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10163FD0
			bool HaveGrabTargetCondition::SetUseStoredProperties(bool newValue)
			{
				useStoredProperties = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10163FE0
			bool HaveGrabTargetCondition::SetCollideWith(int newValue)
			{
				collideWith = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10163FF0
			bool HaveGrabTargetCondition::SetIgnore(int newValue)
			{
				ignore = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164840
			bool HaveGrabTargetCondition::SetValidGrabbableClass(const fight::Name& newValue)
			{
				validGrabbableClass = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164000
			bool HaveGrabTargetCondition::SetRange(float newValue)
			{
				range = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101642E0
			fight::Property* HaveGrabTargetCondition::GetProperty(int index)
			{
				return gHaveGrabTargetConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10164300
			void HaveGrabTargetCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHaveGrabTargetConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164AA0
			HaveGrabTargetCondition::HaveGrabTargetCondition() : fight::Condition(0), range(0.0f), collideWith(0), ignore(67108864), have(true), useStoredProperties(true)
			{
			}

			// FUNCTION: ENGINE 0x10164AF0
			HaveGrabTargetCondition::~HaveGrabTargetCondition()
			{
			}

			// FUNCTION: ENGINE 0x10167E00
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HaveGrabTargetCondition::RegisterProperties()
			{
				if (gHaveGrabTargetConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<HaveGrabTargetCondition>("have", &HaveGrabTargetCondition::SetHave);
					properties[0] = property;
					property = new fight::PropertyBool<HaveGrabTargetCondition>("useStoredProperties", &HaveGrabTargetCondition::SetUseStoredProperties);
					properties[1] = property;
					property = new fight::PropertyBitfieldConstList<HaveGrabTargetCondition>("collideWith", gDetectObbCollisionConditionCollideWithTable, gDetectObbCollisionConditionCollideWithCount, &HaveGrabTargetCondition::SetCollideWith);
					properties[2] = property;
					property = new fight::PropertyBitfieldConstList<HaveGrabTargetCondition>("ignore", gDetectObbCollisionConditionCollideWithTable, gDetectObbCollisionConditionCollideWithCount, &HaveGrabTargetCondition::SetIgnore);
					properties[3] = property;
					property = new fight::PropertyName<HaveGrabTargetCondition>("validGrabbableClass", &HaveGrabTargetCondition::SetValidGrabbableClass);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<HaveGrabTargetCondition>("range", &HaveGrabTargetCondition::SetRange);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gHaveGrabTargetConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10166700
			fight::ConditionFactory* CreateHaveGrabTargetConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HaveGrabTargetCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101671F0
			void RegisterHaveGrabTargetConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HaveGrabTargetCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGrabSlotObjectTemplateConditionProperties;  // 0x1125457C

			// FUNCTION: ENGINE 0x10164860
			bool GrabSlotObjectTemplateCondition::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164020
			bool GrabSlotObjectTemplateCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164880
			bool GrabSlotObjectTemplateCondition::SetObjectTemplate(const fight::Name& newValue)
			{
				objectTemplate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164310
			fight::Property* GrabSlotObjectTemplateCondition::GetProperty(int index)
			{
				return gGrabSlotObjectTemplateConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10164330
			void GrabSlotObjectTemplateCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGrabSlotObjectTemplateConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164B00
			GrabSlotObjectTemplateCondition::GrabSlotObjectTemplateCondition() : fight::Condition(0), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10164B40
			GrabSlotObjectTemplateCondition::~GrabSlotObjectTemplateCondition()
			{
			}

			// FUNCTION: ENGINE 0x10168000
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabSlotObjectTemplateCondition::RegisterProperties()
			{
				if (gGrabSlotObjectTemplateConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyNameList<GrabSlotObjectTemplateCondition>("grabSlot", &GrabSlotObjectTemplateCondition::SetGrabSlot);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<GrabSlotObjectTemplateCondition>("compare", gClassNameConditionCompareTable, gClassNameConditionCompareCount, &GrabSlotObjectTemplateCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyName<GrabSlotObjectTemplateCondition>("objectTemplate", &GrabSlotObjectTemplateCondition::SetObjectTemplate);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gGrabSlotObjectTemplateConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10166730
			fight::ConditionFactory* CreateGrabSlotObjectTemplateConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabSlotObjectTemplateCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10167220
			void RegisterGrabSlotObjectTemplateConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabSlotObjectTemplateCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGrabbedClassNameConditionProperties;  // 0x11254580

			// FUNCTION: ENGINE 0x10164030
			bool GrabbedClassNameCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101648A0
			bool GrabbedClassNameCondition::SetClassName(const fight::Name& newValue)
			{
				className = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164340
			fight::Property* GrabbedClassNameCondition::GetProperty(int index)
			{
				return gGrabbedClassNameConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10164360
			void GrabbedClassNameCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGrabbedClassNameConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164B50
			GrabbedClassNameCondition::GrabbedClassNameCondition() : fight::Condition(0), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10164B80
			GrabbedClassNameCondition::~GrabbedClassNameCondition()
			{
			}

			// FUNCTION: ENGINE 0x10168130
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabbedClassNameCondition::RegisterProperties()
			{
				if (gGrabbedClassNameConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<GrabbedClassNameCondition>("compare", gClassNameConditionCompareTable, gClassNameConditionCompareCount, &GrabbedClassNameCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyName<GrabbedClassNameCondition>("className", &GrabbedClassNameCondition::SetClassName);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gGrabbedClassNameConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10166760
			fight::ConditionFactory* CreateGrabbedClassNameConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabbedClassNameCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10167250
			void RegisterGrabbedClassNameConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabbedClassNameCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gIsGrabbableConditionProperties;  // 0x11254584

			// FUNCTION: ENGINE 0x10164040
			bool IsGrabbableCondition::SetIs(bool newValue)
			{
				is = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164370
			fight::Property* IsGrabbableCondition::GetProperty(int index)
			{
				return gIsGrabbableConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10164390
			void IsGrabbableCondition::ClearProperties()
			{
				fight::FreePropertyList(&gIsGrabbableConditionProperties);
			}

			// FUNCTION: ENGINE 0x101643A0
			IsGrabbableCondition::IsGrabbableCondition() : fight::Condition(0), is(true)
			{
			}

			// FUNCTION: ENGINE 0x101643C0
			IsGrabbableCondition::~IsGrabbableCondition()
			{
			}

			// FUNCTION: ENGINE 0x10166C00
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void IsGrabbableCondition::RegisterProperties()
			{
				if (gIsGrabbableConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<IsGrabbableCondition>("is", &IsGrabbableCondition::SetIs);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gIsGrabbableConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10166790
			fight::ConditionFactory* CreateIsGrabbableConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsGrabbableCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10167280
			void RegisterIsGrabbableConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<IsGrabbableCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGrabbedGrabbableClassConditionProperties;  // 0x11254588

			// FUNCTION: ENGINE 0x10164050
			bool GrabbedGrabbableClassCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101648C0
			bool GrabbedGrabbableClassCondition::SetGrabbableClass(const fight::Name& newValue)
			{
				grabbableClass = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101643D0
			fight::Property* GrabbedGrabbableClassCondition::GetProperty(int index)
			{
				return gGrabbedGrabbableClassConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101643F0
			void GrabbedGrabbableClassCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGrabbedGrabbableClassConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164BC0
			GrabbedGrabbableClassCondition::GrabbedGrabbableClassCondition() : fight::Condition(0), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10164BF0
			GrabbedGrabbableClassCondition::~GrabbedGrabbableClassCondition()
			{
			}

			// FUNCTION: ENGINE 0x10168220
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabbedGrabbableClassCondition::RegisterProperties()
			{
				if (gGrabbedGrabbableClassConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<GrabbedGrabbableClassCondition>("compare", gClassNameConditionCompareTable, gClassNameConditionCompareCount, &GrabbedGrabbableClassCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyName<GrabbedGrabbableClassCondition>("grabbableClass", &GrabbedGrabbableClassCondition::SetGrabbableClass);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gGrabbedGrabbableClassConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101667C0
			fight::ConditionFactory* CreateGrabbedGrabbableClassConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabbedGrabbableClassCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101672B0
			void RegisterGrabbedGrabbableClassConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabbedGrabbableClassCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGrabbedBySlotConditionProperties;  // 0x1125458C

			// FUNCTION: ENGINE 0x10164060
			bool GrabbedBySlotCondition::SetIsGrabbed(bool newValue)
			{
				isGrabbed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101648E0
			bool GrabbedBySlotCondition::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164400
			fight::Property* GrabbedBySlotCondition::GetProperty(int index)
			{
				return gGrabbedBySlotConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10164420
			void GrabbedBySlotCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGrabbedBySlotConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164C00
			GrabbedBySlotCondition::GrabbedBySlotCondition() : fight::Condition(0), isGrabbed(true)
			{
			}

			// FUNCTION: ENGINE 0x10164C30
			GrabbedBySlotCondition::~GrabbedBySlotCondition()
			{
			}

			// FUNCTION: ENGINE 0x10168310
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabbedBySlotCondition::RegisterProperties()
			{
				if (gGrabbedBySlotConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<GrabbedBySlotCondition>("isGrabbed", &GrabbedBySlotCondition::SetIsGrabbed);
					properties[0] = property;
					property = new fight::PropertyNameList<GrabbedBySlotCondition>("grabSlot", &GrabbedBySlotCondition::SetGrabSlot);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gGrabbedBySlotConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101667F0
			fight::ConditionFactory* CreateGrabbedBySlotConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabbedBySlotCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101672E0
			void RegisterGrabbedBySlotConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabbedBySlotCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGrabbedByPlayerConditionProperties;  // 0x11254590

			// FUNCTION: ENGINE 0x10164070
			bool GrabbedByPlayerCondition::SetIsGrabbedByPlayer(bool newValue)
			{
				isGrabbedByPlayer = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164430
			fight::Property* GrabbedByPlayerCondition::GetProperty(int index)
			{
				return gGrabbedByPlayerConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10164450
			void GrabbedByPlayerCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGrabbedByPlayerConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164460
			GrabbedByPlayerCondition::GrabbedByPlayerCondition() : fight::Condition(0), isGrabbedByPlayer(true)
			{
			}

			// FUNCTION: ENGINE 0x10164480
			GrabbedByPlayerCondition::~GrabbedByPlayerCondition()
			{
			}

			// FUNCTION: ENGINE 0x10166CA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabbedByPlayerCondition::RegisterProperties()
			{
				if (gGrabbedByPlayerConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<GrabbedByPlayerCondition>("isGrabbedByPlayer", &GrabbedByPlayerCondition::SetIsGrabbedByPlayer);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gGrabbedByPlayerConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10166820
			fight::ConditionFactory* CreateGrabbedByPlayerConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabbedByPlayerCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10167310
			void RegisterGrabbedByPlayerConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabbedByPlayerCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGrabSlotClassNameConditionProperties;  // 0x11254594

			// FUNCTION: ENGINE 0x10164900
			bool GrabSlotClassNameCondition::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164080
			bool GrabSlotClassNameCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164920
			bool GrabSlotClassNameCondition::SetClassName(const fight::Name& newValue)
			{
				className = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164490
			fight::Property* GrabSlotClassNameCondition::GetProperty(int index)
			{
				return gGrabSlotClassNameConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101644B0
			void GrabSlotClassNameCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGrabSlotClassNameConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164C70
			GrabSlotClassNameCondition::GrabSlotClassNameCondition() : fight::Condition(0), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10164CB0
			GrabSlotClassNameCondition::~GrabSlotClassNameCondition()
			{
			}

			// FUNCTION: ENGINE 0x101683F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabSlotClassNameCondition::RegisterProperties()
			{
				if (gGrabSlotClassNameConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyNameList<GrabSlotClassNameCondition>("grabSlot", &GrabSlotClassNameCondition::SetGrabSlot);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<GrabSlotClassNameCondition>("compare", gClassNameConditionCompareTable, gClassNameConditionCompareCount, &GrabSlotClassNameCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyName<GrabSlotClassNameCondition>("className", &GrabSlotClassNameCondition::SetClassName);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gGrabSlotClassNameConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10166850
			fight::ConditionFactory* CreateGrabSlotClassNameConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabSlotClassNameCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10167340
			void RegisterGrabSlotClassNameConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabSlotClassNameCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGrabSlotDistanceConditionProperties;  // 0x11254598

			// FUNCTION: ENGINE 0x10164940
			bool GrabSlotDistanceCondition::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164090
			bool GrabSlotDistanceCondition::SetDirection(int newValue)
			{
				direction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101640A0
			bool GrabSlotDistanceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101640B0
			bool GrabSlotDistanceCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101644C0
			fight::Property* GrabSlotDistanceCondition::GetProperty(int index)
			{
				return gGrabSlotDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101644E0
			void GrabSlotDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGrabSlotDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164CC0
			GrabSlotDistanceCondition::GrabSlotDistanceCondition() : fight::Condition(0), distance(2e+01f), compare(4), direction(0)
			{
			}

			// FUNCTION: ENGINE 0x10164D10
			GrabSlotDistanceCondition::~GrabSlotDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x10168520
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabSlotDistanceCondition::RegisterProperties()
			{
				if (gGrabSlotDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyNameList<GrabSlotDistanceCondition>("grabSlot", &GrabSlotDistanceCondition::SetGrabSlot);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<GrabSlotDistanceCondition>("direction", gCrowdPositionConditionDirectionTable, gCrowdPositionConditionDirectionCount, &GrabSlotDistanceCondition::SetDirection);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<GrabSlotDistanceCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &GrabSlotDistanceCondition::SetCompare);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<GrabSlotDistanceCondition>("distance", &GrabSlotDistanceCondition::SetDistance);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gGrabSlotDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10166880
			fight::ConditionFactory* CreateGrabSlotDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabSlotDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10167370
			void RegisterGrabSlotDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabSlotDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGrabTargetConditionGroupConditionProperties;  // 0x1125459C

			// FUNCTION: ENGINE 0x101640D0
			fight::ConditionList* GrabTargetConditionGroupCondition::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x101644F0
			fight::Property* GrabTargetConditionGroupCondition::GetProperty(int index)
			{
				return gGrabTargetConditionGroupConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10164510
			void GrabTargetConditionGroupCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGrabTargetConditionGroupConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164520
			GrabTargetConditionGroupCondition::GrabTargetConditionGroupCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x10164550
			GrabTargetConditionGroupCondition::~GrabTargetConditionGroupCondition()
			{
			}

			// FUNCTION: ENGINE 0x10166D40
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabTargetConditionGroupCondition::RegisterProperties()
			{
				if (gGrabTargetConditionGroupConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyConditionGroup<GrabTargetConditionGroupCondition>("conditions", &GrabTargetConditionGroupCondition::SetConditions);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gGrabTargetConditionGroupConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101668B0
			fight::ConditionFactory* CreateGrabTargetConditionGroupConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabTargetConditionGroupCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101673A0
			void RegisterGrabTargetConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabTargetConditionGroupCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGrabSlotGrabbableClassConditionProperties;  // 0x112545A0

			// FUNCTION: ENGINE 0x10164960
			bool GrabSlotGrabbableClassCondition::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101640E0
			bool GrabSlotGrabbableClassCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164980
			bool GrabSlotGrabbableClassCondition::SetGrabbableClass(const fight::Name& newValue)
			{
				grabbableClass = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164570
			fight::Property* GrabSlotGrabbableClassCondition::GetProperty(int index)
			{
				return gGrabSlotGrabbableClassConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10164590
			void GrabSlotGrabbableClassCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGrabSlotGrabbableClassConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164D50
			GrabSlotGrabbableClassCondition::GrabSlotGrabbableClassCondition() : fight::Condition(0), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10164D90
			GrabSlotGrabbableClassCondition::~GrabSlotGrabbableClassCondition()
			{
			}

			// FUNCTION: ENGINE 0x101686A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabSlotGrabbableClassCondition::RegisterProperties()
			{
				if (gGrabSlotGrabbableClassConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyNameList<GrabSlotGrabbableClassCondition>("grabSlot", &GrabSlotGrabbableClassCondition::SetGrabSlot);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<GrabSlotGrabbableClassCondition>("compare", gClassNameConditionCompareTable, gClassNameConditionCompareCount, &GrabSlotGrabbableClassCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyName<GrabSlotGrabbableClassCondition>("grabbableClass", &GrabSlotGrabbableClassCondition::SetGrabbableClass);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gGrabSlotGrabbableClassConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101668E0
			fight::ConditionFactory* CreateGrabSlotGrabbableClassConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabSlotGrabbableClassCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101673D0
			void RegisterGrabSlotGrabbableClassConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabSlotGrabbableClassCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGrabbableSizeConditionProperties;  // 0x112545A4

			// FUNCTION: ENGINE 0x101640F0
			bool GrabbableSizeCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101649A0
			bool GrabbableSizeCondition::SetGrabbableSize(const fight::Name& newValue)
			{
				grabbableSize = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101645A0
			fight::Property* GrabbableSizeCondition::GetProperty(int index)
			{
				return gGrabbableSizeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101645C0
			void GrabbableSizeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGrabbableSizeConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164DA0
			GrabbableSizeCondition::GrabbableSizeCondition() : fight::Condition(0), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10164DD0
			GrabbableSizeCondition::~GrabbableSizeCondition()
			{
			}

			// FUNCTION: ENGINE 0x101687D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabbableSizeCondition::RegisterProperties()
			{
				if (gGrabbableSizeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<GrabbableSizeCondition>("compare", gClassNameConditionCompareTable, gClassNameConditionCompareCount, &GrabbableSizeCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyName<GrabbableSizeCondition>("grabbableSize", &GrabbableSizeCondition::SetGrabbableSize);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gGrabbableSizeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10166910
			fight::ConditionFactory* CreateGrabbableSizeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabbableSizeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10167400
			void RegisterGrabbableSizeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabbableSizeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGrabSlotConditionGroupConditionProperties;  // 0x112545A8

			// FUNCTION: ENGINE 0x101649C0
			bool GrabSlotConditionGroupCondition::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164100
			fight::ConditionList* GrabSlotConditionGroupCondition::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x101645D0
			fight::Property* GrabSlotConditionGroupCondition::GetProperty(int index)
			{
				return gGrabSlotConditionGroupConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101645F0
			void GrabSlotConditionGroupCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGrabSlotConditionGroupConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164DE0
			GrabSlotConditionGroupCondition::GrabSlotConditionGroupCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x10164E10
			GrabSlotConditionGroupCondition::~GrabSlotConditionGroupCondition()
			{
			}

			// FUNCTION: ENGINE 0x101688C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabSlotConditionGroupCondition::RegisterProperties()
			{
				if (gGrabSlotConditionGroupConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyNameList<GrabSlotConditionGroupCondition>("grabSlot", &GrabSlotConditionGroupCondition::SetGrabSlot);
					properties[0] = property;
					property = new fight::PropertyConditionGroup<GrabSlotConditionGroupCondition>("conditions", &GrabSlotConditionGroupCondition::SetConditions);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gGrabSlotConditionGroupConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10166940
			fight::ConditionFactory* CreateGrabSlotConditionGroupConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabSlotConditionGroupCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10167430
			void RegisterGrabSlotConditionGroupConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabSlotConditionGroupCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetIsGrabTargetConditionProperties;  // 0x112545AC

			// FUNCTION: ENGINE 0x10164110
			bool TargetIsGrabTargetCondition::SetIs(bool newValue)
			{
				is = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164600
			fight::Property* TargetIsGrabTargetCondition::GetProperty(int index)
			{
				return gTargetIsGrabTargetConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10164620
			void TargetIsGrabTargetCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetIsGrabTargetConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164630
			TargetIsGrabTargetCondition::TargetIsGrabTargetCondition() : fight::Condition(0), is(true)
			{
			}

			// FUNCTION: ENGINE 0x10164650
			TargetIsGrabTargetCondition::~TargetIsGrabTargetCondition()
			{
			}

			// FUNCTION: ENGINE 0x10166DE0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetIsGrabTargetCondition::RegisterProperties()
			{
				if (gTargetIsGrabTargetConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<TargetIsGrabTargetCondition>("is", &TargetIsGrabTargetCondition::SetIs);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gTargetIsGrabTargetConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10166970
			fight::ConditionFactory* CreateTargetIsGrabTargetConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetIsGrabTargetCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10167460
			void RegisterTargetIsGrabTargetConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetIsGrabTargetCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGrabSlotConditionProperties;  // 0x112545B0

			// FUNCTION: ENGINE 0x101649E0
			bool GrabSlotCondition::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164120
			bool GrabSlotCondition::SetIsGrabbing(bool newValue)
			{
				isGrabbing = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164660
			fight::Property* GrabSlotCondition::GetProperty(int index)
			{
				return gGrabSlotConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10164680
			void GrabSlotCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGrabSlotConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164E60
			GrabSlotCondition::GrabSlotCondition() : fight::Condition(0), isGrabbing(true)
			{
			}

			// FUNCTION: ENGINE 0x10164E90
			GrabSlotCondition::~GrabSlotCondition()
			{
			}

			// FUNCTION: ENGINE 0x101689A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabSlotCondition::RegisterProperties()
			{
				if (gGrabSlotConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyNameList<GrabSlotCondition>("grabSlot", &GrabSlotCondition::SetGrabSlot);
					properties[0] = property;
					property = new fight::PropertyBool<GrabSlotCondition>("isGrabbing", &GrabSlotCondition::SetIsGrabbing);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gGrabSlotConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101669A0
			fight::ConditionFactory* CreateGrabSlotConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabSlotCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10167490
			void RegisterGrabSlotConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabSlotCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gTargetCanGrabConditionProperties;  // 0x112545B4

			// FUNCTION: ENGINE 0x10164130
			bool TargetCanGrabCondition::SetSetGrabTarget(bool newValue)
			{
				setGrabTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164690
			fight::Property* TargetCanGrabCondition::GetProperty(int index)
			{
				return gTargetCanGrabConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101646B0
			void TargetCanGrabCondition::ClearProperties()
			{
				fight::FreePropertyList(&gTargetCanGrabConditionProperties);
			}

			// FUNCTION: ENGINE 0x101646C0
			TargetCanGrabCondition::TargetCanGrabCondition() : fight::Condition(0), setGrabTarget(true)
			{
			}

			// FUNCTION: ENGINE 0x101646E0
			TargetCanGrabCondition::~TargetCanGrabCondition()
			{
			}

			// FUNCTION: ENGINE 0x10166E80
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetCanGrabCondition::RegisterProperties()
			{
				if (gTargetCanGrabConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<TargetCanGrabCondition>("setGrabTarget", &TargetCanGrabCondition::SetSetGrabTarget);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gTargetCanGrabConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101669D0
			fight::ConditionFactory* CreateTargetCanGrabConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetCanGrabCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101674C0
			void RegisterTargetCanGrabConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<TargetCanGrabCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGrabSlotMassConditionProperties;  // 0x112545B8

			// FUNCTION: ENGINE 0x10164A00
			bool GrabSlotMassCondition::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164140
			bool GrabSlotMassCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164150
			bool GrabSlotMassCondition::SetMass(float newValue)
			{
				mass = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101646F0
			fight::Property* GrabSlotMassCondition::GetProperty(int index)
			{
				return gGrabSlotMassConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10164710
			void GrabSlotMassCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGrabSlotMassConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164ED0
			GrabSlotMassCondition::GrabSlotMassCondition() : fight::Condition(0), mass(2e+01f), compare(4)
			{
			}

			// FUNCTION: ENGINE 0x10164F10
			GrabSlotMassCondition::~GrabSlotMassCondition()
			{
			}

			// FUNCTION: ENGINE 0x10168A80
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabSlotMassCondition::RegisterProperties()
			{
				if (gGrabSlotMassConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyNameList<GrabSlotMassCondition>("grabSlot", &GrabSlotMassCondition::SetGrabSlot);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<GrabSlotMassCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &GrabSlotMassCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<GrabSlotMassCondition>("mass", &GrabSlotMassCondition::SetMass);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gGrabSlotMassConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10166A00
			fight::ConditionFactory* CreateGrabSlotMassConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabSlotMassCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101674F0
			void RegisterGrabSlotMassConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabSlotMassCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGrabbableClassConditionProperties;  // 0x112545BC

			// FUNCTION: ENGINE 0x10164170
			bool GrabbableClassCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164A20
			bool GrabbableClassCondition::SetGrabbableClass(const fight::Name& newValue)
			{
				grabbableClass = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164720
			fight::Property* GrabbableClassCondition::GetProperty(int index)
			{
				return gGrabbableClassConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10164740
			void GrabbableClassCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGrabbableClassConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164F20
			GrabbableClassCondition::GrabbableClassCondition() : fight::Condition(0), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10164F50
			GrabbableClassCondition::~GrabbableClassCondition()
			{
			}

			// FUNCTION: ENGINE 0x10168BB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabbableClassCondition::RegisterProperties()
			{
				if (gGrabbableClassConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<GrabbableClassCondition>("compare", gClassNameConditionCompareTable, gClassNameConditionCompareCount, &GrabbableClassCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyName<GrabbableClassCondition>("grabbableClass", &GrabbableClassCondition::SetGrabbableClass);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gGrabbableClassConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10166A30
			fight::ConditionFactory* CreateGrabbableClassConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabbableClassCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10167520
			void RegisterGrabbableClassConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabbableClassCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGrabTargetAngleConditionProperties;  // 0x112545C0

			// FUNCTION: ENGINE 0x10164180
			bool GrabTargetAngleCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164190
			bool GrabTargetAngleCondition::SetAngle(float newValue)
			{
				angle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101641B0
			bool GrabTargetAngleCondition::SetUseMovementDirection(bool newValue)
			{
				useMovementDirection = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10164750
			fight::Property* GrabTargetAngleCondition::GetProperty(int index)
			{
				return gGrabTargetAngleConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10164770
			void GrabTargetAngleCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGrabTargetAngleConditionProperties);
			}

			// FUNCTION: ENGINE 0x10164780
			GrabTargetAngleCondition::GrabTargetAngleCondition() : fight::Condition(0), angle(0.0f), compare(4), useMovementDirection(false)
			{
			}

			// FUNCTION: ENGINE 0x101647B0
			GrabTargetAngleCondition::~GrabTargetAngleCondition()
			{
			}

			// FUNCTION: ENGINE 0x10166F20
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabTargetAngleCondition::RegisterProperties()
			{
				if (gGrabTargetAngleConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<GrabTargetAngleCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &GrabTargetAngleCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<GrabTargetAngleCondition>("angle", &GrabTargetAngleCondition::SetAngle);
					properties[1] = property;
					property = new fight::PropertyBool<GrabTargetAngleCondition>("useMovementDirection", &GrabTargetAngleCondition::SetUseMovementDirection);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gGrabTargetAngleConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10166A60
			fight::ConditionFactory* CreateGrabTargetAngleConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabTargetAngleCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10167550
			void RegisterGrabTargetAngleConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabTargetAngleCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGrabTargetDistanceConditionProperties;  // 0x112545C4

			// FUNCTION: ENGINE 0x101641C0
			bool GrabTargetDistanceCondition::SetDirection(int newValue)
			{
				direction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101641D0
			bool GrabTargetDistanceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101641E0
			bool GrabTargetDistanceCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101647C0
			fight::Property* GrabTargetDistanceCondition::GetProperty(int index)
			{
				return gGrabTargetDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101647E0
			void GrabTargetDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGrabTargetDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x101647F0
			GrabTargetDistanceCondition::GrabTargetDistanceCondition() : fight::Condition(0), distance(2e+01f), compare(4), direction(0)
			{
			}

			// FUNCTION: ENGINE 0x10164830
			GrabTargetDistanceCondition::~GrabTargetDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x10167050
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GrabTargetDistanceCondition::RegisterProperties()
			{
				if (gGrabTargetDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<GrabTargetDistanceCondition>("direction", gCrowdPositionConditionDirectionTable, gCrowdPositionConditionDirectionCount, &GrabTargetDistanceCondition::SetDirection);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<GrabTargetDistanceCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &GrabTargetDistanceCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<GrabTargetDistanceCondition>("distance", &GrabTargetDistanceCondition::SetDistance);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gGrabTargetDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10166A90
			fight::ConditionFactory* CreateGrabTargetDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabTargetDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10167580
			void RegisterGrabTargetDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GrabTargetDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			template class fight::PropertyBool<GrabbedCondition>;
			template class fight::ConditionFactoryTemplate<GrabbedCondition>;
			template class fight::ConditionFactoryCasterTemplate<GrabbedCondition>;
			template class fight::PropertyConditionGroup<GrabbedConditionGroupCondition>;
			template class fight::ConditionFactoryTemplate<GrabbedConditionGroupCondition>;
			template class fight::ConditionFactoryCasterTemplate<GrabbedConditionGroupCondition>;
			template class fight::PropertyBool<HaveGrabTargetCondition>;
			template class fight::PropertyBitfieldConstList<HaveGrabTargetCondition>;
			template class fight::PropertyName<HaveGrabTargetCondition>;
			template class fight::PropertyFloatConstRange<HaveGrabTargetCondition>;
			template class fight::ConditionFactoryTemplate<HaveGrabTargetCondition>;
			template class fight::ConditionFactoryCasterTemplate<HaveGrabTargetCondition>;
			template class fight::PropertyNameList<GrabSlotObjectTemplateCondition>;
			template class fight::PropertyEnumConstList<GrabSlotObjectTemplateCondition>;
			template class fight::PropertyName<GrabSlotObjectTemplateCondition>;
			template class fight::ConditionFactoryTemplate<GrabSlotObjectTemplateCondition>;
			template class fight::ConditionFactoryCasterTemplate<GrabSlotObjectTemplateCondition>;
			template class fight::PropertyEnumConstList<GrabbedClassNameCondition>;
			template class fight::PropertyName<GrabbedClassNameCondition>;
			template class fight::ConditionFactoryTemplate<GrabbedClassNameCondition>;
			template class fight::ConditionFactoryCasterTemplate<GrabbedClassNameCondition>;
			template class fight::PropertyBool<IsGrabbableCondition>;
			template class fight::ConditionFactoryTemplate<IsGrabbableCondition>;
			template class fight::ConditionFactoryCasterTemplate<IsGrabbableCondition>;
			template class fight::PropertyEnumConstList<GrabbedGrabbableClassCondition>;
			template class fight::PropertyName<GrabbedGrabbableClassCondition>;
			template class fight::ConditionFactoryTemplate<GrabbedGrabbableClassCondition>;
			template class fight::ConditionFactoryCasterTemplate<GrabbedGrabbableClassCondition>;
			template class fight::PropertyBool<GrabbedBySlotCondition>;
			template class fight::PropertyNameList<GrabbedBySlotCondition>;
			template class fight::ConditionFactoryTemplate<GrabbedBySlotCondition>;
			template class fight::ConditionFactoryCasterTemplate<GrabbedBySlotCondition>;
			template class fight::PropertyBool<GrabbedByPlayerCondition>;
			template class fight::ConditionFactoryTemplate<GrabbedByPlayerCondition>;
			template class fight::ConditionFactoryCasterTemplate<GrabbedByPlayerCondition>;
			template class fight::PropertyNameList<GrabSlotClassNameCondition>;
			template class fight::PropertyEnumConstList<GrabSlotClassNameCondition>;
			template class fight::PropertyName<GrabSlotClassNameCondition>;
			template class fight::ConditionFactoryTemplate<GrabSlotClassNameCondition>;
			template class fight::ConditionFactoryCasterTemplate<GrabSlotClassNameCondition>;
			template class fight::PropertyNameList<GrabSlotDistanceCondition>;
			template class fight::PropertyEnumConstList<GrabSlotDistanceCondition>;
			template class fight::PropertyFloatConstRange<GrabSlotDistanceCondition>;
			template class fight::ConditionFactoryTemplate<GrabSlotDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<GrabSlotDistanceCondition>;
			template class fight::PropertyConditionGroup<GrabTargetConditionGroupCondition>;
			template class fight::ConditionFactoryTemplate<GrabTargetConditionGroupCondition>;
			template class fight::ConditionFactoryCasterTemplate<GrabTargetConditionGroupCondition>;
			template class fight::PropertyNameList<GrabSlotGrabbableClassCondition>;
			template class fight::PropertyEnumConstList<GrabSlotGrabbableClassCondition>;
			template class fight::PropertyName<GrabSlotGrabbableClassCondition>;
			template class fight::ConditionFactoryTemplate<GrabSlotGrabbableClassCondition>;
			template class fight::ConditionFactoryCasterTemplate<GrabSlotGrabbableClassCondition>;
			template class fight::PropertyEnumConstList<GrabbableSizeCondition>;
			template class fight::PropertyName<GrabbableSizeCondition>;
			template class fight::ConditionFactoryTemplate<GrabbableSizeCondition>;
			template class fight::ConditionFactoryCasterTemplate<GrabbableSizeCondition>;
			template class fight::PropertyNameList<GrabSlotConditionGroupCondition>;
			template class fight::PropertyConditionGroup<GrabSlotConditionGroupCondition>;
			template class fight::ConditionFactoryTemplate<GrabSlotConditionGroupCondition>;
			template class fight::ConditionFactoryCasterTemplate<GrabSlotConditionGroupCondition>;
			template class fight::PropertyBool<TargetIsGrabTargetCondition>;
			template class fight::ConditionFactoryTemplate<TargetIsGrabTargetCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetIsGrabTargetCondition>;
			template class fight::PropertyNameList<GrabSlotCondition>;
			template class fight::PropertyBool<GrabSlotCondition>;
			template class fight::ConditionFactoryTemplate<GrabSlotCondition>;
			template class fight::ConditionFactoryCasterTemplate<GrabSlotCondition>;
			template class fight::PropertyBool<TargetCanGrabCondition>;
			template class fight::ConditionFactoryTemplate<TargetCanGrabCondition>;
			template class fight::ConditionFactoryCasterTemplate<TargetCanGrabCondition>;
			template class fight::PropertyNameList<GrabSlotMassCondition>;
			template class fight::PropertyEnumConstList<GrabSlotMassCondition>;
			template class fight::PropertyFloatConstRange<GrabSlotMassCondition>;
			template class fight::ConditionFactoryTemplate<GrabSlotMassCondition>;
			template class fight::ConditionFactoryCasterTemplate<GrabSlotMassCondition>;
			template class fight::PropertyEnumConstList<GrabbableClassCondition>;
			template class fight::PropertyName<GrabbableClassCondition>;
			template class fight::ConditionFactoryTemplate<GrabbableClassCondition>;
			template class fight::ConditionFactoryCasterTemplate<GrabbableClassCondition>;
			template class fight::PropertyEnumConstList<GrabTargetAngleCondition>;
			template class fight::PropertyFloatConstRange<GrabTargetAngleCondition>;
			template class fight::PropertyBool<GrabTargetAngleCondition>;
			template class fight::ConditionFactoryTemplate<GrabTargetAngleCondition>;
			template class fight::ConditionFactoryCasterTemplate<GrabTargetAngleCondition>;
			template class fight::PropertyEnumConstList<GrabTargetDistanceCondition>;
			template class fight::PropertyFloatConstRange<GrabTargetDistanceCondition>;
			template class fight::ConditionFactoryTemplate<GrabTargetDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<GrabTargetDistanceCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10164A40
// FUNCTION: ENGINE 0x10164A70
// FUNCTION: ENGINE 0x10164B90
// FUNCTION: ENGINE 0x10164C40
// FUNCTION: ENGINE 0x10164D20
// FUNCTION: ENGINE 0x10164E30
// FUNCTION: ENGINE 0x10164EA0
// FUNCTION: ENGINE 0x10164F60
// FUNCTION: ENGINE 0x10164F90
// FUNCTION: ENGINE 0x10164FC0
// FUNCTION: ENGINE 0x10164FD0
// FUNCTION: ENGINE 0x10165000
// FUNCTION: ENGINE 0x10165010
// FUNCTION: ENGINE 0x10165040
// FUNCTION: ENGINE 0x10165050
// FUNCTION: ENGINE 0x10165080
// FUNCTION: ENGINE 0x10165090
// FUNCTION: ENGINE 0x101650C0
// FUNCTION: ENGINE 0x101650D0
// FUNCTION: ENGINE 0x10165100
// FUNCTION: ENGINE 0x10165110
// FUNCTION: ENGINE 0x10165140
// FUNCTION: ENGINE 0x10165150
// FUNCTION: ENGINE 0x10165180
// FUNCTION: ENGINE 0x10165190
// FUNCTION: ENGINE 0x101651C0
// FUNCTION: ENGINE 0x101651D0
// FUNCTION: ENGINE 0x10165200
// FUNCTION: ENGINE 0x10165210
// FUNCTION: ENGINE 0x10165240
// FUNCTION: ENGINE 0x10165250
// FUNCTION: ENGINE 0x10165280
// FUNCTION: ENGINE 0x10165290
// FUNCTION: ENGINE 0x101652C0
// FUNCTION: ENGINE 0x101652D0
// FUNCTION: ENGINE 0x10165300
// FUNCTION: ENGINE 0x10165310
// FUNCTION: ENGINE 0x10165340
// FUNCTION: ENGINE 0x10165350
// FUNCTION: ENGINE 0x10165380
// FUNCTION: ENGINE 0x10165390
// FUNCTION: ENGINE 0x101653C0
// FUNCTION: ENGINE 0x101653D0
// FUNCTION: ENGINE 0x10165400
// FUNCTION: ENGINE 0x10165410
// FUNCTION: ENGINE 0x10165440
// FUNCTION: ENGINE 0x10165450
// FUNCTION: ENGINE 0x10165480
// FUNCTION: ENGINE 0x10165490
// FUNCTION: ENGINE 0x101654C0
// FUNCTION: ENGINE 0x101654D0
// FUNCTION: ENGINE 0x10165500
// FUNCTION: ENGINE 0x10165510
// FUNCTION: ENGINE 0x10165540
// FUNCTION: ENGINE 0x10165570
// FUNCTION: ENGINE 0x101655A0
// FUNCTION: ENGINE 0x101655D0
// FUNCTION: ENGINE 0x10165600
// FUNCTION: ENGINE 0x10165630
// FUNCTION: ENGINE 0x10165660
// FUNCTION: ENGINE 0x10165690
// FUNCTION: ENGINE 0x101656C0
// FUNCTION: ENGINE 0x101656F0
// FUNCTION: ENGINE 0x10165720
// FUNCTION: ENGINE 0x10165750
// FUNCTION: ENGINE 0x10165780
// FUNCTION: ENGINE 0x101657B0
// FUNCTION: ENGINE 0x101657E0
// FUNCTION: ENGINE 0x10165800
// FUNCTION: ENGINE 0x10165810
// FUNCTION: ENGINE 0x10165840
// FUNCTION: ENGINE 0x10165860
// FUNCTION: ENGINE 0x10165890
// FUNCTION: ENGINE 0x101658B0
// FUNCTION: ENGINE 0x101658C0
// FUNCTION: ENGINE 0x10165900
// FUNCTION: ENGINE 0x10165910
// FUNCTION: ENGINE 0x10165930
// FUNCTION: ENGINE 0x10165940
// FUNCTION: ENGINE 0x101659A0
// FUNCTION: ENGINE 0x101659D0
// FUNCTION: ENGINE 0x10165A00
// FUNCTION: ENGINE 0x10165A10
// FUNCTION: ENGINE 0x10165A50
// FUNCTION: ENGINE 0x10165A60
// FUNCTION: ENGINE 0x10165A90
// FUNCTION: ENGINE 0x10165AB0
// FUNCTION: ENGINE 0x10165AC0
// FUNCTION: ENGINE 0x10165B00
// FUNCTION: ENGINE 0x10165B10
// FUNCTION: ENGINE 0x10165B40
// FUNCTION: ENGINE 0x10165B60
// FUNCTION: ENGINE 0x10165B70
// FUNCTION: ENGINE 0x10165BA0
// FUNCTION: ENGINE 0x10165BC0
// FUNCTION: ENGINE 0x10165BD0
// FUNCTION: ENGINE 0x10165C10
// FUNCTION: ENGINE 0x10165C20
// FUNCTION: ENGINE 0x10165C50
// FUNCTION: ENGINE 0x10165C70
// FUNCTION: ENGINE 0x10165C80
// FUNCTION: ENGINE 0x10165CB0
// FUNCTION: ENGINE 0x10165CD0
// FUNCTION: ENGINE 0x10165CE0
// FUNCTION: ENGINE 0x10165D10
// FUNCTION: ENGINE 0x10165D30
// FUNCTION: ENGINE 0x10165D40
// FUNCTION: ENGINE 0x10165D80
// FUNCTION: ENGINE 0x10165D90
// FUNCTION: ENGINE 0x10165DC0
// FUNCTION: ENGINE 0x10165DE0
// FUNCTION: ENGINE 0x10165DF0
// FUNCTION: ENGINE 0x10165E30
// FUNCTION: ENGINE 0x10165E40
// FUNCTION: ENGINE 0x10165E70
// FUNCTION: ENGINE 0x10165E90
// FUNCTION: ENGINE 0x10165EA0
// FUNCTION: ENGINE 0x10165ED0
// FUNCTION: ENGINE 0x10165F00
// FUNCTION: ENGINE 0x10165F10
// FUNCTION: ENGINE 0x10165F40
// FUNCTION: ENGINE 0x10165F60
// FUNCTION: ENGINE 0x10165FA0
// FUNCTION: ENGINE 0x10165FB0
// FUNCTION: ENGINE 0x10165FE0
// FUNCTION: ENGINE 0x10166000
// FUNCTION: ENGINE 0x10166010
// FUNCTION: ENGINE 0x10166050
// FUNCTION: ENGINE 0x10166060
// FUNCTION: ENGINE 0x10166090
// FUNCTION: ENGINE 0x101660B0
// FUNCTION: ENGINE 0x101660C0
// FUNCTION: ENGINE 0x101660F0
// FUNCTION: ENGINE 0x10166110
// FUNCTION: ENGINE 0x10166140
// FUNCTION: ENGINE 0x10166160
// FUNCTION: ENGINE 0x10166170
// FUNCTION: ENGINE 0x101661A0
// FUNCTION: ENGINE 0x101661C0
// FUNCTION: ENGINE 0x101661D0
// FUNCTION: ENGINE 0x10166200
// FUNCTION: ENGINE 0x10166220
// FUNCTION: ENGINE 0x10166230
// FUNCTION: ENGINE 0x10166270
// FUNCTION: ENGINE 0x10166280
// FUNCTION: ENGINE 0x101662B0
// FUNCTION: ENGINE 0x101662D0
// FUNCTION: ENGINE 0x101662E0
// FUNCTION: ENGINE 0x10166310
// FUNCTION: ENGINE 0x10166340
// FUNCTION: ENGINE 0x10166350
// FUNCTION: ENGINE 0x10166390
// FUNCTION: ENGINE 0x101663A0
// FUNCTION: ENGINE 0x101663D0
// FUNCTION: ENGINE 0x101663F0
// FUNCTION: ENGINE 0x10166400
// FUNCTION: ENGINE 0x10166440
// FUNCTION: ENGINE 0x10166450
// FUNCTION: ENGINE 0x10166480
// FUNCTION: ENGINE 0x101664A0
// FUNCTION: ENGINE 0x101664B0
// FUNCTION: ENGINE 0x101664E0
// FUNCTION: ENGINE 0x10166510
// FUNCTION: ENGINE 0x10166520
// FUNCTION: ENGINE 0x10166550
// FUNCTION: ENGINE 0x10166570
// FUNCTION: ENGINE 0x10166580
// FUNCTION: ENGINE 0x101665C0
// FUNCTION: ENGINE 0x101665D0
// FUNCTION: ENGINE 0x10166600
// FUNCTION: ENGINE 0x10166620
// FUNCTION: ENGINE 0x10166630
// FUNCTION: ENGINE 0x10166660
// FUNCTION: ENGINE 0x10166690
// FUNCTION: ENGINE 0x101675B0
// FUNCTION: ENGINE 0x101675E0
// FUNCTION: ENGINE 0x10167600
// FUNCTION: ENGINE 0x10167630
// FUNCTION: ENGINE 0x10167650
// FUNCTION: ENGINE 0x10167660
// FUNCTION: ENGINE 0x10167690
// FUNCTION: ENGINE 0x101676B0
// FUNCTION: ENGINE 0x101676E0
// FUNCTION: ENGINE 0x10167700
// FUNCTION: ENGINE 0x10167730
// FUNCTION: ENGINE 0x10167750
// FUNCTION: ENGINE 0x10167780
// FUNCTION: ENGINE 0x101677A0
// FUNCTION: ENGINE 0x101677B0
// FUNCTION: ENGINE 0x101677E0
// FUNCTION: ENGINE 0x10167800
// FUNCTION: ENGINE 0x10167810
// FUNCTION: ENGINE 0x10167840
// FUNCTION: ENGINE 0x10167860
// FUNCTION: ENGINE 0x10167890
// FUNCTION: ENGINE 0x101678B0
// FUNCTION: ENGINE 0x101678C0
// FUNCTION: ENGINE 0x101678F0
// FUNCTION: ENGINE 0x10167910
// FUNCTION: ENGINE 0x10167920
// FUNCTION: ENGINE 0x10167950
// FUNCTION: ENGINE 0x10167970
// FUNCTION: ENGINE 0x101679A0
// FUNCTION: ENGINE 0x101679C0
// FUNCTION: ENGINE 0x101679F0
// FUNCTION: ENGINE 0x10167A10
// FUNCTION: ENGINE 0x10167A20
// FUNCTION: ENGINE 0x10167A50
// FUNCTION: ENGINE 0x10167A70
// FUNCTION: ENGINE 0x10167A80
// FUNCTION: ENGINE 0x10167AB0
// FUNCTION: ENGINE 0x10167AD0
// FUNCTION: ENGINE 0x10167AE0
// FUNCTION: ENGINE 0x10167B10
// FUNCTION: ENGINE 0x10167B30
// FUNCTION: ENGINE 0x10167B60
// FUNCTION: ENGINE 0x10167B80
// FUNCTION: ENGINE 0x10167BB0
// FUNCTION: ENGINE 0x10167BD0
// FUNCTION: ENGINE 0x10167C00
// FUNCTION: ENGINE 0x10167C20
// FUNCTION: ENGINE 0x10167C50
// FUNCTION: ENGINE 0x10167C70
// FUNCTION: ENGINE 0x10167CA0
// FUNCTION: ENGINE 0x10167CC0
// FUNCTION: ENGINE 0x10167CF0
// FUNCTION: ENGINE 0x10167D10
// FUNCTION: ENGINE 0x10167D40
// FUNCTION: ENGINE 0x10167D60
// FUNCTION: ENGINE 0x10167D90
// FUNCTION: ENGINE 0x10167DB0
// FUNCTION: ENGINE 0x10167DE0
// FUNCTION: ENGINE 0x10168CA0
// FUNCTION: ENGINE 0x10168CF0
// FUNCTION: ENGINE 0x10168D40
// FUNCTION: ENGINE 0x10168D90
// FUNCTION: ENGINE 0x10168DE0
// FUNCTION: ENGINE 0x10168E30
// FUNCTION: ENGINE 0x10168E80
// FUNCTION: ENGINE 0x10168ED0
// FUNCTION: ENGINE 0x10168F20
// FUNCTION: ENGINE 0x10168F70
// FUNCTION: ENGINE 0x10168FA0
// FUNCTION: ENGINE 0x10168FC0
// FUNCTION: ENGINE 0x10168FF0
// FUNCTION: ENGINE 0x10169010
// FUNCTION: ENGINE 0x10169040
// FUNCTION: ENGINE 0x10169060
// FUNCTION: ENGINE 0x10169090
// FUNCTION: ENGINE 0x101690B0
// FUNCTION: ENGINE 0x101690E0
// FUNCTION: ENGINE 0x10169100
// FUNCTION: ENGINE 0x10169130
// FUNCTION: ENGINE 0x10169150
// FUNCTION: ENGINE 0x10169180
// FUNCTION: ENGINE 0x101691A0
// FUNCTION: ENGINE 0x101691D0
// FUNCTION: ENGINE 0x101691F0
// FUNCTION: ENGINE 0x10169220
// FUNCTION: ENGINE 0x10169240
// FUNCTION: ENGINE 0x10169270
// FUNCTION: ENGINE 0x10169290
// FUNCTION: ENGINE 0x101692C0
// FUNCTION: ENGINE 0x101692E0
// FUNCTION: ENGINE 0x10169310
// FUNCTION: ENGINE 0x10169330
// FUNCTION: ENGINE 0x10169360
// FUNCTION: ENGINE 0x10169380
// FUNCTION: ENGINE 0x101693D0
// FUNCTION: ENGINE 0x10169420
// FUNCTION: ENGINE 0x10169470
// FUNCTION: ENGINE 0x101694C0
// FUNCTION: ENGINE 0x10169510
// FUNCTION: ENGINE 0x10169560
// FUNCTION: ENGINE 0x101695B0
// FUNCTION: ENGINE 0x10169600
// FUNCTION: ENGINE 0x10169650
// FUNCTION: ENGINE 0x101696A0
// FUNCTION: ENGINE 0x101696F0
// FUNCTION: ENGINE 0x10169740
