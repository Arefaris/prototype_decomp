// crypto::MD5 (the unit of the hashes' and the message authentication codes' classes, 0x10943E60 - 0x10945800; names
// are guesses).
#include "code/crypto/md5.h"
#include <string.h>

namespace crypto
{
	// FUNCTION: ENGINE 0x10943E60
	// EQUIVALENT: the same comparison; the engine loads the byte of this digest before the byte of the other in the tail of
	// the inlined memcmp, ours the other way round (95.7 %)
	int MD5::Equals(const MD5& other) const
	{
		if (mFinalized && other.mFinalized)
		{
			if (memcmp(mDigest, other.mDigest, 16) == 0)
			{
				return 1;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10943F20
	bool MD5::IsFinal() const
	{
		return mFinalized != 0;
	}

	// FUNCTION: ENGINE 0x10943F30
	const unsigned char* MD5::GetDigest() const
	{
		const unsigned char* result = (const unsigned char*)"";
		if (mFinalized)
		{
			result = mDigestCopy;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10943F50
	const char* MD5::GetHexDigest() const
	{
		const char* result = "";
		if (mFinalized)
		{
			result = mHexDigest;
		}
		return result;
	}

	// FUNCTION: ENGINE 0x10943F70
	void MD5::Encode(unsigned char* output, const unsigned int* input, unsigned int length)
	{
		for (unsigned int i = 0, j = 0; j < length; i++, j += 4)
		{
			output[j] = input[i] & 0xFF;
			output[j + 1] = (input[i] >> 8) & 0xFF;
			output[j + 2] = (input[i] >> 16) & 0xFF;
			output[j + 3] = (input[i] >> 24) & 0xFF;
		}
	}

	// FUNCTION: ENGINE 0x10943FC0
	void MD5::Decode(unsigned int* output, const unsigned char* input, unsigned int length)
	{
		for (unsigned int i = 0, j = 0; j < length; i++, j += 4)
		{
			output[i] = ((unsigned int)input[j]) | (((unsigned int)input[j + 1]) << 8) |
				(((unsigned int)input[j + 2]) << 16) | (((unsigned int)input[j + 3]) << 24);
		}
	}

	// FUNCTION: ENGINE 0x10944010
	void MD5::Copy(unsigned char* to, const unsigned char* from, unsigned int length)
	{
		for (unsigned int i = 0; i < length; i++)
		{
			to[i] = from[i];
		}
	}

	// FUNCTION: ENGINE 0x10944040
	void MD5::Fill(void* to, int value, unsigned int length)
	{
		if (length > 0)
		{
			memset(to, value, length);
		}
	}

	// FUNCTION: ENGINE 0x10944060
	inline unsigned int MD5::RotateLeft(unsigned int x, int n)
	{
		return (x << n) | (x >> (32 - n));
	}

	// FUNCTION: ENGINE 0x10944070
	inline unsigned int MD5::F(unsigned int x, unsigned int y, unsigned int z)
	{
		return (x & y) | (~x & z);
	}

	// FUNCTION: ENGINE 0x10944090
	inline unsigned int MD5::G(unsigned int x, unsigned int y, unsigned int z)
	{
		return (x & z) | (y & ~z);
	}

	// FUNCTION: ENGINE 0x109440B0
	inline unsigned int MD5::H(unsigned int x, unsigned int y, unsigned int z)
	{
		return x ^ y ^ z;
	}

	// FUNCTION: ENGINE 0x109440C0
	inline unsigned int MD5::I(unsigned int x, unsigned int y, unsigned int z)
	{
		return y ^ (x | ~z);
	}

	// FUNCTION: ENGINE 0x109440D0
	inline void MD5::FF(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s,
		unsigned int ac)
	{
		a = RotateLeft(a + F(b, c, d) + x + ac, s) + b;
	}

	// FUNCTION: ENGINE 0x10944100
	inline void MD5::GG(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s,
		unsigned int ac)
	{
		a = RotateLeft(a + G(b, c, d) + x + ac, s) + b;
	}

	// FUNCTION: ENGINE 0x10944140
	inline void MD5::HH(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s,
		unsigned int ac)
	{
		a = RotateLeft(a + H(b, c, d) + x + ac, s) + b;
	}

	// FUNCTION: ENGINE 0x10944170
	inline void MD5::II(unsigned int& a, unsigned int b, unsigned int c, unsigned int d, unsigned int x, unsigned int s,
		unsigned int ac)
	{
		a = RotateLeft(a + I(b, c, d) + x + ac, s) + b;
	}

	// FUNCTION: ENGINE 0x109441A0
	void MD5::Init()
	{
		mFinalized = false;
		mCount[0] = 0;
		mCount[1] = 0;
		mState[0] = 0x67452301;
		mState[1] = 0xefcdab89;
		mState[2] = 0x98badcfe;
		mState[3] = 0x10325476;
		Fill(mDigestCopy, 0, 17);
		memset(mHexDigest, 0, sizeof(mHexDigest));
	}

	// FUNCTION: ENGINE 0x10944220
	void MD5::Transform(const unsigned char* block)
	{
		unsigned int a = mState[0], b = mState[1], c = mState[2], d = mState[3], x[16];
		Decode(x, block, 64);

		FF(a, b, c, d, x[0], 7, 0xd76aa478);
		FF(d, a, b, c, x[1], 12, 0xe8c7b756);
		FF(c, d, a, b, x[2], 17, 0x242070db);
		FF(b, c, d, a, x[3], 22, 0xc1bdceee);
		FF(a, b, c, d, x[4], 7, 0xf57c0faf);
		FF(d, a, b, c, x[5], 12, 0x4787c62a);
		FF(c, d, a, b, x[6], 17, 0xa8304613);
		FF(b, c, d, a, x[7], 22, 0xfd469501);
		FF(a, b, c, d, x[8], 7, 0x698098d8);
		FF(d, a, b, c, x[9], 12, 0x8b44f7af);
		FF(c, d, a, b, x[10], 17, 0xffff5bb1);
		FF(b, c, d, a, x[11], 22, 0x895cd7be);
		FF(a, b, c, d, x[12], 7, 0x6b901122);
		FF(d, a, b, c, x[13], 12, 0xfd987193);
		FF(c, d, a, b, x[14], 17, 0xa679438e);
		FF(b, c, d, a, x[15], 22, 0x49b40821);
		GG(a, b, c, d, x[1], 5, 0xf61e2562);
		GG(d, a, b, c, x[6], 9, 0xc040b340);
		GG(c, d, a, b, x[11], 14, 0x265e5a51);
		GG(b, c, d, a, x[0], 20, 0xe9b6c7aa);
		GG(a, b, c, d, x[5], 5, 0xd62f105d);
		GG(d, a, b, c, x[10], 9, 0x02441453);
		GG(c, d, a, b, x[15], 14, 0xd8a1e681);
		GG(b, c, d, a, x[4], 20, 0xe7d3fbc8);
		GG(a, b, c, d, x[9], 5, 0x21e1cde6);
		GG(d, a, b, c, x[14], 9, 0xc33707d6);
		GG(c, d, a, b, x[3], 14, 0xf4d50d87);
		GG(b, c, d, a, x[8], 20, 0x455a14ed);
		GG(a, b, c, d, x[13], 5, 0xa9e3e905);
		GG(d, a, b, c, x[2], 9, 0xfcefa3f8);
		GG(c, d, a, b, x[7], 14, 0x676f02d9);
		GG(b, c, d, a, x[12], 20, 0x8d2a4c8a);
		HH(a, b, c, d, x[5], 4, 0xfffa3942);
		HH(d, a, b, c, x[8], 11, 0x8771f681);
		HH(c, d, a, b, x[11], 16, 0x6d9d6122);
		HH(b, c, d, a, x[14], 23, 0xfde5380c);
		HH(a, b, c, d, x[1], 4, 0xa4beea44);
		HH(d, a, b, c, x[4], 11, 0x4bdecfa9);
		HH(c, d, a, b, x[7], 16, 0xf6bb4b60);
		HH(b, c, d, a, x[10], 23, 0xbebfbc70);
		HH(a, b, c, d, x[13], 4, 0x289b7ec6);
		HH(d, a, b, c, x[0], 11, 0xeaa127fa);
		HH(c, d, a, b, x[3], 16, 0xd4ef3085);
		HH(b, c, d, a, x[6], 23, 0x04881d05);
		HH(a, b, c, d, x[9], 4, 0xd9d4d039);
		HH(d, a, b, c, x[12], 11, 0xe6db99e5);
		HH(c, d, a, b, x[15], 16, 0x1fa27cf8);
		HH(b, c, d, a, x[2], 23, 0xc4ac5665);
		II(a, b, c, d, x[0], 6, 0xf4292244);
		II(d, a, b, c, x[7], 10, 0x432aff97);
		II(c, d, a, b, x[14], 15, 0xab9423a7);
		II(b, c, d, a, x[5], 21, 0xfc93a039);
		II(a, b, c, d, x[12], 6, 0x655b59c3);
		II(d, a, b, c, x[3], 10, 0x8f0ccc92);
		II(c, d, a, b, x[10], 15, 0xffeff47d);
		II(b, c, d, a, x[1], 21, 0x85845dd1);
		II(a, b, c, d, x[8], 6, 0x6fa87e4f);
		II(d, a, b, c, x[15], 10, 0xfe2ce6e0);
		II(c, d, a, b, x[6], 15, 0xa3014314);
		II(b, c, d, a, x[13], 21, 0x4e0811a1);
		II(a, b, c, d, x[4], 6, 0xf7537e82);
		II(d, a, b, c, x[11], 10, 0xbd3af235);
		II(c, d, a, b, x[2], 15, 0x2ad7d2bb);
		II(b, c, d, a, x[9], 21, 0xeb86d391);

		mState[0] += a;
		mState[1] += b;
		mState[2] += c;
		mState[3] += d;
	}

	// FUNCTION: ENGINE 0x109448D0
	MD5::MD5()
	{
		Init();
	}

	// FUNCTION: ENGINE 0x109448E0
	void MD5::Update(const unsigned char* input, unsigned int length)
	{
		if (!mFinalized)
		{
			unsigned int index = mCount[0] / 8 % 64;
			if ((mCount[0] += (length << 3)) < (length << 3))
			{
				mCount[1]++;
			}
			mCount[1] += (length >> 29);
			unsigned int firstPart = 64 - index;
			unsigned int i;
			if (length >= firstPart)
			{
				Copy(&mBuffer[index], input, firstPart);
				Transform(mBuffer);
				for (i = firstPart; i + 63 < length; i += 64)
				{
					Transform(&input[i]);
				}
				index = 0;
			}
			else
			{
				i = 0;
			}
			Copy(&mBuffer[index], &input[i], length - i);
		}
	}

	// FUNCTION: ENGINE 0x10944990
	void MD5::Update(FILE* file)
	{
		unsigned char buffer[1024];
		size_t read = fread(buffer, 1, 1024, file);
		while (read != 0)
		{
			Update(buffer, read);
			read = fread(buffer, 1, 1024, file);
		}
		fclose(file);
	}

	// FUNCTION: ENGINE 0x10944A00
	void MD5::Finalize()
	{
		static unsigned char padding[64] =
		{
			0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		};
		if (!mFinalized)
		{
			unsigned char bits[8];
			Encode(bits, mCount, 8);
			unsigned int index = mCount[0] / 8 % 64;
			unsigned int padLength = (index < 56) ? (56 - index) : (120 - index);
			Update(padding, padLength);
			Update(bits, 8);
			Encode(mDigest, mState, 16);
			Fill(mBuffer, 0, 1);
			Fill(mDigestCopy, 0, 17);
			char* hex = mHexDigest;
			memset(mHexDigest, 0, sizeof(mHexDigest));
			Copy(mDigestCopy, mDigest, 16);
			for (unsigned int i = 0; i < 16; i++)
			{
				sprintf_s(hex, 3, "%02x", mDigest[i]);
				hex += 2;
			}
			mFinalized = true;
		}
	}

	// FUNCTION: ENGINE 0x10944AE0
	MD5::MD5(const char* text, int length)
	{
		Init();
		if (text != 0)
		{
			Update((const unsigned char*)text, length);
		}
		Finalize();
	}

	// FUNCTION: ENGINE 0x10944B10
	MD5::MD5(FILE* file)
	{
		Init();
		Update(file);
		Finalize();
	}

	// The bytes that pad a digest (a one bit and zeros)
	static const unsigned char MD5_PADDING[64] =
	{
		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	// FUNCTION: ENGINE 0x10944B40
	void MD5Init(MD5Context* context)
	{
		context->bytes[0] = 0;
		context->bytes[1] = 0;
		context->state[0] = 0x67452301;
		context->state[1] = 0xefcdab89;
		context->state[2] = 0x98badcfe;
		context->state[3] = 0x10325476;
	}

	#define MD5_F1(x, y, z) (z ^ (x & (y ^ z)))
	#define MD5_F2(x, y, z) MD5_F1(z, x, y)
	#define MD5_F3(x, y, z) (x ^ y ^ z)
	#define MD5_F4(x, y, z) (y ^ (x | ~z))
	#define MD5_STEP(f, w, x, y, z, data, s) (w += f(x, y, z) + data, w = w << s | w >> (32 - s), w += x)
	#define F1 MD5_F1
	#define F2 MD5_F2
	#define F3 MD5_F3
	#define F4 MD5_F4

	// FUNCTION: ENGINE 0x10944B70
	static void MD5Transform(MD5Context* context, const unsigned char* block)
	{
		unsigned int in[16];
		in[0] = ((unsigned int)block[3] << 24) | ((unsigned int)block[2] << 16) | ((unsigned int)block[1] << 8) | (unsigned int)block[0];
		in[1] = ((unsigned int)block[7] << 24) | ((unsigned int)block[6] << 16) | ((unsigned int)block[5] << 8) | (unsigned int)block[4];
		in[2] = ((unsigned int)block[11] << 24) | ((unsigned int)block[10] << 16) | ((unsigned int)block[9] << 8) | (unsigned int)block[8];
		in[3] = ((unsigned int)block[15] << 24) | ((unsigned int)block[14] << 16) | ((unsigned int)block[13] << 8) | (unsigned int)block[12];
		in[4] = ((unsigned int)block[19] << 24) | ((unsigned int)block[18] << 16) | ((unsigned int)block[17] << 8) | (unsigned int)block[16];
		in[5] = ((unsigned int)block[23] << 24) | ((unsigned int)block[22] << 16) | ((unsigned int)block[21] << 8) | (unsigned int)block[20];
		in[6] = ((unsigned int)block[27] << 24) | ((unsigned int)block[26] << 16) | ((unsigned int)block[25] << 8) | (unsigned int)block[24];
		in[7] = ((unsigned int)block[31] << 24) | ((unsigned int)block[30] << 16) | ((unsigned int)block[29] << 8) | (unsigned int)block[28];
		in[8] = ((unsigned int)block[35] << 24) | ((unsigned int)block[34] << 16) | ((unsigned int)block[33] << 8) | (unsigned int)block[32];
		in[9] = ((unsigned int)block[39] << 24) | ((unsigned int)block[38] << 16) | ((unsigned int)block[37] << 8) | (unsigned int)block[36];
		in[10] = ((unsigned int)block[43] << 24) | ((unsigned int)block[42] << 16) | ((unsigned int)block[41] << 8) | (unsigned int)block[40];
		in[11] = ((unsigned int)block[47] << 24) | ((unsigned int)block[46] << 16) | ((unsigned int)block[45] << 8) | (unsigned int)block[44];
		in[12] = ((unsigned int)block[51] << 24) | ((unsigned int)block[50] << 16) | ((unsigned int)block[49] << 8) | (unsigned int)block[48];
		in[13] = ((unsigned int)block[55] << 24) | ((unsigned int)block[54] << 16) | ((unsigned int)block[53] << 8) | (unsigned int)block[52];
		in[14] = ((unsigned int)block[59] << 24) | ((unsigned int)block[58] << 16) | ((unsigned int)block[57] << 8) | (unsigned int)block[56];
		in[15] = ((unsigned int)block[63] << 24) | ((unsigned int)block[62] << 16) | ((unsigned int)block[61] << 8) | (unsigned int)block[60];
		unsigned int a = context->state[0];
		unsigned int b = context->state[1];
		unsigned int c = context->state[2];
		unsigned int d = context->state[3];

		MD5_STEP(F1, a, b, c, d, in[0] + 0xd76aa478, 7);
		MD5_STEP(F1, d, a, b, c, in[1] + 0xe8c7b756, 12);
		MD5_STEP(F1, c, d, a, b, in[2] + 0x242070db, 17);
		MD5_STEP(F1, b, c, d, a, in[3] + 0xc1bdceee, 22);
		MD5_STEP(F1, a, b, c, d, in[4] + 0xf57c0faf, 7);
		MD5_STEP(F1, d, a, b, c, in[5] + 0x4787c62a, 12);
		MD5_STEP(F1, c, d, a, b, in[6] + 0xa8304613, 17);
		MD5_STEP(F1, b, c, d, a, in[7] + 0xfd469501, 22);
		MD5_STEP(F1, a, b, c, d, in[8] + 0x698098d8, 7);
		MD5_STEP(F1, d, a, b, c, in[9] + 0x8b44f7af, 12);
		MD5_STEP(F1, c, d, a, b, in[10] + 0xffff5bb1, 17);
		MD5_STEP(F1, b, c, d, a, in[11] + 0x895cd7be, 22);
		MD5_STEP(F1, a, b, c, d, in[12] + 0x6b901122, 7);
		MD5_STEP(F1, d, a, b, c, in[13] + 0xfd987193, 12);
		MD5_STEP(F1, c, d, a, b, in[14] + 0xa679438e, 17);
		MD5_STEP(F1, b, c, d, a, in[15] + 0x49b40821, 22);
		MD5_STEP(F2, a, b, c, d, in[1] + 0xf61e2562, 5);
		MD5_STEP(F2, d, a, b, c, in[6] + 0xc040b340, 9);
		MD5_STEP(F2, c, d, a, b, in[11] + 0x265e5a51, 14);
		MD5_STEP(F2, b, c, d, a, in[0] + 0xe9b6c7aa, 20);
		MD5_STEP(F2, a, b, c, d, in[5] + 0xd62f105d, 5);
		MD5_STEP(F2, d, a, b, c, in[10] + 0x02441453, 9);
		MD5_STEP(F2, c, d, a, b, in[15] + 0xd8a1e681, 14);
		MD5_STEP(F2, b, c, d, a, in[4] + 0xe7d3fbc8, 20);
		MD5_STEP(F2, a, b, c, d, in[9] + 0x21e1cde6, 5);
		MD5_STEP(F2, d, a, b, c, in[14] + 0xc33707d6, 9);
		MD5_STEP(F2, c, d, a, b, in[3] + 0xf4d50d87, 14);
		MD5_STEP(F2, b, c, d, a, in[8] + 0x455a14ed, 20);
		MD5_STEP(F2, a, b, c, d, in[13] + 0xa9e3e905, 5);
		MD5_STEP(F2, d, a, b, c, in[2] + 0xfcefa3f8, 9);
		MD5_STEP(F2, c, d, a, b, in[7] + 0x676f02d9, 14);
		MD5_STEP(F2, b, c, d, a, in[12] + 0x8d2a4c8a, 20);
		MD5_STEP(F3, a, b, c, d, in[5] + 0xfffa3942, 4);
		MD5_STEP(F3, d, a, b, c, in[8] + 0x8771f681, 11);
		MD5_STEP(F3, c, d, a, b, in[11] + 0x6d9d6122, 16);
		MD5_STEP(F3, b, c, d, a, in[14] + 0xfde5380c, 23);
		MD5_STEP(F3, a, b, c, d, in[1] + 0xa4beea44, 4);
		MD5_STEP(F3, d, a, b, c, in[4] + 0x4bdecfa9, 11);
		MD5_STEP(F3, c, d, a, b, in[7] + 0xf6bb4b60, 16);
		MD5_STEP(F3, b, c, d, a, in[10] + 0xbebfbc70, 23);
		MD5_STEP(F3, a, b, c, d, in[13] + 0x289b7ec6, 4);
		MD5_STEP(F3, d, a, b, c, in[0] + 0xeaa127fa, 11);
		MD5_STEP(F3, c, d, a, b, in[3] + 0xd4ef3085, 16);
		MD5_STEP(F3, b, c, d, a, in[6] + 0x04881d05, 23);
		MD5_STEP(F3, a, b, c, d, in[9] + 0xd9d4d039, 4);
		MD5_STEP(F3, d, a, b, c, in[12] + 0xe6db99e5, 11);
		MD5_STEP(F3, c, d, a, b, in[15] + 0x1fa27cf8, 16);
		MD5_STEP(F3, b, c, d, a, in[2] + 0xc4ac5665, 23);
		MD5_STEP(F4, a, b, c, d, in[0] + 0xf4292244, 6);
		MD5_STEP(F4, d, a, b, c, in[7] + 0x432aff97, 10);
		MD5_STEP(F4, c, d, a, b, in[14] + 0xab9423a7, 15);
		MD5_STEP(F4, b, c, d, a, in[5] + 0xfc93a039, 21);
		MD5_STEP(F4, a, b, c, d, in[12] + 0x655b59c3, 6);
		MD5_STEP(F4, d, a, b, c, in[3] + 0x8f0ccc92, 10);
		MD5_STEP(F4, c, d, a, b, in[10] + 0xffeff47d, 15);
		MD5_STEP(F4, b, c, d, a, in[1] + 0x85845dd1, 21);
		MD5_STEP(F4, a, b, c, d, in[8] + 0x6fa87e4f, 6);
		MD5_STEP(F4, d, a, b, c, in[15] + 0xfe2ce6e0, 10);
		MD5_STEP(F4, c, d, a, b, in[6] + 0xa3014314, 15);
		MD5_STEP(F4, b, c, d, a, in[13] + 0x4e0811a1, 21);
		MD5_STEP(F4, a, b, c, d, in[4] + 0xf7537e82, 6);
		MD5_STEP(F4, d, a, b, c, in[11] + 0xbd3af235, 10);
		MD5_STEP(F4, c, d, a, b, in[2] + 0x2ad7d2bb, 15);
		MD5_STEP(F4, b, c, d, a, in[9] + 0xeb86d391, 21);

		context->state[0] += a;
		context->state[1] += b;
		context->state[2] += c;
		context->state[3] += d;
	}

	// FUNCTION: ENGINE 0x10945400
	void MD5Update(MD5Context* context, const unsigned char* data, int length)
	{
		if (length > 0)
		{
			unsigned int count = context->bytes[0];
			int used = count & 0x3F;
			int room = 0x40 - used;
			context->bytes[0] = count + length;
			if (context->bytes[0] < (unsigned int)length)
			{
				context->bytes[1]++;
			}
			if (used != 0 && length >= room)
			{
				memcpy(context->in + used, data, room);
				MD5Transform(context, context->in);
				length -= room;
				data += room;
				used = 0;
			}
			while (length >= 64)
			{
				MD5Transform(context, data);
				data += 64;
				length -= 64;
			}
			if (length > 0)
			{
				memcpy(context->in + used, data, length);
			}
		}
	}

	// FUNCTION: ENGINE 0x109454B0
	void MD5Final(MD5Context* context, unsigned char* digest)
	{
		unsigned char length[8];
		unsigned int high = (context->bytes[1] << 3) | (context->bytes[0] >> 29);
		unsigned int low = context->bytes[0] << 3;
		length[0] = (unsigned char)low;
		length[1] = (unsigned char)(low >> 8);
		length[2] = (unsigned char)(low >> 16);
		length[3] = (unsigned char)(low >> 24);
		length[4] = (unsigned char)high;
		length[5] = (unsigned char)(high >> 8);
		length[6] = (unsigned char)(high >> 16);
		length[7] = (unsigned char)(high >> 24);
		unsigned int used = context->bytes[0] & 0x3F;
		int padLength;
		if (used < 56)
		{
			padLength = 56 - used;
		}
		else
		{
			padLength = 120 - used;
		}
		MD5Update(context, MD5_PADDING, padLength);
		MD5Update(context, length, 8);
		digest[0] = (unsigned char)(context->state[0]);
		digest[1] = (unsigned char)(context->state[0] >> 8);
		digest[2] = (unsigned char)(context->state[0] >> 16);
		digest[3] = (unsigned char)(context->state[0] >> 24);
		digest[4] = (unsigned char)(context->state[1]);
		digest[5] = (unsigned char)(context->state[1] >> 8);
		digest[6] = (unsigned char)(context->state[1] >> 16);
		digest[7] = (unsigned char)(context->state[1] >> 24);
		digest[8] = (unsigned char)(context->state[2]);
		digest[9] = (unsigned char)(context->state[2] >> 8);
		digest[10] = (unsigned char)(context->state[2] >> 16);
		digest[11] = (unsigned char)(context->state[2] >> 24);
		digest[12] = (unsigned char)(context->state[3]);
		digest[13] = (unsigned char)(context->state[3] >> 8);
		digest[14] = (unsigned char)(context->state[3] >> 16);
		digest[15] = (unsigned char)(context->state[3] >> 24);
	}

	// FUNCTION: ENGINE 0x109455C0
	void MD5Digest(const unsigned char* data, int length, unsigned char* digest)
	{
		MD5Context context;
		MD5Init(&context);
		MD5Update(&context, data, length);
		MD5Final(&context, digest);
	}

	// FUNCTION: ENGINE 0x10945610
	int MD5File(const char* path, unsigned char* digest)
	{
		FILE* file = fopen(path, "rb");
		if (file == 0)
		{
			return 1;
		}
		MD5Context context;
		unsigned char buffer[1024];
		MD5Init(&context);
		size_t read;
		while ((read = fread(buffer, 1, 1024, file)) > 0)
		{
			MD5Update(&context, buffer, read);
		}
		MD5Final(&context, digest);
		if (ferror(file))
		{
			fclose(file);
			return 2;
		}
		fclose(file);
		return 0;
	}

	// FUNCTION: ENGINE 0x109456E0
	void HmacInit(MD5Context* context, const unsigned char* key, int keyLength)
	{
		memset(context->ipad, 0x36, 64);
		memset(context->opad, 0x5C, 64);
		for (int i = 0; i < keyLength && i < 64; i++)
		{
			context->ipad[i] ^= key[i];
			context->opad[i] ^= key[i];
		}
		MD5Init(context);
		MD5Update(context, context->ipad, 64);
	}

	// FUNCTION: ENGINE 0x10945750
	void HmacUpdate(MD5Context* context, const unsigned char* data, int length)
	{
		MD5Update(context, data, length);
	}

	// FUNCTION: ENGINE 0x10945760
	void HmacFinal(MD5Context* context, unsigned char* digest)
	{
		unsigned char inner[16];
		MD5Final(context, inner);
		MD5Init(context);
		MD5Update(context, context->opad, 64);
		MD5Update(context, inner, 16);
		MD5Final(context, digest);
	}

	// FUNCTION: ENGINE 0x109457B0
	void HmacMD5(const unsigned char* key, int keyLength, const unsigned char* data, int length, unsigned char* out)
	{
		MD5Context context;
		HmacInit(&context, key, keyLength);
		HmacUpdate(&context, data, length);
		HmacFinal(&context, out);
	}
}
