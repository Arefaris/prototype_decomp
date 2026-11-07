// The inlets and outlets of the mgraph library (RTTI: mgraph::Inlet<P> and mgraph::Outlet<P>, P a packet): the nodes through which
// the packets of a graph enter and leave it. Every abstraction of the graph (a node that contains it) gets a pin for each of them,
// of the inlet's name, and the pins are linked with the inlet's or the outlet's own.
#ifndef MGRAPH_INLETS_H
#define MGRAPH_INLETS_H

#include "code/mgraph/throw.h"

namespace mgraph
{
	template<class P> Inlet<P>::Inlet(Graph* newGraph, const om::ClassName& newName) :
		InletBase(CachedNodeType<Inlet>(), newGraph, newName)
	{
		pin = new AbstractOutputPin<P>(this, &MGRAPH_NAME("out"), -1);
		for (Abstraction* abstraction = graph->FirstAbstraction(); abstraction != 0; abstraction = graph->NextAbstraction(abstraction))
		{
			AbstractInputPin<P>* input = new AbstractInputPin<P>(abstraction, &name, -1);
			input->AddSource(pin);
			pin->AddTarget(input);
			abstraction->Refresh();
		}
	}

	template<class P> Inlet<P>::~Inlet()
	{
		delete pin;
		for (Abstraction* abstraction = graph->FirstAbstraction(); abstraction != 0; abstraction = graph->NextAbstraction(abstraction))
		{
			delete abstraction->FindInput(name);
			abstraction->Refresh();
		}
	}

	template<class P> void Inlet<P>::Rename(const om::ClassName& newName)
	{
		om::ClassName oldName = name;
		Node::Rename(newName);
		om::ClassName currentName = name;
		for (Abstraction* abstraction = graph->FirstAbstraction(); abstraction != 0; abstraction = graph->NextAbstraction(abstraction))
		{
			abstraction->FindInput(oldName)->name = currentName;
		}
	}

	template<class P> bool Inlet<P>::Slot8(void* argument)
	{
		for (Abstraction* abstraction = graph->FirstAbstraction(); abstraction != 0; abstraction = graph->NextAbstraction(abstraction))
		{
			if (abstraction->FindInput(name) == 0)
			{
				AbstractInputPin<P>* input = new AbstractInputPin<P>(abstraction, &name, -1);
				input->AddSource(GetPin());
				abstraction->Refresh();
			}
		}
		return true;
	}

	template<class P> om::MetaTypeBase* Inlet<P>::GetValueMetaType()
	{
		om::MetaTypeBase*& cache = om::MetaTypeCache<Value>::type;
		if (cache == 0)
		{
			cache = om::FindMetaType(typeid(Value));
		}
		return cache;
	}

	template<class P> AbstractInputPinBase* Inlet<P>::CreateAbstractPin(Abstraction* abstraction)
	{
		return new AbstractInputPin<P>(abstraction, &name, -1);
	}

	template<class P> Outlet<P>::Outlet(Graph* newGraph, const om::ClassName& newName) :
		OutletBase(CachedNodeType<Outlet>(), newGraph, newName)
	{
		new AbstractInputPin<P>(this, &MGRAPH_NAME("in"), -1);
		for (Abstraction* abstraction = graph->FirstAbstraction(); abstraction != 0; abstraction = graph->NextAbstraction(abstraction))
		{
			AbstractOutputPin<P>* output = new AbstractOutputPin<P>(abstraction, &name, -1);
			output->AddTarget(GetPin());
			GetPin()->AddSource(output);
			abstraction->Refresh();
		}
	}

	template<class P> Outlet<P>::~Outlet()
	{
		delete GetPin();
		for (Abstraction* abstraction = graph->FirstAbstraction(); abstraction != 0; abstraction = graph->NextAbstraction(abstraction))
		{
			delete abstraction->FindOutput(name);
			abstraction->Refresh();
		}
	}

	template<class P> void Outlet<P>::Rename(const om::ClassName& newName)
	{
		om::ClassName oldName = name;
		Node::Rename(newName);
		for (Abstraction* abstraction = graph->FirstAbstraction(); abstraction != 0; abstraction = graph->NextAbstraction(abstraction))
		{
			abstraction->FindOutput(oldName)->name = name;
		}
	}

	template<class P> bool Outlet<P>::Slot8(void* argument)
	{
		for (Abstraction* abstraction = graph->FirstAbstraction(); abstraction != 0; abstraction = graph->NextAbstraction(abstraction))
		{
			if (abstraction->FindOutput(name) == 0)
			{
				AbstractOutputPin<P>* output = new AbstractOutputPin<P>(abstraction, &name, -1);
				output->AddTarget(GetPin());
				abstraction->Refresh();
			}
		}
		return true;
	}

	template<class P> om::MetaTypeBase* Outlet<P>::GetPacketMetaType()
	{
		return om::FindMetaType(typeid(P));
	}

	template<class P> AbstractOutputPinBase* Outlet<P>::CreateAbstractPin(Abstraction* abstraction)
	{
		return new AbstractOutputPin<P>(abstraction, &name, -1);
	}
}

#endif
