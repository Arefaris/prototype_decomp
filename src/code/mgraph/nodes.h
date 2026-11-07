// The node types of the mgraph library (RTTI: mgraph::Node and the nodes derived from it: the math nodes, the typed
// inlets, outlets, throws, catches, switches and lists, the property nodes), their pins, connections and events. The
// classes are described by their names and bases so far; the reflection of each is a template instance of the om library.
#ifndef MGRAPH_NODES_H
#define MGRAPH_NODES_H

#include "code/mgraph/envelope.h"
#include "code/mgraph/graph.h"
#include "code/om/allocator.h"
#include "code/om/dynamicarray.h"
#include "code/om/delegate.h"
#include "code/om/dynamicproperty.h"
#include "code/om/entity.h"
#include "code/om/metaclass.h"
#include "code/om/string.h"

namespace om
{
	// A vector of the engine's property types and a complex number (sizes not recovered)
	class Vector
	{
	public:
		Vector()
		{
			values[2] = 0.0f;
			values[1] = 0.0f;
			values[0] = 0.0f;
		}
		Vector(float x, float y, float z)
		{
			values[0] = x;
			values[1] = y;
			values[2] = z;
		}

		float values[3];
	};

	class Complex
	{
	public:
		Complex()
		{
			values[0] = 0.0f;
			values[1] = 0.0f;
		}

		float values[2];
	};
}

namespace mgraph
{
	// The colour of a node (RTTI: mgraph::NodeColour)
	class NodeColour
	{
	public:
		unsigned int colour;
	};

	// A trigger of the graph (RTTI: mgraph::TriggerData)
	class TriggerData
	{
	public:
		TriggerData() :
			unknown0(0)
		{
		}
		TriggerData& operator=(const TriggerData& other)
		{
			unknown0 = other.unknown0;
			return *this;
		}

		unsigned char unknown0;
	};

	// What a pin keeps for one channel (RTTI: mgraph::PinChannelData and mgraph::Packet<T>, 0x10 bytes). Slot 0 of the packets
	// folds the values of all channels into one again; slot 1 is the destructor. The packet holds its value itself, or a block
	// of the values of 256 channels.
	class PinChannelData
	{
	public:
		PinChannelData() :
			unknown4(0)
		{
		}
		virtual void Slot0(int count, om::Allocator* allocator) = 0;
		virtual ~PinChannelData()
		{
		}

		unsigned int unknown4;  // the owner of the channel (set by the input pins), after Slot0 the number of channels
	};

	// The values of 256 channels, aligned to 128 bytes inside the block (the block is allocated from the pin's allocator)
	template<class T> struct PacketBlock
	{
		PacketBlock()
		{
			data = reinterpret_cast<T*>((reinterpret_cast<unsigned int>(this) + 0x80) & 0xFFFFFF80);
		}
		static void* operator new(size_t size, om::Allocator* allocator)
		{
			return om::AllocateFrom(allocator, AllocationTag(), size, 4);
		}
		static void operator delete(void*, om::Allocator*)
		{
		}
		static const char* AllocationTag();

		char storage[256 * sizeof(T) + 0x80];
		T* data;
	};
	template<class T> const char* PacketBlock<T>::AllocationTag()
	{
		return "";
	}

	// The values a pin carries for each channel
	template<class T> class Packet : public PinChannelData
	{
	public:
		Packet() :
			blocks(0),
			value()
		{
		}
		Packet(const Packet& other) :
			blocks(0),
			value()
		{
			Assign(other, 0, 0);
		}
		virtual void Slot0(int count, om::Allocator* allocator);
		virtual ~Packet()
		{
		}
		// Gives up what the packet holds and takes over what the other holds
		void Assign(const Packet& other, int count, om::Allocator* allocator);
		// The values of the channels (null while the packet holds one value)
		T* GetData();
		const T* GetData() const;

		PacketBlock<T>* blocks;  // 8
		T value;  // 0xC
	};

