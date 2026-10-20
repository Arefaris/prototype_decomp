// The tag set (see the header). The tags are kept in order of their names' hashes; the order of the insertions is
// the one of a comparison function on the names (0x108343F0). Names are guesses.
#include <algorithm>

#include "code/container/string.h"
#include "code/engine/system/tagset.h"

// The engine's copy of the shift lives in another unit (0x102EB9A0)
namespace container
{
	template<> void ArrayDynamic<core::Name<core::CaseSensitiveKey>, AllocatorCoreStatic<12, 16> >::ShiftUp(
		core::Name<core::CaseSensitiveKey>* position, int count);

	// The members FromString and the copies of the sets use, as copies of their own
	template bool ArrayDynamic<core::Name<core::CaseSensitiveKey>, AllocatorCoreStatic<12, 16> >::Create(
		unsigned int count);
}

namespace engine
{
	typedef core::Name<core::CaseSensitiveKey> TagName;

	// 0x10421910 (another unit): the order of two names' hashes, negative when the first is the smaller
	int CompareNames(const TagName& first, const TagName& second);

	// FUNCTION: ENGINE 0x108340F0
	// The first place in [first, last) that is not before value
	template<class It, class T> It LowerBound(It first, It last, const T& value)
	{
		int count = last - first;
		while (count > 0)
		{
			int half = count / 2;
			It middle = first + half;
			if (*middle < value)
			{
				first = middle + 1;
				count = count - half - 1;
			}
			else
			{
				count = half;
			}
		}
		return first;
	}

	// FUNCTION: ENGINE 0x108343F0
	static bool NameLess(const TagName& first, const TagName& second)
	{
		return CompareNames(first, second) < 0;
	}

	// FUNCTION: ENGINE 0x10834D60
	TagSet::TagSet() : all(false)
	{
	}

	// FUNCTION: ENGINE 0x10834960
	void TagSet::Clear()
	{
		tags.end = tags.begin;
	}

