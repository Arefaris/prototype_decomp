// Fight items of the ai group: CheckBodyTrack (unit 0x1021C920 - 0x1021CD90; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_checkbody.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gCheckBodyTrackProperties;  // 0x1125582C

			// FUNCTION: ENGINE 0x1021C920
			bool CheckBodyTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021C940
			bool CheckBodyTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021C960
			bool CheckBodyTrack::SetStopDistance(float newValue)
			{
				stopDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021C980
			bool CheckBodyTrack::SetTimeCheckingBody(float newValue)
			{
				timeCheckingBody = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1021C9A0
			fight::Property* CheckBodyTrack::GetProperty(int index)
			{
				return gCheckBodyTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1021C9C0
			void CheckBodyTrack::ClearProperties()
			{
				fight::FreePropertyList(&gCheckBodyTrackProperties);
			}

			// FUNCTION: ENGINE 0x1021C9D0
			CheckBodyTrack::CheckBodyTrack() : stopDistance(2.0f), timeBegin(0.0f), timeCheckingBody(6.0f), timeEnd(-1.0f)
			{
			}

			// FUNCTION: ENGINE 0x1021CA30
			float CheckBodyTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1021CA40
			float CheckBodyTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1021CA50
			CheckBodyTrack::~CheckBodyTrack()
			{
			}

			// FUNCTION: ENGINE 0x1021CB70
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void CheckBodyTrack::RegisterProperties()
			{
				if (gCheckBodyTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<CheckBodyTrack>("timeBegin", &CheckBodyTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<CheckBodyTrack>("timeEnd", &CheckBodyTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<CheckBodyTrack>("stopDistance", &CheckBodyTrack::SetStopDistance);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<CheckBodyTrack>("timeCheckingBody", &CheckBodyTrack::SetTimeCheckingBody);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gCheckBodyTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1021CB40
			fight::TrackFactory* CreateCheckBodyTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<CheckBodyTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1021CCC0
			void RegisterCheckBodyTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<CheckBodyTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x101DFB80
			CheckBodyAction::CheckBodyAction(CheckBodyTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), link(newTrack), target(newTarget), unknown38(false), unknown3C(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x101DFAA0
			CheckBodyAction::~CheckBodyAction()
			{
			}

			// FUNCTION: ENGINE 0x101E0030
			fight::Action* CheckBodyTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new CheckBodyAction(this, handle);
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<CheckBodyTrack>;
			template class fight::TrackFactoryTemplate<CheckBodyTrack>;
			template class fight::TrackFactoryCasterTemplate<CheckBodyTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101DE130
// FUNCTION: ENGINE 0x101DE2D0
// FUNCTION: ENGINE 0x101DFBF0
// FUNCTION: ENGINE 0x1021CA60
// FUNCTION: ENGINE 0x1021CA90
// FUNCTION: ENGINE 0x1021CAA0
// FUNCTION: ENGINE 0x1021CAD0
// FUNCTION: ENGINE 0x1021CB00
// FUNCTION: ENGINE 0x1021CB30
// FUNCTION: ENGINE 0x1021CCF0
// FUNCTION: ENGINE 0x1021CD20
// FUNCTION: ENGINE 0x1021CD40