	// The operations of the math nodes (RTTI: structs)
	struct VectorAdd
	{
	};
	struct FloatAdd
	{
	};
	struct FloatMultiply
	{
	};
	struct BoolOr
	{
	};
	struct BoolAnd
	{
	};
	struct TriggerAnd
	{
	};
	struct TriggerOr
	{
	};
	struct FloatSub
	{
	};
	struct BoolNot
	{
	};
	template<class T> struct GreaterThan
	{
	};
	template<class T> struct GreaterThanOrEqual
	{
	};
	template<class T> struct LessThanOrEqual
	{
	};
	template<class T> struct LessThan
	{
	};
	template<class T> struct Equal
	{
	};
	template<class T> struct NotEqual
	{
	};

	// The nodes allocate exactly their size (the engine's node classes have members that are not recovered yet)
#define MGRAPH_NODE_BODY(Type, Base, Size) \
	public: \
		Type(Graph* newGraph, const om::ClassName& newName); \
		OM_ALLOCATION(Type); \
		char unknown4[Size - sizeof(Base)]

	// The same for the classes that add nothing to the node
#define MGRAPH_NODE_BODY_PLAIN(Type) \
	public: \
		Type(Graph* newGraph, const om::ClassName& newName); \
		OM_ALLOCATION(Type)

	template<class Op> class __declspec(align(8)) CommutativeMath : public Node
	{
		MGRAPH_NODE_BODY_PLAIN(CommutativeMath);
	};
	template<class Op> const char* CommutativeMath<Op>::AllocationTag()
	{
		return "";
	}
	template<class Op> class __declspec(align(8)) NonCommutativeMath : public Node
	{
		MGRAPH_NODE_BODY_PLAIN(NonCommutativeMath);
	};
	template<class Op> const char* NonCommutativeMath<Op>::AllocationTag()
	{
		return "";
	}
	template<class Op> class __declspec(align(8)) Operator2 : public Node
	{
		MGRAPH_NODE_BODY_PLAIN(Operator2);
	};
	template<class Op> const char* Operator2<Op>::AllocationTag()
	{
		return "";
	}
	template<class Op> class __declspec(align(8)) UnaryMath : public Node
	{
		MGRAPH_NODE_BODY_PLAIN(UnaryMath);
	};
	template<class Op> const char* UnaryMath<Op>::AllocationTag()
	{
		return "";
	}
	template<class T> struct RandSize
	{
		enum { value = 0x60 };
	};
	template<> struct RandSize<om::Vector>
	{
		enum { value = 0x70 };
	};
	template<class T> class __declspec(align(8)) Rand : public Node
	{
		MGRAPH_NODE_BODY(Rand, Node, RandSize<T>::value);
	};
	template<class T> const char* Rand<T>::AllocationTag()
	{
		return "";
	}

	// The queue of the events a context executes (an intrusive list of the events' links and their number)
	class EventQueue
	{
	public:
		// 0x105CBE20: puts the link of an event at the end of the list
		void Add(unsigned int* link);
		// Queues an event and counts it
		void Post(unsigned int* link)
		{
			Add(link);
			count++;
		}

		unsigned int* head;
		unsigned int* tail;
		int count;
	};

	class __declspec(align(8)) PropertyNodeBase : public Node
	{
	public:
		virtual ~PropertyNodeBase()
		{
		}
		// Slots 17 to 20 do nothing in the base: the typed property nodes post the value of a property as an event, take it
		// from the property, answer the reflection of their value and make the delegate of a channel (names guessed)
		virtual void PostPropertyValue(unsigned int channel, EventQueue* queue, const om::DynamicPropertyBase* property);
		virtual void SetPropertyValue(unsigned int channel, const om::DynamicPropertyBase* property, int unknown);
		virtual om::MetaTypeBase* GetValueMetaType();
		virtual om::DelegatePropertyBase* CreateDelegate(unsigned int channel);
		OM_ALLOCATION(PropertyNodeBase);
	};
	class InletBase : public Node
	{
	};
	class OutletBase : public Node
	{
	};
	// The value a packet type carries
	template<class P> struct PacketValue
	{
	};
	template<class T> struct PacketValue<Packet<T> >
	{
		typedef T Type;
	};

