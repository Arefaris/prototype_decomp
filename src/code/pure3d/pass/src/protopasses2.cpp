// The small passes of the render pipeline and the constructors and destructors of the others (0x10764D20 - 0x10775000;
// the file name is a guess, the units of this range are not told apart). Names are guesses.
#include "code/core/refptr.h"
#include "code/engine/render/async/shaderparameter.h"
#include "code/math/pddicolour.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/framebufferpass.h"
#include "code/pure3d/primitive.h"
#include "code/pure3d/protopass.h"
#include "code/pure3d/renderscheme.h"
#include "code/pure3d/scene.h"
#include "code/pure3d/shader.h"
#include "code/pure3d/shaderconstants.h"

namespace pure3d
{
	// 0x11280D98: the texture constant the light decal buffer is bound to (name guessed)
	extern int gConstantLightDecalBuffer;

	namespace
	{
		// Binds a texture to a texture constant: the table is taken before the group is marked
		__forceinline void BindTexture(int& slot, pddiSurface* surface)
		{
			pddiBaseContext::Constants* table = pddi->constants;
			pddi->constantsDirty |= pddiBaseContext::CONSTANT_TEXTURE;
			table->SetTexture(&slot, surface);
		}
	}

	// FUNCTION: ENGINE 0x10764D20
	ProtoLightDecalPass::~ProtoLightDecalPass()
	{
	}

	// FUNCTION: ENGINE 0x10764D40
	bool ProtoLightDecalPass::IsVisible()
	{
		BindTexture(gConstantLightDecalBuffer, 0);
		unsigned int* constant = pddi->GetTextureConstant(gConstantLightDecalBuffer);
		constant[1] = (constant[1] & 0xf8444754) | 0x444454;
		constant = pddi->GetTextureConstant(gConstantLightDecalBuffer);
		constant[1] = (constant[1] & 0xf84047ff) | 0x404400;
		return true;
	}

	// FUNCTION: ENGINE 0x10764DC0
	void ProtoLightDecalPass::Begin()
	{
	}

	// FUNCTION: ENGINE 0x10764DD0
	ProtoLightDecalPass::ProtoLightDecalPass(const PassDesc* desc) : Pass(desc)
	{
		texture = 0;
		entries.SetBit(2);
		entries.AddEntry(2, false);
		entries.AddEntry(1, false);
		entries.AddEntry(0xF, false);
	}

	// FUNCTION: ENGINE 0x10764E50
	void ProtoLightDecalPass::End()
	{
		core::SafeRelease(texture);
	}

	// FUNCTION: ENGINE 0x10764E60
	void ProtoLightDecalPass::SetTexture(Texture* newTexture)
	{
		core::RefAssign(texture, newTexture);
	}

	// FUNCTION: ENGINE 0x10765310
	ProtoDecalPass::~ProtoDecalPass()
	{
	}

	// FUNCTION: ENGINE 0x10765420
	void ProtoDecalPass::Begin()
	{
	}

	// FUNCTION: ENGINE 0x10765330
	bool ProtoDecalPass::IsVisible()
	{
		BindTexture(gConstantDecalColourBuffer, 0);
		unsigned int* constant = pddi->GetTextureConstant(gConstantDecalColourBuffer);
		constant[1] = (constant[1] & 0xf8444754) | 0x444454;
		constant = pddi->GetTextureConstant(gConstantDecalColourBuffer);
		constant[1] = (constant[1] & 0xf84047ff) | 0x404400;
		BindTexture(gConstantDecalNormalBuffer, 0);
		constant = pddi->GetTextureConstant(gConstantDecalNormalBuffer);
		constant[1] = (constant[1] & 0xf8444752) | 0x444452;
		constant = pddi->GetTextureConstant(gConstantDecalColourBuffer);
		constant[1] = (constant[1] & 0xf84047ff) | 0x404400;
		return true;
	}

	// FUNCTION: ENGINE 0x10765430
	ProtoDecalPass::ProtoDecalPass(const PassDesc* desc) : Pass(desc)
	{
		decalTarget = 0;
		entries.SetBit(2);
		entries.AddEntry(2, false);
		entries.AddEntry(1, false);
		entries.AddEntry(0x10, false);
	}

