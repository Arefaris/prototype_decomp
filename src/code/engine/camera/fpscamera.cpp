#include "code/engine/camera/fpscamera.h"
#include "code/engine/firstpersoncontrolbehaviour.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/driving/carattributes.h"
#include "code/pure3d/camera.h"

namespace engine
{
	namespace camera
	{

		// FUNCTION: ENGINE 0x10915450
		content::ClassInfo* FPSCamera::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::camera::FPSCamera";
			sInfo.code = "pn";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x10915490
		FPSCamera::FPSCamera()
		{
		}

		// FUNCTION: ENGINE 0x109154B0
		int FPSCamera::GetType()
		{
			return 4;
		}

		// FUNCTION: ENGINE 0x109155A0
		// NONMATCHING: the engine keeps the handle test and the object lookup as two separate table lookups, ours merges them, best 25.8 %
#ifdef NONMATCHING
		void FPSCamera::Update(float delta, float time, int eventFlags)
		{
			if ((unsigned short)eventFlags != 0x80)
			{
				return;
			}
			GameObjectHandle target = (GameObjectHandle&)unknown20;
			if (!target.IsValid())
			{
				camera->SetMatrix(math::Matrix::IDENTITY);
				return;
			}
			GameObject* object = ((GameObjectHandle&)unknown20).Get();
			math::Matrix view = math::Matrix::IDENTITY;
			bool fromEyepoint = true;
			math::Matrix* source = 0;
			BaseAttribute* attribute = object->FindAttribute(gEyePointName);
			if (attribute != 0)
			{
				source = &((Attribute<math::Matrix>*)attribute)->value;
			}
			if (source == 0)
			{
				fromEyepoint = false;
				source = &object->transform->value;
			}
			view = *source;
			math::Vector position(view.m[3][0], view.m[3][1], view.m[3][2]);
			float forwardY = position.y - view.m[2][1];
			float forwardZ = position.z - view.m[2][2];
			float forwardX = position.x - view.m[2][0];
			if (!fromEyepoint)
			{
				position.y += driving::gTwo;
				forwardY += driving::gTwo;
			}
			camera->SetView(&position,
				math::Vector(forwardX - position.x, forwardY - position.y, forwardZ - position.z),
				math::Vector(view.m[1][0], view.m[1][1], view.m[1][2]));
		}
#endif

		// FUNCTION: ENGINE 0x10915540
		content::MemberList* FPSCamera::GetMembers()
		{
			static content::MemberList sList;
			sList.baseType = content::GetClassMetaType<Camera>();
			static content::BaseClassCasterImpl<Camera, FPSCamera> sCaster;
			sList.baseCaster = &sCaster;
			return &sList;
		}
	}
}

// Kept copies (template instances of this unit):
// FUNCTION: ENGINE 0x109154E0
// FUNCTION: ENGINE 0x109154F0
