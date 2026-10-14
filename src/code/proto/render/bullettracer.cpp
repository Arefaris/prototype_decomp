// proto::BulletTracer, BulletTracerState and the helpers of their unit (code/proto/render/bullettracer.cpp, 0x102CC000 -
// 0x102D2500; the path is a guess from the class names). Names are guesses.
#include "code/math/colour128.h"
#include "code/math/mathutils.h"
#include "code/math/pddicolour.h"
#include "code/math/vector4.h"
#include "code/proto/render/bullettracer.h"
#include "code/pure3d/context.h"
#include "code/pure3d/pddi.h"
#include "code/pure3d/primstream.h"
#include "code/pure3d/shader.h"

#include <algorithm>
#include <math.h>
#include <new>

// The sort of the cut distances is the toolchain's <algorithm> for float*; the unit keeps the instances it needs as
// COMDAT functions of their own, and the compiler reproduces every one of them
// FUNCTION: ENGINE 0x102CE4D0
template void std::_Med3<float*>(float*, float*, float*);

// FUNCTION: ENGINE 0x102CE530
template void std::_Adjust_heap<float*, int, float>(float*, int, int, float);

// FUNCTION: ENGINE 0x102CE630
template void std::_Pop_heap<float*, int, float>(float*, float*, float*, float, int*);

// FUNCTION: ENGINE 0x102CED90
template void std::_Median<float*>(float*, float*, float*);

// FUNCTION: ENGINE 0x102CEF90
template void std::_Make_heap<float*, int, float>(float*, float*, int*, float*);

// FUNCTION: ENGINE 0x102CEFE0
template void std::_Insertion_sort1<float*, float>(float*, float*, float*);

// FUNCTION: ENGINE 0x102CF0B0
template void std::_Pop_heap_0<float*, float>(float*, float*, float*);

// FUNCTION: ENGINE 0x102CF5C0
template void std::sort_heap<float*>(float*, float*);

// FUNCTION: ENGINE 0x102CF7C0
template std::pair<float*, float*> std::_Unguarded_partition<float*>(float*, float*);

// FUNCTION: ENGINE 0x102CFB00
template void std::make_heap<float*>(float*, float*);

// FUNCTION: ENGINE 0x102CFB30
template void std::_Insertion_sort<float*>(float*, float*);

// FUNCTION: ENGINE 0x102CFB50
template void std::pop_heap<float*>(float*, float*);

// FUNCTION: ENGINE 0x102CFBA0
template void std::_Sort_heap<float*>(float*, float*);

// FUNCTION: ENGINE 0x102CFDD0
template void std::_Sort<float*, int>(float*, float*, int);

// FUNCTION: ENGINE 0x102CFF00
template void std::sort<float*>(float*, float*);

namespace math
{
	// The channel of a colour as a byte (255.5 scales 1.0 to 255)
	static inline int ToByte(float value)
	{
		int v = (int)(value * 255.5f);
		if (v < 0)
		{
			v = 0;
		}
		else if (v > 255)
		{
			v = 255;
		}
		return v;
	}

	// FUNCTION: ENGINE 0x102CD7F0
	// EQUIVALENT: the engine tests v < 0 first and then v > 255 on both paths; every clamp form tried here tests in
	// another order
	// A kept copy of the packed colour of a Colour128 (the same code as the copy of the Vector4 one at 0x102CD6D0)
	pddiColour::pddiColour(const Colour128& colour)
	{
		int alpha = ToByte(colour.a);
		int blue = ToByte(colour.b);
		int green = ToByte(colour.g);
		int red = ToByte(colour.r);
		*(unsigned int*)this = ((alpha << 8 | red) << 8 | green) << 8 | blue;
	}
}

namespace proto
{
	// FUNCTION: ENGINE 0x102CCCF0
	// EQUIVALENT: the same operations in the same order; the engine loads the constant before the pointers and multiplies the
	// first channel's factor in the other register
	// Scales a colour by a fade: every channel by 1 + (amount - 1) * factor, so a factor of 1 follows the fade and 0
	// leaves the channel alone
	void ScaleColour(math::Vector4* colour, float amount, const math::Vector4* factors)
	{
		float fade = amount - 1.0f;
		float* channel = &colour->x;
		const float* factor = &factors->x;
		for (int i = 0; i < 4; i++)
		{
			*channel = (*factor * fade + 1.0f) * *channel;
			channel++;
			factor++;
		}
	}

