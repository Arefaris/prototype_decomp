// Fight items of the ai group: ConfigureScaryMonsterBehaviourTrack, ActivateScaryMonsterBehaviourTrack (unit 0x1021AB50 - 0x1021B3C0; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_scarymonster.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gConfigureScaryMonsterBehaviourTrackProperties;  // 0x11255804

			// FUNCTION: ENGINE 0x1021AA70
			bool ConfigureScaryMonsterBehaviourTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021AA90
			bool ConfigureScaryMonsterBehaviourTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021AAB0
			bool ConfigureScaryMonsterBehaviourTrack::SetIntensity(float newValue)
			{
				intensity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021AAD0
			bool ConfigureScaryMonsterBehaviourTrack::SetVelocityOffset(float newValue)
			{
				velocityOffset = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021AAF0
			bool ConfigureScaryMonsterBehaviourTrack::SetFrequency(int newValue)
			{
				frequency = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021AB50
			fight::Property* ConfigureScaryMonsterBehaviourTrack::GetProperty(int index)
			{
				return gConfigureScaryMonsterBehaviourTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1021AB70
			void ConfigureScaryMonsterBehaviourTrack::ClearProperties()
			{
				fight::FreePropertyList(&gConfigureScaryMonsterBehaviourTrackProperties);
			}

			// FUNCTION: ENGINE 0x1021AB80
			ConfigureScaryMonsterBehaviourTrack::ConfigureScaryMonsterBehaviourTrack() : intensity(1e+01f), timeBegin(0.0f), timeEnd(-1.0f), velocityOffset(0.0f), frequency(10)
			{
			}

			// FUNCTION: ENGINE 0x1021ABD0
			float ConfigureScaryMonsterBehaviourTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1021ABE0
			float ConfigureScaryMonsterBehaviourTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1021ABF0
			ConfigureScaryMonsterBehaviourTrack::~ConfigureScaryMonsterBehaviourTrack()
			{
			}

			// FUNCTION: ENGINE 0x1021AF80
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ConfigureScaryMonsterBehaviourTrack::RegisterProperties()
			{
				if (gConfigureScaryMonsterBehaviourTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ConfigureScaryMonsterBehaviourTrack>("timeBegin", &ConfigureScaryMonsterBehaviourTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ConfigureScaryMonsterBehaviourTrack>("timeEnd", &ConfigureScaryMonsterBehaviourTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ConfigureScaryMonsterBehaviourTrack>("intensity", &ConfigureScaryMonsterBehaviourTrack::SetIntensity);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<ConfigureScaryMonsterBehaviourTrack>("velocityOffset", &ConfigureScaryMonsterBehaviourTrack::SetVelocityOffset);
					properties[3] = property;
					property = new fight::PropertyIntConstRange<ConfigureScaryMonsterBehaviourTrack>("frequency", &ConfigureScaryMonsterBehaviourTrack::SetFrequency);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gConfigureScaryMonsterBehaviourTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1021AF20
			fight::TrackFactory* CreateConfigureScaryMonsterBehaviourTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ConfigureScaryMonsterBehaviourTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1021B220
			void RegisterConfigureScaryMonsterBehaviourTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ConfigureScaryMonsterBehaviourTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			fight::Property** gActivateScaryMonsterBehaviourTrackProperties;  // 0x11255808

			// FUNCTION: ENGINE 0x1021AB00
			bool ActivateScaryMonsterBehaviourTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021AB20
			bool ActivateScaryMonsterBehaviourTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021AB40
			bool ActivateScaryMonsterBehaviourTrack::SetActivate(bool newValue)
			{
				activate = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021AC00
			fight::Property* ActivateScaryMonsterBehaviourTrack::GetProperty(int index)
			{
				return gActivateScaryMonsterBehaviourTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1021AC20
			void ActivateScaryMonsterBehaviourTrack::ClearProperties()
			{
				fight::FreePropertyList(&gActivateScaryMonsterBehaviourTrackProperties);
			}

			// FUNCTION: ENGINE 0x1021AC30
			ActivateScaryMonsterBehaviourTrack::ActivateScaryMonsterBehaviourTrack() : timeBegin(0.0f), timeEnd(-1.0f), activate(true)
			{
			}

			// FUNCTION: ENGINE 0x1021AC70
			float ActivateScaryMonsterBehaviourTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1021AC80
			float ActivateScaryMonsterBehaviourTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1021AC90
			ActivateScaryMonsterBehaviourTrack::~ActivateScaryMonsterBehaviourTrack()
			{
			}

			// FUNCTION: ENGINE 0x1021B110
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ActivateScaryMonsterBehaviourTrack::RegisterProperties()
			{
				if (gActivateScaryMonsterBehaviourTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<ActivateScaryMonsterBehaviourTrack>("timeBegin", &ActivateScaryMonsterBehaviourTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ActivateScaryMonsterBehaviourTrack>("timeEnd", &ActivateScaryMonsterBehaviourTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyBool<ActivateScaryMonsterBehaviourTrack>("activate", &ActivateScaryMonsterBehaviourTrack::SetActivate);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gActivateScaryMonsterBehaviourTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1021AF50
			fight::TrackFactory* CreateActivateScaryMonsterBehaviourTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ActivateScaryMonsterBehaviourTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1021B250
			void RegisterActivateScaryMonsterBehaviourTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ActivateScaryMonsterBehaviourTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x101DDD20
			ConfigureScaryMonsterBehaviourAction::ConfigureScaryMonsterBehaviourAction(ConfigureScaryMonsterBehaviourTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0x200), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101DDA00
			ConfigureScaryMonsterBehaviourAction::~ConfigureScaryMonsterBehaviourAction()
			{
			}

			// FUNCTION: ENGINE 0x101DDEC0
			fight::Action* ConfigureScaryMonsterBehaviourTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ConfigureScaryMonsterBehaviourAction(this, handle);
			}

			// FUNCTION: ENGINE 0x101DDB00
			ActivateScaryMonsterBehaviourAction::ActivateScaryMonsterBehaviourAction(ActivateScaryMonsterBehaviourTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101DD9B0
			ActivateScaryMonsterBehaviourAction::~ActivateScaryMonsterBehaviourAction()
			{
			}

			// FUNCTION: ENGINE 0x101DD800
			bool ActivateScaryMonsterBehaviourAction::Slot7(int arg, float value)
			{
				return true;
			}

			// FUNCTION: ENGINE 0x101DDE70
			fight::Action* ActivateScaryMonsterBehaviourTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new ActivateScaryMonsterBehaviourAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<ConfigureScaryMonsterBehaviourTrack>;
			template class fight::PropertyIntConstRange<ConfigureScaryMonsterBehaviourTrack>;
			template class fight::TrackFactoryTemplate<ConfigureScaryMonsterBehaviourTrack>;
			template class fight::TrackFactoryCasterTemplate<ConfigureScaryMonsterBehaviourTrack>;
			template class fight::PropertyFloatConstRange<ActivateScaryMonsterBehaviourTrack>;
			template class fight::PropertyBool<ActivateScaryMonsterBehaviourTrack>;
			template class fight::TrackFactoryTemplate<ActivateScaryMonsterBehaviourTrack>;
			template class fight::TrackFactoryCasterTemplate<ActivateScaryMonsterBehaviourTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101DD890
// FUNCTION: ENGINE 0x101DD8B0
// FUNCTION: ENGINE 0x101DD8E0
// FUNCTION: ENGINE 0x101DD940
// FUNCTION: ENGINE 0x101DDB80
// FUNCTION: ENGINE 0x101DDDA0
// FUNCTION: ENGINE 0x101DE530
// FUNCTION: ENGINE 0x1021ACA0
// FUNCTION: ENGINE 0x1021ACD0
// FUNCTION: ENGINE 0x1021AD00
// FUNCTION: ENGINE 0x1021AD10
// FUNCTION: ENGINE 0x1021AD40
// FUNCTION: ENGINE 0x1021AD50
// FUNCTION: ENGINE 0x1021AD80
// FUNCTION: ENGINE 0x1021ADB0
// FUNCTION: ENGINE 0x1021ADE0
// FUNCTION: ENGINE 0x1021ADF0
// FUNCTION: ENGINE 0x1021AE20
// FUNCTION: ENGINE 0x1021AE40
// FUNCTION: ENGINE 0x1021AE50
// FUNCTION: ENGINE 0x1021AE80
// FUNCTION: ENGINE 0x1021AEB0
// FUNCTION: ENGINE 0x1021AEC0
// FUNCTION: ENGINE 0x1021AEF0
// FUNCTION: ENGINE 0x1021AF10
// FUNCTION: ENGINE 0x1021B280
// FUNCTION: ENGINE 0x1021B2B0
// FUNCTION: ENGINE 0x1021B2D0
// FUNCTION: ENGINE 0x1021B300
// FUNCTION: ENGINE 0x1021B320
// FUNCTION: ENGINE 0x1021B370
