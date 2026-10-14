// The byte-radix sort of an index array (code/container/sort.cpp).
#ifndef CONTAINER_SORT_H
#define CONTAINER_SORT_H

namespace container
{
	// 0x10610E40: sorts count indices into ascending order of the key bytes of data (records of stride bytes); see
	// sort.cpp for the key description
	unsigned short* RadixSort(unsigned char* data, unsigned short count, unsigned short* indices, unsigned short* out,
		unsigned int keyDesc, unsigned short stride, bool initIndices);
}

#endif
