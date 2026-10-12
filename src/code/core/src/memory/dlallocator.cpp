// The dlmalloc parts follow Doug Lea's malloc 2.7 (public domain): no mmap, no trimming, MORECORE over the
// allocator's block, a variable MALLOC_ALIGNMENT and the fastbins in an array of their own.
#include <string.h>

#include "code/core/heap.h"
#include "code/core/memory/align.h"
#include "code/core/memory/dlallocator.h"
#include "code/core/utility.h"

#define INTERNAL_SIZE_T unsigned int
#define SIZE_SZ (sizeof(INTERNAL_SIZE_T))
#define MALLOC_ALIGNMENT (alignment)
#define MALLOC_ALIGN_MASK (MALLOC_ALIGNMENT - 1)
#define MIN_CHUNK_SIZE (sizeof(struct malloc_chunk))
#define MINSIZE (unsigned long)(((MIN_CHUNK_SIZE + MALLOC_ALIGN_MASK) & ~MALLOC_ALIGN_MASK))
#define REQUEST_OUT_OF_RANGE(req) ((unsigned long)(req) >= (unsigned long)(INTERNAL_SIZE_T)(-2 * MINSIZE))
#define request2size(req) \
	(((req) + SIZE_SZ + MALLOC_ALIGN_MASK < MINSIZE) ? MINSIZE : ((req) + SIZE_SZ + MALLOC_ALIGN_MASK) & ~MALLOC_ALIGN_MASK)
#define checked_request2size(req, sz) \
	if (REQUEST_OUT_OF_RANGE(req)) \
	{ \
		return 0; \
	} \
	(sz) = request2size(req);
#define chunk2mem(p) ((void*)((char*)(p) + 2 * SIZE_SZ))
#define mem2chunk(mem) ((mchunkptr)((char*)(mem) - 2 * SIZE_SZ))
#define PREV_INUSE 0x1
#define prev_inuse(p) ((p)->size & PREV_INUSE)
#define IS_MMAPPED 0x2
#define chunk_is_mmapped(p) ((p)->size & IS_MMAPPED)
#define SIZE_BITS (PREV_INUSE | IS_MMAPPED)
#define chunk_at_offset(p, s) ((mchunkptr)(((char*)(p)) + (s)))
#define inuse_bit_at_offset(p, s) (((mchunkptr)(((char*)(p)) + (s)))->size & PREV_INUSE)
#define set_inuse_bit_at_offset(p, s) (((mchunkptr)(((char*)(p)) + (s)))->size |= PREV_INUSE)
#define chunksize(p) ((p)->size & ~(SIZE_BITS))
#define set_head_size(p, s) ((p)->size = (((p)->size & PREV_INUSE) | (s)))
#define set_head(p, s) ((p)->size = (s))
#define set_foot(p, s) (((mchunkptr)((char*)(p) + (s)))->prev_size = (s))
#define bin_at(m, i) ((mbinptr)((char*)&((m)->bins[(i) << 1]) - (SIZE_SZ << 1)))
#define next_bin(b) ((mbinptr)((char*)(b) + (sizeof(mchunkptr) << 1)))
#define first(b) ((b)->fd)
#define last(b) ((b)->bk)
#define unlink(P, BK, FD) \
	{ \
		FD = P->fd; \
		BK = P->bk; \
		FD->bk = BK; \
		BK->fd = FD; \
	}
#define NBINS 128
#define SMALLBIN_WIDTH 8
#define MIN_LARGE_SIZE 512
#define in_smallbin_range(sz) ((unsigned long)(sz) < (unsigned long)MIN_LARGE_SIZE)
#define smallbin_index(sz) (((unsigned)(sz)) >> 3)
#define largebin_index(sz) \
	(((((unsigned long)(sz)) >> 6) <= 32) ? 56 + (((unsigned long)(sz)) >> 6) : \
	((((unsigned long)(sz)) >> 9) <= 20) ? 91 + (((unsigned long)(sz)) >> 9) : \
	((((unsigned long)(sz)) >> 12) <= 10) ? 110 + (((unsigned long)(sz)) >> 12) : \
	((((unsigned long)(sz)) >> 15) <= 4) ? 119 + (((unsigned long)(sz)) >> 15) : \
	((((unsigned long)(sz)) >> 18) <= 2) ? 124 + (((unsigned long)(sz)) >> 18) : 126)
