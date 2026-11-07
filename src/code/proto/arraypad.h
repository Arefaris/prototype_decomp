// The word behind an array member that the engine's element structs keep (the allocator object of the array): a
// copy of the element does not copy it.
#ifndef PROTO_ARRAYPAD_H
#define PROTO_ARRAYPAD_H

namespace proto
{
	struct ElementArrayPad
	{
		ElementArrayPad()
		{
		}
		ElementArrayPad(const ElementArrayPad& other)
		{
		}
		ElementArrayPad& operator=(const ElementArrayPad& other)
		{
			return *this;
		}

		int unused;
	};
}

#endif
