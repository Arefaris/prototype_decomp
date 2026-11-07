// The smoother node of the mgraph library (RTTI: mgraph::Smoother): follows its input with a rate of rise and a rate of fall.
#ifndef MGRAPH_SMOOTHER_H
#define MGRAPH_SMOOTHER_H

#include "code/mgraph/throw.h"

namespace mgraph
{
	// Makes the description of the node class and enters it in the registry (called when the library starts)
	void RegisterSmoother();

	class __declspec(align(8)) Smoother : public Node
	{
	public:
		Smoother(Graph* newGraph, const om::ClassName& newName);
		virtual ~Smoother();
		virtual void SetNumChannels(unsigned int newCount);
		virtual void Slot16(EvaluationFrame* frame);
		static void* operator new(size_t);
		static void operator delete(void* memory);
		static const char* AllocationTag();

		// The properties "RiseRate" and "FallRate" (not reconstructed)
		void SetRiseRate(float newRate);
		float GetRiseRate() const;
		void SetFallRate(float newRate);
		float GetFallRate() const;

		// What the node keeps for each channel (names guessed; 8 bytes)
		struct Channel
		{
			Channel();
			float unknown0;
			float unknown4;
		};
		om::DynamicArray<Channel, unsigned short> channels;  // 0x50
	};
}

namespace om
{
	// The loops that fill and copy the elements are the engine's
	template<> void DynamicArray<mgraph::Smoother::Channel, unsigned short>::FillElements(mgraph::Smoother::Channel* destination, unsigned short count, const mgraph::Smoother::Channel& value);
	template<> void DynamicArray<mgraph::Smoother::Channel, unsigned short>::CopyElements(mgraph::Smoother::Channel* destination, const mgraph::Smoother::Channel* source, unsigned short count);
}


#endif
