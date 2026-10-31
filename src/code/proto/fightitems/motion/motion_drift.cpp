// Fight items of the motion group: DriftTrack (unit 0x1015A810 - 0x1015AC70; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_drift.h"
#include "code/proto/fightitems/motion/motionmessages.h"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gDriftTrackProperties;  // 0x11254474

			// FUNCTION: ENGINE 0x1015A810
			bool DriftTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015A830
			bool DriftTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015A850
			bool DriftTrack::SetMinVelocity(float newValue)
			{
				minVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015A870
			bool DriftTrack::SetMaxVelocity(float newValue)
			{
				maxVelocity = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x1015A890
			fight::Property* DriftTrack::GetProperty(int index)
			{
				return gDriftTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x1015A8B0
			void DriftTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDriftTrackProperties);
			}

			// FUNCTION: ENGINE 0x1015A8C0
			DriftTrack::DriftTrack() : maxVelocity(0.0f), minVelocity(0.0f), timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x1015A910
			float DriftTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x1015A920
			float DriftTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x1015A930
			DriftTrack::~DriftTrack()
			{
			}

			// FUNCTION: ENGINE 0x1015AA50
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DriftTrack::RegisterProperties()
			{
				if (gDriftTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DriftTrack>("timeBegin", &DriftTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DriftTrack>("timeEnd", &DriftTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<DriftTrack>("minVelocity", &DriftTrack::SetMinVelocity);
					properties[2] = property;
					property = new fight::PropertyFloatConstRange<DriftTrack>("maxVelocity", &DriftTrack::SetMaxVelocity);
					properties[3] = property;
					fight::RegisterPropertyList(properties, &gDriftTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x1015AA20
			fight::TrackFactory* CreateDriftTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DriftTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x1015ABA0
			void RegisterDriftTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DriftTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin
			// FUNCTION: ENGINE 0x100B8970
			DriftAction::DriftAction(DriftTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), target(newTarget), link(newTrack)
			{
			}

			// FUNCTION: ENGINE 0x100B8860
			DriftAction::~DriftAction()
			{
			}

			// FUNCTION: ENGINE 0x100B8D80
			fight::Action* DriftTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new DriftAction(this, handle);
			}

			// ---- actions end
			// FUNCTION: ENGINE 0x100B8890
			void DriftAction::Slot6()
			{
				engine::GameObject* object = target.Get();
				if (object != 0)
				{
					DriftEnableMessage message(false);
					object->SendMessage(&message);
				}
			}

			template class fight::PropertyFloatConstRange<DriftTrack>;
			template class fight::TrackFactoryTemplate<DriftTrack>;
			template class fight::TrackFactoryCasterTemplate<DriftTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x1015A940
// FUNCTION: ENGINE 0x1015A970
// FUNCTION: ENGINE 0x1015A980
// FUNCTION: ENGINE 0x1015A9B0
// FUNCTION: ENGINE 0x1015A9E0
// FUNCTION: ENGINE 0x1015AA10
// FUNCTION: ENGINE 0x1015ABD0
// FUNCTION: ENGINE 0x1015AC00
// FUNCTION: ENGINE 0x1015AC20
// FUNCTION: ENGINE 0x100B8670
// FUNCTION: ENGINE 0x100B8680
// FUNCTION: ENGINE 0x100B86B0
// FUNCTION: ENGINE 0x100B8760
// FUNCTION: ENGINE 0x100B87C0
// FUNCTION: ENGINE 0x100B87F0
// FUNCTION: ENGINE 0x100B89E0
