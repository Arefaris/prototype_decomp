#include "code/engine/camera/camera.h"
#include "code/engine/camera/cameramessages.h"
#include "code/engine/camera/cinematographer.h"
#include "code/engine/camera/director.h"
#include "code/engine/system/enginememory.h"
#include <new>

#include "code/math/matrix.h"

namespace container
{
	// The Director's two arrays instantiate these; the engine kept the copies next to the Director's code. Which
	// instantiation each address holds is a guess (the cameras array is used first). The first one also emits the
	// allocator's inline members (0x107DDBF0 Free, 0x107DDC10 Alloc).
	// FUNCTION: ENGINE 0x107DDBF0
	// FUNCTION: ENGINE 0x107DDC10
	// FUNCTION: ENGINE 0x107DDB90
	// FUNCTION: ENGINE 0x107DDBA0
	// FUNCTION: ENGINE 0x107DDBB0
	// FUNCTION: ENGINE 0x107DE580
	// FUNCTION: ENGINE 0x107DE720
	// FUNCTION: ENGINE 0x107DE770
	// FUNCTION: ENGINE 0x107DE790
	template class ArrayDynamic<engine::camera::Cinematographer*, AllocatorNew>;
	// FUNCTION: ENGINE 0x107DDBC0
	// FUNCTION: ENGINE 0x107DDBD0
	// FUNCTION: ENGINE 0x107DDBE0
	// FUNCTION: ENGINE 0x107DE5D0
	// FUNCTION: ENGINE 0x107DE7C0
	// FUNCTION: ENGINE 0x107DE810
	// FUNCTION: ENGINE 0x107DE830
	template class ArrayDynamic<engine::camera::Camera*, AllocatorNew>;
}

namespace engine
{
	namespace camera
	{
		// Camera::GetName is inline in the header; its kept copy is 0x107DDCB0
		// FUNCTION: ENGINE 0x107DDCB0
		// FUNCTION: ENGINE 0x107DD9D0
		int Camera::IsRunningFlags(unsigned int flags)
		{
			return ~(flags >> 1) & 1;
		}

		// FUNCTION: ENGINE 0x107DD9E0
		int Director::GetCameraIndex(int playerIndex, int kind) const
		{
			return playerIndex * 2 + kind;
		}

		// FUNCTION: ENGINE 0x107DD9F0
		inline CameraResetMessage::CameraResetMessage() : IntrusiveMessage(12, 2)
		{
		}

		// 0x107DDC70 is the compiler's scalar deleting destructor of this class
		// FUNCTION: ENGINE 0x107DDC70
		// FUNCTION: ENGINE 0x107DDA10
		inline CameraResetMessage::~CameraResetMessage()
		{
		}

		// FUNCTION: ENGINE 0x107DDA20
		inline CameraCutMessage::CameraCutMessage() : IntrusiveMessage(12, 3)
		{
		}

		// 0x107DDC90 is the compiler's scalar deleting destructor of this class
		// FUNCTION: ENGINE 0x107DDC90
		// FUNCTION: ENGINE 0x107DDA40
		inline CameraCutMessage::~CameraCutMessage()
		{
		}

		// FUNCTION: ENGINE 0x107DDA50
		void Camera::OnKindEventIfRunning(float param)
		{
			if (IsRunning())
			{
				OnKindEvent(param);
			}
		}

		// FUNCTION: ENGINE 0x107DDA70
		int Director::GetMaxControllerIndex() const
		{
			return maxControllerIndex;
		}

		// FUNCTION: ENGINE 0x107DDA80
		void Camera::SetSlot(int value)
		{
			slot = value;
		}

		// FUNCTION: ENGINE 0x107DDA90
		int Camera::GetSlot() const
		{
			return slot;
		}

		// FUNCTION: ENGINE 0x107DDAA0
		void Camera::SetId(int value)
		{
			id = value;
		}

		// FUNCTION: ENGINE 0x107DDAB0
		int Camera::GetId() const
		{
			return id;
		}

		// FUNCTION: ENGINE 0x107DDAC0
		int Cinematographer::GetType() const
		{
			return type;
		}

		// FUNCTION: ENGINE 0x107DDAD0
		bool Cinematographer::IsActive() const
		{
			return active;
		}

		// FUNCTION: ENGINE 0x107DDAE0
		void Cinematographer::SetUnknown7AD(bool value)
		{
			unknown7AD = value;
		}

