// engine::render::Drawable (unit 0x107E8020 - 0x107EE322, assert path ..\..\..\code\engine\render\async\private\
// drawable.cpp): the game thread's drawable handle methods, the static functions their render events run on the
// render thread, and engine::render::DeferredDeletionProxy (RTTI name). Names are guesses unless noted.
#include "code/core/debug.h"
#include "code/core/heap.h"
#include "code/core/memutils.h"
#include "code/engine/render/async/drawable.h"
#include "code/engine/render/async/renderevent.h"
#include "code/engine/render/async/private/drawableimpl.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/math/matrix.h"
#include "code/math/vector2.h"
#include "code/math/vector4.h"
#include "code/core/strings.h"
#include "code/content/memorystream.h"
#include "code/core/file/filesystem.h"
#include "code/engine/system/enginememory.h"
#include "code/pure3d/texture/texture.h"
#include "code/pure3d/pddi/dx9/dxcontext.h"
#include "code/pure3d/pddi/dx9/dxtexture.h"
#include "code/core/namecopy.h"

#define DRAWABLE_FILE "..\\..\\..\\code\\engine\\render\\async\\private\\drawable.cpp"

namespace engine
{
	namespace render
	{
		// The newest frame whose deferred deletions have run (raised by the proxies' destructors)
		static unsigned int gDeletedFrame;
		// The number of the next deferred deletion (the image's variable, 0x111BC664)
		extern unsigned int gDeferredFrame;

		// An entity on the deferred deletion list that records, when the list deletes it, that every deletion
		// deferred in its frame has run
		class DeferredDeletionProxy : public pure3d::Entity
		{
		public:
			// FUNCTION: ENGINE 0x107E89B0
			DeferredDeletionProxy(unsigned int frame) : mFrame(frame)
			{
			}
			// FUNCTION: ENGINE 0x107E89D0
			virtual ~DeferredDeletionProxy()
			{
				unsigned int frame = mFrame;
				if (gDeletedFrame < frame)
				{
					gDeletedFrame = frame;
				}
			}

			static void Defer(unsigned int frame);
			static bool IsDeleted(unsigned int frame);

			unsigned int mFrame;
			unsigned int mUnknown14;
		};

