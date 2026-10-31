// Fight items of the motion group: ShootCheckAmmoCountCondition, ShootCheckCooldownTimeCondition, ShootCurrentWeaponConfigurationCondition, ShootCheckOverheatingCondition, ShootSwitchWeaponConfigurationTrack, ShootSetUserProfileTrack, ShootCalculateHitPositionTrack, ShootSetAmmoProfileTrack, ReloadTrack, ShootTrack, ShootAutoTargetTrack, SetFireRateTimerTrack, ShootSelectWeaponConfigurationTrack, ShootTakeAmmoFromParentTrack (unit 0x101ACEE0 - 0x101B22B0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_shoot.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			extern const int gShootTrackFixedDirectionMembers[];  // 0x1102C124
			fight::Property** gShootCheckAmmoCountConditionProperties;  // 0x11254A88

			// FUNCTION: ENGINE 0x101ACEE0
			bool ShootCheckAmmoCountCondition::SetTestOnParent(bool newValue)
			{
				testOnParent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD7B0
			bool ShootCheckAmmoCountCondition::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD7D0
			bool ShootCheckAmmoCountCondition::SetWeaponEntry(const fight::Name& newValue)
			{
				weaponEntry = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ACEF0
			bool ShootCheckAmmoCountCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ACF00
			bool ShootCheckAmmoCountCondition::SetRequiredAmount(int newValue)
			{
				requiredAmount = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD350
			fight::Property* ShootCheckAmmoCountCondition::GetProperty(int index)
			{
				return gShootCheckAmmoCountConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101AD370
			void ShootCheckAmmoCountCondition::ClearProperties()
			{
				fight::FreePropertyList(&gShootCheckAmmoCountConditionProperties);
			}

			// FUNCTION: ENGINE 0x101ADC30
			ShootCheckAmmoCountCondition::ShootCheckAmmoCountCondition() : fight::Condition(0), compare(0), requiredAmount(1), testOnParent(false)
			{
			}

			// FUNCTION: ENGINE 0x101ADC80
			ShootCheckAmmoCountCondition::~ShootCheckAmmoCountCondition()
			{
			}

			// FUNCTION: ENGINE 0x101B0550
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShootCheckAmmoCountCondition::RegisterProperties()
			{
				if (gShootCheckAmmoCountConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ShootCheckAmmoCountCondition>("testOnParent", &ShootCheckAmmoCountCondition::SetTestOnParent);
					properties[0] = property;
					property = new fight::PropertyNameList<ShootCheckAmmoCountCondition>("grabSlot", &ShootCheckAmmoCountCondition::SetGrabSlot);
					properties[1] = property;
					property = new fight::PropertyNameList<ShootCheckAmmoCountCondition>("weaponEntry", &ShootCheckAmmoCountCondition::SetWeaponEntry);
					properties[2] = property;
					property = new fight::PropertyEnumConstList<ShootCheckAmmoCountCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ShootCheckAmmoCountCondition::SetCompare);
					properties[3] = property;
					property = new fight::PropertyIntConstRange<ShootCheckAmmoCountCondition>("requiredAmount", &ShootCheckAmmoCountCondition::SetRequiredAmount);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gShootCheckAmmoCountConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AF580
			fight::ConditionFactory* CreateShootCheckAmmoCountConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShootCheckAmmoCountCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AFBB0
			void RegisterShootCheckAmmoCountConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShootCheckAmmoCountCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gShootCheckCooldownTimeConditionProperties;  // 0x11254A8C

			// FUNCTION: ENGINE 0x101ACF10
			bool ShootCheckCooldownTimeCondition::SetTestOnParent(bool newValue)
			{
				testOnParent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD7F0
			bool ShootCheckCooldownTimeCondition::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD810
			bool ShootCheckCooldownTimeCondition::SetWeaponEntry(const fight::Name& newValue)
			{
				weaponEntry = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ACF20
			bool ShootCheckCooldownTimeCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ACF30
			bool ShootCheckCooldownTimeCondition::SetRequiredTime(float newValue)
			{
				requiredTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD380
			fight::Property* ShootCheckCooldownTimeCondition::GetProperty(int index)
			{
				return gShootCheckCooldownTimeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101AD3A0
			void ShootCheckCooldownTimeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gShootCheckCooldownTimeConditionProperties);
			}

			// FUNCTION: ENGINE 0x101ADC90
			ShootCheckCooldownTimeCondition::ShootCheckCooldownTimeCondition() : fight::Condition(0), requiredTime(1.0f), compare(0), testOnParent(false)
			{
			}

			// FUNCTION: ENGINE 0x101ADCE0
			ShootCheckCooldownTimeCondition::~ShootCheckCooldownTimeCondition()
			{
			}

			// FUNCTION: ENGINE 0x101B0700
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShootCheckCooldownTimeCondition::RegisterProperties()
			{
				if (gShootCheckCooldownTimeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ShootCheckCooldownTimeCondition>("testOnParent", &ShootCheckCooldownTimeCondition::SetTestOnParent);
					properties[0] = property;
					property = new fight::PropertyNameList<ShootCheckCooldownTimeCondition>("grabSlot", &ShootCheckCooldownTimeCondition::SetGrabSlot);
					properties[1] = property;
					property = new fight::PropertyNameList<ShootCheckCooldownTimeCondition>("weaponEntry", &ShootCheckCooldownTimeCondition::SetWeaponEntry);
					properties[2] = property;
					property = new fight::PropertyEnumConstList<ShootCheckCooldownTimeCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &ShootCheckCooldownTimeCondition::SetCompare);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<ShootCheckCooldownTimeCondition>("requiredTime", &ShootCheckCooldownTimeCondition::SetRequiredTime);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gShootCheckCooldownTimeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AF5B0
			fight::ConditionFactory* CreateShootCheckCooldownTimeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShootCheckCooldownTimeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AFBE0
			void RegisterShootCheckCooldownTimeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShootCheckCooldownTimeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gShootCurrentWeaponConfigurationConditionProperties;  // 0x11254A90

			// FUNCTION: ENGINE 0x101AD830
			bool ShootCurrentWeaponConfigurationCondition::SetWeaponConfiguration(const fight::Name& newValue)
			{
				weaponConfiguration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ACF50
			bool ShootCurrentWeaponConfigurationCondition::SetMatch(bool newValue)
			{
				match = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD3B0
			fight::Property* ShootCurrentWeaponConfigurationCondition::GetProperty(int index)
			{
				return gShootCurrentWeaponConfigurationConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101AD3D0
			void ShootCurrentWeaponConfigurationCondition::ClearProperties()
			{
				fight::FreePropertyList(&gShootCurrentWeaponConfigurationConditionProperties);
			}

			// FUNCTION: ENGINE 0x101ADCF0
			ShootCurrentWeaponConfigurationCondition::ShootCurrentWeaponConfigurationCondition() : fight::Condition(0), match(true)
			{
			}

			// FUNCTION: ENGINE 0x101ADD20
			ShootCurrentWeaponConfigurationCondition::~ShootCurrentWeaponConfigurationCondition()
			{
			}

			// FUNCTION: ENGINE 0x101B08B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShootCurrentWeaponConfigurationCondition::RegisterProperties()
			{
				if (gShootCurrentWeaponConfigurationConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyNameList<ShootCurrentWeaponConfigurationCondition>("weaponConfiguration", &ShootCurrentWeaponConfigurationCondition::SetWeaponConfiguration);
					properties[0] = property;
					property = new fight::PropertyBool<ShootCurrentWeaponConfigurationCondition>("match", &ShootCurrentWeaponConfigurationCondition::SetMatch);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gShootCurrentWeaponConfigurationConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AF5E0
			fight::ConditionFactory* CreateShootCurrentWeaponConfigurationConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShootCurrentWeaponConfigurationCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AFC10
			void RegisterShootCurrentWeaponConfigurationConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShootCurrentWeaponConfigurationCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gShootCheckOverheatingConditionProperties;  // 0x11254A94

			// FUNCTION: ENGINE 0x101ACF60
			bool ShootCheckOverheatingCondition::SetTestOnParent(bool newValue)
			{
				testOnParent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD850
			bool ShootCheckOverheatingCondition::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD870
			bool ShootCheckOverheatingCondition::SetWeaponEntry(const fight::Name& newValue)
			{
				weaponEntry = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ACF70
			bool ShootCheckOverheatingCondition::SetMatch(bool newValue)
			{
				match = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD3E0
			fight::Property* ShootCheckOverheatingCondition::GetProperty(int index)
			{
				return gShootCheckOverheatingConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101AD400
			void ShootCheckOverheatingCondition::ClearProperties()
			{
				fight::FreePropertyList(&gShootCheckOverheatingConditionProperties);
			}

			// FUNCTION: ENGINE 0x101ADD30
			ShootCheckOverheatingCondition::ShootCheckOverheatingCondition() : fight::Condition(0), match(false), testOnParent(false)
			{
			}

			// FUNCTION: ENGINE 0x101ADD70
			ShootCheckOverheatingCondition::~ShootCheckOverheatingCondition()
			{
			}

			// FUNCTION: ENGINE 0x101B0990
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShootCheckOverheatingCondition::RegisterProperties()
			{
				if (gShootCheckOverheatingConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ShootCheckOverheatingCondition>("testOnParent", &ShootCheckOverheatingCondition::SetTestOnParent);
					properties[0] = property;
					property = new fight::PropertyNameList<ShootCheckOverheatingCondition>("grabSlot", &ShootCheckOverheatingCondition::SetGrabSlot);
					properties[1] = property;
					property = new fight::PropertyNameList<ShootCheckOverheatingCondition>("weaponEntry", &ShootCheckOverheatingCondition::SetWeaponEntry);
					properties[2] = property;
					property = new fight::PropertyBool<ShootCheckOverheatingCondition>("match", &ShootCheckOverheatingCondition::SetMatch);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gShootCheckOverheatingConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AF610
			fight::ConditionFactory* CreateShootCheckOverheatingConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShootCheckOverheatingCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AFC40
			void RegisterShootCheckOverheatingConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<ShootCheckOverheatingCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gShootSwitchWeaponConfigurationTrackProperties;  // 0x11254A98

			// FUNCTION: ENGINE 0x101ACF80
			bool ShootSwitchWeaponConfigurationTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ACFA0
			bool ShootSwitchWeaponConfigurationTrack::SetApplyOnParent(bool newValue)
			{
				applyOnParent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD410
			fight::Property* ShootSwitchWeaponConfigurationTrack::GetProperty(int index)
			{
				return gShootSwitchWeaponConfigurationTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101AD430
			void ShootSwitchWeaponConfigurationTrack::ClearProperties()
			{
				fight::FreePropertyList(&gShootSwitchWeaponConfigurationTrackProperties);
			}

			// FUNCTION: ENGINE 0x101AD440
			ShootSwitchWeaponConfigurationTrack::ShootSwitchWeaponConfigurationTrack() : timeBegin(0.0f), applyOnParent(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101AD470
			float ShootSwitchWeaponConfigurationTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101AD480
			float ShootSwitchWeaponConfigurationTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101AD490
			ShootSwitchWeaponConfigurationTrack::~ShootSwitchWeaponConfigurationTrack()
			{
			}

			// FUNCTION: ENGINE 0x101AF820
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShootSwitchWeaponConfigurationTrack::RegisterProperties()
			{
				if (gShootSwitchWeaponConfigurationTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ShootSwitchWeaponConfigurationTrack>("timeBegin", &ShootSwitchWeaponConfigurationTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyBool<ShootSwitchWeaponConfigurationTrack>("applyOnParent", &ShootSwitchWeaponConfigurationTrack::SetApplyOnParent);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gShootSwitchWeaponConfigurationTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AF640
			fight::TrackFactory* CreateShootSwitchWeaponConfigurationTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShootSwitchWeaponConfigurationTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AFC70
			void RegisterShootSwitchWeaponConfigurationTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShootSwitchWeaponConfigurationTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gShootSetUserProfileTrackProperties;  // 0x11254A9C

			// FUNCTION: ENGINE 0x101ACFB0
			bool ShootSetUserProfileTrack::SetApplyOnParent(bool newValue)
			{
				applyOnParent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD890
			bool ShootSetUserProfileTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD8B0
			bool ShootSetUserProfileTrack::SetWeaponEntry(const fight::Name& newValue)
			{
				weaponEntry = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD8D0
			bool ShootSetUserProfileTrack::SetProfileName(const fight::Name& newValue)
			{
				profileName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD4A0
			fight::Property* ShootSetUserProfileTrack::GetProperty(int index)
			{
				return gShootSetUserProfileTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101AD4C0
			void ShootSetUserProfileTrack::ClearProperties()
			{
				fight::FreePropertyList(&gShootSetUserProfileTrackProperties);
			}

			// FUNCTION: ENGINE 0x101ADDB0
			ShootSetUserProfileTrack::ShootSetUserProfileTrack() : applyOnParent(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101ADE00
			float ShootSetUserProfileTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101ADE10
			float ShootSetUserProfileTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101ADE20
			ShootSetUserProfileTrack::~ShootSetUserProfileTrack()
			{
			}

			// FUNCTION: ENGINE 0x101B0AE0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShootSetUserProfileTrack::RegisterProperties()
			{
				if (gShootSetUserProfileTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ShootSetUserProfileTrack>("applyOnParent", &ShootSetUserProfileTrack::SetApplyOnParent);
					properties[0] = property;
					property = new fight::PropertyNameList<ShootSetUserProfileTrack>("grabSlot", &ShootSetUserProfileTrack::SetGrabSlot);
					properties[1] = property;
					property = new fight::PropertyNameList<ShootSetUserProfileTrack>("weaponEntry", &ShootSetUserProfileTrack::SetWeaponEntry);
					properties[2] = property;
					property = new fight::PropertyName<ShootSetUserProfileTrack>("profileName", &ShootSetUserProfileTrack::SetProfileName);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gShootSetUserProfileTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AF670
			fight::TrackFactory* CreateShootSetUserProfileTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShootSetUserProfileTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AFCA0
			void RegisterShootSetUserProfileTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShootSetUserProfileTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gShootCalculateHitPositionTrackProperties;  // 0x11254AA0

			// FUNCTION: ENGINE 0x101ACFC0
			bool ShootCalculateHitPositionTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ACFE0
			bool ShootCalculateHitPositionTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD000
			bool ShootCalculateHitPositionTrack::SetApplyOnParent(bool newValue)
			{
				applyOnParent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD8F0
			bool ShootCalculateHitPositionTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD910
			bool ShootCalculateHitPositionTrack::SetWeaponEntry(const fight::Name& newValue)
			{
				weaponEntry = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD930
			bool ShootCalculateHitPositionTrack::SetShooter(const fight::Name& newValue)
			{
				shooter = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD950
			bool ShootCalculateHitPositionTrack::SetAmmoProfile(const fight::Name& newValue)
			{
				ammoProfile = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD970
			bool ShootCalculateHitPositionTrack::SetUserProfile(const fight::Name& newValue)
			{
				userProfile = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD4D0
			fight::Property* ShootCalculateHitPositionTrack::GetProperty(int index)
			{
				return gShootCalculateHitPositionTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101AD4F0
			void ShootCalculateHitPositionTrack::ClearProperties()
			{
				fight::FreePropertyList(&gShootCalculateHitPositionTrackProperties);
			}

			// FUNCTION: ENGINE 0x101ADE30
			ShootCalculateHitPositionTrack::ShootCalculateHitPositionTrack() : timeBegin(0.0f), timeEnd(0.0f), applyOnParent(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101ADEA0
			float ShootCalculateHitPositionTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101ADEB0
			float ShootCalculateHitPositionTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101ADEC0
			ShootCalculateHitPositionTrack::~ShootCalculateHitPositionTrack()
			{
			}

			// FUNCTION: ENGINE 0x101B0C30
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShootCalculateHitPositionTrack::RegisterProperties()
			{
				if (gShootCalculateHitPositionTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ShootCalculateHitPositionTrack>("timeBegin", &ShootCalculateHitPositionTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ShootCalculateHitPositionTrack>("timeEnd", &ShootCalculateHitPositionTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<ShootCalculateHitPositionTrack>("applyOnParent", &ShootCalculateHitPositionTrack::SetApplyOnParent);
					properties[2] = property;
					property = new fight::PropertyNameList<ShootCalculateHitPositionTrack>("grabSlot", &ShootCalculateHitPositionTrack::SetGrabSlot);
					properties[3] = property;
					property = new fight::PropertyNameList<ShootCalculateHitPositionTrack>("weaponEntry", &ShootCalculateHitPositionTrack::SetWeaponEntry);
					properties[4] = property;
					property = new fight::PropertyNameList<ShootCalculateHitPositionTrack>("shooter", &ShootCalculateHitPositionTrack::SetShooter);
					properties[5] = property;
					property = new fight::PropertyName<ShootCalculateHitPositionTrack>("ammoProfile", &ShootCalculateHitPositionTrack::SetAmmoProfile);
					properties[6] = property;
					property = new fight::PropertyName<ShootCalculateHitPositionTrack>("userProfile", &ShootCalculateHitPositionTrack::SetUserProfile);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gShootCalculateHitPositionTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AF6A0
			fight::TrackFactory* CreateShootCalculateHitPositionTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShootCalculateHitPositionTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AFCD0
			void RegisterShootCalculateHitPositionTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShootCalculateHitPositionTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gShootSetAmmoProfileTrackProperties;  // 0x11254AA4

			// FUNCTION: ENGINE 0x101AD010
			bool ShootSetAmmoProfileTrack::SetApplyOnParent(bool newValue)
			{
				applyOnParent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD990
			bool ShootSetAmmoProfileTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD9B0
			bool ShootSetAmmoProfileTrack::SetWeaponEntry(const fight::Name& newValue)
			{
				weaponEntry = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD9D0
			bool ShootSetAmmoProfileTrack::SetProfileName(const fight::Name& newValue)
			{
				profileName = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD500
			fight::Property* ShootSetAmmoProfileTrack::GetProperty(int index)
			{
				return gShootSetAmmoProfileTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101AD520
			void ShootSetAmmoProfileTrack::ClearProperties()
			{
				fight::FreePropertyList(&gShootSetAmmoProfileTrackProperties);
			}

			// FUNCTION: ENGINE 0x101ADED0
			ShootSetAmmoProfileTrack::ShootSetAmmoProfileTrack() : applyOnParent(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101ADF20
			float ShootSetAmmoProfileTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101ADF30
			float ShootSetAmmoProfileTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101ADF40
			ShootSetAmmoProfileTrack::~ShootSetAmmoProfileTrack()
			{
			}

			// FUNCTION: ENGINE 0x101B0E80
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShootSetAmmoProfileTrack::RegisterProperties()
			{
				if (gShootSetAmmoProfileTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ShootSetAmmoProfileTrack>("applyOnParent", &ShootSetAmmoProfileTrack::SetApplyOnParent);
					properties[0] = property;
					property = new fight::PropertyNameList<ShootSetAmmoProfileTrack>("grabSlot", &ShootSetAmmoProfileTrack::SetGrabSlot);
					properties[1] = property;
					property = new fight::PropertyNameList<ShootSetAmmoProfileTrack>("weaponEntry", &ShootSetAmmoProfileTrack::SetWeaponEntry);
					properties[2] = property;
					property = new fight::PropertyName<ShootSetAmmoProfileTrack>("profileName", &ShootSetAmmoProfileTrack::SetProfileName);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gShootSetAmmoProfileTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AF6D0
			fight::TrackFactory* CreateShootSetAmmoProfileTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShootSetAmmoProfileTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AFD00
			void RegisterShootSetAmmoProfileTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShootSetAmmoProfileTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gReloadTrackProperties;  // 0x11254AA8

			// FUNCTION: ENGINE 0x101AD020
			bool ReloadTrack::SetApplyOnParent(bool newValue)
			{
				applyOnParent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD9F0
			bool ReloadTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ADA10
			bool ReloadTrack::SetAmmoProfile(const fight::Name& newValue)
			{
				ammoProfile = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD530
			fight::Property* ReloadTrack::GetProperty(int index)
			{
				return gReloadTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101AD550
			void ReloadTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReloadTrackProperties);
			}

			// FUNCTION: ENGINE 0x101ADF50
			ReloadTrack::ReloadTrack() : applyOnParent(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101ADF90
			float ReloadTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101ADFA0
			float ReloadTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101ADFB0
			ReloadTrack::~ReloadTrack()
			{
			}

			// FUNCTION: ENGINE 0x101B0FD0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReloadTrack::RegisterProperties()
			{
				if (gReloadTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<ReloadTrack>("applyOnParent", &ReloadTrack::SetApplyOnParent);
					properties[0] = property;
					property = new fight::PropertyNameList<ReloadTrack>("grabSlot", &ReloadTrack::SetGrabSlot);
					properties[1] = property;
					property = new fight::PropertyName<ReloadTrack>("ammoProfile", &ReloadTrack::SetAmmoProfile);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gReloadTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AF700
			fight::TrackFactory* CreateReloadTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReloadTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AFD30
			void RegisterReloadTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReloadTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gShootTrackProperties;  // 0x11254AAC

			// FUNCTION: ENGINE 0x101AD030
			bool ShootTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD050
			bool ShootTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD070
			bool ShootTrack::SetApplyOnParent(bool newValue)
			{
				applyOnParent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ADA30
			bool ShootTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ADA50
			bool ShootTrack::SetWeaponEntry(const fight::Name& newValue)
			{
				weaponEntry = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ADA70
			bool ShootTrack::SetShooter(const fight::Name& newValue)
			{
				shooter = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ADA90
			bool ShootTrack::SetAmmoProfile(const fight::Name& newValue)
			{
				ammoProfile = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ADAB0
			bool ShootTrack::SetUserProfile(const fight::Name& newValue)
			{
				userProfile = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD080
			bool ShootTrack::SetFixedDirectionSpace(int newValue)
			{
				fixedDirectionSpace = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD090
			bool ShootTrack::SetFixedDirectionDirection(const math::Vector& newValue)
			{
				fixedDirectionDirection.x = newValue.x;
				fixedDirectionDirection.y = newValue.y;
				fixedDirectionDirection.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD590
			// NONMATCHING: the engine keeps the group flag's result only in the argument slot and pushes a register copy for the recursive call; ours holds it in a register (best 31%; same as HideHUDTrack::ApplyGroup)
#ifdef NONMATCHING
			void ShootTrack::ApplyGroup(int group, bool value)
			{
				if (group != 0)
				{
					return;
				}
				if (value && !fixedDirection)
				{
					value = false;
				}
				for (int i = 0; gShootTrackFixedDirectionMembers[i] != -1; i++)
				{
					const int* member = &gShootTrackFixedDirectionMembers[i];
					unsigned __int64 bit = 1ui64 << *member;
					if (value)
					{
						overrideMask |= bit;
					}
					else
					{
						overrideMask &= ~bit;
					}
					ApplyGroup(*member, value);
				}
			}
#endif

			// FUNCTION: ENGINE 0x101AE060
			bool ShootTrack::Slot16(int index)
			{
				return (overrideMask & (1ui64 << index)) != 0;
			}

			// FUNCTION: ENGINE 0x101AE0C0
			bool ShootTrack::SetFixedDirection(bool newValue)
			{
				fixedDirection = newValue;
				ApplyGroup(0, newValue);
				return true;
			}

			// FUNCTION: ENGINE 0x101AD560
			fight::Property* ShootTrack::GetProperty(int index)
			{
				return gShootTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101AD580
			void ShootTrack::ClearProperties()
			{
				fight::FreePropertyList(&gShootTrackProperties);
			}

			// FUNCTION: ENGINE 0x101ADFC0
			ShootTrack::ShootTrack() : fixedDirectionDirection(0.0f, 0.0f, 0.0f), timeBegin(0.0f), timeEnd(0.0f), fixedDirectionSpace(0), applyOnParent(false), fixedDirection(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101AE050
			float ShootTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101AE0A0
			float ShootTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101AE0B0
			ShootTrack::~ShootTrack()
			{
			}

			// FUNCTION: ENGINE 0x101B10E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShootTrack::RegisterProperties()
			{
				if (gShootTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ShootTrack>("timeBegin", &ShootTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ShootTrack>("timeEnd", &ShootTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<ShootTrack>("applyOnParent", &ShootTrack::SetApplyOnParent);
					properties[2] = property;
					property = new fight::PropertyNameList<ShootTrack>("grabSlot", &ShootTrack::SetGrabSlot);
					properties[3] = property;
					property = new fight::PropertyNameList<ShootTrack>("weaponEntry", &ShootTrack::SetWeaponEntry);
					properties[4] = property;
					property = new fight::PropertyNameList<ShootTrack>("shooter", &ShootTrack::SetShooter);
					properties[5] = property;
					property = new fight::PropertyName<ShootTrack>("ammoProfile", &ShootTrack::SetAmmoProfile);
					properties[6] = property;
					property = new fight::PropertyName<ShootTrack>("userProfile", &ShootTrack::SetUserProfile);
					properties[7] = property;
					property = new fight::PropertyGroup<ShootTrack>("fixedDirection", &ShootTrack::SetFixedDirection, gShootTrackFixedDirectionMembers);
					properties[8] = property;
					property = new fight::PropertyEnumConstList<ShootTrack>("fixedDirectionSpace", gShootTrackFixedDirectionSpaceTable, gShootTrackFixedDirectionSpaceCount, &ShootTrack::SetFixedDirectionSpace);
					properties[9] = property;
					property = new fight::PropertyVector<ShootTrack>("fixedDirectionDirection", &ShootTrack::SetFixedDirectionDirection);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gShootTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AF730
			fight::TrackFactory* CreateShootTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShootTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AFD60
			void RegisterShootTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShootTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gShootAutoTargetTrackProperties;  // 0x11254AB0

			// FUNCTION: ENGINE 0x101AD0B0
			bool ShootAutoTargetTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD0D0
			bool ShootAutoTargetTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD0F0
			bool ShootAutoTargetTrack::SetArc(float newValue)
			{
				arc = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD110
			bool ShootAutoTargetTrack::SetMaxDistance(float newValue)
			{
				maxDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD130
			bool ShootAutoTargetTrack::SetUseSecondCone(bool newValue)
			{
				useSecondCone = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD140
			bool ShootAutoTargetTrack::SetArc2(float newValue)
			{
				arc2 = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD160
			bool ShootAutoTargetTrack::SetMaxDistance2(float newValue)
			{
				maxDistance2 = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD180
			bool ShootAutoTargetTrack::SetMinPriorityTargetClass(int newValue)
			{
				minPriorityTargetClass = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD190
			bool ShootAutoTargetTrack::SetMaxPriorityTargetClass(int newValue)
			{
				maxPriorityTargetClass = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD640
			fight::Property* ShootAutoTargetTrack::GetProperty(int index)
			{
				return gShootAutoTargetTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101AD660
			void ShootAutoTargetTrack::ClearProperties()
			{
				fight::FreePropertyList(&gShootAutoTargetTrackProperties);
			}

			// FUNCTION: ENGINE 0x101AD670
			ShootAutoTargetTrack::ShootAutoTargetTrack() : arc(3.1415927f), arc2(3.1415927f), maxDistance(25.0f), maxDistance2(25.0f), timeBegin(0.0f), timeEnd(-1.0f), maxPriorityTargetClass(48), minPriorityTargetClass(47), useSecondCone(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101AD6F0
			float ShootAutoTargetTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101AD700
			float ShootAutoTargetTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101AD710
			ShootAutoTargetTrack::~ShootAutoTargetTrack()
			{
			}

			// FUNCTION: ENGINE 0x101AF900
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShootAutoTargetTrack::RegisterProperties()
			{
				if (gShootAutoTargetTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ShootAutoTargetTrack>("timeBegin", &ShootAutoTargetTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ShootAutoTargetTrack>("timeEnd", &ShootAutoTargetTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ShootAutoTargetTrack>("arc", &ShootAutoTargetTrack::SetArc);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<ShootAutoTargetTrack>("maxDistance", &ShootAutoTargetTrack::SetMaxDistance);
					properties[3] = property;
					property = new fight::PropertyBool<ShootAutoTargetTrack>("useSecondCone", &ShootAutoTargetTrack::SetUseSecondCone);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<ShootAutoTargetTrack>("arc2", &ShootAutoTargetTrack::SetArc2);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<ShootAutoTargetTrack>("maxDistance2", &ShootAutoTargetTrack::SetMaxDistance2);
					properties[6] = property;
					property = new fight::PropertyEnumConstList<ShootAutoTargetTrack>("minPriorityTargetClass", gAutoTargetTrackMinPriorityTargetClassTable, gAutoTargetTrackMinPriorityTargetClassCount, &ShootAutoTargetTrack::SetMinPriorityTargetClass);
					properties[7] = property;
					property = new fight::PropertyEnumConstList<ShootAutoTargetTrack>("maxPriorityTargetClass", gAutoTargetTrackMinPriorityTargetClassTable, gAutoTargetTrackMinPriorityTargetClassCount, &ShootAutoTargetTrack::SetMaxPriorityTargetClass);
					properties[8] = property;
					fight::RegisterPropertyList(properties, &gShootAutoTargetTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AF760
			fight::TrackFactory* CreateShootAutoTargetTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShootAutoTargetTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AFD90
			void RegisterShootAutoTargetTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShootAutoTargetTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSetFireRateTimerTrackProperties;  // 0x11254AB4

			// FUNCTION: ENGINE 0x101AD1A0
			bool SetFireRateTimerTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD1C0
			bool SetFireRateTimerTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ADAD0
			bool SetFireRateTimerTrack::SetTimer(const fight::Name& newValue)
			{
				timer = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD1E0
			bool SetFireRateTimerTrack::SetIncrementing(bool newValue)
			{
				incrementing = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD1F0
			bool SetFireRateTimerTrack::SetApplyOnParent(bool newValue)
			{
				applyOnParent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ADAF0
			bool SetFireRateTimerTrack::SetGrabSlot(const fight::Name& newValue)
			{
				grabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ADB10
			bool SetFireRateTimerTrack::SetWeaponEntry(const fight::Name& newValue)
			{
				weaponEntry = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ADB30
			bool SetFireRateTimerTrack::SetShooter(const fight::Name& newValue)
			{
				shooter = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ADB50
			bool SetFireRateTimerTrack::SetAmmoProfile(const fight::Name& newValue)
			{
				ammoProfile = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ADB70
			bool SetFireRateTimerTrack::SetUserProfile(const fight::Name& newValue)
			{
				userProfile = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD720
			fight::Property* SetFireRateTimerTrack::GetProperty(int index)
			{
				return gSetFireRateTimerTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101AD740
			void SetFireRateTimerTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetFireRateTimerTrackProperties);
			}

			// FUNCTION: ENGINE 0x101AE110
			SetFireRateTimerTrack::SetFireRateTimerTrack() : timeBegin(0.0f), timeEnd(0.0f), applyOnParent(false), incrementing(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101AE190
			float SetFireRateTimerTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101AE1A0
			float SetFireRateTimerTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101AE1B0
			SetFireRateTimerTrack::~SetFireRateTimerTrack()
			{
			}

			// FUNCTION: ENGINE 0x101B1400
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetFireRateTimerTrack::RegisterProperties()
			{
				if (gSetFireRateTimerTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SetFireRateTimerTrack>("timeBegin", &SetFireRateTimerTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SetFireRateTimerTrack>("timeEnd", &SetFireRateTimerTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<SetFireRateTimerTrack>("timer", &SetFireRateTimerTrack::SetTimer);
					properties[2] = property;
					property = new fight::PropertyBool<SetFireRateTimerTrack>("incrementing", &SetFireRateTimerTrack::SetIncrementing);
					properties[3] = property;
					property = new fight::PropertyBool<SetFireRateTimerTrack>("applyOnParent", &SetFireRateTimerTrack::SetApplyOnParent);
					properties[4] = property;
					property = new fight::PropertyNameList<SetFireRateTimerTrack>("grabSlot", &SetFireRateTimerTrack::SetGrabSlot);
					properties[5] = property;
					property = new fight::PropertyNameList<SetFireRateTimerTrack>("weaponEntry", &SetFireRateTimerTrack::SetWeaponEntry);
					properties[6] = property;
					property = new fight::PropertyNameList<SetFireRateTimerTrack>("shooter", &SetFireRateTimerTrack::SetShooter);
					properties[7] = property;
					property = new fight::PropertyName<SetFireRateTimerTrack>("ammoProfile", &SetFireRateTimerTrack::SetAmmoProfile);
					properties[8] = property;
					property = new fight::PropertyName<SetFireRateTimerTrack>("userProfile", &SetFireRateTimerTrack::SetUserProfile);
					properties[9] = property;
					fight::RegisterPropertyList(properties, &gSetFireRateTimerTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AF790
			fight::TrackFactory* CreateSetFireRateTimerTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetFireRateTimerTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AFDC0
			void RegisterSetFireRateTimerTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetFireRateTimerTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gShootSelectWeaponConfigurationTrackProperties;  // 0x11254AB8

			// FUNCTION: ENGINE 0x101AD200
			bool ShootSelectWeaponConfigurationTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD220
			bool ShootSelectWeaponConfigurationTrack::SetApplyOnParent(bool newValue)
			{
				applyOnParent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ADB90
			bool ShootSelectWeaponConfigurationTrack::SetWeaponConfiguration(const fight::Name& newValue)
			{
				weaponConfiguration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD750
			fight::Property* ShootSelectWeaponConfigurationTrack::GetProperty(int index)
			{
				return gShootSelectWeaponConfigurationTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101AD770
			void ShootSelectWeaponConfigurationTrack::ClearProperties()
			{
				fight::FreePropertyList(&gShootSelectWeaponConfigurationTrackProperties);
			}

			// FUNCTION: ENGINE 0x101AE1C0
			ShootSelectWeaponConfigurationTrack::ShootSelectWeaponConfigurationTrack() : timeBegin(0.0f), applyOnParent(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101AE200
			float ShootSelectWeaponConfigurationTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101AE210
			float ShootSelectWeaponConfigurationTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101AE220
			ShootSelectWeaponConfigurationTrack::~ShootSelectWeaponConfigurationTrack()
			{
			}

			// FUNCTION: ENGINE 0x101B16C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShootSelectWeaponConfigurationTrack::RegisterProperties()
			{
				if (gShootSelectWeaponConfigurationTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ShootSelectWeaponConfigurationTrack>("timeBegin", &ShootSelectWeaponConfigurationTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyBool<ShootSelectWeaponConfigurationTrack>("applyOnParent", &ShootSelectWeaponConfigurationTrack::SetApplyOnParent);
					properties[1] = property;
					property = new fight::PropertyNameList<ShootSelectWeaponConfigurationTrack>("weaponConfiguration", &ShootSelectWeaponConfigurationTrack::SetWeaponConfiguration);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gShootSelectWeaponConfigurationTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AF7C0
			fight::TrackFactory* CreateShootSelectWeaponConfigurationTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShootSelectWeaponConfigurationTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AFDF0
			void RegisterShootSelectWeaponConfigurationTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShootSelectWeaponConfigurationTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gShootTakeAmmoFromParentTrackProperties;  // 0x11254ABC

			// FUNCTION: ENGINE 0x101AD230
			bool ShootTakeAmmoFromParentTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ADBB0
			bool ShootTakeAmmoFromParentTrack::SetWeaponGrabSlot(const fight::Name& newValue)
			{
				weaponGrabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ADBD0
			bool ShootTakeAmmoFromParentTrack::SetReceiverGrabSlot(const fight::Name& newValue)
			{
				receiverGrabSlot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101ADBF0
			bool ShootTakeAmmoFromParentTrack::SetReceiverJoint(const fight::Name& newValue)
			{
				receiverJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD250
			bool ShootTakeAmmoFromParentTrack::SetReceiverPositionOffset(const math::Vector& newValue)
			{
				receiverPositionOffset.x = newValue.x;
				receiverPositionOffset.y = newValue.y;
				receiverPositionOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD270
			bool ShootTakeAmmoFromParentTrack::SetReceiverRotationOffset(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				receiverRotationOffset.x = scaled.x;
				receiverRotationOffset.y = scaled.y;
				receiverRotationOffset.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101ADC10
			bool ShootTakeAmmoFromParentTrack::SetChildJoint(const fight::Name& newValue)
			{
				childJoint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD2C0
			bool ShootTakeAmmoFromParentTrack::SetChildPositionOffset(const math::Vector& newValue)
			{
				childPositionOffset.x = newValue.x;
				childPositionOffset.y = newValue.y;
				childPositionOffset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD2E0
			bool ShootTakeAmmoFromParentTrack::SetChildRotationOffset(const math::Vector& newValue)
			{
				math::Vector scaled = newValue;
				scaled.x *= 0.017453292f;
				scaled.y *= 0.017453292f;
				scaled.z *= 0.017453292f;
				childRotationOffset.x = scaled.x;
				childRotationOffset.y = scaled.y;
				childRotationOffset.z = scaled.z;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD330
			bool ShootTakeAmmoFromParentTrack::SetBlendTime(float newValue)
			{
				blendTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AD780
			fight::Property* ShootTakeAmmoFromParentTrack::GetProperty(int index)
			{
				return gShootTakeAmmoFromParentTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101AD7A0
			void ShootTakeAmmoFromParentTrack::ClearProperties()
			{
				fight::FreePropertyList(&gShootTakeAmmoFromParentTrackProperties);
			}

			// FUNCTION: ENGINE 0x101AE230
			ShootTakeAmmoFromParentTrack::ShootTakeAmmoFromParentTrack() : childPositionOffset(0.0f, 0.0f, 0.0f), childRotationOffset(0.0f, 0.0f, 0.0f), receiverPositionOffset(0.0f, 0.0f, 0.0f), receiverRotationOffset(0.0f, 0.0f, 0.0f), blendTime(0.0f), timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101AE2E0
			float ShootTakeAmmoFromParentTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101AE2F0
			float ShootTakeAmmoFromParentTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101AE300
			ShootTakeAmmoFromParentTrack::~ShootTakeAmmoFromParentTrack()
			{
			}

			// FUNCTION: ENGINE 0x101B17D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ShootTakeAmmoFromParentTrack::RegisterProperties()
			{
				if (gShootTakeAmmoFromParentTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ShootTakeAmmoFromParentTrack>("timeBegin", &ShootTakeAmmoFromParentTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyNameList<ShootTakeAmmoFromParentTrack>("weaponGrabSlot", &ShootTakeAmmoFromParentTrack::SetWeaponGrabSlot);
					properties[1] = property;
					property = new fight::PropertyNameList<ShootTakeAmmoFromParentTrack>("receiverGrabSlot", &ShootTakeAmmoFromParentTrack::SetReceiverGrabSlot);
					properties[2] = property;
					property = new fight::PropertyNameList<ShootTakeAmmoFromParentTrack>("receiverJoint", &ShootTakeAmmoFromParentTrack::SetReceiverJoint);
					properties[3] = property;
					property = new fight::PropertyVector<ShootTakeAmmoFromParentTrack>("receiverPositionOffset", &ShootTakeAmmoFromParentTrack::SetReceiverPositionOffset);
					properties[4] = property;
					property = new fight::PropertyVector<ShootTakeAmmoFromParentTrack>("receiverRotationOffset", &ShootTakeAmmoFromParentTrack::SetReceiverRotationOffset);
					properties[5] = property;
					property = new fight::PropertyNameList<ShootTakeAmmoFromParentTrack>("childJoint", &ShootTakeAmmoFromParentTrack::SetChildJoint);
					properties[6] = property;
					property = new fight::PropertyVector<ShootTakeAmmoFromParentTrack>("childPositionOffset", &ShootTakeAmmoFromParentTrack::SetChildPositionOffset);
					properties[7] = property;
					property = new fight::PropertyVector<ShootTakeAmmoFromParentTrack>("childRotationOffset", &ShootTakeAmmoFromParentTrack::SetChildRotationOffset);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<ShootTakeAmmoFromParentTrack>("blendTime", &ShootTakeAmmoFromParentTrack::SetBlendTime);
					properties[9] = property;
					fight::RegisterPropertyList(properties, &gShootTakeAmmoFromParentTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AF7F0
			fight::TrackFactory* CreateShootTakeAmmoFromParentTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShootTakeAmmoFromParentTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AFE20
			void RegisterShootTakeAmmoFromParentTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ShootTakeAmmoFromParentTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// FUNCTION: ENGINE 0x10113C80
			ShootSwitchWeaponConfigurationAction::ShootSwitchWeaponConfigurationAction(ShootSwitchWeaponConfigurationTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x10114520
			fight::Action* ShootSwitchWeaponConfigurationTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				return new ShootSwitchWeaponConfigurationAction(this, engine::GetObjectHandle(owner));
			}

			// FUNCTION: ENGINE 0x10113510
			// EQUIVALENT: scheduling, the engine stores the flag byte after the three floats (81.6 %)
			ShootAutoTargetAction::ShootAutoTargetAction(ShootAutoTargetTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xA00), link(newTrack), target(newTarget), unknown2C(0.0f), unknown30(0.0f), unknown34(0.0f)
			{
				unknown38 = false;
			}

			// FUNCTION: ENGINE 0x10111D80
			ShootAutoTargetAction::~ShootAutoTargetAction()
			{
			}

			// FUNCTION: ENGINE 0x10114480
			fight::Action* ShootAutoTargetTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				return new ShootAutoTargetAction(this, engine::GetObjectHandle(owner));
			}

			// FUNCTION: ENGINE 0x10113A50
			ShootSelectWeaponConfigurationAction::ShootSelectWeaponConfigurationAction(ShootSelectWeaponConfigurationTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101144D0
			fight::Action* ShootSelectWeaponConfigurationTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				return new ShootSelectWeaponConfigurationAction(this, engine::GetObjectHandle(owner));
			}

			// ---- actions end
			template class fight::PropertyBool<ShootCheckAmmoCountCondition>;
			template class fight::PropertyNameList<ShootCheckAmmoCountCondition>;
			template class fight::PropertyEnumConstList<ShootCheckAmmoCountCondition>;
			template class fight::PropertyIntConstRange<ShootCheckAmmoCountCondition>;
			template class fight::ConditionFactoryTemplate<ShootCheckAmmoCountCondition>;
			template class fight::ConditionFactoryCasterTemplate<ShootCheckAmmoCountCondition>;
			template class fight::PropertyBool<ShootCheckCooldownTimeCondition>;
			template class fight::PropertyNameList<ShootCheckCooldownTimeCondition>;
			template class fight::PropertyEnumConstList<ShootCheckCooldownTimeCondition>;
			template class fight::PropertyFloatConstRange<ShootCheckCooldownTimeCondition>;
			template class fight::ConditionFactoryTemplate<ShootCheckCooldownTimeCondition>;
			template class fight::ConditionFactoryCasterTemplate<ShootCheckCooldownTimeCondition>;
			template class fight::PropertyNameList<ShootCurrentWeaponConfigurationCondition>;
			template class fight::PropertyBool<ShootCurrentWeaponConfigurationCondition>;
			template class fight::ConditionFactoryTemplate<ShootCurrentWeaponConfigurationCondition>;
			template class fight::ConditionFactoryCasterTemplate<ShootCurrentWeaponConfigurationCondition>;
			template class fight::PropertyBool<ShootCheckOverheatingCondition>;
			template class fight::PropertyNameList<ShootCheckOverheatingCondition>;
			template class fight::ConditionFactoryTemplate<ShootCheckOverheatingCondition>;
			template class fight::ConditionFactoryCasterTemplate<ShootCheckOverheatingCondition>;
			template class fight::PropertyFloatConstRange<ShootSwitchWeaponConfigurationTrack>;
			template class fight::PropertyBool<ShootSwitchWeaponConfigurationTrack>;
			template class fight::TrackFactoryTemplate<ShootSwitchWeaponConfigurationTrack>;
			template class fight::TrackFactoryCasterTemplate<ShootSwitchWeaponConfigurationTrack>;
			template class fight::PropertyBool<ShootSetUserProfileTrack>;
			template class fight::PropertyNameList<ShootSetUserProfileTrack>;
			template class fight::PropertyName<ShootSetUserProfileTrack>;
			template class fight::TrackFactoryTemplate<ShootSetUserProfileTrack>;
			template class fight::TrackFactoryCasterTemplate<ShootSetUserProfileTrack>;
			template class fight::PropertyFloatConstRange<ShootCalculateHitPositionTrack>;
			template class fight::PropertyBool<ShootCalculateHitPositionTrack>;
			template class fight::PropertyNameList<ShootCalculateHitPositionTrack>;
			template class fight::PropertyName<ShootCalculateHitPositionTrack>;
			template class fight::TrackFactoryTemplate<ShootCalculateHitPositionTrack>;
			template class fight::TrackFactoryCasterTemplate<ShootCalculateHitPositionTrack>;
			template class fight::PropertyBool<ShootSetAmmoProfileTrack>;
			template class fight::PropertyNameList<ShootSetAmmoProfileTrack>;
			template class fight::PropertyName<ShootSetAmmoProfileTrack>;
			template class fight::TrackFactoryTemplate<ShootSetAmmoProfileTrack>;
			template class fight::TrackFactoryCasterTemplate<ShootSetAmmoProfileTrack>;
			template class fight::PropertyBool<ReloadTrack>;
			template class fight::PropertyNameList<ReloadTrack>;
			template class fight::PropertyName<ReloadTrack>;
			template class fight::TrackFactoryTemplate<ReloadTrack>;
			template class fight::TrackFactoryCasterTemplate<ReloadTrack>;
			template class fight::PropertyFloatConstRange<ShootTrack>;
			template class fight::PropertyBool<ShootTrack>;
			template class fight::PropertyNameList<ShootTrack>;
			template class fight::PropertyName<ShootTrack>;
			template class fight::PropertyGroup<ShootTrack>;
			template class fight::PropertyEnumConstList<ShootTrack>;
			template class fight::PropertyVector<ShootTrack>;
			template class fight::TrackFactoryTemplate<ShootTrack>;
			template class fight::TrackFactoryCasterTemplate<ShootTrack>;
			template class fight::PropertyFloatConstRange<ShootAutoTargetTrack>;
			template class fight::PropertyBool<ShootAutoTargetTrack>;
			template class fight::PropertyEnumConstList<ShootAutoTargetTrack>;
			template class fight::TrackFactoryTemplate<ShootAutoTargetTrack>;
			template class fight::TrackFactoryCasterTemplate<ShootAutoTargetTrack>;
			template class fight::PropertyFloatConstRange<SetFireRateTimerTrack>;
			template class fight::PropertyName<SetFireRateTimerTrack>;
			template class fight::PropertyBool<SetFireRateTimerTrack>;
			template class fight::PropertyNameList<SetFireRateTimerTrack>;
			template class fight::TrackFactoryTemplate<SetFireRateTimerTrack>;
			template class fight::TrackFactoryCasterTemplate<SetFireRateTimerTrack>;
			template class fight::PropertyFloatConstRange<ShootSelectWeaponConfigurationTrack>;
			template class fight::PropertyBool<ShootSelectWeaponConfigurationTrack>;
			template class fight::PropertyNameList<ShootSelectWeaponConfigurationTrack>;
			template class fight::TrackFactoryTemplate<ShootSelectWeaponConfigurationTrack>;
			template class fight::TrackFactoryCasterTemplate<ShootSelectWeaponConfigurationTrack>;
			template class fight::PropertyFloatConstRange<ShootTakeAmmoFromParentTrack>;
			template class fight::PropertyNameList<ShootTakeAmmoFromParentTrack>;
			template class fight::PropertyVector<ShootTakeAmmoFromParentTrack>;
			template class fight::TrackFactoryTemplate<ShootTakeAmmoFromParentTrack>;
			template class fight::TrackFactoryCasterTemplate<ShootTakeAmmoFromParentTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10110E60
// FUNCTION: ENGINE 0x10110E80
// FUNCTION: ENGINE 0x10110FC0
// FUNCTION: ENGINE 0x10111070
// FUNCTION: ENGINE 0x101110D0
// FUNCTION: ENGINE 0x10111140
// FUNCTION: ENGINE 0x10113590
// FUNCTION: ENGINE 0x10113B00
// FUNCTION: ENGINE 0x10113D30
// FUNCTION: ENGINE 0x101ADD80
// FUNCTION: ENGINE 0x101AE0E0
// FUNCTION: ENGINE 0x101AE310
// FUNCTION: ENGINE 0x101AE320
// FUNCTION: ENGINE 0x101AE350
// FUNCTION: ENGINE 0x101AE360
// FUNCTION: ENGINE 0x101AE390
// FUNCTION: ENGINE 0x101AE3A0
// FUNCTION: ENGINE 0x101AE3D0
// FUNCTION: ENGINE 0x101AE3E0
// FUNCTION: ENGINE 0x101AE410
// FUNCTION: ENGINE 0x101AE420
// FUNCTION: ENGINE 0x101AE450
// FUNCTION: ENGINE 0x101AE460
// FUNCTION: ENGINE 0x101AE490
// FUNCTION: ENGINE 0x101AE4A0
// FUNCTION: ENGINE 0x101AE4D0
// FUNCTION: ENGINE 0x101AE4E0
// FUNCTION: ENGINE 0x101AE510
// FUNCTION: ENGINE 0x101AE520
// FUNCTION: ENGINE 0x101AE550
// FUNCTION: ENGINE 0x101AE560
// FUNCTION: ENGINE 0x101AE590
// FUNCTION: ENGINE 0x101AE5A0
// FUNCTION: ENGINE 0x101AE5D0
// FUNCTION: ENGINE 0x101AE5E0
// FUNCTION: ENGINE 0x101AE610
// FUNCTION: ENGINE 0x101AE620
// FUNCTION: ENGINE 0x101AE650
// FUNCTION: ENGINE 0x101AE660
// FUNCTION: ENGINE 0x101AE690
// FUNCTION: ENGINE 0x101AE6C0
// FUNCTION: ENGINE 0x101AE6F0
// FUNCTION: ENGINE 0x101AE720
// FUNCTION: ENGINE 0x101AE750
// FUNCTION: ENGINE 0x101AE780
// FUNCTION: ENGINE 0x101AE7B0
// FUNCTION: ENGINE 0x101AE7E0
// FUNCTION: ENGINE 0x101AE810
// FUNCTION: ENGINE 0x101AE840
// FUNCTION: ENGINE 0x101AE870
// FUNCTION: ENGINE 0x101AE8A0
// FUNCTION: ENGINE 0x101AE8D0
// FUNCTION: ENGINE 0x101AE900
// FUNCTION: ENGINE 0x101AE920
// FUNCTION: ENGINE 0x101AE930
// FUNCTION: ENGINE 0x101AE970
// FUNCTION: ENGINE 0x101AE980
// FUNCTION: ENGINE 0x101AE9B0
// FUNCTION: ENGINE 0x101AE9D0
// FUNCTION: ENGINE 0x101AE9E0
// FUNCTION: ENGINE 0x101AEA10
// FUNCTION: ENGINE 0x101AEA30
// FUNCTION: ENGINE 0x101AEA40
// FUNCTION: ENGINE 0x101AEA70
// FUNCTION: ENGINE 0x101AEA90
// FUNCTION: ENGINE 0x101AEAA0
// FUNCTION: ENGINE 0x101AEAE0
// FUNCTION: ENGINE 0x101AEAF0
// FUNCTION: ENGINE 0x101AEB20
// FUNCTION: ENGINE 0x101AEB40
// FUNCTION: ENGINE 0x101AEB50
// FUNCTION: ENGINE 0x101AEB80
// FUNCTION: ENGINE 0x101AEBB0
// FUNCTION: ENGINE 0x101AEBC0
// FUNCTION: ENGINE 0x101AEBF0
// FUNCTION: ENGINE 0x101AEC10
// FUNCTION: ENGINE 0x101AEC20
// FUNCTION: ENGINE 0x101AEC50
// FUNCTION: ENGINE 0x101AEC70
// FUNCTION: ENGINE 0x101AEC80
// FUNCTION: ENGINE 0x101AECB0
// FUNCTION: ENGINE 0x101AECE0
// FUNCTION: ENGINE 0x101AECF0
// FUNCTION: ENGINE 0x101AED20
// FUNCTION: ENGINE 0x101AED40
// FUNCTION: ENGINE 0x101AED50
// FUNCTION: ENGINE 0x101AED80
// FUNCTION: ENGINE 0x101AEDA0
// FUNCTION: ENGINE 0x101AEDB0
// FUNCTION: ENGINE 0x101AEDE0
// FUNCTION: ENGINE 0x101AEE10
// FUNCTION: ENGINE 0x101AEE20
// FUNCTION: ENGINE 0x101AEE50
// FUNCTION: ENGINE 0x101AEE70
// FUNCTION: ENGINE 0x101AEE80
// FUNCTION: ENGINE 0x101AEEB0
// FUNCTION: ENGINE 0x101AEED0
// FUNCTION: ENGINE 0x101AEEE0
// FUNCTION: ENGINE 0x101AEF10
// FUNCTION: ENGINE 0x101AEF30
// FUNCTION: ENGINE 0x101AEF40
// FUNCTION: ENGINE 0x101AEF70
// FUNCTION: ENGINE 0x101AEFA0
// FUNCTION: ENGINE 0x101AEFB0
// FUNCTION: ENGINE 0x101AEFE0
// FUNCTION: ENGINE 0x101AF000
// FUNCTION: ENGINE 0x101AF010
// FUNCTION: ENGINE 0x101AF040
// FUNCTION: ENGINE 0x101AF060
// FUNCTION: ENGINE 0x101AF070
// FUNCTION: ENGINE 0x101AF080
// FUNCTION: ENGINE 0x101AF0C0
// FUNCTION: ENGINE 0x101AF0D0
// FUNCTION: ENGINE 0x101AF100
// FUNCTION: ENGINE 0x101AF120
// FUNCTION: ENGINE 0x101AF130
// FUNCTION: ENGINE 0x101AF160
// FUNCTION: ENGINE 0x101AF180
// FUNCTION: ENGINE 0x101AF190
// FUNCTION: ENGINE 0x101AF1C0
// FUNCTION: ENGINE 0x101AF1F0
// FUNCTION: ENGINE 0x101AF200
// FUNCTION: ENGINE 0x101AF230
// FUNCTION: ENGINE 0x101AF250
// FUNCTION: ENGINE 0x101AF260
// FUNCTION: ENGINE 0x101AF2A0
// FUNCTION: ENGINE 0x101AF2B0
// FUNCTION: ENGINE 0x101AF2E0
// FUNCTION: ENGINE 0x101AF300
// FUNCTION: ENGINE 0x101AF310
// FUNCTION: ENGINE 0x101AF340
// FUNCTION: ENGINE 0x101AF370
// FUNCTION: ENGINE 0x101AF380
// FUNCTION: ENGINE 0x101AF3B0
// FUNCTION: ENGINE 0x101AF3D0
// FUNCTION: ENGINE 0x101AF3E0
// FUNCTION: ENGINE 0x101AF410
// FUNCTION: ENGINE 0x101AF440
// FUNCTION: ENGINE 0x101AF450
// FUNCTION: ENGINE 0x101AF480
// FUNCTION: ENGINE 0x101AF4A0
// FUNCTION: ENGINE 0x101AF4B0
// FUNCTION: ENGINE 0x101AF4E0
// FUNCTION: ENGINE 0x101AF510
// FUNCTION: ENGINE 0x101AF520
// FUNCTION: ENGINE 0x101AF550
// FUNCTION: ENGINE 0x101AF570
// FUNCTION: ENGINE 0x101AFE50
// FUNCTION: ENGINE 0x101AFE80
// FUNCTION: ENGINE 0x101AFEA0
// FUNCTION: ENGINE 0x101AFEB0
// FUNCTION: ENGINE 0x101AFEE0
// FUNCTION: ENGINE 0x101AFF00
// FUNCTION: ENGINE 0x101AFF10
// FUNCTION: ENGINE 0x101AFF40
// FUNCTION: ENGINE 0x101AFF60
// FUNCTION: ENGINE 0x101AFF70
// FUNCTION: ENGINE 0x101AFFA0
// FUNCTION: ENGINE 0x101AFFC0
// FUNCTION: ENGINE 0x101AFFD0
// FUNCTION: ENGINE 0x101B0000
// FUNCTION: ENGINE 0x101B0020
// FUNCTION: ENGINE 0x101B0030
// FUNCTION: ENGINE 0x101B0060
// FUNCTION: ENGINE 0x101B0080
// FUNCTION: ENGINE 0x101B00B0
// FUNCTION: ENGINE 0x101B00D0
// FUNCTION: ENGINE 0x101B00E0
// FUNCTION: ENGINE 0x101B0110
// FUNCTION: ENGINE 0x101B0130
// FUNCTION: ENGINE 0x101B0160
// FUNCTION: ENGINE 0x101B0180
// FUNCTION: ENGINE 0x101B0190
// FUNCTION: ENGINE 0x101B01C0
// FUNCTION: ENGINE 0x101B01E0
// FUNCTION: ENGINE 0x101B0210
// FUNCTION: ENGINE 0x101B0230
// FUNCTION: ENGINE 0x101B0240
// FUNCTION: ENGINE 0x101B0270
// FUNCTION: ENGINE 0x101B0290
// FUNCTION: ENGINE 0x101B02C0
// FUNCTION: ENGINE 0x101B02E0
// FUNCTION: ENGINE 0x101B02F0
// FUNCTION: ENGINE 0x101B0320
// FUNCTION: ENGINE 0x101B0340
// FUNCTION: ENGINE 0x101B0370
// FUNCTION: ENGINE 0x101B0390
// FUNCTION: ENGINE 0x101B03C0
// FUNCTION: ENGINE 0x101B03E0
// FUNCTION: ENGINE 0x101B03F0
// FUNCTION: ENGINE 0x101B0420
// FUNCTION: ENGINE 0x101B0440
// FUNCTION: ENGINE 0x101B0450
// FUNCTION: ENGINE 0x101B0480
// FUNCTION: ENGINE 0x101B04A0
// FUNCTION: ENGINE 0x101B04B0
// FUNCTION: ENGINE 0x101B04E0
// FUNCTION: ENGINE 0x101B0500
// FUNCTION: ENGINE 0x101B0530
// FUNCTION: ENGINE 0x101B1A90
// FUNCTION: ENGINE 0x101B1AE0
// FUNCTION: ENGINE 0x101B1B30
// FUNCTION: ENGINE 0x101B1B60
// FUNCTION: ENGINE 0x101B1B80
// FUNCTION: ENGINE 0x101B1BB0
// FUNCTION: ENGINE 0x101B1BD0
// FUNCTION: ENGINE 0x101B1C00
// FUNCTION: ENGINE 0x101B1C20
// FUNCTION: ENGINE 0x101B1C50
// FUNCTION: ENGINE 0x101B1C70
// FUNCTION: ENGINE 0x101B1CA0
// FUNCTION: ENGINE 0x101B1CC0
// FUNCTION: ENGINE 0x101B1CF0
// FUNCTION: ENGINE 0x101B1D10
// FUNCTION: ENGINE 0x101B1D40
// FUNCTION: ENGINE 0x101B1D60
// FUNCTION: ENGINE 0x101B1D90
// FUNCTION: ENGINE 0x101B1DB0
// FUNCTION: ENGINE 0x101B1DE0
// FUNCTION: ENGINE 0x101B1E00
// FUNCTION: ENGINE 0x101B1E30
// FUNCTION: ENGINE 0x101B1E50
// FUNCTION: ENGINE 0x101B1E80
// FUNCTION: ENGINE 0x101B1EA0
// FUNCTION: ENGINE 0x101B1ED0
// FUNCTION: ENGINE 0x101B1EF0
// FUNCTION: ENGINE 0x101B1F40
// FUNCTION: ENGINE 0x101B1F90
// FUNCTION: ENGINE 0x101B1FE0
// FUNCTION: ENGINE 0x101B2030
// FUNCTION: ENGINE 0x101B2080
// FUNCTION: ENGINE 0x101B20D0
// FUNCTION: ENGINE 0x101B2120
// FUNCTION: ENGINE 0x101B2170
// FUNCTION: ENGINE 0x101B21C0
// FUNCTION: ENGINE 0x101B2210
// FUNCTION: ENGINE 0x101B2260
