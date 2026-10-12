// The free lists follow Matthew Conte's TLSF 3.0 (BSD licence), the tree Julienne Walker's top-down red-black
// insertion and deletion (public domain), both reworked to descriptors with 15-bit links.
#include <string.h>

#include "code/core/memory/externalheap.h"
#include "code/core/utility.h"

#define NO_BLOCK 0x7FFF
#define SL_INDEX_COUNT_LOG2 5
#define SMALL_BLOCK_SIZE 0x200

namespace core
{
	template<int Unused> struct ExternalBlockT
	{
		// FUNCTION: ENGINE 0x10B82F80
		static bool IsZero(unsigned int value)
		{
			return value == 0;
		}

		// FUNCTION: ENGINE 0x10B82F90
		void SetSize(unsigned int value)
		{
			location = (location & 0x3FFFFFFFFFull) | ((unsigned __int64)(value & 0x3FFFFFF0) << 34);
		}

		// FUNCTION: ENGINE 0x10B82FC0
		unsigned int GetSize()
		{
			return (unsigned int)(location >> 34) & 0x3FFFFFF0;
		}

		// FUNCTION: ENGINE 0x10B82FE0
		void SetOffset(unsigned int value)
		{
			location = (location & 0xFFFFFFC000000FFFull) | ((unsigned __int64)(value & 0x3FFFFFF0) << 8);
		}

		// FUNCTION: ENGINE 0x10B83010
		unsigned int GetOffset()
		{
			return (unsigned int)(location >> 8) & 0x3FFFFFF0;
		}

		// FUNCTION: ENGINE 0x10B83030
		void SetLeft(int index)
		{
			left = index & NO_BLOCK;
		}

		// FUNCTION: ENGINE 0x10B83060
		unsigned short GetLeft()
		{
			return (unsigned short)left;
		}

		// FUNCTION: ENGINE 0x10B83080
		void SetRight(int index)
		{
			right = index;
		}

		// FUNCTION: ENGINE 0x10B830B0
		unsigned short GetRight()
		{
			return (unsigned short)right;
		}

		// FUNCTION: ENGINE 0x10B830D0
		void SetParent(int index)
		{
			parent = index;
		}

		// FUNCTION: ENGINE 0x10B83110
		unsigned short GetParent()
		{
			return (unsigned short)parent;
		}

		// FUNCTION: ENGINE 0x10B83130
		void SetNext(int index)
		{
			next = index;
		}

		// FUNCTION: ENGINE 0x10B83160
		unsigned short GetNext()
		{
			return (unsigned short)next;
		}

		// FUNCTION: ENGINE 0x10B83180
		void SetPrev(unsigned short index)
		{
			prevHigh = index >> 3;
			prevLow = index & 7;
		}

		// FUNCTION: ENGINE 0x10B831D0
		unsigned short GetPrev()
		{
			return (unsigned short)((unsigned short)(prevHigh << 3) | (unsigned short)prevLow);
		}

		// FUNCTION: ENGINE 0x10B831F0
		void SetColour(unsigned int value)
		{
			black = value;
		}

		// FUNCTION: ENGINE 0x10B83220
		int IsBlack()
		{
			return (int)black;
		}

		// FUNCTION: ENGINE 0x10B83240
		void Clear()
		{
			memset(this, 0xFF, sizeof(*this));
		}

		// FUNCTION: ENGINE 0x10B83250
		void SetChild(int index, int side)
		{
			if (side == 0)
			{
				left = index & NO_BLOCK;
			}
			else
			{
				right = index;
			}
		}

		// FUNCTION: ENGINE 0x10B832A0
		unsigned short GetChild(int side)
		{
			if (side == 0)
			{
				return (unsigned short)left;
			}
			return (unsigned short)right;
		}

		// FUNCTION: ENGINE 0x10B832C0
		void SetRed()
		{
			black = 0;
		}

		// FUNCTION: ENGINE 0x10B832D0
		void SetBlack()
		{
			black = 1;
		}

		// Offset (bits 12 - 37) and size (bits 38 - 63) are read and written as 16-byte multiples in place
		union
		{
			unsigned __int64 location;
			struct
			{
				unsigned __int64 prevHigh : 12;
				unsigned __int64 offset : 26;
				unsigned __int64 size : 26;
			};
		};
		unsigned __int64 prevLow : 3;
		unsigned __int64 black : 1;
		unsigned __int64 next : 15;
		unsigned __int64 parent : 15;
		unsigned __int64 right : 15;
		unsigned __int64 left : 15;
	};

