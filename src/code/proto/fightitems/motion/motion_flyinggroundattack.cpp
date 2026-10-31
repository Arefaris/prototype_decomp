// Fight items of the motion group: FlyingGroundAttackTrack (unit 0x10160940 - 0x101610C0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_flyinggroundattack.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gFlyingGroundAttackTrackProperties;  // 0x1125453C

			// FUNCTION: ENGINE 0x10160940
			bool FlyingGroundAttackTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10160960
			bool FlyingGroundAttackTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10160980
			bool FlyingGroundAttackTrack::SetVelocityXZMin(float newValue)
			{
				velocityXZMin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101609A0
			bool FlyingGroundAttackTrack::SetVelocityXZMax(float newValue)
			{
				velocityXZMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101609C0
			bool FlyingGroundAttackTrack::SetAccelerationXZ(float newValue)
			{
				accelerationXZ = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101609E0
			bool FlyingGroundAttackTrack::SetGravity(float newValue)
			{
				gravity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10160A00
			bool FlyingGroundAttackTrack::SetTurningVelocity(float newValue)
			{
				turningVelocity = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10160A20
			bool FlyingGroundAttackTrack::SetTargetOffset(float newValue)
			{
				targetOffset = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10160A40
			bool FlyingGroundAttackTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10160A50
			bool FlyingGroundAttackTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10160A70
			bool FlyingGroundAttackTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10160A90
			fight::Property* FlyingGroundAttackTrack::GetProperty(int index)
			{
				return gFlyingGroundAttackTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10160AB0
			void FlyingGroundAttackTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFlyingGroundAttackTrackProperties);
			}

			// FUNCTION: ENGINE 0x10160AC0
			FlyingGroundAttackTrack::FlyingGroundAttackTrack() : accelerationXZ(1e+02f), blendInTime(0.0f), blendOutTime(0.0f), gravity(1e+02f), targetOffset(0.0f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocity(1.5707964f), velocityXZMax(5e+01f), velocityXZMin(0.0f), priority(-5)
			{
			}

			// FUNCTION: ENGINE 0x10160B50
			float FlyingGroundAttackTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10160B60
			float FlyingGroundAttackTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10160B70
			FlyingGroundAttackTrack::~FlyingGroundAttackTrack()
			{
			}

			// FUNCTION: ENGINE 0x10160CF0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FlyingGroundAttackTrack::RegisterProperties()
			{
				if (gFlyingGroundAttackTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FlyingGroundAttackTrack>("timeBegin", &FlyingGroundAttackTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FlyingGroundAttackTrack>("timeEnd", &FlyingGroundAttackTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FlyingGroundAttackTrack>("velocityXZMin", &FlyingGroundAttackTrack::SetVelocityXZMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<FlyingGroundAttackTrack>("velocityXZMax", &FlyingGroundAttackTrack::SetVelocityXZMax);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<FlyingGroundAttackTrack>("accelerationXZ", &FlyingGroundAttackTrack::SetAccelerationXZ);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<FlyingGroundAttackTrack>("gravity", &FlyingGroundAttackTrack::SetGravity);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<FlyingGroundAttackTrack>("turningVelocity", &FlyingGroundAttackTrack::SetTurningVelocity);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<FlyingGroundAttackTrack>("targetOffset", &FlyingGroundAttackTrack::SetTargetOffset);
					properties[7] = property;
					property = new fight::PropertyIntConstRange<FlyingGroundAttackTrack>("priority", &FlyingGroundAttackTrack::SetPriority);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<FlyingGroundAttackTrack>("blendInTime", &FlyingGroundAttackTrack::SetBlendInTime);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<FlyingGroundAttackTrack>("blendOutTime", &FlyingGroundAttackTrack::SetBlendOutTime);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gFlyingGroundAttackTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10160CC0
			fight::TrackFactory* CreateFlyingGroundAttackTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FlyingGroundAttackTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10160FF0
			void RegisterFlyingGroundAttackTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FlyingGroundAttackTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x100BF5B0
			FlyingGroundAttackAction::FlyingGroundAttackAction(FlyingGroundAttackTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), driver(0), unknown34(0.0f), unknown38(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x100BF4A0
			FlyingGroundAttackAction::~FlyingGroundAttackAction()
			{
				engine::ReleaseDriverCopy2((choreo::Driver**)&driver);
			}

			// FUNCTION: ENGINE 0x100BFE10
			fight::Action* FlyingGroundAttackTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new FlyingGroundAttackAction(this, handle);
			}

			// ---- actions end
			// FUNCTION: ENGINE 0x100BF4E0
			void FlyingGroundAttackAction::Slot6()
			{
				engine::GameObject* object = target.Get();
				if (object != 0)
				{
					choreo::Puppet* puppet = engine::GetPuppet(object);
					if (puppet != 0)
					{
						puppet->RemoveDriver(driver, false);
					}
				}
			}

			template class fight::PropertyFloatConstRange<FlyingGroundAttackTrack>;
			template class fight::PropertyIntConstRange<FlyingGroundAttackTrack>;
			template class fight::TrackFactoryTemplate<FlyingGroundAttackTrack>;
			template class fight::TrackFactoryCasterTemplate<FlyingGroundAttackTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x100BF400
// FUNCTION: ENGINE 0x100BF430
// FUNCTION: ENGINE 0x100BF630
