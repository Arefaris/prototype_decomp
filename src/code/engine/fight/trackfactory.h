// The fight tracks the engine registers with the fight system and the factory machinery that builds them: a
// reflected property per track member (fight::Property and its type classes), the factory the game looks a track up
// with (fight::TrackFactory / fight::TrackFactoryCaster and their per-class templates) and the tracks themselves.
// Unit 0x108078E0 - 0x10809000 and on (no assert path; the file name is a guess). Class and member names are guesses
// until the binary tells the real ones; the layouts, the vftable slots and the property names come from the code.
#ifndef ENGINE_FIGHT_TRACKFACTORY_H
#define ENGINE_FIGHT_TRACKFACTORY_H

#include "code/content/loadinventory.h"
#include "code/core/name.h"
#include "code/core/strings.h"
#include "code/engine/fight/branch.h"
#include "code/engine/fight/listobject.h"
#include "code/engine/fight/sequencer.h"
#include "code/math/colour128.h"
#include "code/math/vector.h"

namespace fight
{
	class TrackFactory;
	class ConditionFactory;
	class BranchFactory;
	class Branch;
	class TrackRegistry;
	class Reader;

	// The engine's names are case sensitive
	typedef core::Name<core::CaseSensitiveKey> Name;

	// A reflected property of a fight node's class (RTTI: fight::Property, 7 vftable slots, 0x10 bytes): the
	// property's name and, in the derived classes, the accessor that reads or writes the member it stands for.
	class __declspec(align(8)) Property
	{
	public:
		Property(const char* name);

		// vftable slot 0: the kind of value the property carries (every type class returns its own id)
		virtual int GetType() const = 0;
		// vftable slot 1: nothing is attached to the property
		virtual bool IsNull() const;
		virtual void Slot2(int object, int other);
		virtual void Slot3(int object, int other);
		virtual void Slot4(int a, int b, int c, int d);
		virtual void Slot5(int a, int b);
		// vftable slot 6: reads the value off a reader and hands it to the property's own setter below
		virtual bool Slot6(int object, int context, void* reader) = 0;

		// 0x105A9C50: replaces the name (not expanded in the constructor)
		__declspec(noinline) void SetName(const Name& newName)
		{
			name = newName;
		}

		// The word between the vftable and the name (the engine's own constructor leaves it alone)
		unsigned int unknown4;
		Name name;
	};

	// The property classes per value kind: each returns its own type id and reads its value off an object
	class PropertyTypeFloat : public Property
	{
	public:
		PropertyTypeFloat(const char* name);

		// vftable slot 0
		virtual int GetType() const;
		// vftable slot 6
		virtual bool Slot6(int object, int context, void* reader);
		// vftable slot 7: writes a value into the member the property stands for
		virtual bool Set(void* object, float value) = 0;
	};

	class PropertyTypeBool : public Property
	{
	public:
		PropertyTypeBool(const char* name);

		// vftable slot 0
		virtual int GetType() const;
		// vftable slot 6
		virtual bool Slot6(int object, int context, void* reader);
		// vftable slot 7
		virtual bool Set(void* object, bool value) = 0;
	};

	class PropertyTypeString : public Property
	{
	public:
		PropertyTypeString(const char* name);

		// vftable slot 0
		virtual int GetType() const;
		// vftable slot 6
		virtual bool Slot6(int object, int context, void* reader);
		// vftable slot 7: the value came in as text
		virtual bool Set(void* object, const char* text) = 0;
	};

	// A name of 32 bits (RTTI: fight::PropertyTypeName32, 9 vftable slots): the text is turned into the name and handed
	// to slot 8 (0x105A8F50 / 0x105A8F70 / 0x105A8FA0)
	class PropertyTypeName32 : public PropertyTypeString
	{
	public:
		PropertyTypeName32(const char* name);

		// vftable slot 6
		virtual bool Slot6(int object, int context, void* reader);
		// vftable slot 7
		virtual bool Set(void* object, const char* text);
		// vftable slot 8
		virtual bool Set(void* object, const core::Name<core::CaseInsensitiveKey32>& value) = 0;
	};

	class PropertyTypeName : public PropertyTypeString
	{
	public:
		PropertyTypeName(const char* name);

		// vftable slot 6
		virtual bool Slot6(int object, int context, void* reader);
		// vftable slot 7: turns the text into a name and hands it to slot 8
		virtual bool Set(void* object, const char* text);
		// vftable slot 8
		virtual bool Set(void* object, const Name& value) = 0;
	};

	// The object a property is handed is the Param part of the class it belongs to (a branch has it behind its other
	// bases); the setters are the class's own
	template<class T> inline T* ObjectOf(void* object)
	{
		return static_cast<T*>(static_cast<Param*>(object));
	}

