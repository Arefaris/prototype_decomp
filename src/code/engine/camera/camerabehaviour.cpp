#include "code/engine/camera/camerabehaviour.h"
#include "code/engine/camera/cameramessages.h"
#include "code/engine/camera/director.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/math/vector4.h"
#include "code/math/worldbounds.h"
#include <new>
#include "code/pure3d/camera.h"

namespace engine
{
	extern content::ObjectName gTransformName;

	namespace camera
	{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

		static inline void NegateRow(float* out, const float* in)
		{
			float x = math::WORLD_MIN - in[0];
			float y = math::WORLD_MIN - in[1];
			float z = math::WORLD_MIN - in[2];
			float w = math::WORLD_MIN - in[3];
			out[0] = x;
			out[1] = y;
			out[2] = z;
			out[3] = w;
		}

		// FUNCTION: ENGINE 0x108504A0
		content::ClassInfo* CameraBehaviour::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::camera::CameraBehaviour";
			sInfo.code = "pn";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x108504E0
		content::ClassInfo* CameraBehaviour::GetClassInfoV2()
		{
			static content::ClassInfo sInfo;
			sInfo.name = "engine::camera::CameraBehaviour";
			sInfo.version = 2;
			sInfo.code = "p";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x108508D0
		CameraBehaviour::CameraBehaviour(GameObject* newOwner) : Behaviour(newOwner)
		{
			camera = 0;
			Listen2(0x80, true);
			Listen(0xc, true);
			Listen(0x17, true);
			core::HeapScope scope(sCameraHeap);
			owner->SetAttributeAndGet<math::Matrix>(gTransformName, math::Matrix::IDENTITY, false);
		}

		// FUNCTION: ENGINE 0x10850520
		// FUNCTION: ENGINE 0x10850630
		CameraBehaviour::~CameraBehaviour()
		{
			if (camera != 0)
			{
				delete camera;
			}
		}

		// FUNCTION: ENGINE 0x10850540
		void CameraBehaviour::Slot1()
		{
			camera->Register();
			owner->SetActive(true);
			GameObjectHandle handle = GetHandle(owner);
			handle.RouterRemove(sResetListeners);
			camera->unknown18 = handle;
		}

		// FUNCTION: ENGINE 0x10850590
		void CameraBehaviour::OnPostedMessage(Message* message)
		{
			if (message->type == 0xc && message->id == 0)
			{
				((GetCameraMessage*)message)->camera = camera;
			}
		}

		// FUNCTION: ENGINE 0x108505B0
		void CameraBehaviour::SetCamera(Camera* newCamera)
		{
			if (camera != newCamera)
			{
				if (camera != 0)
				{
					delete camera;
				}
				camera = newCamera;
			}
		}

		// FUNCTION: ENGINE 0x10850650
		void CameraBehaviour::OnMessage(Message* message)
		{
			if (message->type == 0xc)
			{
				switch ((unsigned short)message->id)
				{
				case 2:
					owner->transform->Get().Identity();
					break;
				}
			}
		}

		// FUNCTION: ENGINE 0x10850680
		// EQUIVALENT: the engine computes the four negated components of the first row in order and keeps the constant in a register for the third row; ours schedules the x component last and loads the constant again; 73.5 %
		void CameraBehaviour::Update(float dt, unsigned short mask)
		{
			const float* in = camera->camera->GetWorldFloats();
			float* out = (float*)&owner->transform->Get();
			float zero = math::WORLD_MIN;
			float a0 = zero - in[0];
			float a1 = zero - in[1];
			float a2 = zero - in[2];
			float a3 = zero - in[3];
			out[0] = a0;
			out[1] = a1;
			out[2] = a2;
			out[3] = a3;
			out[4] = in[4];
			out[5] = in[5];
			out[6] = in[6];
			out[7] = in[7];
			float c0 = zero - in[8];
			float c1 = zero - in[9];
			float c2 = zero - in[10];
			float c3 = zero - in[11];
			out[8] = c0;
			out[9] = c1;
			out[10] = c2;
			out[11] = c3;
			out[12] = in[12];
			out[13] = in[13];
			out[14] = in[14];
			out[15] = in[15];
		}

		// FUNCTION: ENGINE 0x10850820
		content::MemberList* CameraBehaviour::GetMembers()
		{
			static content::MemberList sList;
			sList.baseType = content::GetClassMetaType<Behaviour>();
			static content::BaseClassCasterImpl<Behaviour, CameraBehaviour> sCaster;
			sList.baseCaster = &sCaster;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetObjectMetaTypeCopy<Camera>("pn"), ENGINE_OFFSET(CameraBehaviour, camera), "camera" }
			};
			sList.members = sMembers;
			sList.count = 1;
			return &sList;
		}
	}
}

// Kept copies (template instances of this unit):
// FUNCTION: ENGINE 0x108505E0
// FUNCTION: ENGINE 0x108505F0
// FUNCTION: ENGINE 0x10850600
// FUNCTION: ENGINE 0x10850740
// FUNCTION: ENGINE 0x10850750
// FUNCTION: ENGINE 0x108507D0
