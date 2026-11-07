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

		// The property "Time" (0x10B6F170 / 0x10B6F180)
		void SetTime(float newTime);
		float GetTime() const;

		float time;  // 0x50
		char unknown54[12];
	};
}

#endif
