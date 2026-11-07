// The throw and catch nodes of the mgraph library (0x10AE7E10 - 0x10B5C000): the template instances for the packet types, in the
// order the compiler emitted them (a guess: one translation unit).
#include "code/mgraph/throw.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10AE7E10
	template void mgraph::Throw<mgraph::Packet<bool> >::SetEventName(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE7E80
	template void mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >::SetEventName(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE8010
	template void mgraph::Throw<mgraph::Packet<float> >::SetEventName(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE8080
	template void mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >::SetEventName(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE80F0
	template void mgraph::Throw<mgraph::Packet<unsigned int> >::SetEventName(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE8160
	template void mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::SetEventName(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE81D0
	template void mgraph::Throw<mgraph::Packet<unsigned __int64> >::SetEventName(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE8240
	template void mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::SetEventName(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE83D0
	template void mgraph::Throw<mgraph::Packet<String> >::SetEventName(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE8440
	template void mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >::SetEventName(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE84B0
	template void mgraph::Throw<mgraph::Packet<Vector> >::SetEventName(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE8520
	template void mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::SetEventName(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE86B0
	template void mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >::SetEventName(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE8720
	template void mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::SetEventName(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE88B0
	template void mgraph::Throw<mgraph::Packet<Complex> >::SetEventName(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE8920
	template void mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::SetEventName(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE8AB0
	template void mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >::SetEventName(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10AE8B20
	template void mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::SetEventName(Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B06F40
	template char const* mgraph::Catch<mgraph::Packet<unsigned __int64> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B06FD0
	template void* mgraph::Catch<mgraph::Packet<unsigned __int64> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B09590
	template mgraph::Catch<mgraph::Packet<mgraph::TriggerData> >::Catch(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B09680
	template void mgraph::Catch<mgraph::Packet<mgraph::TriggerData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B096C0
	template mgraph::Catch<mgraph::Packet<mgraph::TriggerData> >::~Catch();
	// FUNCTION: ENGINE 0x10B09770
	template void mgraph::Catch<mgraph::Packet<mgraph::TriggerData> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B0A220
	template char const* mgraph::Catch<mgraph::Packet<Complex> >::AllocationTag();
	// FUNCTION: ENGINE 0x10B0A2A0
	template void* mgraph::Catch<mgraph::Packet<Complex> >::operator new(size_t);
	// FUNCTION: ENGINE 0x10B328E0
	template<> Node* NodeType<mgraph::Catch<mgraph::Packet<mgraph::TriggerData> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Catch<mgraph::Packet<mgraph::TriggerData> >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B32DC0
	template mgraph::Throw<mgraph::Packet<bool> >::Throw(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B32F30
	template void mgraph::Throw<mgraph::Packet<bool> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B32FB0
	template bool mgraph::Throw<mgraph::Packet<bool> >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B32FE0
	template void mgraph::Throw<mgraph::Packet<bool> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B33040
	template mgraph::Throw<mgraph::Packet<bool> >::~Throw();
	// FUNCTION: ENGINE 0x10B330D0
	template mgraph::Catch<mgraph::Packet<bool> >::Catch(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B331C0
	template void mgraph::Catch<mgraph::Packet<bool> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B331E0
	template mgraph::Catch<mgraph::Packet<bool> >::~Catch();
	// FUNCTION: ENGINE 0x10B33290
	template void mgraph::Catch<mgraph::Packet<bool> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B333D0
	template void mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B33410
	template mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > >::~Catch();
	// FUNCTION: ENGINE 0x10B334D0
	template void mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B33670
	template void mgraph::Throw<mgraph::Packet<float> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B336F0
	template bool mgraph::Throw<mgraph::Packet<float> >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B33720
	template void mgraph::Throw<mgraph::Packet<float> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B33780
	template mgraph::Throw<mgraph::Packet<float> >::~Throw();
	// FUNCTION: ENGINE 0x10B33810
	template mgraph::Catch<mgraph::Packet<float> >::Catch(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B33920
	template mgraph::Catch<mgraph::Packet<float> >::~Catch();
	// FUNCTION: ENGINE 0x10B339D0
	template void mgraph::Catch<mgraph::Packet<float> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B33B10
	template void mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B33B50
	template mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > >::~Catch();
	// FUNCTION: ENGINE 0x10B33C10
	template void mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B33C40
	template mgraph::Throw<mgraph::Packet<unsigned int> >::Throw(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B33D90
	template void mgraph::Throw<mgraph::Packet<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B33E30
	template bool mgraph::Throw<mgraph::Packet<unsigned int> >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B33E90
	template void mgraph::Throw<mgraph::Packet<unsigned int> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B33F60
	template mgraph::Throw<mgraph::Packet<unsigned int> >::~Throw();
	// FUNCTION: ENGINE 0x10B33FF0
	template mgraph::Catch<mgraph::Packet<unsigned int> >::Catch(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B340E0
	template void mgraph::Catch<mgraph::Packet<unsigned int> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B34100
	template mgraph::Catch<mgraph::Packet<unsigned int> >::~Catch();
	// FUNCTION: ENGINE 0x10B341B0
	template void mgraph::Catch<mgraph::Packet<unsigned int> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B342F0
	template void mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B34330
	template mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::~Catch();
	// FUNCTION: ENGINE 0x10B343F0
	template void mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B34420
	template mgraph::Throw<mgraph::Packet<unsigned __int64> >::Throw(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B34570
	template void mgraph::Throw<mgraph::Packet<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B34620
	template bool mgraph::Throw<mgraph::Packet<unsigned __int64> >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B34730
	template mgraph::Throw<mgraph::Packet<unsigned __int64> >::~Throw();
	// FUNCTION: ENGINE 0x10B347A0
	template void mgraph::Throw<mgraph::Packet<unsigned __int64> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B34800
	template mgraph::Catch<mgraph::Packet<unsigned __int64> >::Catch(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B348F0
	template void mgraph::Catch<mgraph::Packet<unsigned __int64> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B34910
	template mgraph::Catch<mgraph::Packet<unsigned __int64> >::~Catch();
	// FUNCTION: ENGINE 0x10B349D0
	template void mgraph::Catch<mgraph::Packet<unsigned __int64> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B34B10
	template void mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B34B50
	template mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::~Catch();
	// FUNCTION: ENGINE 0x10B34C10
	template void mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B34C40
	template mgraph::Throw<mgraph::Packet<String> >::Throw(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B34D70
	template void mgraph::Throw<mgraph::Packet<String> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B34E00
	template bool mgraph::Throw<mgraph::Packet<String> >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B34FA0
	template void mgraph::Throw<mgraph::Packet<String> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B35000
	template mgraph::Catch<mgraph::Packet<String> >::Catch(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B35110
	template void mgraph::Catch<mgraph::Packet<String> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B35130
	template mgraph::Catch<mgraph::Packet<String> >::~Catch();
	// FUNCTION: ENGINE 0x10B351F0
	template void mgraph::Catch<mgraph::Packet<String> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B35220
	template mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > >::Catch(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B35330
	template void mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B35370
	template mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > >::~Catch();
	// FUNCTION: ENGINE 0x10B35430
	template void mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B35460
	template mgraph::Throw<mgraph::Packet<Vector> >::Throw(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B35600
	template void mgraph::Throw<mgraph::Packet<Vector> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B35690
	template bool mgraph::Throw<mgraph::Packet<Vector> >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B356C0
	template void mgraph::Throw<mgraph::Packet<Vector> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B35730
	template mgraph::Throw<mgraph::Packet<Vector> >::~Throw();
	// FUNCTION: ENGINE 0x10B357D0
	template mgraph::Catch<mgraph::Packet<Vector> >::Catch(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B358D0
	template void mgraph::Catch<mgraph::Packet<Vector> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B358F0
	template mgraph::Catch<mgraph::Packet<Vector> >::~Catch();
	// FUNCTION: ENGINE 0x10B359B0
	template void mgraph::Catch<mgraph::Packet<Vector> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B35B30
	template mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::~Catch();
	// FUNCTION: ENGINE 0x10B35BF0
	template void mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B35D90
	template void mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B35DF0
	template bool mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B35E20
	template void mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B35E80
	template mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >::~Throw();
	// FUNCTION: ENGINE 0x10B36020
	template void mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B36060
	template mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::~Catch();
	// FUNCTION: ENGINE 0x10B36120
	template void mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B36150
	template mgraph::Throw<mgraph::Packet<Complex> >::Throw(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B362B0
	template void mgraph::Throw<mgraph::Packet<Complex> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B36330
	template bool mgraph::Throw<mgraph::Packet<Complex> >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B36490
	template mgraph::Throw<mgraph::Packet<Complex> >::~Throw();
	// FUNCTION: ENGINE 0x10B364F0
	template void mgraph::Throw<mgraph::Packet<Complex> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B36550
	template mgraph::Catch<mgraph::Packet<Complex> >::Catch(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B36650
	template void mgraph::Catch<mgraph::Packet<Complex> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B36670
	template mgraph::Catch<mgraph::Packet<Complex> >::~Catch();
	// FUNCTION: ENGINE 0x10B36730
	template void mgraph::Catch<mgraph::Packet<Complex> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B36870
	template void mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B368B0
	template mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::~Catch();
	// FUNCTION: ENGINE 0x10B36970
	template void mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B4CEF0
	template void mgraph::Throw<mgraph::Packet<unsigned int> >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B4CF80
	template void mgraph::Throw<mgraph::Packet<unsigned __int64> >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B4D020
	template void mgraph::Throw<mgraph::Packet<String> >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B4D210
	template void mgraph::Throw<mgraph::Packet<Complex> >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B4D430
	template<> Node* NodeType<mgraph::Throw<mgraph::Packet<bool> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Throw<mgraph::Packet<bool> >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4D4B0
	template<> Node* NodeType<mgraph::Catch<mgraph::Packet<bool> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Catch<mgraph::Packet<bool> >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4D580
	template<> Node* NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Catch<mgraph::Packet<DynamicArray<bool,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4D600
	template<> Node* NodeType<mgraph::Throw<mgraph::Packet<float> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Throw<mgraph::Packet<float> >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4D680
	template<> Node* NodeType<mgraph::Catch<mgraph::Packet<float> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Catch<mgraph::Packet<float> >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4D750
	template<> Node* NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Catch<mgraph::Packet<DynamicArray<float,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4D7D0
	template<> Node* NodeType<mgraph::Throw<mgraph::Packet<unsigned int> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Throw<mgraph::Packet<unsigned int> >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4D850
	template<> Node* NodeType<mgraph::Catch<mgraph::Packet<unsigned int> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Catch<mgraph::Packet<unsigned int> >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4D920
	template<> Node* NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Catch<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4D9A0
	template<> Node* NodeType<mgraph::Throw<mgraph::Packet<unsigned __int64> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Throw<mgraph::Packet<unsigned __int64> >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4DA20
	template<> Node* NodeType<mgraph::Catch<mgraph::Packet<unsigned __int64> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Catch<mgraph::Packet<unsigned __int64> >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4DAF0
	template<> Node* NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Catch<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4DB70
	template<> Node* NodeType<mgraph::Throw<mgraph::Packet<String> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Throw<mgraph::Packet<String> >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4DBF0
	template<> Node* NodeType<mgraph::Catch<mgraph::Packet<String> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Catch<mgraph::Packet<String> >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4DCC0
	template<> Node* NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Catch<mgraph::Packet<DynamicArray<String,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4DD40
	template<> Node* NodeType<mgraph::Throw<mgraph::Packet<Vector> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Throw<mgraph::Packet<Vector> >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4DDC0
	template<> Node* NodeType<mgraph::Catch<mgraph::Packet<Vector> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Catch<mgraph::Packet<Vector> >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4DE90
	template<> Node* NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Catch<mgraph::Packet<DynamicArray<Vector,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4DF10
	template<> Node* NodeType<mgraph::Throw<mgraph::Packet<mgraph::TriggerData> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4E030
	template<> Node* NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4E0B0
	template<> Node* NodeType<mgraph::Throw<mgraph::Packet<Complex> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Throw<mgraph::Packet<Complex> >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4E130
	template<> Node* NodeType<mgraph::Catch<mgraph::Packet<Complex> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Catch<mgraph::Packet<Complex> >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4E200
	template<> Node* NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Catch<mgraph::Packet<DynamicArray<Complex,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B4E530
	template void mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B4E590
	template bool mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B4E6D0
	template void mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B56380
	template void mgraph::Throw<mgraph::Packet<bool> >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B56980
	template void mgraph::Throw<mgraph::Packet<float> >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B580D0
	template void mgraph::Throw<mgraph::Packet<Vector> >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B586E0
	template void mgraph::Throw<mgraph::Packet<mgraph::TriggerData> >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B596C0
	template<> Node* NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Throw<mgraph::Packet<DynamicArray<float,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B596F0
	template mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Throw(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B59820
	template void mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B59880
	template bool mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B599C0
	template void mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B59BC0
	template mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Throw(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B59CF0
	template void mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B59D50
	template bool mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B59E90
	template void mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B5A090
	template mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Throw(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B5A1C0
	template void mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B5A220
	template bool mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B5A360
	template void mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B5A560
	template mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >::Throw(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B5A690
	template void mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B5A6F0
	template bool mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B5A830
	template void mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B5A9A0
	template void mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >::SetNumChannels(unsigned int);
	// FUNCTION: ENGINE 0x10B5AA30
	template mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Throw(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B5AB60
	template void mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B5ABC0
	template bool mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B5AD00
	template void mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B5AF00
	template mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Throw(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B5B030
	template void mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B5B090
	template bool mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B5B1D0
	template void mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B5B3D0
	template mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Throw(mgraph::Graph*, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B5B500
	template void mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B5B560
	template bool mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B5B6A0
	template void mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B5B9D0
	template void mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B5BA80
	template bool mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B5BAF0
	template void mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B5BDC0
	template void mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B5BDE0
	template mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> >::~Catch();
	// FUNCTION: ENGINE 0x10B5BEA0
	template void mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B5C000
	template void mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B5C040
	template mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::~Catch();
	// FUNCTION: ENGINE 0x10B5C100
	template void mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B68B00
	template<> Node* NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Throw<mgraph::Packet<DynamicArray<bool,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B68B30
	template<> Node* NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Throw<mgraph::Packet<DynamicArray<unsigned int,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B68B60
	template<> Node* NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Throw<mgraph::Packet<DynamicArray<unsigned __int64,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B68B90
	template<> Node* NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Throw<mgraph::Packet<DynamicArray<String,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B68BC0
	template<> Node* NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Throw<mgraph::Packet<DynamicArray<Vector,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B68BF0
	template<> Node* NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::TriggerData,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B68C20
	template<> Node* NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Throw<mgraph::Packet<DynamicArray<Complex,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B68C50
	template<> Node* NodeType<mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Throw<mgraph::Packet<mgraph::EnvelopeData> >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B68C80
	template<> Node* NodeType<mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Catch<mgraph::Packet<mgraph::EnvelopeData> >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B68CB0
	template<> Node* NodeType<mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Catch<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}
	// FUNCTION: ENGINE 0x10B69510
	template void mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::operator delete(void*);
	// FUNCTION: ENGINE 0x10B69570
	template bool mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Slot8(void*);
	// FUNCTION: ENGINE 0x10B696B0
	template void mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >::Slot16(mgraph::EvaluationFrame*);
	// FUNCTION: ENGINE 0x10B698C0
	template<> Node* NodeType<mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > > >::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new mgraph::Throw<mgraph::Packet<DynamicArray<mgraph::EnvelopeData,unsigned short> > >(static_cast<Graph*>(graph), *nodeName);
	}
}
