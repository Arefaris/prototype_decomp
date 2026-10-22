// engine::SkuInfo (RTTI and reflection names): a content library object loaded from "skuinfo.p3d" that names the
// edition of the game (the advertising service's SKU name and version) and lists the languages it supports. The one
// that was loaded last is the current one (gSkuInfo). Unit 0x108925F0 - 0x10893070 (no assert path; the directory
// and file name are guesses). The reflected member names are original; the rest is guessed.
#ifndef ENGINE_SYSTEM_SKUINFO_H
#define ENGINE_SYSTEM_SKUINFO_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/content/stringmetatype.h"

namespace engine
{
	class SkuInfo : public content::MetaLoadObject
	{
	public:
		// One supported language
		class Language
		{
		public:
			// 0x10892A10 is its copy constructor (inline)
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			char language[0x20];  // +0
		};

		typedef container::ArrayDynamic<Language, container::AllocatorNew> LanguageArray;

		// 0x10892E60
		SkuInfo();
		// 0x10892E90 (deleting destructor 0x10893070)

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// 0x10892670: lets go of the current SKU info
		static void Shutdown();
		// 0x10892690
		static SkuInfo* GetCurrent();
		// 0x10892F10: loads "skuinfo.p3d" into the heap (a default SKU info when there is no such file)
		static void Load(int heap);

		// vftable slot 3 (0x108926A0): the loading is done, this becomes the current SKU info
		virtual void Slot3(int unused);

		// 0x108926B0 / 0x108926D0: the names, or the defaults when they are empty
		const char* GetMassiveSkuName() const;
		const char* GetMassiveSkuVersion() const;
		// 0x108928C0 / 0x108928D0
		unsigned int GetLanguageCount();
		Language* GetLanguage(unsigned int index);

		LanguageArray languages;  // +8
		// The word behind the array (the arrays of this kind are followed by one; never touched here)
		int unknown14;  // +0x14
		char massiveSkuName[0x20];  // +0x18
		char massiveSkuVersion[8];  // +0x38
	};

	// 0x113176C8
	extern SkuInfo* gSkuInfo;
}

#endif
