// The envelope node of the mgraph library (RTTI: mgraph::GraphItem, mgraph::Node, mgraph::Envelope and the envelope's
// data mgraph::EnvelopeData): a node that follows a curve of points. Only what the reflection names is described so far.
#ifndef MGRAPH_ENVELOPE_H
#define MGRAPH_ENVELOPE_H

#include "code/om/dynamicarray.h"
#include "code/om/vectort.h"

namespace mgraph
{
	class GraphItem
	{
	public:
		virtual ~GraphItem();
	};

	class Node : public GraphItem
	{
	public:
		virtual ~Node();
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
