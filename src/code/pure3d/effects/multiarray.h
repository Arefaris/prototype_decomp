// pure3d::particles::MultiArray<N> and AttributeData<N> (RTTI names, N is 57; the engine's code is the assert path
// effects/multiarray.hpp, a header): the attributes of a block of particles. The block is one allocation that the
// arrays of the attributes share; every array is said by a pair of offsets into it. AttributeData adds four lists of
// such pairs (the attributes by kind). Member names are guesses.
#ifndef PURE3D_EFFECTS_MULTIARRAY_H
#define PURE3D_EFFECTS_MULTIARRAY_H

namespace core
{
	void Free(void* block);
}

namespace pure3d
{
	namespace particles
	{
		// Where an array starts and ends in the block (offsets)
		struct Range
		{
			int first;
			int second;
		};

		// An array of pairs the attributes of one kind are said by
		struct RangeList
		{
			Range* begin;
			Range* end;
		};

		// The arrays' addresses
		struct Span
		{
			Span()
			{
			}
			Span(unsigned char* newBegin, unsigned char* newEnd) : begin(newBegin), end(newEnd)
			{
			}

			unsigned char* begin;
			unsigned char* end;
		};

		template<int N> class MultiArray
		{
		public:
			MultiArray()
			{
				block = 0;
				end = 0;
				ownsBlock = true;
				for (int i = 0; i < N; i++)
				{
					ranges[i].first = 0;
					ranges[i].second = 0;
				}
			}
			virtual ~MultiArray()
			{
				Free();
			}
			// Gives the block back (when the array owns it) and forgets the arrays (not inline in the engine)
			void Free();

			Range ranges[N];
			unsigned char* block;
			unsigned char* end;
			bool ownsBlock;
		};

		template<int N> void MultiArray<N>::Free()
		{
			if (block != 0)
			{
				if (ownsBlock)
				{
					core::Free(block);
				}
				block = 0;
				end = 0;
				for (int i = 0; i < N; i++)
				{
					ranges[i].first = 0;
					ranges[i].second = 0;
				}
			}
		}

		template<int N> class AttributeData : public MultiArray<N>
		{
		public:
			AttributeData();

			// The arrays of the entry in the list: their addresses in the block (the same for a block that is not changed)
			Span GetSpan0(int index)
			{
				Span span;
				const Range* range = &lists[0].begin[index];
				span.begin = this->block + range->first;
				span.end = this->block + range->second;
				return span;
			}
			Span GetSpan0(int index) const
			{
				Span span;
				const Range* range = &lists[0].begin[index];
				span.begin = this->block + range->first;
				span.end = this->block + range->second;
				return span;
			}
			Span GetSpan1(int index)
			{
				Span span;
				const Range* range = &lists[1].begin[index];
				span.begin = this->block + range->first;
				span.end = this->block + range->second;
				return span;
			}
			Span GetSpan1(int index) const
			{
				Span span;
				const Range* range = &lists[1].begin[index];
				span.begin = this->block + range->first;
				span.end = this->block + range->second;
				return span;
			}
			Span GetSpan2(int index)
			{
				Span span;
				const Range* range = &lists[2].begin[index];
				span.begin = this->block + range->first;
				span.end = this->block + range->second;
				return span;
			}
			Span GetSpan2(int index) const
			{
				Span span;
				const Range* range = &lists[2].begin[index];
				span.begin = this->block + range->first;
				span.end = this->block + range->second;
				return span;
			}
			Span GetSpan3(int index)
			{
				Span span;
				const Range* range = &lists[3].begin[index];
				span.begin = this->block + range->first;
				span.end = this->block + range->second;
				return span;
			}
			Span GetSpan3(int index) const
			{
				Span span;
				const Range* range = &lists[3].begin[index];
				span.begin = this->block + range->first;
				span.end = this->block + range->second;
				return span;
			}
			// How many entries the first list has
			int GetCount0() const
			{
				return lists[0].end - lists[0].begin;
			}
			// Whether an entry of the lists is empty (no array)
			bool IsEmpty1(int index) const
			{
				return (lists[1].begin[index].second | lists[1].begin[index].first) == 0;
			}
			bool IsEmpty2(int index) const
			{
				return (lists[2].begin[index].second | lists[2].begin[index].first) == 0;
			}
			bool IsEmpty3(int index) const
			{
				return (lists[3].begin[index].second | lists[3].begin[index].first) == 0;
			}

			RangeList lists[4];
		};

		template<int N> AttributeData<N>::AttributeData()
		{
			for (int i = 0; i < 4; i++)
			{
				lists[i].begin = 0;
				lists[i].end = 0;
			}
		}
	}
}

#endif
