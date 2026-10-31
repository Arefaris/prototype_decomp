// The frame buffer passes (unit around 0x107AD030 - 0x107B2D80; the file name is a guess). Names are guesses.
#include "code/core/refptr.h"
#include "code/engine/render/async/shaderparameter.h"
#include "code/pure3d/framebufferpass.h"
#include "code/pure3d/protopass.h"
#include "code/pure3d/shadows/shadowrendermanager.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"

namespace pure3d
{
	const char* gShaderMother = "pp_mother";
	const char* gShaderInfected = "pp_obj_infected";
	const char* gShaderThermal = "pp_thermal";
	const char* gShaderObjThermal = "pp_obj_thermal";

	// FUNCTION: ENGINE 0x107AC500
	void FrameBufferPass::SetTexture(dxTexture* texture, int slot)
	{
		AssignRef(&textures[slot], texture);
	}

	// FUNCTION: ENGINE 0x107AC520
	void FrameBufferPass::ReleaseTextures()
	{
		for (int i = 0; i < 6; i++)
		{
			ReleaseRef(&textures[i]);
		}
	}

	// FUNCTION: ENGINE 0x107ACE10
	void FrameBufferPass::PushShader(Shader* newShader)
	{
		if (shaderStackEnd < shaderStackCapacity)
		{
			Shader** item = shaderStackEnd++;
			if (item != 0)
			{
				*item = shader;
			}
		}
		shader = newShader;
		newShader->AddRef();
	}

	// FUNCTION: ENGINE 0x107ACE50
	// EQUIVALENT: the same operations in the same order; the engine copies the loaded end pointer into another register
	// for the decrement, ours computes the decremented pointer at the load (60.9 %)
	void FrameBufferPass::PopShader()
	{
		if (shaderStack != shaderStackEnd)
		{
			core::SafeRelease(shader);
			Shader** top = shaderStackEnd;
			shader = top[-1];
			if (shaderStack != top)
			{
				shaderStackEnd = top - 1;
			}
		}
	}

	// FUNCTION: ENGINE 0x107AD070
	// EQUIVALENT: scheduling only (the engine stores the vftable pointer first and pushes the name's address between the
	// first stores, ours pushes it at the start; 88.3 %)
	FrameBufferPass::FrameBufferPass(const PassDesc* desc) : Pass(desc), shaderStack(0), shaderStackEnd(0),
		shaderStackCapacity(0), shader(0), unknownC4(0), unknownC8(false), shaderName(gShaderLit)
	{
		for (int i = 0; i < 6; i++)
		{
			textures[i] = 0;
		}
		shaderStack = (Shader**)operator new[](0x40);
		if (shaderStack != 0)
		{
			shaderStackEnd = shaderStack;
			shaderStackCapacity = shaderStack + 16;
			return;
		}
		shaderStackEnd = 0;
		shaderStackCapacity = 0;
	}

	// FUNCTION: ENGINE 0x107AD120
	// EQUIVALENT: scheduling only (the vftable pointer store sits before the first load in the engine; 89.9 %)
	FrameBufferPass::~FrameBufferPass()
	{
		while (shaderStack != shaderStackEnd)
		{
			PopShader();
		}
		core::SafeRelease(shader);
		ReleaseTextures();
		shaderStackEnd = shaderStack;
		if (shaderStack != 0)
		{
			operator delete[](shaderStack);
		}
	}
}


namespace pure3d
{
	// FUNCTION: ENGINE 0x107AD360
	ParameterHandlerTypeless* ProtoMotherPass::GetParameterHandler()
	{
		return &parameters;
	}

	// FUNCTION: ENGINE 0x107AD230
	bool ProtoMotherPass::IsVisible()
	{
		if (GetUnknown24Bit1())
		{
			return true;
		}
		if (unknownF4 == 0)
		{
			return false;
		}
		bool ready = true;
		if (shader == 0)
		{
			if (gPddiDx->Unknown1061BC00(gShaderMother))
			{
				shader = new Shader(gShaderMother);
				shader->AddRef();
			}
			else
			{
				ready = false;
			}
		}
		if (shaderObject == 0)
		{
			if (gPddiDx->Unknown1061BC00(gShaderInfected))
			{
				shaderObject = new Shader(gShaderInfected);
				shaderObject->AddRef();
			}
			else
			{
				ready = false;
			}
		}
		unknown24Bit1 = ready;
		return ready;
	}