	// What the evaluation of a graph hands to a node for a channel (names guessed): the entries the channel's inputs brought and the
	// place the node leaves its output
	template<class T> struct FrameEntry
	{
		unsigned int unknown0;
		unsigned int id;
		unsigned int unknown8;
		T value;
	};
	template<class T> struct FrameEntries
	{
		FrameEntry<T>** entries;
		unsigned int count;
	};
	template<class T> struct FrameOutput
	{
		FrameEntry<T>* entry;
	};
	class EvaluationFrame
	{
	public:
		unsigned short channel;
		void* inputs;  // 4: the FrameEntries of the channel's type
		char unknown8[8];
		void* outputs;  // 0x10: the FrameOutput of the channel's type
		unsigned int id;  // 0x14
		unsigned int unknown18;

		// The entries the input pin of an index brought (one FrameEntries for each input pin)
		template<class T> FrameEntries<T>* GetInputs(unsigned int pinIndex)
		{
			return reinterpret_cast<FrameEntries<T>*>(static_cast<FrameEntries<int>*>(inputs) + pinIndex);
		}
	};

	// What a property node keeps for a channel: the value, whether it changed and a number that goes with it (names guessed)
	template<class T> struct PropertyChannel
	{
		PropertyChannel(const T& newValue);
		// Takes the value the evaluation brought for its channel and hands it on (0x10B13B10 and the like)
		void Update(PropertyNodeBase* node, EvaluationFrame* frame);

		T value;
		bool changed;
		int unknown8;
	};

	template<class T> PropertyChannel<T>::PropertyChannel(const T& newValue) :
		value(newValue),
		changed(true),
		unknown8(0)
	{
	}

	// How a property node passes the value of a property on: through a local, or (for the types with a destructor)
	// by the address of the temporary the property returns
	struct ValueInLocal
	{
	};
	struct ValueInTemporary
	{
	};
	template<class T> struct PropertyValueAccess
	{
		typedef ValueInLocal Kind;
	};
	template<> struct PropertyValueAccess<om::String>
	{
		typedef ValueInTemporary Kind;
	};
	template<> struct PropertyValueAccess<om::DynamicArray<om::String, unsigned short> >
	{
		typedef ValueInTemporary Kind;
	};

	template<class P> class PropertyNodeOutputEvent;
	template<class P> class PropertyNodeInputEvent;
	template<class P> class PropertyPropertyDelegate;

	template<class P> class __declspec(align(8)) PropertyNode : public PropertyNodeBase
	{
	public:
		typedef typename PacketValue<P>::Type Value;
		typedef PropertyChannel<Value> Channel;

		virtual void SetNumChannels(unsigned int newCount);
		virtual void Slot15(unsigned int channel);
		virtual void Slot16(EvaluationFrame* frame);
		virtual void PostPropertyValue(unsigned int channel, EventQueue* queue, const om::DynamicPropertyBase* property);
		virtual void SetPropertyValue(unsigned int channel, const om::DynamicPropertyBase* property, int unknown);
		virtual om::MetaTypeBase* GetValueMetaType();
		virtual om::DelegatePropertyBase* CreateDelegate(unsigned int channel);
		// Slots 21 to 25 are the property node's own: events for the channels and the values (names guessed)
		virtual void PostInputEvent(EventQueue* queue, unsigned int channel, const Value* newValue);
		virtual void PostOutputEvent(EventQueue* queue, unsigned int channel, Value* destination);
		virtual const Value* GetChannelValue(unsigned int channel);
		virtual void SetDefaultValue(const Value* newValue);
		virtual void SetChannelValue(const Value* newValue, unsigned int channel, int unknown);
		OM_ALLOCATION(PropertyNode);

		void PassPropertyValue(unsigned int channel, const om::DynamicPropertyBase* property, int unknown, ValueInLocal);
		void PassPropertyValue(unsigned int channel, const om::DynamicPropertyBase* property, int unknown, ValueInTemporary);

		char unknown50[8];
		om::DynamicArray<Channel, unsigned short> channels;  // 0x58
		Value value;  // 0x60
	};
	template<class P> const char* PropertyNode<P>::AllocationTag()
	{
		return "";
	}
	template<class P> class __declspec(align(8)) Inlet : public InletBase
	{
		MGRAPH_NODE_BODY(Inlet, InletBase, 0x60);
	};
	template<class P> const char* Inlet<P>::AllocationTag()
	{
		return "";
	}
	template<class P> class __declspec(align(8)) Outlet : public OutletBase
	{
		MGRAPH_NODE_BODY(Outlet, OutletBase, 0x58);
	};
	template<class P> const char* Outlet<P>::AllocationTag()
	{
		return "";
	}
	template<class P> class __declspec(align(8)) Switch : public Node
	{
		MGRAPH_NODE_BODY(Switch, Node, 0x60);
	};
	template<class P> const char* Switch<P>::AllocationTag()
	{
		return "";
	}