	// The property of a float member with an optional range, and of a bool or a name member: the setter is the
	// track's own member function, stored as a member pointer in the property (the classes are 0x18 bytes)
	template<class T> class PropertyFloatConstRange : public PropertyTypeFloat
	{
	public:
		typedef bool (T::*Setter)(float);

		PropertyFloatConstRange(const char* name, Setter setter)
			: PropertyTypeFloat(name), m_setter(setter)
		{
		}

		// vftable slot 1
		virtual bool IsNull() const
		{
			return m_setter == 0;
		}

		// vftable slot 7
		virtual bool Set(void* object, float value)
		{
			if (m_setter == 0)
			{
				return false;
			}
			return (static_cast<T*>(object)->*m_setter)(value);
		}

		Setter m_setter;
	};

	template<class T> class PropertyBool : public PropertyTypeBool
	{
	public:
		typedef bool (T::*Setter)(bool);

		PropertyBool(const char* name, Setter setter)
			: PropertyTypeBool(name), m_setter(setter)
		{
		}

		// vftable slot 1
		virtual bool IsNull() const
		{
			return m_setter == 0;
		}

		// vftable slot 7
		virtual bool Set(void* object, bool value)
		{
			if (m_setter == 0)
			{
				return false;
			}
			return (ObjectOf<T>(object)->*m_setter)(value);
		}

		Setter m_setter;
	};

	template<class T> class PropertyName : public PropertyTypeName
	{
	public:
		typedef bool (T::*Setter)(const Name&);

		PropertyName(const char* name, Setter setter)
			: PropertyTypeName(name), m_setter(setter)
		{
		}

		// vftable slot 8
		virtual bool Set(void* object, const Name& value)
		{
			return (static_cast<T*>(object)->*m_setter)(value);
		}

		Setter m_setter;
	};

	// A script text member (RTTI: fight::PropertyTypeScript, 8 vftable slots): the setter at slot 7 takes the text and
	// its length
	class PropertyTypeScript : public Property
	{
	public:
		PropertyTypeScript(const char* name);

		// vftable slot 0
		virtual int GetType() const;
		// vftable slot 6
		virtual bool Slot6(int object, int context, void* reader);
		// vftable slot 7
		virtual bool Set(void* object, const char* text, int length) = 0;
	};

	template<class T> class PropertyScript : public PropertyTypeScript
	{
	public:
		typedef bool (T::*Setter)(const char*, int);

		PropertyScript(const char* name, Setter setter)
			: PropertyTypeScript(name), m_setter(setter)
		{
		}

		// vftable slot 1
		virtual bool IsNull() const
		{
			return m_setter == 0;
		}

		// vftable slot 7
		virtual bool Set(void* object, const char* text, int length)
		{
			if (m_setter == 0)
			{
				return false;
			}
			return (static_cast<T*>(object)->*m_setter)(text, length);
		}

		Setter m_setter;
	};

	// The other kinds of property the tracks and conditions register: an int, a vector, a colour, a group of
	// properties, a group of tracks, a name picked from a list and a value picked from a table of entries. The base
	// classes are another unit's (8 vftable slots, the setter at slot 7, except where said); the derived templates
	// below hold the setter at +0x10 like the three above.
	class PropertyTypeInt : public Property
	{
	public:
		PropertyTypeInt(const char* name);

		// vftable slot 0
		virtual int GetType() const;
		// vftable slot 6
		virtual bool Slot6(int object, int context, void* reader);
		// vftable slot 7
		virtual bool Set(void* object, int value) = 0;
	};

	class PropertyTypeVector : public Property
	{
	public:
		PropertyTypeVector(const char* name);

		// vftable slot 0
		virtual int GetType() const;
		// vftable slot 6
		virtual bool Slot6(int object, int context, void* reader);
		// vftable slot 7
		virtual bool Set(void* object, const math::Vector& value) = 0;
	};

	class PropertyTypeColour : public Property
	{
	public:
		PropertyTypeColour(const char* name);

		// vftable slot 0
		virtual int GetType() const;
		// vftable slot 6
		virtual bool Slot6(int object, int context, void* reader);
		// vftable slot 7
		virtual bool Set(void* object, const math::Colour128& value) = 0;
	};

	// A group of properties (9 vftable slots): slot 7 sets the group's own value, slot 8 hands out the word the
	// group was built with
	class PropertyTypeGroup : public Property
	{
	public:
		PropertyTypeGroup(const char* name);

		// vftable slot 0
		virtual int GetType() const;
		// vftable slot 6
		virtual bool Slot6(int object, int context, void* reader);
		// vftable slot 7
		virtual bool Set(void* object, bool value) = 0;
		// vftable slot 8
		virtual const int* GetMembers() const = 0;
	};

