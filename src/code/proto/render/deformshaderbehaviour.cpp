// proto::DeformShaderBehaviour: see the header. The file name and the names are guesses.
#include "code/engine/gameobject/gameobject.h"
#include "code/core/heap.h"
#include "code/math/mathutils.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/proto/render/deformshaderbehaviour.h"

namespace pure3d
{
	// 0x106184E0: the inputs of a shader (the object its sort key answers in the engine; the header calls that an
	// int): the number of the input of that kind and name, 0xFFFF when the shader has none
	class ShaderInputs
	{
	public:
		unsigned int Find(int kind, const core::Name<core::CaseInsensitiveKey32>& name);
	};
}

namespace proto
{
	// The binding source of a part the way DrawablePart::GetBindingSource (0x102D3D30) answers; the modifier has it inline
	static inline pure3d::PartBindingSource* FindBindingSource(pure3d::DrawablePart* part)
	{
		if (part->binding)
		{
			return (pure3d::PartBindingSource*)part->binding;
		}
		if (part->state && part->state->GetBindingSource())
		{
			return (pure3d::PartBindingSource*)part->state->GetBindingSource();
		}
		if (part->primitive && part->primitive->unknown18)
		{
			return (pure3d::PartBindingSource*)part->primitive->unknown18;
		}
		return 0;
	}
}

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

	// FUNCTION: ENGINE 0x102D4810
	DeformShaderBehaviour::DeformShaderModifier::DeformShaderModifier()
	{
	}

	// FUNCTION: ENGINE 0x102D4830
	DeformShaderBehaviour::DeformShaderModifier::~DeformShaderModifier()
	{
	}

	// FUNCTION: ENGINE 0x102D4C50
	// EQUIVALENT: the same lookups, bindings and shader parameter writes in the same order; the engine keeps the
	// binding in ebp and the buffer in ebx, computes the buffer's emptiness and size separately and spills the
	// object and the part number the other way round (83 % of the instructions). Writes the dents into the shader
	// parameters of every part that has the inputs for them, then deletes itself
	void DeformShaderBehaviour::DeformShaderModifier::Apply(engine::render::DrawableImpl* drawable)
	{
		core::HeapScope scope(0xA8);
		static core::Name<core::CaseInsensitiveKey32> damage1("damage_pt1", 0);
		static core::Name<core::CaseInsensitiveKey32> damage2("damage_pt2", 0);
		static core::Name<core::CaseInsensitiveKey32> damage3("damage_pt3", 0);
		static core::Name<core::CaseInsensitiveKey32> damage4("damage_pt4", 0);
		static core::Name<core::CaseInsensitiveKey32> crush("crush_params", 0);
		const core::Name<core::CaseInsensitiveKey32>* damage[4] = { &damage1, &damage2, &damage3, &damage4 };
		if (drawable != 0)
		{
			for (unsigned int part = 0, partCount = drawable->parts.Size(); part < partCount; part++)
			{
				bool usable = true;
				for (unsigned int i = 0; i < 4; i++)
				{
					pure3d::PartRef ref(drawable, part);
					usable &= ((pure3d::ShaderInputs*)((pure3d::PartBindingSource*)ref->primitive->unknown18)->shader->GetSortKey())->Find(4, *damage[i]) != 0xFFFF;
				}
				if (usable)
				{
					pure3d::PartRef ref(drawable, part);
					if (ref->primitive->type == 2)
					{
						pure3d::PartRef meshRef(drawable, part);
						pure3d::Primitive* primitive = meshRef->primitive;
						usable &= (((pure3d::Mesh*)primitive)->GetUnknown148() >> 29) & 1;
					}
					if (usable)
					{
						pure3d::PartRef bindingRef(drawable, part);
						pure3d::PartBinding* binding = bindingRef.GetBinding();
						if (binding == 0)
						{
							pure3d::PartRef sourceRef(drawable, part);
							pure3d::PartBindingSource* source = FindBindingSource(sourceRef.Get());
							binding = source->CreateBinding();
							pure3d::PartRef setRef(drawable, part);
							setRef.SetBinding(binding);
						}
						DentBuffer* buffer = &dents;
						if (buffer->Size() != 0)
						{
							float values[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
							for (unsigned int i = 0; i < buffer->Size(); i++)
							{
								const Dent& dent = buffer->dents[i];
								binding->shader->SetVector4(*damage[i],
									math::Vector4(dent.position.x, dent.position.y, dent.position.z, dent.unknown10));
								values[i] = dent.unknown1C;
							}
							binding->shader->SetVector4(crush, *(math::Vector4*)values);
						}
						else
						{
							binding->shader->SetVector4(crush, math::Vector4(0.0f, 0.0f, 0.0f, 0.0f));
							for (unsigned int i = 0; i < 4; i++)
							{
								binding->shader->SetVector4(*damage[i], math::Vector4(0.0f, 0.0f, 0.0f, 0.0f));
							}
						}
					}
				}
			}
		}
		delete this;
	}

	// The atexit stubs of the five function-local names of Apply (the names have a user-declared destructor)
	// FUNCTION: ENGINE 0x10D829F0
	// FUNCTION: ENGINE 0x10D829E0
	// FUNCTION: ENGINE 0x10D829D0
	// FUNCTION: ENGINE 0x10D829C0
	// FUNCTION: ENGINE 0x10D829B0
}
