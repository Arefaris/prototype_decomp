// Fight items of the motion group: ShootCheckAmmoCountCondition, ShootCheckCooldownTimeCondition, ShootCurrentWeaponConfigurationCondition, ShootCheckOverheatingCondition, ShootSwitchWeaponConfigurationTrack, ShootSetUserProfileTrack, ShootCalculateHitPositionTrack, ShootSetAmmoProfileTrack, ReloadTrack, ShootTrack, ShootAutoTargetTrack, SetFireRateTimerTrack, ShootSelectWeaponConfigurationTrack, ShootTakeAmmoFromParentTrack (unit 0x101ACEE0 - 0x101B22B0; no assert path, the file name is a guess).
#ifndef PROTO_FIGHTITEMS_MOTION_MOTION_SHOOT_H
#define PROTO_FIGHTITEMS_MOTION_MOTION_SHOOT_H

#include "code/engine/fight/bitfieldproperty.h"
#include "code/proto/fightitems/motion/motiondata.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			// RTTI: proto::fightitems::motion::ShootCheckAmmoCountCondition (10 vftable slots, 0x30 bytes)
			class ShootCheckAmmoCountCondition : public fight::Condition
			{
			public:
				// 0x101ADC30
				ShootCheckAmmoCountCondition();
				virtual ~ShootCheckAmmoCountCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101116A0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetTestOnParent(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetWeaponEntry(const fight::Name& newValue);
				bool SetCompare(int newValue);
				bool SetRequiredAmount(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name grabSlot;  // +0x10
					fight::Name weaponEntry;  // +0x18
					int compare;  // +0x20
					int requiredAmount;  // +0x24
					bool testOnParent;  // +0x28
					unsigned char unknown29[0x7];
			};

			extern fight::Property** gShootCheckAmmoCountConditionProperties;
			fight::ConditionFactory* CreateShootCheckAmmoCountConditionFactory(const char* name);
			void RegisterShootCheckAmmoCountConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ShootCheckCooldownTimeCondition (10 vftable slots, 0x30 bytes)
			class ShootCheckCooldownTimeCondition : public fight::Condition
			{
			public:
				// 0x101ADC90
				ShootCheckCooldownTimeCondition();
				virtual ~ShootCheckCooldownTimeCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101117C0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetTestOnParent(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetWeaponEntry(const fight::Name& newValue);
				bool SetCompare(int newValue);
				bool SetRequiredTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name grabSlot;  // +0x10
					fight::Name weaponEntry;  // +0x18
					float requiredTime;  // +0x20
					int compare;  // +0x24
					bool testOnParent;  // +0x28
					unsigned char unknown29[0x7];
			};

			extern fight::Property** gShootCheckCooldownTimeConditionProperties;
			fight::ConditionFactory* CreateShootCheckCooldownTimeConditionFactory(const char* name);
			void RegisterShootCheckCooldownTimeConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ShootCurrentWeaponConfigurationCondition (10 vftable slots, 0x20 bytes)
			class ShootCurrentWeaponConfigurationCondition : public fight::Condition
			{
			public:
				// 0x101ADCF0
				ShootCurrentWeaponConfigurationCondition();
				virtual ~ShootCurrentWeaponConfigurationCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101119E0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetWeaponConfiguration(const fight::Name& newValue);
				bool SetMatch(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name weaponConfiguration;  // +0x10
					bool match;  // +0x18
					unsigned char unknown19[0x7];
			};

			extern fight::Property** gShootCurrentWeaponConfigurationConditionProperties;
			fight::ConditionFactory* CreateShootCurrentWeaponConfigurationConditionFactory(const char* name);
			void RegisterShootCurrentWeaponConfigurationConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ShootCheckOverheatingCondition (10 vftable slots, 0x28 bytes)
			class ShootCheckOverheatingCondition : public fight::Condition
			{
			public:
				// 0x101ADD30
				ShootCheckOverheatingCondition();
				virtual ~ShootCheckOverheatingCondition();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9 (0x101118D0, another unit)
				virtual bool Evaluate(int a, int b, int c, int d);

				// The members the properties write
				bool SetTestOnParent(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetWeaponEntry(const fight::Name& newValue);
				bool SetMatch(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned char unknownC[0x4];
					fight::Name grabSlot;  // +0x10
					fight::Name weaponEntry;  // +0x18
					bool match;  // +0x20
					bool testOnParent;  // +0x21
					unsigned char unknown22[0x6];
			};

			extern fight::Property** gShootCheckOverheatingConditionProperties;
			fight::ConditionFactory* CreateShootCheckOverheatingConditionFactory(const char* name);
			void RegisterShootCheckOverheatingConditionFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ShootSwitchWeaponConfigurationTrack (16 vftable slots, 0x18 bytes)
			class ShootSwitchWeaponConfigurationTrack : public fight::Track
			{
			public:
				// 0x101AD440
				ShootSwitchWeaponConfigurationTrack();
				virtual ~ShootSwitchWeaponConfigurationTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10114520, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetApplyOnParent(bool newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float timeBegin;  // +0x10
					bool applyOnParent;  // +0x14
					unsigned char unknown15[0x3];
			};

			extern fight::Property** gShootSwitchWeaponConfigurationTrackProperties;
			fight::TrackFactory* CreateShootSwitchWeaponConfigurationTrackFactory(const char* name);
			void RegisterShootSwitchWeaponConfigurationTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ShootSetUserProfileTrack (16 vftable slots, 0x30 bytes)
			class ShootSetUserProfileTrack : public fight::Track
			{
			public:
				// 0x101ADDB0
				ShootSetUserProfileTrack();
				virtual ~ShootSetUserProfileTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101130F0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetApplyOnParent(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetWeaponEntry(const fight::Name& newValue);
				bool SetProfileName(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					fight::Name profileName;  // +0x18
					fight::Name weaponEntry;  // +0x20
					bool applyOnParent;  // +0x28
					unsigned char unknown29[0x7];
			};

			extern fight::Property** gShootSetUserProfileTrackProperties;
			fight::TrackFactory* CreateShootSetUserProfileTrackFactory(const char* name);
			void RegisterShootSetUserProfileTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ShootCalculateHitPositionTrack (16 vftable slots, 0x48 bytes)
			class ShootCalculateHitPositionTrack : public fight::Track
			{
			public:
				// 0x101ADE30
				ShootCalculateHitPositionTrack();
				virtual ~ShootCalculateHitPositionTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101141F0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetApplyOnParent(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetWeaponEntry(const fight::Name& newValue);
				bool SetShooter(const fight::Name& newValue);
				bool SetAmmoProfile(const fight::Name& newValue);
				bool SetUserProfile(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name ammoProfile;  // +0x10
					fight::Name grabSlot;  // +0x18
					fight::Name shooter;  // +0x20
					fight::Name userProfile;  // +0x28
					fight::Name weaponEntry;  // +0x30
					float timeBegin;  // +0x38
					float timeEnd;  // +0x3C
					bool applyOnParent;  // +0x40
					unsigned char unknown41[0x7];
			};

			extern fight::Property** gShootCalculateHitPositionTrackProperties;
			fight::TrackFactory* CreateShootCalculateHitPositionTrackFactory(const char* name);
			void RegisterShootCalculateHitPositionTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ShootSetAmmoProfileTrack (16 vftable slots, 0x30 bytes)
			class ShootSetAmmoProfileTrack : public fight::Track
			{
			public:
				// 0x101ADED0
				ShootSetAmmoProfileTrack();
				virtual ~ShootSetAmmoProfileTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10113010, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetApplyOnParent(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetWeaponEntry(const fight::Name& newValue);
				bool SetProfileName(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name grabSlot;  // +0x10
					fight::Name profileName;  // +0x18
					fight::Name weaponEntry;  // +0x20
					bool applyOnParent;  // +0x28
					unsigned char unknown29[0x7];
			};

			extern fight::Property** gShootSetAmmoProfileTrackProperties;
			fight::TrackFactory* CreateShootSetAmmoProfileTrackFactory(const char* name);
			void RegisterShootSetAmmoProfileTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ReloadTrack (16 vftable slots, 0x28 bytes)
			class ReloadTrack : public fight::Track
			{
			public:
				// 0x101ADF50
				ReloadTrack();
				virtual ~ReloadTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10112F10, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetApplyOnParent(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetAmmoProfile(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name ammoProfile;  // +0x10
					fight::Name grabSlot;  // +0x18
					bool applyOnParent;  // +0x20
					unsigned char unknown21[0x7];
			};

			extern fight::Property** gReloadTrackProperties;
			fight::TrackFactory* CreateReloadTrackFactory(const char* name);
			void RegisterReloadTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ShootTrack (17 vftable slots, 0x60 bytes)
			class ShootTrack : public fight::Track
			{
			public:
				// 0x101ADFC0
				ShootTrack();
				virtual ~ShootTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10114100, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);
				// vftable slot 16: whether the track overrides a property
				virtual bool Slot16(int index);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetApplyOnParent(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetWeaponEntry(const fight::Name& newValue);
				bool SetShooter(const fight::Name& newValue);
				bool SetAmmoProfile(const fight::Name& newValue);
				bool SetUserProfile(const fight::Name& newValue);
				bool SetFixedDirection(bool newValue);
				// 0x101AD590: sets or clears the override bits of a group's members (name guess)
				void ApplyGroup(int group, bool value);
				bool SetFixedDirectionSpace(int newValue);
				bool SetFixedDirectionDirection(const math::Vector& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					unsigned __int64 overrideMask;  // +0x10
					fight::Name ammoProfile;  // +0x18
					fight::Name grabSlot;  // +0x20
					fight::Name shooter;  // +0x28
					fight::Name userProfile;  // +0x30
					fight::Name weaponEntry;  // +0x38
					math::Vector fixedDirectionDirection;  // +0x40
					float timeBegin;  // +0x4C
					float timeEnd;  // +0x50
					int fixedDirectionSpace;  // +0x54
					bool applyOnParent;  // +0x58
					bool fixedDirection;  // +0x59
					unsigned char unknown5A[0x6];
			};

			extern fight::Property** gShootTrackProperties;
			fight::TrackFactory* CreateShootTrackFactory(const char* name);
			void RegisterShootTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ShootAutoTargetTrack (16 vftable slots, 0x34 bytes)
			class ShootAutoTargetTrack : public fight::Track
			{
			public:
				// 0x101AD670
				ShootAutoTargetTrack();
				virtual ~ShootAutoTargetTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10114480, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetArc(float newValue);
				bool SetMaxDistance(float newValue);
				bool SetUseSecondCone(bool newValue);
				bool SetArc2(float newValue);
				bool SetMaxDistance2(float newValue);
				bool SetMinPriorityTargetClass(int newValue);
				bool SetMaxPriorityTargetClass(int newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					float arc;  // +0x10
					float arc2;  // +0x14
					float maxDistance;  // +0x18
					float maxDistance2;  // +0x1C
					float timeBegin;  // +0x20
					float timeEnd;  // +0x24
					int maxPriorityTargetClass;  // +0x28
					int minPriorityTargetClass;  // +0x2C
					bool useSecondCone;  // +0x30
					unsigned char unknown31[0x3];
			};

			extern fight::Property** gShootAutoTargetTrackProperties;
			fight::TrackFactory* CreateShootAutoTargetTrackFactory(const char* name);
			void RegisterShootAutoTargetTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::SetFireRateTimerTrack (16 vftable slots, 0x50 bytes)
			class SetFireRateTimerTrack : public fight::Track
			{
			public:
				// 0x101AE110
				SetFireRateTimerTrack();
				virtual ~SetFireRateTimerTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10114570, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetTimeEnd(float newValue);
				bool SetTimer(const fight::Name& newValue);
				bool SetIncrementing(bool newValue);
				bool SetApplyOnParent(bool newValue);
				bool SetGrabSlot(const fight::Name& newValue);
				bool SetWeaponEntry(const fight::Name& newValue);
				bool SetShooter(const fight::Name& newValue);
				bool SetAmmoProfile(const fight::Name& newValue);
				bool SetUserProfile(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name ammoProfile;  // +0x10
					fight::Name grabSlot;  // +0x18
					fight::Name shooter;  // +0x20
					fight::Name timer;  // +0x28
					fight::Name userProfile;  // +0x30
					fight::Name weaponEntry;  // +0x38
					float timeBegin;  // +0x40
					float timeEnd;  // +0x44
					bool applyOnParent;  // +0x48
					bool incrementing;  // +0x49
					unsigned char unknown4A[0x6];
			};

			extern fight::Property** gSetFireRateTimerTrackProperties;
			fight::TrackFactory* CreateSetFireRateTimerTrackFactory(const char* name);
			void RegisterSetFireRateTimerTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ShootSelectWeaponConfigurationTrack (16 vftable slots, 0x20 bytes)
			class ShootSelectWeaponConfigurationTrack : public fight::Track
			{
			public:
				// 0x101AE1C0
				ShootSelectWeaponConfigurationTrack();
				virtual ~ShootSelectWeaponConfigurationTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x101144D0, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetApplyOnParent(bool newValue);
				bool SetWeaponConfiguration(const fight::Name& newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name weaponConfiguration;  // +0x10
					float timeBegin;  // +0x18
					bool applyOnParent;  // +0x1C
					unsigned char unknown1D[0x3];
			};

			extern fight::Property** gShootSelectWeaponConfigurationTrackProperties;
			fight::TrackFactory* CreateShootSelectWeaponConfigurationTrackFactory(const char* name);
			void RegisterShootSelectWeaponConfigurationTrackFactory(fight::TrackRegistry* registry, const char* name);

			// RTTI: proto::fightitems::motion::ShootTakeAmmoFromParentTrack (16 vftable slots, 0x68 bytes)
			class ShootTakeAmmoFromParentTrack : public fight::Track
			{
			public:
				// 0x101AE230
				ShootTakeAmmoFromParentTrack();
				virtual ~ShootTakeAmmoFromParentTrack();

				// vftable slot 0
				virtual fight::Property* GetProperty(int index);
				// vftable slot 9
				virtual float GetTimeBegin() const;
				// vftable slot 10
				virtual float Slot10() const;
				// vftable slot 15 (0x10114310, another unit)
				virtual fight::Action* CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner);

				// The members the properties write
				bool SetTimeBegin(float newValue);
				bool SetWeaponGrabSlot(const fight::Name& newValue);
				bool SetReceiverGrabSlot(const fight::Name& newValue);
				bool SetReceiverJoint(const fight::Name& newValue);
				bool SetReceiverPositionOffset(const math::Vector& newValue);
				bool SetReceiverRotationOffset(const math::Vector& newValue);
				bool SetChildJoint(const fight::Name& newValue);
				bool SetChildPositionOffset(const math::Vector& newValue);
				bool SetChildRotationOffset(const math::Vector& newValue);
				bool SetBlendTime(float newValue);

				// The property list, built once and freed again
				static void RegisterProperties();
				static void ClearProperties();

					fight::Name childJoint;  // +0x10
					fight::Name receiverGrabSlot;  // +0x18
					fight::Name receiverJoint;  // +0x20
					fight::Name weaponGrabSlot;  // +0x28
					math::Vector childPositionOffset;  // +0x30
					math::Vector childRotationOffset;  // +0x3C
					math::Vector receiverPositionOffset;  // +0x48
					math::Vector receiverRotationOffset;  // +0x54
					float blendTime;  // +0x60
					float timeBegin;  // +0x64
			};

			extern fight::Property** gShootTakeAmmoFromParentTrackProperties;
			fight::TrackFactory* CreateShootTakeAmmoFromParentTrackFactory(const char* name);
			void RegisterShootTakeAmmoFromParentTrackFactory(fight::TrackRegistry* registry, const char* name);

		}
	}
}

#endif
