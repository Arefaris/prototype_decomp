#include "code/engine/camera/dramaticcamera.h"
#include "code/core/refptr.h"
#include "code/engine/driving/carattributes.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/math/random.h"
#include "code/math/worldbounds.h"
#include "code/pure3d/animation.h"
#include "code/pure3d/channel.h"
#include "code/ravenphysics/context.h"
#include <math.h>

namespace engine
{
	namespace camera
	{
		// The smaller of two floats; the engine keeps this instance out of line (0x10071300)
		float MinOf(float a, float b);

		// What the rays hit by default (the constant is another unit's)
		extern const int gDramaticCollisionMask;

		// FUNCTION: ENGINE 0x1084EF00
		DramaticCamera::DramaticCamera()
			: animationCount(0), collisionMask(gDramaticCollisionMask), unknownB0(0.0f), unknownB4(0.0f),
			unknownB8(0.0f), unknownBC(0.0f), unknownC0(0.0f), unknownC4(0.0f), playing(false), unknownCC(-1.0f),
			unknownD0(false), unknownD1(false), unknownD2(false), unknown120(), controller(0), animationCamera(0),
			unknown12C(0), unknown130(0)
		{
			for (int i = 0; i < 4; i++)
			{
				animations[i].animation = 0;
			}
			core::RefAssign(controller, new pure3d::CameraAnimationController());
			core::RefAssign(animationCamera, new pure3d::Camera());
			animationCamera->SetAspect(16.0f / 9.0f, 0);
			animationCamera->SetMatrix(math::Matrix::IDENTITY);
			controller->SetCamera(animationCamera);
			offsetWorld.x = offsetWorld.y = offsetWorld.z = 0.0f;
			matrix.Identity();
		}

		// FUNCTION: ENGINE 0x1084F060
		// FUNCTION: ENGINE 0x1084F400
		DramaticCamera::~DramaticCamera()
		{
			core::SafeRelease(controller);
			core::SafeRelease(animationCamera);
			for (int i = 0; i < 4; i++)
			{
				core::SafeRelease(animations[i].animation);
			}
		}

		// FUNCTION: ENGINE 0x1084F0B0
		void DramaticCamera::Reset()
		{
			playing = false;
			unknownCC = -1.0f;
			unknownD0 = false;
			controller->Stop();
			animationCamera->SetMatrix(math::Matrix::IDENTITY);
			for (int i = 0; i < 4; i++)
			{
				core::SafeRelease(animations[i].animation);
			}
			Camera::Reset();
		}

		// FUNCTION: ENGINE 0x1084ED90
		void DramaticCamera::SetUnknown12C(int first, int second)
		{
			unknown12C = first;
			unknown130 = second;
		}

		// FUNCTION: ENGINE 0x1084EDB0
		void DramaticCamera::Stop()
		{
			if (playing)
			{
				controller->Stop();
				playing = false;
				unknown12C = 0;
			}
		}

		// FUNCTION: ENGINE 0x1084EDE0
		bool DramaticCamera::IsOver() const
		{
			return unknownB0 >= unknownBC;
		}

		// FUNCTION: ENGINE 0x1084EE00
		bool DramaticCamera::Slot4()
		{
			return unknownD0;
		}

		// FUNCTION: ENGINE 0x1084EE10
		void DramaticCamera::SetCollisionMask(int value)
		{
			collisionMask = value;
		}

