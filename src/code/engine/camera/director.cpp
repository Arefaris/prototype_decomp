#include "code/engine/camera/camera.h"
#include "code/engine/camera/cameramessages.h"
#include "code/engine/camera/cinematographer.h"
#include "code/engine/camera/director.h"

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
	}
}