		// FUNCTION: ENGINE 0x107E8100
		static void DoSetRegistered(Drawable drawable, bool registered)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data && data->registered != registered)
			{
				if (registered)
				{
					GetRenderList()->Add(data->drawable, 0);
				}
				else
				{
					GetRenderList()->Remove(data->drawable);
				}
				data->registered = registered;
			}
		}

		// FUNCTION: ENGINE 0x107E8150
		static void DoUnknown106E02C0(Drawable drawable)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->Unknown106E02C0();
			}
		}

		// FUNCTION: ENGINE 0x107E8170
		static void DoSetFlag10(Drawable drawable)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->SetFlag10();
			}
		}

		// FUNCTION: ENGINE 0x107E8190
		static void DoClearFlag10(Drawable drawable)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->ClearFlag10();
			}
		}

		// FUNCTION: ENGINE 0x107E81B0
		static void DoSetSegmentVisible(Drawable drawable, unsigned __int64 segment, bool visible)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				unsigned short index = data->drawable->FindSegment(segment);
				data->drawable->SetSegmentVisible(index, visible);
			}
		}

		// FUNCTION: ENGINE 0x107E81F0
		static void DoUnknown106E09A0(Drawable drawable, Drawable other)
		{
			DrawableImpl* otherImpl = 0;
			DrawableImpl* impl = 0;
			DrawableData* data = GetDrawableData(other);
			if (data)
			{
				otherImpl = data->drawable;
			}
			data = GetDrawableData(drawable);
			if (data)
			{
				impl = data->drawable;
			}
			if (otherImpl && impl)
			{
				impl->Unknown106E09A0(otherImpl);
			}
		}

		// Sets up a frame controller for a play request: the start frame by mode, the range, speed, mode and cycles
		// FUNCTION: ENGINE 0x107E8230
		static void ApplyPlayback(pure3d::FrameController* controller, float start, float end, float speed,
			pure3d::Animation::CycleMode mode, unsigned int cycles)
		{
			if (controller)
			{
				float frame = controller->GetFrame();
				if (mode == 2 || mode == 4)
				{
					controller->SetFrame(start);
				}
				if (mode == 3 || mode == 5)
				{
					controller->SetFrame(end);
				}
				if (mode == 1 || mode == 0)
				{
					controller->SetFrame(frame);
				}
				controller->SetFrameRange(start, end);
				controller->SetRelativeSpeed(speed);
				controller->SetCycleMode(mode);
				controller->SetNumCycles(cycles);
			}
		}

		// FUNCTION: ENGINE 0x107E82E0
		static void DoUnknown106E03E0(Drawable drawable)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->Unknown106E03E0();
			}
		}

		// FUNCTION: ENGINE 0x107E8300
		static void DoUnknown106E0490(Drawable drawable)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->Unknown106E0490();
			}
		}

		// FUNCTION: ENGINE 0x107E8320
		static void DoSetUnknownCC(Drawable drawable, unsigned int value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data && data->drawable)
			{
				data->drawable->SetUnknownCC(value);
			}
		}

		// FUNCTION: ENGINE 0x107E8350
		static void DoSetName(Drawable drawable, unsigned __int64 name)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->SetName(name);
			}
		}

		// FUNCTION: ENGINE 0x107E8380
		static void DoSetTransform(Drawable drawable, math::Matrix transform)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data && data->drawable && data->drawable->IsRegistered())
			{
				data->drawable->SetTransform(transform);
			}
		}

		// FUNCTION: ENGINE 0x107E83B0
		static void DoSharePose(Drawable drawable, Drawable other)
		{
			DrawableImpl* otherImpl = 0;
			DrawableImpl* impl = 0;
			DrawableData* data = GetDrawableData(other);
			if (data)
			{
				otherImpl = data->drawable;
			}
			data = GetDrawableData(drawable);
			if (data)
			{
				impl = data->drawable;
			}
			if (otherImpl && impl)
			{
				impl->SetPose(otherImpl->GetPose());
			}
		}

		// FUNCTION: ENGINE 0x107E8400
		static void DoCopyPoseState(Drawable drawable, Drawable other)
		{
			DrawableImpl* otherImpl = 0;
			DrawableImpl* impl = 0;
			DrawableData* data = GetDrawableData(other);
			if (data)
			{
				otherImpl = data->drawable;
			}
			data = GetDrawableData(drawable);
			if (data)
			{
				impl = data->drawable;
			}
			if (otherImpl && impl)
			{
				impl->GetPose()->CopyStateFrom(otherImpl->GetPose());
			}
		}

		// The event holds a reference to the pose, released here
		// FUNCTION: ENGINE 0x107E8450
		static void DoSetPose(Drawable drawable, pure3d::Pose* pose)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->SetPose(pose);
			}
			pose->Release();
		}

		// Does nothing in this build but look the drawable up under the heap
		// FUNCTION: ENGINE 0x107E8480
		static void DoSetShader(Drawable drawable, pure3d::Shader* shader, bool enable, int heap)
		{
			core::HeapScope scope(heap);
			GetDrawableData(drawable);
		}

		// FUNCTION: ENGINE 0x107E84B0
		static void DoClearUnknown78(Drawable drawable)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data && data->drawable)
			{
				data->drawable->SetUnknown78(0);
			}
		}

		// FUNCTION: ENGINE 0x107E84D0
		static void DoApplyExpressionPose(Drawable drawable, pure3d::ExpressionPose* pose)
		{
			if (pose)
			{
				DrawableData* data = GetDrawableData(drawable);
				if (data && data->drawable)
				{
					void* target = data->drawable->GetExpressionMixer();
					if (target)
					{
						pose->Unknown10730C10(target);
						pose->Release();
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107E8510
		static void DoSetFlag101Bit1(Drawable drawable, bool value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->SetFlag101Bit1(value);
			}
		}

		// FUNCTION: ENGINE 0x107E8530
		static void DoApplyModifier(Drawable drawable, DrawableModifier* modifier)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data && data->drawable)
			{
				modifier->Apply(data->drawable);
			}
			else
			{
				modifier->Apply(0);
			}
		}

		// FUNCTION: ENGINE 0x107E8560
		Drawable Drawable::Allocate(SourceDrawable* source)
		{
			return AllocateDrawable(source, true);
		}

		// FUNCTION: ENGINE 0x107E8580
		bool Drawable::IsValid() const
		{
			return IsValidDrawable(*this);
		}

		// FUNCTION: ENGINE 0x107E8590
		void* Drawable::GetSourceParameters() const
		{
			void* result = 0;
			DrawableData* data = GetDrawableData(*this);
			if (data && data->sourceDrawable)
			{
				result = data->sourceDrawable->GetParameters();
			}
			return result;
		}

		// FUNCTION: ENGINE 0x107E85C0
		bool Drawable::IsUnknown8() const
		{
			DrawableData* data = GetDrawableData(*this);
			if (data)
			{
				return data->unknown8;
			}
			return true;
		}

		// FUNCTION: ENGINE 0x107E86C0
		ParameterSet* Drawable::GetSourceDrawable() const
		{
			DrawableData* data = GetDrawableData(*this);
			if (data)
			{
				return (ParameterSet*)data->sourceDrawable;
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x107E86E0
		void Drawable::SetTransform(const math::Matrix& transform) const
		{
			DrawableData* data = GetDrawableData(*this);
			if (data)
			{
				OLD_ASSERT_TEXT_AT(DRAWABLE_FILE, 0x9bb, data->drawable, "drawableData->drawable");
				if (data->drawable)
				{
					data->drawable->SetTransform(transform);
				}
			}
		}

		// FUNCTION: ENGINE 0x107E8740
		void Drawable::CopyPoseStateFrom(pure3d::Pose* other) const
		{
			DrawableData* data = GetDrawableData(*this);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				pure3d::Pose* state = impl->GetPose();
				if (state)
				{
					state->CopyStateFrom(other);
					impl->MarkPoseDirty();
				}
			}
		}

		// FUNCTION: ENGINE 0x107E8780
		bool Drawable::IsCyclic() const
		{
			DrawableData* data = GetDrawableData(*this);
			if (data && data->drawable)
			{
				return data->drawable->IsCyclic();
			}
			return false;
		}

		// FUNCTION: ENGINE 0x107E87A0
		bool Drawable::IsFinished() const
		{
			DrawableData* data = GetDrawableData(*this);
			if (data)
			{
				if (data->drawable)
				{
					return data->drawable->IsFinished();
				}
				return false;
			}
			return true;
		}

		// FUNCTION: ENGINE 0x107E87E0
		void Drawable::SetUnknownFloat(int index, float value) const
		{
			DrawableData* data = GetDrawableData(*this);
			if (data)
			{
				data->drawable->SetUnknownFloat(index, value);
			}
		}

		// FUNCTION: ENGINE 0x107E87C0
		void Drawable::Method106E0830(int value) const
		{
			DrawableData* data = GetDrawableData(*this);
			if (data)
			{
				data->drawable->Unknown106E0830(value);
			}
		}

		// FUNCTION: ENGINE 0x107E8810
		bool Drawable::ReturnsTrue() const
		{
			return true;
		}

		// FUNCTION: ENGINE 0x107E8820
		pure3d::Pose* Drawable::CreatePoseInstance() const
		{
			DrawableData* data = GetDrawableData(*this);
			if (data)
			{
				if (data->sourceDrawable)
				{
					if (data->sourceDrawable->drawable->GetPose())
					{
						return data->sourceDrawable->drawable->GetPose()->CreateInstance(3);
					}
					if (data->sourceDrawable->drawable->GetSkeleton())
					{
						return data->sourceDrawable->drawable->GetSkeleton()->CreatePose(3);
					}
				}
				else if (data->drawable)
				{
					return data->drawable->GetPose()->CreateInstance(3);
				}
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x107E88A0
		pure3d::Pose* Drawable::CreatePose(int a, int b) const
		{
			DrawableData* data = GetDrawableData(*this);
			if (data)
			{
				if (data->sourceDrawable)
				{
					pure3d::Skeleton* owner = data->sourceDrawable->drawable->GetSkeleton();
					if (data->sourceDrawable->drawable->GetPose())
					{
						pure3d::Pose* state = data->sourceDrawable->drawable->GetPose();
						pure3d::Pose* object = new pure3d::Pose(owner, a, b, 3);
						object->CopyFrom(state);
						return object;
					}
					if (owner)
					{
						return new pure3d::Pose(owner, a, b, 3);
					}
				}
				else if (data->drawable)
				{
					pure3d::Skeleton* owner = data->drawable->GetSkeleton();
					pure3d::Pose* state = data->drawable->GetPose();
					pure3d::Pose* object = new pure3d::Pose(owner, a, b, 3);
					object->CopyFrom(state);
					return object;
				}
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x107E8980
		pure3d::Skeleton* Drawable::GetSkeleton() const
		{
			DrawableData* data = GetDrawableData(*this);
			pure3d::Skeleton* result = 0;
			if (data)
			{
				if (data->sourceDrawable)
				{
					result = data->sourceDrawable->drawable->GetSkeleton();
				}
				else if (data->drawable)
				{
					result = data->drawable->GetSkeleton();
				}
			}
			return result;
		}

		// FUNCTION: ENGINE 0x107E8A30
		void DeferredDeletionProxy::Defer(unsigned int frame)
		{
			core::HeapScope scope(1);
			DeferDelete(new DeferredDeletionProxy(frame));
		}

		// FUNCTION: ENGINE 0x107E8A90
		bool DeferredDeletionProxy::IsDeleted(unsigned int frame)
		{
			return gDeletedFrame >= frame;
		}

		// FUNCTION: ENGINE 0x107E8B60
		static void DoCreate(Drawable drawable, int heap, DrawableCreator* creator)
		{
			core::HeapScope scope(heap);
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->created = true;
				DrawableImpl* impl = creator->Create();
				if (impl)
				{
					pure3d::RefCounted::Assign(data->drawable, impl);
					if (data->registerOnCreate)
					{
						data->registered = true;
						GetRenderList()->Add(data->drawable, 0);
					}
					else
					{
						data->registered = false;
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107E8BE0
		static void DoDestroy(Drawable drawable, DestroyMode mode)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data && data->drawable)
			{
				unsigned int count = data->drawable->parts.Size();
				for (unsigned int i = 0; i < count; i++)
				{
					PartRef part(data->drawable, i);
					pure3d::PrimitiveState* state = part->state;
					if (state && state->GetType() == 0x10)
					{
						pure3d::GetParticleManager()->ReleaseState(state);
					}
				}
			}
			FreeDrawable(drawable, mode);
		}

		// The visibilities come in memory from the event queue, freed here
		// FUNCTION: ENGINE 0x107E8C90
		static void DoSetSegmentVisibility(Drawable drawable, engine::DrawableSegmentVisibility* visibilities,
			unsigned int count)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				for (unsigned int i = 0; i < count; i++)
				{
					core::Name<core::CaseSensitiveKey> name(visibilities[i].name);
					unsigned short segment = data->drawable->FindSegment(name);
					data->drawable->SetSegmentVisible(segment, visibilities[i].visible);
				}
			}
			FreeRenderEvent(visibilities);
		}

		// FUNCTION: ENGINE 0x107E8D10
		static void DoSetPartsUnknown(Drawable drawable, bool value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				for (unsigned int i = 0; i < (unsigned int)impl->parts.Size(); i++)
				{
					PartRef part(impl, i);
					part.Unknown106E14B0(value);
				}
			}
		}

		// FUNCTION: ENGINE 0x107E8D90
		static void DoPlay(Drawable drawable, float start, float end, float speed, pure3d::Animation::CycleMode mode,
			unsigned int cycles)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->Unknown106E02C0();
				ApplyPlayback(data->drawable->GetUnknown78(), start, end, speed, mode, cycles);
				ApplyPlayback(data->drawable->GetUnknown7C(), start, end, speed, mode, cycles);
				ApplyPlayback(data->drawable->GetUnknown80(), start, end, speed, mode, cycles);
				unsigned int count = data->drawable->parts.Size();
				for (unsigned int i = 0; i < count; i++)
				{
					PartRef part(data->drawable, i);
					pure3d::PrimitiveState* state = part->state;
					if (state)
					{
						switch (state->GetType())
						{
						case 2:
							ApplyPlayback(((pure3d::MeshState*)state)->GetController1(), start, end, speed, mode,
								cycles);
							ApplyPlayback(((pure3d::MeshState*)state)->GetController2(), start, end, speed, mode,
								cycles);
							ApplyPlayback(((pure3d::MeshState*)state)->GetController3(), start, end, speed, mode,
								cycles);
							break;
						case 4:
							ApplyPlayback(((pure3d::SkinState*)state)->GetController1(), start, end, speed, mode,
								cycles);
							ApplyPlayback(((pure3d::SkinState*)state)->GetController2(), start, end, speed, mode,
								cycles);
							break;
						case 8:
							ApplyPlayback(((pure3d::GpuSkinState*)state)->GetController(), start, end, speed, mode,
								cycles);
							break;
						}
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107E8FF0
		// EQUIVALENT: same instructions; the original compares the part counts the other way round (cmp ebx, ecx)
		static void DoShareBindings(Drawable drawable, Drawable other, int heap)
		{
			core::HeapScope scope(heap);
			DrawableImpl* otherImpl = 0;
			DrawableImpl* impl = 0;
			DrawableData* data = GetDrawableData(other);
			if (data)
			{
				otherImpl = data->drawable;
			}
			data = GetDrawableData(drawable);
			if (data)
			{
				impl = data->drawable;
			}
			if (otherImpl && impl && impl->parts.Size() == otherImpl->parts.Size())
			{
				unsigned int i = 0;
				unsigned int count = otherImpl->parts.Size();
				for (; i < count; i++)
				{
					PartRef sourcePart(otherImpl, i);
					PartBindingSource* source = sourcePart->GetBindingSource();
					if (source)
					{
						PartBinding* binding = source->CreateBinding();
						PartRef targetPart(impl, i);
						targetPart->SetBinding(binding);
					}
				}
			}
		}

		// Looks for a part with a binding source and does nothing with it in this build
		// FUNCTION: ENGINE 0x107E9110
		static void DoFindBindingSource(Drawable drawable, Drawable other, int heap)
		{
			core::HeapScope scope(heap);
			DrawableImpl* otherImpl = 0;
			DrawableImpl* impl = 0;
			DrawableData* data = GetDrawableData(other);
			if (data)
			{
				otherImpl = data->drawable;
			}
			data = GetDrawableData(drawable);
			if (data)
			{
				impl = data->drawable;
			}
			if (!otherImpl || !impl)
			{
				return;
			}
			unsigned int count = otherImpl->parts.Size();
			for (unsigned int i = 0; i < count; i++)
			{
				PartRef part(otherImpl, i);
				if (part->primitive && part->primitive->unknown18)
				{
					break;
				}
			}
		}

		// FUNCTION: ENGINE 0x107E91D0
		static void DoResetStates(Drawable drawable)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				if (impl)
				{
					unsigned int count = impl->parts.Size();
					for (unsigned int i = 0; i < count; i++)
					{
						PartRef part(impl, i);
						pure3d::PrimitiveState* state = part->state;
						if (state && state->GetBindingSource())
						{
							state->Unknown106F2F00(0);
						}
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107E9260
		static void DoPlayAnimation(Drawable drawable, pure3d::Animation* animation, float speed, float frame,
			float start, float end, pure3d::Animation::CycleMode mode)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data && !data->unknown8)
			{
				DrawableImpl* impl = data->drawable;
				if (impl)
				{
					if (!animation)
					{
						impl->SetUnknown78(data->unknown4);
						if (!data->unknown4 && impl->GetPose())
						{
							impl->GetPose()->Unknown106DD760();
						}
						pure3d::RefCounted::Release(data->unknown4);
					}
					else
					{
						pure3d::RefCounted::Assign(data->unknown4, impl->GetUnknown78());
						pure3d::PoseAnimationController* controller;
						{
							core::HeapScope scope(0x76);
							controller = new pure3d::PoseAnimationController();
							impl->SetUnknown78(controller);
						}
						controller->SetNameFrom(animation);
						controller->SetAnimation(animation, 0.0f, 0.0f);
						float startFrame = frame;
						if (0.0f > startFrame)
						{
							float wrapped = animation->numFrames + startFrame;
							startFrame = 0.0f > wrapped ? 0.0f : wrapped;
						}
						float endFrame = end;
						if (0.0f > endFrame)
						{
							float wrapped = animation->numFrames + endFrame;
							endFrame = 0.0f > wrapped ? 0.0f : wrapped;
						}
						controller->SetFrameRange(start, endFrame);
						controller->SetFrame(startFrame);
						controller->SetRelativeSpeed(speed);
						controller->SetCycleMode(mode);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107E93F0
		static void DoPlaySkinAnimation(Drawable drawable, pure3d::Animation* animation, float speed, float frame,
			float start, float end, pure3d::Animation::CycleMode mode)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				if (impl)
				{
					unsigned int count = impl->parts.Size();
					for (unsigned int i = 0; i < count; i++)
					{
						PartRef part(impl, i);
						pure3d::PrimitiveState* state = part->state;
						if (state)
						{
							pure3d::SkinState* skin = dynamic_cast<pure3d::SkinState*>(state);
							if (skin)
							{
								pure3d::FrameController* controller = skin->GetController2();
								if (controller)
								{
									controller->Reset();
									controller->SetNameFrom(animation);
									static_cast<pure3d::AnimationFrameController*>(controller)->SetAnimation(animation, 0.0f, 0.0f);
									float startFrame = frame;
									if (0.0f > startFrame)
									{
										float wrapped = animation->numFrames + startFrame;
										startFrame = 0.0f > wrapped ? 0.0f : wrapped;
									}
									float endFrame = end;
									if (0.0f > endFrame)
									{
										float wrapped = animation->numFrames + endFrame;
										endFrame = 0.0f > wrapped ? 0.0f : wrapped;
									}
									controller->SetFrameRange(start, endFrame);
									controller->SetFrame(startFrame);
									controller->SetRelativeSpeed(speed);
									controller->SetCycleMode(mode);
								}
							}
						}
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107E9590
		// EQUIVALENT: same instructions; the original's frame puts the heap scope below the spilled drawable and render object pointers
		static void DoPlayPartAnimation(Drawable drawable, pure3d::Animation* animation, float speed, float frame,
			float start, float end, pure3d::Animation::CycleMode mode, int heap)
		{
			core::HeapScope scope(heap);
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				if (impl)
				{
					unsigned int count = impl->parts.Size();
					for (unsigned int i = 0; i < count; i++)
					{
						PartRef part(impl, i);
						pure3d::PrimitiveState* state = part->state;
						if (!state)
						{
							part.Unknown106DFD70();
							state = part->state;
							if (!state)
							{
								continue;
							}
						}
						pure3d::FrameController* controller;
						if (state->primitive)
						{
							int type = state->primitive->type;
							if (type == 2)
							{
								controller = ((pure3d::MeshState*)state)->GetController1();
							}
							else if (type == 4)
							{
								controller = ((pure3d::SkinState*)state)->GetController1();
							}
							else
							{
								goto other;
							}
							if (controller)
							{
								goto play;
							}
						}
					other:
						controller = part.Unknown106DFE20();
						if (!controller)
						{
							continue;
						}
					play:
						controller->Reset();
						controller->SetNameFrom(animation);
						static_cast<pure3d::AnimationFrameController*>(controller)->SetAnimation(animation, 0.0f, 0.0f);
						controller->SetBindingSource(part->GetBindingSource());
						float startFrame = frame;
						if (0.0f > startFrame)
						{
							float wrapped = animation->numFrames + startFrame;
							startFrame = 0.0f > wrapped ? 0.0f : wrapped;
						}
						float endFrame = end;
						if (0.0f > endFrame)
						{
							float wrapped = animation->numFrames + endFrame;
							endFrame = 0.0f > wrapped ? 0.0f : wrapped;
						}
						controller->SetFrameRange(start, endFrame);
						controller->SetFrame(startFrame);
						controller->SetRelativeSpeed(speed);
						controller->SetCycleMode(mode);
					}
					if (data->registered)
					{
						DoSetRegistered(drawable, false);
						DoSetRegistered(drawable, true);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107E97B0
		static void DoSetVertexDeformRegion(Drawable drawable, pure3d::VertexDeformRegion* region)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				unsigned int i = 0;
				unsigned int count = data->drawable->parts.Size();
				for (; i < count; i++)
				{
					PartRef part(data->drawable, i);
					pure3d::PrimitiveState* state = part->state;
					pure3d::MeshState* mesh = dynamic_cast<pure3d::MeshState*>(state);
					if (mesh)
					{
						pure3d::FrameController* controller = mesh->GetController3();
						if (controller)
						{
							((pure3d::VertexRegionAnimController*)controller)->SetRegion(region);
						}
					}
				}
			}
			if (region)
			{
				region->Release();
			}
		}

		// FUNCTION: ENGINE 0x107E9870
		static void DoSetPartsUnknown2C(Drawable drawable, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				unsigned int count = data->drawable->parts.Size();
				for (unsigned int i = 0; i < count; i++)
				{
					data->drawable->SetPartUnknown2C(i, value);
				}
			}
		}

		// FUNCTION: ENGINE 0x107E98D0
		static void DoSetSegmentUnknown2C(Drawable drawable, core::Name<core::CaseSensitiveKey> segment, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				unsigned short index = data->drawable->FindSegment(segment);
				unsigned int first = 0;
				unsigned int count = 0;
				data->drawable->GetSegmentParts(index, &first, &count);
				unsigned int end = first + count;
				for (unsigned int i = first; i < end; i++)
				{
					data->drawable->SetPartUnknown2C(i, value);
				}
			}
		}

		// FUNCTION: ENGINE 0x107E9950
		static void DoResetParticles(Drawable drawable)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef part(impl, i);
					if (part->primitive->type == 0x10)
					{
						PartRef statePart(impl, i);
						pure3d::ParticleSystemState* state = (pure3d::ParticleSystemState*)statePart->state;
						float zero = 0.0f;
						state->SetOverride(pure3d::gParticleKey1127F214, 2,
							&zero);
					}
					else
					{
						PartRef otherPart(impl, i);
						otherPart.Unknown106E14B0(0);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107E9A30
		static void DoSetEffectOverrides(Drawable drawable, EffectOverrides overrides)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef part(impl, i);
					if (part->primitive->type == 0x10)
					{
						PartRef statePart(impl, i);
						pure3d::ParticleSystemState* state = (pure3d::ParticleSystemState*)statePart->state;
						state->SetOverride(pure3d::gParticleKey1127F214, 2, &overrides.values[0]);
						state->SetOverride(pure3d::gParticleKey1127F2C8, 2, &overrides.values[1]);
						state->SetOverride(pure3d::gParticleKey1127F15C, 2, &overrides.values[2]);
						state->SetOverride(pure3d::gParticleKey1127F20C, 2, &overrides.values[3]);
						state->SetOverride(pure3d::gParticleKey1127F2DC, 2, &overrides.values[4]);
						state->SetOverride(pure3d::gParticleKey1127F188, 2, &overrides.values[5]);
						state->SetOverride(pure3d::gParticleKey1127F2BC, 2, &overrides.values[6]);
						state->SetOverride(pure3d::gParticleKey1127F208, 2, &overrides.values[7]);
						state->SetOverride(pure3d::gParticleKey1127F2AC, 2, &overrides.values[8]);
						state->SetOverride(pure3d::gParticleKey1127F330, 2, &overrides.values[9]);
						state->SetOverride(pure3d::gParticleKey1127F0B8, 2, &overrides.values[10]);
						state->SetOverride(pure3d::gParticleKey1127F284, 2, &overrides.values[11]);
						state->SetOverride(pure3d::gParticleKey1127F1CC, 2, &overrides.values[12]);
						state->SetOverride(pure3d::gParticleKey1127F144, 2, &overrides.values[13]);
						state->SetOverride(pure3d::gParticleKey1127F338, 2, &overrides.values[14]);
						state->SetOverride(pure3d::gParticleKey1127F158, 2, &overrides.values[15]);
						state->SetGeneratorParameter3(pure3d::gParticleKey1127F15C, 2, &overrides.values[16]);
						state->SetGeneratorParameter3(pure3d::gParticleKey1127F20C, 2, &overrides.values[17]);
						state->SetGeneratorParameter3(pure3d::gParticleKey1127F2DC, 2, &overrides.values[18]);
						state->SetGeneratorParameter3(pure3d::gParticleKey1127F188, 2, &overrides.values[19]);
						state->SetGeneratorParameter3(pure3d::gParticleKey1127F2BC, 2, &overrides.values[20]);
						state->SetGeneratorParameter3(pure3d::gParticleKey1127F208, 2, &overrides.values[21]);
						state->SetGeneratorParameter3(pure3d::gParticleKey1127F218, 2, &overrides.values[22]);
						state->SetGeneratorParameter3(pure3d::gParticleKey1127F144, 2, &overrides.values[23]);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107E9CF0
		static void DoSetGeneratorVector(Drawable drawable, core::Name<core::CaseInsensitiveKey32> name,
			math::Vector value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef part(impl, i);
					if (part->primitive->type == 0x10)
					{
						PartRef statePart(impl, i);
						((pure3d::ParticleSystemState*)statePart->state)->SetGeneratorParameter(name, 0, &value);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107E9DB0
		static void DoSetGeneratorFloat2(Drawable drawable, core::Name<core::CaseInsensitiveKey32> name, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef part(impl, i);
					if (part->primitive->type == 0x10)
					{
						PartRef statePart(impl, i);
						((pure3d::ParticleSystemState*)statePart->state)->SetGeneratorParameter2(name, 2,
							&value);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107E9E70
		static void DoSetParticleFloat(Drawable drawable, core::Name<core::CaseInsensitiveKey32> name, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef part(impl, i);
					if (part->primitive->type == 0x10)
					{
						PartRef statePart(impl, i);
						((pure3d::ParticleSystemState*)statePart->state)->SetOverride(name, 2, &value);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107E9F20
		static void DoSetGeneratorFloat3(Drawable drawable, core::Name<core::CaseInsensitiveKey32> name, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef part(impl, i);
					if (part->primitive->type == 0x10)
					{
						PartRef statePart(impl, i);
						((pure3d::ParticleSystemState*)statePart->state)->SetGeneratorParameter3(name, 2,
							&value);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107E9FE0
		static void DoSetParticleUnknownE70(Drawable drawable, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef part(impl, i);
					if (part->primitive->type == 0x10)
					{
						PartRef statePart(impl, i);
						((pure3d::ParticleSystemState*)statePart->state)->Unknown10709E70(value);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107EA090
		static void DoSetParticleUnknownE50(Drawable drawable, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef part(impl, i);
					if (part->primitive->type == 0x10)
					{
						PartRef statePart(impl, i);
						((pure3d::ParticleSystemState*)statePart->state)->Unknown10709E50(value);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107EA140
		static void DoSetParticleUnknownE40(Drawable drawable, bool value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef part(impl, i);
					if (part->primitive->type == 0x10)
					{
						PartRef statePart(impl, i);
						((pure3d::ParticleSystemState*)statePart->state)->Unknown10709E40(value);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107EA1F0
		static void DoSetParticleUnknownCC0(Drawable drawable, bool value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef part(impl, i);
					if (part->primitive->type == 0x10)
					{
						PartRef statePart(impl, i);
						((pure3d::ParticleSystemState*)statePart->state)->Unknown10709CC0(value);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107EA2A0
		static void DoSetParticleUnknown49C(Drawable drawable, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef part(impl, i);
					if (part->primitive->type == 0x10)
					{
						PartRef statePart(impl, i);
						((pure3d::ParticleSystemState*)statePart->state)->SetUnknown49C(value);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107EA350
		static void DoSetParticleUnknown4A8(Drawable drawable, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef part(impl, i);
					if (part->primitive->type == 0x10)
					{
						PartRef statePart(impl, i);
						((pure3d::ParticleSystemState*)statePart->state)->SetUnknown4A8(value);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107EA400
		static void DoSetParticleUnknown4B8(Drawable drawable, bool value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef part(impl, i);
					if (part->primitive->type == 0x10)
					{
						PartRef statePart(impl, i);
						((pure3d::ParticleSystemState*)statePart->state)->SetUnknown4B8(value);
					}
				}
			}
		}

		// The distance fade of a particle system (state +0x4A4 reaches the
		// vertex colour through the TEXCOORD1.w fade)
		// FUNCTION: ENGINE 0x107EA4B0
		static void DoSetParticleFade(Drawable drawable, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef part(impl, i);
					if (part->primitive->type == 0x10)
					{
						PartRef statePart(impl, i);
						((pure3d::ParticleSystemState*)statePart->state)->SetUnknown4A4(value);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107EA560
		static void DoParticleUnknownCD0(Drawable drawable)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef part(impl, i);
					if (part->primitive->type == 0x10)
					{
						PartRef statePart(impl, i);
						((pure3d::ParticleSystemState*)statePart->state)->Unknown10709CD0();
					}
				}
				impl->UpdateBounds(true);
			}
		}

		// FUNCTION: ENGINE 0x107EA610
		static void DoCreateBindings(Drawable drawable, pure3d::pddiShaderInputInitData init, int heap)
		{
			core::HeapScope scope(heap);
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				for (unsigned int i = 0; i < (unsigned int)impl->parts.Size(); i++)
				{
					PartRef ref(impl, i);
					DrawablePart* part = ref.Get();
					if (!part->binding)
					{
						PartBindingSource* source = (PartBindingSource*)part->GetRenderBinding();
						if (source)
						{
							part->SetBinding(source->CreateBinding());
						}
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107EA710
		// EQUIVALENT: our compile folds the part's address into the load of the binding; the original computes the address first
		static void DoSetBindingVector4(Drawable drawable, core::CaseInsensitiveKey32 key, math::Vector4 value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				for (unsigned int i = 0; i < (unsigned int)impl->parts.Size(); i++)
				{
					PartRef ref(impl, i);
					DrawablePart* part = ref.Get();
					PartBinding* binding = part->binding;
					if (binding)
					{
						core::Name<core::CaseInsensitiveKey32> name(key);
						binding->shader->SetVector4(name, value);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107EA7C0
		// EQUIVALENT: as DoSetBindingVector4
		static void DoSetBindingVector(Drawable drawable, core::CaseInsensitiveKey32 key, math::Vector value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				for (unsigned int i = 0; i < (unsigned int)impl->parts.Size(); i++)
				{
					PartRef ref(impl, i);
					DrawablePart* part = ref.Get();
					PartBinding* binding = part->binding;
					if (binding)
					{
						core::Name<core::CaseInsensitiveKey32> name(key);
						binding->shader->SetVector3(name, value);
					}
				}
			}
		}

		// Two-component parameters are not passed on in this build
		// FUNCTION: ENGINE 0x107EA870
		static void DoSetBindingVector2(Drawable drawable, core::CaseInsensitiveKey32 key, math::Vector2 value)
		{
		}

		// FUNCTION: ENGINE 0x107EA880
		// EQUIVALENT: as DoSetBindingVector4
		static void DoSetBindingFloat(Drawable drawable, core::CaseInsensitiveKey32 key, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				for (unsigned int i = 0; i < (unsigned int)impl->parts.Size(); i++)
				{
					PartRef ref(impl, i);
					DrawablePart* part = ref.Get();
					PartBinding* binding = part->binding;
					if (binding)
					{
						core::Name<core::CaseInsensitiveKey32> name(key);
						binding->shader->SetFloat(name, value);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107EA930
		// EQUIVALENT: as DoSetBindingVector4
		static void DoSetBindingBool(Drawable drawable, core::CaseInsensitiveKey32 key, bool value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				for (unsigned int i = 0; i < (unsigned int)impl->parts.Size(); i++)
				{
					PartRef ref(impl, i);
					DrawablePart* part = ref.Get();
					PartBinding* binding = part->binding;
					if (binding)
					{
						core::Name<core::CaseInsensitiveKey32> name(key);
						binding->shader->SetBool(name, value);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107EA9E0
		static void DoUnknown106E1250(Drawable drawable, core::Name<core::CaseSensitiveKey> name)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->Unknown106E1250(name);
			}
		}

		// FUNCTION: ENGINE 0x107EAA00
		Drawable::InstanceOptions::InstanceOptions(const InstanceOptions& other)
		{
			b0 = other.b0;
			b1 = other.b1;
			b2 = other.b2;
			b3 = other.b3;
			b4 = other.b4;
			b5 = other.b5;
			shareSource = other.shareSource;
			instanceOf = other.instanceOf;
			colour.x = other.colour.x;
			colour.y = other.colour.y;
			colour.z = other.colour.z;
			colour.w = other.colour.w;
			unknown1C = other.unknown1C;
			unknown20 = other.unknown20;
			unknown24 = other.unknown24;
		}

		// The drawable of a game object (it answers a GetCurrentDrawable message)
		// FUNCTION: ENGINE 0x107EAA70
		Drawable::Drawable(GameObject* object) : mHandle(0xffffffff)
		{
			GetCurrentDrawable message;
			object->SendMessage(&message);
			mHandle = message.drawable.mHandle;
		}

		// FUNCTION: ENGINE 0x107EAAD0
		void* Drawable::GetExpressionData() const
		{
			DrawableData* data = GetDrawableData(*this);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				if (impl || (impl = data->sourceDrawable->drawable) != 0)
				{
					pure3d::VertexOffsetExpressionMixer* mixer = impl->GetExpressionMixer();
					if (mixer)
					{
						return mixer->mExpressions;
					}
				}
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x107EAB00
		// EQUIVALENT: the clamp of the count is a conditional move here and a branch in the original
		void Drawable::SetJointMatrices(const JointMatrix* matrices, unsigned int count) const
		{
			DrawableData* data = GetDrawableData(*this);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				pure3d::Pose* pose = impl->GetPose();
				if (count > pose->mData.mArrays.mJointCount)
				{
					count = pose->mData.mArrays.mJointCount;
				}
				for (unsigned int i = 0; i != count; i++)
				{
					((JointMatrix*)pose->mData.mWorldMatrices)[i] = matrices[i];
				}
				pose->Unknown106DD730();
				impl->MarkPoseDirty();
			}
		}

		// FUNCTION: ENGINE 0x107EABD0
		bool Drawable::IsSkinAnimationUnknown() const
		{
			DrawableData* data = GetDrawableData(*this);
			if (!data)
			{
				return false;
			}
			DrawableImpl* impl = data->drawable;
			if (!impl)
			{
				return false;
			}
			unsigned int count = impl->parts.Size();
			for (unsigned int i = 0; i < count; i++)
			{
				PartRef part(impl, i);
				pure3d::PrimitiveState* state = part->state;
				if (state)
				{
					pure3d::SkinState* skin = dynamic_cast<pure3d::SkinState*>(state);
					if (skin)
					{
						pure3d::FrameController* controller = skin->GetController1();
						if (controller)
						{
							return controller->Unknown20();
						}
					}
				}
			}
			return true;
		}

		// Loads a texture from memory the event owns (freed here)
		// FUNCTION: ENGINE 0x107EAC90
		static void DoLoadTexture(unsigned char* data, unsigned int size, pure3d::Texture* texture, unsigned int a,
			unsigned int b)
		{
			content::MemoryStream* stream = new content::MemoryStream(data, size);
			stream->AddRef();
			pure3d::DDSParser loader(texture, a, b);
			int usage = texture->info->description.usage;
			const char* name = texture->mName.GetText() ? texture->mName.GetText() : core::GetDefaultString();
			loader.Load(stream, name, usage, gTextureLoadFlag, 0);
			stream->Release();
			texture->Release();
			delete[] data;
		}

		// Makes the render object as an instance of the source drawable's
		// FUNCTION: ENGINE 0x107EBDA0
		// EQUIVALENT: the original expands CreateOptions(bool) in place (the colour from the white constant); ours calls it
		static void DoCreateInstance(Drawable drawable, int heap, bool flag)
		{
			core::HeapScope scope(heap);
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->created = true;
				DrawableImpl* source = data->sourceDrawable->drawable;
				DrawableImpl::CreateOptions options(flag);
				pure3d::RefCounted::Assign(data->drawable, source->CreateInstance(options));
				if (data->registerOnCreate)
				{
					data->registered = true;
					GetRenderList()->Add(data->drawable, 0);
				}
				else
				{
					data->registered = false;
				}
			}
		}

		// FUNCTION: ENGINE 0x107EBED0
		// EQUIVALENT: the original ends both failed lookups in one shared block; ours repeats it
		static void DoCreateInstanceWithOptions(Drawable drawable, int heap, Drawable::InstanceOptions options)
		{
			core::HeapScope scope(heap);
			DrawableData* data = GetDrawableData(drawable);
			// One variable holds the handle and then its render object
			DrawableImpl* instanceOf = 0;
			if (options.b4)
			{
				*(unsigned int*)&instanceOf = options.instanceOf;
				DrawableData* otherData = GetDrawableData(*(Drawable*)&instanceOf);
				if (!otherData)
				{
					FreeDrawable(drawable, DESTROY_MODE_DEFERRED);
					return;
				}
				instanceOf = otherData->drawable;
			}
			if (data)
			{
				bool limitParts = options.b3;
				data->created = true;
				DrawableImpl* source = data->sourceDrawable->drawable;
				if (limitParts &&
					(unsigned int)source->parts.Size() > pure3d::GetParticleManager()->GetMaxParts())
				{
					FreeDrawable(drawable, DESTROY_MODE_DEFERRED);
					return;
				}
				if (options.shareSource)
				{
					data->sourceDrawable->flags24 |= 8;
					if (source->GetSkeleton() && options.b1)
					{
						source->SetPose(source->GetSkeleton()->CreatePose(3));
					}
					pure3d::RefCounted::Assign(data->drawable, source);
				}
				else
				{
					DrawableImpl::CreateOptions createOptions;
					createOptions.b1 = options.b1;
					createOptions.b0 = options.b0;
					createOptions.b2 = options.b2;
					createOptions.b5 = options.b5;
					createOptions.b4 = options.b4;
					createOptions.instanceOf = instanceOf;
					createOptions.colour = options.colour;
					createOptions.unknown1C = options.unknown1C;
					createOptions.unknown20 = options.unknown20;
					createOptions.b3 = limitParts;
					createOptions.unknown24 = options.unknown24;
					pure3d::RefCounted::Assign(data->drawable, source->CreateInstance(createOptions));
				}
				if (data->registerOnCreate)
				{
					data->registered = true;
					GetRenderList()->Add(data->drawable, 0);
				}
				else
				{
					data->registered = false;
				}
			}
		}

		// Makes the render object as an instance of another drawable's
		// FUNCTION: ENGINE 0x107EC0C0
		static void DoCreateInstanceOf(Drawable drawable, Drawable other, int heap)
		{
			core::HeapScope scope(heap);
			DrawableData* data = GetDrawableData(drawable);
			DrawableData* otherData = GetDrawableData(other);
			if (data && otherData)
			{
				data->created = true;
				DrawableImpl::CreateOptions options;
				options.b2 = true;
				options.b0 = true;
				pure3d::RefCounted::Assign(data->drawable, otherData->drawable->CreateInstance(options));
				if (data->registerOnCreate)
				{
					data->registered = true;
					GetRenderList()->Add(data->drawable, 0);
				}
				else
				{
					data->registered = false;
				}
			}
		}

		// FUNCTION: ENGINE 0x107EC170
		static void DoSetUnknownBC(Drawable drawable, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->SetUnknownBC(value);
				GetRenderList()->Refresh(data->drawable);
			}
		}

		// FUNCTION: ENGINE 0x107EC1B0
		static void DoSetPartAnimations(Drawable drawable, int a, bool b)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef ref(impl, i);
					DrawablePart* part = ref.Get();
					PartAnimationState state;
					pure3d::visibility::Client* animation = &part->client;
					if (animation->index != -1 || animation->server != 0)
					{
						animation->GetState(&state);
						state.unknown28.Set(a, b);
						animation->SetState(&state);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107EC280
		// EQUIVALENT: same instructions; the registers of the part temporaries are rotated against the original
		static void DoSetBiasUnknown(Drawable drawable, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef part(impl, i);
					int type = part->primitive->type;
					if (type == 0x10)
					{
						PartRef statePart(impl, i);
						pure3d::ParticleSystemState* state = (pure3d::ParticleSystemState*)statePart->state;
						state->SetBias(pure3d::gParticleKey1127F20C, 2, &value);
						state->SetBias(pure3d::gParticleKey1127F2DC, 2, &value);
						state->SetBias(pure3d::gParticleKey1127F2BC, 2, &value);
					}
					else if (type == 8)
					{
						PartRef statePart(impl, i);
						pure3d::GpuSkinState* state = (pure3d::GpuSkinState*)statePart->state;
						if (state)
						{
							state->Unknown10B87050(value);
						}
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107EC3A0
		static void DoSetEffectBiases(Drawable drawable, EffectBiases biases)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef part(impl, i);
					if (part->primitive->type == 0x10)
					{
						PartRef statePart(impl, i);
						pure3d::ParticleSystemState* state = (pure3d::ParticleSystemState*)statePart->state;
						state->SetBias(pure3d::gParticleKey1127F214, 2, &biases.values[0]);
						state->SetBias(pure3d::gParticleKey1127F2DC, 2, &biases.values[1]);
						state->SetBias(pure3d::gParticleKey1127F338, 2, &biases.values[2]);
						state->SetBias(pure3d::gParticleKey1127F158, 2, &biases.values[3]);
						state->SetBias(pure3d::gParticleKey1127F15C, 2, &biases.values[4]);
						state->SetBias(pure3d::gParticleKey1127F20C, 2, &biases.values[5]);
						state->SetBias(pure3d::gParticleKey1127F188, 2, &biases.values[6]);
						state->SetBias(pure3d::gParticleKey1127F2BC, 2, &biases.values[7]);
						state->SetBias(pure3d::gParticleKey1127F208, 2, &biases.values[8]);
						state->SetBias(pure3d::gParticleKey1127F2AC, 2, &biases.values[9]);
						state->SetBias(pure3d::gParticleKey1127F330, 2, &biases.values[10]);
						state->SetBias(pure3d::gParticleKey1127F0B8, 2, &biases.values[11]);
						state->SetBias(pure3d::gParticleKey1127F284, 2, &biases.values[12]);
						state->SetBias(pure3d::gParticleKey1127F1CC, 2, &biases.values[13]);
						state->SetBias(pure3d::gParticleKey1127F144, 2, &biases.values[14]);
						state->SetBias(pure3d::gParticleKey1127F164, 2, &biases.values[15]);
						state->SetBias(pure3d::gParticleKey1127F314, 2, &biases.values[16]);
						state->SetBias(pure3d::gParticleKey1127F138, 2, &biases.values[17]);
						state->SetBias(pure3d::gParticleKey1127F2B8, 2, &biases.values[18]);
						state->SetBias(pure3d::gParticleKey1127F320, 2, &biases.values[19]);
						state->SetBias(pure3d::gParticleKey1127F29C, 2, &biases.values[20]);
						state->SetBias(pure3d::gParticleKey1127F2D8, 2, &biases.values[21]);
						state->SetBias(pure3d::gParticleKey1127F210, 2, &biases.values[22]);
						state->SetGeneratorParameter(pure3d::gParticleKey1127F204, 0, &biases.values[31]);
						state->SetGeneratorParameter2(pure3d::gParticleKey1127F15C, 2, &biases.values[23]);
						state->SetGeneratorParameter2(pure3d::gParticleKey1127F20C, 2, &biases.values[24]);
						state->SetGeneratorParameter2(pure3d::gParticleKey1127F2DC, 2, &biases.values[25]);
						state->SetGeneratorParameter2(pure3d::gParticleKey1127F188, 2, &biases.values[26]);
						state->SetGeneratorParameter2(pure3d::gParticleKey1127F2BC, 2, &biases.values[27]);
						state->SetGeneratorParameter2(pure3d::gParticleKey1127F208, 2, &biases.values[28]);
						state->SetGeneratorParameter2(pure3d::gParticleKey1127F218, 2, &biases.values[29]);
						state->SetGeneratorParameter2(pure3d::gParticleKey1127F144, 2, &biases.values[30]);
					}
				}
			}
		}

		// FUNCTION: ENGINE 0x107EC710
		static void DoSetParticleBias(Drawable drawable, core::Name<core::CaseInsensitiveKey32> name, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					PartRef part(impl, i);
					if (part->primitive->type == 0x10)
					{
						PartRef statePart(impl, i);
						((pure3d::ParticleSystemState*)statePart->state)->SetBias(name, 2, &value);
					}
				}
			}
		}

		// The event classes the drawable methods queue; the render thread calls the stored function with the
		// stored arguments (an instantiation per argument list)
		// FUNCTION: ENGINE 0x107EAF80
		// FUNCTION: ENGINE 0x107EAFB0
		template class RenderEvent3<Drawable, int, bool>;
		// FUNCTION: ENGINE 0x107EAFD0
		// FUNCTION: ENGINE 0x107EB010
		template class RenderEvent3<Drawable, int, Drawable::InstanceOptions>;
		// FUNCTION: ENGINE 0x107EB040
		// FUNCTION: ENGINE 0x107EB070
		template class RenderEvent3<Drawable, int, DrawableCreator*>;
		// FUNCTION: ENGINE 0x107EB090
		// FUNCTION: ENGINE 0x107EB0C0
		template class RenderEvent3<Drawable, Drawable, int>;
		// FUNCTION: ENGINE 0x107EB0E0
		// FUNCTION: ENGINE 0x107EB100
		template class RenderEvent2<Drawable, DestroyMode>;
		// FUNCTION: ENGINE 0x107EB120
		// FUNCTION: ENGINE 0x107EB140
		template class RenderEvent2<Drawable, Drawable>;
		// FUNCTION: ENGINE 0x107EB160
		// FUNCTION: ENGINE 0x107EB180
		template class RenderEvent2<Drawable, DrawableModifier*>;
		// FUNCTION: ENGINE 0x107EB1A0
		// FUNCTION: ENGINE 0x107EB1C0
		template class RenderEvent2<Drawable, bool>;
		// FUNCTION: ENGINE 0x107EB1E0
		// FUNCTION: ENGINE 0x107EB200
		template class RenderEvent1<Drawable>;
		// FUNCTION: ENGINE 0x107EB220
		// FUNCTION: ENGINE 0x107EB250
		template class RenderEvent3<Drawable, unsigned __int64, bool>;
		// FUNCTION: ENGINE 0x107EB280
		// FUNCTION: ENGINE 0x107EB2B0
		template class RenderEvent3<Drawable, engine::DrawableSegmentVisibility*, unsigned int>;
		// FUNCTION: ENGINE 0x107EB2D0
		// FUNCTION: ENGINE 0x107EB320
		template class RenderEvent6<Drawable, float, float, float, pure3d::Animation::CycleMode, unsigned int>;
		// FUNCTION: ENGINE 0x107EB360
		// FUNCTION: ENGINE 0x107EB390
		template class RenderEvent2<Drawable, unsigned __int64>;
		// FUNCTION: ENGINE 0x107EB3B0
		// FUNCTION: ENGINE 0x107EB3D0
		template class RenderEvent2<Drawable, unsigned int>;
		// FUNCTION: ENGINE 0x107EB3F0
		// FUNCTION: ENGINE 0x107EB4C0
		// EQUIVALENT: the original copies the matrix argument with the compiler's vector copy-constructor helper (four rows); ours copies the sixteen floats inline
		template class RenderEvent2<Drawable, math::Matrix>;
		// FUNCTION: ENGINE 0x107EB4F0
		// FUNCTION: ENGINE 0x107EB510
		template class RenderEvent2<Drawable, pure3d::Pose*>;
		// FUNCTION: ENGINE 0x107EB530
		// FUNCTION: ENGINE 0x107ED4E0
		template class RenderEvent3<Drawable, pure3d::pddiShaderInputInitData, int>;
		// FUNCTION: ENGINE 0x107EB580
		// FUNCTION: ENGINE 0x107EB5D0
		template class RenderEvent3<Drawable, core::CaseInsensitiveKey32, math::Vector4>;
		// FUNCTION: ENGINE 0x107EB610
		// FUNCTION: ENGINE 0x107EB660
		template class RenderEvent3<Drawable, core::CaseInsensitiveKey32, math::Vector>;
		// FUNCTION: ENGINE 0x107EB6A0
		// FUNCTION: ENGINE 0x107EB6E0
		template class RenderEvent3<Drawable, core::CaseInsensitiveKey32, math::Vector2>;
		// FUNCTION: ENGINE 0x107EB710
		// FUNCTION: ENGINE 0x107EB740
		template class RenderEvent3<Drawable, core::CaseInsensitiveKey32, float>;
		// FUNCTION: ENGINE 0x107EB770
		// FUNCTION: ENGINE 0x107EB7A0
		template class RenderEvent3<Drawable, core::CaseInsensitiveKey32, bool>;
		// FUNCTION: ENGINE 0x107EB7C0
		// FUNCTION: ENGINE 0x107EB7F0
		template class RenderEvent4<Drawable, pure3d::Shader*, bool, int>;
		// FUNCTION: ENGINE 0x107EB820
		// FUNCTION: ENGINE 0x107EB880
		template class RenderEvent7<Drawable, pure3d::Animation*, float, float, float, float,
			pure3d::Animation::CycleMode>;
		// FUNCTION: ENGINE 0x107EB8C0
		// FUNCTION: ENGINE 0x107EB8E0
		template class RenderEvent2<Drawable, pure3d::ExpressionPose*>;
		// FUNCTION: ENGINE 0x107EB900
		// FUNCTION: ENGINE 0x107EB960
		template class RenderEvent8<Drawable, pure3d::Animation*, float, float, float, float,
			pure3d::Animation::CycleMode, int>;
		// FUNCTION: ENGINE 0x107EB9B0
		// FUNCTION: ENGINE 0x107EB9D0
		template class RenderEvent2<Drawable, pure3d::VertexDeformRegion*>;
		// FUNCTION: ENGINE 0x107EB9F0
		// FUNCTION: ENGINE 0x107EBA20
		template class RenderEvent2<Drawable, float>;
		// FUNCTION: ENGINE 0x107EBA40
		// FUNCTION: ENGINE 0x107ED520
		template class RenderEvent3<Drawable, core::Name<core::CaseSensitiveKey>, float>;
		// FUNCTION: ENGINE 0x107EBA90
		// FUNCTION: ENGINE 0x107EBAC0
		template class RenderEvent2<Drawable, EffectBiases>;
		// FUNCTION: ENGINE 0x107EBAF0
		// FUNCTION: ENGINE 0x107EBB20
		template class RenderEvent2<Drawable, EffectOverrides>;
		// FUNCTION: ENGINE 0x107EBB50
		// FUNCTION: ENGINE 0x107ED550
		template class RenderEvent3<Drawable, core::Name<core::CaseInsensitiveKey32>, float>;
		// FUNCTION: ENGINE 0x107EBBA0
		// FUNCTION: ENGINE 0x107ED580
		template class RenderEvent3<Drawable, core::Name<core::CaseInsensitiveKey32>, math::Vector>;
		// FUNCTION: ENGINE 0x107EBC00
		// FUNCTION: ENGINE 0x107ED5C0
		template class RenderEvent2<Drawable, core::Name<core::CaseSensitiveKey> >;
		// FUNCTION: ENGINE 0x107EBC40
		// FUNCTION: ENGINE 0x107EBC60
		template class RenderEvent1<unsigned int>;
		// FUNCTION: ENGINE 0x107EBC80
		// FUNCTION: ENGINE 0x107EBCC0
		template class RenderEvent5<unsigned char*, unsigned int, pure3d::Texture*, unsigned int, unsigned int>;

		// The heap a render object is made in: the current one, or the game object heap when the allocator of the
		// current heap says so
		static inline int GetRenderObjectHeap()
		{
			int heap = core::GetCurrentHeap();
			int unknown;
			if (core::GetHeapAllocator(heap)->GetStat(0xb, &unknown))
			{
				heap = engine::GetGameObjectHeap();
			}
			return heap;
		}

		// FUNCTION: ENGINE 0x107ED5F0
		Drawable Drawable::CreateInstance(SourceDrawable* source, bool registerOnCreate, bool flag)
		{
			Drawable drawable = AllocateDrawable(source, registerOnCreate);
			int heap = GetRenderObjectHeap();
			QueueRenderEvent(DoCreateInstance, drawable, heap, flag);
			return drawable;
		}

		// FUNCTION: ENGINE 0x107ED650
		Drawable Drawable::CreateInstance(SourceDrawable* source, const InstanceOptions& options,
			bool registerOnCreate)
		{
			int heap = GetRenderObjectHeap();
			Drawable drawable = AllocateDrawable(source, registerOnCreate);
			QueueRenderEvent(DoCreateInstanceWithOptions, drawable, heap, options);
			return drawable;
		}

		// FUNCTION: ENGINE 0x107ED6C0
		Drawable Drawable::Create(DrawableCreator* creator, bool registerOnCreate)
		{
			Drawable drawable = AllocateDrawable(0, registerOnCreate);
			QueueRenderEvent(DoCreate, drawable, core::GetCurrentHeap(), creator);
			return drawable;
		}

		// FUNCTION: ENGINE 0x107ED700
		Drawable Drawable::CreateInstanceOf(Drawable other)
		{
			Drawable drawable;
			DrawableData* data = GetDrawableData(other);
			if (data)
			{
				drawable = AllocateDrawable(data->sourceDrawable, true);
				QueueRenderEvent(DoCreateInstanceOf, drawable, other, core::GetCurrentHeap());
			}
			return drawable;
		}

		// FUNCTION: ENGINE 0x107ED750
		void Drawable::Destroy(Drawable* drawable)
		{
			QueueRenderEvent(DoDestroy, *drawable, DESTROY_MODE_DEFERRED);
			drawable->mHandle = 0xffffffff;
		}

		// FUNCTION: ENGINE 0x107ED770
		Drawable Drawable::Clone() const
		{
			DrawableData* data = GetDrawableData(*this);
			if (data)
			{
				Drawable drawable = CreateInstance(data->sourceDrawable, true, false);
				QueueRenderEvent(DoUnknown106E09A0, drawable, *this);
				return drawable;
			}
			return Drawable();
		}

		// FUNCTION: ENGINE 0x107ED7D0
		void Drawable::ApplyModifier(DrawableModifier* modifier) const
		{
			QueueRenderEvent(DoApplyModifier, *this, modifier);
		}

		// FUNCTION: ENGINE 0x107ED7F0
		void Drawable::ApplyModifierAgain(DrawableModifier* modifier) const
		{
			QueueRenderEventSecondary(DoApplyModifier, *this, modifier);
		}

		// FUNCTION: ENGINE 0x107ED810
		void Drawable::SetRegistered(bool registered) const
		{
			QueueRenderEvent(DoSetRegistered, *this, registered);
		}

		// FUNCTION: ENGINE 0x107ED830
		void Drawable::Method106E02C0() const
		{
			QueueRenderEvent(DoUnknown106E02C0, *this);
		}

		// FUNCTION: ENGINE 0x107ED850
		void Drawable::SetFlag10() const
		{
			QueueRenderEvent(DoSetFlag10, *this);
		}

		// FUNCTION: ENGINE 0x107ED870
		void Drawable::ClearFlag10() const
		{
			QueueRenderEvent(DoClearFlag10, *this);
		}

		// FUNCTION: ENGINE 0x107ED890
		void Drawable::SetSegmentVisible(const core::Name<core::CaseSensitiveKey>& segment, bool visible) const
		{
			QueueRenderEvent(DoSetSegmentVisible, *this, segment.GetHash(), visible);
		}

		// FUNCTION: ENGINE 0x107ED8C0
		void Drawable::SetSegmentVisibilities(const DrawableSegmentVisibility* visibilities,
			unsigned int count) const
		{
			unsigned int size = count << 4;
			void* copy = AllocRenderEvent(size);
			core::MemCopyUnchecked(copy, visibilities, size);
			QueueRenderEvent(DoSetSegmentVisibility, *this, (DrawableSegmentVisibility*)copy, count);
		}

		// FUNCTION: ENGINE 0x107ED900
		void Drawable::SetPartsUnknown(bool value) const
		{
			QueueRenderEvent(DoSetPartsUnknown, *this, value);
		}

		// FUNCTION: ENGINE 0x107ED920
		void Drawable::Play(float start, float end, float speed, pure3d::Animation::CycleMode mode,
			unsigned int cycles) const
		{
			QueueRenderEvent(DoPlay, *this, start, end, speed, mode, cycles);
		}

		// FUNCTION: ENGINE 0x107ED960
		void Drawable::SetName(const core::Name<core::CaseSensitiveKey>& name) const
		{
			QueueRenderEvent(DoSetName, *this, name.GetHash());
		}

		// FUNCTION: ENGINE 0x107ED990
		void Drawable::SetUnknownCC(unsigned int value) const
		{
			QueueRenderEvent(DoSetUnknownCC, *this, value);
		}

		// FUNCTION: ENGINE 0x107ED9B0
		// EQUIVALENT: as RenderEvent2<Drawable, Matrix>::Execute: the argument copy is the vector copy-constructor helper in the original
		void Drawable::SetTransformQueued(const math::Matrix& transform) const
		{
			QueueRenderEvent(DoSetTransform, *this, transform);
		}

		// FUNCTION: ENGINE 0x107ED9E0
		void Drawable::FindBindingSource(Drawable other) const
		{
			QueueRenderEvent(DoFindBindingSource, *this, other, core::GetCurrentHeap());
		}

		// FUNCTION: ENGINE 0x107EDA10
		void Drawable::ShareBindings(Drawable other) const
		{
			QueueRenderEvent(DoShareBindings, *this, other, core::GetCurrentHeap());
		}

		// FUNCTION: ENGINE 0x107EDA40
		void Drawable::SharePose(Drawable other) const
		{
			QueueRenderEvent(DoSharePose, *this, other);
		}

		// FUNCTION: ENGINE 0x107EDA60
		void Drawable::CopyPoseState(Drawable other) const
		{
			QueueRenderEvent(DoCopyPoseState, *this, other);
		}

		// FUNCTION: ENGINE 0x107EDA80
		void Drawable::SetPose(pure3d::Pose* pose) const
		{
			pose->AddRef();
			QueueRenderEvent(DoSetPose, *this, pose);
		}

		// FUNCTION: ENGINE 0x107EDAB0
		void Drawable::CreateBindings(const pure3d::pddiShaderInputInitData& init) const
		{
			int heap = GetRenderObjectHeap();
			QueueRenderEvent(DoCreateBindings, *this, init, heap);
		}

		// FUNCTION: ENGINE 0x107EDB10
		void Drawable::SetBindingVector4(const core::Name<core::CaseInsensitiveKey32>& name, float x, float y,
			float z, float w) const
		{
			QueueRenderEventSecondary(DoSetBindingVector4, *this, name.GetKey(), math::Vector4(x, y, z, w));
		}

		// FUNCTION: ENGINE 0x107EDB70
		void Drawable::SetBindingVector(const core::Name<core::CaseInsensitiveKey32>& name, float x, float y,
			float z) const
		{
			QueueRenderEventSecondary(DoSetBindingVector, *this, name.GetKey(), math::Vector(x, y, z));
		}

		// FUNCTION: ENGINE 0x107EDBC0
		void Drawable::SetBindingVector2(const core::Name<core::CaseInsensitiveKey32>& name, float x, float y) const
		{
			QueueRenderEventSecondary(DoSetBindingVector2, *this, name.GetKey(), math::Vector2(x, y));
		}

		// FUNCTION: ENGINE 0x107EDC00
		void Drawable::SetBindingFloat(const core::Name<core::CaseInsensitiveKey32>& name, float value) const
		{
			QueueRenderEventSecondary(DoSetBindingFloat, *this, name.GetKey(), value);
		}

		// FUNCTION: ENGINE 0x107EDC30
		void Drawable::SetBindingBool(const core::Name<core::CaseInsensitiveKey32>& name, bool value) const
		{
			QueueRenderEventSecondary(DoSetBindingBool, *this, name.GetKey(), value);
		}

		// FUNCTION: ENGINE 0x107EDC60
		void Drawable::SetShader(pure3d::Shader* shader, bool enable) const
		{
			QueueRenderEvent(DoSetShader, *this, shader, enable, core::GetCurrentHeap());
		}

		// FUNCTION: ENGINE 0x107EDC90
		void Drawable::ResetStates() const
		{
			QueueRenderEvent(DoResetStates, *this);
		}

		// FUNCTION: ENGINE 0x107EDCB0
		void Drawable::PlayAnimation(pure3d::Animation* animation, float speed, float frame, float start,
			float end, pure3d::Animation::CycleMode mode) const
		{
			QueueRenderEvent(DoPlayAnimation, *this, animation, speed, frame, start, end, mode);
		}

		// FUNCTION: ENGINE 0x107EDCF0
		void Drawable::StopAnimation() const
		{
			DrawableData* data = GetDrawableData(*this);
			if (data)
			{
				data->unknown8 = true;
			}
			QueueRenderEvent(DoClearUnknown78, *this);
		}

		// FUNCTION: ENGINE 0x107EDD20
		void Drawable::ApplyExpressionPose(pure3d::ExpressionPose* pose) const
		{
			if (pose)
			{
				pose->AddRef();
				QueueRenderEvent(DoApplyExpressionPose, *this, pose);
			}
		}

		// FUNCTION: ENGINE 0x107EDD50
		void Drawable::PlaySkinAnimation(pure3d::Animation* animation, float speed, float frame, float start,
			float end, pure3d::Animation::CycleMode mode) const
		{
			QueueRenderEvent(DoPlaySkinAnimation, *this, animation, speed, frame, start, end, mode);
		}

		// FUNCTION: ENGINE 0x107EDD90
		void Drawable::PlayPartAnimation(pure3d::Animation* animation, float speed, float frame, float start,
			float end, pure3d::Animation::CycleMode mode) const
		{
			QueueRenderEvent(DoPlayPartAnimation, *this, animation, speed, frame, start, end, mode,
				core::GetCurrentHeap());
		}

		// FUNCTION: ENGINE 0x107EDDE0
		void Drawable::Method106E0490() const
		{
			QueueRenderEvent(DoUnknown106E0490, *this);
		}

		// FUNCTION: ENGINE 0x107EDE00
		void Drawable::Method106E03E0() const
		{
			QueueRenderEvent(DoUnknown106E03E0, *this);
		}

		// FUNCTION: ENGINE 0x107EDE20
		void Drawable::SetVertexDeformRegion(pure3d::VertexDeformRegion* region) const
		{
			if (region)
			{
				region->AddRef();
			}
			QueueRenderEvent(DoSetVertexDeformRegion, *this, region);
		}

		// FUNCTION: ENGINE 0x107EDE50
		void Drawable::SetUnknownBC(float value) const
		{
			QueueRenderEvent(DoSetUnknownBC, *this, value);
		}

		// FUNCTION: ENGINE 0x107EDE70
		void Drawable::SetPartsUnknown2C(float value) const
		{
			QueueRenderEvent(DoSetPartsUnknown2C, *this, value);
		}

		// FUNCTION: ENGINE 0x107EDE90
		void Drawable::SetSegmentUnknown2C(const core::Name<core::CaseSensitiveKey>& segment, float value) const
		{
			QueueRenderEvent(DoSetSegmentUnknown2C, *this, segment, value);
		}

		// FUNCTION: ENGINE 0x107EDEC0
		void Drawable::SetFlag101Bit1(bool value) const
		{
			QueueRenderEvent(DoSetFlag101Bit1, *this, value);
		}

		// FUNCTION: ENGINE 0x107EDEE0
		void Drawable::SetPartAnimations(int a, bool b) const
		{
			QueueRenderEvent(DoSetPartAnimations, *this, a, b);
		}

		// FUNCTION: ENGINE 0x107EDF00
		void Drawable::ResetParticles() const
		{
			QueueRenderEvent(DoResetParticles, *this);
		}

		// FUNCTION: ENGINE 0x107EDF20
		void Drawable::SetBiasUnknown(float value) const
		{
			QueueRenderEvent(DoSetBiasUnknown, *this, value);
		}

		// FUNCTION: ENGINE 0x107EDF40
		void Drawable::SetEffectBiases(EffectBiases biases) const
		{
			QueueRenderEvent(DoSetEffectBiases, *this, biases);
		}

		// FUNCTION: ENGINE 0x107EDF70
		void Drawable::SetEffectOverrides(EffectOverrides overrides) const
		{
			QueueRenderEvent(DoSetEffectOverrides, *this, overrides);
		}

		// FUNCTION: ENGINE 0x107EDFA0
		void Drawable::SetParticleBias(core::Name<core::CaseInsensitiveKey32> name, float value) const
		{
			QueueRenderEvent(DoSetParticleBias, *this, name, value);
		}

		// FUNCTION: ENGINE 0x107EDFD0
		void Drawable::SetGeneratorVector(core::Name<core::CaseInsensitiveKey32> name, float x, float y,
			float z) const
		{
			QueueRenderEvent(DoSetGeneratorVector, *this, name, math::Vector(x, y, z));
		}

		// FUNCTION: ENGINE 0x107EE020
		void Drawable::SetGeneratorFloat2(core::Name<core::CaseInsensitiveKey32> name, float value) const
		{
			QueueRenderEvent(DoSetGeneratorFloat2, *this, name, value);
		}

		// FUNCTION: ENGINE 0x107EE050
		void Drawable::SetParticleFloat(core::Name<core::CaseInsensitiveKey32> name, float value) const
		{
			QueueRenderEvent(DoSetParticleFloat, *this, name, value);
		}

		// FUNCTION: ENGINE 0x107EE080
		void Drawable::SetGeneratorFloat3(core::Name<core::CaseInsensitiveKey32> name, float value) const
		{
			QueueRenderEvent(DoSetGeneratorFloat3, *this, name, value);
		}

		// FUNCTION: ENGINE 0x107EE0B0
		void Drawable::SetParticleUnknownE70(float value) const
		{
			QueueRenderEvent(DoSetParticleUnknownE70, *this, value);
		}

		// FUNCTION: ENGINE 0x107EE0D0
		void Drawable::SetParticleUnknownE50(float value) const
		{
			QueueRenderEvent(DoSetParticleUnknownE50, *this, value);
		}

		// FUNCTION: ENGINE 0x107EE0F0
		void Drawable::SetParticleUnknownE40(bool value) const
		{
			QueueRenderEvent(DoSetParticleUnknownE40, *this, value);
		}

		// FUNCTION: ENGINE 0x107EE110
		void Drawable::SetParticleUnknownCC0(bool value) const
		{
			QueueRenderEvent(DoSetParticleUnknownCC0, *this, value);
		}

		// FUNCTION: ENGINE 0x107EE130
		void Drawable::SetParticleUnknown49C(float value) const
		{
			QueueRenderEvent(DoSetParticleUnknown49C, *this, value);
		}

		// FUNCTION: ENGINE 0x107EE150
		void Drawable::SetParticleUnknown4A8(float value) const
		{
			QueueRenderEvent(DoSetParticleUnknown4A8, *this, value);
		}

		// FUNCTION: ENGINE 0x107EE170
		void Drawable::SetParticleUnknown4B8(bool value) const
		{
			QueueRenderEvent(DoSetParticleUnknown4B8, *this, value);
		}

		// FUNCTION: ENGINE 0x107EE190
		void Drawable::SetParticleFade(float value) const
		{
			QueueRenderEvent(DoSetParticleFade, *this, value);
		}

		// FUNCTION: ENGINE 0x107EE1B0
		void Drawable::ParticleUnknownCD0() const
		{
			QueueRenderEvent(DoParticleUnknownCD0, *this);
		}

		// FUNCTION: ENGINE 0x107EE1D0
		void Drawable::Method106E1250(const core::Name<core::CaseSensitiveKey>& name) const
		{
			QueueRenderEvent(DoUnknown106E1250, *this, name);
		}

		// FUNCTION: ENGINE 0x107EE230
		// EQUIVALENT: the order of the lookup's pushes: the original loads the inventory and its vftable entry first
		void Drawable::LoadTexture(const char* name, int unknown, unsigned int a, unsigned int b)
		{
			content::LoadInventory::DynamicCaster<pure3d::Texture> caster;
			pure3d::Texture* texture = (pure3d::Texture*)content::gRootInventory->FindObject(&caster,
				core::Name<core::CaseSensitiveKey>(name, 1), true);
			if (texture)
			{
				core::IFile* file;
				core::FileSystemOpenFileAsync(&file, name, false, 0, 1, 0, 1, 1, 0);
				if (file)
				{
					texture->AddRef();
					file->Wait();
					unsigned char* buffer = new (1) unsigned char[file->GetCurrentSize()];
					file->Read(buffer, file->GetCurrentSize(), 1);
					file->Wait();
					QueueRenderEvent(DoLoadTexture, buffer, file->GetCurrentSize(), texture, a, b);
					file->Release();
				}
			}
		}

		// FUNCTION: ENGINE 0x107EE200
		int Drawable::QueueDeferredDeletion()
		{
			QueueRenderEvent(DeferredDeletionProxy::Defer, gDeferredFrame);
			return gDeferredFrame++;
		}
	}
}

namespace pure3d
{
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F2B8 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("alphaOverLife", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F254 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourBias", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F138 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("diffuseOverLifeBlue", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F314 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("diffuseOverLifeGreen", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F164 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("diffuseOverLifeRed", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F214 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("emissionRate", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F2D8 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("generatorHorizSpread", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F29C = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("generatorRadial", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F320 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("generatorRadius", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F210 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("generatorVertSpread", 0)));
	core::Name<core::CaseInsensitiveKey32> gParticleKey1127F204 = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("meshGeneratorScale", 0)));
}

namespace engine
{
	namespace render
	{
		core::Name<core::CaseInsensitiveKey32> gAlphaVariance = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("alphaVariance", 0)));
		core::Name<core::CaseInsensitiveKey32> gAngleVar = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("angleVar", 0)));
		core::Name<core::CaseInsensitiveKey32> gAnimDrag = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("animDrag", 0)));
		core::Name<core::CaseInsensitiveKey32> gCameraPosition = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("cameraPosition", 0)));
		core::Name<core::CaseInsensitiveKey32> gCohesionMatrix = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("cohesionMatrix", 0)));
		core::Name<core::CaseInsensitiveKey32> gColourVariance = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourVariance", 0)));
		core::Name<core::CaseInsensitiveKey32> gColourVarianceMask = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("colourVarianceMask", 0)));
		core::Name<core::CaseInsensitiveKey32> gConstantSpin3D = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("constantSpin3D", 0)));
		core::Name<core::CaseInsensitiveKey32> gCurl = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("curl", 0)));
		core::Name<core::CaseInsensitiveKey32> gCutoff = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("cutoff", 0)));
		core::Name<core::CaseInsensitiveKey32> gDiffuseVariance = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("diffuseVariance", 0)));
		core::Name<core::CaseInsensitiveKey32> gGeneratorPosition = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("generatorPosition", 0)));
		core::Name<core::CaseInsensitiveKey32> gGeneratorTransform = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("generatorTransform", 0)));
		core::Name<core::CaseInsensitiveKey32> gHeightScale = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("heightScale", 0)));
		core::Name<core::CaseInsensitiveKey32> gHorizGridSpacing = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("horizGridSpacing", 0)));
		core::Name<core::CaseInsensitiveKey32> gInitDrag = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("initDrag", 0)));
		core::Name<core::CaseInsensitiveKey32> gInitSize3D = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("initSize3D", 0)));
		core::Name<core::CaseInsensitiveKey32> gInheritedVelocity = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("inheritedVelocity", 0)));
		core::Name<core::CaseInsensitiveKey32> gInheritedVelocityScale = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("inheritedVelocityScale", 0)));
		core::Name<core::CaseInsensitiveKey32> gLastPosition = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("lastPosition", 0)));
		core::Name<core::CaseInsensitiveKey32> gLastTexChange = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("lastTexChange", 0)));
		core::Name<core::CaseInsensitiveKey32> gLife = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("life", 0)));
		core::Name<core::CaseInsensitiveKey32> gLockAxis = core::PassName32(core::PassName32(core::Name<core::CaseInsensitiveKey32>("lockAxis", 0)));
	}
}

