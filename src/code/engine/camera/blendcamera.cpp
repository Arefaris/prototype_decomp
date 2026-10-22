#include "code/engine/camera/blendcamera.h"
#include "code/core/heap.h"
#include "code/engine/camera/cameramath.h"
#include "code/engine/camera/director.h"
#include "code/ravenphysics/context.h"
#include <float.h>
#include <math.h>

namespace choreo
{
	extern const float gZero;
}

namespace engine
{
	namespace camera
	{
		// What a sweep's query answers (a ravenphysics::RayHit; the members are guessed from what the sweep sets)
		struct SweepHit
		{
			float distance;
			int unknown4;
			int unknown8;
			math::Vector normal;
			int unknown18;
			int unknown1C;
			unsigned short unknown20;
			unsigned char unknown22[0x30 - 0x22];
		};

		// What the sweeps of a new blend hit (the constant is another unit's)
		extern const int gBlendCollisionMask;

		// FUNCTION: ENGINE 0x108523A0
		BlendCamera::BlendCamera()
			: fromCamera(), toCamera(), unknownA0(0.0f), elapsed(0.0f), duration(0.0f), unknownAC(0), reverse(false),
			unknownB1(false), unknownB2(false), done(false), unknownB4(0), collisionMask(gBlendCollisionMask)
		{
			core::HeapScope scope(sCameraHeap);
			SetEnabled(false);
		}

		// FUNCTION: ENGINE 0x108522C0
		// FUNCTION: ENGINE 0x10852440
		BlendCamera::~BlendCamera()
		{
		}

		// FUNCTION: ENGINE 0x10852390
		bool BlendCamera::Slot4()
		{
			return done;
		}

		// FUNCTION: ENGINE 0x10852300
		int BlendCamera::GetType()
		{
			return 2;
		}

		// FUNCTION: ENGINE 0x10852460
		void BlendCamera::Reset()
		{
			Stop();
			Camera::Reset();
		}

		// FUNCTION: ENGINE 0x10852310
		bool BlendCamera::IsDone() const
		{
			return elapsed >= duration;
		}

		// FUNCTION: ENGINE 0x10852330
		// EQUIVALENT: the engine loads the all-ones constant after the first two stores, ours before them, 71.2 %
		void BlendCamera::Stop()
		{
			SetEnabled(false);
			duration = 0.0f;
			done = false;
			fromCamera.slot = -1;
			fromCamera.id = -1;
			toCamera.slot = -1;
			toCamera.id = -1;
		}

		// FUNCTION: ENGINE 0x10852370
		float BlendCamera::GetDuration() const
		{
			return duration;
		}

		// FUNCTION: ENGINE 0x10852380
		void BlendCamera::SetCollisionMask(int value)
		{
			collisionMask = value;
		}
		// FUNCTION: ENGINE 0x108522F0
		void BlendCamera::Slot11()
		{
		}

		// FUNCTION: ENGINE 0x10852470
		// EQUIVALENT: the engine keeps the source camera in ebx and reaches the matrix of the pure3d camera through a
		// pointer 0x90 into it (ours the source in edi and the matrix by offset), loads the three components of the view
		// direction in another order and scales them in registers; same reads, writes and calls otherwise, 13.7 %
		void BlendCamera::Capture(Camera* source, CameraSnapshot* out)
		{
			pure3d::Camera* view = source->camera;
			math::Vector place;
			place.x = view->position.x;
			place.y = view->position.y;
			place.z = view->position.z;
			out->position.x = place.x;
			out->position.y = place.y;
			out->position.z = place.z;
			math::Matrix& matrix = *view->GetWorldMatrix();
			math::Vector row;
			row.x = matrix.m[2][0];
			row.y = matrix.m[2][1];
			row.z = matrix.m[2][2];
			math::Vector forward;
			forward.x = row.x;
			forward.y = row.y;
			forward.z = row.z;
			out->yaw = GetYaw(&forward);
			out->pitch = GetPitch(&forward);
			float distance = source->focusDistance;
			out->distance = distance;
			forward.Scale(distance);
			out->target.Add(out->position, forward);
			out->roll = atan2f(matrix.m[0][1], matrix.m[1][1]);
			out->fov = source->camera->fov;
			out->nearPlane = source->camera->minZ;
			out->farPlane = source->camera->maxZ;
			out->windowEnabled = source->camera->window.enabled;
			out->window[0] = source->camera->window.values[0];
			out->window[1] = source->camera->window.values[1];
			out->window[2] = source->camera->window.values[2];
			out->window[3] = source->camera->window.values[3];
			source->Slot4();
		}

		// FUNCTION: ENGINE 0x108525A0
		bool BlendCamera::Begin(ControllerRef from, ControllerRef to, bool newReverse, int newKind, float time)
		{
			if (Director::Get()->GetController(from) != 0 && Director::Get()->GetController(to) != 0)
			{
				fromCamera.slot = from.slot;
				fromCamera.id = from.id;
				toCamera.slot = to.slot;
				toCamera.id = to.id;
				reverse = newReverse;
				unknownAC = newKind;
				duration = time;
				if (!newReverse)
				{
					Capture(Director::Get()->GetController(fromCamera), &start);
				}
				unknownB1 = true;
				unknownB2 = false;
				unknownB4 = 0;
				unknownA0 = 0.0f;
				elapsed = 0.0f;
				SetEnabled(true);
				Slot11();
				return true;
			}
			return false;
		}
		// FUNCTION: ENGINE 0x108526D0
		bool BlendCamera::Sweep(const math::Vector* from, const math::Vector* to, math::Vector* out)
		{
			if (collisionMask == 0)
			{
				return false;
			}
			static ravenphysics::RayQuery sQuery;
			sQuery.start.x = from->x;
			sQuery.start.y = from->y;
			sQuery.start.z = from->z;
			sQuery.end.x = to->x;
			sQuery.end.y = to->y;
			sQuery.end.z = to->z;
			sQuery.filter.properties.unknown0 = -1;
			sQuery.filter.properties.unknown4 = collisionMask;
			sQuery.unknown24 = 1;
			SweepHit hit;
			hit.unknown4 = -1;
			hit.unknown8 = -1;
			hit.unknown1C = -1;
			hit.unknown20 = 0xFFFF;
			hit.distance = FLT_MAX;
			if (ravenphysics::gContext->QuerySweepObject((ravenphysics::PhysicsBody*)&sQuery, &hit))
			{
				if (hit.distance == choreo::gZero)
				{
					out->x = from->x;
					out->y = from->y;
					out->z = from->z;
					return true;
				}
				math::Vector direction;
				direction.x = to->x - from->x;
				direction.y = to->y - from->y;
				direction.z = to->z - from->z;
				direction.Normalize();
				direction.Scale(hit.distance);
				math::Vector point;
				point.Add(*from, direction);
				out->x = point.x;
				out->y = point.y;
				out->z = point.z;
				return true;
			}
			return false;
		}
	}
}
