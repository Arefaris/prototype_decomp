// pure3d::dxContext (RTTI name; base pure3d::pddiBaseContext, 69 slots): the Direct3D 9 implementation of the pddi
// device interface. Only the buffer and texture factories the neighbouring units call are reconstructed (unit around
// 0x1061B550; the file name is guessed, no assert path survives).
#ifndef PURE3D_PDDI_DX9_DXCONTEXT_H
#define PURE3D_PDDI_DX9_DXCONTEXT_H

#include "code/container/map.h"
#include "code/core/name.h"
#include "code/math/vector.h"
#include "code/math/vector4.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/primstream.h"
#include "code/pure3d/pddi/dx9/dxindexbuffer.h"
#include "code/pure3d/pddi/dx9/dxprogram.h"
#include "code/pure3d/pddi/dx9/dxtexture.h"
#include "code/pure3d/pddi/dx9/dxvertexbuffer.h"

namespace engine
{
	class Display;
}

namespace pure3d
{
	class pddiShaderInputInitData;
	struct DisplaySettings;
	class dxDevice;
	class dxContext;

	// The techniques of a shader (name guess). 0x10618560 is `bool IsEnabled(int technique)` (the entry's first byte), not
	// declared here: a fifth member function of this class moves two locals of Context::LoadDebugFont (0x1070FC90)
	// out of their slots.
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

	// What a shader is made from (RTTI pddiBaseShaderTemplate; 0x2F0 bytes): the name the shaders find it by, the
	// defaults of the inputs and the passes (dxShaderTemplate adds them)
	class pddiBaseShaderTemplate : public pddiObject
	{
	public:
		// Slot 4 (0x1061A2F0): adds a pass of the template (the names of the pass, its vertex program and its pixel
		// program and its draw state; the last argument is 0 where the template loader calls it); the base class does
		// not keep it
		virtual void AddPass(const char* name, const char* vertexProgram, const char* pixelProgram,
			const PrimStreamParameters* state, int unknown);

		// 0x10618580: copies the defaults of the inputs into the constants of a new shader
		void InitConstants(pddiBaseContext::Constants* constants);

		unsigned char unknown8[0x2E4 - 8];
		bool unknown2E4;
		unsigned char unknown2E5[3];
		core::Name<core::CaseInsensitiveKey32> templateName;
		pddiBaseContext::Constants* defaults;
	};

	// The inputs every shader keeps (RTTI pddiShaderCommon; 8 slots): the template, the constants, the checksum of
	// the constants (made when asked for) and the stamp of the last change. The setters and getters take the
	// inputs by name; a part's binding sets its parameters through them.
	class pddiShaderCommon : public pddiObject
	{
	public:
		// 0x10613C00
		pddiShaderCommon(pddiBaseShaderTemplate* newTemplate);
		// 0x106145A0 (0x10614620 is its scalar deleting form)
		virtual ~pddiShaderCommon();
		// Slots 4 - 7: the techniques (pure), 0x10613CF0 takes the constants of another shader, the draw (pure) and
		// 0x10613C70 clears the two blocks it is given
		virtual dxTechniques* GetTechniques() = 0;
		virtual void CopyConstants(pddiShaderCommon* other);
		virtual void Draw(int technique, pddiBaseContext::Constants* constants, const void* parameters) = 0;
		virtual void Unknown7(int unused, int* first, int* second);

		// 0x10613CB0: makes the checksum of the constants; 0x10614560 answers it
		void UpdateHash();
		unsigned int GetHash();
		// 0x10613CE0: the name of the template
		const core::Name<core::CaseInsensitiveKey32>* GetTemplateName();
		// 0x106145D0: whether both are made from the same template with the same constants
		int IsSameAs(pddiShaderCommon* other);
		// 0x10613BE0: whether the shader is the one the device drew with last
		bool IsCurrent();

