// Fight items of the motion group: CameraAvatarSelectTrack, CameraTypeSelectTrack (unit 0x1035AC20 - 0x1035B690; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_CAMERASELECT_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_CAMERASELECT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			extern fight::EnumEntry gCameraAvatarSelectTrackCameraTypeTable[];  // 0x11263770
			extern const int gCameraAvatarSelectTrackCameraTypeCount;  // 0x10DF4344

			// RTTI: proto::fightitems::motion::CameraAvatarSelectTrack (16 vftable slots, 0x28 bytes)
			class CameraAvatarSelectTrack : public fight::Track
			{
			public:
				// 0x1035ADA0
				CameraAvatarSelectTrack();
				virtual ~CameraAvatarSelectTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10358B50, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetCameraType(int newValue);
				bool SetParent(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					float timeBegin;  // +0x18
					int cameraType;  // +0x1C
					bool parent;  // +0x20
					unsigned char unknown21[0x7];
			};

			extern fight::Property** gCameraAvatarSelectTrackProperties;
			fight::TrackFactory* CreateCameraAvatarSelectTrackFactory(const char* name);
			void RegisterCameraAvatarSelectTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::CameraTypeSelectTrack (16 vftable slots, 0x1C bytes)
			class CameraTypeSelectTrack : public fight::Track
			{
			public:
				// 0x1035AD10
				CameraTypeSelectTrack();
				virtual ~CameraTypeSelectTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10358BA0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetCameraType(int newValue);
				bool SetCameraBlendTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float cameraBlendTime;  // +0x10
					float timeBegin;  // +0x14
					int cameraType;  // +0x18
			};

			extern fight::Property** gCameraTypeSelectTrackProperties;
			fight::TrackFactory* CreateCameraTypeSelectTrackFactory(const char* name);
			void RegisterCameraTypeSelectTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
