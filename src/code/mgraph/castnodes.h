// The cast nodes of the mgraph library (RTTI: mgraph::CastBoolToTrigger and mgraph::CastTriggerToBool): the first turns a bool
// into a trigger on its true output when the bool changes to true and one on its false output when it changes to false, the
// second turns the triggers of two inputs into a bool.
#ifndef MGRAPH_CASTNODES_H
#define MGRAPH_CASTNODES_H

#include "code/mgraph/throw.h"

namespace mgraph
{
	// Whether the trigger of a frame entry is set (0x10B40D50, name guessed)
	bool IsTriggerSet(const FrameEntry<TriggerData>* entry);

	// Where in the frame the first sample of a trigger is set (0x10B6E6A0, name guessed); false when none is
	bool GetTriggerOffset(const FrameEntry<TriggerData>* entry, unsigned int* offset);

	// Makes the description of the node classes and enters it in the registry (called when the library starts)
	void RegisterCastBoolToTrigger();
	void RegisterCastTriggerToBool();

	class __declspec(align(8)) CastBoolToTrigger : public Node
	{
	public:
		CastBoolToTrigger(Graph* newGraph, const om::ClassName& newName);
		virtual void SetNumChannels(unsigned int newCount);
		virtual void Slot16(EvaluationFrame* frame);
		static void* operator new(size_t);
		static void operator delete(void* memory);
		static const char* AllocationTag();

		// The value the input had last, for each channel (name guessed)
		struct LastValue
		{
			LastValue();
			bool value;
		};
		om::DynamicArray<LastValue, unsigned short> lastValues;  // 0x50
	};

	class __declspec(align(8)) CastTriggerToBool : public Node
	{
	public:
		CastTriggerToBool(Graph* newGraph, const om::ClassName& newName);
		virtual void SetNumChannels(unsigned int newCount);
		virtual void Slot16(EvaluationFrame* frame);
		static void* operator new(size_t);
		static void operator delete(void* memory);
		static const char* AllocationTag();

		// The bool the output has, for each channel (name guessed)
		struct Level
		{
			Level();
			bool value;
		};
		om::DynamicArray<Level, unsigned short> levels;  // 0x50
	};
}

#endif
