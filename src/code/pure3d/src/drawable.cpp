// pure3d::Drawable (unit 0x106DE950 - 0x106E28F0; file name guessed from the class): the per-frame update of a
// drawable instance (controllers, expressions, particle emitters), its parts' world matrices and render bits, and its
// bounds. Names are guesses unless noted.
#include "code/core/bitfield.h"
#include "code/core/refptr.h"
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

// FUNCTION: ENGINE 0x10204C10
template bool core::BitField<unsigned short>::Test(unsigned short bit) const;

// The reference helpers of the parts' primitive and state (this unit's copies)
// FUNCTION: ENGINE 0x106DEA60
template void core::RefAssign<pure3d::Primitive>(pure3d::Primitive*& pointer, pure3d::Primitive* object);

// FUNCTION: ENGINE 0x106DEA90
template void core::RefAssign<pure3d::PrimitiveState>(pure3d::PrimitiveState*& pointer, pure3d::PrimitiveState* object);

// FUNCTION: ENGINE 0x106DEAC0
template void core::SafeRelease<pure3d::Primitive>(pure3d::Primitive*& object);

// FUNCTION: ENGINE 0x106DEAE0
template void core::SafeRelease<pure3d::PrimitiveState>(pure3d::PrimitiveState*& object);

// FUNCTION: ENGINE 0x106DEBE0
template void core::BitField<unsigned short>::Set(unsigned short bit, bool value);

// FUNCTION: ENGINE 0x101E0520
template void core::BitField<unsigned short>::Set(unsigned short bit);

// FUNCTION: ENGINE 0x10444290
template void core::BitField<unsigned short>::Clear(unsigned short bit);

// FUNCTION: ENGINE 0x10433D90
template void core::BitField<unsigned int>::ClearAll();

namespace math
{
	// FUNCTION: ENGINE 0x102CBD60
	// An inline of the math headers whose kept copy sits in another unit (the drawable bounds are its users here)
	void AABB::Inflate()
	{
		const float epsilon = 1e-5f;
		if (IsEqual(max.x, min.x, epsilon))
		{
			max.x += epsilon;
			min.x -= epsilon;
		}
		if (IsEqual(max.y, min.y, epsilon))
		{
			max.y += epsilon;
			min.y -= epsilon;
		}
		if (IsEqual(max.z, min.z, epsilon))
		{
			max.z += epsilon;
			min.z -= epsilon;
		}
	}
}

namespace choreo
{
	extern const float gMinusOne;
}

namespace engine
{
	namespace driving
	{
		extern const float gOne;
	}
}

namespace pure3d
{
	void AssignCoreRef(core::IRefCount*& pointer, core::IRefCount* object);

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

	// FUNCTION: ENGINE 0x106DF460
	void SetFrameOverride(unsigned int frame)
	{
		gUseFrameOverride = true;
		gFrameOverride = frame;
	}

	// FUNCTION: ENGINE 0x106DF4A0
	void SetCheckPoseFrame(bool value)
	{
		gCheckPoseFrame = value;
	}

