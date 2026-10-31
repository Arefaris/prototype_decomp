// The passes of the engine's render pipeline that derive from pure3d::Pass (RTTI names pure3d::ViewPass,
// ProtoDecalPass, ProtoSlowZPass, ProtoShadowPass, ProtoLitPass, ProtoOpaquePass, ...). Only the members the
// reconstructed functions use are declared; the layouts stop there and the member names are guesses. The virtual
// functions are listed in vftable order up to the slot a pass overrides last.
#ifndef PURE3D_PROTOPASS_H
#define PURE3D_PROTOPASS_H

#include "code/core/name.h"
#include "code/pure3d/framebufferpass.h"
#include "code/pure3d/parameterhandler.h"
#include "code/pure3d/pass.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/primstream.h"
#include "code/pure3d/renderscheme.h"
#include "code/math/matrix.h"

namespace pure3d
{
	class Light;
	class RenderParams;
	class Shader;
	class Texture;

	// 0x111BADD0: how many lights the shadow passes make room for
	extern unsigned int gShadowLightCapacity;

	// 0x11282ABC: set while the visibility test of a pass runs
	extern bool gVisibilityTestActive;

	// A pass that draws into a texture of its own (the decal buffer): the surface is at +0x10
	class RenderTarget
	{
	public:
		unsigned char unknown0[0x10];
		pddiSurface* surface;
	};

	// Draws the decals: the parts of the decal buffer pass (primitive type 0x200 are drawn with a distance fade),
	// then makes the buffer the decal colour and normal textures of the lit passes. Vftable 0x10E5F2A4
	class ProtoDecalPass : public Pass
	{
	public:
		// 0x10765430
		explicit ProtoDecalPass(const PassDesc* desc);
		// Slot 0 (the body is 0x10765310, the deleting destructor 0x10765490)
		virtual ~ProtoDecalPass();
		// Slot 4 (0x107654E0)
		virtual void Render(PassContext* context);
		// Slot 5 (0x10765420, does nothing), 6 (0x107654B0) and 7 (0x10765330)
		virtual void Begin();
		virtual void End();
		virtual bool IsVisible();

		// 0x107654C0: holds the buffer the decals are drawn into
		void SetTexture(Texture* texture);

		RenderTarget* decalTarget; // +0xB0
	};

	// Draws the light decals into a buffer the lit passes read (vftable 0x10E5F264)
	class ProtoLightDecalPass : public Pass
	{
	public:
		// 0x10764DD0
		explicit ProtoLightDecalPass(const PassDesc* desc);
		// Slot 0 (the body is 0x10764D20, the deleting destructor 0x10764E30)
		virtual ~ProtoLightDecalPass();
		// Slot 4 (0x10764E80), 5 (0x10764DC0, does nothing), 6 (0x10764E50) and 7 (0x10764D40)
		virtual void Render(PassContext* context);
		virtual void Begin();
		virtual void End();
		virtual bool IsVisible();

		// 0x10764E60: holds the buffer
		void SetTexture(Texture* newTexture);

		Texture* texture; // +0xB0
	};

	// The scene calls the root pass makes before it runs its children use the scene's own functions
	// What a root pass is made from: the name of the pass is at +8 (names guessed)
	struct RootPassConfig
	{
		unsigned char unknown0[8];
		core::Name<core::CaseSensitiveKey> name;
	};

	// Runs its children inside a letter box (vftable 0x10E5F2E4)
	class LetterBoxPass : public Pass
	{
	public:
		// 0x10765C60
		explicit LetterBoxPass(const PassDesc* desc);
		// Slot 0 (the body is 0x10765C80, the deleting destructor 0x10765CC0)
		virtual ~LetterBoxPass();
		// Slot 4 (0x10765C90, a jump to RunChildren)
		virtual void Render(PassContext* context);
	};

	// The root of the pass tree (vftable 0x10E5F320): tells the scene the frame starts, then runs the children
	class RootPass : public Pass
	{
	public:
		// 0x10765D10
		explicit RootPass(const RootPassConfig* config);
		// Slot 0 (the body is 0x10765CE0, the deleting destructor 0x10765D40)
		virtual ~RootPass();
		// Slot 4 (0x10765CF0)
		virtual void Render(PassContext* context);
	};

