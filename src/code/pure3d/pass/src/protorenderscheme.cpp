// pure3d::ProtoRenderScheme (unit around 0x10718DD0 - 0x1071A000; file name guessed from the class). Names are guesses.
#include "code/math/colour128.h"
#include "code/math/pddicolour.h"
#include "code/pure3d/lightselection.h"
#include "code/pure3d/pass/rendertargetmanager.h"
#include "code/pure3d/postprocesspass.h"
#include "code/pure3d/protopass.h"
#include "code/pure3d/protorenderscheme.h"

namespace pure3d
{
	// FUNCTION: ENGINE 0x10719390
	ViewPassDesc::ViewPassDesc(const void* name) : PassDesc(name, 1)
	{
		clearColour.bits = gViewClearColour;
		clearMask = 0xFFFFFFFF;
		viewLevel = 0;
		shadowView = true;
		unknown25 = true;
	}

	extern core::Name<core::CaseSensitiveKey> gLetterBoxPass;

	// FUNCTION: ENGINE 0x10718DD0
	ProtoRenderScheme::~ProtoRenderScheme()
	{
		LightSelection::Stop();
		delete unknownA4;
	}

	// FUNCTION: ENGINE 0x10718E00
	void ProtoRenderScheme::Begin()
	{
		RenderTargetManager::sSingleton->Unknown1073B450();
		Texture* decal = RenderTargetManager::sSingleton->BorrowDivided(0, 5, true);
		Texture* lightDecal = RenderTargetManager::sSingleton->BorrowDivided(0, 5, true);
		Texture* half1 = RenderTargetManager::sSingleton->BorrowDivided(1, 5, false);
		Texture* half2 = RenderTargetManager::sSingleton->BorrowDivided(1, 5, false);
		Texture* quarter1 = RenderTargetManager::sSingleton->BorrowDivided(2, 5, false);
		Texture* quarter2 = RenderTargetManager::sSingleton->BorrowDivided(2, 5, false);
		Texture* quarter3 = RenderTargetManager::sSingleton->BorrowDivided(2, 5, false);
		Texture* quarter4 = RenderTargetManager::sSingleton->BorrowDivided(2, 5, false);
		Texture* quarter5 = RenderTargetManager::sSingleton->BorrowDivided(2, 5, false);
		decalPass->SetTexture(decal);
		lightDecalPass->SetTexture(lightDecal);
		fbPass->GetColourMatrixPass()->SetDistortion(quarter1);
		fbPass->SetTextures(decal, half1, half2);
		fbPass->GetBloomPass()->SetTextures(quarter5, quarter4);
		fbPass->GetBlurPass()->SetTextures(half2, quarter2, quarter3);
		RenderTargetManager::sSingleton->Unknown1073A710();
		RenderScheme::Begin();
		pddi->Unknown8(1);
	}

	// FUNCTION: ENGINE 0x10718F70
	void ProtoRenderScheme::End()
	{
		pddi->Unknown8(0);
		RenderScheme::End();
	}

	// FUNCTION: ENGINE 0x10719410
	core::Name<core::CaseSensitiveKey> ProtoRenderScheme::Unknown3()
	{
		return gLetterBoxPass;
	}

	// FUNCTION: ENGINE 0x10718F90
	void ProtoRenderScheme::Unknown4(int a)
	{
		letterBoxPass->Unknown10765CA0(a);
	}

	// FUNCTION: ENGINE 0x10718FA0
	void ProtoRenderScheme::Unknown5(int a, int b, int c, int d)
	{
		letterBoxPass->Unknown10765CB0(a, b, c, d);
	}

	// FUNCTION: ENGINE 0x10718FB0
	void ProtoRenderScheme::SetOverlay(Texture* texture)
	{
		fbPass->GetColourMatrixPass()->SetOverlay(texture);
	}

	// FUNCTION: ENGINE 0x10718FD0
	void ProtoRenderScheme::SetGrain(Texture* texture)
	{
		fbPass->GetColourMatrixPass()->SetGrain(texture);
	}

	// FUNCTION: ENGINE 0x10718FF0
	void ProtoRenderScheme::Unknown10718FF0(bool hidden)
	{
		bool enabled = !hidden;
		shadowPass->SetEnabled(enabled);
		decalPass->SetEnabled(enabled);
		lightDecalPass->SetEnabled(enabled);
		bloodPass->SetEnabled(enabled);
		fbPass->GetToneMapPass()->SetEnabled(enabled);
		fbPass->GetColourMatrixPass()->SetEnabled(enabled);
		fbPass->GetBloomPass()->SetEnabled(enabled);
		radialBlurPass->SetEnabled(enabled);
	}

	// FUNCTION: ENGINE 0x10719090
	void ProtoRenderScheme::Unknown10719090(bool hidden)
	{
		bool enabled = !hidden;
		shadowPass->SetEnabled(enabled);
		zPass->SetEnabled(enabled);
		decalPass->SetEnabled(enabled);
		litRootPass->SetEnabled(enabled);
		lightDecalPass->SetEnabled(enabled);
		opaquePass->SetEnabled(enabled);
		midgroundPass->SetEnabled(enabled);
		translucentPass->SetEnabled(enabled);
	}

