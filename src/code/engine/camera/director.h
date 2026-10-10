// engine::camera::Director (RTTI name): the camera manager singleton (global 0x11283258). It owns two arrays, the
// cameras (two slots per player: playerIndex * 2 + kind) and the registered controllers (free-slot table with a
// high-water mark). Member and method names are guesses from the code.
#ifndef ENGINE_CAMERA_DIRECTOR_H
#define ENGINE_CAMERA_DIRECTOR_H

#include "code/engine/dbobserver.h"

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
		class Cinematographer;

		// The engine's dynamic array: begin, end, end of storage
		template<class T> class Array
		{
		public:
			T* begin;
			T* end;
			T* capacity;

			int Size() const
			{
				return (int)(end - begin);
			}
		};

		// Listener lists the Director's reset message goes to (0x11315318, 0x11315290; another unit)
		extern MessageListeners sResetListeners;
		extern MessageListeners sResetListeners2;
		// Number of players (0x1128326C)
		extern int sPlayerCount;

		class Director : public DBObserver
		{
		public:
			Array<Camera*> cameras;
			Array<Cinematographer*> controllers;
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
		};
	}
}

#endif
