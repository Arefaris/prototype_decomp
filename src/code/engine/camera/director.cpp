#include "code/engine/camera/camera.h"
#include "code/engine/camera/cameramessages.h"
#include "code/engine/camera/cinematographer.h"
#include "code/engine/camera/director.h"
#include "code/math/matrix.h"

namespace engine
{
	namespace camera
	{
		// FUNCTION: ENGINE 0x107DD9F0
		inline CameraResetMessage::CameraResetMessage() : IntrusiveMessage(sizeof(CameraResetMessage), 2)
		{
		}

		// FUNCTION: ENGINE 0x107DDA20
		inline CameraCutMessage::CameraCutMessage() : IntrusiveMessage(sizeof(CameraCutMessage), 3)
		{
		}

		// FUNCTION: ENGINE 0x107DDA70
		int Director::GetMaxControllerIndex() const
		{
			return maxControllerIndex;
		}

		// FUNCTION: ENGINE 0x107DDA80
		void Cinematographer::SetSlot(int value)
		{
			slot = value;
		}

		// FUNCTION: ENGINE 0x107DDAA0
		void Cinematographer::SetId(int value)
		{
			id = value;
		}

		// FUNCTION: ENGINE 0x107DDAB0
		int Cinematographer::GetId() const
		{
			return id;
		}

		// FUNCTION: ENGINE 0x107DDAC0
		int Camera::GetPlayerIndex() const
		{
			return playerIndex;
		}

		// FUNCTION: ENGINE 0x107DDAD0
		bool Camera::IsActive() const
		{
			return active;
		}

		// FUNCTION: ENGINE 0x107DDAE0
		void Camera::SetUnknown7AD(bool value)
		{
			unknown7AD = value;
		}

		// FUNCTION: ENGINE 0x107DDB30
		void Director::Shutdown()
		{
			if (sDirector != 0)
			{
				delete sDirector;
				sDirector = 0;
			}
		}

		// FUNCTION: ENGINE 0x107DDB70
		Director* Director::Get()
		{
			return sDirector;
		}

		// FUNCTION: ENGINE 0x107DDCD0
		void Director::Reset()
		{
			for (int i = 0; i <= maxControllerIndex; i++)
			{
				Cinematographer* controller = controllers.begin[i];
				if (controller != 0)
				{
					controller->Reset();
				}
			}
			int count = cameras.Size();
			for (int i = 0; i < count; i++)
			{
				Camera* camera = cameras.begin[i];
				if (camera != 0)
				{
					camera->Reset();
				}
			}
			CameraResetMessage message;
			SendMessage(&message, &sResetListeners);
			SendMessage(&message, &sResetListeners2);
		}

		// FUNCTION: ENGINE 0x107DDD70
		// EQUIVALENT: identical code except the stack slot of the message: the engine builds it over the dead argument
		// slots, our build over the dead copy of the time info (98.6 %)
		void Director::Update(int unused1, int unused2, float delta, int flags)
		{
			FrameTime* frame = GetFrameTime();
			TimeInfo info = frame->info;
			for (int i = 0; i <= maxControllerIndex; i++)
			{
				Cinematographer* controller = controllers.begin[i];
				if (controller != 0 && controller->enabled && controller->GetType() != 2)
				{
					controller->Update(delta, info.time, flags);
				}
			}
			for (int i = 0; i <= maxControllerIndex; i++)
			{
				Cinematographer* controller = controllers.begin[i];
				if (controller != 0 && controller->enabled && controller->GetType() == 2)
				{
					controller->Update(delta, info.time, flags);
				}
			}
			int count = cameras.Size();
			bool cut = false;
			for (int i = 0; i < count; i++)
			{
				Camera* camera = cameras.begin[i];
				if (camera != 0 && camera->active)
				{
					camera->Update(delta, info.time, flags);
					if (camera->cut)
					{
						cut = true;
					}
				}
			}
			if (cut && (short)flags == 1)
			{
				CameraCutMessage message;
				BroadcastMessage(&message);
			}
		}

		// FUNCTION: ENGINE 0x107DDEE0
		void Director::UpdateCameras(float a, float b, int flags)
		{
			int count = cameras.Size();
			for (int i = 0; i < count; i++)
			{
				Camera* camera = cameras.begin[i];
				if (camera != 0 && camera->active)
				{
					camera->Update(0.0f, 0.0f, 0x200);
				}
			}
		}

