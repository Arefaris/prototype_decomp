// pure3d::dxContext (RTTI name; base pure3d::pddiBaseContext, 69 slots): the Direct3D 9 implementation of the pddi
// device interface. Only the buffer and texture factories the neighbouring units call are reconstructed (unit around
// 0x1061B550; the file name is guessed, no assert path survives).
#ifndef PURE3D_PDDI_DX9_DXCONTEXT_H
#define PURE3D_PDDI_DX9_DXCONTEXT_H

#include "code/core/name.h"
#include "code/math/vector.h"
#include "code/math/vector4.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/primstream.h"
#include "code/pure3d/pddi/dx9/dxindexbuffer.h"
#include "code/pure3d/pddi/dx9/dxtexture.h"
#include "code/pure3d/pddi/dx9/dxvertexbuffer.h"

namespace pure3d
{
	class dxProgram;
	class pddiShaderInputInitData;

	// The techniques of a shader (name guess; 0x10618C90 is its only known method)
	class dxTechniques
	{
	public:
		// 0x10618C90: the number of the technique a shader name draws with (-1 when it has none)
		int Find(const core::Name<core::CaseInsensitiveKey32>* name);
		// 0x10618550: the entry of the table at +0x2D0 for a technique number
		void* Get(int technique);

		unsigned char unknown0[0x2E8];
		// The name of the shader template the techniques belong to
		core::Name<core::CaseInsensitiveKey32> templateName;
		// 0x106283E0 / 0x10628400: the first and second program of the Z fill technique
		dxProgram* Unknown106283E0();
		dxProgram* Unknown10628400();
	};

	// The shader a draw goes through: the draw's own or the context's (RTTI unknown; slots 4 and 6 are the ones
	// the context uses, the others are placeholders)
	class dxShader
	{
	public:
		virtual void Unknown0();
		virtual void Unknown1();
		virtual void Unknown2();
		virtual void Unknown3();
		virtual dxTechniques* GetTechniques();
		virtual void Unknown5();
		virtual void Draw(int technique, pddiBaseContext::Constants* constants, const void* parameters);

		// The values of the shader's inputs by name (pddiShaderCommon's setters; a part's binding sets its parameters
		// through them): 0x10613EC0, 0x10613F30, 0x10613F90, 0x10613FF0, 0x10614050,
		// 0x106140C0, 0x10614140
		void SetBool(const core::Name<core::CaseInsensitiveKey32>& name, bool value);
		void SetTexture(const core::Name<core::CaseInsensitiveKey32>& name, dxTexture* texture);
		void SetFloat(const core::Name<core::CaseInsensitiveKey32>& name, float value);
		void SetVector2(const core::Name<core::CaseInsensitiveKey32>& name, const float* value);
		void SetVector3(const core::Name<core::CaseInsensitiveKey32>& name, const math::Vector& value);
		void SetVector4(const core::Name<core::CaseInsensitiveKey32>& name, const math::Vector4& value);
		void SetMatrix(const core::Name<core::CaseInsensitiveKey32>& name, const float* value);
		// 0x10614130: the same code as SetVector4 (the colour of an input)
		void SetColour(const core::Name<core::CaseInsensitiveKey32>& name, const math::Vector4& value);
	};

	// RTTI: pure3d::dxShaderTemplate (bases pddiBaseShaderTemplate, pddiObject, core::IRefCount; the object is
	// 0x2F0 bytes, made by dxContext::NewShaderTemplate)
	class dxShaderTemplate : public pddiObject
	{
	public:
		// Slot 4: adds a pass of the template (the names of the pass, its vertex program and its pixel program and
		// its draw state; the last argument is 0 where the template loader calls it)
		virtual void AddPass(const char* name, const char* vertexProgram, const char* pixelProgram,
			const PrimStreamParameters* state, int unknown);

		// 0x10619F70: finishes the template once the loader has read every input (the context and the defaults of
		// the inputs)
		void Finish(pddiBaseContext* context, pddiShaderInputInitData* inputs);
	};

	// A vertex or pixel shader program of a technique (name guess; the kind decides which of the two it is)
	class dxProgram
	{
	public:
		int unknown0;
		// 0 for a pixel program
		int kind;
		unsigned char unknown8[0x1C];
		void* pixelShader;
		void* vertexShader;
	};

	// What the context remembers of the programs it has set (the object at 0x11276DEC; name guess)
	struct dxProgramCache
	{
		dxProgram* vertex;
		dxProgram* pixel;
		dxProgram* saved;
		int unknownC;
		bool frozen;
		bool restricted;
		unsigned char unknown12[2];
		int vertexSets;
		int pixelSets;
	};

