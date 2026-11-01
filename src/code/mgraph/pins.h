// The pins of the mgraph library's nodes and the connections between them (RTTI: mgraph::Pin, InputPinBase, OutputPinBase and
// the concrete and abstract pins derived from them, mgraph::GraphConnectionBase and the four kinds of connections between
// abstract and concrete pins, mgraph::ContextConnectionBase). A pin carries the packets of one data type; the classes of
// each type are template instances of the library.
#ifndef MGRAPH_PINS_H
#define MGRAPH_PINS_H

#include "code/mgraph/nodes.h"

namespace mgraph
{
	class GraphConnectionBase;
	// 0x10AD2F00: the reflection of a type found in the registry of the graph library (name guessed)
	om::MetaTypeBase* FindGraphMetaType(const type_info& type);

	// The static in which the engine keeps what FindGraphMetaType answered for a packet type (name guessed)
	template<class P> struct GraphMetaTypeCache
	{
		static om::MetaTypeBase* type;
	};

	// What the pins of a graph are made of: the base of every pin (RTTI: mgraph::Pin, 0x20 bytes). Slots 1 and 2 answer the
	// reflection of the packets the pin carries (the second one keeps the answer).
	class __declspec(align(8)) Pin
	{
	public:
		virtual ~Pin();
		virtual om::MetaTypeBase* GetPacketType() = 0;
		virtual om::MetaTypeBase* GetPacketTypeCached() = 0;

		char unknown4[0x10];
		unsigned char kind;  // 0x14: 0 for a concrete pin, 1 for an abstract one
		char unknown15[3];
		unsigned int unknown18;
		unsigned int unknown1C;
	};

	// Where a connection starts and ends
	class OutputPinBase : public Pin
	{
	public:
		// 0x10AD17B0: keeps the name and registers the pin with its node (the second argument is 0 for the typed pins)
		OutputPinBase(const om::ClassName* newName, int newUnknown, void* newNode, int newIndex);
		virtual ~OutputPinBase();
	};

	class InputPinBase : public Pin
	{
	public:
		virtual ~InputPinBase();
		// Slot 3: makes the connection from an output pin (null when the pins do not fit)
		virtual GraphConnectionBase* MakeConnection(Pin* other);

		bool unknown20;
		char unknown21[7];
	};

	// The pins of the nodes made for a graph's inlets and outlets (RTTI: AbstractInputPinBase, 0x38 bytes, and
	// AbstractOutputPinBase, 0x30 bytes)
	class AbstractInputPinBase : public InputPinBase
	{
	public:
		AbstractInputPinBase(void* newNode, int newKind, const om::ClassName* newName, int newIndex);
		virtual ~AbstractInputPinBase();

		unsigned int unknown28;
		unsigned int unknown2C;
		char unknown30[8];
	};

	class AbstractOutputPinBase : public OutputPinBase
	{
	public:
		AbstractOutputPinBase(void* newNode, const om::ClassName* newName, int newIndex);
		virtual ~AbstractOutputPinBase();
		virtual void Slot3();

		unsigned int unknown20;
		unsigned int unknown24;
		char unknown28[8];
	};

	// The pins that carry the packets themselves (RTTI: ConcreteInputPinBase, 0x30 bytes, and ConcreteOutputPinBase, 0x40
	// bytes); the slots from 3 on are the typed pins' (names guessed)
	class ConcreteInputPinBase : public InputPinBase
	{
	public:
		// 0x10AD1C20: keeps the name and registers the pin with its node
		ConcreteInputPinBase(const om::ClassName* newName, int newUnknown, void* newNode, int newIndex);
		virtual ~ConcreteInputPinBase();
		virtual GraphConnectionBase* MakeConnection(Pin* other) = 0;
		virtual void Slot4() = 0;
		virtual PinChannelData* GetChannelData() = 0;
		virtual void SetChannelOwner(void* newOwner) = 0;
		virtual bool IsChannelOwner(void* checkOwner) = 0;

