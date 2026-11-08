// proto::TimeOfDayVarChannel<T> (RTTI names; base proto::TimeOfDayVarChannelBase): a value that changes over the day,
// as a list of keys (a time and the value then) kept sorted by time. The channel is a member of the time of day
// groups, the global lighting, framebuffer effects and shader parameter rigs. The class names, the key layout and
// the reflected members are original, the member names of the editing functions are guesses.
#ifndef PROTO_TIMEOFDAY_TIMEOFDAYVARCHANNEL_H
#define PROTO_TIMEOFDAY_TIMEOFDAYVARCHANNEL_H

#include <algorithm>

#include "code/container/arraydynamicallocatornew.h"
#include "code/content/metatype.h"
#include "code/math/colour128.h"
#include "code/math/vector.h"
#include "code/math/vector2.h"

namespace proto
{
	// The value a new key starts with (a colour is opaque black); the parameter structs of the rigs construct themselves
	template<class S> inline void InitialValue(S& value)
	{
	}
	inline void InitialValue(float& value)
	{
		value = 0.0f;
	}
	inline void InitialValue(math::Vector2& value)
	{
	}
	inline void InitialValue(math::Vector& value)
	{
		value.x = 0.0f;
		value.y = 0.0f;
		value.z = 0.0f;
	}
	inline void InitialValue(math::Colour128& value)
	{
		value = math::Colour128(0.0f, 0.0f, 0.0f, 1.0f);
	}

	// What ResetKey stores: the value a new key starts with (the engine's two-component channel copies a vector
	// that was never set)
	template<class V> __forceinline void ResetValue(V& value)
	{
		V blank;
		value = blank;
	}
	inline void ResetValue(float& value)
	{
		InitialValue(value);
	}
	inline void ResetValue(math::Vector& value)
	{
		InitialValue(value);
	}
	inline void ResetValue(math::Colour128& value)
	{
		InitialValue(value);
	}
	inline void ResetValue(math::Vector2& value)
	{
		math::Vector2 blank;
		value.x = blank.x;
		value.y = blank.y;
	}

	// The value copies of the engine's keys: the components one by one (a parameter struct is copied whole)
	template<class S> __forceinline void AssignValue(S& destination, const S& source)
	{
		destination = source;
	}
	inline void AssignValue(float& destination, const float& source)
	{
		destination = source;
	}
	inline void AssignValue(math::Vector2& destination, const math::Vector2& source)
	{
		destination.x = source.x;
		destination.y = source.y;
	}
	inline void AssignValue(math::Vector& destination, const math::Vector& source)
	{
		destination.x = source.x;
		destination.y = source.y;
		destination.z = source.z;
	}
	inline void AssignValue(math::Colour128& destination, const math::Colour128& source)
	{
		destination = source;
	}

	// Which of the size and the capacity of the key array the compiler compares first in AddKey (the engine's copies
	// differ, the vector channels' are the only ones that compare the size first)
	template<class T> struct KeyOrder
	{
		enum
		{
			sizeFirst = 0,
			arrayReference = 0
		};
	};
	template<> struct KeyOrder<math::Vector2>
	{
		enum
		{
			sizeFirst = 1,
			arrayReference = 0
		};
	};
	template<> struct KeyOrder<math::Vector>
	{
		enum
		{
			sizeFirst = 1,
			arrayReference = 0
		};
	};

	// The abstract channel (RTTI proto::TimeOfDayVarChannelBase; 4 bytes, the vftable): the editing interface of a
	// channel that does not depend on the type of its value. The key arrays of the engine's copies are laid out
	// behind it at +4.
	class TimeOfDayVarChannelBase
	{
	public:
		virtual ~TimeOfDayVarChannelBase()
		{
		}
		// Whether a key at that time exists
		virtual bool HasKey(float time) = 0;
		// The size of one value in bytes
		virtual int GetValueSize() = 0;
		// Sets the value of the key at that time
		virtual void SetKeyValue(float time, const void* value) = 0;
		// Adds a key at that time (taking the current value of the channel there) unless one exists
		virtual void AddKey(float time) = 0;
		// Replaces all keys by one key at that time that holds the value the channel has there
		virtual void SetSingleKey(float time) = 0;
		// Removes the key at that time
		virtual void RemoveKey(float time) = 0;
		// Removes all keys
		virtual void Clear() = 0;
		// Sets the value of the key at that time back to the value a new key starts with
		virtual void ResetKey(float time) = 0;
	};

