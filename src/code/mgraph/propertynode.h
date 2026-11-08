// The property nodes of the mgraph library (RTTI: mgraph::PropertyNode<P> for the packet types P) with the events they post to the
// context and the delegates of their channels. The member functions are template instances of the library.
#ifndef MGRAPH_PROPERTYNODE_H
#define MGRAPH_PROPERTYNODE_H

#include "code/mgraph/events.h"
#include "code/mgraph/nodes.h"

namespace om
{
	// The comparison of the vectors and complex numbers the property nodes' arrays use
	inline bool operator==(const Vector& left, const Vector& right)
	{
		return left.values[0] == right.values[0] && left.values[1] == right.values[1] && left.values[2] == right.values[2];
	}
	inline bool operator==(const VectorT<float, 2>& left, const VectorT<float, 2>& right)
	{
		return left.values[0] == right.values[0] && left.values[1] == right.values[1];
	}
	inline bool operator==(const Complex& left, const Complex& right)
	{
		return left.values[0] == right.values[0] && left.values[1] == right.values[1];
	}
}

namespace mgraph
{
	// The comparison of the elements of the arrays the property nodes keep
	inline bool operator==(const TriggerData& left, const TriggerData& right)
	{
		return left.unknown0 == right.unknown0;
	}
	inline bool operator==(const EnvelopeData& left, const EnvelopeData& right)
	{
		return left.points == right.points;
	}

	// An event that copies the value of a channel out of its property node (RTTI: mgraph::PropertyNodeOutputEvent<P>, 0x14 bytes)
	template<class P> class PropertyNodeOutputEvent : public ContextEvent
	{
	public:
		typedef typename PacketValue<P>::Type Value;

		PropertyNodeOutputEvent(PropertyNode<P>* newNode, unsigned int newChannel, Value* newDestination) :
			channel(newChannel),
			node(newNode),
			destination(newDestination)
		{
		}
		virtual ~PropertyNodeOutputEvent()
		{
		}
		virtual void Execute(Context* context);
		OM_ALLOCATION(PropertyNodeOutputEvent);

		unsigned int channel;  // 8
		PropertyNode<P>* node;  // 0xC
		Value* destination;  // 0x10
	};

	// An event that sets the value of a channel of its property node (RTTI: mgraph::PropertyNodeInputEvent<P>, 0x18 bytes)
	template<class P> class PropertyNodeInputEvent : public ContextEvent
	{
	public:
		typedef typename PacketValue<P>::Type Value;

		PropertyNodeInputEvent(PropertyNode<P>* newNode, unsigned int newChannel, const Value& newValue, int newUnknown) :
			node(newNode),
			value(newValue),
			unknown(newUnknown),
			channel(newChannel)
		{
		}
		virtual void Execute(Context* context);
		OM_ALLOCATION(PropertyNodeInputEvent);

		PropertyNode<P>* node;  // 8
		Value value;  // 0xC
		int unknown;
		unsigned int channel;
	};

	// The property of a channel of a property node (RTTI: mgraph::PropertyPropertyDelegate<P>, 0x10 bytes)
	template<class P> class PropertyPropertyDelegate : public om::DelegateProperty<typename PacketValue<P>::Type>
	{
	public:
		typedef typename PacketValue<P>::Type Value;

		PropertyPropertyDelegate(PropertyNode<P>* newNode, unsigned int newChannel) :
			node(newNode),
			channel(newChannel)
		{
		}
		virtual ~PropertyPropertyDelegate()
		{
		}
		virtual Value Get();
		virtual void Set(Value newValue);
		OM_ALLOCATION(PropertyPropertyDelegate);

		PropertyNode<P>* node;  // 8
		unsigned int channel;  // 0xC
	};

	template<class P> const char* PropertyNodeOutputEvent<P>::AllocationTag()
	{
		return "";
	}
	template<class P> const char* PropertyNodeInputEvent<P>::AllocationTag()
	{
		return "";
	}
	template<class P> const char* PropertyPropertyDelegate<P>::AllocationTag()
	{
		return "";
	}

	template<class P> void PropertyNodeOutputEvent<P>::Execute(Context* context)
	{
		*destination = *node->GetChannelValue(channel);
	}

	template<class P> void PropertyNodeInputEvent<P>::Execute(Context* context)
	{
		node->SetChannelValue(&value, channel, unknown);
	}

	template<class P> typename PropertyPropertyDelegate<P>::Value PropertyPropertyDelegate<P>::Get()
	{
		return node->channels[channel].value;
	}

	template<class P> void PropertyPropertyDelegate<P>::Set(Value newValue)
	{
		node->channels[channel].value = newValue;
	}
	// Where the queue links an event
	inline om::GarbageLink* EventLink(ContextEvent* event)
	{
		return event != 0 ? &event->link : 0;
	}

