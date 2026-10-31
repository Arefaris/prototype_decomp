// The frame buffer passes of pure3d (RTTI names pure3d::FrameBufferPass, ProtoMotherPass, ProtoThermalPass, ToneMapPass,
// ProtoToneMapPass, CopyPass and CapturePass): passes that draw the finished picture again with a pixel shader (post
// processing). Each one that has parameters keeps a ParameterHandler of its own class. Only what the reconstructed
// functions use is declared; names are guesses.
#ifndef PURE3D_FRAMEBUFFERPASS_H
#define PURE3D_FRAMEBUFFERPASS_H

#include "code/pure3d/parameterhandler.h"
#include "code/pure3d/pass.h"
#include "code/pure3d/pddi/dx9/dxtexture.h"
#include "code/pure3d/shader.h"
#include "code/pure3d/shaderconstants.h"

namespace pure3d
{

	// The texture of the passes (declared as far as the passes use it: the reference count is the entity's)
	class Texture : public Entity
	{
	};

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

	class ToneMapPass : public FrameBufferPass
	{
	public:
		// 0x1075DAF0 / 0x107AF3A0 (another unit)
		bool SetParameterEnable(bool value);

		unsigned char unknownE8[0x3C];
		ParameterHandler<ToneMapPass> parameters; // +0x130
	};
}

#endif
