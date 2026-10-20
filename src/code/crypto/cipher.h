// crypto::Cipher and its two kinds (RTTI names): the block TEA cipher (type 0) and the Blowfish cipher (type 1). A
// cipher keeps its type and a key of sixteen bytes; encryption and decryption are the two virtuals after the
// destructor. The classes of the hashes and the message authentication codes (Hash, MD5Hash, Mac, MD5HMac) sit next
// to them. Member names are guesses.
#ifndef CRYPTO_CIPHER_H
#define CRYPTO_CIPHER_H

namespace crypto
{
	// The sixteen bytes of a key
	struct CipherKey
	{
		unsigned int words[4];
	};

	class Cipher
	{
	public:
		// 0x1093FDE0 (the engine keeps a copy of the constructor and expands it in the other constructors)
		Cipher(int type, const CipherKey& key)
		{
			mType = type;
			mKey = key;
		}
		// 0x1093FE10
		virtual ~Cipher()
		{
		}
		// Encrypts size bytes into out (the number of bytes written goes to outSize; a null out only asks for the size)
		virtual void Encrypt(const void* in, int size, void* out, int* outSize) = 0;
		// Decrypts
		virtual void Decrypt(const void* in, int size, void* out, int* outSize) = 0;

		int mType;                 // 0x04
		CipherKey mKey;            // 0x08
	};

	// The block TEA over the words of the data, the bytes that remain over the bytes (vftable 0x10E8B51C)
	class BlockTEACipher : public Cipher
	{
	public:
		// 0x1093FE20 (the engine's factory calls the constructors)
		explicit BlockTEACipher(const CipherKey& key);
		// 0x1093FE60
		virtual ~BlockTEACipher();
		// 0x10940380 / 0x109403E0
		virtual void Encrypt(const void* in, int size, void* out, int* outSize);
		virtual void Decrypt(const void* in, int size, void* out, int* outSize);
	};

	// A word of the key schedule that is filled byte by byte
	union BlowfishWord
	{
		unsigned int word;
		struct
		{
			unsigned int b0 : 8;
			unsigned int b1 : 8;
			unsigned int b2 : 8;
			unsigned int b3 : 8;
		};
	};

	// The tables of Blowfish: the 18 words of the P array and the four S boxes of 256 words (0x1048 bytes)
	class BlowfishState
	{
	public:
		// 0x10943DE0: the tables of pi
		BlowfishState();
		// 0x10943DF0: puts the tables of pi back
		~BlowfishState();
		// 0x10940F10: the P array and the S boxes of pi
		void Reset();
		// 0x10943E00 / 0x10943E40: resets the tables and mixes a key in
		void SetKey(const char* key);
		void SetKey(const void* key, int length);
		// 0x10943BE0: mixes the key into the tables
		void Expand(const char* key, int length);
		// 0x109407B0 / 0x10940B60: one block of two words
		void EncryptBlock(unsigned int* left, unsigned int* right);
		void DecryptBlock(unsigned int* left, unsigned int* right);
		// 0x10943B80 / 0x10943BB0: size bytes (a multiple of 8) in blocks
		void EncryptBlocks(void* data, unsigned int size);
		void DecryptBlocks(void* data, unsigned int size);

		unsigned int mP[18];       // 0x00
		unsigned int mS[4][256];   // 0x48
	};

	// Blowfish over blocks of eight bytes; the data is preceded by its length (vftable 0x10E8B52C)
	class BlowfishCipher : public Cipher
	{
	public:
		// 0x10940440
		explicit BlowfishCipher(const CipherKey& key);
		// 0x10940490 / 0x109405B0
		virtual ~BlowfishCipher();
		// 0x109404B0 / 0x10940550
		virtual void Encrypt(const void* in, int size, void* out, int* outSize);
		virtual void Decrypt(const void* in, int size, void* out, int* outSize);

		BlowfishState mState;      // 0x18
	};

	// 0x1093FD30: a new cipher of the kind (0 block TEA, 1 Blowfish), null for another kind
	Cipher* CreateCipher(int kind, const CipherKey& key);
}

#endif
