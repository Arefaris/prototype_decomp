#include "code/engine/camera/scriptedcamera.h"
#include "code/core/refptr.h"
#include "code/engine/camera/camera.h"
#include "code/content/loadinventory.h"
#include "code/math/vector4.h"
#include "code/math/worldbounds.h"
#include "code/engine/camera/cameramath.h"
#include "code/engine/fight/effecttrack.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/pure3d/animation.h"
#include <math.h>
#include <new>

namespace choreo
{
	extern const float gZero;
}

namespace content
{
	static const EnumValue sOrientModeValues[] =
	{
		{ "World", 0 },
		{ "Object", 1 },
		{ "Joint", 2 },
		{ "Facing", 3 }
	};

	// FUNCTION: ENGINE 0x10850980
	template<> void EnumInfo<engine::camera::ScriptedCamera::OrientMode>::Get(const char** name, const EnumValue** values,
		int* count, const char** code)
	{
		*name = "engine::camera::ScriptedCamera::OrientMode";
		*code = "pn";
		*values = sOrientModeValues;
		*count = 4;
	}
}

namespace engine
{
	namespace camera
	{
		// Whether two handles hold the same index and serial number
		static inline bool SameHandle(const HandleBase& a, const HandleBase& b)
		{
			return *(const int*)&a == *(const int*)&b;
		}

		// Clamps a value into 0 .. 1 (inlined by the engine; name guessed)
		static inline void ClampUnit(float* value)
		{
			if (!(*value >= 0.0f))
			{
				*value = 0.0f;
			}
			if (*value - 1.0f >= 0.0f)
			{
				*value = 1.0f;
			}
		}

		// FUNCTION: ENGINE 0x10851400
		SplineTrack::SplineTrack() : object(), spline(0), times(0)
		{
			Clear();
		}

		// FUNCTION: ENGINE 0x10850E60
		SplineTrack::~SplineTrack()
		{
			delete spline;
			delete[] times;
		}

		// FUNCTION: ENGINE 0x10850E90
		// EQUIVALENT: the engine loads and tests the spline pointer after the float stores, ours before them, 73.7 %
		void SplineTrack::Clear()
		{
			active = false;
			HandleBase empty;
			object = empty;
			part = 0xFFFF;
			orientMode = 0;
			offset.x = offset.y = offset.z = 0.0f;
			position.x = position.y = position.z = 0.0f;
			delete spline;
			spline = 0;
			delete[] times;
			times = 0;
			timeCount = 0;
		}

		// FUNCTION: ENGINE 0x10850E00
		bool ScriptedCamera::IsActive() const
		{
			return mode != 0;
		}

		// FUNCTION: ENGINE 0x10850E10
		bool ScriptedCamera::Slot4()
		{
			return finished;
		}

		// FUNCTION: ENGINE 0x10850E20
		void ScriptedCamera::SetUp(const math::Vector& newUp)
		{
			up.x = newUp.x;
			up.y = newUp.y;
			up.z = newUp.z;
		}

		// FUNCTION: ENGINE 0x10850E50
		void ScriptedCamera::SetUnknown57(bool value)
		{
			unknown57 = value;
		}

		// FUNCTION: ENGINE 0x108509F0
		void ScriptedCamera::Restart()
		{
			Reset();
		}
		// FUNCTION: ENGINE 0x10851480
		ScriptedCamera::ScriptedCamera()
			: mode(0), unknown55(false), unknown56(false), unknown57(false), pending(0), position(), lookAt(),
			animation(0), controller(0), animationCamera(0), window()
		{
			Restart();
		}

		// FUNCTION: ENGINE 0x10850F50
		// FUNCTION: ENGINE 0x108514E0
		ScriptedCamera::~ScriptedCamera()
		{
			core::SafeRelease(animation);
			core::SafeRelease(controller);
			core::SafeRelease(animationCamera);
		}

