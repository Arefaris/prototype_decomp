// The front end's render output and heap settings (code/engine/frontend/frontendoutput.cpp; the file name is a guess, the functions lie in the
// front end's render unit from 0x10884C70). Names are guesses.
#include "code/engine/frontend/frontend.h"

namespace engine
{
	// 0x11316E40 / 0x11316E50
	void* gFrontendOutput;
	int gFrontEndHeapSetting;

	// FUNCTION: ENGINE 0x10884C70
	void SetFrontendOutput(void* output)
	{
		gFrontendOutput = output;
	}

	// Remembers the heap the front end's movies are made in and answers the one it had (name guess for the answer)
	// FUNCTION: ENGINE 0x1088A230
	int SetFrontEndHeap(int heap)
	{
		int previous = gFrontEndHeapSetting;
		gFrontEndHeapSetting = heap;
		return previous;
	}
}
