// Fight items of the motion group: PunchinCameraTrack (unit 0x1035DC50 - 0x1035E310; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_PUNCHINCAMERA_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_PUNCHINCAMERA_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::PunchinCameraTrack (16 vftable slots, 0x38 bytes)
			class PunchinCameraTrack : public fight::Track
			{
			public:
				// 0x1035DD70
				PunchinCameraTrack();
				virtual ~PunchinCameraTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1035A490, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetInTime(float newValue);
				bool SetOutTime(float newValue);
				bool SetDolly(float newValue);
				bool SetZoom(float newValue);
				bool SetReAim(bool newValue);
				bool SetAimPoint(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector aimPoint;  // +0x10
					float dolly;  // +0x1C
					float inTime;  // +0x20
					float outTime;  // +0x24
					float timeBegin;  // +0x28
					float timeEnd;  // +0x2C
					float zoom;  // +0x30
					bool reAim;  // +0x34
					unsigned char unknown35[0x3];
			};

			extern fight::Property** gPunchinCameraTrackProperties;
			fight::TrackFactory* CreatePunchinCameraTrackFactory(const char* name);
			void RegisterPunchinCameraTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
