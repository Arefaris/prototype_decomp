// engine::NamedInventoryCreator (RTTI and reflection names): a content library object that creates an inventory
// (a table of named load objects) when it is loaded and registers it in the root inventory under its name; taking it
// away again removes the inventory. Unit 0x1090D720 - 0x1090DA00 (no assert path; the directory and file name are
// guesses). The reflected member names are original; the rest is guessed.
#ifndef ENGINE_NAMEDINVENTORYCREATOR_H
#define ENGINE_NAMEDINVENTORYCREATOR_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"

namespace engine
{
	class NamedInventoryCreator : public content::MetaLoadObject
	{
	public:
		// 0x1090D9B0
		NamedInventoryCreator();
		// 0x1090D7F0 (deleting destructor 0x1090D9E0)
		virtual ~NamedInventoryCreator();

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		// vftable slot 3 (0x1090D810): creates the inventory, rounding its size up to a power of two, and adds it to
		// the root inventory
		virtual void Slot3(int unused);
		// vftable slot 4 (0x1090D880): takes the inventory out of the root inventory and drops it once it is done
		virtual bool IsReady();

		core::Name<core::CaseSensitiveKey> inventoryName;  // +8
		unsigned int initialSize;  // +0x10
		content::LoadInventory* inventory;  // +0x14
	};
}

#endif
