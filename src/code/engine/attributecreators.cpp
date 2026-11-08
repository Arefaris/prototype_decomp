// The content library's instance creators of the plain attributes (the other creators of the unit that registers them
// are in metafactories.cpp, which declares these): each makes an attribute with the default value of its type.
#include "code/content/metafactory.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/system/enginememory.h"
#include <new>

namespace pure3d
{
	class Pose;
}

namespace engine
{
	// The values the attributes start with (the engine keeps them in its data: 0x11261111, 0x1125E03C and 0x112750C8)
	extern const bool gDefaultBoolAttribute;
	extern const int gDefaultIntAttribute;
	extern const float gDefaultFloatAttribute;
}

namespace content
{
	// FUNCTION: ENGINE 0x108E07F0
	template<> void* MetaInstanceCreatorImpl<engine::Attribute<bool>, 1>::Create()
	{
		return new engine::Attribute<bool>(engine::gDefaultBoolAttribute);
	}

	// FUNCTION: ENGINE 0x108E0820
	template<> void* MetaInstanceCreatorImpl<engine::ConstAttribute<bool>, 1>::Create()
	{
		engine::ConstAttribute<bool>* attribute = (engine::ConstAttribute<bool>*)operator new(sizeof(engine::ConstAttribute<bool>));
		if (attribute != 0)
		{
			new (attribute) engine::ConstAttribute<bool>;
			attribute->value = engine::gDefaultBoolAttribute;
			return attribute;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x108E0850
	template<> void* MetaInstanceCreatorImpl<engine::Attribute<int>, 1>::Create()
	{
		return new engine::Attribute<int>(engine::gDefaultIntAttribute);
	}

	// FUNCTION: ENGINE 0x108E0880
	template<> void* MetaInstanceCreatorImpl<engine::ConstAttribute<int>, 1>::Create()
	{
		engine::ConstAttribute<int>* attribute = (engine::ConstAttribute<int>*)operator new(sizeof(engine::ConstAttribute<int>));
		if (attribute != 0)
		{
			new (attribute) engine::ConstAttribute<int>;
			attribute->value = engine::gDefaultIntAttribute;
			return attribute;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x108E08B0
	template<> void* MetaInstanceCreatorImpl<engine::Attribute<float>, 1>::Create()
	{
		return new engine::Attribute<float>(engine::gDefaultFloatAttribute);
	}

	// FUNCTION: ENGINE 0x108E08E0
	template<> void* MetaInstanceCreatorImpl<engine::ConstAttribute<float>, 1>::Create()
	{
		engine::ConstAttribute<float>* attribute = (engine::ConstAttribute<float>*)operator new(sizeof(engine::ConstAttribute<float>));
		if (attribute != 0)
		{
			new (attribute) engine::ConstAttribute<float>;
			attribute->value = engine::gDefaultFloatAttribute;
			return attribute;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x108E0930
	template<> void* MetaInstanceCreatorImpl<engine::ConstAttribute<pure3d::Pose*>, 1>::Create()
	{
		engine::ConstAttribute<pure3d::Pose*>* attribute = (engine::ConstAttribute<pure3d::Pose*>*)operator new(sizeof(engine::ConstAttribute<pure3d::Pose*>));
		if (attribute != 0)
		{
			new (attribute) engine::ConstAttribute<pure3d::Pose*>;
			attribute->value = (pure3d::Pose*)0;
			return attribute;
		}
		return 0;
	}

	// The creators are made with their vftables here too
	template MetaInstanceCreatorImpl<engine::Attribute<bool>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template MetaInstanceCreatorImpl<engine::ConstAttribute<bool>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template MetaInstanceCreatorImpl<engine::Attribute<int>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template MetaInstanceCreatorImpl<engine::ConstAttribute<int>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template MetaInstanceCreatorImpl<engine::Attribute<float>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template MetaInstanceCreatorImpl<engine::ConstAttribute<float>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
	template MetaInstanceCreatorImpl<engine::ConstAttribute<pure3d::Pose*>, 1>::MetaInstanceCreatorImpl(const char*, unsigned short, ClassMetaType*);
}
