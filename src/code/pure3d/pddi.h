// pure3d::pddiBaseContext (RTTI name; base pure3d::pddiEmptyClass, 68 virtual functions, implemented by
// pure3d::dxContext): the render device interface. Only the slots the reconstructed code calls are typed; their names
// follow the state they set (view, render, z and stencil state, the RTTI's pddiViewState / pddiRenderState /
// pddiZState / pddiStencilState) and are guesses. The view state setters are not virtual (0x10614C30 - 0x10615570
// write the current view state at +0x2C).
#ifndef PURE3D_PDDI_H
#define PURE3D_PDDI_H

#include "code/core/memory/imemoryallocator.h"
#include "code/core/name.h"
#include "code/math/matrix.h"
#include "code/pure3d/pddi/dx9/d3d9.h"

namespace content
{
	class ChunkReader;
}

namespace pure3d
{
	class pddiEmptyClass
	{
	};

	// Everything the pddi layer hands out by reference count (RTTI name; base core::IRefCount, four slots). The
	// constructor and the destructor the derived classes call live in the pddi base unit (0x10611F90 / 0x10611AF0),
	// so they are only declared here.
	class pddiObject : public core::IRefCount
	{
	public:
		// 0x10611F90: installs the pddiObject vftable and clears the count
		pddiObject();
		// 0x10612FC0 / 0x10611FD0
		virtual void AddRef();
		virtual void Release();
		// 0x10611AF0: installs the core::IRefCount vftable (the body of the derived destructors' base call)
		virtual ~pddiObject();
		// Slot 3; its meaning is unknown
		virtual void Unknown3();

		int mRefCount;
	};

	// The stream a primitive batch is built through (RTTI name, two slots). dxPrimStream is the Direct3D 9 one; the
	// class itself has no data, so its destructor stays in the header and only the second slot is out of line.
	class pddiPrimStream
	{
	public:
		virtual ~pddiPrimStream()
		{
		}
		virtual void Unknown1();
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

	class dxVertexDeclaration;
	class dxIndexBufferState;

	// What the device's slot 24 hands out for a set of flags (a query on the device; the name and the slots are
	// guesses, only slots 3, 4 and 7 are used). For 0x102 slots 3 and 4 read a vertex and an index chunk of a mesh
	// into the locked buffers (the count is the chunk's).
	class pddiQuery
	{
	public:
		virtual void Unknown0();
		virtual void Unknown1();
		virtual void Unknown2();
		virtual void ReadVertices(content::ChunkReader* reader, dxVertexDeclaration* lock, unsigned int count);
		virtual void ReadIndices(content::ChunkReader* reader, dxIndexBufferState* lock, unsigned int count);
		virtual void Unknown5();
		virtual void Unknown6();
		virtual bool Unknown7();
	};

	// The slot of a constant in the device's constant table (the name is a guess)
	struct ConstantSlot
	{
		// 0x10611E10: no slot (-1)
		ConstantSlot();
		// 0x10611E20 (another unit): the slot of the constant of that kind and name
		ConstantSlot(int kind, const core::Name<core::CaseInsensitiveKey32>* name);

		bool IsValid() const
		{
			return index != -1;
		}

		int index;
	};

	class pddiBaseContext;

	// The base of the states the device keeps on stacks (RTTI pddiState; one pure slot, which puts the state on the
	// device)
	class pddiState
	{
	public:
		virtual void Apply(pddiBaseContext* context) = 0;
	};

	// The states the device keeps on stacks (RTTI pddiViewState, pddiRenderState, pddiZState, pddiStencilState; their
	// sizes are 0x3C, 0x3C, 0x18 and 0x38). Only the words the device's accessors use are named, after what they
	// set (guesses)
	class pddiViewState : public pddiState
	{
	public:
		// 0x1061DC70
		virtual void Apply(pddiBaseContext* context);

		int unknown4;
		float unknown8;
		int unknownC;
		int unknown10;
		float unknown14[4];
		float unknown24[6];
	};

	class pddiRenderState : public pddiState
	{
	public:
		// 0x106156F0
		pddiRenderState();
		// 0x1061DBA0
		virtual void Apply(pddiBaseContext* context);

		int cullMode;
		int fillMode;
		int unknownC;
		bool colourWrite[4];
		bool alphaTest;
		unsigned char unknown15[3];
		int blend[4];
		bool fog;
		unsigned char unknown29[3];
		float fogNear;
		float fogFar;
		float alphaRef;
		bool unknown38;
	};

