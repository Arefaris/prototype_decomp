// code/engine/gameobject/details/mastertable.cpp (assert path at 0x10E68734): the game object master table behind
// GameObjectHandle. 0x1800 entries of {object, serial, flags} filled from the front (a fixed array with an end
// pointer) and recycled through a free list threaded through the object pointers; a handle can be reserved before
// its object exists. Unit 0x107E1D20 - 0x107E2440. Class and member names are guesses (the file name gives
// MasterTable); most of the small functions are kept copies of inline functions.
#ifndef ENGINE_GAMEOBJECT_DETAILS_MASTERTABLE_H
#define ENGINE_GAMEOBJECT_DETAILS_MASTERTABLE_H

#include "code/container/arraydynamic.h"
#include "code/container/arrayfixed.h"
#include "code/engine/gameobject/gameobjecthandle.h"

namespace engine
{
	class GameObjectIterator;

	class MasterTable
	{
	public:
		enum
		{
			CAPACITY = 0x1800
		};

		class Entry
		{
		public:
			Entry()
			{
			}
			explicit Entry(void* newObject)
			{
				object = newObject;
				serial = 0;
				flags = 0x8000;
			}

			bool IsValid() const
			{
				return used && object != 0;
			}
			bool IsReserved() const
			{
				return (flags >> 14) & 1;
			}
			void SetFlags(unsigned short mask)
			{
				flags |= mask;
			}
			void ClearFlags(int mask)
			{
				flags &= ~mask;
			}
			unsigned int GetCount() const
			{
				return count;
			}
			void SetCount(unsigned short value)
			{
				flags = (flags & 0xc000) | value;
			}
			void Set(void* newObject, unsigned short newSerial)
			{
				used = 1;
				object = newObject;
				serial = newSerial;
			}
			void SetObject(void* newObject)
			{
				used = 1;
				object = newObject;
			}
			unsigned short NextSerial()
			{
				count = 0;
				return ++serial;
			}
			void ClearObject()
			{
				object = 0;
			}
			void Reserve()
			{
				reserved = 1;
			}
			void Unreserve()
			{
				reserved = 0;
			}
			void* GetObject() const
			{
				return object;
			}
			// Links the entry into the free list
			void SetNext(Entry* next)
			{
				used = 0;
				object = next;
			}
			// Swaps objects and counts
			void Swap(Entry& other)
			{
				container::Swap(object, other.object);
				unsigned short previous = count;
				count = other.count;
				other.SetCount(previous);
			}

			void* object;
			unsigned short serial;
			union
			{
				struct
				{
					unsigned short count : 14;
					unsigned short reserved : 1;
					unsigned short used : 1;
				};
				unsigned short flags;
			};
		};

		MasterTable(int unknown, const container::AllocatorCoreAligned<16>& allocator);

		// A handle the next Allocate hands out (0x11283490 / 0x11283488)
		static GameObjectHandle sReservedHandle;
		static bool sHasReservedHandle;
		void ClearReservedHandle();
		void SetReservedHandle(GameObjectHandle handle);

		// The valid entries (gameobjectsystem.h; Begin is inline, End out of line in gameobjectsystem.cpp)
		GameObjectIterator Begin();
		GameObjectIterator End();

		unsigned short GetSerial(unsigned short index)
		{
			return entries[index].serial;
		}
		unsigned short IncrementSerial(unsigned short index);
		void Release(unsigned short index);
		void Swap(unsigned short a, unsigned short b);
		void Unreserve(unsigned short index);
		bool IsReserved(GameObjectHandle handle);
		void SetFlags(GameObjectHandle handle, unsigned short mask);
		void ClearFlags(GameObjectHandle handle, int mask);
		unsigned short Allocate(void* object);
		GameObjectHandle Reserve();
		unsigned short Move(const GameObjectHandle* from, GameObjectHandle* to);
		unsigned short Replace(const GameObjectHandle* target, const GameObjectHandle* source);

		container::ArrayFixed<Entry, CAPACITY> entries;
		Entry* freeList;
	};

	// The engine's master table (0x1128348C)
	extern MasterTable* gMasterTable;
}

#endif
