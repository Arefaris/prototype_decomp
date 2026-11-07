// Fight items of the motion group: CameraResetTrack (unit 0x1035BB50 - 0x1035BFB0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_CAMERARESET_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_CAMERARESET_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::CameraResetTrack (16 vftable slots, 0x24 bytes)
			class CameraResetTrack : public fight::Track
			{
			public:
				// 0x1035BBE0
				CameraResetTrack();
				virtual ~CameraResetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10359150, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetDirection(const math::Vector& newValue);
				bool SetBlendTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector direction;  // +0x10
					float blendTime;  // +0x1C
					float timeBegin;  // +0x20
			};

			extern fight::Property** gCameraResetTrackProperties;
			fight::TrackFactory* CreateCameraResetTrackFactory(const char* name);
			void RegisterCameraResetTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
