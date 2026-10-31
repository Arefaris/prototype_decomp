// Fight items of the motion group: HaveIconTypeCondition, HUDMarkerTrack (unit 0x1017CA90 - 0x1017D680; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_HUDMARKER_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_HUDMARKER_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::HaveIconTypeCondition (10 vftable slots, 0x10 bytes)
			class HaveIconTypeCondition : public fight::Condition
			{
			public:
				// 0x1017CB80
				HaveIconTypeCondition();
				virtual ~HaveIconTypeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100D6260, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int type;  // +0xC
			};

			extern fight::Property** gHaveIconTypeConditionProperties;
			fight::ConditionFactory* CreateHaveIconTypeConditionFactory(const char* name);
			void RegisterHaveIconTypeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::HUDMarkerTrack (16 vftable slots, 0x38 bytes)
			class HUDMarkerTrack : public fight::Track
			{
			public:
				// 0x1017CC40
				HUDMarkerTrack();
				virtual ~HUDMarkerTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100D66D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetType(int newValue);
				bool SetDisplayType(int newValue);
				bool SetAnimType(int newValue);
				bool SetColor(int newValue);
				bool SetRadius(float newValue);
				bool SetUseGrabSlot(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					float radius;  // +0x18
					float timeBegin;  // +0x1C
					float timeEnd;  // +0x20
					int animType;  // +0x24
					int color;  // +0x28
					int type;  // +0x2C
					int displayType;  // +0x30
					bool useGrabSlot;  // +0x34
					unsigned char unknown35[0x3];
			};

			extern fight::Property** gHUDMarkerTrackProperties;
			fight::TrackFactory* CreateHUDMarkerTrackFactory(const char* name);
			void RegisterHUDMarkerTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