	// The nodes that contain a graph
	class Abstraction : public Node
	{
	};
	class LinkedGraph : public Abstraction
	{
	};
	class EmbeddedGraph : public Abstraction
	{
	};

	// The description of a node class that creates its nodes (RTTI: mgraph::NodeTypeBase and mgraph::NodeType<N>, 0x30 bytes;
	// the slots are the destructor, the creation of a node and the reflection of N)
	class __declspec(align(8)) NodeTypeBase
	{
	public:
		// 0x10AD1860 (registers the node type), the destructor 0x10AD1840 (takes it out of the registry again)
		NodeTypeBase(const unsigned int& newFlags, const om::ClassName& newName);
		virtual ~NodeTypeBase();
		// Slot 1: makes a node of the class (the first argument is the graph the node belongs to, the second is its name)
		virtual Node* CreateNode(void* unknown, const om::ClassName* nodeName) = 0;
		// Slot 2: the reflection of the node class
		virtual om::MetaTypeBase* GetMetaType() = 0;

		// 0x10AD10E0: takes the node type out of the registry
		void Unregister();

		int instanceCount;  // 8: how many nodes of the class there are
		om::ClassName name;  // 0x10
		unsigned int flags;  // 0x18
		om::TreeNode treeNode;  // 0x1C: the node type in the registry of the node types
		unsigned int unknown2C;
	};

	// 0x10AD1460: enters a node type in the registry (name guessed)
	void RegisterNodeType(NodeTypeBase* nodeType);

	// 0x10AD1180: the description of the node class registered for the type_info (name guessed)
	NodeTypeBase* FindNodeType(const type_info& type);

	// The static in which the engine keeps what FindNodeType answered for a node class (one word per class)
	template<class N> struct NodeTypeCache
	{
		static NodeTypeBase* type;
	};

	template<class N> class NodeType : public NodeTypeBase
	{
	public:
		NodeType(om::MetaClassBase* parent, const unsigned int& newUnknown, const om::ClassName& newName) :
			NodeTypeBase(newUnknown, newName)
		{
			om::MetaClass<N>::Create(newName, parent);
		}
		virtual ~NodeType()
		{
			ReleaseMetaType();
			ForgetNodeType();
		}
		virtual Node* CreateNode(void* unknown, const om::ClassName* nodeName);
		virtual om::MetaTypeBase* GetMetaType()
		{
			return FindMetaType();
		}
		// Makes the description of the node class N, which registers itself (names of the statics guessed): under the
		// reflection of a parent class, or under that of the node class another description stands for
		static void Register(om::MetaClassBase* parent, const unsigned int& newUnknown, const om::ClassName& newName)
		{
			new NodeType(parent, newUnknown, newName);
		}
		static void RegisterDerived(NodeTypeBase* parent, const unsigned int& newUnknown, const om::ClassName& newName)
		{
			om::MetaClassBase* parentType = static_cast<om::MetaClassBase*>(parent->GetMetaType());
			new NodeType(parentType, newUnknown, newName);
		}
		// The description of the node class N, found once and kept (names of the statics guessed)
		static NodeTypeBase* Get();
		// Destroys the description of the node class N (when the library shuts down)
		static void Destroy();
		// The reflection of N, found once and kept in the cache the users of the type share
		static om::MetaTypeBase* FindMetaType()
		{
			om::MetaTypeBase*& cache = om::MetaTypeCache<N>::type;
			if (cache == 0)
			{
				cache = om::FindMetaType(typeid(N));
			}
			return cache;
		}
		// Lets go of the reflection of N that the node types share
		static void ReleaseMetaType()
		{
			om::MetaTypeBase*& cache = om::MetaTypeCache<N>::type;
			if (cache == 0)
			{
				cache = om::FindMetaType(typeid(N));
			}
			om::MetaTypeBase* type = cache;
			if (om::ThreadSafeRefCount::Release(&cache->count) == 0 && type != 0)
			{
				delete type;
			}
			cache = 0;
		}
		// Forgets the description of N
		static void ForgetNodeType()
		{
			NodeTypeCache<N>::type = 0;
		}
		OM_ALLOCATION(NodeType);
	};
	template<class N> const char* NodeType<N>::AllocationTag()
	{
		return "";
	}
	template<class N> NodeTypeBase* NodeType<N>::Get()
	{
		NodeTypeBase*& cache = NodeTypeCache<N>::type;
		if (cache == 0)
		{
			cache = FindNodeType(typeid(N));
		}
		return cache;
	}
	template<class N> void NodeType<N>::Destroy()
	{
		NodeTypeBase*& cache = NodeTypeCache<N>::type;
		NodeTypeBase* type = cache;
		if (type == 0)
		{
			type = FindNodeType(typeid(N));
			cache = type;
		}
		if (type != 0)
		{
			delete type;
		}
	}

