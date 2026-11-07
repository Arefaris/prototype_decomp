// The filter node of the mgraph library (RTTI: mgraph::Filter): a biquad filter over the audio at its input.
#ifndef MGRAPH_FILTER_H
#define MGRAPH_FILTER_H

#include "code/dsp/biquadfiltertype.h"
#include "code/mgraph/throw.h"

namespace mgraph
{
	// Makes the description of the node class and enters it in the registry (called when the library starts)
	void RegisterFilter();

	class __declspec(align(8)) Filter : public Node
	{
	public:
		Filter(Graph* newGraph, const om::ClassName& newName);
		static void* operator new(size_t);
		static void operator delete(void* memory);
		static const char* AllocationTag();

		// The properties "Frequency", "Q" and "FilterType" (not reconstructed)
		void SetFrequency(float newFrequency);
		float GetFrequency() const;
		void SetQ(float newQ);
		float GetQ() const;
		void SetFilterType(dsp::BiQuadFilterType newType);
		dsp::BiQuadFilterType GetFilterType() const;

		char unknown50[0x10];
	};
}

#endif