	// FUNCTION: ENGINE 0x102CCEB0
	float BulletTracerState::GetInverseFadeOutTrailTime(const BulletTracerParams::Data* data)
	{
		float time = data->fadeOutTrailTime;
		return time != 0.0f ? 1.0f / time : 0.0f;
	}

	// FUNCTION: ENGINE 0x102CCEF0
	float BulletTracerState::GetInverseFadeInTrailTime(const BulletTracerParams::Data* data)
	{
		float time = data->fadeInTrailTime;
		return time != 0.0f ? 1.0f / time : 0.0f;
	}

	// FUNCTION: ENGINE 0x102CCF30
	float BulletTracerState::GetInverseShrinkOutTime(const BulletTracerParams::Data* data)
	{
		float time = data->shrinkOutTime;
		return time != 0.0f ? 1.0f / time : 0.0f;
	}

	// FUNCTION: ENGINE 0x102CCF70
	float BulletTracerState::GetInverseShrinkInTime(const BulletTracerParams::Data* data)
	{
		float time = data->shrinkInTime;
		return time != 0.0f ? 1.0f / time : 0.0f;
	}

	// FUNCTION: ENGINE 0x102CCFB0
	// EQUIVALENT: the same operations in the same order (62 %); the engine keeps the constant and the first clamp in other
	// registers
	float BulletTracerState::GetTrailFade(const BulletTracerParams::Data* data, float time, float distance)
	{
		float fade = math::Clamp(1.0f - GetInverseFadeOutTrailTime(data) * time, 0.0f, 1.0f);
		if (data->startFadeDistance > 0.0f)
		{
			fade = math::Clamp(distance / data->startFadeDistance, 0.0f, 1.0f) * fade;
		}
		if (data->endFadeDistance > 0.0f)
		{
			fade = math::Clamp((length - distance) / data->endFadeDistance, 0.0f, 1.0f) * fade;
		}
		float grow = 1.0f;
		if (0.0f != GetInverseFadeInTrailTime(data))
		{
			float scaled = GetInverseFadeInTrailTime(data) * age;
			grow = math::Clamp(scaled / age * time, 0.0f, 1.0f);
		}
		return grow * fade;
	}

	// FUNCTION: ENGINE 0x102CD130
	float BulletTracerState::GetWidthFade(const BulletTracerParams::Data* data, float position)
	{
		float fade = math::Clamp(1.0f - GetInverseShrinkOutTime(data) * position, 0.0f, 1.0f);
		float grow = 1.0f;
		if (0.0f != GetInverseShrinkInTime(data))
		{
			float scaled = GetInverseShrinkInTime(data) * age;
			grow = math::Clamp(scaled / age * position, 0.0f, 1.0f);
		}
		return fade * grow;
	}

	// FUNCTION: ENGINE 0x102CDE90
	// EQUIVALENT: the same operations in the same order, all in SSE; the engine keeps the fade in a register through the
	// branches
	float BulletTracerState::GetFade(const BulletTracerParams::Data* data)
	{
		float fadeIn = data->fadeInTime;
		float elapsed = age - wait;
		float fade;
		if (fadeIn >= elapsed)
		{
			fade = elapsed / fadeIn;
		}
		else
		{
			float hold = data->generateTime + fadeIn;
			if (hold >= elapsed)
			{
				fade = 1.0f;
			}
			else
			{
				float fadeOut = data->fadeOutTime;
				if (fadeOut > 0.0f)
				{
					float out = (elapsed - hold) / fadeOut;
					if (out < 0.0f)
					{
						out = 0.0f;
					}
					if (out - 1.0f >= 0.0f)
					{
						out = 1.0f;
					}
					fade = 1.0f - out;
				}
				else
				{
					fade = 0.0f;
				}
			}
		}
		float trail = age - unknown140;
		float result = fade;
		if (trail >= 0.0f && trail > 0.0f)
		{
			float fadeOut = data->fadeOutTime;
			if (fadeOut > 0.0f)
			{
				float out = trail / fadeOut;
				if (out < 0.0f)
				{
					out = 0.0f;
				}
				if (out - 1.0f >= 0.0f)
				{
					out = 1.0f;
				}
				result = (1.0f - out) * fade;
			}
			else
			{
				result = 0.0f;
			}
		}
		return result;
	}

	static inline float Multiply(float a, float b)
	{
		return a * b;
	}

