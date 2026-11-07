// Fight items of the motion group: CameraHintTrack (unit 0x1035B690 - 0x1035BB50; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_CAMERAHINT_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_CAMERAHINT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motionaction.h"

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

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					int hint;  // +0x18
			};

			extern fight::Property** gCameraHintTrackProperties;
			fight::TrackFactory* CreateCameraHintTrackFactory(const char* name);
			void RegisterCameraHintTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
