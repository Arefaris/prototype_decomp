// The cast nodes of the mgraph library (0x10B6BB90 - 0x10B6D030): the nodes, the reflection of their classes and the
// descriptions of their node types, in the order the compiler emitted them (a guess: one translation unit).
#include "code/mgraph/castnodes.h"
#include "code/om/metaclass.h"

#pragma warning(disable: 4661)

namespace mgraph
{
	using namespace om;

	// FUNCTION: ENGINE 0x10B6BBC0
	CastBoolToTrigger::LastValue::LastValue() :
		value(false)
	{
	}

	// FUNCTION: ENGINE 0x10B6BBD0
	CastTriggerToBool::Level::Level() :
		value(false)
	{
	}

	// FUNCTION: ENGINE 0x10B6C5D0
	const char* CastBoolToTrigger::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10B6C790
	const char* CastTriggerToBool::AllocationTag()
	{
		return "";
	}

	// FUNCTION: ENGINE 0x10B6C9A0
	// EQUIVALENT: the call that gets the allocation tag of a pin leads to another copy of the same function (the engine's linker folded the copies) (99.8 %)
	CastBoolToTrigger::CastBoolToTrigger(Graph* newGraph, const ClassName& newName) :
		Node(CachedNodeType<CastBoolToTrigger>(), newGraph, newName, 1, 2)
	{
		new InputPin<Packet<bool> >(this, &MGRAPH_NAME("i"), 0, 0, Packet<bool>());
		new OutputPin<Packet<TriggerData> >(this, &MGRAPH_NAME("t"), 0, Packet<TriggerData>());
		new OutputPin<Packet<TriggerData> >(this, &MGRAPH_NAME("f"), 1, Packet<TriggerData>());
	}

	// FUNCTION: ENGINE 0x10B6C4E0
	void CastBoolToTrigger::SetNumChannels(unsigned int newCount)
	{
		lastValues.Resize(newCount, LastValue());
		Node::SetNumChannels(newCount);
	}

	// Puts a trigger value and the id of the frame in a trigger output
	static inline void SetTrigger(FrameEntry<TriggerData>* output, bool value, unsigned int id)
	{
		output->id = id;
		output->value.unknown0 = value;
	}

	// FUNCTION: ENGINE 0x10B6C160
	// EQUIVALENT: register allocation: the engine keeps the zero and the inverted value in dl, ours in cl, and orders two stores of the unchanged branch differently (97.0 %)
	void CastBoolToTrigger::Slot16(EvaluationFrame* frame)
	{
		LastValue& last = lastValues[frame->channel];
		FrameOutput<TriggerData>* outputs = static_cast<FrameOutput<TriggerData>*>(frame->outputs);
		FrameEntry<TriggerData>* trueOutput = outputs[0].entry;
		FrameEntry<TriggerData>* falseOutput = outputs[1].entry;
		bool value = frame->GetInputs<bool>(0)->entries[0]->value;
		if (value != last.value)
		{
			last.value = value;
			SetTrigger(trueOutput, value, frame->id);
			SetTrigger(falseOutput, !value, frame->id);
		}
		else
		{
			if (trueOutput->value.unknown0 != 0)
			{
				SetTrigger(trueOutput, false, frame->id);
			}
			if (falseOutput->value.unknown0 != 0)
			{
				SetTrigger(falseOutput, false, frame->id);
			}
		}
	}

	// FUNCTION: ENGINE 0x10B6CC60
	// EQUIVALENT: scheduling of the stores that make the trigger input pins, and the call that gets the allocation tag of a pin leads to another copy of the same function (the engine's linker folded the copies) (97.0 %)
	CastTriggerToBool::CastTriggerToBool(Graph* newGraph, const ClassName& newName) :
		Node(CachedNodeType<CastTriggerToBool>(), newGraph, newName, 2, 1)
	{
		new InputPin<Packet<TriggerData> >(this, &MGRAPH_NAME("h"), 0, 0, Packet<TriggerData>());
		new InputPin<Packet<TriggerData> >(this, &MGRAPH_NAME("l"), 0, 1, Packet<TriggerData>());
		new OutputPin<Packet<bool> >(this, &MGRAPH_NAME("b"), 0, Packet<bool>());
	}

	// FUNCTION: ENGINE 0x10B6C540
	void CastTriggerToBool::SetNumChannels(unsigned int newCount)
	{
		levels.Resize(newCount, Level());
		Node::SetNumChannels(newCount);
	}

	// FUNCTION: ENGINE 0x10B6C1D0
	void CastTriggerToBool::Slot16(EvaluationFrame* frame)
	{
		bool& level = levels[frame->channel].value;
		FrameEntries<TriggerData>* inputs = frame->GetInputs<TriggerData>(0);
		FrameEntry<TriggerData>* high = inputs->entries[0];
		FrameEntry<TriggerData>* low = frame->GetInputs<TriggerData>(1)->entries[0];
		bool newLevel = level;
		if (high != 0)
		{
			if (IsTriggerSet(high))
			{
				newLevel = true;
			}
		}
		if (low != 0)
		{
			if (IsTriggerSet(low))
			{
				newLevel = false;
			}
		}
		if (newLevel != level)
		{
			level = newLevel;
			FrameEntry<bool>* output = static_cast<FrameOutput<bool>*>(frame->outputs)->entry;
			unsigned int id = frame->id;
			output->value = newLevel;
			output->id = id;
		}
	}

