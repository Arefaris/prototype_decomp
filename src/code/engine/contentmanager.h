// engine::ContentManager (RTTI names): the definitions the content manager loads, all reflected: the cement file
// definition (the list of cement collections and the files of each), the package key (a package id and its files)
// and the package definition (id, category, flags, localized names and files). Unit 0x108E4510 - 0x108E7C00 (no assert
// path; the file name is a guess). The reflected names are original, the rest is guessed.
#ifndef ENGINE_CONTENTMANAGER_H
#define ENGINE_CONTENTMANAGER_H

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/content/stringmetatype.h"
#include "code/core/name.h"

namespace engine
{
	class ContentManager
	{
	public:
		// The name of a file (RTTI engine::ContentManager::FileName; 4 bytes): an owned copy of the text
		class FileName
		{
		public:
			// 0x108E7B10
			FileName();
			// 0x108E7B20
			~FileName();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x108E7B30: the text, "" when there is none
			const char* GetText();
			// 0x108E7B40
			void SetText(const char* value);

			char* text;  // +0
		};

		typedef container::ArrayDynamic<FileName, container::AllocatorNew> FileArray;

		// The cement collections of the content library
		class ContentCementFileDefinition : public content::MetaLoadObject
		{
		public:
			// One collection (RTTI ...::ContentCementFileDefinition::Collection; 0x28 bytes): a name, the cement files
			// that make it and the libraries opened for them
			class Collection
			{
			public:
				// 0x108E5D20
				Collection();
				// 0x108E5CE0 (the copies share the library list)
				Collection(const Collection& other) : name(other.name), files(other.files), opened(other.opened),
					libraries(other.libraries), unknown20(other.unknown20), unknown24(other.unknown24)
				{
				}
				Collection& operator=(const Collection& other)
				{
					name = other.name;
					files = other.files;
					opened = other.opened;
					libraries = other.libraries;
					unknown20 = other.unknown20;
					unknown24 = other.unknown24;
					return *this;
				}
				// 0x108E5D40 (frees the library list)
				~Collection();

				static content::ClassInfo* GetClassInfo();
				static content::MemberList* GetMembers();

				core::Name<core::CaseSensitiveKey> name;  // +0
				FileArray files;  // +8
				// The word behind the array
				int unknown14;
				bool opened;  // +0x18
				void* libraries;  // +0x1C
				int unknown20;
				int unknown24;
			};

			typedef container::ArrayDynamic<Collection, container::AllocatorNew> CollectionArray;

			ContentCementFileDefinition();
			virtual ~ContentCementFileDefinition();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// vftable slot 3 (0x108E4650): becomes the manager's current definition
			virtual void Slot3(int unused);

			CollectionArray collections;  // +8
			// The word behind the array
			int unknown14;
		};

		// A package definition: id, category, flags, the names it is shown under and its files
		class ContentPackageDefinition : public content::MetaLoadObject
		{
		public:
			// One localized name (RTTI ...::ContentPackageDefinition::LocalizedName; 0x10 bytes)
			class LocalizedName
			{
			public:
				// 0x108E6B60
				LocalizedName();
				// 0x108E6F70 / 0x108E6EF0 (the copies share the text)
				LocalizedName(const LocalizedName& other) : language(other.language), text(other.text)
				{
				}
				LocalizedName& operator=(const LocalizedName& other)
				{
					language = other.language;
					text = other.text;
					return *this;
				}
				// 0x108E6B80 (frees the text)
				~LocalizedName();

				static content::ClassInfo* GetClassInfo();
				static content::MemberList* GetMembers();

				// 0x108E6A90 / 0x108E6A50
				const char* GetText();
				void SetText(const char* value);

				__declspec(align(8)) core::Name<core::CaseSensitiveKey> language;  // +0
				char* text;  // +8
			};

			typedef container::ArrayDynamic<LocalizedName, container::AllocatorNew> NameArray;

			// 0x108E7910
			ContentPackageDefinition();
			virtual ~ContentPackageDefinition();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// vftable slot 3 (0x108E69C0): joins the list of definitions
			virtual void Slot3(int unused);

			// 0x108E69E0 / 0x108E69F0
			const char* GetCategoryName();
			void SetCategoryName(const char* value);