		char unknown28[8];
	};

	class ConcreteOutputPinBase : public OutputPinBase
	{
	public:
		ConcreteOutputPinBase(const om::ClassName* newName, void* newNode, int newIndex) :
			OutputPinBase(newName, 0, newNode, newIndex),
			unknown30(0x10)
		{
		}
		virtual ~ConcreteOutputPinBase();
		// Slot 3: gives the pin the channels for a number of nodes' channels, which belong to an owner
		virtual void Slot3(unsigned int newCount, void* newOwner) = 0;

		// Two lists of the connections (head and tail)
		struct List
		{
			List() :
				head(0),
				tail(0)
			{
			}
			unsigned int head;
			unsigned int tail;
		};
		List unknown20;
		List unknown28;
		unsigned int unknown30;
		char unknown34[0xC];
	};

	// The connections between pins (RTTI: GraphConnectionBase and its four derived kinds). Slot 0 is the destructor, the
	// other slots belong to the library (their meaning is not recovered).
	class GraphConnectionBase : public GraphItem
	{
	public:
		GraphConnectionBase(Pin* newFrom, Pin* newTo);
		virtual ~GraphConnectionBase();
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3();
		virtual void Slot4();
		virtual void Slot5();
		virtual void Slot6();

		char unknown4[0x24];
	};

	class AbstractToConcreteGraphConnectionBase : public GraphConnectionBase
	{
	public:
		AbstractToConcreteGraphConnectionBase(Pin* newFrom, Pin* newTo);
		virtual ~AbstractToConcreteGraphConnectionBase()
		{
		}
	};

	class ConcreteToAbstractGraphConnectionBase : public GraphConnectionBase
	{
	public:
		ConcreteToAbstractGraphConnectionBase(Pin* newFrom, Pin* newTo);
		virtual ~ConcreteToAbstractGraphConnectionBase()
		{
		}
	};

	class AbstractToAbstractGraphConnectionBase : public GraphConnectionBase
	{
	public:
		AbstractToAbstractGraphConnectionBase(Pin* newFrom, Pin* newTo);
		virtual ~AbstractToAbstractGraphConnectionBase()
		{
		}
	};

	// The connection a context keeps for the pin of a graph (RTTI: mgraph::ContextConnectionBase). Slot 0 destroys it
	// through the allocator of its owner, slot 1 is the destructor.
	class PinAllocator
	{
	public:
		virtual void Slot0();
		virtual void Slot1();
		virtual void Release(void* memory, unsigned int size, unsigned int alignment);
	};

	// What owns a context connection: the allocator it was made by sits at 0x50
	class ConnectionOwner
	{
	public:
		char unknown0[0x50];
		PinAllocator allocator;
	};

	class ContextConnectionBase
	{
	public:
		ContextConnectionBase(void* newUnknown, void* newOwner, void* newPin);
		virtual void Destroy() = 0;
		virtual ~ContextConnectionBase();

		char unknown4[0x18];
		void* pin;  // 0x1C
		void* unknown20;
		ConnectionOwner* owner;  // 0x24
	};

	template<class P> class ConcreteToConcreteGraphConnection : public GraphConnectionBase
	{
	public:
		ConcreteToConcreteGraphConnection(Pin* newFrom, Pin* newTo) :
			GraphConnectionBase(newFrom, newTo)
		{
		}
		virtual ~ConcreteToConcreteGraphConnection()
		{
		}
		OM_ALLOCATION(ConcreteToConcreteGraphConnection);
	};
	template<class P> const char* ConcreteToConcreteGraphConnection<P>::AllocationTag()
	{
		return "";
	}

	template<class P> class AbstractToConcreteGraphConnection : public AbstractToConcreteGraphConnectionBase
	{
	public:
		AbstractToConcreteGraphConnection(Pin* newFrom, Pin* newTo) :
			AbstractToConcreteGraphConnectionBase(newFrom, newTo)
		{
		}
		virtual ~AbstractToConcreteGraphConnection()
		{
		}
		OM_ALLOCATION(AbstractToConcreteGraphConnection);
	};
	template<class P> const char* AbstractToConcreteGraphConnection<P>::AllocationTag()
	{
		return "";
	}