		// FUNCTION: ENGINE 0x1084F420
		// EQUIVALENT: register allocation and scheduling: the engine keeps the queued animation in ebx and the index in
		// esi (ours the other way round), pushes ebx only inside the loop, reaches the sample points through the pointer
		// to their last component and orders the loads of the mirrored point differently; same calls, reads, writes and
		// float operations in the same order, 56.6 %
		int DramaticCamera::FindAnimation(const math::Matrix* start, float limit, const math::Vector* point,
			bool* checked)
		{
			int clearCount = 0;
			bool clear[4][2];
			math::Vector path[32];
			math::Vector place;
			const DramaticAnimation* queued = animations;
			for (int i = 0; i < animationCount; i++, queued++)
			{
				clear[i][0] = false;
				clear[i][1] = false;
				int count = SamplePath(queued, path, 32);
				if (count > 0)
				{
					if (queued->unknown10)
					{
						for (int j = 0; j < count; j++)
						{
							place.x = path[j].x;
							place.y = path[j].y;
							place.z = path[j].z;
							start->Transform(place, place);
							if (QueryRay(point, &place))
							{
								goto skipFirst;
							}
						}
						clearCount++;
						clear[i][0] = true;
					}
				skipFirst:
					if (queued->unknown11)
					{
						for (int j = 0; j < count; j++)
						{
							place.y = path[j].y;
							place.z = path[j].z;
							place.x = math::WORLD_MIN - path[j].x;
							start->Transform(place, place);
							if (QueryRay(point, &place))
							{
								goto skipSecond;
							}
						}
						clearCount++;
						clear[i][1] = true;
					}
				}
			skipSecond:;
			}
			if (clearCount > 0)
			{
				float total = 0.0f;
				for (int i = 0; i < animationCount; i++)
				{
					if (clear[i][0])
					{
						total = animations[i].unknown14 + total;
					}
					if (clear[i][1])
					{
						total = animations[i].unknown14 + total;
					}
				}
				if (limit < 0.0f)
				{
					limit = 0.0f;
				}
				if (limit + total != 0.0f)
				{
					unsigned int bits = (math::gRandom->Next() & 0x7FFFFF) | 0x3F800000;
					float roll = (*(float*)&bits - driving::gOne) * (limit + total);
					for (int i = 0; i < animationCount; i++)
					{
						if (clear[i][0])
						{
							roll = roll - animations[i].unknown14;
							if (roll <= 0.0f)
							{
								*checked = false;
								return i;
							}
						}
						if (clear[i][1])
						{
							roll = roll - animations[i].unknown14;
							if (roll <= 0.0f)
							{
								*checked = true;
								return i;
							}
						}
					}
				}
			}
			return -1;
		}

		// FUNCTION: ENGINE 0x1084F7C0
		// EQUIVALENT: the engine adds the translation rows with the rotated offset as the first operand for the x component
		// only, loads the three components of the object's position in another order and schedules the pointer to the
		// rotated offset after the matrix copy; same reads, writes and calls otherwise, 82.1 %
		bool DramaticCamera::Play(HandleBase object, const math::Vector* offset, bool newUnknownD2, float delay,
			float duration, float tail, float limit)
		{
			if (playing)
			{
				return false;
			}
			if (animationCount == 0)
			{
				return false;
			}
			GameObject* target = 0;
			if (object.index != 0xFFFF)
			{
				GameObjectEntry* entry = &GetGameObjectEntries()[object.index];
				if (entry->serial == object.serial)
				{
					target = entry->object;
				}
			}
			if (target != 0)
			{
				math::Vector* rotated = &offsetWorld;
				matrix = target->transform->value;
				matrix.Rotate(*offset, *rotated);
				matrix.m[3][0] = matrix.m[3][0] + rotated->x;
				matrix.m[3][1] = rotated->y + matrix.m[3][1];
				matrix.m[3][2] = rotated->z + matrix.m[3][2];
				math::Matrix& world = target->transform->value;
				math::Vector place(world.m[3][0], world.m[3][1], world.m[3][2]);
				int index = FindAnimation(&matrix, limit, &place, &unknownD1);
				if (index >= 0)
				{
					DramaticAnimation* entry = &animations[index];
					pure3d::Animation* animation = entry->animation;
					controller->SetAnimation(animation, 0.0f, 0.0f);
					controller->SetStartFrame(0.0f);
					if (duration > 0.0f)
					{
						unknownB8 = duration;
					}
					else
					{
						unknownB8 = fabsf(entry->end - entry->start) / (animation->mFrameRate * entry->speed);
					}
					unknownB4 = delay;
					unknownBC = unknownB8 + delay + tail;
					unknownC0 = entry->start;
					unknownC4 = entry->end;
					unknown120 = object;
					unknownD2 = newUnknownD2;
					playing = true;
					unknownB0 = 0.0f;
					unknownCC = -1.0f;
					focusDistance = 0.0f;
				}
			}
			for (int i = 0; i < 4; i++)
			{
				core::SafeRelease(animations[i].animation);
			}
			animationCount = 0;
			return playing;
		}