		// 0x10613D10: whether the shader has an input of that kind and name
		bool HasInput(const core::Name<core::CaseInsensitiveKey32>& name, const int& kind);
		// The values of the shader's inputs by name: 0x10613EC0, 0x10613F30, 0x10613F90, 0x10613FF0, 0x10614050,
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
		// 0x10613D50 / 0x10613DE0 / 0x10613E60: the sampler of a texture input: the filter and the address modes,
		// the address modes, the filters
		void SetSampler(const core::Name<core::CaseInsensitiveKey32>& name, bool linear, int addressU, int addressV,
			int unused);
		void SetSamplerAddress(const core::Name<core::CaseInsensitiveKey32>& name, int addressU, int addressV,
			int addressW);
		void SetSamplerFilters(const core::Name<core::CaseInsensitiveKey32>& name, int minFilter, int magFilter,
			int mipFilter, unsigned int anisotropy);
		// 0x10614230 - 0x10614370: the values of the inputs (a default when there is no such input)
		bool GetBool(const core::Name<core::CaseInsensitiveKey32>& name);
		float GetFloat(const core::Name<core::CaseInsensitiveKey32>& name);
		const float* GetVector2(const core::Name<core::CaseInsensitiveKey32>& name);
		const float* GetVector3(const core::Name<core::CaseInsensitiveKey32>& name);
		const float* GetVector4(const core::Name<core::CaseInsensitiveKey32>& name);
		const float* GetMatrix(const core::Name<core::CaseInsensitiveKey32>& name);
		pddiSurface* GetTexture(const core::Name<core::CaseInsensitiveKey32>& name);
		// 0x106143B0 / 0x10614470 / 0x106144F0: the sampler of a texture input
		void GetSampler(const core::Name<core::CaseInsensitiveKey32>& name, bool* linear, int* addressU, int* addressV,
			int* unknown);
		void GetSamplerAddress(const core::Name<core::CaseInsensitiveKey32>& name, int* addressU, int* addressV,
			int* addressW);
		void GetSamplerFilters(const core::Name<core::CaseInsensitiveKey32>& name, int* minFilter, int* magFilter,
			int* mipFilter, unsigned int* anisotropy);

		pddiBaseShaderTemplate* shaderTemplate;
		pddiBaseContext::Constants* constants;
		unsigned int hash;
		bool hashDirty;
		unsigned int stamp;
	};

	// The shader a draw goes through: the draw's own or the context's (RTTI dxShader; its slots 4 and 6 are the
	// ones the context uses)
	class dxShader : public pddiShaderCommon
	{
	public:
		virtual dxTechniques* GetTechniques();
		virtual void Draw(int technique, pddiBaseContext::Constants* constants, const void* parameters);
	};

	// RTTI: pure3d::dxShaderTemplate (bases pddiBaseShaderTemplate, pddiObject, core::IRefCount; the object is
	// 0x2F0 bytes, made by dxContext::NewShaderTemplate)
	// A one-byte class the shader template is built with by value (its temporary lives in memory; name guess)
	struct ShaderBuildOptions
	{
		ShaderBuildOptions(bool newFlag) : flag(newFlag)
		{
		}

		bool flag;
	};

	class dxShaderTemplate : public pddiBaseShaderTemplate
	{
	public:
		// Slot 4: adds a pass of the template
		virtual void AddPass(const char* name, const char* vertexProgram, const char* pixelProgram,
			const PrimStreamParameters* state, int unknown);

		// 0x10628380 (another unit): a template of that name and the two words of the file it was read from
		dxShaderTemplate(const char* name, unsigned int unknown, unsigned int unknown2);
		// 0x1061B9B0: makes the programs of the template (name guess)
		void Unknown1061B9B0(ShaderBuildOptions options, dxContext* context);
		// 0x10619F70: finishes the template once the loader has read every input (the context and the defaults of
		// the inputs)
		void Finish(pddiBaseContext* context, pddiShaderInputInitData* inputs);
	};

