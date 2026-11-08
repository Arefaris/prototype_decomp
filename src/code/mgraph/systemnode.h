// The system node of the mgraph library (0x10B76E80 - 0x10B77640): the reflection of the class and the description of its node type, in the order the compiler emitted them (a guess: one translation unit).
#ifndef MGRAPH_SYSTEMNODE_H
#define MGRAPH_SYSTEMNODE_H

#include "code/mgraph/throw.h"

namespace mgraph
{
	// Makes the description of the node class and enters it in the registry (called when the library starts)
	void RegisterSystemNode();

	class __declspec(align(8)) SystemNode : public Node
	{
	public:
		SystemNode(Graph* newGraph, const om::ClassName& newName);
		virtual ~SystemNode();
		virtual void SetNumChannels(unsigned int newCount);
		virtual void Slot16(EvaluationFrame* frame);
		static void* operator new(size_t);
		static void operator delete(void* memory);
		static const char* AllocationTag();

		char unknown4[0x50 - sizeof(Node)];
	};

}

#endif