	// A batch of the list DrawBatches draws (name guess; only what the draw reads is named)
	struct dxDrawBatch
	{
		int unknown0;
		dxVertexBuffer* vertices;
		unsigned char unknown8[0x1C];
		dxIndexBuffer* indices;
		unsigned char unknown28[4];
		math::Matrix world;
		unsigned char unknown6C[4];
		unsigned short primitiveType;
		unsigned char unknown72[6];
		int startIndex;
		int indexCount;
	};

	// What the context tells about every draw (0x11276DEC is another of these; name guess)
	class dxDrawTracker
	{
	public:
		// 0x1062A8F0
		void Unknown1062A8F0(int a, int b, int count);
	};

	class dxContext : public pddiBaseContext
	{
	public:
		// 0x1061B530 / 0x1061B540: the words the factories above use
		int GetUnknown8();
		IDirect3DDevice9* GetUnknownC();
		// 0x1061B550 / 0x1061B5A0: a texture from the pool, released again when the description cannot be built
		dxTexture* NewTexture(const TextureDescription* description);
		dxTexture* NewTexture(const TextureDescription* description, const dxTexture* image);
		// 0x1061BCD0: a new shader template of that name, kept by its name (the last two arguments are the file's)
		dxShaderTemplate* NewShaderTemplate(const char* name, unsigned int unknown, unsigned int unknown2);
		// 0x1061B600 / 0x1061B660: a buffer from the pool (the creator's result is dropped)
		dxVertexBuffer* NewVertexBuffer(const VertexBufferDescription* description);
		dxIndexBuffer* NewIndexBuffer(const IndexBufferDescription* description);
		// 0x10620A20: draws with a pass of the shader (the context's own when none is given) and counts the draw;
		// hands out the tracker (names are guesses)
		dxDrawTracker* Unknown10620A20(dxShader* shader, int a, int b, int count,
			const core::Name<core::CaseInsensitiveKey32>* name, const void* parameters);
		// 0x10620B00: the same with the lit pass and no flags (the fifth argument is not used)
		dxDrawTracker* Unknown10620B00(dxShader* shader, int a, int b, int count, int unused);
		// Draws a part: a world matrix, a pass of the shader and then the primitives (0x1061FB40; the desc is a
		// PrimDrawDesc and the parameters are what the shader draws with)
		virtual void DrawPrimitive(const core::Name<core::CaseInsensitiveKey32>* shader, const void* desc,
			const void* parameters);
		// Draws the casters of a shadow pass with the Z fill programs (0x10621060)
		virtual void DrawBatches(const void* const* batches, int count);
		// The same for a gpu skin's descriptor, without the world matrix (0x10623250)
		virtual void Unknown2(const core::Name<core::CaseInsensitiveKey32>* shader, const void* desc,
			const void* parameters);
		// 0x106229B0: the step between a gpu skin's shader and its primitives (name unknown)
		void Unknown106229B0(int a, int b);
		// 0x1061F620: the size of the back buffer (name guess)
		void Unknown1061F620(unsigned int width, unsigned int height);
		// 0x1061F950: the viewport's rectangle (name guess)
		void Unknown1061F950(float x, float y, float width, float height);

		unsigned char unknown5F4[0x664 - 0x5F4];
		// 0x664: the shader a draw without one goes through
		dxShader* defaultShader;
		unsigned char unknown668[0x690 - 0x668];
		dxDrawTracker* tracker;
	};

	// 0x11276DEC
	extern dxProgramCache* gProgramCache;
	// 0x106283E0 / 0x10628400: the Z fill technique's two programs (name guess)
	// 0x10625A80 / 0x106268F0: resets the context keeps around a batch of draws (names unknown)
	void Unknown10625A80();
	void Unknown106268F0();
	// 0x10626180: binds what a batch draws from (name guess)
	void Unknown10626180(const dxDrawBatch* batch);

	// 0x1061F150: how many primitives of a kind the vertices or, when there are any, the indices make
	int PrimitiveCount(int type, int vertices, int indices);
	// 0x10626030: binds what a descriptor draws from (name guess)
	void Unknown10626030(const PrimDrawDesc* desc);
	// 0x11276F2C: set while a draw is under way (name guess)
	extern bool gDrawing;
	// 0x11276DCC: the index buffer the device has set
	extern dxIndexBuffer* gCurrentIndices;
	// 0x110BB690: the Direct3D primitive type of each of the five pddi ones
	extern int gD3DPrimitiveTypes[5];
	// 0x1127F294: the shader name a draw falls back to when its own has no technique
	extern core::Name<core::CaseInsensitiveKey32> gShaderFallback;

	// 0x106256A0: a step of the back end's setup that takes the device (name unknown)
	void Unknown106256A0(IDirect3DDevice9* device);

	// 0x11276D2C: the device the back end was built on (0x106202F0 installs it); the textures it made keep their
	// bytes of texture memory in its `textureMemory`
	extern dxContext* gContext;
}

#endif
