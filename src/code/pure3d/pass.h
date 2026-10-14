// pure3d::Pass (RTTI name, vftable 0x10E5E4D0, nine slots): one step of the render pipeline. Passes form a tree --
// a pass keeps its parent, its first child and the next sibling (RunChildren 0x10754B60 walks the children through
// the sibling link at +0x1C) -- plus the two flag words and the part filter at +0x28 that picks the parts the pass
// draws. A pass is run once per view (Run 0x10754AF0): the render states named by the mask at +0x10 are saved
// around its Render call. The slot names are guesses read from what each slot does.
#ifndef PURE3D_PASS_H
#define PURE3D_PASS_H

#include "code/container/arrayfixed.h"
#include "code/pure3d/view.h"

namespace pure3d
{
	class DrawablePart;
	class Scene;
	class View;

	// One element of a part filter (8 bytes; the meaning of the words is unknown)
	struct PassEntry
	{
		unsigned int unknown0;
		unsigned int unknown4;
	};

	// What a pass keeps at +0x28 (the destructor 0x10610240 sits in another unit): the filter the scene applies when
	// it answers which parts the pass draws -- a word and up to sixteen entries. The class name is a guess.
	class PassEntries
	{
	public:
		~PassEntries();

		unsigned int unknown0;
		container::ArrayFixed<PassEntry, 16> list;
	};

	// The parts a pass answers for a scene (a begin / end pointer pair of the scene's list)
	struct PartList
	{
		DrawablePart** begin;
		DrawablePart** end;
		DrawablePart** capacity;
	};

	// One level of the camera stack of a pass context (12 bytes)
	struct PassView
	{
		CameraData* camera;
		CameraData* shadowCamera;
		Scene* scene;
	};

	// What the passes are run with: the camera, the camera the shadow views use (null: the same), the scene and the
	// stack of views a ViewPass takes its camera and scene from. Names are guesses.
	class PassContext
	{
	public:
		unsigned char unknown0[4];
		CameraData* camera;
		CameraData* shadowCamera;
		Scene* scene;
		unsigned char unknown10[0x14];
		container::ArrayFixed<PassView, 8> views;
	};

	class LightingInputs;

	class Pass
	{
	public:
		// Slot 0 (0x10754AE0) and the compiler's scalar deleting destructor (0x10755100)
		virtual ~Pass();
		// Slot 1 (0x10754760): calls slot 7 and sets or clears bit 0 of the flag word at +0x20
		virtual void SetEnabled(bool enabled);
		// Slot 2 (0x10754AC0): false
		virtual bool IsEnabled();
		// Slot 3 (0x10754690): walks the children and calls 0x10754590 on each with the argument
		virtual void VisitChildren(void* context);
		// Slot 4: pure (the vftable holds the CRT's _purecall); draws what the pass is for
		virtual void Render(PassContext* context) = 0;
		// Slot 5 (0x10754B90) / 6 (0x10754BB0): walks the children calling 0x10754820 / 0x10754840 on each, which set
		// or clear bit 0 of the flag word at +0x24
		virtual void Begin();
		virtual void End();
		// Slot 7 (0x10754740): true
		virtual bool IsVisible();
		// Slot 8 (0x107547B0): asks the scene which parts the pass draws, with the filter at +0x28
		virtual PartList* GetParts(Scene* scene);

		// 0x10754820: runs Begin once (before the first Run)
		void BeginOnce();
		// 0x10754AF0: runs Render between a save and a restore of the render states the pass names
		void Run(PassContext* context);
		// 0x10754B60: runs every child
		void RunChildren(PassContext* context);
		// 0x107545A0 / 0x107545D0: the view takes the camera and is applied / put away (they do not use the pass)
		void BeginView(View* view, CameraData* camera);
		void EndView(View* view);
		// 0x10754D50 / 0x10754E60: starts the visibility test of the scene for the context's camera (the handle
		// is kept in a global) and waits for its result
		void StartVisibilityTest(PassContext* context, bool unknown);
		void FinishVisibilityTest(PassContext* context);
		// 0x10754810: the lighting inputs the passes upload (the global at 0x11282AB0; the pass is not used)
		LightingInputs* GetLightingInputs();

		unsigned char unknown4[0xc];
		// The groups of render states Run saves (RenderStateBackup groups)
		unsigned int stateGroups; // +0x10
		Pass* parent;         // +0x14
		Pass* firstChild;     // +0x18
		Pass* nextSibling;    // +0x1c
		unsigned int flags20; // +0x20
		unsigned int flags24; // +0x24
		PassEntries entries;  // +0x28
	};
}

#endif