	// The description of a pin's data type (RTTI: mgraph::PinDataTypeBase and mgraph::PinDataType<P>, P is a packet, 0x20 bytes,
	// 8-aligned): it names the reflection of the packet and the node classes that carry such packets (slots 1 to 4, names
	// guessed). It sits in a registry under its name (the tree node is the last member).
	class PinDataTypeBase
	{
	public:
		PinDataTypeBase(const om::ClassName& newName) :
			name(newName)
		{
		}
		virtual ~PinDataTypeBase()
		{
		}
		virtual om::MetaTypeBase* GetPacketType() = 0;
		virtual NodeTypeBase* GetPropertyNodeType() = 0;
		virtual NodeTypeBase* GetInletType() = 0;
		virtual NodeTypeBase* GetOutletType() = 0;

		om::ClassName name;  // 8
		om::TreeNode treeNode;  // 0x10: the data type in the registry of the data types
	};

	// 0x10AD31E0 / 0x10AD2ED0: enter a data type in the registry, and take it out of it again (names guessed)
	void RegisterPinDataType(PinDataTypeBase* dataType);
	void UnregisterPinDataType(PinDataTypeBase* dataType);

	// The static in which the engine keeps the data type made for a packet type (one word per packet type, name guessed)
	template<class P> struct PinDataTypeCache
	{
		static PinDataTypeBase* type;
	};

	template<class P> class PinDataType : public PinDataTypeBase
	{
	public:
		PinDataType(const om::ClassName& newName) :
			PinDataTypeBase(newName)
		{
			RegisterPinDataType(this);
		}
		virtual ~PinDataType()
		{
			UnregisterPinDataType(this);
		}
		virtual om::MetaTypeBase* GetPacketType()
		{
			return om::FindMetaType(typeid(P));
		}
		virtual NodeTypeBase* GetPropertyNodeType()
		{
			return FindCachedNodeType<PropertyNode<P> >();
		}
		virtual NodeTypeBase* GetInletType()
		{
			return FindCachedNodeType<Inlet<P> >();
		}
		virtual NodeTypeBase* GetOutletType()
		{
			return FindCachedNodeType<Outlet<P> >();
		}
		// Makes the data type of the packet type P and keeps it (names guessed)
		static void Create(const om::ClassName& newName)
		{
			PinDataTypeCache<P>::type = new PinDataType(newName);
		}
		// Destroys the data type of P and forgets it together with the packet reflection the pins share (defined where the
		// pins are known)
		static void Release();
		OM_ALLOCATION(PinDataType);

	private:
		template<class N> static NodeTypeBase* FindCachedNodeType()
		{
			NodeTypeBase*& cache = NodeTypeCache<N>::type;
			if (cache == 0)
			{
				cache = FindNodeType(typeid(N));
			}
			return cache;
		}
	};
	template<class P> const char* PinDataType<P>::AllocationTag()
	{
		return "";
	}
}

#endif
