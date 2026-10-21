#include "code/engine/namedinventorycreator.h"
#include "code/core/refptr.h"
#include "code/math/mathutils.h"

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define ENGINE_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	inline bool IsPowerOfTwo(unsigned int value)
	{
		if (value == 0)
		{
			return false;
		}
		return (value & (value - 1)) == 0;
	}

	// The size rounded up to a power of two
	inline unsigned int RoundUpToPowerOfTwo(unsigned int value)
	{
		if (IsPowerOfTwo(value))
		{
			return value;
		}
		return 1 << (math::Log2(value) + 1);
	}

	// FUNCTION: ENGINE 0x1090D720
	content::ClassInfo* NamedInventoryCreator::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "NamedInventoryCreator";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x1090D7F0
	NamedInventoryCreator::~NamedInventoryCreator()
	{
		core::SafeRelease(inventory);
	}

	// FUNCTION: ENGINE 0x1090D810
	void NamedInventoryCreator::Slot3(int unused)
	{
		unsigned int size = RoundUpToPowerOfTwo(initialSize);
		core::RefAssign(inventory, new content::LoadInventory(size));
		content::gRootInventory->Add(inventoryName, inventory);
	}

	// FUNCTION: ENGINE 0x1090D880
	bool NamedInventoryCreator::IsReady()
	{
		bool ready = true;
		if (inventory != 0)
		{
			content::gRootInventory->Remove(inventoryName, inventory, true);
			ready = inventory->IsReady();
			if (ready)
			{
				core::SafeRelease(inventory);
			}
		}
		return ready;
	}

	// FUNCTION: ENGINE 0x1090D900
	content::MemberList* NamedInventoryCreator::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<NamedInventoryCreator>(true, true, "p"),
				ENGINE_NAME_OFFSET(NamedInventoryCreator, inventoryName), "inventoryName" },
			{ content::GetMemberPrimitiveMetaType<NamedInventoryCreator, unsigned int, 0>("p"),
				ENGINE_OFFSET(NamedInventoryCreator, initialSize), "initialSize" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x1090D9B0
	// EQUIVALENT: the engine's lea of the name member sits behind the reference count store, ours before it, 81.2 %
	NamedInventoryCreator::NamedInventoryCreator() : initialSize(0x100), inventory(0)
	{
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1090D760
// FUNCTION: ENGINE 0x1090D7A0
// FUNCTION: ENGINE 0x1090D7C0
// FUNCTION: ENGINE 0x1090D8C0
