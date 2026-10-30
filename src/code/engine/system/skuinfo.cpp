#include "code/engine/system/skuinfo.h"
#include "code/container/string.h"
#include "code/content/loadmanager.h"
#include "code/content/memorystream.h"
#include "code/core/file/file.h"
#include "code/core/file/filesystem.h"
#include "code/core/strings.h"
#include <new>

namespace
{
	// What a load of a file is asked with: a name over the 256 characters of a string, the stream the file is read
	// from and a few words (0x120 bytes)
	struct SkuLoadRequest
	{
		SkuLoadRequest() : stream(0), unknown108(0), heap(0), unknown110(0), flags(0x400), unknown118(false),
			unknown119(false), unknown11A(0xFFFF), unknown11C(0)
		{
		}

		container::StringC<256> name;
		content::MemoryStream* stream;
		int unknown108;
		int heap;
		int unknown110;
		int flags;
		bool unknown118;
		bool unknown119;
		unsigned short unknown11A;
		int unknown11C;
	};
}

namespace content
{
	// The meta type of a char array member, one per member (Id tells them apart)
	template<int Id> StringMetaType* GetMemberCharArrayMetaType(int capacity, const char* code)
	{
		static StringMetaType sType(capacity, code);
		return &sType;
	}
}

namespace engine
{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

	// GLOBAL: ENGINE 0x113176C8
	SkuInfo* gSkuInfo = 0;

	// FUNCTION: ENGINE 0x10892F10
	// EQUIVALENT: the engine passes the path through a stack slot it fills after pushing the other arguments, ours
	// pushes the literal (every other instruction is the same), 24.2 %
	void SkuInfo::Load(int heap)
	{
		core::IFile* file;
		core::FileSystemOpenFile(&file, "skuinfo.p3d", false, 0, 1, 0, 1, 1, 0);
		if (!file->IsOpen())
		{
			file->Release();
			gSkuInfo = new (heap) SkuInfo;
			gSkuInfo->AddRef();
			return;
		}
		file->Release();
		SkuLoadRequest request;
		int length = core::StrLen("skuinfo.p3d") + 1;
		if (length > 0x100)
		{
			length = 0x100;
		}
		core::StrNCpy(request.name.buffer, "skuinfo.p3d", (unsigned int)length);
		request.heap = heap;
		request.unknown118 = true;
		content::LoadJob* job;
		content::gLoadManager->Load(&request.name, &job, true);
		job->Slot3(0);
		job->Release();
	}

	// FUNCTION: ENGINE 0x108925F0
	content::ClassInfo* SkuInfo::Language::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SkuInfo::Language";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10892630
	content::ClassInfo* SkuInfo::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "engine::SkuInfo";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x10892670
	void SkuInfo::Shutdown()
	{
		gSkuInfo->Release();
		gSkuInfo = 0;
	}

	// FUNCTION: ENGINE 0x10892690
	SkuInfo* SkuInfo::GetCurrent()
	{
		return gSkuInfo;
	}

	// FUNCTION: ENGINE 0x108926A0
	void SkuInfo::Slot3(int unused)
	{
		gSkuInfo = this;
		AddRef();
	}

	// FUNCTION: ENGINE 0x108926B0
	const char* SkuInfo::GetMassiveSkuName() const
	{
		return core::StrLen(massiveSkuName) == 0 ? "vug_prototype_pc_na" : massiveSkuName;
	}

	// FUNCTION: ENGINE 0x108926D0
	const char* SkuInfo::GetMassiveSkuVersion() const
	{
		return core::StrLen(massiveSkuVersion) == 0 ? "0.0" : massiveSkuVersion;
	}

	// FUNCTION: ENGINE 0x108928C0
	unsigned int SkuInfo::GetLanguageCount()
	{
		return languages.Size();
	}

	// FUNCTION: ENGINE 0x108928D0
	SkuInfo::Language* SkuInfo::GetLanguage(unsigned int index)
	{
		return languages.begin + index;
	}

	// FUNCTION: ENGINE 0x10892840
	content::MemberList* SkuInfo::Language::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberCharArrayMetaType<0>(0x20, "p"), ENGINE_OFFSET(Language, language), "language" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10892CE0
	content::MemberList* SkuInfo::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetArrayDynamicMetaType<SkuInfo, LanguageArray>(content::GetClassMetaType<Language>(), "p"),
				ENGINE_OFFSET(SkuInfo, languages), "supportedLanguages" },
			{ content::GetMemberCharArrayMetaType<1>(0x20, "p"), ENGINE_OFFSET(SkuInfo, massiveSkuName),
				"massiveSkuName" },
			{ content::GetMemberCharArrayMetaType<2>(8, "p"), ENGINE_OFFSET(SkuInfo, massiveSkuVersion),
				"massiveSkuVersion" }
		};
		sList.members = sMembers;
		sList.count = 3;
		return &sList;
	}

	// FUNCTION: ENGINE 0x10892E60
	SkuInfo::SkuInfo()
	{
		massiveSkuName[0] = 0;
		massiveSkuVersion[0] = 0;
	}

}

namespace container
{
	template class ArrayDynamic<engine::SkuInfo::Language, AllocatorNew>;
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108926F0
// FUNCTION: ENGINE 0x10892700
// FUNCTION: ENGINE 0x10892710
// FUNCTION: ENGINE 0x10892770
// FUNCTION: ENGINE 0x10892780
// FUNCTION: ENGINE 0x108927C0
// FUNCTION: ENGINE 0x108927F0
// FUNCTION: ENGINE 0x10892830
// FUNCTION: ENGINE 0x108928E0
// FUNCTION: ENGINE 0x108928F0
// FUNCTION: ENGINE 0x10892950
// FUNCTION: ENGINE 0x10892960
// FUNCTION: ENGINE 0x10892970
// FUNCTION: ENGINE 0x10892980
// FUNCTION: ENGINE 0x108929D0
// FUNCTION: ENGINE 0x108929E0
// FUNCTION: ENGINE 0x108929F0
// FUNCTION: ENGINE 0x10892A10
// FUNCTION: ENGINE 0x10892A30
// FUNCTION: ENGINE 0x10892A60
// FUNCTION: ENGINE 0x10892A90
// FUNCTION: ENGINE 0x10892AA0
// FUNCTION: ENGINE 0x10892AB0
// FUNCTION: ENGINE 0x10892B00
// FUNCTION: ENGINE 0x10892B30
// FUNCTION: ENGINE 0x10892B70
// FUNCTION: ENGINE 0x10892B80
// FUNCTION: ENGINE 0x10892BD0
// FUNCTION: ENGINE 0x10892BF0
// FUNCTION: ENGINE 0x10892CA0
// FUNCTION: ENGINE 0x10892DC0
// FUNCTION: ENGINE 0x10892DE0
// FUNCTION: ENGINE 0x10892E20
// FUNCTION: ENGINE 0x10892EB0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108927B0
// FUNCTION: ENGINE 0x10892820
// FUNCTION: ENGINE 0x10892E90
// FUNCTION: ENGINE 0x108E0ED0
