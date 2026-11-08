// pure3d::Animation (RTTI name; bases pure3d::Entity, pure3d::RefCounted, core::IRefCount) and the memory manager that
// holds the data of the animations. Only what the animation unit and the choreo module read; names are guesses.
#ifndef PURE3D_ANIMATION_H
#define PURE3D_ANIMATION_H

#include "code/pure3d/entity.h"

namespace pure3d
{
	class AnimationMemoryBlock;

	// A group of channels of an animation, found by a name (the members are in another unit)
	class AnimationGroup
	{
	public:
		// 0x106E8240: the hash of the name
		unsigned __int64 GetNameHash();
		// 0x106E7910: the channel of the group by its type and the type of its values
		void* FindChannel(unsigned int type, unsigned int format);

		unsigned char unknown0[8];
		core::Name<core::CaseSensitiveKey> mName;
		// The id the group is found by in an animation sorted by id (the overall groups)
		int mId;
		unsigned int mChannelCount;
		void** mChannels;
		AnimationMemoryBlock* mBlock;
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
		// 0x106E8D30 / 0x106E8D60 / 0x106E8690: the group of a name given as text, and the index of a group by text and by name
		AnimationGroup* FindGroup(const char* name);
		int FindGroupIndex(const char* name);
		int FindGroupIndex(const core::Name<core::CaseSensitiveKey>* name);
		// 0x106E8770: moves a frame on by dt (scaled by the frame rate) inside the range the way the cycle mode says;
		// remaining is the time left to play and forward the direction the frame moves in (name guess)
		float AdvanceFrame(float* remaining, bool* forward, float frame, float dt, float start, float end, bool unlimited,
			int mode);
		// 0x106E79D0: the group at an index
		AnimationGroup* GetGroup(int index);
		AnimationGroup* FindOverallGroup(int mode);
		// 0x106E7A90: the index of the group of that id (-1 for none)
		int FindOverallGroupIndex(int id);

		float numFrames;
		float mFrameRate;
		bool mFlag0;
		unsigned char unknown19[3];
		// The four characters of the kind of animation (the frame controllers test it); the number of groups
		unsigned int mType;
		float mUnknown20;
		// How the groups are kept: 1 sorted by id, 0 sorted by name
		int mSortMode;
		int mGroupCount;
		AnimationGroup** mGroups;
		unsigned char unknown30[0xC];
		AnimationMemoryBlock* mBlock;
	};

	// 0x1127EDDC
	extern AnimationMemoryManager* gAnimationMemoryManager;
}

#endif