#define unsorted_chunks(M) (bin_at(M, 1))
#define initial_top(M) (unsorted_chunks(M))
#define BINMAPSHIFT 5
#define BINMAPSIZE (NBINS / (1U << BINMAPSHIFT))
#define idx2block(i) ((i) >> BINMAPSHIFT)
#define idx2bit(i) ((1U << ((i) & ((1U << BINMAPSHIFT) - 1))))
#define mark_bin(m, i) ((m)->binmap[idx2block(i)] |= idx2bit(i))
#define fastbin_index(sz) ((((unsigned int)(sz)) >> 3) - 2)
#define MAX_FAST_SIZE 80
#define NFASTBINS (fastbin_index(request2size(MAX_FAST_SIZE)) + 1)
#define FASTBIN_CONSOLIDATION_THRESHOLD (65536UL)
#define FASTCHUNKS_BIT (1U)
#define have_fastchunks(M) (((M)->max_fast & FASTCHUNKS_BIT) == 0)
#define clear_fastchunks(M) ((M)->max_fast |= FASTCHUNKS_BIT)
#define set_fastchunks(M) ((M)->max_fast &= ~FASTCHUNKS_BIT)
#define NONCONTIGUOUS_BIT (2U)
#define contiguous(M) (((M)->max_fast & NONCONTIGUOUS_BIT) == 0)
#define set_max_fast(M, s) \
	(M)->max_fast = (((s) == 0) ? SMALLBIN_WIDTH : request2size(s)) | FASTCHUNKS_BIT | ((M)->max_fast & NONCONTIGUOUS_BIT)
#define MORECORE_FAILURE (-1)
#define DEFAULT_MXFAST 64
#define DEFAULT_TRIM_THRESHOLD (128 * 1024)
#define DEFAULT_TOP_PAD (0)
#define DEFAULT_MMAP_THRESHOLD (128 * 1024)
#define DEFAULT_MMAP_MAX (0)
#define malloc_getpagesize (8)
#define get_malloc_state() (state)
#define M_MXFAST 1
#define M_TRIM_THRESHOLD -1
#define M_TOP_PAD -2
#define M_MMAP_THRESHOLD -3
#define M_MMAP_MAX -4

namespace core
{
	// FUNCTION: ENGINE 0x1064AE30
	inline void* MemoryDlAllocator::operator new(unsigned int size, void* where)
	{
		gObjectHeap = -1;
		return where;
	}

	// FUNCTION: ENGINE 0x1064AE70
	void coreDlMalloc::malloc_init_state(mstate av)
	{
		int i;
		mbinptr bin;

		for (i = 1; i < NBINS; ++i)
		{
			bin = bin_at(av, i);
			bin->fd = bin->bk = bin;
		}

		av->top_pad = DEFAULT_TOP_PAD;
		av->n_mmaps_max = DEFAULT_MMAP_MAX;
		av->mmap_threshold = DEFAULT_MMAP_THRESHOLD;
		av->trim_threshold = DEFAULT_TRIM_THRESHOLD;

		set_max_fast(av, DEFAULT_MXFAST);
		av->top = initial_top(av);
		av->pagesize = malloc_getpagesize;
	}