	// FUNCTION: ENGINE 0x107654B0
	void ProtoDecalPass::End()
	{
		core::SafeRelease(*(Texture**)&decalTarget);
	}

	// FUNCTION: ENGINE 0x107654C0
	void ProtoDecalPass::SetTexture(Texture* texture)
	{
		core::RefAssign(*(Texture**)&decalTarget, texture);
	}

	// FUNCTION: ENGINE 0x10765C60
	LetterBoxPass::LetterBoxPass(const PassDesc* desc) : Pass(desc)
	{
	}

	// FUNCTION: ENGINE 0x10765C80
	LetterBoxPass::~LetterBoxPass()
	{
	}

	// FUNCTION: ENGINE 0x10765C90
	void LetterBoxPass::Render(PassContext* context)
	{
		RunChildren(context);
	}

	// FUNCTION: ENGINE 0x10765CE0
	RootPass::~RootPass()
	{
	}

	// FUNCTION: ENGINE 0x10765CF0
	void RootPass::Render(PassContext* context)
	{
		context->scene->Unknown10712760();
		RunChildren(context);
	}

	// FUNCTION: ENGINE 0x10765D10
	RootPass::RootPass(const RootPassConfig* config) : Pass(&PassDesc(&config->name, 1))
	{
	}

	// FUNCTION: ENGINE 0x10765DA0
	ProtoOpaquePass::~ProtoOpaquePass()
	{
	}

	// FUNCTION: ENGINE 0x10766340
	ProtoOpaquePass::ProtoOpaquePass(const PassDesc* desc) : ProtoLitPass(desc)
	{
		PassColour black = *(const PassColour*)&math::pddiColour::BLACK;
		clearColour = black.bits;
		entries.SetWord(1);
		entries.AddEntry(2, false);
		entries.AddEntry(1, false);
		entries.AddEntry(7, false);
		entries.AddEntry(10, true);
		entries.AddEntry(0x17, true);
		entries.AddEntry(0x24, true);
		unknown138 = entries;
		unknownB0 = entries;
		entries.AddEntry(0x20, true);
		entries.AddEntry(0x1F, true);
		unknown138.AddEntry(0x20, false);
		unknownB0.AddEntry(0x1F, false);
	}

	// FUNCTION: ENGINE 0x1076AFF0
	ProtoLitPass::ProtoLitPass(const PassDesc* desc) : Pass(desc)
	{
	}

	// FUNCTION: ENGINE 0x1076B010
	ProtoLitPass::~ProtoLitPass()
	{
	}

	// FUNCTION: ENGINE 0x1076E600
	ProtoCapturePass::ProtoCapturePass(const PassDesc* desc) : CapturePass(desc)
	{
		unknown100 = 0;
	}

	// FUNCTION: ENGINE 0x1076E630
	ProtoCapturePass::~ProtoCapturePass()
	{
	}

	// FUNCTION: ENGINE 0x1076E640
	void ProtoCapturePass::SetUnknown100(void* value)
	{
		unknown100 = value;
	}

	// FUNCTION: ENGINE 0x1076E7F0
	ProtoMidgroundZPass::ProtoMidgroundZPass(const PassDesc* desc) : Pass(desc)
	{
		entries.SetWord(1);
		entries.AddEntry(2, false);
		entries.AddEntry(1, false);
		entries.AddEntry(10, true);
		entries.AddEntry(0x17, false);
		entries.AddEntry(0x12, true);
		entries.AddEntry(0x11, true);
		entries.AddEntry(0x24, true);
	}

	// FUNCTION: ENGINE 0x1076E870
	ProtoMidgroundZPass::~ProtoMidgroundZPass()
	{
	}

