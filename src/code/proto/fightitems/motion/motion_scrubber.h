// Fight items of the motion group: ScrubberTrack (unit 0x101AADF0 - 0x101AB2E0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_SCRUBBER_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_SCRUBBER_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::ScrubberTrack (16 vftable slots, 0x28 bytes)
			class ScrubberTrack : public fight::Track
			{
			public:
				// 0x101AAE90
				ScrubberTrack();
				virtual ~ScrubberTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x1010E8E0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetAnimation(const fight::Name& newValue);
				bool SetFrame(float newValue);
				bool SetFrameOffset(float newValue);
				bool SetHasRootTranslation(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animation;  // +0x10
					float frame;  // +0x18
					float frameOffset;  // +0x1C
					bool hasRootTranslation;  // +0x20
					unsigned char unknown21[0x7];
			};

			extern fight::Property** gScrubberTrackProperties;
			fight::TrackFactory* CreateScrubberTrackFactory(const char* name);
			void RegisterScrubberTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// RTTI: proto::fightitems::motion::ScrubberAction (9 vftable slots, 0x30 bytes)
			class ScrubberAction : public fight::Action
			{
			public:
				// 0x1010E4D0
				ScrubberAction(ScrubberTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x1010E350
				virtual ~ScrubberAction();

				// vftable slot 5 (0x1010E390)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x1010E3F0)
				virtual void Slot6();
				// vftable slot 7 (0x1010E7C0)
				virtual bool Slot7(int arg, float value);

				core::Link<ScrubberTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				choreo::Driver* driver;  // +0x2C
			};

			// ---- actions end
		}
	}
}

#endif
