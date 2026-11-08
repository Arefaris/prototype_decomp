// The envelope node of the mgraph library (RTTI: mgraph::GraphItem, mgraph::Node, mgraph::Envelope and the envelope's
// data mgraph::EnvelopeData): a node that follows a curve of points. Only what the reflection names is described so far.
#ifndef MGRAPH_ENVELOPE_H
#define MGRAPH_ENVELOPE_H

#include "code/mgraph/node.h"
#include "code/om/allocation.h"
#include "code/om/dynamicarray.h"
#include "code/om/vectort.h"

namespace mgraph
{
	// The curve of an envelope: its points, and an array of numbers (meaning not recovered)
	class EnvelopeData
	{
	public:
		void SetPoints(const om::DynamicArray<om::VectorT<float, 2>, unsigned short>& newPoints);
		const om::DynamicArray<om::VectorT<float, 2>, unsigned short>& GetPoints() const;
		OM_ALLOCATION(EnvelopeData);

		om::DynamicArray<om::VectorT<float, 2>, unsigned short> points;
		om::DynamicArray<float, unsigned short> unknown8;
	};

	// 0x10880010 (another unit; name guess): the value of the curve for an input, with the input taken from the range
	// between the second and third number and the answer put into the range between the fourth and fifth
	float EvaluateEnvelope(const EnvelopeData* data, float input, float inputLow, float inputHigh, float outputLow, float outputHigh);

	inline const char* EnvelopeData::AllocationTag()
	{
		return "";
	}

	class Envelope : public Node
	{
	public:
		void SetValue(float newValue);
		float GetValue() const;
	};
}

#endif
