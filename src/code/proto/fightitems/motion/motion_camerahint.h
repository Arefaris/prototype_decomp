// Fight items of the motion group: CameraHintTrack (unit 0x1035B690 - 0x1035BB50; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_CAMERAHINT_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_CAMERAHINT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/proto/camera/cameramanager.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			extern fight::EnumEntry gCameraHintTrackHintTable[];  // 0x112637A0
			extern const int gCameraHintTrackHintCount;  // 0x10DF45C4

			// RTTI: proto::fightitems::motion::CameraHintTrack (16 vftable slots, 0x1C bytes)
			class CameraHintTrack : public fight::Track
			{
			public:
				// 0x1035B710
				CameraHintTrack();
				virtual ~CameraHintTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10358E10, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetHint(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

				// The accessors the engine keeps out of line
				// 0x10358BE0
				int GetHint() const;

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					int hint;  // +0x18
			};

			extern fight::Property** gCameraHintTrackProperties;
			fight::TrackFactory* CreateCameraHintTrackFactory(const char* name);
			void RegisterCameraHintTrackFactory(fight::TrackRegistry* registry, const char* name);


			// ---- actions begin
			// RTTI: proto::fightitems::motion::CameraHintAction (9 vftable slots, 0x2C bytes)
			class CameraHintAction : public fight::Action
			{
			public:
				// 0x10358D40
				CameraHintAction(CameraHintTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10358CA0
				virtual ~CameraHintAction();

				// vftable slot 7 (0x10358DE0)
				virtual bool Slot7(int arg, float value);

				engine::GameObjectHandle target;  // +0x1C
				core::Link<CameraHintTrack> link;  // +0x20
			};

			// ---- actions end
		}
	}
}

#endif