	template<class T> class TimeOfDayVarChannel : public TimeOfDayVarChannelBase
	{
	public:
		// One key (RTTI proto::TimeOfDayVarChannel<T>::Key): a time and the value from then on
		struct Key
		{
			float time;
			T value;

			Key()
			{
				InitialValue(value);
			}

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			bool operator<(const Key& other) const
			{
				return time < other.time;
			}
		};
		typedef container::ArrayDynamic<Key, container::AllocatorNew> KeyArray;

		TimeOfDayVarChannel()
		{
		}
		TimeOfDayVarChannel(const TimeOfDayVarChannel& other) : keys(other.keys)
		{
		}
		TimeOfDayVarChannel& operator=(const TimeOfDayVarChannel& other)
		{
			keys.Reserve(other.keys.Size());
			keys = other.keys;
			return *this;
		}
		virtual ~TimeOfDayVarChannel()
		{
		}

		virtual bool HasKey(float time)
		{
			for (unsigned int i = 0; i < keys.Size(); i++)
			{
				if (time == keys[i].time)
				{
					return true;
				}
			}
			return false;
		}
		virtual int GetValueSize()
		{
			return sizeof(T);
		}
		virtual void SetKeyValue(float time, const void* value)
		{
			SetKey(time, *(const T*)value);
		}
		virtual void AddKey(float time);
		virtual void SetSingleKey(float time);
		virtual void RemoveKey(float time)
		{
			if (HasKey(time))
			{
				if (KeyOrder<T>::arrayReference)
				{
					KeyArray& array = keys;
					for (unsigned int i = 0; i < array.Size(); i++)
					{
						if (time == array[i].time)
						{
							array.Erase(array.begin + i);
							break;
						}
					}
				}
				else
				{
					for (unsigned int i = 0; i < keys.Size(); i++)
					{
						if (time == keys[i].time)
						{
							keys.Erase(keys.begin + i);
							break;
						}
					}
				}
			}
		}
		virtual void Clear()
		{
			keys.end = keys.begin;
		}
		virtual void ResetKey(float time);

		// The index of the last key at or before that time (the time is kept within a day), the last key when there is
		// none; and of the first key behind it, the first when there is none
		int FindPreviousKey(float time);
		int FindNextKey(float time);
		// Whether the channel has any key (defined out of line in the time of day manager's unit)
		bool HasKeys();
		// The value the channel has at that time (the same)
		T Evaluate(float time);
		void SetKey(float time, const T& value)
		{
			for (unsigned int i = 0; i < keys.Size(); i++)
			{
				if (time == keys[i].time)
				{
					keys[i].value = value;
				}
			}
		}

		static content::ClassInfo* GetClassInfo();
		static content::MemberList* GetMembers();

		KeyArray keys;  // +4
		int unknown10;  // behind the array: its allocator word
	};

	// The key of the two-component channel: the engine moves its elements down component by component
	template<> struct TimeOfDayVarChannel<math::Vector2>::Key
	{
		float time;
		math::Vector2 value;

		Key()
		{
			InitialValue(value);
		}
		Key& operator=(const Key& other)
		{
			time = other.time;
			AssignValue(value, other.value);
			return *this;
		}
		bool operator<(const Key& other) const
		{
			return time < other.time;
		}
	};

	template<class T> void TimeOfDayVarChannel<T>::AddKey(float time)
	{
		if (!HasKey(time))
		{
			Key key;
			key.time = time;
			if (HasKeys())
			{
				AssignValue(key.value, Evaluate(time));
			}
			if (KeyOrder<T>::sizeFirst ? (keys.Size() == keys.Capacity()) : (keys.Capacity() == keys.Size()))
			{
				keys.Reserve(keys.Size() + 1);
			}
			KeyArray& array = keys;
			array.PushBack(key);
			// the engine calls its copy of std::sort instead of expanding it
			void (*sort)(Key*, Key*) = std::sort<Key*>;
			sort(array.begin, array.end);
		}
	}