		// FUNCTION: ENGINE 0x10850FA0
		// EQUIVALENT: the engine pushes the address of the first released pointer after three of the float stores, ours
		// before them, 92.3 %
		void ScriptedCamera::Reset()
		{
			mode = 0;
			unknown4C = false;
			unknown4D = false;
			unknown4E = false;
			unknown50 = -1.0f;
			finished = false;
			unknown55 = false;
			unknown56 = false;
			unknown57 = false;
			pending = 0;
			position.Clear();
			lookAt.Clear();
			up.x = 0.0f;
			up.y = 1.0f;
			up.z = 0.0f;
			unknownD8 = 0.0f;
			unknownDC = false;
			core::SafeRelease(animation);
			core::SafeRelease(controller);
			core::SafeRelease(animationCamera);
			camera->SetNearPlane(0.5f);
			camera->SetFarPlane(10000.0f);
			camera->SetMatrix(math::Matrix::IDENTITY);
			window.enabled = false;
			window.values[0] = 0.0f;
			window.values[1] = 0.0f;
			window.values[2] = 0.0f;
			window.values[3] = 0.0f;
		}

		// FUNCTION: ENGINE 0x108510A0
		void ScriptedCamera::ReleaseAnimation()
		{
			core::SafeRelease(animation);
			core::SafeRelease(controller);
			core::SafeRelease(animationCamera);
		}

		// FUNCTION: ENGINE 0x10850A00
		// EQUIVALENT: the engine ORs the flag after the last float store, ours before it, 80.0 %
		bool ScriptedCamera::SetPositionPoint(const math::Vector& point)
		{
			position.position.x = point.x;
			position.position.y = point.y;
			position.position.z = point.z;
			pending |= 1;
			position.active = false;
			return true;
		}

		// FUNCTION: ENGINE 0x10850A30
		// EQUIVALENT: the engine loads the result constant before the last float store and ORs the flag after it, ours
		// the other way round, 65.2 %
		bool ScriptedCamera::SetLookAtPoint(const math::Vector& point)
		{
			lookAt.position.x = point.x;
			lookAt.position.y = point.y;
			lookAt.position.z = point.z;
			pending |= 2;
			lookAt.active = false;
			return true;
		}

		// FUNCTION: ENGINE 0x10850B90
		bool ScriptedCamera::SetUnknownD8(float value)
		{
			if (0.01f > value || (!unknown57 && value > 3.0f))
			{
				return false;
			}
			unknownD8 = value;
			return true;
		}

		// FUNCTION: ENGINE 0x10850BD0
		// EQUIVALENT: the engine loads the result constant before the third float store, ours after it, 76.1 %
		bool ScriptedCamera::SetWindow(float a, float b, float c, float d)
		{
			bool result = true;
			window.values[0] = a;
			window.values[1] = b;
			window.values[2] = c;
			window.enabled = result;
			window.values[3] = d;
			return result;
		}

		// FUNCTION: ENGINE 0x10851360
		bool ScriptedCamera::IsFinished()
		{
			switch (mode)
			{
			case 1:
				{
					float end = 0.0f;
					if (position.spline != 0)
					{
						float last = position.times[position.timeCount - 2];
						if (last > 0.0f)
						{
							end = last;
						}
					}
					if (lookAt.spline != 0)
					{
						float last = lookAt.times[lookAt.timeCount - 2];
						if (last > end)
						{
							end = last;
						}
					}
					if (end == 0.0f)
					{
						end = 1.0f;
					}
					return time >= end;
				}
			case 2:
			case 3:
				if (controller != 0)
				{
					return controller->IsDone();
				}
				return true;
			}
			return true;
		}

