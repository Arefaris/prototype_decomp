// pure3d::BillboardQuadGroupAnimationController (RTTI name; bases SimpleFrameController, AnimationFrameController,
// FrameController, Entity, RefCounted, core::IRefCount; 0x48 bytes, 27 vftable slots): plays an animation that moves the
// quads of a billboard quad group (the class name BillboardQuadGroup is a guess from the loader's name). Names are
// guesses.
#ifndef PURE3D_BILLBOARDQUADGROUPANIMATIONCONTROLLER_H
#define PURE3D_BILLBOARDQUADGROUPANIMATIONCONTROLLER_H

#include "code/pure3d/framecontroller.h"

namespace pure3d
{
	// The quads a controller animates: a reference counted list of quad pointers (the list at +0x60 / +0x64)
	class BillboardQuadGroup : public RefCounted
	{
	public:
		unsigned char unknown8[0x58];
		void** quadsBegin;
		void** quadsEnd;
	};

	class BillboardQuadGroupAnimationController : public SimpleFrameController
	{
	public:
		// 0x107B3B00 / 0x107B3F80
		BillboardQuadGroupAnimationController();
		BillboardQuadGroupAnimationController(const BillboardQuadGroupAnimationController& other);
		// Slot 2 (the body is 0x107B3C30, the deleting destructor 0x107B3F60)
		virtual ~BillboardQuadGroupAnimationController();

		// Slot 3 (0x107B3B50): nothing
		virtual void SetTarget(Entity* target);
		// Slot 5 (0x107B3C70): lays the animation's values at the frame over the quads
		virtual void Unknown5();
		// Slot 24 (0x107B3B30): a billboard quad group animation
		virtual bool IsSupported(Animation* animation);
		// Slot 25 (0x107B3B20): true
		virtual bool Unknown25();
		// Slot 26 (0x107B3FB0)
		virtual BillboardQuadGroupAnimationController* Clone();

		// 0x107B3B60 / 0x107B3C50
		BillboardQuadGroup* GetGroup();
		void SetGroup(BillboardQuadGroup* newGroup);

		BillboardQuadGroup* group; // +0x40
		unsigned char unknown44[4];
	};
}

#endif
