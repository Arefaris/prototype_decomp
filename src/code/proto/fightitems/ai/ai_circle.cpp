// Fight items of the ai group: CirclePatrolTrack, IntersectionCirclePatrolTrack, CircleStrafeTrack (unit 0x1021CD90 - 0x1021E550; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_circle.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gCirclePatrolTrackProperties;  // 0x11255830

			// FUNCTION: ENGINE 0x1021CD90
			bool CirclePatrolTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021CDB0
			bool CirclePatrolTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021CDD0
			bool CirclePatrolTrack::SetHeightMin(float newValue)
			{
				heightMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021CDF0
			bool CirclePatrolTrack::SetHeightMax(float newValue)
			{
				heightMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021CE10
			bool CirclePatrolTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021CE30
			bool CirclePatrolTrack::SetFreeRadius(float newValue)
			{
				freeRadius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021CE50
			bool CirclePatrolTrack::SetAvoidRadius(float newValue)
			{
				avoidRadius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021CE70
			bool CirclePatrolTrack::SetAvoidCost(float newValue)
			{
				avoidCost = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021CE90
			bool CirclePatrolTrack::SetTries(int newValue)
			{
				tries = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021CEA0
			bool CirclePatrolTrack::SetMaxSpeed(float newValue)
			{
				maxSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021CEC0
			bool CirclePatrolTrack::SetMinDistance(float newValue)
			{
				minDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021CEE0
			bool CirclePatrolTrack::SetMinAngle(float newValue)
			{
				minAngle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1021CF00
			bool CirclePatrolTrack::SetMaxPathHeightDiffCurrent(float newValue)
			{
				maxPathHeightDiffCurrent = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021D1F0
			fight::Property* CirclePatrolTrack::GetProperty(int index)
			{
				return gCirclePatrolTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1021D210
			void CirclePatrolTrack::ClearProperties()
			{
				fight::FreePropertyList(&gCirclePatrolTrackProperties);
			}

			// FUNCTION: ENGINE 0x1021D220
			CirclePatrolTrack::CirclePatrolTrack() : avoidCost(1e+01f), avoidRadius(1e+01f), freeRadius(1e+01f), heightMax(1e+01f), heightMin(8.0f), maxPathHeightDiffCurrent(2e+02f), maxSpeed(1.0f), minAngle(1.5707964f), minDistance(5.0f), radius(1e+01f), timeBegin(0.0f), timeEnd(-1.0f), tries(10)
			{
			}

			// FUNCTION: ENGINE 0x1021D2E0
			float CirclePatrolTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1021D2F0
			float CirclePatrolTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1021D300
			CirclePatrolTrack::~CirclePatrolTrack()
			{
			}

			// FUNCTION: ENGINE 0x1021D920
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CirclePatrolTrack::RegisterProperties()
			{
				if (gCirclePatrolTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CirclePatrolTrack>("timeBegin", &CirclePatrolTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<CirclePatrolTrack>("timeEnd", &CirclePatrolTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<CirclePatrolTrack>("heightMin", &CirclePatrolTrack::SetHeightMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<CirclePatrolTrack>("heightMax", &CirclePatrolTrack::SetHeightMax);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<CirclePatrolTrack>("radius", &CirclePatrolTrack::SetRadius);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<CirclePatrolTrack>("freeRadius", &CirclePatrolTrack::SetFreeRadius);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<CirclePatrolTrack>("avoidRadius", &CirclePatrolTrack::SetAvoidRadius);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<CirclePatrolTrack>("avoidCost", &CirclePatrolTrack::SetAvoidCost);
					properties[7] = property;
					property = new fight::PropertyIntConstRange<CirclePatrolTrack>("tries", &CirclePatrolTrack::SetTries);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<CirclePatrolTrack>("maxSpeed", &CirclePatrolTrack::SetMaxSpeed);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<CirclePatrolTrack>("minDistance", &CirclePatrolTrack::SetMinDistance);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<CirclePatrolTrack>("minAngle", &CirclePatrolTrack::SetMinAngle);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<CirclePatrolTrack>("maxPathHeightDiffCurrent", &CirclePatrolTrack::SetMaxPathHeightDiffCurrent);
					properties[12] = property;
					fight::RegisterPropertyList(properties, &gCirclePatrolTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1021D890
			fight::TrackFactory* CreateCirclePatrolTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<CirclePatrolTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1021E2E0
			void RegisterCirclePatrolTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<CirclePatrolTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gIntersectionCirclePatrolTrackProperties;  // 0x11255834

			// FUNCTION: ENGINE 0x1021CF20
			bool IntersectionCirclePatrolTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021CF40
			bool IntersectionCirclePatrolTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021CF60
			bool IntersectionCirclePatrolTrack::SetHeightMin(float newValue)
			{
				heightMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021CF80
			bool IntersectionCirclePatrolTrack::SetHeightMinFromTarget(float newValue)
			{
				heightMinFromTarget = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021CFA0
			bool IntersectionCirclePatrolTrack::SetMinDistance(float newValue)
			{
				minDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021CFC0
			bool IntersectionCirclePatrolTrack::SetRadius(float newValue)
			{
				radius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021CFE0
			bool IntersectionCirclePatrolTrack::SetFreeRadiusPath(float newValue)
			{
				freeRadiusPath = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021D000
			bool IntersectionCirclePatrolTrack::SetFreeRadius(float newValue)
			{
				freeRadius = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021D310
			fight::Property* IntersectionCirclePatrolTrack::GetProperty(int index)
			{
				return gIntersectionCirclePatrolTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1021D330
			void IntersectionCirclePatrolTrack::ClearProperties()
			{
				fight::FreePropertyList(&gIntersectionCirclePatrolTrackProperties);
			}

			// FUNCTION: ENGINE 0x1021D340
			IntersectionCirclePatrolTrack::IntersectionCirclePatrolTrack() : freeRadius(1e+01f), freeRadiusPath(1e+01f), heightMin(8.0f), heightMinFromTarget(1e+01f), minDistance(5.0f), radius(1e+01f), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x1021D3C0
			float IntersectionCirclePatrolTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1021D3D0
			float IntersectionCirclePatrolTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1021D3E0
			IntersectionCirclePatrolTrack::~IntersectionCirclePatrolTrack()
			{
			}

			// FUNCTION: ENGINE 0x1021DCA0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void IntersectionCirclePatrolTrack::RegisterProperties()
			{
				if (gIntersectionCirclePatrolTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<IntersectionCirclePatrolTrack>("timeBegin", &IntersectionCirclePatrolTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<IntersectionCirclePatrolTrack>("timeEnd", &IntersectionCirclePatrolTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<IntersectionCirclePatrolTrack>("heightMin", &IntersectionCirclePatrolTrack::SetHeightMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<IntersectionCirclePatrolTrack>("heightMinFromTarget", &IntersectionCirclePatrolTrack::SetHeightMinFromTarget);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<IntersectionCirclePatrolTrack>("minDistance", &IntersectionCirclePatrolTrack::SetMinDistance);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<IntersectionCirclePatrolTrack>("radius", &IntersectionCirclePatrolTrack::SetRadius);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<IntersectionCirclePatrolTrack>("freeRadiusPath", &IntersectionCirclePatrolTrack::SetFreeRadiusPath);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<IntersectionCirclePatrolTrack>("freeRadius", &IntersectionCirclePatrolTrack::SetFreeRadius);
					properties[7] = property;
					fight::RegisterPropertyList(properties, &gIntersectionCirclePatrolTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1021D8C0
			fight::TrackFactory* CreateIntersectionCirclePatrolTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<IntersectionCirclePatrolTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1021E310
			void RegisterIntersectionCirclePatrolTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<IntersectionCirclePatrolTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gCircleStrafeTrackProperties;  // 0x11255838

			// FUNCTION: ENGINE 0x1021D020
			bool CircleStrafeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021D040
			bool CircleStrafeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021D060
			bool CircleStrafeTrack::SetDistanceMin(float newValue)
			{
				distanceMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021D080
			bool CircleStrafeTrack::SetDistanceMax(float newValue)
			{
				distanceMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021D0A0
			bool CircleStrafeTrack::SetHeightMin(float newValue)
			{
				heightMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021D0C0
			bool CircleStrafeTrack::SetHeightMax(float newValue)
			{
				heightMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021D0E0
			bool CircleStrafeTrack::SetSafeHeight(float newValue)
			{
				safeHeight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021D100
			bool CircleStrafeTrack::SetMinSpeed(float newValue)
			{
				minSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021D120
			bool CircleStrafeTrack::SetMaxSpeed(float newValue)
			{
				maxSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021D140
			bool CircleStrafeTrack::SetShootingDistance(float newValue)
			{
				shootingDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021D160
			bool CircleStrafeTrack::SetUseMissiles(bool newValue)
			{
				useMissiles = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021D170
			bool CircleStrafeTrack::SetMinFireTime(float newValue)
			{
				minFireTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021D190
			bool CircleStrafeTrack::SetMaxFireTime(float newValue)
			{
				maxFireTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021D1B0
			bool CircleStrafeTrack::SetMinWaitTime(float newValue)
			{
				minWaitTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021D1D0
			bool CircleStrafeTrack::SetMaxWaitTime(float newValue)
			{
				maxWaitTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021D3F0
			fight::Property* CircleStrafeTrack::GetProperty(int index)
			{
				return gCircleStrafeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1021D410
			void CircleStrafeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gCircleStrafeTrackProperties);
			}

			// FUNCTION: ENGINE 0x1021D420
			CircleStrafeTrack::CircleStrafeTrack() : distanceMax(2e+01f), distanceMin(1e+01f), heightMax(1e+01f), heightMin(8.0f), maxFireTime(6.0f), maxSpeed(1.0f), maxWaitTime(3.0f), minFireTime(5.0f), minSpeed(0.8f), minWaitTime(2.0f), safeHeight(3.0f), shootingDistance(2e+01f), timeBegin(0.0f), timeEnd(-1.0f), useMissiles(false)
			{
			}

			// FUNCTION: ENGINE 0x1021D500
			float CircleStrafeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1021D510
			float CircleStrafeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1021D520
			CircleStrafeTrack::~CircleStrafeTrack()
			{
			}

			// FUNCTION: ENGINE 0x1021DEF0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CircleStrafeTrack::RegisterProperties()
			{
				if (gCircleStrafeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CircleStrafeTrack>("timeBegin", &CircleStrafeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<CircleStrafeTrack>("timeEnd", &CircleStrafeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<CircleStrafeTrack>("distanceMin", &CircleStrafeTrack::SetDistanceMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<CircleStrafeTrack>("distanceMax", &CircleStrafeTrack::SetDistanceMax);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<CircleStrafeTrack>("heightMin", &CircleStrafeTrack::SetHeightMin);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<CircleStrafeTrack>("heightMax", &CircleStrafeTrack::SetHeightMax);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<CircleStrafeTrack>("safeHeight", &CircleStrafeTrack::SetSafeHeight);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<CircleStrafeTrack>("minSpeed", &CircleStrafeTrack::SetMinSpeed);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<CircleStrafeTrack>("maxSpeed", &CircleStrafeTrack::SetMaxSpeed);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<CircleStrafeTrack>("shootingDistance", &CircleStrafeTrack::SetShootingDistance);
					properties[9] = property;
					property = new fight::PropertyBool<CircleStrafeTrack>("useMissiles", &CircleStrafeTrack::SetUseMissiles);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<CircleStrafeTrack>("minFireTime", &CircleStrafeTrack::SetMinFireTime);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<CircleStrafeTrack>("maxFireTime", &CircleStrafeTrack::SetMaxFireTime);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<CircleStrafeTrack>("minWaitTime", &CircleStrafeTrack::SetMinWaitTime);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<CircleStrafeTrack>("maxWaitTime", &CircleStrafeTrack::SetMaxWaitTime);
					properties[14] = property;
					fight::RegisterPropertyList(properties, &gCircleStrafeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1021D8F0
			fight::TrackFactory* CreateCircleStrafeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<CircleStrafeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1021E340
			void RegisterCircleStrafeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<CircleStrafeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x101E1450
			CirclePatrolAction::CirclePatrolAction(CirclePatrolTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), unknown2C(0), unknown30(0.0f), unknown34(false)
			{
			}

			// FUNCTION: ENGINE 0x101E0EF0
			CirclePatrolAction::~CirclePatrolAction()
			{
			}

			// FUNCTION: ENGINE 0x101E1CA0
			fight::Action* CirclePatrolTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new CirclePatrolAction(this, handle);
			}

			// FUNCTION: ENGINE 0x101E1330
			// EQUIVALENT: scheduling: the engine's instructions in another order (best 93.5 %)
			CircleStrafeAction::CircleStrafeAction(CircleStrafeTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), unknown2C(0.0f), unknown30(0.0f), unknown34(0.0f), unknown38(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x101E0EA0
			CircleStrafeAction::~CircleStrafeAction()
			{
			}

			// FUNCTION: ENGINE 0x101E02F0
			void CircleStrafeAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101E1760
			fight::Action* CircleStrafeTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new CircleStrafeAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<CirclePatrolTrack>;
			template class fight::PropertyIntConstRange<CirclePatrolTrack>;
			template class fight::TrackFactoryTemplate<CirclePatrolTrack>;
			template class fight::TrackFactoryCasterTemplate<CirclePatrolTrack>;
			template class fight::PropertyFloatConstRange<IntersectionCirclePatrolTrack>;
			template class fight::TrackFactoryTemplate<IntersectionCirclePatrolTrack>;
			template class fight::TrackFactoryCasterTemplate<IntersectionCirclePatrolTrack>;
			template class fight::PropertyFloatConstRange<CircleStrafeTrack>;
			template class fight::PropertyBool<CircleStrafeTrack>;
			template class fight::TrackFactoryTemplate<CircleStrafeTrack>;
			template class fight::TrackFactoryCasterTemplate<CircleStrafeTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1021D530
// FUNCTION: ENGINE 0x1021D560
// FUNCTION: ENGINE 0x1021D590
// FUNCTION: ENGINE 0x1021D5C0
// FUNCTION: ENGINE 0x1021D5D0
// FUNCTION: ENGINE 0x1021D600
// FUNCTION: ENGINE 0x1021D610
// FUNCTION: ENGINE 0x1021D640
// FUNCTION: ENGINE 0x1021D650
// FUNCTION: ENGINE 0x1021D680
// FUNCTION: ENGINE 0x1021D6B0
// FUNCTION: ENGINE 0x1021D6E0
// FUNCTION: ENGINE 0x1021D6F0
// FUNCTION: ENGINE 0x1021D720
// FUNCTION: ENGINE 0x1021D740
// FUNCTION: ENGINE 0x1021D750
// FUNCTION: ENGINE 0x1021D780
// FUNCTION: ENGINE 0x1021D7B0
// FUNCTION: ENGINE 0x1021D7C0
// FUNCTION: ENGINE 0x1021D7F0
// FUNCTION: ENGINE 0x1021D820
// FUNCTION: ENGINE 0x1021D830
// FUNCTION: ENGINE 0x1021D860
// FUNCTION: ENGINE 0x1021D880
// FUNCTION: ENGINE 0x1021E370
// FUNCTION: ENGINE 0x1021E3A0
// FUNCTION: ENGINE 0x1021E3C0
// FUNCTION: ENGINE 0x1021E3F0
// FUNCTION: ENGINE 0x1021E410
// FUNCTION: ENGINE 0x1021E440
// FUNCTION: ENGINE 0x1021E460
// FUNCTION: ENGINE 0x1021E4B0
// FUNCTION: ENGINE 0x1021E500
