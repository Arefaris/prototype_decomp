// The node types of the mgraph library (RTTI: mgraph::Node and the nodes derived from it: the math nodes, the typed
// inlets, outlets, throws, catches, switches and lists, the property nodes), their pins, connections and events. The
// classes are described by their names and bases so far; the reflection of each is a template instance of the om library.
#ifndef MGRAPH_NODES_H
#define MGRAPH_NODES_H

#include "code/mgraph/envelope.h"
#include "code/om/dynamicarray.h"
#include "code/om/entity.h"
#include "code/om/metaclass.h"
#include "code/om/string.h"

namespace om
{
	// A vector of the engine's property types and a complex number (sizes not recovered)
	class Vector
	{
	public:
		float values[3];
	};

	class Complex
	{
	public:
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
		unsigned char unknown0;
	};

	// What a pin keeps for one channel (RTTI: mgraph::PinChannelData and mgraph::Packet<T>, 0x10 bytes). Slot 0 of the packets is
	// not recovered; slot 1 is the destructor. The packet is a handle (a pointer into a table, a count and a pool).
	class PinChannelData
	{
	public:
		virtual void Slot0(void* unknown, int unknown2) = 0;
		virtual ~PinChannelData()
		{
		}
	};

	// The values a pin carries for each channel
	template<class T> class Packet : public PinChannelData
	{
	public:
		Packet() :
			unknown4(0),
			unknown8(0),
			unknownC(0)
		{
		}
		Packet(const Packet& other) :
			unknown4(0),
			unknown8(0),
			unknownC(0)
		{
			Assign(other, 0, 0);
		}
		virtual void Slot0(void* unknown, int unknown2);
		virtual ~Packet()
		{
		}
		// 0x10AF5980 (one copy in the engine): gives up what the packet holds and shares what the other holds
		void Assign(const Packet& other, int unknown, int unknown2);

		unsigned int unknown4;
		unsigned int unknown8;
		unsigned int unknownC;
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
		OM_ALLOCATION(Type); \
		char unknown4[Size - sizeof(Base)]

	template<class Op> class __declspec(align(8)) CommutativeMath : public Node
	{
		MGRAPH_NODE_BODY(CommutativeMath, Node, 0x50);
	};
	template<class Op> const char* CommutativeMath<Op>::AllocationTag()
	{
		return "";
	}
	template<class Op> class __declspec(align(8)) NonCommutativeMath : public Node
	{
		MGRAPH_NODE_BODY(NonCommutativeMath, Node, 0x50);
	};
	template<class Op> const char* NonCommutativeMath<Op>::AllocationTag()
	{
		return "";
	}
	template<class Op> class __declspec(align(8)) Operator2 : public Node
	{
		MGRAPH_NODE_BODY(Operator2, Node, 0x50);
	};
	template<class Op> const char* Operator2<Op>::AllocationTag()
	{
		return "";
	}
	template<class Op> class __declspec(align(8)) UnaryMath : public Node
	{
		MGRAPH_NODE_BODY(UnaryMath, Node, 0x50);
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

	class __declspec(align(8)) PropertyNodeBase : public Node
	{
		MGRAPH_NODE_BODY(PropertyNodeBase, Node, 0x50);
	};
	class InletBase : public Node
	{
	};
	class OutletBase : public Node
	{
	};
	// The property nodes of the values the node holds itself are bigger
	template<class P> struct PropertyNodeSize
	{
		enum { value = 0x68 };
	};
	template<class T> struct PropertyNodeSize<Packet<T> > : PropertyNodeSize<T>
	{
	};
	template<> struct PropertyNodeSize<om::String>
	{
		enum { value = 0x70 };
	};
	template<> struct PropertyNodeSize<om::Vector>
	{
		enum { value = 0x70 };
	};
	template<> struct PropertyNodeSize<EnvelopeData>
	{
		enum { value = 0x70 };
	};
	template<> struct PropertyNodeSize<TriggerData>
	{
		enum { value = 0x60 };
	};
	template<class P> class __declspec(align(8)) PropertyNode : public PropertyNodeBase
	{
		MGRAPH_NODE_BODY(PropertyNode, PropertyNodeBase, PropertyNodeSize<P>::value);
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
	template<class P> class __declspec(align(8)) Throw : public Node
	{
		MGRAPH_NODE_BODY(Throw, Node, 0x68);
	};
	template<class P> const char* Throw<P>::AllocationTag()
	{
		return "";
	}
	template<class P> class __declspec(align(8)) Catch : public Node
	{
		MGRAPH_NODE_BODY(Catch, Node, 0x58);
	};
	template<class P> const char* Catch<P>::AllocationTag()
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
	template<class T> class __declspec(align(8)) ListCount : public Node
	{
		MGRAPH_NODE_BODY(ListCount, Node, 0x50);
	};
	template<class T> const char* ListCount<T>::AllocationTag()
	{
		return "";
	}
	template<class T> class __declspec(align(8)) ListEntry : public Node
	{
		MGRAPH_NODE_BODY(ListEntry, Node, 0x50);
	};
	template<class T> const char* ListEntry<T>::AllocationTag()
	{
		return "";
	}

	class CastBoolToTrigger : public Node
	{
	};
	class CastTriggerToBool : public Node
	{
	};
	class Chooser : public Node
	{
	};
	class Delay : public Node
	{
	};
	class Fade : public Node
	{
	};
	class Filter : public Node
	{
	};
	class Meter : public Node
	{
	};
	class MinMaxDistance : public Node
	{
	};
	class SelectIntFromTrigger : public Node
	{
	};
	class Smoother : public Node
	{
	};
	class SystemNode : public Node
	{
	};

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

	// The graph itself, an entity (RTTI: mgraph::Graph)
	class Graph : public om::Entity
	{
	public:
		explicit Graph(const om::ClassName& newName);
	};

	// The description of a node class that creates its nodes (RTTI: mgraph::NodeTypeBase and mgraph::NodeType<N>, 0x30 bytes;
	// the slots are the destructor, the creation of a node and the reflection of N)
	class __declspec(align(8)) NodeTypeBase
	{
	public:
		// 0x10AD1860 (registers the node type), the destructor 0x10AD1840
		NodeTypeBase(const unsigned int& newUnknown, const om::ClassName& newName);
		virtual ~NodeTypeBase();
		// Slot 1: makes a node of the class (the first argument is passed on to the node, the second is its name)
		virtual Node* CreateNode(void* unknown, const om::ClassName* nodeName) = 0;
		// Slot 2: the reflection of the node class
		virtual om::MetaTypeBase* GetMetaType() = 0;

		char unknown4[0x2C];
	};

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

	// The description of a pin's data type (RTTI: mgraph::PinDataTypeBase and mgraph::PinDataType<P>, P is a packet): it
	// names the reflection of the packet and the node classes that carry such packets (slots 1 to 4, names guessed)
	class PinDataTypeBase
	{
	public:
		virtual ~PinDataTypeBase();
		virtual om::MetaTypeBase* GetPacketType() = 0;
		virtual NodeTypeBase* GetPropertyNodeType() = 0;
		virtual NodeTypeBase* GetInletType() = 0;
		virtual NodeTypeBase* GetOutletType() = 0;
	};
	template<class P> class PinDataType : public PinDataTypeBase
	{
	public:
		PinDataType()
		{
		}
		virtual ~PinDataType();
		virtual om::MetaTypeBase* GetPacketType()
		{
			return om::FindMetaType(typeid(P));
		}
		virtual NodeTypeBase* GetPropertyNodeType()
		{
			return NodeType<PropertyNode<P> >::Get();
		}
		virtual NodeTypeBase* GetInletType()
		{
			return NodeType<Inlet<P> >::Get();
		}
		virtual NodeTypeBase* GetOutletType()
		{
			return NodeType<Outlet<P> >::Get();
		}
	};
}

#endif