	class pddiZState : public pddiState
	{
	public:
		// 0x10615700
		pddiZState();
		// 0x1061DD10
		virtual void Apply(pddiBaseContext* context);

		bool zBuffer;
		unsigned char unknown5[3];
		int zCompare;
		bool zWrite;
		unsigned char unknownD[3];
		float zBias;
		float zSlope;
	};

	class pddiStencilState : public pddiState
	{
	public:
		// 0x10615710
		pddiStencilState();
		// 0x1061DD70
		virtual void Apply(pddiBaseContext* context);

		bool enabled;
		unsigned char unknown5[3];
		int compare;
		int ref;
		int mask;
		int writeMask;
		int fail;
		int zFail;
		int zPass;
		bool unknown24;
		unsigned char unknown25[3];
		int unknown28;
		int unknown2C;
		int unknown30;
		int unknown34;
	};

	// A 64-bit time that keeps the 4-byte alignment of the class around it
#pragma pack(push, 4)
	struct Time64
	{
		unsigned __int64 value;
	};
#pragma pack(pop)

	// A matrix of the device that has a copy in its shader constants: setting it marks the matrix constants of the
	// device as changed and writes the copy (0x48 bytes). The constants it is kept under are named by 0x1061E8F0.
	struct ConstantMatrix : public math::Matrix
	{
		// 0x1061DE20 (the engine has a copy of it out of line)
		ConstantMatrix()
		{
			Identity();
		}
		// 0x1061DA00 (the engine has a copy of it out of line): keeps the device and finds the constant of that name
		void Bind(pddiBaseContext* newContext, const core::Name<core::CaseInsensitiveKey32>* name);
		// Sets the matrix and its copy
		void Assign(const math::Matrix& other);
		// this = a * b, and the copy
		void Multiply(const math::Matrix& a, const math::Matrix& b);
		// Writes the matrix to its copy
		void Publish();

		ConstantSlot slot;
		pddiBaseContext* context;
	};

	// A vector of the device that has a copy in its shader constants (0x14 bytes)
	struct ConstantVector3
	{
		// 0x1061DA20 (the engine has a copy of it out of line)
		ConstantVector3()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}
		// 0x1061DA60: sets the vector and its copy
		void Assign(const float* value);

		float x;
		float y;
		float z;
		ConstantSlot slot;
		pddiBaseContext* context;
	};

	// The matrices of the device the shaders ask for by name (p3dWorldMatrix and its products, inverses and
	// transposes; the object lives at +0x154 of the device and 0x1061E670 makes it). Setting the view, the world or the
	// projection marks the products in `dirty`; the device makes them when a draw wants them (names are the shader
	// constants' own).
	struct ShaderMatrices
	{
		// 0x1061E670
		ShaderMatrices();
		// 0x1061E8F0: finds the constants of every matrix on the device
		void Bind(pddiBaseContext* newContext);
		// 0x1061E810: makes the products the mask names that are out of date
		void Update(unsigned int mask);
		// The products (each clears its bit of `dirty`): 0x1061DAA0, 0x10614760, 0x1061DE40, 0x1061DF70, 0x1061DFD0,
		// 0x1061E040, 0x1061E170, 0x1061E2A0, 0x1061E310, 0x1061E380, 0x1061E3F0, 0x1061E460, 0x1061E590
		void MakeViewProjection();
		void MakeWorldViewProjection();
		void MakeProjectionInverse();
		void MakeWorldViewInverse();
		void MakeWorldViewProjectionInverse();
		void MakeProjectionTranspose();
		void MakeWorldViewTranspose();
		void MakeWorldViewProjectionTranspose();
		void MakeWorldInverseTranspose();
		void MakeProjectionInverseTranspose();
		void MakeWorldViewInverseTranspose();
		void MakeWorldViewProjectionInverseTranspose();
		void MakeEyePosition();
		// 0x10615270 / 0x10615300 / 0x106146D0 (the engine has a copy of the last one out of line): the view, world and
		// projection matrix change
		void SetView(const math::Matrix* matrix);
		void SetWorld(const math::Matrix* matrix);
		void SetProjection(const math::Matrix* matrix);

		// 0x10614710 / 0x10614720 / 0x10614730 / 0x10614750 / 0x10614740
		const math::Matrix* GetView()
		{
			return &view;
		}
		const math::Matrix* GetWorld()
		{
			return &world;
		}
		const math::Matrix* GetProjection()
		{
			return &projection;
		}
		const math::Matrix* GetWorldView()
		{
			return &worldView;
		}
		const math::Matrix* GetWorldViewProjection()
		{
			return &worldViewProjection;
		}

