// The fight track that shows and hides the primitives of an object's drawable (RTTI: engine::PrimitiveDisplayTrack) with
// its reflected parts: a property for the time it begins at, a property that holds a list of per-primitive properties
// (fight::PropertyPropertyList) and an enum property for each of them (On / Off / Ignore); and its action. Unit
// 0x108AEDB0 - 0x108AF910 (no assert path; the file name is a guess); the member names are guesses.
#ifndef ENGINE_FIGHT_PRIMITIVEDISPLAYTRACK_H
#define ENGINE_FIGHT_PRIMITIVEDISPLAYTRACK_H

#include "code/core/linklist.h"
#include <new>
#include "code/engine/fight/trackfactory.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/engine/message.h"

namespace fight
{
	// The property of a list of properties of a track (RTTI: fight::PropertyPropertyList<T>, 10 vftable slots): the track
	// tells how many items it has, gives each item's property and takes a new count. The three members are stored at +0x10
	template<class T> class PropertyPropertyList : public PropertyTypePropertyList
	{
	public:
		typedef int (T::*CountGetter)();
		typedef Property* (T::*ItemGetter)(int);
		typedef bool (T::*CountSetter)(int);

		PropertyPropertyList(const char* name, CountGetter getCount, ItemGetter getItem, CountSetter setCount)
			: PropertyTypePropertyList(name), m_getCount(getCount), m_getItem(getItem), m_setCount(setCount)
		{
		}

		// vftable slot 1
		virtual bool IsNull() const
		{
			return false;
		}

		// vftable slots 7 - 9
		virtual int GetCount(int object)
		{
			return (reinterpret_cast<T*>(object)->*m_getCount)();
		}
		virtual Property* GetItem(int object, int index)
		{
			return (reinterpret_cast<T*>(object)->*m_getItem)(index);
		}
		virtual void SetCount(int object, int count)
		{
			(reinterpret_cast<T*>(object)->*m_setCount)(count);
		}

		CountGetter m_getCount;
		ItemGetter m_getItem;
		CountSetter m_setCount;
	};
}

namespace engine
{
	// Shows or hides several primitives at once (RTTI: engine::ShowMultipleMessage, type 8, id 1); the object takes the
	// primitives by the hash of their names
	struct PrimitiveVisibility
	{
		unsigned __int64 hash;
		bool visible;
	};

	struct ShowMultipleMessage : public IntrusiveMessage
	{
		// 0x108AEDE0
		ShowMultipleMessage(PrimitiveVisibility* newItems, int newCount) : IntrusiveMessage(8, 1)
		{
			items = newItems;
			count = newCount;
		}
		// 0x108AEF00 is the deleting destructor
		virtual ~ShowMultipleMessage()
		{
		}

		PrimitiveVisibility* items;  // +0xC
		int count;  // +0x10
	};

	// The names of the table On / Off / Ignore and the empty name the enum properties answer with a bad index
	extern fight::EnumEntry gOnTable[3];
	extern core::Name<core::CaseSensitiveKey> gEmpty81;

	// The first of the track's properties (RTTI: engine::PrimitiveDisplayTrackPropertyTimeBegin, 9 vftable slots): the
	// float lives in the property itself
	class PrimitiveDisplayTrackPropertyTimeBegin : public fight::PropertyTypeFloat
	{
	public:
		// 0x108AF130
		PrimitiveDisplayTrackPropertyTimeBegin(const char* name) : fight::PropertyTypeFloat(name), value(0.0f)
		{
		}

		// vftable slot 7 (0x108AF170) and 8 (0x108AF160)
		virtual bool Set(void* object, float newValue);
		virtual float GetValue(void* object);

		float value;  // +0x10
	};

	// What a primitive is set to (RTTI: engine::PrimitiveDisplayTrackPropertyEnumPrimitiveDisplay, 11 vftable slots):
	// one of the names of gOnTable; the value is in the property itself
#pragma pack(push, 4)
	class PrimitiveDisplayTrackPropertyEnumPrimitiveDisplay : public fight::PropertyTypeEnum
	{
	public:
		// 0x108AF0E0 (left to the engine: it makes the property's name from a one-word argument the base class takes
		// by value)
		PrimitiveDisplayTrackPropertyEnumPrimitiveDisplay();

		// vftable slots 7 - 10 (0x108AEE30, 0x108AEE20, 0x108AF120, 0x108AF110)
		virtual const fight::EnumEntry* GetEntry(void* object, int index);
		virtual int GetCount(void* object) const;
		virtual bool Set(void* object, int newValue);
		virtual int GetValue(void* object);

		int value;  // +0x10
		int unknown14;
	};
#pragma pack(pop)

	// RTTI: engine::PrimitiveDisplayTrack (16 vftable slots, 0x50 bytes)
	class PrimitiveDisplayTrack : public fight::Track
	{
	public:
		// 0x108AF7D0
		PrimitiveDisplayTrack();
		// 0x108AF860 (the deleting destructor is 0x108AF910)
		virtual ~PrimitiveDisplayTrack();

		// vftable slot 0 (0x108AEE70): the first property is the time, the following ones the primitives'
		virtual fight::Property* GetProperty(int index);
		// vftable slot 1 (0x108AEEA0): the time and the list
		virtual fight::Property* Slot1(int index);
		// vftable slot 3 (0x108AEF40)
		virtual void Slot3(int arg);
		// vftable slot 9 (0x108AF840) and 10 (0x108AF850)
		virtual float GetTimeBegin() const;
		virtual float Slot10() const;
		// vftable slot 15 (0x108AF8B0)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// The three members the list property calls (0x108AEDB0, 0x108AEE50, 0x108AF350)
		int GetPrimitiveCount();
		fight::Property* GetPrimitive(int index);
		bool SetPrimitiveCount(int newCount);
		// 0x108AF790: forgets the time and the primitives
		void Reset();
		// 0x108AF320: forgets the primitives
		void ClearPrimitives();
		// The block the primitives are in starts with their count
		void FreePrimitives()
		{
			if (primitives != 0)
			{
				::operator delete[]((void*)((char*)primitives - 4));
			}
		}

		// 0x108AEFF0 / 0x108AF000: the track has no properties to build or free
		static void RegisterProperties();
		static void ClearProperties();

		PrimitiveDisplayTrackPropertyTimeBegin timeBegin;  // +0x10
		PrimitiveDisplayTrackPropertyEnumPrimitiveDisplay* primitives;  // +0x28: the items, their count in the word before
		int primitiveCount;  // +0x2C
		fight::PropertyPropertyList<PrimitiveDisplayTrack> primitiveList;  // +0x30
	};

	// RTTI: engine::PrimitiveDisplayAction (9 vftable slots, 0x2C bytes): sets the primitives of the object
	class PrimitiveDisplayAction : public fight::Action
	{
	public:
		// 0x108AF400
		PrimitiveDisplayAction(PrimitiveDisplayTrack* newTrack, GameObjectHandle newTarget);
		// 0x108AF1E0 (the deleting destructor is 0x108AF470)
		virtual ~PrimitiveDisplayAction();

		// vftable slot 5 (0x108AF490)
		virtual bool Slot5(int arg, float value);

		core::Link<PrimitiveDisplayTrack> link;  // +0x1C
		GameObjectHandle target;  // +0x28
	};
}

#endif