	template struct ExternalBlockT<0>;

	// FUNCTION: ENGINE 0x10B832E0
	static inline int tlsf_fls(unsigned int word)
	{
		int bit = 32;

		if (!word)
		{
			bit -= 1;
		}
		if (!(word & 0xffff0000))
		{
			word <<= 16;
			bit -= 16;
		}
		if (!(word & 0xff000000))
		{
			word <<= 8;
			bit -= 8;
		}
		if (!(word & 0xf0000000))
		{
			word <<= 4;
			bit -= 4;
		}
		if (!(word & 0xc0000000))
		{
			word <<= 2;
			bit -= 2;
		}
		if (!(word & 0x80000000))
		{
			word <<= 1;
			bit -= 1;
		}

		return bit - 1;
	}

	// FUNCTION: ENGINE 0x10B83330
	static int tlsf_fls_sizet(unsigned int size)
	{
		return tlsf_fls(size);
	}

	// FUNCTION: ENGINE 0x10B83380
	static int tlsf_ffs(unsigned int word)
	{
		return tlsf_fls(word & (~word + 1));
	}

	// FUNCTION: ENGINE 0x10B833E0
	unsigned int ExternalHeap::GetOverhead(unsigned int count)
	{
		return (count + 3) * sizeof(ExternalBlock);
	}

	// FUNCTION: ENGINE 0x10B833F0
	ExternalHeap::ExternalHeap()
		: memory(0), size(0), base(0), limit(0), align(0), ready(false), count(0), used(0), freeFront(0), freeBack(0),
		peak(0), blocks(0), first(NO_BLOCK), last(NO_BLOCK), freeBlocks(NO_BLOCK), root(NO_BLOCK), flBitmap(0)
	{
	}

	// FUNCTION: ENGINE 0x10B83430
	ExternalHeap::~ExternalHeap()
	{
	}

	// FUNCTION: ENGINE 0x10B83440
	void ExternalHeap::Shutdown()
	{
		ready = false;
	}

	// FUNCTION: ENGINE 0x10B83450
	void ExternalHeap::GetMemory(void** start, unsigned int* length)
	{
		if (ready)
		{
			*start = (void*)memory;
			*length = size;
		}
	}

	// FUNCTION: ENGINE 0x10B83470
	void ExternalHeap::GetUsedRange(unsigned int* start, unsigned int* length)
	{
		if (ready)
		{
			*length = used;
			if (used == 0)
			{
				*start = 0;
			}
			else
			{
				*start = freeFront + memory;
			}
		}
	}

	// FUNCTION: ENGINE 0x10B834A0
	unsigned int ExternalHeap::GetBlockLimit()
	{
		return limit;
	}

	// FUNCTION: ENGINE 0x10B834B0
	unsigned int ExternalHeap::GetBlockCount()
	{
		return count;
	}

	// FUNCTION: ENGINE 0x10B834C0
	unsigned int ExternalHeap::GetUsedBytes()
	{
		return used;
	}

	// FUNCTION: ENGINE 0x10B834D0
	unsigned int ExternalHeap::GetFreeBytes()
	{
		return freeBack + freeFront;
	}

	// FUNCTION: ENGINE 0x10B834E0
	unsigned int ExternalHeap::GetPeakBytes()
	{
		return peak;
	}

	// FUNCTION: ENGINE 0x10B834F0
	void ExternalHeap::ResetPeak()
	{
		peak = 0;
	}

	// FUNCTION: ENGINE 0x10B83500
	void ExternalHeap::ClearBlocks()
	{
		for (unsigned int i = 0; i < limit + 3; i++)
		{
			blocks[i].Clear();
		}
	}