		// FUNCTION: ENGINE 0x1084F120
		bool DramaticCamera::AddAnimation(pure3d::Animation* newAnimation, float startFrame, float endFrame,
			float newSpeed, bool newUnknown10, bool newUnknown11, float newUnknown14)
		{
			if (playing)
			{
				return false;
			}
			if (newAnimation == 0)
			{
				return false;
			}
			if (newUnknown14 == 0.0f)
			{
				return true;
			}
			if (0.0f > newUnknown14)
			{
				return false;
			}
			if (!newUnknown10 && !newUnknown11)
			{
				return true;
			}
			if (animationCount >= 4)
			{
				return false;
			}
			DramaticAnimation* entry = &animations[animationCount];
			animationCount++;
			core::RefAssign(entry->animation, newAnimation);
			entry->start = 0.0f;
			if (startFrame > 0.0f)
			{
				entry->start = MinOf(startFrame, entry->animation->numFrames);
			}
			if (endFrame >= 0.0f)
			{
				entry->end = MinOf(endFrame, entry->animation->numFrames);
			}
			else
			{
				entry->end = entry->animation->numFrames;
			}
			entry->speed = 1.0f;
			if (newSpeed > 0.0f)
			{
				entry->speed = newSpeed;
			}
			entry->unknown14 = newUnknown14;
			entry->unknown10 = newUnknown10;
			entry->unknown11 = newUnknown11;
			return true;
		}

		// FUNCTION: ENGINE 0x1084F240
		// EQUIVALENT: the engine keeps the queued animation in ebx and the output buffer in edi where ours takes edi and
		// ebx (so the pushes and the loop's address registers differ); same reads, writes, calls and order otherwise, 68.7 %
		int DramaticCamera::SamplePath(const DramaticAnimation* queued, math::Vector* out, int maxCount)
		{
			if (controller == 0)
			{
				return -1;
			}
			controller->SetAnimation(queued->animation, 0.0f, 0.0f);
			int available = (int)(fabsf(queued->end - queued->start) / 15.0f + 0.5f) + 1;
			int count = maxCount;
			if (count >= available)
			{
				count = available;
			}
			int written = 0;
			math::Vector current(0.0f, 0.0f, 0.0f);
			math::Vector previous(0.0f, 0.0f, 0.0f);
			pure3d::AnimationGroup* group = queued->animation->GetGroup(0);
			if (group == 0)
			{
				return -1;
			}
			pure3d::VectorChannel* channel = (pure3d::VectorChannel*)group->FindChannel(0x4E415254, 0x54434556);
			if (channel == 0)
			{
				return -1;
			}
			for (int i = 0; i < count; i++)
			{
				float time = queued->start + (queued->end - queued->start) * ((float)i / (float)(count - 1));
				channel->mKeys.Evaluate(pure3d::FrameTime(time), &current);
				if (i != 0)
				{
					if (!math::VectorsDiffer(current, previous))
					{
						continue;
					}
					if (i != count - 1 && current.IsNearOther(previous, 0.1f))
					{
						continue;
					}
				}
				out[written].x = current.x;
				out[written].y = current.y;
				out[written].z = current.z;
				previous.x = current.x;
				previous.y = current.y;
				previous.z = current.z;
				written++;
			}
			return written;
		}

		// FUNCTION: ENGINE 0x1084EE20
		bool DramaticCamera::QueryRay(const math::Vector* from, const math::Vector* to)
		{
			ravenphysics::RayQuery query;
			query.start.x = from->x;
			query.start.y = from->y;
			query.start.z = from->z;
			query.end.x = to->x;
			query.end.y = to->y;
			query.end.z = to->z;
			query.filter.properties.unknown0 = -1;
			query.filter.properties.unknown4 = collisionMask;
			return ravenphysics::gContext->QueryObject((ravenphysics::PhysicsBody*)&query);
		}
	}
}

// Kept copies (template instances of this unit):
// FUNCTION: ENGINE 0x1084EEB0
// FUNCTION: ENGINE 0x1084EEE0
