// pure3d::Context (code/pure3d/src/context.cpp; asserts "pure3d::context != 0"): the render context, one instance
// at pure3d::context. Only what the reconstructed code uses; layout partial, member names guessed.
#ifndef PURE3D_CONTEXT_H
#define PURE3D_CONTEXT_H

namespace pure3d
{
	class View;

	class Context
	{
	public:
		// 0x1070EE10: the view at +0x28
		View* GetView();

		unsigned char unknown0[0x28];
		View* view;
		unsigned char unknown2C[8];
		// The number of the frame being built
		unsigned int frame;
	};

	// 0x1127F350
	extern Context* context;
}

#endif
