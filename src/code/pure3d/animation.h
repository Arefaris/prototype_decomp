// pure3d::Animation (RTTI name; bases pure3d::Entity, pure3d::RefCounted, core::IRefCount) and the memory manager that
// holds the data of the animations. Only what the animation unit and the choreo module read; names are guesses.
#ifndef PURE3D_ANIMATION_H
#define PURE3D_ANIMATION_H

#include "code/pure3d/entity.h"

namespace pure3d
{
	// A group of channels of an animation, found by a name (the members are in another unit)
	class AnimationGroup
	{
	public:
		// 0x106E7910: the channel of the group by its type and the type of its values
		void* FindChannel(unsigned int type, unsigned int format);
	};

	// pure3d::AnimationMemoryBlock (RTTI name; base pure3d::RefCounted): the memory an animation's data sits in
	class AnimationMemoryBlock : public RefCounted
	{
	public:
		// 0x106E78C0: size bytes from one of the two pools (the one of the 7 mask for objects, the other for
		// arrays), aligned by the mask; null for no bytes (name guess)
		void* Allocate(unsigned int size, unsigned int alignmentMask);

		unsigned char unknown8[8];
		// The animation data, a pointer into the block (zero while it is not loaded)
		void* mData;
	};

	// The manager of the animation memory (the global at 0x1127EDDC)
	class AnimationMemoryManager
	{
	public:
		// 0x106E76C0: marks the data as used (with the manager's lock held)
		void Touch(void* data);
	};

	class Animation : public Entity
	{
	public:
		enum CycleMode
		{
			CYCLE_MODE_0,
			CYCLE_MODE_1,
			CYCLE_MODE_2,
			CYCLE_MODE_3,
			CYCLE_MODE_4,
			CYCLE_MODE_5
		};

		// 0x106E7B20: touches the animation's data in the manager
		void Touch();
		// 0x106E7B50: releases the animation's data through the manager (name guess)
		void Unknown106E7B50();
		// 0x106E9310: keeps the data of mode in the manager's memory (name guess)
		void Unknown106E9310(int mode);
		// 0x106E8590 / 0x106E79E0: the group of the animation for a name, and the group of the whole animation
		AnimationGroup* FindGroup(const core::Name<core::CaseSensitiveKey>* name);
		// 0x106E79D0: the group at an index
		AnimationGroup* GetGroup(int index);
		AnimationGroup* FindOverallGroup(int mode);

		float numFrames;
		float mFrameRate;
		bool mFlag0;
		unsigned char unknown19[7];
		float mUnknown20;
		unsigned char unknown24[0x18];
		AnimationMemoryBlock* mBlock;
	};

	// 0x1127EDDC
	extern AnimationMemoryManager* gAnimationMemoryManager;
}

#endif
