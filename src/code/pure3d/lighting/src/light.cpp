// pure3d::Light and the light bit sets (unit around 0x1075B000 - 0x1075CD00; file name guessed). Names are guesses.
#include "code/engine/driving/carattributes.h"
#include <math.h>
#include "code/core/refptr.h"
#include "code/pure3d/context.h"
#include "code/pure3d/light.h"
#include "code/pure3d/lighting.h"
#include "code/pure3d/primitive.h"

// This unit's copies of the reference helpers for the user data and the shadow parameters of a light
// FUNCTION: ENGINE 0x10758BE0
template void core::RefAssign<pure3d::LightUserData>(pure3d::LightUserData*& pointer, pure3d::LightUserData* object);

// FUNCTION: ENGINE 0x10758C10
template void core::SafeRelease<pure3d::LightUserData>(pure3d::LightUserData*& object);

// FUNCTION: ENGINE 0x10758C30
template void core::SafeRelease<pure3d::RenderParams>(pure3d::RenderParams*& object);

// FUNCTION: ENGINE 0x10758C50
template void core::RefAssign<pure3d::RenderParams>(pure3d::RenderParams*& pointer, pure3d::RenderParams* object);

namespace pure3d
{	float gLightMax120;
	float gLightMax124;
	int gLightSerial;

	// FUNCTION: ENGINE 0x107582A0
	LightUserData* Light::GetUserData()
	{
		return userData;
	}

	// FUNCTION: ENGINE 0x107582B0
	void Light::SetUnknown158(bool value)
	{
		unknown158 = value;
	}

	// FUNCTION: ENGINE 0x107582C0
	bool Light::GetUnknown158()
	{
		return unknown158;
	}

	// FUNCTION: ENGINE 0x107582D0
	void Light::SetColour(const math::Vector4* newColour)
	{
		colour = *newColour;
	}

	// FUNCTION: ENGINE 0x10758300
	const math::Vector4* Light::GetColour()
	{
		return &colour;
	}

	// FUNCTION: ENGINE 0x10758310
	void Light::SetPosition(const math::Vector* newPosition)
	{
		position.x = newPosition->x;
		position.y = newPosition->y;
		position.z = newPosition->z;
		_ReadWriteBarrier();
		dirty |= 0x1E;
	}

	// FUNCTION: ENGINE 0x10758340
	const math::Vector* Light::GetPosition()
	{
		return &position;
	}

	// FUNCTION: ENGINE 0x10758350
	void Light::SetDirection(const math::Vector* newDirection)
	{
		direction.x = newDirection->x;
		direction.y = newDirection->y;
		direction.z = newDirection->z;
		_ReadWriteBarrier();
		dirty |= 0x1F;
	}

	// FUNCTION: ENGINE 0x10758380
	const math::Vector* Light::GetDirection()
	{
		return &direction;
	}

	// FUNCTION: ENGINE 0x10758390
	void Light::SetUnknownF0(const math::Vector* value)
	{
		unknownF0.x = value->x;
		unknownF0.y = value->y;
		unknownF0.z = value->z;
		_ReadWriteBarrier();
		dirty |= 0x1F;
	}

	// FUNCTION: ENGINE 0x107583C0
	void Light::SetUnknown120(float value)
	{
		if (!(value >= 0.0f))
		{
			value = 0.0f;
		}
		if (value - gLightMax120 >= 0.0f)
		{
			value = gLightMax120;
		}
		dirty |= 0x3E;
		unknown120 = value;
	}

	// FUNCTION: ENGINE 0x10758400
	float Light::GetUnknown120()
	{
		return unknown120;
	}

	// FUNCTION: ENGINE 0x10758410
	void Light::SetUnknown124(float value)
	{
		if (!(value >= 0.0f))
		{
			value = 0.0f;
		}
		if (value - gLightMax124 >= 0.0f)
		{
			value = gLightMax124;
		}
		dirty |= 0x3E;
		unknown124 = value;
	}

	// FUNCTION: ENGINE 0x10758450
	void Light::SetUnknown130(bool value)
	{
		unknown130 = value;
	}

	// FUNCTION: ENGINE 0x10758460
	bool Light::GetUnknown130()
	{
		return unknown130;
	}

	// FUNCTION: ENGINE 0x10758470
	Texture* Light::GetUnknown134()
	{
		return unknown134;
	}

