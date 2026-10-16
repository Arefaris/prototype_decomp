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
	class PrimGroupList;

	// A copy of the device's render states, taken by Save and put back by Restore (or by the destructor unless it
	// was dismissed). Bits of `groups`: 1 render state, 2 view state, 4 z state, 8 stencil state.
	class RenderStateBackup
	{
	public:
		// 0x106F3420: dismissed 0 saves the states right away
		RenderStateBackup(pddiBaseContext* context, unsigned int groups, int dismissed);
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
		// 0x10625FA0: fills the descriptor of the buffer (its name and its flags)
		void Unknown10625FA0(int value);
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

	// What the device draws (0x4C bytes; the constructors at 0x10611CB0, 0x10611C30 and 0x10611DC0 fill it from the
	// primitive's own object, the part's world matrix and the list of objects to draw)
	struct PrimDrawDesc
	{
		PrimDrawDesc(void* format, int a, int count, PrimBuffer** buffers, int c, int d, int e, int f);
		PrimDrawDesc(void* format, const math::Matrix* world, int count, void** parts, PrimGroupList* list, int d,
			int e, int f, int g);
		PrimDrawDesc(void* format, const math::Matrix* world, int count, void** parts, int list, int d, int e,
			int f, int g, int h);

		// The vertex format of the object the parts of this primitive are drawn from
		void* format;
		unsigned char unknown4[0x48];
	};

	// The draw parameters (12 bytes; they are the shader's at +0x14). The bits of the second word that the tracer
	// reads: the blend mode (signed) and the factor of the blend
	struct PrimStreamParameters
	{
		// The defaults the render passes start from (bits 0 - 23 of the second word and the three flags of the third;
		// the rest is left as it is)
		PrimStreamParameters()
		{
			blendMode = 1;
			blendFactor = 0;
			unknown4Bits10 = 4;
			unknown4Bits14 = 1;
			flag0 = 0;
			flag1 = 0;
			flag2 = 0;
		}

		float unknown0;
		int blendMode : 5;
		unsigned int blendFactor : 5;
		unsigned int unknown4Bits10 : 4;
		unsigned int unknown4Bits14 : 10;
		unsigned int unknown4Bits24 : 8;
		unsigned char flag0 : 1;
		unsigned char flag1 : 1;
		unsigned char flag2 : 1;
		unsigned char unknown8Rest : 5;
		unsigned char unknown9[3];
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

		// Writes the next vertex (the texture coordinates, the colour with its red and blue bytes swapped, and the
		// position) and moves on to the one after; inline in the engine, the name is a guess
		void Vertex(float u, float v, unsigned int colour, float x, float y, float z)
		{
			float* coordinates = (float*)(vertex + coordinatesOffset);
			coordinates[0] = u;
			coordinates[1] = v;
			*(unsigned int*)(vertex + colourOffset) = colour >> 16 & 0xff | (colour & 0xff) << 16 | colour & 0xff00ff00;
			float* position = (float*)(vertex + positionOffset);
			position[0] = x;
			position[1] = y;
			position[2] = z;
			vertex += stride;
			count++;
		}

		int unknown4;
		int count;
		core::Name<core::CaseInsensitiveKey32> name;
		PrimStreamParameters parameters;
		int type;
		// Where the next vertex goes, the size of a vertex and where in a vertex the position, colour and texture
		// coordinates go
		unsigned char* vertex;
		int stride;
		int positionOffset;
		unsigned char unknown2C[0xC];
		int colourOffset;
		unsigned char unknown3C[4];
		int coordinatesOffset;
		unsigned char unknown44[0x20];
		PrimStreamBuffer* buffer;
		bool written;
	};
}

#endif