	// A list of the tracks a track owns (RTTI unknown; one word, 0x105A7F10 clears it, 0x105A8140 empties it)
	class TrackGroup
	{
	public:
		// 0x105A7F10
		TrackGroup();
		// 0x105A8140 (a jump to the function below)
		~TrackGroup();
		// 0x105A7FD0: frees the tracks
		void Clear();
		// 0x105A80A0: creates the actions of every track of the group into a sequencer (name guess)
		bool Unknown105A80A0(int a, int b, int c, Sequencer* sequencer);

		// 0x105A7F20 / 0x105A7F40 / 0x105A7F70 / 0x105A7FA0: the number of tracks, the track at an index (twice), the index
		int GetCount() const;
		Track* GetAt(int index);
		const Track* GetAtConst(int index) const;
		int IndexOf(const Track* item) const;
		// 0x105A8010 / 0x105A8040 / 0x105A8070: hands an argument to the slots 2, 3 and 4 of every track
		void ForEachSlot2(int arg);
		void ForEachSlot3(int arg);
		void ForEachSlot4(int arg);
		// 0x105A80F0: hands the tracks of another group, one by one, to the slot 14 of these (name guess)
		void ForEachSlot14(TrackGroup* other, int arg);
		// 0x105A82C0: reads the tracks of a node of the reader (the context is the registry of tracks they are made by)
		bool Load(const Name& key, int context, Reader* reader);
		// 0x105A8150 / 0x105A8330: appends a track / inserts it at an index; answer its index (-1 for none)
		int Add(Track* item);
		int Insert(int index, Track* item);

		Track* head;
	};

	// 0x105A8130: makes a track the first one of a group (the group's own address is the first argument)
	void SetHead(TrackGroup* group, Track* item);

	// The track group's slots 2 - 5 are its own as well; the "setter" hands out the group
	class PropertyTypeTrackGroup : public Property
	{
	public:
		PropertyTypeTrackGroup(const char* name);

		// vftable slot 0
		virtual int GetType() const;
		virtual void Slot2(int object, int other);
		virtual void Slot3(int object, int other);
		virtual void Slot4(int a, int b, int c, int d);
		virtual void Slot5(int a, int b);
		// vftable slot 6
		virtual bool Slot6(int object, int context, void* reader);
		// vftable slot 7
		virtual TrackGroup* Set(void* object) = 0;
	};

	// A node of the fight tree held as a member (RTTI: fight::PropertyTypeItem, 8 vftable slots): its slots 2, 3, 5
	// and 6 pass the call on to the item the "setter" hands out
	class PropertyTypeItem : public Property
	{
	public:
		PropertyTypeItem(const char* name);

		// vftable slot 0
		virtual int GetType() const;
		virtual void Slot2(int object, int other);
		virtual void Slot3(int object, int other);
		virtual void Slot5(int object, int other);
		// vftable slot 6
		virtual bool Slot6(int object, int context, void* reader);
		// vftable slot 7
		virtual Item* Set(void* object) = 0;
	};

	// A named reference to a branch of the fight tree, the way a track holds the branch it hands its result to (0x24
	// bytes; the constructor takes the kind of node the branch is): the branch once it is resolved, the path or the
	// index it is found by, and the context (the registry of tracks) the path is looked up in
	class BranchHolder
	{
	public:
		// 0x105A7600
		explicit BranchHolder(const char* newKind);
		// 0x105A7920
		BranchHolder(const BranchHolder& other);
		// 0x105A7720
		~BranchHolder();
		// 0x105A7760
		BranchHolder& operator=(const BranchHolder& other);

		// 0x105A7590: replaces the path
		void SetPath(const char* text);
		// 0x105A75F0: the branch the path or the index is looked up from (name guess)
		void SetBase(Branch* newBase);
		// 0x105A7630: watches another branch (the first argument is not read)
		void Assign(Branch* unused, Branch* newBranch);
		// 0x105A7660: replaces the path and forgets the branch
		bool SetPathAndClear(const char* text);
		// 0x105A77C0: whether there is a path or an index but no branch yet
		bool IsUnresolved() const;
		// 0x105A77E0: finds the branch the path or the index names, from a branch (name guess)
		bool Resolve(Branch* base);
		// 0x105A78E0 / 0x105A7900: lets go of the branch / of the branch and the context
		bool Clear(Branch* unused);
		void Reset();
		// 0x105A7960: the branch the holder names, looked up the first time
		Branch* GetBranch();
		// 0x105A7690: reads the path, and the index when the reader has a value, from a reader; the context is the
		// branch the holder is looked up from
		bool Load(const Name& key, int context, Reader* reader);
		// 0x105A7980 / 0x105A79C0: copies the path into a buffer (false when there is none)
		bool CopyPath(char* buffer, unsigned int size);
		bool CopyPath(int unused, char* buffer, unsigned int size);

