// engine::render::FadeValue and engine::render::FadeHelper (name guesses; the classes have no RTTI): the screen fade the
// letterbox owns two of. A fade value slides a float to a target at a speed; a fade helper keeps two of them (the amount
// of the bars and the one of the dimming) and the "unlit" shader it draws with. Unit 0x108FD0A0 - 0x108FD960 (no assert
// path; the directory and file name are guesses); the member and method names are guesses.
#ifndef ENGINE_RENDER_FADEHELPER_H
#define ENGINE_RENDER_FADEHELPER_H

#include "code/pure3d/shader.h"

namespace engine
{
	namespace render
	{
		class FadeValue
		{
		public:
			// 0x108FD0A0
			FadeValue();
			// 0x108FD0C0: jumps to a value
			void Set(float newValue);
			// 0x108FD0E0: slides to a target in that many seconds (at once for none)
			void Slide(float newTarget, float seconds);
			// 0x108FD130 / 0x108FD140
			bool IsSliding() const;
			float GetValue() const;
			// 0x108FD830: moves on by the time and stops at the target
			void Update(float dt);

			bool sliding;  // +0
			float value;  // +4
			float target;  // +8
			float step;  // +0xC: the change per second
		};

		class FadeHelper
		{
		public:
			// 0x108FD150
			FadeHelper();
			// 0x108FD8B0
			~FadeHelper();

			// 0x108FD1C0: fades the dimming in over its seconds (or at once) and the bars to a level
			void Start(float level, bool barsTimed, float barsSeconds, bool dimmingTimed, float dimmingSeconds);
			// 0x108FD240: fades the dimming out and the bars away
			void Stop(bool barsTimed, float barsSeconds, bool dimmingTimed, float dimmingSeconds);
			// 0x108FD720 / 0x108FD760: whether neither amount is zero / whether both are all the way in
			bool IsShowing();
			bool IsFull();
			// 0x108FD7A0: the amount of the bars
			float GetBarAmount();
			// 0x108FD7B0: the rectangle of the bars on the display
			void GetBars(int* width, int* bottom, int* left, int* height);
			// 0x108FD8C0
			void Update(float dt);

			int unknown0;
			int unknown4;
			int unknown8;
			bool unknownC;  // +0xC
			bool unknownD;  // +0xD
			pure3d::Shader* shader;  // +0x10
			FadeValue bars;  // +0x14
			FadeValue dimming;  // +0x24
			bool unknown34;  // +0x34
		};
	}
}

#endif