	// FUNCTION: ENGINE 0x10B83540
	void ExternalHeap::InitFreeBlocks()
	{
		freeBlocks = 0;
		for (unsigned int i = 0; i < limit + 2; i++)
		{
			blocks[i].SetNext((unsigned short)(i + 1));
		}
		blocks[limit + 2].SetNext(NO_BLOCK);
	}

	// FUNCTION: ENGINE 0x10B835C0
	unsigned short ExternalHeap::NewBlock()
	{
		unsigned short index = freeBlocks;
		ExternalBlock* block = &blocks[index];
		freeBlocks = block->GetNext();
		block->SetNext(NO_BLOCK);
		return index;
	}

	// FUNCTION: ENGINE 0x10B83600
	void ExternalHeap::DeleteBlock(unsigned short index)
	{
		ExternalBlock* block = &blocks[index];
		block->Clear();
		block->SetNext(freeBlocks);
		freeBlocks = index;
	}

	// FUNCTION: ENGINE 0x10B83660
	void ExternalHeap::ClearTree()
	{
		root = NO_BLOCK;
	}

	// FUNCTION: ENGINE 0x10B83670
	// EQUIVALENT: the original does not rotate the loop (the test at the top, both child reads as separate __aullshr calls jumping back to it) and reloads `blocks` each pass; every while / for / goto / indexed form tried gets the rotated loop with one merged call
	unsigned short ExternalHeap::FindBlock(unsigned int offset)
	{
		unsigned short index = root;
		while (index < limit + 3)
		{
			if (blocks[index].GetOffset() == offset)
			{
				break;
			}
			if (blocks[index].GetOffset() < offset)
			{
				index = blocks[index].GetRight();
			}
			else
			{
				index = blocks[index].GetLeft();
			}
		}
		return index;
	}
	// FUNCTION: ENGINE 0x10B836E0
	// EQUIVALENT: same steps; registers and the walk-up loop's flag handling differ (the original keeps the flag in dl on one path and in memory on the other)
	unsigned short ExternalHeap::GetSuccessor(unsigned short index)
	{
		ExternalBlock* items = blocks;
		unsigned int end = limit + 3;
		unsigned short child = items[index].GetRight();
		if (child < end)
		{
			for (unsigned short next = items[child].GetLeft(); next < end; next = items[child].GetLeft())
			{
				child = next;
			}
			return child;
		}
		unsigned short node = index;
		unsigned short parent = items[index].GetParent();
		bool searching = true;
		do
		{
			if (parent < end && node != items[parent].GetLeft())
			{
				node = parent;
				parent = items[parent].GetParent();
			}
			else
			{
				searching = !searching;
			}
		}
		while (searching);
		return parent;
	}

	// FUNCTION: ENGINE 0x10B837E0
	// EQUIVALENT: as GetSuccessor (mirror image)
	unsigned short ExternalHeap::GetPredecessor(unsigned short index)
	{
		ExternalBlock* items = blocks;
		unsigned int end = limit + 3;
		unsigned short child = items[index].GetLeft();
		if (child < end)
		{
			for (unsigned short next = items[child].GetRight(); next < end; next = items[child].GetRight())
			{
				child = next;
			}
			return child;
		}
		unsigned short node = index;
		unsigned short parent = items[index].GetParent();
		bool searching = true;
		do
		{
			if (parent < end && node != items[parent].GetRight())
			{
				node = parent;
				parent = items[parent].GetParent();
			}
			else
			{
				searching = !searching;
			}
		}
		while (searching);
		return parent;
	}

