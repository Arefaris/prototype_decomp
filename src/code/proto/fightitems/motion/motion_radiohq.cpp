// Fight items of the motion group: RadioHQTrack, ScenarioEventRadioAttemptTrack (unit 0x101A0B00 - 0x101A1160; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_radiohq.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gRadioHQTrackProperties;  // 0x1125495C

			// FUNCTION: ENGINE 0x101A0B00
			bool RadioHQTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A0B40
			fight::Property* RadioHQTrack::GetProperty(int index)
			{
				return gRadioHQTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101A0B60
			void RadioHQTrack::ClearProperties()
			{
				fight::FreePropertyList(&gRadioHQTrackProperties);
			}

			// FUNCTION: ENGINE 0x101A0B70
			RadioHQTrack::RadioHQTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101A0BA0
			float RadioHQTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101A0BB0
			float RadioHQTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101A0BC0
			RadioHQTrack::~RadioHQTrack()
			{
			}

			// FUNCTION: ENGINE 0x101A0E80
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void RadioHQTrack::RegisterProperties()
			{
				if (gRadioHQTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<RadioHQTrack>("timeBegin", &RadioHQTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gRadioHQTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A0E20
			fight::TrackFactory* CreateRadioHQTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<RadioHQTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A0FC0
			void RegisterRadioHQTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<RadioHQTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gScenarioEventRadioAttemptTrackProperties;  // 0x11254960

			// FUNCTION: ENGINE 0x101A0B20
			bool ScenarioEventRadioAttemptTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101A0BD0
			fight::Property* ScenarioEventRadioAttemptTrack::GetProperty(int index)
			{
				return gScenarioEventRadioAttemptTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101A0BF0
			void ScenarioEventRadioAttemptTrack::ClearProperties()
			{
				fight::FreePropertyList(&gScenarioEventRadioAttemptTrackProperties);
			}

			// FUNCTION: ENGINE 0x101A0C00
			ScenarioEventRadioAttemptTrack::ScenarioEventRadioAttemptTrack() : timeBegin(0.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101A0C30
			float ScenarioEventRadioAttemptTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101A0C40
			float ScenarioEventRadioAttemptTrack::Slot10() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101A0C50
			ScenarioEventRadioAttemptTrack::~ScenarioEventRadioAttemptTrack()
			{
			}

			// FUNCTION: ENGINE 0x101A0F20
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ScenarioEventRadioAttemptTrack::RegisterProperties()
			{
				if (gScenarioEventRadioAttemptTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ScenarioEventRadioAttemptTrack>("timeBegin", &ScenarioEventRadioAttemptTrack::SetTimeBegin);
					properties[0] = property;
					fight::RegisterPropertyList(properties, &gScenarioEventRadioAttemptTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101A0E50
			fight::TrackFactory* CreateScenarioEventRadioAttemptTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ScenarioEventRadioAttemptTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101A0FF0
			void RegisterScenarioEventRadioAttemptTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ScenarioEventRadioAttemptTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x10105DB0
			RadioHQAction::RadioHQAction(RadioHQTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x10105C80
			RadioHQAction::~RadioHQAction()
			{
			}

			// FUNCTION: ENGINE 0x101060D0
			fight::Action* RadioHQTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new RadioHQAction(this, handle);
			}

			// FUNCTION: ENGINE 0x10106020
			ScenarioEventRadioAttemptAction::ScenarioEventRadioAttemptAction(ScenarioEventRadioAttemptTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x10105CD0
			ScenarioEventRadioAttemptAction::~ScenarioEventRadioAttemptAction()
			{
			}

			// FUNCTION: ENGINE 0x10106120
			fight::Action* ScenarioEventRadioAttemptTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ScenarioEventRadioAttemptAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<RadioHQTrack>;
			template class fight::TrackFactoryTemplate<RadioHQTrack>;
			template class fight::TrackFactoryCasterTemplate<RadioHQTrack>;
			template class fight::PropertyFloatConstRange<ScenarioEventRadioAttemptTrack>;
			template class fight::TrackFactoryTemplate<ScenarioEventRadioAttemptTrack>;
			template class fight::TrackFactoryCasterTemplate<ScenarioEventRadioAttemptTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x10105B70
// FUNCTION: ENGINE 0x10105B90
// FUNCTION: ENGINE 0x10105BC0
// FUNCTION: ENGINE 0x10105C10
// FUNCTION: ENGINE 0x10105E30
// FUNCTION: ENGINE 0x101060A0
// FUNCTION: ENGINE 0x101A0C60
// FUNCTION: ENGINE 0x101A0C90
// FUNCTION: ENGINE 0x101A0CC0
// FUNCTION: ENGINE 0x101A0CD0
// FUNCTION: ENGINE 0x101A0D00
// FUNCTION: ENGINE 0x101A0D10
// FUNCTION: ENGINE 0x101A0D40
// FUNCTION: ENGINE 0x101A0D70
// FUNCTION: ENGINE 0x101A0DA0
// FUNCTION: ENGINE 0x101A0DB0
// FUNCTION: ENGINE 0x101A0DE0
// FUNCTION: ENGINE 0x101A0E10
// FUNCTION: ENGINE 0x101A1020
// FUNCTION: ENGINE 0x101A1050
// FUNCTION: ENGINE 0x101A1070
// FUNCTION: ENGINE 0x101A10A0
// FUNCTION: ENGINE 0x101A10C0
// FUNCTION: ENGINE 0x101A1110