	// FUNCTION: ENGINE 0x1076E880
	ProtoSlowZPass::ProtoSlowZPass(const PassDesc* desc, bool flag) : Pass(desc)
	{
		entries.SetWord(1);
		entries.AddEntry(2, false);
		entries.AddEntry(1, false);
		entries.AddEntry(7, false);
		entries.AddEntry(10, true);
		entries.AddEntry(0x17, true);
		entries.AddEntry(0x18, true);
		entries.AddEntry(0x24, true);
		if (flag)
		{
			entries.AddEntry(9, false);
		}
	}

	// FUNCTION: ENGINE 0x1076E910
	ProtoSlowZPass::~ProtoSlowZPass()
	{
	}

	// FUNCTION: ENGINE 0x1076E920
	ProtoFastZPass::~ProtoFastZPass()
	{
	}

	// FUNCTION: ENGINE 0x1076E950
	ProtoAlphaTestZPass::ProtoAlphaTestZPass(const PassDesc* desc) : Pass(desc)
	{
		entries.SetWord(1);
		entries.AddEntry(2, false);
		entries.AddEntry(1, false);
		entries.AddEntry(0x18, false);
		entries.AddEntry(0x24, true);
	}

	// FUNCTION: ENGINE 0x1076E9B0
	ProtoAlphaTestZPass::~ProtoAlphaTestZPass()
	{
	}

	// FUNCTION: ENGINE 0x1076E9C0
	ProtoZPass::~ProtoZPass()
	{
		delete midgroundPass;
		delete alphaTestPass;
		delete slowPass;
		delete fastPass;
		core::SafeRelease(shader);
	}

	// FUNCTION: ENGINE 0x1076F560
	ProtoFastZPass::ProtoFastZPass(const PassDesc* desc) : Pass(desc)
	{
		entries.SetWord(1);
		entries.AddEntry(2, false);
		entries.AddEntry(1, false);
		entries.AddEntry(7, false);
		entries.AddEntry(9, true);
		entries.AddEntry(10, true);
		entries.AddEntry(0x17, true);
		entries.AddEntry(0x18, true);
		entries.AddEntry(0x24, true);
		unknown138 = entries;
		entries.AddEntry(0x20, true);
		unknown138.AddEntry(0x20, false);
	}

	// FUNCTION: ENGINE 0x1076F620
	// NONMATCHING: the engine builds the names of the four passes in one local that the pass descriptions point at; ours builds a temporary per pass (47.9 %)
#ifdef NONMATCHING
	ProtoZPass::ProtoZPass(const PassDesc* desc) : Pass(desc)
	{
		midgroundPass = 0;
		alphaTestPass = 0;
		slowPass = 0;
		fastPass = 0;
		shader = 0;
		slowPass = new ProtoSlowZPass(&PassDesc(&core::Name<core::CaseSensitiveKey>("SlowZ", 1), 1), true);
		fastPass = new ProtoFastZPass(&PassDesc(&core::Name<core::CaseSensitiveKey>("FastZ", 1), 1));
		AddChild(fastPass, 0);
		AddChild(slowPass, 0);
		alphaTestPass = new ProtoAlphaTestZPass(&PassDesc(&core::Name<core::CaseSensitiveKey>("Prototype TestBlendZ", 1), 1));
		AddChild(alphaTestPass, 0);
		midgroundPass = new ProtoMidgroundZPass(&PassDesc(&core::Name<core::CaseSensitiveKey>("Prototype MidgroundZ", 1), 1));
		AddChild(midgroundPass, 0);
		core::RefAssign(shader, new Shader("unlit"));
	}
#endif

	// FUNCTION: ENGINE 0x1076FDD0
	ParameterHandlerTypeless* ProtoWireframePass::GetParameterHandler()
	{
		return &parameters;
	}

	// FUNCTION: ENGINE 0x10770830
	ProtoWireframePass::~ProtoWireframePass()
	{
	}

	// FUNCTION: ENGINE 0x10770890
	ProtoWireframePass::ProtoWireframePass(const PassDesc* desc) : Pass(desc)
	{
		parameters.object = this;
		parameters.AddBool(&engine::render::gParameterEnable, &ProtoWireframePass::SetParameterEnable, 0);
		entries.SetWord(1);
		entries.AddEntry(2, false);
		entries.AddEntry(1, false);
		entries.AddEntry(7, false);
	}

