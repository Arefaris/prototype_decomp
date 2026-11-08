// proto::LODRenderBehaviour: see the header. The file name and the member names are guesses.
#include <math.h>

#include "code/engine/camera/director.h"
#include "code/pure3d/camera.h"
#include "code/core/heap.h"
#include "code/core/refptr.h"
#include "code/content/namedreference.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/engine/attributemessage.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/math/random.h"
#include "code/pure3d/primitive.h"
#include "code/math/mathutils.h"
#include "code/proto/render/lodrenderbehaviour.h"

namespace pure3d
{
	void AssignCoreRef(core::IRefCount*& pointer, core::IRefCount* object);
	void ReleaseCoreRef(core::IRefCount*& pointer);
}

namespace engine
{
	extern core::Name<core::CaseSensitiveKey> gBoundingBox;
	extern core::Name<core::CaseSensitiveKey> gScaleName;
	extern core::Name<core::CaseSensitiveKey> gInstancePaletteIndex;

	namespace driving
	{
		extern const float gOne;
		extern const float gHalf;
		extern const float gTwo;
	}
}

namespace engine
{
	// FUNCTION: ENGINE 0x102D9810
	int IsVectorNear(const math::Vector& a, const math::Vector& b)
	{
		if (fabsf(a.x - b.x) <= 0.00001f && fabsf(a.y - b.y) <= 0.00001f && fabsf(a.z - b.z) <= 0.00001f)
		{
			return 1;
		}
		return 0;
	}
}

namespace proto
{
	// 0x112834C8 ("pose")
	extern content::ObjectName gDrawableAttributeName;

	// FUNCTION: ENGINE 0x102D91B0
	content::ClassInfo* LODRenderData::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "LODRenderData";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102D91F0
	content::ClassInfo* LODRenderBehaviour::GetClassInfo()
	{
		static content::ClassInfo sInfo;
		sInfo.version = 1;
		sInfo.name = "LODRenderBehaviour";
		sInfo.code = "p";
		return &sInfo;
	}

	// FUNCTION: ENGINE 0x102D9250
	LODLevel::LODLevel(engine::render::Drawable newDrawable) : drawable(newDrawable), firstUses(0), lastUses(0)
	{
	}

	// FUNCTION: ENGINE 0x102D9980
	LODLevel::LODLevel(const LODLevel& other)
	{
		*this = other;
	}

	// FUNCTION: ENGINE 0x102D9270
	LODLevel& LODLevel::operator=(const LODLevel& other)
	{
		drawable = other.drawable;
		firstUses = other.firstUses;
		lastUses = other.lastUses;
		return *this;
	}

	// FUNCTION: ENGINE 0x102D9450
	void LODLevel::Hide()
	{
		drawable.SetRegistered(false);
		firstUses = 0;
		lastUses = 0;
	}

	// FUNCTION: ENGINE 0x102D92A0
	void LODLevel::Destroy()
	{
		engine::render::Drawable::Destroy(&drawable, 0);
		firstUses = 0;
		lastUses = 0;
	}

	// FUNCTION: ENGINE 0x102D92D0
	void LODLevel::Acquire(bool asFirst, bool asLast)
	{
		int usedAsFirst = firstUses;
		int usedAsLast = lastUses;
		if (asFirst)
		{
			firstUses = firstUses + 1;
		}
		if (asLast)
		{
			lastUses = lastUses + 1;
		}
		bool unused;
		if (usedAsFirst == 0 && usedAsLast == 0)
		{
			unused = true;
		}
		else
		{
			unused = false;
			if (usedAsFirst != 0 && usedAsLast != 0)
			{
				return;
			}
		}
		if (firstUses > 0 && lastUses > 0)
		{
			if (unused)
			{
				drawable.SetRegistered(true);
			}
			else
			{
				if (asFirst)
				{
					drawable.SetPartAnimations(0x1F, false);
				}
				else
				{
					drawable.SetPartAnimations(0x1E, false);
				}
			}
		}
		else if (unused)
		{
			drawable.SetRegistered(true);
			if (firstUses > 0)
			{
				drawable.SetPartAnimations(0x1E, true);
			}
			else
			{
				drawable.SetPartAnimations(0x1F, true);
			}
		}
	}

	// FUNCTION: ENGINE 0x102D93A0
	void LODLevel::Release(bool asFirst, bool asLast)
	{
		if (asFirst && firstUses > 0)
		{
			firstUses--;
		}
		if (asLast && lastUses > 0)
		{
			lastUses--;
		}
		if (firstUses == 0 && lastUses == 0)
		{
			drawable.SetRegistered(false);
		}
		else if (firstUses == 0 && asFirst)
		{
			drawable.SetPartAnimations(0x1F, true);
		}
		else if (lastUses == 0 && asLast)
		{
			drawable.SetPartAnimations(0x1E, true);
		}
	}

