// engine::camera::Camera (RTTI name, reflection name "engine::camera::Camera"): the base of the cameras of the game
// (ScriptedCamera, DramaticCamera, BlendCamera and the game's own cameras derive from it). A Camera has a name, the
// index of its player and a pure3d camera with the field of view and the clipping planes; the Director keeps the
// registered cameras in a slot table. The vftable slot names other than Update / GetType / Reset and all member names
// are guesses.
#ifndef ENGINE_CAMERA_CAMERA_H
#define ENGINE_CAMERA_CAMERA_H

#include "code/core/name.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/vector.h"

namespace content
{
	struct ClassInfo;
	struct MemberList;
}

namespace pure3d
{
	class Camera;
}

namespace engine
{
	namespace camera
	{
		class Camera;

		// Slot and id of a registered Camera. The members are out of line (0x1084D870, 0x1084D880, 0x1084D8A0 and
		// 0x1084D8B0 in the cinematographer's unit), so every user calls them.
		class ControllerRef
		{
		public:
			// No camera: slot -1, id 0
			ControllerRef();
			// The slot and id of the camera
			explicit ControllerRef(const Camera* camera);
			~ControllerRef();
			void Set(const Camera* camera);

			int slot;
			int id;
		};

		class Camera
		{
		public:
			// 0x1084D9E0: a camera without a player, enabled never, with a fresh pure3d camera (field of view 0.5,
			// far plane 10000)
			Camera();
			// vftable slot 0 (0x1084DB50 deletes); the destructor body is 0x1084DAA0
			virtual ~Camera();
			// vftable slots 1 and 2 (0x1084D8D0 / 0x1084D8F0): registers with the Director / leaves it
			virtual void Register();
			virtual void Unregister();
			// vftable slot 3 (empty here)
			virtual void Update(float delta, float time, int flags);
			// vftable slot 4 (0x1032A380 in the engine, which keeps its inline copy in another unit)
			virtual bool Slot4()
			{
				return false;
			}
			// vftable slot 5 (6 here)
			virtual int GetType();
			// vftable slot 6 (0x1084D920): the player of the camera
			virtual void SetPlayerIndex(int value);
			// vftable slot 7 (0x1084D930), called by the Director for every camera of a player
			virtual void OnEvent(int param);
			// vftable slot 8 (0x1084D940)
			virtual void SetEnabled(bool value);
			// vftable slot 9 (0x1084D950), called by the Director for the cameras of a kind unless bit 1 of flags is
			// set
			virtual void OnKindEvent(float param);
			// vftable slot 10 (0x1084D980): the pure3d camera back to the identity
			virtual void Reset();

			// 0x1084D830 / 0x1084DCC0: the class's reflection
			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// The reflected accessors: the field of view in degrees (0x1084D7A0 / 0x1084D7B0) and the clipping planes
			// (0x1084D7D0 / 0x1084D7E0 and 0x1084D800 / 0x1084D810)
			float GetFov() const;
			void SetFov(float degrees);
			float GetNearPlane() const;
			void SetNearPlane(float distance);
			float GetFarPlane() const;
			void SetFarPlane(float distance);

			int unknown4;
			core::Name<core::CaseSensitiveKey> name;
			int playerIndex;
			pure3d::Camera* camera;
			HandleBase unknown18;
			int kind;
			HandleBase unknown20;
			unsigned int flags;
			float unknown28;
			bool enabled;
			math::Vector position;
			// Index in the Director's camera table and the serial number given when registered
			int slot;
			int id;
			// Not touched by the Camera itself; the derived classes' members start at 0x48
			int unknown44;

			core::Name<core::CaseSensitiveKey> GetName() const
			{
				return name;
			}
			// Bit 1 of flags clear
			bool IsRunning() const
			{
				return !((flags >> 1) & 1);
			}
			// Bit 1 of a flags word clear, as a free-standing test (0x107DD9D0; name guessed)
			static int IsRunningFlags(unsigned int flags);
			// OnKindEvent unless bit 1 of flags is set (0x107DDA50; name guessed)
			void OnKindEventIfRunning(float param);
			void SetSlot(int value);
			int GetSlot() const;
			void SetId(int value);
			int GetId() const;
		};
	}
}

#endif
