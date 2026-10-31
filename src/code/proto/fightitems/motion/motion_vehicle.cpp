// Fight items of the motion group: HelicopterHeightAboveGroundCondition, HelicopterRotorCollisionCondition, SecondaryWeaponTypeCondition, VehiclePowerOnOffCondition, HelicopterOnGroundCondition, SetVehicleAnimatedTrack, HelicopterSpawnBloodtoxTrack, VehiclePlayAnimationTrack, SetVehicleHeadlightTrack, VehiclePowerOnOffTrack, SetSecondaryWeaponTypeTrack, SetVehicleSolverEnabledTrack (unit 0x101C8410 - 0x101CAFF0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_vehicle.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gHelicopterHeightAboveGroundConditionProperties;  // 0x11254C50

			// FUNCTION: ENGINE 0x101C8410
			bool HelicopterHeightAboveGroundCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C8420
			bool HelicopterHeightAboveGroundCondition::SetHeight(float newValue)
			{
				height = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C85F0
			fight::Property* HelicopterHeightAboveGroundCondition::GetProperty(int index)
			{
				return gHelicopterHeightAboveGroundConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101C8610
			void HelicopterHeightAboveGroundCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHelicopterHeightAboveGroundConditionProperties);
			}

			// FUNCTION: ENGINE 0x101C8620
			HelicopterHeightAboveGroundCondition::HelicopterHeightAboveGroundCondition() : fight::Condition(0), height(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x101C8650
			HelicopterHeightAboveGroundCondition::~HelicopterHeightAboveGroundCondition()
			{
			}

			// FUNCTION: ENGINE 0x101C9C20
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HelicopterHeightAboveGroundCondition::RegisterProperties()
			{
				if (gHelicopterHeightAboveGroundConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<HelicopterHeightAboveGroundCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &HelicopterHeightAboveGroundCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<HelicopterHeightAboveGroundCondition>("height", &HelicopterHeightAboveGroundCondition::SetHeight);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gHelicopterHeightAboveGroundConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C99E0
			fight::ConditionFactory* CreateHelicopterHeightAboveGroundConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HelicopterHeightAboveGroundCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CA630
			void RegisterHelicopterHeightAboveGroundConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HelicopterHeightAboveGroundCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gHelicopterRotorCollisionConditionProperties;  // 0x11254C54

			// FUNCTION: ENGINE 0x101C8440
			bool HelicopterRotorCollisionCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C8450
			bool HelicopterRotorCollisionCondition::SetTime(float newValue)
			{
				time = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C8660
			fight::Property* HelicopterRotorCollisionCondition::GetProperty(int index)
			{
				return gHelicopterRotorCollisionConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101C8680
			void HelicopterRotorCollisionCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHelicopterRotorCollisionConditionProperties);
			}

			// FUNCTION: ENGINE 0x101C8690
			HelicopterRotorCollisionCondition::HelicopterRotorCollisionCondition() : fight::Condition(0), time(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x101C86C0
			HelicopterRotorCollisionCondition::~HelicopterRotorCollisionCondition()
			{
			}

			// FUNCTION: ENGINE 0x101C9D10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HelicopterRotorCollisionCondition::RegisterProperties()
			{
				if (gHelicopterRotorCollisionConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<HelicopterRotorCollisionCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &HelicopterRotorCollisionCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<HelicopterRotorCollisionCondition>("time", &HelicopterRotorCollisionCondition::SetTime);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gHelicopterRotorCollisionConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C9A10
			fight::ConditionFactory* CreateHelicopterRotorCollisionConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HelicopterRotorCollisionCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CA660
			void RegisterHelicopterRotorCollisionConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HelicopterRotorCollisionCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gSecondaryWeaponTypeConditionProperties;  // 0x11254C58

			// FUNCTION: ENGINE 0x101C8470
			bool SecondaryWeaponTypeCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C8480
			bool SecondaryWeaponTypeCondition::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C86D0
			fight::Property* SecondaryWeaponTypeCondition::GetProperty(int index)
			{
				return gSecondaryWeaponTypeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101C86F0
			void SecondaryWeaponTypeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gSecondaryWeaponTypeConditionProperties);
			}

			// FUNCTION: ENGINE 0x101C8700
			SecondaryWeaponTypeCondition::SecondaryWeaponTypeCondition() : fight::Condition(0), compare(0), type(0)
			{
			}

			// FUNCTION: ENGINE 0x101C8730
			SecondaryWeaponTypeCondition::~SecondaryWeaponTypeCondition()
			{
			}

			// FUNCTION: ENGINE 0x101C9E00
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SecondaryWeaponTypeCondition::RegisterProperties()
			{
				if (gSecondaryWeaponTypeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<SecondaryWeaponTypeCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &SecondaryWeaponTypeCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<SecondaryWeaponTypeCondition>("type", gSecondaryWeaponTypeConditionTypeTable, gSecondaryWeaponTypeConditionTypeCount, &SecondaryWeaponTypeCondition::SetType);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gSecondaryWeaponTypeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C9A40
			fight::ConditionFactory* CreateSecondaryWeaponTypeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SecondaryWeaponTypeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CA690
			void RegisterSecondaryWeaponTypeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<SecondaryWeaponTypeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gVehiclePowerOnOffConditionProperties;  // 0x11254C5C

			// FUNCTION: ENGINE 0x101C8490
			bool VehiclePowerOnOffCondition::SetPowerOn(bool newValue)
			{
				powerOn = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C8740
			fight::Property* VehiclePowerOnOffCondition::GetProperty(int index)
			{
				return gVehiclePowerOnOffConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101C8760
			void VehiclePowerOnOffCondition::ClearProperties()
			{
				fight::FreePropertyList(&gVehiclePowerOnOffConditionProperties);
			}

			// FUNCTION: ENGINE 0x101C8770
			VehiclePowerOnOffCondition::VehiclePowerOnOffCondition() : fight::Condition(0), powerOn(false)
			{
			}

			// FUNCTION: ENGINE 0x101C8790
			VehiclePowerOnOffCondition::~VehiclePowerOnOffCondition()
			{
			}

			// FUNCTION: ENGINE 0x101C9F00
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void VehiclePowerOnOffCondition::RegisterProperties()
			{
				if (gVehiclePowerOnOffConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<VehiclePowerOnOffCondition>("powerOn", &VehiclePowerOnOffCondition::SetPowerOn);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gVehiclePowerOnOffConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C9A70
			fight::ConditionFactory* CreateVehiclePowerOnOffConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<VehiclePowerOnOffCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CA6C0
			void RegisterVehiclePowerOnOffConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<VehiclePowerOnOffCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gHelicopterOnGroundConditionProperties;  // 0x11254C60

			// FUNCTION: ENGINE 0x101C84A0
			bool HelicopterOnGroundCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C84B0
			bool HelicopterOnGroundCondition::SetTime(float newValue)
			{
				time = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C87A0
			fight::Property* HelicopterOnGroundCondition::GetProperty(int index)
			{
				return gHelicopterOnGroundConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x101C87C0
			void HelicopterOnGroundCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHelicopterOnGroundConditionProperties);
			}

			// FUNCTION: ENGINE 0x101C87D0
			HelicopterOnGroundCondition::HelicopterOnGroundCondition() : fight::Condition(0), time(0.0f), compare(0)
			{
			}

			// FUNCTION: ENGINE 0x101C8800
			HelicopterOnGroundCondition::~HelicopterOnGroundCondition()
			{
			}

			// FUNCTION: ENGINE 0x101C9FA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HelicopterOnGroundCondition::RegisterProperties()
			{
				if (gHelicopterOnGroundConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<HelicopterOnGroundCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &HelicopterOnGroundCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<HelicopterOnGroundCondition>("time", &HelicopterOnGroundCondition::SetTime);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gHelicopterOnGroundConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C9AA0
			fight::ConditionFactory* CreateHelicopterOnGroundConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HelicopterOnGroundCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CA6F0
			void RegisterHelicopterOnGroundConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HelicopterOnGroundCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gSetVehicleAnimatedTrackProperties;  // 0x11254C64

			// FUNCTION: ENGINE 0x101C84D0
			bool SetVehicleAnimatedTrack::SetAnimated(bool newValue)
			{
				animated = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C8810
			fight::Property* SetVehicleAnimatedTrack::GetProperty(int index)
			{
				return gSetVehicleAnimatedTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C8830
			void SetVehicleAnimatedTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetVehicleAnimatedTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C8840
			SetVehicleAnimatedTrack::SetVehicleAnimatedTrack() : animated(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101C8870
			float SetVehicleAnimatedTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101C8880
			float SetVehicleAnimatedTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101C8890
			SetVehicleAnimatedTrack::~SetVehicleAnimatedTrack()
			{
			}

			// FUNCTION: ENGINE 0x101CA090
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetVehicleAnimatedTrack::RegisterProperties()
			{
				if (gSetVehicleAnimatedTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<SetVehicleAnimatedTrack>("animated", &SetVehicleAnimatedTrack::SetAnimated);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gSetVehicleAnimatedTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C9AD0
			fight::TrackFactory* CreateSetVehicleAnimatedTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetVehicleAnimatedTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CA720
			void RegisterSetVehicleAnimatedTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetVehicleAnimatedTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gHelicopterSpawnBloodtoxTrackProperties;  // 0x11254C68

			// FUNCTION: ENGINE 0x101C84E0
			bool HelicopterSpawnBloodtoxTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C8500
			bool HelicopterSpawnBloodtoxTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C88A0
			fight::Property* HelicopterSpawnBloodtoxTrack::GetProperty(int index)
			{
				return gHelicopterSpawnBloodtoxTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C88C0
			void HelicopterSpawnBloodtoxTrack::ClearProperties()
			{
				fight::FreePropertyList(&gHelicopterSpawnBloodtoxTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C88D0
			HelicopterSpawnBloodtoxTrack::HelicopterSpawnBloodtoxTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101C8910
			float HelicopterSpawnBloodtoxTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C8920
			float HelicopterSpawnBloodtoxTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101C8930
			HelicopterSpawnBloodtoxTrack::~HelicopterSpawnBloodtoxTrack()
			{
			}

			// FUNCTION: ENGINE 0x101CA130
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HelicopterSpawnBloodtoxTrack::RegisterProperties()
			{
				if (gHelicopterSpawnBloodtoxTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<HelicopterSpawnBloodtoxTrack>("timeBegin", &HelicopterSpawnBloodtoxTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<HelicopterSpawnBloodtoxTrack>("timeEnd", &HelicopterSpawnBloodtoxTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gHelicopterSpawnBloodtoxTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C9B00
			fight::TrackFactory* CreateHelicopterSpawnBloodtoxTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<HelicopterSpawnBloodtoxTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CA750
			void RegisterHelicopterSpawnBloodtoxTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<HelicopterSpawnBloodtoxTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gVehiclePlayAnimationTrackProperties;  // 0x11254C6C

			// FUNCTION: ENGINE 0x101C8520
			bool VehiclePlayAnimationTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C8540
			bool VehiclePlayAnimationTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C8940
			fight::Property* VehiclePlayAnimationTrack::GetProperty(int index)
			{
				return gVehiclePlayAnimationTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C8960
			void VehiclePlayAnimationTrack::ClearProperties()
			{
				fight::FreePropertyList(&gVehiclePlayAnimationTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C8970
			VehiclePlayAnimationTrack::VehiclePlayAnimationTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101C89B0
			float VehiclePlayAnimationTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C89C0
			float VehiclePlayAnimationTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101C89D0
			VehiclePlayAnimationTrack::~VehiclePlayAnimationTrack()
			{
			}

			// FUNCTION: ENGINE 0x101CA210
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void VehiclePlayAnimationTrack::RegisterProperties()
			{
				if (gVehiclePlayAnimationTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<VehiclePlayAnimationTrack>("timeBegin", &VehiclePlayAnimationTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<VehiclePlayAnimationTrack>("timeEnd", &VehiclePlayAnimationTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gVehiclePlayAnimationTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C9B30
			fight::TrackFactory* CreateVehiclePlayAnimationTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<VehiclePlayAnimationTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CA780
			void RegisterVehiclePlayAnimationTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<VehiclePlayAnimationTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSetVehicleHeadlightTrackProperties;  // 0x11254C70

			// FUNCTION: ENGINE 0x101C8560
			bool SetVehicleHeadlightTrack::SetEnabled(bool newValue)
			{
				enabled = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C89E0
			fight::Property* SetVehicleHeadlightTrack::GetProperty(int index)
			{
				return gSetVehicleHeadlightTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C8A00
			void SetVehicleHeadlightTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetVehicleHeadlightTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C8A10
			SetVehicleHeadlightTrack::SetVehicleHeadlightTrack() : enabled(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101C8A40
			float SetVehicleHeadlightTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101C8A50
			float SetVehicleHeadlightTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101C8A60
			SetVehicleHeadlightTrack::~SetVehicleHeadlightTrack()
			{
			}

			// FUNCTION: ENGINE 0x101CA2F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetVehicleHeadlightTrack::RegisterProperties()
			{
				if (gSetVehicleHeadlightTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<SetVehicleHeadlightTrack>("enabled", &SetVehicleHeadlightTrack::SetEnabled);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gSetVehicleHeadlightTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C9B60
			fight::TrackFactory* CreateSetVehicleHeadlightTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetVehicleHeadlightTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CA7B0
			void RegisterSetVehicleHeadlightTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetVehicleHeadlightTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gVehiclePowerOnOffTrackProperties;  // 0x11254C74

			// FUNCTION: ENGINE 0x101C8570
			bool VehiclePowerOnOffTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C8590
			bool VehiclePowerOnOffTrack::SetPowerOn(bool newValue)
			{
				powerOn = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C85A0
			bool VehiclePowerOnOffTrack::SetUseSpinup(bool newValue)
			{
				useSpinup = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C8A70
			fight::Property* VehiclePowerOnOffTrack::GetProperty(int index)
			{
				return gVehiclePowerOnOffTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C8A90
			void VehiclePowerOnOffTrack::ClearProperties()
			{
				fight::FreePropertyList(&gVehiclePowerOnOffTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C8AA0
			VehiclePowerOnOffTrack::VehiclePowerOnOffTrack() : timeBegin(0.0f), powerOn(false), useSpinup(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101C8AE0
			float VehiclePowerOnOffTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C8AF0
			float VehiclePowerOnOffTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101C8B00
			VehiclePowerOnOffTrack::~VehiclePowerOnOffTrack()
			{
			}

			// FUNCTION: ENGINE 0x101CA390
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void VehiclePowerOnOffTrack::RegisterProperties()
			{
				if (gVehiclePowerOnOffTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<VehiclePowerOnOffTrack>("timeBegin", &VehiclePowerOnOffTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyBool<VehiclePowerOnOffTrack>("powerOn", &VehiclePowerOnOffTrack::SetPowerOn);
					properties[1] = property;
					property = new fight::PropertyBool<VehiclePowerOnOffTrack>("useSpinup", &VehiclePowerOnOffTrack::SetUseSpinup);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gVehiclePowerOnOffTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C9B90
			fight::TrackFactory* CreateVehiclePowerOnOffTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<VehiclePowerOnOffTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CA7E0
			void RegisterVehiclePowerOnOffTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<VehiclePowerOnOffTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSetSecondaryWeaponTypeTrackProperties;  // 0x11254C78

			// FUNCTION: ENGINE 0x101C85B0
			bool SetSecondaryWeaponTypeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C85D0
			bool SetSecondaryWeaponTypeTrack::SetType(int newValue)
			{
				type = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C8B10
			fight::Property* SetSecondaryWeaponTypeTrack::GetProperty(int index)
			{
				return gSetSecondaryWeaponTypeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C8B30
			void SetSecondaryWeaponTypeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetSecondaryWeaponTypeTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C8B40
			SetSecondaryWeaponTypeTrack::SetSecondaryWeaponTypeTrack() : timeBegin(0.0f), type(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101C8B80
			float SetSecondaryWeaponTypeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101C8B90
			float SetSecondaryWeaponTypeTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101C8BA0
			SetSecondaryWeaponTypeTrack::~SetSecondaryWeaponTypeTrack()
			{
			}

			// FUNCTION: ENGINE 0x101CA4A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetSecondaryWeaponTypeTrack::RegisterProperties()
			{
				if (gSetSecondaryWeaponTypeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SetSecondaryWeaponTypeTrack>("timeBegin", &SetSecondaryWeaponTypeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<SetSecondaryWeaponTypeTrack>("type", gSecondaryWeaponTypeConditionTypeTable, gSecondaryWeaponTypeConditionTypeCount, &SetSecondaryWeaponTypeTrack::SetType);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gSetSecondaryWeaponTypeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C9BC0
			fight::TrackFactory* CreateSetSecondaryWeaponTypeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetSecondaryWeaponTypeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CA810
			void RegisterSetSecondaryWeaponTypeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetSecondaryWeaponTypeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSetVehicleSolverEnabledTrackProperties;  // 0x11254C7C

			// FUNCTION: ENGINE 0x101C85E0
			bool SetVehicleSolverEnabledTrack::SetEnabled(bool newValue)
			{
				enabled = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101C8BB0
			fight::Property* SetVehicleSolverEnabledTrack::GetProperty(int index)
			{
				return gSetVehicleSolverEnabledTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101C8BD0
			void SetVehicleSolverEnabledTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetVehicleSolverEnabledTrackProperties);
			}

			// FUNCTION: ENGINE 0x101C8BE0
			SetVehicleSolverEnabledTrack::SetVehicleSolverEnabledTrack() : enabled(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101C8C10
			float SetVehicleSolverEnabledTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101C8C20
			float SetVehicleSolverEnabledTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101C8C30
			SetVehicleSolverEnabledTrack::~SetVehicleSolverEnabledTrack()
			{
			}

			// FUNCTION: ENGINE 0x101CA590
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetVehicleSolverEnabledTrack::RegisterProperties()
			{
				if (gSetVehicleSolverEnabledTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<SetVehicleSolverEnabledTrack>("enabled", &SetVehicleSolverEnabledTrack::SetEnabled);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gSetVehicleSolverEnabledTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101C9BF0
			fight::TrackFactory* CreateSetVehicleSolverEnabledTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetVehicleSolverEnabledTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101CA840
			void RegisterSetVehicleSolverEnabledTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetVehicleSolverEnabledTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			template class fight::PropertyEnumConstList<HelicopterHeightAboveGroundCondition>;
			template class fight::PropertyFloatConstRange<HelicopterHeightAboveGroundCondition>;
			template class fight::ConditionFactoryTemplate<HelicopterHeightAboveGroundCondition>;
			template class fight::ConditionFactoryCasterTemplate<HelicopterHeightAboveGroundCondition>;
			template class fight::PropertyEnumConstList<HelicopterRotorCollisionCondition>;
			template class fight::PropertyFloatConstRange<HelicopterRotorCollisionCondition>;
			template class fight::ConditionFactoryTemplate<HelicopterRotorCollisionCondition>;
			template class fight::ConditionFactoryCasterTemplate<HelicopterRotorCollisionCondition>;
			template class fight::PropertyEnumConstList<SecondaryWeaponTypeCondition>;
			template class fight::ConditionFactoryTemplate<SecondaryWeaponTypeCondition>;
			template class fight::ConditionFactoryCasterTemplate<SecondaryWeaponTypeCondition>;
			template class fight::PropertyBool<VehiclePowerOnOffCondition>;
			template class fight::ConditionFactoryTemplate<VehiclePowerOnOffCondition>;
			template class fight::ConditionFactoryCasterTemplate<VehiclePowerOnOffCondition>;
			template class fight::PropertyEnumConstList<HelicopterOnGroundCondition>;
			template class fight::PropertyFloatConstRange<HelicopterOnGroundCondition>;
			template class fight::ConditionFactoryTemplate<HelicopterOnGroundCondition>;
			template class fight::ConditionFactoryCasterTemplate<HelicopterOnGroundCondition>;
			template class fight::PropertyBool<SetVehicleAnimatedTrack>;
			template class fight::TrackFactoryTemplate<SetVehicleAnimatedTrack>;
			template class fight::TrackFactoryCasterTemplate<SetVehicleAnimatedTrack>;
			template class fight::PropertyFloatConstRange<HelicopterSpawnBloodtoxTrack>;
			template class fight::TrackFactoryTemplate<HelicopterSpawnBloodtoxTrack>;
			template class fight::TrackFactoryCasterTemplate<HelicopterSpawnBloodtoxTrack>;
			template class fight::PropertyFloatConstRange<VehiclePlayAnimationTrack>;
			template class fight::TrackFactoryTemplate<VehiclePlayAnimationTrack>;
			template class fight::TrackFactoryCasterTemplate<VehiclePlayAnimationTrack>;
			template class fight::PropertyBool<SetVehicleHeadlightTrack>;
			template class fight::TrackFactoryTemplate<SetVehicleHeadlightTrack>;
			template class fight::TrackFactoryCasterTemplate<SetVehicleHeadlightTrack>;
			template class fight::PropertyFloatConstRange<VehiclePowerOnOffTrack>;
			template class fight::PropertyBool<VehiclePowerOnOffTrack>;
			template class fight::TrackFactoryTemplate<VehiclePowerOnOffTrack>;
			template class fight::TrackFactoryCasterTemplate<VehiclePowerOnOffTrack>;
			template class fight::PropertyFloatConstRange<SetSecondaryWeaponTypeTrack>;
			template class fight::PropertyEnumConstList<SetSecondaryWeaponTypeTrack>;
			template class fight::TrackFactoryTemplate<SetSecondaryWeaponTypeTrack>;
			template class fight::TrackFactoryCasterTemplate<SetSecondaryWeaponTypeTrack>;
			template class fight::PropertyBool<SetVehicleSolverEnabledTrack>;
			template class fight::TrackFactoryTemplate<SetVehicleSolverEnabledTrack>;
			template class fight::TrackFactoryCasterTemplate<SetVehicleSolverEnabledTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101C8C40
// FUNCTION: ENGINE 0x101C8C70
// FUNCTION: ENGINE 0x101C8CA0
// FUNCTION: ENGINE 0x101C8CD0
// FUNCTION: ENGINE 0x101C8D00
// FUNCTION: ENGINE 0x101C8D30
// FUNCTION: ENGINE 0x101C8D60
// FUNCTION: ENGINE 0x101C8D90
// FUNCTION: ENGINE 0x101C8DC0
// FUNCTION: ENGINE 0x101C8DF0
// FUNCTION: ENGINE 0x101C8E20
// FUNCTION: ENGINE 0x101C8E50
// FUNCTION: ENGINE 0x101C8E80
// FUNCTION: ENGINE 0x101C8E90
// FUNCTION: ENGINE 0x101C8EC0
// FUNCTION: ENGINE 0x101C8ED0
// FUNCTION: ENGINE 0x101C8F00
// FUNCTION: ENGINE 0x101C8F10
// FUNCTION: ENGINE 0x101C8F40
// FUNCTION: ENGINE 0x101C8F50
// FUNCTION: ENGINE 0x101C8F80
// FUNCTION: ENGINE 0x101C8F90
// FUNCTION: ENGINE 0x101C8FC0
// FUNCTION: ENGINE 0x101C8FD0
// FUNCTION: ENGINE 0x101C9000
// FUNCTION: ENGINE 0x101C9010
// FUNCTION: ENGINE 0x101C9040
// FUNCTION: ENGINE 0x101C9050
// FUNCTION: ENGINE 0x101C9080
// FUNCTION: ENGINE 0x101C9090
// FUNCTION: ENGINE 0x101C90C0
// FUNCTION: ENGINE 0x101C90D0
// FUNCTION: ENGINE 0x101C9100
// FUNCTION: ENGINE 0x101C9110
// FUNCTION: ENGINE 0x101C9140
// FUNCTION: ENGINE 0x101C9150
// FUNCTION: ENGINE 0x101C9180
// FUNCTION: ENGINE 0x101C91C0
// FUNCTION: ENGINE 0x101C91D0
// FUNCTION: ENGINE 0x101C9200
// FUNCTION: ENGINE 0x101C9220
// FUNCTION: ENGINE 0x101C9230
// FUNCTION: ENGINE 0x101C9260
// FUNCTION: ENGINE 0x101C9290
// FUNCTION: ENGINE 0x101C92A0
// FUNCTION: ENGINE 0x101C92E0
// FUNCTION: ENGINE 0x101C92F0
// FUNCTION: ENGINE 0x101C9320
// FUNCTION: ENGINE 0x101C9340
// FUNCTION: ENGINE 0x101C9350
// FUNCTION: ENGINE 0x101C9380
// FUNCTION: ENGINE 0x101C93B0
// FUNCTION: ENGINE 0x101C93C0
// FUNCTION: ENGINE 0x101C9400
// FUNCTION: ENGINE 0x101C9410
// FUNCTION: ENGINE 0x101C9440
// FUNCTION: ENGINE 0x101C9460
// FUNCTION: ENGINE 0x101C9470
// FUNCTION: ENGINE 0x101C94A0
// FUNCTION: ENGINE 0x101C94C0
// FUNCTION: ENGINE 0x101C94D0
// FUNCTION: ENGINE 0x101C9510
// FUNCTION: ENGINE 0x101C9520
// FUNCTION: ENGINE 0x101C9550
// FUNCTION: ENGINE 0x101C9570
// FUNCTION: ENGINE 0x101C9580
// FUNCTION: ENGINE 0x101C95B0
// FUNCTION: ENGINE 0x101C95E0
// FUNCTION: ENGINE 0x101C95F0
// FUNCTION: ENGINE 0x101C9620
// FUNCTION: ENGINE 0x101C9640
// FUNCTION: ENGINE 0x101C9650
// FUNCTION: ENGINE 0x101C9680
// FUNCTION: ENGINE 0x101C96B0
// FUNCTION: ENGINE 0x101C96C0
// FUNCTION: ENGINE 0x101C96F0
// FUNCTION: ENGINE 0x101C9720
// FUNCTION: ENGINE 0x101C9730
// FUNCTION: ENGINE 0x101C9760
// FUNCTION: ENGINE 0x101C9780
// FUNCTION: ENGINE 0x101C9790
// FUNCTION: ENGINE 0x101C97C0
// FUNCTION: ENGINE 0x101C97F0
// FUNCTION: ENGINE 0x101C9800
// FUNCTION: ENGINE 0x101C9830
// FUNCTION: ENGINE 0x101C9850
// FUNCTION: ENGINE 0x101C9860
// FUNCTION: ENGINE 0x101C9890
// FUNCTION: ENGINE 0x101C98C0
// FUNCTION: ENGINE 0x101C98D0
// FUNCTION: ENGINE 0x101C9910
// FUNCTION: ENGINE 0x101C9920
// FUNCTION: ENGINE 0x101C9950
// FUNCTION: ENGINE 0x101C9970
// FUNCTION: ENGINE 0x101C9980
// FUNCTION: ENGINE 0x101C99B0
// FUNCTION: ENGINE 0x101C99D0
// FUNCTION: ENGINE 0x101CA870
// FUNCTION: ENGINE 0x101CA8A0
// FUNCTION: ENGINE 0x101CA8C0
// FUNCTION: ENGINE 0x101CA8F0
// FUNCTION: ENGINE 0x101CA910
// FUNCTION: ENGINE 0x101CA940
// FUNCTION: ENGINE 0x101CA960
// FUNCTION: ENGINE 0x101CA990
// FUNCTION: ENGINE 0x101CA9B0
// FUNCTION: ENGINE 0x101CA9E0
// FUNCTION: ENGINE 0x101CAA00
// FUNCTION: ENGINE 0x101CAA30
// FUNCTION: ENGINE 0x101CAA50
// FUNCTION: ENGINE 0x101CAA80
// FUNCTION: ENGINE 0x101CAAA0
// FUNCTION: ENGINE 0x101CAAD0
// FUNCTION: ENGINE 0x101CAAF0
// FUNCTION: ENGINE 0x101CAB20
// FUNCTION: ENGINE 0x101CAB40
// FUNCTION: ENGINE 0x101CAB70
// FUNCTION: ENGINE 0x101CAB90
// FUNCTION: ENGINE 0x101CABC0
// FUNCTION: ENGINE 0x101CABE0
// FUNCTION: ENGINE 0x101CAC10
// FUNCTION: ENGINE 0x101CAC30
// FUNCTION: ENGINE 0x101CAC80
// FUNCTION: ENGINE 0x101CACD0
// FUNCTION: ENGINE 0x101CAD20
// FUNCTION: ENGINE 0x101CAD70
// FUNCTION: ENGINE 0x101CADC0
// FUNCTION: ENGINE 0x101CAE10
// FUNCTION: ENGINE 0x101CAE60
// FUNCTION: ENGINE 0x101CAEB0
// FUNCTION: ENGINE 0x101CAF00
// FUNCTION: ENGINE 0x101CAF50
// FUNCTION: ENGINE 0x101CAFA0
