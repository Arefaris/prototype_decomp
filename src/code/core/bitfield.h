// core::BitField<T>: a set of flags in one integer (class and method names are guesses; no name survives). The
// members are defined outside the class, so they are not inlined (/Ob1) and every unit that uses one keeps a COMDAT
// copy: 0x10433D70 / 0x10433D90 (unsigned int constructor and ClearAll), 0x101E0520 / 0x10444290 (unsigned short
// Set / Clear), 0x106DEA40 (unsigned int Test) and 0x106DEBE0 (unsigned short Set(bit, value)) are such copies.
#ifndef CORE_BITFIELD_H
#define CORE_BITFIELD_H

namespace core
{
	template<class T> class BitField
	{
	public:
		BitField();
		void ClearAll();
		void Set(T bit);
		void Clear(T bit);
		bool Test(T bit) const;
		void Set(T bit, bool value);

		// The users that set flags in place or a mask in
		void SetMask(T mask)
		{
			mBits |= mask;
		}
		// The users that read a flag in place shift the word (shr / test)
		bool IsSet(int bit) const
		{
			return ((mBits >> bit) & 1) != 0;
		}

		T mBits;
	};

	template<class T> BitField<T>::BitField()
	{
		mBits = 0;
	}

	template<class T> void BitField<T>::ClearAll()
	{
		mBits = 0;
	}

	template<class T> void BitField<T>::Set(T bit)
	{
		T mask = 1;
		mask <<= bit;
		mBits |= mask;
	}

	template<class T> void BitField<T>::Clear(T bit)
	{
		T mask = 1;
		mask <<= bit;
		mBits &= ~mask;
	}

	template<class T> bool BitField<T>::Test(T bit) const
	{
		return ((1 << bit) & mBits) != 0;
	}

	template<class T> void BitField<T>::Set(T bit, bool value)
	{
		if (value)
		{
			Set(bit);
		}
		else
		{
			Clear(bit);
		}
	}
}

#endif
