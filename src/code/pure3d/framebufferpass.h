// The frame buffer passes of pure3d (RTTI names pure3d::FrameBufferPass, ProtoMotherPass, ProtoThermalPass, ToneMapPass,
// ProtoToneMapPass, CopyPass and CapturePass): passes that draw the finished picture again with a pixel shader (post
// processing). Each one that has parameters keeps a ParameterHandler of its own class. Only what the reconstructed
// functions use is declared; names are guesses.
#ifndef PURE3D_FRAMEBUFFERPASS_H
#define PURE3D_FRAMEBUFFERPASS_H

#include "code/pure3d/parameterhandler.h"
#include "code/pure3d/pass.h"
#include "code/pure3d/primitive.h"
#include "code/pure3d/pddi/dx9/dxtexture.h"
#include "code/pure3d/shader.h"
#include "code/pure3d/shaderconstants.h"

namespace pure3d
{

	// The names of the shaders of the passes (0x111BABA4 / 0x111BABA8 / 0x111BAC30 / 0x111BAC34; names guessed)
	extern const char* gShaderMother;
	extern const char* gShaderInfected;
	extern const char* gShaderThermal;
	extern const char* gShaderObjThermal;

	// Draws the picture again with a shader; keeps a stack of shaders (the one in use is at +0xC0) and six textures
	class FrameBufferPass : public Pass
	{
	public:
		// 0x107AD070 (the description is not used here)
		explicit FrameBufferPass(const PassDesc* desc);
		// Slot 0 (the body is 0x107AD120, the deleting destructor 0x107AD190)
		virtual ~FrameBufferPass();

		// 0x107ACE10: makes the shader the one in use (the one in use goes on the stack); 0x107ACE50: takes the
		// shader on top of the stack back into use
		void PushShader(Shader* newShader);
		void PopShader();
		// 0x107AC500: holds the texture in the slot; 0x107AC520: lets go of all six
		void SetTexture(dxTexture* texture, int slot);
		void ReleaseTextures();

		Shader** shaderStack;         // +0xB0
		Shader** shaderStackEnd;      // +0xB4
		Shader** shaderStackCapacity; // +0xB8
		unsigned char unknownBC[4];
		Shader* shader;               // +0xC0
		void* unknownC4;
		bool unknownC8;
		core::Name<core::CaseInsensitiveKey32> shaderName; // +0xCC
		dxTexture* textures[6];       // +0xD0
	};

	// The pass that turns the picture to the "mother" look and the pass that shows heat (vftables 0x10E63EAC and
	// 0x10E63F28; the layouts are the same, the shaders and the constant differ)
	class ProtoMotherPass : public FrameBufferPass
	{
	public:
		// 0x107ADF20
		explicit ProtoMotherPass(const PassDesc* desc);
		// Slot 0 (the body is 0x107ADE80, the deleting destructor 0x107ADFF0)
		virtual ~ProtoMotherPass();

		// Slot 2 (0x107AD360): the handler the pass keeps
		virtual ParameterHandlerTypeless* GetParameterHandler();
		// Slot 4 (0x107AD630) and slot 7 (0x107AD230)
		virtual void Render(PassContext* context);
		virtual bool IsVisible();
		// Slot 5 (0x107AD340): runs the visibility test once before the first Run
		virtual void Begin();

		// 0x107AD1D0 / 0x107AD1E0: the textures the pass reads
		void SetUnknownF4(int value);
		void SetTextures(Texture* first, Texture* second, Texture* third);
		// 0x1075DAF0 (another unit)
		bool SetParameterEnable(bool value);

		Texture* textureE8;
		Texture* textureEC;
		Texture* textureF0;
		int unknownF4;
		float valueF8;
		float valueFC;
		Shader* shaderObject; // +0x100
		ParameterHandler<ProtoMotherPass> parameters; // +0x104
	};

	class ProtoThermalPass : public FrameBufferPass
	{
	public:
		// 0x107AEF10
		explicit ProtoThermalPass(const PassDesc* desc);
		// Slot 0 (the body is 0x107AEE70, the deleting destructor 0x107AEFE0)
		virtual ~ProtoThermalPass();

		// Slot 2 (0x107AE1A0): the handler the pass keeps
		virtual ParameterHandlerTypeless* GetParameterHandler();
		// Slot 4 (0x107AE470) and slot 7 (0x107AE070)
		virtual void Render(PassContext* context);
		virtual bool IsVisible();
		// Slot 5 (0x107AE180)
		virtual void Begin();

		// 0x107AE010 / 0x107AE020
		void SetUnknownF4(int value);
		void SetTextures(Texture* first, Texture* second, Texture* third);
		// 0x1075DAF0 (another unit)
		bool SetParameterEnable(bool value);

		Texture* textureE8;
		Texture* textureEC;
		Texture* textureF0;
		int unknownF4;
		float valueF8;
		float valueFC;
		Shader* shaderObject; // +0x100
		ParameterHandler<ProtoThermalPass> parameters; // +0x104
	};

	// A list of textures made with operator new[] (begin, end of the used part, end of the room)
	struct TextureList
	{
		TextureList()
		{
			begin = 0;
			end = 0;
			capacity = 0;
		}
		~TextureList()
		{
			end = begin;
			if (begin != 0)
			{
				operator delete[](begin);
			}
		}

		Texture** begin;
		Texture** end;
		Texture** capacity;
	};