		// FUNCTION: ENGINE 0x107DDF30
		void Director::AddController(Cinematographer* controller)
		{
			int count = controllers.Size();
			int index = -1;
			for (int i = 0; i < count; i++)
			{
				if (controllers.begin[i] == 0)
				{
					index = i;
					break;
				}
			}
			controller->slot = index;
			controller->id = nextControllerId++;
			controllers.begin[index] = controller;
			if (index > maxControllerIndex)
			{
				maxControllerIndex = index;
			}
		}

		// FUNCTION: ENGINE 0x107DDF80
		void Director::RemoveController(Cinematographer* controller)
		{
			int index = controller->slot;
			controllers.begin[index] = 0;
			if (index == maxControllerIndex)
			{
				while (maxControllerIndex >= 0 && controllers.begin[maxControllerIndex] == 0)
				{
					maxControllerIndex--;
				}
			}
		}

		// FUNCTION: ENGINE 0x107DDFC0
		bool Director::HasController(int type, int owner) const
		{
			for (int i = 0; i <= maxControllerIndex; i++)
			{
				Cinematographer* controller = controllers.begin[i];
				if (controller != 0 && controller->owner == owner && controller->GetType() == type)
				{
					return true;
				}
			}
			return false;
		}

		// FUNCTION: ENGINE 0x107DE010
		bool Director::HasCamera(int playerIndex, int kind) const
		{
			int count = cameras.Size();
			for (int i = 0; i < count; i++)
			{
				Camera* camera = cameras.begin[i];
				if (camera != 0 && camera->kind == kind && camera->playerIndex == playerIndex)
				{
					return true;
				}
			}
			return false;
		}

		// FUNCTION: ENGINE 0x107DE060
		void Director::SetCamera(Camera* camera)
		{
			cameras.begin[camera->playerIndex + camera->kind * 2] = camera;
		}

		// FUNCTION: ENGINE 0x107DE080
		void Director::ClearCamera(Camera* camera)
		{
			cameras.begin[camera->playerIndex + camera->kind * 2] = 0;
			playerCamera[camera->playerIndex] = -1;
		}

