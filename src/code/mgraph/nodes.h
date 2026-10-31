// The node types of the mgraph library (RTTI: mgraph::Node and the nodes derived from it: the math nodes, the typed
// inlets, outlets, throws, catches, switches and lists, the property nodes), their pins, connections and events. The
// classes are described by their names and bases so far; the reflection of each is a template instance of the om library.
#ifndef MGRAPH_NODES_H
#define MGRAPH_NODES_H

#include "code/mgraph/envelope.h"
#include "code/om/dynamicarray.h"
#include "code/om/entity.h"
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

	class PinChannelData
	{
	public:
		virtual ~PinChannelData();
	};

	// The values a pin carries for each channel
	template<class T> class Packet : public PinChannelData
	{
	public:
		T value;
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

	template<class Op> class CommutativeMath : public Node
	{
	};
	template<class Op> class NonCommutativeMath : public Node
	{
	};
	template<class Op> class Operator2 : public Node
	{
	};
	template<class Op> class UnaryMath : public Node
	{
	};
	template<class T> class Rand : public Node
	{
	};

	class PropertyNodeBase : public Node
	{
	};
	class InletBase : public Node
	{
	};
	class OutletBase : public Node
	{
	};
	template<class P> class PropertyNode : public PropertyNodeBase
	{
	};
	template<class P> class Inlet : public InletBase
	{
	};
	template<class P> class Outlet : public OutletBase
	{
	};
	template<class P> class Throw : public Node
	{
	};
	template<class P> class Catch : public Node
	{
	};
	template<class P> class Switch : public Node
	{
	};
	template<class T> class ListCount : public Node
	{
	};
	template<class T> class ListEntry : public Node
	{
	};

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

	class NodeTypeBase
	{
	public:
		virtual ~NodeTypeBase();
	};
	template<class N> class NodeType : public NodeTypeBase
	{
	};

	// 0x10AD1180: the description of the node class registered for the type_info (name guessed)
	NodeTypeBase* FindNodeType(const type_info& type);

	// The static in which the engine keeps what FindNodeType answered for a node class (one word per class)
	template<class N> struct NodeTypeCache
	{
		static NodeTypeBase* type;
	};

	// The description of the node class N, found once and kept (names of the two functions guessed)
	template<class N> NodeTypeBase* GetNodeType()
	{
		NodeTypeBase*& cache = NodeTypeCache<N>::type;
		if (cache == 0)
		{
			cache = FindNodeType(typeid(N));
		}
		return cache;
	}
	// Destroys the description of the node class N (when the library shuts down)
	template<class N> void DestroyNodeType()
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
			return GetNodeType<PropertyNode<P> >();
		}
		virtual NodeTypeBase* GetInletType()
		{
			return GetNodeType<Inlet<P> >();
		}
		virtual NodeTypeBase* GetOutletType()
		{
			return GetNodeType<Outlet<P> >();
		}
	};
}

#endif