	// Fills the depth buffer with the slowly changing parts (vftable 0x10E5F93C)
	class ProtoSlowZPass : public Pass
	{
	public:
		// 0x1076E880 (the flag adds the entry 9)
		ProtoSlowZPass(const PassDesc* desc, bool flag);
		// Slot 0 (the body is 0x1076E910, the deleting destructor 0x1076EFF0)
		virtual ~ProtoSlowZPass();
		// Slot 4 (0x1076F010)
		virtual void Render(PassContext* context);
	};

	// Draws the interface (vftable 0x10E5FD0C)
	class ProtoHUDPass : public Pass
	{
	public:
		// 0x10774570
		explicit ProtoHUDPass(const PassDesc* desc);
		// Slot 0 (the body is 0x107745B0, the deleting destructor 0x107745C0)
		virtual ~ProtoHUDPass();
		// Slot 4 (0x107745E0)
		virtual void Render(PassContext* context);
	};

	// The passes that fill the depth buffer without the Proto prefix (RTTI pure3d::SlowZPass, FastZPass, ZPass; vftables
	// 0x10E5FD48, 0x10E5FD70 and 0x10E5FDA0): made from the name of the pass
	class SlowZPass : public Pass
	{
	public:
		// 0x10774CA0 (the flag adds the entry 9)
		SlowZPass(const core::Name<core::CaseSensitiveKey>* name, bool flag);
		// Slot 0 (the body is 0x107747D0, the deleting destructor 0x10774D10)
		virtual ~SlowZPass();
		// Slot 4 (0x10774D30)
		virtual void Render(PassContext* context);
	};

	class FastZPass : public Pass
	{
	public:
		// 0x10774DD0
		explicit FastZPass(const core::Name<core::CaseSensitiveKey>* name);
		// Slot 0 (the body is 0x107747E0, the deleting destructor 0x10774E40)
		virtual ~FastZPass();
		// Slot 4 (0x10774E60)
		virtual void Render(PassContext* context);
	};

	// What a Z pass is made from (RTTI pure3d::ZPassDesc, a struct; vftable 0x10E5FD98; names guessed)
	struct ZPassDesc : public PassDesc
	{
		// 0x107747F0
		explicit ZPassDesc(const core::Name<core::CaseSensitiveKey>* name);

		unsigned int unknown18; // 2
		unsigned int unknown1C; // 1
		bool unknown20;
	};

	class ZPass : public Pass
	{
	public:
		// Slot 0 (the body is 0x10774830, the deleting destructor 0x10775010)
		virtual ~ZPass();
		// Slot 4 (0x10775030)
		virtual void Render(PassContext* context);

		SlowZPass* slowPass; // +0xB0
		FastZPass* fastPass; // +0xB4
		unsigned char unknownB8[0xC];
		Shader* shader;      // +0xC4
	};

	// Fills the depth buffer with the parts of the middle distance (vftable 0x10E5F914)
	class ProtoMidgroundZPass : public Pass
	{
	public:
		// 0x1076E7F0
		explicit ProtoMidgroundZPass(const PassDesc* desc);
		// Slot 0 (the body is 0x1076E870, the deleting destructor 0x1076EE50)
		virtual ~ProtoMidgroundZPass();
		// Slot 4 (0x1076EE70)
		virtual void Render(PassContext* context);
	};

	// Fills the depth buffer with the parts that test their alpha (vftable 0x10E5F98C)
	class ProtoAlphaTestZPass : public Pass
	{
	public:
		// 0x1076E950
		explicit ProtoAlphaTestZPass(const PassDesc* desc);
		// Slot 0 (the body is 0x1076E9B0, the deleting destructor 0x1076F160)
		virtual ~ProtoAlphaTestZPass();
		// Slot 4 (0x1076F180)
		virtual void Render(PassContext* context);
	};

	// Fills the depth buffer with the quickly changing parts (vftable 0x10E5F964)
	class ProtoFastZPass : public Pass
	{
	public:
		// 0x1076F560
		explicit ProtoFastZPass(const PassDesc* desc);
		// Slot 0 (the body is 0x1076E920, the deleting destructor 0x1076F140)
		virtual ~ProtoFastZPass();
		// Slot 4 (0x1076F7E0)
		virtual void Render(PassContext* context);

		PassEntries unknownB0;  // +0xB0
		PassEntries unknown138; // +0x138
	};