		BranchWatch target;  // +0
		char* path;  // +0xC
		int index;  // +0x10
		Branch* base;  // +0x14
		const char* kind;  // +0x18
		TrackRegistry* context;  // +0x1C
		BranchHolder* nextHolder;  // +0x20: the next holder of the context's list
	};

	// The branch member of a track (RTTI: fight::PropertyTypeBranch, 8 vftable slots): like the track group, slots 2,
	// 3, 5 and 6 are its own; the "setter" hands out the holder
	class PropertyTypeBranch : public Property
	{
	public:
		PropertyTypeBranch(const char* name);

		// vftable slot 0
		virtual int GetType() const;
		virtual void Slot2(int object, int other);
		virtual void Slot3(int object, int other);
		virtual void Slot5(int a, int b);
		// vftable slot 6
		virtual bool Slot6(int object, int context, void* reader);
		// vftable slot 7
		virtual BranchHolder* Set(void* object) = 0;
	};

	// The condition list member of a track (RTTI: fight::PropertyTypeConditionGroup, 8 vftable slots): the same shape
	// as the branch property, and the "setter" hands out the list
	class PropertyTypeConditionGroup : public Property
	{
	public:
		PropertyTypeConditionGroup(const char* name);

		// vftable slot 0
		virtual int GetType() const;
		virtual void Slot2(int object, int other);
		virtual void Slot3(int object, int other);
		virtual void Slot5(int a, int b);
		// vftable slot 6
		virtual bool Slot6(int object, int context, void* reader);
		// vftable slot 7
		virtual ConditionList* Set(void* object) = 0;
	};

	// Replaces a text member by a copy of a new text (0x105AA1F0, another unit): the old text is freed
	char* ReplaceString(char* old, const char* text);

	// A name picked from a list (RTTI: base fight::PropertyTypeStringList, 9 vftable slots: slot 7 of the list is the
	// text setter, slot 8 sets the name)
	class PropertyTypeStringList : public Property
	{
	public:
		PropertyTypeStringList(const char* name);

		virtual int GetType() const;
		virtual bool Slot6(int object, int context, void* reader);
		virtual bool SetText(void* object, const char* text) = 0;
	};

	class PropertyTypeNameList : public PropertyTypeStringList
	{
	public:
		PropertyTypeNameList(const char* name);

		virtual bool Slot6(int object, int context, void* reader);
		virtual bool SetText(void* object, const char* text);
		// vftable slot 8
		virtual bool Set(void* object, const Name& value) = 0;
	};

	// One entry of an enum's table (8 bytes: its text and its value; layout unrecovered)
	struct EnumEntry
	{
		Name name;
	};

	// A value picked from a table of entries (10 vftable slots)
	class PropertyTypeEnum : public Property
	{
	public:
		PropertyTypeEnum(const char* name);

		// vftable slot 0
		virtual int GetType() const;
		// vftable slot 6
		virtual bool Slot6(int object, int context, void* reader);
		// vftable slot 7: the entry at an index (a dummy entry for a bad index)
		virtual const EnumEntry* GetEntry(void* object, int index) = 0;
		// vftable slot 8
		virtual int GetCount(void* object) const = 0;
		// vftable slot 9
		virtual bool Set(void* object, int value) = 0;
	};

	template<class T> class PropertyIntConstRange : public PropertyTypeInt
	{
	public:
		typedef bool (T::*Setter)(int);

		PropertyIntConstRange(const char* name, Setter setter)
			: PropertyTypeInt(name), m_setter(setter)
		{
		}

		// vftable slot 1
		virtual bool IsNull() const
		{
			return m_setter == 0;
		}

		// vftable slot 7
		virtual bool Set(void* object, int value)
		{
			if (m_setter == 0)
			{
				return false;
			}
			return (static_cast<T*>(object)->*m_setter)(value);
		}

		Setter m_setter;
	};

	template<class T> class PropertyVector : public PropertyTypeVector
	{
	public:
		typedef bool (T::*Setter)(const math::Vector&);

		PropertyVector(const char* name, Setter setter)
			: PropertyTypeVector(name), m_setter(setter)
		{
		}

		// vftable slot 1
		virtual bool IsNull() const
		{
			return m_setter == 0;
		}

		// vftable slot 7
		virtual bool Set(void* object, const math::Vector& value)
		{
			if (m_setter == 0)
			{
				return false;
			}
			return (static_cast<T*>(object)->*m_setter)(value);
		}

		Setter m_setter;
	};

