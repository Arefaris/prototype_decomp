// Fight items of the ai group: TankRamTrack (unit 0x10246860 - 0x10246F80; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_AI_AI_TANKRAM_H
#define PROTO_FIGHTITEMS_AI_AI_TANKRAM_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/ai/aiaction.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/ai/aidata2.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			// RTTI: proto::fightitems::ai::TankRamTrack (16 vftable slots, 0x3C bytes)
			class TankRamTrack : public fight::Track
			{
			public:
				// 0x102469F0
				TankRamTrack();
				virtual ~TankRamTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x102089D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTimePreparingForward(float newValue);
				bool SetTimePreparingBackward(float newValue);
				bool SetMaxTurningSpeedFactor(float newValue);
				bool SetRollingScaleFactor(float newValue);
				bool SetRollingScaleBackwardsFactor(float newValue);
				bool SetRollingScaleFactorPush(float newValue);
				bool SetRollingScaleBackwardsFactorPush(float newValue);
				bool SetToleranceForward(float newValue);
				bool SetSpeed(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float maxTurningSpeedFactor;  // +0x10
					float rollingScaleBackwardsFactor;  // +0x14
					float rollingScaleBackwardsFactorPush;  // +0x18
					float rollingScaleFactor;  // +0x1C
					float rollingScaleFactorPush;  // +0x20
					float speed;  // +0x24
					float timeBegin;  // +0x28
					float timeEnd;  // +0x2C
					float timePreparingBackward;  // +0x30
					float timePreparingForward;  // +0x34
					float toleranceForward;  // +0x38
			};

			extern fight::Property** gTankRamTrackProperties;
			fight::TrackFactory* CreateTankRamTrackFactory(const char* name);
			void RegisterTankRamTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::ai::TankRamAction (9 vftable slots, 0x2C bytes)
			class TankRamAction : public fight::Action
			{
			public:
				// 0x10208100
				TankRamAction(TankRamTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x10207F30
				virtual ~TankRamAction();

				// vftable slot 5 (0x102081E0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x10207F60)
				virtual void Slot6();
				// vftable slot 7 (0x102085F0)
				virtual bool Slot7(int arg, float value);

				core::Link<TankRamTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				engine::HandleBase unknown2C;  // +0x2C
				float unknown30;  // +0x30
				float unknown34;  // +0x34
				float unknown38;  // +0x38
				float unknown3C;  // +0x3C
				float unknown40;  // +0x40
				float unknown44;  // +0x44
				int unknown48;  // +0x48
			};

			// ---- actions end
		}
	}
}

#endif