		// FUNCTION: ENGINE 0x107DE0B0
		Camera* Director::GetCamera(int playerIndex, unsigned int kind) const
		{
			if (playerIndex >= 0 && playerIndex < sPlayerCount && kind <= 1)
			{
				return cameras.begin[playerIndex * 2 + kind];
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x107DE0E0
		void Director::StartTransition(int type, float time, int owner, unsigned int kind)
		{
			for (int i = 0; i <= maxControllerIndex; i++)
			{
				Cinematographer* controller = controllers.begin[i];
				if (controller != 0 && controller->owner == owner && controller->GetType() == type)
				{
					Camera* camera = GetCamera(owner, kind);
					if (camera != 0)
					{
						camera->StartTransition((int)controller, time);
					}
					return;
				}
			}
		}

		// FUNCTION: ENGINE 0x107DE150
		// EQUIVALENT: byte-identical except a 2-byte nop our compiler puts before the loop head (the engine's is unpadded)
		void Director::StartTransition(const core::Name<core::CaseSensitiveKey>& name, float time, unsigned int kind, int owner)
		{
			Cinematographer* found = 0;
			int last = maxControllerIndex;
			int i = 0;
			if (i <= last)
			{
				Cinematographer** slot = controllers.begin;
				do
				{
					Cinematographer* controller = *slot;
					if (controller != 0 && controller->owner == owner && controller->GetName() == name)
					{
						found = controller;
						break;
					}
					i++;
					slot++;
				}
				while (i <= last);
			}
			GetCamera(owner, kind)->StartTransition((int)found, time);
		}

		// FUNCTION: ENGINE 0x107DE210
		void Director::SetCameraUnknown7A5(int playerIndex, bool value)
		{
			Camera* camera = GetCamera(playerIndex, 0);
			if (camera != 0)
			{
				camera->SetUnknown7A5(value);
			}
		}

		// FUNCTION: ENGINE 0x107DE230
		void Director::SetCameraUnknown7AD(int playerIndex, bool value)
		{
			Camera* camera = GetCamera(playerIndex, 0);
			if (camera != 0)
			{
				camera->unknown7AD = value;
			}
		}

		// FUNCTION: ENGINE 0x107DE250
		Cinematographer* Director::FindController(int type, int owner) const
		{
			for (int i = 0; i <= maxControllerIndex; i++)
			{
				Cinematographer* controller = controllers.begin[i];
				if (controller != 0 && controller->owner == owner && controller->GetType() == type)
				{
					return controller;
				}
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x107DE2A0
		Cinematographer* Director::FindController(core::Name<core::CaseSensitiveKey> name) const
		{
			int last = maxControllerIndex;
			int i = 0;
			if (i <= last)
			{
				Cinematographer** slot = controllers.begin;
				do
				{
					Cinematographer* controller = *slot;
					if (controller != 0 && controller->GetName() == name)
					{
						return controller;
					}
					i++;
					slot++;
				}
				while (i <= last);
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x107DE330
		void Director::NotifyControllers(int param, int owner)
		{
			for (int i = 0; i <= maxControllerIndex; i++)
			{
				Cinematographer* controller = controllers.begin[i];
				if (controller != 0 && controller->owner == owner)
				{
					controller->OnEvent(param);
				}
			}
		}

		// FUNCTION: ENGINE 0x107DE370
		void Director::NotifyControllersOfKind(int kind, float param)
		{
			for (int i = 0; i <= maxControllerIndex; i++)
			{
				Cinematographer* controller = controllers.begin[i];
				if (controller != 0 && controller->kind == kind && controller->IsRunning())
				{
					controller->OnKindEvent(param);
				}
			}
		}

		// FUNCTION: ENGINE 0x107DE3C0
		void Director::NotifyController(int param, int type, int owner)
		{
			FindController(type, owner)->OnEvent(param);
		}

		// FUNCTION: ENGINE 0x107DE3E0
		void Director::NotifyController(int param, core::Name<core::CaseSensitiveKey> name, int unused)
		{
			FindController(name)->OnEvent(param);
		}

		// FUNCTION: ENGINE 0x107DE410
		Cinematographer* Director::GetController(int slot, int id) const
		{
			if (slot == -1)
			{
				return 0;
			}
			Cinematographer* controller = controllers.begin[slot];
			if (controller == 0 || controller->id != id)
			{
				return 0;
			}
			return controller;
		}

		// FUNCTION: ENGINE 0x107DE440
		int Director::ActivateCamera(int playerIndex, int kind)
		{
			int i;
			for (i = (unsigned int)cameras.Size() / 2 - 1; i >= 0; i--)
			{
				Camera* camera = GetCamera(i, kind);
				if (camera != 0 && camera->active && camera->enabled)
				{
					camera->Activate(false);
					break;
				}
			}
			GetCamera(playerIndex, kind)->Activate(true);
			return i;
		}

		// FUNCTION: ENGINE 0x107DE4B0
		bool Director::NextActiveCamera(int* index, int kind)
		{
			int count = (unsigned int)cameras.Size() >> 1;
			for (++*index; *index < count; ++*index)
			{
				Camera* camera = GetCamera(*index, kind);
				if (camera != 0 && camera->active && camera->enabled)
				{
					if (playerCamera[kind] < 0)
					{
						playerCamera[kind] = *index;
					}
					return true;
				}
			}
			*index = -1;
			return false;
		}

		// FUNCTION: ENGINE 0x107DE530
		void Director::OnCameraDisabled(Camera* camera)
		{
			for (unsigned int i = 0; i < (unsigned int)cameras.Size(); i++)
			{
				if (cameras.begin[i] == camera)
				{
					int kind = i & 1;
					playerCamera[kind] = -1;
					NextActiveCamera(&playerCamera[kind], kind);
					return;
				}
			}
		}

		// FUNCTION: ENGINE 0x107DE660
		Cinematographer* Director::GetCameraController(int playerIndex, unsigned int kind) const
		{
			Camera* camera = GetCamera(playerIndex, kind);
			return Get()->GetController(camera->controller);
		}

		// FUNCTION: ENGINE 0x107DE690
		CameraTarget* Director::GetCameraTarget(int playerIndex, unsigned int kind) const
		{
			Camera* camera = GetCamera(playerIndex, kind);
			if (camera != 0)
			{
				return camera->target;
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x107DE6B0
		const math::Matrix* Director::GetCameraMatrix(int playerIndex, unsigned int kind) const
		{
			Camera* camera = GetCamera(playerIndex, kind);
			if (camera != 0)
			{
				return camera->target->MatrixAt90();
			}
			return &math::Matrix::IDENTITY;
		}

		// FUNCTION: ENGINE 0x107DE6E0
		int Director::GetCameraUnknown40(int playerIndex, unsigned int kind) const
		{
			Camera* camera = GetCamera(playerIndex, kind);
			if (camera != 0)
			{
				return camera->unknown40;
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x107DE700
		int Director::GetCameraUnknown44(int playerIndex, unsigned int kind) const
		{
			Camera* camera = GetCamera(playerIndex, kind);
			if (camera != 0)
			{
				return camera->unknown44;
			}
			return 0;
		}
	}
}