	// FUNCTION: ENGINE 0x10758480
	float Light::GetUnknown12C()
	{
		return unknown12C;
	}

	// FUNCTION: ENGINE 0x10758490
	void Light::SetDecay(const DecayRange* newDecay)
	{
		decay = *newDecay;
		dirty |= 0x3E;
	}

	// FUNCTION: ENGINE 0x107584D0
	DecayRange* Light::GetDecay()
	{
		return &decay;
	}

	// FUNCTION: ENGINE 0x107584F0
	void Light::SetUnknown194(float a, float b, float c)
	{
		unknown194 = a;
		unknown198 = b;
		unknown19C = c;
	}

	// FUNCTION: ENGINE 0x10758520
	void Light::GetUnknown194(float* a, float* b, float* c)
	{
		*a = unknown194;
		*b = unknown198;
		*c = unknown19C;
	}

	// FUNCTION: ENGINE 0x10758550
	RenderParams* Light::GetShadow()
	{
		return shadow;
	}

	// FUNCTION: ENGINE 0x10758560
	bool Light::IsEnabled()
	{
		return enabled;
	}

	// FUNCTION: ENGINE 0x10758570
	void Light::SetUnknown164(int value)
	{
		unknown164 = value;
	}

	// FUNCTION: ENGINE 0x10758580
	int Light::GetUnknown164()
	{
		return unknown164;
	}

	// FUNCTION: ENGINE 0x10758590
	void Light::SetUnknown168(float value)
	{
		unknown168 = value;
	}

	// FUNCTION: ENGINE 0x107585B0
	float Light::GetUnknown168()
	{
		return unknown168;
	}

	// FUNCTION: ENGINE 0x107585C0
	void Light::SetUnknown16C(float value)
	{
		unknown16C = value;
	}

	// FUNCTION: ENGINE 0x107585E0
	float Light::GetUnknown16C()
	{
		return unknown16C;
	}

	// FUNCTION: ENGINE 0x107585F0
	void Light::SetUnknown170(bool value)
	{
		unknown170 = value;
	}

	// FUNCTION: ENGINE 0x10758600
	bool Light::GetUnknown170()
	{
		return unknown170;
	}

	// FUNCTION: ENGINE 0x10758610
	Texture* Light::GetUnknown138()
	{
		return unknown138;
	}

	// FUNCTION: ENGINE 0x10758620
	void Light::SetUnknown13C(float value)
	{
		unknown13C = value;
	}

	// FUNCTION: ENGINE 0x10758640
	float Light::GetUnknown13C()
	{
		return unknown13C;
	}

	// FUNCTION: ENGINE 0x10758650
	void Light::SetUnknown140(float a, float b)
	{
		unknown140 = a;
		unknown144 = b;
	}

	// FUNCTION: ENGINE 0x10758670
	float* Light::GetUnknown140()
	{
		return &unknown140;
	}

	// FUNCTION: ENGINE 0x10758680
	void Light::SetUnknown148(float a, float b)
	{
		unknown148 = a;
		unknown14C = b;
	}

	// FUNCTION: ENGINE 0x107586A0
	float* Light::GetUnknown148()
	{
		return &unknown148;
	}

	// FUNCTION: ENGINE 0x107586B0
	void Light::SetUnknown150(int a, int b)
	{
		unknown150 = a;
		unknown154 = b;
	}

	// FUNCTION: ENGINE 0x107586D0
	int Light::GetUnknown150()
	{
		return unknown150;
	}

	// FUNCTION: ENGINE 0x107586E0
	int Light::GetUnknown154()
	{
		return unknown154;
	}

	// FUNCTION: ENGINE 0x107586F0
	void Light::SetUnknown11C(float value)
	{
		unknown11C = value;
	}

	// FUNCTION: ENGINE 0x10758710
	float Light::GetUnknown11C()
	{
		return unknown11C;
	}

	// FUNCTION: ENGINE 0x10758720
	void Light::SetUnknown128(float value)
	{
		if (!(value >= 0.0f))
		{
			value = 0.0f;
		}
		if (value - engine::driving::gOne >= 0.0f)
		{
			unknown128 = engine::driving::gOne;
			return;
		}
		unknown128 = value;
	}

	// FUNCTION: ENGINE 0x10758760
	float Light::GetUnknown10758760()
	{
		return unknown128;
	}