			unsigned int packageId;  // +8
			unsigned int category;  // +0xC
			char* categoryName;  // +0x10
			NameArray names;  // +0x14
			// The word behind the array
			int unknown20;
			bool keyTransferable;  // +0x24
			bool onlineRequired;  // +0x25
			bool transferable;  // +0x26
			bool ownerOnly;  // +0x27
			FileArray files;  // +0x28
			// The word behind the array
			int unknown34;
			ContentPackageDefinition* next;  // +0x38
		};

		// A package key: the id of a package and its files
		class ContentPackageKey : public content::MetaLoadObject
		{
		public:
			// 0x108E77F0
			ContentPackageKey();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// vftable slot 3 (0x108E6A30): joins the list of keys
			virtual void Slot3(int unused);

			unsigned int packageId;  // +8
			FileArray files;  // +0xC
			// The word behind the array
			int unknown18;
			ContentPackageKey* next;  // +0x1C
		};
	};

	// The manager's lists and its current cement definition (names guessed): 0x1131AC78, 0x1131ADEC, 0x1131ADF0
	extern ContentManager::ContentCementFileDefinition* gCementDefinition;
	extern ContentManager::ContentPackageDefinition** gPackageDefinitions;
	extern ContentManager::ContentPackageKey** gPackageKeys;
}

namespace container
{
	template<> struct ArrayReserveBeginFirst<engine::ContentManager::FileName>
	{
		enum
		{
			value = 1
		};
	};
	template<> struct ArrayReserveBeginFirst<engine::ContentManager::ContentCementFileDefinition::Collection>
	{
		enum
		{
			value = 1
		};
	};
	template<> struct ArrayEraseInline<engine::ContentManager::FileName>
	{
		enum
		{
			value = 3
		};
	};
	template<> struct ArrayEraseInline<engine::ContentManager::ContentCementFileDefinition::Collection>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<engine::ContentManager::ContentPackageDefinition::LocalizedName>
	{
		enum
		{
			value = 0
		};
	};
}

namespace content
{
	// Whether the helper of an element type inserts its default element through the counted Insert (shift, then fill)
	template<class T> struct ContentManagerInsertFill
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ContentManagerInsertFill<engine::ContentManager::ContentCementFileDefinition::Collection>
	{
		enum
		{
			value = 1
		};
	};
}

// The element access of the manager's arrays for their meta types: the default element the reflection inserts is kept
// in a static of the helper (Default)
#define CONTENT_MANAGER_ARRAY_HELPER(ARRAY) \
	namespace content \
	{ \
		template<> class ArrayDynamicHelper<ARRAY> : public ArrayDynamicHelperBase \
		{ \
		public: \
			typedef ARRAY A; \
			typedef A::Element T; \
			\
			static T& Default() \
			{ \
				static T sDefault; \
				return sDefault; \
			} \
			\
			virtual int Size(void* array) \
			{ \
				return ((A*)array)->Size(); \
			} \
			virtual void* Get(void* array, int index) \
			{ \
				return &(*(A*)array)[index]; \
			} \
			virtual void* GetConst(void* array, int index) \
			{ \
				return &(*(A*)array)[index]; \
			} \
			virtual void Insert(void* array, int index, int unused) \
			{ \
				A* a = (A*)array; \
				if (a->Size() >= a->Capacity()) \
				{ \
					a->Reserve(a->Size() + 1); \
				} \
				T* position = a->begin + index; \
				if (ContentManagerInsertFill<T>::value) \
				{ \
					a->Insert(position, 1, Default()); \
				} \
				else \
				{ \
					a->Insert(position, Default()); \
				} \
			} \
			virtual void Erase(void* array, int index, int unused) \
			{ \
				A* a = (A*)array; \
				a->Erase(a->begin + index); \
			} \
			virtual int Capacity(void* array) \
			{ \
				return ((A*)array)->Capacity(); \
			} \
			virtual void Expand(void* array, unsigned int count) \
			{ \
				A* a = (A*)array; \
				if (a->Capacity() == 0) \
				{ \
					a->Allocate(count); \
				} \
				else if (count + a->Size() > a->Capacity()) \
				{ \
					a->Reserve(count + a->Size()); \
				} \
			} \
		}; \
	}

CONTENT_MANAGER_ARRAY_HELPER(engine::ContentManager::FileArray)
CONTENT_MANAGER_ARRAY_HELPER(engine::ContentManager::ContentCementFileDefinition::CollectionArray)
CONTENT_MANAGER_ARRAY_HELPER(engine::ContentManager::ContentPackageDefinition::NameArray)

#endif
