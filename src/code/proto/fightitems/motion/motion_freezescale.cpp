// Fight items of the motion group: FreezeScaleTrack (unit 0x10161980 - 0x10161F50; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_freezescale.h"
#include "code/proto/fightitems/motion/motioncommon.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gFreezeScaleTrackProperties;  // 0x11254544

			// FUNCTION: ENGINE 0x10161980
			bool FreezeScaleTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101619A0
			bool FreezeScaleTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10161A40
			bool FreezeScaleTrack::SetPartition(const fight::Name& newValue)
			{
				partition = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101619C0
			bool FreezeScaleTrack::SetPriority(int newValue)
			{
				priority = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101619D0
			bool FreezeScaleTrack::SetBlendInTime(float newValue)
			{
				blendInTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101619F0
			bool FreezeScaleTrack::SetBlendOutTime(float newValue)
			{
				blendOutTime = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10161A10
			fight::Property* FreezeScaleTrack::GetProperty(int index)
			{
				return gFreezeScaleTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10161A30
			void FreezeScaleTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFreezeScaleTrackProperties);
			}

			// FUNCTION: ENGINE 0x10161A60
			FreezeScaleTrack::FreezeScaleTrack() : blendInTime(0.0f), blendOutTime(0.0f), timeBegin(0.0f), timeEnd(-1.0f), priority(-1)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10161AC0
			float FreezeScaleTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10161AD0
			float FreezeScaleTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10161AE0
			FreezeScaleTrack::~FreezeScaleTrack()
			{
			}

			// FUNCTION: ENGINE 0x10161CE0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FreezeScaleTrack::RegisterProperties()
			{
				if (gFreezeScaleTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FreezeScaleTrack>("timeBegin", &FreezeScaleTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FreezeScaleTrack>("timeEnd", &FreezeScaleTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyName<FreezeScaleTrack>("partition", &FreezeScaleTrack::SetPartition);
					properties[2] = property;
					property = new fight::PropertyIntConstRange<FreezeScaleTrack>("priority", &FreezeScaleTrack::SetPriority);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<FreezeScaleTrack>("blendInTime", &FreezeScaleTrack::SetBlendInTime);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<FreezeScaleTrack>("blendOutTime", &FreezeScaleTrack::SetBlendOutTime);
					properties[5] = property;
					fight::RegisterPropertyList(properties, &gFreezeScaleTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10161C30
			fight::TrackFactory* CreateFreezeScaleTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FreezeScaleTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10161C60
			void RegisterFreezeScaleTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FreezeScaleTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x100C05D0
			void ReleaseDriverFreezescale(choreo::Driver*& driver)
			{
				if (driver != 0)
				{
					driver->Release();
					driver = 0;
				}
			}

			// FUNCTION: ENGINE 0x100C05F0
			void SafeReleaseRefFreezescale(core::IRefCount*& object)
			{
				if (object != 0)
				{
					object->Release();
					object = 0;
				}
			}

			// FUNCTION: ENGINE 0x100C0610
			void AssignRefCountedFreezescale(core::IRefCount*& slot, core::IRefCount* value)
			{
				if (value != 0)
				{
					value->AddRef();
				}
				if (slot != 0)
				{
					slot->Release();
				}
				slot = value;
			}

			// FUNCTION: ENGINE 0x100C0650
			void AssignDriverFreezescale(choreo::Driver*& slot, choreo::Driver* value)
			{
				if (value != 0)
				{
					value->AddRef();
				}
				if (slot != 0)
				{
					slot->Release();
				}
				slot = value;
			}

			// FUNCTION: ENGINE 0x100C0860
			FreezeScaleAction::FreezeScaleAction(FreezeScaleTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), driver(0), pose(0)
			{
			}

			// FUNCTION: ENGINE 0x100C0720
			FreezeScaleAction::~FreezeScaleAction()
			{
				ReleaseDriverFreezescale(driver);
				SafeReleaseRefFreezescale(pose);
			}

			// FUNCTION: ENGINE 0x100C0900
			bool FreezeScaleAction::Slot5(int arg, float value)
			{
				if (link.Get() == 0)
				{
					return false;
				}
				engine::GameObject* object = target.Get();
				if (object == 0)
				{
					return false;
				}
				choreo::Puppet* puppet = engine::GetPuppet(object);
				if (puppet == 0)
				{
					return false;
				}
				pure3d::Skeleton* skeleton = puppet->GetSkeleton();
				core::IRefCount*& slot = pose;
				pure3d::Pose* newPose = puppet->mPoseObject->CreateInstance(3);
				AssignRefCountedFreezescale(slot, newPose);
				AssignDriverFreezescale(driver, new choreo::PoseDriver(skeleton, static_cast<pure3d::Pose*>(slot), 0x10));
				static_cast<choreo::PartitionDriver*>(driver)->SetPartitionByName(link.Get()->partition);
				puppet->SetDriver(driver, choreo::gMinusOne, link.Get()->priority, 1.0f, link.Get()->blendInTime, link.Get()->blendOutTime, choreo::gMinusOne);
				return true;
			}
// FUNCTION: ENGINE 0x100C0770
			void FreezeScaleAction::Slot6()
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
				ReleaseDriverFreezescale(driver);
				SafeReleaseRefFreezescale(pose);
			}


			// FUNCTION: ENGINE 0x100C0A20
			fight::Action* FreezeScaleTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new FreezeScaleAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<FreezeScaleTrack>;
			template class fight::PropertyName<FreezeScaleTrack>;
			template class fight::PropertyIntConstRange<FreezeScaleTrack>;
			template class fight::TrackFactoryTemplate<FreezeScaleTrack>;
			template class fight::TrackFactoryCasterTemplate<FreezeScaleTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x100C0680
// FUNCTION: ENGINE 0x100C06A0
// FUNCTION: ENGINE 0x100C06B0
// FUNCTION: ENGINE 0x100C08D0
// FUNCTION: ENGINE 0x10161AF0
// FUNCTION: ENGINE 0x10161B00
// FUNCTION: ENGINE 0x10161B30
// FUNCTION: ENGINE 0x10161B60
// FUNCTION: ENGINE 0x10161B90
// FUNCTION: ENGINE 0x10161BC0
// FUNCTION: ENGINE 0x10161BD0
// FUNCTION: ENGINE 0x10161C00
// FUNCTION: ENGINE 0x10161C20
// FUNCTION: ENGINE 0x10161C90
// FUNCTION: ENGINE 0x10161CC0
// FUNCTION: ENGINE 0x10161EB0
// FUNCTION: ENGINE 0x10161EE0
// FUNCTION: ENGINE 0x10161F00
