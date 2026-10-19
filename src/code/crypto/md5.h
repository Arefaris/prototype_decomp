// crypto::MD5: the MD5 message digest as a class that is fed bytes and then finalized (the engine's copy of a public
// implementation that keeps the digest, a copy of it and its hexadecimal text in the object). Member names are guesses.
#ifndef CRYPTO_MD5_H
#define CRYPTO_MD5_H

#include <stdio.h>

namespace crypto
{
	class MD5
	{
	public:
		// 0x109448D0 / 0x10944AE0 / 0x10944B10: an empty digest, the digest of a text, the digest of a file (closed
		// afterwards)
		MD5();
		MD5(const char* text, int length);
		explicit MD5(FILE* file);
		// 0x109441A0: starts over
		void Init();
		// 0x109448E0 / 0x10944990: feeds bytes / the rest of a file (which is closed)
		void Update(const unsigned char* input, unsigned int length);
		void Update(FILE* file);
		// 0x10944A00: pads and closes the digest
		void Finalize();
		// 0x10943E60: whether both digests are final and equal
		int Equals(const MD5& other) const;
		// 0x10943F20: whether the digest is final
		bool IsFinal() const;
		// 0x10943F30 / 0x10943F50: the sixteen bytes and their hexadecimal text (empty until the digest is final)
		const unsigned char* GetDigest() const;
		const char* GetHexDigest() const;

		// 0x10943F70 / 0x10943FC0: the words as little endian bytes / the bytes as little endian words
		static void Encode(unsigned char* output, const unsigned int* input, unsigned int length);
		static void Decode(unsigned int* output, const unsigned char* input, unsigned int length);
		// 0x10944010 / 0x10944040: a byte copy and a fill that do nothing for no bytes
		static void Copy(unsigned char* to, const unsigned char* from, unsigned int length);
		static void Fill(void* to, int value, unsigned int length);
		// 0x10944060 - 0x10944170: the rotation, the four functions and the four steps of the rounds
		static unsigned int RotateLeft(unsigned int x, int n);
		static unsigned int F(unsigned int x, unsigned int y, unsigned int z);
		static unsigned int G(unsigned int x, unsigned int y, unsigned int z);
		static unsigned int H(unsigned int x, unsigned int y, unsigned int z);
		static unsigned int I(unsigned int x, unsigned int y, unsigned int z);
		static void FF(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s,
			unsigned int ac);
		static void GG(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s,
			unsigned int ac);
		static void HH(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s,
			unsigned int ac);
		static void II(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s,
			unsigned int ac);

		// 0x10944220: one block of 64 bytes
		void Transform(const unsigned char* block);

		unsigned int mState[4];            // 0x00
		unsigned int mCount[2];            // 0x10 bits, low word first
		unsigned char mBuffer[64];         // 0x18
		unsigned char mDigest[16];         // 0x58
		unsigned char mDigestCopy[17];     // 0x68
		char mHexDigest[33];               // 0x79
		char mFinalized;                   // 0x9A
	};

	// The second MD5 of the unit (functions on a context; the bytes counted so far, the four words of the state, the
	// block being filled and the two padded keys of the message authentication code)
	struct MD5Context
	{
		unsigned int bytes[2];     // 0x00
		unsigned int state[4];     // 0x08
		unsigned char in[64];      // 0x18
		unsigned char ipad[64];    // 0x58
		unsigned char opad[64];    // 0x98
	};

	// 0x10944B40 / 0x10945400 / 0x109454B0
	void MD5Init(MD5Context* context);
	void MD5Update(MD5Context* context, const unsigned char* data, int length);
	void MD5Final(MD5Context* context, unsigned char* digest);
	// 0x109455C0 / 0x10945610: the digest of bytes / of a file (0 done, 1 not opened, 2 not read)
	void MD5Digest(const unsigned char* data, int length, unsigned char* digest);
	int MD5File(const char* path, unsigned char* digest);
	// 0x109456E0 / 0x10945750 / 0x10945760: the three steps of the code
	void HmacInit(MD5Context* context, const unsigned char* key, int keyLength);
	void HmacUpdate(MD5Context* context, const unsigned char* data, int length);
	void HmacFinal(MD5Context* context, unsigned char* digest);
	// 0x109457B0: the code of data under a key (RFC 2104)
	void HmacMD5(const unsigned char* key, int keyLength, const unsigned char* data, int length, unsigned char* out);
}

#endif
