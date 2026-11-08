// pure3d::ProtoRenderScheme (RTTI name, vftable 0x10E5BC74, seven slots; base RenderScheme): the pass tree the game
// draws with. Its passes are made by the functions below, each of which makes a pass of one kind, keeps it in the scheme
// and hangs it below the pass named by the second argument. Member and slot names are guesses.
#ifndef PURE3D_PROTORENDERSCHEME_H
#define PURE3D_PROTORENDERSCHEME_H

#include "code/core/name.h"
#include "code/math/colour128.h"
#include "code/math/pddicolour.h"
#include "code/pure3d/pass.h"
#include "code/pure3d/postprocesspass.h"
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
		// Slot 0 (the body is 0x10718DD0, the deleting destructor 0x107193E0): ends the light selection, deletes the
		// pass at +0xA4
		virtual ~ProtoRenderScheme();
		// Slot 1 (0x10718E00): lends the post processing passes their targets, then begins like the base and switches the
		// device's slot 8 on; slot 2 (0x10718F70) switches it off and ends like the base
		virtual void Begin();
		virtual void End();
		// Slot 3 (0x10719410): the name of the letter box pass; slots 4 / 5 (0x10718F90 / 0x10718FA0) hand on to the
		// letter box pass
		virtual core::Name<core::CaseSensitiveKey> Unknown3();
		virtual void Unknown4(int a);
		virtual void Unknown5(int a, int b, int c, int d);
		// 0x10718FB0 / 0x10718FD0: the overlay and the grain texture of the colour matrix pass
		void SetOverlay(Texture* texture);
		void SetGrain(Texture* texture);
		// 0x10718FF0 / 0x10719090: switch the shadow and post processing passes / the passes of the world on when the flag
		// is clear and off when it is set (names guessed); 0x10719120 switches the wireframe pass
		void Unknown10718FF0(bool hidden);
		void Unknown10719090(bool hidden);
		void SetWireframeEnabled(bool enabled);
		// 0x10719430: the colour the views, the capture and the opaque pass are cleared to
		void SetClearColour(const math::Colour128& colour);
		// 0x107195D0: the pass of that name anywhere in the tree (the last answer is kept)
		Pass* FindPass(const core::Name<core::CaseSensitiveKey>& name);
		// 0x107191B0: makes the root pass and keeps it
		RootPass* CreateRootPass(const RootPassConfig* config);
		// 0x10719680 and the others: a pass of kind T below the pass named parentName, none when there is no such pass
		// or the scheme cannot keep the new one
		template<class T, class Description> T* CreatePass(const Description* description,
			core::Name<core::CaseSensitiveKey> parentName);

		// The passes the constructor (0x1071A000) makes and keeps, by their offsets
		RootPass* rootPass;                       // +0x50
		ViewPass* viewPass54;                     // +0x54
		ViewPass* viewPass58;                     // +0x58
		ProtoWireframePass* wireframePass;        // +0x5C
		unsigned char unknown60[0x14];
		DepthOfFieldPass* depthOfFieldPass;       // +0x74
		ProtoCapturePass* capturePass;            // +0x78
		ProtoZPass* zPass;                        // +0x7C
		ProtoShadowPass* shadowPass;              // +0x80
		LetterBoxPass* letterBoxPass;             // +0x84
		ProtoFogPass* fogPass;                    // +0x88
		ProtoDecalPass* decalPass;                // +0x8C
		ProtoLightDecalPass* lightDecalPass;      // +0x90
		ProtoOpaquePass* opaquePass;              // +0x94
		ProtoTranslucentPass* translucentPass;    // +0x98
		ProtoLitRootPass* litRootPass;            // +0x9C
		unsigned char unknownA0[4];
		Pass* unknownA4;                          // +0xA4
		ViewPass* viewPassA8;                     // +0xA8
		ProtoBloodPass* bloodPass;                // +0xAC
		ProtoHUDPass* hudPass;                    // +0xB0
		ProtoMidgroundPass* midgroundPass;        // +0xB4
		ProtoFBPass* fbPass;                      // +0xB8
		ProtoRadialBlurPass* radialBlurPass;      // +0xBC
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