	// The single rotation of the top-down red-black tree, with the parent links kept
	// FUNCTION: ENGINE 0x10B838E0
	// EQUIVALENT: same stores in the same order; the original keeps the child read for `side` as two separate __aullshr calls with the result stored in memory, ours merges them (if / else and GetChild forms alike)
	void ExternalHeap::Rotate(unsigned short index, int side)
	{
		ExternalBlock* node = &blocks[index];
		unsigned short parent = node->GetParent();
		ExternalBlock* up = &blocks[parent];
		unsigned short save = node->GetChild(!side);
		ExternalBlock* saved = &blocks[save];
		unsigned short inner = saved->GetChild(side);
		ExternalBlock* moved = &blocks[inner];
		int upSide = up->GetLeft() != index;
		node->SetChild(inner, !side);
		node->SetParent(save);
		if (save < limit + 3)
		{
			saved->SetChild(index, side);
			saved->SetParent(parent);
		}
		if (inner < limit + 3)
		{
			moved->SetParent(index);
		}
		if (parent < limit + 3)
		{
			up->SetChild(save, upSide);
		}
		node->SetRed();
		saved->SetBlack();
	}

	// FUNCTION: ENGINE 0x10B83B40
	void ExternalHeap::DoubleRotate(unsigned short index, int side)
	{
		Rotate(blocks[index].GetChild(!side), !side);
		Rotate(index, side);
	}

	// FUNCTION: ENGINE 0x10B83B90
	void ExternalHeap::ClearLists()
	{
		flBitmap = 0;
		for (int i = 0; i < 20; i++)
		{
			slBitmap[i] = 0;
			for (int j = 0; j < 32; j++)
			{
				heads[i][j] = NO_BLOCK;
			}
		}
	}

	// FUNCTION: ENGINE 0x10B83C00
	void ExternalHeap::MappingInsert(unsigned int size, int* fli, int* sli)
	{
		int fl, sl;
		if (size < SMALL_BLOCK_SIZE)
		{
			fl = 0;
			sl = size / (SMALL_BLOCK_SIZE / 32);
		}
		else
		{
			fl = tlsf_fls_sizet(size);
			sl = (int)(size >> (fl - SL_INDEX_COUNT_LOG2)) ^ (1 << SL_INDEX_COUNT_LOG2);
			fl -= 8;
		}
		*fli = fl;
		*sli = sl;
	}

	// FUNCTION: ENGINE 0x10B83C50
	bool ExternalHeap::FindSuitable(unsigned int size, int* fli, int* sli)
	{
		if (size >= 32)
		{
			const unsigned int round = (1 << (tlsf_fls_sizet(size) - SL_INDEX_COUNT_LOG2)) - 1;
			size += round;
		}
		int fl;
		int sl;
		MappingInsert(size, &fl, &sl);
		unsigned int sl_map = slBitmap[fl] & (~0U << sl);
		if (!sl_map)
		{
			const unsigned int fl_map = flBitmap & (~0U << (fl + 1));
			if (!fl_map)
			{
				return false;
			}
			fl = tlsf_ffs(fl_map);
			sl_map = slBitmap[fl];
		}
		sl = tlsf_ffs(sl_map);
		*fli = fl;
		*sli = sl;
		return true;
	}

	// FUNCTION: ENGINE 0x10B83CE0
	unsigned int ExternalHeap::ToAddress(unsigned int offset)
	{
		return base + offset;
	}

	// FUNCTION: ENGINE 0x10B83CF0
	unsigned int ExternalHeap::ToOffset(unsigned int address)
	{
		return address - base;
	}

