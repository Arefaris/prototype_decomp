// Fight items of the motion group: CameraShakeRequestTrack (unit 0x1035BFB0 - 0x1035C460; no assert path, the file name is a guess).
#ifndef PROTO_CAMERA_CAMERASHAKEREQUEST_H
#define PROTO_CAMERA_CAMERASHAKEREQUEST_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/proto/camera/cameramanager.h"

namespace proto
{
	namespace camera
	{
		extern fight::EnumEntry gCameraShakeRequestTrackSizeTable[];  // 0x11263848
		extern const int gCameraShakeRequestTrackSizeCount;  // 0x10DF4894

		// RTTI: proto::camera::CameraShakeRequestTrack (16 vftable slots, 0x1C bytes)
		class CameraShakeRequestTrack : public fight::Track
		{
		public:
			// 0x1035C020
			CameraShakeRequestTrack();
			virtual ~CameraShakeRequestTrack();

			// vftable slot 0
			virtual fight::Property* GetProperty(int index);
			// vftable slot 9
			virtual float GetTimeBegin() const;
			// vftable slot 10
			virtual float Slot10() const;
			// vftable slot 15 (0x10359410, another unit)
			virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

			// The members the properties write
			bool SetTimeBegin(float newValue);
			bool SetSize(int newValue);
			bool SetRange(int newValue);

			// The property list, built once and freed again
			static void RegisterProperties();
			static void ClearProperties();

				// The accessors the engine keeps out of line
				// 0x103591A0
				int GetSize() const;
				// 0x103591B0
				int GetRange() const;

					float timeBegin;  // +0x10
					int range;  // +0x14
					int size;  // +0x18
		};

		extern fight::Property** gCameraShakeRequestTrackProperties;
		fight::TrackFactory* CreateCameraShakeRequestTrackFactory(const char* name);
		void RegisterCameraShakeRequestTrackFactory(fight::TrackRegistry* registry, const char* name);


		// ---- actions begin
		// What a track owner of kind 0x40000 holds: a position (the other kinds carry a game object handle)
		struct ShakeOwnerPoint : fightitems::motion::TrackOwner
		{
			unsigned char unknown10[0x30];
			math::Vector position;  // +0x40
		};

		// RTTI: proto::camera::CameraShakeRequestAction (9 vftable slots, 0x38 bytes)
		class CameraShakeRequestAction : public fight::Action
		{
		public:
			// 0x10359320
			CameraShakeRequestAction(CameraShakeRequestTrack* newTrack, const math::Vector& newPosition);
			// 0x10359290
			virtual ~CameraShakeRequestAction();

			// vftable slot 5 (0x103593D0)
			virtual bool Slot5(int arg, float value);

			core::Link<CameraShakeRequestTrack> link;  // +0x1C
			math::Vector position;  // +0x28
			float unknown34;
		};
		// ---- actions end
	}
}

#endif
