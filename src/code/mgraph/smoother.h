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
		OM_ALLOCATION(Smoother);

		// The properties "RiseRate" and "FallRate" (not reconstructed)
		void SetRiseRate(float newRate);
		float GetRiseRate() const;
		void SetFallRate(float newRate);
		float GetFallRate() const;

		char unknown50[8];
	};
}

#endif
