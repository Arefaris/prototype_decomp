// Fight items of the motion group: DisablePlayerControlTrack (unit 0x101598C0 - 0x10159C60; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_DISABLEPLAYERCONTROL_H
#define PROTO_FIGHTITEMS_MOTION_DISABLEPLAYERCONTROL_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::DisablePlayerControlTrack (16 vftable slots, 0x18 bytes)
			class DisablePlayerControlTrack : public fight::Track
			{
			public:
				// 0x10159930
				DisablePlayerControlTrack();
				virtual ~DisablePlayerControlTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100B7740, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
			};

			extern fight::Property** gDisablePlayerControlTrackProperties;
			fight::TrackFactory* CreateDisablePlayerControlTrackFactory(const char* name);
			void RegisterDisablePlayerControlTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// RTTI: proto::fightitems::motion::DisablePlayerControlAction (9 vftable slots, 0x24 bytes)
			class DisablePlayerControlAction : public fight::Action
			{
			public:
				// 0x100B7700
				explicit DisablePlayerControlAction(engine::GameObjectHandle newTarget);
				// 0x100B7730
				virtual ~DisablePlayerControlAction();

				// vftable slot 5 (0x100B77B0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100B7840)
				virtual void Slot6();

				int player;  // +0x1C
				engine::GameObjectHandle target;  // +0x20
			};

			// ---- actions end
		}
	}
}

#endif