	// FUNCTION: ENGINE 0x10758770
	float Light::GetUnknown17C()
	{
		return unknown17C;
	}

	// FUNCTION: ENGINE 0x10758780
	float Light::GetUnknown180()
	{
		return unknown180;
	}

	// FUNCTION: ENGINE 0x10758790
	float Light::GetUnknown184()
	{
		return unknown184;
	}

	// FUNCTION: ENGINE 0x107587A0
	void Light::SetUnknown188(bool value)
	{
		unknown188 = value;
	}

	// FUNCTION: ENGINE 0x107587B0
	bool Light::GetUnknown188()
	{
		return unknown188;
	}

	// FUNCTION: ENGINE 0x107587C0
	void Light::SetUnknown107587C0(float value)
	{
	}

	// FUNCTION: ENGINE 0x107587D0
	float Light::GetUnknown107587D0()
	{
		return 1.0f;
	}

	// FUNCTION: ENGINE 0x107587E0
	bool Light::GetUnknown190()
	{
		return unknown190;
	}

	// FUNCTION: ENGINE 0x107587F0
	void Light::SetUnknown190(bool value)
	{
		unknown190 = value;
	}

	// FUNCTION: ENGINE 0x10758800
	bool Light::GetUnknown216()
	{
		return unknown216;
	}

	// FUNCTION: ENGINE 0x10758810
	void Light::SetUnknown216(bool value)
	{
		unknown216 = value;
	}

	// FUNCTION: ENGINE 0x10758820
	int Light::GetUnknown20C()
	{
		return unknown20C;
	}

	// FUNCTION: ENGINE 0x10758830
	void Light::SetUnknown20C(int value)
	{
		unknown20C = value;
	}

	// FUNCTION: ENGINE 0x10758840
	// NONMATCHING: the engine reloads the components of unknownF0 for the second test, ours keeps them in the x87 stack (12.6 %)
#ifdef NONMATCHING
	void Light::UpdateAxes()
	{
		math::Vector& up = unknownF0;
		math::Vector& side = unknownFC;
		if (fabsf(up.x * up.x + up.y * up.y + up.z * up.z - engine::driving::gOne) <= 0.00001f &&
			fabsf(up.z * direction.z + up.y * direction.y + direction.x * up.x) <= 0.00001f)
		{
			side.Cross(up, direction);
			side.NormalizeFast();
			dirty &= ~1;
			return;
		}
		up.x = 0.0f;
		up.y = engine::driving::gOne;
		up.z = 0.0f;
		if (fabsf(direction.y) > 0.999f)
		{
			up.x = engine::driving::gOne;
			up.y = 0.0f;
			up.z = 0.0f;
		}
		side.Cross(up, direction);
		side.NormalizeFast();
		up.Cross(direction, side);
		up.NormalizeFast();
		dirty &= ~1;
	}
#endif

	// FUNCTION: ENGINE 0x10758A40
	void Light::NextSerial()
	{
		serial = ++gLightSerial;
	}

	// FUNCTION: ENGINE 0x10758AC0
	// EQUIVALENT: the same stores in the same order; the engine loads the third constant before the store of the kind, ours
	// after it (80.0 %)
	DecayRange::DecayRange()
	{
		unknown4 = 5.0f;
		range = 25.0f;
		kind = 1;
		unknownC = engine::driving::gHalf;
		unknown10 = 0;
	}

	// FUNCTION: ENGINE 0x10758B00
	void DecayRange::SetKind(int newKind)
	{
		kind = newKind;
	}

	// FUNCTION: ENGINE 0x10758B10
	int DecayRange::GetKind()
	{
		return kind;
	}

	// FUNCTION: ENGINE 0x10758B20
	float DecayRange::GetUnknown10758B20()
	{
		return kind == 0 ? 0.0f : unknown4;
	}

	// FUNCTION: ENGINE 0x10758B50
	float DecayRange::GetRange()
	{
		return kind == 0 ? 10000.0f : range;
	}

	// FUNCTION: ENGINE 0x10758CB0
	void Light::SetUserData(LightUserData* newData)
	{
		core::RefAssign(userData, newData);
	}

	// FUNCTION: ENGINE 0x10758CD0
	math::Vector* Light::GetAxisF0()
	{
		if (dirty & 1)
		{
			UpdateAxes();
		}
		return &unknownF0;
	}

