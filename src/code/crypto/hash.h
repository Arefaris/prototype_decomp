// crypto::Hash with the MD5 hash and crypto::Mac with the MD5 based message authentication code (RTTI names; one
// virtual after the destructor each, the computation of the value of a text). Member names are guesses.
#ifndef CRYPTO_HASH_H
#define CRYPTO_HASH_H

#include "code/crypto/cipher.h"

namespace crypto
{
	// The sixteen bytes of a hash or a code
	struct HashValue
	{
		unsigned int words[4];
	};

	class Hash
	{
	public:
		// 0x109405E0
		explicit Hash(int type)
		{
			mType = type;
		}
		// 0x10940600
		virtual ~Hash()
		{
		}
		// The hash of length bytes of data
		virtual void Compute(const void* data, int length, HashValue* out) = 0;

		int mType;                 // 0x04
	};

	// The MD5 hash (vftable 0x10E8B548)
	class MD5Hash : public Hash
	{
	public:
		// 0x10940610
		__declspec(noinline) MD5Hash() : Hash(0)
		{
		}
		// 0x10940620 / 0x109406A0
		virtual ~MD5Hash()
		{
		}
		// 0x10940630
		virtual void Compute(const void* data, int length, HashValue* out);
	};

	class Mac
	{
	public:
		// 0x109406C0
		Mac(int type, const CipherKey& key)
		{
			mType = type;
			mKey = key;
		}
		// 0x109406F0
		virtual ~Mac()
		{
		}
		// The code of length bytes of data
		virtual void Compute(const void* data, int length, HashValue* out) = 0;

		int mType;                 // 0x04
		CipherKey mKey;            // 0x08
	};

	// The message authentication code over MD5 (vftable 0x10E8B560)
	class MD5HMac : public Mac
	{
	public:
		// 0x10940700
		__declspec(noinline) explicit MD5HMac(const CipherKey& key) : Mac(0, key)
		{
		}
		// 0x10940740 / 0x10940790
		virtual ~MD5HMac()
		{
		}
		// 0x10940750
		virtual void Compute(const void* data, int length, HashValue* out);
	};

	// 0x1093FD80 / 0x1093FDA0: a new hash / code of the kind (0 MD5), null for another kind
	Hash* CreateHash(int kind);
	Mac* CreateMac(int kind, const CipherKey& key);
}

#endif
