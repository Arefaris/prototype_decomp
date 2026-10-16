// pure3d::dxIndexBuffer, the Direct3D 9 index buffer of the pddi layer (unit around 0x106266D0 - 0x10626920; the
// file name is guessed, no assert path survives).
#include "code/pure3d/pddi/dx9/dxindexbuffer.h"

namespace pure3d
{
#ifdef NONMATCHING
	// FUNCTION: ENGINE 0x106266D0
	// NONMATCHING: register allocation, 64.9 %: the engine clears the state block with a zero it materialises in eax
	// (`xor eax, eax` after the member's constructor call), ours reuses the zero the initialiser list left in ebx.
	dxIndexBuffer::dxIndexBuffer() : unknown8(0), unknownC(0), unknown10(0), unknown14(0), unknown18(1), unknown34(-1)
	{
		dxIndexBufferState* state = &this->state;
		state->unknown0 = 0;
		state->unknown4 = 0;
		state->unknown8 = 0;
		state->unknownC = 0;
		state->unknown10 = 0;
		state->unknown14 = 0;
	}
#endif
}
