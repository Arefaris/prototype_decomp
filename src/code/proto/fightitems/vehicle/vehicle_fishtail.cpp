// Fight items of the vehicle group: FishTailTrack, EBrakeTrack (unit 0x1027B0F0 - 0x1027BF20; no assert path, the file name is a guess).
#include "code/proto/fightitems/vehicle/vehicle_fishtail.h"

namespace proto
{
	namespace fightitems
	{
		namespace vehicle
		{
			fight::Property** gFishTailTrackProperties;  // 0x112561A0

			// FUNCTION: ENGINE 0x1027B0F0
			bool FishTailTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027B110
			bool FishTailTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027B130
			bool FishTailTrack::SetMinTimeDelay(float newValue)
			{
				minTimeDelay = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027B150
			bool FishTailTrack::SetMaxTimeDelay(float newValue)
			{
				maxTimeDelay = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027B170
			bool FishTailTrack::SetTurning(float newValue)
			{
				turning = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027B190
			bool FishTailTrack::SetDesiredVelocity(float newValue)
			{
				desiredVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027B1B0
			bool FishTailTrack::SetAccelration(float newValue)
			{
				accelration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027B1D0
			bool FishTailTrack::SetBraking(float newValue)
			{
				braking = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027B1F0
			bool FishTailTrack::SetSkidSeverity(float newValue)
			{
				skidSeverity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027B210
			bool FishTailTrack::SetFishTailSeverity(float newValue)
			{
				fishTailSeverity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027B230
			fight::BranchHolder* FishTailTrack::SetMyBranch()
			{
				return &myBranch;
			}

			// FUNCTION: ENGINE 0x1027B350
			fight::Property* FishTailTrack::GetProperty(int index)
			{
				return gFishTailTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1027B370
			void FishTailTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFishTailTrackProperties);
			}

			// FUNCTION: ENGINE 0x1027B380
			FishTailTrack::FishTailTrack() : myBranch(0), accelration(1.0f), braking(1.0f), desiredVelocity(1.0f), fishTailSeverity(0.3f), maxTimeDelay(-1.0f), minTimeDelay(-1.0f), skidSeverity(0.7f), timeBegin(0.0f), timeEnd(-1.0f), turning(1.0f)
			{
			}

			// FUNCTION: ENGINE 0x1027B410
			float FishTailTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1027B420
			float FishTailTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1027B430
			FishTailTrack::~FishTailTrack()
			{
			}

			// FUNCTION: ENGINE 0x1027B800
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FishTailTrack::RegisterProperties()
			{
				if (gFishTailTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FishTailTrack>("timeBegin", &FishTailTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FishTailTrack>("timeEnd", &FishTailTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FishTailTrack>("minTimeDelay", &FishTailTrack::SetMinTimeDelay);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<FishTailTrack>("maxTimeDelay", &FishTailTrack::SetMaxTimeDelay);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<FishTailTrack>("turning", &FishTailTrack::SetTurning);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<FishTailTrack>("desiredVelocity", &FishTailTrack::SetDesiredVelocity);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<FishTailTrack>("accelration", &FishTailTrack::SetAccelration);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<FishTailTrack>("braking", &FishTailTrack::SetBraking);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<FishTailTrack>("skidSeverity", &FishTailTrack::SetSkidSeverity);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<FishTailTrack>("fishTailSeverity", &FishTailTrack::SetFishTailSeverity);
					properties[9] = property;
					property = new fight::PropertyBranch<FishTailTrack>("myBranch", &FishTailTrack::SetMyBranch);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gFishTailTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1027B7A0
			fight::TrackFactory* CreateFishTailTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FishTailTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1027BD80
			void RegisterFishTailTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FishTailTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gEBrakeTrackProperties;  // 0x112561A4

			// FUNCTION: ENGINE 0x1027B240
			bool EBrakeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027B260
			bool EBrakeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027B280
			bool EBrakeTrack::SetMinTimeDelay(float newValue)
			{
				minTimeDelay = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027B2A0
			bool EBrakeTrack::SetMaxTimeDelay(float newValue)
			{
				maxTimeDelay = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027B2C0
			bool EBrakeTrack::SetTurningSpeed(float newValue)
			{
				turningSpeed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027B2E0
			bool EBrakeTrack::SetBraking(float newValue)
			{
				braking = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027B300
			bool EBrakeTrack::SetTurningAmount(float newValue)
			{
				turningAmount = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027B320
			bool EBrakeTrack::SetSkidSeverity(float newValue)
			{
				skidSeverity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1027B340
			fight::BranchHolder* EBrakeTrack::SetMyBranch()
			{
				return &myBranch;
			}

			// FUNCTION: ENGINE 0x1027B450
			fight::Property* EBrakeTrack::GetProperty(int index)
			{
				return gEBrakeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1027B470
			void EBrakeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gEBrakeTrackProperties);
			}

			// FUNCTION: ENGINE 0x1027B480
			EBrakeTrack::EBrakeTrack() : myBranch(0), braking(1.0f), maxTimeDelay(-1.0f), minTimeDelay(-1.0f), skidSeverity(0.7f), timeBegin(0.0f), timeEnd(-1.0f), turningAmount(0.5f), turningSpeed(1.0f)
			{
			}

			// FUNCTION: ENGINE 0x1027B500
			float EBrakeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1027B510
			float EBrakeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1027B520
			EBrakeTrack::~EBrakeTrack()
			{
			}

			// FUNCTION: ENGINE 0x1027BB00
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void EBrakeTrack::RegisterProperties()
			{
				if (gEBrakeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<EBrakeTrack>("timeBegin", &EBrakeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<EBrakeTrack>("timeEnd", &EBrakeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<EBrakeTrack>("minTimeDelay", &EBrakeTrack::SetMinTimeDelay);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<EBrakeTrack>("maxTimeDelay", &EBrakeTrack::SetMaxTimeDelay);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<EBrakeTrack>("turningSpeed", &EBrakeTrack::SetTurningSpeed);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<EBrakeTrack>("braking", &EBrakeTrack::SetBraking);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<EBrakeTrack>("turningAmount", &EBrakeTrack::SetTurningAmount);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<EBrakeTrack>("skidSeverity", &EBrakeTrack::SetSkidSeverity);
					properties[7] = property;
					property = new fight::PropertyBranch<EBrakeTrack>("myBranch", &EBrakeTrack::SetMyBranch);
					properties[8] = property;
					fight::RegisterPropertyList(properties, &gEBrakeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1027B7D0
			fight::TrackFactory* CreateEBrakeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<EBrakeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1027BDB0
			void RegisterEBrakeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<EBrakeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x10278020
			FishTailAction::FishTailAction(FishTailTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), unknown2C(math::kZeroVector), unknown38(math::kZeroVector), unknown44(0), unknown48(0), unknown4C(0), unknown50(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x102776C0
			FishTailAction::~FishTailAction()
			{
			}

			// FUNCTION: ENGINE 0x102774F0
			void FishTailAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x10278970
			fight::Action* FishTailTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new FishTailAction(this, handle);
			}

			// FUNCTION: ENGINE 0x102777D0
			EBrakeAction::EBrakeAction(EBrakeTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), unknown2C(math::kZeroVector), unknown38(1.0f), unknown3C(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x10277670
			EBrakeAction::~EBrakeAction()
			{
			}

			// FUNCTION: ENGINE 0x102774E0
			void EBrakeAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x10278920
			fight::Action* EBrakeTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new EBrakeAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<FishTailTrack>;
			template class fight::PropertyBranch<FishTailTrack>;
			template class fight::TrackFactoryTemplate<FishTailTrack>;
			template class fight::TrackFactoryCasterTemplate<FishTailTrack>;
			template class fight::PropertyFloatConstRange<EBrakeTrack>;
			template class fight::PropertyBranch<EBrakeTrack>;
			template class fight::TrackFactoryTemplate<EBrakeTrack>;
			template class fight::TrackFactoryCasterTemplate<EBrakeTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102765B0
// FUNCTION: ENGINE 0x102767E0
// FUNCTION: ENGINE 0x10277550
// FUNCTION: ENGINE 0x102775A0
// FUNCTION: ENGINE 0x10277890
// FUNCTION: ENGINE 0x10278100
// FUNCTION: ENGINE 0x1027B540
// FUNCTION: ENGINE 0x1027B570
// FUNCTION: ENGINE 0x1027B5A0
// FUNCTION: ENGINE 0x1027B5B0
// FUNCTION: ENGINE 0x1027B5E0
// FUNCTION: ENGINE 0x1027B5F0
// FUNCTION: ENGINE 0x1027B620
// FUNCTION: ENGINE 0x1027B650
// FUNCTION: ENGINE 0x1027B680
// FUNCTION: ENGINE 0x1027B690
// FUNCTION: ENGINE 0x1027B6C0
// FUNCTION: ENGINE 0x1027B6E0
// FUNCTION: ENGINE 0x1027B710
// FUNCTION: ENGINE 0x1027B740
// FUNCTION: ENGINE 0x1027B750
// FUNCTION: ENGINE 0x1027B780
// FUNCTION: ENGINE 0x1027BDE0
// FUNCTION: ENGINE 0x1027BE10
// FUNCTION: ENGINE 0x1027BE30
// FUNCTION: ENGINE 0x1027BE60
// FUNCTION: ENGINE 0x1027BE80
// FUNCTION: ENGINE 0x1027BED0
