// engine::camera::Cinematographer (RTTI name, reflection name "engine::camera::Cinematographer"): the director of one
// view, 0x7B0 bytes. The Director keeps two per player (index playerIndex * 2 + type). A Cinematographer owns the
// pure3d cameras of its view and two Cameras (a blend camera and an animated one), is driven by the Camera whose slot
// and id it holds, and switches or blends between them. Member and method names are guesses.
#ifndef ENGINE_CAMERA_CINEMATOGRAPHER_H
#define ENGINE_CAMERA_CINEMATOGRAPHER_H

#include "code/core/name.h"
#include "code/engine/camera/camera.h"
#include "code/engine/render/viewhandle.h"
#include "code/math/matrix.h"
#include "code/math/vector.h"

namespace content
{
	struct ClassInfo;
	struct MemberList;
}

namespace engine
{
	namespace camera
	{
		class BlendCamera;
		class AnimatedCamera;
		class DebugCamera;

		// Whatever a view follows: only its matrix at 0x90 is known (it is a pure3d camera)
		class CameraTarget
		{
		public:
			unsigned char unknown0[0x90];
			math::Matrix* MatrixAt90()
			{
				return (math::Matrix*)(unknown0 + 0x90);
			}
		};

		// The 0x6F0 byte state the Cinematographer keeps at 0x64 (constructor 0x108D4A80, destructor 0x108D4730,
		// another unit; name guessed)
		class CameraHistory
		{
		public:
			CameraHistory();
			~CameraHistory();
			// 0x108D4760
			void Clear();
			// 0x108D4B80 / 0x108D4CA0 / 0x108D51E0: add a record to one of the two lists / set the parameter (names and
			// parameters guessed)
			void AddA(float a, float b, float c, const math::Vector* vector, int index);
			void AddB(float a, float b, float c, float d, const math::Vector* vector, int index);
			void SetParameter(float value);
			// 0x108D4FC0: the offset of the history at time, written to matrix; false when it holds nothing (name and
			// parameters guessed)
			bool Evaluate(float time, bool all, math::Matrix* matrix);

			unsigned char unknown0[0x6e8];
			int unknown6E8;
			int unknown6EC;
		};

		// 0x1084E120: answers its second argument (name guessed)
		int ReturnSecond(int unused, int value);

		class Cinematographer
		{
		public:
			// 0x1084E150
			Cinematographer();
			// vftable slot 0 (0x1084E8B0 deletes); the destructor body is 0x1084E220
			virtual ~Cinematographer();
			// vftable slot 1 (0x1084EC10): flags 1 starts the frame, 0x80 ends it, 0x200 runs the cuts
			virtual void Update(float delta, float time, int flags);

			// 0x1084DE70 / 0x1084E7E0: the class's reflection
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			int unknown4;
			// The kind of the view (the reflected enumeration CinematographerType: the second index of the Director's
			// table)
			int type;
			int unknownC;
			core::Name<core::CaseSensitiveKey> name;
			// The player the Cinematographer belongs to (the Director keeps two per player)
			int playerIndex;
			// Set by Activate; the Director only hands out the ones that are active and enabled
			bool enabled;
			bool unknown1D;
			// Set when its update cut; the Director broadcasts a CameraCutMessage
			bool cut;
			bool dirty;
			bool unknown20;
			bool unknown21;
			HandleBase handle;
			// The display the view is on (-1: none)
			ViewHandle unknown28;
			float unknown2C;
			int mode;
			int state;
			pure3d::Camera* camera38;
			// The pure3d camera the view follows; its matrix sits at 0x90
			CameraTarget* target;
			pure3d::Camera* unknown40;
			pure3d::Camera* unknown44;
			// Slot and id of the Camera driving this one (Director::GetController)
			ControllerRef controller;
			ControllerRef previous;
			BlendCamera* blend;
			DebugCamera* defaultCamera;
			AnimatedCamera* animated;
			CameraHistory history;
			bool unknown754;
			math::Matrix offset;
			ControllerRef pending;
			float pendingTime;
			bool unknown7A4;
			bool unknown7A5;
			int unknown7A8;
			bool active;
			bool unknown7AD;

			// The name, copied out
			core::Name<core::CaseSensitiveKey> GetName() const
			{
				return name;
			}
			// 0x107DDAC0 (the type)
			int GetType() const;
			// 0x1084DDF0: the same, a copy of this unit's
			int GetTypeValue() const;
			bool IsActive() const;
			void SetUnknown7AD(bool value);
			// The target's matrix (0x107DDAF0; name guessed)
			math::Matrix* GetTargetMatrix() const;
			// 0x1084E260: back to the default state (another unit)
			void Reset();
			// 0x1084DF10: takes the player unless the Director has a view of that kind for it
			void SetPlayerIndex(int value);
			// 0x1084DF90: enables / disables the default camera (and picks the state)
			void SetDefaultCameraEnabled(bool value);
			// 0x1084E050: tells the cameras the zoom changed
			void NotifyZoom();
			// 0x1084DEB0: lets go of the pure3d cameras and the two cameras and leaves the Director
			void Shutdown();
			// 0x1084E4A0: the camera that drives the view from now on (the previous one is disabled)
			void SetController(Camera* newController);
			// 0x1084E660: the mode (0: the Camera of the controller drives, 1: the animated camera does)
			void SetMode(bool value);
			// 0x1084E6D0: the display the view is on; the zoom follows its aspect ratio
			void SetDisplay(int display);
			// 0x1084E8D0: activates the view when it is the one of a local player and makes the animated and blend
			// cameras and the pure3d cameras (name guessed)
			void Start();
			// 0x1084E340: chooses the pure3d camera of the view from the blend, the animated or the controlling camera;
			// returns what that camera reports (its cut)
			bool UpdateView();
			// 0x1084E530: the blend to or from the animated camera (name guessed)
			void StartBlend(bool value, float time);
			// 0x1084EA20: carries out a pending transition and the requested mode changes
			void UpdatePending();
			// 0x1084FFE0: the handle at 0x22 (the game object the view follows; name guessed)
			void SetHandle(HandleBase newHandle);
			// 0x1084DFC0 / 0x1084DFF0 / 0x1084E030: hand a record to the history
			void AddHistoryA(float a, float b, float c, const math::Vector* vector, int index);
			void AddHistoryB(float a, float b, float c, float d, const math::Vector* vector, int index);
			void SetHistoryParameter(float value);
			// 0x1084DF40 (another unit)
			void StartTransition(int target, float time);
			// 0x1084DF70 (another unit): sets the byte at 0x7a5 when the pointer at 0x5c is set
			void SetUnknown7A5(bool value);
			// 0x1084E720 (another unit): sets enabled and tells the Director
			void Activate(bool value);
		};
	}
}

#endif
