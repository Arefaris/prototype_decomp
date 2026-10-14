// engine::render::Drawable (unit 0x107E8020 - 0x107EE322, assert path ..\..\..\code\engine\render\async\private\
// drawable.cpp): the game thread's drawable handle methods, the static functions their render events run on the
// render thread, and engine::render::DeferredDeletionProxy (RTTI name). Names are guesses unless noted.
#include "code/core/debug.h"
#include "code/core/heap.h"
#include "code/engine/render/async/drawable.h"
#include "code/engine/render/async/renderevent.h"
#include "code/engine/render/async/private/drawableimpl.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/math/matrix.h"
#include "code/math/vector2.h"
#include "code/math/vector4.h"
#include "code/core/strings.h"
#include "code/content/memorystream.h"

#define DRAWABLE_FILE "..\\..\\..\\code\\engine\\render\\async\\private\\drawable.cpp"

namespace engine
{
	namespace render
	{
		// The newest frame whose deferred deletions have run (raised by the proxies' destructors)
		static unsigned int gDeletedFrame;

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

		static void DoUnknown106E02C0(Drawable drawable)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->Unknown106E02C0();
			}
		}

		static void DoSetFlag10(Drawable drawable)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->SetFlag10();
			}
		}

		static void DoClearFlag10(Drawable drawable)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->ClearFlag10();
			}
		}

		static void DoSetSegmentVisible(Drawable drawable, unsigned __int64 segment, bool visible)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->SetSegmentVisible(data->drawable->FindSegment(segment), visible);
			}
		}

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

		static void DoUnknown106E03E0(Drawable drawable)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->Unknown106E03E0();
			}
		}

		static void DoUnknown106E0490(Drawable drawable)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->Unknown106E0490();
			}
		}

		static void DoSetUnknownCC(Drawable drawable, int value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data && data->drawable)
			{
				data->drawable->SetUnknownCC(value);
			}
		}

		static void DoSetName(Drawable drawable, unsigned __int64 name)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->SetName(name);
			}
		}

		static void DoSetTransform(Drawable drawable, math::Matrix transform)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data && data->drawable && data->drawable->IsRegistered())
			{
				data->drawable->SetTransform(transform);
			}
		}

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
		static void DoSetShader(Drawable drawable, pure3d::Shader* shader, bool enable, int heap)
		{
			core::HeapScope scope(heap);
			GetDrawableData(drawable);
		}

		static void DoClearUnknown78(Drawable drawable)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data && data->drawable)
			{
				data->drawable->SetUnknown78(0);
			}
		}

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

		static void DoSetFlag101Bit1(Drawable drawable, bool value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->SetFlag101Bit1(value);
			}
		}

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
		static void DoSetSegmentVisibility(Drawable drawable, engine::DrawableSegmentVisibility* visibilities,
			unsigned int count)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				engine::DrawableSegmentVisibility* visibility = visibilities;
				for (unsigned int i = count; i != 0; i--)
				{
					core::Name<core::CaseSensitiveKey> name(visibility->name);
					data->drawable->SetSegmentVisible(data->drawable->FindSegment(name), visibility->visible);
					visibility++;
				}
			}
			FreeRenderEvent(visibilities);
		}

		static void DoSetPartsUnknown(Drawable drawable, int value)
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

		// Shares the binding objects of another drawable with the same parts
		static void DoShareBindings(Drawable drawable, Drawable other, int heap)
		{
			core::HeapScope scope(heap);
			DrawableImpl* impl = 0;
			DrawableImpl* otherImpl = 0;
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
			if (otherImpl && impl && otherImpl->parts.Size() == impl->parts.Size())
			{
				unsigned int count = otherImpl->parts.Size();
				for (unsigned int i = 0; i < count; i++)
				{
					PartBindingSource* source = PartRef(otherImpl, i)->GetBindingSource();
					if (source)
					{
						PartBinding* binding = source->CreateBinding();
						PartRef(impl, i)->SetBinding(binding);
					}
				}
			}
		}

		// Looks for a part with a binding source and does nothing with it in this build
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
			if (otherImpl && impl)
			{
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
		}

		static void DoResetStates(Drawable drawable)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data && data->drawable)
			{
				unsigned int count = data->drawable->parts.Size();
				for (unsigned int i = 0; i < count; i++)
				{
					PartRef part(data->drawable, i);
					pure3d::PrimitiveState* state = part->state;
					if (state && (state->unknownC || state->primitive->unknown18))
					{
						state->Unknown106F2F00(0);
					}
				}
			}
		}

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
						if (0.0f > frame)
						{
							float wrapped = animation->numFrames + frame;
							frame = 0.0f > wrapped ? 0.0f : wrapped;
						}
						if (0.0f > end)
						{
							float wrapped = animation->numFrames + end;
							end = 0.0f > wrapped ? 0.0f : wrapped;
						}
						controller->SetFrameRange(start, end);
						controller->SetFrame(frame);
						controller->SetRelativeSpeed(speed);
						controller->SetCycleMode(mode);
					}
				}
			}
		}

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
									controller->SetAnimation(animation, 0.0f, 0.0f);
									if (0.0f > frame)
									{
										float wrapped = animation->numFrames + frame;
										frame = 0.0f > wrapped ? 0.0f : wrapped;
									}
									if (0.0f > end)
									{
										float wrapped = animation->numFrames + end;
										end = 0.0f > wrapped ? 0.0f : wrapped;
									}
									controller->SetFrameRange(start, end);
									controller->SetFrame(frame);
									controller->SetRelativeSpeed(speed);
									controller->SetCycleMode(mode);
								}
							}
						}
					}
				}
			}
		}

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
						controller->SetAnimation(animation, 0.0f, 0.0f);
						controller->SetBindingSource(part->GetBindingSource());
						if (0.0f > frame)
						{
							float wrapped = animation->numFrames + frame;
							frame = 0.0f > wrapped ? 0.0f : wrapped;
						}
						if (0.0f > end)
						{
							float wrapped = animation->numFrames + end;
							end = 0.0f > wrapped ? 0.0f : wrapped;
						}
						controller->SetFrameRange(start, end);
						controller->SetFrame(frame);
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

		// The event holds a reference to the region, released here
		static void DoSetVertexDeformRegion(Drawable drawable, pure3d::VertexDeformRegion* region)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				unsigned int count = data->drawable->parts.Size();
				for (unsigned int i = 0; i < count; i++)
				{
					PartRef part(data->drawable, i);
					pure3d::MeshState* mesh = dynamic_cast<pure3d::MeshState*>(part->state);
					if (mesh && mesh->GetController3())
					{
						((pure3d::VertexRegionAnimController*)mesh->GetController3())->SetRegion(region);
					}
				}
			}
			if (region)
			{
				region->Release();
			}
		}

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

		static void DoSetSegmentUnknown2C(Drawable drawable, core::Name<core::CaseSensitiveKey> segment, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				unsigned int first;
				unsigned int count;
				data->drawable->GetSegmentParts(data->drawable->FindSegment(segment), &first, &count);
				for (unsigned int i = first; i < first + count; i++)
				{
					data->drawable->SetPartUnknown2C(i, value);
				}
			}
		}

		static void DoResetParticles(Drawable drawable)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					if (PartRef(impl, i)->primitive->type == 0x10)
					{
						float zero = 0.0f;
						((pure3d::ParticleSystemState*)PartRef(impl, i)->state)->SetOverride(
							pure3d::gParticleKey1127F214, 2, &zero);
					}
					else
					{
						PartRef(impl, i).Unknown106E14B0(0);
					}
				}
			}
		}

		static void DoSetEffectOverrides(Drawable drawable, EffectOverrides overrides)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					if (PartRef(impl, i)->primitive->type == 0x10)
					{
						pure3d::ParticleSystemState* state = (pure3d::ParticleSystemState*)PartRef(impl, i)->state;
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
					if (PartRef(impl, i)->primitive->type == 0x10)
					{
						((pure3d::ParticleSystemState*)PartRef(impl, i)->state)->SetGeneratorParameter(name, 0, &value);
					}
				}
			}
		}

		static void DoSetGeneratorFloat2(Drawable drawable, core::Name<core::CaseInsensitiveKey32> name, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					if (PartRef(impl, i)->primitive->type == 0x10)
					{
						((pure3d::ParticleSystemState*)PartRef(impl, i)->state)->SetGeneratorParameter2(name, 2,
							&value);
					}
				}
			}
		}

		static void DoSetParticleFloat(Drawable drawable, core::Name<core::CaseInsensitiveKey32> name, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					if (PartRef(impl, i)->primitive->type == 0x10)
					{
						((pure3d::ParticleSystemState*)PartRef(impl, i)->state)->SetOverride(name, 2, &value);
					}
				}
			}
		}

		static void DoSetGeneratorFloat3(Drawable drawable, core::Name<core::CaseInsensitiveKey32> name, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					if (PartRef(impl, i)->primitive->type == 0x10)
					{
						((pure3d::ParticleSystemState*)PartRef(impl, i)->state)->SetGeneratorParameter3(name, 2,
							&value);
					}
				}
			}
		}

		static void DoSetParticleUnknownE70(Drawable drawable, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					if (PartRef(impl, i)->primitive->type == 0x10)
					{
						((pure3d::ParticleSystemState*)PartRef(impl, i)->state)->Unknown10709E70(value);
					}
				}
			}
		}

		static void DoSetParticleUnknownE50(Drawable drawable, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					if (PartRef(impl, i)->primitive->type == 0x10)
					{
						((pure3d::ParticleSystemState*)PartRef(impl, i)->state)->Unknown10709E50(value);
					}
				}
			}
		}

		static void DoSetParticleUnknownE40(Drawable drawable, bool value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					if (PartRef(impl, i)->primitive->type == 0x10)
					{
						((pure3d::ParticleSystemState*)PartRef(impl, i)->state)->Unknown10709E40(value);
					}
				}
			}
		}

		static void DoSetParticleUnknownCC0(Drawable drawable, bool value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					if (PartRef(impl, i)->primitive->type == 0x10)
					{
						((pure3d::ParticleSystemState*)PartRef(impl, i)->state)->Unknown10709CC0(value);
					}
				}
			}
		}

		static void DoSetParticleUnknown49C(Drawable drawable, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					if (PartRef(impl, i)->primitive->type == 0x10)
					{
						((pure3d::ParticleSystemState*)PartRef(impl, i)->state)->SetUnknown49C(value);
					}
				}
			}
		}

		static void DoSetParticleUnknown4A8(Drawable drawable, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					if (PartRef(impl, i)->primitive->type == 0x10)
					{
						((pure3d::ParticleSystemState*)PartRef(impl, i)->state)->SetUnknown4A8(value);
					}
				}
			}
		}

		static void DoSetParticleUnknown4B8(Drawable drawable, bool value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					if (PartRef(impl, i)->primitive->type == 0x10)
					{
						((pure3d::ParticleSystemState*)PartRef(impl, i)->state)->SetUnknown4B8(value);
					}
				}
			}
		}

		// The distance fade of a particle system (state +0x4A4 reaches the
		// vertex colour through the TEXCOORD1.w fade)
		static void DoSetParticleFade(Drawable drawable, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					if (PartRef(impl, i)->primitive->type == 0x10)
					{
						((pure3d::ParticleSystemState*)PartRef(impl, i)->state)->SetUnknown4A4(value);
					}
				}
			}
		}

		static void DoParticleUnknownCD0(Drawable drawable)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					if (PartRef(impl, i)->primitive->type == 0x10)
					{
						((pure3d::ParticleSystemState*)PartRef(impl, i)->state)->Unknown10709CD0();
					}
				}
				impl->UpdateBounds(true);
			}
		}

		// Gives every part without a binding one made from its binding source (the shader input description is
		// not used in this build)
		static void DoCreateBindings(Drawable drawable, pure3d::pddiShaderInputInitData init, int heap)
		{
			core::HeapScope scope(heap);
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				for (unsigned int i = 0; i < (unsigned int)impl->parts.Size(); i++)
				{
					DrawablePart* part = PartRef(impl, i).Get();
					if (!part->binding)
					{
						PartBindingSource* source;
						pure3d::PrimitiveState* state = part->state;
						if (state && (state->unknownC || state->primitive->unknown18))
						{
							source = (PartBindingSource*)(state->unknownC ? state->unknownC : state->primitive->unknown18);
						}
						else if (part->primitive && part->primitive->unknown18)
						{
							source = (PartBindingSource*)part->primitive->unknown18;
						}
						else
						{
							continue;
						}
						if (source)
						{
							part->SetBinding(source->CreateBinding());
						}
					}
				}
			}
		}

		static void DoSetBindingVector4(Drawable drawable, core::CaseInsensitiveKey32 key, math::Vector4 value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				for (unsigned int i = 0; i < (unsigned int)impl->parts.Size(); i++)
				{
					PartBinding* binding = PartRef(impl, i)->binding;
					if (binding)
					{
						core::Name<core::CaseInsensitiveKey32> name(key);
						binding->parameters->SetVector4(name, value);
					}
				}
			}
		}

		static void DoSetBindingVector(Drawable drawable, core::CaseInsensitiveKey32 key, math::Vector value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				for (unsigned int i = 0; i < (unsigned int)impl->parts.Size(); i++)
				{
					PartBinding* binding = PartRef(impl, i)->binding;
					if (binding)
					{
						core::Name<core::CaseInsensitiveKey32> name(key);
						binding->parameters->SetVector(name, value);
					}
				}
			}
		}

		// Two-component parameters are not passed on in this build
		static void DoSetBindingVector2(Drawable drawable, core::CaseInsensitiveKey32 key, math::Vector2 value)
		{
		}

		static void DoSetBindingFloat(Drawable drawable, core::CaseInsensitiveKey32 key, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				for (unsigned int i = 0; i < (unsigned int)impl->parts.Size(); i++)
				{
					PartBinding* binding = PartRef(impl, i)->binding;
					if (binding)
					{
						core::Name<core::CaseInsensitiveKey32> name(key);
						binding->parameters->SetFloat(name, value);
					}
				}
			}
		}

		static void DoSetBindingBool(Drawable drawable, core::CaseInsensitiveKey32 key, bool value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				for (unsigned int i = 0; i < (unsigned int)impl->parts.Size(); i++)
				{
					PartBinding* binding = PartRef(impl, i)->binding;
					if (binding)
					{
						core::Name<core::CaseInsensitiveKey32> name(key);
						binding->parameters->SetBool(name, value);
					}
				}
			}
		}

		static void DoUnknown106E1250(Drawable drawable, core::Name<core::CaseSensitiveKey> name)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->Unknown106E1250(name);
			}
		}

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
			colour = other.colour;
			unknown1C = other.unknown1C;
			unknown20 = other.unknown20;
			unknown24 = other.unknown24;
		}

		// The drawable of a game object (it answers a GetCurrentDrawable message)
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
						return mixer->unknown10;
					}
				}
			}
			return 0;
		}

		void Drawable::SetJointMatrices(const JointMatrix* matrices, unsigned int count) const
		{
			DrawableData* data = GetDrawableData(*this);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				pure3d::Pose* pose = impl->GetPose();
				unsigned int n = count < pose->mData.mJointCount ? count : pose->mData.mJointCount;
				for (unsigned int i = 0; i < n; i++)
				{
					((JointMatrix*)pose->mData.mWorldMatrices)[i] = matrices[i];
				}
				pose->Unknown106DD730();
				impl->MarkPoseDirty();
			}
		}

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
				pure3d::PrimitiveState* state = PartRef(impl, i)->state;
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
		static void DoLoadTexture(unsigned char* data, unsigned int size, pure3d::Texture* texture, unsigned int a,
			unsigned int b)
		{
			content::MemoryStream* stream = new content::MemoryStream(data, size);
			stream->AddRef();
			pure3d::TextureUploader loader(texture, a, b);
			int unknown = texture->info->unknown20;
			const char* name = texture->mName.GetText() ? texture->mName.GetText() : core::GetDefaultString();
			loader.Load(stream, name, unknown, gTextureLoadFlag, 0);
			stream->Release();
			texture->Release();
			delete[] data;
		}

		// Makes the render object as an instance of the source drawable's
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

		static void DoSetUnknownBC(Drawable drawable, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				data->drawable->SetUnknownBC(value);
				GetRenderList()->Refresh(data->drawable);
			}
		}

		static void DoSetPartAnimations(Drawable drawable, int a, bool b)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					DrawablePart* part = PartRef(impl, i).Get();
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

		static void DoSetBiasUnknown(Drawable drawable, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					int type = PartRef(impl, i)->primitive->type;
					if (type == 0x10)
					{
						pure3d::ParticleSystemState* state = (pure3d::ParticleSystemState*)PartRef(impl, i)->state;
						state->SetBias(pure3d::gParticleKey1127F20C, 2, &value);
						state->SetBias(pure3d::gParticleKey1127F2DC, 2, &value);
						state->SetBias(pure3d::gParticleKey1127F2BC, 2, &value);
					}
					else if (type == 8)
					{
						pure3d::GpuSkinState* state = (pure3d::GpuSkinState*)PartRef(impl, i)->state;
						if (state)
						{
							state->Unknown10B87050(value);
						}
					}
				}
			}
		}

		static void DoSetEffectBiases(Drawable drawable, EffectBiases biases)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					if (PartRef(impl, i)->primitive->type == 0x10)
					{
						pure3d::ParticleSystemState* state = (pure3d::ParticleSystemState*)PartRef(impl, i)->state;
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

		static void DoSetParticleBias(Drawable drawable, core::Name<core::CaseInsensitiveKey32> name, float value)
		{
			DrawableData* data = GetDrawableData(drawable);
			if (data)
			{
				DrawableImpl* impl = data->drawable;
				int count = impl->parts.Size();
				for (int i = 0; i < count; i++)
				{
					if (PartRef(impl, i)->primitive->type == 0x10)
					{
						((pure3d::ParticleSystemState*)PartRef(impl, i)->state)->SetBias(name, 2, &value);
					}
				}
			}
		}
	}
}