	template<class P> class AbstractToAbstractGraphConnection : public AbstractToAbstractGraphConnectionBase
	{
	public:
		AbstractToAbstractGraphConnection(Pin* newFrom, Pin* newTo) :
			AbstractToAbstractGraphConnectionBase(newFrom, newTo)
		{
		}
		virtual ~AbstractToAbstractGraphConnection()
		{
		}
		OM_ALLOCATION(AbstractToAbstractGraphConnection);
	};
	template<class P> const char* AbstractToAbstractGraphConnection<P>::AllocationTag()
	{
		return "";
	}

	template<class P> class ConcreteToAbstractGraphConnection : public ConcreteToAbstractGraphConnectionBase
	{
	public:
		ConcreteToAbstractGraphConnection(Pin* newFrom, Pin* newTo) :
			ConcreteToAbstractGraphConnectionBase(newFrom, newTo)
		{
		}
		virtual ~ConcreteToAbstractGraphConnection()
		{
		}
		OM_ALLOCATION(ConcreteToAbstractGraphConnection);
	};
	template<class P> const char* ConcreteToAbstractGraphConnection<P>::AllocationTag()
	{
		return "";
	}

	template<class P> class InputPin : public ConcreteInputPinBase
	{
	public:
		InputPin(void* newNode, const om::ClassName* newName, int newUnknown, int newIndex, P initial) :
			ConcreteInputPinBase(newName, newUnknown, newNode, newIndex),
			value(initial)
		{
		}
		virtual om::MetaTypeBase* GetPacketType()
		{
			return om::FindMetaType(typeid(P));
		}
		virtual om::MetaTypeBase* GetPacketTypeCached()
		{
			om::MetaTypeBase*& cache = GraphMetaTypeCache<P>::type;
			if (cache == 0)
			{
				cache = FindGraphMetaType(typeid(P));
			}
			return cache;
		}
		virtual GraphConnectionBase* MakeConnection(Pin* other);
		virtual void Slot4();
		virtual PinChannelData* GetChannelData()
		{
			return &value;
		}
		virtual void SetChannelOwner(void* newOwner)
		{
			value.unknown4 = reinterpret_cast<unsigned int>(newOwner);
		}
		virtual bool IsChannelOwner(void* checkOwner)
		{
			return value.unknown4 == reinterpret_cast<unsigned int>(checkOwner);
		}
		OM_ALLOCATION(InputPin);

		P value;  // 0x30
	};
	template<class P> const char* InputPin<P>::AllocationTag()
	{
		return "";
	}
	template<class P> GraphConnectionBase* InputPin<P>::MakeConnection(Pin* other)
	{
		if (other->GetPacketType() == GetPacketType())
		{
			if (other->kind == 0)
			{
				return new ConcreteToConcreteGraphConnection<P>(other, this);
			}
			if (other->kind == 1)
			{
				return new AbstractToConcreteGraphConnection<P>(other, this);
			}
		}
		return 0;
	}