	// Fills the depth buffer in four passes of its own (vftable 0x10E5F9B4)
	class ProtoZPass : public Pass
	{
	public:
		// 0x1076F620
		explicit ProtoZPass(const PassDesc* desc);
		// Slot 0 (the body is 0x1076E9C0, the deleting destructor 0x1076F350)
		virtual ~ProtoZPass();
		// Slot 4 (0x1076F370)
		virtual void Render(PassContext* context);

		ProtoMidgroundZPass* midgroundPass; // +0xB0
		ProtoAlphaTestZPass* alphaTestPass; // +0xB4
		ProtoSlowZPass* slowPass;           // +0xB8
		ProtoFastZPass* fastPass;           // +0xBC
		Shader* shader;                     // +0xC0
	};

	// The passes that light parts: the lights are chosen per part from the scene's selection and uploaded to the
	// shader constants (SetupLights, 0x1076CD90). The vftable of the class itself is 0x10E5F854
	class ProtoLitPass : public Pass
	{
	public:
		// 0x1076AFF0
		explicit ProtoLitPass(const PassDesc* desc);
		// Slot 0 (the body is 0x1076B010, the deleting destructor 0x1076B810)
		virtual ~ProtoLitPass();

		// 0x1076CD90: picks the lights of the selection by type (ambient, the shadow light, directional, point,
		// spot), uploads them to the constants and sets the per-vertex lights and the shadow map; mode is 0 or 1
		void SetupLights(int mode);
		// 0x1076B830: the first three point lights of the list as the per-pixel point light constants
		void UploadPointLights(container::ArrayFixed<Light*, 8>* lights);
		// 0x1076B020: whether the shadow render manager has a shadow map
		bool HasShadowMap();
		// 0x1076B030: the per-vertex lights from the selection (the argument is not used)
		void UploadVertexLights(int unused);
		// 0x1076BB70: draws the parts that are not hidden with the "lit" shader and the parameters; the third
		// argument is not used
		void DrawParts(PartList* parts, PrimStreamParameters* parameters, PassContext* context);
	};

	// The passes that draw translucent parts (RTTI pure3d::ProtoTranslucentPassBase, vftable 0x10E5FB48; the Translucent and
	// Midground passes derive from it): a lit pass with a handler of its own and a filter for the second draw
	class ProtoTranslucentPassBase : public ProtoLitPass
	{
	public:
		// 0x10771FA0
		explicit ProtoTranslucentPassBase(const PassDesc* desc);
		// Slot 0 (the body is 0x10771F20, the deleting destructor 0x10772060)
		virtual ~ProtoTranslucentPassBase();
		// Slot 2 (0x10771490) and 4 (0x107719E0)
		virtual ParameterHandlerTypeless* GetParameterHandler();
		virtual void Render(PassContext* context);

		ParameterHandler<ProtoTranslucentPassBase> parameters; // +0xB0
		PassEntries unknownF4; // +0xF4
		bool unknown17C;
	};

	// Vftable 0x10E5FB70
	class ProtoTranslucentPass : public ProtoTranslucentPassBase
	{
	public:
		// 0x10772080
		explicit ProtoTranslucentPass(const PassDesc* desc);
		// Slot 0 (the body is 0x10771F60, the deleting destructor 0x10772100)
		virtual ~ProtoTranslucentPass();
	};

	// Vftable 0x10E5FA34
	class ProtoMidgroundPass : public ProtoTranslucentPassBase
	{
	public:
		// 0x1076F940
		explicit ProtoMidgroundPass(const PassDesc* desc);
		// Slot 0 (the body is 0x1076F9A0, the deleting destructor 0x1076F9C0)
		virtual ~ProtoMidgroundPass();
		// Slot 4 (0x1076F9E0)
		virtual void Render(PassContext* context);
	};

	// Draws the opaque parts lit (vftable 0x10E5F454)
	class ProtoOpaquePass : public ProtoLitPass
	{
	public:
		// 0x10766340
		explicit ProtoOpaquePass(const PassDesc* desc);
		// Slot 0 (the body is 0x10765DA0, the deleting destructor 0x10765F20)
		virtual ~ProtoOpaquePass();
		// Slot 4 (0x107675B0)
		virtual void Render(PassContext* context);