	template<class T> class PropertyColour : public PropertyTypeColour
	{
	public:
		typedef bool (T::*Setter)(const math::Colour128&);

		PropertyColour(const char* name, Setter setter)
			: PropertyTypeColour(name), m_setter(setter)
		{
		}

		// vftable slot 1
		virtual bool IsNull() const
		{
			return m_setter == 0;
		}

		// vftable slot 7
		virtual bool Set(void* object, const math::Colour128& value)
		{
			if (m_setter == 0)
			{
				return false;
			}
			return (static_cast<T*>(object)->*m_setter)(value);
		}

		Setter m_setter;
	};

	template<class T> class PropertyGroup : public PropertyTypeGroup
	{
	public:
		typedef bool (T::*Setter)(bool);

		PropertyGroup(const char* name, Setter setter, const int* members)
			: PropertyTypeGroup(name), m_setter(setter), m_members(members)
		{
		}

		// vftable slot 1
		virtual bool IsNull() const
		{
			return m_setter == 0;
		}

		// vftable slot 7
		virtual bool Set(void* object, bool value)
		{
			if (m_setter == 0)
			{
				return false;
			}
			return (static_cast<T*>(object)->*m_setter)(value);
		}

		// vftable slot 8
		virtual const int* GetMembers() const
		{
			return m_members;
		}

		Setter m_setter;
		const int* m_members;
	};

	template<class T> class PropertyBranch : public PropertyTypeBranch
	{
	public:
		typedef BranchHolder* (T::*Setter)();

		PropertyBranch(const char* name, Setter setter)
			: PropertyTypeBranch(name), m_setter(setter)
		{
		}

		// vftable slot 7
		virtual BranchHolder* Set(void* object)
		{
			return (ObjectOf<T>(object)->*m_setter)();
		}

		Setter m_setter;
	};

	template<class T> class PropertyConditionGroup : public PropertyTypeConditionGroup
	{
	public:
		typedef ConditionList* (T::*Setter)();

		PropertyConditionGroup(const char* name, Setter setter)
			: PropertyTypeConditionGroup(name), m_setter(setter)
		{
		}

		// vftable slot 7
		virtual ConditionList* Set(void* object)
		{
			return (ObjectOf<T>(object)->*m_setter)();
		}

		Setter m_setter;
	};

	template<class T> class PropertyString : public PropertyTypeString
	{
	public:
		typedef bool (T::*Setter)(const char*);

		PropertyString(const char* name, Setter setter)
			: PropertyTypeString(name), m_setter(setter)
		{
		}

		// vftable slot 1
		virtual bool IsNull() const
		{
			return m_setter == 0;
		}

		// vftable slot 7
		virtual bool Set(void* object, const char* text)
		{
			if (m_setter == 0)
			{
				return false;
			}
			return (static_cast<T*>(object)->*m_setter)(text);
		}

		Setter m_setter;
	};

	template<class T> class PropertyTrackGroup : public PropertyTypeTrackGroup
	{
	public:
		typedef TrackGroup* (T::*Setter)();

		PropertyTrackGroup(const char* name, Setter setter)
			: PropertyTypeTrackGroup(name), m_setter(setter)
		{
		}

		// vftable slot 7
		virtual TrackGroup* Set(void* object)
		{
			return (ObjectOf<T>(object)->*m_setter)();
		}

		Setter m_setter;
	};

	template<class T> class PropertyNameList : public PropertyTypeNameList
	{
	public:
		typedef bool (T::*Setter)(const Name&);

		PropertyNameList(const char* name, Setter setter)
			: PropertyTypeNameList(name), m_setter(setter)
		{
		}

		// vftable slot 1
		virtual bool IsNull() const
		{
			return m_setter == 0;
		}

		// vftable slot 8
		virtual bool Set(void* object, const Name& value)
		{
			return (static_cast<T*>(object)->*m_setter)(value);
		}

		Setter m_setter;
	};

	// A value picked from an enum the track class describes itself: the entry and the count come from two members of
	// the track (stored as pointers beside the setter)
	template<class T> class PropertyEnum : public PropertyTypeEnum
	{
	public:
		typedef bool (T::*Setter)(int);
		typedef const EnumEntry* (T::*EntryGetter)(int);
		typedef int (T::*CountGetter)();

		PropertyEnum(const char* name, EntryGetter entry, CountGetter count, Setter setter)
			: PropertyTypeEnum(name), m_setter(setter), m_entry(entry), m_count(count)
		{
		}

		// vftable slot 1
		virtual bool IsNull() const
		{
			return m_setter == 0;
		}

		// vftable slot 7
		virtual const EnumEntry* GetEntry(void* object, int index)
		{
			return (static_cast<T*>(object)->*m_entry)(index);
		}

		// vftable slot 8
		virtual int GetCount(void* object) const
		{
			return (static_cast<T*>(object)->*m_count)();
		}

		// vftable slot 9
		virtual bool Set(void* object, int value)
		{
			if (m_setter == 0)
			{
				return false;
			}
			return (static_cast<T*>(object)->*m_setter)(value);
		}

		Setter m_setter;
		EntryGetter m_entry;
		CountGetter m_count;
	};

