// Fight items of the ai group: FleeTrack (unit 0x10231FB0 - 0x10232390; no assert path, the file name is a guess).
#include "code/proto/fightitems/ai/ai_flee.h"
#include "code/proto/fightitems/ai/aimessages.h"

namespace proto
{
	namespace fightitems
	{
		namespace ai
		{
			fight::Property** gFleeTrackProperties;  // 0x112559E0

			// FUNCTION: ENGINE 0x10231FB0
			bool FleeTrack::SetTimeBegin(float newValue)
			{
				timeBegin = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10231FD0
			bool FleeTrack::SetTimeEnd(float newValue)
			{
				timeEnd = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10231FF0
			bool FleeTrack::SetFleeDistance(float newValue)
			{
				fleeDistance = newValue;
				return true;
			}

			// FUNCTION: ENGINE 0x10232010
			fight::Property* FleeTrack::GetProperty(int index)
			{
				return gFleeTrackProperties[index];
			}

			// FUNCTION: ENGINE 0x10232030
			void FleeTrack::ClearProperties()
			{
				fight::FreePropertyList(&gFleeTrackProperties);
			}

			// FUNCTION: ENGINE 0x10232040
			FleeTrack::FleeTrack() : fleeDistance(0.0f), timeBegin(0.0f), timeEnd(0.0f)
			{
			}

			// FUNCTION: ENGINE 0x10232070
			float FleeTrack::GetTimeBegin() const
			{
				return timeBegin;
			}

			// FUNCTION: ENGINE 0x10232080
			float FleeTrack::Slot10() const
			{
				return timeEnd - timeBegin;
			}

			// FUNCTION: ENGINE 0x10232090
			FleeTrack::~FleeTrack()
			{
			}

			// FUNCTION: ENGINE 0x102321B0
			// EQUIVALENT: shrink-wrap; the engine saves esi in the entry block before the guard's branch, ours after it; every other instruction is the engine's
			void FleeTrack::RegisterProperties()
			{
				if (gFleeTrackProperties == 0)
				{
					fight::Property* properties[256] = { 0 };
					fight::Property* property = 0;
					property = new fight::PropertyFloatConstRange<FleeTrack>("timeBegin", &FleeTrack::SetTimeBegin);
					properties[0] = property;
					property = new fight::PropertyFloatConstRange<FleeTrack>("timeEnd", &FleeTrack::SetTimeEnd);
					properties[1] = property;
					property = new fight::PropertyFloatConstRange<FleeTrack>("fleeDistance", &FleeTrack::SetFleeDistance);
					properties[2] = property;
					fight::RegisterPropertyList(properties, &gFleeTrackProperties);
				}
			}

			// FUNCTION: ENGINE 0x10232180
			fight::TrackFactory* CreateFleeTrackFactory(const char* name)
			{
				fight::TrackFactoryCasterTemplate<FleeTrack> caster;
				return fight::FindTrackFactory(name, &caster);
			}

			// FUNCTION: ENGINE 0x102322C0
			void RegisterFleeTrackFactory(fight::TrackRegistry* registry, const char* name)
			{
				fight::TrackFactoryCasterTemplate<FleeTrack> caster;
				registry->AddFactory(fight::FindTrackFactory(name, &caster));
			}

			// ---- actions begin

			// FUNCTION: ENGINE 0x101F3270
			FleeAction::FleeAction(FleeTrack* newTrack, engine::GameObjectHandle newTarget) : fight::Action(0xE00), unknown1C(0), link(newTrack), target(newTarget)
			{
			}

			// FUNCTION: ENGINE 0x101F3100
			FleeAction::~FleeAction()
			{
			}

			// FUNCTION: ENGINE 0x101F3020
			bool FleeAction::Slot5(int arg, float value)
			{
				unknown1C = 0;
				unknown20.serial = 0;
				unknown20.index = 0xFFFF;
				return true;
			}

			// FUNCTION: ENGINE 0x101F3040
			void FleeAction::Slot6()
			{
			}

			// FUNCTION: ENGINE 0x101F3320
			void FleeAction::Flee(const math::Vector* newDirection)
			{
				direction.x = newDirection->x;
				direction.y = newDirection->y;
				direction.z = newDirection->z;
				Unknown103B85A0(target.Get(), 1.0f, newDirection, true);
				unknown1C = 1;
			}

			// FUNCTION: ENGINE 0x101F33A0
			void FleeAction::FleeFromThreat()
			{
				engine::GameObject* object = target.Get();
				math::Matrix* own = object->transform->GetPointer();
				math::Vector ownPosition(own->m[3][0], own->m[3][1], own->m[3][2]);
				engine::GameObject* threat = unknown20.Get();
				math::Matrix* other = threat->transform->GetPointer();
				math::Vector otherPosition(other->m[3][0], other->m[3][1], other->m[3][2]);
				math::Vector away;
				away.x = ownPosition.x - otherPosition.x;
				away.y = 0.0f;
				away.z = ownPosition.z - otherPosition.z;
				away.Normalize();
				Flee(&away);
			}

			// FUNCTION: ENGINE 0x101F3130
			bool FleeAction::KeepFleeing(engine::GameObject* object, float time)
			{
				engine::GameObject* self = target.Get();
				math::Matrix* own = self->transform->GetPointer();
				math::Vector ownPosition(own->m[3][0], own->m[3][1], own->m[3][2]);
				engine::GameObject* threat = unknown20.Get();
				math::Matrix* other = threat->transform->GetPointer();
				math::Vector otherPosition(other->m[3][0], other->m[3][1], other->m[3][2]);
				math::Vector away;
				away.x = ownPosition.x - otherPosition.x;
				away.y = 0.0f;
				away.z = ownPosition.z - otherPosition.z;
				away.Normalize();
				Unknown103B85A0(object, 1.0f, &away, true);
				return true;
			}

			// FUNCTION: ENGINE 0x101F34C0
			bool FleeAction::StartFleeing(engine::GameObject* object, float time)
			{
				GetTargetMessage message;
				object->SendMessage(&message);
				if (message.target.Get() != 0)
				{
					unknown20 = message.target;
					FleeFromThreat();
					unknown1C = 1;
				}
				return true;
			}

			// FUNCTION: ENGINE 0x101F3680
			bool FleeAction::Slot7(int arg, float value)
			{
				switch (unknown1C)
				{
				case 0:
					return StartFleeing(target.Get(), value);
				case 1:
					return KeepFleeing(target.Get(), value);
				}
				return true;
			}

			// FUNCTION: ENGINE 0x101F3470
			fight::Action* FleeTrack::CreateAction(fight::Track* listener, core::IRefCount* effect, core::IRefCount* owner)
			{
				engine::GameObjectHandle handle = engine::GetObjectHandle(owner);
				return new FleeAction(this, handle);
			}
			// ---- actions end
			template class fight::PropertyFloatConstRange<FleeTrack>;
			template class fight::TrackFactoryTemplate<FleeTrack>;
			template class fight::TrackFactoryCasterTemplate<FleeTrack>;
		}
	}
}

template core::Link<proto::fightitems::ai::FleeTrack>::~Link();
template proto::fightitems::ai::FleeTrack* core::Link<proto::fightitems::ai::FleeTrack>::Get() const;
template core::Link<proto::fightitems::ai::FleeTrack>::Link(proto::fightitems::ai::FleeTrack*);

// Kept copies (inline members, template instances and compiler-generated functions of this unit):
// FUNCTION: ENGINE 0x102320A0
// FUNCTION: ENGINE 0x102320D0
// FUNCTION: ENGINE 0x102320E0
// FUNCTION: ENGINE 0x10232110
// FUNCTION: ENGINE 0x10232140
// FUNCTION: ENGINE 0x10232170
// FUNCTION: ENGINE 0x102322F0
// FUNCTION: ENGINE 0x10232320
// FUNCTION: ENGINE 0x10232340
// FUNCTION: ENGINE 0x101F3090
// FUNCTION: ENGINE 0x101F30E0
// FUNCTION: ENGINE 0x101F3260