	// FUNCTION: ENGINE 0x106DF4B0
	PartRef::PartRef(Drawable* newOwner, int newIndex)
	{
		owner = newOwner;
		index = newIndex;
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

	// FUNCTION: ENGINE 0x106DF510
	void Drawable::MarkPartsDirty()
	{
		partsDirty = true;
	}

	// FUNCTION: ENGINE 0x106DF570
	void Drawable::MarkFrame()
	{
		frameC0 = GetCurrentFrame();
	}

	// FUNCTION: ENGINE 0x106DF580
	void Drawable::SetFlag100Bit2(bool value)
	{
		flag04 = value;
	}

	// FUNCTION: ENGINE 0x106DF5E0
	void Drawable::SetFlag10()
	{
		flag10 = true;
	}

	// FUNCTION: ENGINE 0x106DF5F0
	void Drawable::ClearFlag10()
	{
		flag10 = false;
	}

	// FUNCTION: ENGINE 0x106DF610
	Skeleton* Drawable::GetSkeleton()
	{
		return skeleton;
	}

	// FUNCTION: ENGINE 0x106DF620
	Pose* Drawable::GetPose()
	{
		return pose;
	}

	// FUNCTION: ENGINE 0x106DF600
	math::Matrix* Drawable::GetTransform()
	{
		return &transform;
	}

	// FUNCTION: ENGINE 0x106DF630
	FrameController* Drawable::GetUnknown78()
	{
		return unknown78;
	}

	// FUNCTION: ENGINE 0x106DF640
	VertexOffsetExpressionMixer* Drawable::GetExpressionMixer()
	{
		return expressionMixer;
	}

	// FUNCTION: ENGINE 0x106DF650
	FrameController* Drawable::GetUnknown7C()
	{
		return unknown7C;
	}

	// FUNCTION: ENGINE 0x106DF660
	int Drawable::GetUnknownB8()
	{
		return unknownB8;
	}

	// FUNCTION: ENGINE 0x106DF670
	float Drawable::GetUnknownBC()
	{
		return unknownBC;
	}

	// FUNCTION: ENGINE 0x106DF680
	void Drawable::SetFlag101Bit1(bool value)
	{
		updateWhenVisible = value;
	}

	// FUNCTION: ENGINE 0x106DF6C0
	void Drawable::SetFlag100Bit3(bool value)
	{
		flag08 = value;
	}

	// FUNCTION: ENGINE 0x106DF6A0
	bool Drawable::GetFlag101Bit1()
	{
		return updateWhenVisible;
	}

	// FUNCTION: ENGINE 0x106DF6B0
	bool Drawable::GetFlag100Bit3()
	{
		return flag08;
	}

	// FUNCTION: ENGINE 0x106DF6F0
	core::Name<core::CaseSensitiveKey>* Drawable::GetUnknownF8()
	{
		return &unknownF8;
	}

	// FUNCTION: ENGINE 0x106DFDE0
	void PartRef::SetBinding(PartBinding* binding)
	{
		Get()->SetBinding(binding);
	}

	// FUNCTION: ENGINE 0x106DFE00
	PartBinding* PartRef::GetBinding() const
	{
		return Get()->binding;
	}

	// FUNCTION: ENGINE 0x106DFD70
	// Gives a part without a state the state of its primitive (only a mesh gets one made)
	void PartRef::Unknown106DFD70()
	{
		DrawablePart* part = Get();
		PrimitiveState* state = 0;
		int type = part->primitive->type;
		if (type == 2)
		{
			state = new MeshState((Mesh*)part->primitive, 0, 0);
		}
		else if (type == 4)
		{
			return;
		}
		part->SetState(state);
	}

	// FUNCTION: ENGINE 0x106DFE20
	// Gives the part's state a shader animation controller and answers it (null for a primitive that has none)
	FrameController* PartRef::Unknown106DFE20()
	{
		DrawablePart* part = Get();
		int type = part->primitive->type;
		if (type == 2)
		{
			ShaderAnimationController* controller = new ShaderAnimationController();
			((MeshState*)part->state)->SetController1(controller);
			owner->cyclic = true;
			return controller;
		}
		if (type == 4)
		{
			ShaderAnimationController* controller = new ShaderAnimationController();
			((SkinState*)part->state)->SetController1(controller);
			owner->cyclic = true;
			return controller;
		}
		if (type == 0x4000)
		{
			ShaderAnimationController* controller = new ShaderAnimationController();
			((GpuSkinState*)part->state)->SetShaderController(controller);
			owner->cyclic = true;
			return controller;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x106DFF80
	FrameController* Drawable::GetUnknown80()
	{
		return unknown80;
	}

	// FUNCTION: ENGINE 0x106DFF90
	void Drawable::SetUnknown80(FrameController* controller)
	{
		FrameController* old = unknown80;
		if (old != controller)
		{
			unknown80 = controller;
			if (controller)
			{
				controller->AddRef();
			}
			if (old)
			{
				old->Release();
			}
		}
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
				if (pose->mData.mFlags & 2)
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
							pose->mData.mWorldMatrices[partJoints.begin[i]]);
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

	// FUNCTION: ENGINE 0x106E02C0
	void Drawable::Unknown106E02C0()
	{
		for (unsigned int i = 0; i < (unsigned int)parts.Size(); i++)
		{
			PrimitiveState* state = parts[i].state;
			if (state)
			{
				state->Unknown5();
			}
		}
		if (unknown78)
		{
			unknown78->Reset();
		}
		if (unknown7C)
		{
			unknown7C->Reset();
		}
	}

	// FUNCTION: ENGINE 0x106E0340
	bool Drawable::IsFinished()
	{
		if (unknown78 && !unknown78->Unknown20())
		{
			return false;
		}
		if (unknown7C && !unknown7C->Unknown20())
		{
			return false;
		}
		for (unsigned int i = 0; i < (unsigned int)parts.Size(); i++)
		{
			PrimitiveState* state = parts[i].state;
			if (state && !state->Unknown6())
			{
				return false;
			}
		}
		return true;
	}

	// FUNCTION: ENGINE 0x106E0540
	void Drawable::SetTransform(const math::Matrix& newTransform)
	{
		if (!(newTransform == transform))
		{
			transform = newTransform;
			partsDirty = true;
			boundsDirty = true;
			dirty.SetMask(4);
		}
		frameC0 = GetCurrentFrame();
	}

	// FUNCTION: ENGINE 0x106E0580
	void Drawable::SetSkeleton(Skeleton* newSkeleton)
	{
		core::RefAssign(skeleton, newSkeleton);
	}

	// FUNCTION: ENGINE 0x106E0810
	void Drawable::SetPartJoint(unsigned int part, unsigned short joint)
	{
		partJoints.begin[part] = joint;
	}

	// FUNCTION: ENGINE 0x106E03E0
	void Drawable::Unknown106E03E0()
	{
		int count = parts.Size();
		for (int i = 0; i < count; i++)
		{
			if (parts.begin[i].primitive->type == 2 && parts.begin[i].state)
			{
				MeshState* mesh = (MeshState*)parts.begin[i].state;
				VertexAnimController* animation = dynamic_cast<VertexAnimController*>((SimpleFrameController*)mesh->GetController2());
				FrameController* region = mesh->GetController3();
				if (animation)
				{
					animation->Unknown28();
				}
				if (region)
				{
					((VertexRegionAnimController*)region)->Unknown28();
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x106E0490
	void Drawable::Unknown106E0490()
	{
		int count = parts.Size();
		for (int i = 0; i < count; i++)
		{
			if (parts.begin[i].primitive->type == 2 && parts.begin[i].state)
			{
				MeshState* mesh = (MeshState*)parts.begin[i].state;
				VertexAnimController* animation = dynamic_cast<VertexAnimController*>((SimpleFrameController*)mesh->GetController2());
				FrameController* region = mesh->GetController3();
				if (animation)
				{
					animation->Unknown27();
				}
				if (region)
				{
					((VertexRegionAnimController*)region)->Unknown27();
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x106E05A0
	// NONMATCHING: register allocation (88 %: the engine keeps this in ebx and the pose in edi; same operations)
#ifdef NONMATCHING
	void Drawable::SetPose(Pose* object)
	{
		if (object != pose)
		{
			AssignCoreRef((core::IRefCount*&)pose, (core::IRefCount*)object);
			if (unknown78 && pose)
			{
				((PoseAnimationController*)unknown78)->SetPose(pose);
			}
			int count = parts.Size();
			for (int i = 0; i < count; i++)
			{
				int type = parts.begin[i].primitive->type;
				if (type == 4)
				{
					SkinState* skin = (SkinState*)parts.begin[i].state;
					Pose* newPose = pose;
					skin->Unknown9();
					AssignCoreRef((core::IRefCount*&)skin->pose, (core::IRefCount*)newPose);
				}
				else if (type == 0x4000)
				{
					// the gpu skin state keeps the pose in the word at +0x1C
					AssignCoreRef(((GpuSkinState*)parts.begin[i].state)->buffer, (core::IRefCount*)pose);
				}
			}
			poseFrame = GetCurrentFrame();
			cyclic = true;
			dirty.SetMask(2);
		}
	}
#endif

	// FUNCTION: ENGINE 0x106E06E0
	void Drawable::SetExpressionSource(Entity* source)
	{
		core::RefAssign(expressionMixer, (VertexOffsetExpressionMixer*)source);
		int count = parts.Size();
		for (int i = 0; i < count; i++)
		{
			if (parts.begin[i].primitive->type == 4)
			{
				ExpressionAnimationController* controller =
					(ExpressionAnimationController*)((SkinState*)parts.begin[i].state)->GetController2();
				if (controller)
				{
					controller->SetMixer((VertexOffsetExpressionMixer*)source);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x106E09A0
	void Drawable::Unknown106E09A0(Drawable* other)
	{
		for (unsigned int i = 0; i < (unsigned int)segments.Size(); i++)
		{
			for (unsigned int j = 0; j < segments.begin[i].partCount; j++)
			{
				unsigned int part = segments.begin[i].firstPart + j;
				SetPartUpdated(part, other->GetPartUpdated(part));
			}
		}
	}

	// FUNCTION: ENGINE 0x106E06A0
	void Drawable::SetUnknown78(FrameController* controller)
	{
		RefCounted::Assign(unknown78, controller);
		if (unknown78 && pose)
		{
			((PoseAnimationController*)unknown78)->SetPose(pose);
		}
		if (unknown78)
		{
			cyclic = true;
		}
	}

	// FUNCTION: ENGINE 0x106E0760
	void Drawable::SetUnknown7C(FrameController* controller)
	{
		core::RefAssign((CompDrawVisibilityAnimationController*&)unknown7C, (CompDrawVisibilityAnimationController*)controller);
		if (unknown7C)
		{
			((CompDrawVisibilityAnimationController*)unknown7C)->SetDrawable(this);
			cyclic = true;
		}
	}

	// FUNCTION: ENGINE 0x106E0790
	bool Drawable::GetPartUpdated(unsigned int part)
	{
		return partFlags.begin[part] & 1;
	}

	// FUNCTION: ENGINE 0x106E07B0
	// NONMATCHING: register allocation (the engine keeps the flag byte in edx and this in ecx; best 9 %, same operations)
#ifdef NONMATCHING
	void Drawable::SetPartUpdated(unsigned int part, bool value)
	{
		unsigned char* entry = &partFlags.begin[part];
		unsigned char flags = *entry;
		flags = value ? flags | 1 : flags & 0xFE;
		*entry = flags;
		visibility::Client& client = parts.begin[part].client;
		if (client.IsRegistered())
		{
			client.SetListed(1, value);
		}
	}
#endif

	// FUNCTION: ENGINE 0x106E0800
	unsigned short Drawable::GetPartJoint(unsigned int part)
	{
		return partJoints.begin[part];
	}

	// FUNCTION: ENGINE 0x106E0910
	void Drawable::SetUnknownFloat(int index, float value)
	{
		if (index != unknownB8 || value != unknownB4)
		{
			partsDirty = true;
			unknownB4 = value;
			unknownB8 = index;
			dirty.SetMask(1);
		}
	}

	// FUNCTION: ENGINE 0x106E1240
	bool Drawable::TestFlag8C(int bit)
	{
		return unknown8C.Test(bit);
	}

	// FUNCTION: ENGINE 0x106E1900
	void Drawable::SetFlag8C(int bit, bool value)
	{
		unknown8C.SetBit(bit, value);
	}

	// FUNCTION: ENGINE 0x106E1250
	void Drawable::Unknown106E1250(const core::Name<core::CaseSensitiveKey>& name)
	{
		unknownF8 = name;
	}

	// FUNCTION: ENGINE 0x106E1260
	void Drawable::SetPartUnknown2C(int part, float value)
	{
		parts.begin[part].unknown2C = value;
		dirty.SetMask(8);
	}

	// FUNCTION: ENGINE 0x106E0A40
	// NONMATCHING: the engine tests the count with sar + je, ours folds the test into a mask test (non-zero test of the shifted size)
#ifdef NONMATCHING
	unsigned short Drawable::FindSegment(const core::Name<core::CaseSensitiveKey>& name)
	{
		unsigned int i = 0;
		unsigned int count = segments.Size();
		if (count != 0)
		{
			DrawableSegment* segment = segments.begin;
			do
			{
				if (name == segment->name)
				{
					return (unsigned short)i;
				}
				i++;
				segment++;
			}
			while (i < (unsigned int)segments.Size());
		}
		return 0xFFFF;
	}
#endif

	// FUNCTION: ENGINE 0x106E0AA0
	// NONMATCHING: the engine tests the count with sar + je, ours folds the test into a mask test (non-zero test of the shifted size)
#ifdef NONMATCHING
	unsigned short Drawable::FindSegment(unsigned __int64 name)
	{
		unsigned int i = 0;
		unsigned int count = segments.Size();
		if (count != 0)
		{
			DrawableSegment* segment = segments.begin;
			do
			{
				if (core::Name<core::CaseSensitiveKey>(name) == segment->name)
				{
					return (unsigned short)i;
				}
				i++;
				segment++;
			}
			while (i < (unsigned int)segments.Size());
		}
		return 0xFFFF;
	}
#endif

	// FUNCTION: ENGINE 0x106E0B30
	void Drawable::GetSegmentParts(unsigned short segment, unsigned int* first, unsigned int* count)
	{
		*first = 0;
		*count = 0;
		if (segment < (unsigned int)segments.Size())
		{
			*first = segments.begin[segment].firstPart;
			*count = segments.begin[segment].partCount;
		}
	}

	// FUNCTION: ENGINE 0x106E0B80
	DrawableSegment* Drawable::GetSegment(unsigned short segment)
	{
		if (segment < (unsigned int)segments.Size())
		{
			return &segments.begin[segment];
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x106E0BB0
	void Drawable::SetSegmentVisible(unsigned short segment, bool visible)
	{
		if (segment < (unsigned int)segments.Size())
		{
			for (unsigned int i = 0; i < segments.begin[segment].partCount; i++)
			{
				SetPartUpdated(segments.begin[segment].firstPart + i, visible);
			}
		}
	}

	// FUNCTION: ENGINE 0x106E0C10
	void Drawable::GetLocalBounds(math::AABB* box)
	{
		math::Matrix inverse;
		inverse.m[0][0] = transform.m[0][0];
		inverse.m[0][1] = transform.m[0][1];
		inverse.m[0][2] = transform.m[0][2];
		inverse.m[0][3] = transform.m[0][3];
		inverse.m[1][0] = transform.m[1][0];
		inverse.m[1][1] = transform.m[1][1];
		inverse.m[1][2] = transform.m[1][2];
		inverse.m[1][3] = transform.m[1][3];
		inverse.m[2][0] = transform.m[2][0];
		inverse.m[2][1] = transform.m[2][1];
		inverse.m[2][2] = transform.m[2][2];
		inverse.m[2][3] = transform.m[2][3];
		inverse.m[3][0] = transform.m[3][0];
		inverse.m[3][1] = transform.m[3][1];
		inverse.m[3][2] = transform.m[3][2];
		inverse.m[3][3] = transform.m[3][3];
		inverse.Invert();
		box->max.x = bounds.max.x;
		box->max.y = bounds.max.y;
		box->max.z = bounds.max.z;
		box->min.x = bounds.min.x;
		box->min.y = bounds.min.y;
		box->min.z = bounds.min.z;
		box->SetTransformed(inverse, *box);
	}

	// FUNCTION: ENGINE 0x106E0D20
	void Drawable::GetLocalSphere(math::Sphere* sphere)
	{
		math::AABB box;
		GetLocalBounds(&box);
		CopySphere(*sphere, box.GetSphere());
	}

	// FUNCTION: ENGINE 0x106E0950
	void Drawable::SetUnknownBC(float value)
	{
		if (value != unknownBC)
		{
			if (!(value >= 0.0f))
			{
				value = 0.0f;
			}
			if (value - engine::driving::gOne >= 0.0f)
			{
				value = engine::driving::gOne;
			}
			partsDirty = true;
			unknownBC = value;
			dirty.SetMask(8);
		}
	}

	// FUNCTION: ENGINE 0x106E11F0
	void Drawable::SetUnknownCC(int value)
	{
		unknownCC = value;
		for (DrawablePart* part = parts.begin; part != parts.end; part++)
		{
			part->primitive->SetUnknown10(value);
			part->unknownCC = value;
		}
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
					world.Multiply(pose->mData.mWorldMatrices[partJoints.begin[i]], transform);
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

	// FUNCTION: ENGINE 0x102D3D30
	PartBindingSource* DrawablePart::GetBindingSource()
	{
		if (binding)
		{
			return (PartBindingSource*)binding;
		}
		if (state && state->GetBindingSource())
		{
			return (PartBindingSource*)state->GetBindingSource();
		}
		if (primitive && primitive->unknown18)
		{
			return (PartBindingSource*)primitive->unknown18;
		}
		return 0;
	}

	// The binding source a part's shader comes from (inline in the engine's SetBinding)
	static __forceinline PartBindingSource* SourceOf(DrawablePart* part)
	{
		if (part->binding)
		{
			return (PartBindingSource*)part->binding;
		}
		if (part->state && part->state->GetBindingSource())
		{
			return (PartBindingSource*)part->state->GetBindingSource();
		}
		if (part->primitive && part->primitive->unknown18)
		{
			return (PartBindingSource*)part->primitive->unknown18;
		}
		return 0;
	}

	// FUNCTION: ENGINE 0x106DE950
	void DrawablePart::SetBinding(PartBinding* newBinding)
	{
		if (newBinding)
		{
			newBinding->AddRef();
			newBinding->Attach(this);
		}
		if (binding)
		{
			binding->Detach(this);
			binding->Release();
		}
		binding = newBinding;
		if (state)
		{
			state->Unknown8(newBinding);
		}
		unknown10C = SourceOf(this)->shader;
	}

	// FUNCTION: ENGINE 0x106DEB80
	bool DrawablePart::GetRenderFlag3()
	{
		PartBinding* source = GetRenderBinding();
		if (source)
		{
			return source->flags.Test(3);
		}
		return false;
	}

	// FUNCTION: ENGINE 0x106DEEC0
	void DrawablePart::SetPrimitive(Primitive* newPrimitive)
	{
		core::RefAssign(primitive, newPrimitive);
		renderBits.Set(9, true);
	}

	// FUNCTION: ENGINE 0x106DEEF0
	void DrawablePart::SetState(PrimitiveState* newState)
	{
		core::RefAssign(state, newState);
		renderBits.Set(9, true);
	}

	// FUNCTION: ENGINE 0x106DEF20
	bool DrawablePart::UpdateBatch()
	{
		bool unknown = true;
		bool filled = primitive->FillBatch(&batch, state, &unknown);
		if (filled)
		{
			unknown10C = GetBindingSource()->shader;
		}
		renderBits.Set(9, filled);
		return unknown;
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
					jointMatrix = &pose->mData.mWorldMatrices[joint];
				}
				else
				{
					jointMatrix = &skeleton->mData.mJoints[joint];
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

	// FUNCTION: ENGINE 0x106E1400
	// NONMATCHING: scheduling (93 %: the engine loads the one before the alpha store, ours after it)
#ifdef NONMATCHING
	Drawable::CreateOptions::CreateOptions()
	{
		b0 = false;
		b2 = false;
		b3 = false;
		b4 = false;
		b5 = false;
		instanceOf = 0;
		b1 = true;
		colour.x = (int)math::pddiColour::WHITE.r * (1.0f / 255.0f);
		colour.y = (int)math::pddiColour::WHITE.g * (1.0f / 255.0f);
		colour.z = (int)math::pddiColour::WHITE.b * (1.0f / 255.0f);
		colour.w = (int)math::pddiColour::WHITE.a * (1.0f / 255.0f);
		unknown1C = engine::driving::gOne;
		float minusOne = choreo::gMinusOne;
		unknown20 = minusOne;
		unknown24 = minusOne;
	}
#endif

	// FUNCTION: ENGINE 0x106E2890
	Drawable* Drawable::CreateInstance(const CreateOptions& options)
	{
		return new Drawable(this, options);
	}
}