// The dynamic initialisers and atexit stubs of the unit's names:
// FUNCTION: ENGINE 0x10D68540
// FUNCTION: ENGINE 0x10D68580
// FUNCTION: ENGINE 0x10D68600
// FUNCTION: ENGINE 0x10D68640
// FUNCTION: ENGINE 0x10D68680
// FUNCTION: ENGINE 0x10D686C0
// FUNCTION: ENGINE 0x10D68700
// FUNCTION: ENGINE 0x10D68740
// FUNCTION: ENGINE 0x10D68780
// FUNCTION: ENGINE 0x10D687C0
// FUNCTION: ENGINE 0x10D68800
// FUNCTION: ENGINE 0x10D68840
// FUNCTION: ENGINE 0x10D68980
// FUNCTION: ENGINE 0x10D689C0
// FUNCTION: ENGINE 0x10D68A00
// FUNCTION: ENGINE 0x10D68A40
// FUNCTION: ENGINE 0x10D68AC0
// FUNCTION: ENGINE 0x10D68B80
// FUNCTION: ENGINE 0x10D68BC0
// FUNCTION: ENGINE 0x10D68C00
// FUNCTION: ENGINE 0x10D68C40
// FUNCTION: ENGINE 0x10D68C80
// FUNCTION: ENGINE 0x10D68CC0
// FUNCTION: ENGINE 0x10D68D80
// FUNCTION: ENGINE 0x10D68DC0
// FUNCTION: ENGINE 0x10D68E00
// FUNCTION: ENGINE 0x10D68E80
// FUNCTION: ENGINE 0x10D68EC0
// FUNCTION: ENGINE 0x10D68F00
// FUNCTION: ENGINE 0x10D68F80
// FUNCTION: ENGINE 0x10D68FC0
// FUNCTION: ENGINE 0x10D69000
// FUNCTION: ENGINE 0x10D69080
// FUNCTION: ENGINE 0x10D690C0
// FUNCTION: ENGINE 0x10D86FD0
// FUNCTION: ENGINE 0x10D86FE0
// FUNCTION: ENGINE 0x10D87000
// FUNCTION: ENGINE 0x10D87010
// FUNCTION: ENGINE 0x10D87020
// FUNCTION: ENGINE 0x10D87030
// FUNCTION: ENGINE 0x10D87040
// FUNCTION: ENGINE 0x10D87050
// FUNCTION: ENGINE 0x10D87060
// FUNCTION: ENGINE 0x10D87070
// FUNCTION: ENGINE 0x10D87080
// FUNCTION: ENGINE 0x10D87090
// FUNCTION: ENGINE 0x10D870E0
// FUNCTION: ENGINE 0x10D870F0
// FUNCTION: ENGINE 0x10D87100
// FUNCTION: ENGINE 0x10D87110
// FUNCTION: ENGINE 0x10D87130
// FUNCTION: ENGINE 0x10D87160
// FUNCTION: ENGINE 0x10D87170
// FUNCTION: ENGINE 0x10D87180
// FUNCTION: ENGINE 0x10D87190
// FUNCTION: ENGINE 0x10D871A0
// FUNCTION: ENGINE 0x10D871B0
// FUNCTION: ENGINE 0x10D871E0
// FUNCTION: ENGINE 0x10D871F0
// FUNCTION: ENGINE 0x10D87200
// FUNCTION: ENGINE 0x10D87220
// FUNCTION: ENGINE 0x10D87230
// FUNCTION: ENGINE 0x10D87240
// FUNCTION: ENGINE 0x10D87260
// FUNCTION: ENGINE 0x10D87270
// FUNCTION: ENGINE 0x10D87280
// FUNCTION: ENGINE 0x10D872A0
// FUNCTION: ENGINE 0x10D872B0


