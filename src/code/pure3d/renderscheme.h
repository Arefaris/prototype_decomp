// pure3d::RenderScheme (RTTI name, vftable 0x10E5E1EC, seven slots): a named way of drawing the scene, which runs one
// pass tree. Member and slot names are guesses.
#ifndef PURE3D_RENDERSCHEME_H
#define PURE3D_RENDERSCHEME_H

#include "code/pure3d/pass.h"

namespace pure3d
{
	class RenderScheme
	{
	public:
		// Slot 0 (0x1074DCF0 is the scalar deleting destructor, its body 0x1074DC80)
		virtual ~RenderScheme();
		// Slots 1 / 2 (0x1074D860 / 0x1074D870): start / stop the pass tree
		virtual void Begin();
		virtual void End();
		// Slot 3 (0x1074D960): a copy of the scheme's default name
		// Slots 4 / 5 (0x1074DC60 / 0x1074DC70): do nothing
		virtual void Unknown4(int a);
		virtual void Unknown5(int a, int b, int c, int d);

		unsigned char unknown4[0x30];
		Pass* pass;
	};
}

#endif