	// FUNCTION: ENGINE 0x1064AF00
	void coreDlMalloc::malloc_consolidate(mstate av)
	{
		mfastbinptr* fb;
		mfastbinptr* maxfb;
		mchunkptr p;
		mchunkptr nextp;
		mchunkptr unsorted_bin;
		mchunkptr first_unsorted;
		mchunkptr nextchunk;
		INTERNAL_SIZE_T size;
		INTERNAL_SIZE_T nextsize;
		INTERNAL_SIZE_T prevsize;
		int nextinuse;
		mchunkptr bck;
		mchunkptr fwd;

		if (av->max_fast != 0)
		{
			clear_fastchunks(av);

			unsorted_bin = unsorted_chunks(av);

			maxfb = &(av->fastbins[fastbin_index(av->max_fast)]);
			fb = &(av->fastbins[0]);
			do
			{
				if ((p = *fb) != 0)
				{
					*fb = 0;

					do
					{
						nextp = p->fd;

						size = p->size & ~PREV_INUSE;
						nextchunk = chunk_at_offset(p, size);
						nextsize = chunksize(nextchunk);

						if (!prev_inuse(p))
						{
							prevsize = p->prev_size;
							size += prevsize;
							p = chunk_at_offset(p, -((long)prevsize));
							unlink(p, bck, fwd);
						}

						if (nextchunk != av->top)
						{
							nextinuse = inuse_bit_at_offset(nextchunk, nextsize);
							set_head(nextchunk, nextsize);

							if (!nextinuse)
							{
								size += nextsize;
								unlink(nextchunk, bck, fwd);
							}

							first_unsorted = unsorted_bin->fd;
							unsorted_bin->fd = p;
							first_unsorted->bk = p;

							set_head(p, size | PREV_INUSE);
							p->bk = unsorted_bin;
							p->fd = first_unsorted;
							set_foot(p, size);
						}

						else
						{
							size += nextsize;
							set_head(p, size | PREV_INUSE);
							av->top = p;
						}

					}
					while ((p = nextp) != 0);

				}
			}
			while (fb++ != maxfb);
		}
		else
		{
			malloc_init_state(av);
		}
	}

	// FUNCTION: ENGINE 0x1064AFF0
	int coreDlMalloc::mALLOPt(int param_number, int value)
	{
		mstate av = get_malloc_state();
		malloc_consolidate(av);

		switch (param_number)
		{
		case M_MXFAST:
			if (value >= 0 && value <= MAX_FAST_SIZE)
			{
				set_max_fast(av, value);
				return 1;
			}
			else
			{
				return 0;
			}

		case M_TRIM_THRESHOLD:
			av->trim_threshold = value;
			return 1;

		case M_TOP_PAD:
			av->top_pad = value;
			return 1;

		case M_MMAP_THRESHOLD:
			av->mmap_threshold = value;
			return 1;

		case M_MMAP_MAX:
			if (value != 0)
			{
				return 0;
			}
			av->n_mmaps_max = value;
			return 1;

		default:
			return 0;
		}
	}

	// FUNCTION: ENGINE 0x1064B120
	void MemoryDlAllocator_Implementation::SetAutoRelease(bool on)
	{
		autoRelease = on;
	}

	// FUNCTION: ENGINE 0x1064B130
	inline MemoryDlAllocator_Implementation::~MemoryDlAllocator_Implementation()
	{
	}

	// FUNCTION: ENGINE 0x1064B180
	inline char* coreDlMalloc::MORECORE(long size)
	{
		char* old = brk;
		if (old + size >= end)
		{
			return (char*)MORECORE_FAILURE;
		}
		brk = old + size;
		return old;
	}

	// FUNCTION: ENGINE 0x1064B1A0
	void MemoryDlAllocator_Implementation::AddRef()
	{
		refs++;
	}