	// Julienne Walker's top-down insertion (the rotations update the links above them)
	// FUNCTION: ENGINE 0x10B83D00
	// EQUIVALENT: same steps as Walker's insertion; the original's GetChild reads stay separate calls (see Rotate) and its registers / spill slots differ
	void ExternalHeap::TreeInsert(unsigned short index)
	{
		ExternalBlock* node = &blocks[index];
		node->SetParent(NO_BLOCK);
		node->SetRight(NO_BLOCK);
		node->SetLeft(NO_BLOCK);
		node->SetRed();
		unsigned int key = blocks[index].GetOffset();
		if (root < limit + 3)
		{
			int dir = 1;
			int last = 1;
			unsigned short head = NewBlock();
			blocks[head].SetRight(root);
			blocks[root].SetParent(head);
			unsigned short g = NO_BLOCK;
			unsigned short p = NO_BLOCK;
			unsigned short q = root;
			for (;;)
			{
				ExternalBlock* item;
				if (q >= limit + 3)
				{
					q = index;
					item = &blocks[q];
					blocks[p].SetChild(index, dir);
					item->SetParent(p);
				}
				else
				{
					item = &blocks[q];
					unsigned short left = item->GetLeft();
					unsigned short right = item->GetRight();
					if (left < limit + 3 && !blocks[left].IsBlack() && right < limit + 3 && !blocks[right].IsBlack())
					{
						item->SetRed();
						blocks[left].SetBlack();
						blocks[right].SetBlack();
					}
				}
				unsigned int offset = item->GetOffset();
				if (!item->IsBlack() && p < limit + 3 && !blocks[p].IsBlack())
				{
					if (blocks[p].GetChild(last) == q)
					{
						Rotate(g, !last);
					}
					else
					{
						DoubleRotate(g, !last);
					}
				}
				if (offset == key)
				{
					break;
				}
				last = dir;
				dir = offset < key;
				g = p;
				p = q;
				q = item->GetChild(dir);
			}
			root = blocks[head].GetRight();
			blocks[root].SetParent(NO_BLOCK);
			DeleteBlock(head);
		}
		else
		{
			root = index;
		}
		blocks[root].SetBlack();
	}

	// FUNCTION: ENGINE 0x10B849C0
	void ExternalHeap::InsertFree(unsigned int size, unsigned short index)
	{
		int fl = 0;
		int sl = 0;
		MappingInsert(size, &fl, &sl);
		blocks[index].SetNext(heads[fl][sl]);
		blocks[index].SetPrev(NO_BLOCK);
		if (blocks[index].GetNext() < limit + 3)
		{
			blocks[blocks[index].GetNext()].SetPrev(index);
		}
		heads[fl][sl] = index;
		flBitmap |= 1 << fl;
		slBitmap[fl] |= 1 << sl;
	}

	// FUNCTION: ENGINE 0x10B84AF0
	// EQUIVALENT: same steps; the original's second loop is not rotated and walks through a block pointer
	unsigned short ExternalHeap::FindFree(unsigned int size, unsigned short* following, int mode)
	{
		int fl = 0;
		int sl = 0;
		if (FindSuitable(size, &fl, &sl))
		{
			unsigned short index = heads[fl][sl];
			*following = GetSuccessor(index);
			return index;
		}
		switch (mode)
		{
		case 0:
			return NO_BLOCK;
		case 1:
			if (size >= 0x400)
			{
				MappingInsert(size, &fl, &sl);
				unsigned short index = heads[fl][sl];
				while (index < limit + 3)
				{
					*following = GetSuccessor(index);
					if (size <= blocks[*following].GetOffset() - blocks[index].GetSize() - blocks[index].GetOffset())
					{
						return index;
					}
					index = blocks[index].GetNext();
				}
				*following = NO_BLOCK;
				return index;
			}
			break;
		}
		return NO_BLOCK;
	}

	// FUNCTION: ENGINE 0x10B84C50
	bool ExternalHeap::RemoveFree(unsigned int size, unsigned short index)
	{
		ExternalBlock* block = &blocks[index];
		if (block->GetNext() < limit + 3)
		{
			ExternalBlock* next = &blocks[block->GetNext()];
			next->SetPrev(block->GetPrev());
		}
		if (block->GetPrev() < limit + 3)
		{
			blocks[block->GetPrev()].SetNext(block->GetNext());
		}
		else
		{
			int fl = 0;
			int sl = 0;
			MappingInsert(size, &fl, &sl);
			if (heads[fl][sl] == index)
			{
				heads[fl][sl] = block->GetNext();
				if (heads[fl][sl] >= limit + 3)
				{
					slBitmap[fl] &= ~(1 << sl);
					if (!slBitmap[fl])
					{
						flBitmap &= ~(1 << fl);
					}
				}
			}
			else
			{
				return false;
			}
		}
		block->SetNext(NO_BLOCK);
		block->SetPrev(NO_BLOCK);
		return true;
	}

