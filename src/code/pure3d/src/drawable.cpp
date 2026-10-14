// pure3d::Drawable (unit 0x106DE950 - 0x106E28F0; file name guessed from the class): the per-frame update of a
// drawable instance (controllers, expressions, particle emitters), its parts' world matrices and render bits, and its
// bounds. Names are guesses unless noted.
#include "code/core/bitfield.h"
#include "code/math/aabb.h"
#include "code/math/matrix.h"
#include "code/math/mathutils.h"
#include "code/math/sphere.h"
#include "code/pure3d/context.h"
#include "code/pure3d/drawable.h"

#include <math.h>

// The flag sets' members the unit uses (their kept copies)
// FUNCTION: ENGINE 0x106DEA40
template bool core::BitField<unsigned int>::Test(unsigned int bit) const;

// FUNCTION: ENGINE 0x106DEBE0
template void core::BitField<unsigned short>::Set(unsigned short bit, bool value);

// FUNCTION: ENGINE 0x101E0520
template void core::BitField<unsigned short>::Set(unsigned short bit);

// FUNCTION: ENGINE 0x10444290
template void core::BitField<unsigned short>::Clear(unsigned short bit);

// FUNCTION: ENGINE 0x10433D90
template void core::BitField<unsigned int>::ClearAll();

namespace pure3d
{
	// The frame number the drawables compare their marks with is pure3d::context's, unless overridden
	// (0x1127EBCD / 0x1127EBD0); 0x106DF4A0 sets whether IsPoseCurrent checks the pose's frame (0x1127EBCC)
	extern bool gUseFrameOverride;
	extern unsigned int gFrameOverride;
	extern bool gCheckPoseFrame;

	struct EmitterTransform
	{
		math::Vector4 rows[4];
	};

	// Member-wise sphere copy
	static inline void CopySphere(math::Sphere& to, const math::Sphere& from)
	{
		to.centre.x = from.centre.x;
		to.centre.y = from.centre.y;
		to.centre.z = from.centre.z;
		to.radius = from.radius;
	}

	// Sets or clears mask in flags
	static inline void SetFlag(unsigned char& flags, unsigned char mask, bool value)
	{
		flags = value ? flags | mask : flags & ~mask;
	}

	// FUNCTION: ENGINE 0x106DF480
	unsigned int GetCurrentFrame()
	{
		if (gUseFrameOverride)
		{
			return gFrameOverride;
		}
		return context->frame;
	}

	// FUNCTION: ENGINE 0x106DF4F0
	bool Drawable::IsPoseCurrent()
	{
		return !gCheckPoseFrame || poseFrame == GetCurrentFrame();
	}

	// FUNCTION: ENGINE 0x106DF520
	bool Drawable::IsCyclic()
	{
		return cyclic;
	}

	// FUNCTION: ENGINE 0x106DF620
	Pose* Drawable::GetPose()
	{
		return pose;
	}

