#include "code/engine/camera/camera.h"
#include "code/content/metatype.h"
#include "code/core/refptr.h"
#include "code/engine/camera/director.h"
#include "code/math/matrix.h"
#include "code/pure3d/camera.h"

namespace engine
{
	namespace camera
	{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define ENGINE_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

		// FUNCTION: ENGINE 0x1084D870
		ControllerRef::ControllerRef()
		{
			slot = -1;
			id = 0;
		}

		// FUNCTION: ENGINE 0x1084D880
		ControllerRef::ControllerRef(const Camera* camera)
		{
			slot = camera->slot;
			id = camera->id;
		}

		// FUNCTION: ENGINE 0x1084D8A0
		ControllerRef::~ControllerRef()
		{
		}

		// FUNCTION: ENGINE 0x1084D8B0
		void ControllerRef::Set(const Camera* camera)
		{
			slot = camera->slot;
			id = camera->id;
		}

		// FUNCTION: ENGINE 0x1084D9E0
		Camera::Camera()
			: playerIndex(0), camera(0), kind(0), flags(0), unknown28(0.0f), enabled(false), position(math::kZeroVector),
			slot(-1), id(0)
		{
			pure3d::Camera* created = new pure3d::Camera();
			core::RefAssign(camera, created);
			camera->SetNearPlane(0.5f);
			camera->SetFarPlane(10000.0f);
		}

		// FUNCTION: ENGINE 0x1084DAA0
		// FUNCTION: ENGINE 0x1084DB50
		Camera::~Camera()
		{
			Unregister();
			camera->ReleaseThunk();
		}

		// FUNCTION: ENGINE 0x1084D8D0
		void Camera::Register()
		{
			Director* director = Director::Get();
			director->AddController(this);
		}

		// FUNCTION: ENGINE 0x1084D8F0
		void Camera::Unregister()
		{
			Director* director = Director::Get();
			if (director != 0)
			{
				director->RemoveController(this);
			}
		}

		// FUNCTION: ENGINE 0x1084D970
		void Camera::Update(float delta, float time, int flags)
		{
		}

		// FUNCTION: ENGINE 0x1084D910
		int Camera::GetType()
		{
			return 6;
		}

		// FUNCTION: ENGINE 0x1084D920
		void Camera::SetPlayerIndex(int value)
		{
			playerIndex = value;
		}

		// FUNCTION: ENGINE 0x1084D930
		void Camera::OnEvent(int param)
		{
			*(int*)&unknown20 = param;
		}

		// FUNCTION: ENGINE 0x1084D940
		void Camera::SetEnabled(bool value)
		{
			enabled = value;
		}

		// FUNCTION: ENGINE 0x1084D950
		void Camera::OnKindEvent(float param)
		{
			camera->SetAspect(param, (int)(unsigned char)flags & 0xffffff01);
		}

		// FUNCTION: ENGINE 0x1084D980
		void Camera::Reset()
		{
			if (camera != 0)
			{
				camera->SetMatrix(math::Matrix::IDENTITY);
			}
		}

		// FUNCTION: ENGINE 0x1084D7A0
		float Camera::GetFov() const
		{
			return camera->fov * 57.295776f;
		}

		// FUNCTION: ENGINE 0x1084D7B0
		void Camera::SetFov(float degrees)
		{
			camera->SetFov(degrees * 0.017453292f);
		}

		// FUNCTION: ENGINE 0x1084D7D0
		float Camera::GetNearPlane() const
		{
			return camera->minZ;
		}

		// FUNCTION: ENGINE 0x1084D7E0
		void Camera::SetNearPlane(float distance)
		{
			camera->SetNearPlane(distance);
		}

		// FUNCTION: ENGINE 0x1084D800
		float Camera::GetFarPlane() const
		{
			return camera->maxZ;
		}

		// FUNCTION: ENGINE 0x1084D810
		void Camera::SetFarPlane(float distance)
		{
			camera->SetFarPlane(distance);
		}

		// FUNCTION: ENGINE 0x1084D830
		content::ClassInfo* Camera::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::camera::Camera";
			sInfo.code = "pn";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x1084DCC0
		content::MemberList* Camera::GetMembers()
		{
			static content::MemberList sList;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetNameMetaType<Camera>(true, true, "pn"), ENGINE_NAME_OFFSET(Camera, name), "name" },
				{ content::GetMemberPrimitiveMetaType<Camera, int, 0>("pn"), ENGINE_OFFSET(Camera, playerIndex),
					"playerIndex" },
				{ content::GetMemberMetaType<Camera, float, 0>(&Camera::GetFov, &Camera::SetFov, "p"), 0, "fov" },
				{ content::GetMemberMetaType<Camera, float, 1>(&Camera::GetNearPlane, &Camera::SetNearPlane, "pn"), 0,
					"nearPlane" },
				{ content::GetMemberMetaType<Camera, float, 2>(&Camera::GetFarPlane, &Camera::SetFarPlane, "pn"), 0,
					"farPlane" }
			};
			sList.members = sMembers;
			sList.count = 5;
			return &sList;
		}
	}
}

// The getter / setter helper of the reflection, kept as an out-of-line instance
template class PrimitiveMemberGetSetter<engine::camera::Camera, float>;

// Kept copies (template instances of this unit):
// FUNCTION: ENGINE 0x1084D9A0
// FUNCTION: ENGINE 0x1084DAC0
// FUNCTION: ENGINE 0x1084DB00
// FUNCTION: ENGINE 0x1084DB20
// FUNCTION: ENGINE 0x1084DB30
// FUNCTION: ENGINE 0x1084DB70
// FUNCTION: ENGINE 0x1084DBE0
// FUNCTION: ENGINE 0x1084DC50
// FUNCTION: ENGINE 0x1032A380