		// FUNCTION: ENGINE 0x108509B0
		content::ClassInfo* ScriptedCamera::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::camera::ScriptedCamera";
			sInfo.code = "pn";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x10851420
		content::MemberList* ScriptedCamera::GetMembers()
		{
			static content::MemberList sList;
			sList.baseType = content::GetClassMetaType<Camera>();
			static content::BaseClassCasterImpl<Camera, ScriptedCamera> sCaster;
			sList.baseCaster = &sCaster;
			return &sList;
		}
		// FUNCTION: ENGINE 0x10851230
		bool ScriptedCamera::SetSpline(SplineTrack* track, math::Spline& source)
		{
			if (source.mode != 4)
			{
				return false;
			}
			int count = source.count;
			if (count < 4)
			{
				return false;
			}
			delete track->spline;
			track->spline = 0;
			delete[] track->times;
			track->times = 0;
			track->times = new float[count];
			track->timeCount = count;
			float previous = 0.0f;
			for (int i = 0; i < count; i++)
			{
				float time = source.GetKey(i)->w;
				if (i > 0 && previous >= time)
				{
					delete[] track->times;
					return false;
				}
				track->times[i] = time;
				previous = time;
			}
			track->spline = new math::Spline(count, 4, false);
			*track->spline = source;
			track->spline->SetFlag(true);
			track->segment = 0;
			track->active = true;
			return true;
		}
		// FUNCTION: ENGINE 0x10851560
		bool SplineTrack::Bind(HandleBase newObject, core::Name<core::CaseSensitiveKey> partName)
		{
			GameObject* gameObject = 0;
			if (newObject.index != 0xFFFF)
			{
				GameObjectEntry* entry = &GetGameObjectEntries()[newObject.index];
				if (entry->serial == newObject.serial)
				{
					gameObject = entry->object;
				}
			}
			if (gameObject == 0)
			{
				HandleBase empty;
				object = empty;
				return false;
			}
			object = newObject;
			part = 0xFFFF;
			if (!partName.IsEmpty())
			{
				Attribute<proto::PartLookup*>* attribute =
					(Attribute<proto::PartLookup*>*)gameObject->FindAttribute(proto::gDrawableAttributeName);
				if (attribute == 0)
				{
					return false;
				}
				proto::PartLookup** lookup = &attribute->value;
				if (lookup == 0 || *lookup == 0)
				{
					return false;
				}
				part = (*lookup)->FindPart(partName);
				if (part == 0xFFFF)
				{
					return false;
				}
			}
			return true;
		}
		// FUNCTION: ENGINE 0x108515F0
		// EQUIVALENT: in the spline branch the engine keeps the clamped parameter t in memory and adds the segment with
		// fild / fadd, ours in a register with cvtsi2ss / addss; the rest is identical
		void SplineTrack::Evaluate(float time, bool update, math::Matrix* matrix)
		{
			if (spline != 0)
			{
				while (segment < timeCount - 4 && time >= times[segment + 2])
				{
					segment++;
				}
				float start = times[segment + 1];
				float t = (time - start) / (times[segment + 2] - start);
				ClampUnit(&t);
				math::Vector point;
				math::Vector& found = spline->Evaluate(point, segment + t);
				position.x = found.x;
				position.y = found.y;
				position.z = found.z;
				return;
			}
			HandleBase empty;
			if (SameHandle(object, empty))
			{
				return;
			}
			if (!active && !update)
			{
				return;
			}
			GameObject* gameObject = 0;
			if (object.index != 0xFFFF)
			{
				GameObjectEntry* entry = &GetGameObjectEntries()[object.index];
				if (entry->serial == object.serial)
				{
					gameObject = entry->object;
				}
			}
			if (gameObject == 0)
			{
				return;
			}
			math::Matrix& transform = gameObject->transform->value;
			math::Vector* result = &position;
			math::Vector current;
			current.x = transform.m[3][0];
			current.y = transform.m[3][1];
			current.z = transform.m[3][2];
			result->x = current.x;
			result->y = current.y;
			result->z = current.z;
			math::Matrix* partMatrix = 0;
			if (part != 0xFFFF)
			{
				AttributePtr<proto::PartLookup*> attribute = gameObject->GetAttributePtr<proto::PartLookup*>(proto::gDrawableAttributeName);
				if (attribute.value != 0)
				{
					proto::PartLookup* lookup = *attribute.value;
					if (lookup != 0)
					{
						partMatrix = &lookup->matrices[part];
						math::Vector local;
						local.x = partMatrix->m[3][0];
						local.y = partMatrix->m[3][1];
						local.z = partMatrix->m[3][2];
						transform.Transform(local, *result);
					}
				}
			}
			math::Vector rotated;
			switch (orientMode)
			{
			case 0:
				rotated.x = offset.x;
				rotated.y = offset.y;
				rotated.z = offset.z;
				break;
			case 1:
				transform.Rotate(offset, rotated);
				break;
			case 2:
				if (partMatrix != 0)
				{
					partMatrix->Rotate(offset, rotated);
					transform.Rotate(rotated, rotated);
				}
				else
				{
					transform.Rotate(offset, rotated);
				}
				break;
			case 3:
				{
					math::Vector forward;
					forward.x = transform.m[2][0];
					forward.y = transform.m[2][1];
					forward.z = transform.m[2][2];
					float yaw = GetYaw(&forward);
					rotated.x = offset.x;
					rotated.y = offset.y;
					rotated.z = offset.z;
					RotateAroundY(yaw, &rotated);
				}
				break;
			}
			result->x += rotated.x;
			result->y += rotated.y;
			result->z += rotated.z;
			if (matrix != 0)
			{
				const float* in = &transform.m[0][0];
				float* out = &matrix->m[0][0];
				float zero = math::WORLD_MIN;
				math::Vector4 first;
				first.x = zero - in[0];
				first.y = zero - in[1];
				first.z = zero - in[2];
				first.w = zero - in[3];
				out[0] = first.x;
				out[1] = first.y;
				out[2] = first.z;
				out[3] = first.w;
				out[4] = in[4];
				out[5] = in[5];
				out[6] = in[6];
				out[7] = in[7];
				math::Vector4 third;
				third.x = zero - in[8];
				third.y = zero - in[9];
				third.z = zero - in[10];
				third.w = zero - in[11];
				out[8] = third.x;
				out[9] = third.y;
				out[10] = third.z;
				out[11] = third.w;
				out[12] = in[12];
				out[13] = in[13];
				out[14] = in[14];
				out[15] = in[15];
			}
		}