	template<class T> class PropertyEnumConstList : public PropertyTypeEnum
	{
	public:
		typedef bool (T::*Setter)(int);

		PropertyEnumConstList(const char* name, const EnumEntry* table, int count, Setter setter)
			: PropertyTypeEnum(name), m_setter(setter), m_table(table), m_count(count)
		{
		}

		// vftable slot 1
		virtual bool IsNull() const
		{
			return m_setter == 0;
		}

		// vftable slot 7
		virtual const EnumEntry* GetEntry(void* object, int index)
		{
			if (index >= 0 && index < m_count)
			{
				return &m_table[index];
			}
			return reinterpret_cast<const EnumEntry*>(core::GetStringHeapCounter1());
		}

		// vftable slot 8
		virtual int GetCount(void* object) const
		{
			return m_count;
		}

		// vftable slot 9
		virtual bool Set(void* object, int value)
		{
			if (m_setter == 0)
			{
				return false;
			}
			return (static_cast<T*>(object)->*m_setter)(value);
		}

		Setter m_setter;
		const EnumEntry* m_table;
		int m_count;
	};

	// A value picked from the names a ListObject (the editor's list) holds: the list is the property's second
	// member, beside the setter (the classes are 0x18 bytes)
	template<class T> class PropertyEnumListObject : public PropertyTypeEnum
	{
	public:
		typedef bool (T::*Setter)(int);

		PropertyEnumListObject(const char* name, ListObject* list, Setter setter)
			: PropertyTypeEnum(name), m_setter(setter), m_list(list)
		{
		}

		// vftable slot 1
		virtual bool IsNull() const
		{
			return m_setter == 0;
		}

		// vftable slot 7
		virtual const EnumEntry* GetEntry(void* object, int index)
		{
			return reinterpret_cast<const EnumEntry*>(m_list->GetName(index));
		}

		// vftable slot 8
		virtual int GetCount(void* object) const
		{
			return m_list->GetCount();
		}

		// vftable slot 9
		virtual bool Set(void* object, int value)
		{
			if (m_setter == 0)
			{
				return false;
			}
			return (static_cast<T*>(object)->*m_setter)(value);
		}

		Setter m_setter;
		ListObject* m_list;
	};

	// The list of a track class's properties, built once from a null-terminated array of them (0x105A8420)
	void RegisterPropertyList(Property** properties, Property*** list);
	// Frees a property list and clears it (0x105A9650, used as a track class's clear function)
	void FreePropertyList(Property*** list);

	// The factory of one track class (RTTI: fight::TrackFactory, 2 vftable slots, 0x18 bytes). Its constructor
	// registers the class's properties the first time one of them is asked for.
	class TrackFactory
	{
	public:
		// 0x105A9E40 / 0x105A9E80
		TrackFactory(const char* name, void (*registerProperties)(), void (*clearProperties)());
		~TrackFactory();

		// vftable slot 0 (0x105A9CF0, inherited from every factory)
		virtual void Slot0();
		// vftable slot 1: makes a track of this factory's class
		virtual void* CreateTrack() = 0;

		unsigned int unknown4;
		Name name;
		int unknown10;
		void (*clearProperties)();
	};

	// What the game casts a factory to before asking it for a track (RTTI: fight::TrackFactoryCaster, 2 vftable
	// slots): the vtable alone, the object has no data
	class TrackFactoryCaster
	{
	public:
		// vftable slot 0: whether a factory is of the class this caster knows
		virtual bool IsType(TrackFactory* factory) = 0;
		// vftable slot 1: makes the factory of that class
		virtual TrackFactory* CreateFactory(const char* name) = 0;
	};

	// 0x105A9E90: the factory of a track class, the one the list of load listeners holds already or a
	// new one made through the caster
	TrackFactory* FindTrackFactory(const char* name, TrackFactoryCaster* caster);

	// The factory of one kind of branch (RTTI: fight::BranchFactory, 6 vftable slots, base fight::Entity)
	class BranchFactory : public Entity
	{
	public:
		// 0x105A2690 / 0x105A26B0 (0x105A26C0 is the deleting destructor)
		BranchFactory();
		virtual ~BranchFactory();

		// vftable slot 5: makes a branch
		virtual Branch* CreateBranch() = 0;
	};

	// What the game casts a branch factory to before asking it for a branch (RTTI: fight::BranchFactoryCaster, 2
	// vftable slots; the object is its vftable alone)
	class BranchFactoryCaster
	{
	public:
		// vftable slot 0: whether a factory is of the class this caster knows
		virtual bool IsType(BranchFactory* factory) = 0;
		// vftable slot 1: makes the factory of that class
		virtual BranchFactory* CreateFactory(const char* name) = 0;
	};