	// FUNCTION: ENGINE 0x10B6CF30
	// FUNCTION: ENGINE 0x10B6D030
	void RegisterCastBoolToTrigger()
	{
		String nodeName("Bool To Trigger", 0);
		ClassName name(core::Hash64(nodeName.GetText(), 0));
		String category("Cast", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<CastBoolToTrigger>::RegisterDerived(CachedNodeType<Node>(), flags, name);
	}

	// FUNCTION: ENGINE 0x10B6D120
	void RegisterCastTriggerToBool()
	{
		String nodeName("Trigger To Bool", 0);
		ClassName name(core::Hash64(nodeName.GetText(), 0));
		String category("Cast", 0);
		unsigned int flags = core::Hash32(category.GetText(), 0);
		NodeType<CastTriggerToBool>::RegisterDerived(CachedNodeType<Node>(), flags, name);
	}

	template<> Node* NodeType<CastBoolToTrigger>::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new CastBoolToTrigger(static_cast<Graph*>(graph), *nodeName);
	}

	// FUNCTION: ENGINE 0x10B6CFB0
	template<> Node* NodeType<CastTriggerToBool>::CreateNode(void* graph, const ClassName* nodeName)
	{
		return new CastTriggerToBool(static_cast<Graph*>(graph), *nodeName);
	}
}

