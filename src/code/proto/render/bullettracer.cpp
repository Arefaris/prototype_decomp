// proto::BulletTracer, BulletTracerState and the helpers of their unit (code/proto/render/bullettracer.cpp, 0x102CC000 -
// 0x102D2500; the path is a guess from the class names). Names are guesses.
#include "code/content/colourmetatype.h"
#include "code/core/refptr.h"
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

namespace engine
{
	namespace driving
	{
		extern const float gZero;
	}
}

namespace proto
{
#define PROTO_OFFSET(type, member) 	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define PROTO_NAME_OFFSET(type, member) 	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

	// FUNCTION: ENGINE 0x102CCC70
	content::ClassInfo* BulletTracerParams::Data::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::BulletTracerParams::Data";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102CCCB0
	content::ClassInfo* BulletTracerProfile::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "proto::BulletTracerProfile";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102CE670
	content::MemberList* BulletTracerParams::Data::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberPrimitiveMetaType<Data, float, 0>("p"), PROTO_OFFSET(Data, fadeInTime), "fadeInTime" },
			{ content::GetMemberPrimitiveMetaType<Data, float, 1>("p"), PROTO_OFFSET(Data, fadeOutTime),
				"fadeOutTime" },
			{ content::GetMemberPrimitiveMetaType<Data, float, 2>("p"), PROTO_OFFSET(Data, startFadeDistance),
				"startFadeDistance" },
			{ content::GetMemberPrimitiveMetaType<Data, float, 3>("p"), PROTO_OFFSET(Data, endFadeDistance),
				"endFadeDistance" },
			{ content::GetMemberPrimitiveMetaType<Data, float, 4>("p"), PROTO_OFFSET(Data, generateTime),
				"generateTime" },
			{ content::GetMemberPrimitiveMetaType<Data, float, 5>("p"), PROTO_OFFSET(Data, fadeInTrailTime),
				"fadeInTrailTime" },
			{ content::GetMemberPrimitiveMetaType<Data, float, 6>("p"), PROTO_OFFSET(Data, fadeOutTrailTime),
				"fadeOutTrailTime" },
			{ content::GetMemberPrimitiveMetaType<Data, float, 7>("p"), PROTO_OFFSET(Data, shrinkInTime),
				"shrinkInTime" },
			{ content::GetMemberPrimitiveMetaType<Data, float, 8>("p"), PROTO_OFFSET(Data, shrinkOutTime),
				"shrinkOutTime" },
			{ content::GetMemberPrimitiveMetaType<Data, float, 9>("p"), PROTO_OFFSET(Data, thickness), "thickness" },
			{ content::GetMemberPrimitiveMetaType<Data, float, 10>("p"), PROTO_OFFSET(Data, textureLength),
				"textureLength" },
			{ content::GetMemberPrimitiveMetaType<Data, float, 11>("p"), PROTO_OFFSET(Data, textureScrollRate),
				"textureScrollRate" },
			{ content::GetMemberColourMetaType<Data, 0>("p"), content::MemberOffset((math::Colour128*)0x38, 0x38),
				"startColour" },
			{ content::GetMemberColourMetaType<Data, 1>("p"), content::MemberOffset((math::Colour128*)0x48, 0x48),
				"endColour" }
		};
		sList.members = sMembers;
		sList.count = 14;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102CF0F0
	content::MemberList* BulletTracerProfile::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetClassMetaType<BulletTracerParams::Data>(), PROTO_OFFSET(BulletTracerProfile, head), "head" },
			{ content::GetClassMetaType<BulletTracerParams::Data>(), PROTO_OFFSET(BulletTracerProfile, tail), "tail" },
			{ content::GetMemberPrimitiveMetaType<BulletTracerProfile, float, 0>("p"),
				PROTO_OFFSET(BulletTracerProfile, wait), "wait" },
			{ content::GetMemberVectorMetaType<BulletTracerProfile, 0>("p"), 0xCC, "offset" },
			{ content::GetNameMetaType<BulletTracerProfile>(true, true, "p"),
				PROTO_NAME_OFFSET(BulletTracerProfile, headShaderName), "headShaderName" },
			{ content::GetMemberNameMetaType<BulletTracerProfile, 1>(true, true, "p"),
				PROTO_NAME_OFFSET(BulletTracerProfile, tailShaderName), "tailShaderName" }
		};
		sList.members = sMembers;
		sList.count = 6;
		return &sList;
	}

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
	float BulletTracerState::GetTrailFade(const BulletTracerParams::Data* data, float time, float distance)
	{
		float fade = math::Clamp(1.0f - GetInverseFadeOutTrailTime(data) * time, 0.0f, 1.0f);
		float grow = 1.0f;
		if (0.0f < data->startFadeDistance)
		{
			fade = math::Clamp(distance / data->startFadeDistance, 0.0f, 1.0f) * fade;
		}
		if (0.0f < data->endFadeDistance)
		{
			fade = math::Clamp((length - distance) / data->endFadeDistance, 0.0f, 1.0f) * fade;
		}
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
	float BulletTracerState::GetFade(const BulletTracerParams::Data* data)
	{
		float elapsed = age - wait;
		float fadeIn = data->fadeInTime;
		float fade = fadeIn >= elapsed ? elapsed / fadeIn
			: data->generateTime + fadeIn >= elapsed ? 1.0f
			: data->fadeOutTime > 0.0f
				? 1.0f - math::Clamp((elapsed - (data->generateTime + fadeIn)) / data->fadeOutTime, 0.0f, 1.0f)
				: 0.0f;
		float trail = age - unknown140;
		float result = fade;
		if (!(0.0f > trail) && 0.0f < trail)
		{
			float fadeOut = data->fadeOutTime;
			if (0.0f < fadeOut)
			{
				float out = math::Clamp(trail / fadeOut, 0.0f, 1.0f);
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

	// FUNCTION: ENGINE 0x102CF450
	BulletTracerState::BulletTracerState(pure3d::Primitive* newPrimitive, const BulletTracerSetup* setup)
		: pure3d::PrimitiveState(newPrimitive), owner(setup->owner), head(setup->head), tail(setup->tail)
	{
		wait = setup->wait;
		local.x = setup->localX;
		local.y = setup->localY;
		local.z = setup->localZ;
		jointIndex = setup->jointIndex;
		age = 0.0f;
		headScroll = 0.0f;
		tailScroll = 0.0f;
		unknown114 = setup->unknownBC;
		unknown118 = setup->unknownC0;
		unknown11C = setup->unknownC4;
		unknown120 = setup->unknownC8;
		unknown124 = setup->unknownC8;
		unknown128 = setup->unknownCC;
		unknown12C = setup->unknownD0;
		speed = setup->unknownC8;
		unknown134 = setup->unknownD4;
		unknown138 = 0.0f;
		length = 0.0f;
		unknown140 = 1000000.0f;
		UpdateMuzzle();
	}

	// FUNCTION: ENGINE 0x102CF600
	BulletTracerState::BulletTracerState(const BulletTracerState& other) : pure3d::PrimitiveState(other.primitive),
		owner(other.owner), head(other.head), tail(other.tail)
	{
		wait = other.wait;
		local.x = other.local.x;
		local.y = other.local.y;
		local.z = other.local.z;
		jointIndex = other.jointIndex;
		age = 0.0f;
		headScroll = 0.0f;
		tailScroll = 0.0f;
		unknown114 = other.unknown114;
		unknown118 = other.unknown118;
		unknown11C = other.unknown11C;
		unknown120 = other.unknown120;
		unknown124 = other.unknown124;
		unknown128 = other.unknown128;
		unknown12C = other.unknown12C;
		speed = other.speed;
		unknown134 = other.unknown134;
		unknown138 = other.unknown138;
		length = other.length;
		unknown140 = other.unknown140;
		UpdateMuzzle();
	}

	// FUNCTION: ENGINE 0x102CF780
	pure3d::PrimitiveState* BulletTracerState::Unknown3()
	{
		return new BulletTracerState(*this);
	}

	// FUNCTION: ENGINE 0x102CDAE0
	// NONMATCHING: the operations and their order are the engine's; the engine reads the updated position back from the
	// object where ours forwards the stored values, and orders the loads differently (about 47 %)
#ifdef NONMATCHING
	void BulletTracerState::Update(float dt)
	{
		dt = dt * 0.001f;
		age = age + dt;
		headScroll = head.textureScrollRate * dt + headScroll;
		tailScroll = tail.textureScrollRate * dt + tailScroll;
		if (unknown140 > 1000.0f)
		{
			if (0.0f >= unknown128)
			{
				unknown120 = unknown12C;
			}
			else
			{
				float rate = unknown120 + unknown128 * dt;
				unknown120 = rate;
				if (rate > unknown12C)
				{
					rate = unknown12C;
				}
				unknown120 = rate;
			}
			math::Vector previous;
			float step = unknown120 * dt;
			previous.z = position.z;
			previous.y = position.y;
			previous.x = position.x;
			position.y = unknown118 * step + position.y;
			position.z = unknown11C * step + position.z;
			position.x = previous.x + unknown114 * step;
			if (unknown134 > engine::driving::gZero)
			{
				unknown138 = unknown134 * dt + unknown138;
				position.y = position.y - unknown138 * dt;
			}
			else
			{
				previous.x = offset.x;
				previous.y = offset.y;
				previous.z = offset.z;
			}
			if (!(fabsf(previous.x - position.x) <= 0.00001f && fabsf(previous.y - position.y) <= 0.00001f
				&& fabsf(previous.z - position.z) <= 0.00001f))
			{
				direction.x = position.x - previous.x;
				direction.y = position.y - previous.y;
				direction.z = position.z - previous.z;
				direction.Normalize();
			}
			float dx = offset.x - position.x;
			float dy = offset.y - position.y;
			float dz = offset.z - position.z;
			length = sqrtf(dz * dz + dy * dy + dx * dx);
			speed = length / age;
		}
	}
#endif

	// FUNCTION: ENGINE 0x102CCE90
	void BulletTracerState::Unknown5()
	{
	}

	// FUNCTION: ENGINE 0x102CDE00
	float BulletTracerState::GetDuration()
	{
		float headTime = head.generateTime + head.fadeOutTime + head.fadeInTime;
		float tailTime = tail.generateTime + tail.fadeOutTime + tail.fadeInTime;
		float longest = tailTime > headTime ? tailTime : headTime;
		return wait + longest;
	}

	// FUNCTION: ENGINE 0x102CDE60
	bool BulletTracerState::Unknown6()
	{
		return age >= GetDuration();
	}

	// FUNCTION: ENGINE 0x102CD220
	void BulletTracerState::GetBoundingBox(math::AABB* box)
	{
		primitive->GetBoundingBox(box);
	}

	// FUNCTION: ENGINE 0x102CEC70
	BulletTracer::BulletTracer(pure3d::Shader* head, pure3d::Shader* tail) : pure3d::Primitive(0x2000), headShader(0),
		tailShader(0)
	{
		Unknown4(head);
		flagWord.SetBit(3, true);
		core::RefAssign(headShader, head);
		core::RefAssign(tailShader, tail);
	}

	// FUNCTION: ENGINE 0x102CE070
	BulletTracer::~BulletTracer()
	{
		core::SafeRelease(headShader);
		core::SafeRelease(tailShader);
	}

	// FUNCTION: ENGINE 0x102D2000
	void BulletTracer::Draw(const core::Name<core::CaseInsensitiveKey32>* shader, pure3d::PrimitiveState* state,
		const math::Matrix* world, const pure3d::PrimStreamParameters* parameters, pure3d::PartBinding* binding)
	{
		int cullMode = pure3d::pddi->GetCullMode();
		pure3d::pddi->SetCullMode(0);
		pure3d::pddi->SetWorldMatrix(&math::Matrix::IDENTITY);
		BulletTracerState* tracer = static_cast<BulletTracerState*>(state);
		if (tracer)
		{
			DrawLayer(1, reinterpret_cast<const char*>(shader), tracer, &tracer->tail, tailShader);
			DrawLayer(0, reinterpret_cast<const char*>(shader), tracer, &tracer->head, headShader);
		}
		pure3d::pddi->SetCullMode(cullMode);
	}

	// FUNCTION: ENGINE 0x102CD250
	void BulletTracer::GetBoundingBox(math::AABB* box)
	{
		box->max.x = 10000.0f;
		box->max.y = 10000.0f;
		box->max.z = 10000.0f;
		box->min.x = -10000.0f;
		box->min.y = -10000.0f;
		box->min.z = -10000.0f;
	}

	// The centre is a Vector4 but the caller's pointer (the vftable takes a Vector) is followed by a fourth float in
	// the engine too
	// FUNCTION: ENGINE 0x102CD2A0
	void BulletTracer::GetCentre(math::Vector* centre)
	{
		centre[0].x = 0.0f;
		centre[0].y = 0.0f;
		centre[0].z = 0.0f;
		centre[1].x = 10000.0f;
	}

	// FUNCTION: ENGINE 0x102CD230
	bool BulletTracer::FillBatch(void* batch, pure3d::PrimitiveState* state, bool* unknown)
	{
		*unknown = false;
		return false;
	}

	// FUNCTION: ENGINE 0x102CE0A0
	int BulletTracer::Unknown8()
	{
		return 0;
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102CC260
// FUNCTION: ENGINE 0x102CD240
// FUNCTION: ENGINE 0x102CD2D0
// FUNCTION: ENGINE 0x102CD2E0
// FUNCTION: ENGINE 0x102CD330
// FUNCTION: ENGINE 0x102CD370
// FUNCTION: ENGINE 0x102CD380
// FUNCTION: ENGINE 0x102CD3C0
// FUNCTION: ENGINE 0x102CD3D0
// FUNCTION: ENGINE 0x102CD410
// FUNCTION: ENGINE 0x102CD450
// FUNCTION: ENGINE 0x102CD520
// FUNCTION: ENGINE 0x102CD530
// FUNCTION: ENGINE 0x102CD550
// FUNCTION: ENGINE 0x102CD560
// FUNCTION: ENGINE 0x102CD570
// FUNCTION: ENGINE 0x102CD590
// FUNCTION: ENGINE 0x102CD600
// FUNCTION: ENGINE 0x102CD610
// FUNCTION: ENGINE 0x102CD620
// FUNCTION: ENGINE 0x102CE150
// FUNCTION: ENGINE 0x102CE190
// FUNCTION: ENGINE 0x102CE1D0
// FUNCTION: ENGINE 0x102CE210
// FUNCTION: ENGINE 0x102CE250
// FUNCTION: ENGINE 0x102CE290
// FUNCTION: ENGINE 0x102CE2D0
// FUNCTION: ENGINE 0x102CE310
// FUNCTION: ENGINE 0x102CE350
// FUNCTION: ENGINE 0x102CE390
// FUNCTION: ENGINE 0x102CE3D0
// FUNCTION: ENGINE 0x102CE410
// FUNCTION: ENGINE 0x102CE450
// FUNCTION: ENGINE 0x102CE4A0
// FUNCTION: ENGINE 0x102CE4B0
// FUNCTION: ENGINE 0x102CE5F0
// FUNCTION: ENGINE 0x102CED20
// FUNCTION: ENGINE 0x102CFDC0
// FUNCTION: ENGINE 0x102D2370

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102CF5C0
// FUNCTION: ENGINE 0x102CD910
// FUNCTION: ENGINE 0x102CECF0
// FUNCTION: ENGINE 0x102CF5D0
