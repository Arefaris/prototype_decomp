// Fight items of the motion group: SetVisibilityTrack (unit 0x101AB2E0 - 0x101AB8A0; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_setvisibility.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gSetVisibilityTrackProperties;  // 0x11254A68

			// FUNCTION: ENGINE 0x101AB2E0
			bool SetVisibilityTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AB300
			bool SetVisibilityTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AB320
			bool SetVisibilityTrack::SetActionOnBegin(int newValue)
			{
				actionOnBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AB330
			bool SetVisibilityTrack::SetActionOnEnd(int newValue)
			{
				actionOnEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AB340
			bool SetVisibilityTrack::SetApplyToGrabSlots(bool newValue)
			{
				applyToGrabSlots = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101AB350
			fight::Property* SetVisibilityTrack::GetProperty(int index)
			{
				return gSetVisibilityTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x101AB370
			void SetVisibilityTrack::ClearProperties()
			{
				fight::FreePropertyList(&gSetVisibilityTrackProperties);
			}

			// FUNCTION: ENGINE 0x101AB380
			SetVisibilityTrack::SetVisibilityTrack() : timeBegin(0.0f), timeEnd(0.0f), actionOnBegin(0), actionOnEnd(0), applyToGrabSlots(true)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x101AB3C0
			float SetVisibilityTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x101AB3D0
			float SetVisibilityTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x101AB3E0
			SetVisibilityTrack::~SetVisibilityTrack()
			{
			}

			// FUNCTION: ENGINE 0x101AB610
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void SetVisibilityTrack::RegisterProperties()
			{
				if (gSetVisibilityTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<SetVisibilityTrack>("timeBegin", &SetVisibilityTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<SetVisibilityTrack>("timeEnd", &SetVisibilityTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyEnumConstList<SetVisibilityTrack>("actionOnBegin", gSetVisibilityTrackActionOnBeginTable, gSetVisibilityTrackActionOnBeginCount, &SetVisibilityTrack::SetActionOnBegin);
					properties[2] = property;
					property = new fight::PropertyEnumConstList<SetVisibilityTrack>("actionOnEnd", gSetVisibilityTrackActionOnEndTable, gSetVisibilityTrackActionOnEndCount, &SetVisibilityTrack::SetActionOnEnd);
					properties[3] = property;
					property = new fight::PropertyBool<SetVisibilityTrack>("applyToGrabSlots", &SetVisibilityTrack::SetApplyToGrabSlots);
					properties[4] = property;
					fight::RegisterPropertyList(properties, &gSetVisibilityTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x101AB5E0
			fight::TrackFactory* CreateSetVisibilityTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetVisibilityTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x101AB7D0
			void RegisterSetVisibilityTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<SetVisibilityTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x1010EC00
			SetVisibilityAction::SetVisibilityAction(SetVisibilityTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x1010EA80
			SetVisibilityAction::~SetVisibilityAction()
			{
			}

			// FUNCTION: ENGINE 0x1010EE90
			fight::Action* SetVisibilityTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new SetVisibilityAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<SetVisibilityTrack>;
			template class fight::PropertyEnumConstList<SetVisibilityTrack>;
			template class fight::PropertyBool<SetVisibilityTrack>;
			template class fight::TrackFactoryTemplate<SetVisibilityTrack>;
			template class fight::TrackFactoryCasterTemplate<SetVisibilityTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1010E9E0
// FUNCTION: ENGINE 0x1010EA10
// FUNCTION: ENGINE 0x1010EC80
// FUNCTION: ENGINE 0x101AB3F0
// FUNCTION: ENGINE 0x101AB420
// FUNCTION: ENGINE 0x101AB430
// FUNCTION: ENGINE 0x101AB460
// FUNCTION: ENGINE 0x101AB490
// FUNCTION: ENGINE 0x101AB4C0
// FUNCTION: ENGINE 0x101AB4D0
// FUNCTION: ENGINE 0x101AB510
// FUNCTION: ENGINE 0x101AB520
// FUNCTION: ENGINE 0x101AB550
// FUNCTION: ENGINE 0x101AB570
// FUNCTION: ENGINE 0x101AB580
// FUNCTION: ENGINE 0x101AB5B0
// FUNCTION: ENGINE 0x101AB5D0
// FUNCTION: ENGINE 0x101AB800
// FUNCTION: ENGINE 0x101AB830
// FUNCTION: ENGINE 0x101AB850