	// The Direct3D render states the device is in (the object at 0x11276D70; name guess): the states the context sets
	// are only passed on when the word differs from the one kept here
	struct dxRenderStateCache
	{
		// The sampler states: four vertex samplers, then the pixel samplers, 0x50 states each
		int samplerStates[20][0x50];
		int renderStates[400];
		// The pixel shader constants the device was given (a register each) and the pass of the cache each was
		// written in: a register is only trusted while its pass is the current one
		float pixelConstants[256][4];
		int pixelConstantPasses[256];
		int pixelPass;
		// The range of registers written since the last flush
		unsigned int pixelDirtyFirst;
		unsigned int pixelDirtyLast;
		float vertexConstants[256][4];
		int vertexConstantPasses[256];
		int vertexPass;
		unsigned int vertexDirtyFirst;
		unsigned int vertexDirtyLast;
		// How many constant writes were left out because the register held the value, and how many were made
		int constantsSkipped;
		int constantsWritten;
	};

	// A batch of the list DrawBatches draws (name guess; only what the draw reads is named)
	struct dxDrawBatch
	{
		// How many of the streams are used
		unsigned int streamCount;
		dxVertexBuffer* streams[8];
		dxIndexBuffer* indices;
		unsigned int unknown28;
		math::Matrix world;
		dxShader* shader;
		unsigned short primitiveType;
		unsigned char unknown72[2];
		int baseVertex;
		int startIndex;
		int indexCount;
		unsigned int unknown80;
		// Set when the batch's streams are not the ones its declaration was made for
		bool rebuildDeclaration;
	};

	// What the context tells about every draw (0x11276DEC is another of these; name guess)
	class dxDrawTracker
	{
	public:
		// 0x1062A8F0
		void Unknown1062A8F0(int a, int b, int count);
		// 0x1062AA00
		void Unknown1062AA00();
	};

	class dxContext : public pddiBaseContext
	{
	public:
		// 0x1061F410: the constructor (another unit); 0x106202F0 takes the device and the display it draws through
		dxContext();
		void Unknown106202F0(dxDevice* device, engine::Display* display);
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
		// 0x1061F8B0: clears the buffers the flags name (1 colour, 2 z, 4 stencil) to that colour, depth and stencil,
		// inside the rectangle when there is one (the answers of the device are dropped)
		void Unknown1061F8B0(unsigned int flags, unsigned int colour, const int* rect, float z, unsigned int stencil);
		// 0x1061F940: tells the tracker (its argument is not used)
		void Unknown1061F940(int unused);
		// 0x1061F950: the viewport's rectangle (name guess)
		void Unknown1061F950(float x, float y, float width, float height);
		// 0x1061FA50: gives the device the viewport the context keeps
		void Unknown1061FA50();
		// 0x1061FAA0 / 0x1061FAF0: draw a descriptor's / a batch's primitives (plain or indexed) on the device
		void Unknown1061FAA0(IDirect3DDevice9* device, int type, unsigned int vertices, int primitives,
			const PrimDrawDesc* desc);
		void Unknown1061FAF0(IDirect3DDevice9* device, int type, unsigned int vertices, int primitives,
			const dxDrawBatch* batch);
		// 0x1061F600 / 0x1061F610: empty
		void Unknown1061F600();
		void Unknown1061F610();

