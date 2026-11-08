#include "code/engine/contentmanager.h"
#include "code/core/strings.h"
#include <new>

namespace engine
{
	typedef ContentManager CM;

#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define ENGINE_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x108E4520
	content::ClassInfo* CM::ContentCementFileDefinition::Collection::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::ContentManager::ContentCementFileDefinition::Collection";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x108E4560
	content::ClassInfo* CM::ContentCementFileDefinition::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ContentCementFileDefinition";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x108E4650
	void CM::ContentCementFileDefinition::Slot3(int unused)
	{
		gCementDefinition = this;
		AddRef();
	}

	// FUNCTION: ENGINE 0x108E5630
	content::MemberList* CM::ContentCementFileDefinition::Collection::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<Collection>(true, true, "p"), ENGINE_NAME_OFFSET(Collection, name), "" },
			{ content::GetArrayDynamicMetaType<Collection, FileArray>(content::GetClassMetaType<FileName>(), "p"),
				ENGINE_OFFSET(Collection, files), "files" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x108E5A70
	content::MemberList* CM::ContentCementFileDefinition::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<ContentCementFileDefinition, CollectionArray>(
				content::GetClassMetaType<Collection>(), "p"), ENGINE_OFFSET(ContentCementFileDefinition, collections),
				"collections" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x108E5D20
	CM::ContentCementFileDefinition::Collection::Collection() : opened(false), libraries(0)
	{
	}

	// FUNCTION: ENGINE 0x108E5D40
	CM::ContentCementFileDefinition::Collection::~Collection()
	{
		operator delete[](libraries);
	}

	// FUNCTION: ENGINE 0x108E0D30
	CM::ContentCementFileDefinition::ContentCementFileDefinition()
	{
	}

	// FUNCTION: ENGINE 0x108E0D50
	CM::ContentCementFileDefinition::~ContentCementFileDefinition()
	{
	}

	// FUNCTION: ENGINE 0x108E6900
	content::ClassInfo* CM::ContentPackageDefinition::LocalizedName::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::ContentManager::ContentPackageDefinition::LocalizedName";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x108E6940
	content::ClassInfo* CM::ContentPackageDefinition::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ContentPackageDefinition";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x108E6980
	content::ClassInfo* CM::ContentPackageKey::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "ContentPackageKey";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x108E69C0
	void CM::ContentPackageDefinition::Slot3(int unused)
	{
		next = *gPackageDefinitions;
		*gPackageDefinitions = this;
		AddRef();
	}

	// FUNCTION: ENGINE 0x108E69E0
	const char* CM::ContentPackageDefinition::GetCategoryName()
	{
		return categoryName != 0 ? categoryName : "";
	}

	// FUNCTION: ENGINE 0x108E69F0
	void CM::ContentPackageDefinition::SetCategoryName(const char* value)
	{
		if (categoryName != 0)
		{
			operator delete[](categoryName);
		}
		categoryName = new char[core::StrLen(value) + 1];
		core::StrCpy(categoryName, value);
	}

	// FUNCTION: ENGINE 0x108E6A30
	void CM::ContentPackageKey::Slot3(int unused)
	{
		next = *gPackageKeys;
		*gPackageKeys = this;
		AddRef();
	}

	// FUNCTION: ENGINE 0x108E6A50
	void CM::ContentPackageDefinition::LocalizedName::SetText(const char* value)
	{
		if (text != 0)
		{
			operator delete[](text);
		}
		text = new char[core::StrLen(value) + 1];
		core::StrCpy(text, value);
	}

	// FUNCTION: ENGINE 0x108E6A90
	const char* CM::ContentPackageDefinition::LocalizedName::GetText()
	{
		return text != 0 ? text : "";
	}

	// FUNCTION: ENGINE 0x108E6B60
	CM::ContentPackageDefinition::LocalizedName::LocalizedName() : language((const char*)0, 1), text(0)
	{
	}

	// FUNCTION: ENGINE 0x108E6B80
	CM::ContentPackageDefinition::LocalizedName::~LocalizedName()
	{
		if (text != 0)
		{
			operator delete[](text);
		}
	}

	// FUNCTION: ENGINE 0x108E71E0
	content::MemberList* CM::ContentPackageDefinition::LocalizedName::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNameMetaType<LocalizedName>(true, true, "p"), ENGINE_NAME_OFFSET(LocalizedName, language),
				"language" },
			{ content::GetStringMemberMetaType<LocalizedName, 0>(&LocalizedName::GetText, &LocalizedName::SetText,
				"p"), 0, "string" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x108E7290
	content::MemberList* CM::ContentPackageKey::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<ContentPackageKey, unsigned int, 0>("p"),
				ENGINE_OFFSET(ContentPackageKey, packageId), "packageId" },
			{ content::GetArrayDynamicMetaType<ContentPackageKey, FileArray>(content::GetClassMetaType<FileName>(),
				"p"), ENGINE_OFFSET(ContentPackageKey, files), "files" }
		};
		sList.members = sMembers;
		sList.count = 2;
		return &sList;
	}

	// FUNCTION: ENGINE 0x108E7490
	content::MemberList* CM::ContentPackageDefinition::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<ContentPackageDefinition, unsigned int, 0>("p"),
				ENGINE_OFFSET(ContentPackageDefinition, packageId), "packageId" },
			{ content::GetMemberPrimitiveMetaType<ContentPackageDefinition, unsigned int, 1>("p"),
				ENGINE_OFFSET(ContentPackageDefinition, category), "category" },
			{ content::GetStringMemberMetaType<ContentPackageDefinition, 0>(&ContentPackageDefinition::GetCategoryName,
				&ContentPackageDefinition::SetCategoryName, "p"), 0, "" },
			{ content::GetMemberPrimitiveMetaType<ContentPackageDefinition, bool, 0>("p"),
				ENGINE_OFFSET(ContentPackageDefinition, transferable), "transferable" },
			{ content::GetMemberPrimitiveMetaType<ContentPackageDefinition, bool, 1>("p"),
				ENGINE_OFFSET(ContentPackageDefinition, keyTransferable), "keyTransferable" },
			{ content::GetMemberPrimitiveMetaType<ContentPackageDefinition, bool, 2>("p"),
				ENGINE_OFFSET(ContentPackageDefinition, onlineRequired), "onlineRequired" },
			{ content::GetMemberPrimitiveMetaType<ContentPackageDefinition, bool, 3>("p"),
				ENGINE_OFFSET(ContentPackageDefinition, ownerOnly), "ownerOnly" },
			{ content::GetArrayDynamicMetaType<ContentPackageDefinition, NameArray>(
				content::GetClassMetaType<LocalizedName>(), "p"), ENGINE_OFFSET(ContentPackageDefinition, names),
				"names" },
			{ content::GetArrayDynamicMetaType<ContentPackageDefinition, FileArray>(
				content::GetClassMetaType<FileName>(), "p"), ENGINE_OFFSET(ContentPackageDefinition, files),
				"files" }
		};
		sList.members = sMembers;
		sList.count = 9;
		return &sList;
	}

	// FUNCTION: ENGINE 0x108E77F0
	CM::ContentPackageKey::ContentPackageKey() : packageId(0)
	{
	}

	// FUNCTION: ENGINE 0x108E7910
	CM::ContentPackageDefinition::ContentPackageDefinition() : packageId(0), category(0), categoryName(0),
		keyTransferable(false), onlineRequired(false), transferable(false), ownerOnly(false)
	{
	}

	// FUNCTION: ENGINE 0x108E7950
	CM::ContentPackageDefinition::~ContentPackageDefinition()
	{
		if (categoryName != 0)
		{
			operator delete[](categoryName);
		}
	}

	// FUNCTION: ENGINE 0x108E7AD0
	content::ClassInfo* CM::FileName::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::ContentManager::FileName";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x108E7B10
	CM::FileName::FileName() : text(0)
	{
	}

	// FUNCTION: ENGINE 0x108E7B20
	CM::FileName::~FileName()
	{
		if (text != 0)
		{
			operator delete[](text);
		}
	}

	// FUNCTION: ENGINE 0x108E7B30
	const char* CM::FileName::GetText()
	{
		return text != 0 ? text : "";
	}

	// FUNCTION: ENGINE 0x108E7B40
	void CM::FileName::SetText(const char* value)
	{
		if (text != 0)
		{
			operator delete[](text);
		}
		text = new char[core::StrLen(value) + 1];
		core::StrCpy(text, value);
	}

	// FUNCTION: ENGINE 0x108E7C40
	content::MemberList* CM::FileName::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetStringMemberMetaType<FileName, 0>(&FileName::GetText, &FileName::SetText, "p"), 0, "" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}
}