		// 0x10766170: puts the parts in drawing order (by their primitive's and binding's sort key)
		void SortParts(PartList* parts);

		PassEntries unknownB0;  // +0xB0
		PassEntries unknown138; // +0x138
		unsigned int clearColour; // +0x1C0
	};

	// The shadow passes' base (RTTI name pure3d::ShadowPass): the view of the light, set for the parts of a shadow
	// The lights a shadow pass collects: room made with operator new[] (begin, end of the used part, end of the room)
	struct ShadowLightList
	{
		ShadowLightList()
		{
			begin = 0;
			end = 0;
			capacity = 0;
		}
		~ShadowLightList()
		{
			end = begin;
			if (begin != 0)
			{
				operator delete[](begin);
			}
		}

		Light** begin;
		Light** end;
		Light** capacity;
	};

	class ShadowPass : public Pass
	{
	public:
		// 0x107B12A0 (the description is not used here)
		explicit ShadowPass(const PassDesc* desc);
		// Slot 0 (the body is 0x107B13A0, the deleting destructor 0x107B13E0)
		virtual ~ShadowPass();
		// Slot 4 (0x107B1A30): renders the shadows of the scene's lights
		virtual void Render(PassContext* context);
		// Slot 7 (0x107B0A80): starts the shadow render manager's frame once
		virtual bool IsVisible();

		// 0x107B0AA0: the viewport of a view state of the render parameters (the pass is not used)
		void SetViewport(const void* viewState);
		// 0x107B0FF0: the camera of the light (its 4x4 matrix at +0xC0 is put on the device)
		void SetCamera(const void* camera);
		// 0x107B0B00: the position of the light (the first four floats of its camera) in the object space of a
		// part, as the shader constant; the matrix null stands for the identity
		void SetObjectSpaceLightPosition(const void* camera, const math::Matrix* world);

		// The room for the lights of a scene (as many as the global at 0x111BADD0 says), and the filter of the shadow
		// views
		ShadowLightList lights;       // +0xB0
		unsigned char unknownBC[4];
		PassEntries shadowEntries; // +0xC0
		unsigned char unknown148[0x18];
	};

	// A list of part pointers made with operator new[] at a given size (begin, end of the used part, end of the room;
	// a fourth word the constructor leaves alone)
	struct PartPointerList
	{
		// 0x107A65F0
		explicit PartPointerList(unsigned int size = 0x800);
		// 0x107A6640
		~PartPointerList();

		DrawablePart** begin;
		DrawablePart** end;
		DrawablePart** capacity;
		unsigned int unknownC;
	};

	// Renders the shadow maps (vftable 0x10E5F584)
	class ProtoShadowPass : public ShadowPass
	{
	public:
		// 0x10767970
		explicit ProtoShadowPass(const PassDesc* desc);
		// Slot 0 (the body is 0x10767870, the deleting destructor 0x10767A60)
		virtual ~ProtoShadowPass();
		virtual void Render(PassContext* context);

		// 0x10767B60: draws the parts that cast shadows into the shadow map of a view
		void DrawShadowCasters(RenderParams* params, int view, Scene* scene);
		// 0x107678C0: the parts of the scene (the view is not used)
		PartList* GetShadowParts(Scene* scene, int view);
		// 0x107678D0: sets the device up for the shadow depth (depends on the shadow render manager's flag)
		void Unknown107678D0();

		PartPointerList shadowParts[5]; // +0x160
		bool unknown1B0;
	};

	// Copies the picture to a texture and draws what the game asks it to (vftable 0x10E5F8CC, twelve slots)
	class ProtoCapturePass : public CapturePass
	{
	public:
		// 0x1076E600
		explicit ProtoCapturePass(const PassDesc* desc);
		// Slot 0 (the body is 0x1076E630, the deleting destructor 0x1076E7D0)
		virtual ~ProtoCapturePass();
		// Slot 4 (0x1076E650) and 11 (0x1076E640)
		virtual void Render(PassContext* context);
		virtual void SetUnknown100(void* value);

		void* unknown100;
	};

	// Draws the parts as lines (vftable 0x10E5FA80)
	class ProtoWireframePass : public Pass
	{
	public:
		// 0x10770890
		explicit ProtoWireframePass(const PassDesc* desc);
		// Slot 0 (the body is 0x10770830, the deleting destructor 0x10770920)
		virtual ~ProtoWireframePass();
		// Slot 2 (0x1076FDD0) and 4 (0x1076FEB0)
		virtual ParameterHandlerTypeless* GetParameterHandler();
		virtual void Render(PassContext* context);

