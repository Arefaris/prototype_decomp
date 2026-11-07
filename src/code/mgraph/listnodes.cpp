// The list nodes of the mgraph library (0x10B2AB00 - 0x10B52000): the template instances for the element types, in the order the
// compiler emitted them (a guess: one translation unit).
#include "code/mgraph/listnodes.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B2AB00
	template mgraph::ListCount<bool>::ListCount(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2ACA0
	template void mgraph::ListCount<bool>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2AFF0
	template mgraph::ListCount<unsigned int>::ListCount(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2B190
	template void mgraph::ListCount<unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2B210
	template mgraph::ListEntry<unsigned int>::ListEntry(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2B430
	template bool mgraph::PacketPresent<struct mgraph::FrameEntry<unsigned int> >(mgraph::FrameEntry<unsigned int> const*);
	// FUNCTION: ENGINE 0x10B2B440
	template bool mgraph::PacketPresent<struct mgraph::FrameEntry<class om::DynamicArray<unsigned int,unsigned short> > >(mgraph::FrameEntry<DynamicArray<unsigned int,unsigned short> > const*);
	// FUNCTION: ENGINE 0x10B2B460
	template void mgraph::ListEntry<unsigned int>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2B480
	template void mgraph::ListEntry<unsigned int>::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B2B690
	template mgraph::ListCount<unsigned __int64>::ListCount(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2B830
	template void mgraph::ListCount<unsigned __int64>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2B8B0
	template mgraph::ListEntry<unsigned __int64>::ListEntry(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2BAD0
	template bool mgraph::PacketPresent<struct mgraph::FrameEntry<class om::DynamicArray<unsigned __int64,unsigned short> > >(mgraph::FrameEntry<DynamicArray<unsigned __int64,unsigned short> > const*);
	// FUNCTION: ENGINE 0x10B2BAF0
	template void mgraph::ListEntry<unsigned __int64>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2BB10
	template void mgraph::ListEntry<unsigned __int64>::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B2BD70
	template mgraph::ListCount<String>::ListCount(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2BF10
	template void mgraph::ListCount<String>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2BF90
	template mgraph::ListEntry<String>::ListEntry(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2C1F0
	template bool mgraph::PacketPresent<struct mgraph::FrameEntry<class om::DynamicArray<class om::String,unsigned short> > >(mgraph::FrameEntry<DynamicArray<String,unsigned short> > const*);
	// FUNCTION: ENGINE 0x10B2C210
	template void mgraph::ListEntry<String>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2C230
	template void mgraph::ListEntry<String>::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B2C450
	template mgraph::ListCount<Vector>::ListCount(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2C5F0
	template void mgraph::ListCount<Vector>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2C6A0
	template mgraph::ListCount<mgraph::TriggerData>::ListCount(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2C840
	template void mgraph::ListCount<mgraph::TriggerData>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B2CC30
	template mgraph::ListCount<Complex>::ListCount(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B2CDD0
	template void mgraph::ListCount<Complex>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B41830
	template<> Node* NodeType<mgraph::ListCount<bool> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::ListCount<bool>(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B41940
	template<> Node* NodeType<mgraph::ListCount<float> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::ListCount<float>(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B41A50
	template<> Node* NodeType<mgraph::ListCount<unsigned int> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::ListCount<unsigned int>(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B41A80
	template<> Node* NodeType<mgraph::ListEntry<unsigned int> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::ListEntry<unsigned int>(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B41B90
	template<> Node* NodeType<mgraph::ListCount<unsigned __int64> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::ListCount<unsigned __int64>(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B41BC0
	template<> Node* NodeType<mgraph::ListEntry<unsigned __int64> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::ListEntry<unsigned __int64>(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B41CD0
	template<> Node* NodeType<mgraph::ListCount<String> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::ListCount<String>(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B41D00
	template<> Node* NodeType<mgraph::ListEntry<String> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::ListEntry<String>(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B41E10
	template<> Node* NodeType<mgraph::ListCount<Vector> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::ListCount<Vector>(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B41F20
	template<> Node* NodeType<mgraph::ListCount<mgraph::TriggerData> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::ListCount<mgraph::TriggerData>(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B42060
	template<> Node* NodeType<mgraph::ListCount<Complex> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::ListCount<Complex>(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B44B00
	template mgraph::ListEntry<bool>::ListEntry(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B44D30
	template bool mgraph::PacketPresent<struct mgraph::FrameEntry<class om::DynamicArray<bool,unsigned short> > >(mgraph::FrameEntry<DynamicArray<bool,unsigned short> > const*);
	// FUNCTION: ENGINE 0x10B44D50
	template void mgraph::ListEntry<bool>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B44D70
	template void mgraph::ListEntry<bool>::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B452A0
	template bool mgraph::PacketPresent<struct mgraph::FrameEntry<class om::DynamicArray<float,unsigned short> > >(mgraph::FrameEntry<DynamicArray<float,unsigned short> > const*);
	// FUNCTION: ENGINE 0x10B452E0
	template void mgraph::ListEntry<float>::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B51D60
	template<> Node* NodeType<mgraph::ListEntry<bool> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::ListEntry<bool>(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B51E80
	template<> Node* NodeType<mgraph::ListEntry<float> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::ListEntry<float>(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B63890
	template<> Node* NodeType<mgraph::ListCount<mgraph::EnvelopeData> >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::ListCount<mgraph::EnvelopeData>(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B2ACC0
	template void mgraph::ListCount<bool>::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B2B1B0
	template void mgraph::ListCount<unsigned int>::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B2B850
	template void mgraph::ListCount<unsigned __int64>::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B2BF30
	template void mgraph::ListCount<String>::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B2C610
	template void mgraph::ListCount<Vector>::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B2C860
	template void mgraph::ListCount<mgraph::TriggerData>::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B2CDF0
	template void mgraph::ListCount<Complex>::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B2AF60
	template void mgraph::ListCount<float>::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B2CB30
	template bool mgraph::PacketPresent<struct mgraph::FrameEntry<class om::DynamicArray<class mgraph::TriggerData,unsigned short> > >(mgraph::FrameEntry<DynamicArray<mgraph::TriggerData,unsigned short> > const*);
	// FUNCTION: ENGINE 0x10B2CB70
	template void mgraph::ListEntry<mgraph::TriggerData>::Slot16(mgraph::EvaluationFrame*);
}
