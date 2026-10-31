// Fight items of the ai group: InReservedAreaCondition, DestinationDistanceCondition, GroundDistanceCondition, DestinationTargetOrientationCondition, InsideReservedVolumeCondition, InBlastAreaCondition, StuckCondition, HaveDestinationCondition, InHotZoneCondition, DestinationHaveArrivedCondition, SetAvoidanceGapAnywhereTrack, SpeedTrack, DestinationJumpToTrack, DestinationFlyToTrack, SetIntersectionPropertiesTrack, DisableStayOnNavmeshTrack, TargetGoToTrack, ForceMotionTrack, ForceRecalculatePathTrack, ReserveVolumeTrack, DestinationSetDeadBodyTrack, StopTrack, TempSpeedTrack, SetBrakeDistanceTrack, AimTrack, DestinationGoToTrack (unit 0x1023BC30 - 0x102432A0; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_destination.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gInReservedAreaConditionProperties;  // 0x11255A90

			// FUNCTION: ENGINE 0x1023BC30
			bool InReservedAreaCondition::SetUseDestination(bool newValue)
			{
				useDestination = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C590
			fight::Property* InReservedAreaCondition::GetProperty(int index)
			{
				return gInReservedAreaConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1023C5B0
			void InReservedAreaCondition::ClearProperties()
			{
				fight::FreePropertyList(&gInReservedAreaConditionProperties);
			}

			// FUNCTION: ENGINE 0x1023C5C0
			InReservedAreaCondition::InReservedAreaCondition() : fight::Condition(0), useDestination(true)
			{
			}

			// FUNCTION: ENGINE 0x1023C5E0
			InReservedAreaCondition::~InReservedAreaCondition()
			{
			}

			// FUNCTION: ENGINE 0x1023FD80
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void InReservedAreaCondition::RegisterProperties()
			{
				if (gInReservedAreaConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<InReservedAreaCondition>("useDestination", &InReservedAreaCondition::SetUseDestination);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gInReservedAreaConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023F8A0
			fight::ConditionFactory* CreateInReservedAreaConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InReservedAreaCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10241D20
			void RegisterInReservedAreaConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InReservedAreaCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDestinationDistanceConditionProperties;  // 0x11255A94

			// FUNCTION: ENGINE 0x1023BC40
			bool DestinationDistanceCondition::SetDirection(int newValue)
			{
				direction = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BC50
			bool DestinationDistanceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BC60
			bool DestinationDistanceCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BC80
			bool DestinationDistanceCondition::SetUseParams(bool newValue)
			{
				useParams = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C5F0
			fight::Property* DestinationDistanceCondition::GetProperty(int index)
			{
				return gDestinationDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1023C610
			void DestinationDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDestinationDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x1023C620
			DestinationDistanceCondition::DestinationDistanceCondition() : fight::Condition(0), distance(2e+01f), compare(4), direction(0), useParams(false)
			{
			}

			// FUNCTION: ENGINE 0x1023C660
			DestinationDistanceCondition::~DestinationDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x1023FE20
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DestinationDistanceCondition::RegisterProperties()
			{
				if (gDestinationDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<DestinationDistanceCondition>("direction", motion::gCrowdPositionConditionDirectionTable, motion::gCrowdPositionConditionDirectionCount, &DestinationDistanceCondition::SetDirection);
					properties[0] = property;
					property = new fight::PropertyEnumConstList<DestinationDistanceCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &DestinationDistanceCondition::SetCompare);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DestinationDistanceCondition>("distance", &DestinationDistanceCondition::SetDistance);
					properties[2] = property;
					property = new fight::PropertyBool<DestinationDistanceCondition>("useParams", &DestinationDistanceCondition::SetUseParams);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gDestinationDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023F8D0
			fight::ConditionFactory* CreateDestinationDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DestinationDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10241D50
			void RegisterDestinationDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DestinationDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gGroundDistanceConditionProperties;  // 0x11255A98

			// FUNCTION: ENGINE 0x1023BC90
			bool GroundDistanceCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BCA0
			bool GroundDistanceCondition::SetDistance(float newValue)
			{
				distance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BCC0
			bool GroundDistanceCondition::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BCE0
			bool GroundDistanceCondition::SetGroundUnit(bool newValue)
			{
				groundUnit = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C670
			fight::Property* GroundDistanceCondition::GetProperty(int index)
			{
				return gGroundDistanceConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1023C690
			void GroundDistanceCondition::ClearProperties()
			{
				fight::FreePropertyList(&gGroundDistanceConditionProperties);
			}

			// FUNCTION: ENGINE 0x1023C6A0
			GroundDistanceCondition::GroundDistanceCondition() : fight::Condition(0), distance(2e+01f), radius(2e+01f), compare(4), groundUnit(false)
			{
			}

			// FUNCTION: ENGINE 0x1023C6E0
			GroundDistanceCondition::~GroundDistanceCondition()
			{
			}

			// FUNCTION: ENGINE 0x1023FFA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void GroundDistanceCondition::RegisterProperties()
			{
				if (gGroundDistanceConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<GroundDistanceCondition>("compare", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &GroundDistanceCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<GroundDistanceCondition>("distance", &GroundDistanceCondition::SetDistance);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<GroundDistanceCondition>("radius", &GroundDistanceCondition::SetRadius);
					properties[2] = property;
					property = new fight::PropertyBool<GroundDistanceCondition>("groundUnit", &GroundDistanceCondition::SetGroundUnit);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gGroundDistanceConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023F900
			fight::ConditionFactory* CreateGroundDistanceConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GroundDistanceCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10241D80
			void RegisterGroundDistanceConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<GroundDistanceCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDestinationTargetOrientationConditionProperties;  // 0x11255A9C

			// FUNCTION: ENGINE 0x1023BCF0
			bool DestinationTargetOrientationCondition::SetCompareTime(int newValue)
			{
				compareTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BD00
			bool DestinationTargetOrientationCondition::SetAngle(float newValue)
			{
				angle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BD20
			bool DestinationTargetOrientationCondition::SetSigned(bool newValue)
			{
				signedValue = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BD30
			bool DestinationTargetOrientationCondition::SetUseParams(bool newValue)
			{
				useParams = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C6F0
			fight::Property* DestinationTargetOrientationCondition::GetProperty(int index)
			{
				return gDestinationTargetOrientationConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1023C710
			void DestinationTargetOrientationCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDestinationTargetOrientationConditionProperties);
			}

			// FUNCTION: ENGINE 0x1023C720
			DestinationTargetOrientationCondition::DestinationTargetOrientationCondition() : fight::Condition(0), angle(0.0f), compareTime(4), signedValue(false), useParams(false)
			{
			}

			// FUNCTION: ENGINE 0x1023C760
			DestinationTargetOrientationCondition::~DestinationTargetOrientationCondition()
			{
			}

			// FUNCTION: ENGINE 0x10240110
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DestinationTargetOrientationCondition::RegisterProperties()
			{
				if (gDestinationTargetOrientationConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<DestinationTargetOrientationCondition>("compareTime", motion::gDistanceFromWaterSurfaceConditionCompareTable, motion::gDistanceFromWaterSurfaceConditionCompareCount, &DestinationTargetOrientationCondition::SetCompareTime);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DestinationTargetOrientationCondition>("angle", &DestinationTargetOrientationCondition::SetAngle);
					properties[1] = property;
					property = new fight::PropertyBool<DestinationTargetOrientationCondition>("signed", &DestinationTargetOrientationCondition::SetSigned);
					properties[2] = property;
					property = new fight::PropertyBool<DestinationTargetOrientationCondition>("useParams", &DestinationTargetOrientationCondition::SetUseParams);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gDestinationTargetOrientationConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023F930
			fight::ConditionFactory* CreateDestinationTargetOrientationConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DestinationTargetOrientationCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10241DB0
			void RegisterDestinationTargetOrientationConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DestinationTargetOrientationCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gInsideReservedVolumeConditionProperties;  // 0x11255AA0

			// FUNCTION: ENGINE 0x1023BD40
			bool InsideReservedVolumeCondition::SetInside(bool newValue)
			{
				inside = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BD50
			bool InsideReservedVolumeCondition::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BD70
			bool InsideReservedVolumeCondition::SetDestination(bool newValue)
			{
				destination = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C770
			fight::Property* InsideReservedVolumeCondition::GetProperty(int index)
			{
				return gInsideReservedVolumeConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1023C790
			void InsideReservedVolumeCondition::ClearProperties()
			{
				fight::FreePropertyList(&gInsideReservedVolumeConditionProperties);
			}

			// FUNCTION: ENGINE 0x1023C7A0
			InsideReservedVolumeCondition::InsideReservedVolumeCondition() : fight::Condition(0), radius(2e+01f), destination(false), inside(true)
			{
			}

			// FUNCTION: ENGINE 0x1023C7E0
			InsideReservedVolumeCondition::~InsideReservedVolumeCondition()
			{
			}

			// FUNCTION: ENGINE 0x10240280
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void InsideReservedVolumeCondition::RegisterProperties()
			{
				if (gInsideReservedVolumeConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<InsideReservedVolumeCondition>("inside", &InsideReservedVolumeCondition::SetInside);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<InsideReservedVolumeCondition>("radius", &InsideReservedVolumeCondition::SetRadius);
					properties[1] = property;
					property = new fight::PropertyBool<InsideReservedVolumeCondition>("destination", &InsideReservedVolumeCondition::SetDestination);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gInsideReservedVolumeConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023F960
			fight::ConditionFactory* CreateInsideReservedVolumeConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InsideReservedVolumeCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10241DE0
			void RegisterInsideReservedVolumeConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InsideReservedVolumeCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gInBlastAreaConditionProperties;  // 0x11255AA4

			// FUNCTION: ENGINE 0x1023BD80
			bool InBlastAreaCondition::SetUseDestination(bool newValue)
			{
				useDestination = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C7F0
			fight::Property* InBlastAreaCondition::GetProperty(int index)
			{
				return gInBlastAreaConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1023C810
			void InBlastAreaCondition::ClearProperties()
			{
				fight::FreePropertyList(&gInBlastAreaConditionProperties);
			}

			// FUNCTION: ENGINE 0x1023C820
			InBlastAreaCondition::InBlastAreaCondition() : fight::Condition(0), useDestination(true)
			{
			}

			// FUNCTION: ENGINE 0x1023C840
			InBlastAreaCondition::~InBlastAreaCondition()
			{
			}

			// FUNCTION: ENGINE 0x10240390
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void InBlastAreaCondition::RegisterProperties()
			{
				if (gInBlastAreaConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<InBlastAreaCondition>("useDestination", &InBlastAreaCondition::SetUseDestination);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gInBlastAreaConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023F990
			fight::ConditionFactory* CreateInBlastAreaConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InBlastAreaCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10241E10
			void RegisterInBlastAreaConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InBlastAreaCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gStuckConditionProperties;  // 0x11255AA8

			// FUNCTION: ENGINE 0x1023BD90
			bool StuckCondition::SetStuck(bool newValue)
			{
				stuck = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BDA0
			bool StuckCondition::SetTimeStuck(float newValue)
			{
				timeStuck = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C850
			fight::Property* StuckCondition::GetProperty(int index)
			{
				return gStuckConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1023C870
			void StuckCondition::ClearProperties()
			{
				fight::FreePropertyList(&gStuckConditionProperties);
			}

			// FUNCTION: ENGINE 0x1023C880
			StuckCondition::StuckCondition() : fight::Condition(0), timeStuck(0.1f), stuck(true)
			{
			}

			// FUNCTION: ENGINE 0x1023C8B0
			StuckCondition::~StuckCondition()
			{
			}

			// FUNCTION: ENGINE 0x10240430
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void StuckCondition::RegisterProperties()
			{
				if (gStuckConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<StuckCondition>("stuck", &StuckCondition::SetStuck);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<StuckCondition>("timeStuck", &StuckCondition::SetTimeStuck);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gStuckConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023F9C0
			fight::ConditionFactory* CreateStuckConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<StuckCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10241E40
			void RegisterStuckConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<StuckCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gHaveDestinationConditionProperties;  // 0x11255AAC

			// FUNCTION: ENGINE 0x1023C920
			fight::Property* HaveDestinationCondition::GetProperty(int index)
			{
				return gHaveDestinationConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1023C940
			void HaveDestinationCondition::ClearProperties()
			{
				fight::FreePropertyList(&gHaveDestinationConditionProperties);
			}

			// FUNCTION: ENGINE 0x1023C950
			HaveDestinationCondition::HaveDestinationCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1023C970
			HaveDestinationCondition::~HaveDestinationCondition()
			{
			}

			// FUNCTION: ENGINE 0x1023C8C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void HaveDestinationCondition::RegisterProperties()
			{
				if (gHaveDestinationConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gHaveDestinationConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023F9F0
			fight::ConditionFactory* CreateHaveDestinationConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HaveDestinationCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10241E70
			void RegisterHaveDestinationConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<HaveDestinationCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gInHotZoneConditionProperties;  // 0x11255AB0

			// FUNCTION: ENGINE 0x1023BDC0
			bool InHotZoneCondition::SetIn(bool newValue)
			{
				in = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BDD0
			bool InHotZoneCondition::SetRequireStayOnGround(bool newValue)
			{
				requireStayOnGround = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C980
			fight::Property* InHotZoneCondition::GetProperty(int index)
			{
				return gInHotZoneConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1023C9A0
			void InHotZoneCondition::ClearProperties()
			{
				fight::FreePropertyList(&gInHotZoneConditionProperties);
			}

			// FUNCTION: ENGINE 0x1023C9B0
			InHotZoneCondition::InHotZoneCondition() : fight::Condition(0), in(true), requireStayOnGround(true)
			{
			}

			// FUNCTION: ENGINE 0x1023C9E0
			InHotZoneCondition::~InHotZoneCondition()
			{
			}

			// FUNCTION: ENGINE 0x10240510
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void InHotZoneCondition::RegisterProperties()
			{
				if (gInHotZoneConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBool<InHotZoneCondition>("in", &InHotZoneCondition::SetIn);
					properties[0] = property;
					property = new fight::PropertyBool<InHotZoneCondition>("requireStayOnGround", &InHotZoneCondition::SetRequireStayOnGround);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gInHotZoneConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023FA20
			fight::ConditionFactory* CreateInHotZoneConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InHotZoneCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10241EA0
			void RegisterInHotZoneConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<InHotZoneCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gDestinationHaveArrivedConditionProperties;  // 0x11255AB4

			// FUNCTION: ENGINE 0x1023CA50
			fight::Property* DestinationHaveArrivedCondition::GetProperty(int index)
			{
				return gDestinationHaveArrivedConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x1023CA70
			void DestinationHaveArrivedCondition::ClearProperties()
			{
				fight::FreePropertyList(&gDestinationHaveArrivedConditionProperties);
			}

			// FUNCTION: ENGINE 0x1023CA80
			DestinationHaveArrivedCondition::DestinationHaveArrivedCondition() : fight::Condition(0)
			{
			}

			// FUNCTION: ENGINE 0x1023CAA0
			DestinationHaveArrivedCondition::~DestinationHaveArrivedCondition()
			{
			}

			// FUNCTION: ENGINE 0x1023C9F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DestinationHaveArrivedCondition::RegisterProperties()
			{
				if (gDestinationHaveArrivedConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					fight::RegisterPropertyList(properties, &gDestinationHaveArrivedConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023FA50
			fight::ConditionFactory* CreateDestinationHaveArrivedConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DestinationHaveArrivedCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10241ED0
			void RegisterDestinationHaveArrivedConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<DestinationHaveArrivedCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gSetAvoidanceGapAnywhereTrackProperties;  // 0x11255AB8

			// FUNCTION: ENGINE 0x1023BDE0
			bool SetAvoidanceGapAnywhereTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BE00
			bool SetAvoidanceGapAnywhereTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BE20
			bool SetAvoidanceGapAnywhereTrack::SetEnable(bool newValue)
			{
				enable = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BE30
			bool SetAvoidanceGapAnywhereTrack::SetTemporary(bool newValue)
			{
				temporary = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023CAB0
			fight::Property* SetAvoidanceGapAnywhereTrack::GetProperty(int index)
			{
				return gSetAvoidanceGapAnywhereTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023CAD0
			void SetAvoidanceGapAnywhereTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetAvoidanceGapAnywhereTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023CAE0
			SetAvoidanceGapAnywhereTrack::SetAvoidanceGapAnywhereTrack() : timeBegin(0.0f), timeEnd(-1.0f), enable(true), temporary(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1023CB30
			float SetAvoidanceGapAnywhereTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1023CB40
			float SetAvoidanceGapAnywhereTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1023CB50
			SetAvoidanceGapAnywhereTrack::~SetAvoidanceGapAnywhereTrack()
			{
			}

			// FUNCTION: ENGINE 0x102405F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetAvoidanceGapAnywhereTrack::RegisterProperties()
			{
				if (gSetAvoidanceGapAnywhereTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SetAvoidanceGapAnywhereTrack>("timeBegin", &SetAvoidanceGapAnywhereTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SetAvoidanceGapAnywhereTrack>("timeEnd", &SetAvoidanceGapAnywhereTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<SetAvoidanceGapAnywhereTrack>("enable", &SetAvoidanceGapAnywhereTrack::SetEnable);
					properties[2] = property;
					property = new fight::PropertyBool<SetAvoidanceGapAnywhereTrack>("temporary", &SetAvoidanceGapAnywhereTrack::SetTemporary);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gSetAvoidanceGapAnywhereTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023FA80
			fight::TrackFactory* CreateSetAvoidanceGapAnywhereTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetAvoidanceGapAnywhereTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10241F00
			void RegisterSetAvoidanceGapAnywhereTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetAvoidanceGapAnywhereTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSpeedTrackProperties;  // 0x11255ABC

			// FUNCTION: ENGINE 0x1023BE40
			bool SpeedTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BE60
			bool SpeedTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BE80
			bool SpeedTrack::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BEA0
			bool SpeedTrack::SetSprint(bool newValue)
			{
				sprint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BEB0
			bool SpeedTrack::SetUseMaxSpeed(bool newValue)
			{
				useMaxSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023CB60
			fight::Property* SpeedTrack::GetProperty(int index)
			{
				return gSpeedTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023CB80
			void SpeedTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSpeedTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023CB90
			SpeedTrack::SpeedTrack() : speed(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), sprint(false), useMaxSpeed(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1023CBE0
			float SpeedTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1023CBF0
			float SpeedTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1023CC00
			SpeedTrack::~SpeedTrack()
			{
			}

			// FUNCTION: ENGINE 0x10240740
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SpeedTrack::RegisterProperties()
			{
				if (gSpeedTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SpeedTrack>("timeBegin", &SpeedTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SpeedTrack>("timeEnd", &SpeedTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<SpeedTrack>("speed", &SpeedTrack::SetSpeed);
					properties[2] = property;
					property = new fight::PropertyBool<SpeedTrack>("sprint", &SpeedTrack::SetSprint);
					properties[3] = property;
					property = new fight::PropertyBool<SpeedTrack>("useMaxSpeed", &SpeedTrack::SetUseMaxSpeed);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gSpeedTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023FAB0
			fight::TrackFactory* CreateSpeedTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SpeedTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10241F30
			void RegisterSpeedTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SpeedTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gDestinationJumpToTrackProperties;  // 0x11255AC0

			// FUNCTION: ENGINE 0x1023BEC0
			bool DestinationJumpToTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BEE0
			bool DestinationJumpToTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BF00
			bool DestinationJumpToTrack::SetReverseFacing(bool newValue)
			{
				reverseFacing = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023CC10
			fight::Property* DestinationJumpToTrack::GetProperty(int index)
			{
				return gDestinationJumpToTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023CC30
			void DestinationJumpToTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDestinationJumpToTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023CC40
			DestinationJumpToTrack::DestinationJumpToTrack() : timeBegin(0.0f), timeEnd(-1.0f), reverseFacing(false)
			{
			}

			// FUNCTION: ENGINE 0x1023CC80
			float DestinationJumpToTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1023CC90
			float DestinationJumpToTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1023CCA0
			DestinationJumpToTrack::~DestinationJumpToTrack()
			{
			}

			// FUNCTION: ENGINE 0x102408D0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DestinationJumpToTrack::RegisterProperties()
			{
				if (gDestinationJumpToTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DestinationJumpToTrack>("timeBegin", &DestinationJumpToTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DestinationJumpToTrack>("timeEnd", &DestinationJumpToTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<DestinationJumpToTrack>("reverseFacing", &DestinationJumpToTrack::SetReverseFacing);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gDestinationJumpToTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023FAE0
			fight::TrackFactory* CreateDestinationJumpToTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DestinationJumpToTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10241F60
			void RegisterDestinationJumpToTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DestinationJumpToTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gDestinationFlyToTrackProperties;  // 0x11255AC4

			// FUNCTION: ENGINE 0x1023BF10
			bool DestinationFlyToTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BF30
			bool DestinationFlyToTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BF50
			bool DestinationFlyToTrack::SetTolerance(float newValue)
			{
				tolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BF70
			bool DestinationFlyToTrack::SetBrake(bool newValue)
			{
				brake = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BF80
			bool DestinationFlyToTrack::SetIgnoreRestrictions(bool newValue)
			{
				ignoreRestrictions = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BF90
			bool DestinationFlyToTrack::SetFreeArea(float newValue)
			{
				freeArea = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BFB0
			bool DestinationFlyToTrack::SetMinHeight(float newValue)
			{
				minHeight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BFD0
			bool DestinationFlyToTrack::SetMaxSpeed(float newValue)
			{
				maxSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023BFF0
			bool DestinationFlyToTrack::SetSpeedFactor(const math::Vector& newValue)
			{
				speedFactor.x = newValue.x;
				speedFactor.y = newValue.y;
				speedFactor.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C010
			bool DestinationFlyToTrack::SetTurningFactorA(int newValue)
			{
				turningFactorA = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C020
			bool DestinationFlyToTrack::SetTurningFactorB(int newValue)
			{
				turningFactorB = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023CCB0
			fight::Property* DestinationFlyToTrack::GetProperty(int index)
			{
				return gDestinationFlyToTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023CCD0
			void DestinationFlyToTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDestinationFlyToTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023CCE0
			DestinationFlyToTrack::DestinationFlyToTrack() : speedFactor(-1.0f, -1.0f, -1.0f), freeArea(0.0f), maxSpeed(1.0f), minHeight(6.0f), timeBegin(0.0f), timeEnd(-1.0f), tolerance(0.5f), turningFactorA(2), turningFactorB(0), brake(true), ignoreRestrictions(false)
			{
			}

			// FUNCTION: ENGINE 0x1023CD80
			float DestinationFlyToTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1023CD90
			float DestinationFlyToTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1023CDA0
			DestinationFlyToTrack::~DestinationFlyToTrack()
			{
			}

			// FUNCTION: ENGINE 0x102409E0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DestinationFlyToTrack::RegisterProperties()
			{
				if (gDestinationFlyToTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DestinationFlyToTrack>("timeBegin", &DestinationFlyToTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DestinationFlyToTrack>("timeEnd", &DestinationFlyToTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DestinationFlyToTrack>("tolerance", &DestinationFlyToTrack::SetTolerance);
					properties[2] = property;
					property = new fight::PropertyBool<DestinationFlyToTrack>("brake", &DestinationFlyToTrack::SetBrake);
					properties[3] = property;
					property = new fight::PropertyBool<DestinationFlyToTrack>("ignoreRestrictions", &DestinationFlyToTrack::SetIgnoreRestrictions);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<DestinationFlyToTrack>("freeArea", &DestinationFlyToTrack::SetFreeArea);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<DestinationFlyToTrack>("minHeight", &DestinationFlyToTrack::SetMinHeight);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<DestinationFlyToTrack>("maxSpeed", &DestinationFlyToTrack::SetMaxSpeed);
					properties[7] = property;
					property = new fight::PropertyVector<DestinationFlyToTrack>("speedFactor", &DestinationFlyToTrack::SetSpeedFactor);
					properties[8] = property;
					property = new fight::PropertyIntConstRange<DestinationFlyToTrack>("turningFactorA", &DestinationFlyToTrack::SetTurningFactorA);
					properties[9] = property;
					property = new fight::PropertyIntConstRange<DestinationFlyToTrack>("turningFactorB", &DestinationFlyToTrack::SetTurningFactorB);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gDestinationFlyToTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023FB10
			fight::TrackFactory* CreateDestinationFlyToTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DestinationFlyToTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10241F90
			void RegisterDestinationFlyToTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DestinationFlyToTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSetIntersectionPropertiesTrackProperties;  // 0x11255AC8

			// FUNCTION: ENGINE 0x1023C030
			bool SetIntersectionPropertiesTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C050
			bool SetIntersectionPropertiesTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023D590
			bool SetIntersectionPropertiesTrack::SetIntersectionProperties(const fight::Name& newValue)
			{
				intersectionProperties = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C070
			bool SetIntersectionPropertiesTrack::SetTemporary(bool newValue)
			{
				temporary = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023CDB0
			fight::Property* SetIntersectionPropertiesTrack::GetProperty(int index)
			{
				return gSetIntersectionPropertiesTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023CDD0
			void SetIntersectionPropertiesTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetIntersectionPropertiesTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023D850
			SetIntersectionPropertiesTrack::SetIntersectionPropertiesTrack() : timeBegin(0.0f), timeEnd(-1.0f), temporary(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1023D8A0
			float SetIntersectionPropertiesTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1023D8B0
			float SetIntersectionPropertiesTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1023D8C0
			SetIntersectionPropertiesTrack::~SetIntersectionPropertiesTrack()
			{
			}

			// FUNCTION: ENGINE 0x10242980
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetIntersectionPropertiesTrack::RegisterProperties()
			{
				if (gSetIntersectionPropertiesTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SetIntersectionPropertiesTrack>("timeBegin", &SetIntersectionPropertiesTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SetIntersectionPropertiesTrack>("timeEnd", &SetIntersectionPropertiesTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<SetIntersectionPropertiesTrack>("intersectionProperties", &SetIntersectionPropertiesTrack::SetIntersectionProperties);
					properties[2] = property;
					property = new fight::PropertyBool<SetIntersectionPropertiesTrack>("temporary", &SetIntersectionPropertiesTrack::SetTemporary);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gSetIntersectionPropertiesTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023FB40
			fight::TrackFactory* CreateSetIntersectionPropertiesTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetIntersectionPropertiesTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10241FC0
			void RegisterSetIntersectionPropertiesTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetIntersectionPropertiesTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gDisableStayOnNavmeshTrackProperties;  // 0x11255ACC

			// FUNCTION: ENGINE 0x1023C080
			bool DisableStayOnNavmeshTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C0A0
			bool DisableStayOnNavmeshTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023CDE0
			fight::Property* DisableStayOnNavmeshTrack::GetProperty(int index)
			{
				return gDisableStayOnNavmeshTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023CE00
			void DisableStayOnNavmeshTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDisableStayOnNavmeshTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023CE10
			DisableStayOnNavmeshTrack::DisableStayOnNavmeshTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1023CE50
			float DisableStayOnNavmeshTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1023CE60
			float DisableStayOnNavmeshTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1023CE70
			DisableStayOnNavmeshTrack::~DisableStayOnNavmeshTrack()
			{
			}

			// FUNCTION: ENGINE 0x10240CE0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DisableStayOnNavmeshTrack::RegisterProperties()
			{
				if (gDisableStayOnNavmeshTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DisableStayOnNavmeshTrack>("timeBegin", &DisableStayOnNavmeshTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DisableStayOnNavmeshTrack>("timeEnd", &DisableStayOnNavmeshTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gDisableStayOnNavmeshTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023FB70
			fight::TrackFactory* CreateDisableStayOnNavmeshTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DisableStayOnNavmeshTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10241FF0
			void RegisterDisableStayOnNavmeshTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DisableStayOnNavmeshTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTargetGoToTrackProperties;  // 0x11255AD0

			// FUNCTION: ENGINE 0x1023C0C0
			bool TargetGoToTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C0E0
			bool TargetGoToTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C100
			bool TargetGoToTrack::SetWhere(int newValue)
			{
				where = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C110
			bool TargetGoToTrack::SetTolerance(float newValue)
			{
				tolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C130
			bool TargetGoToTrack::SetToleranceRePathfind(float newValue)
			{
				toleranceRePathfind = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C150
			bool TargetGoToTrack::SetMinTimeBetweenPathfind(float newValue)
			{
				minTimeBetweenPathfind = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C170
			bool TargetGoToTrack::SetUseRandomOvershoot(bool newValue)
			{
				useRandomOvershoot = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C180
			bool TargetGoToTrack::SetRandomOvershootLowerBound(float newValue)
			{
				randomOvershootLowerBound = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C1A0
			bool TargetGoToTrack::SetRandomOvershootUpperBound(float newValue)
			{
				randomOvershootUpperBound = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C1C0
			bool TargetGoToTrack::SetBrake(bool newValue)
			{
				brake = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C1D0
			bool TargetGoToTrack::SetIgnoreRestrictions(bool newValue)
			{
				ignoreRestrictions = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C1E0
			bool TargetGoToTrack::SetStayOnGround(bool newValue)
			{
				stayOnGround = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C1F0
			bool TargetGoToTrack::SetProjectPositionToGround(bool newValue)
			{
				projectPositionToGround = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C200
			bool TargetGoToTrack::SetTargetClimbing(bool newValue)
			{
				targetClimbing = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023CE80
			fight::Property* TargetGoToTrack::GetProperty(int index)
			{
				return gTargetGoToTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023CEA0
			void TargetGoToTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTargetGoToTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023CEB0
			TargetGoToTrack::TargetGoToTrack() : minTimeBetweenPathfind(0.0f), randomOvershootLowerBound(2.0f), randomOvershootUpperBound(2.0f), timeBegin(0.0f), timeEnd(-1.0f), tolerance(3.0f), toleranceRePathfind(3.0f), where(0), brake(true), ignoreRestrictions(false), projectPositionToGround(false), stayOnGround(false), targetClimbing(false), useRandomOvershoot(false)
			{
			}

			// FUNCTION: ENGINE 0x1023CF40
			float TargetGoToTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1023CF50
			float TargetGoToTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1023CF60
			TargetGoToTrack::~TargetGoToTrack()
			{
			}

			// FUNCTION: ENGINE 0x10240DC0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TargetGoToTrack::RegisterProperties()
			{
				if (gTargetGoToTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TargetGoToTrack>("timeBegin", &TargetGoToTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TargetGoToTrack>("timeEnd", &TargetGoToTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<TargetGoToTrack>("where", gTargetGoToTrackWhereTable, gTargetGoToTrackWhereCount, &TargetGoToTrack::SetWhere);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<TargetGoToTrack>("tolerance", &TargetGoToTrack::SetTolerance);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<TargetGoToTrack>("toleranceRePathfind", &TargetGoToTrack::SetToleranceRePathfind);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<TargetGoToTrack>("minTimeBetweenPathfind", &TargetGoToTrack::SetMinTimeBetweenPathfind);
					properties[5] = property;
					property = new fight::PropertyBool<TargetGoToTrack>("useRandomOvershoot", &TargetGoToTrack::SetUseRandomOvershoot);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<TargetGoToTrack>("randomOvershootLowerBound", &TargetGoToTrack::SetRandomOvershootLowerBound);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<TargetGoToTrack>("randomOvershootUpperBound", &TargetGoToTrack::SetRandomOvershootUpperBound);
					properties[8] = property;
					property = new fight::PropertyBool<TargetGoToTrack>("brake", &TargetGoToTrack::SetBrake);
					properties[9] = property;
					property = new fight::PropertyBool<TargetGoToTrack>("ignoreRestrictions", &TargetGoToTrack::SetIgnoreRestrictions);
					properties[10] = property;
					property = new fight::PropertyBool<TargetGoToTrack>("stayOnGround", &TargetGoToTrack::SetStayOnGround);
					properties[11] = property;
					property = new fight::PropertyBool<TargetGoToTrack>("projectPositionToGround", &TargetGoToTrack::SetProjectPositionToGround);
					properties[12] = property;
					property = new fight::PropertyBool<TargetGoToTrack>("targetClimbing", &TargetGoToTrack::SetTargetClimbing);
					properties[13] = property;
					fight::RegisterPropertyList(properties, &gTargetGoToTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023FBA0
			fight::TrackFactory* CreateTargetGoToTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TargetGoToTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10242020
			void RegisterTargetGoToTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TargetGoToTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gForceMotionTrackProperties;  // 0x11255AD4

			// FUNCTION: ENGINE 0x1023C210
			bool ForceMotionTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C230
			bool ForceMotionTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C250
			bool ForceMotionTrack::SetMotion(const math::Vector& newValue)
			{
				motion.x = newValue.x;
				motion.y = newValue.y;
				motion.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C270
			bool ForceMotionTrack::SetLocal(bool newValue)
			{
				local = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C280
			bool ForceMotionTrack::SetAccelerationFactor(float newValue)
			{
				accelerationFactor = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023CF70
			fight::Property* ForceMotionTrack::GetProperty(int index)
			{
				return gForceMotionTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023CF90
			void ForceMotionTrack::ClearProperties()
			{
				fight::FreePropertyList(&gForceMotionTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023CFA0
			ForceMotionTrack::ForceMotionTrack() : motion(0.0f, 0.0f, 0.0f), accelerationFactor(1.0f), timeBegin(0.0f), timeEnd(-1.0f), local(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1023D010
			float ForceMotionTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1023D020
			float ForceMotionTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1023D030
			ForceMotionTrack::~ForceMotionTrack()
			{
			}

			// FUNCTION: ENGINE 0x10241190
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ForceMotionTrack::RegisterProperties()
			{
				if (gForceMotionTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ForceMotionTrack>("timeBegin", &ForceMotionTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ForceMotionTrack>("timeEnd", &ForceMotionTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyVector<ForceMotionTrack>("motion", &ForceMotionTrack::SetMotion);
					properties[2] = property;
					property = new fight::PropertyBool<ForceMotionTrack>("local", &ForceMotionTrack::SetLocal);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<ForceMotionTrack>("accelerationFactor", &ForceMotionTrack::SetAccelerationFactor);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gForceMotionTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023FBD0
			fight::TrackFactory* CreateForceMotionTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ForceMotionTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10242050
			void RegisterForceMotionTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ForceMotionTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gForceRecalculatePathTrackProperties;  // 0x11255AD8

			// FUNCTION: ENGINE 0x1023C2A0
			bool ForceRecalculatePathTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023D040
			fight::Property* ForceRecalculatePathTrack::GetProperty(int index)
			{
				return gForceRecalculatePathTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023D060
			void ForceRecalculatePathTrack::ClearProperties()
			{
				fight::FreePropertyList(&gForceRecalculatePathTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023D070
			ForceRecalculatePathTrack::ForceRecalculatePathTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1023D0A0
			float ForceRecalculatePathTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1023D0B0
			float ForceRecalculatePathTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1023D0C0
			ForceRecalculatePathTrack::~ForceRecalculatePathTrack()
			{
			}

			// FUNCTION: ENGINE 0x10241320
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ForceRecalculatePathTrack::RegisterProperties()
			{
				if (gForceRecalculatePathTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ForceRecalculatePathTrack>("timeBegin", &ForceRecalculatePathTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gForceRecalculatePathTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023FC00
			fight::TrackFactory* CreateForceRecalculatePathTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ForceRecalculatePathTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10242080
			void RegisterForceRecalculatePathTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ForceRecalculatePathTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gReserveVolumeTrackProperties;  // 0x11255ADC

			// FUNCTION: ENGINE 0x1023C2C0
			bool ReserveVolumeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C2E0
			bool ReserveVolumeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C300
			bool ReserveVolumeTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C320
			bool ReserveVolumeTrack::SetStrafeRun(bool newValue)
			{
				strafeRun = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023D0D0
			fight::Property* ReserveVolumeTrack::GetProperty(int index)
			{
				return gReserveVolumeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023D0F0
			void ReserveVolumeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gReserveVolumeTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023D100
			ReserveVolumeTrack::ReserveVolumeTrack() : radius(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), strafeRun(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1023D150
			float ReserveVolumeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1023D160
			float ReserveVolumeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1023D170
			ReserveVolumeTrack::~ReserveVolumeTrack()
			{
			}

			// FUNCTION: ENGINE 0x102413C0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ReserveVolumeTrack::RegisterProperties()
			{
				if (gReserveVolumeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ReserveVolumeTrack>("timeBegin", &ReserveVolumeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ReserveVolumeTrack>("timeEnd", &ReserveVolumeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ReserveVolumeTrack>("radius", &ReserveVolumeTrack::SetRadius);
					properties[2] = property;
					property = new fight::PropertyBool<ReserveVolumeTrack>("strafeRun", &ReserveVolumeTrack::SetStrafeRun);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gReserveVolumeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023FC30
			fight::TrackFactory* CreateReserveVolumeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReserveVolumeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102420B0
			void RegisterReserveVolumeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ReserveVolumeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gDestinationSetDeadBodyTrackProperties;  // 0x11255AE0

			// FUNCTION: ENGINE 0x1023C330
			fight::BranchHolder* DestinationSetDeadBodyTrack::SetBranch()
			{
				return &branch;
			}

			// FUNCTION: ENGINE 0x1023C340
			bool DestinationSetDeadBodyTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C350
			fight::ConditionList* DestinationSetDeadBodyTrack::SetConditions()
			{
				return &conditions;
			}

			// FUNCTION: ENGINE 0x1023D180
			fight::Property* DestinationSetDeadBodyTrack::GetProperty(int index)
			{
				return gDestinationSetDeadBodyTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023D1A0
			void DestinationSetDeadBodyTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDestinationSetDeadBodyTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023D1B0
			DestinationSetDeadBodyTrack::DestinationSetDeadBodyTrack() : branch(0), priority(0)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1023D1F0
			float DestinationSetDeadBodyTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1023D200
			float DestinationSetDeadBodyTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x1023D210
			DestinationSetDeadBodyTrack::~DestinationSetDeadBodyTrack()
			{
			}

			// FUNCTION: ENGINE 0x10241510
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DestinationSetDeadBodyTrack::RegisterProperties()
			{
				if (gDestinationSetDeadBodyTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyBranch<DestinationSetDeadBodyTrack>("branch", &DestinationSetDeadBodyTrack::SetBranch);
					properties[0] = property;
					property = new fight::PropertyIntConstRange<DestinationSetDeadBodyTrack>("priority", &DestinationSetDeadBodyTrack::SetPriority);
					properties[1] = property;
					property = new fight::PropertyConditionGroup<DestinationSetDeadBodyTrack>("conditions", &DestinationSetDeadBodyTrack::SetConditions);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gDestinationSetDeadBodyTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023FC60
			fight::TrackFactory* CreateDestinationSetDeadBodyTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DestinationSetDeadBodyTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102420E0
			void RegisterDestinationSetDeadBodyTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DestinationSetDeadBodyTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gStopTrackProperties;  // 0x11255AE4

			// FUNCTION: ENGINE 0x1023C360
			bool StopTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C380
			bool StopTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023D240
			fight::Property* StopTrack::GetProperty(int index)
			{
				return gStopTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023D260
			void StopTrack::ClearProperties()
			{
				fight::FreePropertyList(&gStopTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023D270
			StopTrack::StopTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x1023D2A0
			float StopTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1023D2B0
			float StopTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1023D2C0
			StopTrack::~StopTrack()
			{
			}

			// FUNCTION: ENGINE 0x10241620
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void StopTrack::RegisterProperties()
			{
				if (gStopTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<StopTrack>("timeBegin", &StopTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<StopTrack>("timeEnd", &StopTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gStopTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023FC90
			fight::TrackFactory* CreateStopTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<StopTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10242110
			void RegisterStopTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<StopTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gTempSpeedTrackProperties;  // 0x11255AE8

			// FUNCTION: ENGINE 0x1023C3A0
			bool TempSpeedTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C3C0
			bool TempSpeedTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C3E0
			bool TempSpeedTrack::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C400
			bool TempSpeedTrack::SetSprint(bool newValue)
			{
				sprint = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C410
			bool TempSpeedTrack::SetUseMaxSpeed(bool newValue)
			{
				useMaxSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023D2D0
			fight::Property* TempSpeedTrack::GetProperty(int index)
			{
				return gTempSpeedTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023D2F0
			void TempSpeedTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTempSpeedTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023D300
			TempSpeedTrack::TempSpeedTrack() : speed(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), sprint(false), useMaxSpeed(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1023D350
			float TempSpeedTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1023D360
			float TempSpeedTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1023D370
			TempSpeedTrack::~TempSpeedTrack()
			{
			}

			// FUNCTION: ENGINE 0x10241700
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TempSpeedTrack::RegisterProperties()
			{
				if (gTempSpeedTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TempSpeedTrack>("timeBegin", &TempSpeedTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TempSpeedTrack>("timeEnd", &TempSpeedTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TempSpeedTrack>("speed", &TempSpeedTrack::SetSpeed);
					properties[2] = property;
					property = new fight::PropertyBool<TempSpeedTrack>("sprint", &TempSpeedTrack::SetSprint);
					properties[3] = property;
					property = new fight::PropertyBool<TempSpeedTrack>("useMaxSpeed", &TempSpeedTrack::SetUseMaxSpeed);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gTempSpeedTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023FCC0
			fight::TrackFactory* CreateTempSpeedTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TempSpeedTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10242140
			void RegisterTempSpeedTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TempSpeedTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gSetBrakeDistanceTrackProperties;  // 0x11255AEC

			// FUNCTION: ENGINE 0x1023C420
			bool SetBrakeDistanceTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C440
			bool SetBrakeDistanceTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C460
			bool SetBrakeDistanceTrack::SetBrakeDistance(float newValue)
			{
				brakeDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023D380
			fight::Property* SetBrakeDistanceTrack::GetProperty(int index)
			{
				return gSetBrakeDistanceTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023D3A0
			void SetBrakeDistanceTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetBrakeDistanceTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023D3B0
			SetBrakeDistanceTrack::SetBrakeDistanceTrack() : brakeDistance(-1.0f), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x1023D3F0
			float SetBrakeDistanceTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1023D400
			float SetBrakeDistanceTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1023D410
			SetBrakeDistanceTrack::~SetBrakeDistanceTrack()
			{
			}

			// FUNCTION: ENGINE 0x10241890
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetBrakeDistanceTrack::RegisterProperties()
			{
				if (gSetBrakeDistanceTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SetBrakeDistanceTrack>("timeBegin", &SetBrakeDistanceTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SetBrakeDistanceTrack>("timeEnd", &SetBrakeDistanceTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<SetBrakeDistanceTrack>("brakeDistance", &SetBrakeDistanceTrack::SetBrakeDistance);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gSetBrakeDistanceTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023FCF0
			fight::TrackFactory* CreateSetBrakeDistanceTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetBrakeDistanceTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10242170
			void RegisterSetBrakeDistanceTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetBrakeDistanceTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gAimTrackProperties;  // 0x11255AF0

			// FUNCTION: ENGINE 0x1023C480
			bool AimTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C4A0
			bool AimTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C4C0
			bool AimTrack::SetWhere(int newValue)
			{
				where = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C4D0
			bool AimTrack::SetOffset(const math::Vector& newValue)
			{
				offset.x = newValue.x;
				offset.y = newValue.y;
				offset.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C4F0
			bool AimTrack::SetForceWorldAngles(bool newValue)
			{
				forceWorldAngles = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023D420
			fight::Property* AimTrack::GetProperty(int index)
			{
				return gAimTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023D440
			void AimTrack::ClearProperties()
			{
				fight::FreePropertyList(&gAimTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023D450
			AimTrack::AimTrack() : offset(0.0f, 0.0f, 0.0f), timeBegin(0.0f), timeEnd(-1.0f), where(0), forceWorldAngles(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1023D4B0
			float AimTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1023D4C0
			float AimTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1023D4D0
			AimTrack::~AimTrack()
			{
			}

			// FUNCTION: ENGINE 0x102419A0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void AimTrack::RegisterProperties()
			{
				if (gAimTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<AimTrack>("timeBegin", &AimTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<AimTrack>("timeEnd", &AimTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<AimTrack>("where", gAimTrackWhereTable, gAimTrackWhereCount, &AimTrack::SetWhere);
					properties[2] = property;
					property = new fight::PropertyVector<AimTrack>("offset", &AimTrack::SetOffset);
					properties[3] = property;
					property = new fight::PropertyBool<AimTrack>("forceWorldAngles", &AimTrack::SetForceWorldAngles);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gAimTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023FD20
			fight::TrackFactory* CreateAimTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<AimTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102421A0
			void RegisterAimTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<AimTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gDestinationGoToTrackProperties;  // 0x11255AF4

			// FUNCTION: ENGINE 0x1023C500
			bool DestinationGoToTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C520
			bool DestinationGoToTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C540
			bool DestinationGoToTrack::SetTolerance(float newValue)
			{
				tolerance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C560
			bool DestinationGoToTrack::SetBrake(bool newValue)
			{
				brake = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C570
			bool DestinationGoToTrack::SetIgnoreRestrictions(bool newValue)
			{
				ignoreRestrictions = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023C580
			bool DestinationGoToTrack::SetStayOnGround(bool newValue)
			{
				stayOnGround = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1023D4E0
			fight::Property* DestinationGoToTrack::GetProperty(int index)
			{
				return gDestinationGoToTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1023D500
			void DestinationGoToTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDestinationGoToTrackProperties);
			}

			// FUNCTION: ENGINE 0x1023D510
			DestinationGoToTrack::DestinationGoToTrack() : timeBegin(0.0f), timeEnd(-1.0f), tolerance(0.5f), brake(true), ignoreRestrictions(false), stayOnGround(false)
			{
			}

			// FUNCTION: ENGINE 0x1023D560
			float DestinationGoToTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1023D570
			float DestinationGoToTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1023D580
			DestinationGoToTrack::~DestinationGoToTrack()
			{
			}

			// FUNCTION: ENGINE 0x10241B50
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DestinationGoToTrack::RegisterProperties()
			{
				if (gDestinationGoToTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DestinationGoToTrack>("timeBegin", &DestinationGoToTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DestinationGoToTrack>("timeEnd", &DestinationGoToTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DestinationGoToTrack>("tolerance", &DestinationGoToTrack::SetTolerance);
					properties[2] = property;
					property = new fight::PropertyBool<DestinationGoToTrack>("brake", &DestinationGoToTrack::SetBrake);
					properties[3] = property;
					property = new fight::PropertyBool<DestinationGoToTrack>("ignoreRestrictions", &DestinationGoToTrack::SetIgnoreRestrictions);
					properties[4] = property;
					property = new fight::PropertyBool<DestinationGoToTrack>("stayOnGround", &DestinationGoToTrack::SetStayOnGround);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gDestinationGoToTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1023FD50
			fight::TrackFactory* CreateDestinationGoToTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DestinationGoToTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102421D0
			void RegisterDestinationGoToTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DestinationGoToTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x102037B0
			SetAvoidanceGapAnywhereAction::SetAvoidanceGapAnywhereAction(SetAvoidanceGapAnywhereTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x600), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x10200400
			SetAvoidanceGapAnywhereAction::~SetAvoidanceGapAnywhereAction()
			{
			}

			// FUNCTION: ENGINE 0x102044B0
			fight::Action* SetAvoidanceGapAnywhereTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new SetAvoidanceGapAnywhereAction(this, handle);
			}

			// FUNCTION: ENGINE 0x102025A0
			SpeedAction::SpeedAction(SpeedTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101FFED0
			SpeedAction::~SpeedAction()
			{
			}

			// FUNCTION: ENGINE 0x101FED50
			bool SpeedAction::Slot5(int arg, float value)
			{
				return true;
			}

			// FUNCTION: ENGINE 0x101FED60
			void SpeedAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x10204140
			fight::Action* SpeedTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new SpeedAction(this, handle);
			}

			// FUNCTION: ENGINE 0x102039E0
			DisableStayOnNavmeshAction::DisableStayOnNavmeshAction(DisableStayOnNavmeshTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x600), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x10200450
			DisableStayOnNavmeshAction::~DisableStayOnNavmeshAction()
			{
			}

			// FUNCTION: ENGINE 0x10204500
			fight::Action* DisableStayOnNavmeshTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new DisableStayOnNavmeshAction(this, handle);
			}

			// FUNCTION: ENGINE 0x10202ED0
			ForceMotionAction::ForceMotionAction(ForceMotionTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x102001C0
			ForceMotionAction::~ForceMotionAction()
			{
			}

			// FUNCTION: ENGINE 0x10204360
			fight::Action* ForceMotionTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ForceMotionAction(this, handle);
			}

			// FUNCTION: ENGINE 0x10202E20
			ForceRecalculatePathAction::ForceRecalculatePathAction(ForceRecalculatePathTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x10200100
			ForceRecalculatePathAction::~ForceRecalculatePathAction()
			{
			}

			// FUNCTION: ENGINE 0x10204310
			fight::Action* ForceRecalculatePathTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ForceRecalculatePathAction(this, handle);
			}

			// FUNCTION: ENGINE 0x102024F0
			StopAction::StopAction(StopTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101FFE30
			StopAction::~StopAction()
			{
			}

			// FUNCTION: ENGINE 0x101FED30
			bool StopAction::Slot5(int arg, float value)
			{
				return true;
			}

			// FUNCTION: ENGINE 0x101FED40
			void StopAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x102040F0
			fight::Action* StopTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new StopAction(this, handle);
			}

			// FUNCTION: ENGINE 0x10202730
			TempSpeedAction::TempSpeedAction(TempSpeedTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101FFF20
			TempSpeedAction::~TempSpeedAction()
			{
			}

			// FUNCTION: ENGINE 0x10204190
			fight::Action* TempSpeedTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new TempSpeedAction(this, handle);
			}

			// FUNCTION: ENGINE 0x10203110
			SetBrakeDistanceAction::SetBrakeDistanceAction(SetBrakeDistanceTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), unknown2C(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x10200280
			SetBrakeDistanceAction::~SetBrakeDistanceAction()
			{
			}

			// FUNCTION: ENGINE 0x102043B0
			fight::Action* SetBrakeDistanceTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new SetBrakeDistanceAction(this, handle);
			}

			// FUNCTION: ENGINE 0x102022F0
			AimAction::AimAction(AimTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101FFDE0
			AimAction::~AimAction()
			{
			}

			// FUNCTION: ENGINE 0x101FED20
			void AimAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x102040A0
			fight::Action* AimTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new AimAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyBool<InReservedAreaCondition>;
			template class fight::ConditionFactoryTemplate<InReservedAreaCondition>;
			template class fight::ConditionFactoryCasterTemplate<InReservedAreaCondition>;
			template class fight::PropertyEnumConstList<DestinationDistanceCondition>;
			template class fight::PropertyFloatConstRange<DestinationDistanceCondition>;
			template class fight::PropertyBool<DestinationDistanceCondition>;
			template class fight::ConditionFactoryTemplate<DestinationDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<DestinationDistanceCondition>;
			template class fight::PropertyEnumConstList<GroundDistanceCondition>;
			template class fight::PropertyFloatConstRange<GroundDistanceCondition>;
			template class fight::PropertyBool<GroundDistanceCondition>;
			template class fight::ConditionFactoryTemplate<GroundDistanceCondition>;
			template class fight::ConditionFactoryCasterTemplate<GroundDistanceCondition>;
			template class fight::PropertyEnumConstList<DestinationTargetOrientationCondition>;
			template class fight::PropertyFloatConstRange<DestinationTargetOrientationCondition>;
			template class fight::PropertyBool<DestinationTargetOrientationCondition>;
			template class fight::ConditionFactoryTemplate<DestinationTargetOrientationCondition>;
			template class fight::ConditionFactoryCasterTemplate<DestinationTargetOrientationCondition>;
			template class fight::PropertyBool<InsideReservedVolumeCondition>;
			template class fight::PropertyFloatConstRange<InsideReservedVolumeCondition>;
			template class fight::ConditionFactoryTemplate<InsideReservedVolumeCondition>;
			template class fight::ConditionFactoryCasterTemplate<InsideReservedVolumeCondition>;
			template class fight::PropertyBool<InBlastAreaCondition>;
			template class fight::ConditionFactoryTemplate<InBlastAreaCondition>;
			template class fight::ConditionFactoryCasterTemplate<InBlastAreaCondition>;
			template class fight::PropertyBool<StuckCondition>;
			template class fight::PropertyFloatConstRange<StuckCondition>;
			template class fight::ConditionFactoryTemplate<StuckCondition>;
			template class fight::ConditionFactoryCasterTemplate<StuckCondition>;
			template class fight::ConditionFactoryTemplate<HaveDestinationCondition>;
			template class fight::ConditionFactoryCasterTemplate<HaveDestinationCondition>;
			template class fight::PropertyBool<InHotZoneCondition>;
			template class fight::ConditionFactoryTemplate<InHotZoneCondition>;
			template class fight::ConditionFactoryCasterTemplate<InHotZoneCondition>;
			template class fight::ConditionFactoryTemplate<DestinationHaveArrivedCondition>;
			template class fight::ConditionFactoryCasterTemplate<DestinationHaveArrivedCondition>;
			template class fight::PropertyFloatConstRange<SetAvoidanceGapAnywhereTrack>;
			template class fight::PropertyBool<SetAvoidanceGapAnywhereTrack>;
			template class fight::TrackFactoryTemplate<SetAvoidanceGapAnywhereTrack>;
			template class fight::TrackFactoryCasterTemplate<SetAvoidanceGapAnywhereTrack>;
			template class fight::PropertyFloatConstRange<SpeedTrack>;
			template class fight::PropertyBool<SpeedTrack>;
			template class fight::TrackFactoryTemplate<SpeedTrack>;
			template class fight::TrackFactoryCasterTemplate<SpeedTrack>;
			template class fight::PropertyFloatConstRange<DestinationJumpToTrack>;
			template class fight::PropertyBool<DestinationJumpToTrack>;
			template class fight::TrackFactoryTemplate<DestinationJumpToTrack>;
			template class fight::TrackFactoryCasterTemplate<DestinationJumpToTrack>;
			template class fight::PropertyFloatConstRange<DestinationFlyToTrack>;
			template class fight::PropertyBool<DestinationFlyToTrack>;
			template class fight::PropertyVector<DestinationFlyToTrack>;
			template class fight::PropertyIntConstRange<DestinationFlyToTrack>;
			template class fight::TrackFactoryTemplate<DestinationFlyToTrack>;
			template class fight::TrackFactoryCasterTemplate<DestinationFlyToTrack>;
			template class fight::PropertyFloatConstRange<SetIntersectionPropertiesTrack>;
			template class fight::PropertyName<SetIntersectionPropertiesTrack>;
			template class fight::PropertyBool<SetIntersectionPropertiesTrack>;
			template class fight::TrackFactoryTemplate<SetIntersectionPropertiesTrack>;
			template class fight::TrackFactoryCasterTemplate<SetIntersectionPropertiesTrack>;
			template class fight::PropertyFloatConstRange<DisableStayOnNavmeshTrack>;
			template class fight::TrackFactoryTemplate<DisableStayOnNavmeshTrack>;
			template class fight::TrackFactoryCasterTemplate<DisableStayOnNavmeshTrack>;
			template class fight::PropertyFloatConstRange<TargetGoToTrack>;
			template class fight::PropertyEnumConstList<TargetGoToTrack>;
			template class fight::PropertyBool<TargetGoToTrack>;
			template class fight::TrackFactoryTemplate<TargetGoToTrack>;
			template class fight::TrackFactoryCasterTemplate<TargetGoToTrack>;
			template class fight::PropertyFloatConstRange<ForceMotionTrack>;
			template class fight::PropertyVector<ForceMotionTrack>;
			template class fight::PropertyBool<ForceMotionTrack>;
			template class fight::TrackFactoryTemplate<ForceMotionTrack>;
			template class fight::TrackFactoryCasterTemplate<ForceMotionTrack>;
			template class fight::PropertyFloatConstRange<ForceRecalculatePathTrack>;
			template class fight::TrackFactoryTemplate<ForceRecalculatePathTrack>;
			template class fight::TrackFactoryCasterTemplate<ForceRecalculatePathTrack>;
			template class fight::PropertyFloatConstRange<ReserveVolumeTrack>;
			template class fight::PropertyBool<ReserveVolumeTrack>;
			template class fight::TrackFactoryTemplate<ReserveVolumeTrack>;
			template class fight::TrackFactoryCasterTemplate<ReserveVolumeTrack>;
			template class fight::PropertyBranch<DestinationSetDeadBodyTrack>;
			template class fight::PropertyIntConstRange<DestinationSetDeadBodyTrack>;
			template class fight::PropertyConditionGroup<DestinationSetDeadBodyTrack>;
			template class fight::TrackFactoryTemplate<DestinationSetDeadBodyTrack>;
			template class fight::TrackFactoryCasterTemplate<DestinationSetDeadBodyTrack>;
			template class fight::PropertyFloatConstRange<StopTrack>;
			template class fight::TrackFactoryTemplate<StopTrack>;
			template class fight::TrackFactoryCasterTemplate<StopTrack>;
			template class fight::PropertyFloatConstRange<TempSpeedTrack>;
			template class fight::PropertyBool<TempSpeedTrack>;
			template class fight::TrackFactoryTemplate<TempSpeedTrack>;
			template class fight::TrackFactoryCasterTemplate<TempSpeedTrack>;
			template class fight::PropertyFloatConstRange<SetBrakeDistanceTrack>;
			template class fight::TrackFactoryTemplate<SetBrakeDistanceTrack>;
			template class fight::TrackFactoryCasterTemplate<SetBrakeDistanceTrack>;
			template class fight::PropertyFloatConstRange<AimTrack>;
			template class fight::PropertyEnumConstList<AimTrack>;
			template class fight::PropertyVector<AimTrack>;
			template class fight::PropertyBool<AimTrack>;
			template class fight::TrackFactoryTemplate<AimTrack>;
			template class fight::TrackFactoryCasterTemplate<AimTrack>;
			template class fight::PropertyFloatConstRange<DestinationGoToTrack>;
			template class fight::PropertyBool<DestinationGoToTrack>;
			template class fight::TrackFactoryTemplate<DestinationGoToTrack>;
			template class fight::TrackFactoryCasterTemplate<DestinationGoToTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10202370
// FUNCTION: ENGINE 0x10202570
// FUNCTION: ENGINE 0x10202620
// FUNCTION: ENGINE 0x102027B0
// FUNCTION: ENGINE 0x10202EA0
// FUNCTION: ENGINE 0x10202F50
// FUNCTION: ENGINE 0x10203190
// FUNCTION: ENGINE 0x10203830
// FUNCTION: ENGINE 0x10203A60
// FUNCTION: ENGINE 0x1023D5B0
// FUNCTION: ENGINE 0x1023D5E0
// FUNCTION: ENGINE 0x1023D610
// FUNCTION: ENGINE 0x1023D640
// FUNCTION: ENGINE 0x1023D670
// FUNCTION: ENGINE 0x1023D6A0
// FUNCTION: ENGINE 0x1023D6D0
// FUNCTION: ENGINE 0x1023D700
// FUNCTION: ENGINE 0x1023D730
// FUNCTION: ENGINE 0x1023D760
// FUNCTION: ENGINE 0x1023D790
// FUNCTION: ENGINE 0x1023D7C0
// FUNCTION: ENGINE 0x1023D7F0
// FUNCTION: ENGINE 0x1023D820
// FUNCTION: ENGINE 0x1023D8D0
// FUNCTION: ENGINE 0x1023D900
// FUNCTION: ENGINE 0x1023D930
// FUNCTION: ENGINE 0x1023D960
// FUNCTION: ENGINE 0x1023D990
// FUNCTION: ENGINE 0x1023D9C0
// FUNCTION: ENGINE 0x1023D9F0
// FUNCTION: ENGINE 0x1023DA20
// FUNCTION: ENGINE 0x1023DA50
// FUNCTION: ENGINE 0x1023DA80
// FUNCTION: ENGINE 0x1023DAB0
// FUNCTION: ENGINE 0x1023DAE0
// FUNCTION: ENGINE 0x1023DAF0
// FUNCTION: ENGINE 0x1023DB20
// FUNCTION: ENGINE 0x1023DB30
// FUNCTION: ENGINE 0x1023DB60
// FUNCTION: ENGINE 0x1023DB70
// FUNCTION: ENGINE 0x1023DBA0
// FUNCTION: ENGINE 0x1023DBB0
// FUNCTION: ENGINE 0x1023DBE0
// FUNCTION: ENGINE 0x1023DBF0
// FUNCTION: ENGINE 0x1023DC20
// FUNCTION: ENGINE 0x1023DC30
// FUNCTION: ENGINE 0x1023DC60
// FUNCTION: ENGINE 0x1023DC70
// FUNCTION: ENGINE 0x1023DCA0
// FUNCTION: ENGINE 0x1023DCB0
// FUNCTION: ENGINE 0x1023DCE0
// FUNCTION: ENGINE 0x1023DD10
// FUNCTION: ENGINE 0x1023DD30
// FUNCTION: ENGINE 0x1023DD80
// FUNCTION: ENGINE 0x1023DD90
// FUNCTION: ENGINE 0x1023DDC0
// FUNCTION: ENGINE 0x1023DDD0
// FUNCTION: ENGINE 0x1023DE00
// FUNCTION: ENGINE 0x1023DE30
// FUNCTION: ENGINE 0x1023DE50
// FUNCTION: ENGINE 0x1023DEA0
// FUNCTION: ENGINE 0x1023DEB0
// FUNCTION: ENGINE 0x1023DEE0
// FUNCTION: ENGINE 0x1023DEF0
// FUNCTION: ENGINE 0x1023DF20
// FUNCTION: ENGINE 0x1023DF30
// FUNCTION: ENGINE 0x1023DF60
// FUNCTION: ENGINE 0x1023DF70
// FUNCTION: ENGINE 0x1023DFA0
// FUNCTION: ENGINE 0x1023DFB0
// FUNCTION: ENGINE 0x1023DFE0
// FUNCTION: ENGINE 0x1023DFF0
// FUNCTION: ENGINE 0x1023E020
// FUNCTION: ENGINE 0x1023E030
// FUNCTION: ENGINE 0x1023E060
// FUNCTION: ENGINE 0x1023E070
// FUNCTION: ENGINE 0x1023E0A0
// FUNCTION: ENGINE 0x1023E0B0
// FUNCTION: ENGINE 0x1023E0E0
// FUNCTION: ENGINE 0x1023E0F0
// FUNCTION: ENGINE 0x1023E120
// FUNCTION: ENGINE 0x1023E130
// FUNCTION: ENGINE 0x1023E160
// FUNCTION: ENGINE 0x1023E170
// FUNCTION: ENGINE 0x1023E1A0
// FUNCTION: ENGINE 0x1023E1B0
// FUNCTION: ENGINE 0x1023E1E0
// FUNCTION: ENGINE 0x1023E1F0
// FUNCTION: ENGINE 0x1023E220
// FUNCTION: ENGINE 0x1023E230
// FUNCTION: ENGINE 0x1023E260
// FUNCTION: ENGINE 0x1023E270
// FUNCTION: ENGINE 0x1023E2A0
// FUNCTION: ENGINE 0x1023E2D0
// FUNCTION: ENGINE 0x1023E300
// FUNCTION: ENGINE 0x1023E320
// FUNCTION: ENGINE 0x1023E330
// FUNCTION: ENGINE 0x1023E370
// FUNCTION: ENGINE 0x1023E380
// FUNCTION: ENGINE 0x1023E3B0
// FUNCTION: ENGINE 0x1023E3D0
// FUNCTION: ENGINE 0x1023E3E0
// FUNCTION: ENGINE 0x1023E410
// FUNCTION: ENGINE 0x1023E440
// FUNCTION: ENGINE 0x1023E450
// FUNCTION: ENGINE 0x1023E480
// FUNCTION: ENGINE 0x1023E4A0
// FUNCTION: ENGINE 0x1023E4B0
// FUNCTION: ENGINE 0x1023E4F0
// FUNCTION: ENGINE 0x1023E500
// FUNCTION: ENGINE 0x1023E530
// FUNCTION: ENGINE 0x1023E550
// FUNCTION: ENGINE 0x1023E560
// FUNCTION: ENGINE 0x1023E590
// FUNCTION: ENGINE 0x1023E5C0
// FUNCTION: ENGINE 0x1023E5D0
// FUNCTION: ENGINE 0x1023E600
// FUNCTION: ENGINE 0x1023E620
// FUNCTION: ENGINE 0x1023E630
// FUNCTION: ENGINE 0x1023E670
// FUNCTION: ENGINE 0x1023E680
// FUNCTION: ENGINE 0x1023E6B0
// FUNCTION: ENGINE 0x1023E6D0
// FUNCTION: ENGINE 0x1023E6E0
// FUNCTION: ENGINE 0x1023E710
// FUNCTION: ENGINE 0x1023E740
// FUNCTION: ENGINE 0x1023E750
// FUNCTION: ENGINE 0x1023E780
// FUNCTION: ENGINE 0x1023E7A0
// FUNCTION: ENGINE 0x1023E7B0
// FUNCTION: ENGINE 0x1023E7E0
// FUNCTION: ENGINE 0x1023E800
// FUNCTION: ENGINE 0x1023E810
// FUNCTION: ENGINE 0x1023E840
// FUNCTION: ENGINE 0x1023E870
// FUNCTION: ENGINE 0x1023E880
// FUNCTION: ENGINE 0x1023E8B0
// FUNCTION: ENGINE 0x1023E8D0
// FUNCTION: ENGINE 0x1023E8E0
// FUNCTION: ENGINE 0x1023E910
// FUNCTION: ENGINE 0x1023E930
// FUNCTION: ENGINE 0x1023E940
// FUNCTION: ENGINE 0x1023E970
// FUNCTION: ENGINE 0x1023E9A0
// FUNCTION: ENGINE 0x1023E9B0
// FUNCTION: ENGINE 0x1023E9E0
// FUNCTION: ENGINE 0x1023EA00
// FUNCTION: ENGINE 0x1023EA10
// FUNCTION: ENGINE 0x1023EA40
// FUNCTION: ENGINE 0x1023EA70
// FUNCTION: ENGINE 0x1023EA80
// FUNCTION: ENGINE 0x1023EAB0
// FUNCTION: ENGINE 0x1023EAD0
// FUNCTION: ENGINE 0x1023EAE0
// FUNCTION: ENGINE 0x1023EB10
// FUNCTION: ENGINE 0x1023EB40
// FUNCTION: ENGINE 0x1023EB50
// FUNCTION: ENGINE 0x1023EB80
// FUNCTION: ENGINE 0x1023EBA0
// FUNCTION: ENGINE 0x1023EBB0
// FUNCTION: ENGINE 0x1023EBE0
// FUNCTION: ENGINE 0x1023EC10
// FUNCTION: ENGINE 0x1023EC20
// FUNCTION: ENGINE 0x1023EC50
// FUNCTION: ENGINE 0x1023EC70
// FUNCTION: ENGINE 0x1023EC80
// FUNCTION: ENGINE 0x1023ECB0
// FUNCTION: ENGINE 0x1023ECE0
// FUNCTION: ENGINE 0x1023ECF0
// FUNCTION: ENGINE 0x1023ED20
// FUNCTION: ENGINE 0x1023ED40
// FUNCTION: ENGINE 0x1023ED50
// FUNCTION: ENGINE 0x1023ED80
// FUNCTION: ENGINE 0x1023EDA0
// FUNCTION: ENGINE 0x1023EDB0
// FUNCTION: ENGINE 0x1023EDE0
// FUNCTION: ENGINE 0x1023EE00
// FUNCTION: ENGINE 0x1023EE10
// FUNCTION: ENGINE 0x1023EE40
// FUNCTION: ENGINE 0x1023EE70
// FUNCTION: ENGINE 0x1023EE80
// FUNCTION: ENGINE 0x1023EEB0
// FUNCTION: ENGINE 0x1023EED0
// FUNCTION: ENGINE 0x1023EEE0
// FUNCTION: ENGINE 0x1023EF10
// FUNCTION: ENGINE 0x1023EF40
// FUNCTION: ENGINE 0x1023EF50
// FUNCTION: ENGINE 0x1023EF80
// FUNCTION: ENGINE 0x1023EFB0
// FUNCTION: ENGINE 0x1023EFC0
// FUNCTION: ENGINE 0x1023F000
// FUNCTION: ENGINE 0x1023F010
// FUNCTION: ENGINE 0x1023F040
// FUNCTION: ENGINE 0x1023F060
// FUNCTION: ENGINE 0x1023F070
// FUNCTION: ENGINE 0x1023F0A0
// FUNCTION: ENGINE 0x1023F0C0
// FUNCTION: ENGINE 0x1023F0D0
// FUNCTION: ENGINE 0x1023F100
// FUNCTION: ENGINE 0x1023F130
// FUNCTION: ENGINE 0x1023F140
// FUNCTION: ENGINE 0x1023F170
// FUNCTION: ENGINE 0x1023F190
// FUNCTION: ENGINE 0x1023F1A0
// FUNCTION: ENGINE 0x1023F1D0
// FUNCTION: ENGINE 0x1023F1F0
// FUNCTION: ENGINE 0x1023F200
// FUNCTION: ENGINE 0x1023F230
// FUNCTION: ENGINE 0x1023F260
// FUNCTION: ENGINE 0x1023F270
// FUNCTION: ENGINE 0x1023F2A0
// FUNCTION: ENGINE 0x1023F2D0
// FUNCTION: ENGINE 0x1023F2E0
// FUNCTION: ENGINE 0x1023F310
// FUNCTION: ENGINE 0x1023F330
// FUNCTION: ENGINE 0x1023F340
// FUNCTION: ENGINE 0x1023F370
// FUNCTION: ENGINE 0x1023F390
// FUNCTION: ENGINE 0x1023F3C0
// FUNCTION: ENGINE 0x1023F3E0
// FUNCTION: ENGINE 0x1023F3F0
// FUNCTION: ENGINE 0x1023F420
// FUNCTION: ENGINE 0x1023F440
// FUNCTION: ENGINE 0x1023F470
// FUNCTION: ENGINE 0x1023F4A0
// FUNCTION: ENGINE 0x1023F4B0
// FUNCTION: ENGINE 0x1023F4E0
// FUNCTION: ENGINE 0x1023F510
// FUNCTION: ENGINE 0x1023F520
// FUNCTION: ENGINE 0x1023F550
// FUNCTION: ENGINE 0x1023F570
// FUNCTION: ENGINE 0x1023F580
// FUNCTION: ENGINE 0x1023F5B0
// FUNCTION: ENGINE 0x1023F5E0
// FUNCTION: ENGINE 0x1023F5F0
// FUNCTION: ENGINE 0x1023F620
// FUNCTION: ENGINE 0x1023F650
// FUNCTION: ENGINE 0x1023F660
// FUNCTION: ENGINE 0x1023F6A0
// FUNCTION: ENGINE 0x1023F6B0
// FUNCTION: ENGINE 0x1023F6E0
// FUNCTION: ENGINE 0x1023F700
// FUNCTION: ENGINE 0x1023F710
// FUNCTION: ENGINE 0x1023F740
// FUNCTION: ENGINE 0x1023F760
// FUNCTION: ENGINE 0x1023F770
// FUNCTION: ENGINE 0x1023F7A0
// FUNCTION: ENGINE 0x1023F7C0
// FUNCTION: ENGINE 0x1023F7D0
// FUNCTION: ENGINE 0x1023F800
// FUNCTION: ENGINE 0x1023F830
// FUNCTION: ENGINE 0x1023F840
// FUNCTION: ENGINE 0x1023F870
// FUNCTION: ENGINE 0x1023F890
// FUNCTION: ENGINE 0x10242200
// FUNCTION: ENGINE 0x10242230
// FUNCTION: ENGINE 0x10242250
// FUNCTION: ENGINE 0x10242280
// FUNCTION: ENGINE 0x102422A0
// FUNCTION: ENGINE 0x102422D0
// FUNCTION: ENGINE 0x102422F0
// FUNCTION: ENGINE 0x10242320
// FUNCTION: ENGINE 0x10242340
// FUNCTION: ENGINE 0x10242370
// FUNCTION: ENGINE 0x10242390
// FUNCTION: ENGINE 0x102423C0
// FUNCTION: ENGINE 0x102423E0
// FUNCTION: ENGINE 0x10242410
// FUNCTION: ENGINE 0x10242430
// FUNCTION: ENGINE 0x10242460
// FUNCTION: ENGINE 0x10242480
// FUNCTION: ENGINE 0x102424B0
// FUNCTION: ENGINE 0x102424D0
// FUNCTION: ENGINE 0x10242500
// FUNCTION: ENGINE 0x10242520
// FUNCTION: ENGINE 0x10242550
// FUNCTION: ENGINE 0x10242570
// FUNCTION: ENGINE 0x102425A0
// FUNCTION: ENGINE 0x102425C0
// FUNCTION: ENGINE 0x102425F0
// FUNCTION: ENGINE 0x10242610
// FUNCTION: ENGINE 0x10242640
// FUNCTION: ENGINE 0x10242660
// FUNCTION: ENGINE 0x10242690
// FUNCTION: ENGINE 0x102426B0
// FUNCTION: ENGINE 0x102426E0
// FUNCTION: ENGINE 0x10242700
// FUNCTION: ENGINE 0x10242730
// FUNCTION: ENGINE 0x10242750
// FUNCTION: ENGINE 0x10242780
// FUNCTION: ENGINE 0x102427A0
// FUNCTION: ENGINE 0x102427D0
// FUNCTION: ENGINE 0x102427F0
// FUNCTION: ENGINE 0x10242820
// FUNCTION: ENGINE 0x10242840
// FUNCTION: ENGINE 0x10242870
// FUNCTION: ENGINE 0x10242890
// FUNCTION: ENGINE 0x102428C0
// FUNCTION: ENGINE 0x102428E0
// FUNCTION: ENGINE 0x10242910
// FUNCTION: ENGINE 0x10242930
// FUNCTION: ENGINE 0x10242960
// FUNCTION: ENGINE 0x10242AD0
// FUNCTION: ENGINE 0x10242B20
// FUNCTION: ENGINE 0x10242B70
// FUNCTION: ENGINE 0x10242BC0
// FUNCTION: ENGINE 0x10242C10
// FUNCTION: ENGINE 0x10242C60
// FUNCTION: ENGINE 0x10242CB0
// FUNCTION: ENGINE 0x10242D00
// FUNCTION: ENGINE 0x10242D50
// FUNCTION: ENGINE 0x10242DA0
// FUNCTION: ENGINE 0x10242DF0
// FUNCTION: ENGINE 0x10242E40
// FUNCTION: ENGINE 0x10242E90
// FUNCTION: ENGINE 0x10242EE0
// FUNCTION: ENGINE 0x10242F30
// FUNCTION: ENGINE 0x10242F80
// FUNCTION: ENGINE 0x10242FD0
// FUNCTION: ENGINE 0x10243020
// FUNCTION: ENGINE 0x10243070
// FUNCTION: ENGINE 0x102430C0
// FUNCTION: ENGINE 0x10243110
// FUNCTION: ENGINE 0x10243160
// FUNCTION: ENGINE 0x102431B0
// FUNCTION: ENGINE 0x10243200
// FUNCTION: ENGINE 0x10243230
// FUNCTION: ENGINE 0x10243250
