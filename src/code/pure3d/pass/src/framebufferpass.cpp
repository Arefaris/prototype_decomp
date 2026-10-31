// The frame buffer passes (unit around 0x107AD030 - 0x107B2D80; the file name is a guess). Names are guesses.
#include "code/core/refptr.h"
#include "code/engine/render/async/shaderparameter.h"
#include "code/pure3d/framebufferpass.h"

namespace pure3d
{
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

	// FUNCTION: ENGINE 0x107B04D0
	template pure3d::ParameterHandler<pure3d::ToneMapPass>::~ParameterHandler();

