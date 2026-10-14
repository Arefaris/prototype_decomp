// pure3d::Pass (RTTI name, vftable 0x10E5E4D0, nine slots): one step of the render pipeline. Passes form a tree --
// a pass keeps its parent, its first child and the next sibling (the unit's AddChild 0x107546C0 walks the children
// through the sibling link at +0x1C) -- plus the two flag words and the collection at +0x28 the lighting selection
// fills. Only the destructor is reconstructed; the rest of the unit (0x10754690 - 0x10755780) is not, so the slot
// names here are guesses read from what each slot does.
#ifndef PURE3D_PASS_H
#define PURE3D_PASS_H

namespace pure3d
{
	class Scene;

	// What a pass keeps at +0x28: from its destructor (0x10610240, out of line in another unit) an element range that
	// runs from +4 to the end pointer at +0x84, so sixteen 8-byte entries inline. The class name is a guess.
	class PassEntries
	{
	public:
		~PassEntries();

		unsigned int unknown0;
		unsigned char entries[0x80];
		void* end84;
	};

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
		// Slot 4: pure (the vftable holds the CRT's _purecall)
		virtual void Prepare() = 0;
		// Slot 5 (0x10754B90) / 6 (0x10754BB0): walks the children calling 0x10754820 / 0x10754840 on each, which set
		// or clear bit 0 of the flag word at +0x24
		virtual void Begin();
		virtual void End();
		// Slot 7 (0x10754740): true
		virtual bool IsVisible();
		// Slot 8 (0x107547B0): asks the scene for the pass's lights, with the collection at +0x28 as the result
		virtual void SelectLights(Scene* scene);

		unsigned char unknown4[0xc];
		Scene* scene;         // +0x10, the scene the pass belongs to
		Pass* parent;         // +0x14
		Pass* firstChild;     // +0x18
		Pass* nextSibling;    // +0x1c
		unsigned int flags20; // +0x20
		unsigned int flags24; // +0x24
		PassEntries entries;  // +0x28
	};
}

#endif
