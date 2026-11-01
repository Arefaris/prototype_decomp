// Fight items of the motion group: GroundSlideTrack (unit 0x10174CA0 - 0x101753C0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_GROUNDSLIDE_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_GROUNDSLIDE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::GroundSlideTrack (16 vftable slots, 0x38 bytes)
			class GroundSlideTrack : public fight::Track
			{
			public:
				// 0x10174E00
				GroundSlideTrack();
				virtual ~GroundSlideTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100CE740, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetFacing(float newValue);
				bool SetDeceleration(float newValue);
				bool SetMinInitVelocity(float newValue);
				bool SetMinVelocity(float newValue);
				bool SetMaxVelocity(float newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float blendInTime;  // +0x10
					float blendOutTime;  // +0x14
					float deceleration;  // +0x18
					float facing;  // +0x1C
					float maxVelocity;  // +0x20
					float minInitVelocity;  // +0x24
					float minVelocity;  // +0x28
					float timeBegin;  // +0x2C
					float timeEnd;  // +0x30
					int priority;  // +0x34
			};

			extern fight::Property** gGroundSlideTrackProperties;
			fight::TrackFactory* CreateGroundSlideTrackFactory(const char* name);
			void RegisterGroundSlideTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::GroundSlideAction (9 vftable slots, 0x3C bytes)
			class GroundSlideAction : public fight::Action
			{
			public:
				// 0x100CE070
				GroundSlideAction(GroundSlideTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100CDF50
				virtual ~GroundSlideAction();

				// vftable slot 5 (0x100CE120)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100CDF90)
				virtual void Slot6();
				// vftable slot 7 (0x100CE460)
				virtual bool Slot7(int arg, float value);

				engine::GameObjectHandle target;  // +0x1C
				core::Link<GroundSlideTrack> link;  // +0x20
				choreo::Driver* driver;  // +0x2C
				float unknown30;  // +0x30
				float unknown34;  // +0x34
				float unknown38;  // +0x38
			};

			// ---- actions end
		}
	}
}

#endif
