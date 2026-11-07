// Fight items of the motion group: OrientationDesiredCondition, OrientTrack, WorldOrientTrack (unit 0x10198800 - 0x101998F0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_orient.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gOrientationDesiredConditionProperties;  // 0x112548B8

			// FUNCTION: ENGINE 0x10198800
			bool OrientationDesiredCondition::SetCompare(int newValue)
			{
				compare = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10198810
			bool OrientationDesiredCondition::SetAngle(float newValue)
			{
				angle = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10198A00
			fight::Property* OrientationDesiredCondition::GetProperty(int index)
			{
				return gOrientationDesiredConditionProperties[index];
			}

			// FUNCTION: ENGINE 0x10198A20
			void OrientationDesiredCondition::ClearProperties()
			{
				fight::FreePropertyList(&gOrientationDesiredConditionProperties);
			}

			// FUNCTION: ENGINE 0x10198A30
			OrientationDesiredCondition::OrientationDesiredCondition() : fight::Condition(0), angle(0.0f), compare(4)
			{
			}

			// FUNCTION: ENGINE 0x10198A60
			OrientationDesiredCondition::~OrientationDesiredCondition()
			{
			}

			// FUNCTION: ENGINE 0x10199100
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void OrientationDesiredCondition::RegisterProperties()
			{
				if (gOrientationDesiredConditionProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyEnumConstList<OrientationDesiredCondition>("compare", gDistanceFromWaterSurfaceConditionCompareTable, gDistanceFromWaterSurfaceConditionCompareCount, &OrientationDesiredCondition::SetCompare);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<OrientationDesiredCondition>("angle", &OrientationDesiredCondition::SetAngle);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gOrientationDesiredConditionProperties);
				}
			}

			// FUNCTION: ENGINE 0x10199070
			fight::ConditionFactory* CreateOrientationDesiredConditionFactory(const char* name)
			{
				fight::ConditionFactoryCasterTemplate<OrientationDesiredCondition> caster;
				return fight::FindConditionFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10199680
			void RegisterOrientationDesiredConditionFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::ConditionFactoryCasterTemplate<OrientationDesiredCondition> caster;
				registry->AddFactory(fight::FindConditionFactory(name, &caster));
			}

			fight::Property** gOrientTrackProperties;  // 0x112548BC

			// FUNCTION: ENGINE 0x10198830
			bool OrientTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10198850
			bool OrientTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10198870
			bool OrientTrack::SetTurningVelocity(float newValue)
			{
				turningVelocity = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10198890
			bool OrientTrack::SetTurningAcceleration(float newValue)
			{
				turningAcceleration = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101988B0
			bool OrientTrack::SetOffset(float newValue)
			{
				offset = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101988D0
			bool OrientTrack::SetFixedInput(bool newValue)
			{
				fixedInput = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101988E0
			bool OrientTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101988F0
			bool OrientTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10198910
			bool OrientTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10198A70
			fight::Property* OrientTrack::GetProperty(int index)
			{
				return gOrientTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10198A90
			void OrientTrack::ClearProperties()
			{
				fight::FreePropertyList(&gOrientTrackProperties);
			}

			// FUNCTION: ENGINE 0x10198AA0
			OrientTrack::OrientTrack() : blendInTime(0.0f), blendOutTime(0.0f), offset(0.0f), timeBegin(0.0f), timeEnd(-1.0f), turningAcceleration(0.0f), turningVelocity(0.0f), priority(-5), fixedInput(false)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10198B10
			float OrientTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10198B20
			float OrientTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10198B30
			OrientTrack::~OrientTrack()
			{
			}

			// FUNCTION: ENGINE 0x101991F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void OrientTrack::RegisterProperties()
			{
				if (gOrientTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<OrientTrack>("timeBegin", &OrientTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<OrientTrack>("timeEnd", &OrientTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<OrientTrack>("turningVelocity", &OrientTrack::SetTurningVelocity);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<OrientTrack>("turningAcceleration", &OrientTrack::SetTurningAcceleration);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<OrientTrack>("offset", &OrientTrack::SetOffset);
					properties[4] = property;
					property = new fight::PropertyBool<OrientTrack>("fixedInput", &OrientTrack::SetFixedInput);
					properties[5] = property;
					property = new fight::PropertyIntConstRange<OrientTrack>("priority", &OrientTrack::SetPriority);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<OrientTrack>("blendInTime", &OrientTrack::SetBlendInTime);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<OrientTrack>("blendOutTime", &OrientTrack::SetBlendOutTime);
					properties[8] = property;
					fight::RegisterPropertyList(properties, &gOrientTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101990A0
			fight::TrackFactory* CreateOrientTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<OrientTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101996B0
			void RegisterOrientTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<OrientTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gWorldOrientTrackProperties;  // 0x112548C0

			// FUNCTION: ENGINE 0x10198930
			bool WorldOrientTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10198950
			bool WorldOrientTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10198970
			bool WorldOrientTrack::SetYaw(float newValue)
			{
				yaw = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x10198990
			bool WorldOrientTrack::SetTurningVelocity(float newValue)
			{
				turningVelocity = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x101989B0
			bool WorldOrientTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101989C0
			bool WorldOrientTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101989E0
			bool WorldOrientTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10198B40
			fight::Property* WorldOrientTrack::GetProperty(int index)
			{
				return gWorldOrientTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10198B60
			void WorldOrientTrack::ClearProperties()
			{
				fight::FreePropertyList(&gWorldOrientTrackProperties);
			}

			// FUNCTION: ENGINE 0x10198B70
			WorldOrientTrack::WorldOrientTrack() : blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEnd(-1.0f), turningVelocity(0.0f), yaw(0.0f), priority(-5)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10198BD0
			float WorldOrientTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10198BE0
			float WorldOrientTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10198BF0
			WorldOrientTrack::~WorldOrientTrack()
			{
			}

			// FUNCTION: ENGINE 0x10199470
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void WorldOrientTrack::RegisterProperties()
			{
				if (gWorldOrientTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<WorldOrientTrack>("timeBegin", &WorldOrientTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<WorldOrientTrack>("timeEnd", &WorldOrientTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<WorldOrientTrack>("yaw", &WorldOrientTrack::SetYaw);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<WorldOrientTrack>("turningVelocity", &WorldOrientTrack::SetTurningVelocity);
					properties[3] = property;
					property = new fight::PropertyIntConstRange<WorldOrientTrack>("priority", &WorldOrientTrack::SetPriority);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<WorldOrientTrack>("blendInTime", &WorldOrientTrack::SetBlendInTime);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<WorldOrientTrack>("blendOutTime", &WorldOrientTrack::SetBlendOutTime);
					properties[6] = property;
					fight::RegisterPropertyList(properties, &gWorldOrientTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101990D0
			fight::TrackFactory* CreateWorldOrientTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<WorldOrientTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101996E0
			void RegisterWorldOrientTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<WorldOrientTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x100FF660
			OrientAction::OrientAction(OrientTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), target(newTarget), driver(0), link(newTrack), unknown34(0.0f), unknown38(false)
			{
			}

			// FUNCTION: ENGINE 0x100FF3F0
			OrientAction::~OrientAction()
			{
				engine::ReleaseDriverCopy2(&driver);
			}

			// FUNCTION: ENGINE 0x100FFF70
			fight::Action* OrientTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new OrientAction(this, handle);
			}

			// FUNCTION: ENGINE 0x100FFB70
			WorldOrientAction::WorldOrientAction(WorldOrientTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), target(newTarget), driver(0), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x100FF4D0
			WorldOrientAction::~WorldOrientAction()
			{
				engine::ReleaseDriverCopy2(&driver);
			}

			// FUNCTION: ENGINE 0x100FFFC0
			fight::Action* WorldOrientTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new WorldOrientAction(this, handle);
			}

			// FUNCTION: ENGINE 0x100FF430
			void OrientAction::Slot6()
			{
				engine::GameObject* object = target.Get();
				if (object != 0)
				{
					choreo::Puppet* puppet = engine::GetPuppet(object);
					if (puppet != 0)
					{
						puppet->RemoveDriver(driver, false);
					}
					if (driver != 0)
					{
						((choreo::RootDriver*)driver)->mDelta.Reset();
					}
					engine::ReleaseDriverCopy2(&driver);
				}
			}

			// FUNCTION: ENGINE 0x100FF510
			void WorldOrientAction::Slot6()
			{
				engine::GameObject* object = target.Get();
				if (object != 0)
				{
					choreo::Puppet* puppet = engine::GetPuppet(object);
					if (puppet != 0)
					{
						puppet->RemoveDriver(driver, false);
					}
					engine::ReleaseDriverCopy2(&driver);
				}
			}

			// ---- actions end
			template class fight::PropertyEnumConstList<OrientationDesiredCondition>;
			template class fight::PropertyFloatConstRange<OrientationDesiredCondition>;
			template class fight::ConditionFactoryTemplate<OrientationDesiredCondition>;
			template class fight::ConditionFactoryCasterTemplate<OrientationDesiredCondition>;
			template class fight::PropertyFloatConstRange<OrientTrack>;
			template class fight::PropertyBool<OrientTrack>;
			template class fight::PropertyIntConstRange<OrientTrack>;
			template class fight::TrackFactoryTemplate<OrientTrack>;
			template class fight::TrackFactoryCasterTemplate<OrientTrack>;
			template class fight::PropertyFloatConstRange<WorldOrientTrack>;
			template class fight::PropertyIntConstRange<WorldOrientTrack>;
			template class fight::TrackFactoryTemplate<WorldOrientTrack>;
			template class fight::TrackFactoryCasterTemplate<WorldOrientTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x100FF1D0
// FUNCTION: ENGINE 0x100FF1F0
// FUNCTION: ENGINE 0x100FF220
// FUNCTION: ENGINE 0x100FF280
// FUNCTION: ENGINE 0x100FF6E0
// FUNCTION: ENGINE 0x100FFBE0
// FUNCTION: ENGINE 0x10198C00
// FUNCTION: ENGINE 0x10198C30
// FUNCTION: ENGINE 0x10198C60
// FUNCTION: ENGINE 0x10198C90
// FUNCTION: ENGINE 0x10198CA0
// FUNCTION: ENGINE 0x10198CD0
// FUNCTION: ENGINE 0x10198CE0
// FUNCTION: ENGINE 0x10198D10
// FUNCTION: ENGINE 0x10198D20
// FUNCTION: ENGINE 0x10198D50
// FUNCTION: ENGINE 0x10198D90
// FUNCTION: ENGINE 0x10198DA0
// FUNCTION: ENGINE 0x10198DD0
// FUNCTION: ENGINE 0x10198DF0
// FUNCTION: ENGINE 0x10198E00
// FUNCTION: ENGINE 0x10198E30
// FUNCTION: ENGINE 0x10198E60
// FUNCTION: ENGINE 0x10198E70
// FUNCTION: ENGINE 0x10198EA0
// FUNCTION: ENGINE 0x10198ED0
// FUNCTION: ENGINE 0x10198EE0
// FUNCTION: ENGINE 0x10198F10
// FUNCTION: ENGINE 0x10198F30
// FUNCTION: ENGINE 0x10198F40
// FUNCTION: ENGINE 0x10198F70
// FUNCTION: ENGINE 0x10198F90
// FUNCTION: ENGINE 0x10198FA0
// FUNCTION: ENGINE 0x10198FD0
// FUNCTION: ENGINE 0x10199000
// FUNCTION: ENGINE 0x10199010
// FUNCTION: ENGINE 0x10199040
// FUNCTION: ENGINE 0x10199060
// FUNCTION: ENGINE 0x10199710
// FUNCTION: ENGINE 0x10199740
// FUNCTION: ENGINE 0x10199760
// FUNCTION: ENGINE 0x10199790
// FUNCTION: ENGINE 0x101997B0
// FUNCTION: ENGINE 0x101997E0
// FUNCTION: ENGINE 0x10199800
// FUNCTION: ENGINE 0x10199850
// FUNCTION: ENGINE 0x101998A0
