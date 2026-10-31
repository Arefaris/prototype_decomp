// Fight items of the motion group: FallTrack (unit 0x1015E4B0 - 0x1015F0E0; the assert path of the unit's actions names code/proto/fightitems/motion/motion_fall.cpp).
#include "code/proto/fightitems/motion/motion_fall.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gFallTrackProperties;  // 0x11254518

			// FUNCTION: ENGINE 0x1015E4B0
			bool FallTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E4D0
			bool FallTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E4F0
			bool FallTrack::SetTurningVelocityMin(float newValue)
			{
				turningVelocityMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E510
			bool FallTrack::SetTurningAccelerationMin(float newValue)
			{
				turningAccelerationMin = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E530
			bool FallTrack::SetTurningVelocityMinForwardSpeedCap(float newValue)
			{
				turningVelocityMinForwardSpeedCap = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E550
			bool FallTrack::SetTurningVelocityMax(float newValue)
			{
				turningVelocityMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E570
			bool FallTrack::SetTurningAccelerationMax(float newValue)
			{
				turningAccelerationMax = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E590
			bool FallTrack::SetTurningVelocityMaxForwardSpeedCap(float newValue)
			{
				turningVelocityMaxForwardSpeedCap = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E5B0
			bool FallTrack::SetPreserveMomentum(int newValue)
			{
				preserveMomentum = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E5C0
			bool FallTrack::SetInitialVelocity(const math::Vector& newValue)
			{
				initialVelocity.x = newValue.x;
				initialVelocity.y = newValue.y;
				initialVelocity.z = newValue.z;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E5E0
			bool FallTrack::SetGravity(float newValue)
			{
				gravity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E600
			bool FallTrack::SetMaxVelocity(float newValue)
			{
				maxVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E620
			bool FallTrack::SetGravityDecreaseRate(float newValue)
			{
				gravityDecreaseRate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E640
			bool FallTrack::SetMaxVelocityXZ(float newValue)
			{
				maxVelocityXZ = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E660
			bool FallTrack::SetMaxVelocityUp(float newValue)
			{
				maxVelocityUp = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E680
			bool FallTrack::SetLimitTurning(bool newValue)
			{
				limitTurning = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E690
			bool FallTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E6A0
			bool FallTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E6C0
			bool FallTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015E6E0
			fight::Property* FallTrack::GetProperty(int index)
			{
				return gFallTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1015E700
			void FallTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFallTrackProperties);
			}

			// FUNCTION: ENGINE 0x1015E710
			FallTrack::FallTrack() : initialVelocity(0.0f, 0.0f, 0.0f), blendInTime(0.0f), blendOutTime(0.0f), gravity(9.8f), gravityDecreaseRate(0.0f), maxVelocity(-1.0f), maxVelocityUp(-1.0f), maxVelocityXZ(-1.0f), timeBegin(0.0f), timeEnd(-1.0f), turningAccelerationMax(0.0f), turningAccelerationMin(0.0f), turningVelocityMax(0.0f), turningVelocityMaxForwardSpeedCap(0.0f), turningVelocityMin(0.0f), turningVelocityMinForwardSpeedCap(0.0f), priority(-5), preserveMomentum(0), limitTurning(true)
			{
			}

			// FUNCTION: ENGINE 0x1015E7D0
			float FallTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1015E7E0
			float FallTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1015E7F0
			FallTrack::~FallTrack()
			{
			}

			// FUNCTION: ENGINE 0x1015EB10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FallTrack::RegisterProperties()
			{
				if (gFallTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FallTrack>("timeBegin", &FallTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FallTrack>("timeEnd", &FallTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FallTrack>("turningVelocityMin", &FallTrack::SetTurningVelocityMin);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<FallTrack>("turningAccelerationMin", &FallTrack::SetTurningAccelerationMin);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<FallTrack>("turningVelocityMinForwardSpeedCap", &FallTrack::SetTurningVelocityMinForwardSpeedCap);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<FallTrack>("turningVelocityMax", &FallTrack::SetTurningVelocityMax);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<FallTrack>("turningAccelerationMax", &FallTrack::SetTurningAccelerationMax);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<FallTrack>("turningVelocityMaxForwardSpeedCap", &FallTrack::SetTurningVelocityMaxForwardSpeedCap);
					properties[7] = property;
					property = new fight::PropertyBitfieldConstList<FallTrack>("preserveMomentum", gFallTrackPreserveMomentumTable, gFallTrackPreserveMomentumCount, &FallTrack::SetPreserveMomentum);
					properties[8] = property;
					property = new fight::PropertyVector<FallTrack>("initialVelocity", &FallTrack::SetInitialVelocity);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<FallTrack>("gravity", &FallTrack::SetGravity);
					properties[10] = property;
					property = new fight::PropertyFloatConstRange<FallTrack>("maxVelocity", &FallTrack::SetMaxVelocity);
					properties[11] = property;
					property = new fight::PropertyFloatConstRange<FallTrack>("gravityDecreaseRate", &FallTrack::SetGravityDecreaseRate);
					properties[12] = property;
					property = new fight::PropertyFloatConstRange<FallTrack>("maxVelocityXZ", &FallTrack::SetMaxVelocityXZ);
					properties[13] = property;
					property = new fight::PropertyFloatConstRange<FallTrack>("maxVelocityUp", &FallTrack::SetMaxVelocityUp);
					properties[14] = property;
					property = new fight::PropertyBool<FallTrack>("limitTurning", &FallTrack::SetLimitTurning);
					properties[15] = property;
					property = new fight::PropertyIntConstRange<FallTrack>("priority", &FallTrack::SetPriority);
					properties[16] = property;
					property = new fight::PropertyFloatConstRange<FallTrack>("blendInTime", &FallTrack::SetBlendInTime);
					properties[17] = property;
					property = new fight::PropertyFloatConstRange<FallTrack>("blendOutTime", &FallTrack::SetBlendOutTime);
					properties[18] = property;
					fight::RegisterPropertyList(properties, &gFallTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1015EAE0
			fight::TrackFactory* CreateFallTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FallTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1015F010
			void RegisterFallTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FallTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// FUNCTION: ENGINE 0x100BC320
			FallAction::FallAction(FallTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), target(newTarget), driver(0), link(newTrack), unknown30(0.0f), unknown34(0.0f, 0.0f, 0.0f), unknown40(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x100BC200
			FallAction::~FallAction()
			{
				engine::ReleaseDriverCopy2(&driver);
			}

			// FUNCTION: ENGINE 0x100BD230
			fight::Action* FallTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new FallAction(this, handle);
			}

			// FUNCTION: ENGINE 0x100BC240
			void FallAction::Slot6()
			{
				engine::GameObject* object = target.Get();
				if (object != 0)
				{
					choreo::Puppet* puppet = engine::GetPuppet(object);
					if (puppet != 0)
					{
						puppet->RemoveDriver(driver, false);
						engine::ReleaseDriverCopy2(&driver);
					}
				}
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<FallTrack>;
			template class fight::PropertyBitfieldConstList<FallTrack>;
			template class fight::PropertyVector<FallTrack>;
			template class fight::PropertyBool<FallTrack>;
			template class fight::PropertyIntConstRange<FallTrack>;
			template class fight::TrackFactoryTemplate<FallTrack>;
			template class fight::TrackFactoryCasterTemplate<FallTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1015E800
// FUNCTION: ENGINE 0x1015E830
// FUNCTION: ENGINE 0x1015E840
// FUNCTION: ENGINE 0x1015E870
// FUNCTION: ENGINE 0x1015E8A0
// FUNCTION: ENGINE 0x1015E8D0
// FUNCTION: ENGINE 0x1015E8E0
// FUNCTION: ENGINE 0x1015E920
// FUNCTION: ENGINE 0x1015E930
// FUNCTION: ENGINE 0x1015E950
// FUNCTION: ENGINE 0x1015E960
// FUNCTION: ENGINE 0x1015E9C0
// FUNCTION: ENGINE 0x1015E9F0
// FUNCTION: ENGINE 0x1015EA10
// FUNCTION: ENGINE 0x1015EA20
// FUNCTION: ENGINE 0x1015EA50
// FUNCTION: ENGINE 0x1015EA70
// FUNCTION: ENGINE 0x1015EA80
// FUNCTION: ENGINE 0x1015EAB0
// FUNCTION: ENGINE 0x1015EAD0
// FUNCTION: ENGINE 0x1015F040
// FUNCTION: ENGINE 0x1015F070
// FUNCTION: ENGINE 0x1015F090
// FUNCTION: ENGINE 0x100BC160
// FUNCTION: ENGINE 0x100BC190
// FUNCTION: ENGINE 0x100BC3B0