	// FUNCTION: ENGINE 0x102CDFB0
	// EQUIVALENT: the same operations in the same order (the squares add as (x + y) + z); the engine reads the age through an
	// SSE register and spills it twice
	float BulletTracerState::GetDistanceFade(const math::Vector* a, const math::Vector* b)
	{
		float dx = a->x - b->x;
		float dy = a->y - b->y;
		float dz = a->z - b->z;
		float squared = dx * dx;
		squared += dy * dy;
		squared += dz * dz;
		float distance = sqrtf(squared);
		float fraction = math::Clamp(distance / Multiply(speed, age), 0.0f, 1.0f);
		return Multiply(1.0f - fraction, age);
	}

	// A vertex of a ribbon: where it is, its texture coordinates and its colour
	struct TracerVertex
	{
		math::Vector position;
		float u;
		float v;
		math::Colour128 colour;
	};

	// Writes a vertex that was kept from the cut before
	static inline void Emit(pure3d::PrimStream* stream, const TracerVertex& vertex)
	{
		math::pddiColour colour(vertex.colour);
		stream->Vertex(vertex.u, vertex.v, *(unsigned int*)&colour, vertex.position.x, vertex.position.y, vertex.position.z);
	}

	// A list of up to 12 floats in place (the distances along the ribbon at which it is cut)
	class DistanceList
	{
	public:
		DistanceList() : last(values)
		{
		}
		void Add(float value)
		{
			if (last - values != 12)
			{
				new (last++) float(value);
			}
		}
		unsigned int Count() const
		{
			return last - values;
		}

		float values[12];
		float* last;
	};