	// FUNCTION: ENGINE 0x107AD1D0
	void ProtoMotherPass::SetUnknownF4(int value)
	{
		unknownF4 = value;
	}

	// FUNCTION: ENGINE 0x107AD1E0
	void ProtoMotherPass::SetTextures(Texture* first, Texture* second, Texture* third)
	{
		textureE8 = first;
		textureEC = second;
		textureF0 = third;
		first->AddRef();
		textureEC->AddRef();
		textureF0->AddRef();
	}

	// FUNCTION: ENGINE 0x107AD340
	void ProtoMotherPass::Begin()
	{
		if (!GetUnknown24Bit1())
		{
			CallIsVisible();
		}
		begun = 1;
	}

	// FUNCTION: ENGINE 0x107ADE80
	ProtoMotherPass::~ProtoMotherPass()
	{
		core::SafeRelease(shaderObject);
		core::SafeRelease(textureE8);
		core::SafeRelease(textureEC);
		core::SafeRelease(textureF0);
	}

	// FUNCTION: ENGINE 0x107ADF20
	ProtoMotherPass::ProtoMotherPass(const PassDesc* desc) : FrameBufferPass(desc), textureE8(0), textureEC(0),
		textureF0(0), unknownF4(0), valueF8(3.0f), valueFC(3.0f), shaderObject(0)
	{
		parameters.object = this;
		parameters.AddBool(&engine::render::gParameterEnable, &ProtoMotherPass::SetParameterEnable, 0);
		entries.SetWord(1);
		entries.AddEntry(2, false);
		entries.AddEntry(1, false);
		entries.AddEntry(0x17, true);
		entries.AddEntry(0xF, false);
	}

	// FUNCTION: ENGINE 0x107AE1A0
	ParameterHandlerTypeless* ProtoThermalPass::GetParameterHandler()
	{
		return &parameters;
	}

	// FUNCTION: ENGINE 0x107AE070
	bool ProtoThermalPass::IsVisible()
	{
		if (GetUnknown24Bit1())
		{
			return true;
		}
		if (unknownF4 == 0)
		{
			return false;
		}
		bool ready = true;
		if (shader == 0)
		{
			if (gPddiDx->Unknown1061BC00(gShaderThermal))
			{
				shader = new Shader(gShaderThermal);
				shader->AddRef();
			}
			else
			{
				ready = false;
			}
		}
		if (shaderObject == 0)
		{
			if (gPddiDx->Unknown1061BC00(gShaderObjThermal))
			{
				shaderObject = new Shader(gShaderObjThermal);
				shaderObject->AddRef();
			}
			else
			{
				ready = false;
			}
		}
		unknown24Bit1 = ready;
		return ready;
	}

	// FUNCTION: ENGINE 0x107AE010
	void ProtoThermalPass::SetUnknownF4(int value)
	{
		unknownF4 = value;
	}

	// FUNCTION: ENGINE 0x107AE020
	void ProtoThermalPass::SetTextures(Texture* first, Texture* second, Texture* third)
	{
		textureE8 = first;
		textureEC = second;
		textureF0 = third;
		first->AddRef();
		textureEC->AddRef();
		textureF0->AddRef();
	}

	// FUNCTION: ENGINE 0x107AE180
	void ProtoThermalPass::Begin()
	{
		if (!GetUnknown24Bit1())
		{
			CallIsVisible();
		}
		begun = 1;
	}

	// FUNCTION: ENGINE 0x107AEE70
	ProtoThermalPass::~ProtoThermalPass()
	{
		core::SafeRelease(shaderObject);
		core::SafeRelease(textureE8);
		core::SafeRelease(textureEC);
		core::SafeRelease(textureF0);
	}