	// 0x105A31F0: the factory of a branch class, the one the list of load listeners holds already or a new one made
	// through the caster
	BranchFactory* FindBranchFactory(const char* name, BranchFactoryCaster* caster);

	// The factory of one branch class (RTTI: fight::BranchFactoryTemplate<T>, 6 vftable slots)
	template<class T> class BranchFactoryTemplate : public BranchFactory
	{
	public:
		BranchFactoryTemplate(const char* name)
		{
			SetName(Name(name, 1));
			T::RegisterProperties();
		}
		virtual ~BranchFactoryTemplate()
		{
			T::ClearProperties();
		}

		// vftable slot 5
		virtual Branch* CreateBranch()
		{
			return new T();
		}
	};

	// RTTI: fight::BranchFactoryCasterTemplate<fight::BranchFactoryTemplate<T> >
	template<class F> class BranchFactoryCasterTemplate : public BranchFactoryCaster
	{
	public:
		BranchFactoryCasterTemplate()
		{
		}

		// vftable slot 0
		virtual bool IsType(BranchFactory* factory)
		{
			return dynamic_cast<F*>(factory) != 0;
		}

		// vftable slot 1
		virtual BranchFactory* CreateFactory(const char* name)
		{
			return new F(name);
		}
	};


	// The factories one fight context knows (RTTI: fight::Context, 0xD8 bytes, a load object; the class name here is a
	// guess from its use; another unit's class, only what the fight system's set-up calls is declared)
	class TrackRegistry : public Entity
	{
	public:
		// 0x105A5DB0
		TrackRegistry();
		// 0x105A5D10
		void AddFactory(TrackFactory* factory);
		// 0x105A5CD0
		void AddFactory(ConditionFactory* factory);
		// 0x105A5C90
		void AddFactory(BranchFactory* factory);
		// 0x105A51C0 / 0x105A51D0 (empty bodies): called once all the factories are in
		void Prepare();
		void Complete();
		// 0x105A5330 / 0x105A5350: a holder takes the context in / lets go of it (names guessed)
		void AddHolder(BranchHolder* holder);
		void RemoveHolder(BranchHolder* holder);
		// 0x105A5260: resolves the branch references of the context's nodes
		void ResolveBranchRefs();
		// 0x105A51E0 / 0x105A5520 / 0x105A5460: a loader takes the context in (exclusive: takes the lock for good) /
		// lets go of it / gives the lock back (names guessed)
		void BeginLoading(bool exclusive);
		void EndLoading(bool exclusive);
		void Unlock(bool exclusive);
		// 0x105A5240: marks the context as changed
		void MarkChanged();
		// 0x105A2630 / 0x105A2640 / 0x105A2650: the next context / the same / the root of the tree
		TrackRegistry* GetNext() const;
		TrackRegistry* GetNextOfList() const;
		Branch* GetRootBranch() const;
		// 0x105A5500: makes another context the next one
		void SetNext(TrackRegistry* following);

		// A node of the list the context keeps of what waits to be loaded (the next one at +0x34; names guessed)
		struct PendingItem
		{
			unsigned char unknown0[0x34];
			PendingItem* next;
		};
		// 0x105A52A0 / 0x105A52E0: puts an item at the end of the pending list / takes it out (under the second lock)
		void AddPending(PendingItem* item);
		void RemovePending(PendingItem* item, int unused);

		// 0x105A59D0 / 0x105A5990 / 0x105A5950: the track / condition / branch factory of a name (null when there is none)
		TrackFactory* FindTrackFactory(const Name& key);
		ConditionFactory* FindConditionFactory(const Name& key);
		BranchFactory* FindBranchFactory(const Name& key);

		TrackRegistry* next;  // +0x10: the next context of the load listeners' list
		unsigned char unknown14[0x78];
		// The root branch of the context's tree
		Branch* branches;  // +0x8C
		unsigned char lockA[0x18];  // +0x90
		unsigned char lockB[0x18];  // +0xA8
		int lockCount;  // +0xC0
		unsigned int sharedCount;  // +0xC4
		int exclusiveCount;  // +0xC8
		PendingItem* pending;  // +0xCC
		BranchHolder* holders;  // +0xD0: the holders that name a branch of the context (linked through their words)
		bool changed;  // +0xD4
	};

	template<class T> class TrackFactoryTemplate : public TrackFactory
	{
	public:
		TrackFactoryTemplate(const char* name)
			: TrackFactory(name, T::RegisterProperties, T::ClearProperties)
		{
		}

		// vftable slot 1
		virtual void* CreateTrack()
		{
			return new T();
		}
	};