	// Maps the picture's brightness (vftable 0x10E64004; ProtoToneMapPass derives from it)
	class ToneMapPass : public FrameBufferPass
	{
	public:
		// 0x107B0610
		explicit ToneMapPass(const PassDesc* desc);
		// Slot 0 (the body is 0x107B04F0, the deleting destructor 0x107B0830)
		virtual ~ToneMapPass();

		// Slot 1 (0x107AF220): remembers that the state changed
		virtual void SetEnabled(bool enabled);
		// Slot 2 (0x107AF2C0)
		virtual ParameterHandlerTypeless* GetParameterHandler();
		// Slot 4 (0x107AF770), 5 (0x107AF5C0), 6 (0x107B0180), 7 (0x107AF010)
		virtual void Render(PassContext* context);
		virtual void Begin();
		virtual void End();
		virtual bool IsVisible();

		// 0x107AF250 / 0x107AF260 / 0x107AF270 / 0x107AF290
		float GetUnknown100();
		float GetUnknownFC();
		void SetUnknownFC100(float second, float first);
		void SetUnknown104(float first, float second, float third);
		// 0x107AF3B0: the texture the pass reads (the global at 0x111BACE0 says which of the list, -1 the first)
		dxTexture* GetSource();

		Shader* shaderE8;
		Shader* shaderEC;
		Shader* shaderF0;
		Shader* shaderF4;
		Shader* shaderF8;
		float unknownFC;
		float unknown100;
		float unknown104;
		float unknown108;
		float unknown10C;
		int unknown110;
		bool unknown114;
		unsigned char unknown115[3];
		Texture* texture118;
		Texture* texture11C;
		TextureList textures;       // +0x120
		unsigned char unknown12C[4];
		ParameterHandler<ToneMapPass> parameters; // +0x130
	};

	// 0x11281490 / 0x11281478 / 0x112814A8 / 0x11281488 / 0x11281438: the names of the tone map pass's variable parameters (the
	// floats at +0x100, +0xFC, +0x10C, +0x104 and +0x108; names guessed)
	extern core::Name<core::CaseSensitiveKey> gToneMapName100;
	extern core::Name<core::CaseSensitiveKey> gToneMapNameFC;
	extern core::Name<core::CaseSensitiveKey> gToneMapName10C;
	extern core::Name<core::CaseSensitiveKey> gToneMapName104;
	extern core::Name<core::CaseSensitiveKey> gToneMapName108;

	// 0x111BACE0: which texture of the tone map pass's list is the source (-1: the one at +0x11C)
	extern int gToneMapSourceIndex;

	// Draws the translucent parts (vftable 0x10E642B4)
	class TranslucentPass : public Pass
	{
	public:
		// 0x107B1AD0
		explicit TranslucentPass(const PassDesc* desc);
		// Slot 0 (the body is 0x107B1B20, the deleting destructor 0x107B1B50)
		virtual ~TranslucentPass();
		// Slot 4 (0x107B2410)
		virtual void Render(PassContext* context);
	};

	// Copies the picture (vftable 0x10E64044)
	class CopyPass : public FrameBufferPass
	{
	public:
		// 0x107B0990
		explicit CopyPass(const PassDesc* desc);
		// Slot 0 (the body is 0x107B0850, the deleting destructor 0x107B0A30)
		virtual ~CopyPass();
		// Slot 4 (0x107B0860)
		virtual void Render(PassContext* context);
	};

	// 0x11281440 / 0x112815E8: the names of the capture pass's parameters (names guessed)
	extern core::Name<core::CaseSensitiveKey> gCaptureColour;
	extern core::Name<core::CaseSensitiveKey> gCaptureAmount;

	// A colour word as the capture pass copies it: assembled channel by channel (the engine's copy of a pddiColour)
	struct PassColour
	{
		PassColour()
		{
		}
		PassColour(const PassColour& other)
		{
			bits = (((other.a << 8 | other.r) << 8) | other.g) << 8 | other.b;
		}
		PassColour& operator=(const PassColour& other)
		{
			bits = (((other.a << 8 | other.r) << 8) | other.g) << 8 | other.b;
			return *this;
		}

		union
		{
			unsigned int bits;
			struct
			{
				unsigned int b : 8;
				unsigned int g : 8;
				unsigned int r : 8;
				unsigned int a : 8;
			};
		};
	};

	// Copies the picture to a texture (vftable 0x10E642F8, eleven slots; ProtoCapturePass derives from it)
	class CapturePass : public Pass
	{
	public:
		// 0x107B2CC0 (the colour and the second word come from the description)
		explicit CapturePass(const PassDesc* desc);
		// Slot 0 (the body is 0x107B2C60, the deleting destructor 0x107B2D60)
		virtual ~CapturePass();

		// Slot 2 (0x107B2470)
		virtual ParameterHandlerTypeless* GetParameterHandler();
		// Slot 4 (0x107B2480)
		virtual void Render(PassContext* context);
		// Slots 9 and 10 (0x107B2430, 0x107B2460): the parameters the handler registers
		virtual void SetColour(const unsigned int* newColour);
		virtual void SetUnknownB4(unsigned int value);

		PassColour colour;        // +0xB0
		unsigned int unknownB4;
		ParameterHandler<CapturePass> parameters; // +0xB8
		unsigned char unknownFC[4];
	};
}

#endif