	template<class T> int TimeOfDayVarChannel<T>::FindPreviousKey(float time)
	{
		if (!(time >= 0.0f))
		{
			time = 0.0f;
		}
		if (time - 24.0f >= 0.0f)
		{
			time = 24.0f;
		}
		int last = keys.Size() - 1;
		int index = keys.Size() - 1;
		if (index >= 0)
		{
			Key* key = keys.begin + index;
			do
			{
				if (key->time <= time)
				{
					return index;
				}
				index--;
				key--;
			} while (index >= 0);
		}
		return last;
	}

	template<class T> int TimeOfDayVarChannel<T>::FindNextKey(float time)
	{
		if (!(time >= 0.0f))
		{
			time = 0.0f;
		}
		if (time - 24.0f >= 0.0f)
		{
			time = 24.0f;
		}
		int result = 0;
		unsigned int index = 0;
		if (keys.Size() != 0)
		{
			Key* key = keys.begin;
			do
			{
				if (time < key->time)
				{
					result = index;
					break;
				}
				index++;
				key++;
			} while (index < keys.Size());
		}
		return result;
	}

	template<class T> void TimeOfDayVarChannel<T>::SetSingleKey(float time)
	{
		if (HasKeys())
		{
			T value = Evaluate(time);
			Clear();
			AddKey(time);
			SetKey(time, value);
		}
	}

	template<class T> void TimeOfDayVarChannel<T>::ResetKey(float time)
	{
		for (unsigned int i = 0; i < keys.Size(); i++)
		{
			if (time == keys[i].time)
			{
				ResetValue(keys[i].value);
				break;
			}
		}
	}
}

namespace proto
{
	// The vector channels copy the value of a key component by component
	template<> inline void TimeOfDayVarChannel<math::Vector2>::SetKey(float time, const math::Vector2& value)
	{
		for (unsigned int i = 0; i < keys.Size(); i++)
		{
			if (time == keys[i].time)
			{
				AssignValue(keys[i].value, value);
			}
		}
	}
	template<> inline void TimeOfDayVarChannel<math::Vector>::SetKey(float time, const math::Vector& value)
	{
		for (unsigned int i = 0; i < keys.Size(); i++)
		{
			if (time == keys[i].time)
			{
				AssignValue(keys[i].value, value);
			}
		}
	}

	// Left to the engine (declared and mapped in symbols.txt, not defined): the colour channel's AddKey schedules two loads
	// differently and the two-component channel's RemoveKey copies the elements in another order
	template<> void TimeOfDayVarChannel<math::Colour128>::AddKey(float time);
	template<> void TimeOfDayVarChannel<math::Vector2>::RemoveKey(float time);
}

namespace container
{
	// The keys of the vector channel are moved down by the out-of-line AssignRange
	template<> struct ArrayEraseInline<proto::TimeOfDayVarChannel<math::Vector>::Key>
	{
		enum
		{
			value = 0
		};
	};
	template<> struct ArrayEraseInline<proto::TimeOfDayVarChannel<math::Colour128>::Key>
	{
		enum
		{
			value = 0
		};
	};
}

namespace container
{
	// The engine's Insert of the float key array expands the shift of the elements in place
	template<> inline proto::TimeOfDayVarChannel<float>::Key* ArrayDynamic<proto::TimeOfDayVarChannel<float>::Key,
		AllocatorNew>::Insert(proto::TimeOfDayVarChannel<float>::Key* position, unsigned int count,
		const proto::TimeOfDayVarChannel<float>::Key& value)
	{
		typedef proto::TimeOfDayVarChannel<float>::Key Key;
		Key* result = end;
		Key* newEnd = end + count;
		if (newEnd <= capacity)
		{
			Key* from = end;
			end = newEnd;
			Key* to = newEnd;
			while (from != position)
			{
				from--;
				to--;
				ConstructCopyAt(to, *from);
				Destroy(from);
			}
			ConstructFill(position, count, value);
			result = position;
		}
		return result;
	}
	// The engine's single insert of the colour keys goes through the count version
	template<> inline proto::TimeOfDayVarChannel<math::Colour128>::Key* ArrayDynamic<proto::TimeOfDayVarChannel<math::Colour128>::Key,
		AllocatorNew>::Insert(proto::TimeOfDayVarChannel<math::Colour128>::Key* position,
		const proto::TimeOfDayVarChannel<math::Colour128>::Key& value)
	{
		return Insert(position, 1, value);
	}
}