		unsigned int dirty;
		pddiBaseContext* context;
		ConstantMatrix view;
		ConstantMatrix world;
		ConstantMatrix projection;
		ConstantMatrix worldView;
		ConstantMatrix viewProjection;
		ConstantMatrix projectionInverse;
		ConstantMatrix worldViewProjection;
		ConstantMatrix worldViewInverse;
		ConstantMatrix worldViewProjectionInverse;
		ConstantMatrix projectionTranspose;
		ConstantMatrix worldViewTranspose;
		ConstantMatrix worldViewProjectionTranspose;
		ConstantMatrix worldInverseTranspose;
		ConstantMatrix projectionInverseTranspose;
		ConstantMatrix worldViewInverseTranspose;
		ConstantMatrix worldViewProjectionInverseTranspose;
		ConstantVector3 eyePosition;
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
		// Draws a primitive buffer with a shader whose world matrix is not the current one (the gpu skin's Draw; the
		// descriptor is the one DrawPrimitive takes)
		virtual void Unknown2(const core::Name<core::CaseInsensitiveKey32>* shader, const void* desc,
			const void* parameters);
		virtual void Unknown3(int a, int b, int c);
		// Draws a part's batch (the 0x2C bytes at +0xA0 of a drawable part) with a shader and its parameters
		virtual void DrawBatch(const core::Name<core::CaseInsensitiveKey32>* shader, const void* batch,
			const void* parameters);
		// Draws a list of batches (the shadow casters of a pass)
		virtual void DrawBatches(const void* const* batches, int count);
		virtual void SetRenderTargets(const pddiRenderTargets* targets);
		virtual void Unknown7(int a, pddiSurface* surface, int b, int c, int d, int e);
		virtual void Unknown8(int a);
		virtual void Unknown9();
		// Slots 10 - 21: the device's queries. 10 makes an event query and ends it; 11 waits for one and lets go of
		// it; 12 tells (true) while one is still under way and lets go of it when it is not; 13 makes an occlusion
		// query (0 for the flag it is given); 14 lets go of one; 15 / 16 begin / end it; 17 waits for it and answers
		// the pixels it counted; 18 makes an event query; 19 lets go of one; 20 ends it; 21 waits for it. The base
		// class does none of it.
		virtual IDirect3DQuery9* Unknown10();
		virtual void Unknown11(IDirect3DQuery9* query);
		virtual bool Unknown12(IDirect3DQuery9* query);
		virtual IDirect3DQuery9* Unknown13(int flag);
		virtual void Unknown14(IDirect3DQuery9* query);
		virtual void Unknown15(IDirect3DQuery9* query);
		virtual void Unknown16(IDirect3DQuery9* query);
		virtual unsigned int Unknown17(IDirect3DQuery9* query);
		virtual IDirect3DQuery9* Unknown18();
		virtual void Unknown19(IDirect3DQuery9* query);
		virtual void Unknown20(IDirect3DQuery9* query);
		virtual void Unknown21(IDirect3DQuery9* query);
		// Slot 22 / 23: the projection from a field of view (the angle is multiplied by the radians to degrees factor)
		// or from the planes of the view volume; both set the projection matrix
		virtual void SetPerspective(float nearZ, float farZ, float fov, float aspect);
		virtual void SetOrthographic(float left, float right, float bottom, float top, float nearZ, float farZ);
		virtual pddiQuery* Unknown24(int flags);
		virtual bool Unknown25(int flags);
		virtual void Unknown26();
		// Slot 27 / 28 (0x10614B90 / 0x10614C00; the frame start and end): a frame starts (counted; asserts the device was initialised) / ends
		virtual void Unknown27();
		virtual void Unknown28();
		// Slots 29 - 35: the timings at +0x600 - +0x620 (microseconds). 31 reads the clock into +0x608; 32 reads
		// it into +0x610 and takes the time between and what slot 29 answers off, into +0x620
		virtual unsigned __int64 GetTimeUnknown600();
		virtual void SetTimeUnknown600(unsigned __int64 time);
		virtual void ReadTimeUnknown608();
		virtual void ReadTimeUnknown610();
		virtual void SetTimeUnknown618(unsigned __int64 time);
		virtual unsigned __int64 GetTimeUnknown618();
		virtual unsigned __int64 GetTimeUnknown620();
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
		// Slots 49 / 50: the word at +0xC of the render state, set / read
		virtual void SetRenderUnknownC(int value);
		virtual int GetRenderUnknownC();
		virtual void Unknown51(bool enable);
		virtual void Unknown52(int compare);
		virtual void Unknown53(int fail, int zFail, int zPass);
		virtual void Unknown54(int a);
		virtual void Unknown55(int a);
		virtual void Unknown56(int a, int b);
		virtual void Unknown57(int a);
		virtual void SetRenderUnknown38(bool value);
		// Render state
		virtual void SetFillMode(int mode);
		virtual void EnableAlphaTest(bool enable);
		virtual void SetBlendMode(int source, int destination, int sourceAlpha, int destinationAlpha);
		virtual void EnableFog(bool enable);
		virtual void SetFogRange(float nearZ, float farZ);
		virtual void SetAlphaRef(float ref);
		virtual void Unknown65();
		virtual ~pddiBaseContext();
		virtual void Unknown67();
		virtual void Unknown68();

