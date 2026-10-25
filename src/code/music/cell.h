// The cells of the music library (RTTI: music::Cell and music::MGraphCell): the unit a cue plays. A cell fades in and
// out with a pair of music::Fade, says what follows it, and answers the serialisation slots (text and binary) through
// the description of its own class. Member names come from the strings the reflection registers them under.
#ifndef MUSIC_CELL_H
#define MUSIC_CELL_H

#include "code/music/cellplayer.h"
#include "code/music/time.h"
#include "code/om/allocation.h"
#include "code/om/metaclass.h"
#include "code/om/metatype.h"
#include "code/om/name.h"

namespace music
{
	// What a cell owns (its destructor and slot 1 are called when the cell goes)
	class CellOwned
	{
	public:
		virtual ~CellOwned();
		virtual void Slot1();
	};

	// The description a cell is made from (only the patch name is known)
	struct CellSource
	{
		char unknown0[0x10];
		om::ClassName patchName;  // 0x10
	};

	class Cell
	{
	public:
		// 0x105DFCA0
		Cell();
		OM_ALLOCATION(Cell);
		// Slot 0 (0x105DFC50 is the body, the deleting destructor 0x105DFD00)
		virtual ~Cell()
		{
			if (owned != 0)
			{
				owned->Slot1();
			}
			delete owned;
		}
		// Slots 1 to 4 (0x105DFA50 / 0x105DFA70 / 0x105DFA90 / 0x105E0D90): the cell through the description of its class
		virtual bool ReadText(const om::TextValue* text);
		virtual void WriteText(om::TextValue* text);
		virtual bool ReadBinary(om::BinaryStream* stream);
		virtual bool WriteBinary(om::BinaryStream* stream);
		// Slots 5 to 7 (0x105DFAD0 / 0x105DFAC0): true and nothing, whatever the argument is; and the copy of the cell
		// made through its serialisation (0x105DFAE0)
		virtual bool Slot5(int unknown);
		virtual void Slot6(const void* unknown);
		virtual Cell* Clone();
		// Slot 8 (0x105E0DD0): the description of the class
		virtual om::MetaTypeBase* GetMetaType()
		{
			om::MetaTypeBase*& cache = om::MetaTypeCache<Cell>::type;
			if (cache == 0)
			{
				cache = om::FindMetaType(typeid(Cell));
			}
			return cache;
		}
		// Slot 9 (0x105DFAB0 answers nothing, 0x105E0E10): the description of the class of the player that plays the cell
		virtual om::MetaTypeBase* GetPlayerMetaType()
		{
			return 0;
		}

		// 0x105DF9C0 / 0x105DF9D0 and 0x105DF9F0 / 0x105DFA00
		const Fade& GetFadeIn() const;
		void SetFadeIn(const Fade& newFadeIn);
		const Fade& GetFadeOut() const;
		void SetFadeOut(const Fade& newFadeOut);
		// 0x105D2840 / 0x105DFA20
		const FollowAction& GetFollowAction() const;
		void SetFollowAction(const FollowAction& newFollowAction);

		Fade fadeIn;  // 4
		Fade fadeOut;  // 0x2C
		FollowAction followAction;  // 0x54
		CellOwned* owned;  // 0x58
	};

	class MGraphCell : public Cell
	{
	public:
		// Inlined by the users (the engine's own copy is 0x105E01B0)
		MGraphCell()
		{
		}
		OM_ALLOCATION(MGraphCell);
		// Slot 0 (0x105E01F0 is the body, the deleting destructor 0x105E0240)
		virtual ~MGraphCell()
		{
		}
		// Slots 1 and 2 (0x105E0280 / 0x105E0290): the base class's
		virtual bool ReadText(const om::TextValue* text)
		{
			return Cell::ReadText(text);
		}
		virtual void WriteText(om::TextValue* text)
		{
			Cell::WriteText(text);
		}
		// Slots 3 and 4 (0x105E24A0 / 0x105E23F0)
		virtual bool ReadBinary(om::BinaryStream* stream);
		virtual bool WriteBinary(om::BinaryStream* stream);
		// Slot 6 (0x105E02E0): takes the patch name of the cell's source (a CellSource)
		virtual void Slot6(const void* source);
		// Slots 8 and 9 (0x105E0DF0 / 0x105E0E10)
		virtual om::MetaTypeBase* GetMetaType()
		{
			om::MetaTypeBase*& cache = om::MetaTypeCache<MGraphCell>::type;
			if (cache == 0)
			{
				cache = om::FindMetaType(typeid(MGraphCell));
			}
			return cache;
		}
		virtual om::MetaTypeBase* GetPlayerMetaType();

		// 0x105DFA30 / 0x105E0220
		const om::ClassName& GetPatchName() const;
		void SetPatchName(const om::ClassName& newPatchName);

		om::ClassName patchName;  // 0x60
	};
}

namespace om
{
	// The cells that can be made from nothing: the description of their class creates and destroys them
	template<> int MetaClass<music::MGraphCell>::Slot5();
	template<> void MetaClass<music::MGraphCell>::Slot6(void* object);
}

#endif