	// FUNCTION: ENGINE 0x102D9470
	void LODLevel::ApplyPalette(ShaderPaletteData* data)
	{
		engine::render::Drawable copy = drawable;
		data->AddBindings(copy);
	}

	// FUNCTION: ENGINE 0x102D9500
	void LODRenderBehaviour::ShowLevels(const LODLevel* first, const LODLevel* last)
	{
		const_cast<LODLevel*>(first)->Acquire(true, first == last);
		if (first != last)
		{
			const_cast<LODLevel*>(last)->Acquire(false, true);
		}
	}

	// FUNCTION: ENGINE 0x102D9540
	void LODRenderBehaviour::HideLevels(const LODLevel* first, const LODLevel* last)
	{
		const_cast<LODLevel*>(first)->Release(true, first == last);
		if (first != last)
		{
			const_cast<LODLevel*>(last)->Release(false, true);
		}
	}

	// FUNCTION: ENGINE 0x102D9AB0
	void LODRenderBehaviour::ApplyPaletteToLevels(ShaderPaletteData* data)
	{
		if (data != 0)
		{
			for (unsigned int i = 0; i < levels.Size(); i++)
			{
				levels.begin[i].ApplyPalette(data);
			}
		}
	}

	// FUNCTION: ENGINE 0x102D9B10
	void LODRenderBehaviour::ApplyAvailablePalette()
	{
		if (available != 0 && availableIndex >= 0 && availableIndex < (int)available->data.Size())
		{
			ApplyPaletteToLevels(&available->data.begin[availableIndex]);
		}
	}

	// FUNCTION: ENGINE 0x102DA7E0
	void LODRenderBehaviour::DestroyLevels()
	{
		if (poseSource != 0)
		{
			core::IRefCount*& pose = reinterpret_cast<core::IRefCount*&>(poseSource->pose);
			if (pose != 0)
			{
				pure3d::ReleaseCoreRef(pose);
			}
		}
		for (unsigned int i = 0; i < levels.Size(); i++)
		{
			levels.begin[i].Destroy();
		}
	}

	// FUNCTION: ENGINE 0x102DA850
	void LODRenderBehaviour::ResetLevels()
	{
		int count = levels.Size();
		for (int i = 0; i < count; i++)
		{
			if (levels.begin[i].drawable.IsValid())
			{
				levels.begin[i].Hide();
				levels.begin[i].drawable.SetUnknownBC(1.0f);
			}
		}
		fade = engine::driving::gOne;
		flags &= 0xFB;
		forcedFirst = 0;
		forcedLast = 0;
		shownFirst = 0;
		shownLast = 0;
		level = 0xFFFFFFFF;
		forcedFade = 0.0f;
		if (count > 0)
		{
			UpdateLevel();
		}
	}

	// FUNCTION: ENGINE 0x102DA910
	void LODRenderBehaviour::SetAnimation(pure3d::Animation* newAnimation)
	{
		core::RefAssign(animation, newAnimation);
	}

	// The messages of type 8 (id 0: one segment shown or hidden; 1: a list of them; 2: the parts' flag set; 3: set)
	struct SegmentVisibleMessage : public engine::Message
	{
		int unknownC;
		core::Name<core::CaseSensitiveKey> segment;  // +0x10
		bool visible;  // +0x18
	};

	struct SegmentVisibilitiesMessage : public engine::Message
	{
		const engine::DrawableSegmentVisibility* visibilities;  // +0xC
		unsigned int count;  // +0x10
	};

	struct PartsFlagMessage : public engine::Message
	{
		bool value;  // +0xC
	};

	// FUNCTION: ENGINE 0x102D9ED0
	// NONMATCHING: the instructions are the engine's; the engine keeps the loop index in ebp and its byte offset in ebx where ours swaps them (about 92 %)
#ifdef NONMATCHING
	void LODRenderBehaviour::OnSegmentMessage(engine::Message* message)
	{
		switch ((unsigned short)message->id)
		{
		case 0:
			{
				int count = levels.Size();
				for (int i = 0; i < count; i++)
				{
					if (levels.begin[i].drawable.IsValid())
					{
						SegmentVisibleMessage* segment = static_cast<SegmentVisibleMessage*>(message);
						levels.begin[i].drawable.SetSegmentVisible(segment->segment, segment->visible);
					}
				}
			}
			break;
		case 1:
			{
				int count = levels.Size();
				for (int i = 0; i < count; i++)
				{
					if (levels.begin[i].drawable.IsValid())
					{
						SegmentVisibilitiesMessage* list = static_cast<SegmentVisibilitiesMessage*>(message);
						levels.begin[i].drawable.SetSegmentVisibilities(list->visibilities, list->count);
					}
				}
			}
			break;
		case 2:
			{
				int count = levels.Size();
				for (int i = 0; i < count; i++)
				{
					if (levels.begin[i].drawable.IsValid())
					{
						levels.begin[i].drawable.SetPartsUnknown(static_cast<PartsFlagMessage*>(message)->value);
					}
				}
			}
			break;
		case 3:
			{
				int count = levels.Size();
				for (int i = 0; i < count; i++)
				{
					if (levels.begin[i].drawable.IsValid())
					{
						levels.begin[i].drawable.SetPartsUnknown(true);
					}
				}
			}
			break;
		}
	}
#endif

