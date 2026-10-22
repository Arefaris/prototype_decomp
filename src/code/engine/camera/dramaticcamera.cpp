#include "code/engine/camera/dramaticcamera.h"
#include "code/core/refptr.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/pure3d/animation.h"
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

		// FUNCTION: ENGINE 0x1084EE20
		void DramaticCamera::QueryRay(const math::Vector* from, const math::Vector* to)
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
			ravenphysics::gContext->QueryObject((ravenphysics::PhysicsBody*)&query);
		}
	}
}

// Kept copies (template instances of this unit):
// FUNCTION: ENGINE 0x1084EEB0
// FUNCTION: ENGINE 0x1084EEE0