		// The state getters (names follow the setters; 0x10614C40 - 0x10615170)
		void GetViewUnknown4(int* value);
		float GetViewUnknown8();
		int GetViewUnknownC();
		int GetViewUnknown10();
		void GetViewUnknown14(float* a, float* b, float* c, float* d);
		void GetViewUnknown24(float* a, float* b, float* c, float* d);
		void GetViewUnknown34(float* a, float* b);
		int GetCullMode();
		void GetColourWrite(bool* red, bool* green, bool* blue, bool* alpha);
		bool IsZBufferEnabled();
		int GetZCompare();
		bool IsZWriteEnabled();
		void GetZBias(float* bias, float* slope);
		bool IsStencilBufferEnabled();
		int GetStencilCompare();
		int GetStencilRef();
		int GetStencilMask();
		int GetStencilWriteMask();
		void GetStencilOp(int* fail, int* zFail, int* zPass);
		int GetFillMode();
		bool IsAlphaTestEnabled();
		bool IsFogEnabled();
		void GetFogRange(float* nearZ, float* farZ);
		float GetAlphaRef();
		// 0x106150B0: the four words of the blend mode (name guess; SetBlendMode's own)
		void GetBlendMode(int* a, int* b, int* c, int* d);
		// 0x10615190: the same clock as GetFrameCount, as a float
		float GetFrameTimeUnknown(int index);

		// 0x10614840: the matrix at +0x15C (the current view matrix)
		const math::Matrix* GetUnknown10614840();
		// 0x10614870: the matrix at +0x1EC (the projection matrix)
		const math::Matrix* GetUnknown10614870();
		// 0x10614850 / 0x10614860: the world matrix (+0x1A4) and the world view projection matrix (+0x30C)
		const math::Matrix* GetUnknown10614850();
		const math::Matrix* GetUnknown10614860();
		// 0x10614880: makes the matrices the mask names that are out of date
		void UpdateMatrices(unsigned int mask);
		// 0x10614890: makes the world view projection matrix (the products are made here too, not only by 0x10614760)
		void Unknown10614890();
		// 0x106148E0: puts the four states on the device
		void ApplyStates();
		// 0x10614910: clears the numbers the frame adds up (name unknown); 0x10614A10 works out the averages of them
		void Unknown10614910();
		void Unknown10614A10();
		// 0x10614C20: the word at +0x14 is not 0 (the meaning is unknown)
		bool IsUnknown14Set();
		// 0x106147E0: sets the projection matrix
		void SetProjectionMatrix(const math::Matrix* matrix);
		// 0x10615770: sets the world matrix (nothing when it is the one already set)
		void SetWorldMatrix(const math::Matrix* matrix);
		// 0x10615390: sets the view matrix (nothing when it is the one already set)
		void SetViewMatrix(const math::Matrix* matrix);

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
			// 0x1061A540: the slot of the constant of that kind and name (-1 in the slot when there is none)
			ConstantSlot* Find(ConstantSlot* slot, int kind, const core::Name<core::CaseInsensitiveKey32>* name);

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