	// The playback message of type 10 (id 1)
	struct PlayMessage : public engine::Message
	{
		float start;  // +0xC
		float end;  // +0x10
		float speed;  // +0x14
		pure3d::Animation::CycleMode mode;  // +0x18
		unsigned int cycles;  // +0x1C
	};

	// FUNCTION: ENGINE 0x102DA090
	// NONMATCHING: the cases are the engine's; register choices of the loops and of the playback arguments differ (about 31 %)
#ifdef NONMATCHING
	void LODRenderBehaviour::OnPlaybackMessage(engine::Message* message)
	{
		switch ((unsigned short)message->id)
		{
		case 1:
			{
				int count = levels.Size();
				for (int i = 0; i < count; i++)
				{
					if (levels.begin[i].drawable.IsValid())
					{
						PlayMessage* play = static_cast<PlayMessage*>(message);
						levels.begin[i].drawable.Play(play->start, play->end, play->speed, play->mode, play->cycles);
					}
				}
			}
			break;
		case 2:
			{
				int count = levels.Size();
				for (int i = 0; i < count; i++)
				{
					if (levels.begin[i].drawable.IsValid())
					{
						levels.begin[i].drawable.ClearFlag10();
					}
				}
			}
			break;
		case 3:
			{
				int count = levels.Size();
				for (int i = 0; i < count; i++)
				{
					if (levels.begin[i].drawable.IsValid())
					{
						levels.begin[i].drawable.SetFlag10();
					}
				}
			}
			break;
		case 7:
			{
				int count = levels.Size();
				for (int i = 0; i < count; i++)
				{
					if (levels.begin[i].drawable.IsValid())
					{
						levels.begin[i].drawable.Method106E0490();
					}
				}
			}
			break;
		case 8:
			{
				int count = levels.Size();
				for (int i = 0; i < count; i++)
				{
					if (levels.begin[i].drawable.IsValid())
					{
						levels.begin[i].drawable.Method106E03E0();
					}
				}
			}
			break;
		}
	}
#endif

	// FUNCTION: ENGINE 0x102DB450
	void LODRenderBehaviour::SetBound(bool bound)
	{
		if (bound != (flags & 1))
		{
			flags = ((flags ^ (int)bound) & 1) ^ flags;
			if (level != 0)
			{
				ResetLevels();
			}
		}
	}

	// FUNCTION: ENGINE 0x102DB3B0
	void LODRenderBehaviour::ReleaseLevelsForPackage()
	{
		core::Name<core::CaseSensitiveKey> none("", 1);
		if (packageName == none)
		{
			for (unsigned int i = 0; i < levels.Size(); i++)
			{
				levels.begin[i].Destroy();
			}
		}
		else
		{
			DestroyLevels();
		}
		flags |= 8;
	}

	// FUNCTION: ENGINE 0x102DB2E0
	void LODRenderBehaviour::OnAttributeUpdated(engine::Message* message)
	{
		engine::AttributeUpdatedMessage* update = static_cast<engine::AttributeUpdatedMessage*>(message);
		if (engine::gScaleName == update->name)
		{
			if (scaleSource == 0)
			{
				scaleSource = reinterpret_cast<LODScaleSource*>(owner->FindAttribute(engine::gScaleName));
			}
			const math::Vector& scale = scaleSource->scale;
			if (fabsf(scale.x - 1.0f) <= 0.00001f && fabsf(scale.y - 1.0f) <= 0.00001f && fabsf(scale.z - 1.0f) <= 0.00001f)
			{
				scaleSource = 0;
			}
		}
		else if (engine::gInstancePaletteIndex == update->name)
		{
			PickPaletteEntry();
		}
	}

	// FUNCTION: ENGINE 0x102D9B50
	// NONMATCHING: the steps of the inlined generator are the engine's; the engine keeps the generator's address and the
	// second state in other registers (about 36 %)
#ifdef NONMATCHING
	void LODRenderBehaviour::PickPaletteEntry()
	{
		if (available != 0)
		{
			availableIndex = paletteIndexSource->value;
			if (availableIndex < 0 || availableIndex >= (int)available->data.Size())
			{
				availableIndex = math::gRandom->Next() % available->data.Size();
			}
			ApplyAvailablePalette();
		}
	}
#endif

