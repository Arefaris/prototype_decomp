// engine::camera::Director (RTTI name): the camera manager singleton (global 0x11283258). It owns two arrays, the
// cameras (two slots per player: playerIndex * 2 + kind) and the registered controllers (free-slot table with a
// high-water mark). Member and method names are guesses from the code.
#ifndef ENGINE_CAMERA_DIRECTOR_H
#define ENGINE_CAMERA_DIRECTOR_H

#include "code/container/arraydynamic.h"
#include "code/core/name.h"
#include "code/engine/dbobserver.h"

namespace math
{
	class Matrix;
}

namespace engine
{
	class Message;
	class MessageListeners;

	// 0x107EFF00 (another unit): delivers message to every listener of the list
	void SendMessage(Message* message, MessageListeners* listeners);
	// 0x107EF5E0 (another unit): delivers message to every registered object
	void BroadcastMessage(Message* message);

	// What 0x10836AD0 returns (another unit): the frame's timing. The Director copies the 12 bytes at +4 and passes
	// their last float to the cameras; the other fields are unknown.
	class TimeInfo
	{
	public:
		float unknown0;
		float unknown4;
		float time;
	};
	class FrameTime
	{
	public:
		int unknown0;
		TimeInfo info;
	};
	FrameTime* GetFrameTime();

	namespace camera
	{
		class Camera;
		class CameraTarget;
		class ControllerRef;
		class Cinematographer;

		// Listener lists the Director's reset message goes to (0x11315318, 0x11315290; another unit)
		extern MessageListeners sResetListeners;
		extern MessageListeners sResetListeners2;
		// Number of players (0x1128326C)
		extern int sPlayerCount;

		class Director : public DBObserver
		{
		public:
			container::ArrayDynamic<Camera*, container::AllocatorNew> cameras;
			container::ArrayDynamic<Cinematographer*, container::AllocatorNew> controllers;
			int maxControllerIndex;
			int playerCamera[2];
			int nextControllerId;

			static Director* sDirector;
			static Director* Get();
			static void Shutdown();

			int GetMaxControllerIndex() const;
			// Puts the controller in the first free slot and gives it the next id
			void AddController(Cinematographer* controller);
			void RemoveController(Cinematographer* controller);
			bool HasController(int type, int owner) const;
			bool HasCamera(int playerIndex, int kind) const;
			void SetCamera(Camera* camera);
			void ClearCamera(Camera* camera);
			Camera* GetCamera(int playerIndex, unsigned int kind) const;
			// Resets every controller and camera and sends a CameraResetMessage
			void Reset();
			// Updates the controllers (type 2 last), then the active cameras; broadcasts a CameraCutMessage when a camera cut
			// and flags is 1. The first two arguments are unused.
			void Update(int unused1, int unused2, float delta, int flags);
			// Update(0, 0, 0x200) on every active camera; its own arguments are unused
			void UpdateCameras(float a, float b, int flags);
			// Finds the controller of type for owner and starts a transition on the owner's camera of that kind
			void StartTransition(int type, float time, int owner, unsigned int kind);
			// The same with the controller found by name (no check that the camera exists)
			void StartTransition(const core::Name<core::CaseSensitiveKey>& name, float time, unsigned int kind, int owner);
			void SetCameraUnknown7A5(int playerIndex, bool value);
			void SetCameraUnknown7AD(int playerIndex, bool value);
			Cinematographer* FindController(int type, int owner) const;
			Cinematographer* FindController(core::Name<core::CaseSensitiveKey> name) const;
			// OnEvent(param) on every controller of owner / OnKindEvent(param) on every controller of kind without flag 2
			void NotifyControllers(int param, int owner);
			void NotifyControllersOfKind(int kind, float param);
			// OnEvent(param) on the controller of type for owner / with that name (neither checks for a missing one)
			void NotifyController(int param, int type, int owner);
			void NotifyController(int param, core::Name<core::CaseSensitiveKey> name, int unused);
			// The controller in slot with that id, 0 when the slot is empty or reused
			Cinematographer* GetController(int slot, int id) const;
			Cinematographer* GetController(const ControllerRef& ref) const
			{
				return GetController(ref.slot, ref.id);
			}
			// Disables the highest enabled camera of kind, enables playerIndex's; returns the index disabled (-1: none)
			int ActivateCamera(int playerIndex, int kind);
			// Advances index to the next enabled, active camera of kind; false (index = -1) when there is none. The first
			// one found becomes playerCamera[kind] when that was unset
			bool NextActiveCamera(int* index, int kind);
			// Recomputes playerCamera for the kind of a camera that was disabled
			void OnCameraDisabled(Camera* camera);
			Cinematographer* GetCameraController(int playerIndex, unsigned int kind) const;
			CameraTarget* GetCameraTarget(int playerIndex, unsigned int kind) const;
			// The target's matrix, or the identity without a camera
			const math::Matrix* GetCameraMatrix(int playerIndex, unsigned int kind) const;
			int GetCameraUnknown40(int playerIndex, unsigned int kind) const;
			int GetCameraUnknown44(int playerIndex, unsigned int kind) const;
		};
	}
}

#endif
