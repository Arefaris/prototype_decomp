// pure3d::ProtoRenderScheme (RTTI name, vftable 0x10E5BC74, seven slots; base RenderScheme): the pass tree the game
// draws with. Its passes are made by the functions below, each of which makes a pass of one kind, keeps it in the scheme
// and hangs it below the pass named by the second argument. Member and slot names are guesses.
#ifndef PURE3D_PROTORENDERSCHEME_H
#define PURE3D_PROTORENDERSCHEME_H

#include "code/core/name.h"
#include "code/pure3d/pass.h"
#include "code/pure3d/protopass.h"
#include "code/pure3d/renderscheme.h"

namespace pure3d
{
	struct PassDesc;

	// RTTI pure3d::ProtoLitRootPass (vftable 0x10E5F890, nine slots; base Pass): 0x130 bytes, the members are not known
	class ProtoLitRootPass : public Pass
	{
	public:
		// 0x1076D950
		explicit ProtoLitRootPass(const PassDesc* desc);
		virtual void Render(PassContext* context);

		unsigned char unknownB0[0x80];
	};

	class ProtoRenderScheme : public RenderScheme
	{
	public:
		// 0x107195D0: the pass of that name anywhere in the tree (the last answer is kept)
		Pass* FindPass(const core::Name<core::CaseSensitiveKey>& name);
		// 0x107191B0: makes the root pass and keeps it
		RootPass* CreateRootPass(const RootPassConfig* config);
		// 0x10719680 and the others: a pass of kind T below the pass named parentName, none when there is no such pass
		// or the scheme cannot keep the new one
		template<class T, class Description> T* CreatePass(const Description* description,
			core::Name<core::CaseSensitiveKey> parentName);
	};

	template<class T, class Description> T* ProtoRenderScheme::CreatePass(const Description* description,
		core::Name<core::CaseSensitiveKey> parentName)
	{
		Pass* parent = FindPass(parentName);
		if (parent == 0)
		{
			return 0;
		}
		T* newPass = new T(description);
		if (RegisterPass(newPass))
		{
			parent->AddChild(newPass, 0);
		}
		else
		{
			delete newPass;
			newPass = 0;
		}
		return newPass;
	}
}

#endif
