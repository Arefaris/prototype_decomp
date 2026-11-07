// The select-int-from-trigger node of the mgraph library (RTTI: mgraph::SelectIntFromTrigger): puts out the number of the input
// whose trigger fired last.
#ifndef MGRAPH_SELECTINTTRIGGER_H
#define MGRAPH_SELECTINTTRIGGER_H

#include "code/mgraph/throw.h"

namespace mgraph
{
	// Makes the description of the node class and enters it in the registry (called when the library starts)
	void RegisterSelectIntFromTrigger();

	class __declspec(align(8)) SelectIntFromTrigger : public Node
	{
	public:
		SelectIntFromTrigger(Graph* newGraph, const om::ClassName& newName);
		static void* operator new(size_t);
		static void operator delete(void* memory);
		static const char* AllocationTag();

		// The property "NumInputs" (not reconstructed)
		void SetNumInputs(unsigned int newCount);
		unsigned int GetNumInputs() const;

		char unknown50[0x10];
	};
}

#endif
