// Fight items of the motion group: HasMarkerCondition, HideHUDTrack (unit 0x10161F50 - 0x10162970; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_HASMARKER_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_HASMARKER_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::HasMarkerCondition (10 vftable slots, 0x10 bytes)
			class HasMarkerCondition : public fight::Condition
			{
			public:
				// 0x10161FE0
				HasMarkerCondition();
				virtual ~HasMarkerCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100C0C10, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					int type;  // +0xC
			};

			extern fight::Property** gHasMarkerConditionProperties;
			fight::ConditionFactory* CreateHasMarkerConditionFactory(const char* name);
			void RegisterHasMarkerConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::HideHUDTrack (17 vftable slots, 0x28 bytes)
			class HideHUDTrack : public fight::Track
			{
			public:
				// 0x10162050
				HideHUDTrack();
				virtual ~HideHUDTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100C0EB0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);
				// vftable slot 16: whether the track overrides a property
				virtual bool Slot16(int index);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetHideIndividualElements(bool newValue);
				bool SetHideIndividualElementsHideElements(int newValue);
				// 0x10162110: sets or clears the override bits of a group's members (name guess)
				void ApplyGroup(int group, bool value);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned __int64 overrideMask;  // +0x10
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
					int hideIndividualElementsHideElements;  // +0x20
					bool hideIndividualElements;  // +0x24
			};

			extern fight::Property** gHideHUDTrackProperties;
			fight::TrackFactory* CreateHideHUDTrackFactory(const char* name);
			void RegisterHideHUDTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
