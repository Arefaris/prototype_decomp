// Fight items of the ai group: TankRamTrack (unit 0x10246860 - 0x10246F80; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_tankram.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gTankRamTrackProperties;  // 0x11255B54

			// FUNCTION: ENGINE 0x10246860
			bool TankRamTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10246880
			bool TankRamTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102468A0
			bool TankRamTrack::SetTimePreparingForward(float newValue)
			{
				timePreparingForward = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102468C0
			bool TankRamTrack::SetTimePreparingBackward(float newValue)
			{
				timePreparingBackward = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102468E0
			bool TankRamTrack::SetMaxTurningSpeedFactor(float newValue)
			{
				maxTurningSpeedFactor = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10246900
			bool TankRamTrack::SetRollingScaleFactor(float newValue)
			{
				rollingScaleFactor = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10246920
			bool TankRamTrack::SetRollingScaleBackwardsFactor(float newValue)
			{
				rollingScaleBackwardsFactor = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10246940
			bool TankRamTrack::SetRollingScaleFactorPush(float newValue)
			{
				rollingScaleFactorPush = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10246960
			bool TankRamTrack::SetRollingScaleBackwardsFactorPush(float newValue)
			{
				rollingScaleBackwardsFactorPush = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10246980
			bool TankRamTrack::SetToleranceForward(float newValue)
			{
				toleranceForward = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102469A0
			bool TankRamTrack::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102469C0
			fight::Property* TankRamTrack::GetProperty(int index)
			{
				return gTankRamTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x102469E0
			void TankRamTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTankRamTrackProperties);
			}

			// FUNCTION: ENGINE 0x102469F0
			TankRamTrack::TankRamTrack() : maxTurningSpeedFactor(1.0f), rollingScaleBackwardsFactor(1.0f), rollingScaleBackwardsFactorPush(1.0f), rollingScaleFactor(1.0f), rollingScaleFactorPush(1.0f), speed(1.0f), timeBegin(0.0f), timeEnd(0.0f), timePreparingBackward(0.0f), timePreparingForward(0.0f), toleranceForward(0.8f)
			{
			}

			// FUNCTION: ENGINE 0x10246A70
			float TankRamTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10246A80
			float TankRamTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10246A90
			TankRamTrack::~TankRamTrack()
			{
			}

			// FUNCTION: ENGINE 0x10246BB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TankRamTrack::RegisterProperties()
			{
				if (gTankRamTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("timeBegin", &TankRamTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("timeEnd", &TankRamTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("timePreparingForward", &TankRamTrack::SetTimePreparingForward);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("timePreparingBackward", &TankRamTrack::SetTimePreparingBackward);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("maxTurningSpeedFactor", &TankRamTrack::SetMaxTurningSpeedFactor);
					properties[4] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("rollingScaleFactor", &TankRamTrack::SetRollingScaleFactor);
					properties[5] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("rollingScaleBackwardsFactor", &TankRamTrack::SetRollingScaleBackwardsFactor);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("rollingScaleFactorPush", &TankRamTrack::SetRollingScaleFactorPush);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("rollingScaleBackwardsFactorPush", &TankRamTrack::SetRollingScaleBackwardsFactorPush);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("toleranceForward", &TankRamTrack::SetToleranceForward);
					properties[9] = property;
					property = new fight::PropertyFloatConstRange<TankRamTrack>("speed", &TankRamTrack::SetSpeed);
					properties[10] = property;
					fight::RegisterPropertyList(properties, &gTankRamTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10246B80
			fight::TrackFactory* CreateTankRamTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TankRamTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10246EB0
			void RegisterTankRamTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TankRamTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x10208100
			// EQUIVALENT: scheduling; the integer store at +0x48 follows the float stores in the engine, ours hoists it; the same stores
			TankRamAction::TankRamAction(TankRamTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), unknown30(0.0f), unknown34(-1.0f), unknown38(0.0f), unknown3C(0.0f), unknown40(0.0f), unknown44(0.0f), unknown48(0)
			{
			}

			// FUNCTION: ENGINE 0x10207F30
			TankRamAction::~TankRamAction()
			{
			}

			// FUNCTION: ENGINE 0x102089D0
			fight::Action* TankRamTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new TankRamAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<TankRamTrack>;
			template class fight::TrackFactoryTemplate<TankRamTrack>;
			template class fight::TrackFactoryCasterTemplate<TankRamTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10207E90
// FUNCTION: ENGINE 0x10207EC0
// FUNCTION: ENGINE 0x102081B0
// FUNCTION: ENGINE 0x10246AA0
// FUNCTION: ENGINE 0x10246AD0
// FUNCTION: ENGINE 0x10246AE0
// FUNCTION: ENGINE 0x10246B10
// FUNCTION: ENGINE 0x10246B40
// FUNCTION: ENGINE 0x10246B70
// FUNCTION: ENGINE 0x10246EE0
// FUNCTION: ENGINE 0x10246F10
// FUNCTION: ENGINE 0x10246F30
