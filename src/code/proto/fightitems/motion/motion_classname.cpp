// Fight items of the motion group: ClassNameCondition (unit 0x10149690 - 0x10149A90; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_classname.h"
#include "code/proto/fightitems/motion/motioncommon.h"
#include "code/core/strings.h"
#include "code/engine/gameobject/gameobjectsystem.h"

namespace proto
{
	namespace HitEffectManager
	{
		// 0x112562B8: the name of the attribute that holds an object's class name
		extern core::Name<core::CaseSensitiveKey> gClassNameAttributeName;
	}
}

namespace fight
{
	// FUNCTION: ENGINE 0x100A1F10
	bool HashesEqual(const unsigned __int64* lhs, const unsigned __int64* rhs)
	{
		return *lhs == *rhs;
	}

	// FUNCTION: ENGINE 0x100A1F40
	bool CompareHashes(int op, const unsigned __int64* lhs, const unsigned __int64* rhs)
	{
		switch (op)
		{
		case 0:
			return HashesEqual(lhs, rhs);
		case 1:
			return !HashesEqual(lhs, rhs);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x100A1F90
	bool NamesEqual(const core::Name<core::CaseSensitiveKey>* lhs, const core::Name<core::CaseSensitiveKey>* rhs)
	{
		return *lhs == *rhs;
	}

	// FUNCTION: ENGINE 0x100A1FB0
	bool CompareNames(int op, const core::Name<core::CaseSensitiveKey>* lhs, const core::Name<core::CaseSensitiveKey>* rhs)
	{
		switch (op)
		{
		case 0:
			return NamesEqual(lhs, rhs);
		case 1:
			return !NamesEqual(lhs, rhs);
		}
		return false;
	}
}

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gClassNameConditionProperties;  // 0x11254338

			// FUNCTION: ENGINE 0x10149690
			bool ClassNameCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101496D0
			bool ClassNameCondition::SetValue(const fight::Name& newValue)
			{
				value = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101496A0
			fight::Property* ClassNameCondition::GetProperty(int index)
			{
				return gClassNameConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101496C0
			void ClassNameCondition::ClearProperties()
			{
				fight::FreePropertyList(&gClassNameConditionProperties);
			}

			// FUNCTION: ENGINE 0x101496F0
			ClassNameCondition::ClassNameCondition() : fight::Condition(0), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x10149720
			ClassNameCondition::~ClassNameCondition()
			{
			}

			// FUNCTION: ENGINE 0x10149900
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ClassNameCondition::RegisterProperties()
			{
				if (gClassNameConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<ClassNameCondition>("compare", gClassNameConditionCompareTable, gClassNameConditionCompareCount, &ClassNameCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyName<ClassNameCondition>("value", &ClassNameCondition::SetValue);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gClassNameConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10149850
			fight::ConditionFactory* CreateClassNameConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ClassNameCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10149880
			void RegisterClassNameConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ClassNameCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			// ---- actions begin

			// The class name of the last object asked, with the handle (index and serial swapped) and the game object frame it was read in
			static unsigned __int64 sCachedHash;  // 0x112536A8
			static unsigned int sCachedHandle;  // 0x112536B0
			static int sCachedFrame;  // 0x112536B4

			// FUNCTION: ENGINE 0x100A2000
			bool ClassNameCondition::Evaluate(int a, int b, int c, int d)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(AsOwner(c));
				unsigned int key = ((unsigned int)handle.index << 16) | handle.serial;
				if (sCachedHandle == key)
				{
					if (engine::GetGameObjectFrame() == sCachedFrame)
					{
						return fight::CompareHashes(compare, &sCachedHash, &value.GetHash());
					}
				}
				core::Name<core::CaseSensitiveKey>* attributeValue = 0;
				bool found = false;
				if (handle.index != 0xffff)
				{
					engine::GameObject* object = handle.Get();
					if (object != 0)
					{
						engine::BaseAttribute* attribute = object->FindAttribute(HitEffectManager::gClassNameAttributeName);
						core::Name<core::CaseSensitiveKey>* nameValue = (attribute != 0) ? &((engine::Attribute<core::Name<core::CaseSensitiveKey> >*)attribute)->value : 0;
						attributeValue = nameValue;
						found = nameValue != 0;
					}
				}
				sCachedHandle = key;
				sCachedFrame = engine::GetGameObjectFrame();
				core::Name<core::CaseSensitiveKey>* className;
				if (found)
				{
					className = attributeValue;
				}
				else
				{
					className = (core::Name<core::CaseSensitiveKey>*)core::GetStringHeapCounter1();
				}
				sCachedHash = className->GetHash();
				return fight::CompareNames(compare, className, &value);
			}

			// ---- actions end
			template class fight::PropertyEnumConstList<ClassNameCondition>;
			template class fight::PropertyName<ClassNameCondition>;
			template class fight::ConditionFactoryTemplate<ClassNameCondition>;
			template class fight::ConditionFactoryCasterTemplate<ClassNameCondition>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10149730
// FUNCTION: ENGINE 0x10149740
// FUNCTION: ENGINE 0x10149770
// FUNCTION: ENGINE 0x101497A0
// FUNCTION: ENGINE 0x101497E0
// FUNCTION: ENGINE 0x101497F0
// FUNCTION: ENGINE 0x10149820
// FUNCTION: ENGINE 0x10149840
// FUNCTION: ENGINE 0x101498B0
// FUNCTION: ENGINE 0x101498E0
// FUNCTION: ENGINE 0x101499F0
// FUNCTION: ENGINE 0x10149A20
// FUNCTION: ENGINE 0x10149A40