		// Slot 3 (0x1061FDB0, does nothing), 6 (0x1061FF70) and 7 (0x1061FF10)
		virtual void Unknown3(int a, int b, int c);
		virtual void SetRenderTargets(const pddiRenderTargets* targets);
		virtual void Unknown7(int a, pddiSurface* surface, int b, int c, int d, int e);
		// Slots 9 - 21 are the device's queries (0x1061F650 - 0x1061F860, see the base class)
		virtual void Unknown9();
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
		// Slot 28 (0x1061F5C0): the frame ends, the device's scene with it
		virtual void Unknown28();
		// Slot 41 (0x1061FDC0): the bias is kept in the depth range of the viewport
		virtual void SetZBias(float bias, float slope);
		virtual void Unknown48();
		// Slots 54 - 58 (0x1061FE20 - 0x1061FE60) do nothing; slot 61 sets the scissor rectangle of the device and
		// 64 passes the reference on to the base class
		virtual void Unknown54(int a);
		virtual void Unknown55(int a);
		virtual void Unknown56(int a, int b);
		virtual void Unknown57(int a);
		virtual void SetRenderUnknown38(bool value);
		virtual void SetBlendMode(int source, int destination, int sourceAlpha, int destinationAlpha);
		virtual void SetAlphaRef(float ref);
		virtual void Unknown68();

		// Slots 22 and 23 (0x10620BE0, 0x10620C30)
		virtual void SetPerspective(float nearZ, float farZ, float fov, float aspect);
		virtual void SetOrthographic(float left, float right, float bottom, float top, float nearZ, float farZ);
		// Slot 24 (0x10620110): the object that answers for a set of flags (0x102 and 0x400001; null for any other)
		virtual pddiQuery* Unknown24(int flags);
		// Slot 25 (0x10620140): whether the flags are the one the device answers for (0x400001)
		virtual bool Unknown25(int flags);
		// The render states: each calls the base class's and passes the Direct3D value on when it differs from the
		// one the device is in (0x10621440 - 0x10621B50)
		virtual void SetCullMode(int mode);
		virtual void SetColourWrite(bool red, bool green, bool blue, bool alpha);
		virtual void EnableZBuffer(bool enable);
		virtual void SetZCompare(int compare);
		virtual void EnableZWrite(bool enable);
		virtual void EnableStencilBuffer(bool enable);
		virtual void SetStencilCompare(int compare);
		virtual void SetStencilRef(int ref);
		virtual void SetStencilMask(int mask);
		virtual void SetStencilWriteMask(int mask);
		virtual void SetStencilOp(int fail, int zFail, int zPass);
		// The slots 51 - 53 are the same for the counter-clockwise faces (0x106217E0, 0x10621830, 0x10621880)
		virtual void Unknown51(bool enable);
		virtual void Unknown52(int compare);
		virtual void Unknown53(int fail, int zFail, int zPass);
		virtual void SetFillMode(int mode);
		// Slot 60 sets the scissor test state (0x106219C0)
		virtual void EnableAlphaTest(bool enable);
		// Slots 62 and 63 set the slope scaled depth bias and the depth bias (0x10621A80, 0x10621A00)
		virtual void EnableFog(bool enable);
		virtual void SetFogRange(float nearZ, float farZ);

		unsigned char unknown634[0x638 - 0x634];
		// 0x638: the viewport the device is given (the depth range at +0x10 holds the bias of slot 41)
		D3DVIEWPORT9 viewport;
		unsigned char unknown650[0x65C - 0x650];
		// 0x65C / 0x660: what slot 24 hands out for the flags 0x400001 and 0x102
		pddiQuery* queryUnknown65C;
		pddiQuery* queryUnknown660;
		// 0x664: the shader a draw without one goes through
		dxShader* defaultShader;
		unsigned char unknown668[0x674 - 0x668];
		// 0x674 / 0x678: the size of the surface the device draws into
		unsigned int targetWidth;
		unsigned int targetHeight;
		// 0x67C: the colour write mask (red 1, green 2, blue 4, alpha 8)
		unsigned int colourWriteMask;
		// 0x680: set while the context draws into render targets of its own (not the back buffer)
		bool unknown680;
		// 0x681: set while the frame ends
		bool endingFrame;
		unsigned char unknown682[2];
		// 0x684 / 0x688: the two words of the depth bias
		float depthBiasSlope;
		float depthBias;
		unsigned char unknown68C[4];
		dxDrawTracker* tracker;
		int unknown694;
	};