namespace content
{
	// The element access of the key arrays, in three parts: the slots before Insert, Insert, the slots behind it. The
	// engine's copies insert the default key with the count version of Array::Insert (float keys, the shift expanded
	// in the array's Insert), with the single one (vector keys) or with the count version behind a function that
	// answers the default key (colour keys)
#define PROTO_KEY_ARRAY_HELPER_BEGIN(KeyType) \
	template<> class ArrayDynamicHelper<container::ArrayDynamic<KeyType, container::AllocatorNew> > \
		: public ArrayDynamicHelperBase \
	{ \
	public: \
		typedef container::ArrayDynamic<KeyType, container::AllocatorNew> A; \
		typedef KeyType T; \
		virtual int Size(void* array) \
		{ \
			return ((A*)array)->Size(); \
		} \
		virtual void* Get(void* array, int index) \
		{ \
			return ((A*)array)->begin + index; \
		} \
		virtual void* GetConst(void* array, int index) \
		{ \
			return ((A*)array)->begin + index; \
		}
#define PROTO_KEY_ARRAY_HELPER_INSERT(...) \
		virtual void Insert(void* array, int index, int unused) \
		{ \
			A* a = (A*)array; \
			if (a->Size() >= a->Capacity()) \
			{ \
				a->Reserve(a->Size() + 1); \
			} \
			T* position = a->begin + index; \
			__VA_ARGS__ \
		}
#define PROTO_KEY_ARRAY_HELPER_INSERT_DECL 		virtual void Insert(void* array, int index, int unused);
#define PROTO_KEY_ARRAY_HELPER_ERASE_DECL 		virtual void Erase(void* array, int index, int unused);
#define PROTO_KEY_ARRAY_HELPER_TAIL 		virtual int Capacity(void* array) 		{ 			return ((A*)array)->Capacity(); 		} 		virtual void Expand(void* array, unsigned int count) 		{ 			A* a = (A*)array; 			if (a->Capacity() == 0) 			{ 				a->Allocate(count); 			} 			else if (count + a->Size() > a->Capacity()) 			{ 				a->Reserve(count + a->Size()); 			} 		} 	};
#define PROTO_KEY_ARRAY_HELPER_END \
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
	};

	// The float keys' Erase is left to the engine (the engine adds the element size to the position with a separate add)
	PROTO_KEY_ARRAY_HELPER_BEGIN(proto::TimeOfDayVarChannel<float>::Key)
	PROTO_KEY_ARRAY_HELPER_INSERT(static T sDefault; a->Insert(position, 1, sDefault);)
	PROTO_KEY_ARRAY_HELPER_ERASE_DECL
	PROTO_KEY_ARRAY_HELPER_TAIL

	PROTO_KEY_ARRAY_HELPER_BEGIN(proto::TimeOfDayVarChannel<math::Vector>::Key)
	PROTO_KEY_ARRAY_HELPER_INSERT(static T sDefault; a->Insert(position, sDefault);)
	PROTO_KEY_ARRAY_HELPER_END

	PROTO_KEY_ARRAY_HELPER_BEGIN(proto::TimeOfDayVarChannel<math::Colour128>::Key)
		static T& Default()
		{
			static T sDefault;
			return sDefault;
		}
	PROTO_KEY_ARRAY_HELPER_INSERT(a->Insert(position, 1, Default());)
	PROTO_KEY_ARRAY_HELPER_END
}

#endif