		int unknown4;
		int unknown8;
		// 0x1061B550 and 0x1061B5A0 hand this to a new dxTexture
		IDirect3DDevice9* unknownC;
		// 0x10: the number of frames begun; 0x14: set while one is under way
		unsigned int frameNumber;
		unsigned int frameActive;
		unsigned char unknown18[4];
		// The stacks of the four states and the state each is on (the top)
		void* viewStack;
		void* renderStack;
		void* zStack;
		void* stencilStack;
		pddiViewState* viewState;
		pddiRenderState* renderState;
		pddiZState* zState;
		pddiStencilState* stencilState;
		Constants* constants;
		unsigned char unknown40[0x1C];
		// 0x5C: the clocks of the device as floats (GetFrameCount answers them as whole numbers; BeginFrame sets the
		// first to the frame number)
		float clocks[2];
		// 0x64 - 0x74: what the draw calls added up to this frame (floats): the primitives and the vertices of
		// the plain draws, then of the indexed ones, then how many draws there were (names are guesses)
		float drawnPrimitives;
		float drawnVertices;
		float drawnIndexedPrimitives;
		float drawnIndexedVertices;
		float drawCalls;
		// 0x78: the primitives per draw of the frame
		float primitivesPerDraw;
		unsigned char unknown7C[8];
		float unknown84;
		// 0x88 / 0x8C: what the batch draws added up to (the primitives, then how many draws there were)
		float batchedPrimitives;
		float batchDraws;
		// 0x90: 0x84 over the draws
		float unknown90;
		float unknown94[10];
		unsigned char unknownBC[0xFC - 0xBC];
		float unknownFC[3];
		unsigned char unknown108[8];
		float unknown110[10];
		// The bytes of texture memory the textures made on this device hold (0x1061CD70 adds a new texture's size
		// to it, 0x1061CBE0 takes it away again)
		float textureMemory;
		unsigned char unknown13C[0x10];
		unsigned int constantsDirty;
		unsigned char unknown150[4];
		// 0x154: the matrices the shaders ask for
		ShaderMatrices matrices;
		// Bit 0: a pass draws, bit 2: lit parts, bit 3: shadow parts (set around the passes' draw loops)
		unsigned int drawFlags;
		// 0x5F4: set by Init (BeginFrame asserts it)
		bool initialized;
		unsigned char unknown5F5[0x600 - 0x5F5];
		// 0x600 - 0x628: eight words of timings, in microseconds as 64-bit values (names are guesses)
		Time64 timeUnknown600;
		Time64 timeUnknown608;
		Time64 timeUnknown610;
		Time64 timeUnknown618;
		Time64 timeUnknown620;
		unsigned char unknown628[0x634 - 0x628];
	};

	inline void ConstantMatrix::Assign(const math::Matrix& other)
	{
		math::Matrix::operator=(other);
		pddiBaseContext* device = context;
		device->constantsDirty |= pddiBaseContext::CONSTANT_MATRIX;
		math::Matrix* copy = (math::Matrix*)&device->constants->values[slot.index];
		*copy = other;
	}

	inline void ConstantMatrix::Bind(pddiBaseContext* newContext, const core::Name<core::CaseInsensitiveKey32>* name)
	{
		context = newContext;
		newContext->constants->Find(&slot, 5, name);
	}

	inline void ConstantMatrix::Multiply(const math::Matrix& a, const math::Matrix& b)
	{
		math::Matrix::Multiply(a, b);
		Publish();
	}

	inline void ConstantMatrix::Publish()
	{
		pddiBaseContext* device = context;
		device->constantsDirty |= pddiBaseContext::CONSTANT_MATRIX;
		math::Matrix* copy = (math::Matrix*)&device->constants->values[slot.index];
		*copy = *this;
	}

	__forceinline void ShaderMatrices::SetProjection(const math::Matrix* matrix)
	{
		projection.Assign(*matrix);
		dirty |= 0x92493;
	}

	inline void ConstantVector3::Assign(const float* value)
	{
		x = value[0];
		y = value[1];
		z = value[2];
		pddiBaseContext* device = context;
		device->constantsDirty |= pddiBaseContext::CONSTANT_FLOAT3;
		float* copy = &device->constants->values[slot.index];
		copy[0] = x;
		copy[1] = y;
		copy[2] = z;
	}

	// The surfaces of the display (the object at 0x112818C0; names are guesses)
	class pddiDisplay
	{
	public:
		// 0x1073B850: the size of the display (0, 0: the engine's display's); false when the surfaces cannot be made
		bool SetSize(unsigned int width, unsigned int height);
		// 0x1073B450: puts the display's state back (the word at +0x3C into +0x40)
		void Unknown1073B450();
		// 0x1073AA10 (another unit, 342 bytes; 0x1070F1E0 jumps to it)
		void Unknown1073AA10();

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
