// The min-max distance node of the mgraph library (0x10B73A00 - 0x10B748C0): the reflection of the class and the description of its node type, in the order the compiler emitted them (a guess: one translation unit).
#ifndef MGRAPH_MINMAXDISTANCE_H
#define MGRAPH_MINMAXDISTANCE_H

#include "code/mgraph/throw.h"

namespace mgraph
{
	// Makes the description of the node class and enters it in the registry (called when the library starts)
	void RegisterMinMaxDistance();

	class __declspec(align(8)) MinMaxDistance : public Node
	{
	public:
		MinMaxDistance(Graph* newGraph, const om::ClassName& newName);
		virtual void SetNumChannels(unsigned int newCount);
		virtual void Slot16(EvaluationFrame* frame);
		static void* operator new(size_t);
		static void operator delete(void* memory);
		static const char* AllocationTag();

		// What the node keeps for each channel (names guessed; 12 bytes)
		struct Channel
		{
			Channel();
			float unknown0;
			float unknown4;
			float unknown8;
		};
		om::DynamicArray<Channel, unsigned short> channels;  // 0x50
		char unknown58[8];
	};

}

namespace om
{
	// The loops that fill and copy the elements are the engine's
	template<> void DynamicArray<mgraph::MinMaxDistance::Channel, unsigned short>::FillElements(mgraph::MinMaxDistance::Channel* destination, unsigned short count, const mgraph::MinMaxDistance::Channel& value);
	template<> void DynamicArray<mgraph::MinMaxDistance::Channel, unsigned short>::CopyElements(mgraph::MinMaxDistance::Channel* destination, const mgraph::MinMaxDistance::Channel* source, unsigned short count);
}


#endif
