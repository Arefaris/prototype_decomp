// The meter node of the mgraph library (0x10B730D0 - 0x10B73A00): the reflection of the class and the description of its node type, in the order the compiler emitted them (a guess: one translation unit).
#ifndef MGRAPH_METER_H
#define MGRAPH_METER_H

#include "code/mgraph/throw.h"

namespace mgraph
{
	// Makes the description of the node class and enters it in the registry (called when the library starts)
	void RegisterMeter();

	// Whether an entry of a float packet is there (0x10B4AE90, name guessed; the engine keeps one copy for each of its users' packets)
	bool IsPresent(const FrameEntry<float>* entry);

	class __declspec(align(8)) Meter : public Node
	{
	public:
		Meter(Graph* newGraph, const om::ClassName& newName);
		virtual void Slot16(EvaluationFrame* frame);
		static void* operator new(size_t);
		static void operator delete(void* memory);
		static const char* AllocationTag();
	};

}

#endif
