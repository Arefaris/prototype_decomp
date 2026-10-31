// The passes of the engine's render pipeline that derive from pure3d::Pass (RTTI names pure3d::ViewPass,
// ProtoDecalPass, ProtoSlowZPass, ProtoShadowPass, ProtoLitPass, ProtoOpaquePass, ...). Only the members the
// reconstructed functions use are declared; the layouts stop there and the member names are guesses. The virtual
// functions are listed in vftable order up to the slot a pass overrides last.
#ifndef PURE3D_PROTOPASS_H
#define PURE3D_PROTOPASS_H

#include "code/pure3d/pass.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/primstream.h"
#include "code/math/matrix.h"

namespace pure3d
{
	class Light;
	class RenderParams;

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
		virtual ~ProtoDecalPass();
		// Slot 4 (0x107654E0)
		virtual void Render(PassContext* context);
		virtual void Begin();
		virtual void End();
		virtual bool IsVisible();

		RenderTarget* decalTarget; // +0xB0
	};

	// Fills the depth buffer with the slowly changing parts (vftable 0x10E5F93C)
	class ProtoSlowZPass : public Pass
	{
	public:
		virtual ~ProtoSlowZPass();
		// Slot 4 (0x1076F010)
		virtual void Render(PassContext* context);
	};

	// The passes that light parts: the lights are chosen per part from the scene's selection and uploaded to the
	// shader constants (SetupLights, 0x1076CD90). The vftable of the class itself is 0x10E5F854
	class ProtoLitPass : public Pass
	{
	public:
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

	// Draws the opaque parts lit (vftable 0x10E5F454)
	class ProtoOpaquePass : public ProtoLitPass
	{
	public:
		virtual ~ProtoOpaquePass();
		virtual void Render(PassContext* context);

		// 0x10766170: puts the parts in drawing order (by their primitive's and binding's sort key)
		void SortParts(PartList* parts);
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
	};

	// Renders the shadow maps (vftable 0x10E5F584)
	class ProtoShadowPass : public ShadowPass
	{
	public:
		virtual ~ProtoShadowPass();
		virtual void Render(PassContext* context);

		// 0x10767B60: draws the parts that cast shadows into the shadow map of a view
		void DrawShadowCasters(RenderParams* params, int view, Scene* scene);
		// 0x107678C0: the parts of the scene (the view is not used)
		PartList* GetShadowParts(Scene* scene, int view);
		// 0x107678D0: sets the device up for the shadow depth (depends on the shadow render manager's flag)
		void Unknown107678D0();
	};

	// Sets up a view of the scene, runs its children and puts the view away (vftable 0x10E5F6BC, fourteen slots)
	class ViewPass : public Pass
	{
	public:
		virtual ~ViewPass();
		virtual ParameterHandlerTypeless* GetParameterHandler();
		// Slot 4 (0x10768670)
		virtual void Render(PassContext* context);
		virtual void Unknown9();
		virtual void Unknown10();
		virtual void Unknown11();
		virtual void Unknown12();
		virtual void Unknown13(int value);

		// 0x1076AF90
		float GetUnknownE4();

		unsigned char unknownB0[8];
		bool unknownB8;
		unsigned char unknownB9[3];
		View* view; // +0xBC
		// The window of the view (left, top, right, bottom)
		float window[4]; // +0xC0
		// The level of the context's stack of views this pass takes its camera and scene from
		unsigned int viewLevel; // +0xD0
		bool clearAlpha; // +0xD4
		unsigned char unknownD5[3];
		float alpha; // +0xD8
		bool shadowView; // +0xDC
		unsigned char unknownDD[7];
		float unknownE4;
	};
}

#endif
