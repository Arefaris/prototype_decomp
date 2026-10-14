// pure3d::pddiBaseContext (RTTI name; base pure3d::pddiEmptyClass, 68 virtual functions, implemented by
// pure3d::dxContext): the render device interface. Only the slots the reconstructed code calls are typed; their names
// follow the state they set (view, render, z and stencil state, the RTTI's pddiViewState / pddiRenderState /
// pddiZState / pddiStencilState) and are guesses. The view state setters are not virtual (0x10614C30 - 0x10615570
// write the current view state at +0x2C).
#ifndef PURE3D_PDDI_H
#define PURE3D_PDDI_H

#include "code/core/name.h"

namespace pure3d
{
	class pddiEmptyClass
	{
	};

	class pddiBaseContext : public pddiEmptyClass
	{
	public:
		virtual void Unknown0();
		// Draws a primitive buffer with a shader and its parameters
		virtual void DrawPrimitive(const core::Name<core::CaseInsensitiveKey32>* shader, const void* desc,
			const void* parameters);
		virtual void Unknown2();
		virtual void Unknown3();
		virtual void Unknown4();
		virtual void Unknown5();
		virtual void Unknown6();
		virtual void Unknown7();
		virtual void Unknown8();
		virtual void Unknown9();
		virtual void Unknown10();
		virtual void Unknown11();
		virtual void Unknown12();
		virtual void Unknown13();
		virtual void Unknown14();
		virtual void Unknown15();
		virtual void Unknown16();
		virtual void Unknown17();
		virtual void Unknown18();
		virtual void Unknown19();
		virtual void Unknown20();
		virtual void Unknown21();
		virtual void Unknown22();
		virtual void Unknown23();
		virtual void Unknown24();
		virtual void Unknown25();
		virtual void Unknown26();
		virtual void Unknown27();
		virtual void Unknown28();
		virtual void Unknown29();
		virtual void Unknown30();
		virtual void Unknown31();
		virtual void Unknown32();
		virtual void Unknown33();
		virtual void Unknown34();
		virtual void Unknown35();
		// Render state
		virtual void SetCullMode(int mode);
		virtual void SetColourWrite(bool red, bool green, bool blue, bool alpha);
		// Z state
		virtual void EnableZBuffer(bool enable);
		virtual void SetZCompare(int compare);
		virtual void EnableZWrite(bool enable);
		virtual void SetZBias(float bias, float slope);
		// Stencil state
		virtual void EnableStencilBuffer(bool enable);
		virtual void SetStencilCompare(int compare);
		virtual void SetStencilRef(int ref);
		virtual void SetStencilMask(int mask);
		virtual void SetStencilWriteMask(int mask);
		virtual void SetStencilOp(int fail, int zFail, int zPass);
		virtual void Unknown48();
		virtual void Unknown49();
		virtual void Unknown50();
		virtual void Unknown51();
		virtual void Unknown52();
		virtual void Unknown53();
		virtual void Unknown54();
		virtual void Unknown55();
		virtual void Unknown56();
		virtual void Unknown57();
		virtual void Unknown58();
		// Render state
		virtual void SetFillMode(int mode);
		virtual void EnableAlphaTest(bool enable);
		virtual void SetBlendMode(int source, int destination, int sourceAlpha, int destinationAlpha);
		virtual void EnableFog(bool enable);
		virtual void SetFogRange(float nearZ, float farZ);
		virtual void SetAlphaRef(float ref);

		// View state (0x10614C30, 0x10614C50, 0x10614C80, 0x10614CA0, 0x10614CD0, 0x10615570)
		void SetViewUnknown4(int value);
		void SetViewUnknown8(float value);
		void SetViewUnknownC(int value);
		void SetViewUnknown10(int value);
		void SetViewUnknown14(float a, float b, float c, float d);
		void SetViewUnknown24(float a, float b, float c, float d, float e, float f);
	};

	// 0x1127F354: the render device
	extern pddiBaseContext* pddi;
}

#endif