		// 0x1075DAF0 (another unit)
		bool SetParameterEnable(bool value);

		ParameterHandler<ProtoWireframePass> parameters; // +0xB0
	};

	// Draws the blood on the parts (vftable 0x10E5FABC)
	class ProtoBloodPass : public Pass
	{
	public:
		// 0x10770940
		explicit ProtoBloodPass(const PassDesc* desc);
		// Slot 0 (the body is 0x10770980, the deleting destructor 0x10770990)
		virtual ~ProtoBloodPass();
		// Slot 4 (0x107709B0)
		virtual void Render(PassContext* context);
	};

	// Shows the levels of detail of the shaders (vftable 0x10E5FB00)
	class ProtoShaderLODDebugPass : public Pass
	{
	public:
		// 0x107711E0
		explicit ProtoShaderLODDebugPass(const PassDesc* desc);
		// Slot 0 (the body is 0x10771180, the deleting destructor 0x10771260)
		virtual ~ProtoShaderLODDebugPass();
		// Slot 2 (0x10770AC0) and 4 (0x10770BB0)
		virtual ParameterHandlerTypeless* GetParameterHandler();
		virtual void Render(PassContext* context);

		// 0x1075DAF0 (another unit)
		bool SetParameterEnable(bool value);

		ParameterHandler<ProtoShaderLODDebugPass> parameters; // +0xB0
	};

	// What a view pass is made from (RTTI pure3d::ViewPassDesc, a struct; names guessed)
	struct ViewPassDesc : public PassDesc
	{
		PassColour clearColour; // +0x18
		unsigned int clearMask; // +0x1C
		unsigned int viewLevel; // +0x20
		bool shadowView;        // +0x24
		bool unknown25;         // +0x25
	};

	// Sets up a view of the scene, runs its children and puts the view away (vftable 0x10E5F6BC, fourteen slots)
	class ViewPass : public Pass
	{
	public:
		// 0x107696C0
		explicit ViewPass(const ViewPassDesc* desc);
		// Slot 0 (the body is 0x10769640, the deleting destructor 0x107698A0)
		virtual ~ViewPass();
		virtual ParameterHandlerTypeless* GetParameterHandler();
		// Slot 4 (0x10768670)
		virtual void Render(PassContext* context);
		// Slots 9 - 11 (0x107683D0, 0x10768400, 0x10768410): the colour the view is cleared to, which buffers it clears and
		// the checker board flag; slots 12 and 13 (0x10768840, 0x107688B0)
		virtual void Unknown9(const unsigned int* value);
		virtual void Unknown10(unsigned int value);
		virtual void Unknown11(bool value);
		virtual void Unknown12();
		virtual void Unknown13(int value);

		// 0x1076AF90
		float GetUnknownE4();
		// 0x1075DAF0 (the virtual thunk of Pass::SetEnabled)
		bool SetParameterEnable(bool value);
		// 0x10768420 - 0x10768480, 0x107684A0, 0x107684B0, 0x107684C0: the window, the level, the alpha clear and its alpha
		void SetWindowLeft(float value);
		void SetWindowTop(float value);
		void SetWindowRight(float value);
		void SetWindowBottom(float value);
		void SetViewLevel(unsigned int value);
		void SetClearAlpha(bool value);
		void SetAlpha(float value);

		PassColour clearColour; // +0xB0
		unsigned int clearMask; // +0xB4
		bool unknownB8;
		unsigned char unknownB9[3];
		View* view; // +0xBC
		// The window of the view
		float windowLeft;   // +0xC0
		float windowTop;    // +0xC4
		float windowRight;  // +0xC8
		float windowBottom; // +0xCC
		// The level of the context's stack of views this pass takes its camera and scene from
		unsigned int viewLevel; // +0xD0
		bool clearAlpha; // +0xD4
		unsigned char unknownD5[3];
		float alpha; // +0xD8
		bool shadowView; // +0xDC
		bool unknownDD;
		unsigned char unknownDE[2];
		ParameterHandler<ViewPass> parameters; // +0xE0
		PassEntries unknown124;                // +0x124
	};
}

#endif