	// FUNCTION: ENGINE 0x106DFFD0
	// EQUIVALENT: the engine keeps the part offset of the expression loop in eax between iterations and starts it
	// with its own xor; ours keeps it in memory, and the state loop's part address is formed [begin + offset] there
	void Drawable::Update(float dt)
	{
		if (flag10)
		{
			return;
		}
		bool changed = !updateWhenVisible || forceUpdate;
		if (!changed)
		{
			unsigned int count = parts.Size();
			for (unsigned int i = 0; i < count; i++)
			{
				changed |= parts[i].client.GetResult(2);
			}
			if (!changed)
			{
				goto pose;
			}
		}
		if (unknown78)
		{
			unknown78->Advance(dt, true);
			poseFrame = GetCurrentFrame();
		}
		if (unknown7C)
		{
			unknown7C->Advance(dt, true);
		}
	pose:
		if (pose)
		{
			if (IsPoseCurrent() || frameC0 == GetCurrentFrame())
			{
				if (pose->mFlags & 2)
				{
					pose->Update();
				}
				MarkTransformDirty();
			}
		}
		if (changed)
		{
			if (expressionMixer)
			{
				expressionMixer->Update();
			}
			int count = parts.Size();
			for (int i = 0; i < count; i++)
			{
				if (parts[i].primitive->type == 4)
				{
					SkinState* skin = (SkinState*)parts[i].state;
					if (skin->GetExpression() && skin->GetExpressionState() && expressionMixer)
					{
						expressionMixer->Apply(skin->GetExpression(), skin->GetExpressionState());
					}
				}
				if (pose && partJoints.begin[i] != 0xFFFF && parts.begin[i].primitive->type == 2)
				{
					MeshState* mesh = (MeshState*)parts.begin[i].state;
					if (mesh && mesh->GetController3())
					{
						((VertexRegionAnimController*)mesh->GetController3())->SetTransform(
							((math::Matrix*)pose->mJoints)[partJoints.begin[i]]);
					}
				}
			}
			unsigned int j = 0;
			unsigned int stateCount = parts.Size();
			for (; j < stateCount; j++)
			{
				PrimitiveState* state = parts.begin[j].state;
				if (state && (partFlags.begin[j] & 2))
				{
					if (state->GetPrimitive()->type == 0x10 && !((ParticleSystemState*)state)->GetUnknown490())
					{
						math::Matrix emitter;
						const float* from = &transform.m[0][0];
						float* to = &emitter.m[0][0];
						int row = 3;
						do
						{
							to[0] = from[0];
							to[1] = from[1];
							to[2] = from[2];
							to[3] = from[3];
							from += 4;
							to += 4;
						}
						while (--row >= 0);
						((ParticleSystemState*)state)->SetTransform(emitter);
						boundsDirty = true;
					}
					state->Update(dt);
				}
			}
			if (unknown80)
			{
				unknown80->Advance(dt, true);
			}
		}
		forceUpdate = false;
	}

	// FUNCTION: ENGINE 0x106E0680
	void Drawable::MarkPoseDirty()
	{
		poseFrame = GetCurrentFrame();
		MarkTransformDirty();
	}

	// FUNCTION: ENGINE 0x106E0D60
	// EQUIVALENT: register and stack slot choice (the engine keeps the bounds in ebx, the part index in ebp and the
	// count and part offset in memory; its frame is 4 bytes smaller)
	void Drawable::UpdateBounds(bool force)
	{
		if (boundsDirty || force)
		{
			math::AABB& total = bounds;
			total.Reset();
			if (parts.begin == parts.end)
			{
				return;
			}
			unsigned int i = 0;
			unsigned int count = parts.Size();
			math::Sphere partSphere;
			partSphere.centre.Set(0.0f, 0.0f, 0.0f);
			math::Sphere worldSphere;
			worldSphere.centre.Set(0.0f, 0.0f, 0.0f);
			for (; i < count; i++)
			{
				DrawablePart& part = parts[i];
				math::AABB box;
				PrimitiveState* state = part.state;
				if (state)
				{
					state->GetBoundingBox(&box);
					CopySphere(partSphere, box.GetSphere());
				}
				else
				{
					part.primitive->GetBoundingBox(&box);
					CopySphere(partSphere, box.GetSphere());
				}
				if (box.IsEmpty())
				{
					partSphere.centre.Set(0.0f, 0.0f, 0.0f);
					partSphere.radius = 0.0f;
				}
				math::AABB worldBox;
				if (pose && partJoints.begin[i] != 0xFFFF)
				{
					math::Matrix world;
					world.Multiply(((math::Matrix*)pose->mJoints)[partJoints.begin[i]], transform);
					if (!box.IsEmpty())
					{
						worldBox.SetTransformed(world, box);
					}
					worldSphere.radius = partSphere.radius;
					worldSphere.centre.Transform(partSphere.centre, world);
				}
				else
				{
					if (!box.IsEmpty())
					{
						worldBox.SetTransformed(transform, box);
					}
					worldSphere.radius = partSphere.radius;
					worldSphere.centre.Transform(partSphere.centre, transform);
				}
				if (box.IsEmpty())
				{
					worldBox.Reset();
				}
				if (i < (unsigned int)parts.Size())
				{
					visibility::Client& client = parts[i].client;
					if (client.IsRegistered())
					{
						client.SetBox(worldBox);
						client.SetSphere(worldSphere);
					}
				}
				total.min.x = math::Min(total.min.x, worldBox.min.x);
				total.min.y = math::Min(total.min.y, worldBox.min.y);
				total.min.z = math::Min(total.min.z, worldBox.min.z);
				total.max.x = math::Max(worldBox.max.x, total.max.x);
				total.max.y = math::Max(worldBox.max.y, total.max.y);
				total.max.z = math::Max(worldBox.max.z, total.max.z);
			}
			total.Inflate();
			float x;
			float y;
			float z;
			float radius;
			if (!total.IsEmpty())
			{
				float hz = (total.max.z - total.min.z) * 0.5f;
				float hy = (total.max.y - total.min.y) * 0.5f;
				float hx = (total.max.x - total.min.x) * 0.5f;
				x = total.min.x + hx;
				y = total.min.y + hy;
				z = total.min.z + hz;
				radius = sqrtf(hz * hz + hy * hy + hx * hx);
			}
			else
			{
				x = 0.0f;
				y = 0.0f;
				z = 0.0f;
				radius = 0.0f;
			}
			sphere.centre.x = x;
			sphere.centre.y = y;
			sphere.centre.z = z;
			sphere.radius = radius;
			boundsDirty = false;
		}
	}

