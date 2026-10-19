// The block TEA (XXTEA) of crypto::BlockTEACipher: the word version works on whole 32-bit words, the byte version on
// the 0 to 7 bytes that remain. The key is four elements of the same type for the words and sixteen bytes. Names are
// guesses.
#ifndef CRYPTO_TEA_H
#define CRYPTO_TEA_H

namespace crypto
{
	// The increment of the sum of the type (0x9E3779B9 for words, its low byte for bytes)
	template <class T> T GetDelta();
	template <> unsigned int GetDelta<unsigned int>();
	template <> unsigned char GetDelta<unsigned char>();

	// 0x1093FED0 / 0x1093FFF0: encrypts n elements of v in place
	template <class T> void TeaEncrypt(T* v, T n, const T* key);
	template <> void TeaEncrypt<unsigned int>(unsigned int* v, unsigned int n, const unsigned int* key);
	template <> void TeaEncrypt<unsigned char>(unsigned char* v, unsigned char n, const unsigned char* key);
	// 0x10940130 / 0x10940240: decrypts n elements of v in place
	template <class T> void TeaDecrypt(T* v, T n, const T* key);
	template <> void TeaDecrypt<unsigned int>(unsigned int* v, unsigned int n, const unsigned int* key);
	template <> void TeaDecrypt<unsigned char>(unsigned char* v, unsigned char n, const unsigned char* key);
}

#endif