	// FUNCTION: ENGINE 0x102DB9F0
	void LODRenderBehaviour::AddLevel(const LODRenderData* data)
	{
		engine::render::Drawable drawable = engine::render::Drawable::CreateInstance(data->GetSource(), true, false);
		drawable.SetUnknownCC(4);
		drawable.SetRegistered(false);
		LODLevel level(drawable);
		levels.PushBack(level);
	}

	// FUNCTION: ENGINE 0x102D99A0
	void LODRenderBehaviour::UpdateFadeIn(float dt)
	{
		float position = fadeInPosition;
		float previous = position;
		float target = fadeInTarget;
		if (position > target)
		{
			position = position - dt * 4.0f;
			if (target > position)
			{
				position = target;
			}
			fadeInPosition = position;
		}
		else if (position < target)
		{
			position = dt * 4.0f + position;
			if (!(target > position))
			{
				position = target;
			}
			fadeInPosition = position;
		}
		fadeInTarget = engine::driving::gOne;
		if (previous != fadeInPosition)
		{
			float shown = fadeInScale * fadeInPosition;
			int count = levels.Size();
			for (int i = 0; i < count; i++)
			{
				if (levels.begin[i].drawable.IsValid())
				{
					levels.begin[i].drawable.SetUnknownBC(shown);
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x102D9BF0
	// NONMATCHING: the fade arithmetic and the order of the calls are the engine's; the engine clamps in other registers
	// and keeps the shown levels' fades in x87 temporaries (about 50 %)
#ifdef NONMATCHING
	void LODRenderBehaviour::UpdateForced(float dt)
	{
		float step = gLODRanges[distanceLevel].rate * dt;
		if (forcedFade >= engine::driving::gOne)
		{
			flags &= 0xFB;
			shownFirst->drawable.SetUnknownBC(1.0f);
			if (shownFirst != shownLast)
			{
				shownLast->drawable.SetUnknownBC(1.0f);
			}
			if (IsActive())
			{
				HideLevels(forcedFirst, forcedLast);
			}
			else
			{
				forcedFirst->Hide();
				forcedLast->Hide();
			}
			return;
		}
		if (forcedFade == 0.0f)
		{
			if (IsActive())
			{
				ShowLevels(shownFirst, shownLast);
			}
			else
			{
				shownFirst->Hide();
				shownLast->Hide();
			}
		}
		float out = (forcedFade - engine::driving::gHalf) * engine::driving::gTwo;
		if (out < 0.0f)
		{
			out = 0.0f;
		}
		if (out - engine::driving::gOne >= 0.0f)
		{
			out = engine::driving::gOne;
		}
		float in = (engine::driving::gHalf - forcedFade) * engine::driving::gTwo;
		float outShown = (engine::driving::gOne - out) * fadeInPosition * fadeInScale;
		if (in < 0.0f)
		{
			in = 0.0f;
		}
		if (in - engine::driving::gOne >= 0.0f)
		{
			in = engine::driving::gOne;
		}
		float inShown = (1.0f - in) * fadeInPosition * fadeInScale;
		shownFirst->drawable.SetUnknownBC(inShown);
		forcedFirst->drawable.SetUnknownBC(outShown);
		LODLevel* last = shownLast;
		if (forcedLast == last)
		{
			if (inShown < outShown)
			{
				inShown = outShown;
			}
			forcedLast->drawable.SetUnknownBC(inShown);
		}
		else
		{
			if (shownFirst != last)
			{
				last->drawable.SetUnknownBC(inShown);
			}
			if (forcedFirst != forcedLast)
			{
				forcedLast->drawable.SetUnknownBC(outShown);
			}
		}
		forcedFade = step + forcedFade;
	}
#endif

	// A message of the shader palette's: the byte it points at takes the number of entries and the picked entry
	struct PaletteIndexMessage : public engine::Message
	{
		unsigned char* index;
	};

	// FUNCTION: ENGINE 0x102D9E80
	void LODRenderBehaviour::OnPostedMessage(engine::Message* message)
	{
		if (message->type == 0x16 && message->id == 6 && available != 0)
		{
			int count = available->data.Size();
			if ((unsigned int)(count - 1) <= 0xFE)
			{
				unsigned char* index = static_cast<PaletteIndexMessage*>(message)->index;
				*index = (unsigned char)(*index * (char)count + (char)availableIndex);
			}
		}
	}

	// FUNCTION: ENGINE 0x102DA2C0
	void LODRenderBehaviour::OnActiveChanged(bool active)
	{
		if (active != IsActive())
		{
			engine::Behaviour::OnActiveChanged(active);
			flags &= 0xFB;
			level = 0xFFFFFFFF;
			forcedFade = 0.0f;
			if (!active)
			{
				if (shownFirst != 0)
				{
					shownFirst->Hide();
					shownLast->Hide();
				}
				if (forcedFirst != 0)
				{
					forcedFirst->Hide();
					forcedLast->Hide();
				}
				int count = levels.Size();
				for (int i = 0; i < count; i++)
				{
					if (levels.begin[i].drawable.IsValid())
					{
						levels.begin[i].drawable.SetUnknownBC(1.0f);
					}
				}
			}
		}
	}

	// FUNCTION: ENGINE 0x102DA3A0
	void LODRenderBehaviour::ChangeDrawableLevels(unsigned int previous, const LODLevel* first, const LODLevel* last)
	{
		if (previous != 0xFFFFFFFF && IsActive() && (flags & 1) != 0)
		{
			flags |= 4;
			forcedFirst = shownFirst;
			forcedFade = 0.0f;
			shownFirst = const_cast<LODLevel*>(first);
			forcedLast = shownLast;
			shownLast = const_cast<LODLevel*>(last);
		}
		else
		{
			flags &= 0xFB;
			shownFirst = const_cast<LODLevel*>(first);
			shownLast = const_cast<LODLevel*>(last);
			if (IsActive())
			{
				ShowLevels(first, last);
			}
			else
			{
				const_cast<LODLevel*>(first)->Hide();
				shownLast->Hide();
			}
		}
		shownFirst->drawable.SetTransformQueued(owner->transform->value);
		if (poseSource != 0)
		{
			core::HeapScope scope(heap);
			pure3d::ReleaseCoreRef(reinterpret_cast<core::IRefCount*&>(poseSource->pose));
			core::IRefCount** pose = reinterpret_cast<core::IRefCount**>(&poseSource->pose);
			pure3d::AssignCoreRef(*pose, shownFirst->drawable.CreatePose((int)boneData, (int)&boneDataSize));
		}
		engine::AttributeUpdatedMessage message(engine::gBoundingBox);
		owner->SendMessage(&message);
	}

	inline float LengthOf(const math::Vector& v)
	{
		return sqrtf(v.z * v.z + v.y * v.y + v.x * v.x);
	}

	// FUNCTION: ENGINE 0x102DA540
	void LODRenderBehaviour::UpdateFade()
	{
		// Reset through a reference: the store then stays ahead of the load and compare of the lod range
		float& reset = fade;
		reset = 1.0f;
		if (lod.IsEmpty())
		{
			return;
		}
		// The Director hands out the word at the cinematographer's +0x40, which is a pure3d camera (name guess)
		pure3d::Camera* camera =
			(pure3d::Camera*)engine::camera::Director::Get()->GetCameraUnknown40(0, 0);
		if (camera == 0)
		{
			return;
		}
		const math::Matrix& transform = owner->transform->value;
		math::Vector position;
		transform.GetTranslation(position);
		math::Vector delta;
		math::Vector cameraPosition = camera->GetPosition();
		delta.Sub(position, cameraPosition);
		float distance = LengthOf(delta);
		float scale = gCameraManager->GetScale(camera);
		float divisor = scale > 1.0f ? scale : 1.0f;
		float scaled = fadeScale * gLODDistanceScale;
		float value = scaled * (distance / divisor);
		float clamped = math::Clamp(value, gLODRanges[distanceLevel].minimum, gLODRanges[distanceLevel].maximum);
		fade = 1.0f - (clamped - gLODRanges[distanceLevel].minimum) /
			(gLODRanges[distanceLevel].maximum - gLODRanges[distanceLevel].minimum);
		fade = math::Clamp(fade, 0.0f, 1.0f);
	}

	// FUNCTION: ENGINE 0x102DA700
	void LODRenderBehaviour::UpdateLevel()
	{
		unsigned int wanted = 0;
		if ((flags & 1) != 0 && !lod.IsEmpty())
		{
			unsigned int size = levels.Size();
			float t = math::Clamp(fade, 0.0f, 1.0f);
			wanted = (unsigned int)((1.0f - t) * (float)(unsigned int)(size - 1));
		}
		unsigned int previous = level;
		if (wanted != previous)
		{
			level = wanted;
			unsigned int last = wanted >= minimumLevels ? wanted : minimumLevels;
			ChangeDrawableLevels(previous, levels.begin + wanted, levels.begin + last);
		}
	}

	inline float HalfDiagonal(const math::AABB& box)
	{
		math::Vector half;
		half.Sub(box.max, box.min);
		half.x *= 0.5f;
		half.y *= 0.5f;
		half.z *= 0.5f;
		return LengthOf(half);
	}

	// The first update: the entry of the shader palette is picked and every level gets its drawable bound
	// FUNCTION: ENGINE 0x102DC5F0
	void LODRenderBehaviour::Slot1()
	{
		ShaderPaletteData* entry = 0;
		availableIndex = -1;
		if (available != 0 && available->data.begin != available->data.end)
		{
			availableIndex = math::gRandom->Range(0, available->data.Size() - 1);
			entry = &available->data.begin[availableIndex];
			Listen(0x16, true);
		}
		if ((flags & 8) == 0)
		{
			for (unsigned int i = 0; i < lod.Size(); i++)
			{
				AddLevel(lod.begin + i);
			}
			for (unsigned int i = 0; i < levels.Size(); i++)
			{
				LODLevel* item = levels.begin + i;
				if (entry != 0)
				{
					pure3d::pddiShaderInputInitData inputs;
					entry->FillShaderInputs(&inputs);
					item->drawable.CreateBindings(inputs);
					item->ApplyPalette(entry);
				}
				if (animation != 0)
				{
					item->drawable.PlayAnimation(animation, 1.0f, 0.0f, 0.0f, animation->numFrames,
						pure3d::Animation::CYCLE_MODE_2);
				}
			}
			if (!lod.IsEmpty() && !levels.IsEmpty())
			{
				const math::AABB* box = ((engine::render::DrawableArchetype*)lod[0].source)->GetBounds();
				float length = HalfDiagonal(*box);
				distanceLevel = 0;
				for (int i = 0; i < 3; i++)
				{
					if (length < gLODDistances[i])
					{
						distanceLevel = i;
						break;
					}
				}
			}
		}
		int count = levels.Size();
		if (count != 0)
		{
			unsigned int joints = 0;
			for (int i = 0; i < count; i++)
			{
				pure3d::Skeleton* skeleton = levels[i].drawable.GetSkeleton();
				if (skeleton != 0 && skeleton->mData.mJointCount > joints)
				{
					joints = skeleton->mData.mJointCount;
				}
			}
			core::HeapScope scope(heap);
			boneData = pure3d::AllocateBoneData(joints, &boneDataSize, 3);
		}
	}

	// FUNCTION: ENGINE 0x102DAF80
	void LODRenderBehaviour::Update(float dt, unsigned short mask)
	{
		math::Matrix matrix = owner->transform->value;
		if (scaleSource != 0)
		{
			LODScaleSource* source = scaleSource;
			math::Matrix scale = math::Matrix::IDENTITY;
			scale.Scale(source->scale.x, source->scale.y, source->scale.z);
			matrix.Multiply(scale, matrix);
		}
		if (shownFirst != 0)
		{
			shownFirst->drawable.SetTransform(matrix);
			if (shownFirst != shownLast)
			{
				shownLast->drawable.SetTransform(matrix);
			}
		}
		if (1.0f != fadeInPosition || 1.0f != fadeInTarget)
		{
			UpdateFadeIn(dt);
		}
		if ((flags & 4) != 0)
		{
			forcedFirst->drawable.SetTransform(matrix);
			if (forcedFirst != forcedLast)
			{
				forcedLast->drawable.SetTransform(matrix);
			}
			UpdateForced(dt);
		}
		else
		{
			if ((flags & 1) != 0)
			{
				UpdateFade();
			}
			UpdateLevel();
		}
		if (poseSource != 0)
		{
			pure3d::Pose* pose = poseSource->pose;
			if (pose != 0)
			{
				pose->Update();
				shownFirst->drawable.CopyPoseStateFrom(pose);
			}
		}
	}
	// FUNCTION: ENGINE 0x102DAB40
	LODRenderData::LODRenderData(const LODRenderData& other) : source(other.source), name(other.name)
	{
		if (source != 0)
		{
			source->AddRef();
		}
	}

	// FUNCTION: ENGINE 0x102DAB10
	LODRenderData& LODRenderData::operator=(const LODRenderData& other)
	{
		source = other.source;
		name = other.name;
		return *this;
	}

	// FUNCTION: ENGINE 0x102D90A0
	engine::render::DrawableArchetype* LODRenderData::GetArchetype() const
	{
		return static_cast<engine::render::DrawableArchetype*>(source);
	}

	// FUNCTION: ENGINE 0x102D90B0
	const content::ObjectName* LODRenderData::GetArchetypeName() const
	{
		return &name;
	}

	// FUNCTION: ENGINE 0x102D98A0
	void LODRenderData::SetArchetype(engine::render::DrawableArchetype* newArchetype, const content::ObjectName& newName)
	{
		name = newName;
		source = newArchetype;
		if (newArchetype != 0)
		{
			newArchetype->AddRef();
		}
	}

	// FUNCTION: ENGINE 0x102DB940
	content::MemberList* LODRenderData::GetMembers()
	{
		static content::MemberList sList;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetNamedReferenceMemberMetaType<LODRenderData, engine::render::DrawableArchetype>(
				&LODRenderData::GetArchetype, &LODRenderData::GetArchetypeName, &LODRenderData::SetArchetype, "p"),
				0, "drawable" }
		};
		sList.members = sMembers;
		sList.count = 1;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102D90E0
	bool LODRenderBehaviour::GetEnableGeoLOD() const
	{
		return bits.bound;
	}

	// FUNCTION: ENGINE 0x102D90F0
	bool LODRenderBehaviour::GetEnableGeoFade() const
	{
		return bits.geoFade;
	}

	// FUNCTION: ENGINE 0x102D94A0
	void LODRenderBehaviour::SetEnableGeoFade(bool enable)
	{
		bits.geoFade = enable;
	}

	// FUNCTION: ENGINE 0x102D94C0
	engine::render::DrawableArchetype* LODRenderBehaviour::GetSource() const
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x102D94D0
	const content::ObjectName* LODRenderBehaviour::GetSourceName() const
	{
		return &sourceName;
	}

	// FUNCTION: ENGINE 0x102D90C0
	pure3d::Animation* LODRenderBehaviour::GetAnimation() const
	{
		return 0;
	}

	// FUNCTION: ENGINE 0x102DBF90
	void LODRenderBehaviour::SetSource(engine::render::DrawableArchetype* archetype, const content::ObjectName& name)
	{
		sourceName = name;
		heap = core::GetCurrentHeap();
		unsigned int value;
		if (core::GetHeapAllocator(heap)->GetStat(0xb, (int*)&value))
		{
			heap = engine::GetGameObjectHeap();
		}
		bits.deferred = archetype == 0;
		if (!bits.deferred)
		{
			LODRenderData data(archetype);
			archetype->AddRef();
			AddLevel(&data);
		}
	}

	// FUNCTION: ENGINE 0x102DC390
	content::MemberList* LODRenderBehaviour::GetMembers()
	{
		static content::MemberList sList;
		sList.baseType = content::GetClassMetaType<engine::Behaviour>();
		static content::BaseClassCasterImpl<engine::Behaviour, LODRenderBehaviour> sCaster;
		sList.baseCaster = &sCaster;
		static content::MemberInfo sMembers[] =
		{
			{ content::GetMemberMetaType<LODRenderBehaviour, bool, 0>(&LODRenderBehaviour::GetEnableGeoLOD,
				&LODRenderBehaviour::SetBound, "p"), 0, "enableGeoLOD" },
			{ content::GetMemberMetaType<LODRenderBehaviour, bool, 1>(&LODRenderBehaviour::GetEnableGeoFade,
				&LODRenderBehaviour::SetEnableGeoFade, "p"), 0, "enableGeoFade" },
			{ content::GetNameMetaType<LODRenderBehaviour>(true, true, "pn"),
				content::MemberOffset(&((LODRenderBehaviour*)0)->packageName, (int)&((LODRenderBehaviour*)0)->packageName),
				"sourcePackage" },
			{ content::GetNamedReferenceMemberMetaType<LODRenderBehaviour, engine::render::DrawableArchetype>(
				&LODRenderBehaviour::GetSource, &LODRenderBehaviour::GetSourceName, &LODRenderBehaviour::SetSource, "p"),
				0, "drawableSource" },
			{ content::GetReferenceMemberMetaType<LODRenderBehaviour, pure3d::Animation>(
				&LODRenderBehaviour::GetAnimation, &LODRenderBehaviour::SetAnimation, "p"), 0, "animSource" },
			{ content::GetArrayDynamicMetaType<LODRenderBehaviour, container::ArrayDynamic<LODRenderData,
				container::AllocatorNew> >(content::GetClassMetaType<LODRenderData>(), "p"),
				content::MemberOffset((container::ArrayDynamic<LODRenderData, container::AllocatorNew>*)
					&((LODRenderBehaviour*)0)->lod, (int)&((LODRenderBehaviour*)0)->lod), "lod" },
			{ content::GetMemberReferenceMetaType<LODRenderBehaviour, ShaderPalette, 0>("p"),
				content::MemberOffset(&((LODRenderBehaviour*)0)->available, (int)&((LODRenderBehaviour*)0)->available),
				"shaderPalette" },
			{ content::GetMemberPrimitiveMetaType<LODRenderBehaviour, unsigned int, 0>("p"),
				content::MemberOffset(&((LODRenderBehaviour*)0)->minimumLevels,
					(int)&((LODRenderBehaviour*)0)->minimumLevels), "minShadowLODIndex" }
		};
		sList.members = sMembers;
		sList.count = 8;
		return &sList;
	}

	// FUNCTION: ENGINE 0x102DCD20
	// NONMATCHING: the engine loads the constant once at the top of the constructor and stores the level after the address
	// of the name; ours loads it after the level store (82.5 %)
#ifdef NONMATCHING
	LODRenderBehaviour::LODRenderBehaviour(engine::GameObject* newOwner) : engine::Behaviour(newOwner), shownFirst(0),
		forcedFirst(0), shownLast(0), forcedLast(0), animation(0), available(0), availableIndex(-1), distanceLevel(0),
		minimumLevels(0), level(-1), fade(engine::driving::gOne), forcedFade(fade),
		fadeInPosition(fade), fadeInTarget(fade), fadeInScale(fade), fadeScale(fade)
	{
		flags = flags & 0xF0;
		heap = 0;
		boneData = 0;
		boneDataSize = 0;
		Listen2(0x200, true);
		Listen(0x1A, true);
		Listen(1, true);
		Listen(2, true);
		Listen(7, true);
		Listen(0x3D, true);
		Listen(8, true);
		Listen(10, true);
		lod.Allocate(4);
		levels.Allocate(4);
		poseSource = (LODPoseSource*)owner->FindAttribute(gDrawableAttributeName);
		if (poseSource != 0 && poseSource->pose != 0)
		{
			poseSource->pose->AddRef();
		}
		scaleSource = (LODScaleSource*)owner->FindAttribute(engine::gScaleName);
		if (scaleSource != 0 && fabsf(scaleSource->scale.x - 1.0f) <= 0.00001f &&
			fabsf(scaleSource->scale.y - 1.0f) <= 0.00001f && fabsf(scaleSource->scale.z - 1.0f) <= 0.00001f)
		{
			scaleSource = 0;
		}
		int unset = -1;
		paletteIndexSource = (LODIndexSource*)owner->SetAttributeAndGet<int>(engine::gInstancePaletteIndex, unset, false);
	}
#endif

	// FUNCTION: ENGINE 0x102DCF80
	LODRenderBehaviour::~LODRenderBehaviour()
	{
		DestroyLevels();
		core::SafeRelease(animation);
		core::SafeRelease(available);
		core::Free(boneData);
	}

}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102D9580
// FUNCTION: ENGINE 0x102D9590
// FUNCTION: ENGINE 0x102D95A0
// FUNCTION: ENGINE 0x102D95B0
// FUNCTION: ENGINE 0x102D95C0
// FUNCTION: ENGINE 0x102D95E0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102D98F0
// FUNCTION: ENGINE 0x102DB490

// Kept copies (inline members, template instances and compiler-generated functions of this unit):

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102D9080
// FUNCTION: ENGINE 0x102D9930

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102D95D0
// FUNCTION: ENGINE 0x102D97D0
// FUNCTION: ENGINE 0x102DABC0
// FUNCTION: ENGINE 0x102DABF0
// FUNCTION: ENGINE 0x102DAC10
// FUNCTION: ENGINE 0x102DAC30
// FUNCTION: ENGINE 0x102DB4E0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102D9710
// FUNCTION: ENGINE 0x102D9750
// FUNCTION: ENGINE 0x102D9760
// FUNCTION: ENGINE 0x102D97E0
// FUNCTION: ENGINE 0x102D9870
// FUNCTION: ENGINE 0x102D9890
// FUNCTION: ENGINE 0x102D9940
// FUNCTION: ENGINE 0x102D9950
// FUNCTION: ENGINE 0x102DA940
// FUNCTION: ENGINE 0x102DAA10
// FUNCTION: ENGINE 0x102DAA90
// FUNCTION: ENGINE 0x102DAAA0
// FUNCTION: ENGINE 0x102DAAC0
// FUNCTION: ENGINE 0x102DAAE0
// FUNCTION: ENGINE 0x102DAB80
// FUNCTION: ENGINE 0x102DAC50
// FUNCTION: ENGINE 0x102DAC70
// FUNCTION: ENGINE 0x102DAC90
// FUNCTION: ENGINE 0x102DACB0
// FUNCTION: ENGINE 0x102DACE0
// FUNCTION: ENGINE 0x102DAD00
// FUNCTION: ENGINE 0x102DAD20
// FUNCTION: ENGINE 0x102DAD40
// FUNCTION: ENGINE 0x102DAD60
// FUNCTION: ENGINE 0x102DAD80
// FUNCTION: ENGINE 0x102DADA0
// FUNCTION: ENGINE 0x102DADC0
// FUNCTION: ENGINE 0x102DAED0
// FUNCTION: ENGINE 0x102DB580
// FUNCTION: ENGINE 0x102DB600
// FUNCTION: ENGINE 0x102DB680
// FUNCTION: ENGINE 0x102DB720
// FUNCTION: ENGINE 0x102DB7B0
// FUNCTION: ENGINE 0x102DB810
// FUNCTION: ENGINE 0x102DB8C0
// FUNCTION: ENGINE 0x102DC080
// FUNCTION: ENGINE 0x102DC0E0
// FUNCTION: ENGINE 0x102DCAC0
// FUNCTION: ENGINE 0x102DCC90
// FUNCTION: ENGINE 0x102DD020

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102DC110
// FUNCTION: ENGINE 0x102DCBF0

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102D9680
// FUNCTION: ENGINE 0x102D9700
// FUNCTION: ENGINE 0x102DC060
// FUNCTION: ENGINE 0x102DCC40
// FUNCTION: ENGINE 0x102DD0D0