	// FUNCTION: ENGINE 0x106E13C0
	math::Matrix* DrawablePart::GetWorldMatrix()
	{
		renderBits.Set(10, false);
		return &worldMatrix;
	}

	// FUNCTION: ENGINE 0x106E14E0
	void Drawable::UpdatePart(unsigned int index)
	{
		DrawablePart& part = parts.begin[index];
		if (dirty.IsSet(0))
		{
			part.unknownIndex = unknownB8;
			part.unknown18 = unknownB4;
		}
		if (dirty.IsSet(3))
		{
			float value = unknownBC * part.unknown2C;
			part.unknown1C = value;
			if (part.client.IsRegistered())
			{
				part.client.SetFlag(5, value != 1.0f);
			}
		}
		if (dirty.IsSet(2))
		{
			unsigned short joint;
			if ((pose || skeleton) && (joint = partJoints.begin[index]) != 0xFFFF)
			{
				const math::Matrix* jointMatrix;
				if (pose)
				{
					jointMatrix = &((const math::Matrix*)pose->mJoints)[joint];
				}
				else
				{
					jointMatrix = &((const math::Matrix*)skeleton->mJoints)[joint];
				}
				if (part.client.IsRegistered())
				{
					if (part.client.GetFlag(0x19))
					{
						part.jointMatrix = *jointMatrix;
						*part.GetWorldMatrix() = transform;
					}
					else
					{
						part.jointMatrix = math::Matrix::IDENTITY;
						part.GetWorldMatrix()->Multiply(*jointMatrix, transform);
					}
				}
				else
				{
					part.jointMatrix = math::Matrix::IDENTITY;
					part.renderBits.Set(10, false);
					part.worldMatrix.Multiply(*jointMatrix, transform);
				}
			}
			else
			{
				if (transform == math::Matrix::IDENTITY)
				{
					part.worldMatrix.Identity();
					part.renderBits.Set(10, true);
				}
				else
				{
					part.renderBits.Set(10, false);
					part.worldMatrix = transform;
				}
				part.jointMatrix = math::Matrix::IDENTITY;
			}
		}
		PartBinding* binding = part.GetRenderBinding();
		part.renderBits.Set(7, part.primitive->GetFlag8());
		part.renderBits.Set(1, binding->flags.Test(0));
		part.renderBits.Set(2, binding->flags.Test(1));
		part.renderBits.Set(3, binding->flags.Test(2));
		part.renderBits.Set(4, part.primitive->GetFlag4() && !binding->flags.Test(2));
		part.renderBits.Set(5, part.primitive->GetFlag5() && !binding->flags.Test(2));
		SetFlag(partFlags.begin[index], 8, part.GetRenderBinding()->flags.Test(3));
		SetFlag(partFlags.begin[index], 4, part.primitive->GetFlag5() && unknownBC > 0.25f);
		SetFlag(partFlags.begin[index], 0x10, !part.primitive->GetFlag3() && !(part.primitive->type & 0x200) &&
			unknownBC > 0.99999f);
	}

	// FUNCTION: ENGINE 0x106E18A0
	void Drawable::UpdateParts()
	{
		if (!partsDirty)
		{
			return;
		}
		unsigned int i = 0;
		unsigned int count = parts.Size();
		for (; i < count; i++)
		{
			UpdatePart(i);
		}
		partsDirty = false;
		dirty.ClearAll();
	}
}