	// FUNCTION: ENGINE 0x10834760
	inline const TagName* TagSet::Find(const TagName& name) const
	{
		TagName* end = tags.end;
		TagName* found = LowerBound(tags.begin, end, name);
		if (found != end)
		{
			if (!(name < *found))
			{
				return found;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10834910
	bool TagSet::Contains(const TagName& name) const
	{
		if (all)
		{
			return true;
		}
		return Find(name) != 0;
	}

	// FUNCTION: ENGINE 0x108342A0
	// EQUIVALENT: register choices and the order of the first loads (same comparisons in the same order)
	bool TagSet::Intersects(const TagSet& other) const
	{
		if (all || other.all)
		{
			return true;
		}
		const TagName* mine = tags.begin;
		unsigned int count = tags.end - tags.begin;
		const TagName* theirs = other.tags.begin;
		unsigned int otherCount = other.tags.end - other.tags.begin;
		unsigned int i = 0;
		unsigned int j = 0;
		while (i < count)
		{
			if (j >= otherCount)
			{
				break;
			}
			if (*mine < *theirs)
			{
				i++;
				mine++;
			}
			else if (*theirs < *mine)
			{
				j++;
				theirs++;
			}
			else
			{
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10834340
	// EQUIVALENT: register choices and the order of the first loads (same comparisons in the same order)
	bool TagSet::Includes(const TagSet& other) const
	{
		if (all || other.all)
		{
			return true;
		}
		const TagName* mine = tags.begin;
		unsigned int count = tags.end - tags.begin;
		const TagName* theirs = other.tags.begin;
		unsigned int otherCount = other.tags.end - other.tags.begin;
		unsigned int i = 0;
		unsigned int j = 0;
		while (i < count)
		{
			if (j >= otherCount)
			{
				break;
			}
			if (*mine < *theirs)
			{
				i++;
				mine++;
			}
			else if (*mine == *theirs)
			{
				i++;
				j++;
				mine++;
				theirs++;
			}
			else
			{
				return false;
			}
		}
		return j == otherCount;
	}

	// FUNCTION: ENGINE 0x10834D70
	// EQUIVALENT: register choices and the layout of the search loop (same calls and stores in the same order)
	TagName* TagSet::InsertSorted(const TagName& name, bool (*less)(const TagName&, const TagName&))
	{
		TagName* last = tags.end;
		TagName* first = tags.begin;
		TagName* middle = first + ((last - first) >> 1);
		TagName* position = middle;
		if (middle != 0)
		{
			do
			{
				position = middle;
				if (last <= middle)
				{
					break;
				}
				TagName* newLast = middle;
				if (less(*middle, name))
				{
					first = middle + 1;
					newLast = last;
				}
				middle = first + ((newLast - first) >> 1);
				last = newLast;
			} while (middle != position);
		}
		TagName* result = tags.end;
		if (tags.end + 1 <= tags.capacity)
		{
			tags.ShiftUp(position, 1);
			container::ConstructCopyAt(position, name);
			result = position;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10834E80
	// EQUIVALENT: register roles of the pointer and the counter, the zero is made by mov instead of xor
	bool TagSet::Add(const TagName& name)
	{
		TagName* item = tags.begin;
		unsigned int count = tags.end - item;
		for (unsigned int i = 0; i < count; i++, item++)
		{
			if (*item == name)
			{
				return false;
			}
		}
		InsertSorted(name, NameLess);
		return true;
	}

	// FUNCTION: ENGINE 0x10834970
	// EQUIVALENT: register choices and the shape of the address computations (same calls and stores in the same order)
	bool TagSet::Remove(const TagName& name)
	{
		TagName* end = tags.end;
		TagName* item = tags.begin;
		for (unsigned int i = 0; i < (unsigned int)(end - tags.begin); i++, item++)
		{
			if (*item == name)
			{
				TagName* next = tags.begin + i;
				for (next = next + 1; next != end; next++)
				{
					*(next - 1) = *next;
				}
				tags.end--;
				return true;
			}
		}
		return false;
	}

	// FUNCTION: ENGINE 0x10834690
	const char* TagSet::ToString()
	{
		static container::StringC<512> text;
		text.Clear();
		unsigned int count = tags.end - tags.begin;
		if (count != 0)
		{
			text.Append(tags.begin->GetText());
		}
		for (unsigned int i = 1; i < count; i++)
		{
			text.Append(";");
			text.Append(tags.begin[i].GetText());
		}
		return text.buffer;
	}

	// FUNCTION: ENGINE 0x10835010
	void TagSet::FromString(const char* text)
	{
		container::StringLiteral source(text);
		if (!source.IsEmpty())
		{
			container::StringC<256> token;
			tags.Create(source.Count(';') + 1);
			int start = 0;
			int next = source.Find(';', 0, 1);
			while (next > -1)
			{
				token.Assign(source, start, next - start);
				if (token.Equals(container::StringLiteral("*"), true))
				{
					all = true;
				}
				tags.PushBack(TagName(token.buffer, 1));
				start = next + 1;
				next = source.Find(';', start, 1);
			}
			token.Assign(source, start, 0x7FFFFFFF);
			if (token.Equals(container::StringLiteral("*"), true))
			{
				all = true;
			}
			tags.PushBack(TagName(token.buffer, 1));
			void (*sorter)(TagName*, TagName*) = std::sort<TagName*>;
			sorter(tags.begin, tags.end);
		}
	}

	// FUNCTION: ENGINE 0x10835000
	void TagSet::Sort()
	{
		// std::sort is called out of line, as the engine does
		void (*sorter)(TagName*, TagName*) = std::sort<TagName*>;
		sorter(tags.begin, tags.end);
	}
}

// The sort of the tags is the toolchain's <algorithm> for the names; the unit keeps the instances it needs as COMDAT
// functions of its own
typedef core::Name<core::CaseSensitiveKey> TagNameType;
template void std::_Med3<TagNameType*>(TagNameType*, TagNameType*, TagNameType*);
template void std::_Push_heap<TagNameType*, int, TagNameType>(TagNameType*, int, int, TagNameType);
template void std::_Median<TagNameType*>(TagNameType*, TagNameType*, TagNameType*);
template void std::_Adjust_heap<TagNameType*, int, TagNameType>(TagNameType*, int, int, TagNameType);
template void std::_Make_heap<TagNameType*, int, TagNameType>(TagNameType*, TagNameType*, int*, TagNameType*);
template std::pair<TagNameType*, TagNameType*> std::_Unguarded_partition<TagNameType*>(TagNameType*, TagNameType*);
template void std::_Insertion_sort1<TagNameType*, TagNameType>(TagNameType*, TagNameType*, TagNameType*);
template void std::_Sort_heap<TagNameType*>(TagNameType*, TagNameType*);
template void std::_Sort<TagNameType*, int>(TagNameType*, TagNameType*, int);
template void std::sort<TagNameType*>(TagNameType*, TagNameType*);

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108340E0
// FUNCTION: ENGINE 0x10834140
// FUNCTION: ENGINE 0x10834150
// FUNCTION: ENGINE 0x10834170
// FUNCTION: ENGINE 0x10834180
// FUNCTION: ENGINE 0x10834190
// FUNCTION: ENGINE 0x108341D0
// FUNCTION: ENGINE 0x10834240
// FUNCTION: ENGINE 0x10834250
// FUNCTION: ENGINE 0x10834260
// FUNCTION: ENGINE 0x108344A0
// FUNCTION: ENGINE 0x108344B0
// FUNCTION: ENGINE 0x108344F0
// FUNCTION: ENGINE 0x10834590
// FUNCTION: ENGINE 0x10834610
// FUNCTION: ENGINE 0x10834740
// FUNCTION: ENGINE 0x108347A0
// FUNCTION: ENGINE 0x10834830
// FUNCTION: ENGINE 0x10834880
// FUNCTION: ENGINE 0x108348C0
// FUNCTION: ENGINE 0x108349E0
// FUNCTION: ENGINE 0x10834C40
// FUNCTION: ENGINE 0x10834C70
// FUNCTION: ENGINE 0x10834DF0
// FUNCTION: ENGINE 0x10834E10
// FUNCTION: ENGINE 0x10834EE0
// FUNCTION: ENGINE 0x10834EF0
// FUNCTION: ENGINE 0x10834FE0
// FUNCTION: ENGINE 0x10D8A1C0
