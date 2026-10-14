// proto::BulletTracer (RTTI name; a pure3d primitive that draws a bullet's tracer as two ribbons, a bright head and a
// trail), its per-shot state proto::BulletTracerState and the parameters of a ribbon, proto::BulletTracerParams::Data (a
// reflected type; its fields' names are the engine's own, from the reflection strings). Layouts partial; the names of
// the state's runtime members and of the methods are guesses.
#ifndef PROTO_RENDER_BULLETTRACER_H
#define PROTO_RENDER_BULLETTRACER_H

#include "code/core/name.h"
#include "code/math/vector.h"
#include "code/math/vector4.h"
#include "code/pure3d/primitive.h"

namespace pure3d
{
	class Shader;
}

namespace proto
{
	struct BulletTracerParams
	{
		// The parameters of one ribbon (0x58 bytes)
		struct Data
		{
			float fadeInTime;
			float fadeOutTime;
			float startFadeDistance;
			float endFadeDistance;
			float generateTime;
			float fadeInTrailTime;
			float fadeOutTrailTime;
			float shrinkInTime;
			float shrinkOutTime;
			float thickness;
			float textureLength;
			float textureScrollRate;
			unsigned char unknown30[8];
			math::Vector4 startColour;
			math::Vector4 endColour;
		};
	};

	// The state of a tracer in flight: a copy of the profile (the ribbons and the delay), the head's position and
	// direction, and the clocks of the ribbons
	class BulletTracerState : public pure3d::PrimitiveState
	{
	public:
		// 0x102CCEB0 / 0x102CCEF0 / 0x102CCF30 / 0x102CCF70: one over the fade out trail / fade in trail / shrink out /
		// shrink in time, zero when it is zero
		float GetInverseFadeOutTrailTime(const BulletTracerParams::Data* data);
		float GetInverseFadeInTrailTime(const BulletTracerParams::Data* data);
		float GetInverseShrinkOutTime(const BulletTracerParams::Data* data);
		float GetInverseShrinkInTime(const BulletTracerParams::Data* data);
		// 0x102CCFB0: the opacity of the trail at a distance along it, from its age and the distance
		float GetTrailFade(const BulletTracerParams::Data* data, float time, float distance);
		// 0x102CD130: the fade of the ribbon's width towards its end, from the position along it
		float GetWidthFade(const BulletTracerParams::Data* data, float position);
		// 0x102CDE90: the opacity of a ribbon: it fades in, holds for the generate time and fades out
		float GetFade(const BulletTracerParams::Data* data);
		// 0x102CDFB0: how far the point a is behind the head, as a fade (1 at the head) scaled by the age
		float GetDistanceFade(const math::Vector* a, const math::Vector* b);

		unsigned char unknown10[0x10];
		BulletTracerParams::Data head;
		BulletTracerParams::Data tail;
		float wait;
		math::Vector offset;
		math::Vector position;
		math::Vector direction;
		unsigned char unknownF8[0x10];
		float age;
		float headScroll;
		float tailScroll;
		unsigned char unknown114[0x1C];
		float speed;
		unsigned char unknown134[8];
		float length;
		float unknown140;
	};

	// The two ribbons share one primitive: the shaders of the head and the trail
	class BulletTracer : public pure3d::Primitive
	{
	public:
		// 0x102CFF50: builds the triangles of one ribbon (layer 0: the head, 1: the trail) and draws them
		void DrawLayer(int layer, const core::Name<core::CaseInsensitiveKey32>& name, BulletTracerState* state,
			const BulletTracerParams::Data* data, pure3d::Shader* shader);

		pure3d::Shader* headShader;
		pure3d::Shader* tailShader;
	};
}

#endif