	template<class T> class TrackFactoryCasterTemplate : public TrackFactoryCaster
	{
	public:
		// 0x108079C0 (out of line): sets the vftable
		TrackFactoryCasterTemplate();

		// vftable slot 0
		virtual bool IsType(TrackFactory* factory)
		{
			return dynamic_cast<TrackFactoryTemplate<T>*>(factory) != 0;
		}

		// vftable slot 1
		virtual TrackFactory* CreateFactory(const char* name)
		{
			return new TrackFactoryTemplate<T>(name);
		}
	};

	// Out of line like the engine's copies (a template member defined outside its class is not inlined)
	template<class T> TrackFactoryCasterTemplate<T>::TrackFactoryCasterTemplate()
	{
	}

	// The factory of one condition class (RTTI: fight::ConditionFactory, 2 vftable slots, 0x18 bytes), built like the
	// track factory
	class ConditionFactory
	{
	public:
		// 0x105A9790 / 0x105A97D0
		ConditionFactory(const char* name, void (*registerProperties)(), void (*clearProperties)());
		~ConditionFactory();

		// vftable slot 0 (0x105A9720, inherited from every factory)
		virtual void Slot0();
		// vftable slot 1: makes a condition of this factory's class
		virtual void* CreateCondition() = 0;

		unsigned int unknown4;
		Name name;
		int unknown10;
		void (*clearProperties)();
	};

	// What the game casts a condition factory to (RTTI: fight::ConditionFactoryCaster, 2 vftable slots)
	class ConditionFactoryCaster
	{
	public:
		virtual bool IsType(ConditionFactory* factory) = 0;
		virtual ConditionFactory* CreateFactory(const char* name) = 0;
	};

	// 0x105A97E0
	ConditionFactory* FindConditionFactory(const char* name, ConditionFactoryCaster* caster);

	template<class T> class ConditionFactoryTemplate : public ConditionFactory
	{
	public:
		ConditionFactoryTemplate(const char* name)
			: ConditionFactory(name, T::RegisterProperties, T::ClearProperties)
		{
		}

		// vftable slot 1
		virtual void* CreateCondition()
		{
			return new T();
		}
	};

	template<class T> class ConditionFactoryCasterTemplate : public ConditionFactoryCaster
	{
	public:
		ConditionFactoryCasterTemplate();

		// vftable slot 0
		virtual bool IsType(ConditionFactory* factory)
		{
			return dynamic_cast<ConditionFactoryTemplate<T>*>(factory) != 0;
		}

		// vftable slot 1
		virtual ConditionFactory* CreateFactory(const char* name)
		{
			return new ConditionFactoryTemplate<T>(name);
		}
	};

	template<class T> ConditionFactoryCasterTemplate<T>::ConditionFactoryCasterTemplate()
	{
	}
}

namespace engine
{
	using fight::Property;
	using fight::PropertyBool;
	using fight::PropertyFloatConstRange;
	using fight::PropertyName;
	using fight::TrackFactory;
	using fight::TrackFactoryCasterTemplate;
	using fight::TrackFactoryTemplate;

	// engine::PlaybackTrack (RTTI: engine::PlaybackTrack, 16 vftable slots, 0x28 bytes): plays a playback set
	class PlaybackTrack : public fight::Track
	{
	public:
		PlaybackTrack();
		virtual ~PlaybackTrack();

		// vftable slot 0
		virtual fight::Property* GetProperty(int index);
		// vftable slot 9
		virtual float GetTimeBegin() const;
		// vftable slot 10
		virtual float Slot10() const;
		// vftable slot 15 (another unit)
		virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

		// 0x108078E0 / 0x108078F0 / 0x10807920 / 0x10807940: the members the properties write
		bool SetTimeBegin(float value);
		bool SetNotifyOnPlaybackFinished(bool value);
		bool SetState(const fight::Name& value);
		bool SetSpecificPlaybackSet(const fight::Name& value);

		// 0x10807B50 / 0x10807910: the property list, built once and freed again
		static void RegisterProperties();
		static void ClearProperties();

		// The two names the properties write: "specificPlaybackSet" at +0x10, "state" at +0x18
		fight::Name specificPlaybackSet;
		fight::Name state;
		float timeBegin;
		bool notifyOnPlaybackFinished;
	};

	// The properties of the track classes, one list per class (0x11284B50 for the playback track)
	extern fight::Property** gPlaybackTrackProperties;

	// The per-class list accessors the properties and the factory use
	fight::Property* GetPlaybackTrackProperty(int index);
}

namespace fight
{
	// The playback track's caster has its own annotated copy in the .cpp (0x108079C0)
	template<> TrackFactoryCasterTemplate<engine::PlaybackTrack>::TrackFactoryCasterTemplate();
}

#endif
