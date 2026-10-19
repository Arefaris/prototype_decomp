// The controller handles of the asynchronous renderer (renderglobals.cpp): the game thread holds a handle to an object
// of the render thread (a light, say) that a table slot stands for. The slot keeps the object and the frame controller
// that animates it. Names are guesses.
#ifndef ENGINE_RENDER_ASYNC_PRIVATE_CONTROLLER_H
#define ENGINE_RENDER_ASYNC_PRIVATE_CONTROLLER_H

namespace pure3d
{
	class FrameController;
}

namespace engine
{
	namespace render
	{
		// A handle the controller table gave out
		class ControllerHandle
		{
		public:
			ControllerHandle() : mHandle(-1)
			{
			}

			int mHandle;
		};

		// A slot of the controller table: the object a controller handle stands for, its controller and whether the
		// controller runs
		struct ControllerSlot
		{
			ControllerSlot();
			ControllerSlot(const ControllerSlot& other);

			void* unknown0;
			pure3d::FrameController* controller;
			bool active;
		};

		// 0x10818290 / 0x10818820 / 0x10818900 / 0x10818950 / 0x10818990 (renderglobals.cpp)
		bool IsValidController(const ControllerHandle& handle);
		ControllerHandle AllocateController();
		void FreeController(const ControllerHandle& handle);
		void* GetControllerObject(const ControllerHandle& handle);
		ControllerSlot* GetControllerSlot(const ControllerHandle& handle);
	}
}

#endif
