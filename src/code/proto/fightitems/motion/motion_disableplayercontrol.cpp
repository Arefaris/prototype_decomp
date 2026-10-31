// Fight items of the motion group: DisablePlayerControlTrack (unit 0x101598C0 - 0x10159C60; no assert path, the file name is a guess).
#include "code/proto/fightitems/motion/motion_disableplayercontrol.h"
#include "code/engine/system/poimanager.hpp"

namespace proto
{
	namespace fightitems
	{
		namespace motion
		{
			fight::Property** gDisablePlayerControlTrackProperties;  // 0x11254464

			// FUNCTION: ENGINE 0x101598C0
			bool DisablePlayerControlTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x101598E0
			bool DisablePlayerControlTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10159900
			fight::Property* DisablePlayerControlTrack::GetProperty(int index)
			{
				return gDisablePlayerControlTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10159920
			void DisablePlayerControlTrack::ClearProperties()
			{
				fight::FreePropertyList(&gDisablePlayerControlTrackProperties);
			}

			// FUNCTION: ENGINE 0x10159930
			DisablePlayerControlTrack::DisablePlayerControlTrack() : timeBegin(0.0f), timeEnd(-1.0f)
			{
				unknownC = 1;
			}

			// FUNCTION: ENGINE 0x10159970
			float DisablePlayerControlTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10159980
			float DisablePlayerControlTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10159990
			DisablePlayerControlTrack::~DisablePlayerControlTrack()
			{
			}

			// FUNCTION: ENGINE 0x10159AB0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void DisablePlayerControlTrack::RegisterProperties()
			{
				if (gDisablePlayerControlTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<DisablePlayerControlTrack>("timeBegin", &DisablePlayerControlTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<DisablePlayerControlTrack>("timeEnd", &DisablePlayerControlTrack::SetTimeEnd);
					properties[1] = property;
					fight::RegisterPropertyList(properties, &gDisablePlayerControlTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10159A80
			fight::TrackFactory* CreateDisablePlayerControlTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<DisablePlayerControlTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x10159B90
			void RegisterDisablePlayerControlTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<DisablePlayerControlTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// FUNCTION: ENGINE 0x100B7700
			DisablePlayerControlAction::DisablePlayerControlAction(engine::GameObjectHandle newTarget) : fight::Action(0xE00), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x100B7730
			DisablePlayerControlAction::~DisablePlayerControlAction()
			{
			}

			// FUNCTION: ENGINE 0x100B7740
			fight::Action* DisablePlayerControlTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new DisablePlayerControlAction(handle);
			}

			// FUNCTION: ENGINE 0x100B77B0
			bool DisablePlayerControlAction::Slot5(int arg, float value)
			{
				engine::GameObject* object = target.Get();
				if (object == 0)
				{
					return false;
				}
				player = engine::GetControllingPlayer(object);
				if (player >= 0)
				{
					engine::GameObjectHandle none;
					engine::POIManager::Get(player).PushControlled(none);
				}
				return true;
			}

			// FUNCTION: ENGINE 0x100B7840
			void DisablePlayerControlAction::Slot6()
			{
				if (target.Get() != 0 && player >= 0)
				{
					engine::GameObjectHandle none;
					engine::POIManager::Get(player).PopControlled(none);
				}
			}

			// ---- actions end
			template class fight::PropertyFloatConstRange<DisablePlayerControlTrack>;
			template class fight::TrackFactoryTemplate<DisablePlayerControlTrack>;
			template class fight::TrackFactoryCasterTemplate<DisablePlayerControlTrack>;
		}
	}
}

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x101599A0
// FUNCTION: ENGINE 0x101599D0
// FUNCTION: ENGINE 0x101599E0
// FUNCTION: ENGINE 0x10159A10
// FUNCTION: ENGINE 0x10159A40
// FUNCTION: ENGINE 0x10159A70
// FUNCTION: ENGINE 0x10159BC0
// FUNCTION: ENGINE 0x10159BF0
// FUNCTION: ENGINE 0x10159C10
// FUNCTION: ENGINE 0x100B7690
// FUNCTION: ENGINE 0x100B7780
