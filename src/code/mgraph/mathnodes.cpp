// The math nodes of the mgraph library (0x10B2F1D0 - 0x10B30A90): the constructors of the trigger and vector operations, which
// have one input and one output pin.
#include "code/mgraph/throw.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B2F1D0
	template<> CommutativeMath<VectorAdd>::CommutativeMath(Graph* newGraph, const om::ClassName& newName) :
		Node(CachedNodeType<CommutativeMath>(), newGraph, newName, 1, 1)
	{
		new OutputPin<Packet<Vector> >(this, &MGRAPH_NAME("o"), 0, Packet<Vector>());
		new InputPin<Packet<Vector> >(this, &MGRAPH_NAME("i"), 1, 0, Packet<Vector>());
	}
	// FUNCTION: ENGINE 0x10B2F7F0
	// NONMATCHING: 96.8 %, the packet of the input pin stores its trigger behind the argument push, the engine's before it
#ifdef NONMATCHING
	template<> CommutativeMath<TriggerAnd>::CommutativeMath(Graph* newGraph, const om::ClassName& newName) :
		Node(CachedNodeType<CommutativeMath>(), newGraph, newName, 1, 1)
	{
		new OutputPin<Packet<TriggerData> >(this, &MGRAPH_NAME("o"), 0, Packet<TriggerData>());
		new InputPin<Packet<TriggerData> >(this, &MGRAPH_NAME("i"), 1, 0, Packet<TriggerData>());
	}
#endif
	// FUNCTION: ENGINE 0x10B2FB40
	// NONMATCHING: 96.8 %, the packet of the input pin stores its trigger behind the argument push, the engine's before it
#ifdef NONMATCHING
	template<> CommutativeMath<TriggerOr>::CommutativeMath(Graph* newGraph, const om::ClassName& newName) :
		Node(CachedNodeType<CommutativeMath>(), newGraph, newName, 1, 1)
	{
		new OutputPin<Packet<TriggerData> >(this, &MGRAPH_NAME("o"), 0, Packet<TriggerData>());
		new InputPin<Packet<TriggerData> >(this, &MGRAPH_NAME("i"), 1, 0, Packet<TriggerData>());
	}
#endif
}
