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
		OM_ALLOCATION(SelectIntFromTrigger);

		// The property "NumInputs" (not reconstructed)
		void SetNumInputs(unsigned int newCount);
		unsigned int GetNumInputs() const;

		char unknown50[0x10];
	};
}

#endif