	template<class T> void PropertyChannel<T>::Update(PropertyNodeBase* node, EvaluationFrame* frame)
	{
		FrameEntry<T>* target = static_cast<FrameOutput<T>*>(frame->outputs)->entry;
		FrameEntries<T>* inputs = static_cast<FrameEntries<T>*>(frame->inputs);
		unsigned int i = 0;
		if (inputs->count > 0)
		{
			FrameEntry<T>** entryPointer = inputs->entries;
			FrameEntry<T>* entry;
			do
			{
				entry = *entryPointer;
				if (entry->id == frame->id)
				{
					break;
				}
				i++;
				entryPointer++;
			}
			while (i < inputs->count);
			if (entry->id == frame->id)
			{
				value = entry->value;
				changed = true;
			}
		}
		if (changed)
		{
			unsigned int channelId = frame->id;
			target->value = value;
			target->id = channelId;
			changed = false;
		}
	}

	template<class P> void PropertyNode<P>::Slot16(EvaluationFrame* frame)
	{
		channels[frame->channel].Update(this, frame);
	}

	template<class P> void PropertyNode<P>::SetNumChannels(unsigned int newCount)
	{
		channels.Resize(newCount, Channel(value));
		Node::SetNumChannels(newCount);
	}

	template<class P> void PropertyNode<P>::Slot15(unsigned int channel)
	{
		channels[channel].changed = true;
	}

	template<class P> void PropertyNode<P>::PostPropertyValue(unsigned int channel, EventQueue* queue,
		const om::DynamicPropertyBase* property)
	{
		// The temporary value of the property lives until the event is queued
		queue->Post(EventLink(new PropertyNodeInputEvent<P>(this, channel,
			static_cast<const om::DynamicProperty<Value>*>(property)->GetValue(), 0)));
	}

	template<class P> void PropertyNode<P>::SetPropertyValue(unsigned int channel, const om::DynamicPropertyBase* property,
		int unknown)
	{
		PassPropertyValue(channel, property, unknown, typename PropertyValueAccess<Value>::Kind());
	}

	template<class P> __forceinline void PropertyNode<P>::PassPropertyValue(unsigned int channel, const om::DynamicPropertyBase* property,
		int unknown, ValueInLocal)
	{
		Value newValue = static_cast<const om::DynamicProperty<Value>*>(property)->GetValue();
		SetChannelValue(&newValue, channel, unknown);
	}

	template<class P> __forceinline void PropertyNode<P>::PassPropertyValue(unsigned int channel, const om::DynamicPropertyBase* property,
		int unknown, ValueInTemporary)
	{
		SetChannelValue(&static_cast<const om::DynamicProperty<Value>*>(property)->GetValue(), channel, unknown);
	}

	template<class P> om::MetaTypeBase* PropertyNode<P>::GetValueMetaType()
	{
		om::MetaTypeBase*& cache = om::MetaTypeCache<Value>::type;
		if (cache == 0)
		{
			cache = om::FindMetaType(typeid(Value));
		}
		return cache;
	}

	template<class P> om::DelegatePropertyBase* PropertyNode<P>::CreateDelegate(unsigned int channel)
	{
		return new PropertyPropertyDelegate<P>(this, channel);
	}

	template<class P> void PropertyNode<P>::PostInputEvent(EventQueue* queue, unsigned int channel, const Value* newValue)
	{
		queue->Post(EventLink(new PropertyNodeInputEvent<P>(this, channel, *newValue, 0)));
	}

	template<class P> void PropertyNode<P>::PostOutputEvent(EventQueue* queue, unsigned int channel, Value* destination)
	{
		queue->Post(EventLink(new PropertyNodeOutputEvent<P>(this, channel, destination)));
	}

	template<class P> const typename PropertyNode<P>::Value* PropertyNode<P>::GetChannelValue(unsigned int channel)
	{
		return &channels[channel].value;
	}

	template<class P> void PropertyNode<P>::SetDefaultValue(const Value* newValue)
	{
		value = *newValue;
	}

	// Whether a new value differs from the one a channel has: the engine does not compare the complex numbers
	template<class V> inline bool ValuesDiffer(const V& left, const V& right)
	{
		return left != right;
	}
	inline bool ValuesDiffer(const om::Complex& left, const om::Complex& right)
	{
		return false;
	}
	template<class E> inline bool ValuesDiffer(const om::DynamicArray<E, unsigned short>& left,
		const om::DynamicArray<E, unsigned short>& right)
	{
		return !(left == right);
	}
	// The engine compares only the curve of an envelope
	inline bool ValuesDiffer(const EnvelopeData& left, const EnvelopeData& right)
	{
		return !(left.points == right.points);
	}
	inline bool ValuesDiffer(const om::Vector& left, const om::Vector& right)
	{
		return !(left.values[0] == right.values[0] && left.values[1] == right.values[1] && left.values[2] == right.values[2]);
	}

	template<class P> void PropertyNode<P>::SetChannelValue(const Value* newValue, unsigned int channel, int unknown)
	{
		Channel& target = channels[channel];
		if (ValuesDiffer(target.value, *newValue) || target.unknown8 != unknown)
		{
			target.value = *newValue;
			target.unknown8 = unknown;
			target.changed = true;
		}
	}
}

#endif
