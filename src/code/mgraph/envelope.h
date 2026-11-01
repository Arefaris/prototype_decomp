// The envelope node of the mgraph library (RTTI: mgraph::GraphItem, mgraph::Node, mgraph::Envelope and the envelope's
// data mgraph::EnvelopeData): a node that follows a curve of points. Only what the reflection names is described so far.
#ifndef MGRAPH_ENVELOPE_H
#define MGRAPH_ENVELOPE_H

#include "code/om/dynamicarray.h"
#include "code/om/vectort.h"

namespace mgraph
{
	// The base of the nodes and of the connections of a graph (RTTI: mgraph::GraphItem). Slots 1 and 2 are pure, 3 to 6 are the
	// library's (not recovered).
	class GraphItem
	{
	public:
		virtual ~GraphItem();
		virtual void Slot1() = 0;
		virtual void Slot2() = 0;
		virtual void Slot3();
		virtual void Slot4();
		virtual void Slot5();
		virtual void Slot6();
	};

	class Node : public GraphItem
	{
	public:
		virtual ~Node();
		virtual void Slot1();
		virtual void Slot2();
		virtual void Slot3();
		virtual void Slot4();
		virtual void Slot5();
		virtual void Slot6();
		virtual void Slot7();
		virtual void Slot8();
		virtual void Slot9();
		virtual void Slot10();
		virtual void SetNumChannels(unsigned short newCount);
		virtual void Slot12();
		virtual void Slot13();
		virtual void Slot14();
		virtual void Slot15(unsigned int channel);
		virtual void Slot16();
	};

	// The curve of an envelope: its points, and an array of numbers (meaning not recovered)
	class EnvelopeData
	{
	public:
		void SetPoints(const om::DynamicArray<om::VectorT<float, 2>, unsigned short>& newPoints);
		const om::DynamicArray<om::VectorT<float, 2>, unsigned short>& GetPoints() const;

		om::DynamicArray<om::VectorT<float, 2>, unsigned short> points;
		om::DynamicArray<float, unsigned short> unknown8;
	};

	class Envelope : public Node
	{
	public:
		void SetValue(float newValue);
		float GetValue() const;
	};
}

#endif