	// FUNCTION: ENGINE 0x102CFF50
	// EQUIVALENT: the same operations in the same order; the vertices of the ribbon are written one by one from
	// expressions here, and the compiler keeps the intermediate values in other places and registers
	void BulletTracer::DrawLayer(int layer, const core::Name<core::CaseInsensitiveKey32>& name, BulletTracerState* state,
		const BulletTracerParams::Data* data, pure3d::Shader* shader)
	{
		Unknown4(shader);
		math::Matrix view(*pure3d::pddi->GetUnknown10614840());
		float length = state->length;
		float headX = state->position.x;
		float headY = state->position.y;
		float headZ = state->position.z;
		float back = -length;
		float tailX = state->direction.x * back + headX;
		float tailY = state->direction.y * back + headY;
		float tailZ = state->direction.z * back + headZ;
		math::Vector tail;
		tail.Set(tailX, tailY, tailZ);
		view.Invert();
		math::Vector camera;
		camera.Set(view.m[3][0], view.m[3][1], view.m[3][2]);
		math::Vector toTail;
		toTail.Set(tailX - camera.x, tailY - camera.y, tailZ - camera.z);
		toTail.NormalizeFast();
		math::Vector toHead;
		toHead.Set(headX - camera.x, headY - camera.y, headZ - camera.z);
		toHead.NormalizeFast();
		math::Vector axis;
		axis.Set(headX - tailX, headY - tailY, headZ - tailZ);
		axis.NormalizeFast();
		math::Vector tailSide;
		tailSide.Cross(axis, toTail);
		math::Vector headSide;
		headSide.Cross(axis, toHead);
		if (!(sqrtf(tailSide.z * tailSide.z + tailSide.y * tailSide.y + tailSide.x * tailSide.x) > 0.0f)
			|| !(sqrtf(headSide.z * headSide.z + headSide.y * headSide.y + headSide.x * headSide.x) > 0.0f))
		{
			return;
		}
		tailSide.NormalizeFast();
		headSide.NormalizeFast();

		// The texture scroll of the ribbon
		float scroll = 0.0f;
		if (layer == 0)
		{
			scroll = state->headScroll;
		}
		else if (layer == 1)
		{
			scroll = state->tailScroll;
		}

		// How the fade acts on the colour: on every channel of an additive ribbon, on the alpha of a blended one
		math::Vector4 factors;
		if (shader->parameters.blendMode == 1 && shader->parameters.blendFactor == 1)
		{
			factors.x = 1.0f;
			factors.y = 1.0f;
			factors.z = 1.0f;
			factors.w = 0.0f;
		}
		else if (shader->parameters.blendMode == 1 && shader->parameters.blendFactor == 7)
		{
			factors.x = 1.0f;
			factors.y = 1.0f;
			factors.z = 1.0f;
			factors.w = 1.0f;
		}
		else if (shader->parameters.blendMode == 6 && shader->parameters.blendFactor == 7)
		{
			factors.x = 0.0f;
			factors.y = 0.0f;
			factors.z = 0.0f;
			factors.w = 1.0f;
		}
		else
		{
			factors.x = 0.0f;
			factors.y = 0.0f;
			factors.z = 0.0f;
			factors.w = 0.0f;
		}

		math::Vector4 startColour = data->startColour;
		math::Vector4 endColour = data->endColour;
		float halfWidth = data->thickness * 0.5f;
		ScaleColour(&startColour, state->GetFade(data), &factors);
		ScaleColour(&endColour, state->GetFade(data), &factors);

		// The corners of the ribbon at its tail and its head, and the edges between them
		float tailLeftX = tailX - tailSide.x * halfWidth;
		float tailLeftY = tailY - tailSide.y * halfWidth;
		float tailLeftZ = tailZ - tailSide.z * halfWidth;
		float tailRightX = tailSide.x * halfWidth + tailX;
		float tailRightY = tailSide.y * halfWidth + tailY;
		float tailRightZ = tailSide.z * halfWidth + tailZ;
		float headRightX = headSide.x * halfWidth + headX;
		float headRightY = headSide.y * halfWidth + headY;
		float headRightZ = headSide.z * halfWidth + headZ;
		math::Vector leftEdge;
		leftEdge.Set((headX - headSide.x * halfWidth) - tailLeftX, (headY - headSide.y * halfWidth) - tailLeftY,
			(headZ - headSide.z * halfWidth) - tailLeftZ);
		leftEdge.NormalizeFast();
		math::Vector rightEdge;
		rightEdge.Set(headRightX - tailRightX, headRightY - tailRightY, headRightZ - tailRightZ);
		rightEdge.NormalizeFast();
		float textureScale = (length / data->textureLength + scroll) - scroll;

		// The ends of the part of the ribbon that is shown: the head has shrunk away from the far end for the
		// shrink out time, the near end follows over the shrink in time
		float shown = 0.0f;
		if (0.0f < data->shrinkOutTime)
		{
			shown = state->age - data->shrinkOutTime;
			if (shown <= 0.0f)
			{
				shown = 0.0f;
			}
			shown = state->speed * shown;
			if (!(0.0f <= shown))
			{
				shown = 0.0f;
			}
		}
		if (0.0f <= shown - length)
		{
			shown = length;
		}
		float lowEnd = length - state->speed * data->shrinkInTime;
		if (lowEnd < 0.0f)
		{
			lowEnd = 0.0f;
		}
		if (0.0f <= lowEnd - length)
		{
			lowEnd = length;
		}
		float highEnd = shown;
		if (shown < lowEnd)
		{
			highEnd = lowEnd;
			lowEnd = shown;
		}

		// The distances along the ribbon at which it is cut: its middle, the ends of the fades at its head and tail, and
		// four steps between each end of the shown part and the middle
		DistanceList cuts;
		cuts.Add((highEnd + lowEnd) * 0.5f);
		float nearFade = data->startFadeDistance;
		if (length <= nearFade)
		{
			nearFade = length;
		}
		cuts.Add(nearFade);
		float fadeEnd = length - data->endFadeDistance;
		float farFade = 0.0f;
		if (0.0f <= fadeEnd)
		{
			farFade = fadeEnd;
		}
		cuts.Add(farFade);
		for (unsigned int i = 0; i < 4; i++)
		{
			float step = (float)i * (1.0f / 3.0f);
			cuts.Add(step * (cuts.values[0] - lowEnd) + lowEnd);
		}
		for (unsigned int i = 0; i < 4; i++)
		{
			float step = (float)i * (1.0f / 3.0f);
			cuts.Add(step * (length - highEnd) + highEnd);
		}
		void (*sort)(float*, float*) = std::sort<float*>;
		sort(cuts.values, cuts.last);

		pure3d::PrimStream* stream = pure3d::context->primStream;
		stream->Begin(shader, 0, 0x2021, 0x5a, name, &shader->parameters);
		ScaleColour(&startColour, state->GetTrailFade(data, state->age, 0.0f), &factors);

		float inverseLength = 1.0f / length;
		TracerVertex previousLeft;
		TracerVertex previousCentre;
		TracerVertex previousRight;
		for (unsigned int index = 0; index < cuts.Count(); index++)
		{
			float distance = cuts.values[index];
			float along = inverseLength * distance;
			math::Vector point;
			point.Set(leftEdge.x * distance + tailX, leftEdge.y * distance + tailY, leftEdge.z * distance + tailZ);
			float fade = state->GetDistanceFade(&point, &tail);
			math::Vector4 colour;
			colour.x = (endColour.x - startColour.x) * along + startColour.x;
			colour.y = (endColour.y - startColour.y) * along + startColour.y;
			colour.z = (endColour.z - startColour.z) * along + startColour.z;
			colour.w = (endColour.w - startColour.w) * along + startColour.w;
			ScaleColour(&colour, state->GetTrailFade(data, fade, distance), &factors);
			float width = state->GetWidthFade(data, fade);
			float leftX = (tailLeftX - tailX) * width + tailX;
			float leftY = (tailLeftY - tailY) * width + tailY;
			float leftZ = (tailLeftZ - tailZ) * width + tailZ;
			float rightX = (tailRightX - tailX) * width + tailX;
			float rightY = (tailRightY - tailY) * width + tailY;
			float rightZ = (tailRightZ - tailZ) * width + tailZ;
			float centreX = (rightX - leftX) * 0.5f + leftX;
			float centreY = (rightY - leftY) * 0.5f + leftY;
			float centreZ = (rightZ - leftZ) * 0.5f + leftZ;
			math::pddiColour packed(colour);
			unsigned int bits = *(unsigned int*)&packed;
			float u = along * textureScale + scroll;
			if (index != 0)
			{
				if (index < 6)
				{
					stream->Vertex(u, 1.0f, bits, leftEdge.x * distance + leftX, leftEdge.y * distance + leftY,
						leftEdge.z * distance + leftZ);
					stream->Vertex(u, 0.5f, bits, centreX + leftEdge.x * distance, leftEdge.y * distance + centreY,
						leftEdge.z * distance + centreZ);
					Emit(stream, previousLeft);
					stream->Vertex(u, 0.5f, bits, centreX + leftEdge.x * distance, leftEdge.y * distance + centreY,
						leftEdge.z * distance + centreZ);
					Emit(stream, previousLeft);
					Emit(stream, previousRight);
					stream->Vertex(u, 0.5f, bits, centreX + leftEdge.x * distance, leftEdge.y * distance + centreY,
						leftEdge.z * distance + centreZ);
					Emit(stream, previousRight);
					stream->Vertex(u, 0.0f, bits, rightX + rightEdge.x * distance, rightEdge.y * distance + rightY,
						rightEdge.z * distance + rightZ);
				}
				else
				{
					Emit(stream, previousLeft);
					Emit(stream, previousCentre);
					stream->Vertex(u, 1.0f, bits, leftEdge.x * distance + leftX, leftEdge.y * distance + leftY,
						leftEdge.z * distance + leftZ);
					Emit(stream, previousCentre);
					stream->Vertex(u, 1.0f, bits, leftEdge.x * distance + leftX, leftEdge.y * distance + leftY,
						leftEdge.z * distance + leftZ);
					stream->Vertex(u, 0.0f, bits, rightEdge.x * distance + rightX, rightEdge.y * distance + rightY,
						rightEdge.z * distance + rightZ);
					Emit(stream, previousCentre);
					stream->Vertex(u, 0.0f, bits, rightEdge.x * distance + rightX, rightEdge.y * distance + rightY,
						rightEdge.z * distance + rightZ);
					Emit(stream, previousRight);
				}
			}
			previousLeft.position.Set(leftX + leftEdge.x * distance, leftEdge.y * distance + leftY, leftEdge.z * distance + leftZ);
			previousLeft.u = u;
			previousLeft.v = 1.0f;
			previousLeft.colour = math::Colour128(packed);
			previousCentre.position.Set(centreX + leftEdge.x * distance, leftEdge.y * distance + centreY,
				leftEdge.z * distance + centreZ);
			previousCentre.u = u;
			previousCentre.v = 0.5f;
			previousCentre.colour = previousLeft.colour;
			previousRight.position.Set(rightX + rightEdge.x * distance, rightEdge.y * distance + rightY,
				rightEdge.z * distance + rightZ);
			previousRight.u = u;
			previousRight.v = 0.0f;
			previousRight.colour = previousLeft.colour;
		}
		stream->End();
	}
}
