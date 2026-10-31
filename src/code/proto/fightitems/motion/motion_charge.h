// Fight items of the motion group: ChargeCondition, ChargeTrack, ChargeSetTrack, AnimationChargeTrack, ChargeClearTrack (unit 0x101479B0 - 0x10149690; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_CHARGE_H
#define PROTO_FIGHTITEMS_MOTION_CHARGE_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"
#include "code/proto/fightitems/motion/motionaction.h"
#include "code/choreo/rootdriver.h"
#include "code/choreo/puppet.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::ChargeCondition (10 vftable slots, 0x18 bytes)
			class ChargeCondition : public fight::Condition
			{
			public:
				// 0x10147C70
				ChargeCondition();
				virtual ~ChargeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x100A0EC0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetCompare(int newValue);
				bool SetCharge(float newValue);
				bool SetType(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float charge;  // +0xC
					int compare;  // +0x10
					int type;  // +0x14
			};

			extern fight::Property** gChargeConditionProperties;
			fight::ConditionFactory* CreateChargeConditionFactory(const char* name);
			void RegisterChargeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ChargeTrack (16 vftable slots, 0x28 bytes)
			class ChargeTrack : public fight::Track
			{
			public:
				// 0x10147CF0
				ChargeTrack();
				virtual ~ChargeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100A1D90, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetType(int newValue);
				bool SetClearOnBegin(bool newValue);
				bool SetFinalCharge(float newValue);
				bool SetRandomRange(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float finalCharge;  // +0x10
					float randomRange;  // +0x14
					float timeBegin;  // +0x18
					float timeEnd;  // +0x1C
					int type;  // +0x20
					bool clearOnBegin;  // +0x24
					unsigned char unknown25[0x3];
			};

			extern fight::Property** gChargeTrackProperties;
			fight::TrackFactory* CreateChargeTrackFactory(const char* name);
			void RegisterChargeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ChargeSetTrack (16 vftable slots, 0x20 bytes)
			class ChargeSetTrack : public fight::Track
			{
			public:
				// 0x10147DB0
				ChargeSetTrack();
				virtual ~ChargeSetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100A1DE0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetType(int newValue);
				bool SetCharge(float newValue);
				bool SetRandomRange(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float charge;  // +0x10
					float randomRange;  // +0x14
					float timeBegin;  // +0x18
					int type;  // +0x1C
			};

			extern fight::Property** gChargeSetTrackProperties;
			fight::TrackFactory* CreateChargeSetTrackFactory(const char* name);
			void RegisterChargeSetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::AnimationChargeTrack (16 vftable slots, 0x48 bytes)
			class AnimationChargeTrack : public fight::Track
			{
			public:
				// 0x10147FD0
				AnimationChargeTrack();
				virtual ~AnimationChargeTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100A1E80, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetAnimation(const fight::Name& newValue);
				bool SetType(int newValue);
				bool SetStartFrame(float newValue);
				bool SetEndFrame(float newValue);
				bool SetReverse(bool newValue);
				bool SetPartition(const fight::Name& newValue);
				bool SetPriority(int newValue);
				bool SetBlendInTime(float newValue);
				bool SetBlendOutTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name animation;  // +0x10
					fight::Name partition;  // +0x18
					float blendInTime;  // +0x20
					float blendOutTime;  // +0x24
					float endFrame;  // +0x28
					float startFrame;  // +0x2C
					float timeBegin;  // +0x30
					float timeEnd;  // +0x34
					int priority;  // +0x38
					int type;  // +0x3C
					bool reverse;  // +0x40
					unsigned char unknown41[0x7];
			};

			extern fight::Property** gAnimationChargeTrackProperties;
			fight::TrackFactory* CreateAnimationChargeTrackFactory(const char* name);
			void RegisterAnimationChargeTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ChargeClearTrack (16 vftable slots, 0x1C bytes)
			class ChargeClearTrack : public fight::Track
			{
			public:
				// 0x10147E90
				ChargeClearTrack();
				virtual ~ChargeClearTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x100A1E30, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetClearOnBegin(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					float timeEnd;  // +0x14
					bool clearOnBegin;  // +0x18
					unsigned char unknown19[0x3];
			};

			extern fight::Property** gChargeClearTrackProperties;
			fight::TrackFactory* CreateChargeClearTrackFactory(const char* name);
			void RegisterChargeClearTrackFactory(fight::TrackRegistry* registry, const char* name);

			// ---- actions begin
			// RTTI: proto::fightitems::motion::ChargeAction (9 vftable slots, 0x2C bytes)
			class ChargeAction : public fight::Action
			{
			public:
				// 0x100A1310
				ChargeAction(ChargeTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100A0FB0
				virtual ~ChargeAction();

				// vftable slot 5 (0x100A13C0)
				virtual bool Slot5(int arg, float value);
				// vftable slot 7 (0x100A1550)
				virtual bool Slot7(int arg, float value);

				engine::GameObjectHandle target;  // +0x1C
				core::Link<ChargeTrack> link;  // +0x20
				float unknown2C;  // +0x2C
			};

			// RTTI: proto::fightitems::motion::ChargeSetAction (9 vftable slots, 0x2C bytes)
			class ChargeSetAction : public fight::Action
			{
			public:
				// 0x100A1600
				ChargeSetAction(ChargeSetTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100A1000
				virtual ~ChargeSetAction();

				// vftable slot 5 (0x100A16A0)
				virtual bool Slot5(int arg, float value);

				engine::GameObjectHandle target;  // +0x1C
				core::Link<ChargeSetTrack> link;  // +0x20
			};

			// RTTI: proto::fightitems::motion::ChargeClearAction (9 vftable slots, 0x2C bytes)
			class ChargeClearAction : public fight::Action
			{
			public:
				// 0x100A1770
				ChargeClearAction(ChargeClearTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100A1050
				virtual ~ChargeClearAction();

				// vftable slot 5 (0x100A1810)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100A18C0)
				virtual void Slot6();

				engine::GameObjectHandle target;  // +0x1C
				core::Link<ChargeClearTrack> link;  // +0x20
			};

			// RTTI: proto::fightitems::motion::AnimationChargeAction (9 vftable slots, 0x2C bytes)
			class AnimationChargeAction : public fight::Action
			{
			public:
				// 0x100A1960
				AnimationChargeAction(AnimationChargeTrack* newTrack, engine::GameObjectHandle newTarget);
				// 0x100A10A0
				virtual ~AnimationChargeAction();

				// vftable slot 5 (0x100A1A00)
				virtual bool Slot5(int arg, float value);
				// vftable slot 6 (0x100A10E0)
				virtual void Slot6();
				// vftable slot 7 (0x100A1C70)
				virtual bool Slot7(int arg, float value);

				core::Link<AnimationChargeTrack> link;  // +0x1C
				engine::GameObjectHandle target;  // +0x28
				choreo::Driver* driver;  // +0x2C
			};

			// ---- actions end
		}
	}
}

#endif
