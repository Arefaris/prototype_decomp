// The registration of the node classes of the packet types the library has so far (0x10B60430 - 0x10B63450): each makes the description of
// one node class under the name a caller gives it and enters it in the registry (a guess: one translation unit with the registrations of the
// other kinds of node classes).
#include "code/mgraph/listnodes.h"
#include "code/om/metaclass.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B60430
	void RegisterListCountVector(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Misc", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<ListCount<Vector> >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B60500
	void RegisterListEntryVector(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Misc", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<ListEntry<Vector> >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B60820
	void RegisterInletTriggerData(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Inlet", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<Inlet<Packet<TriggerData> > >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B608F0
	void RegisterOutletTriggerData(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Outlet", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<Outlet<Packet<TriggerData> > >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B609C0
	void RegisterInletTriggerDataArray(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Inlet", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<Inlet<Packet<DynamicArray<TriggerData,unsigned short> > > >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B60A90
	void RegisterOutletTriggerDataArray(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Outlet", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<Outlet<Packet<DynamicArray<TriggerData,unsigned short> > > >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B60DA0
	void RegisterListCountTriggerData(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Misc", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<ListCount<TriggerData> >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B60E70
	void RegisterListEntryTriggerData(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Misc", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<ListEntry<TriggerData> >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B61190
	void RegisterInletComplex(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Inlet", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<Inlet<Packet<Complex> > >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B61260
	void RegisterOutletComplex(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Outlet", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<Outlet<Packet<Complex> > >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B61330
	void RegisterInletComplexArray(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Inlet", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<Inlet<Packet<DynamicArray<Complex,unsigned short> > > >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B61400
	void RegisterOutletComplexArray(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Outlet", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<Outlet<Packet<DynamicArray<Complex,unsigned short> > > >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B61950
	void RegisterListCountComplex(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Misc", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<ListCount<Complex> >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B61A20
	void RegisterListEntryComplex(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Misc", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<ListEntry<Complex> >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B61E40
	void RegisterInletEnvelopeData(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Inlet", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<Inlet<Packet<EnvelopeData> > >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B61F10
	void RegisterOutletEnvelopeData(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Outlet", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<Outlet<Packet<EnvelopeData> > >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B61FE0
	void RegisterInletEnvelopeDataArray(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Inlet", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<Inlet<Packet<DynamicArray<EnvelopeData,unsigned short> > > >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B620B0
	void RegisterOutletEnvelopeDataArray(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Outlet", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<Outlet<Packet<DynamicArray<EnvelopeData,unsigned short> > > >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B63380
	void RegisterListCountEnvelopeData(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Misc", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<ListCount<EnvelopeData> >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}

	// FUNCTION: ENGINE 0x10B63450
	void RegisterListEntryEnvelopeData(const String& name)
	{
		ClassName nodeName(core::Hash64(name.GetText(), 0));
		String category("Misc", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<ListEntry<EnvelopeData> >::RegisterDerived(CachedNodeType<Node>(), flags, nodeName);
	}
}
