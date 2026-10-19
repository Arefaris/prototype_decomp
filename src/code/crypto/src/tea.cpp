// The block TEA of crypto::BlockTEACipher (unit guessed from the neighbouring cipher classes; names are guesses). The
// four functions are one template instantiated for words and for bytes; they are written out per type here so that
// each carries the annotation of its address. The key index of the bytes runs over sixteen bytes, that of the words
// over four words.
#include "code/crypto/tea.h"

namespace crypto
{
	#define TEA_MX(KEYMASK) (((z >> 5) ^ (y << 2)) + ((y >> 3) ^ (z << 4))) ^ ((sum ^ y) + (key[(p & (KEYMASK)) ^ e] ^ z))

	#define TEA_ENCRYPT_BODY(T, KEYMASK) \
		static T delta = GetDelta<T>(); \
		T y, z = v[n - 1], sum = 0, e, p; \
		if (n > 1) \
		{ \
			T rounds = 6 + 52 / n; \
			while (rounds-- > 0) \
			{ \
				sum += delta; \
				e = (sum >> 2) & 3; \
				for (p = 0; p < n - 1; p++) \
				{ \
					y = v[p + 1]; \
					z = v[p] += TEA_MX(KEYMASK); \
				} \
				y = v[0]; \
				z = v[n - 1] += TEA_MX(KEYMASK); \
			} \
		}

	#define TEA_DECRYPT_BODY(T, KEYMASK) \
		static T delta = GetDelta<T>(); \
		T y = v[0], z, sum = 0, e, p; \
		if (n > 1) \
		{ \
			T rounds = 6 + 52 / n; \
			sum = rounds * delta; \
			while (sum != 0) \
			{ \
				e = (sum >> 2) & 3; \
				for (p = n - 1; p > 0; p--) \
				{ \
					z = v[p - 1]; \
					y = v[p] -= TEA_MX(KEYMASK); \
				} \
				z = v[n - 1]; \
				y = v[0] -= TEA_MX(KEYMASK); \
				sum -= delta; \
			} \
		}

	// FUNCTION: ENGINE 0x1093FED0
	// EQUIVALENT: the same rounds with the same operations in the same order; the engine keeps the test of the inner loop
	// against the count of words minus one where ours drops the test that the entry test implies (49.1 %)
	template <> void TeaEncrypt<unsigned int>(unsigned int* v, unsigned int n, const unsigned int* key)
	{
		TEA_ENCRYPT_BODY(unsigned int, 3)
	}

	// FUNCTION: ENGINE 0x1093FFF0
	// NONMATCHING: the engine runs the rounds as a loop that is entered at its condition and keeps the key and the sum
	// in registers where ours enters the loop through two jumps and reloads them (19.2 %)
#ifdef NONMATCHING
	template <> void TeaEncrypt<unsigned char>(unsigned char* v, unsigned char n, const unsigned char* key)
	{
		TEA_ENCRYPT_BODY(unsigned char, 15)
	}
#endif

	// FUNCTION: ENGINE 0x10940130
	// EQUIVALENT: the same rounds with the same operations in the same order; the engine evaluates the term with the
	// right shifts of the previous word first where ours evaluates the other term first (74.7 %)
	template <> void TeaDecrypt<unsigned int>(unsigned int* v, unsigned int n, const unsigned int* key)
	{
		TEA_DECRYPT_BODY(unsigned int, 3)
	}

	// FUNCTION: ENGINE 0x10940240
	// EQUIVALENT: as the words' decryption, with the key index over sixteen bytes (46.2 %)
	template <> void TeaDecrypt<unsigned char>(unsigned char* v, unsigned char n, const unsigned char* key)
	{
		TEA_DECRYPT_BODY(unsigned char, 15)
	}
}
