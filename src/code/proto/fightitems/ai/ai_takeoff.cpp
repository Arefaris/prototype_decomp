// Fight items of the ai group: TakeOffTrack, LandTrack (unit 0x102356A0 - 0x10236270; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_takeoff.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gTakeOffTrackProperties;  // 0x11255A20

			// FUNCTION: ENGINE 0x102356A0
			bool TakeOffTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102356C0
			bool TakeOffTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102356E0
			bool TakeOffTrack::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10235700
			bool TakeOffTrack::SetAcceleration(float newValue)
			{
				acceleration = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10235720
			bool TakeOffTrack::SetMinHeight(float newValue)
			{
				minHeight = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10235850
			fight::Property* TakeOffTrack::GetProperty(int index)
			{
				return gTakeOffTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10235870
			void TakeOffTrack::ClearProperties()
			{
				fight::FreePropertyList(&gTakeOffTrackProperties);
			}

			// FUNCTION: ENGINE 0x10235880
			TakeOffTrack::TakeOffTrack() : acceleration(5.0f), minHeight(6.0f), speed(0.2f), timeBegin(0.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x102358F0
			float TakeOffTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10235900
			float TakeOffTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10235910
			TakeOffTrack::~TakeOffTrack()
			{
			}

			// FUNCTION: ENGINE 0x10235C80
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void TakeOffTrack::RegisterProperties()
			{
				if (gTakeOffTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<TakeOffTrack>("timeBegin", &TakeOffTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<TakeOffTrack>("timeEnd", &TakeOffTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<TakeOffTrack>("speed", &TakeOffTrack::SetSpeed);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<TakeOffTrack>("acceleration", &TakeOffTrack::SetAcceleration);
					properties[3] = property;
					property = new fight::PropertyFloatConstRange<TakeOffTrack>("minHeight", &TakeOffTrack::SetMinHeight);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gTakeOffTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10235C20
			fight::TrackFactory* CreateTakeOffTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<TakeOffTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102360D0
			void RegisterTakeOffTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<TakeOffTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gLandTrackProperties;  // 0x11255A24

			// FUNCTION: ENGINE 0x10235740
			bool LandTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10235760
			bool LandTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10235780
			bool LandTrack::SetSpeed(float newValue)
			{
				speed = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102357A0
			bool LandTrack::SetToleraceAngleStartLanding(float newValue)
			{
				toleraceAngleStartLanding = newValue * 0.017453292f;
				return true;
			}

			// FUNCTION: ENGINE 0x102357C0
			bool LandTrack::SetClearDestination(bool newValue)
			{
				clearDestination = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102357D0
			bool LandTrack::SetTurnOffRotor(bool newValue)
			{
				turnOffRotor = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102357E0
			bool LandTrack::SetIgnoreOrientation(bool newValue)
			{
				ignoreOrientation = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x102357F0
			bool LandTrack::SetToleranceY(float newValue)
			{
				toleranceY = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10235810
			bool LandTrack::SetToleranceXZ(float newValue)
			{
				toleranceXZ = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10235830
			bool LandTrack::SetDistanceToGround(float newValue)
			{
				distanceToGround = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10235920
			fight::Property* LandTrack::GetProperty(int index)
			{
				return gLandTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10235940
			void LandTrack::ClearProperties()
			{
				fight::FreePropertyList(&gLandTrackProperties);
			}

			// FUNCTION: ENGINE 0x10235950
			LandTrack::LandTrack() : distanceToGround(1.0f), speed(0.2f), timeBegin(0.0f), timeEnd(-1.0f), toleraceAngleStartLanding(0.43633232f), toleranceXZ(1.0f), toleranceY(1.0f), clearDestination(true), ignoreOrientation(true), turnOffRotor(true)
			{
			}

			// FUNCTION: ENGINE 0x102359D0
			float LandTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x102359E0
			float LandTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x102359F0
			LandTrack::~LandTrack()
			{
			}

			// FUNCTION: ENGINE 0x10235E10
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void LandTrack::RegisterProperties()
			{
				if (gLandTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<LandTrack>("timeBegin", &LandTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<LandTrack>("timeEnd", &LandTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<LandTrack>("speed", &LandTrack::SetSpeed);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<LandTrack>("toleraceAngleStartLanding", &LandTrack::SetToleraceAngleStartLanding);
					properties[3] = property;
					property = new fight::PropertyBool<LandTrack>("clearDestination", &LandTrack::SetClearDestination);
					properties[4] = property;
					property = new fight::PropertyBool<LandTrack>("turnOffRotor", &LandTrack::SetTurnOffRotor);
					properties[5] = property;
					property = new fight::PropertyBool<LandTrack>("ignoreOrientation", &LandTrack::SetIgnoreOrientation);
					properties[6] = property;
					property = new fight::PropertyFloatConstRange<LandTrack>("toleranceY", &LandTrack::SetToleranceY);
					properties[7] = property;
					property = new fight::PropertyFloatConstRange<LandTrack>("toleranceXZ", &LandTrack::SetToleranceXZ);
					properties[8] = property;
					property = new fight::PropertyFloatConstRange<LandTrack>("distanceToGround", &LandTrack::SetDistanceToGround);
					properties[9] = property;
					fight::RegisterPropertyList(properties, &gLandTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10235C50
			fight::TrackFactory* CreateLandTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<LandTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10236100
			void RegisterLandTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<LandTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x101F9B20
			TakeOffAction::TakeOffAction(TakeOffTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), unknown2C(0.0f), unknown30(0.0f), unknown34(false)
			{
			}

			// FUNCTION: ENGINE 0x101F8F60
			TakeOffAction::~TakeOffAction()
			{
			}

			// FUNCTION: ENGINE 0x101F9EC0
			fight::Action* TakeOffTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new TakeOffAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<TakeOffTrack>;
			template class fight::TrackFactoryTemplate<TakeOffTrack>;
			template class fight::TrackFactoryCasterTemplate<TakeOffTrack>;
			template class fight::PropertyFloatConstRange<LandTrack>;
			template class fight::PropertyBool<LandTrack>;
			template class fight::TrackFactoryTemplate<LandTrack>;
			template class fight::TrackFactoryCasterTemplate<LandTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10235A00
// FUNCTION: ENGINE 0x10235A30
// FUNCTION: ENGINE 0x10235A60
// FUNCTION: ENGINE 0x10235A70
// FUNCTION: ENGINE 0x10235AA0
// FUNCTION: ENGINE 0x10235AB0
// FUNCTION: ENGINE 0x10235AE0
// FUNCTION: ENGINE 0x10235B10
// FUNCTION: ENGINE 0x10235B40
// FUNCTION: ENGINE 0x10235B50
// FUNCTION: ENGINE 0x10235B80
// FUNCTION: ENGINE 0x10235BB0
// FUNCTION: ENGINE 0x10235BC0
// FUNCTION: ENGINE 0x10235BF0
// FUNCTION: ENGINE 0x10235C10
// FUNCTION: ENGINE 0x10236130
// FUNCTION: ENGINE 0x10236160
// FUNCTION: ENGINE 0x10236180
// FUNCTION: ENGINE 0x102361B0
// FUNCTION: ENGINE 0x102361D0
// FUNCTION: ENGINE 0x10236220
