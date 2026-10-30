// The frame controllers of pure3d (RTTI names pure3d::FrameController, AnimationFrameController,
// SimpleFrameController, BlendFrameController; the vftable slots are those of the engine, 22, 25, 25 and 29 of them):
// objects that advance an animation over time and apply its values to what they drive. A Simple controller plays one
// animation; a Blend controller keeps up to five (the last one fades in over the ones before it). Slot and member names
// are guesses read from what each one does.
#ifndef PURE3D_FRAMECONTROLLER_H
#define PURE3D_FRAMECONTROLLER_H

#include "code/pure3d/animation.h"
#include "code/pure3d/entity.h"

namespace pure3d
{
	// Slot 2 is the destructor, slots 3 - 21 are pure
	class FrameController : public Entity
	{
	public:
		// 0x10776F80 / 0x10776FA0 / 0x10776FC0
		FrameController();
		FrameController(const FrameController& other);
		virtual ~FrameController();

		// Slot 3: gives the controller the entity it drives (a drawable, a shader or a pose; the controller takes the
		// kind it can use)
		virtual void SetTarget(Entity* target) = 0;
		// Advances the controller by dt (in milliseconds for the camera controllers); applies the values (slot 5)
		// when the controller always updates or when told to
		virtual void Advance(float dt, bool update) = 0;
		virtual void Unknown5() = 0;
		virtual void SetRelativeSpeed(float speed) = 0;
		virtual float GetRelativeSpeed() = 0;
		// Slots 8 / 9: the frame rate of the animation (30 without one) and its last frame
		virtual float Unknown8() = 0;
		virtual float Unknown9() = 0;
		virtual void SetFrame(float frame) = 0;
		virtual float GetFrame() = 0;
		virtual void SetFrameRange(float start, float end) = 0;
		virtual void GetFrameRange(float* start, float* end) = 0;
		virtual void SetCycleMode(Animation::CycleMode mode) = 0;
		virtual int GetCycleMode() = 0;
		virtual void SetNumCycles(unsigned int count) = 0;
		virtual unsigned int GetNumCycles() = 0;
		// Slot 18: how much of the animation is left to play (the largest float for one that never ends)
		virtual float GetRemaining() = 0;
		// Slot 19: the remaining time the controller last computed
		virtual float Unknown19() = 0;
		// Slot 20: whether nothing is left to play
		virtual bool Unknown20() = 0;
		virtual void Reset() = 0;

		// 0x1072E610
		void SetBindingSource(void* source);
		// 0x10776FD0 / 0x10776FE0
		void SetUpdateOnAdvance(bool value);
		bool GetUpdateOnAdvance();

		// Whether Advance applies the values every time
		bool mUpdateOnAdvance; // +0x10
		unsigned char unknown11[7];
	};

	// Slot 22 - 24 are pure here: the animation a controller plays and the kinds of animation it can play. 0x20 bytes
	class AnimationFrameController : public FrameController
	{
	public:
		// 0x10776FF0 / 0x10777010 / 0x10777040
		AnimationFrameController();
		AnimationFrameController(const AnimationFrameController& other);
		virtual ~AnimationFrameController();

		// Slots 6 / 7 (0x10777050 / 0x10777060), 18 (0x10777070), 21 (0x107771D0: speed 1)
		virtual void SetRelativeSpeed(float speed);
		virtual float GetRelativeSpeed();
		virtual float GetRemaining();
		virtual void Reset();

		virtual void SetAnimation(Animation* animation, float a, float b) = 0;
		virtual Animation* GetAnimation() = 0;
		// Whether the controller can play the animation (the kind of animation it names is the controller's)
		virtual bool IsSupported(Animation* animation) = 0;

		float mRelativeSpeed; // +0x18
		unsigned char unknown1C[4];
	};

	// The base of the controllers that animate one thing (a shader, a vertex region, a vertex animation). 0x40 bytes
	class SimpleFrameController : public AnimationFrameController
	{
	public:
		// 0x107771E0 / 0x10777D20 / 0x10777D80
		SimpleFrameController();
		SimpleFrameController(const SimpleFrameController& other);
		virtual ~SimpleFrameController();

		virtual void Advance(float dt, bool update);
		virtual float Unknown8();
		virtual float Unknown9();
		virtual void SetFrame(float frame);
		virtual float GetFrame();
		virtual void SetFrameRange(float start, float end);
		virtual void GetFrameRange(float* start, float* end);
		virtual void SetCycleMode(Animation::CycleMode mode);
		virtual int GetCycleMode();
		virtual void SetNumCycles(unsigned int count);
		virtual unsigned int GetNumCycles();
		virtual float Unknown19();
		virtual bool Unknown20();
		virtual void Reset();
		virtual void SetAnimation(Animation* animation, float a, float b);
		virtual Animation* GetAnimation();

		int mCycleMode;           // +0x20
		unsigned int mNumCycles;  // +0x24
		float mRemaining;         // +0x28
		float mStartFrame;        // +0x2C
		float mEndFrame;          // +0x30
		float mFrame;             // +0x34
		bool mForward;            // +0x38
		unsigned char unknown39[3];
		Animation* mAnimation;    // +0x3C
	};

	// An animation of a Blend controller with its own frame, range and fade (0x2C bytes)
	struct BlendEntry
	{
		// 0x10777520 / 0x10777E60 (lets go of the animation)
		BlendEntry();
		~BlendEntry();

		// 0x10777570
		Animation* GetAnimation();
		// 0x10777E80: takes the animation
		void SetAnimation(Animation* animation);
		// 0x10777EC0: the whole range of the animation, no fade
		void Reset();

		float frame;        // +0
		float startFrame;   // +4
		float endFrame;     // +8
		float fadeLeft;     // +0xC
		float fadeRate;     // +0x10
		float weight;       // +0x14
		float remaining;    // +0x18
		unsigned int numCycles; // +0x1C
		int cycleMode;      // +0x20
		bool forward;       // +0x24
		unsigned char unknown25[3];
		Animation* animation; // +0x28
	};

	// The base of the pose, light and camera controllers: up to five animations, the last one fading in
	class BlendFrameController : public AnimationFrameController
	{
	public:
		// 0x10777F20 / 0x10777F80 / 0x10778090
		BlendFrameController();
		BlendFrameController(const BlendFrameController& other);
		virtual ~BlendFrameController();

		virtual void Advance(float dt, bool update);
		virtual void Unknown5();
		virtual float Unknown8();
		virtual float Unknown9();
		virtual void SetFrame(float frame);
		virtual float GetFrame();
		virtual void SetFrameRange(float start, float end);
		virtual void GetFrameRange(float* start, float* end);
		virtual void SetCycleMode(Animation::CycleMode mode);
		virtual int GetCycleMode();
		virtual void SetNumCycles(unsigned int count);
		virtual unsigned int GetNumCycles();
		virtual float Unknown19();
		virtual bool Unknown20();
		virtual void Reset();
		virtual void SetAnimation(Animation* animation, float a, float b);
		virtual Animation* GetAnimation();
		// Slot 25 (0x107782C0): drops all but the first animation and clears it
		virtual void Stop();
		// Slots 26 and 27: pure here
		virtual void Unknown26() = 0;
		virtual void Unknown27() = 0;
		// Slot 28 (0x10778320): drops the oldest animation
		virtual void RemoveFirst();

		int mCycleMode;           // +0x20
		unsigned int mNumCycles;  // +0x24
		unsigned int mCount;      // +0x28
		BlendEntry mEntries[5];   // +0x2C
		bool unknown108;
		unsigned char unknown109[3];
	};
}

#endif