namespace container
{
	template class ArrayDynamic<engine::ContentManager::FileName, AllocatorNew>;
	template class ArrayDynamic<engine::ContentManager::ContentCementFileDefinition::Collection, AllocatorNew>;
	template class ArrayDynamic<engine::ContentManager::ContentPackageDefinition::LocalizedName, AllocatorNew>;
}


// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108E4660
// FUNCTION: ENGINE 0x108E4680
// FUNCTION: ENGINE 0x108E4690
// FUNCTION: ENGINE 0x108E46E0
// FUNCTION: ENGINE 0x108E4750
// FUNCTION: ENGINE 0x108E4790
// FUNCTION: ENGINE 0x108E47A0
// FUNCTION: ENGINE 0x108E47B0
// FUNCTION: ENGINE 0x108E4A60
// FUNCTION: ENGINE 0x108E4A70
// FUNCTION: ENGINE 0x108E4A80
// FUNCTION: ENGINE 0x108E4A90
// FUNCTION: ENGINE 0x108E4AA0
// FUNCTION: ENGINE 0x108E4AF0
// FUNCTION: ENGINE 0x108E4B00
// FUNCTION: ENGINE 0x108E4B10
// FUNCTION: ENGINE 0x108E4B20
// FUNCTION: ENGINE 0x108E4B40
// FUNCTION: ENGINE 0x108E4B70
// FUNCTION: ENGINE 0x108E4BA0
// FUNCTION: ENGINE 0x108E4BB0
// FUNCTION: ENGINE 0x108E4BD0
// FUNCTION: ENGINE 0x108E4BF0
// FUNCTION: ENGINE 0x108E4C40
// FUNCTION: ENGINE 0x108E4C60
// FUNCTION: ENGINE 0x108E4C70
// FUNCTION: ENGINE 0x108E4C80
// FUNCTION: ENGINE 0x108E4C90
// FUNCTION: ENGINE 0x108E4CA0
// FUNCTION: ENGINE 0x108E4CD0
// FUNCTION: ENGINE 0x108E4D00
// FUNCTION: ENGINE 0x108E4D10
// FUNCTION: ENGINE 0x108E4D20
// FUNCTION: ENGINE 0x108E4D40
// FUNCTION: ENGINE 0x108E4D60
// FUNCTION: ENGINE 0x108E5390
// FUNCTION: ENGINE 0x108E53E0
// FUNCTION: ENGINE 0x108E5430
// FUNCTION: ENGINE 0x108E54A0
// FUNCTION: ENGINE 0x108E54F0
// FUNCTION: ENGINE 0x108E5860
// FUNCTION: ENGINE 0x108E58B0
// FUNCTION: ENGINE 0x108E5920
// FUNCTION: ENGINE 0x108E5A30
// FUNCTION: ENGINE 0x108E5BD0
// FUNCTION: ENGINE 0x108E5C10
// FUNCTION: ENGINE 0x108E5C50
// FUNCTION: ENGINE 0x108E5C80
// FUNCTION: ENGINE 0x108E5CE0
// FUNCTION: ENGINE 0x108E5D90
// FUNCTION: ENGINE 0x108E5E50
// FUNCTION: ENGINE 0x108E5EB0
// FUNCTION: ENGINE 0x108E5F10
// FUNCTION: ENGINE 0x108E5F60
// FUNCTION: ENGINE 0x108E5FD0
// FUNCTION: ENGINE 0x108E6010
// FUNCTION: ENGINE 0x108E6140
// FUNCTION: ENGINE 0x108E6180
// FUNCTION: ENGINE 0x108E6B10
// FUNCTION: ENGINE 0x108E6B50
// FUNCTION: ENGINE 0x108E6B90
// FUNCTION: ENGINE 0x108E6BA0
// FUNCTION: ENGINE 0x108E6BE0
// FUNCTION: ENGINE 0x108E6C20
// FUNCTION: ENGINE 0x108E6C60
// FUNCTION: ENGINE 0x108E6CA0
// FUNCTION: ENGINE 0x108E6CE0
// FUNCTION: ENGINE 0x108E6D20
// FUNCTION: ENGINE 0x108E6D60
// FUNCTION: ENGINE 0x108E6D70
// FUNCTION: ENGINE 0x108E6DE0
// FUNCTION: ENGINE 0x108E6E10
// FUNCTION: ENGINE 0x108E6E30
// FUNCTION: ENGINE 0x108E6E40
// FUNCTION: ENGINE 0x108E6E60
// FUNCTION: ENGINE 0x108E6E80
// FUNCTION: ENGINE 0x108E6E90
// FUNCTION: ENGINE 0x108E6EB0
// FUNCTION: ENGINE 0x108E6EC0
// FUNCTION: ENGINE 0x108E6ED0
// FUNCTION: ENGINE 0x108E6EE0
// FUNCTION: ENGINE 0x108E6EF0
// FUNCTION: ENGINE 0x108E6F10
// FUNCTION: ENGINE 0x108E6F50
// FUNCTION: ENGINE 0x108E6F70
// FUNCTION: ENGINE 0x108E6F90
// FUNCTION: ENGINE 0x108E7000
// FUNCTION: ENGINE 0x108E7070
// FUNCTION: ENGINE 0x108E70C0
// FUNCTION: ENGINE 0x108E7110
// FUNCTION: ENGINE 0x108E7160
// FUNCTION: ENGINE 0x108E71A0
// FUNCTION: ENGINE 0x108E7340
// FUNCTION: ENGINE 0x108E7390
// FUNCTION: ENGINE 0x108E73C0
// FUNCTION: ENGINE 0x108E73F0
// FUNCTION: ENGINE 0x108E7440
// FUNCTION: ENGINE 0x108E7690
// FUNCTION: ENGINE 0x108E76C0
// FUNCTION: ENGINE 0x108E7810
// FUNCTION: ENGINE 0x108E7850
// FUNCTION: ENGINE 0x108E7890
// FUNCTION: ENGINE 0x108E78D0
// FUNCTION: ENGINE 0x108E79D0
// FUNCTION: ENGINE 0x108E7A20
// FUNCTION: ENGINE 0x108E7AB0
// FUNCTION: ENGINE 0x108E7B80
// FUNCTION: ENGINE 0x108E7BA0
// FUNCTION: ENGINE 0x108E7BB0
// FUNCTION: ENGINE 0x108E7BD0
// FUNCTION: ENGINE 0x108E0D90