	// FUNCTION: ENGINE 0x10719120
	void ProtoRenderScheme::SetWireframeEnabled(bool enabled)
	{
		wireframePass->SetEnabled(enabled);
	}

	// FUNCTION: ENGINE 0x10719430
	void ProtoRenderScheme::SetClearColour(const math::Colour128& colour)
	{
		math::pddiColour clear;
		clear.FromColour128(colour);
		// the passes take the packed word
		viewPass54->Unknown9((const unsigned int*)&clear);
		capturePass->SetColour((const unsigned int*)&clear);
		opaquePass->Unknown10765DD0(&clear);
	}

	// FUNCTION: ENGINE 0x10719310
	Pass* Pass::FindDescendant(const core::Name<core::CaseSensitiveKey>& searchName)
	{
		for (Pass* child = firstChild; child != 0; child = child->nextSibling)
		{
			if (searchName == child->name)
			{
				return child;
			}
			Pass* found = child->FindDescendant(searchName);
			if (found != 0)
			{
				return found;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x10719570
	// Orders a name against the name of a node
	static int ComparePassKey(const void* key, const container::TreeBase::Node* node)
	{
		const core::Name<core::CaseSensitiveKey>& name = *(const core::Name<core::CaseSensitiveKey>*)key;
		const core::Name<core::CaseSensitiveKey>& nodeName = ((const RenderScheme::PassNode*)node)->name;
		if (name < nodeName)
		{
			return -1;
		}
		return (nodeName < name) ? 1 : 0;
	}

	// FUNCTION: ENGINE 0x107195D0
	Pass* ProtoRenderScheme::FindPass(const core::Name<core::CaseSensitiveKey>& name)
	{
		const unsigned int* hash = (const unsigned int*)&name.GetHash();
		if (hash[0] == lastFoundHash[0] && hash[1] == lastFoundHash[1])
		{
			return lastFound;
		}
		PassNode* node = (PassNode*)passes.Find(ComparePassKey, &name);
		if (node != 0)
		{
			lastFoundHash[0] = hash[0];
			lastFoundHash[1] = hash[1];
			Pass* found = node->pass;
			lastFound = found;
			return found;
		}
		for (node = (PassNode*)passes.First(); node != 0; node = (PassNode*)passes.Next(node))
		{
			Pass* found = node->pass->FindDescendant(name);
			if (found != 0)
			{
				lastFoundHash[0] = hash[0];
			lastFoundHash[1] = hash[1];
				lastFound = found;
				return found;
			}
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x107191B0
	RootPass* ProtoRenderScheme::CreateRootPass(const RootPassConfig* config)
	{
		RootPass* newPass = new RootPass(config);
		if (!RegisterRootPass(newPass))
		{
			delete newPass;
			return 0;
		}
		return newPass;
	}
}

// The passes of the tree, one function each
// FUNCTION: ENGINE 0x10719680
template pure3d::ProtoShadowPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoShadowPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719700
template pure3d::LetterBoxPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::LetterBoxPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719780
template pure3d::ViewPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ViewPass, pure3d::ViewPassDesc>(
	const pure3d::ViewPassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719800
template pure3d::ProtoFogPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoFogPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719880
template pure3d::ProtoLitRootPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoLitRootPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719900
template pure3d::ProtoCapturePass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoCapturePass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719980
template pure3d::ProtoZPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoZPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719A00
template pure3d::ProtoDecalPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoDecalPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719A80
template pure3d::ProtoLightDecalPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoLightDecalPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719B00
template pure3d::ProtoOpaquePass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoOpaquePass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719B80
template pure3d::ProtoMidgroundPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoMidgroundPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719C00
template pure3d::ProtoWireframePass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoWireframePass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719C80
template pure3d::ProtoBloodPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoBloodPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719D00
template pure3d::ProtoShaderLODDebugPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoShaderLODDebugPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719D80
template pure3d::ProtoTranslucentPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoTranslucentPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719E00
template pure3d::ProtoRadialBlurPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoRadialBlurPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719E80
template pure3d::DepthOfFieldPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::DepthOfFieldPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719F00
template pure3d::ProtoFBPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoFBPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

// FUNCTION: ENGINE 0x10719F80
template pure3d::ProtoHUDPass* pure3d::ProtoRenderScheme::CreatePass<pure3d::ProtoHUDPass, pure3d::PassDesc>(
	const pure3d::PassDesc* description, core::Name<core::CaseSensitiveKey> parentName);

namespace math
{
	// FUNCTION: ENGINE 0x10719210
	pddiColour* pddiColour::FromColour128(const Colour128& colour)
	{
		unsigned int alpha = (unsigned int)(colour.a * 255.5f);
		unsigned int red = (unsigned int)(colour.r * 255.5f);
		unsigned int green = (unsigned int)(colour.g * 255.5f);
		unsigned int blue = (unsigned int)(colour.b * 255.5f);
		*(unsigned int*)this = ((alpha << 8 | red) << 8 | green) << 8 | blue;
		return this;
	}
}
