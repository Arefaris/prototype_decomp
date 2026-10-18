// proto::DeformShaderBehaviour: see the header. The file name and the names are guesses.
#include "code/engine/gameobject/gameobject.h"
#include "code/math/mathutils.h"
#include "code/proto/render/deformshaderbehaviour.h"

namespace proto
{
	// FUNCTION: ENGINE 0x102D41C0
	bool DentBuffer::Push(const Dent& dent)
	{
		Dent* slot = end;
		if ((((unsigned char*)slot - (unsigned char*)this) & ~0x1Fu) != sizeof(dents))
		{
			end = slot + 1;
			if (slot != 0)
			{
				*slot = dent;
			}
			return true;
		}
		return false;
	}

	// FUNCTION: ENGINE 0x102D4350
	bool DeformShaderBehaviour::DeformShaderModifier::AddDent(const math::Vector& position, float unknownC, float unknown14, float unknown18)
	{
		Dent dent;
		dent.position.x = position.x;
		dent.position.y = position.y;
		dent.position.z = position.z;
		dent.unknownC = unknownC;
		dent.unknown10 = 0.0f;
		dent.unknown14 = unknown14;
		dent.unknown18 = unknown18;
		dent.unknown1C = 0.0f;
		return dents.Push(dent);
	}

	// FUNCTION: ENGINE 0x102D4920
	// Fades the live dents in and runs the modifier again whenever one changed
	void DeformShaderBehaviour::Update(float dt, unsigned short mask)
	{
		bool changed = false;
		if (dirty)
		{
			dirty = false;
			engine::render::Drawable drawable = GetDrawable();
			if (drawable.IsValid())
			{
				DeformShaderModifier* modifier = new DeformShaderModifier();
				modifier->dents = dents;
				modifier->bias = bias;
				drawable.ApplyModifierAgain(modifier);
			}
		}
		if (count > 0)
		{
			engine::render::Drawable drawable = GetDrawable();
			if (drawable.IsValid())
			{
				DeformShaderModifier* modifier = new DeformShaderModifier();
				modifier->dents = dents;
				modifier->bias = bias;
				drawable.ApplyModifierAgain(modifier);
			}
		}
		bool faded = false;
		for (int i = 0; i < count; i++)
		{
			Dent& dent = dents.dents[i];
			if (dent.unknown14 > 0.0f)
			{
				float step = dt / dent.unknown14;
				dent.unknown10 = (dent.unknownC - dent.unknown10) * step + dent.unknown10;
				dent.unknown10 = math::Min(dent.unknown10, dent.unknownC);
				dent.unknown1C = (dent.unknown18 - dent.unknown1C) * step + dent.unknown1C;
				dent.unknown1C = math::Min(dent.unknown1C, dent.unknown18);
				if (!biasSent && dent.unknown1C > 0.75f)
				{
					biasSent = true;
					SetLODBiasMessage message(0.4f);
					owner->SendMessage(&message);
				}
				dent.unknown14 = dent.unknown14 - dt;
				faded = true;
			}
		}
		if (faded)
		{
			changed = true;
			engine::render::Drawable drawable = GetDrawable();
			if (drawable.IsValid())
			{
				DeformShaderModifier* modifier = new DeformShaderModifier();
				modifier->dents = dents;
				modifier->bias = bias;
				drawable.ApplyModifierAgain(modifier);
			}
		}
		Listen2(0x100, changed);
	}
}
