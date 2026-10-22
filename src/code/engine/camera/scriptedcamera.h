// engine::camera::ScriptedCamera (RTTI name, reflection name "engine::camera::ScriptedCamera"; base
// engine::camera::Camera): the camera the game scripts drive. Its position and look-at point each follow a spline
// track (kept as a position in the world, relative to a game object or to a part of an object) or the engine plays a
// camera animation on it. Unit 0x10850950 - 0x108522F0 (no assert path; the directory and file names are guesses).
// Member and method names are guesses except the reflected ones.
#ifndef ENGINE_CAMERA_SCRIPTEDCAMERA_H
#define ENGINE_CAMERA_SCRIPTEDCAMERA_H

#include "code/content/metatype.h"
#include "code/engine/camera/camera.h"
#include "code/engine/gameobject/gameobjecthandle.h"
#include "code/math/matrix.h"
#include "code/math/spline.h"
#include "code/math/vector.h"
#include "code/pure3d/camera.h"
#include "code/pure3d/cameraanimationcontroller.h"

namespace pure3d
{
	class Animation;
}

namespace engine
{
	namespace camera
	{
		// What the camera follows with its position or its look-at point (0x38 bytes): a spline or a point in the world,
		// relative to a game object (and a part of it) with an offset
		class SplineTrack
		{
		public:
			// 0x10851400
			SplineTrack();
			// 0x10850E60: frees the spline and its key times
			~SplineTrack();
			// 0x10850E90: back to nothing followed
			void Clear();
			// 0x10851560: the game object (handle) and the part of it (by name) the track follows
			bool Bind(HandleBase newObject, core::Name<core::CaseSensitiveKey> partName);
			// 0x108515F0: the point of the track at time (writes position)
			void Evaluate(float time, bool update, math::Matrix* matrix);

			bool active;
			HandleBase object;  // +0x02
			int part;  // +0x08 (0xFFFF: the object itself)
			math::Spline* spline;  // +0x0C
			float* times;  // +0x10, one per key
			int timeCount;  // +0x14
			int segment;  // +0x18
			int orientMode;  // +0x1C
			math::Vector offset;  // +0x20
			math::Vector position;  // +0x2C
		};

		class ScriptedCamera : public Camera
		{
		public:
			// How a track's offset is applied (the reflection names the enumeration)
			enum OrientMode
			{
				ORIENT_WORLD = 0,
				ORIENT_OBJECT = 1,
				ORIENT_JOINT = 2,
				ORIENT_FACING = 3
			};

			// 0x10851480
			ScriptedCamera();
			// vftable slot 0 (0x108514E0 deletes); the destructor body is 0x10850F50
			virtual ~ScriptedCamera();
			// vftable slot 3 (0x10851CA0)
			virtual void Update(float delta, float time, int flags);
			// vftable slot 4 (0x10850E10): the track or animation has finished
			virtual bool Slot4();
			// vftable slot 10 (0x10850FA0): back to the initial state
			virtual void Reset();

			static content::ClassInfo* GetClassInfo();
			static content::MemberList* GetMembers();

			// 0x10850E00
			bool IsActive() const;
			// 0x10850E20: the up vector of the camera
			void SetUp(const math::Vector& up);
			// 0x10850E50
			void SetUnknown57(bool value);
			// 0x108509F0: Reset through the vftable
			void Restart();
			// 0x10850A00 / 0x10850A30: the camera's position / look-at point as a point of the world
			bool SetPositionPoint(const math::Vector& point);
			bool SetLookAtPoint(const math::Vector& point);
			// 0x10850B90: the value at 0xD8 (a field of view in radians; larger than 3 only with byte 0x57 set)
			bool SetUnknownD8(float value);
			// 0x10850BD0: the window of the view
			bool SetWindow(float a, float b, float c, float d);
			// 0x10851360: the tracks have run out (or the animation is done)
			bool IsFinished();
			// 0x10851950 / 0x108519C0: the position / look-at track follows a part of a game object with an offset
			// (applied as the mode says; ignored for a mode above 3), and is active when the flag is set
			bool BindPosition(HandleBase object, const char* partName, const math::Vector* newOffset, unsigned int newMode,
				bool newActive);
			bool BindLookAt(HandleBase object, const char* partName, const math::Vector* newOffset, unsigned int newMode,
				bool newActive);
			// 0x10851A30: the position track as above, the part given by a name; also sets the byte at 0xDC
			bool BindPositionNamed(HandleBase object, core::Name<core::CaseSensitiveKey> partName,
				const math::Vector* newOffset, unsigned int newMode, bool newActive);
			// 0x10851AA0: the animation of that name from the root inventory
			bool LoadAnimation(const char* name);
			// 0x108510D0: plays an animation on a camera of its own
			bool SetAnimation(pure3d::Animation* newAnimation);
			// 0x10851B20: evaluates the tracks at time and builds the camera's view matrix
			void UpdateTracks(float newTime, bool update);
			// 0x10851230: gives a track the spline (a copy; it must have four keys with rising times in w)
			bool SetSpline(SplineTrack* track, math::Spline& source);
			// 0x10851500 / 0x10851530: the position / look-at track is given the spline and set to be used (bits 0x10 /
			// 0x20 of the pending word)
			bool SetPositionSpline(math::Spline& source);
			bool SetLookAtSpline(math::Spline& source);
			// 0x10850A60: plays the animation from first to last (a negative value: the start / the end of the
			// animation) at frame, looping as loopMode says (0: as the animation does, 2: looping)
			bool SetPlayback(float first, float last, float frame, bool newUnknown55, bool newUnknown56, int loopMode);
			// 0x10850C20: starts what was set (the tracks or the animation) and picks the mode
			bool Start();
			// 0x108510A0: lets go of the animation and the camera that plays it
			void ReleaseAnimation();

			int mode;  // +0x48
			bool unknown4C;
			bool unknown4D;
			bool unknown4E;
			float unknown50;
			bool finished;  // +0x54
			bool unknown55;
			bool unknown56;
			bool unknown57;
			int pending;  // +0x58, bits for the tracks that were set
			SplineTrack position;  // +0x5C
			SplineTrack lookAt;  // +0x94
			math::Vector up;  // +0xCC
			float unknownD8;
			bool unknownDC;
			math::Matrix view;  // +0xE0
			math::Matrix target;  // +0x120
			pure3d::Animation* animation;  // +0x160
			pure3d::CameraAnimationController* controller;  // +0x164
			pure3d::Camera* animationCamera;  // +0x168
			pure3d::CameraWindow window;  // +0x16C
			float time;  // +0x184
		};
	}
}

namespace content
{
	template<> void EnumInfo<engine::camera::ScriptedCamera::OrientMode>::Get(const char** name, const EnumValue** values,
		int* count, const char** code);
}

#endif