	// FUNCTION: ENGINE 0x10758CF0
	math::Vector* Light::GetAxisFC()
	{
		if (dirty & 1)
		{
			UpdateAxes();
		}
		return &unknownFC;
	}

	// FUNCTION: ENGINE 0x10758D10
	// NONMATCHING: ours keeps the dirty word and the decay pointer in registers across the two calls and uses esi where the
	// engine uses edx (18.9 %)
#ifdef NONMATCHING
	float* Light::GetUnknown218()
	{
		if (spotDirty)
		{
			float half = unknown120 * engine::driving::gHalf;
			float inner = cos(half);
			float outer = cos(unknown124 + half + 0.00001f);
			float scale = -1.0f / (outer - inner);
			float near = decay.GetUnknown10758B20();
			float far = decay.GetRange();
			unknown218 = scale;
			float slope = engine::driving::gOne / (far - near);
			unknown220 = slope;
			unknown224 = slope * near;
			unknown21C = 1.0f - scale * inner;
			spotDirty = 0;
		}
		return &unknown218;
	}
#endif

	// FUNCTION: ENGINE 0x10758DD0
	void Light::GetFrame(math::Matrix* out)
	{
		if (dirty & 1)
		{
			UpdateAxes();
		}
		out->Identity();
		out->m[0][0] = unknownFC.x;
		out->m[0][1] = unknownFC.y;
		out->m[0][2] = unknownFC.z;
		out->m[1][0] = unknownF0.x;
		out->m[1][1] = unknownF0.y;
		out->m[1][2] = unknownF0.z;
		out->m[2][0] = direction.x;
		out->m[2][1] = direction.y;
		out->m[2][2] = direction.z;
	}

	// FUNCTION: ENGINE 0x10758E50
	float Light::GetUnknown10758E50()
	{
		float outer = unknown124;
		float limit = (3.12413955f - GetUnknown120()) * engine::driving::gHalf;
		if (!(limit > outer))
		{
			outer = limit;
		}
		return outer > 0.0f ? outer : 0.0f;
	}

	// FUNCTION: ENGINE 0x10758EF0
	void Light::SetShadowEnabled(bool value)
	{
		enabled = value;
		RenderParams** slot = &shadow;
		if (value)
		{
			if (*slot == 0)
			{
				core::RefAssign(*slot, context->AllocRenderParams());
			}
		}
		else if (*slot != 0)
		{
			context->FreeRenderParams(*slot);
			core::SafeRelease(*slot);
		}
	}

	// FUNCTION: ENGINE 0x10758F70
	void Light::SetUnknown17C(float value)
	{
		if (!(value > 0.01f))
		{
			value = 0.01f;
		}
		dirty |= 0x16;
		unknown17C = value;
	}

	// FUNCTION: ENGINE 0x10758FA0
	void Light::SetUnknown180(float value)
	{
		if (!(value > 0.01f))
		{
			value = 0.01f;
		}
		dirty |= 0x16;
		unknown180 = value;
	}

	// FUNCTION: ENGINE 0x10758FD0
	void Light::SetUnknown184(float value)
	{
		if (!(value > 0.01f))
		{
			value = 0.01f;
		}
		dirty |= 0x16;
		unknown184 = value;
	}

	// FUNCTION: ENGINE 0x1075A7E0
	DecayRange::~DecayRange()
	{
		core::SafeRelease(unknown10);
	}

	// FUNCTION: ENGINE 0x1075A7F0
	void DecayRange::SetUnknown1075A7F0(float value)
	{
		unknown4 = value < 10000.0f ? value : 10000.0f;
	}

	// FUNCTION: ENGINE 0x1075A810
	void DecayRange::SetUnknown1075A810(float value)
	{
		range = value < 10000.0f ? value : 10000.0f;
	}

	// FUNCTION: ENGINE 0x1075C750
	void MergeLightBits(LightBits* out, const LightBits* a, const LightBits* b, const LightGroups* layout,
		unsigned int groups)
	{
		for (unsigned int i = 0; i < 14; i++, groups >>= 1)
		{
			if (!groups)
			{
				return;
			}
			if (groups & 1)
			{
				unsigned int first = layout->first[i] << 5;
				unsigned int last = ((layout->count[i] << 5) + first - 1) >> 5;
				for (unsigned int word = first >> 5; word <= last; word++)
				{
					out->words[word] = a->words[word] | b->words[word];
				}
			}
		}
	}
}