	// FUNCTION: ENGINE 0x107AEF10
	ProtoThermalPass::ProtoThermalPass(const PassDesc* desc) : FrameBufferPass(desc), textureE8(0), textureEC(0),
		textureF0(0), unknownF4(0), valueF8(7.0f), valueFC(7.0f), shaderObject(0)
	{
		parameters.object = this;
		parameters.AddBool(&engine::render::gParameterEnable, &ProtoThermalPass::SetParameterEnable, 0);
		entries.SetWord(1);
		entries.AddEntry(2, false);
		entries.AddEntry(1, false);
		entries.AddEntry(0x17, true);
		entries.AddEntry(0xF, false);
	}
}

namespace pure3d
{
	// FUNCTION: ENGINE 0x107B2430
	void CapturePass::SetColour(const unsigned int* newColour)
	{
		colour = *(const PassColour*)newColour;
	}

	// FUNCTION: ENGINE 0x107B2460
	void CapturePass::SetUnknownB4(unsigned int value)
	{
		unknownB4 = value;
	}

	// FUNCTION: ENGINE 0x107B2470
	ParameterHandlerTypeless* CapturePass::GetParameterHandler()
	{
		return &parameters;
	}

	// FUNCTION: ENGINE 0x107B2C60
	CapturePass::~CapturePass()
	{
	}

	// FUNCTION: ENGINE 0x107B2CC0
	CapturePass::CapturePass(const PassDesc* desc) : Pass(desc), colour(*(const PassColour*)((const unsigned char*)desc + 0x18)),
		unknownB4(*(const unsigned int*)((const unsigned char*)desc + 0x1C))
	{
		parameters.object = this;
		parameters.AddColour(&gCaptureColour, &CapturePass::SetColour, 0);
		parameters.AddUnsigned(&gCaptureAmount, &CapturePass::SetUnknownB4, 0);
	}
}

namespace pure3d
{
	unsigned int gShadowLightCapacity = 0x200;

	// FUNCTION: ENGINE 0x107B0850
	CopyPass::~CopyPass()
	{
	}

	// FUNCTION: ENGINE 0x107B0A80
	bool ShadowPass::IsVisible()
	{
		if (!GetUnknown24Bit1())
		{
			ShadowRenderManager::Get()->Unknown10715D60();
			unknown24Bit1 = 1;
		}
		return true;
	}

	// FUNCTION: ENGINE 0x107B12A0
	// EQUIVALENT: scheduling only (the vftable store sits right after the base constructor call in the engine, after the
	// first register set-up in ours; 75.1 %)
	ShadowPass::ShadowPass(const PassDesc* desc) : Pass(desc)
	{
		entries.SetWord(1);
		entries.AddEntry(2, false);
		entries.AddEntry(1, false);
		entries.AddEntry(7, false);
		entries.AddEntry(6, false);
		shadowEntries.SetWord(1);
		shadowEntries.AddEntry(2, false);
		shadowEntries.AddEntry(1, false);
		shadowEntries.AddEntry(7, false);
		shadowEntries.AddEntry(6, false);
		shadowEntries.AddEntry(9, true);
		if (gShadowLightCapacity == 0)
		{
			lights.begin = 0;
		}
		else
		{
			unsigned int size = gShadowLightCapacity * 4;
			lights.begin = (Light**)operator new[](size);
			if (lights.begin != 0)
			{
				lights.capacity = (Light**)((unsigned char*)lights.begin + size);
				lights.end = lights.begin;
				return;
			}
		}
		lights.end = 0;
		lights.capacity = 0;
	}

	// FUNCTION: ENGINE 0x107B13A0
	ShadowPass::~ShadowPass()
	{
	}

	// FUNCTION: ENGINE 0x107B1AD0
	TranslucentPass::TranslucentPass(const PassDesc* desc) : Pass(desc)
	{
		entries.SetWord(1);
		entries.AddEntry(2, false);
		entries.AddEntry(1, false);
		entries.AddEntry(7, true);
	}

	// FUNCTION: ENGINE 0x107B1B20
	TranslucentPass::~TranslucentPass()
	{
	}
}

namespace pure3d
{
	int gToneMapSourceIndex = -1;