	// 0x11276D70
	extern dxRenderStateCache* gRenderStateCache;
	// 0x11276D4C / 0x11276D50 / 0x11276D54 / 0x11276D58 / 0x11276D5C (dxdefaulttextures.cpp)
	extern dxTexture* gWhiteTexture;
	extern dxTexture* gBlackTexture;
	extern dxTexture* gTransparentTexture;
	extern dxTexture* gFlatNormalTexture;
	extern dxTexture* gRampTexture;
	// The Direct3D values of the pddi ones: the stencil operations (0x110BB6C4), the comparisons of the stencil
	// (0x110BB6DC) and of the z buffer (0x110BB6FC) and the fill modes (0x110BB71C); names are guesses
	extern int gD3DStencilOps[6];
	extern int gD3DStencilCompares[8];
	extern int gD3DZCompares[8];
	extern int gD3DFillModes[3];
	// 0x110BB750 / 0x110BB74C: the slope scaled depth bias and the depth bias EnableFog(true) sets
	extern int gDepthBiasSlopeOn;
	extern int gDepthBiasOn;
	// 0x106283E0 / 0x10628400: the Z fill technique's two programs (name guess)
	// 0x10625A80 / 0x106268F0: the resets the context keeps around a batch of draws (names unknown): they let go of
	// the streams and of the index buffer the device has set
	void Unknown10625A80();
	void Unknown106268F0();
	// 0x10613BF0 (the shader unit): forgets which shader the device last drew with
	void ResetShaderStamp();
	// 0x1062AE40: another reset at the end of a frame (name unknown)
	void Unknown1062AE40();
	// 0x11276DA8: the vertex buffer set on each stream of the device (name guess) and 0x11276DC8 how many streams
	// are set
	extern dxVertexBuffer* gBoundStreams[8];
	extern unsigned int gBoundStreamCount;
	// 0x10625930: the number of the device declaration for the elements of count streams (name guess)
	int BuildVertexDeclaration(dxVertexBuffer* const* streams, unsigned int count);
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

	// The shader templates of the device by the hash of their names (the nodes come from the global array new and
	// delete)
	struct ShaderTemplateAllocator
	{
		static void* Alloc(unsigned int size)
		{
			return operator new[](size);
		}
		static void Free(void* block)
		{
			operator delete[](block);
		}
	};
	typedef container::Map<unsigned int, dxShaderTemplate*, ShaderTemplateAllocator> ShaderTemplateMap;

	// The driver object the context starts the back end through (0x10 bytes, no virtual functions; RTTI-less, the
	// name is a guess; gPddiDx points at it). It makes the display it keeps at +8 and the 0x698-byte device context
	// at +0xC, and keeps the shader templates by name.
	class dxDevice
	{
	public:
		// 0x1061BA70: keeps the Direct3D object, makes the tree at +4 and records itself in 0x11276D30
		dxDevice(IDirect3D9* direct3D);
		// 0x1061BEC0 (0x1070EDD0 is its scalar deleting form, made in the context unit)
		~dxDevice();
		void* DeleteThis(unsigned int flags);
		// 0x1061B4C0: makes the display and the device context over the settings of the display
		void Initialize(const DisplaySettings* settings);
		// 0x1061B480 (it does not read the object): fills in the description of the device
		void GetVersion(void* version);
		// 0x1061B530 / 0x1061B540: the display and the device context (as the callers took them)
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
		// 0x1061BC00: the byte at +0x2E4 of the shader template of that name (false when there is none)
		bool Unknown1061BC00(const char* name);

		IDirect3D9* direct3D;    // +0
		ShaderTemplateMap* shaderTemplates;
		engine::Display* display;
		dxContext* context;
	};

	// 0x11276D40: the one driver object (0x1061BBC0 makes it)
	extern dxDevice* gDevice;
	// 0x10627FB0: counts the starts of the back end (the word at 0x11276F28; name unknown)
	void Unknown10627FB0();
}

#endif