	// FUNCTION: ENGINE 0x10B84E00
	void ExternalHeap::Init(void* start, unsigned int length, void* bookkeeping, unsigned int overhead, unsigned int origin,
		unsigned int alignment, unsigned int count, int mode)
	{
		memory = (unsigned int)start;
		size = length;
		base = origin;
		align = alignment;
		limit = count;
		blocks = (ExternalBlock*)bookkeeping;
		ClearBlocks();
		InitFreeBlocks();
		ClearLists();
		ClearTree();
		first = NewBlock();
		last = NewBlock();
		blocks[first].SetOffset(memory - base - 16);
		blocks[last].SetOffset(size - base + memory);
		blocks[first].SetSize(16);
		blocks[last].SetSize(0);
		TreeInsert(first);
		TreeInsert(last);
		InsertFree(size, first);
		this->count = 0;
		freeFront = size;
		freeBack = 0;
		used = 0;
		peak = 0;
		strategy = mode;
		ready = true;
	}

	// FUNCTION: ENGINE 0x10B84F50
	void* ExternalHeap::Alloc(unsigned int length, unsigned int alignment, int mode)
	{
		if (!ready)
		{
			return 0;
		}
		if (length < 16)
		{
			length = 16;
		}
		else if (length > 0x3FFFFFF0)
		{
			return 0;
		}
		unsigned int rounded = (align - 1 + length) & ~(align - 1);
		alignment = alignment < align ? align : alignment;
		unsigned short following = NO_BLOCK;
		unsigned short index = FindFree((align != alignment ? alignment : 0) + rounded, &following, mode);
		if (index >= limit + 3)
		{
			return 0;
		}
		unsigned short block = NewBlock();
		if (block >= limit + 3)
		{
			return 0;
		}
		ExternalBlock* created = &blocks[block];
		ExternalBlock* previous = &blocks[index];
		unsigned int start = previous->GetOffset() + previous->GetSize() + base;
		unsigned int end = blocks[following].GetOffset() + base;
		unsigned int gap = end - start;
		unsigned int address = 0;
		switch (strategy)
		{
		case 0:
			address = (start - 1 + alignment) & ~(alignment - 1);
			break;
		case 1:
			address = (end - rounded) & ~(alignment - 1);
			break;
		}
		RemoveFree(gap, index);
		unsigned int before = address - start;
		unsigned int after = gap - before - rounded;
		created->SetSize(rounded);
		created->SetOffset(address - base);
		TreeInsert(block);
		InsertFree(before, index);
		InsertFree(after, block);
		count++;
		if (index == first)
		{
			freeFront = before;
		}
		if (following == last)
		{
			freeBack = after;
		}
		used = size - freeBack - freeFront;
		peak = Max(used, peak);
		return (void*)address;
	}

	// FUNCTION: ENGINE 0x10B85150
	// EQUIVALENT: same steps; register allocation and the join of the strategy branches differ (one more stack slot in the original)
	void* ExternalHeap::AllocEnd(unsigned int length, unsigned int alignment)
	{
		if (!ready)
		{
			return 0;
		}
		unsigned short block = NewBlock();
		if (block >= limit + 3)
		{
			return 0;
		}
		if (length < 16)
		{
			length = 16;
		}
		else if (length > 0x3FFFFFF0)
		{
			return 0;
		}
		unsigned int rounded = (align - 1 + length) & ~(align - 1);
		alignment = alignment < align ? align : alignment;
		unsigned short index = NO_BLOCK;
		unsigned short following = NO_BLOCK;
		if (strategy == 0)
		{
			index = GetPredecessor(last);
			following = last;
		}
		else if (strategy == 1)
		{
			index = first;
			following = GetSuccessor(index);
		}
		ExternalBlock* previous = &blocks[index];
		ExternalBlock* created = &blocks[block];
		unsigned int start = previous->GetOffset() + previous->GetSize() + base;
		unsigned int end = blocks[following].GetOffset() + base;
		unsigned int gap = end - start;
		unsigned int address = 0;
		switch (strategy)
		{
		case 0:
			address = (start - 1 + alignment) & ~(alignment - 1);
			break;
		case 1:
			address = (end - rounded) & ~(alignment - 1);
			break;
		}
		created->SetSize(rounded);
		created->SetOffset(address - base);
		if (end - address < rounded)
		{
			DeleteBlock(block);
			return 0;
		}
		RemoveFree(gap, index);
		unsigned int before = address - start;
		unsigned int after = gap - before - rounded;
		TreeInsert(block);
		InsertFree(before, index);
		InsertFree(after, block);
		count++;
		if (index == first)
		{
			freeFront = before;
		}
		if (following == last)
		{
			freeBack = after;
		}
		used = size - freeBack - freeFront;
		peak = Max(used, peak);
		return (void*)address;
	}

