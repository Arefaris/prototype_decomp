// pure3d::pddiBaseContext (RTTI name; base pure3d::pddiEmptyClass, 68 virtual functions, implemented by
// pure3d::dxContext): the render device interface. Only the slots the reconstructed code calls are typed; their names
// follow the state they set (view, render, z and stencil state, the RTTI's pddiViewState / pddiRenderState /
// pddiZState / pddiStencilState) and are guesses. The view state setters are not virtual (0x10614C30 - 0x10615570
// write the current view state at +0x2C).
#ifndef PURE3D_PDDI_H
#define PURE3D_PDDI_H

#include "code/core/name.h"
#include "code/math/matrix.h"

namespace pure3d
{
	class pddiEmptyClass
	{
	};

	// A surface of the device (a render target or texture; names are guesses). The handle is what the device's
	// target setters take, the size is behind the info pointer
	struct pddiSize
	{
		unsigned int width;
		unsigned int height;
	};

	struct pddiSurfaceInfo
	{
		int unknown0;
		pddiSize* size;
	};

	class pddiSurface
	{
	public:
		// 0x1061C480
		int GetHandle();

		unsigned char unknown0[0x40];
		int handle;
		pddiSurfaceInfo* info;
	};

	// The render targets the device draws into (five handles; only the first two are set by the passes)
	struct pddiRenderTargets
	{
		int depth;
		int colour;
		int unknown8;
		int unknownC;
		int unknown10;
	};

	class pddiBaseContext : public pddiEmptyClass
	{
	public:
		// 0x10615180: one of the device's clocks, as a whole frame number
		int GetFrameCount(int index);
		// Clears the buffers named by the flags (1: colour) to the view state's clear colour
		virtual void Clear(int flags);
		// Draws a primitive buffer with a shader and its parameters
		virtual void DrawPrimitive(const core::Name<core::CaseInsensitiveKey32>* shader, const void* desc,
			const void* parameters);
		virtual void Unknown2();
		virtual void Unknown3();
		// Draws a part's batch (the 0x2C bytes at +0xA0 of a drawable part) with a shader and its parameters
		virtual void DrawBatch(const core::Name<core::CaseInsensitiveKey32>* shader, const void* batch,
			const void* parameters);
		// Draws a list of batches (the shadow casters of a pass)
		virtual void DrawBatches(const void* const* batches, int count);
		virtual void SetRenderTargets(const pddiRenderTargets* targets);
		virtual void Unknown7(int a, pddiSurface* surface, int b, int c, int d, int e);
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

		// 0x10614840: the matrix at +0x15C (the current view matrix)
		const math::Matrix* GetUnknown10614840();
		// 0x10614C20: the word at +0x14 is not 0 (the meaning is unknown)
		bool IsUnknown14Set();
		// 0x10615770: sets the world matrix (nothing when it is the one already set)
		void SetWorldMatrix(const math::Matrix* matrix);

		// View state (0x10614C30, 0x10614C50, 0x10614C80, 0x10614CA0, 0x10614CD0, 0x10615570)
		void SetViewUnknown4(int value);
		void SetViewUnknown8(float value);
		void SetViewUnknownC(int value);
		void SetViewUnknown10(int value);
		void SetViewUnknown14(float a, float b, float c, float d);
		void SetViewUnknown24(float a, float b, float c, float d, float e, float f);

		// The shader constants (floats, set by index; bit 4 of constantsDirty marks the pixel constants changed)
		struct Constants
		{
			// 0x1061A470: binds a texture to the constant at *slot (a texture constant keeps its sampler state word
			// at values[*slot + 1])
			void SetTexture(int* slot, pddiSurface* surface);

			int unknown0;
			int unknown4;
			float* values;
		};

		// A group of the constant table: the bit of constantsDirty a write marks (1 textures, 2 floats, 4 float
		// pairs, 8 float triples, 0x10 float quads, 0x20 matrices, 0x40 flags)
		enum ConstantGroup
		{
			CONSTANT_TEXTURE = 1,
			CONSTANT_FLOAT = 2,
			CONSTANT_FLOAT2 = 4,
			CONSTANT_FLOAT3 = 8,
			CONSTANT_FLOAT4 = 0x10,
			CONSTANT_MATRIX = 0x20,
			CONSTANT_FLAG = 0x40
		};

		// The value of a constant, marked as changed
		__forceinline float* GetConstant(const int& slot, unsigned int group)
		{
			constantsDirty |= group;
			Constants* table = constants;
			return &table->values[slot];
		}
		// The flag constants share the first word of the table: bit `bit` is cleared / set
		void ClearFlagConstant(const int& bit)
		{
			constantsDirty |= CONSTANT_FLAG;
			Constants* table = constants;
			*(unsigned int*)table->values &= ~(1 << bit);
		}
		void SetFlagConstant(const int& bit)
		{
			constantsDirty |= CONSTANT_FLAG;
			Constants* table = constants;
			*(unsigned int*)table->values |= 1 << bit;
		}
		// The words of a texture constant (the value, then the sampler state), marked as changed
		unsigned int* GetTextureConstant(const int& slot)
		{
			constantsDirty |= CONSTANT_TEXTURE;
			Constants* table = constants;
			return (unsigned int*)&table->values[slot];
		}

		unsigned char unknown4[0x10];
		int unknown14;
		unsigned char unknown18[0x24];
		Constants* constants;
		unsigned char unknown40[0x10C];
		unsigned int constantsDirty;
		unsigned char unknown150[0x4A0];
		// Bit 0: a pass draws, bit 2: lit parts, bit 3: shadow parts (set around the passes' draw loops)
		unsigned int drawFlags;
	};

	// The surfaces of the display (the object at 0x112818C0; names are guesses)
	class pddiDisplay
	{
	public:
		// 0x1073B850: the size of the display (0, 0: the engine's display's); false when the surfaces cannot be made
		bool SetSize(unsigned int width, unsigned int height);
		// 0x1073B450: puts the display's state back (the word at +0x3C into +0x40)
		void Unknown1073B450();

		unsigned char unknown0[0x20];
		pddiSurface* colour;
		pddiSurface* depth;
		unsigned char unknown28[0x28];
		unsigned int width;
		unsigned int height;
	};

	// 0x112818C0
	extern pddiDisplay* gDisplay;

	// The fog range the passes set (0x111B9514, 0x11282BC8)
	extern float gFogRangeNear;
	extern float gFogRangeFar;

	// 0x1127F354: the render device
	extern pddiBaseContext* pddi;
}

#endif