		// FUNCTION: ENGINE 0x107DDAF0
		math::Matrix* Cinematographer::GetTargetMatrix() const
		{
			return target->MatrixAt90();
		}

		// FUNCTION: ENGINE 0x107DDB00
		CameraSystemConfig::CameraSystemConfig()
		{
			heap = 0;
			unknown4 = 1;
			unknown8 = 1;
			controllerCount = 0x20;
			playerCount = 8;
		}

		// FUNCTION: ENGINE 0x107DDB50
		void Director::OnDBSlot0(int a, int b)
		{
		}

		// FUNCTION: ENGINE 0x107DDB60
		void Director::OnDBSlot1(int a, int b)
		{
		}

		// FUNCTION: ENGINE 0x107DE860
		Director::Director()
			: cameras(sPlayerCount * 2), controllers(sControllerCount)
		{
			maxControllerIndex = -1;
			nextControllerId = 0;
			int cameraCount = cameras.Size();
			sDirector = this;
			for (int i = 0; i < cameraCount; i++)
			{
				cameras.begin[i] = 0;
			}
			int controllerCount = controllers.Size();
			for (int i = 0; i < controllerCount; i++)
			{
				controllers.begin[i] = 0;
			}
			playerCamera[0] = -1;
			playerCamera[1] = -1;
			core::Name<core::CaseSensitiveKey> name("ConsoleAspectRatio", 0);
			GameDatabase* database = gGameDatabase;
			float ratio = gDisplay->GetAspectRatio();
			database->AddFloatSubject(name, 1, ratio, DBSubjectInfo(false, 1, -1));
			database->AddObserver(name, this, 0, 0);
		}

		// 0x107DEAA0 is the compiler's scalar deleting destructor of this class
		// FUNCTION: ENGINE 0x107DEAA0
		// FUNCTION: ENGINE 0x107DE990
		// EQUIVALENT: 93.7 %; in the last inlined member destructor the engine reuses the this register (esi) for the
		// pointer being freed, our build takes eax
		Director::~Director()
		{
			cameras.Clear();
			controllers.Clear();
			sDirector = 0;
			core::Name<core::CaseSensitiveKey> name("ConsoleAspectRatio", 0);
			GameDatabase* database = gGameDatabase;
			database->RemoveObserver(name, this);
			database->ReleaseSubject(name);
		}

		// FUNCTION: ENGINE 0x107DEA30
		bool InitCameraSystem(const CameraSystemConfig* config)
		{
			sCameraHeap = config->heap;
			sUnknown60 = config->unknown4;
			sUnknown64 = config->unknown8;
			sControllerCount = config->controllerCount;
			sPlayerCount = config->playerCount;
			void* memory = operator new(sizeof(Director), sCameraHeap);
			if (memory != 0)
			{
				new (memory) Director();
			}
			InitMessageListeners(&sResetListeners2, sPlayerCount * 2);
			InitMessageListeners(&sResetListeners, sControllerCount);
			return true;
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
				Camera* controller = controllers.begin[i];
				if (controller != 0)
				{
					controller->Reset();
				}
			}
			int count = cameras.Size();
			for (int i = 0; i < count; i++)
			{
				Cinematographer* camera = cameras.begin[i];
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
				Camera* controller = controllers.begin[i];
				if (controller != 0 && controller->enabled && controller->GetType() != 2)
				{
					controller->Update(delta, info.time, flags);
				}
			}
			for (int i = 0; i <= maxControllerIndex; i++)
			{
				Camera* controller = controllers.begin[i];
				if (controller != 0 && controller->enabled && controller->GetType() == 2)
				{
					controller->Update(delta, info.time, flags);
				}
			}
			int count = cameras.Size();
			bool cut = false;
			for (int i = 0; i < count; i++)
			{
				Cinematographer* camera = cameras.begin[i];
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
				Cinematographer* camera = cameras.begin[i];
				if (camera != 0 && camera->active)
				{
					camera->Update(0.0f, 0.0f, 0x200);
				}
			}
		}