	// FUNCTION: ENGINE 0x10770940
	ProtoBloodPass::ProtoBloodPass(const PassDesc* desc) : Pass(desc)
	{
		entries.SetBit(3);
		entries.AddEntry(1, false);
		entries.AddEntry(0x14, false);
	}

	// FUNCTION: ENGINE 0x10770980
	ProtoBloodPass::~ProtoBloodPass()
	{
	}

	// FUNCTION: ENGINE 0x10770AC0
	ParameterHandlerTypeless* ProtoShaderLODDebugPass::GetParameterHandler()
	{
		return &parameters;
	}

	// FUNCTION: ENGINE 0x10771180
	ProtoShaderLODDebugPass::~ProtoShaderLODDebugPass()
	{
	}

	// FUNCTION: ENGINE 0x107711E0
	ProtoShaderLODDebugPass::ProtoShaderLODDebugPass(const PassDesc* desc) : Pass(desc)
	{
		entries.SetWord(1);
		entries.AddEntry(2, false);
		entries.AddEntry(1, false);
		parameters.object = this;
		parameters.AddBool(&engine::render::gParameterEnable, &ProtoShaderLODDebugPass::SetParameterEnable, 0);
	}
}

// ---- the instances of the parameter handlers ----

	// FUNCTION: ENGINE 0x1076FE00
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Pair::Pair(const core::Name<core::CaseSensitiveKey>&, const pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry&);

	// FUNCTION: ENGINE 0x1076FE30
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Iterator::operator!=(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Iterator&) const;

	// FUNCTION: ENGINE 0x1076FE50
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Pair& container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Iterator::operator*() const;

	// FUNCTION: ENGINE 0x1076FE60
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Pair::Pair(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x1076FDE0
	template void pure3d::ParameterHandler<pure3d::ProtoWireframePass>::SetObject(pure3d::ProtoWireframePass*);

	// FUNCTION: ENGINE 0x10770410
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Map(pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator);

	// FUNCTION: ENGINE 0x10770420
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Pair* container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Iterator::operator->() const;

	// FUNCTION: ENGINE 0x10770430
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::MapNode::MapNode(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10770470
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Iterator::Iterator(container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::MapNode*, container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>*);

	// FUNCTION: ENGINE 0x107704B0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::End();

	// FUNCTION: ENGINE 0x107704D0
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::CompareNodes(const container::TreeBase::Node*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x10770510
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::CompareKey(const void*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x10770550
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Insert(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x107705C0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Find(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x107705F0
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::DeleteNode(container::TreeBase::Node*, void*);

	// FUNCTION: ENGINE 0x10770600
	template pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry& pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryMap::At(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x10770670
	template bool pure3d::ParameterHandler<pure3d::ProtoWireframePass>::SetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool);

	// FUNCTION: ENGINE 0x107706D0
	template bool pure3d::ParameterHandler<pure3d::ProtoWireframePass>::GetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool*);

	// FUNCTION: ENGINE 0x10770750
	template void container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::Clear();

	// FUNCTION: ENGINE 0x10770760
	template void pure3d::ParameterHandler<pure3d::ProtoWireframePass>::AddBool(const core::Name<core::CaseSensitiveKey>*, bool (pure3d::ProtoWireframePass::*)(bool), bool (pure3d::ProtoWireframePass::*)());

	// FUNCTION: ENGINE 0x107707D0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::Entry, pure3d::ParameterHandler<pure3d::ProtoWireframePass>::EntryAllocator>::~Map();

	// FUNCTION: ENGINE 0x107707E0
	template pure3d::ParameterHandler<pure3d::ProtoWireframePass>::ParameterHandler();

	// FUNCTION: ENGINE 0x10770810
	template pure3d::ParameterHandler<pure3d::ProtoWireframePass>::~ParameterHandler();

	// FUNCTION: ENGINE 0x10770AF0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Pair::Pair(const core::Name<core::CaseSensitiveKey>&, const pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry&);

	// FUNCTION: ENGINE 0x10770B20
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Iterator::operator!=(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Iterator&) const;

	// FUNCTION: ENGINE 0x10770B40
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Pair& container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Iterator::operator*() const;

	// FUNCTION: ENGINE 0x10770B50
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Pair::Pair(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10770AD0
	template void pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::SetObject(pure3d::ProtoShaderLODDebugPass*);

	// FUNCTION: ENGINE 0x10770D60
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Map(pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator);

	// FUNCTION: ENGINE 0x10770D70
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Pair* container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Iterator::operator->() const;

	// FUNCTION: ENGINE 0x10770D80
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::MapNode::MapNode(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10770DC0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Iterator::Iterator(container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::MapNode*, container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>*);

	// FUNCTION: ENGINE 0x10770E00
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::End();

	// FUNCTION: ENGINE 0x10770E20
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::CompareNodes(const container::TreeBase::Node*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x10770E60
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::CompareKey(const void*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x10770EA0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Insert(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10770F10
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Find(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x10770F40
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::DeleteNode(container::TreeBase::Node*, void*);

	// FUNCTION: ENGINE 0x10770F50
	template pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry& pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryMap::At(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x10770FC0
	template bool pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::SetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool);

	// FUNCTION: ENGINE 0x10771020
	template bool pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::GetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool*);

	// FUNCTION: ENGINE 0x107710A0
	template void container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::Clear();

	// FUNCTION: ENGINE 0x107710B0
	template void pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::AddBool(const core::Name<core::CaseSensitiveKey>*, bool (pure3d::ProtoShaderLODDebugPass::*)(bool), bool (pure3d::ProtoShaderLODDebugPass::*)());

	// FUNCTION: ENGINE 0x10771120
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::Entry, pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::EntryAllocator>::~Map();

	// FUNCTION: ENGINE 0x10771130
	template pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::ParameterHandler();

	// FUNCTION: ENGINE 0x10771160
	template pure3d::ParameterHandler<pure3d::ProtoShaderLODDebugPass>::~ParameterHandler();

	// FUNCTION: ENGINE 0x10768590
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Pair::Pair(const core::Name<core::CaseSensitiveKey>&, const pure3d::ParameterHandler<pure3d::ViewPass>::Entry&);

	// FUNCTION: ENGINE 0x107685C0
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Iterator::operator!=(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Iterator&) const;

	// FUNCTION: ENGINE 0x107685E0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Pair& container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Iterator::operator*() const;

	// FUNCTION: ENGINE 0x107685F0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Pair::Pair(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10768520
	template void pure3d::ParameterHandler<pure3d::ViewPass>::SetObject(pure3d::ViewPass*);

	// FUNCTION: ENGINE 0x10768D80
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Map(pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator);

	// FUNCTION: ENGINE 0x10768D90
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Pair* container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Iterator::operator->() const;

	// FUNCTION: ENGINE 0x10768DA0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::MapNode::MapNode(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10768DE0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Iterator::Iterator(container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::MapNode*, container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>*);

	// FUNCTION: ENGINE 0x10768E20
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::End();

	// FUNCTION: ENGINE 0x10768E40
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::CompareNodes(const container::TreeBase::Node*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x10768E80
	template int container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::CompareKey(const void*, const container::TreeBase::Node*);

	// FUNCTION: ENGINE 0x10768EC0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Insert(const container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Pair&);

	// FUNCTION: ENGINE 0x10768F30
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Iterator container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Find(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x10768F60
	template bool container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::DeleteNode(container::TreeBase::Node*, void*);

	// FUNCTION: ENGINE 0x10768F70
	template pure3d::ParameterHandler<pure3d::ViewPass>::Entry& pure3d::ParameterHandler<pure3d::ViewPass>::EntryMap::At(const core::Name<core::CaseSensitiveKey>&);

	// FUNCTION: ENGINE 0x10768FE0
	template bool pure3d::ParameterHandler<pure3d::ViewPass>::SetFloatAdapter(void*, const core::Name<core::CaseSensitiveKey>*, float);

	// FUNCTION: ENGINE 0x10769040
	template bool pure3d::ParameterHandler<pure3d::ViewPass>::SetUnsignedAdapter(void*, const core::Name<core::CaseSensitiveKey>*, unsigned int);

	// FUNCTION: ENGINE 0x107690A0
	template bool pure3d::ParameterHandler<pure3d::ViewPass>::SetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool);

	// FUNCTION: ENGINE 0x10769100
	template bool pure3d::ParameterHandler<pure3d::ViewPass>::SetColourAdapter(void*, const core::Name<core::CaseSensitiveKey>*, const unsigned int*);

	// FUNCTION: ENGINE 0x10769160
	template bool pure3d::ParameterHandler<pure3d::ViewPass>::GetFloatAdapter(void*, const core::Name<core::CaseSensitiveKey>*, float*);

	// FUNCTION: ENGINE 0x107691E0
	template bool pure3d::ParameterHandler<pure3d::ViewPass>::GetUnsignedAdapter(void*, const core::Name<core::CaseSensitiveKey>*, unsigned int*);

	// FUNCTION: ENGINE 0x10769260
	template bool pure3d::ParameterHandler<pure3d::ViewPass>::GetBoolAdapter(void*, const core::Name<core::CaseSensitiveKey>*, bool*);

	// FUNCTION: ENGINE 0x107692E0
	template bool pure3d::ParameterHandler<pure3d::ViewPass>::GetColourAdapter(void*, const core::Name<core::CaseSensitiveKey>*, unsigned int*);

	// FUNCTION: ENGINE 0x10769370
	template void pure3d::ParameterHandler<pure3d::ViewPass>::AddAdapters(const core::Name<core::CaseSensitiveKey>*, bool (*)(void*, const core::Name<core::CaseSensitiveKey>*, const unsigned int*), bool (*)(void*, const core::Name<core::CaseSensitiveKey>*, unsigned int*));

	// FUNCTION: ENGINE 0x107693C0
	template void pure3d::ParameterHandler<pure3d::ViewPass>::AddAdapters(const core::Name<core::CaseSensitiveKey>*, bool (*)(void*, const core::Name<core::CaseSensitiveKey>*, unsigned int), bool (*)(void*, const core::Name<core::CaseSensitiveKey>*, unsigned int*));

	// FUNCTION: ENGINE 0x10769410
	template void container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::Clear();

	// FUNCTION: ENGINE 0x10769420
	template void pure3d::ParameterHandler<pure3d::ViewPass>::AddColour(const core::Name<core::CaseSensitiveKey>*, void (pure3d::ViewPass::*)(const unsigned int*), pure3d::ColourResult (pure3d::ViewPass::*)());

	// FUNCTION: ENGINE 0x10769490
	template void pure3d::ParameterHandler<pure3d::ViewPass>::AddFloat(const core::Name<core::CaseSensitiveKey>*, void (pure3d::ViewPass::*)(float), float (pure3d::ViewPass::*)());

	// FUNCTION: ENGINE 0x10769500
	template void pure3d::ParameterHandler<pure3d::ViewPass>::AddUnsigned(const core::Name<core::CaseSensitiveKey>*, void (pure3d::ViewPass::*)(unsigned int), unsigned int (pure3d::ViewPass::*)());

	// FUNCTION: ENGINE 0x10769570
	template void pure3d::ParameterHandler<pure3d::ViewPass>::AddBool(const core::Name<core::CaseSensitiveKey>*, bool (pure3d::ViewPass::*)(bool), bool (pure3d::ViewPass::*)());

	// FUNCTION: ENGINE 0x107695E0
	template container::Map<core::Name<core::CaseSensitiveKey>, pure3d::ParameterHandler<pure3d::ViewPass>::Entry, pure3d::ParameterHandler<pure3d::ViewPass>::EntryAllocator>::~Map();

	// FUNCTION: ENGINE 0x107695F0
	template pure3d::ParameterHandler<pure3d::ViewPass>::ParameterHandler();

	// FUNCTION: ENGINE 0x10769620
	template pure3d::ParameterHandler<pure3d::ViewPass>::~ParameterHandler();

