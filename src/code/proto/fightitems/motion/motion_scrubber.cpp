// Fight items of the motion group: ScrubberTrack (unit 0x101AADF0 - 0x101AB2E0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_scrubber.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gScrubberTrackProperties;  // 0x11254A64

			// FUNCTION: ENGINE 0x101AAE70
			bool ScrubberTrack::SetAnimation(const fight::Name& newValue)
			{
				animation = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AADF0
			bool ScrubberTrack::SetFrame(float newValue)
			{
				frame = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AAE10
			bool ScrubberTrack::SetFrameOffset(float newValue)
			{
				frameOffset = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AAE30
			bool ScrubberTrack::SetHasRootTranslation(bool newValue)
			{
				hasRootTranslation = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AAE40
			fight::Property* ScrubberTrack::GetProperty(int index)
			{
				return gScrubberTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101AAE60
			void ScrubberTrack::ClearProperties()
			{
				fight::FreePropertyList(&gScrubberTrackProperties);
			}

			// FUNCTION: ENGINE 0x101AAE90
			ScrubberTrack::ScrubberTrack() : frame(0.0f), frameOffset(0.0f), hasRootTranslation(true)
			{
			}

			// FUNCTION: ENGINE 0x101AAED0
			float ScrubberTrack::GetTimeBegin() const
			{
				return 0.0f;
			}

			// FUNCTION: ENGINE 0x101AAEE0
			float ScrubberTrack::Slot10() const
			{
				return -1.0f;
			}

			// FUNCTION: ENGINE 0x101AAEF0
			ScrubberTrack::~ScrubberTrack()
			{
			}

			// FUNCTION: ENGINE 0x101AB0F0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void ScrubberTrack::RegisterProperties()
			{
				if (gScrubberTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyName<ScrubberTrack>("animation", &ScrubberTrack::SetAnimation);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<ScrubberTrack>("frame", &ScrubberTrack::SetFrame);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<ScrubberTrack>("frameOffset", &ScrubberTrack::SetFrameOffset);
					properties[2] = property;
					property = new fight::PropertyBool<ScrubberTrack>("hasRootTranslation", &ScrubberTrack::SetHasRootTranslation);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gScrubberTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AB040
			fight::TrackFactory* CreateScrubberTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<ScrubberTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AB070
			void RegisterScrubberTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<ScrubberTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// FUNCTION: ENGINE 0x1010E4D0
			ScrubberAction::ScrubberAction(ScrubberTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), driver(0)
			{
			}

			// FUNCTION: ENGINE 0x1010E350
			ScrubberAction::~ScrubberAction()
			{
				engine::ReleaseDriver(driver);
			}

			// FUNCTION: ENGINE 0x1010E8E0
			fight::Action* ScrubberTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				return new ScrubberAction(this, engine::GetObjectHandle(owner));
			}

			// FUNCTION: ENGINE 0x1010E390
			// EQUIVALENT: instruction selection of the pointer to bool conversion (neg, sbb, neg where ours has test, setne) (63.9 %)
			bool ScrubberAction::Slot5(int arg, float value)
			{
				return engine::GetPuppet(target.Get()) != 0;
			}

			// FUNCTION: ENGINE 0x1010E3F0
			void ScrubberAction::Slot6()
			{
				engine::GameObject* object = target.Get();
				if (object != 0)
				{
					choreo::Puppet* puppet = engine::GetPuppet(object);
					if (puppet != 0)
					{
						puppet->RemoveDriver(driver, false);
						engine::ReleaseDriver(driver);
					}
				}
			}

			// ---- actions end
			template class fight::PropertyName<ScrubberTrack>;
			template class fight::PropertyFloatConstRange<ScrubberTrack>;
			template class fight::PropertyBool<ScrubberTrack>;
			template class fight::TrackFactoryTemplate<ScrubberTrack>;
			template class fight::TrackFactoryCasterTemplate<ScrubberTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1010E2B0
// FUNCTION: ENGINE 0x1010E2E0
// FUNCTION: ENGINE 0x1010E540
// FUNCTION: ENGINE 0x101AAF00
// FUNCTION: ENGINE 0x101AAF10
// FUNCTION: ENGINE 0x101AAF40
// FUNCTION: ENGINE 0x101AAF70
// FUNCTION: ENGINE 0x101AAFA0
// FUNCTION: ENGINE 0x101AAFD0
// FUNCTION: ENGINE 0x101AAFE0
// FUNCTION: ENGINE 0x101AB010
// FUNCTION: ENGINE 0x101AB030
// FUNCTION: ENGINE 0x101AB0A0
// FUNCTION: ENGINE 0x101AB0D0
// FUNCTION: ENGINE 0x101AB240
// FUNCTION: ENGINE 0x101AB270
// FUNCTION: ENGINE 0x101AB290
