// Fight items of the motion group: FlyingDashTrack (unit 0x101601F0 - 0x10160940; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_flyingdash.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gFlyingDashTrackProperties;  // 0x11254538

			// FUNCTION: ENGINE 0x101601F0
			bool FlyingDashTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10160210
			bool FlyingDashTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10160230
			bool FlyingDashTrack::SetVelocityAdd(float newValue)
			{
				velocityAdd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10160250
			bool FlyingDashTrack::SetVelocityMax(float newValue)
			{
				velocityMax = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10160270
			bool FlyingDashTrack::SetPreserveYVelocity(bool newValue)
			{
				preserveYVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10160300
			bool FlyingDashTrack::SetDashToTargetGrabbableClass(const fight::Name& newValue)
			{
				dashToTargetGrabbableClass = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10160280
			bool FlyingDashTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10160290
			bool FlyingDashTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101602B0
			bool FlyingDashTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101602D0
			fight::Property* FlyingDashTrack::GetProperty(int index)
			{
				return gFlyingDashTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101602F0
			void FlyingDashTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFlyingDashTrackProperties);
			}

			// FUNCTION: ENGINE 0x10160320
			FlyingDashTrack::FlyingDashTrack() : blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEnd(-1.0f), velocityAdd(2e+01f), velocityMax(5e+01f), priority(-5), preserveYVelocity(false)
			{
			}

			// FUNCTION: ENGINE 0x101603A0
			float FlyingDashTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101603B0
			float FlyingDashTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101603C0
			FlyingDashTrack::~FlyingDashTrack()
			{
			}

			// FUNCTION: ENGINE 0x10160620
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FlyingDashTrack::RegisterProperties()
			{
				if (gFlyingDashTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FlyingDashTrack>("timeBegin", &FlyingDashTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FlyingDashTrack>("timeEnd", &FlyingDashTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FlyingDashTrack>("velocityAdd", &FlyingDashTrack::SetVelocityAdd);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<FlyingDashTrack>("velocityMax", &FlyingDashTrack::SetVelocityMax);
					properties[3] = property;
					property = new fight::PropertyBool<FlyingDashTrack>("preserveYVelocity", &FlyingDashTrack::SetPreserveYVelocity);
					properties[4] = property;
					property = new fight::PropertyName<FlyingDashTrack>("dashToTargetGrabbableClass", &FlyingDashTrack::SetDashToTargetGrabbableClass);
					properties[5] = property;
					property = new fight::PropertyIntConstRange<FlyingDashTrack>("priority", &FlyingDashTrack::SetPriority);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<FlyingDashTrack>("blendInTime", &FlyingDashTrack::SetBlendInTime);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<FlyingDashTrack>("blendOutTime", &FlyingDashTrack::SetBlendOutTime);
					properties[8] = property;
					fight::RegisterPropertyList(properties, &gFlyingDashTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10160570
			fight::TrackFactory* CreateFlyingDashTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FlyingDashTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101605A0
			void RegisterFlyingDashTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FlyingDashTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x100BEC20
			FlyingDashAction::FlyingDashAction(FlyingDashTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), driver(0), unknown30(0.0f, 0.0f, 0.0f), unknown3C(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x100BEA50
			FlyingDashAction::~FlyingDashAction()
			{
				engine::ReleaseDriverCopy2((choreo::Driver**)&driver);
			}

			// FUNCTION: ENGINE 0x100BF310
			fight::Action* FlyingDashTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new FlyingDashAction(this, handle);
			}

			// ---- actions end
			// FUNCTION: ENGINE 0x100BEA90
			bool FlyingDashAction::Slot7(int arg, float value)
			{
				if (arg != 0)
				{
					return true;
				}
				if (driver == 0)
				{
					return false;
				}
				engine::GameObject* object = target.Get();
				if (object == 0)
				{
					return false;
				}
				math::Quaternion rotation;
				choreo::InverseRotation(&rotation, object->transform->value);
				choreo::DeltaTransform* delta = &driver->mDelta;
				delta->SetVelocity(unknown30, rotation);
				delta->SetOrientation(unknown3C, rotation);
				return true;
			}

			// FUNCTION: ENGINE 0x100BEB40
			void FlyingDashAction::Slot6()
			{
				if (driver != 0)
				{
					engine::GameObject* object = target.Get();
					if (object != 0)
					{
						choreo::Puppet* puppet = engine::GetPuppet(object);
						if (puppet != 0)
						{
							puppet->RemoveDriver(driver, false);
							engine::ReleaseDriverCopy2((choreo::Driver**)&driver);
						}
					}
				}
			}

			template class fight::PropertyFloatConstRange<FlyingDashTrack>;
			template class fight::PropertyBool<FlyingDashTrack>;
			template class fight::PropertyName<FlyingDashTrack>;
			template class fight::PropertyIntConstRange<FlyingDashTrack>;
			template class fight::TrackFactoryTemplate<FlyingDashTrack>;
			template class fight::TrackFactoryCasterTemplate<FlyingDashTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101603D0
// FUNCTION: ENGINE 0x101603E0
// FUNCTION: ENGINE 0x10160410
// FUNCTION: ENGINE 0x10160440
// FUNCTION: ENGINE 0x10160470
// FUNCTION: ENGINE 0x101604A0
// FUNCTION: ENGINE 0x101604B0
// FUNCTION: ENGINE 0x101604E0
// FUNCTION: ENGINE 0x10160500
// FUNCTION: ENGINE 0x10160510
// FUNCTION: ENGINE 0x10160540
// FUNCTION: ENGINE 0x10160560
// FUNCTION: ENGINE 0x101605D0
// FUNCTION: ENGINE 0x10160600
// FUNCTION: ENGINE 0x101608A0
// FUNCTION: ENGINE 0x101608D0
// FUNCTION: ENGINE 0x101608F0
// FUNCTION: ENGINE 0x100BE9B0
// FUNCTION: ENGINE 0x100BE9E0
// FUNCTION: ENGINE 0x100BECA0
