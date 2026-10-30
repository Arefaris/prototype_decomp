#include "code/engine/camera/onfootcamera.h"
#include "code/engine/driving/carattributes.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/math/worldbounds.h"
#include "code/pure3d/camera.h"
#include <math.h>

namespace engine
{
	namespace camera
	{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)
#define ENGINE_NAME_OFFSET(type, member) \
	content::MemberOffset((core::Name<core::CaseSensitiveKey>*)&((type*)0)->member, (int)&((type*)0)->member)

		// FUNCTION: ENGINE 0x109157E0
		content::ClassInfo* OnFootCamera::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::camera::OnFootCamera";
			sInfo.code = "pn";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x10915860
		// EQUIVALENT: the engine stores the vftable after the first float members, ours right behind the base
		// constructor, 54.5 %
		OnFootCamera::OnFootCamera() :
			elevation(driving::gTwo),
			distance(gFifteen),
			lookAhead(driving::gThirty),
			lag(0.0f),
			reverseTargetHeading(false)
		{
		}

		// FUNCTION: ENGINE 0x10915900
		OnFootCamera::~OnFootCamera()
		{
		}

		// FUNCTION: ENGINE 0x109158B0
		int OnFootCamera::GetType()
		{
			return 5;
		}

		// FUNCTION: ENGINE 0x10915A50
		content::MemberList* OnFootCamera::GetMembers()
		{
			static content::MemberList sList;
			sList.baseType = content::GetClassMetaType<Camera>();
			static content::BaseClassCasterImpl<Camera, OnFootCamera> sCaster;
			sList.baseCaster = &sCaster;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetMemberPrimitiveMetaType<OnFootCamera, float, 0>("pn"),
					ENGINE_OFFSET(OnFootCamera, elevation), "elevation" },
				{ content::GetMemberPrimitiveMetaType<OnFootCamera, float, 1>("pn"),
					ENGINE_OFFSET(OnFootCamera, distance), "distance" },
				{ content::GetMemberPrimitiveMetaType<OnFootCamera, float, 2>("pn"),
					ENGINE_OFFSET(OnFootCamera, lookAhead), "lookAhead" },
				{ content::GetMemberPrimitiveMetaType<OnFootCamera, float, 3>("pn"),
					ENGINE_OFFSET(OnFootCamera, lag), "lag" },
				{ content::GetMemberPrimitiveMetaType<OnFootCamera, bool, 0>("pn"),
					ENGINE_OFFSET(OnFootCamera, reverseTargetHeading), "reverseTargetHeading" },
				{ content::GetNameMetaType<OnFootCamera>(true, true, "pn"),
					ENGINE_NAME_OFFSET(OnFootCamera, targetName), "targetName" }
			};
			sList.members = sMembers;
			sList.count = 6;
			return &sList;
		}

		// FUNCTION: ENGINE 0x10915BF0
		// NONMATCHING: the engine copies the heading through a local and mixes x87 and SSE copies, the handle test as in FPSCamera::Update, best 15.4 %
#ifdef NONMATCHING
		void OnFootCamera::Update(float delta, float time, int eventFlags)
		{
			if ((unsigned short)eventFlags != 0x80)
			{
				return;
			}
			GameObjectHandle target = (GameObjectHandle&)unknown20;
			if (!target.IsValid())
			{
				return;
			}
			math::Matrix& transform = target.Get()->transform->value;
			float upX = transform.m[1][0];
			float upY = transform.m[1][1];
			float upZ = transform.m[1][2];
			float faceX = transform.m[2][0];
			float faceY = transform.m[2][1];
			float faceZ = transform.m[2][2];
			focus.x = transform.m[3][0];
			focus.y = transform.m[3][1];
			focus.z = transform.m[3][2];
			if (reverseTargetHeading)
			{
				faceX = math::WORLD_MIN - faceX;
				faceY = math::WORLD_MIN - faceY;
				faceZ = math::WORLD_MIN - faceZ;
			}
			heading.x = faceX;
			heading.y = faceY;
			heading.z = faceZ;
			heading.y = 0.0f;
			if (heading.x * heading.x + heading.y * heading.y + heading.z * heading.z < gThousandth)
			{
				heading.x = upX;
				heading.y = upY;
				heading.z = upZ;
			}
			heading.Normalize();
			if (heading.x * heading.x + heading.y * heading.y + heading.z * heading.z < gThousandth)
			{
				heading.x = 0.0f;
				heading.y = 0.0f;
				heading.z = driving::gOne;
			}
			float back = math::WORLD_MIN - distance;
			float aboveX = elevation * gUpVector.x + heading.x * back + focus.x;
			float aboveY = elevation * gUpVector.y + heading.y * back + focus.y;
			float aboveZ = elevation * gUpVector.z + heading.z * back + focus.z;
			float* current = (float*)((char*)camera + 0x90);
			float moveX = aboveX - current[0x30 / 4];
			float moveY = aboveY - current[0x34 / 4];
			float moveZ = aboveZ - current[0x38 / 4];
			math::Vector position(aboveX, aboveY, aboveZ);
			if (sqrtf(moveX * moveX + moveY * moveY + moveZ * moveZ) <= distance * gThree && lag != 0.0f)
			{
				float blend = lag * delta;
				if (!(blend < driving::gOne))
				{
					blend = driving::gOne;
				}
				position.x = moveX * blend + current[0x30 / 4];
				position.y = moveY * blend + current[0x34 / 4];
				position.z = moveZ * blend + current[0x38 / 4];
			}
			math::Vector look(lookAhead * heading.x + focus.x - position.x, heading.y * lookAhead + focus.y - position.y,
				heading.z * lookAhead + focus.z - position.z);
			look.Normalize();
			camera->SetView(&position, look, gUpVector);
		}
#endif
	}
}

// Kept copies (template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10915820
// FUNCTION: ENGINE 0x109158C0
// FUNCTION: ENGINE 0x109158D0
// FUNCTION: ENGINE 0x10915910
// FUNCTION: ENGINE 0x10915950
// FUNCTION: ENGINE 0x10915990
// FUNCTION: ENGINE 0x109159D0
// FUNCTION: ENGINE 0x10915A10