	// FUNCTION: ENGINE 0x10B853A0
	void ExternalHeap::Free(void* address)
	{
		if (!ready)
		{
			return;
		}
		unsigned short index = FindBlock((unsigned int)address - base);
		if (index >= limit + 3)
		{
			return;
		}
		unsigned int length = blocks[index].GetSize();
		unsigned short previous = GetPredecessor(index);
		unsigned short next = GetSuccessor(index);
		unsigned int before = (unsigned int)address - blocks[previous].GetSize() - blocks[previous].GetOffset() - base;
		unsigned int after = blocks[next].GetOffset() - length - (unsigned int)address + base;
		unsigned int merged = after + before + length;
		RemoveFree(before, previous);
		RemoveFree(after, index);
		TreeRemove((unsigned int)address - base);
		InsertFree(merged, previous);
		DeleteBlock(index);
		count--;
		if (previous == first && next == last)
		{
			freeFront = merged;
			freeBack = 0;
		}
		else if (previous == first)
		{
			freeFront = merged;
		}
		else if (next == last)
		{
			freeBack = merged;
		}
		used = size - freeBack - freeFront;
		peak = Max(used, peak);
	}

	// FUNCTION: ENGINE 0x10B85520
	// EQUIVALENT: same steps; the original saves ebx before the count test, which keeps its early `return true` paths apart (ours shares one)
	bool ExternalHeap::Resize(unsigned int start, unsigned int length)
	{
		if (!ready)
		{
			return false;
		}
		if (start == memory && length == size)
		{
			return true;
		}
		if (start < base + 16)
		{
			return false;
		}
		if (count == 0)
		{
			RemoveFree(size, first);
			memory = start;
			size = length;
			blocks[first].SetOffset(memory - base - 16);
			blocks[last].SetOffset(size - base + memory);
			InsertFree(size, first);
			freeFront = length;
			freeBack = 0;
			return true;
		}
		unsigned int usedStart = freeFront + memory;
		unsigned int usedEnd = used + usedStart;
		unsigned int end = length + start;
		if (start > usedStart || end < usedEnd)
		{
			return false;
		}
		unsigned short lastUsed = GetPredecessor(last);
		RemoveFree(freeFront, first);
		RemoveFree(freeBack, lastUsed);
		size = end - start;
		memory = start;
		blocks[first].SetOffset(start - base - 16);
		blocks[last].SetOffset(size - base + memory);
		freeFront = usedStart - start;
		freeBack = end - usedEnd;
		InsertFree(freeFront, first);
		InsertFree(freeBack, lastUsed);
		return true;
	}

	// FUNCTION: ENGINE 0x10B856A0
	bool ExternalHeap::Grow(unsigned int amount)
	{
		unsigned int length = size;
		unsigned int start = memory;
		switch (strategy)
		{
		case 0:
			length += amount;
			break;
		case 1:
			length += amount;
			start -= amount;
			break;
		}
		return Resize(start, length);
	}

	// FUNCTION: ENGINE 0x10B856E0
	bool ExternalHeap::Shrink(unsigned int amount)
	{
		unsigned int length = size;
		unsigned int start = memory;
		switch (strategy)
		{
		case 0:
			length -= amount;
			break;
		case 1:
			length -= amount;
			start += amount;
			break;
		}
		return Resize(start, length);
	}
}
