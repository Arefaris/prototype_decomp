// Fight items of the playback group: WasShotByPlayerCondition, ShootTrack (unit 0x1025BC30 - 0x1025C660; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_PLAYBACK_PLAYBACK_SHOOT_H
#define PROTO_FIGHTITEMS_PLAYBACK_PLAYBACK_SHOOT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/scenario/scenariodata.h"
#include "code/proto/fightitems/ai/aidata.h"
#include "code/proto/fightitems/playback/playbackdata.h"

namespace proto
{
	namespace fightitems
	{
		namespace playback
		{
			// RTTI: proto::fightitems::playback::WasShotByPlayerCondition (10 vftable slots, 0x10 bytes)
			class WasShotByPlayerCondition : public fight::Condition
			{
			public:
				// 0x1025BD40
				WasShotByPlayerCondition();
				virtual ~WasShotByPlayerCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x102581C0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetShotByPlayer(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					bool shotByPlayer;  // +0xC
					unsigned char unknownD[0x3];
			};

			extern fight::Property** gWasShotByPlayerConditionProperties;
			fight::ConditionFactory* CreateWasShotByPlayerConditionFactory(const char* name);
			void RegisterWasShotByPlayerConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::playback::ShootTrack (16 vftable slots, 0x44 bytes)
			class ShootTrack : public fight::Track
			{
			public:
				// 0x1025BDA0
				ShootTrack();
				virtual ~ShootTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10258720, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetDirectionSpace(int newValue);
				bool SetDirection(const math::Vector& newValue);
				bool SetSingleShot(bool newValue);
				bool SetShooterIsOriginator(bool newValue);
				bool SetWeaponSpaceOffset(const math::Vector& newValue);
				bool SetWeaponSpaceRotationOffset(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					math::Vector direction;  // +0x10
					math::Vector weaponSpaceOffset;  // +0x1C
					math::Vector weaponSpaceRotationOffset;  // +0x28
					float timeBegin;  // +0x34
					float timeEnd;  // +0x38
					int directionSpace;  // +0x3C
					bool shooterIsOriginator;  // +0x40
					bool singleShot;  // +0x41
					unsigned char unknown42[0x2];
			};

			extern fight::Property** gShootTrackProperties;
			fight::TrackFactory* CreateShootTrackFactory(const char* name);
			void RegisterShootTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin

			// ---- actions end
		}
	}
}

#endif
