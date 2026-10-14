// pure3d::PrimStream (RTTI name; one virtual function) and the render state backup next to it in the primitive unit
// (code/pure3d/src/primitive.cpp, 0x106F2D00 - 0x106F4400; file name guessed). A PrimStream fills a vertex buffer
// between Begin and End and draws it with a shader. Layouts partial; names are guesses.
#ifndef PURE3D_PRIMSTREAM_H
#define PURE3D_PRIMSTREAM_H

#include "code/core/memory/imemoryallocator.h"
#include "code/core/name.h"
#include "code/pure3d/pddi.h"

namespace pure3d
{
	class Shader;

	// A copy of the device's render states, taken by Save and put back by Restore (or by the destructor unless it
	// was dismissed). Bits of `groups`: 1 render state, 2 view state, 4 z state, 8 stencil state.
	class RenderStateBackup
	{
	public:
		// 0x106F3460
		~RenderStateBackup();
		// 0x106F3050
		void Save();
		// 0x106F31D0
		void Restore();

		pddiBaseContext* context;
		unsigned char groups;
		int dismissed;
		// Render state
		int cullMode;
		int fillMode;
		bool colourWrite[4];
		bool alphaTest;
		int blend[4];
		bool fog;
		float fogNear;
		float fogFar;
		float alphaRef;
		// View state
		int view4;
		float view8;
		int viewC;
		int view10;
		float view14[4];
		float view24[6];
		// Z state
		bool zBuffer;
		int zCompare;
		bool zWrite;
		float zBias;
		float zSlope;
		// Stencil state
		bool stencil;
		int stencilCompare;
		int stencilRef;
		int stencilMask;
		int stencilWriteMask;
		int stencilFail;
		int stencilZFail;
		int stencilZPass;
	};

	// The vertex buffer a PrimStream fills (+0x8 its owner object, +0x14 the device buffer)
	class PrimBuffer
	{
	public:
		// 0x106258D0
		void Unlock();
	};

	struct PrimBufferOwner : core::IRefCount
	{
		unsigned char unknown4[0xC];
		void* format;
	};

	struct PrimStreamBuffer
	{
		unsigned char unknown0[8];
		PrimBufferOwner* owner;
		unsigned char unknownC[8];
		PrimBuffer* buffer;
	};

	// What the device draws (0x4C bytes, constructor 0x10611CB0)
	struct PrimDrawDesc
	{
		PrimDrawDesc(void* format, int a, int b, PrimBuffer** buffers, int c, int count, int type, int d);

		unsigned char unknown0[0x4C];
	};

	// The draw parameters (12 bytes)
	struct PrimStreamParameters
	{
		float unknown0;
		unsigned int unknown4;
		unsigned int unknown8;
	};

	class PrimStream
	{
	public:
		virtual void Unknown0();

		// 0x106F4100: Open, then the shader name and the parameters when given
		bool Begin(Shader* shader, int type, int format, int count, const core::Name<core::CaseInsensitiveKey32>& name,
			const PrimStreamParameters* parameters);
		// 0x106F3630: unlocks the buffer, draws what was written and lets the buffer go
		void End();
		// 0x106F3CD0
		bool Open(Shader* shader, int type, int format, int count);

		int unknown4;
		int count;
		core::Name<core::CaseInsensitiveKey32> name;
		PrimStreamParameters parameters;
		int type;
		unsigned char unknown20[0x44];
		PrimStreamBuffer* buffer;
		bool written;
	};
}

#endif