using namespace om;
using namespace mgraph;

	// FUNCTION: ENGINE 0x10B6BBE0
	template om::MetaClass<mgraph::CastBoolToTrigger>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B6BC10
	template type_info const* om::MetaClass<mgraph::CastBoolToTrigger>::GetType();
	// FUNCTION: ENGINE 0x10B6BC40
	template om::MetaClass<mgraph::CastTriggerToBool>::MetaClass(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B6BC70
	template type_info const* om::MetaClass<mgraph::CastTriggerToBool>::GetType();
	// FUNCTION: ENGINE 0x10B6BCC0
	template void om::MetaClass<mgraph::CastBoolToTrigger>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B6BCE0
	template void om::MetaClass<mgraph::CastTriggerToBool>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B6BD00
	template om::DynamicArray<mgraph::CastBoolToTrigger::LastValue,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B6BD10
	template om::DynamicArray<mgraph::CastTriggerToBool::Level,unsigned short>::DynamicArray();
	// FUNCTION: ENGINE 0x10B6BD20
	template mgraph::NodeTypeBase* mgraph::CachedNodeType<mgraph::CastBoolToTrigger>();
	// FUNCTION: ENGINE 0x10B6BD50
	template mgraph::NodeTypeBase* mgraph::CachedNodeType<mgraph::CastTriggerToBool>();
	// FUNCTION: ENGINE 0x10B6BDA0
	template char const* mgraph::NodeType<mgraph::CastBoolToTrigger>::AllocationTag();
	// FUNCTION: ENGINE 0x10B6BDB0
	template char const* mgraph::NodeType<mgraph::CastTriggerToBool>::AllocationTag();
	// FUNCTION: ENGINE 0x10B6BDC0
	template char const* om::MetaClass<mgraph::CastBoolToTrigger>::AllocationTag();
	// FUNCTION: ENGINE 0x10B6BDD0
	template char const* om::MetaClass<mgraph::CastTriggerToBool>::AllocationTag();
	// FUNCTION: ENGINE 0x10B6BDE0
	template void om::DynamicArray<mgraph::CastBoolToTrigger::LastValue,unsigned short>::DestroyElements(mgraph::CastBoolToTrigger::LastValue*, unsigned short);
	// FUNCTION: ENGINE 0x10B6BE60
	template void om::DynamicArray<mgraph::CastBoolToTrigger::LastValue,unsigned short>::ReleaseElements(mgraph::CastBoolToTrigger::LastValue*, unsigned short);
	// FUNCTION: ENGINE 0x10B6BE80
	template void om::DynamicArray<mgraph::CastTriggerToBool::Level,unsigned short>::DestroyElements(mgraph::CastTriggerToBool::Level*, unsigned short);
	// FUNCTION: ENGINE 0x10B6BE90
	template mgraph::CastTriggerToBool::Level& om::DynamicArray<mgraph::CastTriggerToBool::Level,unsigned short>::operator[](unsigned short);
	// FUNCTION: ENGINE 0x10B6BF00
	template void om::DynamicArray<mgraph::CastTriggerToBool::Level,unsigned short>::ReleaseElements(mgraph::CastTriggerToBool::Level*, unsigned short);
	// FUNCTION: ENGINE 0x10B6BF40
	template char const* om::DynamicArray<mgraph::CastBoolToTrigger::LastValue,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B6BF50
	template char const* om::DynamicArray<mgraph::CastTriggerToBool::Level,unsigned short>::AllocationTag();
	// FUNCTION: ENGINE 0x10B6BF60
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::CastBoolToTrigger>::Get();
	// FUNCTION: ENGINE 0x10B6BF80
	template mgraph::NodeTypeBase* mgraph::NodeType<mgraph::CastTriggerToBool>::Get();
	// FUNCTION: ENGINE 0x10B6BFA0
	template int om::MetaClass<mgraph::CastBoolToTrigger>::Slot5();
	// FUNCTION: ENGINE 0x10B6BFB0
	template void om::MetaClass<mgraph::CastBoolToTrigger>::Slot6(void*);
	// FUNCTION: ENGINE 0x10B6BFC0
	template int om::MetaClass<mgraph::CastTriggerToBool>::Slot5();
	// FUNCTION: ENGINE 0x10B6BFD0
	template void om::MetaClass<mgraph::CastTriggerToBool>::Slot6(void*);
	// FUNCTION: ENGINE 0x10B6BFE0
	template void* mgraph::NodeType<mgraph::CastBoolToTrigger>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B6C000
	template void* mgraph::NodeType<mgraph::CastTriggerToBool>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B6C020
	template void* om::MetaClass<mgraph::CastBoolToTrigger>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B6C040
	template void* om::MetaClass<mgraph::CastTriggerToBool>::operator new(size_t);
	// FUNCTION: ENGINE 0x10B6C0C0
	template om::DynamicArray<mgraph::CastTriggerToBool::Level,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10B6C0F0
	template om::DynamicArray<mgraph::CastBoolToTrigger::LastValue,unsigned short>::~DynamicArray();
	// FUNCTION: ENGINE 0x10B6C120
	template mgraph::CastBoolToTrigger::LastValue* om::DynamicArray<mgraph::CastBoolToTrigger::LastValue,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B6C140
	template mgraph::CastTriggerToBool::Level* om::DynamicArray<mgraph::CastTriggerToBool::Level,unsigned short>::Allocate(unsigned short);
	// FUNCTION: ENGINE 0x10B6C290
	template void om::MetaClass<mgraph::CastBoolToTrigger>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B6C300
	template void om::MetaClass<mgraph::CastTriggerToBool>::Create(Name<CaseSensitive64BitKey> const&, MetaClassBase*);
	// FUNCTION: ENGINE 0x10B6C370
	template void om::DynamicArray<mgraph::CastBoolToTrigger::LastValue,unsigned short>::Resize(unsigned short, mgraph::CastBoolToTrigger::LastValue const&);
	// FUNCTION: ENGINE 0x10B6C410
	template void om::DynamicArray<mgraph::CastTriggerToBool::Level,unsigned short>::Resize(unsigned short, mgraph::CastTriggerToBool::Level const&);
	// FUNCTION: ENGINE 0x10B6C4B0
	template void mgraph::NodeType<mgraph::CastBoolToTrigger>::Destroy();
	// FUNCTION: ENGINE 0x10B6C510
	template void mgraph::NodeType<mgraph::CastTriggerToBool>::Destroy();
	// FUNCTION: ENGINE 0x10B6C570
	template mgraph::NodeType<mgraph::CastBoolToTrigger>::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B6C5B0
	template void mgraph::NodeType<mgraph::CastBoolToTrigger>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B6C5E0
	template void mgraph::NodeType<mgraph::CastBoolToTrigger>::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B6C610
	template MetaTypeBase* mgraph::NodeType<mgraph::CastBoolToTrigger>::FindMetaType();
	// FUNCTION: ENGINE 0x10B6C630
	template MetaTypeBase* mgraph::NodeType<mgraph::CastBoolToTrigger>::GetMetaType();
	// FUNCTION: ENGINE 0x10B6C6A0
	template mgraph::NodeType<mgraph::CastBoolToTrigger>::~NodeType();
	// FUNCTION: ENGINE 0x10B6C740
	template mgraph::NodeType<mgraph::CastTriggerToBool>::NodeType(MetaClassBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B6C770
	template void mgraph::NodeType<mgraph::CastTriggerToBool>::operator delete(void*);
	// FUNCTION: ENGINE 0x10B6C7A0
	template void mgraph::NodeType<mgraph::CastTriggerToBool>::ForgetNodeType();
	// FUNCTION: ENGINE 0x10B6C7D0
	template MetaTypeBase* mgraph::NodeType<mgraph::CastTriggerToBool>::FindMetaType();
	// FUNCTION: ENGINE 0x10B6C7F0
	template MetaTypeBase* mgraph::NodeType<mgraph::CastTriggerToBool>::GetMetaType();
	// FUNCTION: ENGINE 0x10B6C860
	template mgraph::NodeType<mgraph::CastTriggerToBool>::~NodeType();
	// FUNCTION: ENGINE 0x10B6CF60
	template void mgraph::NodeType<mgraph::CastBoolToTrigger>::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
	// FUNCTION: ENGINE 0x10B6CFE0
	template void mgraph::NodeType<mgraph::CastTriggerToBool>::RegisterDerived(mgraph::NodeTypeBase*, unsigned int const&, Name<CaseSensitive64BitKey> const&);
