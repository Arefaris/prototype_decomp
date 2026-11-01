// The creation of the nodes of the other node classes (the first slot of their node types): a node of the class is made from the graph
// and the name (the constructors are the engine's).
#include "code/mgraph/nodes.h"

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B17C10
	template<> Node* NodeType<mgraph::Inlet<mgraph::Packet<bool> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Inlet<mgraph::Packet<bool> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B18200
	template<> Node* NodeType<mgraph::Outlet<mgraph::Packet<bool> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Outlet<mgraph::Packet<bool> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B18AA0
	template<> Node* NodeType<mgraph::Inlet<mgraph::Packet<om::DynamicArray<bool,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Inlet<mgraph::Packet<om::DynamicArray<bool,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B19070
	template<> Node* NodeType<mgraph::Outlet<mgraph::Packet<om::DynamicArray<bool,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Outlet<mgraph::Packet<om::DynamicArray<bool,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B19910
	template<> Node* NodeType<mgraph::Inlet<mgraph::Packet<float> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Inlet<mgraph::Packet<float> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B19EE0
	template<> Node* NodeType<mgraph::Outlet<mgraph::Packet<float> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Outlet<mgraph::Packet<float> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B1A780
	template<> Node* NodeType<mgraph::Inlet<mgraph::Packet<om::DynamicArray<float,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Inlet<mgraph::Packet<om::DynamicArray<float,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B1AD50
	template<> Node* NodeType<mgraph::Outlet<mgraph::Packet<om::DynamicArray<float,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Outlet<mgraph::Packet<om::DynamicArray<float,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B1B5F0
	template<> Node* NodeType<mgraph::Inlet<mgraph::Packet<unsigned int> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Inlet<mgraph::Packet<unsigned int> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B1BBC0
	template<> Node* NodeType<mgraph::Outlet<mgraph::Packet<unsigned int> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Outlet<mgraph::Packet<unsigned int> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B1C460
	template<> Node* NodeType<mgraph::Inlet<mgraph::Packet<om::DynamicArray<unsigned int,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Inlet<mgraph::Packet<om::DynamicArray<unsigned int,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B1CA30
	template<> Node* NodeType<mgraph::Outlet<mgraph::Packet<om::DynamicArray<unsigned int,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Outlet<mgraph::Packet<om::DynamicArray<unsigned int,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B1D2D0
	template<> Node* NodeType<mgraph::Inlet<mgraph::Packet<unsigned __int64> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Inlet<mgraph::Packet<unsigned __int64> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B1D8A0
	template<> Node* NodeType<mgraph::Outlet<mgraph::Packet<unsigned __int64> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Outlet<mgraph::Packet<unsigned __int64> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B1E140
	template<> Node* NodeType<mgraph::Inlet<mgraph::Packet<om::DynamicArray<unsigned __int64,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Inlet<mgraph::Packet<om::DynamicArray<unsigned __int64,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B1E710
	template<> Node* NodeType<mgraph::Outlet<mgraph::Packet<om::DynamicArray<unsigned __int64,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Outlet<mgraph::Packet<om::DynamicArray<unsigned __int64,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B1EFB0
	template<> Node* NodeType<mgraph::Inlet<mgraph::Packet<om::String> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Inlet<mgraph::Packet<om::String> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B1F580
	template<> Node* NodeType<mgraph::Outlet<mgraph::Packet<om::String> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Outlet<mgraph::Packet<om::String> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B1FE20
	template<> Node* NodeType<mgraph::Inlet<mgraph::Packet<om::DynamicArray<om::String,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Inlet<mgraph::Packet<om::DynamicArray<om::String,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B203F0
	template<> Node* NodeType<mgraph::Outlet<mgraph::Packet<om::DynamicArray<om::String,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Outlet<mgraph::Packet<om::DynamicArray<om::String,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B20CD0
	template<> Node* NodeType<mgraph::Inlet<mgraph::Packet<om::Vector> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Inlet<mgraph::Packet<om::Vector> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B212A0
	template<> Node* NodeType<mgraph::Outlet<mgraph::Packet<om::Vector> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Outlet<mgraph::Packet<om::Vector> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B21B40
	template<> Node* NodeType<mgraph::Inlet<mgraph::Packet<om::DynamicArray<om::Vector,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Inlet<mgraph::Packet<om::DynamicArray<om::Vector,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B22110
	template<> Node* NodeType<mgraph::Outlet<mgraph::Packet<om::DynamicArray<om::Vector,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Outlet<mgraph::Packet<om::DynamicArray<om::Vector,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B229D0
	template<> Node* NodeType<mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Inlet<mgraph::Packet<mgraph::TriggerData> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B22FA0
	template<> Node* NodeType<mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Outlet<mgraph::Packet<mgraph::TriggerData> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B23840
	template<> Node* NodeType<mgraph::Inlet<mgraph::Packet<om::DynamicArray<mgraph::TriggerData,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Inlet<mgraph::Packet<om::DynamicArray<mgraph::TriggerData,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B23E10
	template<> Node* NodeType<mgraph::Outlet<mgraph::Packet<om::DynamicArray<mgraph::TriggerData,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Outlet<mgraph::Packet<om::DynamicArray<mgraph::TriggerData,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B246B0
	template<> Node* NodeType<mgraph::Inlet<mgraph::Packet<om::Complex> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Inlet<mgraph::Packet<om::Complex> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B24C80
	template<> Node* NodeType<mgraph::Outlet<mgraph::Packet<om::Complex> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Outlet<mgraph::Packet<om::Complex> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B25520
	template<> Node* NodeType<mgraph::Inlet<mgraph::Packet<om::DynamicArray<om::Complex,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Inlet<mgraph::Packet<om::DynamicArray<om::Complex,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B25AF0
	template<> Node* NodeType<mgraph::Outlet<mgraph::Packet<om::DynamicArray<om::Complex,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Outlet<mgraph::Packet<om::DynamicArray<om::Complex,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B26390
	template<> Node* NodeType<mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Inlet<mgraph::Packet<mgraph::EnvelopeData> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B26960
	template<> Node* NodeType<mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Outlet<mgraph::Packet<mgraph::EnvelopeData> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B27240
	template<> Node* NodeType<mgraph::Inlet<mgraph::Packet<om::DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Inlet<mgraph::Packet<om::DynamicArray<mgraph::EnvelopeData,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B27810
	template<> Node* NodeType<mgraph::Outlet<mgraph::Packet<om::DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Outlet<mgraph::Packet<om::DynamicArray<mgraph::EnvelopeData,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B495B0
	template<> Node* NodeType<mgraph::Rand<om::Vector> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Rand<om::Vector>(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B49640
	template<> Node* NodeType<mgraph::CommutativeMath<mgraph::VectorAdd> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::CommutativeMath<mgraph::VectorAdd>(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B49800
	template<> Node* NodeType<mgraph::CommutativeMath<mgraph::TriggerAnd> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::CommutativeMath<mgraph::TriggerAnd>(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B49880
	template<> Node* NodeType<mgraph::CommutativeMath<mgraph::TriggerOr> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::CommutativeMath<mgraph::TriggerOr>(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B4D2F0
	template<> Node* NodeType<mgraph::Rand<float> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Rand<float>(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B4D370
	template<> Node* NodeType<mgraph::Rand<unsigned int> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Rand<unsigned int>(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B51FF0
	template<> Node* NodeType<mgraph::Switch<mgraph::Packet<unsigned int> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Switch<mgraph::Packet<unsigned int> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B52110
	template<> Node* NodeType<mgraph::Switch<mgraph::Packet<unsigned __int64> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Switch<mgraph::Packet<unsigned __int64> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B52230
	template<> Node* NodeType<mgraph::Switch<mgraph::Packet<om::String> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Switch<mgraph::Packet<om::String> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B52560
	template<> Node* NodeType<mgraph::Switch<mgraph::Packet<om::Complex> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Switch<mgraph::Packet<om::Complex> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B553A0
	template<> Node* NodeType<mgraph::CommutativeMath<mgraph::FloatAdd> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::CommutativeMath<mgraph::FloatAdd>(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B553D0
	template<> Node* NodeType<mgraph::CommutativeMath<mgraph::FloatMultiply> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::CommutativeMath<mgraph::FloatMultiply>(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B55400
	template<> Node* NodeType<mgraph::CommutativeMath<mgraph::BoolOr> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::CommutativeMath<mgraph::BoolOr>(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B55430
	template<> Node* NodeType<mgraph::CommutativeMath<mgraph::BoolAnd> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::CommutativeMath<mgraph::BoolAnd>(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B55460
	template<> Node* NodeType<mgraph::NonCommutativeMath<mgraph::FloatSub> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::NonCommutativeMath<mgraph::FloatSub>(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B55490
	template<> Node* NodeType<mgraph::Operator2<mgraph::GreaterThan<float> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Operator2<mgraph::GreaterThan<float> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B554C0
	template<> Node* NodeType<mgraph::Operator2<mgraph::GreaterThanOrEqual<float> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Operator2<mgraph::GreaterThanOrEqual<float> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B554F0
	template<> Node* NodeType<mgraph::Operator2<mgraph::LessThanOrEqual<float> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Operator2<mgraph::LessThanOrEqual<float> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B55520
	template<> Node* NodeType<mgraph::Operator2<mgraph::LessThan<float> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Operator2<mgraph::LessThan<float> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B55550
	template<> Node* NodeType<mgraph::Operator2<mgraph::Equal<float> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Operator2<mgraph::Equal<float> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B55580
	template<> Node* NodeType<mgraph::Operator2<mgraph::NotEqual<float> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Operator2<mgraph::NotEqual<float> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B555B0
	template<> Node* NodeType<mgraph::UnaryMath<mgraph::BoolNot> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::UnaryMath<mgraph::BoolNot>(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B637D0
	template<> Node* NodeType<mgraph::Switch<mgraph::Packet<bool> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Switch<mgraph::Packet<bool> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B63800
	template<> Node* NodeType<mgraph::Switch<mgraph::Packet<float> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Switch<mgraph::Packet<float> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B63830
	template<> Node* NodeType<mgraph::Switch<mgraph::Packet<om::Vector> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Switch<mgraph::Packet<om::Vector> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B63860
	template<> Node* NodeType<mgraph::Switch<mgraph::Packet<mgraph::TriggerData> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Switch<mgraph::Packet<mgraph::TriggerData> >(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B68D40
	template<> Node* NodeType<mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Switch<mgraph::Packet<mgraph::EnvelopeData> >(static_cast<Graph*>(graph), *nodeName);
	}

}