// Kept copies: inline members of the headers that the original left as separate code
// FUNCTION: ENGINE 0x107E85E0
// FUNCTION: ENGINE 0x107E8020
// FUNCTION: ENGINE 0x107E89F0
// FUNCTION: ENGINE 0x107E8030
// FUNCTION: ENGINE 0x107E8050
// FUNCTION: ENGINE 0x107E8060
// FUNCTION: ENGINE 0x107E8080
// FUNCTION: ENGINE 0x107E80A0
// FUNCTION: ENGINE 0x107E80C0
// FUNCTION: ENGINE 0x107E80D0
// FUNCTION: ENGINE 0x107E8AA0
// FUNCTION: ENGINE 0x107E8B10
// FUNCTION: ENGINE 0x107E8B30
// FUNCTION: ENGINE 0x107EAD50
// EQUIVALENT: the original converts the channels with the x87 truncation and merges them with xor masks; ours narrows to byte stores

// Instantiations of QueueRenderEvent that the drawable methods use
// FUNCTION: ENGINE 0x107EC7C0
// FUNCTION: ENGINE 0x107EC810
// FUNCTION: ENGINE 0x107EC880
// FUNCTION: ENGINE 0x107EC8D0
// FUNCTION: ENGINE 0x107EC920
// FUNCTION: ENGINE 0x107EC960
// FUNCTION: ENGINE 0x107EC9A0
// FUNCTION: ENGINE 0x107EC9E0
// FUNCTION: ENGINE 0x107ECA20
// FUNCTION: ENGINE 0x107ECA60
// FUNCTION: ENGINE 0x107ECAA0
// FUNCTION: ENGINE 0x107ECAF0
// FUNCTION: ENGINE 0x107ECB40
// FUNCTION: ENGINE 0x107ECBB0
// FUNCTION: ENGINE 0x107ECC00
// FUNCTION: ENGINE 0x107ECC40
// FUNCTION: ENGINE 0x107ECD30
// FUNCTION: ENGINE 0x107ECD70
// FUNCTION: ENGINE 0x107ECDE0
// FUNCTION: ENGINE 0x107ECE50
// FUNCTION: ENGINE 0x107ECEB0
// FUNCTION: ENGINE 0x107ECF10
// FUNCTION: ENGINE 0x107ECF60
// FUNCTION: ENGINE 0x107ECFB0
// FUNCTION: ENGINE 0x107ED000
// FUNCTION: ENGINE 0x107ED070
// FUNCTION: ENGINE 0x107ED0B0
// FUNCTION: ENGINE 0x107ED130
// FUNCTION: ENGINE 0x107ED170
// FUNCTION: ENGINE 0x107ED1B0
// FUNCTION: ENGINE 0x107ED220
// FUNCTION: ENGINE 0x107ED2A0
// FUNCTION: ENGINE 0x107ED2F0
// FUNCTION: ENGINE 0x107ED360
// FUNCTION: ENGINE 0x107ED3E0
// FUNCTION: ENGINE 0x107ED450
// FUNCTION: ENGINE 0x107ED490

// Destructors and scalar deleting destructors of the event classes whose members have destructors
// FUNCTION: ENGINE 0x107EB570
// FUNCTION: ENGINE 0x107EBA80
// FUNCTION: ENGINE 0x107EBB90
// FUNCTION: ENGINE 0x107EBBF0
// FUNCTION: ENGINE 0x107EBC30
// FUNCTION: ENGINE 0x107EBCF0
// FUNCTION: ENGINE 0x107EBD20
// FUNCTION: ENGINE 0x107EBD40
// FUNCTION: ENGINE 0x107EBD60
// FUNCTION: ENGINE 0x107EBD80