		// FUNCTION: ENGINE 0x10851950
		bool ScriptedCamera::BindPosition(HandleBase object, const char* partName,
			const math::Vector* newOffset, unsigned int newMode, bool newActive)
		{
			if (!position.Bind(object, core::Name<core::CaseSensitiveKey>(partName, 1)))
			{
				return false;
			}
			if (newMode <= 3)
			{
				position.orientMode = newMode;
				position.offset.x = newOffset->x;
				position.offset.y = newOffset->y;
				position.offset.z = newOffset->z;
			}
			pending |= 1;
			position.active = newActive;
			return true;
		}

		// FUNCTION: ENGINE 0x108519C0
		bool ScriptedCamera::BindLookAt(HandleBase object, const char* partName,
			const math::Vector* newOffset, unsigned int newMode, bool newActive)
		{
			if (!lookAt.Bind(object, core::Name<core::CaseSensitiveKey>(partName, 1)))
			{
				return false;
			}
			if (newMode <= 3)
			{
				lookAt.orientMode = newMode;
				lookAt.offset.x = newOffset->x;
				lookAt.offset.y = newOffset->y;
				lookAt.offset.z = newOffset->z;
			}
			pending |= 2;
			lookAt.active = newActive;
			return true;
		}

		// FUNCTION: ENGINE 0x10851A30
		bool ScriptedCamera::BindPositionNamed(HandleBase object, core::Name<core::CaseSensitiveKey> partName,
			const math::Vector* newOffset, unsigned int newMode, bool newActive)
		{
			if (!position.Bind(object, partName))
			{
				return false;
			}
			if (newMode <= 3)
			{
				position.orientMode = newMode;
				position.offset.x = newOffset->x;
				position.offset.y = newOffset->y;
				position.offset.z = newOffset->z;
			}
			pending |= 4;
			position.active = newActive;
			unknownDC = true;
			return true;
		}

