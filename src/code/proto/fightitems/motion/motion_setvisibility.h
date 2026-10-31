// Fight items of the motion group: SetVisibilityTrack (unit 0x101AB2E0 - 0x101AB8A0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_SETVISIBILITY_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_SETVISIBILITY_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::SetVisibilityTrack (16 vftable slots, 0x24 bytes)
			class SetVisibilityTrack : public fight::Track
			{
			public:
				// 0x101AB380
				SetVisibilityTrack();
				virtual ~SetVisibilityTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1010EE90, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetActionOnBegin(int newValue);
				bool SetActionOnEnd(int newValue);
				bool SetApplyToGrabSlots(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					int actionOnBegin;  // +0x18
					int actionOnEnd;  // +0x1C
					bool applyToGrabSlots;  // +0x20
					unsigned char unknown21[0x3];
			};

			extern fight::Property** gSetVisibilityTrackProperties;
			fight::TrackFactory* CreateSetVisibilityTrackFactory(const char* name);
			void RegisterSetVisibilityTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