	template<class P> class OutputPin : public ConcreteOutputPinBase
	{
	public:
		OutputPin(void* newNode, const om::ClassName* newName, int newIndex, const P& initial) :
			ConcreteOutputPinBase(newName, newNode, newIndex),
			value(initial)
		{
		}
		virtual ~OutputPin()
		{
		}
		virtual om::MetaTypeBase* GetPacketType()
		{
			return om::FindMetaType(typeid(P));
		}
		virtual om::MetaTypeBase* GetPacketTypeCached()
		{
			om::MetaTypeBase*& cache = GraphMetaTypeCache<P>::type;
			if (cache == 0)
			{
				cache = FindGraphMetaType(typeid(P));
			}
			return cache;
		}
		virtual void Slot3(unsigned int newCount, void* newOwner);
		OM_ALLOCATION(OutputPin);

		P value;  // 0x40
		om::DynamicArray<P, unsigned short> channels;  // 0x50
	};
	template<class P> const char* OutputPin<P>::AllocationTag()
	{
		return "";
	}
	template<class P> void OutputPin<P>::Slot3(unsigned int newCount, void* newOwner)
	{
		unsigned int oldCount = channels.size;
		channels.Resize(newCount, value);
		if (oldCount < newCount)
		{
			unsigned int i = oldCount;
			do
			{
				channels[i].unknown4 = reinterpret_cast<unsigned int>(newOwner);
				i++;
			}
			while (i < newCount);
		}
		unknown28.tail = reinterpret_cast<unsigned int>(channels.data);
	}

	template<class P> class AbstractInputPin : public AbstractInputPinBase
	{
	public:
		AbstractInputPin(const om::ClassName* newName, void* newNode, int newIndex) :
			AbstractInputPinBase(newNode, 1, newName, newIndex)
		{
		}
		virtual ~AbstractInputPin()
		{
		}
		virtual om::MetaTypeBase* GetPacketType()
		{
			return om::FindMetaType(typeid(P));
		}
		virtual om::MetaTypeBase* GetPacketTypeCached()
		{
			om::MetaTypeBase*& cache = GraphMetaTypeCache<P>::type;
			if (cache == 0)
			{
				cache = FindGraphMetaType(typeid(P));
			}
			return cache;
		}
		virtual GraphConnectionBase* MakeConnection(Pin* other);
		OM_ALLOCATION(AbstractInputPin);
	};
	template<class P> const char* AbstractInputPin<P>::AllocationTag()
	{
		return "";
	}

	template<class P> GraphConnectionBase* AbstractInputPin<P>::MakeConnection(Pin* other)
	{
		if (other->GetPacketType() == GetPacketType())
		{
			if (unknown20 != 0 || unknown18 == 0 || reinterpret_cast<GraphConnectionBase*>(unknown18 - 8) == 0)
			{
				if (other->kind == 1)
				{
					return new AbstractToAbstractGraphConnection<P>(other, this);
				}
				if (other->kind == 0)
				{
					return new ConcreteToAbstractGraphConnection<P>(other, this);
				}
			}
		}
		return 0;
	}

	template<class P> class AbstractOutputPin : public AbstractOutputPinBase
	{
	public:
		AbstractOutputPin(const om::ClassName* newName, void* newNode, int newIndex) :
			AbstractOutputPinBase(newNode, newName, newIndex)
		{
		}
		virtual ~AbstractOutputPin()
		{
		}
		virtual om::MetaTypeBase* GetPacketType()
		{
			return om::FindMetaType(typeid(P));
		}
		virtual om::MetaTypeBase* GetPacketTypeCached()
		{
			om::MetaTypeBase*& cache = GraphMetaTypeCache<P>::type;
			if (cache == 0)
			{
				cache = FindGraphMetaType(typeid(P));
			}
			return cache;
		}
		OM_ALLOCATION(AbstractOutputPin);
	};
	template<class P> const char* AbstractOutputPin<P>::AllocationTag()
	{
		return "";
	}

	template<class P> class ContextConnection : public ContextConnectionBase
	{
	public:
		ContextConnection(void* newUnknown, void* newOwner, void* newPin) :
			ContextConnectionBase(newUnknown, newOwner, newPin)
		{
		}
		virtual void Destroy();
		virtual ~ContextConnection()
		{
		}
		OM_ALLOCATION(ContextConnection);
	};
	template<class P> const char* ContextConnection<P>::AllocationTag()
	{
		return "";
	}
	template<class P> void ContextConnection<P>::Destroy()
	{
		ConnectionOwner* connectionOwner = owner;
		this->~ContextConnection();
		connectionOwner->allocator.Release(this, sizeof(ContextConnection), __alignof(ContextConnection));
	}
}

#endif
