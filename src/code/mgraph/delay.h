// The delay node of the mgraph library (0x10B6E360 - 0x10B6F1A0): the reflection of the class and the description of its node type, in the order the compiler emitted them (a guess: one translation unit).
#ifndef MGRAPH_DELAY_H
#define MGRAPH_DELAY_H

#include "code/mgraph/castnodes.h"
#include "code/mgraph/throw.h"

namespace mgraph
{
	// Makes the description of the node class and enters it in the registry (called when the library starts)
	void RegisterDelay();

	class __declspec(align(8)) Delay : public Node
	{
	public:
		Delay(Graph* newGraph, const om::ClassName& newName);
		virtual ~Delay();
		virtual void SetNumChannels(unsigned int newCount);
		virtual void Slot16(EvaluationFrame* frame);
		static void* operator new(size_t);
		static void operator delete(void* memory);
		static const char* AllocationTag();

		// What the node keeps for each channel (name guessed; 16 bytes)
		struct Channel
		{
			Channel();
			// Takes the delay range of the inputs and, when a trigger arrives and none is on its way, picks the number of samples to hold it back
			void Update(Delay* node, EvaluationFrame* frame);

			float minimum;
			float maximum;
			unsigned int pending;  // 1 while a trigger is held back
			unsigned int remaining;  // the samples until it is let through
		};
		om::DynamicArray<Channel, unsigned short> channels;  // 0x50
	};


}

namespace om
{
	// The loops that fill and copy the elements are the engine's
	template<> void DynamicArray<mgraph::Delay::Channel, unsigned short>::FillElements(mgraph::Delay::Channel* destination, unsigned short count, const mgraph::Delay::Channel& value);
	template<> void DynamicArray<mgraph::Delay::Channel, unsigned short>::CopyElements(mgraph::Delay::Channel* destination, const mgraph::Delay::Channel* source, unsigned short count);
}


#endif
