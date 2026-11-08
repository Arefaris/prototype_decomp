// The unlockables of the game (RTTI and reflection names, namespace proto): the enumerations of the unlockables
// manager's reflection and the classes of the unlock list. Unit 0x10578EA0 - 0x1057F000 (no assert path; the file
// name is a guess). Only the reflection of the enumerations and the class infos are reconstructed.
#ifndef PROTO_UNLOCKABLES_H
#define PROTO_UNLOCKABLES_H

#include "code/content/loadinventory.h"
#include "code/content/metatype.h"
#include "code/core/name.h"

namespace proto
{
	// Every unlockable item (484 reflected values, see unlockables.cpp)
	enum Unlockable
	{
		UNLOCKABLE_NONE = 0
	};

	// What kind of thing an unlockable is
	enum UnlockableType
	{
		UNLOCKABLE_TYPE_POWER = 0
	};

	// What an unlockable is bought with or as (21 reflected values)
	enum PurchaseType
	{
		PURCHASE_TYPE_EP = 0
	};

	// How necessary an unlockable is
	enum NecessityType
	{
		NECESSITY_GENERAL = 0,
		NECESSITY_CORE = 1
	};

	// How the multipliers of the unlock table are applied
	enum UnlockableMultiplierConfig
	{
		MULTIPLIER_NONE = 0,
		MULTIPLIER_INTERLACED = 1
	};

	class UnlockablesList;

	// The table of the progress flags of the unlockables (RTTI proto::UnlockTable; the one table is gUnlockTable at
	// 0x112738B8). Four flags per unlockable are kept in the byte of the game database's "Unlockables" subject the
	// unlockable falls in (four unlockables to a word). The first argument of the accessors is the player (always 0).
	class UnlockTable
	{
	public:
		// The one virtual function is the deleting destructor (0x1001C5BC through the vftable 0x10E28254)
		virtual ~UnlockTable();

		// 0x10579310 / 0x10579370: bit 0 (the script natives unlockable_IsAvailable / unlockable_SetIsAvailable)
		bool IsAvailable(int player, int unlockable);
		void SetAvailable(int player, int unlockable, bool on);
		// 0x10579390: bit 1 (unlockable_IsAcquired)
		bool IsUnlocked(int player, int unlockable);
		// 0x10579450: bit 2 (unlockable_SetIsActivated; the getter is fightitems::motion::IsUnlockableAvailable 0x105793F0,
		// unlockable_IsActivated)
		void SetActivated(int player, int unlockable, bool on);
		// 0x10579470 / 0x105794D0: bit 3 (unlockable_HasDisplayedInFE / unlockable_SetDisplayedInFE)
		bool HasDisplayedInFE(int player, int unlockable);
		void SetDisplayedInFE(int player, int unlockable, bool on);
		// 0x10579560: sets the flag of the bit 2 of every unlockable (484; unlockable_SetIsActivatedAll)
		void SetAllActivated(int player, bool on);
		// 0x105792D0: tells the scenario that an unlockable was acquired
		void SendAcquired(int unlockable);
		// 0x10579600: how many of the unlockables from first to last are unlocked
		int CountUnlocked(int first, int last);
		// 0x105795D0: empties the count of one purchase type (unlockable_ClearPurchaseTypeCount)
		void ClearPurchaseTypeCount(int purchaseType);
		// 0x105795C0 (um_GetCategoryPurchaseType)
		int GetCategoryPurchaseType();
		// The script natives um_*: a list of the manager (0 - 6) and the index of an entry in it; an entry that is not
		// there answers 0 / false
		// 0x10579BF0 / 0x10579C40 / 0x1057A0E0 / 0x1057A130 / 0x1057A180: the entry's members
		int GetUnlockableEnum(unsigned int list, int index);
		int GetNecessityType(unsigned int list, int index);
		int GetPurchaseType(unsigned int list, int index);
		int GetPurchaseCost(unsigned int list, int index);
		int* GetFEIdentifier(unsigned int list, int index);
		// 0x1057A1D0
		int GetUnlockablesListCount(unsigned int list);
		// 0x10579C90 / 0x10579D80 / 0x10579DE0: whether the entry's unlockable is available / acquired / displayed
		bool GetAvailable(unsigned int list, int index);
		bool GetAcquired(unsigned int list, int index);
		bool GetDisplayedInFE(unsigned int list, int index);
		// 0x10579CF0: whether the entry is available and its prerequisite is acquired
		bool GetPrerequisiteSatisfied(unsigned int list, int index);
		// 0x1057A200: marks the entry's unlockable displayed or not
		void SetDisplayedInFE(unsigned int list, int index, bool displayed);
		// 0x105795A0 / 0x105795B0: the unlockable the front end is looking at (um_SetUnlockableOfInterest /
		// um_GetUnlockableOfInterest)
		void SetUnlockableOfInterest(int unlockable);
		int GetUnlockableOfInterest();

		UnlockablesList* lists[7];  // +4
		unsigned char unknown20[0x204];
		int unlockableOfInterest;  // +0x224
	};
	extern UnlockTable* gUnlockTable;

	// 0x10579280: deletes the table
	void Unknown10579280();

	// One unlockable of the list (0x20 bytes; the members the script natives of the manager answer, names guessed)
	struct UnlockableInfo
	{
		// 0x10579010
		static content::ClassInfo* GetClassInfo();

		int unlockable;  // +0 (a proto::Unlockable)
		int feIdentifier;  // +4 (the front end identifier; the native answers its address)
		int purchaseType;  // +8
		int purchaseCost;  // +0xC
		core::Name<core::CaseSensitiveKey> name;  // +0x10
		int prerequisite;  // +0x18 (an unlockable that has to be acquired first, 0 for none)
		int necessityType;  // +0x1C
	};

	// The list of the unlockables (RTTI proto::UnlockablesList, a load object; only the entries are recovered)
	class UnlockablesList : public content::MetaLoadObject
	{
	public:
		// 0x10579050
		static content::ClassInfo* GetClassInfo();

		unsigned int GetCount() const
		{
			return end - begin;
		}

		UnlockableInfo* begin;  // +8
		UnlockableInfo* end;  // +0xC
		UnlockableInfo* capacity;  // +0x10
	};
}

#endif
