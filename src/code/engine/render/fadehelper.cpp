// engine::render::FadeValue and engine::render::FadeHelper: the screen fade of the letterbox (unit 0x108FD0A0 -
// 0x108FD960, no assert path; file name guessed).
#include "code/engine/render/fadehelper.h"
#include "code/core/refptr.h"
#include "code/engine/display.h"

namespace choreo
{
	extern const float gMinusOne;
}

namespace engine
{
	extern Display* gDisplay;

	namespace driving
	{
		extern const float gOne;
	}

	namespace render
	{
		// FUNCTION: ENGINE 0x108FD0A0
		FadeValue::FadeValue()
		{
			sliding = false;
			value = 0.0f;
			target = 0.0f;
			step = 0.0f;
		}

		// FUNCTION: ENGINE 0x108FD130
		bool FadeValue::IsSliding() const
		{
			return sliding;
		}

		// 0x108FD140 (the engine folded it with the identical pure3d::FrameTime::GetFloat)
		float FadeValue::GetValue() const
		{
			return value;
		}

		// FUNCTION: ENGINE 0x108FD0C0
		void FadeValue::Set(float newValue)
		{
			target = newValue;
			value = newValue;
			step = 0.0f;
			sliding = false;
		}

		// FUNCTION: ENGINE 0x108FD0E0
		void FadeValue::Slide(float newTarget, float seconds)
		{
			if (seconds == 0.0f)
			{
				Set(newTarget);
				return;
			}
			target = newTarget;
			sliding = true;
			step = (newTarget - value) / seconds;
		}

		// The sign of a number as -1, 0 or 1
		static inline float SignOf(float number)
		{
			return number < 0.0f ? -1.0f : (number > 0.0f ? 1.0f : 0.0f);
		}

		// FUNCTION: ENGINE 0x108FD830
		void FadeValue::Update(float dt)
		{
			value = step * dt + value;
			if (SignOf(value - target) == SignOf(step))
			{
				value = target;
				sliding = false;
				step = 0.0f;
			}
		}

		// FUNCTION: ENGINE 0x108FD150
		FadeHelper::FadeHelper() : unknown0(0), unknown4(0), unknown8(0), unknownD(false), unknown34(false)
		{
			shader = new pure3d::Shader("unlit");
			shader->AddRef();
			unknownC = false;
		}

		// FUNCTION: ENGINE 0x108FD8B0
		FadeHelper::~FadeHelper()
		{
			core::SafeRelease(shader);
		}

		// FUNCTION: ENGINE 0x108FD1C0
		void FadeHelper::Start(float level, bool barsTimed, float barsSeconds, bool dimmingTimed, float dimmingSeconds)
		{
			bars.Slide(1.0f, dimmingTimed ? dimmingSeconds : 0.0f);
			dimming.Slide(level, barsTimed ? barsSeconds : 0.0f);
			unknown34 = true;
		}

		// FUNCTION: ENGINE 0x108FD240
		void FadeHelper::Stop(bool barsTimed, float barsSeconds, bool dimmingTimed, float dimmingSeconds)
		{
			bars.Slide(dimmingTimed ? 0.0f : 1.0f, dimmingTimed ? dimmingSeconds : 0.0f);
			dimming.Slide(barsTimed ? 0.0f : dimming.GetValue(), barsTimed ? barsSeconds : 0.0f);
		}

		// FUNCTION: ENGINE 0x108FD720
		bool FadeHelper::IsShowing()
		{
			float amount = dimming.GetValue();
			return amount != 0.0f && bars.GetValue() != 0.0f;
		}

		// FUNCTION: ENGINE 0x108FD760
		bool FadeHelper::IsFull()
		{
			float amount = dimming.GetValue();
			return amount == 1.0f && bars.GetValue() == 1.0f;
		}

		// FUNCTION: ENGINE 0x108FD7A0
		float FadeHelper::GetBarAmount()
		{
			return bars.GetValue();
		}

		// FUNCTION: ENGINE 0x108FD7B0
		// NONMATCHING: scheduling (the engine multiplies the display height by a half before the call that answers the amount, ours after it; 45.8 %)
#ifdef NONMATCHING
		void FadeHelper::GetBars(int* width, int* bottom, int* left, int* height)
		{
			float displayHeight = (float)gDisplay->GetUnknown8();
			float half = displayHeight * 0.5f;
			float amount = dimming.GetValue();
			*left = 0;
			float barHeight = amount * half;
			*height = (int)barHeight;
			*bottom = (int)((displayHeight - barHeight * 2.0f) + 1.0f);
			*width = gDisplay->GetWidth();
		}
#endif

		// FUNCTION: ENGINE 0x108FD8C0
		void FadeHelper::Update(float dt)
		{
			if (dimming.IsSliding() || bars.IsSliding())
			{
				dimming.Update(dt);
				bars.Update(dt);
				if (!dimming.IsSliding() && !bars.IsSliding())
				{
					if (dimming.GetValue() == 0.0f || bars.GetValue() == 0.0f)
					{
						dimming.Set(0.0f);
						bars.Set(0.0f);
					}
				}
			}
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x108FD140
