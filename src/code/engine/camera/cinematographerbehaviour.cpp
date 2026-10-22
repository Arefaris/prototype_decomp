#include "code/engine/camera/camerabehaviour.h"
#include "code/engine/camera/cameramessages.h"
#include "code/engine/camera/director.h"
#include "code/engine/gameobject/gameobject.h"
#include "code/engine/gameobject/gameobjectsystem.h"
#include "code/math/worldbounds.h"
#include "code/pure3d/camera.h"

namespace engine
{
	extern content::ObjectName gTransformName;

	namespace camera
	{
#define ENGINE_OFFSET(type, member) \
	content::MemberOffset(&((type*)0)->member, (int)&((type*)0)->member)

		// FUNCTION: ENGINE 0x1084FFF0
		content::ClassInfo* CinematographerBehaviour::GetClassInfo()
		{
			static content::ClassInfo sInfo;
			sInfo.version = 1;
			sInfo.name = "engine::camera::CinematographerBehaviour";
			sInfo.code = "pn";
			return &sInfo;
		}

		// FUNCTION: ENGINE 0x10850430
		CinematographerBehaviour::CinematographerBehaviour(GameObject* newOwner) : Behaviour(newOwner)
		{
			cinematographer = 0;
			autoRegister = true;
			Listen2(0x80, true);
			Listen(0xc, true);
			Listen(0x17, true);
			owner->SetAttributeAndGet<math::Matrix>(gTransformName, math::Matrix::IDENTITY, false);
		}

		// FUNCTION: ENGINE 0x10850030
		// FUNCTION: ENGINE 0x10850190
		CinematographerBehaviour::~CinematographerBehaviour()
		{
			if (cinematographer != 0)
			{
				delete cinematographer;
			}
		}

		// FUNCTION: ENGINE 0x10850050
		void CinematographerBehaviour::Slot1()
		{
			if (autoRegister)
			{
				cinematographer->Start();
			}
			owner->SetActive(true);
			GameObjectHandle handle = GetHandle(owner);
			handle.RouterRemove(sResetListeners2);
			*(GameObjectHandle*)((char*)cinematographer + 0x22) = handle;
		}

		// FUNCTION: ENGINE 0x108500A0
		void CinematographerBehaviour::OnPostedMessage(Message* message)
		{
			if (message->type == 0xc)
			{
				switch ((unsigned short)message->id)
				{
				case 1:
					((GetCinematographerMessage*)message)->cinematographer = cinematographer;
					break;
				}
			}
		}

		// FUNCTION: ENGINE 0x108500C0
		void CinematographerBehaviour::SetCinematographer(Cinematographer* newCinematographer)
		{
			if (cinematographer != 0)
			{
				delete cinematographer;
				cinematographer = newCinematographer;
				return;
			}
			cinematographer = newCinematographer;
		}

		// FUNCTION: ENGINE 0x108501B0
		void CinematographerBehaviour::OnMessage(Message* message)
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

		// FUNCTION: ENGINE 0x108501E0
		// EQUIVALENT: the engine computes the four negated components of the first row in order and keeps the constant in a register for the third row; ours schedules the x component last and loads the constant again; 73.5 %
		void CinematographerBehaviour::Update(float dt, unsigned short mask)
		{
			const float* in = ((pure3d::Camera*)cinematographer->unknown44)->GetWorldFloats();
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

		// FUNCTION: ENGINE 0x10850360
		content::MemberList* CinematographerBehaviour::GetMembers()
		{
			static content::MemberList sList;
			sList.baseType = content::GetClassMetaType<Behaviour>();
			static content::BaseClassCasterImpl<Behaviour, CinematographerBehaviour> sCaster;
			sList.baseCaster = &sCaster;
			static content::MemberInfo sMembers[] =
			{
				{ content::GetObjectMetaType<Cinematographer>("pn"), ENGINE_OFFSET(CinematographerBehaviour, cinematographer),
					"cinematographer" },
				{ content::GetMemberPrimitiveMetaType<CinematographerBehaviour, bool, 0>("pn"),
					ENGINE_OFFSET(CinematographerBehaviour, autoRegister), "autoRegister" }
			};
			sList.members = sMembers;
			sList.count = 2;
			return &sList;
		}
	}
}


// Kept copies (template instances of this unit):
// FUNCTION: ENGINE 0x108500F0
// FUNCTION: ENGINE 0x10850100
// FUNCTION: ENGINE 0x10850150
// FUNCTION: ENGINE 0x10850160
// FUNCTION: ENGINE 0x108502A0
// FUNCTION: ENGINE 0x108502E0
// FUNCTION: ENGINE 0x108502F0
// FUNCTION: ENGINE 0x10850310
