// The fade node of the mgraph library (RTTI: mgraph::Fade): fades a value towards a goal in a time.
#ifndef MGRAPH_FADE_H
#define MGRAPH_FADE_H

#include "code/mgraph/throw.h"

namespace mgraph
{
	// Makes the description of the node class and enters it in the registry (called when the library starts)
	void RegisterFade();

	class __declspec(align(8)) Fade : public Node
	{
	public:
		Fade(Graph* newGraph, const om::ClassName& newName);
		static void* operator new(size_t);
		static void operator delete(void* memory);
		static const char* AllocationTag();
		virtual void SetNumChannels(unsigned int newCount);
		virtual void Slot16(EvaluationFrame* frame);

		// What the node keeps for each channel (name guessed): the time it starts with
		struct Channel
		{
			explicit Channel(float newValue);
			float unknown0;
		};

		// The property "Time" (0x10B6F170 / 0x10B6F180)
		void SetTime(float newTime);
		float GetTime() const;

		float time;  // 0x50
		om::DynamicArray<Channel, unsigned short> channels;  // 0x54
		char unknown5C[4];
	};
}

namespace om
{
	// The loops that fill and copy the elements are the engine's
	template<> void DynamicArray<mgraph::Fade::Channel, unsigned short>::FillElements(mgraph::Fade::Channel* destination, unsigned short count, const mgraph::Fade::Channel& value);
	template<> void DynamicArray<mgraph::Fade::Channel, unsigned short>::CopyElements(mgraph::Fade::Channel* destination, const mgraph::Fade::Channel* source, unsigned short count);
}


#endif