		// FUNCTION: ENGINE 0x10851AA0
		bool ScriptedCamera::LoadAnimation(const char* name)
		{
			content::ObjectName animationName(name, 1);
			content::ObjectName empty((const char*)0, 1);
			if (animationName == empty)
			{
				return false;
			}
			pure3d::Animation* found = content::gRootInventory->Find<pure3d::Animation>(animationName);
			if (found == 0)
			{
				return false;
			}
			return SetAnimation(found);
		}
		// FUNCTION: ENGINE 0x108510D0
		bool ScriptedCamera::SetAnimation(pure3d::Animation* newAnimation)
		{
			if (newAnimation == 0)
			{
				return false;
			}
			core::RefAssign(animation, newAnimation);
			core::RefAssign(controller, new pure3d::CameraAnimationController());
			core::RefAssign(animationCamera, new pure3d::Camera());
			if (animation == 0 || controller == 0 || animationCamera == 0)
			{
				core::SafeRelease(animation);
				core::SafeRelease(controller);
				core::SafeRelease(animationCamera);
				return false;
			}
			animationCamera->SetAspect(16.0f / 9.0f, 0);
			controller->SetAnimation(animation, 0.0f, 0.0f);
			controller->SetCamera(animationCamera);
			controller->SetCycleMode(0);
			controller->SetLoop(animation->mFlag0 == false);
			animationCamera->SetNearPlane(0.5f);
			animationCamera->SetFarPlane(10000.0f);
			animationCamera->SetWindow(false, 0.0f, 0.0f, 0.0f, 0.0f, false);
			target.Identity();
			pending |= 0x40;
			return true;
		}
		// FUNCTION: ENGINE 0x10851B20
		// EQUIVALENT: the look-at point of the first branch: the engine loads the rows of the view and the constant in
		// another order and uses other xmm registers for the same products and sums
		void ScriptedCamera::UpdateTracks(float newTime, bool update)
		{
			if (unknownDC)
			{
				math::Matrix* current = &view;
				position.Evaluate(newTime, update, current);
				current->SetTranslation(position.position);
				math::Vector origin;
				origin.x = current->m[3][0];
				origin.y = current->m[3][1];
				origin.z = current->m[3][2];
				math::Vector forward;
				forward.x = current->m[2][0] * 3.0f;
				forward.y = current->m[2][1] * 3.0f;
				forward.z = current->m[2][2] * 3.0f;
				lookAt.position.Add(origin, forward);
				return;
			}
			position.Evaluate(newTime, update, 0);
			lookAt.Evaluate(newTime, update, 0);
			if (position.active || lookAt.active || update)
			{
				math::Vector direction;
				direction.Sub(lookAt.position, position.position);
				if (direction.IsZero())
				{
					direction.x = 0.0f;
					direction.y = 0.0f;
					direction.z = 1.0f;
				}
				view.Identity();
				view.SetBasis(direction, up);
				view.SetTranslation(position.position);
			}
		}
		// FUNCTION: ENGINE 0x10850A60
		bool ScriptedCamera::SetPlayback(float first, float last, float frame, bool newUnknown55,
			bool newUnknown56, int loopMode)
		{
			if (animation == 0 || controller == 0 || animationCamera == 0)
			{
				return false;
			}
			bool reversed = false;
			if (first >= 0.0f || last >= 0.0f)
			{
				if (0.0f > first)
				{
					first = 0.0f;
				}
				if (0.0f > last)
				{
					last = animation->numFrames;
				}
				if (last > first)
				{
					controller->SetFrameRange(first, last);
				}
				else
				{
					reversed = true;
					controller->SetFrameRange(last, first);
				}
				controller->SetStartFrame(first);
			}
			controller->SetFrame(frame);
			bool loop = loopMode == 2 || (loopMode == 0 && animation->mFlag0);
			controller->SetCycleMode(reversed ? 3 : 2);
			controller->SetLoop(!loop);
			unknown55 = newUnknown55;
			unknown56 = newUnknown56;
			return true;
		}