		// FUNCTION: ENGINE 0x107DDF30
		void Director::AddController(Camera* controller)
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
		void Director::RemoveController(Camera* controller)
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
				Camera* controller = controllers.begin[i];
				if (controller != 0 && controller->playerIndex == owner && controller->GetType() == type)
				{
					return true;
				}
			}
			return false;
		}

		// FUNCTION: ENGINE 0x107DE010
		bool Director::HasCamera(int type, int playerIndex) const
		{
			int count = cameras.Size();
			for (int i = 0; i < count; i++)
			{
				Cinematographer* camera = cameras.begin[i];
				if (camera != 0 && camera->playerIndex == playerIndex && camera->type == type)
				{
					return true;
				}
			}
			return false;
		}

		// FUNCTION: ENGINE 0x107DE060
		void Director::SetCamera(Cinematographer* camera)
		{
			cameras.begin[camera->type + camera->playerIndex * 2] = camera;
		}

		// FUNCTION: ENGINE 0x107DE080
		void Director::ClearCamera(Cinematographer* camera)
		{
			cameras.begin[camera->type + camera->playerIndex * 2] = 0;
			playerCamera[camera->type] = -1;
		}

		// FUNCTION: ENGINE 0x107DE0B0
		Cinematographer* Director::GetCamera(int playerIndex, unsigned int kind) const
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
				Camera* controller = controllers.begin[i];
				if (controller != 0 && controller->playerIndex == owner && controller->GetType() == type)
				{
					Cinematographer* camera = GetCamera(owner, kind);
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
			Camera* found = 0;
			int last = maxControllerIndex;
			int i = 0;
			if (i <= last)
			{
				Camera** slot = controllers.begin;
				do
				{
					Camera* controller = *slot;
					if (controller != 0 && controller->playerIndex == owner && controller->GetName() == name)
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
			Cinematographer* camera = GetCamera(playerIndex, 0);
			if (camera != 0)
			{
				camera->SetUnknown7A5(value);
			}
		}

		// FUNCTION: ENGINE 0x107DE230
		void Director::SetCameraUnknown7AD(int playerIndex, bool value)
		{
			Cinematographer* camera = GetCamera(playerIndex, 0);
			if (camera != 0)
			{
				camera->unknown7AD = value;
			}
		}

		// FUNCTION: ENGINE 0x107DE250
		Camera* Director::FindController(int type, int owner) const
		{
			for (int i = 0; i <= maxControllerIndex; i++)
			{
				Camera* controller = controllers.begin[i];
				if (controller != 0 && controller->playerIndex == owner && controller->GetType() == type)
				{
					return controller;
				}
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x107DE2A0
		Camera* Director::FindController(core::Name<core::CaseSensitiveKey> name) const
		{
			int last = maxControllerIndex;
			int i = 0;
			if (i <= last)
			{
				Camera** slot = controllers.begin;
				do
				{
					Camera* controller = *slot;
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
				Camera* controller = controllers.begin[i];
				if (controller != 0 && controller->playerIndex == owner)
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
				Camera* controller = controllers.begin[i];
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
		Camera* Director::GetController(int slot, int id) const
		{
			if (slot == -1)
			{
				return 0;
			}
			Camera* controller = controllers.begin[slot];
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
				Cinematographer* camera = GetCamera(i, kind);
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
				Cinematographer* camera = GetCamera(*index, kind);
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
		void Director::OnCameraDisabled(Cinematographer* camera)
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
		Camera* Director::GetCameraController(int playerIndex, unsigned int kind) const
		{
			Cinematographer* camera = GetCamera(playerIndex, kind);
			return Get()->GetController(camera->controller);
		}

		// FUNCTION: ENGINE 0x107DE690
		CameraTarget* Director::GetCameraTarget(int playerIndex, unsigned int kind) const
		{
			Cinematographer* camera = GetCamera(playerIndex, kind);
			if (camera != 0)
			{
				return camera->target;
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x107DE6B0
		const math::Matrix* Director::GetCameraMatrix(int playerIndex, unsigned int kind) const
		{
			Cinematographer* camera = GetCamera(playerIndex, kind);
			if (camera != 0)
			{
				return camera->target->MatrixAt90();
			}
			return &math::Matrix::IDENTITY;
		}

		// FUNCTION: ENGINE 0x107DE6E0
		int Director::GetCameraUnknown40(int playerIndex, unsigned int kind) const
		{
			Cinematographer* camera = GetCamera(playerIndex, kind);
			if (camera != 0)
			{
				return camera->unknown40;
			}
			return 0;
		}

		// FUNCTION: ENGINE 0x107DE700
		int Director::GetCameraUnknown44(int playerIndex, unsigned int kind) const
		{
			Cinematographer* camera = GetCamera(playerIndex, kind);
			if (camera != 0)
			{
				return camera->unknown44;
			}
			return 0;
		}
	}
}
