// engine::ViewHandle: the handle of a view of the renderer (a table index and a serial number, like the game object
// handles). The Cinematographer keeps the handle of its display and hands its pure3d cameras to the view. The class
// and its methods are named by guess; the view table is the engine's own.
#ifndef ENGINE_RENDER_VIEWHANDLE_H
#define ENGINE_RENDER_VIEWHANDLE_H


namespace pure3d
{
	class Camera;
}

namespace engine
{
	class ViewHandle
	{
	public:
		// No view: every bit set
		ViewHandle()
		{
			value = -1;
		}
		// 0x10826E40: the view still exists
		bool IsValid() const;
		// 0x10828230: gives the view its two cameras (the second one defaults to the first) and the aspect ratio of
		// its viewport
		void SetCameras(pure3d::Camera* first, pure3d::Camera* second);

		// The table index in the low and the serial number in the high half
		int value;
	};

	// 0x10826820: the aspect ratio of the render object's letterbox (name guessed)
	float GetAspect();
}

#endif