	// FUNCTION: ENGINE 0x107B04F0
	ToneMapPass::~ToneMapPass()
	{
		core::SafeRelease(shaderF0);
		core::SafeRelease(shaderEC);
		core::SafeRelease(shaderF4);
		core::SafeRelease(shaderE8);
		core::SafeRelease(shaderF8);
		core::SafeRelease(texture118);
		core::SafeRelease(texture11C);
		for (unsigned int i = 0; i < (unsigned int)(textures.end - textures.begin); i++)
		{
			core::SafeRelease(textures.begin[i]);
		}
		textures.end = textures.begin;
	}

	// FUNCTION: ENGINE 0x107B0610
	ToneMapPass::ToneMapPass(const PassDesc* desc) : FrameBufferPass(desc), shaderE8(0), shaderEC(0), shaderF0(0),
		shaderF4(0), shaderF8(0), unknownFC(0.18f), unknown100(30.0f), unknown104(1.0f), unknown108(2.5f),
		unknown10C(1.0f), unknown110(0), unknown114(true), texture118(0), texture11C(0)
	{
		parameters.object = this;
		parameters.AddBool(&engine::render::gParameterEnable, (bool (ToneMapPass::*)(bool))&ToneMapPass::SetEnabled, 0);
		parameters.parameters.At(&gToneMapName100) = ParameterValue(&unknown100);
		parameters.parameters.At(&gToneMapNameFC) = ParameterValue(&unknownFC);
		parameters.parameters.At(&gToneMapName10C) = ParameterValue(&unknown10C);
		parameters.parameters.At(&gToneMapName104) = ParameterValue(&unknown104);
		parameters.parameters.At(&gToneMapName108) = ParameterValue(&unknown108);
		textures.begin = (Texture**)operator new[](0x30);
		if (textures.begin != 0)
		{
			textures.end = textures.begin;
			textures.capacity = textures.begin + 12;
			return;
		}
		textures.end = 0;
		textures.capacity = 0;
	}

	// FUNCTION: ENGINE 0x107AF220
	void ToneMapPass::SetEnabled(bool enabled)
	{
		// The engine compares the byte IsActive answers (its result is a bool here)
		bool (Pass::*isActive)(bool) = (bool (Pass::*)(bool))&Pass::IsActive;
		if (enabled != (this->*isActive)(false))
		{
			unknown114 = true;
		}
		Pass::SetEnabled(enabled);
	}

	// FUNCTION: ENGINE 0x107AF250
	float ToneMapPass::GetUnknown100()
	{
		return unknown100;
	}

	// FUNCTION: ENGINE 0x107AF260
	float ToneMapPass::GetUnknownFC()
	{
		return unknownFC;
	}

	// FUNCTION: ENGINE 0x107AF270
	void ToneMapPass::SetUnknownFC100(float second, float first)
	{
		unknownFC = first;
		unknown100 = second;
	}

	// FUNCTION: ENGINE 0x107AF290
	void ToneMapPass::SetUnknown104(float first, float second, float third)
	{
		unknown10C = third;
		unknown108 = second;
		unknown104 = first;
	}

	// FUNCTION: ENGINE 0x107AF2C0
	ParameterHandlerTypeless* ToneMapPass::GetParameterHandler()
	{
		return &parameters;
	}

	// FUNCTION: ENGINE 0x107AF3B0
	dxTexture* ToneMapPass::GetSource()
	{
		if (gToneMapSourceIndex == -1)
		{
			return texture11C->info;
		}
		return textures.begin[gToneMapSourceIndex]->info;
	}