		// FUNCTION: ENGINE 0x10850C20
		// EQUIVALENT: the engine reads the aspect ratio of the pure3d camera again from memory for the call's argument,
		// ours keeps the first load in a register and spills it (one more word of locals); the jump table and the case
		// table behind the code are the same, 76.1 %
		bool ScriptedCamera::Start()
		{
			switch (pending)
			{
			case 3:
			case 4:
			case 0x12:
			case 0x21:
			case 0x30:
				mode = 1;
				break;
			case 0x40:
				mode = 2;
				break;
			case 0x43:
			case 0x44:
			case 0x52:
			case 0x61:
			case 0x70:
				mode = 3;
				break;
			default:
				return false;
			}
			unknown4C = false;
			unknown4D = false;
			if (pending & 0x74)
			{
				unknown4C = true;
			}
			else
			{
				unknown4D = true;
			}
			if ((position.active && (pending & 5)) || (lookAt.active && (pending & 2)))
			{
				unknown4D = true;
			}
			unknown4E = true;
			camera->SetOrthographic(unknown57);
			camera->SetWindow(&window);
			if (unknownD8 == 0.0f)
			{
				unknownD8 = unknown57 ? 100.0f : 1.5707964f;
			}
			float vertical = unknownD8;
			float horizontal = unknownD8;
			if (!unknown57 && (flags & 1))
			{
				pure3d::Camera* view = camera;
				if (view->unknown1C != 16.0f / 9.0f)
				{
					pure3d::ConvertFov(horizontal, 16.0f / 9.0f, view->unknown1C, &vertical, &horizontal);
				}
			}
			camera->SetFov(vertical);
			time = 0.0f;
			unknown50 = -1.0f;
			return true;
		}
		// FUNCTION: ENGINE 0x10851CA0
		// NONMATCHING: the engine builds the mirrored view of the last case from rows copied by out-of-line Vector4 and
		// Matrix copy constructors (0x1005FFF0, 0x10071800) and keeps different values in registers, 11.2 %
#ifdef NONMATCHING
		void ScriptedCamera::Update(float delta, float timeValue, int flags)
		{
			if (camera == 0)
			{
				return;
			}
			if (mode == 0)
			{
				math::Vector eye(0.0f, 10.0f, 0.0f);
				camera->SetView(&eye, math::Vector(0.0f, 0.0f, 1.0f), math::Vector(0.0f, 1.0f, 0.0f));
				focusDistance = 1.0f;
				return;
			}
			unsigned short eventFlags = (unsigned short)flags;
			if (eventFlags == 1)
			{
				time += delta;
				finished = false;
				if (!unknown4E && !unknown4C)
				{
					return;
				}
			}
			else if (eventFlags == 0x80)
			{
				if (!unknown4D)
				{
					return;
				}
			}
			switch (mode)
			{
			case 1:
				{
					UpdateTracks(time, unknown4E);
					camera->SetMatrix(view);
					float dx = lookAt.position.x - position.position.x;
					float dy = lookAt.position.y - position.position.y;
					float dz = lookAt.position.z - position.position.z;
					float length = (float)sqrt(dx * dx + dy * dy + dz * dz);
					if (length > 0.0f)
					{
						float distance = view.m[2][0] * dx + view.m[2][2] * dz + view.m[2][1] * dy;
						if (distance - 0.1f < 0.0f)
						{
							distance = 0.1f;
						}
						if (distance - 1000.0f >= 0.0f)
						{
							distance = 1000.0f;
						}
						focusDistance = distance;
					}
					else
					{
						focusDistance = 1.0f;
					}
					unknown4E = false;
					return;
				}
			case 2:
			case 3:
				break;
			default:
				unknown4E = false;
				return;
			}
			if (mode == 3)
			{
				UpdateTracks(time, unknown4E);
			}
			if (eventFlags == 1 && controller != 0)
			{
				finished = false;
				controller->Advance(delta * 1000.0f, true);
				float frame = controller->GetFrame();
				float previousFrame = unknown50;
				if (previousFrame >= choreo::gZero)
				{
					finished = controller->IsFinished(previousFrame, frame);
				}
				unknown50 = frame;
			}
			if (animationCamera != 0)
			{
				target = *animationCamera->GetWorldMatrix();
				float zero = math::WORLD_MIN;
				if (unknown55)
				{
					target.m[0][0] = zero - target.m[0][0];
					target.m[0][2] = zero - target.m[0][2];
					target.m[1][0] = zero - target.m[1][0];
					target.m[1][2] = zero - target.m[1][2];
					target.m[2][0] = zero - target.m[2][0];
					target.m[2][2] = zero - target.m[2][2];
					target.m[3][0] = zero - target.m[3][0];
					target.m[3][2] = zero - target.m[3][2];
				}
				if (unknown56)
				{
					target.m[1][0] = zero - target.m[1][0];
					target.m[2][0] = zero - target.m[2][0];
					target.m[3][0] = zero - target.m[3][0];
					target.m[0][1] = zero - target.m[0][1];
					target.m[0][2] = zero - target.m[0][2];
					target.m[0][3] = zero - target.m[0][3];
				}
				if (flags & 1)
				{
					camera->SetFovHorizontal(animationCamera->unknown18);
				}
				else
				{
					camera->SetFov(animationCamera->fov);
				}
				camera->SetNearPlane(animationCamera->minZ);
				camera->SetFarPlane(animationCamera->maxZ);
				if (animationCamera->window.enabled)
				{
					camera->SetWindow(&animationCamera->window);
				}
				float distance = 1.0f;
				if (mode == 3)
				{
					math::Vector away(zero - target.m[3][0], zero - target.m[3][1], zero - target.m[3][2]);
					float length = away.Normalize();
					float dot = target.m[2][2] * away.z + target.m[2][1] * away.y + target.m[2][0] * away.x;
					if (dot > 0.707f)
					{
						distance = dot * length;
					}
					else
					{
						distance = 2.0f;
					}
				}
				focusDistance = distance;
			}
			math::Matrix final(target);
			if (mode == 3)
			{
				// The view with its X and Z axes mirrored
				float zero = math::WORLD_MIN;
				math::Matrix mirrored;
				mirrored.m[0][0] = zero - view.m[0][0];
				mirrored.m[0][1] = zero - view.m[0][1];
				mirrored.m[0][2] = zero - view.m[0][2];
				mirrored.m[0][3] = zero - view.m[0][3];
				mirrored.m[1][0] = view.m[1][0];
				mirrored.m[1][1] = view.m[1][1];
				mirrored.m[1][2] = view.m[1][2];
				mirrored.m[1][3] = view.m[1][3];
				mirrored.m[2][0] = zero - view.m[2][0];
				mirrored.m[2][1] = zero - view.m[2][1];
				mirrored.m[2][2] = zero - view.m[2][2];
				mirrored.m[2][3] = zero - view.m[2][3];
				mirrored.m[3][0] = view.m[3][0];
				mirrored.m[3][1] = view.m[3][1];
				mirrored.m[3][2] = view.m[3][2];
				mirrored.m[3][3] = view.m[3][3];
				final.Multiply(final, mirrored);
				camera->SetMatrix(final);
			}
			else
			{
				camera->SetMatrix(target);
			}
			unknown4E = false;
		}
#endif
	}
}

// Kept copies (template instances of this unit):
// FUNCTION: ENGINE 0x10850F20