	// FUNCTION: ENGINE 0x1064B1B0
	bool MemoryDlAllocator_Implementation::GetStatUnlocked(int id, int* value)
	{
		unsigned int capacity = end - base;
		switch (id)
		{
		case 0:
			*value = count;
			return true;
		case 1:
			*value = capacity;
			return true;
		case 17:
			*value = total;
			return true;
		case 2:
			*value = bytes;
			return true;
		case 3:
			capacity -= bytes;
			*value = capacity;
			if (count > 0)
			{
				*value = capacity - alignment + 8;
			}
			return true;
		case 7:
			*value = peak + alignment - 8;
			return true;
		case 10:
			*value = requested;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1064B280
	inline bool MemoryDlAllocator_Implementation::ResetStatUnlocked(int id)
	{
		switch (id)
		{
		case 7:
			peak = 0;
			return true;
		case 10:
			requested = 0;
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x1064B2B0
	bool MemoryDlAllocator_Implementation::GetStat(int id, int* value)
	{
		AllocatorLock lock(this);
		return GetStatUnlocked(id, value);
	}

	// FUNCTION: ENGINE 0x1064B2F0
	bool MemoryDlAllocator_Implementation::ResetStat(int id)
	{
		AllocatorLock lock(this);
		return ResetStatUnlocked(id);
	}

	// FUNCTION: ENGINE 0x1064B340
	int MemoryDlAllocator_Implementation::GetType()
	{
		return 1;
	}

	// FUNCTION: ENGINE 0x1064B350
	void MemoryDlAllocator_Implementation::GetRange(MemoryRange* range, int index)
	{
		range->start = (unsigned int)memory;
		range->end = (unsigned int)end;
	}

	// FUNCTION: ENGINE 0x1064B370
	bool MemoryDlAllocator_Implementation::IsThreadSafe()
	{
		return true;
	}

	// FUNCTION: ENGINE 0x1064B390
	void coreDlMalloc::fREe(void* mem)
	{
		mstate av = get_malloc_state();

		mchunkptr p;
		INTERNAL_SIZE_T size;
		mfastbinptr* fb;
		mchunkptr nextchunk;
		INTERNAL_SIZE_T nextsize;
		int nextinuse;
		INTERNAL_SIZE_T prevsize;
		mchunkptr bck;
		mchunkptr fwd;

		if (mem != 0)
		{
			p = mem2chunk(mem);
			size = chunksize(p);

			if ((unsigned long)(size) <= (unsigned long)(av->max_fast))
			{
				set_fastchunks(av);
				fb = &(av->fastbins[fastbin_index(size)]);
				p->fd = *fb;
				*fb = p;
			}

			else if (!chunk_is_mmapped(p))
			{
				nextchunk = chunk_at_offset(p, size);
				nextsize = chunksize(nextchunk);

				if (!prev_inuse(p))
				{
					prevsize = p->prev_size;
					size += prevsize;
					p = chunk_at_offset(p, -((long)prevsize));
					unlink(p, bck, fwd);
				}

				if (nextchunk != av->top)
				{
					nextinuse = inuse_bit_at_offset(nextchunk, nextsize);
					set_head(nextchunk, nextsize);

					if (!nextinuse)
					{
						unlink(nextchunk, bck, fwd);
						size += nextsize;
					}

					bck = unsorted_chunks(av);
					fwd = bck->fd;
					p->bk = bck;
					p->fd = fwd;
					bck->fd = p;
					fwd->bk = p;

					set_head(p, size | PREV_INUSE);
					set_foot(p, size);
				}

				else
				{
					size += nextsize;
					set_head(p, size | PREV_INUSE);
					av->top = p;
				}

				if ((unsigned long)(size) >= FASTBIN_CONSOLIDATION_THRESHOLD)
				{
					if (have_fastchunks(av))
					{
						malloc_consolidate(av);
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x1064B470
	void MemoryDlAllocator_Implementation::Release()
	{
		if (refs == 1)
		{
			void* own = block;
			int ownHeap = blockHeap;
			if (!inPlace)
			{
				delete this;
			}
			else
			{
				this->~MemoryDlAllocator_Implementation();
			}
			if (own != 0)
			{
				HeapFree(ownHeap, own);
			}
		}
		else
		{
			refs--;
		}
	}

	// mallopt(M_MXFAST, 0) without the switch
	__forceinline void coreDlMalloc::DisableFastbins()
	{
		mstate av = get_malloc_state();
		malloc_consolidate(av);
		set_max_fast(av, 0);
	}

	__forceinline void MemoryDlAllocator_Implementation::Reset()
	{
		brk = base;
		mfastbinptr* fastbins = state->fastbins;
		memset(state, 0, sizeof(malloc_state));
		state->fastbins = fastbins;
		if (state->fastbins != 0)
		{
			memset(state->fastbins, 0, fastbinCount * sizeof(mfastbinptr));
		}
		if (noFastbins)
		{
			DisableFastbins();
		}
	}

	// FUNCTION: ENGINE 0x1064B4C0
	void MemoryDlAllocator_Implementation::Free(void* mem)
	{
		if (mem != 0)
		{
			AllocatorLock lock(this);
			bytes -= chunksize(mem2chunk(mem));
			fREe(mem);
			if (--count == 0)
			{
				Reset();
			}
		}
	}

	// FUNCTION: ENGINE 0x1064B570
	void MemoryDlAllocator_Implementation::FreeAligned(void* mem)
	{
		if (mem != 0)
		{
			AllocatorLock lock(this);
			bytes -= chunksize(mem2chunk(mem));
			fREe(mem);
			if (--count == 0)
			{
				Reset();
			}
		}
	}

	// FUNCTION: ENGINE 0x1064B620
	void* coreDlMalloc::sYSMALLOc(INTERNAL_SIZE_T nb, mstate av)
	{
		mchunkptr old_top;
		INTERNAL_SIZE_T old_size;
		char* old_end;

		long size;
		char* brk;

		long correction;
		char* snd_brk;

		INTERNAL_SIZE_T front_misalign;
		INTERNAL_SIZE_T end_misalign;
		char* aligned_brk;

		mchunkptr p;
		mchunkptr remainder;
		unsigned long remainder_size;

		unsigned long sum;

		unsigned int pagemask = av->pagesize - 1;

		old_top = av->top;
		old_size = chunksize(old_top);
		old_end = (char*)(chunk_at_offset(old_top, old_size));

		brk = snd_brk = (char*)(MORECORE_FAILURE);

		size = nb + av->top_pad + MINSIZE;

		if (contiguous(av))
		{
			size -= old_size;
		}

		size = (size + pagemask) & ~pagemask;

		if (size > 0)
		{
			brk = (char*)(MORECORE(size));
		}

		if (brk != (char*)(MORECORE_FAILURE))
		{
			av->sbrked_mem += size;

			if (brk == old_end && snd_brk == (char*)(MORECORE_FAILURE))
			{
				set_head(old_top, (size + old_size) | PREV_INUSE);
			}

			else
			{
				front_misalign = 0;
				end_misalign = 0;
				correction = 0;
				aligned_brk = brk;

				if (contiguous(av))
				{
					front_misalign = (INTERNAL_SIZE_T)chunk2mem(brk) & MALLOC_ALIGN_MASK;
					if (front_misalign > 0)
					{
						correction = MALLOC_ALIGNMENT - front_misalign;
						aligned_brk += correction;
					}

					correction += old_size;

					end_misalign = (INTERNAL_SIZE_T)(brk + size + correction);
					correction += ((end_misalign + pagemask) & ~pagemask) - end_misalign;

					snd_brk = (char*)(MORECORE(correction));

					if (snd_brk == (char*)(MORECORE_FAILURE))
					{
						correction = 0;
						snd_brk = (char*)(MORECORE(0));
					}
				}

				else
				{
					if (snd_brk == (char*)(MORECORE_FAILURE))
					{
						snd_brk = (char*)(MORECORE(0));
					}
				}

				if (snd_brk != (char*)(MORECORE_FAILURE))
				{
					av->top = (mchunkptr)aligned_brk;
					set_head(av->top, (snd_brk - aligned_brk + correction) | PREV_INUSE);
					av->sbrked_mem += correction;

					if (old_size != 0)
					{
						old_size = (old_size - 3 * SIZE_SZ) & ~MALLOC_ALIGN_MASK;
						set_head(old_top, old_size | PREV_INUSE);

						chunk_at_offset(old_top, old_size)->size = SIZE_SZ | PREV_INUSE;

						chunk_at_offset(old_top, old_size + SIZE_SZ)->size = SIZE_SZ | PREV_INUSE;

						if (old_size >= MINSIZE)
						{
							fREe(chunk2mem(old_top));
						}
					}
				}
			}

			sum = av->sbrked_mem;
			if (sum > (unsigned long)(av->max_sbrked_mem))
			{
				av->max_sbrked_mem = sum;
			}

			sum += av->mmapped_mem;
			if (sum > (unsigned long)(av->max_total_mem))
			{
				av->max_total_mem = sum;
			}

			p = av->top;
			size = chunksize(p);

			if ((unsigned long)(size) >= (unsigned long)(nb + MINSIZE))
			{
				remainder_size = size - nb;
				remainder = chunk_at_offset(p, nb);
				av->top = remainder;
				set_head(p, nb | PREV_INUSE);
				set_head(remainder, remainder_size | PREV_INUSE);
				return chunk2mem(p);
			}
		}

		return 0;
	}

	// FUNCTION: ENGINE 0x1064B810
	void* coreDlMalloc::mALLOc(unsigned int bytes)
	{
		mstate av = get_malloc_state();

		INTERNAL_SIZE_T nb;
		unsigned int idx;
		mbinptr bin;
		mfastbinptr* fb;

		mchunkptr victim;
		INTERNAL_SIZE_T size;
		int victim_index;

		mchunkptr remainder;
		unsigned long remainder_size;

		unsigned int block;
		unsigned int bit;
		unsigned int map;

		mchunkptr fwd;
		mchunkptr bck;

		checked_request2size(bytes, nb);

		if ((unsigned long)(nb) <= (unsigned long)(av->max_fast))
		{
			fb = &(av->fastbins[(fastbin_index(nb))]);
			if ((victim = *fb) != 0)
			{
				*fb = victim->fd;
				return chunk2mem(victim);
			}
		}

		if (in_smallbin_range(nb))
		{
			idx = smallbin_index(nb);
			bin = bin_at(av, idx);

			if ((victim = last(bin)) != bin)
			{
				if (victim == 0)
				{
					malloc_consolidate(av);
				}
				else
				{
					bck = victim->bk;
					set_inuse_bit_at_offset(victim, nb);
					bin->bk = bck;
					bck->fd = bin;

					return chunk2mem(victim);
				}
			}
		}

		else
		{
			idx = largebin_index(nb);
			if (have_fastchunks(av))
			{
				malloc_consolidate(av);
			}
		}

		for (;;)
		{
			while ((victim = unsorted_chunks(av)->bk) != unsorted_chunks(av))
			{
				bck = victim->bk;
				size = chunksize(victim);

				if (in_smallbin_range(nb) && bck == unsorted_chunks(av) && victim == av->last_remainder
					&& (unsigned long)(size) > (unsigned long)(nb + MINSIZE))
				{
					remainder_size = size - nb;
					remainder = chunk_at_offset(victim, nb);
					unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;
					av->last_remainder = remainder;
					remainder->bk = remainder->fd = unsorted_chunks(av);

					set_head(victim, nb | PREV_INUSE);
					set_head(remainder, remainder_size | PREV_INUSE);
					set_foot(remainder, remainder_size);

					return chunk2mem(victim);
				}

				unsorted_chunks(av)->bk = bck;
				bck->fd = unsorted_chunks(av);

				if (size == nb)
				{
					set_inuse_bit_at_offset(victim, size);
					return chunk2mem(victim);
				}

				if (in_smallbin_range(size))
				{
					victim_index = smallbin_index(size);
					bck = bin_at(av, victim_index);
					fwd = bck->fd;
				}
				else
				{
					victim_index = largebin_index(size);
					bck = bin_at(av, victim_index);
					fwd = bck->fd;

					if (fwd != bck)
					{
						size |= PREV_INUSE;
						if ((unsigned long)(size) <= (unsigned long)(bck->bk->size))
						{
							fwd = bck;
							bck = bck->bk;
						}
						else
						{
							while ((unsigned long)(size) < (unsigned long)(fwd->size))
							{
								fwd = fwd->fd;
							}
							bck = fwd->bk;
						}
					}
				}

				mark_bin(av, victim_index);
				victim->bk = bck;
				victim->fd = fwd;
				fwd->bk = victim;
				bck->fd = victim;
			}

			if (!in_smallbin_range(nb))
			{
				bin = bin_at(av, idx);

				if ((victim = last(bin)) != bin && (unsigned long)(first(bin)->size) >= (unsigned long)(nb))
				{
					while (((unsigned long)(size = chunksize(victim)) < (unsigned long)(nb)))
					{
						victim = victim->bk;
					}

					remainder_size = size - nb;
					unlink(victim, bck, fwd);

					if (remainder_size < MINSIZE)
					{
						set_inuse_bit_at_offset(victim, size);
						return chunk2mem(victim);
					}
					else
					{
						remainder = chunk_at_offset(victim, nb);
						unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;
						remainder->bk = remainder->fd = unsorted_chunks(av);
						set_head(victim, nb | PREV_INUSE);
						set_head(remainder, remainder_size | PREV_INUSE);
						set_foot(remainder, remainder_size);
						return chunk2mem(victim);
					}
				}
			}

			++idx;
			bin = bin_at(av, idx);
			block = idx2block(idx);
			map = av->binmap[block];
			bit = idx2bit(idx);

			for (;;)
			{
				if (bit > map || bit == 0)
				{
					do
					{
						if (++block >= BINMAPSIZE)
						{
							goto use_top;
						}
					}
					while ((map = av->binmap[block]) == 0);

					bin = bin_at(av, (block << BINMAPSHIFT));
					bit = 1;
				}

				while ((bit & map) == 0)
				{
					bin = next_bin(bin);
					bit <<= 1;
				}

				victim = last(bin);

				if (victim == bin)
				{
					av->binmap[block] = map &= ~bit;
					bin = next_bin(bin);
					bit <<= 1;
				}

				else
				{
					size = chunksize(victim);

					remainder_size = size - nb;

					bck = victim->bk;
					bin->bk = bck;
					bck->fd = bin;

					if (remainder_size < MINSIZE)
					{
						set_inuse_bit_at_offset(victim, size);
						return chunk2mem(victim);
					}

					else
					{
						remainder = chunk_at_offset(victim, nb);

						unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;
						remainder->bk = remainder->fd = unsorted_chunks(av);
						if (in_smallbin_range(nb))
						{
							av->last_remainder = remainder;
						}

						set_head(victim, nb | PREV_INUSE);
						set_head(remainder, remainder_size | PREV_INUSE);
						set_foot(remainder, remainder_size);
						return chunk2mem(victim);
					}
				}
			}

		use_top:
			victim = av->top;
			size = chunksize(victim);

			if ((unsigned long)(size) >= (unsigned long)(nb + MINSIZE))
			{
				remainder_size = size - nb;
				remainder = chunk_at_offset(victim, nb);
				av->top = remainder;
				set_head(victim, nb | PREV_INUSE);
				set_head(remainder, remainder_size | PREV_INUSE);

				return chunk2mem(victim);
			}

			else if (have_fastchunks(av))
			{
				malloc_consolidate(av);
				idx = smallbin_index(nb);
			}

			else
			{
				return sYSMALLOc(nb, av);
			}
		}
	}

	// FUNCTION: ENGINE 0x1064BD00
	void* coreDlMalloc::mEMALIGn(unsigned int alignment, unsigned int bytes)
	{
		INTERNAL_SIZE_T nb;
		char* m;
		mchunkptr p;
		char* brk;
		mchunkptr newp;
		INTERNAL_SIZE_T newsize;
		INTERNAL_SIZE_T leadsize;
		mchunkptr remainder;
		unsigned long remainder_size;
		INTERNAL_SIZE_T size;

		if (alignment <= this->alignment)
		{
			return mALLOc(bytes);
		}

		if (alignment < (((MIN_CHUNK_SIZE + this->alignment - 1) & ~(this->alignment - 1))))
		{
			alignment = ((MIN_CHUNK_SIZE + this->alignment - 1) & ~(this->alignment - 1));
		}

		if ((alignment & (alignment - 1)) != 0)
		{
			unsigned int a = this->alignment * 2;
			while ((unsigned long)a < (unsigned long)alignment)
			{
				a <<= 1;
			}
			alignment = a;
		}

#undef MALLOC_ALIGNMENT
#define MALLOC_ALIGNMENT (this->alignment)
		checked_request2size(bytes, nb);

		m = (char*)(mALLOc(nb + alignment + MINSIZE));

		if (m == 0)
		{
			return 0;
		}

		p = mem2chunk(m);

		if ((((unsigned long)(m)) % alignment) != 0)
		{
			brk = (char*)mem2chunk(((unsigned long)(m + alignment - 1)) & -((signed long)alignment));
			if ((unsigned long)(brk - (char*)(p)) < MINSIZE)
			{
				brk += alignment;
			}

			newp = (mchunkptr)brk;
			leadsize = brk - (char*)(p);
			newsize = chunksize(p) - leadsize;

			if (chunk_is_mmapped(p))
			{
				newp->prev_size = p->prev_size + leadsize;
				set_head(newp, newsize | IS_MMAPPED);
				return chunk2mem(newp);
			}

			set_head(newp, newsize | PREV_INUSE);
			set_inuse_bit_at_offset(newp, newsize);
			set_head_size(p, leadsize | (p->size & PREV_INUSE));
			fREe(chunk2mem(p));
			p = newp;
		}

		if (!chunk_is_mmapped(p))
		{
			size = chunksize(p);
			if ((unsigned long)(size) > (unsigned long)(nb + MINSIZE))
			{
				remainder_size = size - nb;
				remainder = chunk_at_offset(p, nb);
				set_head(remainder, remainder_size | PREV_INUSE);
				set_head_size(p, nb);
				fREe(chunk2mem(remainder));
			}
		}

		return chunk2mem(p);
#undef MALLOC_ALIGNMENT
#define MALLOC_ALIGNMENT (alignment)
	}

	// FUNCTION: ENGINE 0x1064BEB0
	void* MemoryDlAllocator_Implementation::Alloc(unsigned int size)
	{
		AllocatorLock lock(this);
		void* mem = mALLOc(size);
		if (mem != 0)
		{
			bytes += chunksize(mem2chunk(mem));
			peak = Max(bytes, peak);
			requested += size != 0 ? RoundUp(size, alignment) : alignment;
			count++;
			total++;
		}
		return mem;
	}

	// FUNCTION: ENGINE 0x1064BF30
	void* MemoryDlAllocator_Implementation::AllocAligned(unsigned int size, unsigned int align)
	{
		AllocatorLock lock(this);
		void* mem = mEMALIGn(align, size);
		if (mem != 0)
		{
			bytes += chunksize(mem2chunk(mem));
			peak = Max(bytes, peak);
			requested += size != 0 ? RoundUp(size, align) : align;
			count++;
			total++;
		}
		return mem;
	}

	// FUNCTION: ENGINE 0x1064C030
	MemoryDlAllocator_Implementation::MemoryDlAllocator_Implementation(void* own, int ownHeap, bool placed,
		void* start, unsigned int size, const char* name, unsigned int align, bool noFast)
		: count(0), total(0), bytes(0), requested(0), peak(0), block(own), inPlace(placed), blockHeap(ownHeap),
		noFastbins(noFast), autoRelease(true)
	{
		refs = 0;
		SetName(name);
		if (align > 8)
		{
			alignment = align;
		}
		else
		{
			alignment = 8;
		}
		memorySize = size;
		end = (char*)start + size;
		memory = start;
		fastbinCount = NFASTBINS;
		unsigned int address = AlignUp<unsigned int>((unsigned int)start, 8);
		unsigned int after = AlignUp<unsigned int>(address + sizeof(malloc_state), 8);
		unsigned int fastbins = AlignUp<unsigned int>(after, 8);
		unsigned int heapStart = AlignUp<unsigned int>(fastbins + fastbinCount * sizeof(mfastbinptr), 8);
		state = (mstate)address;
		memset((void*)address, 0, sizeof(malloc_state));
		char* first;
		if (noFastbins)
		{
			state->fastbins = 0;
			first = (char*)after;
		}
		else
		{
			state->fastbins = (mfastbinptr*)fastbins;
			memset(state->fastbins, 0, fastbinCount * sizeof(mfastbinptr));
			first = (char*)heapStart;
		}
		base = first;
		brk = first;
		if (noFastbins)
		{
			DisableFastbins();
		}
	}

	// FUNCTION: ENGINE 0x1064C1E0
	MemoryDlAllocator::MemoryDlAllocator(void* own, int ownHeap, bool placed, void* start, unsigned int size,
		const char* name, unsigned int align, bool noFast)
		: MemoryDlAllocator_Implementation(own, ownHeap, placed, start, size, name, align, noFast)
	{
	}

	// FUNCTION: ENGINE 0x1064C240
	inline MemoryDlAllocator::~MemoryDlAllocator()
	{
	}

	// FUNCTION: ENGINE 0x1064C300
	MemoryDlAllocator* CreateDlAllocator(bool allocate, int heap, bool inPlace, void* memory, unsigned int size,
		const char* name, unsigned int align, bool noFastbins, bool manual)
	{
		MemoryDlAllocator* allocator;
		if (inPlace)
		{
			unsigned int header = RoundUp(sizeof(MemoryDlAllocator), 0x10);
			allocator = new (memory) MemoryDlAllocator(heap, (char*)memory + header, size - header, name, align,
				noFastbins);
		}
		else if (allocate)
		{
			unsigned int header = RoundUp(sizeof(MemoryDlAllocator), 0x10);
			void* own = HeapAlloc(heap, header + size);
			allocator = new (own) MemoryDlAllocator(own, heap, true, (char*)own + header, size, name, align,
				noFastbins);
		}
		else
		{
			allocator = new (heap) MemoryDlAllocator(0, heap, false, memory, size, name, align, noFastbins);
		}
		if (manual)
		{
			allocator->autoRelease = false;
		}
		return allocator;
	}
}