	// FUNCTION: ENGINE 0x107B0180
	void ToneMapPass::End()
	{
		for (unsigned int i = 0; i < (unsigned int)(textures.end - textures.begin); i++)
		{
			core::SafeRelease(textures.begin[i]);
		}
		textures.end = textures.begin;
		core::SafeRelease(texture11C);
		core::SafeRelease(texture118);
	}
}
	// FUNCTION: ENGINE 0x107AD390
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Pair::Pair(const core::Name<core::CaseSensitiveKey>&, const pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry&);

	// FUNCTION: ENGINE 0x107AD3C0
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Iterator::operator!=(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Iterator&) const;

	// FUNCTION: ENGINE 0x107AD3E0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Pair& container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Iterator::operator*() const;

	// FUNCTION: ENGINE 0x107AD3F0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Pair::Pair(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x107ADA60
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Map(pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator);

	// FUNCTION: ENGINE 0x107ADA70
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Pair* container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Iterator::operator->() const;

	// FUNCTION: ENGINE 0x107ADA80
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::MapNode::MapNode(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x107ADAC0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Iterator::Iterator(container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::MapNode*, container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>*);

	// FUNCTION: ENGINE 0x107ADB00
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::End();

	// FUNCTION: ENGINE 0x107ADB20
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::CompareNodes(const container::TreeBase::Node*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x107ADB60
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::CompareKey(const void*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x107ADBA0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Insert(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x107ADC10
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Find(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x107ADC40
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::DeleteNode(container::TreeBase::Node*, void*);

	// FUNCTION: ENGINE 0x107ADC50
	template pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry& pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryMap::At(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x107ADCC0
	template bool pure3d::ParameterHandler<pure3d::ProtoMotherPass>::SetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool);

	// FUNCTION: ENGINE 0x107ADD20
	template bool pure3d::ParameterHandler<pure3d::ProtoMotherPass>::GetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool*);

	// FUNCTION: ENGINE 0x107ADDA0
	template void container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::Clear();

	// FUNCTION: ENGINE 0x107ADDB0
	template void pure3d::ParameterHandler<pure3d::ProtoMotherPass>::AddBool(const core::Name<core::CaseSensitiveKey>*, bool (pure3d::ProtoMotherPass::*)(bool), bool (pure3d::ProtoMotherPass::*)());

	// FUNCTION: ENGINE 0x107ADE20
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoMotherPass>::EntryAllocator>::~Map();

	// FUNCTION: ENGINE 0x107ADE30
	template pure3d::ParameterHandler<pure3d::ProtoMotherPass>::ParameterHandler();

	// FUNCTION: ENGINE 0x107AD370
	template void pure3d::ParameterHandler<pure3d::ProtoMotherPass>::SetObject(pure3d::ProtoMotherPass*);

	// FUNCTION: ENGINE 0x107ADE60
	template pure3d::ParameterHandler<pure3d::ProtoMotherPass>::~ParameterHandler();

	// FUNCTION: ENGINE 0x107AE1D0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Pair::Pair(const core::Name<core::CaseSensitiveKey>&, const pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry&);

	// FUNCTION: ENGINE 0x107AE200
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Iterator::operator!=(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Iterator&) const;

	// FUNCTION: ENGINE 0x107AE220
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Pair& container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Iterator::operator*() const;

	// FUNCTION: ENGINE 0x107AE230
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Pair::Pair(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x107AEA50
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Map(pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator);

	// FUNCTION: ENGINE 0x107AEA60
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Pair* container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Iterator::operator->() const;

	// FUNCTION: ENGINE 0x107AEA70
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::MapNode::MapNode(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x107AEAB0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Iterator::Iterator(container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::MapNode*, container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>*);

	// FUNCTION: ENGINE 0x107AEAF0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::End();

	// FUNCTION: ENGINE 0x107AEB10
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::CompareNodes(const container::TreeBase::Node*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x107AEB50
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::CompareKey(const void*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x107AEB90
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Insert(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x107AEC00
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Find(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x107AEC30
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::DeleteNode(container::TreeBase::Node*, void*);

	// FUNCTION: ENGINE 0x107AEC40
	template pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry& pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryMap::At(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x107AECB0
	template bool pure3d::ParameterHandler<pure3d::ProtoThermalPass>::SetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool);

	// FUNCTION: ENGINE 0x107AED10
	template bool pure3d::ParameterHandler<pure3d::ProtoThermalPass>::GetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool*);

	// FUNCTION: ENGINE 0x107AED90
	template void container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::Clear();

	// FUNCTION: ENGINE 0x107AEDA0
	template void pure3d::ParameterHandler<pure3d::ProtoThermalPass>::AddBool(const core::Name<core::CaseSensitiveKey>*, bool (pure3d::ProtoThermalPass::*)(bool), bool (pure3d::ProtoThermalPass::*)());

	// FUNCTION: ENGINE 0x107AEE10
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoThermalPass>::EntryAllocator>::~Map();

	// FUNCTION: ENGINE 0x107AEE20
	template pure3d::ParameterHandler<pure3d::ProtoThermalPass>::ParameterHandler();

	// FUNCTION: ENGINE 0x107AE1B0
	template void pure3d::ParameterHandler<pure3d::ProtoThermalPass>::SetObject(pure3d::ProtoThermalPass*);

	// FUNCTION: ENGINE 0x107AEE50
	template pure3d::ParameterHandler<pure3d::ProtoThermalPass>::~ParameterHandler();

	// FUNCTION: ENGINE 0x107AF2F0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Pair::Pair(const core::Name<core::CaseSensitiveKey>&, const pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry&);

	// FUNCTION: ENGINE 0x107AF320
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Iterator::operator!=(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Iterator&) const;

	// FUNCTION: ENGINE 0x107AF340
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Pair& container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Iterator::operator*() const;

	// FUNCTION: ENGINE 0x107AF350
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Pair::Pair(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x107AF540
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Map(pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator);

	// FUNCTION: ENGINE 0x107AF550
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Pair* container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Iterator::operator->() const;

	// FUNCTION: ENGINE 0x107AF560
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::MapNode::MapNode(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x107AF5A0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Iterator::Iterator(container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::MapNode*, container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>*);

	// FUNCTION: ENGINE 0x107B00F0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::End();

	// FUNCTION: ENGINE 0x107B0110
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::CompareNodes(const container::TreeBase::Node*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x107B0150
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::CompareKey(const void*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x107B0210
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Insert(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x107B0280
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Find(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x107B02B0
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::DeleteNode(container::TreeBase::Node*, void*);

	// FUNCTION: ENGINE 0x107B02C0
	template pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry& pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryMap::At(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x107B0330
	template bool pure3d::ParameterHandler<pure3d::ToneMapPass>::SetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool);

	// FUNCTION: ENGINE 0x107B0390
	template bool pure3d::ParameterHandler<pure3d::ToneMapPass>::GetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool*);

	// FUNCTION: ENGINE 0x107B0410
	template void container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::Clear();

	// FUNCTION: ENGINE 0x107B0420
	template void pure3d::ParameterHandler<pure3d::ToneMapPass>::AddBool(const core::Name<core::CaseSensitiveKey>*, bool (pure3d::ToneMapPass::*)(bool), bool (pure3d::ToneMapPass::*)());

	// FUNCTION: ENGINE 0x107B0490
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ToneMapPass>::Entry, pure3d::ParameterHandler<pure3d::ToneMapPass>::EntryAllocator>::~Map();

	// FUNCTION: ENGINE 0x107B04A0
	template pure3d::ParameterHandler<pure3d::ToneMapPass>::ParameterHandler();

	// FUNCTION: ENGINE 0x107AF2D0
	template void pure3d::ParameterHandler<pure3d::ToneMapPass>::SetObject(pure3d::ToneMapPass*);

	// FUNCTION: ENGINE 0x107B04D0
	template pure3d::ParameterHandler<pure3d::ToneMapPass>::~ParameterHandler();

	// FUNCTION: ENGINE 0x107B2600
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Pair::Pair(const core::Name<core::CaseSensitiveKey>&, const pure3d::ParameterHandler<pure3d::CapturePass>::Entry&);

	// FUNCTION: ENGINE 0x107B2630
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Iterator::operator!=(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Iterator&) const;

	// FUNCTION: ENGINE 0x107B2650
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Pair& container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Iterator::operator*() const;

	// FUNCTION: ENGINE 0x107B2660
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Pair::Pair(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x107B26E0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Map(pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator);

	// FUNCTION: ENGINE 0x107B26F0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Pair* container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Iterator::operator->() const;

	// FUNCTION: ENGINE 0x107B2700
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::MapNode::MapNode(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x107B2740
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Iterator::Iterator(container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::MapNode*, container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>*);

	// FUNCTION: ENGINE 0x107B2780
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::End();

	// FUNCTION: ENGINE 0x107B27A0
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::CompareNodes(const container::TreeBase::Node*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x107B27E0
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::CompareKey(const void*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x107B2820
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Insert(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x107B2890
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Find(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x107B28C0
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::DeleteNode(container::TreeBase::Node*, void*);

	// FUNCTION: ENGINE 0x107B28D0
	template pure3d::ParameterHandler<pure3d::CapturePass>::Entry& pure3d::ParameterHandler<pure3d::CapturePass>::EntryMap::At(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x107B2B10
	template void container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::Clear();

	// FUNCTION: ENGINE 0x107B2C00
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::CapturePass>::Entry, pure3d::ParameterHandler<pure3d::CapturePass>::EntryAllocator>::~Map();

	// FUNCTION: ENGINE 0x107B2C10
	template pure3d::ParameterHandler<pure3d::CapturePass>::ParameterHandler();

	// FUNCTION: ENGINE 0x107B25E0
	template void pure3d::ParameterHandler<pure3d::CapturePass>::SetObject(pure3d::CapturePass*);

	// FUNCTION: ENGINE 0x107B2940
	template bool pure3d::ParameterHandler<pure3d::CapturePass>::SetUnsignedAdapter(void*, const core::Name<core::CaseSensitiveKey>*, unsigned int);

	// FUNCTION: ENGINE 0x107B2A00
	template bool pure3d::ParameterHandler<pure3d::CapturePass>::GetUnsignedAdapter(void*, const core::Name<core::CaseSensitiveKey>*, unsigned int*);

	// FUNCTION: ENGINE 0x107B29A0
	template bool pure3d::ParameterHandler<pure3d::CapturePass>::SetColourAdapter(void*, const core::Name<core::CaseSensitiveKey>*, const unsigned int*);

	// FUNCTION: ENGINE 0x107B2A80
	template bool pure3d::ParameterHandler<pure3d::CapturePass>::GetColourAdapter(void*, const core::Name<core::CaseSensitiveKey>*, unsigned int*);

	// FUNCTION: ENGINE 0x107B2B90
	template void pure3d::ParameterHandler<pure3d::CapturePass>::AddUnsigned(const core::Name<core::CaseSensitiveKey>*, void (pure3d::CapturePass::*)(unsigned int), unsigned int (pure3d::CapturePass::*)());

	// FUNCTION: ENGINE 0x107B2B20
	template void pure3d::ParameterHandler<pure3d::CapturePass>::AddColour(const core::Name<core::CaseSensitiveKey>*, void (pure3d::CapturePass::*)(const unsigned int*), pure3d::ColourResult (pure3d::CapturePass::*)());

	// FUNCTION: ENGINE 0x107B2C40
	template pure3d::ParameterHandler<pure3d::CapturePass>::~ParameterHandler();

namespace pure3d
{
	core::Name<core::CaseSensitiveKey> gToneMapName100("adapt_rate", 0);
	core::Name<core::CaseSensitiveKey> gToneMapNameFC("average_luminance", 0);
	core::Name<core::CaseSensitiveKey> gToneMapName104("min", 0);
	core::Name<core::CaseSensitiveKey> gToneMapName108("max", 0);
	core::Name<core::CaseSensitiveKey> gToneMapName10C("exposure_power", 0);
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D720D0
// FUNCTION: ENGINE 0x10D720F0
// FUNCTION: ENGINE 0x10D72110
// FUNCTION: ENGINE 0x10D72130
// FUNCTION: ENGINE 0x10D72150
// FUNCTION: ENGINE 0x10D892E0
// FUNCTION: ENGINE 0x10D892F0
// FUNCTION: ENGINE 0x10D89300
// FUNCTION: ENGINE 0x10D89310
// FUNCTION: ENGINE 0x10D89320
